
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>

int main(int argc, char *argv[]){
    pid_t pid;
    int ret;
    int fd;
    
    pid = getpid();
    fd = open("text1.txt", O_CREAT | O_RDWR, 0644);
    if (ret < 0) {
        perror("open failed \n");
        return -1;
    }
    printf("%d try to lock file \n", pid);
    
    
    ret = flock(fd, LOCK_EX);
    if (ret < 0){
        perror("lock failed \n");
        return -1;
    }
    printf("%d locked file \n", pid);

    
    sleep(5);
    
    ret = flock(fd, LOCK_EX);
    if (ret < 0) {
        perror("unlock failed \n");
        return -1;
    }
    printf("%d unlock file \n", pid);
    
    
    return 0;
}
