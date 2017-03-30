/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#ifndef SelectRoomLayer_h__
#define SelectRoomLayer_h__

#include "HNUIExport.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "HNLobby/GameLists.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

// ���浯��
class SelectRoomLayer : public HNLayer
{
public:
	// ��ʼ��
	virtual bool init() override;

	// ���캯��
	SelectRoomLayer();

	// ��������
	virtual ~SelectRoomLayer();

	// �رյ����ص�
	void onCloseClickCallback(Ref* pSender, Widget::TouchEventType type);

	// ��Ϸ�����ص�
	void normalRoomClickCallback(Ref* pSender, Widget::TouchEventType type);

	// ��������ص�
	void createRoomClickCallback(Ref* pSender, Widget::TouchEventType type);

	// ������Ϸ�ص�
	void joinRoomClickCallback(Ref* pSender, Widget::TouchEventType type);

	// ������Ϸ����
	void setSelectedGameName(const std::string &name);

	// ��������
	CREATE_FUNC(SelectRoomLayer);

private:

	struct SelectRoomStruct
	{
		Node*		node_selectRoom;
		Layout*     layout_selectRoom;

		Button*		btn_close;
		Button*		btn_normalRoom;
		Button*		btn_createRoom;
		Button*		btn_join;
		
	} _selectRoomStruct;

	GameLists* _gameList;

	std::string _gameName;

	Size _winSize;
	
};

#endif // SelectRoomLayer_h__
