/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#ifndef CreateRoomLayer_h__
#define CreateRoomLayer_h__

#include "HNUIExport.h"
#include "HNNetExport.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "extensions/cocos-ext.h"
#include "network/HttpClient.h"
#include "ui/UICheckBox.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;
using namespace HN;

// 公告弹窗
class CreateRoomLayer : public HNLayer
{
public:
	// 初始化
	virtual bool init() override;

	// 构造函数
	CreateRoomLayer();

	// 析构函数
	virtual ~CreateRoomLayer();

	// 关闭弹窗回调
	void onCloseClickCallback(Ref* pSender, Widget::TouchEventType type);

	// 创建房间回调
	void createRoomClickCallback(Ref* pSender, Widget::TouchEventType type);

	// 复选框回调函数
	void checkBoxCallback(Ref* pSender, CheckBox::EventType type);

	// 创建桌子回调
	bool createRoomMessagesEventSelector(HNSocketMessage* socketMessage);

	// 设置游戏名称
	void setSelectedGameName(const std::string &name);

	// 创建弹窗
	CREATE_FUNC(CreateRoomLayer);

private:
	// 获取房间配置
	void getRoomConfiguration();

	// 获取桌子配置回调
	bool getRoomConfigurationEventSelector(HNSocketMessage* socketMessage);

	struct CreateRoomStruct
	{
		Node*		node_createRoom;
		Layout*     layout_createRoom;

		Button*		btn_close;
		CheckBox*	checkBox_round1;
		CheckBox*	checkBox_round2;
		Button*		btn_createRoom;

		Text*       txt_round1;
		Text*       txt_round2;

		Text*       txt_prompt1;
		Text*       txt_prompt2;
		
	} _createRoomStruct;

	std::vector<INT> _gameRoundVector;
	std::vector<INT> _roomPrice;

	std::string _gameName;
	
};

#endif // CreateRoomLayer_h__
