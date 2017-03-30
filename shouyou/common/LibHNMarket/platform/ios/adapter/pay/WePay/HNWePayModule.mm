//Copyright (c) 2012—2015 Beijing TianRuiDiAn Network Technology Co,Ltd. All rights reserved

#include "HNWePayModule.h"
#include <string>
#import "../../../HNMarket.h"
#import "json.h"
#import "oc-marco.h"
#define MODULE_NAME "wepay"

//////////////////////////////////////////////////
namespace HN
{
    create_impl(WePayModule)
    
    WePayModule::WePayModule():Module(MODULE_NAME)
    {
        registerAyncMethod("pay", HN_CALLFUNC_SELECTOR(WePayModule::Pay));
    }
    
    WePayModule::~WePayModule()
    {
        [_impl release];
        _impl = nil;
    }
    
    void WePayModule::Start(const std::string& appID, const std::string& mchID,const std::string& spKey)
    {
        _impl = [[HNWePay_IMPL sharedManager] initWithAppID:stringToNSString(appID)
                                              mchID:stringToNSString(mchID)
                                              spKey:stringToNSString(spKey)
                                              Delegate:this];
    }
    
    bool WePayModule::HandleURL(NSURL *url)
    {
        return true;
    }
    
    std::string WePayModule::Pay(const std::string &args, CALLBACK_PRAGMA *callback)
    {
        Json::Value JsonValue;
        Json::Reader JsonReader;
        if (JsonReader.parse(args, JsonValue))
        {
            _callback = *callback;
            std::string orderID = JsonValue["orderID"].asString();
            double price = JsonValue["price"].asDouble();
            NSString *priceStr = [NSString stringWithFormat:@"%f", price];
            NSString *description = [NSString stringWithFormat:@"%d金币",JsonValue["number"].asUInt()];
            [_impl pay:stringToNSString(orderID) Price:priceStr Description:description];
        }
        
        return "";
    }
    
#pragma delegate
    
    void WePayModule::HandlePayResult(bool bSuccess,int platform)
    {
        NSString *result = [NSString stringWithFormat:@"{\"status\":%d,\"platform\":%d}",bSuccess,platform];
        Market::sharedMarket()->responseChannel(&_callback, result.UTF8String);
    }
}
