/* issue undefined symbol in architecture x86_64
reason: inline is c++ 
solution: add extern "C"

issue: expected (
solution: change file suffix from .c to .cc
*/

#include <stdio.h>


//#define Expression(var1, var2) ((var1 + var2) * (var1 - var2))

#ifdef __cplusplus
extern "C" {
#endif

inline int judge(int a) {
    return (a % 2 > 0) ? 1 : 0;
}

int main(){
    int i = 0;
    for (i = 0; i<100; i++){
        printf("\n %d 奇偶性:  %d \n", i, judge(i));
    }
}

    
    
    
    
#ifdef __cplusplus
}
#endif
