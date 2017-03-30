//Copyright (c) 2012—2015 Beijing TianRuiDiAn Network Technology Co,Ltd. All rights reserved

#ifndef __HNVoiceModule__
#define __HNVoiceModule__

#include "HNModule.h"
#import "oc/HNVoiceAdapter_IMPL.h"
#import <UIKit/UIKit.h>

namespace HN
{
    class HNVoiceModule:public Module,public HNVoiceDelegate
    {
        create_declare(HNVoiceModule)
        
    public:
        ~HNVoiceModule();
        
        void Start(UIViewController *viewController);
        
    private:
        HNVoiceModule();
        
        std::string StartRecord(const std::string &args,CALLBACK_PRAGMA* callback);
        
        std::string StopRecord(const std::string &args,CALLBACK_PRAGMA* callback);
        
        std::string CancelRecord(const std::string &args,CALLBACK_PRAGMA* callback);
        
        std::string PlayAudio(const std::string &args,CALLBACK_PRAGMA* callback);
        
        virtual void HandleStopRecord(const std::string& data) override;
		
		// 声音播放结束
        virtual void HandlePlayFinish(const std::string& data);
        
    private:
        HNVoiceAdapter_IMPL *_impl;
        
        CALLBACK_PRAGMA* _callback;
    };
}

#endif //__HNVoiceModule__
