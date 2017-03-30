#include "HNLobby/GameMenu/GameLandLayer.h"
#include "HNLobby/PlatformDefine.h"
#include "HNLobby/GamePrompt.h"

static const char* LANDUI_PATH = "platform/LoginorRegistUi/Login/loginUI.csb";

#define Word_Empty_Name		GBKToUtf8("�˺Ų���Ϊ��!")
#define Word_Empty_Pass		GBKToUtf8("���벻��Ϊ��!")

LandLayer::LandLayer()
	: onLoginCallBack(nullptr)
	, onCloseCallBack(nullptr)
	, onRegistCallBack(nullptr)
	, _isGetPassWord(false)
	, _isOpenLayer(true)
{	
	memset(&_landUI, 0x0, sizeof(_landUI));
}

LandLayer::~LandLayer()
{	

}

void LandLayer::closeLand()
{
	_landUI.backGround->runAction(Sequence::create(ScaleTo::create(0.1f, 0.1f), CCCallFunc::create([&]()
	{
		if (nullptr != onCloseCallBack)
		{
			onCloseCallBack();
		}
		this->removeFromParent();
	}), nullptr));
}

bool LandLayer::init()
{
	if (!HNLayer::init()) return false;
	//���κ���Ĳ�
	colorLayer = LayerColor::create( Color4B( 0, 0, 0, 100));
	addChild(colorLayer);
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		auto target = dynamic_cast<LandLayer*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect( 0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode))
		{
			return true;
		}
		else
		{
			return false;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	Size winSize = Director::getInstance()->getWinSize();

	// ��¼����ui
	_landUI.landUI = CSLoader::createNode(LANDUI_PATH);
	_landUI.landUI->setPosition(Vec2(winSize / 2));
	addChild(_landUI.landUI, 2, 2);
	auto landlayout = _landUI.landUI->getChildByName("Panel_1");

	//��¼����
	_landUI.backGround =(ImageView*)landlayout->getChildByName("Image_BG");

	// �رհ�ť
	Button* Btn_close = (Button*)_landUI.backGround->getChildByName("Button_close");
	Btn_close->addTouchEventListener(CC_CALLBACK_2(LandLayer::closeEventCallback, this));

	// ��½��ť
	Button* Btn_land = (Button*)_landUI.backGround->getChildByName("Button_land");
	Btn_land->addTouchEventListener(CC_CALLBACK_2(LandLayer::landEventCallback, this));

	// ע���ʺŰ�ť
	Button* Btn_regist = (Button*)_landUI.backGround->getChildByName("Button_regist");
	Btn_regist->addTouchEventListener(CC_CALLBACK_2(LandLayer::registEventCallback, this));

	auto userDefault = UserDefault::getInstance();
	std::string username = userDefault->getStringForKey(USERNAME_TEXT);
	std::string password = userDefault->getStringForKey(PASSWORD_TEXT);
	bool save = userDefault->getBoolForKey(SAVE_TEXT);

	// �˺������
	auto TextField_userName = (TextField*)_landUI.backGround->getChildByName("TextField_userName");
	TextField_userName->setVisible(false);
	// �˺������
	_landUI.editBoxUserName = HNEditBox::createEditBox(TextField_userName, this);
	_landUI.editBoxUserName->setString(username);

	// �������븴ѡ��
	_landUI.checkBoxSave = (CheckBox*)_landUI.backGround->getChildByName("CheckBox_save");
	_landUI.checkBoxSave->setSelected(save);
	_landUI.checkBoxSave->addEventListener(CheckBox::ccCheckBoxCallback(CC_CALLBACK_2( LandLayer::checkBoxCallback, this)));

	// ���������
	auto textField_PassWord = (TextField* )_landUI.backGround->getChildByName("TextField_passWord");
	textField_PassWord->setVisible(false);
	// ���������
	_landUI.editBoxPassWord = HNEditBox::createEditBox(textField_PassWord, this);
	_landUI.editBoxPassWord->setInputFlag(cocos2d::ui::EditBox::InputFlag::PASSWORD);
	if (_landUI.checkBoxSave->isSelected())
	{
		_isGetPassWord = true;
		_landUI.editBoxPassWord->setString("******");
	}
	return true;
}

void LandLayer::landEventCallback(Ref* pSender, Widget::TouchEventType type)
{
	if (Widget::TouchEventType::ENDED != type) return;
	auto btn = (Button*)pSender;

	HNAudioEngine::getInstance()->playEffect(GAME_SOUND_BUTTON);
	do 
	{
		// ��ȡ������˺�
		std::string userName = _landUI.editBoxUserName->getString();
		if (userName.empty())
		{
			GamePromptLayer::create()->showPrompt(Word_Empty_Name);
			break;
		}

		// ��ȡ���������
		std::string passWord = _landUI.editBoxPassWord->getString(); 
		if (passWord.empty())
		{
			GamePromptLayer::create()->showPrompt(Word_Empty_Pass);
			break;
		}
		auto userdefault = UserDefault::getInstance();
		std::string savePassWord = userdefault->getStringForKey(PASSWORD_TEXT);
			if (nullptr != onLoginCallBack)
			{
				if (_isGetPassWord)
				{
					onLoginCallBack(userName, savePassWord);
				}
				else
				{
					passWord = MD5_CTX::MD5String(passWord);
					onLoginCallBack(userName, passWord);
				}
			}
	} while (0);
}

void LandLayer::closeEventCallback(Ref* pSender, Widget::TouchEventType type)
{
	Button* selectedBtn = (Button*)pSender;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		selectedBtn->setColor(Color3B(170,170,170));
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			HNAudioEngine::getInstance()->playEffect(GAME_SOUND_CLOSE);
			selectedBtn->setColor(Color3B(255,255,255));
			closeLand();
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		selectedBtn->setColor(Color3B(255,255,255));
		break;
	default:
		break;
	}
}

void LandLayer::checkBoxCallback(Ref* pSender, CheckBox::EventType type)
{
	auto userDefault = UserDefault::getInstance();
	switch (type)
	{
	case cocos2d::ui::CheckBox::EventType::SELECTED:
		userDefault->setBoolForKey(SAVE_TEXT, true);
		break;
	case cocos2d::ui::CheckBox::EventType::UNSELECTED:
		userDefault->setBoolForKey(SAVE_TEXT, false);
		_landUI.editBoxPassWord->setText("");
		break;
	default:
		break;
	}
	userDefault->flush();
}

// ע�ᰴť�ص�����
void LandLayer::registEventCallback(Ref* pSender, Widget::TouchEventType type)
{
	if (Widget::TouchEventType::ENDED != type) return;
	auto btn = (Button*)pSender;
	
	auto winSize = Director::getInstance()->getWinSize();
	HNAudioEngine::getInstance()->playEffect(GAME_SOUND_CLOSE);

	_landUI.backGround->runAction(Sequence::create(ScaleTo::create(0.1f, 0.1f), CCCallFunc::create([&](){
		if (nullptr != onRegistCallBack)
		{
			onRegistCallBack();
		}
		this->removeFromParent();
		}), nullptr));
}

void LandLayer::editBoxEditingDidBegin(EditBox* editBox)
{
	_isOpenLayer = false;
}

void LandLayer::editBoxTextChanged(ui::EditBox* editBox, const std::string& text)
{
	if (!_isOpenLayer)
	{
		if (editBox == _landUI.editBoxPassWord && text != "******")
		{
			if (_isGetPassWord)
			{
				UserDefault::getInstance()->setStringForKey(PASSWORD_TEXT, "0");
				_isGetPassWord = false;
			}
		}
	}
}
