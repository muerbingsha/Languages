//MARK: CFNetwork

-(void) request {
    CFStringRef s = CFSTR("http://www.jobyme88.com/wp-content/uploads/2017/07/1-ps-1.jpg");
    CFURLRef url = CFURLCreateWithString(kCFAllocatorDefault, s, NULL);
    
    CFHTTPMessageRef request = CFHTTPMessageCreateRequest(kCFAllocatorDefault,
                                                           CFSTR("get"),
                                                           url,
                                                           kCFHTTPVersion1_1);//http version:
    //1.0 Connection: closed
    //1.1 Connection: keep-alive
    
    CFReadStreamRef readStream = CFReadStreamCreateForHTTPRequest(kCFAllocatorDefault, request);

    //set delegate
    CFStreamClientContext ctx = {0, (__bridge void*)(self), NULL, NULL, NULL};
    
    CFOptionFlags event = kCFStreamEventHasBytesAvailable | kCFStreamEventEndEncountered;

    CFReadStreamSetClient(readStream, event, loadImageData, &ctx);
    
    //将流加入到runloop中
    CFReadStreamScheduleWithRunLoop(readStream, CFRunLoopGetCurrent(), kCFRunLoopCommonModes);
    
    //打开流
    CFReadStreamOpen(readStream);


}


// -(void) is not supported
void loadImageData (CFReadStreamRef stream, CFStreamEventType type, void * clientCallBackInfo) {
    
    ViewController *tempVC = (__bridge ViewController*)clientCallBackInfo;

    //has data
    if (type == kCFStreamEventHasBytesAvailable) {
        UInt8 buf [255];
        int length = CFReadStreamRead(stream, buf, 255);
        
        if (! tempVC.imageData) {
            tempVC.imageData = [NSMutableData data];
        }
        [tempVC.imageData appendBytes:buf length: length];
        
        
        NSString *info = [[NSString alloc]initWithData:tempVC.imageData encoding:NSUTF8StringEncoding];
        NSLog(@"%@", info);
        //we get 405 not allowed error form nginx
        //reason: we visit static resource(a image) by post method, which is not allowed by nginx
        //solution: use "get" will be fine or modify nginx server configuration
        
        
        //question: how to see this?
        CFStreamStatus status = CFReadStreamGetStatus(stream);
        CFStreamError err = CFReadStreamGetError(stream);
    
    }
    
    //data is over
    if (type == kCFStreamEventEndEncountered){
        [tempVC turnDataToImage];
        
        CFReadStreamClose(stream);
        CFReadStreamUnscheduleFromRunLoop(stream, CFRunLoopGetCurrent(), kCFRunLoopCommonModes);
    }
}

- (void)turnDataToImage {
    UIImageView *imageView = [[UIImageView alloc] initWithFrame:CGRectMake(0, 100, 320, 200)];
    UIImage *image = [UIImage imageWithData: _imageData];
    
    imageView.image = image;
    imageView.backgroundColor = UIColor.redColor;
    
    [self.view addSubview:imageView];
}
 

 

//CFSteamError

//CFStreamErrorDomain

//CFStreamStatus

//CFStreamEventType

//CFStreamClientContext

//CFReadStreamRef

//CFWriteStreamRef
