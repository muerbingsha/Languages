
/* Author: Shark
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/event.h>

#include <unistd.h>
#include <fcntl.h>

#include <stdbool.h>





#define exit_if(r, ...) if(r) {printf(__VA_ARGS__); printf("error no: %d error msg %s\n", errno, strerror(errno)); exit(1);}


/*----------------config----------------*/
#define SERVER_PORT 9988
const char *SERVER_IP = "192.168.0.102";
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 10000
#define BACKLOG 20


typedef struct _stClient {
    int fd;                 //id
    char *name;             //玩家名
    long long hashValue;    //hash值
    int transform;          //坐标
    char *host;
    short port;
    int state;              //玩家状态
}stClient;


typedef struct _stServer{
    int fd;                 //也放进来，方便函数传参 4
    char *name;             //8
    short port;             //2
    char *host;             //8
    int backlog;            //listen 队列数 4
    int inputBufferSize;    //4
    int outputBufferSize;   //4
    struct timespec timeout;//超时 16
    int isRunning;          //是否运行，初始化用 4
    
    int maxClients;         //最大连接数 4
    int currentPlayers;     //当前玩家数 4
    
    //玩家组
    //method 1:
    //stClient clients[MAX_CLIENTS];
    //uint32_t clients[MAX_CLIENTS]; //可以
    
    //method 2:
    //uint32_t clients[0];
    stClient *clients[0];   //softArray
    
    //method 3: uthash
}stServer; //80




enum clientState {
    CLIENT_STATE_CONNECT = 0,
    CLIENT_STATE_OFFLINE,
    CLIENT_STATE_ILLEGAL,   //异常客户，需要对其强制下线
};
