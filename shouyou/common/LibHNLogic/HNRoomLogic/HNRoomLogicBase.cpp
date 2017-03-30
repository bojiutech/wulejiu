#include "HNRoomLogic/HNRoomLogicBase.h"
#include "HNNetExport.h"

namespace HN
{
	void HNRoomLogicBase::start()
	{
		RoomLogic()->addRoomObserver(this);
		PlatformLogic()->addObserver(this);
	}

	void HNRoomLogicBase::stop()
	{
		RoomLogic()->removeRoomObserver(this);
		PlatformLogic()->removeObserver(this);
	}

	void HNRoomLogicBase::requestLogin(UINT roomID, bool forced/* = false*/)
	{
		ComRoomInfo* pRoomInfo = RoomInfoModule()->getByRoomID(roomID);
		RoomLogic()->setSelectedRoom(pRoomInfo);
		GameCreator()->setCurrentGame(pRoomInfo->uNameID);
		GameCreator()->setGameKindId(pRoomInfo->uNameID, pRoomInfo->uKindID);

		if(nullptr == pRoomInfo)
		{
			_callback->onRoomLoginCallback(false, GBKToUtf8("������Ϸ������Ƿ�����"), _roomID, -1);
		}
		else
		{
			if (PlatformLogic()->loginResult.i64Money < pRoomInfo->iLessPoint)
			{
				char buffer[128];
				sprintf(buffer, GBKToUtf8("���Ľ��С��%u, ���ܽ��뷿��, �뵽�̵��ֵ��"), pRoomInfo->iLessPoint);
				_callback->onRoomLoginCallback(false, buffer, _roomID, -1);
			}
			else if(pRoomInfo->iMaxPoint != 0 && (PlatformLogic()->loginResult.i64Money > pRoomInfo->iMaxPoint))
			{
				char buffer[128];
				sprintf(buffer, GBKToUtf8("���Ľ�Ҵ���%u, ���ܽ��뷿��,����������롣"), pRoomInfo->iMaxPoint);
				_callback->onRoomLoginCallback(false, buffer, _roomID, -1);
			}
			else
			{
				_roomID = roomID;
				_forced = forced;

				if (RoomLogic()->getRoomRule() & GRR_QUEUE_GAME)		
				{
					// �Ŷӻ�
					// ���ӷ��������
					UserInfoModule()->clear();
					RoomLogic()->connect(pRoomInfo->szServiceIP, pRoomInfo->uServicePort);
				}
				else												
				{
					// ��ҳ����ۻ���
					// ���ӷ��������
					UserInfoModule()->clear();
					RoomLogic()->connect(pRoomInfo->szServiceIP, pRoomInfo->uServicePort);
				}
			}
		}
	}

	void HNRoomLogicBase::requestSit(BYTE deskNo)
	{
		
		ComRoomInfo* pRoomInfo = RoomLogic()->getSelectedRoom();
		if(nullptr == pRoomInfo)
		{
			_callback->onRoomSitCallback(false, GBKToUtf8("������ϢΪ��"), _roomID, deskNo, INVALID_DESKSTATION);
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
			requestSit(deskNo, seatNo);
		}	
		else
		{
			_callback->onRoomSitCallback(false, GBKToUtf8("����û�п���"), _roomID, deskNo, seatNo);
		}
	}

	void HNRoomLogicBase::requestSit(BYTE deskNo, BYTE seatNo)
	{
		MSG_GR_S_UserSit data;
		data.bDeskIndex   = deskNo;
		data.bDeskStation = seatNo;
		RoomLogic()->sendData(MDM_GR_USER_ACTION, ASS_GR_USER_SIT, &data ,sizeof(data));
	}

	void HNRoomLogicBase::requestJoinQueue()
	{
		RoomLogic()->sendData(MDM_GR_USER_ACTION, ASS_GR_JOIN_QUEUE);
	}

	void HNRoomLogicBase::requestQuickSit(BYTE deskNo/* = 255*/, std::string password/* = ""*/)
	{
		MSG_GR_S_UserSit data;
		data.bDeskIndex = deskNo;
		data.bDeskStation = 255;
		strcpy(data.szCreateRoomPassword, password.c_str());
		RoomLogic()->sendData(MDM_GR_USER_ACTION, ASS_GR_FAST_JOIN_IN, &data, sizeof(data));
	}

	void HNRoomLogicBase::requestRoomPasword(UINT roomId, const std::string& password)
	{
		MSG_GP_CheckRoomPasswd data;
		data.uRoomID = roomId;
		strcpy(data.szMD5PassWord, MD5_CTX::MD5String(password).c_str());
		PlatformLogic()->sendData(MDM_GP_LIST, ASS_GP_ROOM_PASSWORD, &data, sizeof(data));
	}

	void HNRoomLogicBase::I_R_M_SitError(const std::string& message)
	{
		_callback->onRoomSitCallback(false, message, INVALID_USER_ID, INVALID_DESKNO, INVALID_DESKSTATION);
	}

	void HNRoomLogicBase::I_R_M_UserSit(MSG_GR_R_UserSit * userSit, const UserInfoStruct* user)
	{
		if (userSit->dwUserID == PlatformLogic()->loginResult.dwUserID && (nullptr == userSit ||  nullptr == user)) 
		{
			_callback->onRoomSitCallback(false, GBKToUtf8("����ʧ��"), _roomID, INVALID_DESKNO, INVALID_DESKSTATION);
			RoomLogic()->close();
			return;
		}

		// ������������
		if (userSit->dwUserID == PlatformLogic()->loginResult.dwUserID)
		{
			if (INVALID_DESKNO != userSit->bDeskIndex && INVALID_DESKSTATION != userSit->bDeskStation)
			{
				_callback->onRoomSitCallback(true, GBKToUtf8("���³ɹ�"), _roomID, userSit->bDeskIndex, userSit->bDeskStation);
			}
		}
	}

	void HNRoomLogicBase::I_R_M_QueueUserSit(BYTE deskNo, const std::vector<QUEUE_USER_SIT_RESULT*>& users)
	{
		if(INVALID_DESKNO == deskNo)
		{
			_callback->onRoomQueueSitCallback(false, GBKToUtf8("��λ�Ŵ���"), _roomID, deskNo);
			return;
		}

		bool find = false;
		for (auto iter = users.begin(); iter != users.end(); ++iter)
		{
			if((*iter)->dwUserID == PlatformLogic()->loginResult.dwUserID)
			{
				find = true;
				break;
			}
		}
		if (find)
		{
			_callback->onRoomQueueSitCallback(true, GBKToUtf8("�ɹ�������Ϸ"), _roomID, deskNo);
		}
		else
		{
			_callback->onRoomQueueSitCallback(false, GBKToUtf8("δ�������"), _roomID, deskNo);
		}
	}

	void HNRoomLogicBase::I_R_M_UserUp(MSG_GR_R_UserUp * userUp, const UserInfoStruct* user)
	{
		if(INVALID_DESKNO == userUp->bDeskIndex)
		{
			_callback->onRoomSitUpCallback(false, GBKToUtf8("վ��ʧ��"), userUp->bDeskIndex, userUp->bDeskStation);
		}
		else
		{
			_callback->onRoomSitUpCallback(true, GBKToUtf8("վ��ɹ�"), userUp->bDeskIndex, userUp->bDeskStation);
		}
	}

	void HNRoomLogicBase::I_R_M_DisConnect()
	{
		//_callback->onRoomDisConnect(GBKToUtf8("����Ͽ�����"));
	}

	void HNRoomLogicBase::I_R_M_Connect(bool result)
	{
		if(!result)
		{
			_callback->onRoomLoginCallback(false, GBKToUtf8("��������ʧ��"), _roomID, -1);
		}
		else
		{
			ComRoomInfo* pRoomInfo = RoomLogic()->getSelectedRoom();
			if(pRoomInfo == nullptr)
			{
				_callback->onRoomLoginCallback(false, GBKToUtf8("������ϢΪ��"), _roomID, -1);
			}
			else
			{
				RoomLogic()->login(pRoomInfo->uNameID, _forced);
			}			
		}
	}

	void HNRoomLogicBase::I_R_M_Login(bool success, UINT handleCode, const std::string& message)
	{
		if(!success)
		{
			_callback->onRoomLoginCallback(false, message, _roomID, handleCode);
		}
		else
		{
			;
		}
	}

	void HNRoomLogicBase::I_R_M_LoginFinish()
	{
		UserInfoStruct info = RoomLogic()->loginResult.pUserInfoStruct;

		if (INVALID_DESKNO != info.bDeskNO && INVALID_DESKSTATION != info.bDeskStation)
		{
			_callback->onRoomSitCallback(true, GBKToUtf8("���³ɹ�"), _roomID, info.bDeskNO, info.bDeskStation);
		}
		else
		{
			_callback->onRoomLoginCallback(true, GBKToUtf8("���ӳɹ�"), _roomID, -1);
		}
	}

	void HNRoomLogicBase::I_R_M_UserCome(UserInfoStruct* user) 
	{
		_callback->onRoomUserCome(user->dwUserID);
	}

	void HNRoomLogicBase::I_R_M_UserLeft(const UserInfoStruct* user)
	{
		_callback->onRoomUserLeft(user->dwUserID);
	}

	void HNRoomLogicBase::I_R_M_GamePoint(void * object, INT objectSize)
	{

	}

	void HNRoomLogicBase::I_P_M_RoomPassword(MSG_GP_S_C_CheckRoomPasswd* pData)
	{
		CCAssert(pData != nullptr, "size error.");
		_callback->onPlatformRoomPassEnter(pData->bRet, pData->uRoomID);
	}

	HNRoomLogicBase::HNRoomLogicBase(IHNRoomLogicBase* callback)
	{
		CCAssert(callback != nullptr, "callback is null.");
		_callback = callback;
	}

	HNRoomLogicBase::~HNRoomLogicBase()
	{
		_callback = nullptr;
	}
}