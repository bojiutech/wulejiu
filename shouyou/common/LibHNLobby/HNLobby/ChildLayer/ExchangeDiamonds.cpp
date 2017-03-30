#include "HNLobby/ChildLayer/ExchangeDiamonds.h"
#include "HNLobby/ChildLayer/GameStoreLayer.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include <string>
#include "../GamePrompt.h"

static const char* EXCHANGE_DIAMONDS_CSB	= "platform/store/exchangeDiamonds.csb";

#define JSON_RESOVE(obj, key) (obj.HasMember(key) && !obj[key].IsNull())

ExchangeDiamonds* ExchangeDiamonds::createExchangeMoneyLayer()
{
	ExchangeDiamonds *pRet = new ExchangeDiamonds();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return pRet;
}

ExchangeDiamonds::ExchangeDiamonds() : _exchangeRate(0)
{
	
}

ExchangeDiamonds::~ExchangeDiamonds()
{
}

bool ExchangeDiamonds::init()
{
	if (!HNLayer::init()) return false;
	//屏蔽后面的层
	auto colorLayer = LayerColor::create(Color4B(0, 0, 0, 100));
	addChild(colorLayer, 1);

	_exchangeDiamondsUI.exchangeDiamondsNode = CSLoader::createNode(EXCHANGE_DIAMONDS_CSB);
	addChild(_exchangeDiamondsUI.exchangeDiamondsNode, 2);
	_exchangeDiamondsUI.exchangeDiamondsLayout = (Layout*)_exchangeDiamondsUI.exchangeDiamondsNode->getChildByName("Panel_1");
	
	//兑换金币输入框
	_exchangeDiamondsUI.txtField_number = dynamic_cast<TextField*>(_exchangeDiamondsUI.exchangeDiamondsLayout->getChildByName("txtField_number"));
	_exchangeDiamondsUI.txtField_number->setVisible(false);
	_exchangeDiamondsUI._txtField = HNEditBox::createEditBox(_exchangeDiamondsUI.txtField_number, this);
	_exchangeDiamondsUI._txtField->setText("");
	_exchangeDiamondsUI._txtField->setFontColor(Color3B(255, 0, 0));
	//editBoxUserName->setString("");
	
	//兑换金币按钮
	_exchangeDiamondsUI.btn_exchange = (Button*)_exchangeDiamondsUI.exchangeDiamondsLayout->getChildByName("btn_exchange");
	_exchangeDiamondsUI.btn_exchange->addTouchEventListener(CC_CALLBACK_2(ExchangeDiamonds::buttonEventCallBack, this));
	_exchangeDiamondsUI.btn_exchange->setVisible(false);

	auto bgRect = _exchangeDiamondsUI.exchangeDiamondsLayout->getBoundingBox();

	//创建一个点击事件
	auto MyListener = EventListenerTouchOneByOne::create();
	MyListener->setSwallowTouches(true);//阻止触摸向下传递
	MyListener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		// 获取的当前触摸的目标
		auto target = dynamic_cast<ExchangeDiamonds*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode))
		{
			if (bgRect.containsPoint(locationInNode)) return true;
			closeExchangeMoneyUI();
			return true;
		}
		else
		{
			return false;
		}
	};
	//把点击监听添加到监听序列中,因为只创建了一个监听,一个监听只能绑定到一个对象上,所以其他对象要使用监听则克隆
	_eventDispatcher->addEventListenerWithSceneGraphPriority(MyListener, this);

	return true;
}

void ExchangeDiamonds::showExchangeMoneyUI(Node* parent, Vec2 vec, int zorder, int tag)
{
	_exchangeDiamondsUI.exchangeDiamondsNode->setPosition(Vec2(vec.x, vec.y));
	auto winSize = Director::getInstance()->getWinSize();
	parent->addChild(this, zorder, tag);
}

void ExchangeDiamonds::closeExchangeMoneyUI()
{
	_exchangeDiamondsUI.exchangeDiamondsNode->runAction(Sequence::create(ScaleTo::create(0.1f, 0.3f), CCCallFunc::create([&]()
	{
		this->removeFromParent();
	}), nullptr));

}

void ExchangeDiamonds::setBGPositon(Vec2 vec)
{
	_exchangeDiamondsUI.exchangeDiamondsNode->setPosition(Vec2(vec.x, vec.y - 100));
}

void ExchangeDiamonds::buttonEventCallBack(Ref* pSender, Widget::TouchEventType type)
{
	if (Widget::TouchEventType::ENDED != type) return;

	MSG_GP_S_MONEY_TO_JEWEL moneyToJewel;
	moneyToJewel.i64Money = atoi(_exchangeDiamondsUI._txtField->getString().c_str()) * 5000;
	moneyToJewel.iUserID = PlatformLogic()->loginResult.dwUserID;

	PlatformLogic()->sendData(MDM_GP_DESK_VIP, ASS_GP_MONEY_TO_DIAMOND, ASS_GP_MONEY_TO_DIAMOND,
		&moneyToJewel, sizeof(moneyToJewel), HN_SOCKET_CALLBACK(ExchangeDiamonds::exchangeDiamondsCallBack, this));
}

bool  ExchangeDiamonds::exchangeDiamondsCallBack(HNSocketMessage* socketMessage)
{
	CCAssert(sizeof(MSG_GP_S_MONEY_TO_JEWEL_RES) == socketMessage->objectSize, "MSG_GP_S_VIP_DESK_CONFIG_RES is error.");
	MSG_GP_S_MONEY_TO_JEWEL_RES* exchangeResult = (MSG_GP_S_MONEY_TO_JEWEL_RES*)socketMessage->object;

	//(0:未知异常；1：兑换成功;2：用户不存在；3：金币不足)
	auto consumeMoney = exchangeResult->i64Money;
	auto getDiamonds = exchangeResult->iJewels;
	switch (exchangeResult->iResult)
	{
	case 0:
		GamePromptLayer::create()->showPrompt(GBKToUtf8("未知异常，请检查输入数量是否合法！"));
		break;
	case 1:
	{
			  auto promptMessage = StringUtils::format("兑换成功！获得%d, 消耗金币%d。", getDiamonds, consumeMoney);
			  GamePromptLayer::create()->showPrompt(GBKToUtf8(promptMessage.c_str()));
	}
		break;
	case 2:
		GamePromptLayer::create()->showPrompt(GBKToUtf8("用户不存在！"));
		break;
	case 3:
		GamePromptLayer::create()->showPrompt(GBKToUtf8("金币不足！"));
		break;
	default:
		break;
	}

	return true;
}

void ExchangeDiamonds::updateExchangeMoney()
{
	//LLONG points = PlatformLogic()->loginResult.i64Bonus;
	//
	//if (0 == _exchangeRate) return;
	//
	//LLONG exchangeMoney = (LLONG)(points / _exchangeRate);
	//_exchangeDiamondsUI.txtField_number->setString(StringUtils::format("%ld", exchangeMoney));
}

void ExchangeDiamonds::setChangeDelegate(MoneyChangeNotify* delegate)
{
	_delegate = delegate;
}
