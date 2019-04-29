/* 一对一， 收发消息次序固定 */

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>



int main() {
    
    //create 3 args
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0 ) {
        perror("create server failed \n");
        return -1;
    } else {
        printf("create server good \n");
    }
    
    

    struct sockaddr_in addr4;
    memset(&addr4, 0, sizeof(addr4));
    addr4.sin_family = AF_INET;
    addr4.sin_port = htons(9888);
    addr4.sin_addr.s_addr = inet_addr("192.168.0.103");
    addr4.sin_len = sizeof(addr4);

    
    
    //bind 3 args
    int b = bind(server, (struct sockaddr *)&addr4, sizeof(struct sockaddr));
    if (b < 0) {
        perror("bind server failed. Check ip/port/program \n");
        return -1;
    } else {
        printf("bind server good \n");
    }
    
    //listen 2 args
    //@param 5: 队列的大小。完成tcp三次握手，还没有accept的连接放在队列里，最大放5个，超过出错。
    int l = listen(server, 5);
    if (l < 0){
        perror("listen server failed \n");
        return -1;
    } else {
        printf("listen good \n");
    }
    
    
    //accept 3 args
    struct sockaddr_in c_addr;  //客户地址容器
    socklen_t c_addr_len;       //客户地址长度容器
    
    //accept没有循环，只接受一个客户端
    int c_fd = accept(server, (struct sockaddr *)&c_addr, &c_addr_len);
    if (c_fd < 0) {
        perror("accept failed \n");
        return -1;
    } else {
        printf("欢迎新客户，id号：%d， 地址：%s : %d \n",
               c_fd,
               inet_ntoa(c_addr.sin_addr),
               ntohs(c_addr.sin_port));
    }
    
    
    
    //两个缓存区,
    char input[1024];   //CFReadStream  / NSInputStream
    char output[1024];  //CFWriteStream / NSOutputStream
    
    
    //ios 封装Runloop，1）不需要自己写while；2）为了美观，while比较丑陋；3）为了检测，while用特殊标记Runloop，出错好定位。
    
    /*
     * 提示信息
     * 发
     * 收
     */
    while(1) {
        //1 - 清空缓存区
        bzero(input, 1024);
        bzero(output, 1024);
        
        //2 - 提示信息
        printf("------input msg to client------\n");
        
        //3 - 发(send 4 args, 阻塞）
        scanf("%s", output);
        send(c_fd, output, 1024, 0);
        
        //4 - 收(recv 4 args，阻塞）
        long byte_num = recv(c_fd, input, 1024, 0);
        if (byte_num <= 0 ){
            perror("receive failed \n");
            return -1;
        } else {
            printf("[%d say]: %s\n", c_fd, input);
        }
    }
    
    return 0;
}
