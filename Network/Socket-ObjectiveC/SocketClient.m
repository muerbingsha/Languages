#import "SocketClient.h"

@implementation SocketClient


//MARK: CFSocket TCP
//CFSocketCreate()
//CFSocketConnectToAddress()
- (void) create {
    
    CFSocketContext ctx = {0, //version, must be 0
        (__bridge void *)(self), NULL, NULL, NULL};
    _socket = CFSocketCreate(kCFAllocatorDefault,
                             PF_INET, //windows AF_INET == PF_INET while in unix/linux, AF -> BSD, PF -> POSIX
                             SOCK_STREAM, //SOCK_DGRAM -> udp
                             IPPROTO_TCP,
                             kCFSocketConnectCallBack, //method type
                             TCPServerConnectCallBack,
                             &ctx);
    if (_socket != nil) {
        NSLog(@"\n\r socket create successfully");
        
        //1
        struct sockaddr_in addr4;
        memset(&addr4, 0, sizeof(addr4));
        addr4.sin_len = sizeof(addr4);
        addr4.sin_family = AF_INET;
        
        //ip and port
        addr4.sin_addr.s_addr = inet_addr([@"192.168.1.2" UTF8String]);
        addr4.sin_port = htons(9503);
        
        //turn sockaddr_in to CFDataRef
        CFDataRef address = CFDataCreate(kCFAllocatorDefault, (UInt8 *) &addr4, sizeof(addr4));
        
        
        //2
        CFSocketError result = CFSocketConnectToAddress(_socket, address, -1);
        //if 3rd param is negative, means backgroud connection
        //I set 3rd param 5 and it prompt connect failed while -1 works
        
        //4: enable callback
        CFRunLoopRef loop = CFRunLoopGetCurrent(); //get current thread loop
        CFRunLoopSourceRef src = CFSocketCreateRunLoopSource(kCFAllocatorDefault, _socket, 0);
        CFRunLoopAddSource(loop, src, kCFRunLoopDefaultMode);
        CFRelease(src);
        CFRunLoopRun();
        
        
        
        //3: handle here or in callback func
        if (result == kCFSocketSuccess) {
            NSLog(@"\r\n socket connect successfully");
            
            _isOnline = YES;
            
            //start new thread to read data from server
            [NSThread detachNewThreadSelector:@selector(read) toTarget:self withObject:nil];
            
            
        } else {
            NSLog(@"\r\n socket connect failed");
        }
        
        
        
        
    } else {
        NSLog(@"\r\n socket create failed");
    }
}


static void TCPServerConnectCallBack(CFSocketRef socket, CFSocketCallBackType type, CFDataRef address, const void *data, void *info) {
    //when select kCFSocketConnectCallBack, fail will return error pointer, others return NULL
    if (data != NULL) {
  
        
        NSLog(@"connect error");
        
        return;
    }
    
    //read data
    SocketClient *client = (__bridge SocketClient*) info;
    [client performSelectorInBackground:@selector(read) withObject:nil];
    
}


//recv()
- (void) read {
    char buf[2048];
    int hasRead;
    //NSAutoReleasePool is in run phase
    //@autoreleasepool is in build phase, more recommended
    @autoreleasepool {
        while ((hasRead = recv(CFSocketGetNative(_socket), buf, sizeof(buf), 0))) {
            NSLog(@"%d", hasRead);
            NSLog(@"data from server: %@", [[NSString alloc] initWithBytes:buf length:hasRead encoding:NSUTF8StringEncoding]);
        }
    }
    
}


//send()
- (void) send{
    if (_isOnline) {
        NSString *stringToSend = @"greeting from ios client";
        const char *data = [stringToSend UTF8String];
        send(CFSocketGetNative(_socket), data, strlen(data), 1);
    } else {
        NSLog(@"offline!");
    }
}



@end
