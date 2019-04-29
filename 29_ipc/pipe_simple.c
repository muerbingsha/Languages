#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    int fd[2] = {0,0};
    pid_t p;
    char buf[20];
    
    if (pipe(fd) == -1){
        perror("pipe failed\n");
        exit(-1);
    }
    
    p = fork();
    if (p == -1){
        perror("fork failed\n");
        exit(-1);
    } else if (p == 0){
        //child
        close(fd[0]);
        sprintf(buf, "%s", "hello");
        write(fd[1], buf, 20);
    } else {
        //father
        close(fd[1]);
        read(fd[0], buf, 20);
        printf("%s\n", buf);
    }
}

