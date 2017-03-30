#ifndef __HNPlatformLogicBase_H__
#define __HNPlatformLogicBase_H__

#include "HNLogic/HNLogicBase.h"
#include "HNNetExport.h"

namespace HN
{
	/*
	 * common interface for platform logic.
	 */
	class IHNPlatformLogicBase 
	{
	public:
		virtual void onPlatformDisConnectCallback(const std::string& message){}
		virtual void onPlatformNewsCallback(const std::string& message){};
	};

	/*
	 * platform logic base.
	 */
	class HNPlatformLogicBase: public HNLogicBase, public IPlatformMessageDelegate
	{
	public:
		virtual void start() override;
		virtual void stop() override;
		HNPlatformLogicBase(IHNPlatformLogicBase* callback);
		virtual ~HNPlatformLogicBase();
	public:
		// ����Ͽ�
		virtual void I_P_M_DisConnect() override;

		// ����ϵͳ��Ϣ
		virtual void I_P_M_NewsSys(MSG_GR_RS_NormalTalk* pData) override;
	protected:
		IHNPlatformLogicBase* _callback;
	};
}


#endif