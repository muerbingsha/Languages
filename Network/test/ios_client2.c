
#include "ios_client2.h"

//serer info
#define INFO_MAX_CONNECTION "server reaches max connection"


stClient* create_client(){
    stClient *c = (stClient *)malloc(sizeof(stClient));
    if (c == NULL){
        perror("client create failed\n");
        exit(-1);
    }
    memset(c, '\0', sizeof(stClient));
    
    c->timeout.tv_sec = 10;
    c->timeout.tv_usec = 0;
    return c;
}
void test() {
    printf("good\n");
    
}
int connect_server(stClient *c){
    
    printf("c= %d\n", c->timeout.tv_sec);
    c->fd = socket(AF_INET, SOCK_STREAM, 0);
    //check(c->fd, "socket failed\n");
    if(c->fd == -1) {
        perror("socket error\n");
        return -1;
    }
    set_nonblock(c->fd);
    
    struct sockaddr_in addr4;
    addr4.sin_family = AF_INET;
    addr4.sin_port = htons(PORT);
    
    addr4.sin_addr.s_addr = inet_addr(IP);
    
    int ret = connect(c->fd, (struct sockaddr*)&addr4, sizeof(struct sockaddr));
   // check(ret, "connect failed\n");
    if( ret == -1) {
        perror("socket error\n");
        return -1;
    }
    //No route to host
    //Network is unreachable
    //Connection refused
    write(c->fd, "hello\n", sizeof("hello\n"));
    printf("connect good\n");
    return 0;
}

void pulse(stClient *c) {
    //while(1){
    
        fd_set changes;
        FD_ZERO(&changes);
        FD_SET(c->fd, &changes);
        
        int num = select(1, &changes, NULL, NULL, &c->timeout);
        if (num == -1) {
            perror("select error");
            
        } else if (num == 0){
            printf("timeout\n");
            
        } else {
            if(FD_ISSET(c->fd, &changes)){
                bzero(c->input, BUFSIZE);
                int ret = recv(c->fd, c->input, BUFSIZE, 0);
                
                if (ret == -1){
                   perror("recv from server failed\n");
                    
                } else if (ret == 0){
                    printf("server is out\n");
                    //客户端退出
                    
                    
                } else {
                    
                    if(strncmp(c->input, INFO_MAX_CONNECTION, 29) == 0){
                        printf("%s\n", c->input);
                        close(c->fd);
                        exit(-1);
                    }
                
                }
            }
        }
    
    //}
    /*
    char *msg = "hello";
    sprintf(output, "%s\n", msg);
    int ret = send(c->fd, output, BUFSIZE, 0);
    check(ret, "send to server failed\n");

    bzero(input, BUFSIZE);
    ret = recv(c->fd, input, BUFSIZE, 0);
    check(ret, "recv failed\n");
    
    bzero(output, BUFSIZE);
    sprintf(output, "Hello World");
    ret = write(c->fd, output, BUFSIZE);
    check(ret, "write failed\n");
     */
}

void set_nonblock(int fd) {
    int flags = fcntl(fd, F_GETFL);
    check(flags, "fcntl get failed\n")
    flags |= O_NONBLOCK;
    int ret = fcntl(fd, F_SETFL);
    check(ret, "nonblock failed\n");
    
}


