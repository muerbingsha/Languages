/* Author: Shark
 */

#include "poll_common.h"


int createClient(char *ip, int port);
int readWrite(int client, int timeout);

int main(int argc, char *argv[]){
    int client = createClient(IP, PORT);
    readWrite(client, 5000);
    return 0;
}


int createClient(char *ip, int port){
    int client = socket(AF_INET, SOCK_STREAM, 0);
    if(client == -1){
        perror("socket() failed\n");
        exit(-1);
    }
    
    struct sockaddr_in s_addr;
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &s_addr.sin_addr);
    int ret = connect(client, (struct sockaddr*)&s_addr, sizeof(struct sockaddr));
    if (ret == -1){
        perror("connect failed\n");
        exit(-1);
    }
    
    printf("connect %s : %d good\n", ip, port);
    
    return client;
}


int readWrite(int client, int timeout) {
    //缓存区
    char input[BUFSIZE], output[BUFSIZE];
    memset(input, 0, BUFSIZE);
    memset(output, 0, BUFSIZE);
    
    struct pollfd c_fds[2];
    
    //监听客户端
    c_fds[0].fd = client;
    c_fds[0].events = POLLIN;
    //监听终端输入
    c_fds[1].fd = STDIN_FILENO;
    c_fds[1].events = POLLIN;
    
    for(;;){
        int ret = poll(c_fds, 2, timeout);
        
        if (ret == -1) {
            perror("poll() failed\n");
            exit(-1);
            
        } else if (ret == 0){
            //printf("do something when nothing change\n");
            continue;
            
        } else if (ret > 0) {
            
            //客户端
            if (c_fds[0].revents & POLLIN) {
                int readBytes = read(client, input, BUFSIZE);
                if (readBytes == -1) {
                    perror("read() failed\n");
                    exit(-1);
                } else if (readBytes == 0) {
                    fprintf(stderr, "server is closed\n");
                    close(client);  //客户终端没有退出
                } else {
                    stWrite(client, output, readBytes);
                }
            }
            
            
            //终端
            if (c_fds[1].revents & POLLIN) {
                int readBytes = read(STDIN_FILENO, output, BUFSIZE);
                if (readBytes == -1){
                    perror("read() failed\n");
                    exit(-1);
                } else if (readBytes == 0){
                    /*SHUT_WR 关闭写
                     *SHUT_RD 关闭读
                     *SHUT_RDWR 关闭读写
                     */
                    shutdown(client, SHUT_WR);
                    continue;
                } else {
                    //printf("readBytes: %d\n", readBytes);
                    stWrite(client, output, readBytes);
                }
                
            }
            
        }
    }
    
    return 0;
}


