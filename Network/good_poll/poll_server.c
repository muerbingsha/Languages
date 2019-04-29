/* Author: Shark
 */

#include "poll_common.h"



/* poll
 * struct pollfd {
 *  int fd;
 *  short events;
 *  short revents;
 * }
 *
 * int poll(struct pollfd *fds, unsigned int nfds, int timeout);
 * @param fds 数组
 * @param nfds 监听数量
 * @param timeout 超时（决定进入ret==0）
 */

 /* list
  * 0       服务器
  * 1~1000  客户端
  * 10001   终端输入
  */


int createSocket(char *ip, int port);
int usePoll(stServer *s, int timeout);
int createClient(stServer *s, struct pollfd *list);
int readWrite(stServer *s, struct pollfd list[]);
int removeClient(stServer *s, struct pollfd *fds, int clientFd);
int broadcast(struct pollfd *fds, void *data, int dataLen, int avoidPlayer);


int main(int argc, char* argv[]){
    stServer *s = malloc(sizeof(stServer));
    bzero(s, sizeof(stServer));
    
    s->fd = createSocket(IP, PORT);
    usePoll(s, 5000);

    return 0;
}


int createSocket(char *ip, int port) {
    int serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFd == -1){
        perror("socket() failed\n");
        exit(-1);
    }
    
    struct sockaddr_in addr4;
    addr4.sin_family = AF_INET;
    addr4.sin_port = htons(port);
    inet_pton(AF_INET, ip, &addr4.sin_addr);
    int ret = bind(serverFd, (struct sockaddr *)&addr4, sizeof(struct sockaddr));
    if (ret == -1){
        perror("bind() failed\n");
        exit(-1);
    }
    
    ret = listen(serverFd, BACKLOG);
    if (ret == -1){
        perror("listen() failed\n");
        exit(-1);
    }
    
    printf("server create good! %s, %d \n", ip, port);
    
    return serverFd;
}


/* @param timeout
 * >0 阻塞等待（等多久进入ret==0）
 * 0  立即返回（立即进入ret==0)
 * -1 无限等待（永远不进入ret==0)
 */
int usePoll(stServer *s, int timeout){
    
    struct pollfd list[MAXCLIENTS+2];
    //监听服务器
    list[0].fd = s->fd;
    list[0].events = POLLIN;
    
    //监听终端
    list[MAXCLIENTS + 1].fd = STDIN_FILENO;
    list[MAXCLIENTS + 1].events = POLLIN;
    
    for (int i=0; i<MAXCLIENTS; i++){
        list[i+1].fd = -1;  //忽略
    }
 
    
    for (;;){

        int ret = poll(list, s->currentClients + 1, timeout);
        
        //poll返回值
        if (ret == -1) {
            perror("poll() failed\n");
            exit(-1);
        
        //0: 没有变化且超时
        } else if (ret == 0) {
            //printf("time out\n");
            continue;
            
        //>0: 变化的数量，遍历list，内核会给revents赋值,检查revents非空的元素
        } else if (ret > 0){

            //打印revents
            //printf("0x%x", list[0].revents);
            
            //服务器反馈
            if (list[0].revents & POLLIN) {
                if (createClient(s, list) == 0)
                    continue;
                
            } else if (list[0].revents & POLLPRI) {
                printf("POLLRDPRI\n");
                
            } else if (list[0].revents & POLLRDNORM) {
                printf("POLLRDNORM\n");
            } else if (list[0].revents & POLLRDBAND) {
                printf("POLLRDBAND\n");
                
            } else if (list[0].revents & POLLOUT) {
                printf("POLLOUT\n");
                
            } else if (list[0].revents & POLLWRBAND) {
                printf("POLLWRBAND\n");
                
            //error zone
            } else if (list[0].revents & POLLERR) {
                printf("POLLERR: some poll error occurred\n");
                
            } else if (list[0].revents & POLLNVAL) {
                printf("POLLNVAL: requested events invalid\n check socket\n");
                
            } else if (list[0].revents & POLLHUP) {
                printf("POLLHUP: file descriptor was hung up\n");
            }
        
            //客户端反馈
            if (s->currentClients != 0){
                readWrite(s, list);
            }
            
        }
    }
    
    return 0;
}


/*@return
 * -1 error
 * 0 continue for loop
 * >0 clientFd
 */
int createClient(stServer *s, struct pollfd *list){
    //客户地址容器
    struct sockaddr_in c_addr;
    socklen_t c_addrlen = sizeof(c_addr);
    
    int clientFd = accept(s->fd, (struct sockaddr *)&c_addr, &c_addrlen);
    if (clientFd == -1){
        if (errno == EINTR){
            printf("interrupted by a signal");
            return 0;
        }
        perror("accept() failed\n");
        exit(-1);
    }
    
    //放进poll列表中
    int i;
    for (i=1; i<MAXCLIENTS; i++){
        if (list[i].fd == -1){
            list[i].fd = clientFd;
            list[i].events = POLLIN;
            printf("welcome new player %s : %d \n", inet_ntoa(c_addr.sin_addr), ntohs(c_addr.sin_port));
        
            printf("list[%d].fd: %d\n", i, list[i].fd);
            break;
        }
    }
    if (i == MAXCLIENTS){
        fprintf(stderr, "accept new player failed for reach max connection\n");
        exit(-1);
    }
    
    s->currentClients++;
    
    return clientFd;
}


int readWrite(stServer *s, struct pollfd list[]){
    //缓存区
    char input[BUFSIZE], output[BUFSIZE];
    memset(input, 0, BUFSIZE);
    memset(output, 0, BUFSIZE);
    
    for(int i=1; i<MAXCLIENTS; i++){
        
        if (list[i].fd != -1 && list[i].revents & POLLIN){
            int curentPlayer = list[i].fd;
            
            printf("msg from client %d\n", list[i].fd);
            int readBytes = read(list[i].fd, input, BUFSIZE);
            if (readBytes == -1){
                perror("read() failed\n");
                exit(-1);
                
            //玩家下线
            } else if (readBytes == 0) {
                removeClient(s, list, i);
            
            //玩家数据
            } else {
                write(STDOUT_FILENO, input, readBytes);
                
                //广播
                broadcast(list, input, readBytes, curentPlayer);
            }
        }
    }
    
    return 0;
}

//用户只需关注这3个变量
int removeClient(stServer *s, struct pollfd *fds, int clientFd){
    printf("client %d offline\n", clientFd);
    s->currentClients--;
    fds[clientFd].fd = -1;
    fds[clientFd].events = 0;
    return 0;
}

/* @return
 * -1 no broadcast;
 */
int broadcast(struct pollfd *fds, void *data, int dataLen, int avoidPlayer){
    for(int i=1; i<MAXCLIENTS; i++){
        if (fds[i].fd != -1 && fds[i].fd != avoidPlayer){
            return stWrite(fds[i].fd, data, dataLen);
        } else {
            return -1;
        }
    }
    return -1;
}
