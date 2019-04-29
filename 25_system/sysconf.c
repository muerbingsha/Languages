#include <stdio.h>
#include <unistd.h>
#define ONE_MB (1024 * 1024)

int main (void) {
    //cpu
    printf ("CPU num: %ld 个\n", sysconf (_SC_NPROCESSORS_CONF));
    printf("online CPU num: %ld\n", sysconf(_SC_NPROCESSORS_ONLN));
    
    //page
    long page_size = sysconf (_SC_PAGESIZE);
    printf("page size: %ld K\n", page_size / 1024 );
    long num_pages = sysconf (_SC_PHYS_PAGES);
    printf("page num: %ld 个\n", num_pages);
    
    long long mem = (long long) ((long long)num_pages * (long long)page_size);
    mem /= ONE_MB;
    printf("总共有 %lld MB 的物理内存 \n", mem);
    
    
    printf("The number of files max opened:: %ld\n", sysconf(_SC_OPEN_MAX));
    printf("The number of ticks per second: %ld\n", sysconf(_SC_CLK_TCK));
    printf("The max length of host name: %ld\n", sysconf(_SC_HOST_NAME_MAX));
    printf("The max length of login name: %ld\n", sysconf(_SC_LOGIN_NAME_MAX));
    
    printf("table size: %d \n", getdtablesize());
    
    printf("pid: %d \nparent id: %d \nsession id: %d \nuser id: %d \ngroupd id: %d\n", getpid(), getppid(), getsid(getpid()), getuid(), getgid());
    
    return (0);
}

