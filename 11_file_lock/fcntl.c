/* don't run well */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>


int main(int argc, char *argv[]) {
    pid_t pid;
    int ret;    //返回句柄
    struct flock lock;
    int fd;     //文件句柄
    
    pid = getpid();
    
    fd = open("text1.txt", O_CREAT | O_RDWR, 0644);
    if (fd < 0) {
        perror("open failed \n");
        return -1;
    }
    
    lock.l_len = 0;
    lock.l_start = 0;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    printf("%d try to lock file \n", pid);
    
    
    ret = fcntl(fd, F_SETLKW, &lock);
    if (ret < 0){
        perror("lock failed \n");
        return -1;
    }
    printf("%d locking file \n", pid);
    
    
    sleep(5);

    
    lock.l_type = F_ULOCK;
    ret = fcntl(fd, F_SETLK, &lock);
    if (ret < 0) {
        perror("unlock failed \n");
        return -1;
    }
    printf("%d unlock file \n", pid);
    
    
    return 0;
}

/*
#include <unistd.h>
#include <fcntl.h>
int fcntl(int fd, int cmd);
int fcntl(int fd, int cmd, long arg);
int fcntl(int fd, int cmd, struct flock *lock);

cmd
 //文件句柄
 F_DUPFD
 F_GETFD
 F_SETFD
 
 //文件状态
 F_GETFL
 F_SETFL
 
 //文件锁
 F_GETLK
 F_SETLK
 
 //文件锁（阻塞）
 F_SETLKW
 F_GETLKW
 
 F_GETOWN
 F_SETOWN
*/
