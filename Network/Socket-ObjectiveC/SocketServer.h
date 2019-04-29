#import <Foundation/Foundation.h>
#import <sys/socket.h>
#import <arpa/inet.h>

@interface SocketServer : NSObject

@property CFSocketRef server;

-(void) create :(NSString *)ip :(int) port;

@end
