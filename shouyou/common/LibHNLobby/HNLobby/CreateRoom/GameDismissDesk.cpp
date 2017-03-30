/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#include "GameDismissDesk.h"
#include "HNLobby/FontConfig.h"
#include "HNLobby/PlatformDefine.h"
#include <string>

static const char* PROMPT_CSB		= "platform/dismissDesk/dismissDesk.csb";

static const int DismissDesk_LAYER_ZORDER	= 100000000;		// 子节点弹出框层级

static const int DismissDesk_LAYER_TAG		= 100000000;		// 子节点弹出框层级

const std::string AgreeDismiss				= "同意解散";		// 同意解散

const std::string RefuseDismiss				= "拒绝解散";		// 同意解散

GameDismissDesk::GameDismissDesk() 
	: _dismissDeskNode(nullptr)
	, _sure (nullptr)
	, _cancel (nullptr)
	, _btn_agree(nullptr)
	, _btn_refuse(nullptr)
	, _applyUserID(0)
	, _sequenceNumber(0)
{

}

GameDismissDesk::~GameDismissDesk()
{

}

void GameDismissDesk::show()
{
	Node* root = Director::getInstance()->getRunningScene();
	CCAssert(nullptr != root, "root is null");
	if (nullptr == root)
	{
		log("vip-----------rootFail");
	}

	root->addChild(this, DismissDesk_LAYER_ZORDER, DismissDesk_LAYER_TAG);
}

void GameDismissDesk::close()
{
	HNAudioEngine::getInstance()->playEffect(GAME_SOUND_CLOSE);
	_dismissDeskNode->runAction(Sequence::create(ScaleTo::create(0.1f, 0.3f), CCCallFunc::create([&]()
	{
		this->removeFromParent();
	}), nullptr));
}

bool GameDismissDesk::init()
{
    if ( !HNLayer::init()) return false;
	//屏蔽后面的层
	auto colorLayer = LayerColor::create(Color4B(0, 0, 0, 100));
	addChild(colorLayer, 1);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [=](Touch* touch ,Event* event){
		return true;
	};
	touchListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,colorLayer);

	Size winSize = Director::getInstance()->getWinSize();

	_dismissDeskNode = CSLoader::createNode(PROMPT_CSB);
	_dismissDeskNode->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	_dismissDeskNode->setScale(0);
	addChild(_dismissDeskNode, 2);
	_dismissDeskNode->runAction(ScaleTo::create(0.2f, 1.0f));
	_dismissDeskLayout = (Layout*)_dismissDeskNode->getChildByName("Panel_1");

	//申请玩家昵称
	_txt_applyUser = (Text*)_dismissDeskLayout->getChildByName("txt_applyUser");

	//确定按钮
	_btn_agree = (Button*)_dismissDeskLayout->getChildByName("btn_agree");
	_btn_agree->addTouchEventListener(CC_CALLBACK_2(GameDismissDesk::agreeBtnCallBack, this));

	//拒绝按钮
	_btn_refuse = (Button*)_dismissDeskLayout->getChildByName("btn_refuse");
	_btn_refuse->addTouchEventListener(CC_CALLBACK_2(GameDismissDesk::refuseBtnCallBack, this));

	return true;
}

void GameDismissDesk::agreeBtnCallBack(Ref* pSender, Widget::TouchEventType type)
{
	if (Widget::TouchEventType::ENDED != type) return;

	VIP_Desk_Dismiss_Agree dismiss_agree;
	dismiss_agree.bAgree = true;
	RoomLogic()->sendData(MDM_GR_VIP_ROOM, ASS_GR_DISSMISS_AGREE, &dismiss_agree, sizeof(dismiss_agree));

	_btn_agree->setVisible(false);
	_btn_refuse->setVisible(false);
}

void GameDismissDesk::refuseBtnCallBack(Ref* pSender, Widget::TouchEventType type)
{
	if (Widget::TouchEventType::ENDED != type) return;

	VIP_Desk_Dismiss_Agree dismiss_agree;
	dismiss_agree.bAgree = false;
	RoomLogic()->sendData(MDM_GR_VIP_ROOM, ASS_GR_DISSMISS_AGREE, &dismiss_agree, sizeof(dismiss_agree));

	_btn_agree->setVisible(false);
	_btn_refuse->setVisible(false);
}

void GameDismissDesk::setApplyUser(int applyUserID, const std::string& applyUserName)
{
	_applyUserID = applyUserID;

	char buffer[64] = { 0 };
	sprintf(buffer, "%s", applyUserName.c_str());
	_txt_applyUser->setString(GBKToUtf8(buffer));
	_txt_applyUser->setVisible(true);

	bool isApplyUser = applyUserID == PlatformLogic()->loginResult.dwUserID ? true : false;
	_btn_agree->setVisible(!isApplyUser);
	_btn_refuse->setVisible(!isApplyUser);
}

void GameDismissDesk::setActionUser(int userID, const std::string& applyUserName)
{
	if (userID == _applyUserID) return;

	char buffer[64] = { 0 };
	sprintf(buffer, "txt_actionUser%d", _sequenceNumber);
	auto actionUser = dynamic_cast<Text*>(_dismissDeskLayout->getChildByName(buffer));
	if (actionUser)
	{
		sprintf(buffer, "%s", applyUserName.c_str());
		actionUser->setString(GBKToUtf8(buffer));
		actionUser->setVisible(true);

		sprintf(buffer, "txt_action%d", _sequenceNumber);
		auto action = dynamic_cast<Text*>(_dismissDeskLayout->getChildByName(buffer));
		action->setTag(userID);
		action->setVisible(true);
	}

	_sequenceNumber++;
}

void GameDismissDesk::DisplayAction(int userID, ACTION_TYPE action)
{
	auto txtAction = dynamic_cast<Text*>(_dismissDeskLayout->getChildByTag(userID));

	if (ACTION_TYPE::agree == action)
	{
		txtAction->setString(GBKToUtf8(AgreeDismiss.c_str()));
		txtAction->setColor(Color3B::YELLOW);
	}
	else
	{
		txtAction->setString(GBKToUtf8(RefuseDismiss.c_str()));
		txtAction->setColor(Color3B::RED);
	}
}
