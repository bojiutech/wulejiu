#include "HNLobby/GameMenu/GameMenu.h"
#include "HNLobby/GamePlatform.h"
#include "HNLobby/PlatformDefine.h"
#include "HNLobby/GamePrompt.h"
#include "HNLobby/GameExitLayer.h"
#include "HNLobby/FontConfig.h"
#include "HNLobby/HNUpdate.h"
#include "HNLobby/GameMenu/GameLandLayer.h"
#include "HNLobby/GameMenu/GameRegisterLayer.h"
#include "HNUIExport.h"
#include "HNMarketExport.h"
#include "HNOpenExport.h"
#include "../Reconnection/Reconnection.h"

using namespace HN;

static const int   CHILD_TAG_LAND				= 100;
static const int   CHILD_TAG_REGISTER			= 101;

#define Word_Loading		"正在登陆..."
#define Word_Register		"正在注册..."
#define Word_Empty_Name		"账号不能为空!"
#define Word_Empty_Pass		"密码不能为空!"
#define Word_Wrong_Name		"登陆名字错误!"
#define Word_Wrong_Pass		"用户密码错误!"
#define Word_Logined		"帐号已经登录!"

static const char* GUEST_LOGIN_DEFAULT_PASSWORD = "123456";	

bool GameMenu::isVisitor = false;

static const char* MENU_BG						= "platform/hallBg.png";	
static const char* DECORATION_LEFT				= "platform/subViewBambooLeft.png";
static const char* DECORATION_RIGHT				= "platform/subViewBambooRight.png";

static const char* GUESTLOGIN_MENU_N				= "platform/menu/tourist1.png";

static const char* REGISTER_MENU_N				    = "platform/menu/register1.png";

static const char* ACCOUNTLOGIN_MENU_N				= "platform/menu/numberLogin1.png";

static const char* WEIXINLOGIN_MENU_N				= "platform/menu/weixinLogin1.png";

static const char* BIRDANIMATION_JSON				= "platform/animation/BirdAnimation.ExportJson";

static const int CHILD_LAYER_EXIT_TAG		    = 1000;			// 退出层标签

void GameMenu::createMenu()
{
	auto scene = Scene::create();
	auto mainlayer = GameMenu::create();
	scene->addChild(mainlayer);
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.3f, scene));

	PlatformConfig::getInstance()->setSceneState(PlatformConfig::SCENE_STATE::OTHER);
}


GameMenu::GameMenu()
{
	_logo = nullptr;
	_isAccountLogin = false;
	_gameRegist = new HNPlatformRegist(this);
	_gameLogin = new HNPlatformLogin(this);
}

GameMenu::~GameMenu()
{
	_gameRegist->stop();
	_gameLogin->stop();
	HN_SAFE_DELETE(_gameRegist);
	HN_SAFE_DELETE(_gameLogin);
	ArmatureDataManager::getInstance()->removeArmatureFileInfo(BIRDANIMATION_JSON);
}

void GameMenu::checkUpdate()
{
	HNUpdate* update = HNUpdate::create();
	if(update != nullptr)
	{
		this->addChild(update, 100);
		update->onFinishCallback = std::bind(&GameMenu::updateCheckFinishCallback, this,
			std::placeholders::_1,
			std::placeholders::_2,
			std::placeholders::_3,
			std::placeholders::_4);
		update->checkUpdate();
		update->setName("update");
	}
}

void GameMenu::updateCheckFinishCallback(bool updated, cocos2d::Node* pSender, const std::string& message, const std::string& installPath)
{
	if(updated)
	{		
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		HN::Operator::requestChannel("sysmodule", "installApp", installPath);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
         Application::getInstance()->openURL(PlatformConfig::getInstance()->getOnlineInstallUrl_iOS(installPath));
#endif
		if(pSender != nullptr)
		{
			pSender->removeFromParent();
		}
	}
	else 
	{
		std::string str(GBKToUtf8("更新失败！"));
		str.append(message);
		GamePromptLayer::create()->showPrompt(str);
		if(pSender != nullptr)
		{
			pSender->removeFromParent();
		}
	}
}

bool GameMenu::init()
{
	if (!HNLayer::init()) 
	{
		return false;
	}		

	enableKeyboard();
	setBackGroundImage(MENU_BG);

	Size winSize = Director::getInstance()->getWinSize();	

	// 加载ICON
	loadIcon();

	//屏幕显示竹叶-左上
	auto Decoration_left = Sprite::create(DECORATION_LEFT);
	Decoration_left->setAnchorPoint(Vec2(0.0f, 1.0f));
	Decoration_left->setPosition(Vec2(0.f, winSize.height));
	addChild(Decoration_left, 1);

	//屏幕显示竹叶-右上
	auto Decoration_right = Sprite::create(DECORATION_RIGHT);
	Decoration_right->setAnchorPoint(Vec2(1.0f, 1.0f));
	Decoration_right->setPosition(Vec2(winSize.width, winSize.height));
	addChild(Decoration_right, 1);

	// 游客登录按钮
	_buttonGuestLogin = Button::create(GUESTLOGIN_MENU_N);
	_buttonGuestLogin->setPosition(Vec2(winSize.width + _buttonGuestLogin->getContentSize().width, winSize.height * 0.7f));
	_buttonGuestLogin->addTouchEventListener(CC_CALLBACK_2(GameMenu::guestLoginEventCallback, this));
	addChild(_buttonGuestLogin, 1);

	// 账号登录按钮
	_buttonAccountLogin = Button::create(ACCOUNTLOGIN_MENU_N);
	_buttonAccountLogin->setPosition(Vec2(winSize.width + _buttonAccountLogin->getContentSize().width, winSize.height * 0.5f));
	_buttonAccountLogin->addTouchEventListener(CC_CALLBACK_2(GameMenu::accountLoginEventCallback, this));
	addChild(_buttonAccountLogin, 1);

	//账号注册
	_buttonRegister = Button::create(REGISTER_MENU_N);
	_buttonRegister->setPosition(Vec2(winSize.width + _buttonRegister->getContentSize().width, winSize.height * 0.3f));
	_buttonRegister->addTouchEventListener(CC_CALLBACK_2(GameMenu::RegisterEventCallback, this));
	addChild(_buttonRegister, 1);
	_buttonRegister->setVisible(false);

	//微信登陆
	_buttonWeiXinLogin = Button::create(WEIXINLOGIN_MENU_N);
	_buttonWeiXinLogin->setPosition(Vec2(winSize.width + _buttonWeiXinLogin->getContentSize().width, winSize.height * 0.3f));
	_buttonWeiXinLogin->addTouchEventListener(CC_CALLBACK_2(GameMenu::onWeChatLoginClicked, this));
	addChild(_buttonWeiXinLogin, 1);
	_buttonWeiXinLogin->setVisible(Operator::requestChannel("sysmodule", "isAppInstalled", StringUtils::format("%d", WEIXIN)).compare("true") == 0);

	// 游戏版本
	std::string version = Operator::requestChannel("sysmodule", "getversion");
	auto gameVersion = createLabel(StringUtils::format(GBKToUtf8("版本：%s"), version.c_str()), 18);
	gameVersion->setAnchorPoint(Vec2(0.0f, 0.0f));
	gameVersion->setPosition(Vec2(10.f, 10.f));
	addChild(gameVersion, 2);

	// 预存储游戏配置
	auto userDefault = UserDefault::getInstance();
	int music = userDefault->getIntegerForKey(MUSIC_VALUE_TEXT, -1);
	int sound = userDefault->getIntegerForKey(SOUND_VALUE_TEXT, -1);

	if (INVALID_MUSIC_VALUE == music)
	{
		music = 60;
		userDefault->setIntegerForKey(MUSIC_VALUE_TEXT, 60);
	}
	if (INVALID_SOUND_VALUE == sound)
	{
		sound = 50;
		userDefault->setIntegerForKey(SOUND_VALUE_TEXT, 50);
	}

	// 播放背景音乐
	float musicValue = (float)(music) / 100;
	float effectValue = (float)(sound) / 100;
	if (musicValue <= 0.0f || effectValue <= 0.0f)
	{
		HNAudioEngine::getInstance()->setSwitchOfMusic(false);
	}
	HNAudioEngine::getInstance()->setBackgroundMusicVolume(musicValue);
	HNAudioEngine::getInstance()->setEffectsVolume(effectValue);

	return true;
}

void GameMenu::onEnterTransitionDidFinish()
{
	HNLayer::onEnterTransitionDidFinish();

	releaseUnusedRes();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	this->checkUpdate();
#endif

	Size winSize = Director::getInstance()->getWinSize();

	if (_logo) _logo->runAction(EaseBackOut::create(MoveTo::create(0.3f, Vec2(winSize.width / 3, winSize.height / 2))));

	if (_buttonGuestLogin) _buttonGuestLogin->runAction(EaseBackOut::create(MoveTo::create(0.2f, Vec2(winSize.width * 0.8f, winSize.height * 0.7f))));

	if (_buttonAccountLogin) _buttonAccountLogin->runAction(Sequence::create(DelayTime::create(0.2f), 
		EaseBackOut::create(MoveTo::create(0.2f, Vec2(winSize.width * 0.8f, winSize.height * 0.5f))), nullptr));

	//if (_buttonRegister) _buttonRegister->runAction(Sequence::create(DelayTime::create(0.4f), 
	//	EaseBackOut::create(MoveTo::create(0.2f, Vec2(winSize.width * 0.8f, winSize.height * 0.3f))), nullptr));
	if (_buttonWeiXinLogin) _buttonWeiXinLogin->runAction(Sequence::create(DelayTime::create(0.4f),
		EaseBackOut::create(MoveTo::create(0.2f, Vec2(winSize.width * 0.8f, winSize.height * 0.3f))), nullptr));
}

// 手机返回键监听回调函数
void GameMenu::onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (EventKeyboard::KeyCode::KEY_BACK == keyCode)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if (EventKeyboard::KeyCode::KEY_F1 == keyCode)
#endif
	{
		auto winSize = Director::getInstance()->getVisibleSize();
		do 
		{
			auto update = this->getChildByName("update");
			if (update != nullptr)
			{
				return;
			}

			RegisterLayer* registerLayer = (RegisterLayer*)this->getChildByTag(CHILD_TAG_REGISTER);
			if (nullptr != registerLayer)
			{
				registerLayer->closeRegister();
				break;
			}

			LandLayer* landLayer = (LandLayer*)this->getChildByTag(CHILD_TAG_LAND);
			if (nullptr != landLayer)
			{
				landLayer->closeLand();
				break;
			}

			// 调用离开游戏层
			GameExitLayer* exitLayer = dynamic_cast<GameExitLayer*>(this->getChildByTag(CHILD_LAYER_EXIT_TAG));
			if (nullptr == exitLayer)
			{
				auto exitLayer = GameExitLayer::create();
				exitLayer->setPosition(Size::ZERO);
				addChild(exitLayer, 100000000, CHILD_LAYER_EXIT_TAG);
			}
			else
			{
				exitLayer->callBackNo();
			}
		} while (0);
	}
}

//游客登陆回调
void GameMenu::guestLoginEventCallback(Ref* pSender, Widget::TouchEventType type)
{
	isVisitor = true;
	Button* selectedBtn = (Button*)pSender;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		selectedBtn->setColor(Color3B(170, 170, 170));
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		selectedBtn->setColor(Color3B(255, 255, 255));
		HNAudioEngine::getInstance()->playEffect(GAME_SOUND_BUTTON);
		LoadingLayer::createLoading(this, GBKToUtf8("游客登陆中......"), 22, LOADING);

		//游客登陆
		_gameRegist->start();
		_gameRegist->requestRegist();
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		selectedBtn->setColor(Color3B(255, 255, 255));
		break;
	default:
		break;
	}
}

// 账号登陆回调
void GameMenu::accountLoginEventCallback(Ref* pSender, Widget::TouchEventType type)
{
	isVisitor = false;
	auto winSize = Director::getInstance()->getWinSize();	
	Button* selectedBtn = (Button*)pSender;

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		selectedBtn->setColor(Color3B(170, 170, 170));
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			selectedBtn->setColor(Color3B(255, 255, 255));
			HNAudioEngine::getInstance()->playEffect(GAME_SOUND_BUTTON);
			LandLayer* landLayer = LandLayer::create();
			landLayer->onLoginCallBack = [this](const std::string& name, const std::string& psd)
			{
				_userName = name;
				_userPsd = psd;
				_isAccountLogin = true;

				//账号登陆
				enterGame(_userName, _userPsd);
				LoadingLayer::createLoading(this, GBKToUtf8(Word_Loading), 30, LOADING);
			};
			landLayer->onCloseCallBack = [this]()
			{

			};
			//注册按钮接口
			landLayer->onRegistCallBack = [this]()
			{
				registerActionCallBack();
			};
			this->addChild(landLayer, 3, CHILD_TAG_LAND);
			landLayer->ignoreAnchorPointForPosition(false);
			landLayer->setAnchorPoint(Vec2( 0.5f, 0.5f));
			landLayer->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		selectedBtn->setColor(Color3B(255, 255, 255));
		break;
	default:
		break;
	}
}

// 账号注册按钮回调函数
void GameMenu::RegisterEventCallback(Ref* pSender, Widget::TouchEventType type)
{
	auto winSize = Director::getInstance()->getWinSize();	
	Button* selectedBtn = (Button*)pSender;

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		selectedBtn->setColor(Color3B(170, 170, 170));
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			selectedBtn->setColor(Color3B(255, 255, 255));
			HNAudioEngine::getInstance()->playEffect(GAME_SOUND_BUTTON);
			registerActionCallBack();
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		selectedBtn->setColor(Color3B(255, 255, 255));
		break;
	default:
		break;
	}
}

// 微信登陆按钮回调函数
void GameMenu::onWeChatLoginClicked(Ref* pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED) return;

    /*
	auto callback = CALLBACK_PRAGMA([=](const std::string& args){
		//GamePromptLayer::create()->showPrompt(GBKToUtf8(args));
        
        rapidjson::Document doc;
        doc.Parse<rapidjson::kParseDefaultFlags>(args.c_str());
        if (!doc.HasParseError() && doc.IsObject())
        {
            bool isSuccess = doc["success"].GetBool();
            if (isSuccess) {
                
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
                //纬度
                std::string latitude = doc["latitude"].GetString();
                //经度
                std::string lontitude = doc["lontitude"].GetString();
                //详细地址
                std::string addr = doc["addr"].GetString();
                //国家
                std::string Country = doc["Country"].GetString();
                //城市
                std::string city = doc["city"].GetString();
                //区
                std::string District = doc["District"].GetString();
                //街道
                std::string Street = doc["Street"].GetString();
                
                
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                //纬度
                std::string latitude = doc["latitude"].GetString();
                //经度
                std::string lontitude = doc["lontitude"].GetString();
				
				//百度地图webapi请求地址
				//http://api.map.baidu.com/geocoder/v2/?ak=72ZLMg7P17Dl092USPcpGWsCqwdhoFb3&location=22.545624,113.948572&output=json      
                
#endif
            }
            else{
                GamePromptLayer::create()->showPrompt(GBKToUtf8("定位失败"));
            }
        }
        
		});

		std::string pos = Operator::requestChannel("hnLocation", "getLocation", "", &callback);
		return;
    */
    
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID && CC_TARGET_PLATFORM != CC_PLATFORM_IOS)
	GamePromptLayer::create()->showPrompt(GBKToUtf8("仅支持android和ios"));
	return;
#endif

	UMengSocial::getInstance()->onAuthorizeCallBack = [=](bool success, ThirdPartyLoginInfo* info, const std::string& errorMsg, int errorCode) {

		if (success)
		{
			log("isSuccess");
			_bAuthorize = false;
			_gameRegist->start();
			_gameRegist->requestRegist(ThirdLoginType::WeChat, "", "", "", Utf8ToGB(info->nickName.c_str()), info->unionid, info->headUrl, info->bBoy);
		}
		else
		{
			if (errorCode == -1 && !_bAuthorize)
			{
				_bAuthorize = true;
				UMengSocial::getInstance()->doThirdLogin(WEIXIN);
			}
			else
			{
				_bAuthorize = false;
				GamePromptLayer::create()->showPrompt(GBKToUtf8(errorMsg.c_str()));
			}
		}
	};

	UMengSocial::getInstance()->getLoginInfo(WEIXIN);

}

// QQ登陆按钮回调
void GameMenu::onQQLoginClicked(Ref* pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED) return;
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID && CC_TARGET_PLATFORM != CC_PLATFORM_IOS)
	GamePromptLayer::create()->showPrompt(GBKToUtf8("仅支持android和ios"));
	return;
#endif

	UMengSocial::getInstance()->onAuthorizeCallBack = [=](bool success, ThirdPartyLoginInfo* info, const std::string& errorMsg, int errorCode) {

		if (success)
		{
			log("isSuccess");
			_bAuthorize = false;
			//_gameRegist->start();
			//_gameRegist->requestRegist(ThirdLoginType::QQLogin, "", "", "", Utf8ToGB(info->nickName.c_str()), info->unionid, info->bBoy);
		}
		else
		{
			if (errorCode == -1 && !_bAuthorize)
			{
				_bAuthorize = true;
				UMengSocial::getInstance()->doThirdLogin(QQ);
			}
			else
			{
				_bAuthorize = false;
				GamePromptLayer::create()->showPrompt(GBKToUtf8(errorMsg.c_str()));
			}
		}
	};

	UMengSocial::getInstance()->getLoginInfo(QQ);
}

//注册按钮回调
void GameMenu::registerActionCallBack()
{
	isVisitor = false;
	auto winSize = Director::getInstance()->getWinSize();
	RegisterLayer* registerLayer = RegisterLayer::create();
	registerLayer->onRegisterCallBack = [this](const std::string& name, const std::string& psd)
	{
		_userName = name;
		_userPsd = psd;

		//注册
		_gameRegist->start();
		_gameRegist->requestRegist(1, _userName, MD5_CTX::MD5String(_userPsd));
		LoadingLayer::createLoading(this, GBKToUtf8(Word_Register), 30, LOADING);
	};

	registerLayer->onCloseCallBack = [this]()
	{		
	};

	this->addChild(registerLayer,3, CHILD_TAG_REGISTER);
	registerLayer->ignoreAnchorPointForPosition(false);
	registerLayer->setAnchorPoint(Vec2(0.5f, 0.5f));
	registerLayer->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
}

void GameMenu::onPlatformRegistCallback(bool success, bool fastRegist, const std::string& message,
							  const std::string&name, const std::string& pwd, int loginTimes)
{
	LoadingLayer::removeLoading(this);
	auto userDefault = UserDefault::getInstance();

	_gameRegist->stop();

	if (success)
	{
		std::string str;
	
		if (0 == loginTimes && !fastRegist)
		{
			userDefault->setBoolForKey(SAVE_TEXT, true);
			_isAccountLogin = true;

			str.clear();
			str.append("请牢记你的用户名以及密码。\n用户名称: ");
			str.append(name);
			str.append("\n用户密码: ");
			str.append(_userPsd);
			auto prompt = GamePromptLayer::create();
			prompt->showPrompt(str.c_str());
			prompt->setCallBack(CC_CALLBACK_0(GameMenu::enterGame, this, name, pwd));			
		}
		else
		{
			enterGame(name, pwd);
		}
	}
	else
	{
		GamePromptLayer::create()->showPrompt(message);
	}
}

void GameMenu::onPlatformLoginCallback(bool success, const std::string& message,
							 const std::string& name, const std::string& pwd)
{
	LoadingLayer::removeLoading(this);
	_gameLogin->stop();

	auto userDefault = UserDefault::getInstance();
	if (success)
	{
		if (_isAccountLogin)
		{
			saveUserInfo(name, pwd);
		}

		Reconnection::getInstance()->saveInfoAndCheckReconnection(name, pwd);
	}
	else
	{
		GamePromptLayer::create()->showPrompt(message);
	}
}

void GameMenu::saveUserInfo(const std::string& userName, const std::string& userPswd)
{
	auto userDefault = UserDefault::getInstance();

	if (userDefault->getBoolForKey(SAVE_TEXT))
	{
		if (!userName.empty())
		{
			userDefault->setStringForKey(USERNAME_TEXT, userName);
		}

		if (!userPswd.empty())
		{
			userDefault->setStringForKey(PASSWORD_TEXT, userPswd);
		}
	}
	else
	{
		userDefault->setStringForKey(USERNAME_TEXT, "");
		userDefault->setStringForKey(PASSWORD_TEXT, "");
	}
	userDefault->flush();
}

void GameMenu::enterGame(const std::string& userName, const std::string& userPswd)
{
	_gameLogin->start();
	_gameLogin->requestLogin(userName, userPswd);
}

void GameMenu::loadIcon()
{
	auto winSize = Director::getInstance()->getWinSize();
	bool isCustomer = false;
	do 
	{
		std::string filename = "config.json";
		if (FileUtils::getInstance()->isFileExist(filename))
		{
			std::string json = FileUtils::getInstance()->getStringFromFile(filename);
			rapidjson::Document doc;
			doc.Parse<rapidjson::kParseDefaultFlags>(json.c_str());
			if (doc.HasParseError())
			{
				break;
			}

			if (doc.IsObject() && doc.HasMember("isCustomer"))
			{
				isCustomer = doc["isCustomer"].GetBool();
			}
		}
	} while (0);

	if (isCustomer)
	{
		std::string gameLogo = PlatformConfig::getInstance()->getGameLogo();
		if (FileUtils::getInstance()->isFileExist(gameLogo))
		{
			_logo = Sprite::create(gameLogo);
			_logo->setPosition(Vec2(winSize.width / 3, winSize.height * 0.45f));
			addChild(_logo, 2);
		}
	}	
	else
	{
		ArmatureDataManager::getInstance()->addArmatureFileInfo(BIRDANIMATION_JSON);

		Armature* armature = Armature::create("BirdAnimation");
		armature->setScale(0.80f);
		armature->setPosition(Vec2(winSize.width / 3, winSize.height * 0.48f));
		armature->getAnimation()->play("Animation1");
		addChild(armature, 2);

		auto textAnima1 = Sprite::create("platform/text1.png");
		textAnima1->setAnchorPoint(Vec2(1, 0.5f));
		textAnima1->setScale(1.1f);
		textAnima1->setPosition(Vec2(0, winSize.height * 0.24f));
		addChild(textAnima1, 2);
		textAnima1->runAction(Sequence::create(DelayTime::create(0.3f),
			EaseBounceOut ::create(MoveBy::create(0.4f, Vec2(winSize.width * 0.34f, 0))), nullptr));

		auto textAnima2 = Sprite::create("platform/text2.png");
		textAnima2->setAnchorPoint(Vec2(0, 0.5f));
		textAnima2->setScale(0.9f);
		textAnima2->setPosition(Vec2(winSize.width, winSize.height * 0.17f));
		addChild(textAnima2, 2);
		textAnima2->runAction(Sequence::create(DelayTime::create(0.5f),
			EaseBounceOut ::create(MoveBy::create(0.6f, Vec2(-winSize.width * 0.76f, 0))), nullptr));
	}
}
