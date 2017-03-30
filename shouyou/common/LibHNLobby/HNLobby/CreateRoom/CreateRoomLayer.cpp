/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#include "CreateRoomLayer.h"
#include "HNNetExport.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "HNLobby/GamePrompt.h"
#include "ui/UICheckBox.h"
#include "../Reconnection/Reconnection.h"

// 对话框布局文件
static const char* CREATEROOM_CSB = "platform/createRoom/createRoom.csb";
static const char* LOADING = "platform/loading.png";
static const char* CREATE_ROOM_PROMPT1 = "%d局";
static const char* CREATE_ROOM_PROMPT2 = "(消耗 %d 个钻石)";

static const char* JOINROOMLAYERNAME = "joinRoomLayer";
static const int JOINROOMLAYERZORDER = -100;

bool CreateRoomLayer::init()
{
	if (!HNLayer::init())
	{
		return false;
	}

	ignoreAnchorPointForPosition(false);

	// 添加屏蔽层
	auto colorLayer = LayerColor::create(Color4B(0, 0, 0, 100));
	addChild(colorLayer);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [=](Touch* touch, Event* event){
		return true;
	};
	touchListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, colorLayer);

	auto winSize = Director::getInstance()->getWinSize();

	// 加载布局
	_createRoomStruct.node_createRoom = CSLoader::createNode(CREATEROOM_CSB);
	CCAssert(_createRoomStruct.node_createRoom != nullptr, "null");

	this->addChild(_createRoomStruct.node_createRoom);
	_createRoomStruct.node_createRoom->setPosition(Vec2(winSize.width / 2, winSize.height / 2));

	_createRoomStruct.layout_createRoom = dynamic_cast<ui::Layout*>(_createRoomStruct.node_createRoom->getChildByName("layout_createRoom"));

	// 局数选择复选框1
	_createRoomStruct.checkBox_round1 = dynamic_cast<ui::CheckBox*>(_createRoomStruct.layout_createRoom->getChildByName("checkBox_1"));
	CCAssert(_createRoomStruct.checkBox_round1 != nullptr, "null");
	_createRoomStruct.checkBox_round1->setSelected(true);
	_createRoomStruct.checkBox_round1->addEventListener(CheckBox::ccCheckBoxCallback(CC_CALLBACK_2(CreateRoomLayer::checkBoxCallback, this)));

	// 局数选择复选框2
	_createRoomStruct.checkBox_round2 = dynamic_cast<ui::CheckBox*>(_createRoomStruct.layout_createRoom->getChildByName("checkBox_2"));
	CCAssert(_createRoomStruct.checkBox_round2 != nullptr, "null");
	_createRoomStruct.checkBox_round2->setSelected(false);
	_createRoomStruct.checkBox_round2->addEventListener(CheckBox::ccCheckBoxCallback(CC_CALLBACK_2(CreateRoomLayer::checkBoxCallback, this)));

	// 局数选择文本
	_createRoomStruct.txt_round1 = dynamic_cast<ui::Text*>(_createRoomStruct.layout_createRoom->getChildByName("txt_round1"));
	_createRoomStruct.txt_round2 = dynamic_cast<ui::Text*>(_createRoomStruct.layout_createRoom->getChildByName("txt_round2"));

	// 局数提示文本
	_createRoomStruct.txt_prompt1 = dynamic_cast<ui::Text*>(_createRoomStruct.layout_createRoom->getChildByName("txt_prompt_1"));
	_createRoomStruct.txt_prompt2 = dynamic_cast<ui::Text*>(_createRoomStruct.layout_createRoom->getChildByName("txt_prompt_2"));


	// 创建房间按钮
	_createRoomStruct.btn_createRoom = dynamic_cast<ui::Button*>(_createRoomStruct.layout_createRoom->getChildByName("btn_createRoom"));
	CCAssert(_createRoomStruct.btn_createRoom != nullptr, "null");
	_createRoomStruct.btn_createRoom->addTouchEventListener(CC_CALLBACK_2(CreateRoomLayer::createRoomClickCallback, this));
	_createRoomStruct.btn_createRoom->setTouchEnabled(false);

	// 关闭按钮
	_createRoomStruct.btn_close = dynamic_cast<ui::Button*>(_createRoomStruct.layout_createRoom->getChildByName("btn_close"));
	CCAssert(_createRoomStruct.btn_close != nullptr, "null");
	_createRoomStruct.btn_close->addTouchEventListener(CC_CALLBACK_2(CreateRoomLayer::onCloseClickCallback, this));

	getRoomConfiguration();

	return true;
}

void CreateRoomLayer::checkBoxCallback(Ref* pSender, CheckBox::EventType type)
{
	auto checkBox_round = (CheckBox*)pSender;
	if (CheckBox::EventType::UNSELECTED == type)
	{
		if (checkBox_round == _createRoomStruct.checkBox_round1)
		{
			_createRoomStruct.checkBox_round2->setSelected(true);
		}
		else
		{
			_createRoomStruct.checkBox_round1->setSelected(true);
		}
	}
	else
	{
		if (checkBox_round == _createRoomStruct.checkBox_round1)
		{
			_createRoomStruct.checkBox_round2->setSelected(false);
		}
		else
		{
			_createRoomStruct.checkBox_round1->setSelected(false);
		}
	}
}

void CreateRoomLayer::onCloseClickCallback(Ref* pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
	{
		return;
	}

	this->removeFromParent();
}

void CreateRoomLayer::createRoomClickCallback(Ref* pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
	{
		return;
	}

	// 创建桌子
	MSG_GP_S_BUY_DESK buyDesk;
	buyDesk.iUserID = PlatformLogic()->loginResult.dwUserID;
	if (_createRoomStruct.checkBox_round1->isSelected())
	{
		buyDesk.iJewels = _roomPrice.at(0);
	}
	else
	{
		buyDesk.iJewels = _roomPrice.at(1);
	}

	if (_gameName.empty())
	{
		GamePromptLayer::create()->showPrompt(GBKToUtf8("游戏不存在！"));
		return;
	}

	strcpy(buyDesk.szGameName, _gameName.c_str());

	_createRoomStruct.btn_createRoom->setTouchEnabled(false);

	PlatformLogic()->sendData(MDM_GP_DESK_VIP, ASS_GP_BUY_DESK, 0, &buyDesk, sizeof(buyDesk),
		HN_SOCKET_CALLBACK(CreateRoomLayer::createRoomMessagesEventSelector, this));
}

void CreateRoomLayer::setSelectedGameName(const std::string &name)
{
	_gameName = name;
}

bool CreateRoomLayer::createRoomMessagesEventSelector(HNSocketMessage* socketMessage)
{
	CCAssert(sizeof(MSG_GP_S_BUY_DESK_RES) == socketMessage->objectSize, "MSG_GP_S_BUY_DESK_RES is error.");
	MSG_GP_S_BUY_DESK_RES* buyRoomResult = (MSG_GP_S_BUY_DESK_RES*)socketMessage->object;

	auto buyResultCode = buyRoomResult->iResult;
	switch (buyResultCode)
	{
	case 1:
	{
			  _createRoomStruct.btn_createRoom->setTouchEnabled(false);

			  auto roomID = buyRoomResult->iRoomID;
			  auto deskID = buyRoomResult->iDeskID;
			  std::string password = buyRoomResult->szPassWord;

			  std::string psd(buyRoomResult->szPassWord);
			  std::string tips = StringUtils::format(GBKToUtf8("创建成功！【房号：%s】"), buyRoomResult->szPassWord);
			  auto prompt = GamePromptLayer::create();
			  prompt->showPrompt(tips);
			  prompt->setCallBack([=](){
				  Reconnection::getInstance()->doLoginVipRoom(psd);
			  });
			  break;
	}
	case 2:
	{
			  GamePromptLayer::create()->showPrompt(GBKToUtf8("用户不存在!"));
			  _createRoomStruct.btn_createRoom->setTouchEnabled(true);
			  break;
	}

	case 3:
	{
			  GamePromptLayer::create()->showPrompt(GBKToUtf8("钱包钻石不足!"));
			  _createRoomStruct.btn_createRoom->setTouchEnabled(true);
			  break;
	}

	case 4:
	{
			  GamePromptLayer::create()->showPrompt(GBKToUtf8("购买钻石不合法!"));
			  _createRoomStruct.btn_createRoom->setTouchEnabled(true);
			  break;
	}

	case 5:
	{
			  GamePromptLayer::create()->showPrompt(GBKToUtf8("桌子已购买完!"));
			  _createRoomStruct.btn_createRoom->setTouchEnabled(true);
			  break;
	}

	case 6:
	{
			  if (GameCreator()->getCurrentGameNameID() == buyRoomResult->iGameNameID)
			  {
				  Reconnection::getInstance()->doLoginVipRoom(buyRoomResult->szPassWord);
			  }
			  else
			  {
				  auto info = GamesInfoModule()->getGameNameByGameID(buyRoomResult->iGameNameID);
				  if (!info) return true;
				  GameCreator()->setCurrentGame(buyRoomResult->iGameNameID);

				  std::string psd(buyRoomResult->szPassWord);
				  std::string tips = StringUtils::format(GBKToUtf8("您已在游戏:%s中【房号：%s】，确认进入"), GBKToUtf8(info->szGameName), buyRoomResult->szPassWord);

				  auto prompt = GamePromptLayer::create();
				  prompt->showPrompt(tips);
				  prompt->setCallBack([=](){
					  Reconnection::getInstance()->doLoginVipRoom(psd);
				  });
			  }
			  break;
	}
	}

	return true;
}

void CreateRoomLayer::getRoomConfiguration()
{
	// 创建桌子
	MSG_GP_S_VIP_DESK_CONFIG roomConfig;
	roomConfig.iUserID = PlatformLogic()->loginResult.dwUserID;
	//roomConfig.iGameID = GameCreator()->getCurrentGameNameID();

	PlatformLogic()->sendData(MDM_GP_DESK_VIP, ASS_GP_DESK_VIP_CONFIG,
		&roomConfig, sizeof(roomConfig), HN_SOCKET_CALLBACK(CreateRoomLayer::getRoomConfigurationEventSelector, this));
}

bool CreateRoomLayer::getRoomConfigurationEventSelector(HNSocketMessage* socketMessage)
{
	CCAssert(sizeof(MSG_GP_S_VIP_DESK_CONFIG_RES) == socketMessage->objectSize, "MSG_GP_S_VIP_DESK_CONFIG_RES is error.");
	MSG_GP_S_VIP_DESK_CONFIG_RES* roomConfig = (MSG_GP_S_VIP_DESK_CONFIG_RES*)socketMessage->object;

	_gameRoundVector.push_back(roomConfig->iGameCount[0]);
	_gameRoundVector.push_back(roomConfig->iGameCount[1]);

	_roomPrice.push_back(roomConfig->iJewels[0]);
	_roomPrice.push_back(roomConfig->iJewels[1]);

	char buffer[64] = { 0 };
	//sprintf(buffer, "%d局", _gameRoundVector.at(0));
	std::string str1 = StringUtils::format("%d", _gameRoundVector.at(0)) + "局";
	_createRoomStruct.txt_round1->setString(GBKToUtf8(str1.c_str()));

	std::string str2 = StringUtils::format("%d", _gameRoundVector.at(1)) + "局";
	//sprintf(buffer, "%d局", _gameRoundVector.at(1));
	_createRoomStruct.txt_round2->setString(GBKToUtf8(str2.c_str()));

	std::string str3 = "(消耗 " + StringUtils::format("%d", roomConfig->iJewels[0]) + "个钻石)";
	//sprintf(buffer, "(消耗 %d 个钻石)", roomConfig->iJewels[0]);
	_createRoomStruct.txt_prompt1->setString(GBKToUtf8(str3.c_str()));

	std::string str4 = "(消耗 " + StringUtils::format("%d", roomConfig->iJewels[1]) + "个钻石)";
	//sprintf(buffer, "(消耗 %d 个钻石)", roomConfig->iJewels[1]);
	_createRoomStruct.txt_prompt2->setString(GBKToUtf8(str4.c_str()));

	_createRoomStruct.btn_createRoom->setTouchEnabled(true);

	return true;
}

CreateRoomLayer::CreateRoomLayer()
{

}

CreateRoomLayer::~CreateRoomLayer()
{
}