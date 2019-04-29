/****************************************************** 
* Program Assignment : 输出进程ID和用户基本信息
* Author: Densin.Tian
* Date: 2015/05/02  
* Description: 
*****************************************************/
 
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char **argv){
    pid_t my_pid, parent_pid;
    uid_t my_uid, parent_uid;
    gid_t my_gid, parent_gid;
    
    struct passwd *my_info;
    
    my_pid      = getpid();
    parent_pid  = getppid();
    my_uid      = getuid();
    parent_uid  = geteuid();
    my_gid      = getgid();
    parent_gid  = getegid();
    
    my_info     = getpwuid(my_uid);
    
    printf("===================================\n");
    printf("        Process Information        \n");
    printf("===================================\n");
    printf("Process ID : %ld\n", (long)my_pid);
    printf("Parent  ID : %ld\n", (long)parent_pid);
    printf("User    ID : %ld\n", (long)my_uid);
    printf("Effective User  ID : %ld\n", (long)parent_uid);
    printf("Group   ID : %ld\n", (long)my_gid);
    printf("Effective Group ID : %ld\n", (long)parent_gid);
    
    
    if(my_info){
        printf("===================================\n");
        printf("           User Information        \n");
        printf("===================================\n");
        printf("My Login Name : %s\n", my_info->pw_name);
        printf("My Password   : %s\n", my_info->pw_passwd);    
        printf("My User ID    : %ld\n", (long)my_info->pw_uid);
        printf("My Group ID   : %ld\n", (long)my_info->pw_gid);
        printf("My Real Name  : %s\n", my_info->pw_gecos);
        printf("My Home Dir   : %s\n", my_info->pw_dir);
        printf("My Work Shell : %s\n", my_info->pw_shell);
    }
 
	 return 0; 
}


