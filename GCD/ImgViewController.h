//
// 功能：从网络加载3张图片，当加载完第一张后在加载第二张，然后再加载第三张
// 知识点：GCD信号量
// 划重点：信号量控制下载图片的线程数
// 改进处：并不一定是最顶上的view开始加载。
// Author: SharkDeng
// Github: muerbignsha
// Reference: https://blog.csdn.net/chenyufeng1991/article/details/49356389

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface ImgViewController : UIViewController {
    UIImageView *imgView[3];
}


@end

NS_ASSUME_NONNULL_END
