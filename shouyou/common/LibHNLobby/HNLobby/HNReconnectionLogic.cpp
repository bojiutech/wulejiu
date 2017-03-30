#include "HNReconnectionLogic.h"
#include "GamePrompt.h"
#include "GameMenu/GameMenu.h"
#include "GamePlatform.h"
#include "json/rapidjson.h"
#include "json/document.h"

HNReconnectionLogic * HNReconnectionLogic::reconnectNode = nullptr;

HNReconnectionLogic::HNReconnectionLogic()
{
	m_debugView = nullptr;
	m_useReconnect = false;
	m_currLoginIndex = -1;
	m_maxDeskNumbers = 0;
	m_maxDeskPlayer = 0;
	m_currTestDeskStation = 0;
	m_firstTestDeskStation = 0;
	m_connTimes = 10;
	m_currConnTimes = 0;
	m_selectRoom = nullptr;
	m_gameId = -1;
	m_sitDeskNo = -1;
	m_kindId = -1;
	reconnectFromGame = false;
}

HNReconnectionLogic::~HNReconnectionLogic()
{
	if (m_selectRoom != nullptr) {
		delete m_selectRoom;
		m_selectRoom = nullptr;
	}
	if (reconnectNode != nullptr)
	{
		reconnectNode->stopReconnect();
		reconnectNode->removeFromParent();
		reconnectNode = nullptr;
	}
}

void HNReconnectionLogic::createScene()
{
	auto scene = Scene::create();
	auto layer = HNReconnectionLogic::create();
	scene->addChild(layer);
	Director::getInstance()->replaceScene(scene);
}

HNReconnectionLogic* HNReconnectionLogic::createReconnectNode(Node* uiParent, int gameID, int deskNo, int deskStation, std::function<void(int, bool)> successCallback)
{
	if (reconnectNode == nullptr)
	{
		reconnectNode = new HNReconnectionLogic();
		if (reconnectNode != nullptr && reconnectNode->init(uiParent, gameID, deskNo, deskStation, successCallback))
		{
			reconnectNode->autorelease();
		}
		else 
		{
			delete reconnectNode;
			reconnectNode = nullptr;
		}
	}
	else
	{
		reconnectNode->init(uiParent, gameID, deskNo, deskStation, successCallback);
	}
	return reconnectNode;
}

HNReconnectionLogic* HNReconnectionLogic::createReconnectNode(Node* uiParent)
{
	if (reconnectNode == nullptr) 
	{
		reconnectNode = new HNReconnectionLogic();
		if (reconnectNode != nullptr && reconnectNode->init(uiParent)) 
		{
			reconnectNode->autorelease();
		}
		else 
		{
			delete reconnectNode;
			reconnectNode = nullptr;
		}
	}
	else
	{
		reconnectNode->init(uiParent);
	}
	return reconnectNode;
}

bool HNReconnectionLogic::init(Node* uiParent, int gameID, int deskNo, int deskStation, std::function<void(int, bool)> successCallback)
{
	if (!Node::init())
		return false;

	m_currLoginIndex = -1;
	m_useReconnect = true;
	m_userAcc.clear();
	m_userAcc.push_back(PlatformLogic()->loginResult.szName);
	m_userPass.clear();
	m_userPass.push_back(PlatformLogic()->loginResult.szMD5Pass);
	m_currConnTimes = 0;
	m_gameId = gameID;
	m_sitDeskNo = deskNo;
	m_currTestDeskStation = deskStation;	
	if (uiParent != nullptr && this->getParent() == nullptr)
	{
		uiParent->addChild(this, INT_MAX);
	}
	createLogicCallBack = successCallback;

	reconnectFromGame = true; //����Ϸ������

	startReconnect();

	return true;
}

bool HNReconnectionLogic::init(Node* uiParent)
{
	if (!Node::init()) 
	{
		return false;
	}

	m_currLoginIndex = -1;
	m_useReconnect = true;
	m_userAcc.assign(1, PlatformLogic()->loginResult.szName);
	m_userPass.assign(1, PlatformLogic()->loginResult.szMD5Pass);
	m_currConnTimes = 0;
	m_gameId = -1;
	m_sitDeskNo = -1;
	m_currTestDeskStation = -1;
	if (uiParent != nullptr && this->getParent() == nullptr)
	{
		uiParent->addChild(this, INT_MAX);
	}
	createLogicCallBack = nullptr;

	reconnectFromGame = false; // ��ƽ̨����

	startReconnect();

	return true;
}

void HNReconnectionLogic::startReconnect()
{
	log("#### data  startReconnect");

	auto loading = LoadingLayer::createLoading(this, GBKToUtf8("��Ϸ�ѶϿ�,������������..."), 40, "platform/loading.png");
	loading->quicklyShade(150);

	// �������ķ������,������ʹ��,�����һ�ζ��ߴ��߼����ȡ
	auto selectRoom = RoomLogic()->getSelectedRoom();

	if (m_selectRoom != nullptr || selectRoom != nullptr) {

		if (m_selectRoom == nullptr) {
			m_selectRoom = new ComRoomInfo;
			memcpy(m_selectRoom, selectRoom, sizeof(ComRoomInfo));
		}

		m_gameId = m_selectRoom->uNameID;
		m_serverIp = m_selectRoom->szServiceIP;
		m_serverPort = m_selectRoom->uServicePort;
		m_maxDeskNumbers = m_selectRoom->uDeskCount;
		m_maxDeskPlayer = m_selectRoom->uDeskPeople;

	    ComRoomInfo roomInfo;
		memcpy(&roomInfo, m_selectRoom, sizeof(ComRoomInfo));

		RoomLogic()->setSelectedRoom(&roomInfo);
	}

	PlatformLogic()->close();
	PlatformLogic()->addObserver(this);
	PlatformLogic()->connect();

	//// 1. ��ƽ̨�����ӣ���ֱ��������Ϸ���䣬����������ƽ̨�� 
	//if (PlatformLogic()->isConnect())
	//{
	//	RoomLogic()->addRoomObserver(this);
	//	RoomLogic()->connect(m_serverIp.c_str(), m_serverPort);
	//}
	//else {
	//	PlatformLogic()->addObserver(this);
	//	PlatformLogic()->connect();
	//}
}

void HNReconnectionLogic::stopReconnect()
{
	log("#### data  stopReconnect");

	LoadingLayer::removeLoading(this);
	RoomLogic()->removeRoomObserver(this);
	PlatformLogic()->removeObserver(this);
}

void HNReconnectionLogic::I_P_M_Connect(bool success)
{
	log("#### data  I_P_M_Connect");

	if (success) 
	{
		// ���Ե�½��һ���˺�
		tryLogin(++m_currLoginIndex);
	}
	else 
	{
		if (m_currConnTimes < m_connTimes) 
		{
			++m_currConnTimes;
			PlatformLogic()->connect();
		}
		else 
		{
			stopReconnect();
			auto prompt = GamePromptLayer::create();
			prompt->showPrompt(GBKToUtf8("����ʧ��,�����Ѿ��Ͽ�����!"));
			prompt->setCallBack([](){
				GameMenu::createMenu();
			});
		}
	}
}

void HNReconnectionLogic::I_P_M_Login(bool success, UINT dwErrorCode)
{
	log("#### data  I_P_M_GameList.");

	if (success) 
	{ 
		log("#### data  I_P_M_GameList. success");

		// �˺ŵ�½ƽ̨�ɹ�
		if (!reconnectFromGame) {
			PlatformLogic()->sendData(MDM_GP_LIST, ASS_GP_LIST_KIND);
		}
		else{
			RoomLogic()->addRoomObserver(this);
			RoomLogic()->connect(m_serverIp.c_str(), m_serverPort);
		}
	}
	else 
	{
		if (dwErrorCode == ERR_GP_USER_LOGON) 
		{
			//// �ѵ�½�����ӷ���
			//if (m_useReconnect) {
			//	PlatformLogic()->sendData(MDM_GP_LIST, ASS_GP_LIST_KIND);
			//}
			log("#### data  I_P_M_GameList. ERR_GP_USER_LOGON");

			if (!reconnectFromGame) {
				PlatformLogic()->sendData(MDM_GP_LIST, ASS_GP_LIST_KIND);
			}
			else{
				RoomLogic()->addRoomObserver(this);
				RoomLogic()->connect(m_serverIp.c_str(), m_serverPort);
			}
		}
		/*if (m_useReconnect)
		{
		tryLogin(0);
		}
		else
		{
		tryLogin(++m_currLoginIndex);
		}*/
	}
}

void HNReconnectionLogic::I_P_M_GameList()
{
	log("#### data  I_P_M_GameList.");

	// ��Ϸ������
	if (reconnectFromGame)
	{
		auto gameInfo = GamesInfoModule()->getGameNameByGameID(m_gameId);
		if (gameInfo == nullptr)
		{
			if (m_useReconnect)
			{
				returnGameMenu();
			}
		}
		else
		{
			m_kindId = gameInfo->uKindID;
			GameCreator()->setGameKindId(m_gameId, m_kindId);
			PlatformLogic()->getRoomList(m_kindId, m_gameId);
		}
	}

	// ����������
	else
	{
		reconnectNode->stopReconnect();
		reconnectNode->removeFromParent();
		reconnectNode = nullptr;
		//removeReconnectNode();
	}
	
}

void HNReconnectionLogic::I_P_M_RoomList()
{
	log("#### data  I_P_M_RoomList.");

	PlatformLogic()->removeObserver(this);

	if (m_selectRoom == nullptr)
	{
		auto roomCount = RoomInfoModule()->getRoomCount();
		int findRoom = 0;
		if (roomCount > 0)
		{
			ComRoomInfo* room = nullptr;
			ComRoomInfo* preRoom = nullptr;
			for (int i = 0; i < 100; i++)
			{
				room = RoomInfoModule()->getRoom(i);
				if (room != nullptr) {
					if (room->uNameID == m_gameId && room->uKindID == m_kindId) {
						m_selectRoom = new ComRoomInfo;
						preRoom = room;
						memcpy(m_selectRoom, room, sizeof(ComRoomInfo));
						if (findRoom++ >= m_roomSelect) {
							break;
						}
					}
				}
				else
					break;
			}
			if (m_selectRoom != nullptr) 
			{
				RoomLogic()->setSelectedRoom(preRoom);
			}
			else 
			{
				
			}
		}
		else 
		{
			
		}
	}
	if (m_selectRoom != nullptr) 
	{
		m_maxDeskNumbers = m_selectRoom->uDeskCount;
		m_maxDeskPlayer = m_selectRoom->uDeskPeople;
		string setGameInfo = StringUtils::format(">> ׼��������Ϸ������... \n<��ϷIP��ַ: %s> \n<��Ϸ�˿ں�: %d> \n<GAME_ID: %d> \n<KIND_ID: %d> \n",
			m_selectRoom->szServiceIP, m_selectRoom->uServicePort, m_gameId, m_kindId);
		
		GameCreator()->setGameKindId(m_gameId, m_kindId);
		RoomLogic()->removeRoomObserver(this);
		RoomLogic()->addRoomObserver(this);
		
		m_serverIp = m_selectRoom->szServiceIP;
		m_serverPort = m_selectRoom->uServicePort;
		static ComRoomInfo roomInfo;
		memcpy(&roomInfo, m_selectRoom, sizeof(ComRoomInfo));
		RoomLogic()->setSelectedRoom(&roomInfo);
		m_serverIp = m_selectRoom->szServiceIP;
		m_serverPort = m_selectRoom->uServicePort;
		RoomLogic()->connect(m_serverIp.c_str(), m_serverPort);
	}
	else
	{
		returnGameMenu();
	}
}

void HNReconnectionLogic::I_R_M_Connect(bool success)  // ����socket���ӳɹ�, ��½��Ӧ����
{
	log("#### data  I_R_M_Connect.");
	if (success) 
	{
		if (reconnectFromGame)
		{
			RoomLogic()->login(m_gameId);
		}		
	}
	else 
	{
		returnGameMenu();
	}
}

void HNReconnectionLogic::I_R_M_Login(bool success, UINT handleCode, const std::string& message)
{
	log("#### data  I_R_M_Login.");
	if (success)
	{  
		// �����½�ɹ�����������
		trySit(m_sitDeskNo, m_currTestDeskStation);
	}
	else 
	{
		// ����9 �˺��ѵ�½,��ʱ����˻��ߵ����������,�Ⱥ�һ��ʱ��,������
		if (m_useReconnect && handleCode == 9) 
		{
			RoomLogic()->close();
			RoomLogic()->connect(m_serverIp.c_str(), m_serverPort);
		}
		else
		{
			returnGameMenu();
		}
	}
}

void HNReconnectionLogic::I_R_M_UserSit(MSG_GR_R_UserSit * userSit, const UserInfoStruct* user)
{
	if (PlatformLogic()->loginResult.dwUserID == userSit->dwUserID)
	{
		RoomLogic()->removeRoomObserver(this);
		if (!m_useReconnect) 
		{
			GameCreator()->startGameClient(m_gameId, userSit->bDeskIndex, true);  // ����������Ϣ,������Ϸ������
		}
		else
		{
			if (createLogicCallBack != nullptr) 
			{
				createLogicCallBack(userSit->bDeskIndex, true);
			}
			stopReconnect();
		}
	}
}

void HNReconnectionLogic::I_R_M_SitError(const std::string& message)
{
	if (!m_useReconnect)
	{
		if (m_currTestDeskStation == m_firstTestDeskStation) 
		{
			m_currTestDeskStation = m_firstTestDeskStation = -1;
		}
		m_currTestDeskStation++;
		trySit(m_sitDeskNo, m_currTestDeskStation);
	}
}

void HNReconnectionLogic::tryLogin(int accIndex) // ��½
{
	if (accIndex < m_userAcc.size() && accIndex < m_userPass.size()) {
		auto username = m_userAcc.at(accIndex);
		auto password = m_userPass.at(accIndex);
		PlatformLogic()->login(username, password, m_gameId);
	}
	else {  // ���û�и�����˻���.,���˳�
		if (m_useReconnect) {
			PlatformLogic()->removeObserver(this);
		}
		else {
			stopReconnect();
		}

		return;
	}
}

void HNReconnectionLogic::trySit(int deskNo, int deskPos)
{
	if (deskPos < 0 || deskPos >= m_maxDeskPlayer || deskNo < 0 || deskNo >= m_maxDeskNumbers) {		
		returnGameMenu();
		return;
	}

	MSG_GR_S_UserSit data;
	memset(&data, 0, sizeof(data));
	data.bDeskIndex = deskNo;
	data.bDeskStation = deskPos;
	strcpy(data.szPassword, m_deskPassword.c_str());
	RoomLogic()->sendData(MDM_GR_USER_ACTION, ASS_GR_USER_SIT, &data, sizeof(data));
}

void HNReconnectionLogic::returnGameMenu()
{
	PlatformLogic()->removeObserver(this);
	RoomLogic()->removeRoomObserver(this);
	PlatformLogic()->close();
	RoomLogic()->close();

	auto prompt = GamePromptLayer::create();
	prompt->showPrompt(GBKToUtf8("��Ϸ����������ʧ��,��������!"));
	prompt->setCallBack([](){
		GameMenu::createMenu();
	});
}