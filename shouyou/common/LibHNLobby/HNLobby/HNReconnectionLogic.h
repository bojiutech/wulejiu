/*********************************************************/
//	类简介：免登录 游戏断线重连
//  ①免登录使用方法:
// 1. 在AppDelegate.cpp 引入头文件 #include "HNReconnectionLogic.h"，
// 2. 在AppDelegate.cpp 修改代码

// 修改前
// auto scene = GameInitial::createScene();
// director->runWithScene(scene);

// 修改后
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//	 HNReconnectionLogic::createScene();
//#else
//	 Scene * scene = GameInitial::createScene();
//	 director->runWithScene(scene);
//#endif

// 3. 修改HNReconnectionLogic.cpp 内init函数配置信息
// 4. 启动程序，将自动查找可用账号，尝试登陆

/*********************************************************/
// ②游戏断线重连使用方法
// 创建方法名> HNReconnectionLogic::createReconnectNode(...)
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

// 断线重连
class HNReconnectionLogic : public Layer, public IPlatformMessageDelegate, public IRoomMessageDelegate
{
public:
	HNReconnectionLogic();
	~HNReconnectionLogic();
	static void createScene();

	// 用于游戏中重连的接口
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
	// 连接平台服务器
	virtual void I_P_M_Connect(bool success) override;
	// 登陆平台服务器
	virtual void I_P_M_Login(bool success, UINT dwErrorCode) override;
	// 获取后台配置的游戏列表
	virtual void I_P_M_GameList() override;
	// 获取后台配置的房间列表
	virtual void I_P_M_RoomList() override;
	// 连接游戏服务器
	virtual void I_R_M_Connect(bool success) override;
	// 登陆游戏服务器
	virtual void I_R_M_Login(bool success, UINT handleCode, const std::string& message) override;
	// 玩家坐下
	virtual void I_R_M_UserSit(MSG_GR_R_UserSit * userSit, const UserInfoStruct* user) override;
	// 坐下失败
	virtual void I_R_M_SitError(const std::string& message) override;

private:

	void tryLogin(int accIndex);			// 尝试登陆 @accIndex 账户数组下标

	void trySit(int deskNo, int deskPos);	// 尝试坐下 @deskNo 桌子号 @ deskPos 座位号

	void returnGameMenu();

	ui::ScrollView* m_debugView;
	vector<string> m_userAcc;   // 账号容器
	vector<string> m_userPass;  // 密码容器
	int m_currLoginIndex;		// 当前登陆的账号位置
	int m_gameId;				// 游戏id
	int m_kindId;				// 游戏kindId
	int m_roomSelect;			// 选择的游戏房间
	int m_sitDeskNo;			// 坐下的桌子号
	string m_deskPassword;      // 桌子密码
	int m_firstTestDeskStation; // 优先尝试的位置
	int m_currTestDeskStation;  // 当前尝试坐下的位置
	int m_maxDeskPlayer;		// 游戏最大座位数
	int m_maxDeskNumbers;       // 最大桌子数
	bool m_useReconnect;		// 用于游戏重连
	string m_serverIp;
	int m_serverPort;
	ComRoomInfo* m_selectRoom;

	bool reconnectFromGame;		// 从游戏中重连， 如果在平台中重连则置为false
};

#endif  // __HNReconnectionLogic_H__
