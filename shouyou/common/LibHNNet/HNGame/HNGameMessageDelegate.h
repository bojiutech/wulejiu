#ifndef __HN_GameMessageDelegate_H__
#define __HN_GameMessageDelegate_H__

#include "HNBaseType.h"
#include "HNNetProtocol/HNProtocolExport.h"
#include <vector>

namespace HN
{
	
	class IGameMessageDelegate	: public IGameMatchMessageDelegate
								, public IGameChartMessageDelegate
								, public IUserActionMessageDelegate
	{
	public:		
		// 网络断开
		virtual void I_R_M_DisConnect() {}

		// 用户同意
		virtual void I_R_M_UserAgree(MSG_GR_R_UserAgree* agree){}

		// 游戏开始消息
		virtual void I_R_M_GameBegin(BYTE bDeskNO){}
		
		// 结算消息
		virtual void I_R_M_GamePoint(void * object, INT objectSize){}
		
		// 游戏结束消息
		virtual void I_R_M_GameEnd(BYTE bDeskNO){}

		// 游戏信息消息
		virtual void I_R_M_GameInfo(MSG_GM_S_GameInfo* pGameInfo){}

		// 游戏状态消息
		virtual void I_R_M_GameStation(void* object, INT objectSize){}

		// 游戏消息
		virtual bool onGameMessage(NetMessageHead* messageHead, void* object, INT objectSize){ return true; }

		// VIP房间消息
		virtual bool I_R_M_VIP_Room(NetMessageHead* messageHead, void* object, INT objectSize){ return true; }

		// PC专用
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		// 房间信息
		virtual void I_R_M_GameBaseInfo(GameInfoEx* data){}

		// 玩家信息
		virtual void I_R_M_UserInfoList(UserInfoStruct* data){}
#endif
	};
}

#endif	//__HN_GameMessageDelegate_H__

