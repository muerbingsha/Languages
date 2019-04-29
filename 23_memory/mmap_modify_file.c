/*
 * mmap file to memory
 * ./mmap1 data.txt
 */
#include <stdio.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int fd = -1;
    struct stat fs;
    
    char *mm = NULL;
    
    fd = open(argv[1], O_RDWR);
    if (fd < 0) {
        fprintf(stderr, "open %s fail\n", argv[1]);
        exit(-1);
    }
    
    if (stat(argv[1], &fs) < 0) {
        fprintf(stderr, "stat %s fail\n", argv[1]);
        goto err;
    }
    
    /* 将文件映射至进程的地址空间 */
    mm = (char *)mmap(NULL, fs.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mm == (char *)-1) {
        fprintf(stderr, "mmap fail\n");
        goto err;
    }
    
    /* 映射完后, 关闭文件也可以操纵内存 */
    close(fd);
    printf("after: \n%s", mm);
    
    mm[5] = '$';
    if (msync(mm, fs.st_size, MS_SYNC) < 0) {
        fprintf(stderr, "msync fail\n");
        goto err;
    }
    
    return 0;
    
err:
    if (fd > 0)
    close(fd);
    
    if (mm != (char *)-1)
    munmap(mm, fs.st_size);
    
    return -1;
}
