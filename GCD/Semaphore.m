//
// 知识点：GCD信号量
// Author: SharkDeng
// Github: muerbignsha


#include "Semaphore.h"

void sema() {
    //2个停车位，3个车子
    dispatch_semaphore_t s = dispatch_semaphore_create(1);
    dispatch_queue_t bgQueue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    
    __block long x = 0;
    
    //开3个线程
    dispatch_async(bgQueue, ^{
        dispatch_semaphore_wait(s, DISPATCH_TIME_FOREVER);
        NSLog(@"run task 1");
        NSLog(@"completer task 1");
        dispatch_semaphore_signal(s);
    });
    
    dispatch_async(bgQueue, ^{
        dispatch_semaphore_wait(s, DISPATCH_TIME_FOREVER);
        NSLog(@"run task 2");
        NSLog(@"completer task 2");
        dispatch_semaphore_signal(s);
    });
    
    
    dispatch_async(bgQueue, ^{
        dispatch_semaphore_wait(s, DISPATCH_TIME_FOREVER);
        NSLog(@"run task 3");
        NSLog(@"completer task 3");
        dispatch_semaphore_signal(s);
    });


    
    
}



