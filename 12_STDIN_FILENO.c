#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char buf_read[1024];
    char buf_write[1024];
    
    while(1) {
        memset(buf_read, 0, sizeof(buf_read));
        memset(buf_write, 0, sizeof(buf_write));
        
        //打印屏幕输出信息
        char input[100] = "input message \n";
        write(STDOUT_FILENO, input, sizeof(input));
        
        read(STDIN_FILENO, buf_read, sizeof(buf_read));
        
        if (strncmp(buf_read, "quit", 4) == 0) {
            break;
        }
        
        strcpy(buf_write, buf_read);
        char output[100] = "see the outputs \n";
        write(STDOUT_FILENO, output, sizeof(output));
        write(STDOUT_FILENO, buf_write, strlen(buf_write));
    }
    
    return 0;
}
