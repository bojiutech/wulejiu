#include "Cherry97GameShare.h"
#include "HNLobbyExport.h"

using namespace ui;

namespace Cherry97{
	static const char* HISTORY_CSB = "Cherry97/Cherry97Ui/ShareNode.csb";    //奖励框
	GameShare* GameShare::create(GameTableUICallback* uicallback)
	{
		GameShare* ref = new GameShare();
		if (ref->init(uicallback))
		{
			ref->autorelease();
			return ref;
		}
		CC_SAFE_DELETE(ref);
		return nullptr;
	}

	bool GameShare::init(GameTableUICallback* uicallback)
	{
		if (!HN::HNLayer::init())
		{
			return false;
		}
		_uicallback = uicallback;
		// 添加屏蔽层
		auto colorLayer = LayerColor::create(Color4B(0, 0, 0, 0));
		addChild(colorLayer);

		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan = [=](Touch* touch, Event* event){
			return true;
		};
		touchListener->setSwallowTouches(true);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, colorLayer);

		winsize = Director::getInstance()->getWinSize();
		_loader = CSLoader::createNode(HISTORY_CSB);
		addChild(_loader);
		_layout = (Layout*)_loader->getChildByName("Panel_1");
		_layout->setPosition(Vec2(winsize.width / 2, winsize.height / 2));
		_layout->setVisible(true);
		m_textAward = (TextAtlas*)_layout->getChildByName("AtlasLabel_award");
		m_shareButton = (Button*)_layout->getChildByName("Button_share");
		m_shareButton->addTouchEventListener(CC_CALLBACK_2(GameShare::btnCallBack, this));

		m_closeButton = (Button*)_layout->getChildByName("Button_close");
		m_closeButton->addTouchEventListener(CC_CALLBACK_2(GameShare::btnCallBack, this));
		return true;
	}

	void GameShare::setShareAward(int iShareAward){
		std::string str = StringUtils::format("%d", iShareAward);
		m_textAward->setString(GBKToUtf8(str));
	}

	void GameShare::btnCallBack(cocos2d::Ref* pSender, ui::Widget::TouchEventType touchtype)
	{
		if (Widget::TouchEventType::ENDED != touchtype) return;
		auto btn = (Button*)pSender;
		HNAudioEngine::getInstance()->playEffect(GAME_SOUND_BUTTON);
		auto winSize = Director::getInstance()->getWinSize();

		std::string name(btn->getName());
		if (btn == m_closeButton)
		{
			_layout->runAction(Sequence::create(ScaleTo::create(0.3f, 0.1f), CallFunc::create([=](){
				this->removeFromParent();
			}), nullptr));
		}
		else if (btn == m_shareButton){
			std::string param = StringUtils::format("action=GetShareInfo&key=");
			HNHttpRequest::getInstance()->request("game_share", network::HttpRequest::Type::POST, PlatformConfig::getInstance()->getEditUrl(), param);
			HNHttpRequest::getInstance()->addObserver(this);
		}
	}

	void GameShare::onHttpResponse(const std::string& requestName, bool isSucceed, const std::string &responseData){
		if (!isSucceed){
			return;
		}

		if (requestName.compare("game_share") == 0){
			dealShareResp(responseData);
		}
	}

	void GameShare::dealShareResp(const std::string& data){
		std::string shareUrl = "";
		std::string shareContent = "";
		std::string shareImage = "";
		rapidjson::Document doc;
		doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
		if (doc.HasParseError() || !doc.IsObject() || !doc.HasMember("content") || !doc["content"].IsArray()){
			return;
		}

		for (auto i = 0; i < doc["content"].Size(); i++){
			if (!doc["content"][i].IsObject() || !doc["content"][i].HasMember("ParaName") || !doc["content"][i].HasMember("ParaValue")){
				continue;
			}

			std::string name = doc["content"][i]["ParaName"].GetString();
			std::string value = doc["content"][i]["ParaValue"].GetString();

			if (name.compare("ShareUrl") == 0)
			{
				shareUrl = value;
			}
			else if (name.compare("ShareContent") == 0)
			{
				shareContent = value;
			}
			else if (name.compare("ShareBgPic") == 0)
			{
				shareImage = value;
			}
		}
		UMengSocial::getInstance()->onShareCallBack = [=](bool success, int platform, const std::string& errorMsg) {
			if(!success){
				GamePromptLayer::create()->showPrompt(GBKToUtf8(errorMsg.c_str()));
			}
			else{
				updateBankData();
			}
		};
		shareContent = "您成功分享朋友圈，获得分享奖励" + m_textAward->getString() + "金币。下载注册就送大礼！";
		UMengSocial::getInstance()->doShare(GBKToUtf8(shareContent), GBKToUtf8("欢迎下载舞乐久在线棋牌竞技平台，享受棋牌竞技的快乐！"), shareUrl, shareImage, 2);

//		updateBankData();
		
	}

	void GameShare::updateBankData(){
		LLONG award = atol(m_textAward->getString().c_str());//当前总筹码
		TMSG_GP_BankCheck BankCheck = { 0 };
		BankCheck.operate_type = 3;
		BankCheck.user_id = PlatformLogic()->loginResult.dwUserID;
		BankCheck.game_id = 0;
		BankCheck.money = award;
		if (BankCheck.money <= 0)
		{
			GamePromptLayer::create()->showPrompt(GBKToUtf8("请输入合法金额。"));
			return;
		}
		PlatformLogic()->sendData(MDM_GP_BANK, ASS_GP_BANK_CHECK, &BankCheck, sizeof(BankCheck),
			HN_SOCKET_CALLBACK(GameShare::bankerEventSelector, this));
	}

	bool GameShare::bankerEventSelector(HNSocketMessage* socketMessage)
	{
		UINT bAssistantID = socketMessage->messageHead.bAssistantID;
		UINT bHandleCode = socketMessage->messageHead.bHandleCode;
		
		// 存取钱
	    if (ASS_GP_BANK_CHECK == bAssistantID)
		{
			switch (bHandleCode)
			{
			case HC_GP_BANK_CHECK_SUC://					0			//操作成功
			{

				std::string str = "您成功分享朋友圈，分享奖励" + m_textAward->getString() + "金币已存入保险箱，请查收。";
				GamePromptLayer::create()->showPrompt(GBKToUtf8(str));

				_layout->runAction(Sequence::create(ScaleTo::create(0.3f, 0.1f), CallFunc::create([=](){
					this->removeFromParent();
				}), nullptr));

			} break;
			case HC_GP_BANK_CHECK_NO_USER://				1			//没有找到用户
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8("金币不足无法存入。"));
			} break;
			case HC_GP_BANK_CHECK_ERR_PWD://				2			//错误密码
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8("错误密码。"));
			} break;
			case HC_GP_BANK_CHECK_NOT_MONEY://				4			//余额不足
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8("余额不足。"));
			} break;
			case HC_GP_BANK_CHECK_CAN_NOT_OPEN://			5			//房间中不能进行存取操作
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8("房间中不能进行存取操作。"));
			} break;
			default:
				break;
			}
		}
		return true;
	}
	GameShare::GameShare()
	{
	}

	GameShare::~GameShare(){
		HNHttpRequest::getInstance()->removeObserver(this);
		PlatformLogic()->removeEventSelector(MDM_GP_BANK, ASS_GP_BANK_OPEN);
		PlatformLogic()->removeEventSelector(MDM_GP_BANK, ASS_GP_BANK_CHPWD);
		PlatformLogic()->removeEventSelector(MDM_GP_BANK, ASS_GP_BANK_CHECK);
		PlatformLogic()->removeEventSelector(MDM_GP_BANK, ASS_GP_BANK_TRANSFER);
	}
}