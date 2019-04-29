#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>


int main(int argc, char* argv[]) {
    int fd;
    unsigned char key_val;
    struct pollfd fds;
    int ret;
    
    //linux在操作硬件设备时，屏蔽了硬件的基本细节，只把硬件当作文件来操作，而所有的操作都是以open
    fd = open("/dev/buttons", O_RDWR);
    if (fd == -1){
        perror("open failed\n");
        return -1;
    }
    
    fds.fd = fd;
    fds.events = POLLIN;
    while(1){
        ret = poll(&fds, 1, 5000);
        if (ret == -1){
            perror("poll() failed\n");
            return -1;
        } else {
            read(fd, &key_val, 1);
            printf("key_val = 0x%x\n", key_val);
        }
    }
    
    return 0;
}
