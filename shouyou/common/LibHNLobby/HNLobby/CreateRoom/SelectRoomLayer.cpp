/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#include "SelectRoomLayer.h"
#include "CreateRoomLayer.h"
#include "HNLobby/GamePrompt.h"
#include "JoinRoomLayer.h"

USING_NS_CC_EXT;
using namespace network;

// 对话框布局文件
static const char* SELECTROOM_LIST_CSB = "platform/selectRoom/selectRoom.csb";

bool SelectRoomLayer::init()
{
	if(!HNLayer::init())
	{
		return false;
	}

	ignoreAnchorPointForPosition(false);

	// 添加屏蔽层
	auto colorLayer = LayerColor::create(Color4B(0, 0, 0, 100));
	addChild(colorLayer);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [=](Touch* touch ,Event* event){
		return true;
	};
	touchListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,colorLayer);

	_winSize = Director::getInstance()->getWinSize();

	// 加载布局
	_selectRoomStruct.node_selectRoom = CSLoader::createNode(SELECTROOM_LIST_CSB);
	CCAssert(_selectRoomStruct.node_selectRoom != nullptr, "null");

	this->addChild(_selectRoomStruct.node_selectRoom);
	_selectRoomStruct.node_selectRoom->setPosition(Vec2(_winSize.width / 2, _winSize.height / 2));

	_selectRoomStruct.layout_selectRoom = dynamic_cast<ui::Layout*>(_selectRoomStruct.node_selectRoom->getChildByName("selectRoom_layout"));

	// 普通房间按钮
	_selectRoomStruct.btn_normalRoom = dynamic_cast<ui::Button*>(_selectRoomStruct.layout_selectRoom->getChildByName("btn_normalRoom"));
	CCAssert(_selectRoomStruct.btn_normalRoom != nullptr, "null");
	_selectRoomStruct.btn_normalRoom->addTouchEventListener(CC_CALLBACK_2(SelectRoomLayer::normalRoomClickCallback, this));
	// 创建房间按钮
	_selectRoomStruct.btn_createRoom = dynamic_cast<ui::Button*>(_selectRoomStruct.layout_selectRoom->getChildByName("btn_createRoom"));
	CCAssert(_selectRoomStruct.btn_createRoom != nullptr, "null");
	_selectRoomStruct.btn_createRoom->addTouchEventListener(CC_CALLBACK_2(SelectRoomLayer::createRoomClickCallback, this));
	// 加入游戏按钮
	_selectRoomStruct.btn_join = dynamic_cast<ui::Button*>(_selectRoomStruct.layout_selectRoom->getChildByName("btn_join"));
	CCAssert(_selectRoomStruct.btn_join != nullptr, "null");
	_selectRoomStruct.btn_join->addTouchEventListener(CC_CALLBACK_2(SelectRoomLayer::joinRoomClickCallback, this));

	// 关闭按钮
	_selectRoomStruct.btn_close = dynamic_cast<ui::Button*>(_selectRoomStruct.layout_selectRoom->getChildByName("btn_close"));
	CCAssert(_selectRoomStruct.btn_close != nullptr, "null");
	_selectRoomStruct.btn_close->addTouchEventListener(CC_CALLBACK_2(SelectRoomLayer::onCloseClickCallback, this));

	return true;
}

void SelectRoomLayer::onCloseClickCallback(Ref* pSender, Widget::TouchEventType type)
{
	if(type != Widget::TouchEventType::ENDED)
	{
		return;
	}

	this->removeFromParent();
}

void SelectRoomLayer::normalRoomClickCallback(Ref* pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
	{
		return;
	}

	_gameList = dynamic_cast<GameLists*>(this->getParent());
	CCAssert(_gameList != nullptr, "null");

	_gameList->enterRoomAction();
	this->removeFromParent();
	
}

void SelectRoomLayer::createRoomClickCallback(Ref* pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
	{
		return;
	}

	CreateRoomLayer* createRoomLayer = CreateRoomLayer::create();
	createRoomLayer->setSelectedGameName(_gameName);
	this->getParent()->addChild(createRoomLayer, 10);
	createRoomLayer->setPosition(Vec2(_winSize.width / 2, _winSize.height / 2));

	this->removeFromParent();
}

void SelectRoomLayer::joinRoomClickCallback(Ref* pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
	{
		return;
	}

	JoinRoomLayer* joinRoomLayer = JoinRoomLayer::create();
	joinRoomLayer->setSelectedGameName(_gameName);
	this->getParent()->addChild(joinRoomLayer, 10);
	joinRoomLayer->setPosition(Vec2(_winSize.width / 2, _winSize.height / 2));

	this->removeFromParent();
}

void SelectRoomLayer::setSelectedGameName(const std::string &name)
{
	_gameName = name;
}

SelectRoomLayer::SelectRoomLayer()
{
	_gameName = "";
}

SelectRoomLayer::~SelectRoomLayer()
{
}