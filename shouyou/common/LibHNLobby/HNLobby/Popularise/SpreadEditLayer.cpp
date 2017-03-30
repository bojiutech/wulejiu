//Copyright (c) 2012��2015 Beijing TianRuiDiAn Network Technology Co,Ltd. All rights reserved


#include "SpreadEditLayer.h"
#include "HNMarketExport.h"
#include "HNLobby/PlatformDefine.h"
#include "HNLobby/FontConfig.h"
#include "HNLobby/GamePrompt.h"
#include "HNUIExport.h"
#include "HNMarketExport.h"

namespace HN
{
	static const char* SPREAD_EDIT_CSB		= "platform/popularise/SpreadEditLayer.csb";
	static const char* POPULARISE_BG		= "platform/store/second_payBg.png";            //backGround
	static const char* SELF_FRAME			= "platform/common/frame.png";					//frame
	static const char* CLOSE_N				= "platform/popularise/second_back.png";  
	static const char* TITLE_INFO			= "platform/popularise/populariseTitle_info.png";  
	static const char* TITLE_APPLY			= "platform/popularise/populariseTitle_apply.png";  
	static const char* LEAF_LEFT	        = "platform/subViewBambooLeft.png";               
	static const char* LEAF_RIGHT	        = "platform/subViewBambooRight.png";  

	SpreadEditLayer* SpreadEditLayer::create(Delegate* dlte/* = nullptr*/)
	{
		SpreadEditLayer* obj = new SpreadEditLayer(dlte);
		if(obj && obj->init())
		{
			obj->autorelease();
		}
		else
		{
			CC_SAFE_DELETE(obj);
		}
		return obj;
	}

	SpreadEditLayer::SpreadEditLayer(Delegate* dlte)
	:_delegate(dlte)
	{}

	SpreadEditLayer::~SpreadEditLayer()
	{}

	bool SpreadEditLayer::init()
	{
		if(! HNLayer::init()) return false;

		_spreadLogic.init(this);

		_cardInfoMain = _spreadLogic.getSpreadInfo().IDCardImgUrlMain;
		_cardInfoOther = _spreadLogic.getSpreadInfo().IDCardImgUrlOther;

		Size winSize = Director::getInstance()->getWinSize();

		//�����ƹ�Ա����
		setBackGroundImage(POPULARISE_BG);

		//�޸��ƹ�Ա����
		_titleSprite_Info = HNSprite::create(TITLE_INFO);
		_titleSprite_Info->setAnchorPoint(Point(0.5, 1));
		_titleSprite_Info->setPosition(Vec2(winSize.width / 2, winSize.height-10));
		_titleSprite_Info->setScale((0.8f*1280.0f/winSize.width)/(720/winSize.height),(0.8f*1280.0f/winSize.width)/(720/winSize.height));
		this->addChild(_titleSprite_Info, 2);
		_titleSprite_Info->setVisible(false);

		//�����ƹ�Ա����
		_titleSprite_Apply = HNSprite::create(TITLE_APPLY);
		_titleSprite_Apply->setAnchorPoint(Point(0.5, 1));
		_titleSprite_Apply->setPosition(Vec2(winSize.width / 2, winSize.height-10));
		_titleSprite_Apply->setScale((0.8f*1280.0f/winSize.width)/(720/winSize.height),(0.8f*1280.0f/winSize.width)/(720/winSize.height));
		this->addChild(_titleSprite_Apply, 2);

		//��Ҷ
		auto leftLeaf = Sprite::create(LEAF_LEFT);
		leftLeaf->setAnchorPoint(Point(0, 1));
		leftLeaf->setPosition(0, winSize.height);
		addChild(leftLeaf, 5);
		auto rightleaf = Sprite::create(LEAF_RIGHT);
		rightleaf->setAnchorPoint(Point(1, 1));
		rightleaf->setPosition(winSize.width, winSize.height);
		addChild(rightleaf, 5);

		auto MyListener = EventListenerTouchOneByOne::create();
		//��ֹ�������´���
		MyListener->setSwallowTouches(true);
		MyListener->onTouchBegan = [&](Touch* touch, Event* event)
		{
			auto target = dynamic_cast<SpreadEditLayer*>(event->getCurrentTarget());//��ȡ�ĵ�ǰ������Ŀ��       
			Point locationInNode = target->convertToNodeSpace(touch->getLocation());
			Size s = target->getContentSize();
			Rect rect = Rect(0, 0, s.width, s.height);
			return rect.containsPoint(locationInNode);//�жϴ������Ƿ���Ŀ��ķ�Χ��

		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(MyListener, this);

		//�رհ�ť
		auto closeBtn = Button::create(CLOSE_N , CLOSE_N);
		closeBtn->setPosition(Vec2(winSize.width * 0.05f, winSize.height * 0.94f));
		addChild(closeBtn,5);
		closeBtn->addTouchEventListener(CC_CALLBACK_2(SpreadEditLayer::closeEventCallBack,this));

		
		//�޸��ƹ�Ա������ɫ
		auto popularisebg = ui::Scale9Sprite::create(SELF_FRAME);
		popularisebg->setAnchorPoint(Point(0.5, 0));
		popularisebg->setPreferredSize(Size(1300 ,( 620.0f*(1280.0f / winSize.width))/(720.0f/winSize.height)));
		popularisebg->setPosition(Vec2(winSize.width / 2,0));
		addChild(popularisebg,2);

		_studioUI.root = CSLoader::createNode(SPREAD_EDIT_CSB);
		_studioUI.root->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		_studioUI.root->setPosition(winSize / 2);
		this->addChild(_studioUI.root, 3);

		_studioUI.layout = (Layout*)_studioUI.root->getChildByName("layout_edit");

		auto applicationBtn = (Button*)_studioUI.layout->getChildByName("Button_Application");
		applicationBtn->setVisible(false);
		applicationBtn->addTouchEventListener(CC_CALLBACK_2(SpreadEditLayer::btnCallback, this));
		auto changeBtn = (Button*)_studioUI.layout->getChildByName("Button_ChangeInfo");
		changeBtn->setVisible(false);
		changeBtn->addTouchEventListener(CC_CALLBACK_2(SpreadEditLayer::btnCallback, this));

		//����
		auto editName = dynamic_cast<TextField* >(_studioUI.layout->getChildByName("TextField_Name"));
		editName->setVisible(false);
		_studioUI.editName = HNEditBox::createEditBox(editName, this);
		_studioUI.editName->setFontColor(Color3B::WHITE);
		_studioUI.editName->setString(_spreadLogic.getSpreadInfo().reallName);

		//���֤��
		auto editPersonNum = dynamic_cast<TextField* >(_studioUI.layout->getChildByName("TextField_PersonNum"));
		editPersonNum->setVisible(false);
		_studioUI.editPersonNum = HNEditBox::createEditBox(editPersonNum, this);
		_studioUI.editPersonNum->setFontColor(Color3B::WHITE);
		_studioUI.editPersonNum->setString(_spreadLogic.getSpreadInfo().personNum);

		//�绰����
		auto editPhone = dynamic_cast<TextField* >(_studioUI.layout->getChildByName("TextField_PhoneNum"));
		editPhone->setVisible(false);
		_studioUI.editPhone = HNEditBox::createEditBox(editPhone, this);
		_studioUI.editPhone->setFontColor(Color3B::WHITE);
		_studioUI.editPhone->setString(_spreadLogic.getSpreadInfo().phoneNum);

		//��������
		auto editBankName = dynamic_cast<TextField* >(_studioUI.layout->getChildByName("TextField_BankName"));
		editBankName->setVisible(false);
		_studioUI.editBankName = HNEditBox::createEditBox(editBankName, this);
		_studioUI.editBankName->setFontColor(Color3B::WHITE);
		_studioUI.editBankName->setString(_spreadLogic.getSpreadInfo().bankName);

		//����
		auto editBankNum = dynamic_cast<TextField* >(_studioUI.layout->getChildByName("TextField_BankNum"));
		editBankNum->setVisible(false);
		_studioUI.editBankNum = HNEditBox::createEditBox(editBankNum, this);
		_studioUI.editBankNum->setFontColor(Color3B::WHITE);
		_studioUI.editBankNum->setString(_spreadLogic.getSpreadInfo().bankNum);

		//��ַ
		auto editAddress = dynamic_cast<TextField* >(_studioUI.layout->getChildByName("TextField_Address"));
		editAddress->setVisible(false);
		_studioUI.editAddress = HNEditBox::createEditBox(editAddress, this);
		_studioUI.editAddress->setFontColor(Color3B::WHITE);
		_studioUI.editAddress->setString(_spreadLogic.getSpreadInfo().address);

		//_studioUI.editName = EditBox::create((TextField*)_studioUI.layout->getChildByName("TextField_Name"));
		//_studioUI.editName->setText(_spreadLogic.getSpreadInfo().reallName.c_str());
		//_studioUI.editPersonNum = BillLayer::createEditBoxWithTextField((TextField*)_studioUI.layout->getChildByName("TextField_PersonNum"));
		//_studioUI.editPersonNum->setText(_spreadLogic.getSpreadInfo().personNum.c_str());
		//_studioUI.editPhone = BillLayer::createEditBoxWithTextField((TextField*)_studioUI.layout->getChildByName("TextField_PhoneNum"));
		//_studioUI.editPhone->setText(_spreadLogic.getSpreadInfo().phoneNum.c_str());
		//_studioUI.editBankName = BillLayer::createEditBoxWithTextField((TextField*)_studioUI.layout->getChildByName("TextField_BankName"));
		//_studioUI.editBankName->setText(_spreadLogic.getSpreadInfo().bankName.c_str());
		//_studioUI.editBankNum = BillLayer::createEditBoxWithTextField((TextField*)_studioUI.layout->getChildByName("TextField_BankNum"));
		//_studioUI.editBankNum->setText(_spreadLogic.getSpreadInfo().bankNum.c_str());
		//_studioUI.editAddress = BillLayer::createEditBoxWithTextField((TextField*)_studioUI.layout->getChildByName("TextField_Address"));
		//_studioUI.editAddress->setText(_spreadLogic.getSpreadInfo().address.c_str());

		_studioUI.scSFZZM_Btn = (Button*)_studioUI.layout->getChildByName("Button_Pic1");
		_studioUI.scSFZZM_Btn->addTouchEventListener(CC_CALLBACK_2(SpreadEditLayer::btnCallback, this));
		_studioUI.scSFZZM_Btn->setVisible(false);

		auto tmpBg1 = (ImageView*)_studioUI.layout->getChildByName("Image_ZMBG");
		_studioUI.scSFZZM_Tips = (Text*)tmpBg1->getChildByName("Text_9");

		_studioUI.picSFZZM = (Sprite*)tmpBg1->getChildByName("Sprite_1");
		_studioUI.picSFZZM->setVisible(false);

		_studioUI.scSFZFM_Btn = (Button*)_studioUI.layout->getChildByName("Button_Pic2");
		_studioUI.scSFZFM_Btn->addTouchEventListener(CC_CALLBACK_2(SpreadEditLayer::btnCallback, this));
		_studioUI.scSFZFM_Btn->setVisible(false);

		auto tmpBg2 = (ImageView*)_studioUI.layout->getChildByName("Image_FMBG");
		_studioUI.scSFZFM_Tips = (Text*)tmpBg2->getChildByName("Text_9_13");

		_studioUI.picSFZFM = (Sprite*)tmpBg2->getChildByName("Sprite_1_6");
		_studioUI.picSFZFM->setVisible(false);

		_studioUI.tips = (Text*)_studioUI.layout->getChildByName("Text_Tips");

		if(SPREADER_STATUS_SUCCESS == _spreadLogic.getSpreadInfo().applyStatus)
		{
			_studioUI.tips->setString(GBKToUtf8(StringUtils::format("���Ѿ����ƹ�Ա�������ƹ�ԱID: %d", _spreadLogic.getSpreadInfo().userId).c_str()));
			_studioUI.editName->setTouchEnabled(false);
			_studioUI.editPersonNum->setTouchEnabled(false);
			_studioUI.editBankName->setTouchEnabled(false);
			_studioUI.editBankNum->setTouchEnabled(false);
			_studioUI.editPhone->setTouchEnabled(false);
			_studioUI.editAddress->setTouchEnabled(false);
			_studioUI.picSFZZM->setVisible(false);
			_studioUI.picSFZFM->setVisible(false);

			_studioUI.picSFZZM->setVisible(true);
			_studioUI.picSFZFM->setVisible(true);
			_studioUI.scSFZZM_Tips->setString(GBKToUtf8("���֤��Ϣ\n�����ٸ���"));
			_studioUI.scSFZFM_Tips->setString(GBKToUtf8("���֤��Ϣ\n�����ٸ���"));
			
			changeBtn->setVisible(false);
			_titleSprite_Info->setVisible(true);
			_titleSprite_Apply->setVisible(false);
		}
		else if(SPREADER_STATUS_ING == _spreadLogic.getSpreadInfo().applyStatus)
		{
			_studioUI.tips->setString(GBKToUtf8("��������С�����������"));
			_studioUI.editName->setTouchEnabled(false);
			_studioUI.editPersonNum->setTouchEnabled(false);
			_studioUI.editBankName->setTouchEnabled(false);
			_studioUI.editBankNum->setTouchEnabled(false);
			_studioUI.editPhone->setTouchEnabled(false);
			_studioUI.editAddress->setTouchEnabled(false);
		
			_studioUI.picSFZZM->setVisible(true);
			_studioUI.picSFZFM->setVisible(true);
			_studioUI.scSFZZM_Tips->setString(GBKToUtf8("���֤��Ϣ\n�����ٸ���"));
			_studioUI.scSFZFM_Tips->setString(GBKToUtf8("���֤��Ϣ\n�����ٸ���"));

			_titleSprite_Info->setVisible(false);
			_titleSprite_Apply->setVisible(true);
		}
		else if(SPREADER_STATUS_FAILED == _spreadLogic.getSpreadInfo().applyStatus)
		{
			_cardInfoMain = "";
			_cardInfoOther = "";
			_studioUI.tips->setString(_spreadLogic.getSpreadInfo().failedInfo);
			_studioUI.editName->setText("");
			_studioUI.editPersonNum->setText("");
			_studioUI.editBankName->setText("");
			_studioUI.editBankNum->setText("");
			_studioUI.editPhone->setText("");
			_studioUI.editAddress->setText("");
			_studioUI.scSFZZM_Btn->setVisible(true);
			_studioUI.scSFZFM_Btn->setVisible(true);
			applicationBtn->setVisible(true);
			_titleSprite_Info->setVisible(false);
			_titleSprite_Apply->setVisible(true);

			_studioUI.scSFZZM_Tips->setString(GBKToUtf8("���֤��Ϣ\n�����ٸ���"));
			_studioUI.scSFZFM_Tips->setString(GBKToUtf8("���֤��Ϣ\n�����ٸ���"));
		}
		else
		{
			_studioUI.scSFZZM_Btn->setVisible(true);
			_studioUI.scSFZFM_Btn->setVisible(true);
			_studioUI.tips->setString(GBKToUtf8("��������д�ƹ�Ա������Ϣ��"));
			applicationBtn->setVisible(true);
			_titleSprite_Info->setVisible(false);
			_titleSprite_Apply->setVisible(true);
		}

		return true;
	}

	void SpreadEditLayer::show(Node* parent, int orderZ, int tagV)
	{
		parent->addChild(this, orderZ, tagV);
	}

	void SpreadEditLayer::close()
	{
		this->removeFromParentAndCleanup(true);
	}

	void SpreadEditLayer::showBase64Pic(std::string code, Sprite* sprite)
	{
		if (0 == code.compare("") || !sprite)
			return;

		int len = 0;
		unsigned char* buffer = nullptr;
		len = base64Decode((unsigned char*)code.c_str(), (unsigned int)code.length(), &buffer);
		Image* img = new Image();
		img->autorelease();
		bool ok = img->initWithImageData(buffer, len);
		if (ok)
		{
			Texture2D* tex = new Texture2D();
			tex->autorelease();
			tex->initWithImage(img);
			sprite->setTexture(tex);
		}
		free(buffer);
	}

	void SpreadEditLayer::getSFZZM_CB(std::string code)
	{
		if (0 != code.compare(""))
		{
			_cardInfoMain = code;
			_studioUI.picSFZZM->setVisible(true);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			showBase64Pic(_cardInfoMain, _studioUI.picSFZZM);
			GamePromptLayer::create()->showPrompt(GBKToUtf8("���֤�������ϴ��ɹ���"));
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			this->scheduleOnce([this](float dt)
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8("���֤�������ϴ��ɹ���"));
				showBase64Pic(_cardInfoMain, _studioUI.picSFZZM);
			}, 0.3f, "delay");
#endif
		}
		else
		{
			this->scheduleOnce([this](float dt)
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8("���֤�������ϴ�ʧ�ܣ�"));
			}, 0.3f, "delay");

		}
	}

	void SpreadEditLayer::getSFZFM_CB(std::string code)
	{
		if (0 != code.compare(""))
		{
			_cardInfoOther = code;
			_studioUI.picSFZFM->setVisible(true);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			showBase64Pic(_cardInfoOther, _studioUI.picSFZFM);
			GamePromptLayer::create()->showPrompt(GBKToUtf8("���֤�������ϴ��ɹ���"));
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			this->scheduleOnce([this](float dt)
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8("���֤�������ϴ��ɹ���"));
				showBase64Pic(_cardInfoOther, _studioUI.picSFZFM);
			}, 0.3f, "delay");
#endif
		}
		else
		{
			this->scheduleOnce([this](float dt)
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8("���֤�������ϴ�ʧ�ܣ�"));
			}, 0.3f, "delay");
		}
	}

	void SpreadEditLayer::btnCallback(cocos2d::Ref* pSender,Widget::TouchEventType touchtype)
	{
		if (touchtype != Widget::TouchEventType::ENDED) return;
		HNAudioEngine::getInstance()->playEffect(GAME_SOUND_BUTTON);

		Button* btn = (Button*)pSender;
		if("Button_Back" == btn->getName())
		{
			close();
		}
		else if ("Button_Pic1" == btn->getName())
		{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			getSFZZM_CB("win32_test");
			return;
#endif
			CALLBACK_PRAGMA pragma(HN_PAY_CALLBACK(SpreadEditLayer::getSFZZM_CB, this));
			Operator::requestChannel("hnphoto", "getphoto", "{\"x\":100, \"y\":100}", &pragma);
		}
		else if ("Button_Pic2" == btn->getName())
		{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			getSFZFM_CB("win32_test");
			return;
#endif
			CALLBACK_PRAGMA pragma(HN_PAY_CALLBACK(SpreadEditLayer::getSFZFM_CB, this));
			Operator::requestChannel("hnphoto", "getphoto", "{\"x\":100, \"y\":100}", &pragma);
		}
		else if("Button_Application" == btn->getName())
		{
			std::string reallName = _studioUI.editName->getText();
			std::string personNum = _studioUI.editPersonNum->getText();
			std::string phone = _studioUI.editPhone->getText();
			std::string bankName = _studioUI.editBankName->getText();
			std::string bankNum = _studioUI.editBankNum->getText();
			std::string address = _studioUI.editAddress->getText();
			do 
			{
				if(reallName.empty())
				{				
					GamePromptLayer::create()->showPrompt(GBKToUtf8("��������ʵ������"));
					break;
				}
				if(reallName.size() > 20)
				{				
					GamePromptLayer::create()->showPrompt(GBKToUtf8("�������������20�ֽڣ�"));
					break;
				}
				if (personNum.size() < 15)
				{					
					GamePromptLayer::create()->showPrompt(GBKToUtf8("���֤������������"));
					break;
				}
				if(!Tools::verifyNumber(phone) || 11 != phone.size() || '1' != phone.at(0))
				{					
					GamePromptLayer::create()->showPrompt(GBKToUtf8("�ֻ�������������"));
					break;
				}
				if (bankName.empty())
				{					
					GamePromptLayer::create()->showPrompt(GBKToUtf8("�����뿪�����п��ţ�"));
					break;
				}
				if (bankName.size() > 20)
				{					
					GamePromptLayer::create()->showPrompt(GBKToUtf8("���п������������20�ֽڣ�"));
					break;
				}
				if (!Tools::verifyNumber(bankNum) || !(16 <= bankNum.size() && bankNum.size() <= 19))
				{					
					GamePromptLayer::create()->showPrompt(GBKToUtf8("���п�����������"));
					break;
				}
				if(address.empty())
				{
					GamePromptLayer::create()->showPrompt(GBKToUtf8("��������ϵ��ַ��"));
					break;
				}
				if(address.size() > 20)
				{
					GamePromptLayer::create()->showPrompt(GBKToUtf8("��ַ���������20�ֽڣ�"));
					break;
				}
				if (_cardInfoMain.empty())
				{					
					GamePromptLayer::create()->showPrompt(GBKToUtf8("���ϴ����֤�����գ�"));
					break;
				}
				if (_cardInfoOther.empty())
				{					
					GamePromptLayer::create()->showPrompt(GBKToUtf8("���ϴ����֤�����գ�"));
					break;
				}
				LoadingLayer::createLoading(this, GBKToUtf8("�����ύ��Ϣ�����Ժ�..."), 22, LOADING);
				std::string tmpMainInfoStr = _cardInfoMain;
				std::string tmpOtherInfoStr = _cardInfoOther;
				std::ostringstream ostr;
                ostr <<"option=AddOrUpdateTuiGugang&tgUserId=" << PlatformLogic()->loginResult.dwUserID
                <<"&trueName=" << reallName
                <<"&phone=" << phone
                <<"&address=" << address
                <<"&BankName=" << bankName
                <<"&BankNo=" << bankNum
                <<"&IDCardNo=" <<personNum
				<<"&IDCardImgUrlMain=" << Tools::base64urlencode(tmpMainInfoStr)
				<<"&IDCardImgUrlOther=" << Tools::base64urlencode(tmpOtherInfoStr);
                std::string param = ostr.str();
                _spreadLogic.requestBeSpreader(PlatformConfig::getInstance()->getPromoterUrl(), param);
                
			} while (0);
		}
		else if("Button_ChangeInfo" == btn->getName())
		{
			std::string phone = _studioUI.editPhone->getText();
			std::string bankName = _studioUI.editBankName->getText();
			std::string bankNum = _studioUI.editBankNum->getText();
			std::string address = _studioUI.editAddress->getText();
			do 
			{
				if (!Tools::verifyNumber(phone) || 11 != phone.size() || '1' != phone.at(0))
				{
					GamePromptLayer::create()->showPrompt(GBKToUtf8("�ֻ�������������"));
					break;
				}
				if (bankName.empty())
				{
					GamePromptLayer::create()->showPrompt(GBKToUtf8("���������п��ţ�"));
					break;
				}
				if (bankName.size() > 20)
				{
					GamePromptLayer::create()->showPrompt(GBKToUtf8("���п������������20�ֽڣ�"));
					break;
				}
				if (!Tools::verifyNumber(bankNum) || !(16 <= bankNum.size() && bankNum.size() <= 19))
				{
					GamePromptLayer::create()->showPrompt(GBKToUtf8("���п�����������"));
					break;
				}
				if (address.empty())
				{
					GamePromptLayer::create()->showPrompt(GBKToUtf8("��������ϵ��ַ��"));
					break;
				}
				if (address.size() > 20)
				{
					GamePromptLayer::create()->showPrompt(GBKToUtf8("��ַ���������20�ֽڣ�"));
					break;
				}
				if(0 == phone.compare(_spreadLogic.getSpreadInfo().phoneNum) &&
					0 == bankName.compare(_spreadLogic.getSpreadInfo().bankName) &&
					0 == bankNum.compare(_spreadLogic.getSpreadInfo().bankNum) &&
					0 == address.compare(_spreadLogic.getSpreadInfo().address))
				{
					GamePromptLayer::create()->showPrompt(GBKToUtf8("��������Ϣ��ԭ��Ϣһ�£�"));
					break;
				}
				std::ostringstream ostr;
                ostr <<"option=AddOrUpdateTuiGugang&tgUserId=" << PlatformLogic()->loginResult.dwUserID
                <<"&CheckState=2&trueName=" << _spreadLogic.getSpreadInfo().reallName
                <<"&phone=" << phone
                <<"&address=" << address
                <<"&BankName=" << bankName
                <<"&BankNo=" << bankNum
                <<"&IDCardNo=" <<_spreadLogic.getSpreadInfo().phoneNum
                <<"&IDCardImgUrlMain=" << ""
                <<"&IDCardImgUrlOther="<< "";
                std::string param = ostr.str();
                _spreadLogic.requestBeSpreader(PlatformConfig::getInstance()->getPromoterUrl(), param);
			} while (0);
		}
	}

	void SpreadEditLayer::onBeSpreader(bool result, const std::string& msg)//����ֻ���ύ����ɹ���񣬲����ǳɹ���Ϊ�ƹ�Ա���
	{
		LoadingLayer::removeLoading(this);
		GamePromptLayer::create()->showPrompt(msg);
		if(result)
		{
			LoadingLayer::createLoading(this, GBKToUtf8("���ڻ�ȡ��Ϣ�����Ժ�..."), 22, LOADING);
			char tmpstr[100];
			sprintf(tmpstr, "option=GetTuiGuangInfo&tgUserId=%d", PlatformLogic()->loginResult.dwUserID);
			_spreadLogic.requestSpreadInfo(PlatformConfig::getInstance()->getPromoterUrl(), tmpstr);
		}
		else
		{
			;
		}
	}

	void SpreadEditLayer::onSpreadInfo(bool result, bool bInfo, const std::string& msg)
	{
		LoadingLayer::removeLoading(this);
		if(result)
		{
			if(bInfo)
			{
				if(SPREADER_STATUS_ING == _spreadLogic.getSpreadInfo().applyStatus)
				{
					_studioUI.tips->setString(GBKToUtf8("��������С�����������"));
					_studioUI.editName->setTouchEnabled(false);
					_studioUI.editPersonNum->setTouchEnabled(false);
					_studioUI.editBankName->setTouchEnabled(false);
					_studioUI.editBankNum->setTouchEnabled(false);
					_studioUI.editPhone->setTouchEnabled(false);
					_studioUI.editAddress->setTouchEnabled(false);

					_studioUI.picSFZZM->setVisible(false);
					_studioUI.picSFZFM->setVisible(false);
					_studioUI.scSFZZM_Tips->setString(GBKToUtf8("���֤��Ϣ\n�����ٸ���"));
					_studioUI.scSFZFM_Tips->setString(GBKToUtf8("���֤��Ϣ\n�����ٸ���"));
		
					_studioUI.layout->getChildByName("Button_Application")->setVisible(false);
				}
				_studioUI.editName->setText(_spreadLogic.getSpreadInfo().reallName.c_str());
				_studioUI.editPhone->setText(_spreadLogic.getSpreadInfo().phoneNum.c_str());
				_studioUI.editAddress->setText(_spreadLogic.getSpreadInfo().address.c_str());
				if(_delegate)
				{
					_delegate->onSpreadInfoChanged();
				}
			}
			else
			{
				GamePromptLayer::create()->showPrompt(msg);
			}
		}
		else
		{
			GamePromptLayer::create()->showPrompt(msg);
		}
	}

	//�رհ�ť�ص�
	void SpreadEditLayer::closeEventCallBack(Ref* pSender, Widget::TouchEventType type)
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
}