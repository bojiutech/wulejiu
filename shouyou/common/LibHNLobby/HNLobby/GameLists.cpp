#include "HNLobby/GameLists.h"
#include "HNLobby/FontConfig.h"
#include "HNLobby/PlatformDefine.h"
#include "HNLobby/GameDesk.h"
#include "HNLobby/GamePrompt.h"
#include "HNLobby/GameRoom.h"
#include "HNLobby/CreateRoom/SelectRoomLayer.h"
#include <string>

//////////////////////////////////////////////////////////////////////////
static const float enter_room_outtime_timer_time = 30.0f;
//////////////////////////////////////////////////////////////////////////
static const char* request_room_list_text = "��ȡ�����б�......";
static const char* game_dev_text		  = "��Ϸ���ڿ����С�";
//////////////////////////////////////////////////////////////////////////
static const char* GAME_ITEM_UI	= "platform/gameList/gameItem.csb";
static const char* GAME_NAME_FNT = "platform/fonts/gameName.fnt";

static const char* GAME_PAGESPROMPT_PATH = "platform/gameList/gameItemRes/page_Prompt.png";

static const Size pageViewGamesSize(1280, 500);

GameLists::GameLists()
	: _pageViewGames (nullptr)
	, _currentSelectedGame (nullptr)
	, _currentPageIdx (0)
	, _isTouch (true)
{

}

GameLists::~GameLists()
{

}

bool GameLists::init()
{
    if (!HNLayer::init())
    {
        return false;
    }

	this->setCascadeOpacityEnabled(true);

	createGameList();

    return true;
}

void GameLists::onEnter()
{
	HNLayer::onEnter();
}

void GameLists::onExit()
{
	HNLayer::onExit();
}

void GameLists::createGameList()
{
	Size winSize = Director::getInstance()->getWinSize();

	_pageViewGames = PageView::create();
	_pageViewGames->setContentSize(pageViewGamesSize);
	_pageViewGames->setAnchorPoint(Vec2(0.5f, 0.5f));
	_pageViewGames->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
	_pageViewGames->setTouchEnabled(true);
	_pageViewGames->setCustomScrollThreshold(15);
	_pageViewGames->setCascadeOpacityEnabled(true);

	addChild(_pageViewGames, 4, 4);

	std::vector<ComNameInfo*> gameNames = GameCreator()->getValidGames();

	int gameAllCount = gameNames.size();

	int currentIndex = 0; 

	int pageCount = (gameAllCount / 4);
	int remainder = (gameAllCount % 4);

	int pageLen = (remainder == 0) ? pageCount : pageCount + 1;
	int central = -pageLen / 2;
	if (abs(central) > 0)
	{
		for (int i = 0; i < pageLen; i++)
		{
			auto page = Sprite::create(GAME_PAGESPROMPT_PATH);
			addChild(page);
			_pagesPrompt.push_back(page);

			page->setPosition(Vec2(winSize.width / 2 + central * 25, winSize.height * 0.16f));
			if (i > 0)
			{
				page->setScale(0.8f);
				page->setColor(Color3B(150, 150, 150));
			}
			central++;
		}
	}

	std::vector<ComNameInfo*> pages;

	if (pageCount > 0)
	{
		for (int currentPage  = 0; currentPage < pageCount; currentPage++)
		{
			pages.clear();
			for (int room = 0; room < 4; room ++, currentIndex ++)
			{
				ComNameInfo* roomInfo = gameNames[currentIndex];
				pages.push_back(roomInfo);
			}
			createGamePage(pages);
		}
	}

	if (remainder > 0)
	{
		pages.clear();
		for (int room = 0; room < remainder; room ++, currentIndex ++)
		{
			ComNameInfo* roomInfo = gameNames[currentIndex];
			pages.push_back(roomInfo);
		}
		createGamePage(pages);
	}

	auto userDefault = UserDefault::getInstance();
	_currentPageIdx = userDefault->getIntegerForKey("gamePageIdx", 0);
	_pageViewGames->scrollToPage(_currentPageIdx);

	auto iter = _pagesPrompt.begin();
	for (int i = 0; iter != _pagesPrompt.end(); iter++, i++)
	{
		auto page = (Sprite*)*iter;
		page->setColor(Color3B(150, 150, 150));
		page->setScale(0.8f);
		if (i == _currentPageIdx)
		{
			page->setScale(1.0f);
			page->setColor(Color3B(255, 255, 255));
		}
	}
}

//�����Ϸ
void GameLists::createGamePage(std::vector<ComNameInfo*> games)
{
	// ������Ϸ�б���ҳ��
	auto gameLayout = Layout::create();
	gameLayout->setName("page");
	gameLayout->setContentSize(pageViewGamesSize);

	gameLayout->setCascadeOpacityEnabled(true);

	int idx = 0;
	for (auto game : games)
	{
		idx++;
		float posX = -0.1f + idx * 0.24f;

		auto gameItem = createGameItem(game);
		auto gameButton = (Button*)gameItem->getChildByName("Button_gameItem");
		gameButton->removeFromParentAndCleanup(false);
		gameButton->setPosition(Vec2(gameLayout->getContentSize().width * posX, gameLayout->getContentSize().height * 0.5f));
		gameLayout->addChild(gameButton, 3, idx);
	}
	
	//�����ҳ������б���
	_pageViewGames->addPage(gameLayout);

	//�϶�����
	_pageViewGames->addEventListener(PageView::ccPageViewCallback(CC_CALLBACK_2(GameLists::pageViewMoveCallBack, this)));
}

Node* GameLists::createGameItem(ComNameInfo* game)
{
	auto gameItemNode = CSLoader::createNode(GAME_ITEM_UI);
	gameItemNode->setCascadeOpacityEnabled(true);

	auto gameButton = (Button*)gameItemNode->getChildByName("Button_gameItem");
	gameButton->setUserData(game);
	gameButton->addTouchEventListener(CC_CALLBACK_2(GameLists::enterRoomEventCallBack, this));

	char str[128];
	// ��Ϸ
	auto Image_Ico = (ImageView*)Helper::seekWidgetByName(gameButton, "Image_Ico");
	sprintf(str, "platform/gameList/gameItemRes/%d.png", game->uNameID);
	if (FileUtils::getInstance()->isFileExist(str))
	{
		Image_Ico->loadTexture(str);
	}

	// ��Ϸ����
	auto Text_name = (Text*)Helper::seekWidgetByName(gameButton, "Text_name");
	sprintf(str, "%s", game->szGameName);
	Text_name->setString(GBKToUtf8(str));

	// ��Ϸ����
	auto Text_online = (Text*)Helper::seekWidgetByName(gameButton, "Text_online");
	sprintf(str, GBKToUtf8("%d��"), game->m_uOnLineCount);
	Text_online->setString(str);

	return gameItemNode;
}

void GameLists::pageViewMoveCallBack(Ref* pSender, PageView::EventType type)
{
	if (_currentPageIdx == _pageViewGames->getCurPageIndex()) return;
	_currentPageIdx = _pageViewGames->getCurPageIndex();

	auto userDefault = UserDefault::getInstance();
	userDefault->setIntegerForKey("gamePageIdx", _currentPageIdx);
	userDefault->flush();

	auto iter = _pagesPrompt.begin();
	for (int i = 0; iter != _pagesPrompt.end(); iter++, i++)
	{
		auto page = (Sprite*)*iter;
		page->setColor(Color3B(150, 150, 150));
		page->setScale(0.8f);
		if (i == _currentPageIdx)
		{
			page->setScale(1.0f);
			page->setColor(Color3B(255, 255, 255));
		}
	}
}

//��ҳ�水ť�ص�
void GameLists::enterRoomEventCallBack(Ref* pSender, Widget::TouchEventType type)
{
	if (_isTouch == false) return;

	_currentSelectedGame = dynamic_cast<Button*>(pSender);

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		_currentSelectedGame->runAction(ScaleTo::create(0.2f, 1.1f));
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			_isTouch = false;

			HNAudioEngine::getInstance()->playEffect(GAME_SOUND_BUTTON);
			_currentSelectedGame->runAction(ScaleTo::create(0.2f, 1.0f));

			Size winSize = Director::getInstance()->getWinSize();

			ComNameInfo* game = static_cast<ComNameInfo*>(_currentSelectedGame->getUserData());

			// ����У��
			CCAssert(nullptr != game, "game is nullptr!");
			if (nullptr == game) 
			{
				_isTouch = true;
				return;
			}			

			GameCreator()->setCurrentGame(game->uNameID);

			// ֻ�а����齫�д�������
			if (20116004 == game->uNameID)
			{
				SelectRoomLayer* selectRoomLayer = SelectRoomLayer::create();
				this->addChild(selectRoomLayer, 10);
				auto gameName = StringUtils::format("%s", game->szGameName);
				selectRoomLayer->setSelectedGameName(gameName);
				selectRoomLayer->setPosition(Vec2(winSize.width / 2, winSize.height / 2));

				_isTouch = true;

				return;
			}

			enterRoomAction();
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		_currentSelectedGame->runAction(ScaleTo::create(0.2f, 1.0f));
		break;
	default:
		break;
	}
}

//�б�ť�����Ķ���
void GameLists::enterRoomAction()
{
	if (nullptr != onRunActionCallBack)
	{
		onRunActionCallBack();
	}

	this->runAction(Sequence::create(FadeOut::create(0.3f), CallFunc::create([&](){
		if (nullptr != onEnterGameCallBack)
		{
			onEnterGameCallBack();
		}
		_isTouch = true;
		this->removeFromParent();
	}), nullptr));
}

//������Ϸ����
void GameLists::updateGamePeopleCount(UINT Id, UINT count)
{
	Vector<Layout*> pages = _pageViewGames->getPages();

	char buffer[64];
	for (auto iter = pages.begin(); iter != pages.end(); ++iter)
	{
		Vector<Node*> childs = (*iter)->getChildren();
		for (auto iter1 = childs.begin(); iter1 != childs.end(); ++iter1)
		{
			auto gameButton = dynamic_cast<Button*>(*iter1);
			auto TextBMFont_PeopleCount = (Text*)Helper::seekWidgetByName(gameButton, "Text_online");

			if (nullptr != gameButton)
			{
				ComNameInfo* names = static_cast<ComNameInfo*>(gameButton->getUserData());

				if (names->uNameID == Id)
				{
					if (nullptr != TextBMFont_PeopleCount)
					{
						sprintf(buffer, GBKToUtf8("%d��"), count);

						std::string str = StringUtils::format("%d", count) + "��";
						TextBMFont_PeopleCount->setString(GBKToUtf8(str));
					}
				}
			}
		}
	}
}

