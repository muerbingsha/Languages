#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>




int main() {
    //两个文件描述符，f[0]输入，f[1]输出
    int fd[2] = {0, 0};
    if(pipe(fd) != 0 ) {
        perror("pipe failed \n");
        exit(1);
    }
    
    //父子进程
    pid_t id = fork();
    if (id == 0) {
        printf("child process \n");
        sleep(2);
        
        const char *msg = "Hello \n";
        close(fd[0]); //关闭读
        
        int count = 3;
        while(count--){
            size_t size = write(fd[1], msg, strlen(msg));
            printf("size: %zu \n", size);
            
            sleep(1);
            printf("child is waiting... \n");
        }
        close(fd[1]);
        exit(1);
        
    } else {
        printf("father process \n");
        sleep(2);
        close(fd[1]); //关闭写
        
        char buf[1024];
        int count = 3;
        while(1){
            printf("father is reading... \n");
            
            size_t len = read(fd[0], buf, 1024);
            if (len > 0 ) {
                buf[len] = '\0';
                printf("child say: %s \n", buf);
            } else if (len == 0) {
                printf("read the end of pipe \n");
                break;
            } else {
                perror("error \n");
                exit(1);
            }
        }
        close(fd[0]);
        int status = 0;
        pid_t _pid = waitpid(id, &status, 0);
        if (_pid == id) {
            printf("wait success for child \n");
            printf("exit code: %d, exit signal: %d \n", (status >> 8) & 0xff, status&0xff);
        } else {
            perror("wait \n");
        }
        
        exit(0);
        
    }
    
    return 0;
    
}
