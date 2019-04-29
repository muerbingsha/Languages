#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <time.h>
#include <syslog.h>


int init_daemon(void) 
{
    /*
     * MARK: 父进程区
     */

	int pid;
    //getpid() 7698

	//忽略终端I/O信号，STOP信号
	signal(SIGTTOU,SIG_IGN); //当Background Group的进程尝试写Terminal的时候发送
	signal(SIGTTIN,SIG_IGN); //当Background Group的进程尝试读取Terminal的时候发送
	signal(SIGTSTP,SIG_IGN); //uspend Key，一般是Ctrl+Z。发送给所有Foreground Group的进程
	signal(SIGHUP,SIG_IGN);  //送给具有Terminal的Controlling Process，当terminal被disconnect时候发送
	
    
    
	pid = fork();
	if(pid > 0) {
        //父进程退出
        //getpid() 7698
        
		exit(0);
	} else if(pid < 0) {
		return -1;
	}
    
    
    
    /*
     * MARK: 子进程区
     */
	//建立一个新的进程组,在这个新的进程组中,子进程成为这个进程组的首进程,以使该进程脱离所有终端
	setsid();
 
    
    //getpid() 7699
    //子进程再创建一个子进程
	//保证该进程不是进程组长，同时让该进程无法再打开一个新的终端
	pid = fork();
	if( pid > 0) {
        //getpid() 7699
		exit(0);
	} else if( pid < 0) {
		return -1;
	}
 
    
    /*
     * MARK: 孙子进程区 (守护进程）
     */
    //getpid() 7700
	//关闭所有从父进程继承的不再需要的文件描述符
	for(int i = 0; i < NOFILE; close(i++));
 
	//改变工作目录，使得进程不与任何文件系统联系
	chdir("/");
 
	//将文件当时创建屏蔽字设置为0
	umask(0);
 
	//忽略SIGCHLD信号
	signal(SIGCHLD,SIG_IGN); 
	
	return 0;
}
 
int main() 
{ 
	time_t now;
	init_daemon();
    
    system("ps -o pid,ppid,state,command");
    
    // 系统日志
    // /var/log
    // /etc/syslog_conf
	// 无效 syslog(LOG_USER|LOG_INFO,"TestDaemonProcess! \n");
    /*
	while(1) { 
		sleep(8);
		time(&now); 
		syslog(LOG_USER|LOG_INFO,"SystemTime: \t %s \t\t\n", ctime(&now));
	} */
    
    
}


