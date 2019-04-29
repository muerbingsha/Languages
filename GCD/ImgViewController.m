//
// 功能：从网络加载3张图片，当加载完第一张后在加载第二张，然后再加载第三张
// 知识点：GCD信号量
// 划重点：信号量控制下载图片的线程数
// 改进处：并不一定是最顶上的view开始加载。
// Author: SharkDeng
// Github: muerbignsha
// Reference: https://blog.csdn.net/chenyufeng1991/article/details/49356389

#import "ImgViewController.h"

@interface ImgViewController ()

@end

@implementation ImgViewController


- (void)viewDidLoad {
    [super viewDidLoad];
    
    
    [self createImg];
    [self downloadImg];


}

- (void)createImg {
    for (int i=0; i<3; i++){
        imgView[i] = [[UIImageView alloc]initWithFrame:CGRectMake(0, 250 * i, 200, 200)];
        imgView[i].backgroundColor = UIColor.redColor;
        imgView[i].alpha = 0.0;
        [self.view addSubview:imgView[i]];
    }
}

- (void) downloadImg {
    NSString *url0 = @"http://pic17.nipic.com/20111026/8662498_125925242183_2.jpg";
    NSString *url1 = @"http://b.hiphotos.baidu.com/zhidao/wh%3D450%2C600/sign=53da5874352ac65c67506e77cec29e27/9f2f070828381f30807909bda9014c086e06f046.jpg";
    NSString *url2 = @"http://cimg.163.com/sport/0412/23/wu2305.jpg";
    
    dispatch_semaphore_t s = dispatch_semaphore_create(1);
    dispatch_queue_t bgQueue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    
    
    dispatch_async(bgQueue, ^{
        NSLog(@"%d", NSThread.currentThread);
        
        dispatch_semaphore_wait(s, DISPATCH_TIME_FOREVER);
        UIImage *img = [self getImg:url0];
        
        //住线程更新ui
        dispatch_async(dispatch_get_main_queue(), ^{
            [UIView animateWithDuration:2.0 animations:^{
                [self->imgView[0] setImage:img];
                self->imgView[0].alpha = 1.0;
            } completion:^(BOOL finished) {
                dispatch_semaphore_signal(s);
            }];
        });
        
    });
    
    dispatch_async(bgQueue, ^{
        NSLog(@"%d", NSThread.currentThread);
        
        dispatch_semaphore_wait(s, DISPATCH_TIME_FOREVER);
        UIImage *img = [self getImg:url1];
        
        dispatch_async(dispatch_get_main_queue(), ^{
            [UIView animateWithDuration:2.0 animations:^{
                [self->imgView[1] setImage:img];
                self->imgView[1].alpha = 1.0;
            } completion:^(BOOL finished) {
                dispatch_semaphore_signal(s);
            }];
        });
        
        
    });
    
    dispatch_async(bgQueue, ^{
        NSLog(@"%d", NSThread.currentThread);
        
        dispatch_semaphore_wait(s, DISPATCH_TIME_FOREVER);
        UIImage *img = [self getImg:url2];
        
        dispatch_async(dispatch_get_main_queue(), ^{
            [UIView animateWithDuration:2.0 animations:^{
                [self->imgView[2] setImage:img];
                self->imgView[2].alpha = 2.0;
            } completion:^(BOOL finished) {
                dispatch_semaphore_signal(s);
            }];
        });
    
    });
    
}

- (UIImage *)getImg: (NSString *)imgUrl {
    NSURL *url = [NSURL URLWithString:imgUrl];
    NSData *data = [NSData dataWithContentsOfURL:url];
    UIImage *img = [[UIImage alloc]initWithData:data];
    return img;
}
@end
