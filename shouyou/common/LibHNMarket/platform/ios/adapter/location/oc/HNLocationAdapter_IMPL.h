//Copyright (c) 2012—2015 Beijing TianRuiDiAn Network Technology Co,Ltd. All rights reserved

#include "HNModule.h"
#import <UIKit/UIKit.h>

@interface HNLocationAdapter_IMPL : NSObject
{
    CALLBACK_PRAGMA _callback;
}

- (id)init;

- (void) locationAddress : (CALLBACK_PRAGMA*) callback;
@end