#include "Cherry97GameBet.h"
#include "HNLobbyExport.h"

using namespace ui;

namespace Cherry97
{
	static const char* BET_CSB	=    "Cherry97/Cherry97Ui/BetTableNode.csb";    //±¶ÂÊ
	GameBet* GameBet::create()
	{
		GameBet* ref = new GameBet();
		if(ref->init())
		{
			ref->autorelease();
			return ref;
		}
		CC_SAFE_DELETE(ref);
		return nullptr;
	}

	bool GameBet::init()
	{
		if(!HN::HNLayer::init())
		{
			return false;
		}
		winsize = Director::getInstance()->getWinSize();

		_loader = CSLoader::createNode(BET_CSB);
		addChild(_loader);
		_layout = (Layout* ) _loader->getChildByName("Panel_1");
		_layout->setScaleY(winsize.height / _layout->getContentSize().height	);
		_btnClose = (Button* ) _layout->getChildByName("Button_close");
		_btnClose->addTouchEventListener(CC_CALLBACK_2(GameBet::btnCallBack,this));

		return true;
	}

	void GameBet::btnCallBack(cocos2d::Ref* pSender, ui::Widget::TouchEventType touchtype)
	{
		if (Widget::TouchEventType::ENDED != touchtype)	return;
		Button* btn = (Button* ) pSender;
		if (btn == _btnClose)
		{
			_layout->runAction(Sequence::create(ScaleTo::create(0.3f, 0.1f), CallFunc::create([=](){
				_loader->removeFromParent();
			}), nullptr));
		}
	}

	GameBet::GameBet()
	{
	}

	GameBet::~GameBet()
	{
	}
}

