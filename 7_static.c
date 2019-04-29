#include <stdio.h>

int fun(int a){
	static int f = 1; /*静态变量，1）生命周期随源程序；2）作用域只在该函数内部*/
	f = f * a;
	return f;
}

int fun2(int a){
	int f = 1;    /*局部变量，存在stack上，生命周期随函数*/
	f = f * a;
	return f;
}

int main(){
	for (int i = 1; i<=5; i++) {
	printf("fun(%d): %d \n", i, fun2(i));
	}	
	return 0;
}
