//Copyright (c) 2012—2015 Beijing TianRuiDiAn Network Technology Co,Ltd. All rights reserved

#ifndef __HNLocationModule__
#define __HNLocationModule__

#include "HNModule.h"
#import "oc/HNLocationAdapter_IMPL.h"


namespace HN
{
    class HNLocationModule:public Module
    {
        create_declare(HNLocationModule)
        
    public:
        HNLocationModule();
        
        void Start();
        
    private:
        ~HNLocationModule();
        
        std::string GetLocation(const std::string &args,CALLBACK_PRAGMA* callback);
        
    private:
        HNLocationAdapter_IMPL *_impl;
        CALLBACK_PRAGMA _callback;
    };
}

#endif //__HNLocationModule__
