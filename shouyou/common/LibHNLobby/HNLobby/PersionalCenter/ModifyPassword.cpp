#include "ModifyPassword.h"
#include "HNLobby/FontConfig.h"
#include "HNLobby/PlatformDefine.h"
#include "HNLobby/GamePrompt.h"
#include "HNLobby/PersionalCenter/GameUserDataLayer.h"
#include <string>

static const char* MODIFYPASSWORD_JSON	= "platform/modifyPassWord/modifyPassWordNode.csb";

ModifyPasswordLayer::ModifyPasswordLayer()
{
	memset(&_ui, 0x0, sizeof(_ui));
}

ModifyPasswordLayer::~ModifyPasswordLayer()
{
	PlatformLogic()->removeEventSelector(MDM_GP_USERINFO, ASS_GP_USERINFO_ACCEPT);
	PlatformLogic()->removeEventSelector(MDM_GP_USERINFO, ASS_GP_USERINFO_NOTACCEPT);
}

void ModifyPasswordLayer::show(Node* parent, int zorder, int tag)
{
	CCAssert(nullptr != parent, "parent is nullptr");
	parent->addChild(this, zorder, tag);
}

void ModifyPasswordLayer::close()
{
	HNAudioEngine::getInstance()->playEffect(GAME_SOUND_CLOSE);
	_ui.modifyLoader->runAction(Sequence::create(ScaleTo::create(0.1f, 0.3f),  CCCallFunc::create([&]()
	{
		this->removeFromParent();
	}), nullptr));
}

bool ModifyPasswordLayer::init()
{
    if ( !HNLayer::init()) return false;
	Size winSize = Director::getInstance()->getWinSize();

	//���κ���Ĳ�
	auto colorLayer = LayerColor::create(Color4B(0, 0, 0, 100));
	addChild(colorLayer,1);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [=](Touch* touch ,Event* event){
		return true;
	};
	touchListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,colorLayer);

	// ������Ͽ򱳾�
	_ui.modifyLoader = CSLoader::createNode(MODIFYPASSWORD_JSON);
	_ui.modifyLoader->setPosition(winSize / 2);
	addChild(_ui.modifyLoader, 2);
	_ui.modifyLoader->setScale(0);
	_ui.modifyLoader->runAction(ScaleTo::create(0.2f, 1.0f));
	auto panel = (Layout*)_ui.modifyLoader->getChildByName("Panel_1");
	_ui.layout = (ImageView*)panel->getChildByName("modifyBg_1");
	//�رհ�ť
	_ui.Button_Cancel = (Button* )_ui.layout->getChildByName("Button_close");
	_ui.Button_Cancel ->addTouchEventListener(CC_CALLBACK_2(ModifyPasswordLayer::closeCallBack, this));
	//ȷ����ť
	_ui.Button_OK = (Button* )_ui.layout->getChildByName("Button_sure");
	_ui.Button_OK ->addTouchEventListener(CC_CALLBACK_2(ModifyPasswordLayer::okEventCallBack, this));
	//������ 
	auto oldPassword = (TextField*) _ui.layout->getChildByName("TextField_oldPass");
	oldPassword->setVisible(false);
	_ui.TextField_oldPassword = HNEditBox::createEditBox(oldPassword, this);
	_ui.TextField_oldPassword->setPasswordEnabled(true);
	//������
	auto NewPassword = (TextField*) _ui.layout->getChildByName("TextField_newPass");
	NewPassword->setVisible(false);
	_ui.TextField_NewPassword = HNEditBox::createEditBox(NewPassword, this);
	_ui.TextField_NewPassword->setPasswordEnabled(true);
	//ȷ������
	auto SurePassword = (TextField*) _ui.layout->getChildByName("TextField_surePass");
	SurePassword->setVisible(false);
	_ui.TextField_SurePassword = HNEditBox::createEditBox(SurePassword, this);
	_ui.TextField_SurePassword->setPasswordEnabled(true);


	//// ������Ͽ򱳾�
	//_ui.layout = dynamic_cast<Layout*>(GUIReader::getInstance()->widgetFromJsonFile(MODIFYPASSWORD_JSON));
	//if (nullptr != _ui.layout)
	//{
	//	_ui.layout->setAnchorPoint(Vec2(0.5f, 0.5f));
	//	_ui.layout->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	//	float _xScale = winSize.width / PlatformConfig::getInstance()->getPlatformDesignSize().width;
	//	float _yScale = winSize.height / PlatformConfig::getInstance()->getPlatformDesignSize().height;
	//	//uiLayout->setScale(MIN(_xScale, _yScale));
	//	addChild(_ui.layout, 2, 3);
	//
	//	_ui.TextField_NewPassword = (TextField*)Helper::seekWidgetByName(_ui.layout, "TextField_NewPassword");
	//	_ui.TextField_SurePassword = (TextField*)Helper::seekWidgetByName(_ui.layout, "TextField_SurePassword");
	//	_ui.Button_Cancel = (Button*)Helper::seekWidgetByName(_ui.layout, "Button_Cancel");
	//	_ui.Button_Cancel = (Button*)Helper::seekWidgetByName(_ui.layout, "Button_Cancel");
	//	_ui.Button_Cancel->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type)
	//	{
	//		if (Widget::TouchEventType::ENDED != type) return;
	//		close();
	//	});
	//	_ui.Button_OK = (Button*)Helper::seekWidgetByName(_ui.layout, "Button_OK");
	//	_ui.Button_OK->addTouchEventListener(CC_CALLBACK_2(ModifyPasswordLayer::okEventCallBack, this));
	//}
	//_userRect = _ui.layout->getBoundingBox();
	//// ����һ������¼�
	//auto MyListener = EventListenerTouchOneByOne::create();
	//MyListener->setSwallowTouches(true);
	//MyListener->onTouchBegan = [&](Touch* touch, Event* event)
	//{
	//	auto target = dynamic_cast<ModifyPasswordLayer*>(event->getCurrentTarget());       
	//	Point locationInNode = target->convertToNodeSpace(touch->getLocation());
	//	Size s = target->getContentSize();
	//	Rect rect = Rect(0, 0, s.width, s.height);
	//	if (rect.containsPoint(locationInNode))
	//	{
	//		if (_userRect.containsPoint(locationInNode)) return true;
	//		close();
	//		return true;
	//	}
	//	else
	//	{
	//		return false;
	//	}
	//};
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(MyListener, this);
	//float xScale = winSize.width / PlatformConfig::getInstance()->getPlatformDesignSize().width;
	//float yScale = winSize.height / PlatformConfig::getInstance()->getPlatformDesignSize().height;
	//_ui.layout->runAction(Sequence::create(ScaleTo::create(0.1f, MIN(xScale, yScale)), nullptr));

	return true;
}

void ModifyPasswordLayer::okEventCallBack(Ref* pSender, Widget::TouchEventType type)
{
	if (Widget::TouchEventType::ENDED != type) return;
	
	std::string newPassword = _ui.TextField_NewPassword->getString();
	std::string surePassword = _ui.TextField_SurePassword->getString();
	std::string oldPassword = _ui.TextField_oldPassword->getString();
	std::string MD5oldPass = MD5_CTX::MD5String(oldPassword).c_str();

	std::string tmp (PlatformLogic()->loginResult.szMD5Pass);

	do
	{
		if (oldPassword.empty())
		{
			GamePromptLayer::create()->showPrompt(GBKToUtf8("����������롣")); break;
		}
		if (newPassword.empty())
		{
			GamePromptLayer::create()->showPrompt(GBKToUtf8("�����������롣")); break;
		}

		if (surePassword.empty())
		{
			GamePromptLayer::create()->showPrompt(GBKToUtf8("������ȷ�����롣")); break;
		}
		if (0 != tmp.compare(MD5oldPass))
		{
			GamePromptLayer::create()->showPrompt(GBKToUtf8("�������������")); break;
		}
		if (0 != newPassword.compare(surePassword))
		{
			GamePromptLayer::create()->showPrompt(GBKToUtf8("�������ȷ�����벻��ͬ��")); break;
		}
		
		_userPswd = MD5_CTX::MD5String(newPassword).c_str();

		MSG_GP_S_ChPassword ChPassword;
		ChPassword.dwUserID = PlatformLogic()->loginResult.dwUserID;
		strcpy(ChPassword.szMD5OldPass, PlatformLogic()->loginResult.szMD5Pass);
		strcpy(ChPassword.szMD5NewPass, _userPswd.c_str());
		PlatformLogic()->sendData(MDM_GP_USERINFO, ASS_GP_USERINFO_UPDATE_PWD, &ChPassword, sizeof(ChPassword));
		PlatformLogic()->addEventSelector(MDM_GP_USERINFO, ASS_GP_USERINFO_ACCEPT, HN_SOCKET_CALLBACK(ModifyPasswordLayer::modifyPasswordSelector, this));
		PlatformLogic()->addEventSelector(MDM_GP_USERINFO, ASS_GP_USERINFO_NOTACCEPT, HN_SOCKET_CALLBACK(ModifyPasswordLayer::modifyPasswordSelector, this));
	} while (0);
}

bool ModifyPasswordLayer::modifyPasswordSelector(HNSocketMessage* socketMessage)
{
	if (ASS_GP_USERINFO_ACCEPT == socketMessage->messageHead.bAssistantID)	// ������ѽ���
	{
		auto userDefault = UserDefault::getInstance();
		userDefault->setStringForKey(PASSWORD_TEXT, _userPswd);
		userDefault->flush();
		_userPswd.clear();
		GamePromptLayer::create()->showPrompt(GBKToUtf8("�����޸ĳɹ���"));
	}
	else if (ASS_GP_USERINFO_NOTACCEPT == socketMessage->messageHead.bAssistantID)	// �����δ�ܽ���
	{
		GamePromptLayer::create()->showPrompt(GBKToUtf8("�����޸�ʧ�ܡ�"));
	}
	else
	{

	}
	return true;
}

void ModifyPasswordLayer::closeCallBack(Ref* pSender, Widget::TouchEventType type)
{
	Button* selectedBtn = (Button*)pSender;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		selectedBtn->setColor(Color3B(170, 170, 170));
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		selectedBtn->setColor(Color3B(255, 255, 255));
		close();
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		selectedBtn->setColor(Color3B(255, 255, 255));
		break;
	default:
		break;
	}
}