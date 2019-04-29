#include <stdio.h>
#define SIG_DFL ((void(*)(int))0)
#define SIG_IGN ((void(*)(int))1)

int main() {
    int a = (int) SIG_DFL;
    int b = (int) SIG_IGN;

    printf("a = %d \n", a);  //0
    printf("b = %d \n", b);  //1

    return 0;
}
