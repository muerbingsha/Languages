#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#include <unistd.h>
#include <fcntl.h>


int main(int argc, char *argv[]) {
    int fd; //文件句柄
    int kq;
    int nev;
    
    struct kevent ev;
    static const struct timespec tout = {1, 0};
    
    //打开文件
    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        err(1, "Cannot open %s \n", argv[1]);
    }
    
    if ((kq = kqueue()) == -1) {
        err(1, "Create kqueue failed \n");
    }
    
    
    /*
     * 监听类型9：EVFILT_TIMER / EVFILT_VNODE / EVFILT_READ / EVFILT_WRITE / EVFILT_AIO / EVFILT_SIGNAL / EVFILT_USER / EVFILT_PROC / EVFILT_PROCDESC
     * 操作类型：EV_ADD / EV_ENABLE / EV_DISABLE / EV_ERROR / EV_EOF / EV_CLEAR / EV_DELETE / EV_DISPATCH / EV_RECEIPT / EV_ONESHOT
     */
    EV_SET(&ev, fd,
           EVFILT_VNODE, //监听文件操作
           EV_ADD | EV_ENABLE | EV_CLEAR,
           NOTE_DELETE | NOTE_WRITE | NOTE_EXTEND | NOTE_ATTRIB | NOTE_LINK | NOTE_RENAME | NOTE_REVOKE, //具体监听
           0,
           0);
    
    //把kqueue和struct kevent绑在一起
    if (kevent(kq, &ev, 1, NULL, 0, &tout) == -1) {
        err(1, "kevent failed \n");
    }
    
    for (;;) {
        nev = kevent(kq, NULL, 0, &ev, 1, &tout);
        if (nev == -1) {
            err(1, "kevent failed \n");
        }
        
        if (nev == 0) {
            continue; //没有就绪事件
        }
        
        //文件有操作
        if (ev.fflags & NOTE_DELETE) {
            printf("delete \n");
            ev.fflags &= ~NOTE_DELETE;
        }
        
        if (ev.fflags & NOTE_WRITE) {
            printf("written \n");
            ev.fflags &= ~NOTE_WRITE;
        }
        
        if (ev.fflags & NOTE_EXTEND) {
            printf("extended \n");
            ev.fflags &= ~NOTE_EXTEND;
        }
        
        if (ev.fflags & NOTE_ATTRIB) {
            printf("attrib \n");
            ev.fflags &= ~NOTE_ATTRIB;
        }
        
        if (ev.fflags & NOTE_LINK) {
            printf("hardlinked ");
            ev.fflags &= ~NOTE_LINK;
        }
        
        if (ev.fflags & NOTE_RENAME) {
            printf("renamed ");
            ev.fflags &= ~NOTE_RENAME;
        }
        
        if (ev.fflags & NOTE_REVOKE) {
            printf("revoked ");
            ev.fflags &= ~NOTE_REVOKE;
        }
        
        printf("\n");
        if (ev.fflags)
            warnx("unknown event 0x%x\n", ev.fflags);
        
        
    }

}
