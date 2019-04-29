#include <string.h>


int main(int argc, char **argv){
    
    char *src = "This is good!";
    char *des;
    
    des = strdup(src);
    printf("now see des %s \n", des);
    
    char from[] = "I'm ios developer";
    char to[18];
    //Abort trap 6
    //char to[1];
    //char to[17]; 字符串要保存结束符'\0'
    
    
    strcpy(to, from);
    printf("length of from %lu \n", strlen(from)); //17
    printf("sizeof from %lu \n", sizeof(from)); //18
    printf("now see to %s \n", to);
    
    return 0;
}
