#ifndef __HNPlatformRegist_H__
#define __HNPlatformRegist_H__

#include "HNPlatformLogic/HNPlatformLogicBase.h"

namespace HN
{
	/*
	 * 注册接口
	 */
	class IHNPlatformRegist: public IHNPlatformLogicBase
	{
	public:
		virtual void onPlatformRegistCallback(bool success, bool fastRegist, const std::string& message,
			const std::string&name, const std::string& pwd, int loginTimes){}

		// 获取验证码结果
		virtual void onPlatformGetVerifyCode(bool success, const std::string& phone,
			const std::string& code, const std::string& message) {}
	};

	/*
	 * 注册逻辑
	 */
	class HNPlatformRegist: public HNPlatformLogicBase
	{
	public:
		// 注册请求
		//bool requestRegist(const std::string &name, const std::string pwd, bool fastRegist);

		// 注册请求
		bool requestRegist(BYTE RegistType = 0, const std::string &name = "", const std::string pwd = "", 
			const std::string& phoneNum = "", const std::string& nickName = "", const std::string& uionID = "", const std::string& headUrl = "", bool bBoy = true);

		// 平台连接
		virtual void I_P_M_Connect(bool result) override;
		
		// 平台注册
		virtual void I_P_M_Regist(MSG_GP_S_Register* registerStruct, UINT ErrorCode) override;
		
		// 构造函数
		HNPlatformRegist(IHNPlatformRegist* callback);

		// 析构函数
		virtual ~HNPlatformRegist();

	private:
		bool verifyCodeSelector(HNSocketMessage* socketMessage);

	protected:
		// 是否快速注册
		bool _fastRegist;

		// 注册类型
		BYTE _registType = 0;

		// 是否获取验证码
		bool _getVerifyCode = false;

		// 注册用户名
		std::string _name = "";

		// 注册密码
		std::string _pwd = "";

		// 电话号码
		std::string _phone = "";

		// 头像url
		std::string _headUrl = "";

		// 昵称
		std::string _nickName = "";

		// 微信，QQ登陆验证码
		std::string _uionID = "";

		// 性别
		bool		_bBoy = true;

		// 回调
		IHNPlatformRegist* _callback = nullptr;

		// 注册逻辑
		void platformRegist();

		// 获取验证码
		void getVerifyCode();

		// 注册返回码
		enum REGIST_CODE
		{
			eFAILE     = 0, // 注册失败
			eSUCCESS   = 1, // 注册成功
			eEXIST     = 2, // 相同名称
			eSENSITIVE = 3, // 敏感词汇
			eNUMLIMIT  = 4, // 注册限制
			eAGENTERR  = 5, // 代理商错误
			eTUIGUANGERR = 6, // 推广信息错误
		};
	};
}


#endif // !__HNPlatformRegist_H__
