//Copyright (c) 2012—2015 Beijing TianRuiDiAn Network Technology Co,Ltd. All rights reserved



#include "HNLocationModule.h"
#import "HNMarket.h"
#import "json.h"
#import "oc-marco.h"

#define MODULE_NAME "hnLocation"

namespace HN
{
    
    create_impl(HNLocationModule)
    
    HNLocationModule::HNLocationModule():Module(MODULE_NAME)
    {
        registerAyncMethod("getLocation", HN_CALLFUNC_SELECTOR(HNLocationModule::GetLocation));
    }

    HNLocationModule::~HNLocationModule()
    {
        [_impl release];
        _impl = nil;
    }
    
    void HNLocationModule::Start()
    {
        _impl = [[HNLocationAdapter_IMPL alloc] init];
    }
    
    std::string HNLocationModule::GetLocation(const std::string &args,CALLBACK_PRAGMA* callback)
    {
        
        _callback = *callback;
        
        [_impl locationAddress : callback];
        return "";
    }
}