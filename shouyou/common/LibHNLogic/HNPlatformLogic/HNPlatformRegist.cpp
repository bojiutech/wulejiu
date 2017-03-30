#include "HNPlatformRegist.h"
#include "HNMarketExport.h"

namespace HN
{
	/*
	bool HNPlatformRegist::requestRegist(const std::string &name, const std::string pwd, bool fastRegist)
	{
	if(!fastRegist)
	{
	if(name.empty() || pwd.empty())
	{
	_callback->onPlatformRegistCallback(false, fastRegist, GBKToUtf8("名称或密码为空"), name, pwd, 0);
	return false;
	}
	}

	_fastRegist = fastRegist;
	_name       = name;
	_pwd        = pwd;
	platformRegist();
	return true;
	}
	*/
	
	bool HNPlatformRegist::requestRegist(BYTE RegistType /*= 0*/, const std::string &name /*= ""*/, const std::string pwd /*= ""*/, const std::string& phoneNum /*= ""*/, const std::string& nickName /*= ""*/, const std::string& uionID /*= ""*/, const std::string& headUrl /*= ""*/, bool bBoy /*= true*/)
	{
		if (RegistType == 1)
		{
			if (name.empty() || pwd.empty())
			{
				_callback->onPlatformRegistCallback(false, RegistType, GBKToUtf8("名称或密码为空"), name, pwd, 0);
				return false;
			}
		}

		_registType = RegistType;
		_name = name;
		_pwd = pwd;
		_phone = phoneNum;
		_nickName = nickName;
		_uionID = uionID;
		_bBoy = bBoy;
		_headUrl = headUrl;
		platformRegist();
		return true;
	}
	
	void HNPlatformRegist::I_P_M_Connect(bool result)
	{
		if(!result)
		{
			_callback->onPlatformRegistCallback(false, _fastRegist, GBKToUtf8("平台网络连接失败"), _name, _pwd, 0);
			return;
		}
		platformRegist();
	}
	
	void HNPlatformRegist::I_P_M_Regist(MSG_GP_S_Register* registerStruct, UINT ErrorCode)
	{	
		_name = std::string(registerStruct->szName);
		_pwd = std::string(registerStruct->szPswd);

		switch (ErrorCode)
		{
		case eFAILE:
			_callback->onPlatformRegistCallback(false, _fastRegist, GBKToUtf8("注册失败"), _name, _pwd, registerStruct->LogonTimes);
			break;
		case eSUCCESS:
			_callback->onPlatformRegistCallback(true, _fastRegist, GBKToUtf8("注册成功"), _name, _pwd, registerStruct->LogonTimes);
			break;
		case eEXIST:
			_callback->onPlatformRegistCallback(false, _fastRegist, GBKToUtf8("用户名已存在"), _name, _pwd, registerStruct->LogonTimes);
			break;
		case eSENSITIVE:
			_callback->onPlatformRegistCallback(false, _fastRegist, GBKToUtf8("包含敏感词汇"), _name, _pwd, registerStruct->LogonTimes);
			break;
		case eNUMLIMIT:
			_callback->onPlatformRegistCallback(false, _fastRegist, GBKToUtf8("超出注册限制"), _name, _pwd, registerStruct->LogonTimes);
			break;
		case eAGENTERR:
			_callback->onPlatformRegistCallback(false, _fastRegist, GBKToUtf8("代理信息错误"), _name, _pwd, registerStruct->LogonTimes);
			break;
		case eTUIGUANGERR:
			_callback->onPlatformRegistCallback(false, _fastRegist, GBKToUtf8("推广信息错误"), _name, _pwd, registerStruct->LogonTimes);
			break;
		default:
			_callback->onPlatformRegistCallback(false, _fastRegist, GBKToUtf8("注册失败"), _name, _pwd, registerStruct->LogonTimes);
			break;
		}
	}

	HNPlatformRegist::HNPlatformRegist(IHNPlatformRegist* callback)
		: HNPlatformLogicBase(callback)
		, _fastRegist(true)
	{
		CCAssert(callback != nullptr, "callback is null.");
		_callback = callback;
	}

	HNPlatformRegist::~HNPlatformRegist()
	{
		_callback = nullptr;
	}

	void HNPlatformRegist::platformRegist()
	{
		if (PlatformLogic()->isConnect())
		{
			// 0-快速注册，1-普通注册，2-微信登陆，3-QQ登陆
			std::string onlyString = Operator::requestChannel("sysmodule", "GetSerialNumber");
			if (_registType == 0)
			{
				PlatformLogic()->regist(_registType, onlyString);
			}
			else if (_registType == 1)
			{
				PlatformLogic()->regist(_registType, onlyString, _bBoy, _uionID, _nickName, _name, _pwd);
			}
			else if (_registType == 2 || _registType == 3)
			{
				PlatformLogic()->regist(_registType, onlyString, _bBoy, _uionID, _nickName, _name, _pwd, _phone, _headUrl);
			}
			else
			{
			}
		}
		else
		{
			PlatformLogic()->connect();
		}
	}

	void HNPlatformRegist::getVerifyCode()
	{
		if (PlatformLogic()->isConnect())
		{
			MSG_GP_SmsVCode SmsVCode;
			SmsVCode.nType = 4;
			strcpy(SmsVCode.szName, PlatformLogic()->loginResult.szName);
			strcpy(SmsVCode.szMobileNo, _phone.c_str());
			PlatformLogic()->sendData(MDM_GP_SMS, ASS_GP_SMS_VCODE, &SmsVCode, sizeof(SmsVCode),
				HN_SOCKET_CALLBACK(HNPlatformRegist::verifyCodeSelector, this));
		}
		else
		{
			PlatformLogic()->connect();
		}
	}

	bool HNPlatformRegist::verifyCodeSelector(HNSocketMessage* socketMessage)
	{
		CCAssert(sizeof (MSG_GP_SmsVCode) == socketMessage->objectSize, "MSG_GP_SmsVCode is error.");
		if (socketMessage->objectSize != sizeof(MSG_GP_SmsVCode)) return true;

		MSG_GP_SmsVCode *smsVCode = (MSG_GP_SmsVCode *)socketMessage->object;

		_callback->onPlatformGetVerifyCode(true, smsVCode->szMobileNo, smsVCode->szVCode, GBKToUtf8("获取验证码成功"));
		return true;
	}
}