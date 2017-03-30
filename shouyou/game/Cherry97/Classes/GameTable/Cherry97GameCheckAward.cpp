#include "Cherry97GameCheckAward.h"
#include "HNLobbyExport.h"

using namespace ui;

namespace Cherry97
{
	static const char* CHECKAWARD_CSB	=    "Cherry97/Cherry97Ui/CheckPrizeNode.csb";    //查看大奖界面
	GameCheckAward* GameCheckAward::create(GameTableUICallback* uicallback)
	{
		GameCheckAward* ref = new GameCheckAward();
		if(ref->init(uicallback))
		{
			ref->autorelease();
			return ref;
		}
		CC_SAFE_DELETE(ref);
		return nullptr;
	}

	bool GameCheckAward::init(GameTableUICallback* uicallback)
	{
		if(!HN::HNLayer::init())
		{
			return false;
		}
		_uicallback = uicallback;
		winsize = Director::getInstance()->getWinSize();
		//屏蔽后面的层
		_colorLayer = LayerColor::create(Color4B(0, 0, 0, 0));
		addChild(_colorLayer);

		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan = [=](Touch* touch ,Event* event){
			return true;
		};
		touchListener->setSwallowTouches(true);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,_colorLayer);

		_loader = CSLoader::createNode(CHECKAWARD_CSB);
		addChild(_loader);
		_layout = (Layout* ) _loader->getChildByName("Panel_1");
		_layout->setScaleY(winsize.height / _layout->getContentSize().height	);
		//退出
		_btnClose = (Button* ) _layout->getChildByName("Button_close");
		_btnClose->addTouchEventListener(CC_CALLBACK_2(GameCheckAward::btnCallBack,this));
		//上一页，下一页按钮
		_btnLastPage = (Button* ) _layout->getChildByName("Button_lastPage");
		_btnLastPage->addTouchEventListener(CC_CALLBACK_2(GameCheckAward::btnCallBack,this));
		_btnNextPage = (Button* ) _layout->getChildByName("Button_nextPage");
		_btnNextPage->addTouchEventListener(CC_CALLBACK_2(GameCheckAward::btnCallBack,this));
		//数据文本
		char str[32];
		for (int i = 0; i < 18; i++)
		{
			sprintf(str, "Text_all_%d", i);
			_award[i] = (Text* ) _layout->getChildByName(str);
		}

		return true;
	}

	void GameCheckAward::btnCallBack(cocos2d::Ref* pSender, ui::Widget::TouchEventType touchtype)
	{
		if (Widget::TouchEventType::ENDED != touchtype)	return;
		Button* btn = (Button* ) pSender;
		if (btn == _btnClose)
		{
			_layout->runAction(Sequence::create(ScaleTo::create(0.3f, 0.1f), CallFunc::create([=](){
				_layout->removeFromParent();
				_colorLayer->removeFromParent();
			}), nullptr));
		}
		if (btn == _btnLastPage)
		{
			//在这个界面点上一页不需要处理，因为现在就是在第一页
		}
		if (btn == _btnNextPage)
		{
			//发送请求下一页数据的消息
			_uicallback->sendNextPageReq();
		}
	}

	void GameCheckAward::setAwardInfo(int award[18])
	{
		for (int i = 0; i < 18; i++)
		{
			_award[i]->setString(String::createWithFormat("%d", award[i])->getCString());
		}
	}

	GameCheckAward::GameCheckAward()
	{
	}

	GameCheckAward::~GameCheckAward()
	{
	}
}

