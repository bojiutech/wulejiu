#ifndef GameDesk_h__
#define GameDesk_h__

#include "HNNetExport.h"
#include "HNUIExport.h"
#include "HNLogicExport.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <vector>

USING_NS_CC;

using namespace cocostudio;
using namespace ui;

//������Ϣ
typedef struct tagDeskInfo
{
	INT		deskID;               // ����
	INT		multiple;             // ����
	INT		goldMin;              // ��СЯ����Ǯ
	INT		goldMax;              // ���Я����Ǯ
	INT		peopleValue;          // ���ӵ�ǰ����
	INT		peopleMax;            // �����������
	bool    isLocked;             // �Ƿ�����
	//bool	isVIP;				  // �Ƿ�VIP��
}DeskInfo;

class GameDesk : public HNLayer, public IHNRoomDeskLogic
{
public:
	typedef std::function<void ()> CloseCallBack;
	CloseCallBack				onCloseCallBack;

private:
	ComRoomInfo*				_roomInfo;
	PageView*					_pageViewDesks;			// �����б�
	Button*						_currentSelectedDesk;	// �б�ť
	INT							_deskNO;				// ���Ӻ�
	
	// ����ҳ��ʱ����
	std::vector<DeskInfo*>		_deskinfos;

	// �����б���������
	std::vector<DeskInfo*>      _allDeskInfo;
	
	bool						_pageEven;				//�Ƿ�����ҳ
	INT							_pageLen;				//�����������ҳ��
	bool						_canCreate;				//�Ƿ���Ҫ����ҳ��

	std::vector<Sprite*>		_pagesPrompt;
	INT							_currentPageIdx;
	bool						_isTouch;

public:
	static GameDesk* createDesk(ComRoomInfo* roomInfo);

public:
	GameDesk();
	virtual ~GameDesk();

	bool initData(ComRoomInfo* roomInfo);
	virtual void onExit() override;

public:
	void closeDeskList();

	// ��������ص�
	void onEnterPasswordCallback(const std::string& password);

public:
	// ���������б�pageView
	void createDeskList(ComRoomInfo* roomInfo);
	// ��ҳ���������б�page
	void createDeskPage();
	// ��������ҳ������
	void createDeskPageInfo(ComRoomInfo* roomInfo);
	// ���������б�page
	void createDeskListPage(std::vector<DeskInfo*> deskinfos);
	// ���������б�button
	Node* addDesk(DeskInfo* deskInfo);

public:
	// pageView�϶��ص�����
	void pageViewMoveCallBack(Ref* pSender, PageView::EventType type);

	// �����Ƿ���������
	void updateLockDesk();

	// ������Ϸ������ص�
	void enterTableEventCallBack(Ref* pSender, Widget::TouchEventType type);

public:
	virtual void onDeskSitCallback(bool success, const std::string& message, UINT roomID, BYTE deskNo, BYTE seatNo) override;
	virtual void onRoomDeskLock(BYTE deskNo) override;
	virtual void onRoomDeskUnLock(BYTE deskNo) override;
	virtual void onRoomDeskUserCountChanged() override;

	//������Ϸ����
	void updateDeskPeopleCount(BYTE deskNo, bool isLock);

protected:
	HNRoomDeskLogic* _deskLogic;
};

#endif // GameDesk_h__