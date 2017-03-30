#include "GameGiftShop.h"
#include "HNLobby/GamePrompt.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include <string>      

/*
����Ϊ��Ʒ�һ��̵���
*/

static const char* GIFTSHOP_CSB				= "platform/GiftShopUi/giftShopNode.csb";
static const char* GIFT_CSB					= "platform/GiftShopUi/giftNode.csb";
static const char* GAME_PAGESPROMPT_PATH	= "platform/GiftShopUi/Res/page_Prompt.png";


GameGiftShop* GameGiftShop::createGameGiftShop(MoneyChangeNotify* delegate, LLONG lottery)
{
	GameGiftShop *pRet = new GameGiftShop(); 
	if (pRet && pRet->init(lottery)) 
	{ 
		pRet->setChangeDelegate(delegate);
		pRet->autorelease(); 
		return pRet; 
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return nullptr;
	}
}

GameGiftShop::GameGiftShop() 
 : onCloseCallBack (nullptr)
{
	
}

GameGiftShop::~GameGiftShop()
{
	HNHttpRequest::getInstance()->removeObserver(this);
}

void GameGiftShop::closeGiftShop()
{
	HNAudioEngine::getInstance()->playEffect(GAME_SOUND_CLOSE);
	auto winSize = Director::getInstance()->getWinSize();
	_panel_Gift->runAction(Sequence::create(FadeOut::create(0.1f),
		CallFunc::create([&]()
	{
		this->removeFromParent();
	}), nullptr));
}

bool GameGiftShop::init(LLONG lottery)
{
	if (!HNLayer::init())
	{
		return false;
	}

	Size winSize = Director::getInstance()->getWinSize();

	this->ignoreAnchorPointForPosition(false);

	auto MyListener = EventListenerTouchOneByOne::create();
	MyListener->setSwallowTouches(true);
	MyListener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(MyListener, this);

	auto node = CSLoader::createNode(GIFTSHOP_CSB);
	addChild(node);

	_panel_Gift = dynamic_cast<Layout*>(node->getChildByName("Panel_Gift"));
	_panel_Gift->setPosition(winSize / 2);
	float scaleX = winSize.width / _panel_Gift->getContentSize().width;
	float scaleY = winSize.height / _panel_Gift->getContentSize().height;
	_panel_Gift->setScale(scaleX, scaleY);

	//����
	Vector<Node*> children = _panel_Gift->getChildren();
	float scX = 1280 / winSize.width;
	float scY = 720 / winSize.height;

	for (auto child : children)
	{
		if (winSize.width / winSize.height <= 1.7f)
		{
			child->setScaleY(scY);
			child->setScaleX(scX);
		}
	}

	auto bg = dynamic_cast<ImageView*>(_panel_Gift->getChildByName("Image_GiftBG"));
	bg->setScale(scaleX, scaleY);

	_panel_GiftPage = dynamic_cast<Layout*>(_panel_Gift->getChildByName("Panel_GiftPage"));
	_panel_Record = dynamic_cast<Layout*>(_panel_Gift->getChildByName("Panel_Record"));
	_panel_Virtual = dynamic_cast<Layout*>(_panel_Gift->getChildByName("Panel_Virtual"));
	_panel_Entity = dynamic_cast<Layout*>(_panel_Gift->getChildByName("Panel_Entity"));

	_pageView_Gift = dynamic_cast<PageView*>(_panel_GiftPage->getChildByName("PageView_GiftList"));
	_listView_Record = dynamic_cast<ListView*>(_panel_Record->getChildByName("ListView_Record"));

	auto top = dynamic_cast<ImageView*>(_panel_Gift->getChildByName("Image_Top"));

	auto colorLayer = dynamic_cast<ImageView*>(_panel_Gift->getChildByName("Image_15"));
	colorLayer->setContentSize(Size(winSize.width + 50, winSize.height - top->getContentSize().height));
	//�Ƹ�
	char bufferCoin[64];
	auto moneyText = dynamic_cast<Text*>(top->getChildByName("Text_Money"));
	LLONG iMoney = PlatformLogic()->loginResult.i64Money;
	if (iMoney < 100000000)
	{
		sprintf(bufferCoin, "%lld", iMoney);
	}
	else
	{
		float value = (float)iMoney / 100000000;
		sprintf(bufferCoin, GBKToUtf8("%.2f��"), value);
	}
	moneyText->setColor(Color3B::BLACK);
	moneyText->setString(bufferCoin);

	//��ȯ
	auto lotteryText = dynamic_cast<Text*>(top->getChildByName("Text_Lottery"));
	if (lottery < 100000000)
	{
		sprintf(bufferCoin, "%lld", lottery);
	}
	else
	{
		float value = (float)lottery / 100000000;
		sprintf(bufferCoin, GBKToUtf8("%.2f��"), value);
	}
	lotteryText->setColor(Color3B::BLACK);
	lotteryText->setString(bufferCoin);

	//��Ʒҳ�水ť
	_btnShop = dynamic_cast<Button*>(top->getChildByName("Button_Shop"));
	//�һ���¼��ť
	_btnRecord = dynamic_cast<Button*>(top->getChildByName("Button_Record"));

	_btnShop->addClickEventListener([=](Ref*){
		_btnShop->setEnabled(false);
		_btnShop->setBright(true);
		_btnRecord->setEnabled(true);
		_btnRecord->setBright(false);
		_panel_GiftPage->setVisible(true);
		_panel_Record->setVisible(false);
	});

	_btnRecord->addClickEventListener([=](Ref*){
		_listView_Record->removeAllItems();
		//��ѯ�һ���¼
		getRecordParams();
		_btnRecord->setEnabled(false);
		_btnRecord->setBright(true);
		_btnShop->setEnabled(true);
		_btnShop->setBright(false);
		_panel_GiftPage->setVisible(false);
		_panel_Record->setVisible(true);		
	});
	_btnShop->setEnabled(false);
	_btnShop->setBright(true);

	_btnRecord->setEnabled(true);
	_btnRecord->setBright(false);

	// �رհ�ť
	auto btn_Close = dynamic_cast<Button*>(top->getChildByName("Button_Return"));
	btn_Close->addClickEventListener([=](Ref*){
		if (!_btnRecord->isEnabled())
		{
			_btnRecord->setEnabled(true);
			_btnRecord->setBright(false);
		}

		if (_panel_Virtual->isVisible())
		{
			_panel_Virtual->setVisible(false);
			_panel_GiftPage->setVisible(true);
		}
		else if (_panel_Entity->isVisible())
		{
			_panel_Entity->setVisible(false);
			_panel_GiftPage->setVisible(true);
		}
		else
		{
			closeGiftShop();
		}		
	});

	//��ѯ��Ʒ��Ϣ
	getQueryParams();

	return true;
}

void GameGiftShop::getVirtualPage(GiftInfo* info, SpriteFrame* frame)
{
	auto giftSprite = dynamic_cast<Sprite*>(_panel_Virtual->getChildByName("Sprite_Gift"));
	giftSprite->setDisplayFrame(frame);

	auto textName = dynamic_cast<Text*>(_panel_Virtual->getChildByName("Text_Name"));
	textName->setString(info->giftName);

	std::string str;
	LLONG value = info->lotteryNum;
	if (value < 10000)
	{
		str.clear();
		str.append(StringUtils::toString(value));
	}
	else if (value >= 10000 && value < 100000000)
	{
		int money = (int)value / 10000;
		str.clear();
		str.append(StringUtils::toString(money));
		str.append("��");
	}
	else
	{
		float money = (float)value / 100000000;
		char tmp[60] = {0};
		sprintf(tmp, "%.2f", money);
		str.clear();
		str.append(tmp);
		str.append("��");
	}

	auto textNum = dynamic_cast<Text*>(_panel_Virtual->getChildByName("Text_Num"));
	textNum->setString(GBKToUtf8(str.c_str()));

	auto TextField_PhoneNum = dynamic_cast<TextField*>(_panel_Virtual->getChildByName("TextField_PhoneNumber"));

	auto btn_Ture = dynamic_cast<Button*>(_panel_Virtual->getChildByName("Button_True"));
	btn_Ture->setUserData(info);
	btn_Ture->addClickEventListener([=](Ref*){
		std::string phoneNum = TextField_PhoneNum->getString();
		if (phoneNum.size() != 11 || !Tools::verifyNumber(phoneNum))
		{
			GamePromptLayer::create()->showPrompt(GBKToUtf8("��������ȷ��11λ�ֻ����룡"));
			return;
		}
		std::string str = getExchangeParams(info->giftID, "", "", phoneNum);

		requestWithParams(str, "Exchange", PlatformConfig::getInstance()->getPrizeUrl(), HttpRequest::Type::POST);
	});
}

void GameGiftShop::getEntityPage(GiftInfo* info, SpriteFrame* frame)
{
	auto giftSprite = dynamic_cast<Sprite*>(_panel_Entity->getChildByName("Sprite_Gift"));
	giftSprite->setDisplayFrame(frame);

	auto textName = dynamic_cast<Text*>(_panel_Entity->getChildByName("Text_Name"));
	textName->setString(info->giftName);

	std::string str;
	LLONG value = info->lotteryNum;
	if (value < 10000)
	{
		str.clear();
		str.append(StringUtils::toString(value));
	}
	else if (value >= 10000 && value < 100000000)
	{
		int money = (int)value / 10000;
		str.clear();
		str.append(StringUtils::toString(money));
		str.append("��");
	}
	else
	{
		float money = (float)value / 100000000;
		char buff[60] = {0};
		sprintf(buff, "%.2f", money);
		str.clear();
		str.append(buff);
		str.append("��");
	}

	auto textNum = dynamic_cast<Text*>(_panel_Entity->getChildByName("Text_Num"));
	textNum->setString(GBKToUtf8(str.c_str()));

	//ȷ�϶һ���ť
	auto btn_Ture = dynamic_cast<Button*>(_panel_Entity->getChildByName("Button_True"));
	btn_Ture->addClickEventListener([=](Ref*){

		auto Text_Name = dynamic_cast<TextField*>(_panel_Entity->getChildByName("TextField_Name"));
		auto TextField_PhoneNum = dynamic_cast<TextField*>(_panel_Entity->getChildByName("TextField_PhoneNumber"));
		auto TextField_Address = dynamic_cast<TextField*>(_panel_Entity->getChildByName("TextField_Address"));
		auto TextField_DetailedAddress = dynamic_cast<TextField*>(_panel_Entity->getChildByName("TextField_DetailedAddress"));

		do
		{
			//�ջ�������
			std::string name = Utf8ToGB(Text_Name->getString().c_str());
			if (name.empty())
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8("����д��Ч����ʵ������"));
				break;
			}

			//��ϵ��ʽ
			std::string phoneNum = Utf8ToGB(TextField_PhoneNum->getString().c_str());
			if (phoneNum.size() != 11 || !Tools::verifyNumber(phoneNum))
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8("��������ȷ��11λ�ֻ����룡"));
				break;
			}

			//ʡ������ַ
			std::string address = Utf8ToGB(TextField_Address->getString().c_str());
			if (address.empty())
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8("����д��Ч��ʡ���У�����"));
				break;
			}

			//��ϸ��ַ
			std::string detailedAddress = Utf8ToGB(TextField_DetailedAddress->getString().c_str());
			if (detailedAddress.empty())
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8("����д��Ч�Ľֵ�����ϸ��ַ��"));
				break;
			}

			//��ַ���
			std::string temp(address);
			temp.append(detailedAddress);

			//��Ϸ�������
			std::string str = getExchangeParams(info->giftID, temp, name, phoneNum);

			std::string xxx(GBKToUtf8(str.c_str()));
			//log("message: %s", xxx.c_str());
			//���Ͷһ���Ϣ
			requestWithParams(GBKToUtf8(str.c_str()), "Exchange", PlatformConfig::getInstance()->getPrizeUrl(), HttpRequest::Type::POST);
		} while (0);
	});
}

void GameGiftShop::setChangeDelegate(MoneyChangeNotify* delegate)
{
	_delegate = delegate;
}

// ��ȡ�һ���¼����
void GameGiftShop::getRecordParams()
{
	char str[64];
	sprintf(str, "action=ExchangeRecord&userid=%d", PlatformLogic()->loginResult.dwUserID);
	requestWithParams(str, "Record", PlatformConfig::getInstance()->getPrizeUrl(), HttpRequest::Type::POST);
}

// �һ���¼��Ӧ
void GameGiftShop::onHttpRecordCompleted(const std::string& data)
{
	char str[100] = {0};
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
	if (doc.HasParseError() || !doc.IsObject())
	{
		return;
	}

	if (doc.HasMember("content"))
	{
		rapidjson::Value& array = doc["content"];
		if(array.IsArray())
		{
			char str[64];
			//�����һ���¼����
			for (UINT i = 0; i < array.Size(); i++)
			{
				rapidjson::Value& arraydoc = array[i];
				do
				{
					// �һ���¼���б���ͼ
					auto listItem = ImageView::create("platform/GiftShopUi/Res/item.png");
					float itemWidth = listItem->getContentSize().width;
					float itemHeight = listItem->getContentSize().height;

					if(arraydoc.HasMember("OrderNo"))
					{
						std::string orderNo = arraydoc["OrderNo"].GetString();
					 	//������
						sprintf(str, "%s", orderNo.c_str());
						auto numText = Text::create(str, "", 22);
						numText->setPosition(Vec2(itemWidth * 0.12f, itemHeight * 0.55f));
						listItem->addChild(numText);
					}

					if(arraydoc.HasMember("Award_Name"))
					{
						std::string name = arraydoc["Award_Name"].GetString();
						//��Ʒ����
						sprintf(str, "%s", name.c_str());
						auto nameText = Text::create(str, "", 22);
						nameText->setPosition(Vec2(itemWidth * 0.37f, itemHeight * 0.55f));
						listItem->addChild(nameText);
					}

					if(arraydoc.HasMember("AwardTime"))
					{
						std::string time = arraydoc["AwardTime"].GetString();
						//��Ʒ����
						sprintf(str, "%s", time.c_str());
						auto timeText = Text::create(str, "", 22);
						timeText->setPosition(Vec2(itemWidth * 0.64f, itemHeight * 0.55f));
						listItem->addChild(timeText);
					}

					if(arraydoc.HasMember("IsCash"))
					{
						bool state = arraydoc["IsCash"].GetBool();
						//����״̬
						std::string temp = state ? "�ѷ���" : "δ����";
						auto stateText = Text::create(GBKToUtf8(temp.c_str()), "", 22);
						stateText->setPosition(Vec2(itemWidth * 0.88f, itemHeight * 0.55f));
						listItem->addChild(stateText);
					}

					_listView_Record->pushBackCustomItem(listItem);
				} while (0);
			}
		}
	}
}

//��ȡ��ѯ����
void GameGiftShop::getQueryParams()
{
	requestWithParams("action=PrizeList", "Query", PlatformConfig::getInstance()->getPrizeUrl(), HttpRequest::Type::POST);
}

// ��ѯ�����Ӧ
void GameGiftShop::onHttpQueryCompleted(const std::string& data)
{
	_gifts.clear();

	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
	if (doc.HasParseError() || !doc.IsObject())
	{
		return;
	}

	if (doc.HasMember("content"))
	{
		rapidjson::Value& array = doc["content"];
		if(array.IsArray())
		{
			//������Ʒ���������б�ҳ�棬8��һҳ
			int pageCount = (array.Size() / 8);
			int remainder = (array.Size() % 8);

			int pageLen = (remainder == 0) ? pageCount : pageCount + 1;
			int central = -pageLen / 2;
			//����һҳ���ײ�ҳ����ʾ
			if (abs(central) > 0)
			{
				for (int i = 0; i < pageLen; i++)
				{
					//ҳ����ʾ
					auto pageTip = Sprite::create(GAME_PAGESPROMPT_PATH);
					_panel_GiftPage->addChild(pageTip);
					_pagesPrompt.push_back(pageTip);

					pageTip->setPosition(Vec2(_panel_Gift->getContentSize().width / 2 + central * 25, 
						_panel_Gift->getContentSize().height * 0.04f));
					if (i > 0)
					{
						pageTip->setScale(0.8f);
						pageTip->setColor(Color3B(150, 150, 150));
					}
					central++;
				}
			}

			//����ҳ��
			for (int i = 0; i < pageLen; i++)
			{
				createGiftPages();
			}

			//������Ʒ����
			for (UINT i = 0; i < array.Size(); i++)
			{
				rapidjson::Value& arraydoc = array[i];

				GiftInfo giftInfo;
				do
				{
					if(arraydoc.HasMember("Award_ID"))
					{
						int id = arraydoc["Award_ID"].GetInt();
						giftInfo.giftID = id;
					}

					if(arraydoc.HasMember("Award_Name"))
					{
						std::string name = arraydoc["Award_Name"].GetString();
						giftInfo.giftName = name;
					}

					if(arraydoc.HasMember("Award_Info"))
					{
						std::string info = arraydoc["Award_Info"].GetString();
						giftInfo.giftInfo = info;
					}

					if(arraydoc.HasMember("Award_Pic"))
					{
						std::string pic = arraydoc["Award_Pic"].GetString();
						giftInfo.giftPic = pic;
						char str[24];
						sprintf(str, "Award_Pic%d", i);
						requestWithParams("", str, pic, HttpRequest::Type::GET);
					}

					if(arraydoc.HasMember("Award_Num"))
					{
						int num = arraydoc["Award_Num"].GetInt();
						giftInfo.giftNum = num;
					}

					if(arraydoc.HasMember("Award_MoneyCost"))
					{
						LLONG lottery = arraydoc["Award_MoneyCost"].GetInt64();
						giftInfo.lotteryNum = lottery;
					}

					if(arraydoc.HasMember("Award_Type"))
					{
						int type = arraydoc["Award_Type"].GetInt();
						giftInfo.giftType = type;
					}

					if(arraydoc.HasMember("Award_AddDate"))
					{
						std::string date = arraydoc["Award_AddDate"].GetString();
						giftInfo.addDate = date;
					}

					_gifts.push_back(giftInfo);
				} while (0);
			}
		}
	}
}

// ������Ʒҳ��
void GameGiftShop::createGiftPages()
{
	// ������Ϸ�б���ҳ��
	auto gameLayout = Layout::create();
	gameLayout->setName("page");
	gameLayout->setContentSize(Size(1280, 600));
	gameLayout->setCascadeOpacityEnabled(true);

	//�����ҳ������б���
	_pageView_Gift->addPage(gameLayout);
	//�϶�����
	_pageView_Gift->addEventListener(PageView::ccPageViewCallback(CC_CALLBACK_2(GameGiftShop::pageViewMoveCallBack, this)));
}

// ����ͼƬ��Ӧ
void GameGiftShop::onHttpDownloadPicCompleted(const std::string& tag, const std::string& data)
{
	//�����ͼƬ˳��һ�������԰Ѷ�Ӧ����Ʒ��ͼƬ�������
	char str[24];
	for (UINT i = 0; i < _gifts.size(); i++)
	{
		sprintf(str, "Award_Pic%d", i);
		if(tag.compare(str) == 0)
		{
			//һҳ8����Ʒ����ȡ�ڼ�ҳ
			int pageIdx = i / 8;
			auto page = _pageView_Gift->getPage(pageIdx);

			auto giftNode = CSLoader::createNode(GIFT_CSB);
			page->addChild(giftNode);

			auto giftBtn = dynamic_cast<Button*>(giftNode->getChildByName("Button_Gift"));
			giftBtn->removeFromParentAndCleanup(false);
			page->addChild(giftBtn);
			giftBtn->addTouchEventListener(CC_CALLBACK_2(GameGiftShop::btnEventCallBack, this));

			int x = i % 8 + 1;
			float y = 0.75f;
			if (x > 4) x -= 4, y = 0.26f;
			float posX = -0.1f + x * 0.24f;
			giftBtn->setPosition(Vec2(page->getContentSize().width * posX, page->getContentSize().height * y));

			auto textName = dynamic_cast<Text*>(giftBtn->getChildByName("Text_Name"));
			textName->setString(_gifts.at(i).giftName.c_str());

			std::string info;
			LLONG value = _gifts.at(i).lotteryNum;
			if (value < 10000)
			{
				info.clear();
				info.append(StringUtils::toString(value));
				info.append("��ȯ");
			}
			else if (value >= 10000 && value < 100000000)
			{
				int money = (int)value / 10000;
				info.clear();
				info.append(StringUtils::toString(money));
				info.append("��ȯ");
			}
			else
			{
				float money = (float)value / 100000000;				
				sprintf(str, "%.2f", money);
				info.clear();
				info.append(str);
				info.append("�ڽ�ȯ");
			}
			auto textLottery = dynamic_cast<Text*>(giftBtn->getChildByName("Text_Lottery"));
			textLottery->setString(GBKToUtf8(info.c_str()));

////////////////////////////////////////////////////////////////////////////////////////////
			std::vector<char> buffer;
			buffer.assign(data.begin(), data.end());

			//create image
			Image* image = new Image;
			image->initWithImageData((BYTE*)buffer.data(), buffer.size());

			//create texture
			auto texture = new Texture2D();
			bool isImage = texture->initWithImage(image);

			if(!isImage){
				log("Texture2D init faile!");
				return;
			}

			image->release();
			//�Ѱѻ�ȡ����texture������sprite
			auto pSprite = Sprite::createWithTexture(texture);
			//ͨ��sprite�Ĵ�С���spriteFrame�ľ��δ�С
			Size size = pSprite->getContentSize();
			Rect rect = Rect(0, 0, size.width, size.height);
			//ͨ����ȡ����texture�;��Σ����spriteFrame
			sprintf(str, "gift_%d.png", i);
			auto spriteFrame = SpriteFrame::createWithTexture(texture, rect);
			SpriteFrameCache::getInstance()->addSpriteFrame(spriteFrame, str);
			//������Ʒ��ϢͼƬΪ�����ȡ����spriteFrame
			auto giftSprite = dynamic_cast<Sprite*>(giftBtn->getChildByName("Sprite_Gift"));
			giftSprite->setSpriteFrame(spriteFrame);

			giftBtn->setUserObject(spriteFrame);
			giftBtn->setUserData(&_gifts.at(i));

			break;
		}
	}
}

// ��ȡ�һ���������
std::string GameGiftShop::getExchangeParams(int awardid, const std::string address, const std::string name, const std::string mobile)
{
	std::vector<std::string> params;

	char chars[128] = {0};
	std::string str;

	// ��������
	params.push_back("action=ExchangeGift");

	// �û�ID
	str = "userid=";
	sprintf(chars, "%d", PlatformLogic()->loginResult.dwUserID);
	str.append(chars);
	params.push_back(str);

	// ��Ʒ��¼ID
	str = "awardid=";
	sprintf(chars, "%d", awardid);
	str.append(chars);
	params.push_back(str);

	// �ջ���ַ
	str = "address=";
	sprintf(chars, "%s", address.c_str());
	str.append(chars);
	params.push_back(str);

	// �ջ�������
	str = "name=";
	sprintf(chars, "%s", name.c_str());
	str.append(chars);
	params.push_back(str);

	// ��ϵ�绰
	str = "mobile=";
	sprintf(chars, "%s", mobile.c_str());
	str.append(chars);
	params.push_back(str);

	// ��Ϣ
	params.push_back("remark=");

	std::string paramStr = signParams(params);

	return paramStr;
}

void GameGiftShop::onHttpResponse(const std::string& requestName, bool isSucceed, const std::string &responseData)
{
	if (!isSucceed)
	{
		GamePromptLayer::create()->showPrompt(responseData);
		return;
	}

	if (requestName.compare("Exchange") == 0)
	{
		onHttpExchangeGiftCompleted(responseData);
	}
	else if (requestName.compare("Record") == 0)
	{
		onHttpRecordCompleted(responseData);
	}
	else if (requestName.compare("Query") == 0)
	{
		onHttpQueryCompleted(responseData);
	}
	else
	{
		size_t pos = requestName.find("Award_Pic");
		if (pos != std::string::npos)
		{
			onHttpDownloadPicCompleted(requestName, responseData);
		}
		
	}
}

// �һ���Ʒ��Ӧ
void GameGiftShop::onHttpExchangeGiftCompleted(const std::string& data)
{
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
	if (doc.HasParseError() || !doc.IsObject())
	{
		return;
	}

	do
	{
		if (doc.HasMember("status"))
		{
			int statu = doc["status"].GetInt();
			if (statu == -1)
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8("�һ�ʧ�ܣ���ȯ�������㣡"));
				break;
			}
			else if (statu == 0)
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8("��������æ�����Ժ����ԣ�"));
				break;
			}
			else
			{					
			}
		}

		if (doc.HasMember("content"))
		{
			rapidjson::Value& array = doc["content"];
			if(array.IsArray())
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8("��ϲ�㣬�һ��ɹ���"));
				//�����һ���Ʒ��������
				for (UINT i = 0; i < array.Size(); i++)
				{
					rapidjson::Value& arraydoc = array[i];
					do
					{
						if (arraydoc.HasMember("WalletMoney"))
						{
							LLONG money = arraydoc["WalletMoney"].GetInt64();
							//�Ƹ�
							char bufferCoin[24];
							auto top = dynamic_cast<ImageView*>(_panel_Gift->getChildByName("Image_Top"));
							auto moneyText = dynamic_cast<Text*>(top->getChildByName("Text_Money"));
							sprintf(bufferCoin, "%lld", money);
							moneyText->setString(GBKToUtf8(bufferCoin));

						}

						if (arraydoc.HasMember("Lotteries"))
						{
							LLONG lottery = arraydoc["Lotteries"].GetInt64();
							//��ȯ
							char bufferCoin[24];
							auto top = dynamic_cast<ImageView*>(_panel_Gift->getChildByName("Image_Top"));
							auto lotteryText = dynamic_cast<Text*>(top->getChildByName("Text_Lottery"));
							sprintf(bufferCoin, "%lld", lottery);
							lotteryText->setString(GBKToUtf8(bufferCoin));
							_delegate->lotteryChanged(lottery);
						}
					} while (0);
				}
			}
		}
	} while (0);
}

// ����ǩ��
std::string GameGiftShop::signParams(std::vector<std::string>& params)
{
	std::string paramStr;

	//std::sort(params.begin(), params.end());
	for(size_t i = 0; i < params.size(); i++)
	{
		if(i != 0)
		{
			paramStr += "&";
		}
		paramStr += params.at(i);
	}

	return paramStr;
}

//�������ݽӿ�
void GameGiftShop::requestWithParams(const std::string& params, const std::string& tag, const std::string& url, HttpRequest::Type type)
{
	HNHttpRequest::getInstance()->addObserver(this);
	HNHttpRequest::getInstance()->request(tag, type, url, params);
}

//�б�������
void GameGiftShop::pageViewMoveCallBack(Ref* pSender, PageView::EventType type)
{
	if (_currentPageIdx == _pageView_Gift->getCurPageIndex()) return;
	_currentPageIdx = _pageView_Gift->getCurPageIndex();

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

//�б�ť����ص�����
void GameGiftShop::btnEventCallBack(Ref* pSender, Widget::TouchEventType type)
{
	auto btn = dynamic_cast<Button*>(pSender);

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		btn->runAction(ScaleTo::create(0.2f, 1.1f));
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			btn->runAction(ScaleTo::create(0.2f, 1.0f));

			GiftInfo* info = (GiftInfo*)btn->getUserData();
			SpriteFrame* frame = (SpriteFrame*)btn->getUserObject();

			_btnRecord->setEnabled(false);
			_panel_GiftPage->setVisible(false);

			if (info->giftType == 1)
			{
				_panel_Virtual->setVisible(true);
				getVirtualPage(info, frame);
			}
			else if (info->giftType == 2)
			{
				_panel_Entity->setVisible(true);
				getEntityPage(info, frame);
			}
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		btn->runAction(ScaleTo::create(0.2f, 1.0f));
		break;
	default:
		break;
	}
}