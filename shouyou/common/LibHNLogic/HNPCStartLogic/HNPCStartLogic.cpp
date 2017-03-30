#include "HNPCStartLogic/HNPCStartLogic.h"
#include "HNNetExport.h"

namespace HN
{
	void HNPCStartLogic::connect(const std::string& ip, int port)
	{
		RoomLogic()->connect(ip.c_str(), port);
	}

	void HNPCStartLogic::start()
	{
		RoomLogic()->addObserver(this);
		RoomLogic()->addRoomObserver(this);
	}

	void HNPCStartLogic::stop()
	{
		RoomLogic()->removeObserver(this);
		RoomLogic()->removeRoomObserver(this);
	}

	HNPCStartLogic::HNPCStartLogic(HNPCStartLogicDelegate* delegate)
		:_delegate(delegate)
	{

	}

	HNPCStartLogic::~HNPCStartLogic()
	{

	}

	void HNPCStartLogic::I_R_M_GameBaseInfo(GameInfoEx* data)
	{
		// 平台登陆信息
		PlatformLogic()->loginResult.dwUserID = data->uisMeUserInfo.GameUserInfo.dwUserID;

		// 房间登陆信息
		RoomLogic()->loginResult.pUserInfoStruct.dwUserID = data->uisMeUserInfo.GameUserInfo.dwUserID;
		RoomLogic()->loginResult.pUserInfoStruct.bDeskNO  = data->uisMeUserInfo.GameUserInfo.bDeskNO;

		// 房间信息
		ComRoomInfo roomInfo;

		// 主要信息
		roomInfo.dwRoomRule = data->dwRoomRule;
		roomInfo.uComType = data->uComType;
		roomInfo.uRoomID = data->uRoomID;
		roomInfo.uNameID = data->uNameID;
		roomInfo.uDeskPeople = data->uDeskPeople;
		sprintf(roomInfo.szGameRoomName, data->szGameRoomName);
		
		// 信息记录
		RoomInfoModule()->addRoom(&roomInfo);
		RoomLogic()->setSelectedRoom(RoomInfoModule()->getByRoomID(data->uRoomID));

		// 校验数据
		HNSocketProtocolData::PlatformCheckCode = 0;
		HNSocketProtocolData::GameCheckCode = 0;
		RoomLogic()->setConnect(true);

		// 启动游戏
		UINT nameId = RoomLogic()->getSelectedRoom()->uNameID;
		BYTE deskId = RoomLogic()->loginResult.pUserInfoStruct.bDeskNO;
		
		// 停止接受消息，启动游戏
		stop();
		if (!GameCreator()->startGameClient(nameId, deskId, true))
		{
			std::string message = StringUtils::format("游戏启动失败(nameid:%d, deskid:%d)", nameId, deskId);
			if (_delegate)
			{
				_delegate->onStartGameError(message);
			}
		}
	}

	void HNPCStartLogic::I_R_M_UserInfoList(UserInfoStruct* data)
	{

	}
}