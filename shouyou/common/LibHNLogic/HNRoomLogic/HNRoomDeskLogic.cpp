#include "HNRoomDeskLogic.h"

namespace HN
{
	void HNRoomDeskLogic::start()
	{
		RoomLogic()->addRoomObserver(this);
	}

	void HNRoomDeskLogic::stop()
	{
		RoomLogic()->removeRoomObserver(this);
	}

	void HNRoomDeskLogic::requestSit(BYTE deskNo, const std::string& password)
	{
		ComRoomInfo* pRoomInfo = RoomLogic()->getSelectedRoom();
		if(nullptr == pRoomInfo)
		{
			_callback->onDeskSitCallback(false, GBKToUtf8("���䲻���ڣ�"), _roomID, deskNo, INVALID_DESKSTATION);
			return;
		}

		std::vector<UserInfoStruct*> deskUsers;
		UserInfoModule()->findDeskUsers(deskNo, deskUsers);

		std::vector<bool> empty(pRoomInfo->uDeskPeople, true);

		// �������µ��û���λ�� 
		for (auto user : deskUsers)
		{
			if (USER_SITTING == user->bUserState		    // ����
				|| USER_PLAY_GAME == user->bUserState		// ��Ϸ��
				|| USER_CUT_GAME == user->bUserState		// ����
				|| USER_ARGEE == user->bUserState)			// ͬ����Ϸ
			{
				empty[user->bDeskStation] = false;
			}
		}

		BYTE seatNo = INVALID_DESKSTATION;
		for(size_t i = 0; i < empty.size(); i++)
		{
			if(empty[i])
			{
				seatNo = i; 
				break;
			}
		}

		if(INVALID_DESKSTATION != seatNo)
		{
			requestSit(deskNo, seatNo, password);
		}	
		else
		{
			_callback->onDeskSitCallback(false, GBKToUtf8("����û�п���"), _roomID, deskNo, seatNo);
		}
	}

	void HNRoomDeskLogic::requestSit(BYTE deskNo, BYTE seatNo, const std::string& password)
	{
		MSG_GR_S_UserSit data;
		data.bDeskIndex   = deskNo;
		data.bDeskStation = seatNo;
		strcpy(data.szPassword, password.c_str());
		RoomLogic()->sendData(MDM_GR_USER_ACTION, ASS_GR_USER_SIT, &data ,sizeof(data));
	}

	void HNRoomDeskLogic::requestQuickSit()
	{
		RoomLogic()->sendData(MDM_GR_USER_ACTION, ASS_GR_FAST_JOIN_IN, nullptr, 0);
	}

	HNRoomDeskLogic::HNRoomDeskLogic(IHNRoomDeskLogic* callback)
	{
		CCAssert(callback != nullptr, "callback is null.");
		_callback = callback;
		ComRoomInfo* pRoomInfo = RoomLogic()->getSelectedRoom();
		CCAssert(pRoomInfo != nullptr, "room info is null.");
		_roomID = pRoomInfo->uRoomID;
	}

	HNRoomDeskLogic::~HNRoomDeskLogic()
	{
		_callback = nullptr;
	}

	void HNRoomDeskLogic::I_R_M_UserSit(MSG_GR_R_UserSit * userSit, const UserInfoStruct* user)
	{
		if (nullptr == userSit ||  nullptr == user) 
		{			
			return;
		}

		// ������������
		if (userSit->dwUserID == PlatformLogic()->loginResult.dwUserID)
		{
			if (INVALID_DESKNO != userSit->bDeskIndex && INVALID_DESKSTATION != userSit->bDeskStation)
			{
				_callback->onDeskSitCallback(true, GBKToUtf8("���³ɹ�"), _roomID, userSit->bDeskIndex, userSit->bDeskStation);
			}
		}
		else
		{
			_callback->onRoomDeskUserCountChanged();
		}
	}

	// �û�����ʧ��
	void HNRoomDeskLogic::I_R_M_SitError(const std::string& message)
	{
		_callback->onDeskSitCallback(false, message, _roomID, INVALID_DESKNO, INVALID_DESKSTATION);
	}

	void HNRoomDeskLogic::I_R_M_UserUp(MSG_GR_R_UserUp * userUp, const UserInfoStruct* user)
	{
		_callback->onRoomDeskUserCountChanged();
	}

	void HNRoomDeskLogic::I_R_M_LockDesk(BYTE deskNo)
	{
		_callback->onRoomDeskLock(deskNo);
	}

	void HNRoomDeskLogic::I_R_M_UnLockDesk(BYTE deskNo)
	{
		_callback->onRoomDeskUnLock(deskNo);
	}

	void HNRoomDeskLogic::I_R_M_UserCome(UserInfoStruct* user)
	{
		_callback->onRoomUserCome(user->dwUserID);
	}
	
	void HNRoomDeskLogic::I_R_M_UserLeft(const UserInfoStruct* user)
	{
		_callback->onRoomUserLeft(user->dwUserID);
	}

	void HNRoomDeskLogic::I_R_M_DisConnect()
	{
		if (PlatformConfig::getInstance()->getSceneState() == PlatformConfig::SCENE_STATE::OTHER) return;
		__NotificationCenter::getInstance()->postNotification(DISCONNECT);
	}
}