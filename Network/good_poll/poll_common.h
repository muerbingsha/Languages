/* Author: Shark
 */

#include <sys/event.h>
#include <arpa/inet.h>  //inet_pton
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>      //perror
#include <poll.h>
#include <errno.h>      //errno
#include <unistd.h>     //STDIN_FILEMO
#include <string.h>     //memset

#define PORT 9090
#define IP "127.0.0.1"
#define BACKLOG 20
#define MAXCLIENTS 1000
#define BUFSIZE 2048

typedef struct _st_server{
    int fd;
    int pid;
    int currentClients;
} stServer;


//@return
// >0 已写的字节数
int stWrite(int fd, void *buf, int bufSize){
    
    int w = write(fd, buf, bufSize);
    if(w == -1){
        perror("write() failed\n");
        exit(-1);
    } else {
        //printf("w: %d\n", w);
        return w;
    }
    
}
