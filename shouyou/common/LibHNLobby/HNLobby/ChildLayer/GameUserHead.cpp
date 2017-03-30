#include "GameUserHead.h"
#include <string>
//#include "network\HttpRequest.h"
#include "../GamePrompt.h"

using namespace network;

namespace HN
{

	GameUserHead* GameUserHead::create(const std::string& frame)
	{
		GameUserHead *pRet = new GameUserHead();
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

	GameUserHead* GameUserHead::create()
	{
		GameUserHead *pRet = new GameUserHead();
		if (pRet && pRet->init())
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

	GameUserHead::GameUserHead() : _userHead(nullptr)
	{
	}

	GameUserHead::~GameUserHead()
	{
		HNUserHeadHttpRequest::getInstance()->removeObserver(this);
	}

	void GameUserHead::setUserHead(const std::string& head)
	{
		_userHead = Sprite::create(head);
		_userHead->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
		addChild(_userHead, -1);
	}

	void GameUserHead::updateOwnUserHead(const std::string& headUrl, int userID)
	{
		if ("" == headUrl) return;

		updateGeneralUserHead(headUrl, _userHead, userID);
	}

	/*void GameUserHead::updateGeneralUserHead(const std::string& headUrl, Sprite* head, int userID)
	{
		if ("" == headUrl || nullptr == head) return;

		std::string spriteFrameName = StringUtils::format("%d_portrait", userID);
		auto spriteFrame_Head = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
		if (spriteFrame_Head)
		{
			if (spriteFrame_Head == head->getSpriteFrame()) return;

			auto spriteFrameSize = spriteFrame_Head->getOriginalSize();
			auto headSize = head->getContentSize();

			auto originalScale = head->getScale();
			auto adjustSize = (headSize.width / spriteFrameSize.width)*originalScale;
			head->setSpriteFrame(spriteFrame_Head);
			head->setScale(adjustSize);

			return;
		}

		_tempHeadSprite = head;
		_userID = userID;

		HNUserHeadHttpRequest::getInstance()->addObserver(this);

		char buffer[56] = { 0 };
		sprintf(buffer, "GetWeChatPortrait_%d", _userID);
		HNUserHeadHttpRequest::getInstance()->request(buffer, HttpRequest::Type::GET, headUrl);
	}*/

	void GameUserHead::updateGeneralUserHead(const std::string& headUrl, Sprite* head, int userID)
	{
		if ("" == headUrl || nullptr == head)
		{
			head->removeFromParent();
			return;
		}

		//head->setTag(userID);

		std::string spriteFrameName = StringUtils::format("%d_portrait", userID);
		auto spriteFrame_Head = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
		if (spriteFrame_Head)
		{
			if (spriteFrame_Head == head->getSpriteFrame() && -1 != head->getTag()) return;

			log("spriteFrame_Head2");

			auto spriteFrameSize = spriteFrame_Head->getOriginalSize();
			auto headSize = head->getContentSize();

			auto originalScale = head->getScale();
			float adjustSizeX = (headSize.width / spriteFrameSize.width)*head->getScaleX();
			float adjustSizeY = (headSize.height / spriteFrameSize.height)*head->getScaleY();
			head->setSpriteFrame(spriteFrame_Head);
			head->setScaleX(adjustSizeX);
			head->setScaleY(adjustSizeY);
			head->setVisible(true);

			

			return;
		}

		log("spriteFrame_Head3");

		//head->setTag(0);
		_tempHeadSprite = head;
		_userID = userID;

		HNUserHeadHttpRequest::getInstance()->addObserver(this);

		char buffer[56] = { 0 };
		sprintf(buffer, "GetWeChatPortrait_%d", _userID);
		HNUserHeadHttpRequest::getInstance()->request(buffer, HttpRequest::Type::GET, headUrl);
	}

	bool GameUserHead::initWithImage(const std::string& frame)
	{
		if (!HNSprite::init())
		{
			return false;
		}
		this->initWithFile(frame);

		// 创建一个点击事件
		auto MyListener = EventListenerTouchOneByOne::create();
		MyListener->setSwallowTouches(true);

		MyListener->onTouchBegan = CC_CALLBACK_2(GameUserHead::onTouchBegan, this);
		MyListener->onTouchEnded = CC_CALLBACK_2(GameUserHead::onTouchEnd, this);

		_eventDispatcher->addEventListenerWithSceneGraphPriority(MyListener, this);

		return true;
	}

	bool GameUserHead::onTouchBegan(Touch* touch, Event* event)
	{
		if (!isVisible())
		{
			return false;
		}
		auto target = static_cast<GameUserHead*>(event->getCurrentTarget());
		Vec2 touchVec = touch->getLocation();
		Point locationInNode = target->convertToNodeSpace(touchVec);
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		// 判断触摸点是否在目标的范围内
		if (rect.containsPoint(locationInNode))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void GameUserHead::onTouchEnd(Touch* touch, Event* event)
	{
		auto target = static_cast<GameUserHead*>(event->getCurrentTarget());
		Vec2 touchVec = touch->getLocation();
		Point locationInNode = target->convertToNodeSpace(touchVec);
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		// 判断触摸点是否在目标的范围内
		if (rect.containsPoint(locationInNode))
		{
			onHeadClickEvent(target, touchVec);
		}
	}

	//void GameUserHead::onHttpResponse(const std::string& requestName, bool isSucceed, std::vector<char> &responseData)
	//{
	//	char buffer[56] = { 0 };
	//	sprintf(buffer, "GetWeChatPortrait_%d", _userID);

	//	if (requestName.compare(buffer) == 0)
	//	{
	//		if (!isSucceed)
	//		{
	//			GamePromptLayer::create()->showPrompt(GBKToUtf8("头像查询失败！"));
	//			return;
	//		}

	//		//create image
	//		Image* image = new Image;
	//		image->initWithImageData((unsigned char*)responseData.data(), responseData.size());

	//		//create texture
	//		auto texture = new Texture2D();
	//		bool isImage = texture->initWithImage(image);

	//		if (!isImage){
	//			log("Texture2D init fail!");
	//			return;
	//		}
	//		image->release();

	//		auto textureSize = texture->getContentSize();
	//		Rect rect = Rect(0, 0, textureSize.width, textureSize.height);

	//		std::string spriteFrameName = StringUtils::format("%d_portrait", _userID);
	//		auto spriteFrame = SpriteFrame::createWithTexture(texture, rect);
	//		SpriteFrameCache::getInstance()->addSpriteFrame(spriteFrame, spriteFrameName);
	//		spriteFrame->retain();

	//		if (spriteFrame == _tempHeadSprite->getSpriteFrame()) return;

	//		Size size = _tempHeadSprite->getContentSize();
	//		auto originalScale = _tempHeadSprite->getScale();
	//		float adjustScale = (size.width / textureSize.width)*originalScale;

	//		_tempHeadSprite->setSpriteFrame(spriteFrame);
	//		_tempHeadSprite->setScale(adjustScale);
	//	}
	//}

	void GameUserHead::onHttpResponse(const std::string& requestName, bool isSucceed, std::vector<char> &responseData)
	{
		char buffer[56] = { 0 };
		sprintf(buffer, "GetWeChatPortrait_%d", _userID);

		if (requestName.compare(buffer) == 0)
		{
			if (!isSucceed)
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8("头像查询失败！"));
				return;
			}

			//create image
			Image* image = new Image;
			image->initWithImageData((unsigned char*)responseData.data(), responseData.size());

			//create texture
			auto texture = new Texture2D();
			bool isImage = texture->initWithImage(image);

			if (!isImage){
				log("Texture2D init fail!");
				return;
			}
			image->release();

			auto textureSize = texture->getContentSize();
			Rect rect = Rect(0, 0, textureSize.width, textureSize.height);

			std::string spriteFrameName = StringUtils::format("%d_portrait", _userID);
			auto spriteFrame = SpriteFrame::createWithTexture(texture, rect);
			SpriteFrameCache::getInstance()->addSpriteFrame(spriteFrame, spriteFrameName);
			spriteFrame->retain();

			_tempHeadSprite->setVisible(true);

			if (spriteFrame == _tempHeadSprite->getSpriteFrame()) return;

			Size size = _tempHeadSprite->getContentSize();
			auto originalScale = _tempHeadSprite->getScale();
			//float adjustScale = (size.width / textureSize.width)*originalScale;

			float adjustSizeX = (size.width / textureSize.width)*_tempHeadSprite->getScaleX();
			float adjustSizeY = (size.height / textureSize.height)*_tempHeadSprite->getScaleY();

			_tempHeadSprite->setSpriteFrame(spriteFrame);
			_tempHeadSprite->setScale(adjustSizeX, adjustSizeY);
		}
	}
}