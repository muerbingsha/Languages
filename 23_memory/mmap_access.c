// 文件大小, mmap的参数len 都不能决定进程能访问的大小,
// 而是容纳文件被映射部分的最小页面数决定进程能访问的大小

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int fd,i;
    int pagesize, offset;
    char *p_map;
    struct stat sb;

    /* 取得page size */
    pagesize = sysconf(_SC_PAGESIZE);
    printf("pagesize is %d\n",pagesize);  //4096
    printf("pagesize %d \n", getpagesize());
        
    /* 打开文件 */
    fd = open(argv[1], O_RDWR, 00777);
    fstat(fd, &sb);
    printf("file size is %zd\n", (size_t)sb.st_size);

    offset = 0;
    p_map = (char *)mmap(NULL, pagesize * 2, PROT_READ|PROT_WRITE, MAP_SHARED, fd, offset);
    close(fd);

    p_map[sb.st_size] = '9';  /* 导致总线错误 */
    p_map[pagesize] = '9';    /* 导致段错误 */

    munmap(p_map, pagesize * 2);

    return 0;
}
