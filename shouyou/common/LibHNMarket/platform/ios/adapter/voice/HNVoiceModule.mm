//Copyright (c) 2012—2015 Beijing TianRuiDiAn Network Technology Co,Ltd. All rights reserved



#include "HNVoiceModule.h"
#import "HNMarket.h"
#import "json.h"
#import "oc-marco.h"

#define MODULE_NAME "hnvoice"

namespace HN
{
    
    create_impl(HNVoiceModule)
    
    HNVoiceModule::HNVoiceModule():Module(MODULE_NAME)
    {
		_callback = nullptr;
        registerAyncMethod("startRecord", HN_CALLFUNC_SELECTOR(HNVoiceModule::StartRecord));
        registerAyncMethod("stopRecord", HN_CALLFUNC_SELECTOR(HNVoiceModule::StopRecord));
        registerAyncMethod("playAudio", HN_CALLFUNC_SELECTOR(HNVoiceModule::PlayAudio));
        registerAyncMethod("cancelRecord", HN_CALLFUNC_SELECTOR(HNVoiceModule::CancelRecord));
    }

    HNVoiceModule::~HNVoiceModule()
    {
		_callback = nullptr;
        [_impl release];
        _impl = nil;
    }
    
    void HNVoiceModule::Start(UIViewController *viewController)
    {
        _impl = [[HNVoiceAdapter_IMPL alloc] initWithViewController:viewController Delegate:this];
    }
    
    std::string HNVoiceModule::CancelRecord(const std::string &args,CALLBACK_PRAGMA* callback)
    {
        [_impl cancelRecord];
        return "";
    }
    
    void HNVoiceModule::HandleStopRecord(const std::string &data)
    {
        Market::sharedMarket()->responseChannel(_callback, data);
    }
    
	void HNVoiceModule::HandlePlayFinish(const std::string& data)
    {
        if(data.compare("audio") == 0 && _callback != nullptr)
        {
            _callback->doCallSelector("finish");
        }
    }
	
    std::string HNVoiceModule::StartRecord(const std::string &args,CALLBACK_PRAGMA* callback)
    {
        [_impl startRecord];
        return "";
    }
    
    std::string HNVoiceModule::StopRecord(const std::string &args,CALLBACK_PRAGMA* callback)
    {
        NSString *audio  = [_impl stopRecord];
        
        
        return [audio UTF8String];
    }
    
    std::string HNVoiceModule::PlayAudio(const std::string &args,CALLBACK_PRAGMA* callback)
    {
		_callback = callback;
        NSString *audio = [NSString stringWithUTF8String:args.c_str()];
        [_impl playVoiceFilesWith:audio];
        return "";
    }
}