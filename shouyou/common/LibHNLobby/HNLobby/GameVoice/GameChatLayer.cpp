/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#include "GameChatLayer.h"
#include "HNLobbyExport.h"

static const char* CHATDLG_PATH		= "platform/Chat/chat.csb";
static const char* LIST_BG			= "platform/Chat/list.png";               //listBG
static const char* Chat_Image_Small = "platform/Chat/chatSmallRes/";
static const char* Chat_Image_Voice = "platform/Chat/voice_chat.png";

#define BUBBLE_PATH             "platform/Chat/bubble.png"
#define EMOTION_PATH			"platform/Chat/chatSmallRes/"

GameChatLayer::GameChatLayer() :_isRecordedVoiceValid(false), _isClosed(false)
{
}

GameChatLayer::~GameChatLayer()
{
	HNAudioEngine::getInstance()->resumeBackgroundMusic();
}

void GameChatLayer::closeChatLayer()
{
	_chatUI.ImageView_BG->runAction(Sequence::create(ScaleTo::create(0.1f, 0.1f), CCCallFunc::create([&]()
	{
		_eventDispatcher->removeEventListener(_touchEventListener);
		this->setVisible(false);
		_isClosed = true;
	}), nullptr));

	//HNAudioEngine::getInstance()->resumeBackgroundMusic(); //恢复音效
}

bool GameChatLayer::init()
{
	if (!HNLayer::init()) return false;

	Size winSize = Director::getInstance()->getWinSize();

	auto chat_Node = CSLoader::createNode(CHATDLG_PATH);
	this->addChild(chat_Node, 1, 10);

	_chatUI.chatUI = (Layout*)chat_Node->getChildByName("Panel_Chat");
	_chatUI.chatUI->setAnchorPoint(Vec2(0.5, 0.5));
	_chatUI.chatUI->setPosition(Vec2(winSize.width / 2, winSize.height / 2));

	_scalex = winSize.width / 800;
	_scaley = winSize.height / 480;
	if (winSize.width / winSize.height <= 1.5f)
	{
		_chatUI.chatUI->setScale(_scalex);
	}
	else
	{
		_chatUI.chatUI->setScale(_scaley);
	}

	//聊天界面
	_chatUI.ImageView_BG = (ImageView*)_chatUI.chatUI->getChildByName("Image_chatBG");

	if (nullptr != _chatUI.ImageView_BG)
	{
		//常用语
		_chatUI.Button_common = (Button*)_chatUI.ImageView_BG->getChildByName("Button_common");
		_chatUI.Button_common->addTouchEventListener(CC_CALLBACK_2(GameChatLayer::chatUiButtonCallBack, this));

		//表情
		_chatUI.Button_face = (Button*)_chatUI.ImageView_BG->getChildByName("Button_face");
		_chatUI.Button_face->addTouchEventListener(CC_CALLBACK_2(GameChatLayer::chatUiButtonCallBack, this));

		//聊天
		_chatUI.Button_chat = (Button*)_chatUI.ImageView_BG->getChildByName("Button_chat");
		_chatUI.Button_chat->addTouchEventListener(CC_CALLBACK_2(GameChatLayer::chatUiButtonCallBack, this));

		//聊天记录列表
		_chatUI.ListView_chatRecord = (ui::ListView*)_chatUI.ImageView_BG->getChildByName("ListView_chatRecord");
		_chatUI.ListView_chatRecord->addEventListener(ListView::ccListViewCallback(CC_CALLBACK_2(GameChatLayer::chatRecordEventCallBack, this)));
		_chatUI.ListView_chatRecord->setVisible(false);

		//确定
		_chatUI.Button_send = (Button*)_chatUI.ImageView_BG->getChildByName("Button_send");
		_chatUI.Button_send->addTouchEventListener(CC_CALLBACK_2(GameChatLayer::chatUiButtonCallBack, this));

		//语音聊天
		_chatUI.Button_voice = (Button*)_chatUI.ImageView_BG->getChildByName("Button_voice");
		_chatUI.Button_voice->addTouchEventListener(CC_CALLBACK_2(GameChatLayer::chatUiButtonCallBack, this));
		_chatUI.Button_voice->setVisible(true);

		//文本聊天
		_chatUI.Button_message = (Button*)_chatUI.ImageView_BG->getChildByName("Button_message");
		_chatUI.Button_message->addTouchEventListener(CC_CALLBACK_2(GameChatLayer::chatUiButtonCallBack, this));
		_chatUI.Button_message->setVisible(false);

		//聊天按钮
		_chatUI.Button_chat_content = (Button*)_chatUI.ImageView_BG->getChildByName("Button_chat_content");
		_chatUI.Button_chat_content->addTouchEventListener(CC_CALLBACK_2(GameChatLayer::voiceChatUiButtonCallBack, this));
		_chatUI.Button_chat_content->setVisible(true);
		_chatUI.Button_chat_content->setEnabled(false);

		//输入框
		_chatUI.TextField_chat_content = (TextField*)_chatUI.ImageView_BG->getChildByName("TextField_msg");
		_chatUI.TextField_chat_content->setVisible(false);
		_chatUI.editBox = HNEditBox::createEditBox(_chatUI.TextField_chat_content, this);

		//表情列表
		_chatUI.ScrollView_face = (ui::ScrollView*)_chatUI.ImageView_BG->getChildByName("ScrollView_face");
		char str[12];
		for (int i = 0; i < 68; i++)
		{
			sprintf(str, "/:%02d", i);
			auto face = (Button*)_chatUI.ScrollView_face->getChildByName(str);
			face->addTouchEventListener(CC_CALLBACK_2(GameChatLayer::faceTouchEventCallBack, this));
		}

		//常用语列表
		_chatUI.ListView_common = (ui::ListView*)_chatUI.ImageView_BG->getChildByName("ListView_common");

		for (int i = 0; i < 10; i++)
		{
			createCommonList(i);
		}

		_chatUI.ListView_common->addEventListener(ListView::ccListViewCallback(CC_CALLBACK_2(GameChatLayer::commonListEventCallBack, this)));
	}
	return true;
}

void GameChatLayer::createCommonList(INT idx)
{
	if (idx < 0 || idx >= 10)
		return;

	std::string str[10] = 
	{
		"快点吧，等到花儿都谢了。",
		"大家好， 很高兴见到各位。",
		"又断线了，网络怎么这么差啊。",
		"和你合作真是太愉快了。",
		"我们交个朋友吧，能告诉我你的联系方式吗？",
		"你是MM，还是GG？",
		"不要吵了，不要吵了，专心玩游戏吧。",
		"不要走，决战到天亮。",
		"各位真是不好意思，我要走了。",
		"再见了，我会想念大家的。"
	};

	// 常用语列表背景图
	auto listItem = ImageView::create(LIST_BG);
	float itemWidth = listItem->getContentSize().width;
	float itemHeight = listItem->getContentSize().height;
	listItem->setName("listItem");
	listItem->setTouchEnabled(true);

	// 文字
	auto commonText = Text::create("", "", 22);
	commonText->setColor(colorBlack);
	commonText->setName("commonText");
	commonText->setAnchorPoint(Vec2(0, 0.5));
	commonText->setPosition(Vec2(itemWidth * 0.1f, itemHeight * 0.55f));
	commonText->setString(GBKToUtf8(str[idx].c_str()));
	listItem->addChild(commonText);

	_chatUI.ListView_common->pushBackCustomItem(listItem);
}

//聊天界面按钮回调
void GameChatLayer::chatUiButtonCallBack(Ref* pSender, Widget::TouchEventType type)
{
	if (Widget::TouchEventType::ENDED != type) return;
	auto btn = (Button*)pSender;
	HNAudioEngine::getInstance()->playEffect(GAME_SOUND_BUTTON);

	std::string name = btn->getName();

	if (name.compare("Button_send") == 0)
	{
		if (_chatUI.editBox->getString().empty())
		{
			auto prompt = GamePromptLayer::create();
			prompt->showPrompt(GBKToUtf8("输入框不能为空！"));
		}
		else
		{
			if (nullptr != onSendTextCallBack)
			{
				onSendTextCallBack(_chatUI.editBox->getString());

				closeChatLayer();
			}
		}
	}
	if (name.compare("Button_common") == 0)
	{
		_chatUI.ListView_common->setVisible(true);
		_chatUI.ScrollView_face->setVisible(false);
		_chatUI.ListView_chatRecord->setVisible(false);
	}

	if (name.compare("Button_face") == 0)
	{
		_chatUI.ListView_common->setVisible(false);
		_chatUI.ScrollView_face->setVisible(true);
		_chatUI.ListView_chatRecord->setVisible(false);
	}
	if (name.compare("Button_chat") == 0)
	{
		_chatUI.ListView_common->setVisible(false);
		_chatUI.ScrollView_face->setVisible(false);
		_chatUI.ListView_chatRecord->setVisible(true);

		//showChatRecords();
		updateRecordListView();

	}
	if (name.compare("Button_voice") == 0) //语音聊天
	{
		_chatUI.Button_voice->setVisible(false);
		_chatUI.Button_message->setVisible(true);

		_chatUI.Button_chat_content->setEnabled(true);
		_chatUI.Button_chat_content->setTitleText(GBKToUtf8("按住 说话"));

		_chatUI.editBox->setVisible(false);
	}
	if (name.compare("Button_message") == 0) //文本聊天
	{
		_chatUI.Button_voice->setVisible(true);
		_chatUI.Button_message->setVisible(false);

		_chatUI.Button_chat_content->setEnabled(false);
		_chatUI.Button_chat_content->setTitleText("");

		_chatUI.editBox->setVisible(true);
		_chatUI.editBox->setString("");
		_chatUI.TextField_chat_content->setString("");
	}
}

void GameChatLayer::voiceChatUiButtonCallBack(Ref* pSender, Widget::TouchEventType type)
{
	Button* voice_chat_btn = (Button*)pSender;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		{
			VoiceManager::getInstance()->startRecordAudio();
			this->scheduleOnce(schedule_selector(GameChatLayer::setRecordVoiceValid), 0.5f);
			this->scheduleOnce(schedule_selector(GameChatLayer::setRecordVoiceInValid), 20.0f);
			voice_chat_btn->setTitleText(GBKToUtf8("松开 结束"));
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			if (!_isRecordedVoiceValid) //如果录音时间小于0.5s或大于20s，则认为录音时间太短或太长，录音不合法，不会发送
			{
				VoiceManager::getInstance()->cancelRecordAudio();
			}
			else
			{
				VoiceManager::getInstance()->stopRecordAudio();
			}

			this->unschedule(schedule_selector(GameChatLayer::setRecordVoiceValid));
			this->unschedule(schedule_selector(GameChatLayer::setRecordVoiceInValid));
			voice_chat_btn->setTitleText(GBKToUtf8("按住 说话"));
			_isRecordedVoiceValid = false;
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED: //滑出按钮，则取消录音
		{
			VoiceManager::getInstance()->cancelRecordAudio();

			this->unschedule(schedule_selector(GameChatLayer::setRecordVoiceValid));
			this->unschedule(schedule_selector(GameChatLayer::setRecordVoiceInValid));
			voice_chat_btn->setTitleText(GBKToUtf8("按住 说话"));
			_isRecordedVoiceValid = false;
		}
		break;
	default:
		break;
	}
}

void GameChatLayer::setRecordVoiceValid(float dalta)
{
	_isRecordedVoiceValid = true;
}

void GameChatLayer::setRecordVoiceInValid(float dalta)
{
	if (_isRecordedVoiceValid)
	{
		_isRecordedVoiceValid = false;
		VoiceManager::getInstance()->stopRecordAudio(); //到了20s的时候自动停止，发送之前20s内的录音			
	}
}

//点击表情回调
void GameChatLayer::faceTouchEventCallBack(Ref* pSender, Widget::TouchEventType type)
{
	if (Widget::TouchEventType::ENDED != type) return;
	auto btn = (Button*)pSender;
	std::string str = _chatUI.editBox->getString();
	str += btn->getName();
	_chatUI.editBox->setString(str);
}

//常用语列表点击回调
void GameChatLayer::commonListEventCallBack(Ref* pSender, ui::ListView::EventType type)
{
	if (ListView::EventType::ON_SELECTED_ITEM_END != type) return;
	ListView* listItems = dynamic_cast<ListView*>(pSender);
	UINT selected = listItems->getCurSelectedIndex();
	Widget* listItem = listItems->getItem(selected);
	auto commontext = (Text*)listItem->getChildByName("commonText");

	if (nullptr != onSendTextCallBack)
	{
		onSendTextCallBack(commontext->getString());
		closeChatLayer();
	}
}

void GameChatLayer::showChatRecords()
{
	char str[501] = { 0 };
	std::string filenameSmallImage(Chat_Image_Small);//小图路径
	auto maxFaceCount = 68;
	std::string word;
	char num[3] = { 0, 0, 0 };
	Size lineSize(540, 30);
	int fontSize = 18;
	int imageSize = 24;
	float msgAllLenght = 0;
	int ImageNum = 0;//表情个数，用来计算表情需占用的位置
	int msgNumber = 0;

	while (msgNumber < _chatRecords.size())
	{
		auto charMsg = RichText::create();
		charMsg->ignoreContentAdaptWithSize(false);
		charMsg->setContentSize(Size(lineSize.width - 20, lineSize.height));
		charMsg->setAnchorPoint(Vec2(0.5f, 1));

		Chat_Record_Info chat_info_item = _chatRecords.at(_chatRecords.size() - msgNumber - 1);
		std::string aloneMsg = chat_info_item.content;

		if (chat_info_item.tag != 0) //如果是语音
		{
			word.append(aloneMsg);
			auto text = RichElementText::create(0, colorBlack, 255, GBKToUtf8(word.c_str()), "Arial", fontSize);
			charMsg->pushBackElement(text);
			word.clear();

			RichElementImage* img = RichElementImage::create(0, Color3B(255, 255, 255), 255, Chat_Image_Voice);
			charMsg->pushBackElement(img);
			charMsg->setName("chatRecord_voice_richText");

			charMsg->setTag(chat_info_item.tag);
		}
		else //不是语音
		{
			for (int i = 0; aloneMsg[i] != '\0'; i++)
			{
				if (aloneMsg[i] == '/' && aloneMsg[i + 1] == ':')
				{
					//符合表情条件，再判断是否在表情范围内
					num[0] = aloneMsg[i + 2];
					num[1] = aloneMsg[i + 3];
					auto imageNumber = atoi(num);
					// 一定是表情
					if (imageNumber >= 0 && imageNumber < maxFaceCount)
					{
						if (word.length() > 0)
						{
							RichElementText* rtext = RichElementText::create(0, colorBlack, 255, GBKToUtf8(word.c_str()), "Arial", fontSize);
							charMsg->pushBackElement(rtext);
							word.clear();
						}
						ImageNum++;
						RichElementImage* img = RichElementImage::create(0, Color3B(255, 255, 255), 255, filenameSmallImage + StringUtils::format("im%d.png", imageNumber));
						charMsg->pushBackElement(img);
						i += 3;
					}
					//不是表情
					else
					{
						msgAllLenght += 0.5f;
						word.push_back(aloneMsg[i]);
					}
				}
				else
				{
					msgAllLenght += 0.5f;
					word.push_back(aloneMsg[i]);
				}
			}
		}


		//显示文本
		if (word.length() > 0)
		{
			auto text = RichElementText::create(0, colorBlack, 255, GBKToUtf8(word.c_str()), "Arial", fontSize);
			charMsg->pushBackElement(text);
			word.clear();
		}



		float realAllLenght = msgAllLenght * fontSize + ImageNum * imageSize;//文本图片总的真实大小
		float msgRowNum = realAllLenght / 520.0f;
		float msgHeight = 0;
		if (msgRowNum < 1)
		{
			msgHeight = lineSize.height;
		}
		else
		{
			msgHeight = lineSize.height + (20 * (int)msgRowNum);
		}

		//聊天消息子项
		auto msgLayout = Layout::create();
		//msgLayout->setSwallowTouches(true);
		msgLayout->setContentSize(Size(lineSize.width, msgHeight));
		msgLayout->addChild(charMsg);
		msgLayout->setTouchEnabled(true);
		charMsg->setPosition(Vec2(msgLayout->getContentSize().width / 2 + 10, msgLayout->getContentSize().height));

		_chatUI.ListView_chatRecord->pushBackCustomItem(msgLayout);

		msgNumber++;
		ImageNum = 0;
		msgAllLenght = 0;
	}
}

void GameChatLayer::chatRecordEventCallBack(Ref* pSender, ui::ListView::EventType type)
{
	if (ListView::EventType::ON_SELECTED_ITEM_END != type) return;
	ListView* listView = dynamic_cast<ListView*>(pSender);
	UINT selected = listView->getCurSelectedIndex();
	Widget* listItem = listView->getItem(selected);
	auto chatRecord = (RichText*)listItem->getChildByName("chatRecord_voice_richText");

	if (chatRecord && 0 != chatRecord->getTag())
	{
		int voiceID = chatRecord->getTag();

		VoiceManager::getInstance()->downloadAudio(voiceID);

		//HNAudioEngine::getInstance()->pauseBackgroundMusic();
		this->unschedule(schedule_selector(GameChatLayer::resumeBackgroundMusic));
		this->scheduleOnce(schedule_selector(GameChatLayer::resumeBackgroundMusic), 10.f);
	}

}

void GameChatLayer::chatBubbleEventCallBack(Ref* pSender, Widget::TouchEventType type)
{
	if (Widget::TouchEventType::ENDED != type) return;

	ImageView* bubble = dynamic_cast<ImageView*>(pSender);

	int voiceID = bubble->getTag();

	VoiceManager::getInstance()->downloadAudio(voiceID);

	//HNAudioEngine::getInstance()->pauseBackgroundMusic();
	this->unschedule(schedule_selector(GameChatLayer::resumeBackgroundMusic));
	this->scheduleOnce(schedule_selector(GameChatLayer::resumeBackgroundMusic), 10.f);
}

//更新聊天记录
void GameChatLayer::updateRecordListView()
{	
	if (_isClosed) return;

	_chatUI.ListView_chatRecord->removeAllChildrenWithCleanup(true);

	_chatUI.ListView_common->setVisible(false);
	_chatUI.ScrollView_face->setVisible(false);
	_chatUI.ListView_chatRecord->setVisible(true);

	showChatRecords();
}

void GameChatLayer::clearChatRecords()
{
	_chatRecords.clear();
}

void GameChatLayer::show(bool willShow)
{
	if (willShow)
	{
		_isClosed = false;

		_chatUI.ImageView_BG->setScale(1.0);

		_chatUI.TextField_chat_content->setString("");
		_chatUI.editBox->setString("");

		_chatUI.ListView_common->setVisible(true);
		_chatUI.ScrollView_face->setVisible(false);
		_chatUI.ListView_chatRecord->setVisible(false);
		
		_touchEventListener = EventListenerTouchOneByOne::create();
		_touchEventListener->setSwallowTouches(true);
		_touchEventListener->onTouchBegan = [&](Touch* touch, Event* event)
		{
			auto target = static_cast<Sprite*>(event->getCurrentTarget());//获取的当前触摸的目标
			Point locationInNode = target->convertToNodeSpace(touch->getLocation());
			Size s = target->getContentSize();
			Rect rect = Rect(0, 0, s.width, s.height);
			if (rect.containsPoint(locationInNode))//判断触摸点是否在目标的范围内
			{
				Rect uRect = (this->getChildByTag(10))->getBoundingBox();
				if (uRect.containsPoint(locationInNode)) return true;
				closeChatLayer();
				return true;
			}
			else
				return false;
		};

		_eventDispatcher->addEventListenerWithSceneGraphPriority(_touchEventListener, this);
	}

	this->setVisible(willShow);
}

void GameChatLayer::addChatRecords(std::vector<Chat_Record_Info> records)
{
	for (int i = 0; i < records.size(); ++i)
	{
		_chatRecords.push_back(records.at(i));
	}
}

//更新聊天记录容器
void GameChatLayer::addChatRecord(Chat_Record_Info record)
{
	_chatRecords.push_back(record);

	if (_chatRecords.size() == 101)
	{
		for (int i = 0; i < 100; i++)
		{
			_chatRecords[i] = _chatRecords[i + 1];
		}
		//移除最后加进去的一行
		_chatRecords.pop_back();
	}
}

void GameChatLayer::onHandleTextMessage(Vec2 bubblePos, CHAR msg[], const std::string &nickName, bool isBubbleFlipped, 
	bool showUserName, bool showUpBubble)
{
	//显示聊天记录
	showChatRecord(msg, nickName);

	if (showUpBubble)
	{
		//显示聊天气泡
		showBubble(bubblePos, msg, nickName, isBubbleFlipped, showUserName);
	}	
}

void GameChatLayer::showChatRecord(CHAR content[], const std::string &nickName)
{
	//增加聊天记录
	std::string message = StringUtils::format("[%s说]:", nickName.c_str());
	message.append(content);

	Chat_Record_Info chat_item;
	chat_item.content = message;
	addChatRecord(chat_item);
}

//显示聊天气泡
void GameChatLayer::showBubble(Vec2 bubblePos, CHAR content[], const std::string &nickName, bool isBubbleFlipped,
	bool showUserName)
{
	//显示气泡
	auto bubbleNode = Node::create();
	this->getParent()->addChild(bubbleNode, 99999999);
	bubbleNode->setAnchorPoint(Vec2::ZERO);
	bubbleNode->setPosition(bubblePos);
	
	auto bubbleSprite = Sprite::create(BUBBLE_PATH);
	auto tmpSize = bubbleSprite->getContentSize();
	Rect fullRect(0, 0, tmpSize.width, tmpSize.height);
	Rect insetRect = Rect(30, 25, 10, 10);//自动缩放的区域

	auto bubbleBackGround = ui::Scale9Sprite::create(BUBBLE_PATH, fullRect, insetRect);
	bubbleBackGround->setAnchorPoint(Vec2::ZERO);
	bubbleNode->addChild(bubbleBackGround);

	//初始化富文本
	auto messageRichText = RichText::create();
	messageRichText->ignoreContentAdaptWithSize(false);
	messageRichText->setAnchorPoint(Vec2::ZERO);
	messageRichText->setContentSize(Size(320, 58));
	bubbleNode->addChild(messageRichText, 100);

	RichElementText* textElement = nullptr;
	textElement = RichElementText::create(1, colorBlue, 255, GBKToUtf8(" "), "Arial", 18);

	messageRichText->pushBackElement(textElement);

	char num[3] = { 0, 0, 0 };
	int _RichTag = 0;
	auto maxEmotionCount = 68;
	int ImageEmotionNum = 0;//表情个数，用来计算表情需占用的位置
	int ImageEmotionSize = 24;
	int fontSize = 18;
	float messageLength = 0;
	Size lineSize(320, 45);
	std::string word;

	//显示说话者名字
	if (showUserName)
	{
		auto message = StringUtils::format("[%s说]:", nickName.c_str());
		auto text = RichElementText::create(_RichTag++, colorBlack, 255, GBKToUtf8(message.c_str()), "Arial", fontSize);
		messageRichText->pushBackElement(text);

		messageLength += 0.5f*message.length();
	}

	for (int i = 0; content[i] != '\0'; i++)
	{
		if (content[i] == '/' && content[i + 1] == ':')
		{
			// 符合表情条件，再判断是否在表情范围内
			num[0] = content[i + 2];
			num[1] = content[i + 3];
			auto imageNumber = atoi(num);
			// 一定是表情
			if (imageNumber >= 0 && imageNumber < maxEmotionCount)
			{
				if (word.length() > 0)
				{
					RichElementText* rtext = RichElementText::create(_RichTag++, colorBlack, 255, GBKToUtf8(word.c_str()), "Arial", fontSize);
					messageRichText->pushBackElement(rtext);
					word.clear();
				}
				ImageEmotionNum++;
				RichElementImage* img = RichElementImage::create(_RichTag++, Color3B(255, 255, 255), 255, EMOTION_PATH + StringUtils::format("im%d.png", imageNumber));
				messageRichText->pushBackElement(img);
				i += 3;
			}
			//不是表情
			else
			{
				messageLength += 0.5f;
				word.push_back(content[i]);
			}
		}
		else
		{
			messageLength += 0.5f;
			word.push_back(content[i]);
		}
	}

	//显示文本
	if (word.length() > 0)
	{
		auto text = RichElementText::create(_RichTag++, colorBlack, 255, GBKToUtf8(word.c_str()), "Arial", fontSize);
		messageRichText->pushBackElement(text);
		word.clear();
	}

	float realAllLenght = messageLength * fontSize + ImageEmotionNum * ImageEmotionSize;//文本图片总的真实大小
	float msgRowNum = realAllLenght / 320.0f;
	float bgWidht, bgHeight;
	bgWidht = bgHeight = 0;
	if (msgRowNum < 1)
	{
		//msgRowNum小于1，说明消息只有一行，需缩放气泡的宽
		if (msgRowNum <= 0.12f)
		{
			bgWidht = 80;
			bgHeight = lineSize.height;
		}
		else
		{
			bgWidht = realAllLenght + 50;
			bgHeight = lineSize.height;
		}
	}
	else
	{
		//msgRowNum大于1，需缩放气泡的高
		bgWidht = lineSize.width + 50;
		bgHeight = (20.0f * (int)msgRowNum) + lineSize.height;
	}
	//设置气泡大小
	bubbleBackGround->setContentSize(Size(bgWidht, bgHeight));
	messageRichText->setContentSize(Size(lineSize.width, bgHeight));
	messageRichText->setPosition(Vec2(bubbleBackGround->getPositionX() + 30, bubbleBackGround->getPositionY() - 10));
	//messageRichText->setPosition(bubbleBackGround->getPosition());

	if (isBubbleFlipped)
	{
		auto bubbleSize = bubbleBackGround->getContentSize();
		messageRichText->setPosition(Vec2(bubbleBackGround->getPositionX() - bubbleSize.width + 10, bubbleBackGround->getPositionY() - 10));
		bubbleBackGround->setFlippedX(true);
	}

	bubbleNode->setScale(1.5);
	bubbleNode->runAction(Sequence::create(DelayTime::create(8.0f), RemoveSelf::create(true), nullptr));
}

//显示语音聊天
void GameChatLayer::onHandleVocieMessage(UserInfoStruct* userInfo, int voiceID, bool showBuble /*= false*/, Vec2 bubblePos /*= Vec2::ZERO*/, 
	bool isBubbleFlipped /*= false*/, bool showUserName /*= true*/)
{
	if (nullptr == userInfo) //如果为空，则是同一个房间，不同桌子, 直接返回
	{
		return;
	}

	//增加聊天记录
	Chat_Record_Info chat_info;
	chat_info.tag = voiceID;
	chat_info.content = StringUtils::format("[%s说]:", userInfo->nickName);
	addChatRecord(chat_info);

	////如果是自己发的语音则马上显示语音记录
	//if (userInfo->dwUserID == PlatformLogic()->loginResult.dwUserID)
	//{
	//	updateRecordListView();
	//}

	if (showBuble)
	{
		showVoiceBubble(bubblePos, userInfo->nickName, voiceID, showUserName, isBubbleFlipped);
		closeChatLayer();
	}
}

//显示语音气泡
void GameChatLayer::showVoiceBubble(Vec2 bubblePos, const std::string &nickName, int voiceID, 
	bool showUserName /*= false*/, bool isBubbleFlipped /*= false*/)
{
	//显示气泡
	auto bubbleImageView = ImageView::create(BUBBLE_PATH);
	this->getParent()->addChild(bubbleImageView, 99999999);
	bubbleImageView->setScale9Enabled(true);
	bubbleImageView->setTouchEnabled(true);
	bubbleImageView->setAnchorPoint(Vec2::ZERO);
	bubbleImageView->setPosition(bubblePos);
	//语音聊天不显示气泡背景
	bubbleImageView->setOpacity(0);

	//初始化富文本
	auto messageRichText = RichText::create();
	messageRichText->ignoreContentAdaptWithSize(false);
	messageRichText->setAnchorPoint(Vec2::ZERO);
	messageRichText->setContentSize(Size(320, 58));
	bubbleImageView->setSwallowTouches(true);
	messageRichText->setVisible(true);
	bubbleImageView->addChild(messageRichText, 100);

	RichElementText* textElement = nullptr;
	textElement = RichElementText::create(1, colorBlue, 255, GBKToUtf8(" "), "Arial", 18);

	messageRichText->pushBackElement(textElement);

	int _RichTag = 0;
	int fontSize = 18;
	
	Size lineSize;

	if (!showUserName)
	{
		lineSize.width = 200;
		lineSize.height = 50;
	}
	else
	{
		lineSize.width = 300;
		lineSize.height = 58;
	}

	//显示说话者名字
	if (showUserName)
	{
		std::string word = StringUtils::format("[%s说]:", nickName.c_str());
		auto text = RichElementText::create(_RichTag++, colorBlack, 255, GBKToUtf8(word.c_str()), "Arial", fontSize);
		messageRichText->pushBackElement(text);	
	}
	//显示语音图片
	RichElementImage* img = RichElementImage::create(_RichTag++, Color3B(255, 255, 255), 255, Chat_Image_Voice);
	messageRichText->pushBackElement(img);

	//设置气泡大小
	//bubbleBackGround->setContentSize(lineSize);
	bubbleImageView->setContentSize(lineSize);
	messageRichText->setContentSize(lineSize);
	messageRichText->setPosition(Vec2(30, -10));
	//messageRichText->setPosition(Vec2(bubbleBackGround->getPositionX() + 30, bubbleBackGround->getPositionY() - 10));

	bubbleImageView->setTag(voiceID);
	bubbleImageView->addTouchEventListener(CC_CALLBACK_2(GameChatLayer::chatBubbleEventCallBack, this));

	if (isBubbleFlipped)
	{
		//auto bubbleSize = bubbleImageView->getContentSize();
		//messageRichText->setPosition(Vec2(bubbleImageView->getPositionX() - bubbleSize.width + 10, bubbleImageView->getPositionY() - 10));
		if (showUserName)
		{
			messageRichText->setAnchorPoint(Vec2(0.5, 0.5));
			messageRichText->setPosition(Vec2(lineSize.width*0.5 - 10, lineSize.height*0.5 - 10));
			messageRichText->setFlippedX(true);
		}
		bubbleImageView->setFlippedX(true);
	}

	bubbleImageView->setScale(1.5);
	bubbleImageView->runAction(Sequence::create(DelayTime::create(8.0f), RemoveSelf::create(true), nullptr));
}

void GameChatLayer::resumeBackgroundMusic(float delta)
{
	HNAudioEngine::getInstance()->resumeBackgroundMusic();
}