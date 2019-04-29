

#ifndef IOS_CLIENT2_H_
#define IOS_CLIENT2_H_

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/event.h>
#include <sys/time.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "ios_client2.h"

#define check(fd, errorMsg) { \
    if(fd == -1) { \
        perror(errorMsg); \
        exit(-1); \
    } \
}

#define IP "192.168.0.102"
#define PORT 9501
#define BUFSIZE 1024





typedef struct _stClient {
    int fd;
    char input[BUFSIZE];
    char output[BUFSIZE];
    struct timeval timeout;
} stClient;



stClient* create_client();
int connect_server(stClient *c);
void pulse(stClient *c);
void set_nonblock(int fd);
void test(void);

#endif /* ios_client2.h */
