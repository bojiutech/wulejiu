//Copyright (c) 2012—2015 Beijing TianRuiDiAn Network Technology Co,Ltd. All rights reserved



#include "../HNVoiceDelegate.h"
#import "UIKit/UIKit.h"
#import "RecordTools.h"

@interface HNVoiceAdapter_IMPL : NSObject<UIActionSheetDelegate,UINavigationControllerDelegate,UIImagePickerControllerDelegate, RecorderDelegate>
{
    bool _supportPortrait;
}

- (void)setSupportPortrait:(bool)support;

-(id)initWithViewController:(UIViewController *)viewController Delegate:(HNVoiceDelegate *)delegate;

//开始录音
- (void)startRecord;

// 停止录音返回二进制字符串
- (NSString*)stopRecord;

//播放
- (void)playVoiceFilesWith:(NSString*)fileStr;

- (void)cancelRecord;

//播放结束
- (void)playFinish;

@end
