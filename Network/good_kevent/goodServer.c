
/* Author: Shark
 */

#include "goodCommon.h"




void setNonBlock(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    exit_if(flags<0, "fcntl failed");
    
    int r = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    exit_if(r<0, "fcntl failed");
}




void initServer(stServer *serv){
    
    if (serv->isRunning == -1) {
        printf("sever is alreayd inited \n");
        return;
    }
    memset(serv, 0, sizeof(*serv));
  
    serv->isRunning = 0;
     
    serv->host = (char *)SERVER_IP;  //类型转换const char* 为 char *
    serv->port = SERVER_PORT;
    serv->inputBufferSize = BUFFER_SIZE;
    serv->outputBufferSize = BUFFER_SIZE;
    serv->maxClients = MAX_CLIENTS;
    serv->backlog = BACKLOG;
    serv->timeout.tv_sec = 10;  //秒
    serv->timeout.tv_nsec = 0;  //纳秒
    serv->name = "gameServer";
}


void createServer(stServer *serv) {
    int sockFd = socket(AF_INET, SOCK_STREAM, 0);
    exit_if(sockFd < 0, "create failed");
    
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(serv->port);
    addr.sin_addr.s_addr = INADDR_ANY;
    
    int ret = bind(sockFd,(struct sockaddr *)&addr, sizeof(struct sockaddr));
    exit_if(ret < 0, "bind failed");
    
    ret = listen(sockFd, serv->backlog);
    exit_if(ret < 0, "listen failed");
    
    
    serv->fd = sockFd;
    printf("%s %d is ready at %s : %d \n", serv->name, serv->fd, serv->host, serv->port);

}


void createPlayer(stServer *serv, int fd) {
    stClient *player;
    player->fd = fd;
    
    //放入客户组中
    for (int i = 0; i < serv->maxClients; i++){
        if (serv->clients[i] == 0){
            printf("%d: ", i);
            serv->clients[i] = player;
            printf("fd %d \n\n\n\n", serv->clients[i]->fd);
            return;
        } else {
            printf("serv->clients[%d] = %d \n", i, serv->clients[i]->fd);
        }
    }
}


void handleAccept(stServer *serv){
    //地址容器
    struct sockaddr_in addr4;
    socklen_t addr4_len;
    
    /* accept 第一个地址有点问题 */
    int newFd = accept(serv->fd, (struct sockaddr *)&addr4, &addr4_len);
    exit_if(newFd < 0, "accept failed");
    //printf("accept new player %d from %s : %d \n", newFd, inet_ntoa(addr4.sin_addr), ntohs(addr4.sin_port));
    
    /* 得到客户端 地址信息，比accept能显出第一个 */
    int peerFd = getpeername(newFd, (struct sockaddr *)&addr4, &addr4_len);
    exit_if(peerFd < 0, "getpeername failed");
    printf("new player %d, %s : %d \n", newFd, inet_ntoa(addr4.sin_addr), ntohs(addr4.sin_port));
    
    /* 得到服务器 地址信息
    int sockFd = getsockname(newFd, (struct sockaddr *)&peerAddr, &peerAddrLen);
    exit_if(sockFd < 0, "accept failed");
    printf("sock %d, %s : %d \n", sockFd, inet_ntoa(peerAddr.sin_addr), ntohs(peerAddr.sin_port));
    */
    

    createPlayer(serv, newFd);
 
}


void daemonServer(){
    
}

void updateEvent(){
    
}

//try to simulte swift RunLoop
//but how to set general variables?
/*
void runloop(int (*callback)()){
    while(1){
        (*callback)();
    }
}

int add(int a) {
    return a;
}
*/

int main() {
    stServer *serv = malloc(sizeof(stServer) + sizeof(stClient) * MAX_CLIENTS);
    initServer(serv);
    createServer(serv);
    

    /*为什么一开始数组也有值
     *因为没有分配内存
    for (int i = 0; i < serv->maxClients; i++){
        if (serv->clients[i] == 0){
            printf("%d \n", i);
        } else {
            printf("serv->clients[%d] = %u \n", i, serv->clients[i]);
        }
    }*/
    
   
    
    
    int kq = kqueue();
    exit_if(kq < 0, "kqueue failed");
    struct kevent changes;
    
    //注册终端输入
    EV_SET(&changes, STDIN_FILENO, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    kevent(kq, &changes, 1, NULL, 0, NULL);
    
    //注册server监听
    //struvt kevent, ident,    filter,      flags, fflags, data, *udata
    EV_SET(&changes, serv->fd, EVFILT_READ, EV_ADD, 0,     0,    NULL);
    kevent(kq, &changes, 1, NULL, 0, NULL);
    
    struct kevent events[serv->maxClients];
    while (1) {
        int ret = kevent(kq, NULL, 0, events, serv->maxClients, &serv->timeout);
        exit_if(ret < 0, "kevent create failed \n");
        
        if (ret == 0){
            printf("kevent timeout\n");
            continue;
            
        } else if (ret > 0){
            for(int i = 0; i< ret; i++) {
                struct kevent current_event = events[i];
                if (current_event.ident == STDIN_FILENO) {
                    printf("input msg \n");
                    
                } else if (current_event.ident == serv->fd) {
                    handleAccept(serv);
                }
            }
        }
    }
    
}


