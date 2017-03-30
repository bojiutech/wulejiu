#include "HNPlatformLogicBase.h"

namespace HN
{
	void HNPlatformLogicBase::start()
	{
		PlatformLogic()->addObserver(this);
	}

	void HNPlatformLogicBase::stop()
	{
		PlatformLogic()->removeObserver(this);
	}

	HNPlatformLogicBase::HNPlatformLogicBase(IHNPlatformLogicBase* callback)
	{
		CCAssert(callback != nullptr, "callback is null.");
		_callback = callback;
	}

	HNPlatformLogicBase::~HNPlatformLogicBase()
	{

	}

	void HNPlatformLogicBase::I_P_M_DisConnect()
	{
		if (PlatformConfig::getInstance()->getSceneState() == PlatformConfig::SCENE_STATE::OTHER) return;
		__NotificationCenter::getInstance()->postNotification(DISCONNECT);
	}

	void HNPlatformLogicBase::I_P_M_NewsSys(MSG_GR_RS_NormalTalk* pData)
	{
		_callback->onPlatformNewsCallback(pData->szMessage);
	}
}