#include "HNExitPrompt.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

namespace HN
{
	static const char* EXIT_BG = "platform/exitUi/exit_bg_1.png";
	static const char* EXIT_CANCEL_N = "platform/exitUi/exit_cancel_n.png";
	static const char* EXIT_CANCEL_D = "platform/exitUi/exit_cancel_d.png";
	static const char* EXIT_OK_N = "platform/exitUi/exit_ok_n.png";
	static const char* EXIT_OK_D = "platform/exitUi/exit_ok_d.png";

	//////////////////////////////////////////////////////////////////////////

	HNExitPromptLayer::HNExitPromptLayer() : _onExit(nullptr)
	{

	}

	HNExitPromptLayer::~HNExitPromptLayer()
	{

	}

	void HNExitPromptLayer::setExitCallBack(const std::function<void ()>& onExit)
	{
		_onExit = onExit;
	}

	bool HNExitPromptLayer::init()
	{
		if (!HNLayer::init())
		{
			return false;
		}

		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = [&](Touch* touch, Event* event)
		{
			return true;
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

		quicklyShade(150);

		Size winSize = Director::getInstance()->getWinSize();

		Sprite* bg = Sprite::create(EXIT_BG);
		bg->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
		bg->setAnchorPoint(Vec2(0.5f, 0.5f));
		this->addChild(bg, 2);
		
		Button* exitOk = Button::create(EXIT_OK_N, EXIT_OK_D);
		exitOk->setPosition(Vec2(bg->getContentSize().width * 0.25f, exitOk->getContentSize().height));
		exitOk->setAnchorPoint(Vec2(0.5f, 0.5f));
		exitOk->addTouchEventListener(CC_CALLBACK_2(HNExitPromptLayer::onExitCallBack, this));
		bg->addChild(exitOk);

		Button* exitCancel = Button::create(EXIT_CANCEL_N, EXIT_CANCEL_D);
		exitCancel->setPosition(Vec2(bg->getContentSize().width * 0.75f, exitCancel->getContentSize().height));
		exitCancel->setAnchorPoint(Vec2(0.5f, 0.5f));
		exitCancel->addTouchEventListener(CC_CALLBACK_2(HNExitPromptLayer::onCancelCallBack, this));
		bg->addChild(exitCancel);

		return true;
	}

	void HNExitPromptLayer::onExitCallBack(Ref* pSender, Widget::TouchEventType type)
	{
		if (Widget::TouchEventType::ENDED != type) return;
		
		if(nullptr != _onExit)
		{
			_onExit();
		}
	}

	void HNExitPromptLayer::onCancelCallBack(Ref* pSender, Widget::TouchEventType type)
	{
		if (Widget::TouchEventType::ENDED != type) return;

		this->runAction(RemoveSelf::create());
	}
}
