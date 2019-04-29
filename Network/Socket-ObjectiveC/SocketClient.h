#import <Foundation/Foundation.h>
#import "sys/socket.h"
#import "netinet/in.h"
#import "arpa/inet.h"


@interface SocketClient : NSObject

@property CFSocketRef socket;
@property BOOL isOnline;

-(void) create;
-(void) send; 
-(void) read;
@end
