
/* Author: Shark
 */
#include "goodCommon.h"


void createClient(){
    struct sockaddr_in server_addr;
    server_addr.sin_len = sizeof(struct sockaddr_in);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    bzero(&(server_addr.sin_zero),8);
    
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    exit_if(server_fd<0, "client create failed \n");
    printf("client create good \n");
    
    char recv_msg[BUFFER_SIZE];
    char input_msg[BUFFER_SIZE];
    
    int c = connect(server_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in));
    exit_if(c<0, "client create failed \n");
    printf("client connect good \n");
}
    
    
int main(){
    pid_t p;
    for (int i=0; i<3; i++) {
        p = fork();
        if (p == -1){
            perror("fork() error\n");
            continue;
        } else if (p == 0){
            printf("children %d \n", getpid());
        } else {
            printf("father %d \n", getpid());
        }
    }
    
    //存活的进程都会执行，fork细胞分裂, 2^n个进程
    printf("------------\n");
    createClient();
    return 0;
}
