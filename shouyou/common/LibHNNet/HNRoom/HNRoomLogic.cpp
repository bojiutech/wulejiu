#include "HNRoomLogic.h"
#include "HNRoomMessageDelegate.h"
#include "HNData/HNRoomInfoModule.h"
#include "HNData/HNUserInfoModule.h"
#include "HNPlatform/HNPlatformExport.h"
#include "HNSocket/HNSocketProtocolData.h"
#include "HNSocket/HNSocketLogic.h"
#include "HNNetProtocol/HNProtocolExport.h"
#include "HNGame/HNGameMessageDelegate.h"
#include "HNCommon/HNConverCode.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "HNNetProtocol/HNRoomForPCMessage.h"
#endif

namespace HN
{
	static HNRoomLogic* sHNRoomLogic = nullptr;

	HNRoomLogic* HNRoomLogic::getInstance()
	{
		if (nullptr == sHNRoomLogic)
		{
			sHNRoomLogic = new HNRoomLogic();
			sHNRoomLogic->init();
		}
		return sHNRoomLogic;
	}
	
	HNRoomLogic::HNRoomLogic(void)
		: _gameRoomRule(0)
		, _serverPort(-1)
		, _connected(false)
		, _logined(false)
		, _selectedRoom(nullptr)
	{
        memset(&loginResult, 0x00, sizeof(loginResult));
		_socketLogic = new HNSocketLogic(this, "game");
		
		_gameNotifyQueue = new HNUIDelegateQueue<IGameMessageDelegate*>();
		_addGameNotifyQueue = new HNUIDelegateQueue<IGameMessageDelegate*>();
		_removeGameNotifyQueue = new HNUIDelegateQueue<IGameMessageDelegate*>();

		_roomNotifyQueue = new HNUIDelegateQueue<IRoomMessageDelegate*>();
		_addRoomNotifyQueue = new HNUIDelegateQueue<IRoomMessageDelegate*>();
		_removeRoomNotifyQueue = new HNUIDelegateQueue<IRoomMessageDelegate*>();
	}

	HNRoomLogic::~HNRoomLogic(void)
	{
		HN_SAFE_DELETE(_addGameNotifyQueue);
		HN_SAFE_DELETE(_gameNotifyQueue);
		HN_SAFE_DELETE(_removeGameNotifyQueue);
		HN_SAFE_DELETE(_roomNotifyQueue);
		HN_SAFE_DELETE(_addRoomNotifyQueue);
		HN_SAFE_DELETE(_removeRoomNotifyQueue);
		HN_SAFE_DELETE(_socketLogic);
	}

	bool HNRoomLogic::init() 
	{
		return true;
	}

	bool HNRoomLogic::connect(const CHAR* ipOrHost, INT port)
	{
		std::string ip(ipOrHost);
		if(!HNSocket::isValidIP(ip))
		{
			ip = HNSocket::getIpAddress(ip.c_str()).at(0);
		}
		_serverAddress = ip;
		_serverPort    = port;
		return _socketLogic->openWithIp(_serverAddress.c_str(), _serverPort);
	}

	bool HNRoomLogic::close()
	{
		_connected = false;
		return _socketLogic->close();
	}

	bool HNRoomLogic::isConnect() const 
	{ 
		return _connected && _socketLogic->connected(); 
	} 

	void HNRoomLogic::setConnect(bool isConnect)
	{
		_connected = isConnect;
	}

	bool HNRoomLogic::isLogin() const
	{
		return _logined;
	}

	INT HNRoomLogic::sendData(UINT MainID, UINT AssistantID, void* object, INT objectSize)
	{	
		return _socketLogic->send(MainID, AssistantID, HNSocketProtocolData::GameCheckCode, object, objectSize);
	}

	void HNRoomLogic::sendData(UINT MainID, UINT AssistantID, void* object, INT objectSize, SEL_SocketMessage selector)
	{
		_socketLogic->send(MainID, AssistantID, HNSocketProtocolData::GameCheckCode, object, objectSize);
		_socketLogic->addEventSelector(MainID, AssistantID, selector);
	}

	void HNRoomLogic::addEventSelector(UINT MainID, UINT AssistantID, SEL_SocketMessage selector)
	{
		_socketLogic->addEventSelector(MainID, AssistantID, selector);
	}

	void HNRoomLogic::removeEventSelector(UINT MainID, UINT AssistantID)
	{
		_socketLogic->removeEventSelector(MainID, AssistantID);
	}

	void HNRoomLogic::addObserver(IGameMessageDelegate* delegate)
	{
		_addGameNotifyQueue->addObserver(delegate);
		_removeGameNotifyQueue->removeObserver(delegate);
	}

	void HNRoomLogic::removeObserver(IGameMessageDelegate* delegate)
	{
		_removeGameNotifyQueue->addObserver(delegate);
		_addGameNotifyQueue->removeObserver(delegate);
	}

	void HNRoomLogic::addRoomObserver(IRoomMessageDelegate* delegate)
	{
		_addRoomNotifyQueue->addObserver(delegate);
		_removeRoomNotifyQueue->removeObserver(delegate);
	}

	void HNRoomLogic::removeRoomObserver(IRoomMessageDelegate* delegate)
	{
		_removeRoomNotifyQueue->addObserver(delegate);
		_addRoomNotifyQueue->removeObserver(delegate);
	}

	void HNRoomLogic::login(UINT uGameID, bool forced/* = false*/)
	{
		MSG_GR_S_RoomLogon data = { 0 };

		data.bForced = forced;
		data.uNameID = uGameID;
		data.dwUserID = PlatformLogic()->loginResult.dwUserID;
		strcpy(data.szMD5Pass, PlatformLogic()->loginResult.szMD5Pass);
		sendData(MDM_GR_LOGON, ASS_GR_LOGON_BY_ID, &data, sizeof(data));
	}

	void HNRoomLogic::onConnected(bool connect)
	{
		_connected = connect;
		// �ַ��¼�
		dispatchFrameMessage([connect](IRoomMessageDelegate* delegate) -> bool
		{
			delegate->I_R_M_Connect(connect);
			return false;
		});
	}

	void HNRoomLogic::onDisConnect()
	{
		_logined = false;

		_connected = false;

		// �ַ���Ϣ������
		dispatchFrameMessage([](IRoomMessageDelegate* delegate) -> bool
		{
			delegate->I_R_M_DisConnect();
			return false;
		});

		// �ַ���Ϣ����Ϸ
		dispatchGameMessage([](IGameMessageDelegate* delegate) -> bool
		{
			delegate->I_R_M_DisConnect();
			return false;
		});
	}

	void HNRoomLogic::onSocketMessage(HNSocketMessage* socketMessage)
	{
		std::string msgInfo = StringUtils::format("==========mainid:%d, assistid:%d==========", socketMessage->messageHead.bMainID, socketMessage->messageHead.bAssistantID);
		log("%s", msgInfo.c_str());

		switch (socketMessage->messageHead.bMainID)
		{
		// ����
		case MDM_GR_CONNECT: 
			H_R_M_Connect(&socketMessage->messageHead, socketMessage->object, socketMessage->objectSize);
			break;

		// ��¼��Ϣ
		case MDM_GR_LOGON: 
			H_R_M_Login(&socketMessage->messageHead, socketMessage->object, socketMessage->objectSize);
			break;

		// �û��б�
		case MDM_GR_USER_LIST:
			H_R_M_UserList(&socketMessage->messageHead, socketMessage->object, socketMessage->objectSize);
			break;

		// �û����� 
		case MDM_GR_USER_ACTION:
			H_R_M_UserAction(&socketMessage->messageHead, socketMessage->object, socketMessage->objectSize);
			break;

		// ������Ϣ
		case MDM_GR_ROOM:
			H_R_M_Room(&socketMessage->messageHead, socketMessage->object, socketMessage->objectSize);
			break;

		// VIP������Ϣ
		case MDM_GR_VIP_ROOM:
			H_R_M_VIP_Room(&socketMessage->messageHead, socketMessage->object, socketMessage->objectSize);
			break;

		// �����Ϣ
		case MDM_GM_GAME_FRAME:	
			H_R_M_GameFrame(&socketMessage->messageHead, socketMessage->object, socketMessage->objectSize);
			break;

		// ��Ϸ��Ϣ
		case MDM_GM_GAME_NOTIFY:	
			H_R_M_GameNotify(&socketMessage->messageHead, socketMessage->object, socketMessage->objectSize);
			break;

		// ����
		case MDM_GR_MANAGE:
			H_R_M_Manage(&socketMessage->messageHead, socketMessage->object, socketMessage->objectSize);
			break;

		// PCר����Ϣ
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		// ������Ϣ
		case MDM_GR_GAMEBASEINFO:
			H_R_M_GameBaseInfo(&socketMessage->messageHead, socketMessage->object, socketMessage->objectSize);
			break;

		// ����б�
		case MDM_GR_USERINFO:
			H_R_M_UserInfo(&socketMessage->messageHead, socketMessage->object, socketMessage->objectSize);
			break;

		// �û�״̬
		case MDM_GR_USERSTATUS:
			H_R_M_UserStats(&socketMessage->messageHead, socketMessage->object, socketMessage->objectSize);
			break;

		// �رմ���
		case MDM_GR_CONTROL:
			H_R_M_Control(&socketMessage->messageHead, socketMessage->object, socketMessage->objectSize);
			break;
#endif

		default:
			break;
		}
	}

	void HNRoomLogic::H_R_M_GameNotify(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		dispatchGameMessage([&messageHead, &object, & objectSize](IGameMessageDelegate* delegate) -> bool 
		{
			delegate->onGameMessage((NetMessageHead*)messageHead, object, objectSize);
			return true;
		});
	}

	void HNRoomLogic::H_R_M_GameFrame(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		// ��Ϸ��Ϣ
		if(ASS_GM_GAME_INFO == messageHead->bAssistantID)
		{
			H_R_M_GameInfo(messageHead, object, objectSize);
		}

		// ��Ϸ״̬
		else if(ASS_GM_GAME_STATION == messageHead->bAssistantID)
		{
			H_R_M_GameStation(messageHead, object, objectSize);
		}

		// ��ͨ����
		else if(ASS_GM_NORMAL_TALK == messageHead->bAssistantID)
		{
			H_R_M_NormalTalk(messageHead, object, objectSize);
		}
	}


	void HNRoomLogic::H_R_M_GameInfo(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		MSG_GM_S_GameInfo* pGameInfo = (MSG_GM_S_GameInfo*)object;

		// ��ʾ��Ϣ
		if (messageHead->uMessageSize > (sizeof(MSG_GM_S_GameInfo) - sizeof(pGameInfo->szMessage)))
		{
			dispatchGameMessage([&pGameInfo](IGameMessageDelegate* delegate) -> bool 
			{
				delegate->I_R_M_GameInfo(pGameInfo);
				return true;
			});
		}
	}

	void HNRoomLogic::H_R_M_GameStation(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		dispatchGameMessage([&object, objectSize](IGameMessageDelegate* delegate) -> bool 
		{
			delegate->I_R_M_GameStation(object, objectSize);
			return true;
		});
	}

	void HNRoomLogic::H_R_M_NormalTalk(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		dispatchGameMessage([&object, objectSize](IGameMessageDelegate* delegate) -> bool 
		{
			(dynamic_cast<IGameChartMessageDelegate*>(delegate))->I_R_M_NormalTalk(object, objectSize);
			return true;
		});
	}

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	void HNRoomLogic::H_R_M_GameBaseInfo(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		CCAssert(ASS_GR_GAMEBASEINFO == messageHead->bAssistantID, "assist id error.");
		CCAssert(objectSize == sizeof(GameInfoEx), "size error.");

		dispatchGameMessage([&object, objectSize](IGameMessageDelegate* delegate) -> bool
		{
			delegate->I_R_M_GameBaseInfo((GameInfoEx*)object);
			return true;
		});
	}
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	void HNRoomLogic::H_R_M_UserInfo(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		
		CCAssert(ASS_GR_USERINFOLIST == messageHead->bAssistantID, "assist id error.");
		CHECK_SOCKET_DATA(UserInfoStruct, objectSize, "size error.");

		UserInfoStruct* pData = (UserInfoStruct*)object;

		// ����
		UserInfoModule()->updateUser(pData);

		MSG_GR_R_UserSit userSit;
		userSit.bDeskIndex   = pData->bDeskNO;
		userSit.bDeskStation = pData->bDeskStation;
		userSit.dwUserID     = pData->dwUserID;

		// �ַ���Ϸ��Ϣ(����������Ϣ����
		dispatchGameMessage([&userSit, &pData](IGameMessageDelegate* delegate) -> bool
		{
			delegate->I_R_M_UserSit(&userSit, pData);
			return false;
		});
	}
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	void HNRoomLogic::H_R_M_UserStats(const NetMessageHead* messageHead, void* object, INT objectSize)
	{

	}
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	void HNRoomLogic::H_R_M_Control(const NetMessageHead* messageHead, void* object, INT objectSize)
	{

	}
#endif

	void HNRoomLogic::H_R_M_Room(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		// ��Ϸ��ʼ
		if(ASS_GR_GAME_BEGIN == messageHead->bAssistantID)
		{
			H_R_M_GameBegin(messageHead, object, objectSize);
		}

		// ��Ϸ����
		else if(ASS_GR_USER_POINT == messageHead->bAssistantID)
		{
			H_R_M_UserPoint(messageHead, object, objectSize);
		}

		// ��Ϸ����
		else if(ASS_GR_GAME_END == messageHead->bAssistantID)
		{
			H_R_M_GameEnd(messageHead, object, objectSize);
		}

		// �û�ͬ��
		else if(ASS_GR_USER_AGREE == messageHead->bAssistantID)
		{
			H_R_M_UserAgree(messageHead, object, objectSize);
		}

		// ��ʱ���½�Һͻ���
		else if(ASS_GR_INSTANT_UPDATE == messageHead->bAssistantID)
		{
			H_R_M_InstantUpdate(messageHead, object, objectSize);
		}

		// �û�������Ϣ
		else if(ASS_GR_USER_CONTEST == messageHead->bAssistantID)
		{
			H_R_M_UserContest(messageHead, object, objectSize);
		}

		// ������Ϣ�㲥
		else if (ASS_GR_CONTEST_APPLYINFO == messageHead->bAssistantID)
		{
			H_R_M_ContestNotic(messageHead, object, objectSize);
		}

		// ��������
		else if(ASS_GR_CONTEST_GAMEOVER == messageHead->bAssistantID)
		{
			H_R_M_ContestOver(messageHead, object, objectSize);
		}

		// �û�����̭
		else if(ASS_GR_CONTEST_KICK == messageHead->bAssistantID)
		{
			H_R_M_ContestKick(messageHead, object, objectSize);
		}

		// �����ȴ�����
		else if(ASS_GR_CONTEST_WAIT_GAMEOVER == messageHead->bAssistantID)
		{
			H_R_M_ContestWaitOver(messageHead, object, objectSize);
		}

		// ������ʼ��
		else if(ASS_GR_INIT_CONTEST == messageHead->bAssistantID)
		{
			H_R_M_ContestInit(messageHead, object, objectSize);
		}

		// ������������
		/*else if(ASS_GR_CONTEST_PEOPLE == messageHead->bAssistantID)
		{
			H_R_M_ContestPeople(messageHead, object, objectSize);
		}*/

		// ���˲�����¼
		/*else if(ASS_GR_CONTEST_RECORD == messageHead->bAssistantID)
		{
			H_R_M_ContestRecord(messageHead, object, objectSize);
		}*/

		// ��������
		else if(ASS_GR_CONTEST_AWARDS == messageHead->bAssistantID)
		{
			H_R_M_ContestAward(messageHead, object, objectSize);
		}
	}

	void HNRoomLogic::H_R_M_VIP_Room(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		dispatchGameMessage([&messageHead, &object, &objectSize](IGameMessageDelegate* delegate) -> bool
		{
			delegate->I_R_M_VIP_Room((NetMessageHead*)messageHead, object, objectSize);
			return true;
		});
	}

	void HNRoomLogic::H_R_M_GameBegin(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		BYTE deskNo = (BYTE)messageHead->bHandleCode;
		// �����û�״̬
		UserInfoModule()->transform(deskNo, [](UserInfoStruct* user, INT index) 
		{
			user->bUserState = USER_PLAY_GAME;
		});

		dispatchGameMessage([&messageHead](IGameMessageDelegate* delegate) -> bool 
		{
			delegate->I_R_M_GameBegin((BYTE)messageHead->bHandleCode);
			return false;
		});
	}

	void HNRoomLogic::H_R_M_UserPoint(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		// �ж��Ƿ����������
		auto isNormal = []()->bool
		{
			UINT flag = (RoomLogic()->getRoomRule() & GRR_EXPERCISE_ROOM) || (RoomLogic()->getRoomRule() & GRR_CONTEST);
			bool ret = !(flag != 0);
			return ret;
		};

		if (10 == messageHead->bHandleCode)			// ͬ�����
		{
			// Ч������
			CHECK_SOCKET_DATA(MSG_GR_S_RefalshMoney, objectSize, "MSG_GR_S_RefalshMoney size is error.");

			MSG_GR_S_RefalshMoney * pReflashMoney = (MSG_GR_S_RefalshMoney*)object;

			// ��������
			const UserInfoStruct * pUserInfo = UserInfoModule()->findUser(pReflashMoney->dwUserID);
			if (pUserInfo == nullptr) return;

			UserInfoStruct userInfo = *pUserInfo;
			userInfo.i64Money = pReflashMoney->i64Money;
			UserInfoModule()->updateUser(&userInfo);

			// �����Լ�����
			if (pReflashMoney->dwUserID == PlatformLogic()->loginResult.dwUserID)
			{
				RoomLogic()->loginResult.pUserInfoStruct = userInfo;
				if (isNormal())
				{
					PlatformLogic()->loginResult.i64Money = pReflashMoney->i64Money;
				}				
			}
		}
		else if (11 == messageHead->bHandleCode)	// ͬ������ֵ
		{
			// Ч������
			CHECK_SOCKET_DATA(MSG_GR_S_RefalshMoney, objectSize, "MSG_GR_S_RefalshMoney size is error.");

			MSG_GR_S_RefalshMoney * pReflashMoney = (MSG_GR_S_RefalshMoney*)object;

			// ��������
			const UserInfoStruct * pUserInfo = UserInfoModule()->findUser(pReflashMoney->dwUserID);
			if (pUserInfo == nullptr) return;

			UserInfoStruct userInfo = *pUserInfo;
			userInfo.dwPoint = pReflashMoney->i64Money;
			UserInfoModule()->updateUser(&userInfo);

			// �����Լ�����
			if (pUserInfo->dwUserID == PlatformLogic()->loginResult.dwUserID)
			{
				RoomLogic()->loginResult.pUserInfoStruct = userInfo;
			}

		}
		else if (0 == messageHead->bHandleCode)		// ͬ������ֵ
		{
			// Ч������
			CHECK_SOCKET_DATA(MSG_GR_R_UserPoint, objectSize, "MSG_GR_R_UserPoint size is error.");

			MSG_GR_R_UserPoint * pUserPoint = (MSG_GR_R_UserPoint*)object;

			const UserInfoStruct * pUserInfo = UserInfoModule()->findUser(pUserPoint->dwUserID);
			if (pUserInfo == nullptr) return;

			UserInfoStruct userInfo = *pUserInfo;

			// �����û���Ϣ
			userInfo.dwPoint += pUserPoint->dwPoint;				// �û�����ֵ
			userInfo.i64Money += pUserPoint->dwMoney;				// �û����
			userInfo.uWinCount += pUserPoint->bWinCount;			// ʤ��
			userInfo.uLostCount += pUserPoint->bLostCount;			// ���
			userInfo.uMidCount += pUserPoint->bMidCount;			// ƽ��
			userInfo.uCutCount += pUserPoint->bCutCount;			// �Ӿ�

			UserInfoModule()->updateUser(&userInfo);

			// �����Լ�����
			if (pUserInfo->dwUserID == PlatformLogic()->loginResult.dwUserID)
			{
				RoomLogic()->loginResult.pUserInfoStruct = userInfo;
				if (isNormal() && RoomLogic()->getSelectedRoom()->uNameID != 31011001)
				{
					PlatformLogic()->loginResult.i64Money += pUserPoint->dwMoney;
				}				
			}
		}
		dispatchFrameMessage([&object, objectSize](IRoomMessageDelegate* delegate) -> bool 
		{
			delegate->I_R_M_GamePoint(object, objectSize);
			return false;
		});

		dispatchGameMessage([&object, objectSize](IGameMessageDelegate* delegate) -> bool 
		{
			delegate->I_R_M_GamePoint(object, objectSize);
			return false;
		});
	}

	void HNRoomLogic::H_R_M_GameEnd(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		BYTE deskIndex = (BYTE)messageHead->bHandleCode;

		dispatchGameMessage([deskIndex](IGameMessageDelegate* delegate) -> bool 
		{
			delegate->I_R_M_GameEnd(deskIndex);
			return false;
		});

		if ((_gameRoomRule & GRR_CONTEST) || (_gameRoomRule & GRR_QUEUE_GAME))
		{
			std::vector<UserInfoStruct*> users;
			UserInfoModule()->findDeskUsers(deskIndex, users);
			std::for_each(users.begin(), users.end(), [](UserInfoStruct* user)
			{
				user->bDeskStation = INVALID_DESKSTATION;
				user->bDeskNO = INVALID_DESKNO;
				user->bUserState = USER_LOOK_STATE;
			});
		}
	}


	void HNRoomLogic::H_R_M_UserAgree(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		CHECK_SOCKET_DATA(MSG_GR_R_UserAgree, objectSize, "MSG_GR_R_UserAgree size is error.");

		MSG_GR_R_UserAgree * pUserAgree = (MSG_GR_R_UserAgree*)object;

		const UserInfoStruct * pUserInfo = UserInfoModule()->findUser(pUserAgree->bDeskNO, pUserAgree->bDeskStation);
		if (nullptr != pUserInfo)
		{
			UserInfoStruct userInfo = *pUserInfo;
			userInfo.bUserState = USER_ARGEE;
			UserInfoModule()->updateUser(&userInfo);
		}

		dispatchGameMessage([&pUserAgree](IGameMessageDelegate* delegate) -> bool 
		{
			delegate->I_R_M_UserAgree(pUserAgree);
			return false;
		});
	}


	void HNRoomLogic::H_R_M_InstantUpdate(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		CHECK_SOCKET_DATA(MSG_GR_R_InstantUpdate, objectSize, "MSG_GR_R_InstantUpdate size is error.");

		MSG_GR_R_InstantUpdate * pInstantUpdate = (MSG_GR_R_InstantUpdate*)object;

		// ��������
		const UserInfoStruct * pUserInfo = UserInfoModule()->findUser(pInstantUpdate->dwUserID);
		if (nullptr != pUserInfo)
		{
			UserInfoStruct userInfo = *pUserInfo;
			userInfo.i64Money += pInstantUpdate->dwMoney;
			userInfo.dwPoint += pInstantUpdate->dwPoint;
			UserInfoModule()->updateUser(&userInfo);
		}

		// �����Լ�����
		if (pUserInfo->dwUserID == PlatformLogic()->loginResult.dwUserID)
		{
			RoomLogic()->loginResult.pUserInfoStruct = *pUserInfo;
			PlatformLogic()->loginResult.i64Money = pInstantUpdate->dwMoney;
		}
	}


	void HNRoomLogic::H_R_M_UserContest(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		CHECK_SOCKET_DATA(MSG_GR_ContestChange, objectSize, "MSG_GR_ContestChange size of error!");
		MSG_GR_ContestChange * contestChange = (MSG_GR_ContestChange*)object;

		const UserInfoStruct* pUserInfo = UserInfoModule()->findUser(contestChange->dwUserID);
		if (nullptr != pUserInfo)
		{
			UserInfoStruct userInfo = *pUserInfo;

			// ��������
			userInfo.iRankNum = contestChange->iRankNum;

			// �����л�ʣ�µ�����
			userInfo.iRemainPeople = contestChange->iRemainPeople;

			// ��������
			userInfo.i64ContestScore = contestChange->i64ContestScore;

			// ��������
			userInfo.iContestCount = contestChange->iContestCount + 1;

			UserInfoModule()->updateUser(&userInfo);
		}

		if (contestChange->dwUserID != PlatformLogic()->loginResult.dwUserID)		
		{
			return;
		}

		dispatchGameMessage([contestChange](IGameMessageDelegate* delegate) -> bool
		{
			delegate->I_R_M_UserContest(contestChange);
			return false;
		});
	}

	void HNRoomLogic::H_R_M_ContestNotic(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		CHECK_SOCKET_DATA(MSG_GR_I_ContestInfo, objectSize, "MSG_GR_ContestChange size of error!");
		MSG_GR_I_ContestInfo * contestInfo = (MSG_GR_I_ContestInfo*)object; //NET_ROOM_CONTEST_CHANGE_RESULT
			
		dispatchFrameMessage([&](IRoomMessageDelegate* delegate) -> bool 
		{
			delegate->I_R_M_ContestNotic(contestInfo);
			return false;
		});

		dispatchGameMessage([&](IGameMessageDelegate* delegate) -> bool 
		{
			delegate->I_R_M_ContestNotic(contestInfo);
			return false;
		});	
	}

	void HNRoomLogic::H_R_M_ContestOver(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		CHECK_SOCKET_DATA(MSG_GR_ContestAward, objectSize, "MSG_GR_ContestAward size of error!");
		MSG_GR_ContestAward* contestAward = (MSG_GR_ContestAward*)object;

		dispatchFrameMessage([contestAward](IRoomMessageDelegate* delegate) -> bool 
		{
			delegate->I_R_M_ContestOver(contestAward);
			return false;
		});	

		dispatchGameMessage([contestAward](IGameMessageDelegate* delegate) -> bool 
		{
			delegate->I_R_M_ContestOver(contestAward);
			return false;
		});	
	}

	void HNRoomLogic::H_R_M_ContestKick(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		dispatchGameMessage([](IGameMessageDelegate* delegate) -> bool 
		{
			delegate->I_R_M_ContestKick();
			return false;
		});	
	}


	void HNRoomLogic::H_R_M_ContestWaitOver(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		dispatchGameMessage([](IGameMessageDelegate* delegate) -> bool 
		{
			delegate->I_R_M_ContestWaitOver();
			return false;
		});	
	}

	void HNRoomLogic::H_R_M_ContestInit(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		CHECK_SOCKET_DATA(MSG_GR_ContestChange, objectSize, "MSG_GR_ContestChange size of error!");

		MSG_GR_ContestChange* contestChange = (MSG_GR_ContestChange*)object;

		const UserInfoStruct* pUserInfo = UserInfoModule()->findUser(contestChange->dwUserID);
		if (nullptr != pUserInfo)
		{
			UserInfoStruct userInfo = *pUserInfo;
			userInfo.iRemainPeople  = contestChange->iRemainPeople;		// �����л�ʣ�µ�����
			userInfo.iRankNum       = contestChange->iRankNum;			// ��������
			userInfo.iContestCount  = contestChange->iContestCount + 1;	// ��������
			UserInfoModule()->updateUser(&userInfo);
		}	
	}

	void HNRoomLogic::H_R_M_ContestPeople(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		CHECK_SOCKET_DATA(NET_ROOM_CONTEST_PEOPLE_RESULT, objectSize, "NET_ROOM_CONTEST_PEOPLE_RESULT size of error!");
		NET_ROOM_CONTEST_PEOPLE_RESULT* contestPeople = (NET_ROOM_CONTEST_PEOPLE_RESULT*)object;

		// �ַ���������
		dispatchFrameMessage([contestPeople](IRoomMessageDelegate* delegate) -> bool 
		{
			delegate->I_R_M_ContestPeople(contestPeople);
			return false;
		});
	}


	void HNRoomLogic::H_R_M_ContestRecord(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		CHECK_SOCKET_DATA(NET_ROOM_CONTEST_RECORD_RESULT, objectSize, "NET_ROOM_CONTEST_RECORD_RESULT size of error!");
		NET_ROOM_CONTEST_RECORD_RESULT* contestRecord = (NET_ROOM_CONTEST_RECORD_RESULT*)object;

		// �ַ���������
		dispatchFrameMessage([contestRecord](IRoomMessageDelegate* delegate) -> bool 
		{
			delegate->I_R_M_ContestRecord(contestRecord);
			return false;
		});
	}


	void HNRoomLogic::H_R_M_ContestAward(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		UINT count = objectSize / sizeof(NET_ROOM_CONTEST_AWARD_RESULT);
		if (count > 0)
		{
			NET_ROOM_CONTEST_AWARD_RESULT* contestRecord = (NET_ROOM_CONTEST_AWARD_RESULT*)object;

			std::vector<NET_ROOM_CONTEST_AWARD_RESULT*> results(count);
			while (count > 0)
			{
				NET_ROOM_CONTEST_AWARD_RESULT* tmp = contestRecord++;
				results[count - 1] = tmp;
				count--;
			}

			// �ַ���������
			dispatchFrameMessage([&results](IRoomMessageDelegate* delegate) -> bool 
			{
				delegate->I_R_M_ContestAwards(&results);
				return false;
			});
		}
	}

	
	void HNRoomLogic::H_R_M_Manage(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		//����
		if(messageHead->bHandleCode == 1)
		{
			BYTE deskNo = messageHead->bAssistantID;
			RoomLogic()->deskStation.bVirtualDesk[deskNo / 8] |= (1 << (deskNo % 8));

			dispatchFrameMessage([&messageHead](IRoomMessageDelegate* delegate) -> bool 
			{
				delegate->I_R_M_LockDesk(messageHead->bAssistantID);
				return true;
			});
		}

		// �������
		else
		{
			BYTE deskNo = messageHead->bAssistantID;
			RoomLogic()->deskStation.bVirtualDesk[deskNo / 8] &= (~(1 << (deskNo % 8)));

			dispatchFrameMessage([&messageHead](IRoomMessageDelegate* delegate) -> bool 
			{
				delegate->I_R_M_UnLockDesk(messageHead->bAssistantID);
				return true;
			});
		}
	}

	void HNRoomLogic::H_R_M_Connect(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		CCAssert(ASS_GR_CONNECT_SUCCESS == messageHead->bAssistantID, "assistId error.");

		CHECK_SOCKET_DATA(MSG_S_ConnectSuccess, objectSize, "size error.");

		int n = sizeof(MSG_S_ConnectSuccess);
		MSG_S_ConnectSuccess* pData = (MSG_S_ConnectSuccess*)object;

		_connected = true;
		HNSocketProtocolData::GameCheckCode = (UINT)(pData->i64CheckCode - getSecrectKey()) / 23;

		// �ַ��¼�
		dispatchFrameMessage([](IRoomMessageDelegate* delegate) -> bool
		{
			delegate->I_R_M_Connect(true);
			return false;
		});
	}	

	void HNRoomLogic::H_R_M_Login(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		char chs[20] = {0};
		std::string message;

		// ��ص�¼
		if(ASS_GP_LOGON_ALLO_PART == messageHead->bAssistantID)
		{
			message = GBKToUtf8("��ص�¼");

			dispatchFrameMessage([&messageHead, &message](IRoomMessageDelegate* delegate) -> bool
			{
				delegate->I_R_M_Login(false, messageHead->bHandleCode, message);
				return false;
			});
		}

		// �豸����
		else if(ASS_GP_LOGON_LOCK_VALID == messageHead->bAssistantID)
		{
			message = GBKToUtf8("�豸����");

			dispatchFrameMessage([&messageHead, &message](IRoomMessageDelegate* delegate) -> bool
			{
				delegate->I_R_M_Login(false, messageHead->bHandleCode, message);
				return false;
			});
		}

		// ��¼�ɹ�
		else if(ASS_GR_LOGON_SUCCESS == messageHead->bAssistantID)
		{
			message = GBKToUtf8("�����¼�ɹ�");

			CHECK_SOCKET_DATA(MSG_GR_R_LogonResult, objectSize, "size error.");			

			MSG_GR_R_LogonResult * pData = (MSG_GR_R_LogonResult*)object;

			loginResult = *pData;
			_logined    = (ERR_GP_LOGON_SUCCESS == messageHead->bHandleCode);

			dispatchFrameMessage([&messageHead, &message](IRoomMessageDelegate* delegate) -> bool
			{
				delegate->I_R_M_Login(true, messageHead->bHandleCode, message);
				return false;
			});
		}

		// ��¼����
		else if(ASS_GR_LOGON_ERROR == messageHead->bAssistantID)
		{
			switch (messageHead->bHandleCode)
			{
			case ERR_GR_USER_PASS_ERROR:
				message = GBKToUtf8("�û��������");
				break;
			case ERR_GR_CONTEST_TIMEOUT:
				message = GBKToUtf8("���ӳ�ʱ");
				break;
			case ERR_GR_IN_OTHER_ROOM:
				message = GBKToUtf8("������������");
				break;
			case ERR_GR_ACCOUNTS_IN_USE:
				message = GBKToUtf8("�ʺ�����ʹ��");
				break;
			case ERR_GR_STOP_LOGON:
				message = GBKToUtf8("��ͣ��½����");
				break;
			case ERR_GR_PEOPLE_FULL:
				message = GBKToUtf8("���������Ѿ���");
				break;
			default:
				message = GBKToUtf8("δ֪��¼����");
				break;
			}

			dispatchFrameMessage([&messageHead, &message](IRoomMessageDelegate* delegate) -> bool
			{
				delegate->I_R_M_Login(false, messageHead->bHandleCode, message);
				return false;
			});
		}

		// ��¼���
		else if(ASS_GR_SEND_FINISH == messageHead->bAssistantID)
		{
			dispatchFrameMessage([](IRoomMessageDelegate* delegate) -> bool
			{
				delegate->I_R_M_LoginFinish();
				return false;
			});	
		}
	}	

	void HNRoomLogic::H_R_M_UserList(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		if(ASS_GR_ONLINE_USER == messageHead->bAssistantID || ASS_GR_NETCUT_USER == messageHead->bAssistantID)
		{
			UINT userCount = objectSize / sizeof(UserInfoStruct);
			UserInfoStruct * pUserInfo = (UserInfoStruct *)object;
			while (userCount-- > 0)
			{
				UserInfoModule()->updateUser(pUserInfo++);
			}
		}
		else if(ASS_GR_DESK_STATION == messageHead->bAssistantID)
		{
			CHECK_SOCKET_DATA(MSG_GR_DeskStation, objectSize, "size error.");

			MSG_GR_DeskStation * pDeskStation = (MSG_GR_DeskStation *)object;
			deskStation = *pDeskStation;
		}
		else
		{

		}
	}

	void HNRoomLogic::H_R_M_UserAction(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		// �Ŷ�����
		if(ASS_GR_QUEUE_USER_SIT == messageHead->bAssistantID)
		{
			H_R_M_QueueUserSit(messageHead, object, objectSize);
		}

		// �û����뷿��
		else if(ASS_GR_USER_COME == messageHead->bAssistantID)
		{
			H_R_M_UserCome(messageHead, object, objectSize);
		}

		// �û��뿪����
		else if(ASS_GR_USER_LEFT == messageHead->bAssistantID)
		{
			H_R_M_UserLeft(messageHead, object, objectSize);
		}

		// �û�����
		else if(ASS_GR_USER_CUT == messageHead->bAssistantID)
		{
			H_R_M_UserCut(messageHead, object, objectSize);
		}

		// �û�վ�𣨰����Թ�վ��
		else if(ASS_GR_USER_UP == messageHead->bAssistantID || ASS_GR_WATCH_UP == messageHead->bAssistantID)
		{
			H_R_M_UserUp(messageHead, object, objectSize);
		}

		// ���´���
		else if(ASS_GR_SIT_ERROR == messageHead->bAssistantID)
		{
			H_R_M_SitError(messageHead, object, objectSize);
		}

		// �û�����
		else if(ASS_GR_USER_SIT == messageHead->bAssistantID || ASS_GR_WATCH_SIT == messageHead->bAssistantID)
		{
			H_R_M_UserSit(messageHead, object, objectSize);
		}
		//�û���������
		else if (ASS_GR_FAST_JOIN_IN == messageHead->bAssistantID)
		{
			H_R_M_UserFastSit(messageHead, object, objectSize);
		}
	}

	void HNRoomLogic::H_R_M_QueueUserSit(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		auto queueData = (int*)object;										
		auto deskNo = (BYTE)queueData[0];
		bool isFind = false;
		for (int i = 0; i < 3; i++)
		{
			if (PlatformLogic()->loginResult.dwUserID == queueData[3*i+1])
			{
				isFind = true;
			}
		}
		std::vector<QUEUE_USER_SIT_RESULT *> queueUsers;
		if (isFind)
		{
			for (int i = 0; i < 3; i++)
			{
				QUEUE_USER_SIT_RESULT * tmp = new QUEUE_USER_SIT_RESULT;
				tmp->dwUserID = queueData[3*i+1];
				tmp->bDeskStation = i;
				const UserInfoStruct* pUserInfo = UserInfoModule()->findUser(tmp->dwUserID);

				if (nullptr != pUserInfo)
				{
					UserInfoStruct userInfo = *pUserInfo;
					userInfo.bDeskNO        = deskNo;
					userInfo.bDeskStation   = tmp->bDeskStation;
					userInfo.bUserState     = USER_ARGEE;
					userInfo.iRankNum       = queueData[3 * i + 2];
					userInfo.iRemainPeople  = queueData[3 * i + 3];
					UserInfoModule()->updateUser(&userInfo);
					//UserInfoModule()->addUser(userInfo);
				}
						
				queueUsers.push_back(tmp);
				//CC_SAFE_DELETE(tmp);
			}
		}

		// �ַ���Ϸ��Ϣ
		dispatchGameMessage([&deskNo, &queueUsers](IGameMessageDelegate* delegate) -> bool
		{
			delegate->I_R_M_QueueUserSit(deskNo, queueUsers);
			return false;
		});

		// �ַ�������Ϣ
		dispatchFrameMessage([&deskNo, &queueUsers](IRoomMessageDelegate* delegate) -> bool
		{
			delegate->I_R_M_QueueUserSit(deskNo, queueUsers);
			return false;
		});

		for (auto sit : queueUsers)
		{
			CC_SAFE_DELETE(sit);
		}
		queueUsers.clear();

	}

	void HNRoomLogic::H_R_M_UserCome(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		CHECK_SOCKET_DATA(MSG_GR_R_UserCome, objectSize, "size error.");

		MSG_GR_R_UserCome* pUserCome = (MSG_GR_R_UserCome*)object;

		UserInfoModule()->updateUser(&pUserCome->pUserInfoStruct);
		
		// �ַ�������Ϣ
		dispatchFrameMessage([&pUserCome](IRoomMessageDelegate* delegate) -> bool
		{
			delegate->I_R_M_UserCome(&pUserCome->pUserInfoStruct);
			return false;
		});	
	}


	void HNRoomLogic::H_R_M_UserLeft(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		CHECK_SOCKET_DATA(MSG_GR_R_UserLeft, objectSize, "size error.");

		MSG_GR_R_UserLeft * pUserLeft = (MSG_GR_R_UserLeft*)object;

		const UserInfoStruct* userInfo = UserInfoModule()->findUser(pUserLeft->dwUserID);

		if (userInfo == nullptr)
		{
			return;
		}

		// �ַ�������Ϣ
		dispatchFrameMessage([&userInfo](IRoomMessageDelegate* delegate) -> bool
		{
			delegate->I_R_M_UserLeft(userInfo);
			return false;
		});
		UserInfoModule()->removeUser(pUserLeft->dwUserID);
	}

	void HNRoomLogic::H_R_M_UserCut(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		CHECK_SOCKET_DATA(MSG_GR_R_UserCut, objectSize, "size error.");

		MSG_GR_R_UserCut* pUserCut = (MSG_GR_R_UserCut*)object;

		const UserInfoStruct* pUserInfo = UserInfoModule()->findUser(pUserCut->dwUserID);
		if (nullptr != pUserInfo)
		{
			UserInfoStruct userInfo = *pUserInfo;
			//��������
			userInfo.bUserState = USER_CUT_GAME;
			UserInfoModule()->updateUser(&userInfo);
		}

		// �ַ���Ϸ��Ϣ
		dispatchGameMessage([&pUserCut, &pUserInfo](IGameMessageDelegate* delegate) -> bool
		{
			delegate->I_R_M_UserCut(pUserCut->dwUserID, pUserCut->bDeskNO, pUserCut->bDeskStation);
			return false;
		});

		// �ַ�������Ϣ
		dispatchFrameMessage([&pUserCut](IRoomMessageDelegate* delegate) -> bool
		{
			delegate->I_R_M_UserCut(pUserCut->dwUserID, pUserCut->bDeskNO, pUserCut->bDeskStation);
			return false;
		});
	}


	void HNRoomLogic::H_R_M_UserUp(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		if (ERR_GR_SIT_SUCCESS == messageHead->bHandleCode)
		{
			// ����У��
			CHECK_SOCKET_DATA(MSG_GR_R_UserUp, objectSize, "size error.");

			MSG_GR_R_UserUp* pUserUp = (MSG_GR_R_UserUp*)object;

			// ��������
			if(pUserUp->bDeskIndex != INVALID_DESKNO)
			{
				bool isLocked = (pUserUp->bLock != 0);
				BYTE deskNo = pUserUp->bDeskIndex;
				if(isLocked)
				{
					// ����							
					RoomLogic()->deskStation.bDeskLock[deskNo / 8] |= (1 << (deskNo % 8));
				}
				else
				{
					// ����
					RoomLogic()->deskStation.bDeskLock[deskNo / 8] &= (~(1 << (deskNo % 8)));
				}
			}

			// �����Լ���Ϣ
			if (pUserUp->dwUserID == loginResult.pUserInfoStruct.dwUserID)
			{
				loginResult.pUserInfoStruct.bDeskNO = pUserUp->bDeskIndex;
				loginResult.pUserInfoStruct.bDeskStation = pUserUp->bDeskStation;
				loginResult.pUserInfoStruct.bUserState = pUserUp->bUserState;
			}

			const UserInfoStruct* pUserInfo = UserInfoModule()->findUser(pUserUp->dwUserID);
			// �����û�����
			if (nullptr != pUserInfo)
			{
				UserInfoStruct userInfo = *pUserInfo;
				userInfo.bDeskNO        = INVALID_DESKNO;
				userInfo.bDeskStation   = INVALID_DESKSTATION;
				userInfo.bUserState     = USER_LOOK_STATE;
				UserInfoModule()->updateUser(&userInfo);
			}
			// �ַ���Ϸ��Ϣ
			dispatchGameMessage([&pUserUp, &pUserInfo](IGameMessageDelegate* delegate) -> bool
			{
				delegate->I_R_M_UserUp(pUserUp, pUserInfo);
				return false;
			});

			// �ַ�������Ϣ
			dispatchFrameMessage([&pUserUp, &pUserInfo](IRoomMessageDelegate* delegate) -> bool
			{
				delegate->I_R_M_UserUp(pUserUp, pUserInfo);
				return false;
			});
		}
		else
		{
			std::string message = getSitErrorReason(messageHead->bHandleCode);
			// �ַ���Ϸ��Ϣ
			dispatchGameMessage([&message](IGameMessageDelegate* delegate) -> bool
			{
				delegate->I_R_M_SitError(message);
				return false;
			});

			// �ַ�������Ϣ
			dispatchFrameMessage([&message](IRoomMessageDelegate* delegate) -> bool
			{
				delegate->I_R_M_SitError(message);
				return false;
			});
		}
	}

	void HNRoomLogic::H_R_M_SitError(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		std::string message = getSitErrorReason(messageHead->bHandleCode);
		// �ַ���Ϸ��Ϣ
		dispatchGameMessage([&message](IGameMessageDelegate* delegate) -> bool
		{
			delegate->I_R_M_SitError(message);
			return false;
		});	

		// �ַ�������Ϣ
		dispatchFrameMessage([&message](IRoomMessageDelegate* delegate) -> bool
		{
			delegate->I_R_M_SitError(message);
			return false;
		});
	}


	void HNRoomLogic::H_R_M_UserSit(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		if (ERR_GR_SIT_SUCCESS == messageHead->bHandleCode)
		{
			// ����У��
			CHECK_SOCKET_DATA(MSG_GR_R_UserSit, objectSize, "MSG_GR_R_UserSit size error.");

			MSG_GR_R_UserSit * pUserSit = (MSG_GR_R_UserSit*)object;

			// ��������
			if (pUserSit->bDeskIndex != INVALID_DESKNO)
			{
				bool isLocked = (pUserSit->bLock != 0);
				BYTE deskNo   = pUserSit->bDeskIndex;
				if (isLocked)
				{
					// ����							
					RoomLogic()->deskStation.bDeskLock[deskNo / 8] |= (1 << (deskNo % 8));
				}
				else
				{
					// ����
					RoomLogic()->deskStation.bDeskLock[deskNo / 8] &= (~(1 << (deskNo % 8)));
				}
			}

			// �����Լ���Ϣ
			if (pUserSit->dwUserID == loginResult.pUserInfoStruct.dwUserID)
			{
				loginResult.pUserInfoStruct.bDeskNO      = pUserSit->bDeskIndex;
				loginResult.pUserInfoStruct.bDeskStation = pUserSit->bDeskStation;
				loginResult.pUserInfoStruct.bUserState   = pUserSit->bUserState;
			}

			const UserInfoStruct* pUserInfo = UserInfoModule()->findUser(pUserSit->dwUserID);
			// �����û�����
			if (nullptr != pUserInfo)
			{
				UserInfoStruct userInfo = *pUserInfo;
				userInfo.bDeskNO      = pUserSit->bDeskIndex;
				userInfo.bDeskStation = pUserSit->bDeskStation;
				userInfo.bUserState   = pUserSit->bUserState;
				UserInfoModule()->updateUser(&userInfo);
			}

			// �ַ���Ϸ��Ϣ
			dispatchGameMessage([&pUserSit, &pUserInfo](IGameMessageDelegate* delegate) -> bool
			{
				delegate->I_R_M_UserSit(pUserSit, pUserInfo);
				return false;
			});

			// �ַ�������Ϣ
			dispatchFrameMessage([&pUserSit, &pUserInfo](IRoomMessageDelegate* delegate) -> bool
			{
				delegate->I_R_M_UserSit(pUserSit, pUserInfo);
				return false;
			});
		}
	}

	// �û��������£���λƽ̨������
	void HNRoomLogic::H_R_M_UserFastSit(const NetMessageHead* messageHead, void* object, INT objectSize)
	{
		if (ERR_GR_SIT_SUCCESS == messageHead->bHandleCode)
		{
			// ����У��
			CHECK_SOCKET_DATA(MSG_GR_R_UserSit, objectSize, "MSG_GR_R_UserSit size error.");

			MSG_GR_R_UserSit * pUserSit = (MSG_GR_R_UserSit*)object;

			// ��������
			if (pUserSit->bDeskIndex != INVALID_DESKNO)
			{
				bool isLocked = (pUserSit->bLock != 0);
				BYTE deskNo = pUserSit->bDeskIndex;
				if (isLocked)
				{
					// ����							
					RoomLogic()->deskStation.bDeskLock[deskNo / 8] |= (1 << (deskNo % 8));
				}
				else
				{
					// ����
					RoomLogic()->deskStation.bDeskLock[deskNo / 8] &= (~(1 << (deskNo % 8)));
				}
			}

			// �����Լ���Ϣ
			if (pUserSit->dwUserID == loginResult.pUserInfoStruct.dwUserID)
			{
				loginResult.pUserInfoStruct.bDeskNO = pUserSit->bDeskIndex;
				loginResult.pUserInfoStruct.bDeskStation = pUserSit->bDeskStation;
				loginResult.pUserInfoStruct.bUserState = pUserSit->bUserState;
			}

			const UserInfoStruct* pUserInfo = UserInfoModule()->findUser(pUserSit->dwUserID);
			// �����û�����
			if (nullptr != pUserInfo)
			{
				UserInfoStruct userInfo = *pUserInfo;
				userInfo.bDeskNO = pUserSit->bDeskIndex;
				userInfo.bDeskStation = pUserSit->bDeskStation;
				userInfo.bUserState = pUserSit->bUserState;
				UserInfoModule()->updateUser(&userInfo);
			}

			// �ַ���Ϸ��Ϣ
			dispatchGameMessage([&pUserSit, &pUserInfo](IGameMessageDelegate* delegate) -> bool
			{
				delegate->I_R_M_UserSit(pUserSit, pUserInfo);
				return false;
			});

			// �ַ�������Ϣ
			dispatchFrameMessage([&pUserSit, &pUserInfo](IRoomMessageDelegate* delegate) -> bool
			{
				delegate->I_R_M_UserSit(pUserSit, pUserInfo);
				return false;
			});
		}
	}

	std::string HNRoomLogic::getSitErrorReason(int handleCode)
	{
		std::string message;
		switch (handleCode)
		{
		case ERR_GR_BEGIN_GAME:
			message = "���´�λ��ʧ��,��Ϸ�Ѿ���ʼ��!";
			break;
		case ERR_GR_ALREAD_USER:
			message = "���´�λ��ʧ��,�´ζ�����һ���!";
			break;
		case ERR_GR_PASS_ERROR:
			message = "��Ϸ���������,������Ϸ������������������Я������!";
			break;
		case ERR_GR_IP_SAME:
			message = "ͬ����Ҳ���������ͬ IP ��ַ�����һ�������Ϸ!";
			break;
		case ERR_GR_IP_SAME_3:
			message = "ͬ����Ҳ������� IP ��ַǰ��λ��ͬ�����һ�������Ϸ!";
			break;
		case ERR_GR_IP_SAME_4:
			message = "ͬ����Ҳ�������IP ��ַǰ��λ��ͬ�����һ�������Ϸ!";
			break;
		case ERR_GR_CUT_HIGH:
			message = "ͬ�������Ϊ����������̫��,��Ը�������Ϸ!";
			break;
		case ERR_GR_POINT_LOW:
			message = "����������õĽ����������������ϱ�����������!";
			break;
		case ERR_GR_POINT_HIGH:	
			message = "����������õĽ����������������ϱ�����������!";
			break;
		case ERR_GR_NO_FRIEND:
			message = "������������ӭ�����!";
			break;
		case ERR_GR_POINT_LIMIT:
			message = StringUtils::format("����Ϸ����Ҫ���� %u ����Ϸ����, ���Ļ��ֲ���, ������Ϸ!", loginResult.uLessPoint);
			break;
		case ERR_GR_CAN_NOT_LEFT:
			message = "��������Ϸ��...";
			break;
		case ERR_GR_NOT_FIX_STATION:
			message = "�����ܼ������Ϸ����Ϸ!";
			break;
		case ERR_GR_MATCH_FINISH:
			message = "���ı����Ѿ�������,���ܼ����μӱ���!";
			break;
		case ERR_GR_MATCH_WAIT://�������Ŷ���
			message = "�����Ŷ���";
			break;
		case ERR_GR_UNENABLE_WATCH:
			message = "�������Թ���Ϸ!";
			break;
		case ERR_GR_FAST_SIT:
			message = "��������������";
			break;			
		default:
			message = "δ֪����";
			break;
		}

		return GBKToUtf8(message.c_str());
	}

	bool HNRoomLogic::dispatchFrameMessage(const RoomFrameMessageFun& func)
	{
		auto iterA = _addRoomNotifyQueue->begin();
		while(iterA != _addRoomNotifyQueue->end())
		{
			auto next = iterA;
			next++;
			_roomNotifyQueue->addObserver(iterA->second);
			_addRoomNotifyQueue->removeObserver(iterA->second);
			iterA = next;
		}

		auto iterR = _removeRoomNotifyQueue->begin();
		while(iterR != _removeRoomNotifyQueue->end())
		{
			auto next = iterR;
			next++;
			_roomNotifyQueue->removeObserver(iterR->second);
			_removeRoomNotifyQueue->removeObserver(iterR->second);
			iterR = next;
		}

		for (auto iter = _roomNotifyQueue->begin(); iter != _roomNotifyQueue->end(); ++iter)
		{
			bool bRemoved = false;
			for(auto iterR = _removeRoomNotifyQueue->begin(); iterR != _removeRoomNotifyQueue->end(); iterR++)
			{
				if(iterR->second == iter->second)
				{
					bRemoved = true;
					break;
				}
			}
			if(!bRemoved)
			{
				func(iter->second);
			}				
		}
		return true;
	}

	bool HNRoomLogic::dispatchGameMessage(const GameMessageFun& func)
	{
		auto iterA = _addGameNotifyQueue->begin();
		while(iterA != _addGameNotifyQueue->end())
		{
			auto next = iterA;
			next++;
			_gameNotifyQueue->addObserver(iterA->second);
			_addGameNotifyQueue->removeObserver(iterA->second);
			iterA = next;
		}
		
		auto iterR = _removeGameNotifyQueue->begin();
		while(iterR != _removeGameNotifyQueue->end())
		{
			auto next = iterR;
			next++;
			_gameNotifyQueue->removeObserver(iterR->second);
			_removeGameNotifyQueue->removeObserver(iterR->second);
			iterR = next;
		}		

		for (auto iter = _gameNotifyQueue->begin(); iter != _gameNotifyQueue->end(); ++iter)
		{
			bool bRemoved = false;
			for(auto iterR = _removeGameNotifyQueue->begin(); iterR != _removeGameNotifyQueue->end(); iterR++)
			{
				if(iterR->second == iter->second)
				{
					bRemoved = true;
					break;
				}
			}
			if(!bRemoved)
			{
				func(iter->second);
			}				
		}
		return true;
	}

}
