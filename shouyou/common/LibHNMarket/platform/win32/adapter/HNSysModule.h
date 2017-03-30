﻿#ifndef __HNSYSMODULE_H__
#define __HNSYSMODULE_H__

#include "../../../HNModule.h"
#include "../../../HNPayCallBack.h"

namespace HN
{
    class SysModule : public Module
    {
		create_declare(SysModule)

    private:
        SysModule();
        
    public:
        ~SysModule();

    private:
        std::string getBuildVersion(const std::string& args);
        std::string getVersion(const std::string& args);
        std::string getOSVersion(const std::string& args);
        std::string getDevice(const std::string& args);
        std::string getIMEI(const std::string& args);
        std::string getISP(const std::string& args);
		std::string GetSerialNumber(const std::string& args);
		std::string installApp(const std::string& args);
		std::string IsAppInstalled(const std::string& args);
		
		// 获取本机ip地址
		std::string getNetIp(const std::string& args);
    };
}

#endif	//__HNSYSMODULE_H__