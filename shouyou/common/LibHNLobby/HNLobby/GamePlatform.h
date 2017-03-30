#ifndef __PLATFORMFRAME_SCENE_H__
#define __PLATFORMFRAME_SCENE_H__

#include "HNLobby/ChildLayer/GameStoreLayer.h"
#include "HNLobby/Popularise/SpreadEditLayer.h"
#include "HNLobby/ChildLayer/GameUserHead.h"
#include "HNNetExport.h"
#include "HNUIExport.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "HNLogicExport.h"
#include <string>
#include <vector>
#include "network/HttpClient.h"

using namespace ui;
using namespace cocostudio;

enum LayerType
{
	ROOMLIST = 0,
	DESKLIST,
	GAMELIST
};

class GameUserDataLayer;
class GameNotice;

class GamePlatform : public HNLayer, public MoneyChangeNotify, public HN::IHNPlatformRoomList,
	public HN::IHNPlatformGameList, public HNSpreadLogic::Delegate, public HNHttpDelegate
{
public:
	HNPlatformRoomList*		_roomListLogic;
	HNPlatformGameList*		_gameListLogic;

	struct LOBBY_BOTTOM
	{
		Button* Button_Friend;
		Button* Button_Task;
		Button* Button_Activity;
		Button* Button_Bank;
		Button* Button_Store;
		Button* Button_Rank;

		Layout*	layout;
		Node*   node;

	} _lobbyBotttom;

	struct LOBBY_TOP
	{
		Text* Label_UserName;
		Text* Label_UserMoney;
		Text* Label_UserJewels;

		GameUserHead*	UserHead_Head;
		Button*		Button_Return;
		Button*		Button_service;
		Button*		Button_exit;
		Button*		Button_notice;
		Button*		Button_sign;
		Button*		Button_setting;
		Button*		Button_popularize; //�ƹ�ͼ��
		Button*     Button_exchange;//��Ʒ�һ�ͼ��
		Layout*	layout;
		Node*   node;
	} _lobbyTop;

	std::map<std::string, cocos2d::String> _Data;

private:
	Label*				_peopleCountLabel;    //
	Sprite*				_Decoration_left;
	Sprite*				_Decoration_right;
	Sprite*				_NoticeBG;
	GameNotice*			_PlatformNotic;
	bool				_isTouch;
	INT					_Time;
	bool				_isCustomer;
	INT					_iValue;
	HNSpreadLogic		_spreadLogic; //�ƹ��߼���
public:
	static void createPlatform();
	static void returnPlatform(LayerType type);

	void createLayerChoose(LayerType type);

	virtual void onSpreadInfo(bool result, bool bInfo, const std::string& msg) override;

	CREATE_FUNC(GamePlatform);
public:
	GamePlatform();
	virtual ~GamePlatform();

    virtual bool init() override;
	virtual void onExit() override;
	virtual void onEnterTransitionDidFinish() override;

	// ��ֲ����
	void plantSeed();

	//���ؼ������ص�����
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent) override;

private:
	//��ѯ���ֽ�����Ϣ
	void checkGiftMessages();
	//ж�ؽ�������
	void unSocketCallBack();
	//��ѯ��Ϣ�ص�
	bool checkGiftMessagesEventSelector(HNSocketMessage* socketMessage);
	//�콱���ѵ���ʱ
	void updataGetRewardTimeMessage(float dt);
	//��ȡ�������ʾ��
	std::string showHint();

private:
	// ��ȡ����/��Ϸ�б�ʱ��
	void requestGameRoomTimerCallBack(float dt);
	//������ť�ص�
	void menuLobbyTopCallBack(Ref* pSender, Widget::TouchEventType type);
	//�ײ���ť�ص�
	void menuLobbyBottomCallBack(Ref* pSender, Widget::TouchEventType type);
	// �����˷������
	void openUMengShare();

public:
	//���������б��
	void createRoomListLayer();
	//������Ϸ�б��
	void createGameListLayer();
	//���������б��
	void createDeskListLayer(ComRoomInfo* roomInfo);

public:
	//�����͵ײ���ö���
	void showTopAndBottomAction(bool isOut, bool canReturn);

public:
	// ������ҹ�������Ϣ
	virtual void walletChanged(LLONG money) override;

	// ��ȡ��������
	void requestNotice();
	void dealNoticeResp(const std::string& data);

	// ��ȡ������ʾģ��
	void requestModule();
	void dealModuleResp(const std::string& data);

	// ��ȡ������Ϣ
	void requestShare();
	void dealShareResp(const std::string& data);

public:
	////////////////////////////////////////////////////////////////////////////////////////////
	//���뷿���б�ص�
	virtual void onPlatformRoomListCallback(bool success, const std::string& message) override;
	//���·�������
	virtual void onPlatformRoomUserCountCallback(UINT roomID, UINT userCount) override;

	////////////////////////////////////////////////////////////////////////////////////////////
	//������Ϸ�б�ص�
	virtual void onPlatformGameListCallback(bool success, const std::string& message) override;
	//������Ϸ����
	virtual void onPlatformGameUserCountCallback(UINT Id, UINT count) override;

	//����֪ͨ
	virtual void onPlatformDisConnectCallback(const std::string& message) override;
	//���Ź㲥��Ϣ
	virtual void onPlatformNewsCallback(const std::string& message) override;

	virtual void onHttpResponse(const std::string& requestName, bool isSucceed, const std::string &responseData) override;

private:
	//��ʱ��������ʼ
	bool enterTimeMatch();
	//��ⱨ���Ķ�ʱ���Ƿ�ʼ
	void checkTimeMatchStart(float dt);
	//����Ϸ�б�λ�ÿ�ݽ��뷿�����
	void fastEnterRoom();

	// ������������
	void playOrStopJump(cocos2d::Node* pNode, bool bJump);

	// �����ַ
	std::string _shareUrl;

	// ��������
	std::string _shareContent;

	// ����ͼƬ
	std::string _shareImage;
};

#endif // __PLATFORMFRAME_SCENE_H__
