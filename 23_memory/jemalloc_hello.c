#include <stdio.h>
#include <jemalloc/jemalloc.h>

//
// 测试 jemalloc hello world
//
int main(int argc, char * argv[]) {
    
    int *p1 = je_malloc(sizeof(int));
    if (p1 == NULL){
        puts("jemalloc() failed \n");
        return EXIT_FAILURE;
    }
    printf("p1 = %p, d = %d \n", p1, *p1);
    je_free(p1);
    
    int *p2 = je_calloc(2, sizeof(int));
    if (p2 == NULL) {
        puts("je_calloc() failed\n");
        return EXIT_FAILURE;
    }
    printf("p2 = %p, d = %d \n", p2, *p2);
    
    p2 = je_realloc(p2, sizeof(int));
    if (p2 == NULL) {
        puts("je_realloc() failed \n");
        return EXIT_FAILURE;
    }
    printf("p2 = %p, d = %d \n", p2, *p2);
    je_free(p2);
    
    return EXIT_SUCCESS;
   
     
}

