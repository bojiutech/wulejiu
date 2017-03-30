/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#ifndef JoinRoomLayer_h__
#define JoinRoomLayer_h__

#include "HNUIExport.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "extensions/cocos-ext.h"
#include "network/HttpClient.h"
#include "CreateRoomLayer.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

// 公告弹窗
class JoinRoomLayer : public HNLayer
{
public:
	// 初始化
	virtual bool init() override;

	// 构造函数
	JoinRoomLayer(bool autoJoin = false, const std::string &password = "");

	// 析构函数
	virtual ~JoinRoomLayer();

	// 关闭弹窗回调
	void onCloseClickCallback(Ref* pSender, Widget::TouchEventType type);

	// 数字按钮回调
	void onNumberBtnClickCallback(Ref* pSender, Widget::TouchEventType type);

	// 创建房间回调
	void createRoomClickCallback(Ref* pSender, Widget::TouchEventType type);

	// 删除按钮回调
	void deleteBtnClickCallback(Ref* pSender, Widget::TouchEventType type);

	// 设置游戏名称
	void setSelectedGameName(const std::string &name);

	// 创建弹窗
	CREATE_FUNC(JoinRoomLayer);

	static JoinRoomLayer* create(bool autoJoin, const std::string &password);

private:

	struct JoinRoomStruct
	{
		Node*		node_joinRoom;
		Layout*     layout_joinRoom;

		Button*		btn_createRoom;
		Button*		btn_close;
		Button*		btn_delete;
	} _joinRoomStruct;
	
	std::string _currentPassWord;  //当前输入的房间密码

	Vector<ImageView*> _numberVector;

	INT _roomID;

	INT _deskID;

	std::string _joinRoomPassword;

	std::string _gameName;
};

#endif // JoinRoomLayer_h__
