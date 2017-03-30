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
		// ƽ̨��½��Ϣ
		PlatformLogic()->loginResult.dwUserID = data->uisMeUserInfo.GameUserInfo.dwUserID;

		// �����½��Ϣ
		RoomLogic()->loginResult.pUserInfoStruct.dwUserID = data->uisMeUserInfo.GameUserInfo.dwUserID;
		RoomLogic()->loginResult.pUserInfoStruct.bDeskNO  = data->uisMeUserInfo.GameUserInfo.bDeskNO;

		// ������Ϣ
		ComRoomInfo roomInfo;

		// ��Ҫ��Ϣ
		roomInfo.dwRoomRule = data->dwRoomRule;
		roomInfo.uComType = data->uComType;
		roomInfo.uRoomID = data->uRoomID;
		roomInfo.uNameID = data->uNameID;
		roomInfo.uDeskPeople = data->uDeskPeople;
		sprintf(roomInfo.szGameRoomName, data->szGameRoomName);
		
		// ��Ϣ��¼
		RoomInfoModule()->addRoom(&roomInfo);
		RoomLogic()->setSelectedRoom(RoomInfoModule()->getByRoomID(data->uRoomID));

		// У������
		HNSocketProtocolData::PlatformCheckCode = 0;
		HNSocketProtocolData::GameCheckCode = 0;
		RoomLogic()->setConnect(true);

		// ������Ϸ
		UINT nameId = RoomLogic()->getSelectedRoom()->uNameID;
		BYTE deskId = RoomLogic()->loginResult.pUserInfoStruct.bDeskNO;
		
		// ֹͣ������Ϣ��������Ϸ
		stop();
		if (!GameCreator()->startGameClient(nameId, deskId, true))
		{
			std::string message = StringUtils::format("��Ϸ����ʧ��(nameid:%d, deskid:%d)", nameId, deskId);
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