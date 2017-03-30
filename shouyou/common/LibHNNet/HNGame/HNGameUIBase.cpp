#include "HNGameUIBase.h"
#include "HNRoom/HNRoomLogic.h"

namespace HN
{
	HNGameUIBase::HNGameUIBase()
	{

	}

	HNGameUIBase::~HNGameUIBase()
	{
		unLoadUI();
	}

	bool HNGameUIBase::init()
	{
		if (!HNLayer::init())
		{
			return false;
		}

		loadUI();

		return true;
	}

	void HNGameUIBase::loadUI()
	{

	}

	void HNGameUIBase::unLoadUI()
	{

	}

	void HNGameUIBase::sendData(UINT MainID, UINT AssistantID, void* object, INT objectSize)
	{
		RoomLogic()->sendData(MainID, AssistantID, object, objectSize);
	}
}