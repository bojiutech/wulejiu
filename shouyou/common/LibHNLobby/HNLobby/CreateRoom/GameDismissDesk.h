/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#ifndef GameDismissDesk_h__
#define GameDismissDesk_h__

#include "HNUIExport.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

using namespace ui;
using namespace cocostudio;

enum ACTION_TYPE
{
	agree = 0,
	refuse,
};

class GameDismissDesk : public HNLayer
{
	Rect _userRect;

private:
	Button*         _btn_agree;
	Button*         _btn_refuse;
	Text*			_txt_applyUser;
	Node*			_dismissDeskNode;
	Layout*			_dismissDeskLayout;

	int				_applyUserID;		//申请玩家ID

	int				_sequenceNumber;  //设置动作玩家显示的顺序

public:
	CREATE_FUNC(GameDismissDesk);

	GameDismissDesk();
	virtual ~GameDismissDesk();

public:
	virtual bool init() override;  

	void show();

	void close();

	void setApplyUser(int applyUserID, const std::string& applyUserName);

	void setActionUser(int userID, const std::string& applyUserName);

	void DisplayAction(int userID, ACTION_TYPE action);

private:
	std::function<void ()> _sure;

	std::function<void ()> _cancel;

	//同意按钮回调
	void agreeBtnCallBack(Ref* pSender, Widget::TouchEventType type);

	//拒绝按钮回调
	void refuseBtnCallBack(Ref* pSender, Widget::TouchEventType type);

};

#endif // GameDismissDesk_h__
