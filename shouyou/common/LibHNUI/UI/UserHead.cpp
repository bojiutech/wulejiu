#include "UserHead.h"
#include <string>

namespace HN
{

	UserHead* UserHead::create(const std::string& frame)
	{
		UserHead *pRet = new UserHead();
		if (pRet && pRet->initWithImage(frame))
		{ 
			pRet->autorelease(); 
			return pRet; 
		} 
		else 
		{ 
			delete pRet; 
			pRet = nullptr; 
			return nullptr; 
		} 
	}

	UserHead::UserHead() : _userHead(nullptr)
	{

	}

	UserHead::~UserHead()
	{

	}

	void UserHead::setUserHead(const std::string& head)
	{
		_userHead = Sprite::create(head);
		_userHead->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
		addChild(_userHead, -1);
	}

	bool UserHead::initWithImage(const std::string& frame)
	{
		if ( !HNSprite::init())
		{
			return false;
		}
		this->initWithFile(frame);

		// ����һ������¼�
		auto MyListener = EventListenerTouchOneByOne::create();
		MyListener->setSwallowTouches(true);

		MyListener->onTouchBegan = CC_CALLBACK_2(UserHead::onTouchBegan, this);
		MyListener->onTouchEnded = CC_CALLBACK_2(UserHead::onTouchEnd, this);

		_eventDispatcher->addEventListenerWithSceneGraphPriority(MyListener, this);

		return true;
	}

	bool UserHead::onTouchBegan(Touch* touch, Event* event)
	{
		if(!isVisible())
		{
			return false;
		}
		auto target = static_cast<UserHead*>(event->getCurrentTarget());
		Vec2 touchVec = touch->getLocation();
		Point locationInNode = target->convertToNodeSpace(touchVec);
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		// �жϴ������Ƿ���Ŀ��ķ�Χ��
		if (rect.containsPoint(locationInNode))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void UserHead::onTouchEnd(Touch* touch, Event* event)
	{
		auto target = static_cast<UserHead*>(event->getCurrentTarget());
		Vec2 touchVec = touch->getLocation();
		Point locationInNode = target->convertToNodeSpace(touchVec);
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		// �жϴ������Ƿ���Ŀ��ķ�Χ��
		if (rect.containsPoint(locationInNode))
		{
			onHeadClickEvent(target, touchVec);
		}
	}
}