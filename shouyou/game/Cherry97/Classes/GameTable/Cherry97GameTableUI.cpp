#include "Cherry97GameTableUI.h"
#include "Cherry97GameTableLogic.h"
#include "Cherry97GameAudio.h"
#include "Cherry97GameBet.h"
#include "Cherry97GameCell.h"
#include "Cherry97GameCheckAward.h"
#include "Cherry97GameCheckAwardNext.h"
#include "Cherry97GameShare.h"
#include "HNLobbyExport.h"
#include "HNUIExport.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include <ctime>

namespace Cherry97
{
	static const char* GAME_MAIN_CSB	=    "Cherry97/Cherry97Ui/MainNode.csb";    //������
	static const int      SETBTN_TAG	=    20;           //���ư�ť�ı�ǩֵ
	static const int      EXIT_TAG      =    30;           //�˳���ť�ı�ǩֵ
	static const int      MAX_LINEBET   =    50;           //���ĵ�����ע��
    static const BYTE     ALLLINE       =    8;            //��������
	static const char*    NOTIC_BG		=    "Cherry97/MsgManager_BG.png";
	static const char*    Bg_Stencil	=    "Cherry97/Msg_BG.png";
	static const char*    BTN_CANAELN	=    "Cherry97/quxiao_02.png";//ȡ����ť
	static const char*    BTN_CANAELS   =    "Cherry97/quxiao_03.png";//ȡ����ť
	static const char*    BTN_CANAELD	=    "Cherry97/quxiao_04.png";//ȡ����ť
	static const char*    BTN_AUTON	    =    "Cherry97/autobtn_02.png";//�Զ���ť
	static const char*    BTN_AUTOS	    =    "Cherry97/autobtn_03.png";//�Զ���ť
	static const char*    BTN_AUTOD	    =    "Cherry97/autobtn_04.png";//�Զ���ť
	static const char*    BTN_STOPN	    =    "Cherry97/stop_02.png";//ֹͣ��ť
	static const char*    BTN_STOPS	    =    "Cherry97/stop_03.png";//ֹͣ��ť
	static const char*    BTN_STOPD	    =    "Cherry97/stop_04.png";//ֹͣ��ť
	static const char*    BTN_STARTN	=    "Cherry97/kaishi_02.png";//��ʼ��ť
	static const char*    BTN_STARTS	=    "Cherry97/kaishi_03.png";//��ʼ��ť
	static const char*    BTN_STARTD	=    "Cherry97/kaishi_04.png";//��ʼ��ť

	static const char*    PROMPT_START	=    "Cherry97/PUSHSTART.png";//��ʾ��ʼ
	static const char*    PROMPT_BET	=    "Cherry97/PUSHBET.png";//��ʾ��ע
	static const char*    PROMPT_OVER	=    "Cherry97/gameover.png";//��ʾ����
	static const char*    PROMPT_WIN	=    "Cherry97/youwin.png";//��ʾӮ
	static const char*    PROMPT_INSERT	=    "Cherry97/insertcoin.png";//��ʾ��Ϸ��
	static const char*    PROMPT_BONUS	=    "Cherry97/bonus.png";//��ʾ��

	static int            MAX_ZORDER    = 10000; //���㼶
	static int            MIN_LINE_ZORDER = -1;  //��������С�㼶
	static int            MAX_LINE_ZORDER = 100; //���������㼶
	static int            SKIP_ZORDER   = 10001; //������ť�Ĳ㼶

	GameTableUI::GameTableUI():
		_isOutWait(false),  
		_gameCell(nullptr), 
		_curLineBet(0),
		_isAuto(false),
		_curStarBet(2), 
		_isStart(false), 
		_saveRightAwayTime(0.0f),
		_saveLineBet(0),
		_singleWinnings(0),
		_allWinnings(0),
		_nextaward(nullptr),
		_lastaward(nullptr),
		_singlePond(0)
	{
		memset(_openAwardLine, NULL, sizeof(_openAwardLine));
		memset(_imageType, NULL, sizeof(_imageType));
	}

	GameTableUI::~GameTableUI()
	{
		if (_gameTableLogic != nullptr)
		{
			HN_SAFE_DELETE(_gameTableLogic);
		}
	}

	GameTableUI* GameTableUI::create(char bDeskIndex, bool bAutoCreate)
	{
		GameTableUI* tableUI = new GameTableUI();
		if (tableUI->init(bDeskIndex, bAutoCreate))
		{
			tableUI->autorelease();
			return tableUI;
		}
		else
		{
			CC_SAFE_DELETE(tableUI);
			return nullptr;
		}
	}

	bool GameTableUI::init(char bDeskIndex, bool bAutoCreate)
	{
		if (!HNLayer::init())
		{
			return false;
		}
		winSize = Director::getInstance()->getWinSize();
		GameAudio::playBackground();//��������
		//��������
		addStartGameAnimate();
		createGameLayer();
		return true;
	}

	//����������
	void GameTableUI::createGameLayer()
	{
		auto gameLoader = CSLoader::createNode(GAME_MAIN_CSB);
		gameLoader->setPosition(winSize/2);
		addChild(gameLoader);
		_layout = (Layout* ) gameLoader->getChildByName("Panel_1");
		_layout->setVisible(false);
		_layout->setScaleY(winSize.height/(_layout->getContentSize()).height);
		_mainBg = (ImageView* ) _layout->getChildByName("Image_bg");
		_turnBg = (ImageView* ) _layout->getChildByName("Image_zhuapan");
		_turnBg->setLocalZOrder(10);
		_tTishi = (Text* ) _layout->getChildByName("Text_state");

		//��ʾ��
		_tishiSp = Sprite::create();
		_tishiSp->setPosition(_tTishi->getPosition());
		_tTishi->getParent()->addChild(_tishiSp, MAX_ZORDER);
		getChildNode();

		//��������ʼ��Ϸ
		_gameTableLogic = new GameTableLogic(this, _desk, _baotoCreate);
		_gameTableLogic->sendGameInfo();
		//����ת��ת������
		_gameCell = GameCell::create();
		addChild(_gameCell);
		_gameCell->setImage(_panelImage);
		_gameCell->showRollImage();
		//������
		_gameAward = GameAward::create(this);
		addChild(_gameAward);

		//�㲥��
		addRadioFrame();
		//��Ӽ��̼����¼�
		auto keyBoard = EventListenerKeyboard::create();
		keyBoard->onKeyReleased= CC_CALLBACK_2(GameTableUI::onKeyReleased, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoard, this);
	}

	void GameTableUI::getChildNode()
	{
		char str[50];
		//��Ϸ���ư�ť
		for (int i = 0; i < 6; i++)
		{
			sprintf(str, "Button_set_%d", i);
			_setbtn[i] = (Button* ) _layout->getChildByName(str);
			_setbtn[i]->setTag(SETBTN_TAG + i);
			_setbtn[i]->addTouchEventListener(CC_CALLBACK_2(GameTableUI::BtnCallBack,this));
		}
		//���ʣ����ã���ʷ�������Ϣ��ť
		_btnBet = (Button* ) _layout->getChildByName("Button_showBet");
		_btnBet->addTouchEventListener(CC_CALLBACK_2(GameTableUI::BtnCallBack,this));
		//ǿ�˰�ť
		_exitBtn = (Button* ) _layout->getChildByName("Button_close");
		_exitBtn->setTag(EXIT_TAG);
		_exitBtn->addTouchEventListener(CC_CALLBACK_2(GameTableUI::BtnCallBack,this));
		//����ǳ� 
		_userName = (Text* ) _layout->getChildByName("Text_userName");
		sprintf(str, "%s", PlatformLogic()->loginResult.nickName);
		_userName->setString(GBKToUtf8(str));
		//����ܽ��
		_userMoney = (Text* ) _layout->getChildByName("Text_userMoney");
		sprintf(str, "%lld", PlatformLogic()->loginResult.i64Money);
		_userMoney->setString(GBKToUtf8(str));

		//������Ϣ
		m_roomNameText = (Text*)_layout->getChildByName("Text_RoomName");
		m_deskId = (Text*)_layout->getChildByName("Text_DeskId");
		//����ܳ�����
		_curHandoff = (TextAtlas* ) _layout->getChildByName("AtlasLabel_zongchouma");
		_curHandoff->setString("0");
		//�������ע
		_curAllBet = (TextAtlas* ) _layout->getChildByName("AtlasLabel_zongxiazhu");
		//�ʽ�ֵ
		_handsel =  (TextAtlas* ) _turnBg->getChildByName("AtlasLabel_caijin_fangjian");
		_handselAll = (TextAtlas* ) _turnBg->getChildByName("AtlasLabel_caijin_all");
		_handselAll->setVisible(false);
		_textHandSelAll = (Text*)_turnBg->getChildByName("Text_fangjian");
		_textHandSelAll->setVisible(false);
		_textgetHandsel = (Text* ) _turnBg->getChildByName("Text_getCaijin");
		_textgetHandsel->setVisible(false);
		_getHandsel = (TextAtlas* ) _turnBg->getChildByName("AtlasLabel_getCaijin");
		_getHandsel->setString("");
		//��ұ���Ӯ��Ǯ��
		_curWinMoney = (TextAtlas*)_turnBg->getChildByName("AtlasLabel_winScore");
		_curWinMoney->setString("");
		//����Ӯ��Ǯ
		_ewMoney = (TextAtlas* ) _turnBg->getChildByName("AtlasLabel_ewFen");
		_ewMoney->setString("");
		//���淨��ȱ�����ʾͼ
		_specialRate = (ImageView* ) _turnBg->getChildByName("Image_specialRate");
		_specialRate->setVisible(false);
		_specialCountText = (TextAtlas* ) _turnBg->getChildByName("AtlasLabel_teshuRest");
		_specialCountText->setVisible(false);
		
		//����ͼƬ�Ĳü��㣬�Ÿ�ȫ�̵ĺ��
		for (int i = 0; i < 9; i++)
		{
			sprintf(str, "Panel_image_%d", i);
			_panelImage[i] = (Layout* ) _turnBg->getChildByName(str);
			sprintf(str, "Image_redFrame_%d", i);
			_redFrame[i] = (ImageView* )  _turnBg->getChildByName(str);
		}
		//��ȡ8���ߡ�8��������ע����
		for (int i = 0; i < 8; i++)
		{
			sprintf(str, "Image_line_%d", i);
			_line[i] = (ImageView* ) _turnBg->getChildByName(str);
			sprintf(str, "AtlasLabel_line_%d", i);
			_aloneBetNum[i] = (TextAtlas* ) _turnBg->getChildByName(str);
		}
		setLineState();//���������ĳ�ʼ״̬Ϊ����
		setRedFrameState(false);//���ú��ĳ�ʼ״̬Ϊ����
	}

	void GameTableUI::BtnCallBack(Ref* pSender, Widget::TouchEventType type)
	{
		auto i= ImageView::create();

		if (Widget::TouchEventType::ENDED != type) return;
		GameAudio::playBtn();//������
		Button* btn = (Button* ) pSender;
		int btnTag = btn->getTag();
		switch (btnTag)
		{
		case SETBTN_TAG://�Ϸ�
			{
				C_S_ShangFen shangfen;
				shangfen.bIsShangFen = true;
				sendData(MDM_GM_GAME_NOTIFY, C_S_SHANG_FEN, &shangfen, sizeof(shangfen));
				break;
			}
		case SETBTN_TAG + 1:
			{
				//(Ѻ�ֲ���Ҫ������������Ϣ���ȱ��ر��棬��ת����Ϣʱһ����Ѻ��ֵ)
				if (_curLineBet < _maxLineBet)
				{
					int curHand = atoi(_curHandoff->getString().c_str());//��ǰ�ܳ���
					if (curHand >= 80)
					{
						_curLineBet += 10;
						_curAllBet->setString(String::createWithFormat("%d", (_curLineBet * 8))->getCString());
						int num = curHand - 80;
						_curHandoff->setString(String::createWithFormat("%d", num)->getCString());
						int curhand = atoi(_curHandoff->getString().c_str());//��ǰ�ܳ���
						if (curhand < 80)
						{
							_setbtn[1]->setBright(false);
							_setbtn[1]->setEnabled(false);
						}
					}
				}
				else
				{
					_curLineBet = 0;
					_curAllBet->setString(String::createWithFormat("%d", 0)->getCString());
					_curHandoff->setString(String::createWithFormat("%d", getAllHandOff())->getCString());
					if (getAllHandOff() < 80)
					{
						_setbtn[1]->setBright(false);
						_setbtn[1]->setEnabled(false);
					}
				}
				showAloneLineNum(_curLineBet);
				setLineState();
				_saveLineBet = _curLineBet;
				break;
			}
		case SETBTN_TAG + 2:
			{
				if (_isStart)
				{
					setStart();
				}
				else
				{
					sendGameStartRoll();
				}
				break;
			}
		case SETBTN_TAG + 3:
			{
				if (_saveLineBet == 0)
				{
					break;
				}
				_isAuto = !_isAuto;
				auto curhand = atoi(_curHandoff->getString().c_str());
				auto curAllBet = atoi(_curAllBet->getString().c_str());
				if (curAllBet == 0)
				{
					if (curhand < (_saveLineBet*8))
					{
						_isAuto = false;
						setAuto();
						setBtnState(true);
						break;
					}
				}
				//�Զ���Ϸ������
				if (_isAuto)
				{
					if (_gameTableLogic->_gameState == GS_WAIT_NEXT)
					{
						setAutoGame();//�ж���Ϸ�Ƿ��Զ���ʼ
					}
					setCancel();
				}
				else
				{
					setAuto();
				}
				break;
			}
		case SETBTN_TAG + 4:
			{
				sendLastPageReq();
				break;
			}
		case SETBTN_TAG + 5:
			{
				_gameAward->stopAllSchedule();
				setGameEndData();
				break;
			}
		case EXIT_TAG:
			{
				returnMain();
				break;
			}
		default:
			break;
		}
		if(btn == _btnBet)
		{
			showBetLayer();
		}
	}

	void GameTableUI::setBtnState(bool isvisible)
	{
		//��Ϸ���ư�ť
		for (int i = 0; i < 5; i++)
		{
			_setbtn[i]->setBright(true);
			_setbtn[i]->setEnabled(true);
		}
		if (_gameTableLogic->_gameState != GS_WAIT_NEXT)
		{
			_setbtn[1]->setBright(false);
			_setbtn[1]->setEnabled(false);
		}
	}

	//���ÿ�ʼ/ֹͣ��ͼƬ״̬
	void GameTableUI::setStop()
	{
		//��ͼƬ״̬���ó�ֹͣ
		_setbtn[2]->loadTextureNormal(BTN_STOPN);
		_setbtn[2]->loadTexturePressed(BTN_STOPS);
		_setbtn[2]->loadTextureDisabled(BTN_STOPD);
		//���Ƿ�ʼ������ֵΪtrue,��ʾ�����Ѿ���ʼת��
		_isStart = true;
		//�����ʼ�󣬽�ֹͣ��ť���óɿɵ�״̬
		_setbtn[2]->setBright(true);
		_setbtn[2]->setEnabled(true);
	}
	void GameTableUI::setStart()
	{
		//��ͼƬ״̬���óɿ�ʼ
		_setbtn[2]->loadTextureNormal(BTN_STARTN);
		_setbtn[2]->loadTexturePressed(BTN_STARTS);
		_setbtn[2]->loadTextureDisabled(BTN_STARTD);
		//���Ƿ�ʼ������ֵΪfalse,��ʾ����ֹͣת��
		_isStart = false;
		//���ù���ͼƬ�Ƿ�����ֹͣ����falseΪ����ֹͣ
		_gameCell->setIsStop(_isStart);
		//���ֹͣ�󣬽���ʼ��ť���óɲ��ɵ�״̬
		_setbtn[2]->setBright(false);
		_setbtn[2]->setEnabled(false);
	}

	//�����Զ�/ȡ����ͼƬ״̬
	void GameTableUI::setAuto()
	{
		//��ͼƬ״̬���óɿ�ʼ
		_setbtn[3]->loadTextureNormal(BTN_AUTON);
		_setbtn[3]->loadTexturePressed(BTN_AUTOS);
		_setbtn[3]->loadTextureDisabled(BTN_AUTOD);
	}
	void GameTableUI::setCancel()
	{
		_setbtn[3]->loadTextureNormal(BTN_CANAELN);
		_setbtn[3]->loadTexturePressed(BTN_CANAELS);
		_setbtn[3]->loadTextureDisabled(BTN_CANAELD);
	}

	void GameTableUI::setLineState()
	{
		for (int i = 0; i < 8; i++)
		{
			int bet = atoi(_curAllBet->getString().c_str());
			if (_curLineBet > 0 && bet > 0)
			{
				_line[i]->setVisible(true);
			}
			else
			{
				_line[i]->setVisible(false);
			}
		}
	}

	void GameTableUI::setPlayStartAndBet()
	{
		setStopStartAndBet();
		_tishiSp->setTexture(PROMPT_START);
		_tishiSp->runAction(RepeatForever::create( Sequence::create(DelayTime::create(0.5f), CallFunc::create([=](){
			_tishiSp->setTexture(PROMPT_BET);
		}), DelayTime::create(0.5f), CallFunc::create([=](){
			_tishiSp->setTexture(PROMPT_START);
		}), nullptr)));
	}
	//ֹͣ��ʼ����עͼƬ�����Ķ���
	void GameTableUI::setStopStartAndBet()
	{
		_tishiSp->stopAllActions();
	}

	//��ӿ�ʼ����
	void GameTableUI::addStartGameAnimate()
	{
		showGameNameAni();
	}

	//��ʾ��Ϸ���ƵĶ���
	void GameTableUI::showGameNameAni()
	{
		auto aniSp = Sprite::create("Cherry97/cherryAni/cherry0.png");
		aniSp->setScaleY(winSize.height / aniSp->getContentSize().height	);
		aniSp->setPosition(winSize/2);
		addChild(aniSp, MAX_ZORDER);
		auto nameAniSpSize = aniSp->getContentSize();

		char str[64];
		auto animation = Animation::create();
		for (int i = 0; i < 18; i++)
		{
			sprintf(str, "Cherry97/cherryAni/cherry%d.png", i);
			animation->addSpriteFrameWithFile(str);
		}
		animation->setDelayPerUnit(0.1f);
		auto action = Animate::create(animation);
		aniSp->runAction(Sequence::create(action, CallFunc::create([=](){
			showGameBetAni();
		}), RemoveSelf::create(), nullptr));
	}

	//��ʾ����ʱ�ı��ʶ���
	void GameTableUI::showGameBetAni()
	{
		auto aniSp = Sprite::create("Cherry97/cherryAni/cherry18.png");
		aniSp->setScaleY(winSize.height / aniSp->getContentSize().height	);
		aniSp->setPosition(winSize/2);
		addChild(aniSp, MAX_ZORDER);
		auto nameAniSpSize = aniSp->getContentSize();

		char str[64];
		auto animation = Animation::create();
		for (int i = 18; i < 26; i++)
		{
			sprintf(str, "Cherry97/cherryAni/cherry%d.png", i);
			animation->addSpriteFrameWithFile(str);
		}
		animation->setDelayPerUnit(0.5f);
		auto action = Animate::create(animation);
		aniSp->runAction(Sequence::create(action, CallFunc::create([=](){
			_layout->setVisible(true);
			showStarBetAni();
		}), RemoveSelf::create(), nullptr));
	}

	//��ʾ���Ǳ����Ķ���
	void GameTableUI::showStarBetAni()
	{
		for (int i = 0; i < 6; i++)
		{
			_setbtn[i]->setBright(false);
			_setbtn[i]->setEnabled(false);
		}
		_gameCell->playCompleteAni();
		runAction(Sequence::create(DelayTime::create(10.0f), CallFunc::create([=](){
			setPlayStartAndBet();
			setBtnState(true);//���Ƕ���������������а�ť�ɵ��
		}), nullptr));
	}

	//�����ϷֵĽ����ʾ
	void GameTableUI::setOnResult(int money)
	{
		setAllHandOff(money);
		if (getGameRule() == 1)
		{
			money = money - (_curLineBet * 8);//��ֹѺ�����Ϸֵ��µ����ݴ���
		}
		_curHandoff->setString(String::createWithFormat("%d", money)->getCString());
	}
	//�����������ע��
	void GameTableUI::setMaxLineBet(int bet)
	{
		_maxLineBet = bet;
		//Ϊ�˺�pcһ�¡��������õ���200�����ε����ֵ����200������pc����190���������յ����ݺ��ȼ�ȥ10
		//_maxLineBet -= 10;  //0109 ע�͵� add by leishengchao
	}
	//���õ��ߵ���ע��
	void GameTableUI::showAloneLineNum(int aloneNum)
	{
		for (int i = 0; i < 8; i++)
		{
			_aloneBetNum[i]->setString(String::createWithFormat("%d", aloneNum)->getCString());
		}
	}

	//�����н������Ĳ㼶
	void GameTableUI::setAllLineZorder(int zorder)
	{
		for (int i = 0; i < 8; i++)
		{
			if (_openAwardLine[i])
			{
				_line[i]->setLocalZOrder(zorder);
			}
		}
	}
	//���ú��Ĳ㼶
	void GameTableUI::setRedFrameZorder(int zorder)
	{
		for (int i = 0; i < 9; i++)//����Ӧ���жϵ�ǰ��ЩͼƬ�н���Ȼ����ʾ���Ӧ�ĺ��
		{
			_redFrame[i]->setLocalZOrder(zorder);
		}
	}

	//���濪��ͼ�ε�����
	void GameTableUI::setImageType(int imageType[9]) 
	{
		for (int i = 0; i < 9; i++)
		{
			_imageType[i] = imageType[i];
		}
	}
	//���ν���
	void GameTableUI::setSecondGetMoney(int secondMoney)
	{
		_secondMoney = secondMoney;
	}
	int GameTableUI::getSecondGetMoney()
	{
		return _secondMoney;
	}
	//���������Ӯ����
	void GameTableUI::setWinMoney(int money)
	{
		_userWinMoney = money;
	}
	int GameTableUI::getWinMoney()
	{
		return _userWinMoney;
	}

	//���浥���ʽ�
	void GameTableUI::saveSinglePond(LLONG money)
	{
		_singlePond = money;
	}

	//�ж���Ϸ�Ƿ�Ϊȫ��
	void GameTableUI::isAllGame(bool isAll)
	{
		_isAll = isAll;
	}
	bool GameTableUI::getAllGame()	
	{
		return _isAll;
	}

	//�����н�������
	void GameTableUI::saveWinLine(bool winLine[8])
	{
		for (int i = 0; i < 8; i++)
		{
			_openAwardLine[i] = winLine[i];
		}
	}

	//�ж���Ϸ���ͣ��Ƿ�Ϊ������Ϸ��
	void GameTableUI::setGameRule(BYTE rule)
	{
		_gameRule = rule;
	}
	BYTE GameTableUI::getGameRule()
	{
		return _gameRule;
	}

	//�����淨ʱ����ʾ�����淨������ͼƬ
	void GameTableUI::setSpecialRateImage(BYTE rate)
	{
		if (getGameRule() > 1 && getGameRule() < 5)
		{
			char str[32] = {0};
			sprintf(str, "Cherry97/num_%d.png", rate);
			_specialRate->loadTexture(str);
			_specialRate->setVisible(true);
			sprintf(str, "%d/%d", (getSpecialRestCount()),_SpecialRealCount);
			_specialCountText->setString(str);
			_specialCountText->setVisible(true);
		}
		else
		{
			_specialRate->setVisible(false);
			_specialCountText->setVisible(false);
		}
	}

	//���ý�������
	void GameTableUI::setAward(int score)
	{
		_gameAward->setAwardScore(score);
	}

	//��������ܳ���
	void GameTableUI::setAllHandOff(int handoff)
	{
		_handOff = handoff;
	}
	int GameTableUI::getAllHandOff()
	{
		return _handOff;
	}
	//����7�ĸ���
	void GameTableUI::set7Count(int count)
	{
		_7Count = count;
	}
	int GameTableUI::get7Count()
	{
		return _7Count;
	}

	//�����淨����
	void GameTableUI::setSpecialRestCount(BYTE count)
	{
		_SpecialCount = count;
	}

	void GameTableUI::setSpecialCount(BYTE count)
	{
		_SpecialRealCount = count;
	}

	BYTE GameTableUI::getSpecialRestCount()
	{
		return _SpecialCount;
	}

	//����ͼƬ����
	void GameTableUI::setRunCell()
	{
		//������Ϸ״̬Ϊ��Ϸ��
		_gameTableLogic->_gameState = GS_PLAY_GAME;
		setStop();
		//ͼƬ��ʼ����ʱ����������״̬
		setLineState();
		//ͼƬ��ʼ�������ͽ�_isStart��λtrue
		_isStart = true;
		_gameCell->setImageResult(_imageType);
		setBtnState(false);
		setStopStartAndBet();
		_tishiSp->setTexture(PROMPT_INSERT);
		if (getGameRule() > 1 && getSpecialRestCount() == 4)//������ǳ�����Ϸ,�������������淨�ĵ�һ�֣����Ȳ������Ƕ���
		{
			GameAudio::playSpecial();//�����淨������
			//�����淨ʱ�Ȳ��������淨����
			_gameCell->playNumAni(getGameRule());
			//�������Ƕ���ʱ�����ÿ�ʼ��ť���ɵ㣬��ֹ����
			_setbtn[2]->setBright(false);
			_setbtn[2]->setEnabled(false);
			runAction(Sequence::create(DelayTime::create(2.5f), CallFunc::create([=](){
				_setbtn[2]->setBright(true);
				_setbtn[2]->setEnabled(true);
				GameAudio::playRoll();//ת�̿�ʼת��������
				_gameCell->setCell();
				schedule(schedule_selector(GameTableUI::setRightAwayStop), 0.1f);
			}), nullptr));
		}
		else
		{
			setStop();//�л���ʼͼƬ���������ڽ������ó�ֹͣͼƬ��

			GameAudio::playRoll();//ת�̿�ʼת��������
			_gameCell->setCell();
			schedule(schedule_selector(GameTableUI::setRightAwayStop), 0.1f);
		}
	}

	//���Ƽ��㼴ͣ�ļ�ʱ��
	void GameTableUI::setRightAwayStop(float dt)
	{
		if (!_isStart)//������ڰ�ť��ֹͣ״̬�����һ�£��ͻ���ͼƬֹͣ������
		{
			scheduleOnce(schedule_selector(GameTableUI::setGameEnd), 0.5f);
			unschedule(schedule_selector(GameTableUI::setRightAwayStop));
		}
		else
		{
			_saveRightAwayTime += dt;
			if (_saveRightAwayTime >= 3.5f)
			{
				unschedule(schedule_selector(GameTableUI::setRightAwayStop));
				scheduleOnce(schedule_selector(GameTableUI::setGameEnd), 0.1f);
			}
		}
	}

	//��Ϸ��������
	void GameTableUI::setGameEnd(float dt)
	{
		//��Ϸ������ʱ�䣬�Ͱ�ֹͣ��ť��Ϊ���ɵ��
		_setbtn[2]->setBright(false);
		_setbtn[2]->setEnabled(false);
		if (getAllGame())//ȫ��
		{
			showAllGameAni();
			showShareAward();
		}
		else
		{
			if (get7Count() > 1)
			{
				showAllGameAni();
				if (get7Count() == 9){
					showShareAward();
				}
			}
			showWinningLine();
		}
		if (getWinMoney() > 0)
		{
			GameAudio::playLine();//�����н������������ͺ������
		}
		readyNextGame();
	}

	//��ʾ�н�������
	void GameTableUI::showWinningLine()
	{
		for (int i = 0; i < 8; i++)
		{
			if (_openAwardLine[i])//(false��ʾ����ʾ)
			{
				setAllLineZorder(MAX_LINE_ZORDER);
				_line[i]->runAction(Blink::create(2.0f, 3));
				_line[i]->setVisible(true);
			}
		}
		_curWinMoney->setString(String::createWithFormat("%d", getWinMoney())->getCString());
		_ewMoney->setString(StringUtils::format("%d", _gameAward->getAwardScore()));
	}

	//���ú�����ʾ״̬
	void GameTableUI::setRedFrameState(bool isVisib)
	{
		if (isVisib)
		{
			if (getAllGame())
			{
				for (int i = 0; i < 9; i++)
				{
					_redFrame[i]->setVisible(isVisib);
				}
			}
			else if (get7Count() > 1)
			{
				for (int i = 0; i < 9; i++)
				{
					if (_imageType[i] == 0)
					{
						_redFrame[i]->setVisible(isVisib);
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < 9; i++)
			{
				_redFrame[i]->setVisible(isVisib);
			}
		}
	}

	//��ʾȫ�̶���
	void GameTableUI::showAllGameAni()
	{
		_curWinMoney->setString(String::createWithFormat("%d", getWinMoney())->getCString());
		_ewMoney->setString(StringUtils::format("%d", _gameAward->getAwardScore()));
		setRedFrameState(true);
		setRedFrameZorder(MAX_LINE_ZORDER);
		if (getAllGame())
		{
			for (int i = 0; i < 9; i++)
			{
				_redFrame[i]->runAction(Blink::create(5.0f, 6));
			}
		}
		else if(get7Count() > 1)
		{
			for (int i = 0; i < 9; i++)
			{
				if (_imageType[i] == 0)
				{
					_redFrame[i]->runAction(Blink::create(5.0f, 6));
				}
			}
		}
	}

	void GameTableUI::showShareAward(){
		_isAuto = false;
		setAuto();
		setBtnState(true);
		GameShare* gameShare = GameShare::create(this);
		gameShare->setShareAward(m_shareAward);
		addChild(gameShare, MAX_ZORDER);
	}
	//������ʾ����������ݣ�׼����һ����Ϸ
	void GameTableUI::readyNextGame()
	{
		//��ʾ��õ��ܲʽ�
		if (_allWinnings > 0)
		{
			_textgetHandsel->setVisible(true);
			_getHandsel->setString(String::createWithFormat("%lld", _allWinnings)->getCString());
		}
		if (_gameAward->getAwardScore() > 0 || getWinMoney() > 0)
		{
			runAction(Sequence::create(DelayTime::create(3.0f), CallFunc::create([=](){
				GameAudio::playAward();//���Ŷ��⽱��������
				TextAtlas* iswin;
				_tishiSp->setTexture(PROMPT_WIN);
				_curWinMoney->setString(String::createWithFormat("%d", getWinMoney())->getCString());
				
				if (_singleWinnings > 0)
				{
					iswin = _handsel;
				}
				else
				{
					iswin = _handselAll;
				}
				_setbtn[5]->setBright(true);
				_setbtn[5]->setEnabled(true);

				_gameAward->showAwardFrame(_curHandoff, _ewMoney, _curWinMoney, iswin, _singleWinnings, _gameAward->getAwardScore(), getWinMoney(), getSecondGetMoney());
				setAllLineZorder(MIN_LINE_ZORDER);
				setRedFrameZorder(MIN_LINE_ZORDER);
			}), nullptr));
		}
		else
		{
			//ȥ����Ϸʧ����Ч
			//GameAudio::playlose();//�������
			_tishiSp->setTexture(PROMPT_OVER);
			runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create([=](){
				setAllLineZorder(MIN_LINE_ZORDER);
				setRedFrameZorder(MIN_LINE_ZORDER);
				setGameEndData();
			}), nullptr));
		}
	}

	//������Ϸ�����������
	void GameTableUI::setGameEndData()
	{
		_setbtn[5]->setBright(false);
		_setbtn[5]->setEnabled(false);
		_curHandoff->setString(String::createWithFormat("%d", getAllHandOff())->getCString());
		_handsel->setString(String::createWithFormat("%lld", _singlePond)->getCString());
		setGameStartData();
		sendGameOver();//���ͽ�����Ϸ����Ϣ
	}

	void GameTableUI::setGameOver(bool isOver)
	{
		_gameTableLogic->_gameState = GS_WAIT_NEXT;//���õ�ǰΪ�ȴ�״̬
		_textgetHandsel->setVisible(false);
		_getHandsel->setString("");
		setBtnState(true);
		setLineState();
		setRedFrameState(false);
		if (getSpecialRestCount() > 0)
		{
			//�����淨ʱ��������Ѻ��
			_setbtn[1]->setBright(false);
			_setbtn[1]->setEnabled(false);
			if (_isAuto)
			{
				if (getAllHandOff() < (_saveLineBet * 8))
				{
					_isAuto = false;
					setAuto();
				}
				else
				{
					sendGameStartRoll();
				}
			}
		}
		else
		{
			_curLineBet = 0;
			if (_isAuto)
			{
				if (getAllHandOff() < (_saveLineBet * 8))
				{
					_isAuto = false;
					setAuto();
					setBtnState(true);
				}
				else
				{
					setAutoGame();//�ж���Ϸ�Ƿ��Զ���ʼ
				}
			}
		}
	}
	//�������������Ϸ��������Ϣ
	void GameTableUI::sendGameOver()
	{
		C_S_GameEnd gc ;
		gc.bGameOver = true;
		sendData(MDM_GM_GAME_NOTIFY, C_S_GAME_OVER, &gc, sizeof(gc));
	}

	//���Ͳ鿴��һҳ���ݵ���Ϣ
	void GameTableUI::sendNextPageReq()
	{
		C_S_Next_Prize np;
		np.bFlag = true;
		sendData(MDM_GM_GAME_NOTIFY, C_S_NEXT_PAGE_PRIZE, &np, sizeof(np));
	}
	//���Ͳ鿴��һҳ���ݵ���Ϣ
	void GameTableUI::sendLastPageReq()
	{
		sendData(MDM_GM_GAME_NOTIFY, C_S_CHECK_PRIZE, NULL, sizeof(NULL));
	}

	void GameTableUI::setGameStartData()
	{
		if (getSpecialRestCount() == 0)
		{
			_specialRate->setVisible(false);
			_specialCountText->setVisible(false);
			_curAllBet->setString(String::createWithFormat("%d", 0)->getCString());
			showAloneLineNum(0);
		}
		//��ͼƬ״̬���óɿ�ʼ
		_setbtn[2]->loadTextureNormal(BTN_STARTN);
		_setbtn[2]->loadTexturePressed(BTN_STARTS);
		_setbtn[2]->loadTextureDisabled(BTN_STARTD);
		//���Ƿ�ʼ������ֵΪfalse,��ʾ�����Ѿ�ֹͣת��
		_isStart = false;
		
		_saveRightAwayTime = 0.0f;

		setPlayStartAndBet();
		_curWinMoney->setString("");
		_ewMoney->setString("");
		setSecondGetMoney(0);
	}

	//����ʽ�
	void GameTableUI::setWinnings(LLONG allHandsel)
	{
		_handselAll->setString(String::createWithFormat("%lld", allHandsel)->getCString());
		//_handsel->setString(String::createWithFormat("%lld", fangjianHandsel)->getCString());
	}

	//�������õĵ����ʽ�
	void GameTableUI::setSingleWinnings(LLONG winning)
	{
		_singleWinnings = winning;
	}

	//�������õ��ܲʽ�
	void GameTableUI::setAllWinnings(LLONG winning)
	{
		_allWinnings = winning;
	}

	//��ʾ���߽����ǵĲʽ�
	void GameTableUI::setHandsel(LLONG winning, LLONG allwinning)
	{
		_handsel->setString(String::createWithFormat("%lld", winning)->getCString());
		_handselAll->setString(String::createWithFormat("%lld", allwinning)->getCString());
	}

	//�����Լ��Ľ��
	void GameTableUI::setMyMoney(LLONG money)
	{
		_userMoney->setString(String::createWithFormat("%lld", money)->getCString());
	}

	//�Զ���Ϸ
	void GameTableUI::setAutoGame()
	{
		if (_isAuto)
		{
			if (_curLineBet <= 0)
			{
				int curHand = atoi(_curHandoff->getString().c_str());//��ǰ�ܳ���
				if (_saveLineBet == 0)
				{
					_saveLineBet = 10;
				}
				if (curHand >= (_saveLineBet * 8))
				{
					_curLineBet = _saveLineBet;
					_curAllBet->setString(String::createWithFormat("%d", (_curLineBet * 8))->getCString());
					int num = curHand - (_saveLineBet * 8);
					_curHandoff->setString(String::createWithFormat("%d", num)->getCString());
					sendGameStartRoll();
				}
				else
				{
					_isAuto = false;
					setAuto();
					setBtnState(true);
				}
			}
			else
			{
				setBtnState(false);
				setStop();
				sendGameStartRoll();
			}
		}
		else
		{
			_curLineBet = 0;
		}
		showAloneLineNum(_curLineBet);
	}

	//�����㲥��
	void GameTableUI::addRadioFrame()
	{
		_radioFrame = Sprite::create(NOTIC_BG);
		_radioFrame->setAnchorPoint(Vec2(0.5f, 0.0f));
		_radioFrame->setPosition(Vec2(_turnBg->getContentSize().width/2, _turnBg->getContentSize().height));
		_radioFrame->setCascadeOpacityEnabled(true);
		_turnBg->addChild(_radioFrame, MAX_ZORDER);
		_radioFrame->setVisible(false);
		_radioFrame->setCascadeOpacityEnabled(true);

		_radio = GameNotice::createGameNotice(Bg_Stencil);
		_radio->setPosition(Vec2(_radioFrame->getContentSize().width * 0.50f, _radioFrame->getContentSize().height / 2));
		_radio->setCascadeOpacityEnabled(true);
		_radio->setTag(888);
		_radio->setCallBack([this](){
			_radioFrame->setVisible(false);
		});
		_radioFrame->addChild(_radio);
	}
	//��ʾ�㲥
	void GameTableUI::showRadio(const std::string& str)
	{
		_radioFrame->setVisible(true);
		_radio->postMessage(GBKToUtf8(str), 0);//��ʾ�㲥��Ϣ
	}

	void GameTableUI::setPromptText(const std::string& prompt)
	{
		_tTishi->setString(prompt);
	}

	void GameTableUI::showCheckPrize(int AllCount[18])
	{
		if (_nextaward != nullptr)
		{
			_nextaward->removeFromParent();
			_nextaward = nullptr;
		}
		//��ͼ
		_lastaward = GameCheckAward::create(this);
		_lastaward->setAwardInfo(AllCount);
		_lastaward->setPosition(winSize/2);
		addChild(_lastaward);
	}
	//��ʾ��һҳ�󽱽���
	void GameTableUI::showCheckPrizeNext(UINT AllCount[12])
	{
		if (_lastaward != nullptr)
		{
			_lastaward->removeFromParent();
			_lastaward = nullptr;
		}
		//��ͼ
		_nextaward = GameCheckAwardNext::create(this);
		_nextaward->setAwardInfo(AllCount);
		_nextaward->setPosition(winSize/2);
		addChild(_nextaward);
	}

	//��ʾ���ʲ�
	void GameTableUI::showBetLayer()
	{
		auto showbet = GameBet::create();
		showbet->setPosition(winSize/2);
		addChild(showbet, 100);
	}

	//�ֻ����ؼ������ص�����
	void GameTableUI::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
	{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if (EventKeyboard::KeyCode::KEY_BACK != keyCode) return;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		if (EventKeyboard::KeyCode::KEY_F1 != keyCode) return;
#endif
		returnMain();
	}

	void GameTableUI::returnMain()
	{
		if (_gameTableLogic->_gameState == GS_WAIT_NEXT)
		{
			//�Ͽ��������ӣ��˳���¼
			if (!_isOutWait)
			{
				_isOutWait = true;
				if (RoomLogic()->isConnect())
				{
					_gameTableLogic->sendUserUp();
				//	RoomLogic()->close();
					GamePlatform::returnPlatform(LayerType::DESKLIST);
				}
				else
				{
					RoomLogic()->close();
					GamePlatform::returnPlatform(LayerType::ROOMLIST);
				}
			}
		}
		else
		{
			isPopGame();
		}
	}

	//���õ�����ʾ
	void GameTableUI::setOnConnect()
	{
		auto prompt = GamePromptLayer::create();
		prompt->showPrompt(GBKToUtf8("�ѵ��ߣ������µ�¼��"));
		prompt->setCallBack([=](){
			GameMenu::createMenu();
		});
	}

	void GameTableUI::dealLeaveDesk()
	{
		RoomLogic()->close();
		GamePlatform::returnPlatform(LayerType::ROOMLIST);
	}

	//��ʼ��������Ϣ
	void GameTableUI::sendGameStartRoll()
	{
		int curHand = atoi(_curHandoff->getString().c_str());//��ǰ�ܳ���
		int curallBet = atoi(_curAllBet->getString().c_str());//��ǰ�ܳ���
		if (curallBet == 0)
		{
			if (_saveLineBet == 0)
			{
				_saveLineBet = 10;
			}
			if (curHand >= (_saveLineBet * 8))
			{
				if (_curLineBet == 0) 
				{
					_curLineBet = _saveLineBet;
					_curAllBet->setString(String::createWithFormat("%d", (_curLineBet * 8))->getCString());
					int num = curHand - (_saveLineBet * 8);
					_curHandoff->setString(String::createWithFormat("%d", num)->getCString());
				}
			}
			else
			{
				_isAuto = false;
				setBtnState(true);
				setAuto();
				return;
			}
		}
		_curLineBet = _saveLineBet;
		showAloneLineNum(_curLineBet);
		_curAllBet->setString(String::createWithFormat("%d", (_curLineBet * 8))->getCString());
		C_S_StartRoll roll;
		roll.byDeposit = _curLineBet;
		roll.byLines = ALLLINE;
		sendData(MDM_GM_GAME_NOTIFY, C_S_START_ROLL, &roll, sizeof(roll));
		_saveLineBet = _curLineBet;

		_gameTableLogic->m_userAllMoney = atol(_userMoney->getString().c_str());
	}

	void GameTableUI::isPopGame()
	{
		//���κ���Ĳ�
		auto colorLayer = LayerColor::create(Color4B(0, 0, 0, 0));
		addChild(colorLayer,2000);

		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan = [=](Touch* touch ,Event* event){
			return true;
		};
		touchListener->setSwallowTouches(true);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,colorLayer);

		auto popText = Sprite::create("Cherry97/prompt.png");
		popText->setPosition(winSize/2);
		addChild(popText, 2000);
		popText->runAction(Sequence::create(DelayTime::create(1.0f), FadeOut::create(1.0f), CallFunc::create([=](){
			colorLayer->removeFromParent();
			popText->removeFromParent();
		}), nullptr));
	}

	void GameTableUI::setRoomInfo(char szRoomName[64], BYTE deskId){
		m_roomNameText->setString(GBKToUtf8(szRoomName));

		std::string str = StringUtils::format("%d", deskId) + "����";
		m_deskId->setString(GBKToUtf8(str));
	}

	void GameTableUI::setShareAward(int iShareAward){
		m_shareAward = iShareAward;
	}
}
