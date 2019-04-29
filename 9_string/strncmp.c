#include <stdio.h>
#include <string.h>


/* strncmp */
int main(){
	printf("%d", strncmp("A", "b", 1));      //从第一个字符的ASCII码开始比较， A -> 65, B -> 98, return -33，不同直接返回，相同继续下一个。
	printf("%d", strncmp("int", "int", 3));  //0
	return 0;
}
