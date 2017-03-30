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
	static const char* GAME_MAIN_CSB	=    "Cherry97/Cherry97Ui/MainNode.csb";    //主界面
	static const int      SETBTN_TAG	=    20;           //控制按钮的标签值
	static const int      EXIT_TAG      =    30;           //退出按钮的标签值
	static const int      MAX_LINEBET   =    50;           //最大的单线下注额
    static const BYTE     ALLLINE       =    8;            //总线条数
	static const char*    NOTIC_BG		=    "Cherry97/MsgManager_BG.png";
	static const char*    Bg_Stencil	=    "Cherry97/Msg_BG.png";
	static const char*    BTN_CANAELN	=    "Cherry97/quxiao_02.png";//取消按钮
	static const char*    BTN_CANAELS   =    "Cherry97/quxiao_03.png";//取消按钮
	static const char*    BTN_CANAELD	=    "Cherry97/quxiao_04.png";//取消按钮
	static const char*    BTN_AUTON	    =    "Cherry97/autobtn_02.png";//自动按钮
	static const char*    BTN_AUTOS	    =    "Cherry97/autobtn_03.png";//自动按钮
	static const char*    BTN_AUTOD	    =    "Cherry97/autobtn_04.png";//自动按钮
	static const char*    BTN_STOPN	    =    "Cherry97/stop_02.png";//停止按钮
	static const char*    BTN_STOPS	    =    "Cherry97/stop_03.png";//停止按钮
	static const char*    BTN_STOPD	    =    "Cherry97/stop_04.png";//停止按钮
	static const char*    BTN_STARTN	=    "Cherry97/kaishi_02.png";//开始按钮
	static const char*    BTN_STARTS	=    "Cherry97/kaishi_03.png";//开始按钮
	static const char*    BTN_STARTD	=    "Cherry97/kaishi_04.png";//开始按钮

	static const char*    PROMPT_START	=    "Cherry97/PUSHSTART.png";//提示开始
	static const char*    PROMPT_BET	=    "Cherry97/PUSHBET.png";//提示下注
	static const char*    PROMPT_OVER	=    "Cherry97/gameover.png";//提示结束
	static const char*    PROMPT_WIN	=    "Cherry97/youwin.png";//提示赢
	static const char*    PROMPT_INSERT	=    "Cherry97/insertcoin.png";//提示游戏中
	static const char*    PROMPT_BONUS	=    "Cherry97/bonus.png";//提示大奖

	static int            MAX_ZORDER    = 10000; //最大层级
	static int            MIN_LINE_ZORDER = -1;  //线条的最小层级
	static int            MAX_LINE_ZORDER = 100; //线条的最大层级
	static int            SKIP_ZORDER   = 10001; //跳过按钮的层级

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
		GameAudio::playBackground();//背景音乐
		//进场动画
		addStartGameAnimate();
		createGameLayer();
		return true;
	}

	//进入主界面
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

		//提示语
		_tishiSp = Sprite::create();
		_tishiSp->setPosition(_tTishi->getPosition());
		_tTishi->getParent()->addChild(_tishiSp, MAX_ZORDER);
		getChildNode();

		//发送请求开始游戏
		_gameTableLogic = new GameTableLogic(this, _desk, _baotoCreate);
		_gameTableLogic->sendGameInfo();
		//创建转盘转动对象
		_gameCell = GameCell::create();
		addChild(_gameCell);
		_gameCell->setImage(_panelImage);
		_gameCell->showRollImage();
		//奖励框
		_gameAward = GameAward::create(this);
		addChild(_gameAward);

		//广播框
		addRadioFrame();
		//添加键盘监听事件
		auto keyBoard = EventListenerKeyboard::create();
		keyBoard->onKeyReleased= CC_CALLBACK_2(GameTableUI::onKeyReleased, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoard, this);
	}

	void GameTableUI::getChildNode()
	{
		char str[50];
		//游戏控制按钮
		for (int i = 0; i < 6; i++)
		{
			sprintf(str, "Button_set_%d", i);
			_setbtn[i] = (Button* ) _layout->getChildByName(str);
			_setbtn[i]->setTag(SETBTN_TAG + i);
			_setbtn[i]->addTouchEventListener(CC_CALLBACK_2(GameTableUI::BtnCallBack,this));
		}
		//倍率，设置，历史，玩家信息按钮
		_btnBet = (Button* ) _layout->getChildByName("Button_showBet");
		_btnBet->addTouchEventListener(CC_CALLBACK_2(GameTableUI::BtnCallBack,this));
		//强退按钮
		_exitBtn = (Button* ) _layout->getChildByName("Button_close");
		_exitBtn->setTag(EXIT_TAG);
		_exitBtn->addTouchEventListener(CC_CALLBACK_2(GameTableUI::BtnCallBack,this));
		//玩家昵称 
		_userName = (Text* ) _layout->getChildByName("Text_userName");
		sprintf(str, "%s", PlatformLogic()->loginResult.nickName);
		_userName->setString(GBKToUtf8(str));
		//玩家总金币
		_userMoney = (Text* ) _layout->getChildByName("Text_userMoney");
		sprintf(str, "%lld", PlatformLogic()->loginResult.i64Money);
		_userMoney->setString(GBKToUtf8(str));

		//房间信息
		m_roomNameText = (Text*)_layout->getChildByName("Text_RoomName");
		m_deskId = (Text*)_layout->getChildByName("Text_DeskId");
		//玩家总筹码数
		_curHandoff = (TextAtlas* ) _layout->getChildByName("AtlasLabel_zongchouma");
		_curHandoff->setString("0");
		//玩家总下注
		_curAllBet = (TextAtlas* ) _layout->getChildByName("AtlasLabel_zongxiazhu");
		//彩金值
		_handsel =  (TextAtlas* ) _turnBg->getChildByName("AtlasLabel_caijin_fangjian");
		_handselAll = (TextAtlas* ) _turnBg->getChildByName("AtlasLabel_caijin_all");
		_handselAll->setVisible(false);
		_textHandSelAll = (Text*)_turnBg->getChildByName("Text_fangjian");
		_textHandSelAll->setVisible(false);
		_textgetHandsel = (Text* ) _turnBg->getChildByName("Text_getCaijin");
		_textgetHandsel->setVisible(false);
		_getHandsel = (TextAtlas* ) _turnBg->getChildByName("AtlasLabel_getCaijin");
		_getHandsel->setString("");
		//玩家本局赢的钱数
		_curWinMoney = (TextAtlas*)_turnBg->getChildByName("AtlasLabel_winScore");
		_curWinMoney->setString("");
		//额外赢的钱
		_ewMoney = (TextAtlas* ) _turnBg->getChildByName("AtlasLabel_ewFen");
		_ewMoney->setString("");
		//殊玩法额度倍数显示图
		_specialRate = (ImageView* ) _turnBg->getChildByName("Image_specialRate");
		_specialRate->setVisible(false);
		_specialCountText = (TextAtlas* ) _turnBg->getChildByName("AtlasLabel_teshuRest");
		_specialCountText->setVisible(false);
		
		//滚动图片的裁剪层，九个全盘的红框
		for (int i = 0; i < 9; i++)
		{
			sprintf(str, "Panel_image_%d", i);
			_panelImage[i] = (Layout* ) _turnBg->getChildByName(str);
			sprintf(str, "Image_redFrame_%d", i);
			_redFrame[i] = (ImageView* )  _turnBg->getChildByName(str);
		}
		//获取8条线、8个单线下注数量
		for (int i = 0; i < 8; i++)
		{
			sprintf(str, "Image_line_%d", i);
			_line[i] = (ImageView* ) _turnBg->getChildByName(str);
			sprintf(str, "AtlasLabel_line_%d", i);
			_aloneBetNum[i] = (TextAtlas* ) _turnBg->getChildByName(str);
		}
		setLineState();//设置线条的初始状态为隐藏
		setRedFrameState(false);//设置红框的初始状态为隐藏
	}

	void GameTableUI::BtnCallBack(Ref* pSender, Widget::TouchEventType type)
	{
		auto i= ImageView::create();

		if (Widget::TouchEventType::ENDED != type) return;
		GameAudio::playBtn();//按键声
		Button* btn = (Button* ) pSender;
		int btnTag = btn->getTag();
		switch (btnTag)
		{
		case SETBTN_TAG://上分
			{
				C_S_ShangFen shangfen;
				shangfen.bIsShangFen = true;
				sendData(MDM_GM_GAME_NOTIFY, C_S_SHANG_FEN, &shangfen, sizeof(shangfen));
				break;
			}
		case SETBTN_TAG + 1:
			{
				//(押分不需要给服务器发消息，先本地保存，发转盘消息时一起发送押分值)
				if (_curLineBet < _maxLineBet)
				{
					int curHand = atoi(_curHandoff->getString().c_str());//当前总筹码
					if (curHand >= 80)
					{
						_curLineBet += 10;
						_curAllBet->setString(String::createWithFormat("%d", (_curLineBet * 8))->getCString());
						int num = curHand - 80;
						_curHandoff->setString(String::createWithFormat("%d", num)->getCString());
						int curhand = atoi(_curHandoff->getString().c_str());//当前总筹码
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
				//自动游戏的设置
				if (_isAuto)
				{
					if (_gameTableLogic->_gameState == GS_WAIT_NEXT)
					{
						setAutoGame();//判断游戏是否自动开始
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
		//游戏控制按钮
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

	//设置开始/停止的图片状态
	void GameTableUI::setStop()
	{
		//将图片状态设置成停止
		_setbtn[2]->loadTextureNormal(BTN_STOPN);
		_setbtn[2]->loadTexturePressed(BTN_STOPS);
		_setbtn[2]->loadTextureDisabled(BTN_STOPD);
		//将是否开始变量赋值为true,表示现在已经开始转动
		_isStart = true;
		//点击开始后，将停止按钮设置成可点状态
		_setbtn[2]->setBright(true);
		_setbtn[2]->setEnabled(true);
	}
	void GameTableUI::setStart()
	{
		//将图片状态设置成开始
		_setbtn[2]->loadTextureNormal(BTN_STARTN);
		_setbtn[2]->loadTexturePressed(BTN_STARTS);
		_setbtn[2]->loadTextureDisabled(BTN_STARTD);
		//将是否开始变量赋值为false,表示现在停止转动
		_isStart = false;
		//设置滚动图片是否立即停止，传false为立即停止
		_gameCell->setIsStop(_isStart);
		//点击停止后，将开始按钮设置成不可点状态
		_setbtn[2]->setBright(false);
		_setbtn[2]->setEnabled(false);
	}

	//设置自动/取消的图片状态
	void GameTableUI::setAuto()
	{
		//将图片状态设置成开始
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
	//停止开始和下注图片闪动的动画
	void GameTableUI::setStopStartAndBet()
	{
		_tishiSp->stopAllActions();
	}

	//添加开始动画
	void GameTableUI::addStartGameAnimate()
	{
		showGameNameAni();
	}

	//显示游戏名称的动画
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

	//显示开场时的倍率动画
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

	//显示明星倍数的动画
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
			setBtnState(true);//明星动画播放完后，让所有按钮可点击
		}), nullptr));
	}

	//设置上分的结果显示
	void GameTableUI::setOnResult(int money)
	{
		setAllHandOff(money);
		if (getGameRule() == 1)
		{
			money = money - (_curLineBet * 8);//防止押分又上分导致的数据错误
		}
		_curHandoff->setString(String::createWithFormat("%d", money)->getCString());
	}
	//设置最大线条注数
	void GameTableUI::setMaxLineBet(int bet)
	{
		_maxLineBet = bet;
		//为了和pc一致。现在配置的是200，手游的最大值就是200，但是pc的是190，所以在收到数据后先减去10
		//_maxLineBet -= 10;  //0109 注释掉 add by leishengchao
	}
	//设置单线的下注数
	void GameTableUI::showAloneLineNum(int aloneNum)
	{
		for (int i = 0; i < 8; i++)
		{
			_aloneBetNum[i]->setString(String::createWithFormat("%d", aloneNum)->getCString());
		}
	}

	//设置中奖线条的层级
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
	//设置红框的层级
	void GameTableUI::setRedFrameZorder(int zorder)
	{
		for (int i = 0; i < 9; i++)//这里应该判断当前哪些图片中奖，然后显示相对应的红框
		{
			_redFrame[i]->setLocalZOrder(zorder);
		}
	}

	//保存开奖图形的数据
	void GameTableUI::setImageType(int imageType[9]) 
	{
		for (int i = 0; i < 9; i++)
		{
			_imageType[i] = imageType[i];
		}
	}
	//二次奖励
	void GameTableUI::setSecondGetMoney(int secondMoney)
	{
		_secondMoney = secondMoney;
	}
	int GameTableUI::getSecondGetMoney()
	{
		return _secondMoney;
	}
	//保存玩家输赢分数
	void GameTableUI::setWinMoney(int money)
	{
		_userWinMoney = money;
	}
	int GameTableUI::getWinMoney()
	{
		return _userWinMoney;
	}

	//保存单机彩金
	void GameTableUI::saveSinglePond(LLONG money)
	{
		_singlePond = money;
	}

	//判断游戏是否为全盘
	void GameTableUI::isAllGame(bool isAll)
	{
		_isAll = isAll;
	}
	bool GameTableUI::getAllGame()	
	{
		return _isAll;
	}

	//保存中奖的线条
	void GameTableUI::saveWinLine(bool winLine[8])
	{
		for (int i = 0; i < 8; i++)
		{
			_openAwardLine[i] = winLine[i];
		}
	}

	//判断游戏类型（是否为常规游戏）
	void GameTableUI::setGameRule(BYTE rule)
	{
		_gameRule = rule;
	}
	BYTE GameTableUI::getGameRule()
	{
		return _gameRule;
	}

	//特殊玩法时，显示特殊玩法倍数的图片
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

	//设置奖励分数
	void GameTableUI::setAward(int score)
	{
		_gameAward->setAwardScore(score);
	}

	//保存玩家总筹码
	void GameTableUI::setAllHandOff(int handoff)
	{
		_handOff = handoff;
	}
	int GameTableUI::getAllHandOff()
	{
		return _handOff;
	}
	//设置7的个数
	void GameTableUI::set7Count(int count)
	{
		_7Count = count;
	}
	int GameTableUI::get7Count()
	{
		return _7Count;
	}

	//特殊玩法局数
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

	//设置图片滚动
	void GameTableUI::setRunCell()
	{
		//设置游戏状态为游戏中
		_gameTableLogic->_gameState = GS_PLAY_GAME;
		setStop();
		//图片开始滚动时，设置线条状态
		setLineState();
		//图片开始滚动，就将_isStart置位true
		_isStart = true;
		_gameCell->setImageResult(_imageType);
		setBtnState(false);
		setStopStartAndBet();
		_tishiSp->setTexture(PROMPT_INSERT);
		if (getGameRule() > 1 && getSpecialRestCount() == 4)//如果不是常规游戏,且现在是特殊玩法的第一轮，就先播放明星动画
		{
			GameAudio::playSpecial();//特殊玩法的音乐
			//特殊玩法时先播放特殊玩法动画
			_gameCell->playNumAni(getGameRule());
			//播放明星动画时，先让开始按钮不可点，防止出错
			_setbtn[2]->setBright(false);
			_setbtn[2]->setEnabled(false);
			runAction(Sequence::create(DelayTime::create(2.5f), CallFunc::create([=](){
				_setbtn[2]->setBright(true);
				_setbtn[2]->setEnabled(true);
				GameAudio::playRoll();//转盘开始转动的音乐
				_gameCell->setCell();
				schedule(schedule_selector(GameTableUI::setRightAwayStop), 0.1f);
			}), nullptr));
		}
		else
		{
			setStop();//切换开始图片的纹理（现在将它设置成停止图片）

			GameAudio::playRoll();//转盘开始转动的音乐
			_gameCell->setCell();
			schedule(schedule_selector(GameTableUI::setRightAwayStop), 0.1f);
		}
	}

	//控制即点即停的计时器
	void GameTableUI::setRightAwayStop(float dt)
	{
		if (!_isStart)//如果现在按钮是停止状态，点击一下，就会让图片停止滚动。
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

	//游戏结算设置
	void GameTableUI::setGameEnd(float dt)
	{
		//游戏到结算时间，就把停止按钮设为不可点击
		_setbtn[2]->setBright(false);
		_setbtn[2]->setEnabled(false);
		if (getAllGame())//全盘
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
			GameAudio::playLine();//播放中奖的线条声音和红框声音
		}
		readyNextGame();
	}

	//显示中奖的线条
	void GameTableUI::showWinningLine()
	{
		for (int i = 0; i < 8; i++)
		{
			if (_openAwardLine[i])//(false表示不显示)
			{
				setAllLineZorder(MAX_LINE_ZORDER);
				_line[i]->runAction(Blink::create(2.0f, 3));
				_line[i]->setVisible(true);
			}
		}
		_curWinMoney->setString(String::createWithFormat("%d", getWinMoney())->getCString());
		_ewMoney->setString(StringUtils::format("%d", _gameAward->getAwardScore()));
	}

	//设置红框的显示状态
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

	//显示全盘动画
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
	//动画显示完后清理数据，准备下一局游戏
	void GameTableUI::readyNextGame()
	{
		//显示获得的总彩金
		if (_allWinnings > 0)
		{
			_textgetHandsel->setVisible(true);
			_getHandsel->setString(String::createWithFormat("%lld", _allWinnings)->getCString());
		}
		if (_gameAward->getAwardScore() > 0 || getWinMoney() > 0)
		{
			runAction(Sequence::create(DelayTime::create(3.0f), CallFunc::create([=](){
				GameAudio::playAward();//播放额外奖励的音乐
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
			//去掉游戏失败音效
			//GameAudio::playlose();//输的音乐
			_tishiSp->setTexture(PROMPT_OVER);
			runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create([=](){
				setAllLineZorder(MIN_LINE_ZORDER);
				setRedFrameZorder(MIN_LINE_ZORDER);
				setGameEndData();
			}), nullptr));
		}
	}

	//处理游戏结束后的数据
	void GameTableUI::setGameEndData()
	{
		_setbtn[5]->setBright(false);
		_setbtn[5]->setEnabled(false);
		_curHandoff->setString(String::createWithFormat("%d", getAllHandOff())->getCString());
		_handsel->setString(String::createWithFormat("%lld", _singlePond)->getCString());
		setGameStartData();
		sendGameOver();//发送结束游戏的消息
	}

	void GameTableUI::setGameOver(bool isOver)
	{
		_gameTableLogic->_gameState = GS_WAIT_NEXT;//设置当前为等待状态
		_textgetHandsel->setVisible(false);
		_getHandsel->setString("");
		setBtnState(true);
		setLineState();
		setRedFrameState(false);
		if (getSpecialRestCount() > 0)
		{
			//特殊玩法时，不允许押分
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
					setAutoGame();//判断游戏是否自动开始
				}
			}
		}
	}
	//向服务器发送游戏结束的消息
	void GameTableUI::sendGameOver()
	{
		C_S_GameEnd gc ;
		gc.bGameOver = true;
		sendData(MDM_GM_GAME_NOTIFY, C_S_GAME_OVER, &gc, sizeof(gc));
	}

	//发送查看下一页数据的消息
	void GameTableUI::sendNextPageReq()
	{
		C_S_Next_Prize np;
		np.bFlag = true;
		sendData(MDM_GM_GAME_NOTIFY, C_S_NEXT_PAGE_PRIZE, &np, sizeof(np));
	}
	//发送查看上一页数据的消息
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
		//将图片状态设置成开始
		_setbtn[2]->loadTextureNormal(BTN_STARTN);
		_setbtn[2]->loadTexturePressed(BTN_STARTS);
		_setbtn[2]->loadTextureDisabled(BTN_STARTD);
		//将是否开始变量赋值为false,表示现在已经停止转动
		_isStart = false;
		
		_saveRightAwayTime = 0.0f;

		setPlayStartAndBet();
		_curWinMoney->setString("");
		_ewMoney->setString("");
		setSecondGetMoney(0);
	}

	//处理彩金
	void GameTableUI::setWinnings(LLONG allHandsel)
	{
		_handselAll->setString(String::createWithFormat("%lld", allHandsel)->getCString());
		//_handsel->setString(String::createWithFormat("%lld", fangjianHandsel)->getCString());
	}

	//保存所得的单机彩金
	void GameTableUI::setSingleWinnings(LLONG winning)
	{
		_singleWinnings = winning;
	}

	//保存所得的总彩金
	void GameTableUI::setAllWinnings(LLONG winning)
	{
		_allWinnings = winning;
	}

	//显示断线进来是的彩金
	void GameTableUI::setHandsel(LLONG winning, LLONG allwinning)
	{
		_handsel->setString(String::createWithFormat("%lld", winning)->getCString());
		_handselAll->setString(String::createWithFormat("%lld", allwinning)->getCString());
	}

	//设置自己的金币
	void GameTableUI::setMyMoney(LLONG money)
	{
		_userMoney->setString(String::createWithFormat("%lld", money)->getCString());
	}

	//自动游戏
	void GameTableUI::setAutoGame()
	{
		if (_isAuto)
		{
			if (_curLineBet <= 0)
			{
				int curHand = atoi(_curHandoff->getString().c_str());//当前总筹码
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

	//创建广播框
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
	//显示广播
	void GameTableUI::showRadio(const std::string& str)
	{
		_radioFrame->setVisible(true);
		_radio->postMessage(GBKToUtf8(str), 0);//显示广播信息
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
		//大奖图
		_lastaward = GameCheckAward::create(this);
		_lastaward->setAwardInfo(AllCount);
		_lastaward->setPosition(winSize/2);
		addChild(_lastaward);
	}
	//显示下一页大奖界面
	void GameTableUI::showCheckPrizeNext(UINT AllCount[12])
	{
		if (_lastaward != nullptr)
		{
			_lastaward->removeFromParent();
			_lastaward = nullptr;
		}
		//大奖图
		_nextaward = GameCheckAwardNext::create(this);
		_nextaward->setAwardInfo(AllCount);
		_nextaward->setPosition(winSize/2);
		addChild(_nextaward);
	}

	//显示倍率层
	void GameTableUI::showBetLayer()
	{
		auto showbet = GameBet::create();
		showbet->setPosition(winSize/2);
		addChild(showbet, 100);
	}

	//手机返回键监听回调函数
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
			//断开网络连接，退出登录
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

	//设置掉线提示
	void GameTableUI::setOnConnect()
	{
		auto prompt = GamePromptLayer::create();
		prompt->showPrompt(GBKToUtf8("已掉线，请重新登录。"));
		prompt->setCallBack([=](){
			GameMenu::createMenu();
		});
	}

	void GameTableUI::dealLeaveDesk()
	{
		RoomLogic()->close();
		GamePlatform::returnPlatform(LayerType::ROOMLIST);
	}

	//开始滚动的消息
	void GameTableUI::sendGameStartRoll()
	{
		int curHand = atoi(_curHandoff->getString().c_str());//当前总筹码
		int curallBet = atoi(_curAllBet->getString().c_str());//当前总筹码
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
		//屏蔽后面的层
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

		std::string str = StringUtils::format("%d", deskId) + "号桌";
		m_deskId->setString(GBKToUtf8(str));
	}

	void GameTableUI::setShareAward(int iShareAward){
		m_shareAward = iShareAward;
	}
}
