/* 一对一， 收发消息次序固定 */

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0){
        perror("create client failed \n");
        return -1;
    } else {
        printf("create good \n");
    }
    
    struct sockaddr_in addr4;
    memset(&addr4, 0, sizeof(addr4));
    addr4.sin_len = sizeof(addr4);
    addr4.sin_family = AF_INET;
    addr4.sin_port = htons(9888);
    addr4.sin_addr.s_addr = inet_addr("192.168.0.103");
    
    
    char fromServer[1024];
    char toServer[1024];
    
    //connect 3 args
    int c = connect(server, (struct sockaddr *)&addr4, sizeof(struct sockaddr));
    if (c == 0) {
        printf("connect good \n");
        
        /*
         * 收
         * 提示信息
         * 发
         */
        while(1) {
            // 1 - 收
            int reply = recv(server, fromServer, 1024, 0);
            if (reply < 0) {
                perror("msg from server faild\n");
                return -1;
            } else {
                printf("[server]: %s \n", fromServer);
            }
            
            //2 - 提示
            printf("------reply to server------\n");
            
            //3 - 发
            scanf("%s", toServer);
            send(server, toServer, 1024, 0);
            
        }
    } else {
        perror("connect failed \n");
        return -1;
    }
    
    return 0;
    
}

