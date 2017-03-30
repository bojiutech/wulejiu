#import "UIImagePickerController+LandScapeImagePicker.h"


@implementation UIImagePickerController (LandScapeImagePicker)

- (BOOL)shouldAutorotate
{
    
    return NO;
    
}

- (UIInterfaceOrientationMask)supportedInterfaceOrientations
{
    return UIInterfaceOrientationMaskPortrait;
    
}



- (UIInterfaceOrientation)preferredInterfaceOrientationForPresentation
{
    return  UIInterfaceOrientationPortrait;
    
}

@end




