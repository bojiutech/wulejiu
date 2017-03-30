#include "HNCalculateBoard.h"
#include <string>
#include "cocostudio/ActionTimeline/CSLoader.h"

USING_NS_CC;
using namespace ui;
using namespace HN;
using namespace cocostudio;

static const int CALCULATE_LAYER_ZORDER		= 100000000;		// 子节点弹出框层级

static const int CALCULATE_LAYER_TAG		= 100000000;		// 子节点弹出框层级

HNCalculateBoard::HNCalculateBoard() 
	: _calculateBoardNode(nullptr)
	, _calculateBoardLayout(nullptr)
	, _btn_confirm(nullptr)
	, _btn_share(nullptr)
	, _btn_back(nullptr)
{
}

HNCalculateBoard::~HNCalculateBoard()
{

}

void HNCalculateBoard::showBoard()
{
	Node* root = Director::getInstance()->getRunningScene();
	CCAssert(nullptr != root, "root is null");

	root->addChild(this, CALCULATE_LAYER_ZORDER, CALCULATE_LAYER_TAG);
	this->setVisible(true);
}

void HNCalculateBoard::close()
{
	_calculateBoardNode->runAction(Sequence::create(ScaleTo::create(0.1f, 0.3f), CCCallFunc::create([&]()
	{
		this->removeFromParent();
	}), nullptr));
}

bool HNCalculateBoard::init()
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
	
	return true;
}

void HNCalculateBoard::confirmBtnCallBack(Ref* pSender, Widget::TouchEventType type)
{
	//for override 
}

void HNCalculateBoard::shareBtnCallBack(Ref* pSender, Widget::TouchEventType type)
{
	//for override 
}

void HNCalculateBoard::backBtnCallBack(Ref* pSender, Widget::TouchEventType type)
{
	//for override 
}

void HNCalculateBoard::showAndUpdateBoard()
{
	// for override
}

void HNCalculateBoard::updateUserHead(int userId, int logoID, const std::string& headUrl, Sprite* headSprite)
{
	// for override 
}
