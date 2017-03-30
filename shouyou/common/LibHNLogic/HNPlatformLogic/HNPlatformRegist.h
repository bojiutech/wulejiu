#ifndef __HNPlatformRegist_H__
#define __HNPlatformRegist_H__

#include "HNPlatformLogic/HNPlatformLogicBase.h"

namespace HN
{
	/*
	 * ע��ӿ�
	 */
	class IHNPlatformRegist: public IHNPlatformLogicBase
	{
	public:
		virtual void onPlatformRegistCallback(bool success, bool fastRegist, const std::string& message,
			const std::string&name, const std::string& pwd, int loginTimes){}

		// ��ȡ��֤����
		virtual void onPlatformGetVerifyCode(bool success, const std::string& phone,
			const std::string& code, const std::string& message) {}
	};

	/*
	 * ע���߼�
	 */
	class HNPlatformRegist: public HNPlatformLogicBase
	{
	public:
		// ע������
		//bool requestRegist(const std::string &name, const std::string pwd, bool fastRegist);

		// ע������
		bool requestRegist(BYTE RegistType = 0, const std::string &name = "", const std::string pwd = "", 
			const std::string& phoneNum = "", const std::string& nickName = "", const std::string& uionID = "", const std::string& headUrl = "", bool bBoy = true);

		// ƽ̨����
		virtual void I_P_M_Connect(bool result) override;
		
		// ƽ̨ע��
		virtual void I_P_M_Regist(MSG_GP_S_Register* registerStruct, UINT ErrorCode) override;
		
		// ���캯��
		HNPlatformRegist(IHNPlatformRegist* callback);

		// ��������
		virtual ~HNPlatformRegist();

	private:
		bool verifyCodeSelector(HNSocketMessage* socketMessage);

	protected:
		// �Ƿ����ע��
		bool _fastRegist;

		// ע������
		BYTE _registType = 0;

		// �Ƿ��ȡ��֤��
		bool _getVerifyCode = false;

		// ע���û���
		std::string _name = "";

		// ע������
		std::string _pwd = "";

		// �绰����
		std::string _phone = "";

		// ͷ��url
		std::string _headUrl = "";

		// �ǳ�
		std::string _nickName = "";

		// ΢�ţ�QQ��½��֤��
		std::string _uionID = "";

		// �Ա�
		bool		_bBoy = true;

		// �ص�
		IHNPlatformRegist* _callback = nullptr;

		// ע���߼�
		void platformRegist();

		// ��ȡ��֤��
		void getVerifyCode();

		// ע�᷵����
		enum REGIST_CODE
		{
			eFAILE     = 0, // ע��ʧ��
			eSUCCESS   = 1, // ע��ɹ�
			eEXIST     = 2, // ��ͬ����
			eSENSITIVE = 3, // ���дʻ�
			eNUMLIMIT  = 4, // ע������
			eAGENTERR  = 5, // �����̴���
			eTUIGUANGERR = 6, // �ƹ���Ϣ����
		};
	};
}


#endif // !__HNPlatformRegist_H__
