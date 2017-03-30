#ifndef GameLists_h__
#define GameLists_h__


#include "HNNetExport.h"
#include "HNUIExport.h"

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio;
using namespace ui;

class GameLists : public HNLayer
{
public:
	typedef std::function<void ()> EnterGameCallBack;
	EnterGameCallBack onEnterGameCallBack;
	EnterGameCallBack onRunActionCallBack;

private:
	PageView*					_pageViewGames;			// ��Ϸ�б�
	Button*						_currentSelectedGame;	// �б�ť

	std::vector<Sprite*>		_pagesPrompt;
	INT							_currentPageIdx;
	bool						_isTouch;

public:
	GameLists();
	virtual ~GameLists();

	CREATE_FUNC(GameLists);

public:
	virtual bool init() override;

	virtual void onEnter() override;

	virtual void onExit() override;

	// ����ص��ӿ�
public:
	//pageView�϶��ص�����
	void pageViewMoveCallBack(Ref* pSender, PageView::EventType type);
	//�б�ť����ص�����
	void enterRoomEventCallBack(Ref* pSender, Widget::TouchEventType type);

	//�б�ť�����Ķ���
	void enterRoomAction();

	// ���ܽӿ�
private:
	// ������Ϸ�б�
	void createGameList();
	// ������Ϸ
	void createGamePage(std::vector<ComNameInfo*> games);
	// ������ϷԪ��
	Node* createGameItem(ComNameInfo* game);

public:
	//������Ϸ����
	void updateGamePeopleCount(UINT Id, UINT count);
};
#endif // GameLists_h__
