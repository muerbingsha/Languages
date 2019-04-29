#include <sys/file.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>
                                        
int main (int argc, char ** argv)
{
    pid_t p;
    p = fork();
    if ( p > 0 ) {
        printf ( "parent begin\n" ) ;
        sleep(10);
        printf ( "parent exit\n" ) ;
        
        exit ( 0 ) ;
    } else if (p ==0) {
        printf ( "child begin\n" ) ;
        sleep(50);
        printf ( "child exit\n" ) ;
        
        return 0 ;
    } else (p < 0) {
        printf("error \n");
        return 0;
    }
    
}
