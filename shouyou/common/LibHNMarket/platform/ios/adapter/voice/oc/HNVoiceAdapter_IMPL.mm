//Copyright (c) 2012—2015 Beijing TianRuiDiAn Network Technology Co,Ltd. All rights reserved



#import "HNVoiceAdapter_IMPL.h"
#import <MobileCoreServices/MobileCoreServices.h>

@interface HNVoiceAdapter_IMPL()
{
    HNVoiceDelegate *_delegate;
    UIViewController *_viewController;
    UIImagePickerController *_albumPicker;
    UIImagePickerController *_cameraPicker;
    int _cropX;
    int _cropY;
    
}
@end

@implementation HNVoiceAdapter_IMPL

- (void)dealloc
{
    [super dealloc];
    [_albumPicker release];
    [_cameraPicker release];
    _albumPicker = nil;
    _cameraPicker = nil;
}

//- (AppController *)getAppController {
//    AppController *controller = [[UIApplication sharedApplication] delegate];
//    return controller;
//}

- (id)getAppController {
    id controller = [[UIApplication sharedApplication] delegate];
    return controller;
}

-(id)initWithViewController:(UIViewController *)viewController Delegate:(HNVoiceDelegate *)delegate
{
    if (self = [super init]) {
        _delegate = delegate;
        _viewController = viewController;
    }
    return self;
}

- (void)startRecord
{
    //AudioServicesPlaySystemSound (kSystemSoundID_Vibrate); //震动一下
    
    [[RecordTools shareRecorder]starRecordwith:_viewController.view];
}

- (NSString*)stopRecord
{
    //AudioServicesPlaySystemSound (kSystemSoundID_Vibrate); //震动一下
    NSString *audio = [[RecordTools shareRecorder] stopRecord];

    return audio;
}

- (void)cancelRecord
{
    [[RecordTools shareRecorder] cancelRecord];
}

- (void)playVoiceFilesWith:(NSString*)fileStr
{
	[[RecordTools shareRecorder] setDelegate:self];
    [[RecordTools shareRecorder] playVoiceFilesWith:fileStr];
}

- (void)playFinish{
    if(_delegate != nullptr){
        _delegate->HandlePlayFinish("audio");
    }
}

- (void)actionSheet:(UIActionSheet *)actionSheet didDismissWithButtonIndex:(NSInteger)buttonIndex
{
    NSNumber *value = [NSNumber numberWithInt:UIInterfaceOrientationPortrait];
    [[UIDevice currentDevice] setValue:value forKey:@"orientation"];

    switch (buttonIndex)
    {
        case 0:
            //拍照
            [[self getAppController] setSupportPortrait:true];
            [self getImageFromCamera];
            break;
        case 1:
        {
            [[self getAppController] setSupportPortrait:true];
            [self getPhotoFromAlbum];
            break;
        }
        case 2:
            //取消
            //_delegate->HandleGet("");
            break;
    }
}

- (void)getPhotoFromAlbum
{
    _albumPicker = [[UIImagePickerController alloc] init];
    [_albumPicker setDelegate:self];
    _albumPicker.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
    [_albumPicker setMediaTypes:@[(NSString *)kUTTypeImage]];
    _albumPicker.allowsEditing = YES;
    [_viewController presentViewController:_albumPicker animated:YES completion:nil];
}

- (void)getImageFromCamera
{
    _cameraPicker = [[UIImagePickerController alloc] init];
    _cameraPicker.delegate = self;
    _cameraPicker.sourceType = UIImagePickerControllerSourceTypeCamera;
    [_cameraPicker setMediaTypes:@[(NSString *)kUTTypeImage]];
    _cameraPicker.allowsEditing = YES;
    [_viewController presentViewController:_cameraPicker animated:YES completion:nil];
}

- (void) imageWasSavedSuccessfully:(UIImage *)paramImage didFinishSavingWithError:(NSError *)paramError contextInfo:(void *)paramContextInfo
{
    if (paramError == nil)
    {
        //照片保存成功
    }
    else
    {
        //照片保存失败
    }
}

- (void) imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    [[self getAppController] setSupportPortrait:false];
    UIImage *image = nil;
    if ([picker allowsEditing]) image = [info objectForKey:UIImagePickerControllerEditedImage];
    else image = [info objectForKey:UIImagePickerControllerOriginalImage];
    image = [self changeImageSize:image Size:CGSizeMake(_cropX, _cropY)];
    NSData* data = UIImageJPEGRepresentation(image, 0.5);
    NSString *imagestr = [data base64Encoding];
    std::string stdstr = imagestr.UTF8String;
    //_delegate->HandleGetPhoto(stdstr);
    if (picker.sourceType == UIImagePickerControllerSourceTypeCamera)
    {
        // 保存图片到相册中
        SEL selectorToCall = @selector(imageWasSavedSuccessfully:didFinishSavingWithError:contextInfo:);
        UIImageWriteToSavedPhotosAlbum(image, self,selectorToCall, NULL);
        [_cameraPicker dismissViewControllerAnimated:YES completion:nil];
        [_cameraPicker release];
        _cameraPicker = nil;
    }
    else
    {
        [_albumPicker dismissViewControllerAnimated:YES completion:nil];
        [_albumPicker release];
        _albumPicker = nil;
    }
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker
{
    [[self getAppController] setSupportPortrait:false];
    if (picker.sourceType == UIImagePickerControllerSourceTypeCamera)
    {
        [_cameraPicker dismissViewControllerAnimated:YES completion:nil];
        [_cameraPicker release];
        _cameraPicker = nil;
    }
    else
    {
        [_albumPicker dismissViewControllerAnimated:YES completion:nil];
        [_albumPicker release];
        _albumPicker = nil;
    }
    
    //_delegate->HandleGetPhoto("");
}

- (UIImage*)changeImageSize:(UIImage*)image Size:(CGSize)newSize
{
    // Create a graphics image context
    UIGraphicsBeginImageContext(newSize);
    // Tell the old image to draw in this new context, with the desired
    // new size
    [image drawInRect:CGRectMake(0,0,newSize.width,newSize.height)];
    // Get the new image from the context
    UIImage* newImage = UIGraphicsGetImageFromCurrentImageContext();
    // End the context
    UIGraphicsEndImageContext();
    // Return the new image.
    return newImage;
}
@end
