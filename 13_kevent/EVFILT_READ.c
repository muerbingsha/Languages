#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>

#include <sys/event.h>


void turn_on_flags(int fd, int flags) {
    int ret;
    ret = fcntl(fd, F_GETFL);
    if (ret < 0) {
        perror("get fd flag failed \n");
        exit(1);
    }
    
    //新的状态
    ret |= flags;
    if (fcntl(fd, F_SETFL, ret) < 0 ) {
        perror("set fd flag failed \n");
        exit(1);
    }
}



const static int FD_NUM = 2;  //swift: static let FD_NUM: Int = 2
const static int BUFFER_SIZE = 1024;

int main(int argc, char *argv[]) {
    struct kevent changes[FD_NUM];  //监听列表
    struct kevent events[FD_NUM];   //就绪列表
    
    
    int kq = kqueue();
    //c don't have bool
    //-1 false
    //0 true
    if (kq == -1) {
        perror("creat kqueue failed \n");
        return -1;
    }
    printf("create kqueue good \n");
    
    
    int in = STDIN_FILENO;    //键盘输入
    int out = STDOUT_FILENO;  //屏幕输出
    
    //设为非阻塞
    turn_on_flags(in, O_NONBLOCK);
    turn_on_flags(out, O_NONBLOCK);
    
    //注册监听
    int k = 0;
    EV_SET(&changes[k++], in, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, &in);
    EV_SET(&changes[k++], out, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, &out);
 
    //printf("k: %d", k);   // k = 1
    //k ++;                 // k = 2
    
    
    
    int nev, nread, nwrite = 0; //发生事件数量， 已读字节数， 已写字节数
    
    char buffer[BUFFER_SIZE];
    
    while(1) {
        /* kevent函数 */
        nev = kevent(kq, changes, FD_NUM, events, FD_NUM, NULL);  //1
        
        if (nev <= 0) {
            perror("failed to get events \n");
            return -1;
        }
        
        /* 跳出条件 打开会导致出错 *//*
        read(in, buffer, BUFFER_SIZE);
        if (strncmp(buffer, "quit", 4) == 0){
            break;
        } */

        for (int i = 0; i< nev; i++) {
         
            struct kevent e = events[i];
            if (e.flags & EV_ERROR) {
                perror("event error");
                return -1;
            }
            
            
            int e_fd = *((int *)e.udata);  //1
            
            
            //输入流， 缓冲区还有空间
            if (e_fd == in && nread < BUFFER_SIZE) {
                //e_fd = 0 / in = 0
            
                int new_nread = read(e_fd, buffer + nread, sizeof(buffer) - nread);
                //-1 出错，0字节也是正常的
                if (new_nread <= 0) {
                    perror("read failed \n");
                    return -1;
                }
                nread += new_nread;     //递增已读字节数
                
            }
            
            //输出流，
            if (e_fd == out && nread > 0 ) {
                if ((nwrite = write(out, buffer, nread)) <= 0){
                    perror("write failed \n");
                }
                memmove(buffer, buffer + nwrite, nwrite);
                nread -= nwrite;        //减去已写的字节数B
            }
        }
        
    }
    
    return 0;
}


/*
 struct kevent {
 // identifer for this event
 uintptr_t   ident;
 // filter for event, 事件监听类型，如 EVFILT_READ, EVFILT_WRITE, EVFILT_TIMER
 int16_t     filter;
 // general flags，事件操作类型， 如EV_ADD, EV_ENABLE, EV_DISABLE
 uint16_t    flags;
 // filter-specific flags, 事件监听的操作类型
 uint32_t    fflags;
 // filter-specfic data
 uintptr_t   data;
 // opaque user data identifier
 void        *udata;
 }
 */

//便利宏，初始化kevent
//EV_SET(&key, ident, filter, flags, fflags, data, udata);

/*
 int kevent(int kq,
 const strct kevent *change_list,
 int nchanges,
 struct kevent *event_list,
 int nevents,
 const struct timespect *timeout);
 */
