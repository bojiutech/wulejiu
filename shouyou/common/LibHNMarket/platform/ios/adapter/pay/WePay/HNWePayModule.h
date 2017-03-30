#ifndef __HNWePayModule__
#define __HNWePayModule__

#import <Foundation/Foundation.h>
#import "SDKExport/WXApi.h"
#import "HNWePay_IMPL.h"

#include "../../../../../HNModule.h"

namespace HN
{
    class WePayModule:public Module ,public HNPayDelegate
    {
        create_declare(WePayModule)
        
    public:
        ~WePayModule();
        
        void Start(const std::string& appID, const std::string& mchID,const std::string& spKey);
        
        bool HandleURL(NSURL *url);
        
        void HandlePayResult(bool bSuccess,int platform) override;
        
    private:
        WePayModule();
        
        std::string Pay(const std::string &args,CALLBACK_PRAGMA* callback);
        
    private:
        HNWePay_IMPL* _impl;
        CALLBACK_PRAGMA _callback;
    };
}

#endif //__HNAliPayModule__
