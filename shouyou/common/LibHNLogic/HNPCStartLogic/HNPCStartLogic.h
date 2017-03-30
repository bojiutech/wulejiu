#ifndef __HNPCStartLogic_H__
#define __HNPCStartLogic_H__

#include "HNLogic/HNLogicBase.h"
#include <string>

namespace HN
{
	class HNPCStartLogicDelegate
	{
	public:
		virtual void onStartGameError(const std::string& message){}
	};

	class HNPCStartLogic : public HNLogicBase, public IRoomMessageDelegate, public IGameMessageDelegate
	{
	public:
		void connect(const std::string& ip, int port);
		virtual void start() override;
		virtual void stop() override;
		HNPCStartLogic(HNPCStartLogicDelegate* delegate);
		~HNPCStartLogic();

		// 房间消息
		virtual void I_R_M_GameBaseInfo(GameInfoEx* data);

		// 玩家信息
		virtual void I_R_M_UserInfoList(UserInfoStruct* data);
		
	protected:
		HNPCStartLogicDelegate* _delegate;
	};
}

#endif