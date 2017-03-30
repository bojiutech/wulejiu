//
//  RecordTools.h
//  VoiceRecord
//
//  Created by mac_111 on 16/2/17.
//  Copyright © 2016年 mac_111. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <AudioToolbox/AudioToolbox.h>
#import <UIKit/UIKit.h>
#import "MBProgressHUD/MBProgressHUD.h"
@protocol RecorderDelegate <NSObject>

//播放结束
- (void)playFinish;

//录音结束
- (void)recordFinish;




@end

@interface RecordTools : NSObject<AVAudioRecorderDelegate,AVAudioPlayerDelegate>
@property(strong, nonatomic) AVAudioRecorder *audioRecorder;
@property(strong, nonatomic) NSString *filename,*filePath;
@property (nonatomic, strong) AVAudioPlayer *audioPlayer;
@property (nonatomic,strong)  NSTimer *recorTimer;//录音音量提示timer
@property (nonatomic, strong) NSTimer *voiceImageChangTimer;//录音切换图片的timer
@property (nonatomic,assign)id<RecorderDelegate>delegate;
@property (nonatomic,strong)NSArray    *voiceVols;
@property (nonatomic, strong) MBProgressHUD *hud;//录音超时提示
@property (nonatomic, assign) NSInteger voiceImageCount;//录音时的音量提示照片是第几张
@property (nonatomic,strong)UIView    *backView;
@property (nonatomic, strong) NSTimer *addUpdateRecordHud;
+ (RecordTools *)shareRecorder;

//开始录音
- (void)starRecordwith:(UIView *)view;

// 停止录音返回二进制字符串
- (NSString*) stopRecord;



//- (void)playVoiceFiles;


//播放
- (void)playVoiceFilesWith:(NSString*)fileStr;


- (void)cancelRecord;



-(void)creatVoiceVolImages;
/**
 * 是否可以录音
 **/
- (BOOL)canRecord;

//音量大小UI动画
- (void)creatVoiceAnimation;
//移除动画
- (void)removeVoiceAnimation;
@end
