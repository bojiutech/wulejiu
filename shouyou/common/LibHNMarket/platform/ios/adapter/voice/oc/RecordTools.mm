//
//  RecordTools.m
//  VoiceRecord
//
//  Created by mac_111 on 16/2/17.
//  Copyright © 2016年 mac_111. All rights reserved.
//

#import "RecordTools.h"

#import "VoiceConverter.h"
#define DefaultSubPath @"Voice"
#define SampleRateKey 8000.0 //采样率
#define LinearPCMBitDepth 16 //采样位数 默认 16
#define NumberOfChannels 1  //通道的数目

@implementation RecordTools

+ (RecordTools *)shareRecorder
{
    
    static  RecordTools  *shareRecorderInstance = nil;
    
    static  dispatch_once_t   predicate;
    dispatch_once(&predicate, ^{
        
        shareRecorderInstance = [[self alloc]init];
        
    });
    
    return shareRecorderInstance;
}

- (BOOL)canRecord
{
    __block BOOL bCanRecord = YES;
    AVAudioSession *audioSession = [AVAudioSession sharedInstance];
    if ([audioSession respondsToSelector:@selector(requestRecordPermission:)]) {
        
        [audioSession performSelector:@selector(requestRecordPermission:) withObject:^(BOOL granted){
            if (granted) {
              bCanRecord =  YES;
                
            }else{
                
                bCanRecord =  NO;
                
            }
        }];
        
    }
    return bCanRecord;
    
}

- (void)starRecordwith:(UIView *)view
{
   
    self.filename = [self createFileName];
    NSString  *soundFilePath =[NSString stringWithFormat:@"%@/%@.wav",[self creatFilePath],self.filename];
    self.filePath = soundFilePath;
    self.backView = view;
    
    [self startRecordWithFilePath:soundFilePath];
    
    
}

- (void)startRecordWithFilePath:(NSString*)filePath
{
    
    AVAudioSession *session = [AVAudioSession sharedInstance];
    
    [session setCategory:AVAudioSessionCategoryPlayAndRecord error:nil];
    [session setActive:YES error:nil];
    
    NSDictionary *recordSetting = [NSDictionary dictionaryWithObjectsAndKeys:
                                   [NSNumber numberWithFloat: SampleRateKey],AVSampleRateKey, //采样率
                                   [NSNumber numberWithInt: kAudioFormatLinearPCM],AVFormatIDKey,
                                   [NSNumber numberWithInt:LinearPCMBitDepth],AVLinearPCMBitDepthKey,//采样位数 默认 16
                                   [NSNumber numberWithInt: NumberOfChannels], AVNumberOfChannelsKey,//通道的数目,
                                   nil];
    
    
    NSURL *url = [NSURL fileURLWithPath:filePath];
    self.filePath = filePath;
    NSError *error = nil;
    if (self.audioRecorder) {
        if (self.audioRecorder.isRecording) {
            [self.audioRecorder stop];
        }
        self.audioRecorder = nil;
    }
    
    
    AVAudioRecorder *tmpRecord = [[ AVAudioRecorder alloc] initWithURL:url settings:recordSetting error:&error];
    self.audioRecorder = tmpRecord;
    self.audioRecorder.meteringEnabled = YES;
    self.audioRecorder.delegate = self;
    if ([self.audioRecorder prepareToRecord] == YES){
        self.audioRecorder.meteringEnabled = YES;
        [self.audioRecorder record];
        
        [[UIApplication sharedApplication] setIdleTimerDisabled: YES];//保持屏幕长亮
        [[UIDevice currentDevice] setProximityMonitoringEnabled:NO]; //建议在播放之前设置yes，播放结束设置NO，这个功能是开启红外感应
       
    }else {
        int errorCode = CFSwapInt32HostToBig ([error code]);
        NSLog(@"Error: %@ [%4.4s])" , [error localizedDescription], (char*)&errorCode);
    }

}

- (void)creatVoiceAnimation
{
    [self creatVoiceVolImages];
    [self addPrompthud];
    self.recorTimer = [NSTimer scheduledTimerWithTimeInterval:1/2 target:self selector:@selector(monitorVolumn:) userInfo:nil repeats:YES];
}




-(void)monitorVolumn:(NSTimer *)timer{
    float var = [self.audioRecorder peakPowerForChannel:0];
    NSLog(@"var---------   %f",var);
    
    [self changVoiceImage:var];
    [self.audioRecorder updateMeters];
}

//生成录音时的音量大小图片
-(void)creatVoiceVolImages{
    
    if (self.voiceVols == nil) {
        NSMutableArray *images = [NSMutableArray arrayWithCapacity:7];
        [images addObject:[UIImage imageNamed:@"microphone-"]];
        for (int i=1; i<7; i++) {
            NSString *imageName = [NSString stringWithFormat:@"vol-%d",i];
            [images addObject:[UIImage imageNamed:imageName]];
        }
        self.voiceVols = [NSArray arrayWithArray:images];
    }
}

//根据音量更换音亮大小图片
-(void)changVoiceImage:(float)var{
    NSInteger count    = var / -5;
    if (count == self.voiceImageCount) {
        return;
    }
    if (count > 6) {
        self.hud.customView = [[UIImageView alloc] initWithImage:self.voiceVols.firstObject];
        return;
    }
    NSInteger calCount = count>self.voiceImageCount ? count - self.voiceImageCount : self.voiceImageCount - count;
    
    if (self.voiceImageChangTimer) {
        [self.voiceImageChangTimer invalidate];
        self.voiceImageChangTimer = nil;
    }
    self.voiceImageChangTimer = [NSTimer scheduledTimerWithTimeInterval:(1/4)/calCount target:self selector:@selector(changVoiceImageWithTimer:) userInfo:[NSNumber numberWithInteger:count] repeats:YES];
}

//切换音量大小图片
-(void)changVoiceImageWithTimer:(NSTimer *)timer{
    NSInteger count = ((NSNumber *)timer.userInfo).integerValue;
    if (self.voiceImageCount > count) {
        self.voiceImageCount--;
    }else{
        self.voiceImageCount++;
    }
    self.hud.customView = [[UIImageView alloc] initWithImage:self.voiceVols[6 - self.voiceImageCount]];
    if (count == self.voiceImageCount) {
        [timer invalidate];
    }
}
-(void)addPrompthud{
//    [self deleteHud];
    self.hud = [[MBProgressHUD alloc] initWithView:self.backView];
    self.hud.customView = [[UIImageView alloc] initWithImage:self.voiceVols.firstObject];
    self.hud.mode = MBProgressHUDModeCustomView;
    self.hud.labelText = @"手指上滑，取消发送";
    [self.backView addSubview:self.hud];
    [self.hud show:YES];
    
//   self.addUpdateRecordHud = [NSTimer scheduledTimerWithTimeInterval:50 target:self selector:@selector(addUpdateRecordHud:) userInfo:nil repeats:NO];
}



-  (void)audioRecorderDidFinishRecording:(AVAudioRecorder *)recorder successfully:(BOOL)flag
{
    
    
}


- (NSString *)stopRecord
{

    
    if (self.audioRecorder) {
        [self.audioRecorder stop];
        AVAudioSession *session = [AVAudioSession sharedInstance];
        [session setActive:NO error:nil];
        [session setCategory:AVAudioSessionCategoryAmbient error:nil];
        
    }
    NSString *fileName = [NSString stringWithFormat:@"%@.amr", [self  createFileName]];
    NSString *fullPath = [NSString stringWithFormat:@"%@/%@",[self creatFilePath],fileName];
    //        self.amrUrl = [NSURL URLWithString:self.filePath];
    [VoiceConverter wavToAmr:self.filePath amrSavePath:fullPath];
    
     BOOL blHave=[[NSFileManager defaultManager] fileExistsAtPath:self.filePath];
    if (blHave) {
        BOOL blDele= [[NSFileManager defaultManager] removeItemAtPath:self.filePath error:nil];
    
        if (blDele) {
            NSLog(@"删除成功");
            
        }else
        {
            NSLog(@"删除失败");
        }
    }
    
    NSData *recordData =[NSData dataWithContentsOfFile:fullPath];
    NSString *recordStr =[NSString stringWithFormat:@"%@",[recordData base64EncodedStringWithOptions:0]];
    
    [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayAndRecord error:nil];
    
    return recordStr;


}

- (void)removeVoiceAnimation
{
    if (self.recorTimer) {
        [self.recorTimer invalidate];
        self.recorTimer = nil;
    }
    
    if(self.voiceImageChangTimer){
        [self.voiceImageChangTimer invalidate];
        self.voiceImageChangTimer = nil;
        
    }
    
    [self.hud removeFromSuperview];

    
}





// 创建录音文件名字
- (NSString*) createFileName
{
    NSDate *date_ = [NSDate date];
    NSDateFormatter *dateformater = [[NSDateFormatter alloc] init];
    [dateformater setDateFormat:@"yyyy-MM-dd HH-mm-ss"];
    NSString *timeFileName = [dateformater stringFromDate:date_];
    return timeFileName;
}

// 创建存储路径
- (NSString*)creatFilePath
{
    NSFileManager *fileManager = [[NSFileManager alloc] init];
    NSString *pathDocuments = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    NSString *createPath = [NSString stringWithFormat:@"%@/%@", pathDocuments,DefaultSubPath];
    
    if (![[NSFileManager defaultManager] fileExistsAtPath:createPath]) {
        [fileManager createDirectoryAtPath:createPath withIntermediateDirectories:YES attributes:nil error:nil];
    } else {
    }
    
    NSLog(@"%@",createPath);
    return createPath;
}
- (void)playVoiceFilesWith:(NSString*)fileStr
{

    if (self.audioPlayer) {
        [self.audioPlayer stop];
        self.audioPlayer = nil;
        
        
    }
    NSString *fileName2 = [NSString stringWithFormat:@"%@.amr",[self createFileName]];
    NSString *fullPath2 = [NSString stringWithFormat:@"%@/%@",[self creatFilePath],fileName2];
    NSError *error = nil;
    [[[NSData alloc] initWithBase64EncodedString:fileStr options:NSDataBase64DecodingIgnoreUnknownCharacters] writeToFile:fullPath2 atomically:YES];
    if (error) {
        //        NSLog(@"错误：error:%@", error);

    }
    NSString *fileName = [NSString stringWithFormat:@"%@.wav",[self createFileName]];
    NSString *fullPath = [NSString stringWithFormat:@"%@/%@",[self creatFilePath],fileName];
   
    [VoiceConverter amrToWav:fullPath2 wavSavePath:fullPath];
    
    BOOL blHave=[[NSFileManager defaultManager] fileExistsAtPath:fullPath2];
    if (blHave) {
        BOOL blDele= [[NSFileManager defaultManager] removeItemAtPath:fullPath2 error:nil];
        if (blDele) {
            NSLog(@"删除成功");
            
        }else
        {
            NSLog(@"删除文件时出现问题:%@",[error localizedDescription]);
            NSLog(@"删除失败");
            
            
        }
    }
    
    NSData *recordData =[NSData dataWithContentsOfFile:fullPath];
    AVAudioSession *audioSession  = [AVAudioSession sharedInstance];
    
    [audioSession setCategory:AVAudioSessionCategoryPlayback
                        error:nil];
    [audioSession setActive:YES error:nil];
    
    self.audioPlayer = [[AVAudioPlayer alloc] initWithData:recordData error:&error];
    [self.audioPlayer updateMeters];
    if (error) {
        NSLog(@"音乐播放错误：%@",error);
        [[UIDevice currentDevice] setProximityMonitoringEnabled:NO];
        return;
    }
    [self.audioPlayer prepareToPlay];
    self.audioPlayer.volume = 8;
    [self.audioPlayer setDelegate:self];
    [self.audioPlayer play];

    
}

- (void)cancelRecord
{
    
    if (self.voiceImageChangTimer) {
        
       [self.voiceImageChangTimer setFireDate:[NSDate distantFuture]];
//        [self.voiceImageChangTimer invalidate];
//         self.voiceImageChangTimer = nil;
    }
    
    if (self.recorTimer) {
        [self.recorTimer setFireDate:[NSDate distantFuture]];
//        [self.recorTimer invalidate];
//        self.recorTimer = nil;
        
    }
    self.hud.customView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"cancel"]];
    self.hud.labelText  = @"手指松开，取消录音";
    self.hud.labelColor = [UIColor redColor];
    
    [self.audioRecorder stop];
}

- (void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player successfully:(BOOL)flag
{
    if (self.delegate &&[self.delegate respondsToSelector:@selector(playFinish)]) {
        [self.delegate playFinish];
    }
    
    NSLog(@"播放完毕");
	
	if(self.delegate != nullptr){
        [self.delegate playFinish ];
    }
}


- (void)dealloc
{
    self.audioRecorder = nil;
	[super dealloc];
    
    
}


@end
