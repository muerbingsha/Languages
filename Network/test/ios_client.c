
#include "ios_client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/time.h>
//serer info
#define BUFSIZE 1024
#define INFO_MAX_CONNECTION "server reaches max connection"
typedef struct _dClient {
    int fd;
    char input[BUFSIZE];
    char output[BUFSIZE];
    struct timeval timeout;
} dClient;


dClient* getClient(){
    dClient *c = (dClient *)malloc(sizeof(dClient));
    if (c == NULL){
        perror("client create failed\n");
        exit(-1);
    }
    memset(c, '\0', sizeof(dClient));
    
    c->timeout.tv_sec = 10;
    c->timeout.tv_usec = 0;
    return c;
}

int what(int argc, char *str) {
    int port = 9501;
    int fd = -1;
    char buf[1024] = {0};
    if (argc == 2) port = strtol(str, NULL, 10) ;
        

    dClient * c = getClient();
    if((fd = open("log.txt",O_RDWR|O_CREAT,0777))== -1 ) {
        perror("socket error\n");
        return -1;
    }
 
    printf("c= %ld\n", c->timeout.tv_sec);
  
int sockFd = socket(AF_INET, SOCK_STREAM, 0);
    //check(c->fd, "socket failed\n");
    if(sockFd == -1) {
        perror("socket error\n");
        return -1;
    }
    //    set_nonblock(c->fd);
    
    struct sockaddr_in addr4;
    addr4.sin_family = AF_INET;
    addr4.sin_port = htons(port);
    
    addr4.sin_addr.s_addr = inet_addr("192.168.0.102");
    
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
    read(c->fd, buf, sizeof(buf));
    printf("buf = %s\n", buf);
    printf("connect good\n");
    close(c->fd);
    return 0;
}

