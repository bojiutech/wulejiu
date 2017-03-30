/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#include "JoinRoomLayer.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "HNLobby/GamePrompt.h"
#include "../Reconnection/Reconnection.h"

USING_NS_CC_EXT;
using namespace network;

// 对话框布局文件
static const char* JOINROOM_LIST_CSB = "platform/joinRoom/joinRoom.csb";
static const char* NUMBER_IMAGE = "platform/joinRoom/joinRoomRes/selectroom_%d.png";
static const char* LOADING = "platform/loading.png";

JoinRoomLayer* JoinRoomLayer::create(bool autoJoin, const std::string &password)
{
	auto pJoinRoom = new (std::nothrow) JoinRoomLayer(autoJoin, password);
	if (pJoinRoom && pJoinRoom->init())
	{
		pJoinRoom->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pJoinRoom);
	}
	return pJoinRoom;
}

bool JoinRoomLayer::init()
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

	auto winSize = Director::getInstance()->getWinSize();

	// 加载布局
	_joinRoomStruct.node_joinRoom = CSLoader::createNode(JOINROOM_LIST_CSB);
	CCAssert(_joinRoomStruct.node_joinRoom != nullptr, "null");

	this->addChild(_joinRoomStruct.node_joinRoom);
	_joinRoomStruct.node_joinRoom->setPosition(Vec2(winSize.width / 2, winSize.height / 2));

	_joinRoomStruct.layout_joinRoom = dynamic_cast<ui::Layout*>(_joinRoomStruct.node_joinRoom->getChildByName("layout_joinRoom"));

	// 创建房间按钮
	Layout* layout_createRoom = dynamic_cast<ui::Layout*>(_joinRoomStruct.layout_joinRoom->getChildByName("layout_createRoom"));
	_joinRoomStruct.btn_createRoom = dynamic_cast<ui::Button*>(layout_createRoom->getChildByName("btn_createRoom"));
	CCAssert(_joinRoomStruct.btn_createRoom != nullptr, "null");
	_joinRoomStruct.btn_createRoom->addTouchEventListener(CC_CALLBACK_2(JoinRoomLayer::createRoomClickCallback, this));


	// 数字按钮
	char buffer[16];
	for (int i = 0; i < 10; ++i)
	{
		sprintf(buffer, "layout_%d", i);
		Layout* layout_number = dynamic_cast<ui::Layout*>(_joinRoomStruct.layout_joinRoom->getChildByName(buffer));
		sprintf(buffer, "btn_%d", i);
		Button* btn_number = dynamic_cast<ui::Button*>(layout_number->getChildByName(buffer));
		btn_number->setTag(i);
		btn_number->addTouchEventListener(CC_CALLBACK_2(JoinRoomLayer::onNumberBtnClickCallback, this));
	}

	// 数字图片
	for (int i = 0; i < 6; ++i)
	{
		sprintf(buffer, "image_num_%d", i);
		auto image_num = dynamic_cast<ui::ImageView*>(_joinRoomStruct.layout_joinRoom->getChildByName(buffer));
		_numberVector.pushBack(image_num);
	}

	// 删除按钮
	Layout* layout_delete = dynamic_cast<ui::Layout*>(_joinRoomStruct.layout_joinRoom->getChildByName("layout_delete"));
	_joinRoomStruct.btn_delete = dynamic_cast<ui::Button*>(layout_delete->getChildByName("btn_delete"));
	CCAssert(_joinRoomStruct.btn_delete != nullptr, "null");
	_joinRoomStruct.btn_delete->addTouchEventListener(CC_CALLBACK_2(JoinRoomLayer::deleteBtnClickCallback, this));

	// 关闭按钮
	_joinRoomStruct.btn_close = dynamic_cast<ui::Button*>(_joinRoomStruct.layout_joinRoom->getChildByName("btn_close"));
	CCAssert(_joinRoomStruct.btn_close != nullptr, "null");
	_joinRoomStruct.btn_close->addTouchEventListener(CC_CALLBACK_2(JoinRoomLayer::onCloseClickCallback, this));

	return true;
}

void JoinRoomLayer::onNumberBtnClickCallback(Ref* pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
	{
		return;
	}

	auto clickedBtn = (Button*)pSender;
	auto btnTag = clickedBtn->getTag();

	auto passwordLen = _currentPassWord.length();
	if (passwordLen < 6)
	{
		char buffer[128] = "";		
		sprintf(buffer, NUMBER_IMAGE, btnTag);
		auto number = _numberVector.at(passwordLen);
		if (number)
		{
			number->loadTexture(buffer);
			number->setVisible(true);
		}
		
		_currentPassWord = _currentPassWord.append(StringUtils::format("%d", btnTag));

		if (6 == _currentPassWord.length())
		{	
			// 调用重连逻辑进入创建房间
			Reconnection::getInstance()->doLoginVipRoom(_currentPassWord);
		}
	}
	
}

void JoinRoomLayer::onCloseClickCallback(Ref* pSender, Widget::TouchEventType type)
{
	if(type != Widget::TouchEventType::ENDED)
	{
		return;
	}

	this->removeFromParent();
}

void JoinRoomLayer::setSelectedGameName(const std::string &name)
{
	_gameName = name;
}

void JoinRoomLayer::createRoomClickCallback(Ref* pSender, Widget::TouchEventType type)
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

void JoinRoomLayer::deleteBtnClickCallback(Ref* pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
	{
		return;
	}

	auto passwordLen = _currentPassWord.length();
	if (passwordLen <= 6 && passwordLen > 0)
	{
		_numberVector.at(passwordLen-1)->setVisible(false);
		
		if (1 == passwordLen)
		{
			_currentPassWord = "";
		}
		else
		{
			_currentPassWord = _currentPassWord.substr(0, _currentPassWord.length() - 1);
		}
	}
}

JoinRoomLayer::JoinRoomLayer(bool autoJoin, const std::string &password) : _roomID(-1), _deskID(-1)
{
	_joinRoomPassword = password;

	_currentPassWord = "";

	_gameName = "";	
}

JoinRoomLayer::~JoinRoomLayer()
{
	_numberVector.clear();
}