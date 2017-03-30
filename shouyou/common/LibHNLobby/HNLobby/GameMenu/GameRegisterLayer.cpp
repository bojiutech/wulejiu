#include "HNLobby/GameMenu/GameRegisterLayer.h"
#include "HNLobby/GamePrompt.h"
#include "HNLobby/GameWebView.h"
#include "HNLobby/PlatformDefine.h"
#include "HNMarketExport.h"

static const char* REGISTERUI_PATH = "platform/LoginorRegistUi/regist/registUI.csb";


RegisterLayer::RegisterLayer()
	: onRegisterCallBack(nullptr)
	, onCloseCallBack(nullptr)
{	
	memset(&_registUI, 0x0, sizeof(_registUI));
}

RegisterLayer::~RegisterLayer()
{	

}

void RegisterLayer::closeRegister()
{
	_registUI.registBG->runAction(Sequence::create(ScaleTo::create(0.1f, 0.1f), CCCallFunc::create([&]()
	{
		if (nullptr != onCloseCallBack)
		{
			onCloseCallBack();
		}
		this->removeFromParent();
	}), nullptr));
}

bool RegisterLayer::init()
{
	if (!HNLayer::init()) return false;

	//���κ���Ĳ�
	auto colorLayer = LayerColor::create(Color4B(0,0,0,100));
	addChild(colorLayer,1);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [=](Touch* touch , Event* event){
		return true;
	};
	touchListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,colorLayer);

	Size winSize = Director::getInstance()->getWinSize();
	Size frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();

	// ע�����ui
	_registUI.registUI = CSLoader::createNode(REGISTERUI_PATH);
	_registUI.registUI->setPosition(Vec2(winSize/2));
	addChild(_registUI.registUI, 2, 2);
	auto registLayout = _registUI.registUI->getChildByName("Panel_1");
	
	//��¼����
	_registUI.registBG = (ImageView*)registLayout->getChildByName("Image_registBG");

	// �رհ�ť
	Button * closeBtn = (Button*)_registUI.registBG->getChildByName("Button_close");
	closeBtn->addTouchEventListener(CC_CALLBACK_2(RegisterLayer::closeClickCallback, this));

	// ע�ᰴť
	Button * buttonRegister = (Button*)_registUI.registBG->getChildByName("Button_registOK");
	buttonRegister->addTouchEventListener(CC_CALLBACK_2(RegisterLayer::registerClickCallback, this));

	// ���ð�ť
	Button * buttonReset = (Button*)_registUI.registBG->getChildByName("Button_reset");
	buttonReset->addTouchEventListener(CC_CALLBACK_2(RegisterLayer::resetClickCallBack, this));

	// �˺������
	auto textField_UserName = (TextField*)_registUI.registBG->getChildByName("TextField_userName");
	textField_UserName->setVisible(false);
	_registUI.editBoxUserName = HNEditBox::createEditBox(textField_UserName, this);

	// ���������
	auto textField_PassWord = (TextField*)_registUI.registBG->getChildByName("TextField_passWord");
	textField_PassWord->setVisible(false);
	_registUI.editBoxPassWord = HNEditBox::createEditBox(textField_PassWord, this);
	_registUI.editBoxPassWord->setPasswordEnabled(true);

	// ͬ�⸴ѡ��
	_registUI.agree = (CheckBox*)_registUI.registBG->getChildByName("CheckBox_agree");
	_registUI.agree->setSelected(false);

	// ��ʾ���븴ѡ��
	_registUI.showPass = (CheckBox*)_registUI.registBG->getChildByName("CheckBox_showPass");
	_registUI.showPass->setSelected(false);
	_registUI.showPass->addEventListener(CheckBox::ccCheckBoxCallback(CC_CALLBACK_2(RegisterLayer::checkBoxCallback, this)));
	
	//Э�鰴ť
	Button * buttonagree = (Button*)_registUI.registBG->getChildByName("Button_agree");
	buttonagree->addTouchEventListener(CC_CALLBACK_2(RegisterLayer::AgreeClickCallBack, this));

	return true;
}

void RegisterLayer::registerClickCallback(Ref* pSender, Widget::TouchEventType type)
{
	if (Widget::TouchEventType::ENDED != type) return;
	auto btn = (Button*)pSender;

	if (!_registUI.agree->isSelected())
	{
		GamePromptLayer::create()->showPrompt(GBKToUtf8("�빴ѡͬ���û�Э�飡"));
		return;
	}	

	HNAudioEngine::getInstance()->playEffect(GAME_SOUND_BUTTON);

	do 
	{
		// ��ȡ������˺�
		std::string userName = _registUI.editBoxUserName->getString();

		if (userName.empty())
		{
			GamePromptLayer::create()->showPrompt(GBKToUtf8("�˺Ų���Ϊ�գ�"));
			break;
		}	

		if (_registUI.editBoxUserName->getStringLength() < 6 ||
			_registUI.editBoxUserName->getStringLength() > 12 ||
			!Tools::verifyNumberAndEnglish(userName))
		{
			GamePromptLayer::create()->showPrompt(GBKToUtf8("������6-12λӢ�Ļ������ʺţ�"));
			_registUI.editBoxUserName->setString("");
			break;
		}

		// ��ȡ���������
		std::string passWord = _registUI.editBoxPassWord->getString();
		if (passWord.empty())
		{
			GamePromptLayer::create()->showPrompt(GBKToUtf8("���벻��Ϊ�գ�"));
			break;
		}

		if (_registUI.editBoxPassWord->getStringLength() < 6 || 
			_registUI.editBoxPassWord->getStringLength() > 16 ||
			!Tools::verifyNumberAndEnglish(passWord))
		{
			GamePromptLayer::create()->showPrompt(GBKToUtf8("������6-16λӢ�Ļ��������룡"));
			_registUI.editBoxPassWord->setString("");
			break;
		}

		if (nullptr != onRegisterCallBack)
		{
			onRegisterCallBack(userName, passWord);
		}

	} while (0);
}

void RegisterLayer::resetClickCallBack(Ref* pSender, Widget::TouchEventType type)
{
	if (Widget::TouchEventType::ENDED != type) return;
	auto btn = (Button*)pSender;
	HNAudioEngine::getInstance()->playEffect(GAME_SOUND_BUTTON);

	_registUI.editBoxUserName->setText("");
	_registUI.editBoxPassWord->setText("");
}

void RegisterLayer::closeClickCallback(Ref* pSender, Widget::TouchEventType type)
{
	Button* selectedBtn = (Button*)pSender;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		selectedBtn->setColor(Color3B(170, 170, 170));
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			HNAudioEngine::getInstance()->playEffect(GAME_SOUND_CLOSE);
			selectedBtn->setColor(Color3B(255, 255, 255));
			closeRegister();
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		selectedBtn->setColor(Color3B(255, 255, 255));
		break;
	default:
		break;
	}
}

void RegisterLayer::AgreeClickCallBack(Ref* pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)		return;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	auto webViewLayer = GameWebViewLayer::create();
	webViewLayer->setTitle(GBKToUtf8("�û�Э��"));
	webViewLayer->showWebView(PlatformConfig::getInstance()->getProtocolUrl());
#endif
	
}

void RegisterLayer::checkBoxCallback(Ref* pSender, CheckBox::EventType type)
{
	_registUI.editBoxPassWord->setPasswordEnabled(_registUI.editBoxPassWord->isPasswordEnabled() ? false : true);
	_registUI.editBoxPassWord->setString(_registUI.editBoxPassWord->getString());
}

