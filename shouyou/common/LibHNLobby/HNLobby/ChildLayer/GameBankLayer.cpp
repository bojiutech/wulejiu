#include "GameBankLayer.h"
#include "HNLobby/PlatformDefine.h"
#include "HNLobby/GamePrompt.h"
#include "HNLobby/FontConfig.h"
#include "HNMarketExport.h"
#include <string>

static const char* BANKER_JSON_PATH		= "platform/bankUi/bankNode.csb";
static const char* BANKER_TITLE_CSB	    = "platform/bankUi/bankTitleNode.csb";

static const char* CLOSE_N				= "platform/close_n.png";   
static const char* CLOSE_D				= "platform/close_d.png";   

static const char* BANKER_BG			= "platform/bankUi/bankUiRes/second_payBg.png";      
static const char* BANK_TITLE			= "platform/bankUi/bankTitle.png";
static const char* CLOSE_MENU_N         = "platform/store/second_back.png";                         //closeMenu
static const char* SELF_FRAME	    = "platform/store/common_opaque.png";   

static const char* LEAF_LEFT	    = "platform/subViewBambooLeft.png";               
static const char* LEAF_RIGHT	    = "platform/subViewBambooRight.png";      
static const char* STAR_BIG	        = "platform/bankUi/bankUiRes/star1.png";               
static const char* STAR_SMALL	    = "platform/bankUi/bankUiRes/star2.png";   

GameBankLayer* GameBankLayer::createGameBank()
{
	GameBankLayer *pRet = new GameBankLayer(); 
	if (pRet && pRet->init()) 
	{ 
		pRet->autorelease(); 
		return pRet; 
	}
	CC_SAFE_DELETE(pRet);
	return pRet;
}

GameBankLayer::GameBankLayer() : _bankMoney(0), _walletMoney(0)
{
	memset(&_publicUi, 0x0, sizeof(_publicUi));
	memset(&_publicBtn, 0x0, sizeof(_publicBtn));
	memset(&_bankDataUi, 0x0, sizeof(_bankDataUi));
	memset(&_caozuoUi, 0x0, sizeof(_caozuoUi));
	memset(&_xiugaiUi, 0x0, sizeof(_xiugaiUi));
	memset(&_zhuanzhangUi, 0x0, sizeof(_zhuanzhangUi));

	/*memset(&_operatorUI, 0x0, sizeof(_operatorUI));
	memset(&_userDataUI, 0x0, sizeof(_userDataUI));
	memset(&_bankerUI, 0x0, sizeof(_bankerUI));
	memset(&_forwardUI, 0x0, sizeof(_forwardUI));*/
}

GameBankLayer::~GameBankLayer()
{
	PlatformLogic()->removeEventSelector(MDM_GP_BANK, ASS_GP_BANK_OPEN);
	PlatformLogic()->removeEventSelector(MDM_GP_BANK, ASS_GP_BANK_CHPWD);
	PlatformLogic()->removeEventSelector(MDM_GP_BANK, ASS_GP_BANK_CHECK);
	PlatformLogic()->removeEventSelector(MDM_GP_BANK, ASS_GP_BANK_TRANSFER);
}

void GameBankLayer::openBank(Node* parent, Vec2 vec, int zorder, int tag)
{
	CCAssert(nullptr != parent, "parent is nullptr");

	Size winSize = Director::getInstance()->getWinSize();
	this->setPosition(vec);
	parent->addChild(this, zorder, tag);
	//parent->runAction(EaseSineOut::create(MoveBy::create(0.2f, Vec2(-winSize.width, 0))));
	parent->runAction(MoveBy::create(0.3f, Vec2(-winSize.width, 0)));
}

void GameBankLayer::closeBank()
{
	HNAudioEngine::getInstance()->playEffect(GAME_SOUND_CLOSE);
	auto winSize = Director::getInstance()->getWinSize();
	this->getParent()->runAction(Sequence::create(MoveBy::create(0.3f, Vec2(winSize.width, 0)),
		CCCallFunc::create([&]()
		{
			this->removeFromParent();
		}), nullptr));
}

bool GameBankLayer::init()
{
	if (!HNLayer::init())
	{
		return false;
	}
	setBackGroundImage(BANKER_BG);

	Size winSize = Director::getInstance()->getWinSize();

	//����
	auto bankTitleLoader = CSLoader::createNode(BANKER_TITLE_CSB);
	bankTitleLoader->setPosition(Vec2(winSize.width / 2, winSize.height));
	addChild(bankTitleLoader, 2 );
	auto bankTitleLayout = (Layout*)bankTitleLoader->getChildByName("Panel_1");
	auto bankTitleContentSize = bankTitleLayout->getContentSize();
	bankTitleLayout->setContentSize(Size(bankTitleContentSize.width,( bankTitleContentSize.height*(1280.0f / winSize.width))/(720.0f/winSize.height)));

	//������ť
	_publicBtn.bankBtn = (Button*)bankTitleLayout->getChildByName("Button_bank");
	_publicBtn.bankBtn ->addTouchEventListener(CC_CALLBACK_2(GameBankLayer::navigationCheckBoxEvent, this));
	_publicBtn.bankBtn->setEnabled(false);
	_publicBtn.bankBtn->setBright(true);

	_publicBtn.dataBtn = (Button*)bankTitleLayout->getChildByName("Button_data");
	_publicBtn.dataBtn ->addTouchEventListener(CC_CALLBACK_2(GameBankLayer::navigationCheckBoxEvent, this));
	_publicBtn.dataBtn->setEnabled(true);
	_publicBtn.dataBtn->setBright(false);

	_publicBtn.zhuanzhangBtn = (Button*)bankTitleLayout->getChildByName("Button_zhuanzhang");
	_publicBtn.zhuanzhangBtn ->addTouchEventListener(CC_CALLBACK_2(GameBankLayer::navigationCheckBoxEvent, this));
	_publicBtn.zhuanzhangBtn->setEnabled(true);
	_publicBtn.zhuanzhangBtn->setBright(false);

	_publicBtn.zhuanzhangBtn->setVisible(Configuration::getInstance()->getValue("transfer", Value(false)).asBool());

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	if (PlatformConfig::getInstance()->isIAP())
	{
		_publicBtn.zhuanzhangBtn->setVisible(false);
	}
#endif


	//��Ʒ������ɫ
	auto storebg = cocos2d::ui::Scale9Sprite::create(SELF_FRAME);
	storebg->setAnchorPoint(Point(0.5f, 0));
	storebg->setPreferredSize(Size(1300 ,( 620.0f*(1280.0f / winSize.width))/(720.0f/winSize.height)));
	storebg->setPosition(Vec2(winSize.width / 2, 0));
	addChild(storebg,2);
	//��Ҷ
	auto leftLeaf = Sprite::create(LEAF_LEFT);
	leftLeaf->setAnchorPoint(Point(0, 1));
	leftLeaf->setPosition(0, winSize.height);
	addChild(leftLeaf, 2);
	auto rightleaf = Sprite::create(LEAF_RIGHT);
	rightleaf->setAnchorPoint(Point(1, 1));
	rightleaf->setPosition(winSize.width, winSize.height);
	addChild(rightleaf, 2);

	// �رհ�ť
	auto closeBtn = Button::create(CLOSE_MENU_N,CLOSE_MENU_N);
	closeBtn->setPosition(Vec2(winSize.width * 0.05f, winSize.height * 0.94f ));
	addChild(closeBtn,2);
	closeBtn->addTouchEventListener(CC_CALLBACK_2(GameBankLayer::closeEvent,this));

	// ���н���
	_publicUi.bankLoader = CSLoader::createNode(BANKER_JSON_PATH);
	_publicUi.bankLoader->setPosition(Vec2(winSize.width / 2, winSize.height / 2 - 35));
	addChild(_publicUi.bankLoader, 2);
	_publicUi.bankLayout = (Layout*)_publicUi.bankLoader->getChildByName("Panel_1");
	auto LoaderContentSize = _publicUi.bankLayout->getContentSize();
	_publicUi.bankLayout->setContentSize(Size(LoaderContentSize.width,( LoaderContentSize.height*(1280.0f / winSize.width))/(720.0f/winSize.height)));

	//��ȡԪ��
	auto yuanbao = (ImageView* ) _publicUi.bankLayout->getChildByName("Image_yuanbao");
	auto yuanbaoWidth = yuanbao->getContentSize().width;
	auto yuanbaoHeight = yuanbao->getContentSize().height;
	//��˸������
	auto starBig = Sprite::create(STAR_BIG);

	starBig->runAction(RepeatForever::create(Sequence::create(Spawn::create(Sequence::create(FadeIn::create(2.0f), FadeOut::create(3.0f), 
		nullptr), RotateBy::create(5.0f, 210), nullptr), DelayTime::create(5.0f), nullptr)));

	starBig->setPosition(Vec2(120, 120));
	yuanbao->addChild(starBig);
	
	auto starSmall1 = Sprite::create(STAR_SMALL);
	auto starSmall2 = Sprite::create(STAR_SMALL);
	starSmall1->runAction(RepeatForever::create(Sequence::create(Spawn::create(Sequence::create(FadeIn::create( 1.0f ), FadeOut::create( 2.0f ), 
		nullptr), RotateBy::create(3.0f, 150), nullptr), DelayTime::create(2.0f), nullptr)));

	starSmall2->runAction(RepeatForever::create(Sequence::create(Spawn::create(Sequence::create(FadeIn::create( 1.0f ), FadeOut::create( 2.0f ), 
		nullptr), RotateBy::create(3.0f, 150), nullptr), DelayTime::create(3.0f), nullptr)));

	starSmall1->setPosition(Vec2(70, 70));
	starSmall2->setPosition(Vec2(200, 60));
	yuanbao->addChild(starSmall1);
	yuanbao->addChild(starSmall2);

	_xiugaiUi.xiugaiBG = (ImageView*)_publicUi.bankLayout->getChildByName("Image_xiugaiMesg");
	_xiugaiUi.xiugaiBG->setVisible(false);
	_zhuanzhangUi.zhuanzhangBG = (ImageView*)_publicUi.bankLayout->getChildByName("Image_zhuanzhangMesg");
	_zhuanzhangUi.zhuanzhangBG->setVisible(false);

	// ����������ҳ��
	createOperatorUI(_publicUi.bankLayout);

	// �������ݴ�����ҳ��
	createUserDataUI(_publicUi.bankLayout);

	createForwardUI(_publicUi.bankLayout);

	createBankInfoUI(_publicUi.bankLayout);
	
	// ������
	PlatformLogic()->sendData(MDM_GP_BANK, ASS_GP_BANK_OPEN, nullptr, 0 , HN_SOCKET_CALLBACK(GameBankLayer::bankerEventSelector, this));

	return true;

}

void GameBankLayer::createOperatorUI(Layout* root)
{
	//��ʾ��������
	_caozuoUi.caozuoBG = (Sprite*)root->getChildByName("caozuo");
	_caozuoUi.caozuoBG->setVisible(true);
	//��ȡ����Ŀ��
	auto moneyFrame = (ImageView*) _caozuoUi.caozuoBG->getChildByName("Image_moneyFrame");
	auto mimaFrame = (ImageView*) _caozuoUi.caozuoBG->getChildByName("Image_mimaFrame");
	
	_caozuoUi.cunMoney = (CheckBox*) _caozuoUi.caozuoBG->getChildByName("CheckBox_cun");
	_caozuoUi.cunMoney ->addEventListener(CheckBox::ccCheckBoxCallback(CC_CALLBACK_2(GameBankLayer::operatorUIEventCheckBoxCallBack, this)));

	_caozuoUi.quMoney = (CheckBox*) _caozuoUi.caozuoBG->getChildByName("CheckBox_qu");
	_caozuoUi.quMoney->addEventListener(CheckBox::ccCheckBoxCallback(CC_CALLBACK_2(GameBankLayer::operatorUIEventCheckBoxCallBack, this)));

	auto TextField_CunorQuMoney = (TextField*) moneyFrame->getChildByName("TextField_CunorQuMoney");
	TextField_CunorQuMoney->setVisible(false);
	_caozuoUi.CunorQuMoney = HNEditBox::createEditBox(TextField_CunorQuMoney, this);
	_caozuoUi.CunorQuMoney->setInputMode(cocos2d::ui::EditBox::InputMode::PHONE_NUMBER);

	auto TextField_CunorQuMima = (TextField*) mimaFrame->getChildByName("TextField_CunorQuMima");
	TextField_CunorQuMima->setVisible(false);
	_caozuoUi.CunorQuMima = HNEditBox::createEditBox(TextField_CunorQuMima, this);
	_caozuoUi.CunorQuMima->setPasswordEnabled(true);

	_caozuoUi.sureBtn = (Button*) _caozuoUi.caozuoBG->getChildByName("Button_caozuoOK");
	_caozuoUi.sureBtn->addTouchEventListener(CC_CALLBACK_2(GameBankLayer::operatorUIEventCallBack, this));
}

void GameBankLayer::createUserDataUI(Layout* root)
{
	//��ʾ�޸Ľ���
	_xiugaiUi.xiugaiBG = (ImageView* ) root->getChildByName("Image_xiugaiMesg");
	_xiugaiUi.xiugaiBG->setVisible(false);

	//��ȡ����Ŀ��
	auto oldFrame = (ImageView* ) _xiugaiUi.xiugaiBG->getChildByName("Image_oldFrame");
	auto newFrame = (ImageView* ) _xiugaiUi.xiugaiBG->getChildByName("Image_newFrame");
	auto sureFrame = (ImageView* ) _xiugaiUi.xiugaiBG->getChildByName("Image_sureFrame");

	//��ȡ���������
	auto TextField_old = (TextField* ) oldFrame->getChildByName("TextField_OldMima");
	TextField_old->setVisible(false);
	_xiugaiUi.oldPassWord = HNEditBox::createEditBox(TextField_old, this);
	_xiugaiUi.oldPassWord->setPasswordEnabled(true);

	auto TextField_new = (TextField* ) newFrame->getChildByName("TextField_NewMima");
	TextField_new->setVisible(false);
	_xiugaiUi.newPassWord = HNEditBox::createEditBox(TextField_new, this);
	_xiugaiUi.newPassWord->setPasswordEnabled(true);

	auto TextField_sure = (TextField* ) sureFrame->getChildByName("TextField_SureMima");
	TextField_sure->setVisible(false);
	_xiugaiUi.surePassWord = HNEditBox::createEditBox(TextField_sure, this);
	_xiugaiUi.surePassWord->setPasswordEnabled(true);

	_xiugaiUi.sureBtn = (Button*) _xiugaiUi.xiugaiBG->getChildByName("Button_xiugaiOK");
	_xiugaiUi.sureBtn->addTouchEventListener(CC_CALLBACK_2(GameBankLayer::userDataUIEventCallBack, this));
}

void GameBankLayer::createForwardUI(Layout* root)
{
	//��ʾת�ʽ���
	_zhuanzhangUi.zhuanzhangBG = (ImageView* ) root->getChildByName("Image_zhuanzhangMesg");
	_xiugaiUi.xiugaiBG->setVisible(false);

	//��ȡ����Ŀ��
	auto nameFrame = (ImageView* ) _zhuanzhangUi.zhuanzhangBG->getChildByName("Image_nameFrame");
	auto giveFrame = (ImageView* ) _zhuanzhangUi.zhuanzhangBG->getChildByName("Image_giveFrame");
	auto mimaFrame = (ImageView* ) _zhuanzhangUi.zhuanzhangBG->getChildByName("Image_mimaFrame");

	//ѡ���ǳƻ�IDת��
	_zhuanzhangUi.name = (CheckBox*) _zhuanzhangUi.zhuanzhangBG->getChildByName("CheckBox_name");
	_zhuanzhangUi.name->addEventListener(CheckBox::ccCheckBoxCallback(CC_CALLBACK_2(GameBankLayer::forwardUICheckBoxEvent, this)));
	_zhuanzhangUi.name->setSelected(true);

	_zhuanzhangUi.ID = (CheckBox* ) _zhuanzhangUi.zhuanzhangBG->getChildByName("CheckBox_ID");
	_zhuanzhangUi.ID->addEventListener(CheckBox::ccCheckBoxCallback(CC_CALLBACK_2(GameBankLayer::forwardUICheckBoxEvent, this)));
	_zhuanzhangUi.ID->setSelected(false);

	//��ȡ�����
	auto TextField_NameorID = (TextField*) nameFrame->getChildByName("TextField_NameorID");
	TextField_NameorID->setVisible(false);
	_zhuanzhangUi.NameorID = HNEditBox::createEditBox(TextField_NameorID, this);

	auto TextField_giveMoney = (TextField*) giveFrame->getChildByName("TextField_GiveMoney");
	TextField_giveMoney->setVisible(false);
	_zhuanzhangUi.giveMoney = HNEditBox::createEditBox(TextField_giveMoney, this);
	_zhuanzhangUi.giveMoney->setInputMode(cocos2d::ui::EditBox::InputMode::PHONE_NUMBER);

	auto TextField_mima = (TextField*) mimaFrame->getChildByName("TextField_bankMima");
	TextField_mima->setVisible(false);
	_zhuanzhangUi.mima = HNEditBox::createEditBox(TextField_mima, this);
	_zhuanzhangUi.mima->setPasswordEnabled(true);

	_zhuanzhangUi.sureBtn = (Button*) _zhuanzhangUi.zhuanzhangBG->getChildByName("Button_zhuanzhangOK");
	_zhuanzhangUi.sureBtn->addTouchEventListener(CC_CALLBACK_2(GameBankLayer::forwardUIEventCallBack, this));
}

void GameBankLayer::createBankInfoUI(Layout* root)
{
	_bankDataUi.bankDataBG = (ImageView*) root->getChildByName("Image_bankMesg");
	char buffer[128];

	//��ȡ����Ŀ��
	auto nowCoinFrame = (Sprite* ) _bankDataUi.bankDataBG->getChildByName("nowCoin_3");
	auto moneyFrame = (Sprite* ) _bankDataUi.bankDataBG->getChildByName("bankMoney_4");

	//��ȡ��ǰ���
	sprintf(buffer, "%lld", _walletMoney);
	_bankDataUi.curMoney = (Text*) nowCoinFrame->getChildByName("Text_currentMoney");
	_bankDataUi.curMoney->setString(buffer);
	//��ȡ���
	sprintf(buffer, "%lld", _bankMoney);
	_bankDataUi.depositMoney = (Text*) moneyFrame->getChildByName("Text_bankDeposit");
	_bankDataUi.depositMoney->setString(buffer);
}

void GameBankLayer::userDataUIEventCallBack(Ref* pSender, Widget::TouchEventType type)
{
	if (Widget::TouchEventType::ENDED != type) return;
	Button* psender = (Button*) pSender;
	if (psender == _xiugaiUi.sureBtn)
	{
		HNAudioEngine::getInstance()->playEffect(GAME_SOUND_BUTTON);
		// ���д�ʧ�ܣ������κδ���
		if (!_bankOpen) return;

		bool canModify = false;
		std::string oldPassword = _xiugaiUi.oldPassWord->getString();
		std::string newPassword = _xiugaiUi.newPassWord->getString();
		std::string surePassword = _xiugaiUi.surePassWord->getString();
		do  
		{
			std::string errorText("");
			if (oldPassword.empty())
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8("������Ϊ�ա�")); break;
			}

			if (newPassword.empty())
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8("������Ϊ�ա�")); break;
			}

			if (surePassword.empty())
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8("ȷ������Ϊ�ա�")); break;
			}

			if (surePassword.compare(newPassword))
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8("ȷ������������벻ƥ�䡣")); break;
			}

			TMSG_GP_BankChPwd BankChPwd = {0};
			BankChPwd.user_id = PlatformLogic()->loginResult.dwUserID;
			strcpy(BankChPwd.MD5Pass_old, MD5_CTX::MD5String(oldPassword).c_str());
			strcpy(BankChPwd.MD5Pass_new, MD5_CTX::MD5String(newPassword).c_str());
			PlatformLogic()->sendData(MDM_GP_BANK, ASS_GP_BANK_CHPWD, &BankChPwd, sizeof(BankChPwd), 
				HN_SOCKET_CALLBACK(GameBankLayer::bankerEventSelector, this));
		} while (0);
	}
}

void GameBankLayer::operatorUIEventCheckBoxCallBack(Ref* pSender, CheckBox::EventType type)
{
	CheckBox* psender = (CheckBox*) pSender;
	switch (type)
	{
	case CheckBox::EventType::SELECTED:
		{
			HNAudioEngine::getInstance()->playEffect(GAME_SOUND_BUTTON);
			_caozuoUi.CunorQuMoney->setText("");
			_caozuoUi.CunorQuMima->setText("");
			if (psender == _caozuoUi.cunMoney)
			{
				_caozuoUi.quMoney->setSelected(false);
				_caozuoUi.CunorQuMima->setTouchEnabled(false);
			}

			if (psender == _caozuoUi.quMoney)
			{
				_caozuoUi.CunorQuMima->setTouchEnabled(true);
				_caozuoUi.cunMoney->setSelected(false);
			}
		}
		break;
	default:
		break;
	}
}

void GameBankLayer::forwardUICheckBoxEvent(Ref* pSender, CheckBox::EventType type)
{
	CheckBox* psender = (CheckBox*) pSender;
	switch (type)
	{
	case CheckBox::EventType::SELECTED:
		{
			HNAudioEngine::getInstance()->playEffect(GAME_SOUND_BUTTON);
			if (psender == _zhuanzhangUi.name)
			{
				_zhuanzhangUi.ID->setSelected(false);
			}

			if (psender ==_zhuanzhangUi.ID)
			{
				_zhuanzhangUi.name->setSelected(false);
			}
		}
		break;
	default:
		break;
	}
}

void GameBankLayer::forwardUIEventCallBack(Ref* pSender, Widget::TouchEventType type)
{
	if (Widget::TouchEventType::ENDED != type) return;
	Button* psender = (Button*) pSender;
	if (psender == _zhuanzhangUi.sureBtn)
	{
		HNAudioEngine::getInstance()->playEffect(GAME_SOUND_BUTTON);
		std::string userText = _zhuanzhangUi.NameorID->getString();
		std::string forwardMoney = _zhuanzhangUi.giveMoney->getString();
		std::string bankPassword = _zhuanzhangUi.mima->getString();
		do 
		{
			if (userText.empty())
			{
				if (_zhuanzhangUi.ID->isSelected())
				{
					GamePromptLayer::create()->showPrompt(GBKToUtf8("������Է�ID��")); break;
				}

				if (_zhuanzhangUi.name->isSelected())
				{
					GamePromptLayer::create()->showPrompt(GBKToUtf8("������Է��ǳơ�")); break;
				}
			}

			if (forwardMoney.empty())
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8("ת�˽����Ϊ�ա�")); break;
			}

			if (bankPassword.empty())
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8("�������������롣")); break;
			}

			MSG_GP_R_LogonResult& LogonResult = PlatformLogic()->loginResult;
			TMSG_GP_BankTransfer bankTransfer;
			if (_zhuanzhangUi.ID->isSelected())
			{
				bankTransfer.UserID = LogonResult.dwUserID;
				strcpy(bankTransfer.szNickName, LogonResult.nickName);

				bankTransfer.destUserID = atol(userText.c_str());
				bankTransfer.i64Money = atol(forwardMoney.c_str());
				bankTransfer.bUseDestID = true;
				strcpy(bankTransfer.szMD5Pass, MD5_CTX::MD5String(bankPassword).c_str());
			}

			if (_zhuanzhangUi.name->isSelected())
			{
				bankTransfer.UserID = LogonResult.dwUserID;
				strcpy(bankTransfer.szNickName, LogonResult.nickName);

				strcpy(bankTransfer.szDestNickName, Utf8ToGB(userText.c_str()));
				bankTransfer.i64Money = atol(forwardMoney.c_str());
				bankTransfer.bUseDestID = false;
				strcpy(bankTransfer.szMD5Pass, MD5_CTX::MD5String(bankPassword).c_str());
			}
			if(bankTransfer.i64Money <= 0)
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8("������Ϸ���")); 
				break;
			}
			PlatformLogic()->sendData(MDM_GP_BANK, ASS_GP_BANK_TRANSFER, &bankTransfer, sizeof(bankTransfer), 
				HN_SOCKET_CALLBACK(GameBankLayer::bankerForwardSelector, this));
		} while (0);
	}
}

void GameBankLayer::operatorUIEventCallBack(Ref* pSender, Widget::TouchEventType type)
{
	if (Widget::TouchEventType::ENDED != type) return;
	Button* psender = (Button*) pSender;
	if (psender == _caozuoUi.sureBtn)
	{
		HNAudioEngine::getInstance()->playEffect(GAME_SOUND_BUTTON);
		// ���д�ʧ�ܣ������κδ���
		if (!_bankOpen) return;
		// ���
		if (_caozuoUi.cunMoney->isSelected())
		{
			std::string strMoney = _caozuoUi.CunorQuMoney->getString();
			do 
			{
				if (strMoney.empty())
				{
					GamePromptLayer::create()->showPrompt(GBKToUtf8("���������")); break;
				}

				TMSG_GP_BankCheck BankCheck = {0};
				BankCheck.operate_type = 2;
				BankCheck.user_id = PlatformLogic()->loginResult.dwUserID;
				BankCheck.game_id = 0;
				BankCheck.money = atol(strMoney.c_str());
				if(BankCheck.money <= 0)
				{
					GamePromptLayer::create()->showPrompt(GBKToUtf8("������Ϸ���")); 
					break;
				}
				PlatformLogic()->sendData(MDM_GP_BANK, ASS_GP_BANK_CHECK, &BankCheck, sizeof(BankCheck), 
					HN_SOCKET_CALLBACK(GameBankLayer::bankerEventSelector, this));
			} while (0);
		}
		// ȡ��
		else if (_caozuoUi.quMoney->isSelected())
		{
			std::string strMoney = _caozuoUi.CunorQuMoney->getString();
			std::string password = _caozuoUi.CunorQuMima->getString();
			do 
			{
				if (strMoney.empty())
				{
					GamePromptLayer::create()->showPrompt(GBKToUtf8("������ȡ���")); break;
				}

				if (password.empty())
				{
					GamePromptLayer::create()->showPrompt(GBKToUtf8("�������������롣")); break;
				}
				TMSG_GP_BankCheck BankCheck = {0};
				BankCheck.operate_type = 1;
				BankCheck.user_id = PlatformLogic()->loginResult.dwUserID;
				BankCheck.game_id = 0;
				BankCheck.money = atol(strMoney.c_str());
				strcpy(BankCheck.szMD5Pass, MD5_CTX::MD5String(password).c_str());
				if(BankCheck.money <= 0)
				{
					GamePromptLayer::create()->showPrompt(GBKToUtf8("������Ϸ���")); 
					break;
				}
				PlatformLogic()->sendData(MDM_GP_BANK, ASS_GP_BANK_CHECK, &BankCheck, sizeof(BankCheck), 
					HN_SOCKET_CALLBACK(GameBankLayer::bankerEventSelector, this));
			} while (0);
		}
		else
		{
			GamePromptLayer::create()->showPrompt(GBKToUtf8("��ѡ��������͡�"));
		}
	}
}

void GameBankLayer::navigationCheckBoxEvent(Ref* pSender, Widget::TouchEventType  type)
{
	if (Widget::TouchEventType::ENDED != type) return;
	Button* psender = (Button*) pSender;
	HNAudioEngine::getInstance()->playEffect(GAME_SOUND_BUTTON);
	if (psender == _publicBtn.bankBtn)
	{		
		_caozuoUi.caozuoBG->setVisible(true);
		_xiugaiUi.xiugaiBG->setVisible(false);
		_zhuanzhangUi.zhuanzhangBG->setVisible(false);
		_publicBtn.bankBtn->setEnabled(false);
		_publicBtn.bankBtn->setBright(true);
		_publicBtn.dataBtn->setEnabled(true);
		_publicBtn.dataBtn->setBright(false);
		_publicBtn.zhuanzhangBtn->setEnabled(true);
		_publicBtn.zhuanzhangBtn->setBright(false);

		_xiugaiUi.oldPassWord->setText("");
		_xiugaiUi.newPassWord->setText("");
		_xiugaiUi.surePassWord->setText("");
		_zhuanzhangUi.NameorID->setText("");
		_zhuanzhangUi.giveMoney->setText("");
		_zhuanzhangUi.mima->setText("");

	}
	else if (psender == _publicBtn.dataBtn)
	{
		_xiugaiUi.xiugaiBG->setVisible(true);
		_caozuoUi.caozuoBG->setVisible(false);
		_zhuanzhangUi.zhuanzhangBG->setVisible(false);
		_publicBtn.dataBtn->setEnabled(false);
		_publicBtn.dataBtn->setBright(true);
		_publicBtn.bankBtn->setEnabled(true);
		_publicBtn.bankBtn->setBright(false);
		_publicBtn.zhuanzhangBtn->setEnabled(true);
		_publicBtn.zhuanzhangBtn->setBright(false);

		_caozuoUi.CunorQuMoney->setText("");
		_caozuoUi.CunorQuMima->setText("");
		_zhuanzhangUi.NameorID->setText("");
		_zhuanzhangUi.giveMoney->setText("");
		_zhuanzhangUi.mima->setText("");
	}
	else if (psender == _publicBtn.zhuanzhangBtn)
	{
		_zhuanzhangUi.zhuanzhangBG->setVisible(true);
		_caozuoUi.caozuoBG->setVisible(false);
		_xiugaiUi.xiugaiBG->setVisible(false);
		_publicBtn.zhuanzhangBtn->setEnabled(false);
		_publicBtn.zhuanzhangBtn->setBright(true);
		_publicBtn.bankBtn->setEnabled(true);
		_publicBtn.bankBtn->setBright(false);
		_publicBtn.dataBtn->setEnabled(true);
		_publicBtn.dataBtn->setBright(false);

		_caozuoUi.CunorQuMoney->setText("");
		_caozuoUi.CunorQuMima->setText("");
		_xiugaiUi.oldPassWord->setText("");
		_xiugaiUi.newPassWord->setText("");
		_xiugaiUi.surePassWord->setText("");
	}

}

void GameBankLayer::closeEvent(Ref* pSender, Widget::TouchEventType type)
{
	Button* selectedBtn = (Button*)pSender;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		selectedBtn->setColor(Color3B(170, 170, 170));
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		selectedBtn->setColor(Color3B(255, 255, 255));
		closeBank();
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		selectedBtn->setColor(Color3B(255, 255, 255));
		break;
	default:
		break;

	}
}

bool GameBankLayer::bankerForwardSelector(HNSocketMessage* socketMessage)
{
	UINT bAssistantID = socketMessage->messageHead.bAssistantID;
	UINT bHandleCode = socketMessage->messageHead.bHandleCode;

	CCAssert(sizeof(TMSG_GP_BankTransfer) == socketMessage->objectSize, "bank error");

	TMSG_GP_BankTransfer* pdate = (TMSG_GP_BankTransfer*)socketMessage->object;

	std::string errText("");
	if (ASS_GP_BANK_TRANSFER == bAssistantID)	// ת��
	{	
		if (HC_GP_BANK_TRANSFER_ERROR == bHandleCode)	//1		//ת�ʴ���
		{
			errText = "ת�ʴ���";
		}
		else if (HC_GP_BANK_TRANSFER_NO_DEST == bHandleCode)	//3		//ת��Ŀ�겻����
		{
			errText = "ת��Ŀ�겻���ڡ�";
		}
		else if (HC_GP_BANK_TRANSFER_PASSWORD_ERROR == bHandleCode)	//4		//ת���������
		{
			errText = "ת���������";
		}
		else if (HC_GP_BANK_TRANSFER_TOTAL_LESS == bHandleCode)	//5		//�����ܶ�̫С�������ʸ�
		{
			errText = "�����ܶ�̫С�������ʸ�";
		}
		else if (HC_GP_BANK_TRANSFER_TOO_LESS == bHandleCode)//6		// ����ת����Ŀ̫��
		{
			errText = "����ת����Ŀ̫�١�";
		}
		else if (HC_GP_BANK_TRANSFER_MULTIPLE == bHandleCode)//7		// ����ת����Ŀ������ĳ���ı���
		{
			errText = "����ת����Ŀ������ĳ���ı�����";
		}
		else if (HC_GP_BANK_TRANSFER_NOT_ENOUGH == bHandleCode)//8		// ���н�������ת��
		{
			errText = "���н�������ת�ʡ�";
		}
		else if (HC_GP_BANK_TRANSFER_TOO_MANY_TIME == bHandleCode)	//9	// ����ת�˵Ĵ���̫����
		{
			errText = "����ת�˵Ĵ���̫�ࡣ";
		}
		else if (HC_GP_BANK_TRANSFER_SUC == bHandleCode)		//2		//ת�ʳɹ�
		{
			errText = "ת�ʳɹ���";

			_bankMoney -= pdate->i64Money;
			PlatformLogic()->loginResult.i64Bank = _bankMoney;
			_delegate->bankChanged(_bankMoney);

			std::string str = StringUtils::format("%lld", _bankMoney);

			if (nullptr != _bankDataUi.depositMoney)
			{
				_bankDataUi.depositMoney->setString(str);
			}
			_zhuanzhangUi.NameorID->setText("");
			_zhuanzhangUi.giveMoney->setText("");
			_zhuanzhangUi.mima->setText("");
		}
		else
		{

		}
		GamePromptLayer::create()->showPrompt(GBKToUtf8(errText.c_str()));
	}
	else if (ASS_GP_BANK_TRANS_RECORD == bAssistantID)	// ת�˲�ѯ
	{
		if (HC_GP_BANK_TRANS_RECORD_SUC == bHandleCode)
		{

		}
	}
	return true;
}

void GameBankLayer::openbankResult(TMSG_GP_BankInfo* pBankInfo)
{
	_bankMoney = pBankInfo->i64Bank;

	_walletMoney = pBankInfo->i64Wallet;

	char buffer[128];
	sprintf(buffer, "%lld", _walletMoney);
	if (nullptr != _bankDataUi.curMoney)
	{
		_bankDataUi.curMoney->setString(buffer);
	}

	sprintf(buffer, "%lld", _bankMoney);
	if (nullptr != _bankDataUi.depositMoney)
	{
		_bankDataUi.depositMoney->setString(buffer);
	}
}

bool GameBankLayer::bankerEventSelector(HNSocketMessage* socketMessage)
{ 
	UINT bAssistantID = socketMessage->messageHead.bAssistantID;
	UINT bHandleCode = socketMessage->messageHead.bHandleCode;
	// ������
	if (ASS_GP_BANK_OPEN == bAssistantID)
	{
		switch (bHandleCode)
		{
		case HC_GP_BANK_OPEN_SUC://					1		//��Ǯ��ɹ�
			{
				// �㲥����
				CCAssert(sizeof (TMSG_GP_BankInfo) == socketMessage->objectSize, "TMSG_GP_BankInfo size is error.");
				if (sizeof (TMSG_GP_BankInfo) != socketMessage->objectSize)
				{
					return true;
				}
				TMSG_GP_BankInfo * bankInfo = reinterpret_cast<TMSG_GP_BankInfo*>(socketMessage->object);

				openbankResult(bankInfo);
				
				_bankOpen = true;

			} break;
		case HC_GP_BANK_OPEN_ERR://					2		//��Ǯ�����
			{
				_bankOpen = false;
			} break;
		case HC_GP_BANK_OPEN_ERR_PSW://				3		//��Ǯ�����
			{
				_bankOpen = false;
			} break;
		default:
			break;
		}
	}
	// �޸�����
	else if (ASS_GP_BANK_CHPWD == bAssistantID)
	{
		switch (bHandleCode)
		{
		case HC_GP_BANK_CHPWD_SUC://					1			//�޸ĳɹ�
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8("�����޸ĳɹ�"));
				_xiugaiUi.oldPassWord->setText("");
				_xiugaiUi.newPassWord->setText("");
				_xiugaiUi.surePassWord->setText("");
			} break;
		case HC_GP_BANK_CHPWD_ERR_PWD://					2		//�޸�ʧ�ܣ��������
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8("�޸�ʧ�ܣ��������"));
			} break;
		default:
			break;
		}
	}
	// ��ȡǮ
	else if (ASS_GP_BANK_CHECK == bAssistantID)
	{
		switch (bHandleCode)
		{
		case HC_GP_BANK_CHECK_SUC://					0			//�����ɹ�
			{
				// �㲥����
				SaveAndOpenBank(socketMessage->object, socketMessage->objectSize);

			} break;
		case HC_GP_BANK_CHECK_NO_USER://				1			//û���ҵ��û�
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8("��Ҳ����޷����롣"));
			} break;
		case HC_GP_BANK_CHECK_ERR_PWD://				2			//��������
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8("�������롣"));
			} break;
		case HC_GP_BANK_CHECK_NOT_MONEY://				4			//����
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8("���㡣"));
			} break;
		case HC_GP_BANK_CHECK_CAN_NOT_OPEN://			5			//�����в��ܽ��д�ȡ����
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8("�����в��ܽ��д�ȡ������"));
			} break;
		default:
			break;
		}
	}
	return true;
}

void GameBankLayer::SaveAndOpenBank(void* pDate, int isize)
{
	// �㲥����
	CCAssert(sizeof (TMSG_GP_BankCheck) == isize, "TMSG_GP_BankCheck size is error.");

	if (sizeof (TMSG_GP_BankCheck) != isize)
		return ;

	TMSG_GP_BankCheck *BankCheck = reinterpret_cast<TMSG_GP_BankCheck*>(pDate);

	std::string promptInfo;

	// ȡǮ
	if (1 == BankCheck->operate_type)
	{
		_bankMoney -= BankCheck->money;
		_walletMoney += BankCheck->money;
		promptInfo = GBKToUtf8("ȡ��ɹ�");
	}

	// ��Ǯ 
	if (2 == BankCheck->operate_type)
	{
		_bankMoney += BankCheck->money;
		_walletMoney -= BankCheck->money;
		promptInfo = GBKToUtf8("���ɹ�");
	}

	PlatformLogic()->loginResult.i64Bank = _bankMoney;
	PlatformLogic()->loginResult.i64Money = _walletMoney;
	_delegate->walletChanged(_walletMoney);
	_delegate->bankChanged(_bankMoney);


	char buffer[128];
	sprintf(buffer, "%lld", _walletMoney);
	if (nullptr != _bankDataUi.curMoney)
	{
		_bankDataUi.curMoney->setString(buffer);
	}

	sprintf(buffer, "%lld", _bankMoney);
	if (nullptr != _bankDataUi.depositMoney)
	{
		_bankDataUi.depositMoney->setString(buffer);
	}

	_caozuoUi.CunorQuMoney->setText("");
	_caozuoUi.CunorQuMima->setText("");

	GamePromptLayer::create()->showPrompt(promptInfo.c_str());
}
