
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


int main() {
	struct rlimit l;
	memset(&l, 0, sizeof(l));

    //查看资源限制
    //CORE文件的最大字节数，0表示组织创建core文件
    int ret = getrlimit(RLIMIT_CORE, &l);
    if (ret < 0 ){
        printf("get RLIMIT_CORE error \n");
    } else {
        printf("get RLIMIT_CORE %llu \n", l.rlim_cur);
    }
    
    //设置资源限制
    l.rlim_cur = RLIM_INFINITY;
    l.rlim_max = RLIM_INFINITY;
    ret = setrlimit(RLIMIT_CORE, &l);
    if (ret < 0 ){
        printf("set RLIM_CORE error \n");
    } else {
        printf("set RLIM_CORE %llu \n", l.rlim_cur);
    }
    
    //查看是否更改成功s
    ret = getrlimit(RLIMIT_CORE, &l);
    if (ret < 0 ){
        printf("get RLIMIT_CORE error \n");
    } else {
        printf("get RLIMIT_CORE %llu \n", l.rlim_cur);
    }
	
    printf("\n");
    
    //CPU时间最大量值，超过此软限制，向该进程发送SIGXCPU信号
    ret = getrlimit(RLIMIT_CPU, &l);
    if (ret < 0 ){
        printf("get RLIMIT_CPU error \n");
    } else {
        printf("get RLIMIT_CPU %llu \n", l.rlim_cur);
    }
    
    //STACK：栈的最大字节长度
    ret = getrlimit(RLIMIT_STACK, &l);
    if (ret < 0 ){
        printf("get RLIMIT_STACK error \n");
    } else {
        printf("get RLIMIT_STACK %llu \n", l.rlim_cur);
    }
    
    //DATA：数据段的最大字节长度，初始化数据/非初始化数据/堆的总和
    ret = getrlimit(RLIMIT_DATA, &l);
    if (ret < 0 ){
        printf("get RLIMIT_DATA error \n");
    } else {
        printf("get RLIMIT_DATA %llu \n", l.rlim_cur);
    }
    
    //FSIZE：文件的最大字节长度，超过此限制，发送SIGXFSZ信号
    ret = getrlimit(RLIMIT_FSIZE, &l);
    if (ret < 0 ){
        printf("get RLIMIT_FSIZE error \n");
    } else {
        printf("get RLIMIT_FSIZE %llu \n", l.rlim_cur);
    }

    
    //一个进程能打开最大文件数
    ret = getrlimit(RLIMIT_NOFILE, &l);
    if (ret < 0 ){
        printf("get RLIMIT_NOFILE error \n");
    } else {
        printf("get RLIMIT_NOFILE %llu \n", l.rlim_cur);
    }
    
    //RSS：最大驻内存的字节长度(resident set size in bytes)
    ret = getrlimit(RLIMIT_RSS, &l);
    if (ret < 0 ){
        printf("get RLIMIT_RSS error \n");
    } else {
        printf("get RLIMIT_RSS %llu \n", l.rlim_cur);
    }
    
    
}
 


