/*********************************************************/
//	���飺���¼ ��Ϸ��������
//  �����¼ʹ�÷���:
// 1. ��AppDelegate.cpp ����ͷ�ļ� #include "HNReconnectionLogic.h"��
// 2. ��AppDelegate.cpp �޸Ĵ���

// �޸�ǰ
// auto scene = GameInitial::createScene();
// director->runWithScene(scene);

// �޸ĺ�
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//	 HNReconnectionLogic::createScene();
//#else
//	 Scene * scene = GameInitial::createScene();
//	 director->runWithScene(scene);
//#endif

// 3. �޸�HNReconnectionLogic.cpp ��init����������Ϣ
// 4. �������򣬽��Զ����ҿ����˺ţ����Ե�½

/*********************************************************/
// ����Ϸ��������ʹ�÷���
// ����������> HNReconnectionLogic::createReconnectNode(...)
// @deskNo: RoomLogic()->loginResult.pUserInfoStruct.bDeskNO 
// @successCallback: std::bind(&GameTableUI::createLogic, this, std::placeholders::_1, std::placeholders::_2);
// void GameTableUI::createLogic(BYTE deskNo, bool bAutoCreate) {
//		if (_tableLogic == nullptr) {
//			_tableLogic = new GameTableLogic(this, deskNo, bAutoCreate);
//		}
//		_tableLogic->sendGameInfo();
//}


#ifndef __HNReconnectionLogic_H__
#define __HNReconnectionLogic_H__

#include "cocos2d.h"
#include "HNNetExport.h"
#include "ui/UIScrollView.h"
#include "../../../common/LibHNNet/HNRoom/HNRoomMessageDelegate.h"

USING_NS_CC;
using namespace std;
using namespace ui;

// ��������
class HNReconnectionLogic : public Layer, public IPlatformMessageDelegate, public IRoomMessageDelegate
{
public:
	HNReconnectionLogic();
	~HNReconnectionLogic();
	static void createScene();

	// ������Ϸ�������Ľӿ�
	static HNReconnectionLogic* createReconnectNode(Node* uiParent, int gameID, int deskNo, int deskStation, std::function<void(int, bool)> successCallback);
	static HNReconnectionLogic* createReconnectNode(Node* uiParent);
	bool init(Node* uiParent, int gameID, int deskNo, int deskStation, std::function<void(int, bool)> successCallback);
	bool init(Node* uiParent);
	void startReconnect();
	void stopReconnect();
	static HNReconnectionLogic* getInstance() { return reconnectNode; };

private:
	std::function<void(int, bool)> createLogicCallBack;
	int m_currConnTimes;
	int m_connTimes;
	Node * uiParent;
	static HNReconnectionLogic* reconnectNode;

public:
	// ����ƽ̨������
	virtual void I_P_M_Connect(bool success) override;
	// ��½ƽ̨������
	virtual void I_P_M_Login(bool success, UINT dwErrorCode) override;
	// ��ȡ��̨���õ���Ϸ�б�
	virtual void I_P_M_GameList() override;
	// ��ȡ��̨���õķ����б�
	virtual void I_P_M_RoomList() override;
	// ������Ϸ������
	virtual void I_R_M_Connect(bool success) override;
	// ��½��Ϸ������
	virtual void I_R_M_Login(bool success, UINT handleCode, const std::string& message) override;
	// �������
	virtual void I_R_M_UserSit(MSG_GR_R_UserSit * userSit, const UserInfoStruct* user) override;
	// ����ʧ��
	virtual void I_R_M_SitError(const std::string& message) override;

private:

	void tryLogin(int accIndex);			// ���Ե�½ @accIndex �˻������±�

	void trySit(int deskNo, int deskPos);	// �������� @deskNo ���Ӻ� @ deskPos ��λ��

	void returnGameMenu();

	ui::ScrollView* m_debugView;
	vector<string> m_userAcc;   // �˺�����
	vector<string> m_userPass;  // ��������
	int m_currLoginIndex;		// ��ǰ��½���˺�λ��
	int m_gameId;				// ��Ϸid
	int m_kindId;				// ��ϷkindId
	int m_roomSelect;			// ѡ�����Ϸ����
	int m_sitDeskNo;			// ���µ����Ӻ�
	string m_deskPassword;      // ��������
	int m_firstTestDeskStation; // ���ȳ��Ե�λ��
	int m_currTestDeskStation;  // ��ǰ�������µ�λ��
	int m_maxDeskPlayer;		// ��Ϸ�����λ��
	int m_maxDeskNumbers;       // ���������
	bool m_useReconnect;		// ������Ϸ����
	string m_serverIp;
	int m_serverPort;
	ComRoomInfo* m_selectRoom;

	bool reconnectFromGame;		// ����Ϸ�������� �����ƽ̨����������Ϊfalse
};

#endif  // __HNReconnectionLogic_H__
