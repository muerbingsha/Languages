#include <stdio.h>

void hello(int a);
void* goodbye(int *a);

int main(){
	int a = 10;
    hello(a);
    
	int *b;
	b = goodbye(&a);
	
	printf("finally %d \n", *b);

	return 0;

}

void hello(int a){
    printf("hello: %d \n", a);
    return;
}

void* goodbye(int *a){
    printf("goodbye %d \n", *a);
    return a;        //int *
}
