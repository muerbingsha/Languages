//
//  SocketServer.m
//  SRClient
//
//  Created by sj on 11/06/2018.
//  Copyright © 2018 Apple. All rights reserved.
//

#import "SocketServer.h"

@implementation SocketServer



-(void) create: (NSString *)ip :(int) port {
    _server = CFSocketCreate(kCFAllocatorDefault,
                             PF_INET,
                             SOCK_STREAM,
                             IPPROTO_TCP,
                             kCFSocketAcceptCallBack,
                             TCPServerAcceptCallBack,
                             nil);
    
    if (_server != nil) {
        NSLog(@"server create successfully \n");
        
        int opt = 1;
        setsockopt(CFSocketGetNative(_server), SOL_SOCKET, SO_REUSEADDR, (void *)&opt, sizeof(opt));
        
        
        struct sockaddr_in addr4;
        memset(&addr4, 0, sizeof(addr4));
        addr4.sin_addr.s_addr = inet_addr([ip UTF8String]);
        addr4.sin_port = htons(port);
        addr4.sin_family = AF_INET;
        addr4.sin_len = sizeof(addr4);
        
        //turn ipv4 to address
        CFDataRef address = CFDataCreate(kCFAllocatorDefault, (UInt8 *)&addr4, sizeof(addr4));
        CFSocketError result = CFSocketSetAddress(_server, address);
        if (result == kCFSocketSuccess) {
            NSLog(@"server set successfully \n");
            
            //loop listening client
            CFRunLoopRef current = CFRunLoopGetCurrent();
            CFRunLoopSourceRef src = CFSocketCreateRunLoopSource(kCFAllocatorDefault, _server, 0);
            CFRunLoopAddSource(current, src, kCFRunLoopDefaultMode);
            CFRelease(src);
            CFRunLoopRun();
            
            
        } else {
            NSLog(@"server set failed \n");
            
            if (_server) {
                CFRelease(_server);
            }
            _server = NULL;
            
            exit(0);
        }
        
    } else {
        NSLog(@"server create failed \n");
    }

}



void serverRead(CFReadStreamRef iStream, CFStreamEventType type, void *info) {
    UInt8 buff[2048];
    
    CFIndex hasRead = CFReadStreamRead(iStream, buff, 2048);
    
    if(hasRead > 0) {
        printf("接收到数据: %s\n", buff);
        
    }
    
}



void TCPServerAcceptCallBack(CFSocketRef socket, CFSocketCallBackType type, CFDataRef  address, const void *data, void *info ){
    
    if(type == kCFSocketAcceptCallBack){
        
        CFSocketNativeHandle nh = *(CFSocketNativeHandle*)data;
        uint8_t name[1024];
        socklen_t nameLen = sizeof(name);
        
        // 获取对方Socket信息，还有getsocketname()函数则用于获取本程序所在Socket信息
        if(getpeername(nh, (struct sockaddr *)name, &nameLen) != 0){
            
            NSLog(@"error");
            exit(1);
            
        }
        
        // 获取连接信息
        struct sockaddr_in * addr_in = (struct sockaddr_in*) name;
        
        NSLog(@"%s: %d 连接进来了", inet_ntoa(addr_in->sin_addr), addr_in->sin_port);
        
        CFReadStreamRef iStream;
        CFWriteStreamRef oStream;
        
        // 创建一组可读/写的CFStream
        
        CFStreamCreatePairWithSocket(kCFAllocatorDefault , nh, &iStream, &oStream);
        
        if(iStream && oStream){
            
            // 打开输入流和输入流
            
            CFReadStreamOpen(iStream);
            CFWriteStreamOpen(oStream);
            
            CFStreamClientContext streamContext = {0, NULL, NULL, NULL};
            
            if(!CFReadStreamSetClient(iStream,
                                      kCFStreamEventHasBytesAvailable,
                                      serverRead,
                                      &streamContext)) {
                
                exit(1);
                
            }
            
            CFReadStreamScheduleWithRunLoop(iStream, CFRunLoopGetCurrent(), kCFRunLoopCommonModes);
            
            const char* str = "您好,您收到Mac服务器的新年祝福!\n";
            
            // 向客户端输出数据
            
            CFWriteStreamWrite(oStream, (UInt8 *)str, strlen(str) + 1);
            
        }
        
    }
    
}


int main(int argc, char * argv[]) {
    SocketServer *server = [[SocketServer alloc]init];
    [server create:@"192.168.1.2" :9503];
}



@end
