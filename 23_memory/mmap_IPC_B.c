#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define BUF_SIZE 100

int main(int argc, char **argv) {
    int fd, nread, i;
    struct stat sb;
    char *mapped, buf[BUF_SIZE];

    for (i = 0; i < BUF_SIZE; i++) {
        buf[i] = '#';
    }

    /* 打开文件 */
    if ((fd = open(argv[1], O_RDWR)) < 0) {
        perror("open failed");
    }

    /* 获取文件的属性 */
    if ((fstat(fd, &sb)) == -1) {
        perror("fstat failed");
    }

    /* 私有文件映射将无法修改文件 */
    /*
    if ((mapped = (char *)mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == (void *)-1) {
        perror("mmap failed");
    }
    */
    //进程间通信实验
    if ((mapped = (char *)mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == (void *) -1) {
        perror("mmap() failed");
    }

    /* 映射完后, 关闭文件也可以操纵内存 */
    close(fd);

    /* 修改一个字符 */
    mapped[0] = 'H';
    mapped[1] = 'e';
    mapped[2] = 'l';
    mapped[3] = 'l';
    mapped[4] = 'o';
    
    mapped[5] = 'W';
    mapped[6] = 'o';
    mapped[7] = 'r';
    mapped[8] = 'l';
    mapped[9] = 'd';


  
    //不需要msync
    
    return 0;
}  
