#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  //open()

int main(int argc, char* argv[]){

	int fd = open("/dev/ptyw4", O_RDWR);
	if (fd == -1){
        perror("open() failed\n");
        return -1;
	}
    return 0;
}
