#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>



int main(int argc, char **argv) {
    int fd;
    char buf[80] = {0};
    pid_t pid;
    
	unlink("aa");
	mkfifo("aa", 0777);
    
	pid = fork();
    
	if (pid == 0) {
        //child1

        sprintf(buf, "child1 pid=%d, hello\n", getpid());
        fd = open("aa", O_WRONLY);
        write(fd, buf, sizeof(buf));
        close(fd);
        
    } else if (pid > 0){

		pid = fork();
        
		if (pid == 0) {
            //child2
 
        	sprintf(buf, "child2 pid=%d, hello\n", getpid());
            printf("%s\n", buf);
            fd = open("aa", O_WRONLY);
            write(fd, buf, sizeof(buf));
            close(fd);
        } else if (pid > 0){

            //father
            fd = open("aa", O_RDONLY);
            read(fd, buf, sizeof(readbuf));
            printf("buf = \n%s\n", buf);
            close(fd);
        }
	
	}


    
    return 0;
}
