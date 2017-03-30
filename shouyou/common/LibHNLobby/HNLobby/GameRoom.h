#ifndef __GameRoom_SCENE_H__
#define __GameRoom_SCENE_H__

#include "HNNetExport.h"
#include "HNUIExport.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "HNLogicExport.h"

USING_NS_CC;

using namespace cocostudio;
using namespace ui;

class GameRoom : public HNLayer, public HN::IHNRoomLogicBase
{
public:
	typedef std::function<void ()> CloseCallBack;
	CloseCallBack				onCloseCallBack;
	CloseCallBack				onRunActionCallBack;

	typedef std::function<void (ComRoomInfo* roomInfo)> EnterDeskCallBack;
	EnterDeskCallBack			onEnterDeskCallBack;

	HNRoomLogicBase*			_roomLogic;
private:
	PageView*					_pageViewRooms;						// �����б�
	Button*						_currentSelectedRoom;			// �б�ť

	std::vector<Sprite*>		_pagesPrompt;
	INT							_currentPageIdx;
	bool						_isTouch;
	
	std::vector<UINT>				_vecContestRoom;
	bool											_overdueTime;					//��õĿ���ʱ���Ƿ����
	bool											_fastEnterMatch;
	INT												_roomID;

public:
	CREATE_FUNC(GameRoom);

public:
	GameRoom();
	virtual ~GameRoom();

public:
    virtual bool init() override;
	
	virtual void onExit() override;


public:
	void closeRoomList();

	// ������������ص�
	void onEnterPasswordClickCallback(const std::string& password);

	// ����ص��ӿ�
public:
	// pageView�϶��ص�����
	void pageViewMoveCallBack(Ref* pSender, PageView::EventType type);

	// �б�ť����ص�����
	void enterRoomEventCallBack(Ref* pSender, Widget::TouchEventType type);

	// ���ܽӿ�
private:
	// ���������б�
	void createRoomList();
	// ��������
	void createRoomPage(std::vector<ComRoomInfo*> pages);
	// ��������Ԫ��
	Node* createRoomItem(ComRoomInfo* roomInfo);
	
	// ��ʱ���ص�����
public:
	//// ���·���������Ϣ��ʱ��
	//void updateRoomPeopleTimerCallBack(float dt);
	//// ���ӷ��䳬ʱ��ʱ��
	//void enterRoomOutTimerTimerCallBack(float dt);
	//���·�������
	void updateRoomPeopleCount(UINT roomID, UINT userCount);

	// ������ӿ�
public:
	//��½����ص�
	virtual void onRoomLoginCallback(bool success, const std::string& message, UINT roomID, UINT handldeCode) override;
	virtual void onRoomSitCallback(bool success, const std::string& message, UINT roomID, BYTE deskNo, BYTE seatNo) override;
	virtual void onRoomQueueSitCallback(bool success, const std::string& message, UINT roomID, BYTE deskNo) override;
	virtual void onRoomDisConnect(const std::string &message) override;

	// ��������
	virtual void onPlatformRoomPassEnter(bool success, UINT roomId);

	//�����ӿ�
public:
	// ���������Ƿ񴴽��ж�
	bool JudgeMatchRoom(UINT upPeople, UINT roomRule);
	//���������ʼ��
	bool contestInit(HNSocketMessage* socketMessage);
	//�������䶼�ڱ���
	bool contestInitError(HNSocketMessage* socketMessage);
	//��ʱ������ʱ��
	bool contestBeginTime(HNSocketMessage* socketMessage);
	//�����ʱ����������
	void cleanTimeMatchData();
	//���������������
	void fastEnterTimeMatch(UINT roomID);
	//��ȡ��ʱ������id
	UINT getTimeMatchRoomID();

};

#endif // __GameRoom_SCENE_H__
