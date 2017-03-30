#include "Cherry97GameAward.h"
#include "HNLobbyExport.h"
#include "Cherry97GameAudio.h"

using namespace ui;

namespace Cherry97
{
	static const char* HISTORY_CSB	=    "Cherry97/Cherry97Ui/AwardNode.csb";    //奖励框
	GameAward* GameAward::create(GameTableUICallback* uiCallback)
	{
		GameAward* ref = new GameAward();
		if(ref->init(uiCallback))
		{
			ref->autorelease();
			return ref;
		}
		CC_SAFE_DELETE(ref);
		return nullptr;
	}

	bool GameAward::init(GameTableUICallback* uiCallback)
	{
		if(!HN::HNLayer::init())
		{
			return false;
		}
		_uicallback = uiCallback;
		winsize = Director::getInstance()->getWinSize();
		_loader = CSLoader::createNode(HISTORY_CSB);
		addChild(_loader);
		_layout = (Layout* ) _loader->getChildByName("Panel_1");
		_layout->setVisible(false);
		_TextAward = (TextAtlas* ) _layout->getChildByName("AtlasLabel_award");
		return true;
	}

	//判断是否显示奖励框
	void GameAward::showAwardFrame(TextAtlas* allMoney, TextAtlas* ewMoney, TextAtlas* defen, TextAtlas* caiJin, LLONG winWinnings,LLONG awardMoney, int winMoney, int secondMoney)
	{
		_caijin = atoi(caiJin->getString().c_str());
		_allMoney = atoi(allMoney->getString().c_str());
		_textAllMoney = allMoney;
		_textEW = ewMoney;
		_textDefen = defen;
		_textCaijin = caiJin;
		_winHandSel = winWinnings;
		_awardMoney = awardMoney;
		_winScore = winMoney;
		_secondMoney = secondMoney;
		if (_winHandSel > 0)//有彩金奖励就先加彩金
		{
			showWinningsSub();
		}
		else if(_awardMoney > 0)//有额外奖励没有彩金奖励，加额外奖励
		{
			showAwardSub();
		}
		else
		{
			showMyAllMoney();
		}
	}

	//显示彩金递减的动画
	void GameAward::showWinningsSub()
	{
		GameAudio::playAddMoney();
		_keepNUm = 0;
		if (_winHandSel >= 10000)
		{
			_stageNum = 103;
		}
		else if(_winHandSel > 1000 && _winHandSel < 10000)
		{
			_stageNum	 = 53;
		}
		else
		{
			_stageNum = 23;
		}
		schedule(schedule_selector(GameAward::updateWinningSub), 0.02f);
	}
	void GameAward::updateWinningSub(float dt)
	{
		_keepNUm += _stageNum;
		_textCaijin->setString(String::createWithFormat("%d", (_caijin -_keepNUm))->getCString());
		_textDefen->setString(String::createWithFormat("%d", (_keepNUm + _winScore))->getCString());
		if (_keepNUm >= _winHandSel)
		{
			_textCaijin->setString(String::createWithFormat("%d", _caijin - _winHandSel)->getCString());
			_textDefen->setString(String::createWithFormat("%lld", (_winHandSel + _winScore))->getCString());
			unschedule(schedule_selector(GameAward::updateWinningSub));
			if (_awardMoney > 0)
			{
				_winScore = atoi(_textDefen->getString().c_str());
				showAwardSub();
			}
			else
			{
				showMyAllMoney();
			}
		}
	}

	void GameAward::showAwardSub()
	{
		GameAudio::playAddMoney();
		_keepNUm = 0;
		if (_awardMoney >= 1000)
		{
			_stageNum = 51;
		}
		else if(_awardMoney > 500 && _awardMoney < 1000)
		{
			_stageNum	 = 26;
		}
		else
		{
			_stageNum = 17;
		}
		schedule(schedule_selector(GameAward::updateAwardSub), 0.02f);
	}
	void GameAward::updateAwardSub(float dt)
	{
		_keepNUm += _stageNum;
		_textEW->setString(String::createWithFormat("%lld", (_awardMoney -_keepNUm))->getCString());
		_textDefen->setString(String::createWithFormat("%d", (_keepNUm + _winScore))->getCString());
		if (_keepNUm >= _awardScore)
		{
			_textEW->setString("");
			_textDefen->setString(String::createWithFormat("%d", (_awardScore + _winScore))->getCString());
			unschedule(schedule_selector(GameAward::updateAwardSub));
			if (_secondMoney > 0)
			{
				_winScore = atoi(_textDefen->getString().c_str());
				runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create([=](){
					showSecondMoney();
				}) , nullptr));
			}
			else
			{
				showMyAllMoney();
			}
		}
	}

	void GameAward::showSecondMoney()
	{
		GameAudio::playAddMoney();
		_keepNUm = 0;
		if (_secondMoney >= 20000)
		{
			_stageNum = 321;
		}
		else if (_secondMoney >= 10000 && _secondMoney < 20000)
		{
			_stageNum = 103;
		}
		else if (_secondMoney >= 1000 && _secondMoney < 10000)
		{
			_stageNum = 68;
		}
		else if(_secondMoney > 500 && _secondMoney < 1000)
		{
			_stageNum = 26;
		}
		else
		{
			_stageNum = 17;
		}
		schedule(schedule_selector(GameAward::updateSecondMoney), 0.02f);
	}
	void GameAward::updateSecondMoney(float dt)
	{
		_keepNUm += _stageNum;
		_textEW->setString(String::createWithFormat("%d", (_secondMoney -_keepNUm))->getCString());
		_textDefen->setString(String::createWithFormat("%d", (_keepNUm + _winScore))->getCString());
		if (_keepNUm >= _secondMoney)
		{
			_textEW->setString("");
			_textDefen->setString(String::createWithFormat("%d", (_secondMoney + _winScore))->getCString());
			unschedule(schedule_selector(GameAward::updateSecondMoney));
			_winScore = atoi(_textDefen->getString().c_str());
			runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create([=](){
				showMyAllMoney();
			}) , nullptr));
		}
	}

	void GameAward::showMyAllMoney()
	{
		GameAudio::playAddMoney();
		_keepNUm = 0;
		if (_winScore >= 20000)
		{
			_stageNum = 321;
		}
		else if (_winScore >= 10000 && _winScore < 20000)
		{
			_stageNum = 103;
		}
		else if (_winScore >= 1000 && _winScore < 10000)
		{
			_stageNum = 68;
		}
		else if(_winScore >= 500 && _winScore < 1000)
		{
			_stageNum = 26;
		}
		else if(_winScore > 200 && _winScore < 500)
		{
			_stageNum = 11;
		}
		else
		{
			_stageNum = 1;
		}
		schedule(schedule_selector(GameAward::updateAllMoney), 0.02f);
	}
	void GameAward::updateAllMoney(float dt)
	{
		_keepNUm += _stageNum;
		_textDefen->setString(String::createWithFormat("%d", (_winScore -_keepNUm))->getCString());
		auto sc = atoi(_textDefen->getString().c_str());
		log("defen = %d", sc);
		_textAllMoney->setString(String::createWithFormat("%lld", (_allMoney + _keepNUm))->getCString());
		auto sa = atoi(_textAllMoney->getString().c_str());
		log("allMoney ======================== %lld", sa);
		if (_keepNUm >= _winScore)
		{
			_textDefen->setString("");
			_textAllMoney->setString(String::createWithFormat("%lld", (_allMoney + _winScore))->getCString());
			unschedule(schedule_selector(GameAward::updateAllMoney));
			_uicallback->setGameEndData();
		}
	}

	//停止所有计时器
	void GameAward::stopAllSchedule()
	{
		unschedule(schedule_selector(GameAward::updateWinningSub));
		unschedule(schedule_selector(GameAward::updateAwardSub));
		unschedule(schedule_selector(GameAward::updateSecondMoney));
		unschedule(schedule_selector(GameAward::updateAllMoney));
	}

	GameAward::GameAward()
	{
	}

	GameAward::~GameAward()
	{
	}
}