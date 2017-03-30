#include "HNLobby/GameDesk.h"
#include "HNLobby/FontConfig.h"
#include "HNLobby/PlatformDefine.h"
#include "HNLobby/GamePrompt.h"
#include "HNLobby/ChildLayer/GamePasswordInput.h"
#include "HNUIExport.h"
#include "Reconnection/Reconnection.h"

//////////////////////////////////////////////////////////////////////////
static const char* DESK_ITEM_UI = "platform/DeskList/deskListUi.csb";

static const char* GAME_PAGESPROMPT_PATH = "platform/gameList/gameItemRes/page_Prompt.png";


static const Size pageViewDesksSize(1280, 500);

//////////////////////////////////////////////////////////////////////////

GameDesk* GameDesk::createDesk(ComRoomInfo* roomInfo)
{
	GameDesk* deskList = new GameDesk();
	if (deskList->initData(roomInfo))
	{
		deskList->autorelease();
		return deskList;
	}
	else
	{
		CC_SAFE_DELETE(deskList);
		return nullptr;
	}
}

GameDesk::GameDesk() 
	: _currentSelectedDesk(nullptr)
	, _deskNO (0)
	, _pageLen (0)
	, _canCreate (true)
	, _pageEven (false)
	, _currentPageIdx (0)
	, _isTouch (true)
{
	_deskLogic = new HNRoomDeskLogic(this);
	_deskLogic->start();
}

GameDesk::~GameDesk()
{
	_deskLogic->stop();
	HN_SAFE_DELETE(_deskLogic);

	for (auto desk : _deskinfos)
	{
		HN_SAFE_DELETE(desk);
	}
}

void GameDesk::closeDeskList()
{
	_deskLogic->stop();
	RoomLogic()->close();
	this->runAction(Sequence::create(FadeOut::create(0.5f), CallFunc::create([&](){
		if (nullptr != onCloseCallBack)
		{
			PlatformConfig::getInstance()->setSceneState(PlatformConfig::SCENE_STATE::INPLATFORM);
			onCloseCallBack();
		}
		this->removeFromParent();
	}), nullptr));
}

void GameDesk::onEnterPasswordCallback(const std::string& password)
{
	DeskInfo* deskInfo = static_cast<DeskInfo*>(_currentSelectedDesk->getUserData());
	_deskLogic->requestSit(deskInfo->deskID, password);
}

bool GameDesk::initData(ComRoomInfo* roomInfo)
{
	if (!HNLayer::init()) return false;

	PlatformConfig::getInstance()->setSceneState(PlatformConfig::SCENE_STATE::INROOM);

	auto winSize = Director::getInstance()->getWinSize();

	this->setCascadeOpacityEnabled(true);

	createDeskList(roomInfo);

	return true;
}

void GameDesk::onExit()
{
	_deskLogic->stop();
	HNLayer::onExit();
}

// ���������б�
void GameDesk::createDeskList(ComRoomInfo* roomInfo)
{
	bool isFull = true;
	if (RoomLogic()->getRoomRule() & GRR_NOTCHEAT)
	{
		//�����׳����������ӽ���
		int count = roomInfo->uDeskCount;

		for (int num = roomInfo->uDeskPeople - 1; num >= 0; num--)//��������
		{
			for (int i = 0; i < count; i++)//��������
			{
				// ��ȡ���������Ϣ
				std::vector<UserInfoStruct*> deskUsers;
				UserInfoModule()->findDeskUsers(i, deskUsers);
				//������������
				int peopleCount = deskUsers.size();
				//�ж��Ƿ����
				BYTE value = RoomLogic()->deskStation.bVirtualDesk[i / 8] & (1 << (i % 8));
				if (0 != value)
				{
					//����Ƿ�������������Ϊ��������
					peopleCount = roomInfo->uDeskPeople;
				}
				//�����������δ��
				if (peopleCount == num)
				{
					_deskLogic->requestSit(i);
					isFull = false;
					break;
				}
			}
			if (!isFull)
				break;
		}
		if (isFull)
		{
			auto prompt = GamePromptLayer::create();
			prompt->showPrompt(GBKToUtf8("������Ա��"));

			if (RoomLogic()->getRoomRule() & GRR_NOTCHEAT)
			{
				prompt->setCallBack([=](){
					_deskLogic->stop();
					RoomLogic()->close();
					removeFromParent();
				});
			}
		}
		return;
	}

	_roomInfo = roomInfo;
	auto winSize = Director::getInstance()->getWinSize();

	// �����б�
	_pageViewDesks = PageView::create();
	_pageViewDesks->setContentSize(pageViewDesksSize);
	_pageViewDesks->setAnchorPoint(Vec2(0.5f, 0.5f));
	_pageViewDesks->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
	_pageViewDesks->setTouchEnabled(true);
	_pageViewDesks->setCustomScrollThreshold(15);
	_pageViewDesks->addEventListener(PageView::ccPageViewCallback(CC_CALLBACK_2(GameDesk::pageViewMoveCallBack, this)));
	addChild(_pageViewDesks, 3);

	_pageViewDesks->setCascadeOpacityEnabled(true);

	_pageEven = ((_roomInfo->uDeskCount % 6) == 0);
	_pageLen = _roomInfo->uDeskCount / 6;

	int pageCount = _pageEven ? _pageLen : _pageLen + 1;
	int central = -pageCount / 2;
	if (abs(central) > 0)
	{
		for (int i = 0; i < pageCount; i++)
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

	createDeskPage();
}

void GameDesk::createDeskPage()
{
	if (!_canCreate) return;

	if (_pageLen > 0)
	{
		_deskinfos.clear();
		for (int m = 0; m < 6; m++)
		{
			createDeskPageInfo(_roomInfo);
			_deskNO++;
		}
		createDeskListPage(_deskinfos);
		_pageLen--;
		if (_pageEven && 0 == _pageLen)
		{
			_canCreate = false;
		}
	}

	if (0 == _pageLen && !_pageEven)
	{
		_deskinfos.clear();
		INT num = _roomInfo->uDeskCount % 6;
		for (int i = 0; i < num; i++)
		{
			createDeskPageInfo(_roomInfo);
			_deskNO++;
		}
		createDeskListPage(_deskinfos);
		_canCreate = false;
	}
	_deskinfos.clear();

	this->runAction(Sequence::create(DelayTime::create(0.4f), CallFunc::create([this](){
		createDeskPage();
	}), nullptr));
}

// ��������ҳ������
void GameDesk::createDeskPageInfo(ComRoomInfo* roomInfo)
{
	// ��ȡ���������Ϣ
	std::vector<UserInfoStruct*> deskUsers;
	UserInfoModule()->findDeskUsers(_deskNO, deskUsers);

	DeskInfo* desk = new DeskInfo;
	memset(desk, 0x0, sizeof(desk));

	if (nullptr != desk)
	{
		desk->deskID			= _deskNO;
		desk->multiple			= roomInfo->iBasePoint;
		desk->goldMin			= roomInfo->iLessPoint;
		desk->goldMax			= roomInfo->iMaxPoint;
		desk->peopleMax			= roomInfo->uDeskPeople;

		// �������ӣ�������
		BYTE isVirtual = ((RoomLogic()->deskStation.bVirtualDesk[desk->deskID / 8]) & (1 << (desk->deskID % 8)) != 0);
		desk->peopleValue = isVirtual ? roomInfo->uDeskPeople : deskUsers.size();

		// ���������ܣ�
		BYTE isLocked = RoomLogic()->deskStation.bDeskLock[desk->deskID / 8] & (1 << (desk->deskID % 8));
		desk->isLocked = (isLocked != 0);
	}
	_deskinfos.push_back(desk);
	_allDeskInfo.push_back(desk);
}

// ���������б�page
void GameDesk::createDeskListPage(std::vector<DeskInfo*> deskinfos)
{
	//���������б���ҳ��
	auto deskListLayout = Layout::create();
	deskListLayout->setName("page");
	deskListLayout->setContentSize(pageViewDesksSize);
	deskListLayout->setPassFocusToChild(true);

	float pageWidth = _pageViewDesks->getContentSize().width;
	float pageHeight = _pageViewDesks->getContentSize().height;

	deskListLayout->setCascadeOpacityEnabled(true);

	int idx = 0;
	for (auto desk : deskinfos)
	{
		idx++;
		auto deskNode = addDesk(desk);
		auto button = deskNode->getChildByName("Button_deskItem");
		button->removeFromParentAndCleanup(false);

		float posX = idx % 2 ? 0.25f : 0.75f;
		float posY = 0.0f;
		if (idx <= 2) posY = 0.8f;
		else if (idx > 2 && idx <= 4) posY = 0.5f;
		else posY = 0.2f;

		button->setPosition(Vec2(pageWidth * posX, pageHeight * posY));
		deskListLayout->addChild(button);
	}

	// �����ҳ������б���
	_pageViewDesks->addPage(deskListLayout);
}

// �������
Node* GameDesk::addDesk(DeskInfo* deskInfo)
{
	auto deskItemNode = CSLoader::createNode(DESK_ITEM_UI);
	if (nullptr == deskItemNode) return nullptr;
	deskItemNode->setCascadeOpacityEnabled(true);

	auto deskItem = (Button*)deskItemNode->getChildByName("Button_deskItem");
	if (nullptr == deskItem) return nullptr;

	deskItem->setScale(0.9f);
	deskItem->setUserData(deskInfo);
	deskItem->setPropagateTouchEvents(true);
	deskItem->addTouchEventListener(CC_CALLBACK_2(GameDesk::enterTableEventCallBack, this));

	std::string str;

	// ����
	str.clear();
	str.append(StringUtils::toString(int(deskInfo->deskID + 1)));
	str.append("����");
	auto Text_deskName = (Text*)Helper::seekWidgetByName(deskItem, "Text_deskName");
	Text_deskName->setString(GBKToUtf8(str.c_str()));

	// ��������
	str.clear();
	str.append(StringUtils::toString(deskInfo->peopleValue));
	str.append(" / ");
	str.append(StringUtils::toString(deskInfo->peopleMax));
	auto Label_people = (Text*)Helper::seekWidgetByName(deskItem, "Text_count");
	Label_people->setString(str);

	// ����������
	float count =  deskInfo->peopleValue * 100.f / deskInfo->peopleMax;
	auto progress = (LoadingBar*)Helper::seekWidgetByName(deskItem, "LoadingBar_count");
	progress->setPercent(count);

	// ��������
	str.clear();
	str.append(StringUtils::toString(deskInfo->peopleValue));
	str.append("������");
	auto Label_PeopleCount = (Text*)Helper::seekWidgetByName(deskItem, "Text_people");
	Label_PeopleCount->setString(GBKToUtf8(str.c_str()));

	// �������
	auto Label_MoneyLimit = (Text*)Helper::seekWidgetByName(deskItem, "Text_Limit");
	if (nullptr != Label_MoneyLimit)
	{
		if (0 == deskInfo->goldMin)
		{
			str.clear();
			str.append("������");
		}
		else if (0 == deskInfo->goldMax)
		{
			str.clear();
			str.append(StringUtils::toString(deskInfo->goldMin));
			str.append("׼��");
		}
		else
		{
			str.clear();
			str.append(StringUtils::toString(deskInfo->goldMin));
			str.append("-");
			str.append(StringUtils::toString(deskInfo->goldMax));
			str.append("׼��");
		}
		Label_MoneyLimit->setString(GBKToUtf8(str.c_str()));
	}
	return deskItemNode;
}

// ������Ϸ������ص�
void GameDesk::enterTableEventCallBack(Ref* pSender, Widget::TouchEventType type)
{
	if (_isTouch == false) return;

	_currentSelectedDesk = dynamic_cast<Button*>(pSender);

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		_currentSelectedDesk->setColor(Color3B(170, 170, 170));
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			_isTouch = false;
			this->runAction(Sequence::create(DelayTime::create(15.0f), CCCallFunc::create([=]()
			{
				_isTouch = true;
			}), nullptr));

			Size winSize = Director::getInstance()->getWinSize();
			_currentSelectedDesk->setColor(Color3B(255, 255, 255));
			HNAudioEngine::getInstance()->playEffect(GAME_SOUND_BUTTON);

			DeskInfo* deskInfo = static_cast<DeskInfo*>(_currentSelectedDesk->getUserData());

			// ����У��
			CCAssert(nullptr != deskInfo, "desk is nullptr!");
			if (nullptr == deskInfo)
			{
				_isTouch = true;
				return;
			}

			if (deskInfo->peopleValue == deskInfo->peopleMax)
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8("��������������"));
				_isTouch = true;
				return;
			}

			// ��������
			if(deskInfo->isLocked)
			{
				GamePasswordInput* layer = GamePasswordInput::create();
				layer->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
				this->addChild(layer, 1000);
				layer->onEnterCallback = CC_CALLBACK_1(GameDesk::onEnterPasswordCallback, this);
				_isTouch = true;
				return;
			}

			_deskLogic->requestSit(deskInfo->deskID);
			//_deskLogic->requestQuickSit();
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		_currentSelectedDesk->setColor(Color3B(255, 255, 255));
		break;
	default:
		break;
	}
}

void GameDesk::pageViewMoveCallBack(Ref* pSender, PageView::EventType type)
{
	if (_currentPageIdx == _pageViewDesks->getCurPageIndex()) return;
	_currentPageIdx = _pageViewDesks->getCurPageIndex();

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

void GameDesk::updateLockDesk()
{
	for(auto &deskInfo: _allDeskInfo)
	{
		BYTE isLocked = RoomLogic()->deskStation.bDeskLock[deskInfo->deskID / 8] & (1 << (deskInfo->deskID % 8));
		deskInfo->isLocked = (isLocked != 0);
	}
}

void GameDesk::onDeskSitCallback(bool success, const std::string& message, UINT roomID, BYTE deskNo, BYTE seatNo)
{
	_isTouch = true;
	if(success)
	{
		ComRoomInfo* pRoomInfo = RoomLogic()->getSelectedRoom();
		if(nullptr == pRoomInfo)
		{
			auto prompt = GamePromptLayer::create();
			prompt->showPrompt(GBKToUtf8("���ҷ���ʧ�ܡ�"));

			if (RoomLogic()->getRoomRule() & GRR_NOTCHEAT)
			{
				prompt->setCallBack([=](){
					_deskLogic->stop();
					RoomLogic()->close();
					removeFromParent();
				});
			}
			return;
		}
		bool bRet = GameCreator()->startGameClient(pRoomInfo->uNameID, deskNo, true);
		if (!bRet)
		{
			auto prompt = GamePromptLayer::create();
			prompt->showPrompt(GBKToUtf8("��Ϸ����ʧ�ܡ�"));

			if (RoomLogic()->getRoomRule() & GRR_NOTCHEAT)
			{
				prompt->setCallBack([=](){
					_deskLogic->stop();
					RoomLogic()->close();
					removeFromParent();
				});
			}
		}
	}
	else
	{
		auto prompt = GamePromptLayer::create();
		prompt->showPrompt(message);

		if (RoomLogic()->getRoomRule() & GRR_NOTCHEAT)
		{
			prompt->setCallBack([=](){
				_deskLogic->stop();
				RoomLogic()->close();
				removeFromParent();
			});
		}
	}
}

void GameDesk::onRoomDeskLock(BYTE deskNo)
{
	updateDeskPeopleCount(deskNo, true);
}

void GameDesk::onRoomDeskUnLock(BYTE deskNo)
{
	updateDeskPeopleCount(deskNo, false);
}

void GameDesk::onRoomDeskUserCountChanged()
{
	updateLockDesk();
	updateDeskPeopleCount(INVALID_DESKNO, false);
}

//������Ϸ����
void GameDesk::updateDeskPeopleCount(BYTE deskNo, bool isLock)
{
	if (nullptr == _pageViewDesks) return;
	Vector<Layout*> pages = _pageViewDesks->getPages();

	std::string str;
	for (auto iter = pages.begin(); iter != pages.end(); ++iter)
	{
		Vector<Node*> childs = (*iter)->getChildren();
		for (auto iter1 = childs.begin(); iter1 != childs.end(); ++iter1)
		{
			auto gameButton = dynamic_cast<Button*>(*iter1);
			if (nullptr != gameButton)
			{
				DeskInfo* info = static_cast<DeskInfo*>(gameButton->getUserData());

				BYTE value = RoomLogic()->deskStation.bVirtualDesk[info->deskID/8]&(1<<(info->deskID%8));

				if (info->deskID == deskNo && isLock)
				{
					info->peopleValue = info->peopleMax;
				}
				else if (0 != value)
				{
					info->peopleValue	= info->peopleMax;
				}
				else
				{
					std::vector<UserInfoStruct*> deskUsers;
					UserInfoModule()->findDeskUsers(info->deskID, deskUsers);
					info->peopleValue = deskUsers.size();
				}

				// ��������
				auto Label_people = (Text*)Helper::seekWidgetByName(gameButton, "Text_count");
				str.clear();
				str.append(StringUtils::toString(info->peopleValue));
				str.append(" / ");
				str.append(StringUtils::toString(info->peopleMax));
				Label_people->setString(str.c_str());

				// ����������
				auto progress = (LoadingBar*)Helper::seekWidgetByName(gameButton, "LoadingBar_count");
				float count =  info->peopleValue * 100.f / info->peopleMax;
				progress->setPercent(count);

				// ��������
				auto Label_PeopleCount = (Text*)Helper::seekWidgetByName(gameButton, "Text_people");
				str.clear();
				str.append(StringUtils::toString(info->peopleValue));
				str.append("������");
				Label_PeopleCount->setString(GBKToUtf8(str.c_str()));
			}
		}
	}
}