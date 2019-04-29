//
// 知识点：__block
// 划重点：__block就是让闭包可以使用在闭包外定义的变量。


#import "block.h"

int global_i = 1;
static int static_global_j = 2;

void block() {
    
    static int static_k = 3;
    __block int val = 4;  //让闭包可以修改这个值，去掉__block修饰就会报错
    

    void (^myBlock)(void) = ^{
        global_i ++;
        static_global_j ++;
        static_k ++;
        val++; 
        NSLog(@"Block中 global_i = %d,static_global_j = %d,static_k = %d,val = %d",global_i,static_global_j,static_k,val);
    };
    
    global_i ++;
    static_global_j ++;
    static_k ++;
    val ++;
    NSLog(@"Block外 global_i = %d,static_global_j = %d,static_k = %d,val = %d",global_i,static_global_j,static_k,val);
    
    myBlock();
    

}

