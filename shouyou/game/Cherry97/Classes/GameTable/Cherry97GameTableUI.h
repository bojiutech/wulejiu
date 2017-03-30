#ifndef __Cherry97_Game_Table_UI_H__
#define __Cherry97_Game_Table_UI_H__

#include "Cherry97GameTableUICallback.h"
#include "Cherry97GameCell.h"
#include "Cherry97GameAward.h"
#include "Cherry97GameCheckAwardNext.h"
#include "Cherry97GameShare.h"
#include "HNNetExport.h"
#include "HNLobbyExport.h"
#include "cocos2d.h"
#include <vector>

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocostudio;

namespace Cherry97
{
	class GameTableLogic;
	class GameCheckAward;
	class GameCheckAwardNext;
	class GameShare;
	class GameTableUI : public HN::HNGameUIBase, public GameTableUICallback
	{
	public:
		static GameTableUI* create(char bDeskIndex, bool bAutoCreate);
		virtual bool init(char bDeskIndex, bool bAutoCreate);
		GameTableUI();
		virtual ~GameTableUI();	
		virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) override;
		void returnMain();
		BYTE _desk;
		bool _baotoCreate;
	public:
		Node* _loader;
		Layout* _layout;
		ImageView* _mainBg;
		ImageView* _turnBg;
		//裁剪层图片
		Layout* _panelImage[9];
		//8条连线
		ImageView* _line[8];
		//九个全盘闪烁的框
		ImageView* _redFrame[9];
		//8个单线下注数
		TextAtlas* _aloneBetNum[8];
		//游戏控制按钮
		Button* _setbtn[6];
		//退出按钮
		Button* _exitBtn;
		//玩家昵称 
		Text* _userName;
		//玩家总金币
		Text* _userMoney;
		//玩家游戏筹码数
		TextAtlas* _curHandoff;
		//玩家总下注
		TextAtlas* _curAllBet;
		//彩金值
		TextAtlas* _handsel;//房间彩金
		
		TextAtlas* _handselAll;//总彩金
		Text* _textHandSelAll;

		Text* _textgetHandsel;
		TextAtlas* _getHandsel;//获得的总彩金
		//玩家本局赢的钱数
		TextAtlas* _curWinMoney;
		//玩家本局额外赢的钱
		TextAtlas* _ewMoney;
		//提示文本
		Text* _tTishi;
		//倍率
		Button* _btnBet;
		//显示特殊倍数的图片
		ImageView* _specialRate;
		//显示特殊玩法当前的局数
		TextAtlas* _specialCountText;

		Text* m_roomNameText;

		Text* m_deskId;

		int m_shareAward;

		LayerColor* colorLayer;
	private:
		Size winSize;
		GameTableLogic*	_gameTableLogic;
		GameCell* _gameCell;
		GameAward* _gameAward;

		//广播背景图
		Sprite* _radioFrame;
		GameNotice* _radio;

		Sprite* _tishiSp;

		bool _isOutWait;
		int _maxLineBet;//最大单线下注额
		int _imageType[9];//保存开奖的图片信息
		int _userWinMoney;//保存玩家输赢筹码
		bool _openAwardLine[8];//开奖的线条
		int _curLineBet;//本局单线下注额
		bool _isAuto;//是否自动游戏  true-是，false-否
		int _curStarBet;//当前明星倍数
		bool _isAll;//转盘结果 true-是全盘 false-不是全盘
		BYTE _gameRule;//0:代表常规游戏  1:代表2倍奖励  2:代表3倍奖励  3:代表4倍奖励
		BYTE _SpecialCount;//特殊玩法局数
		BYTE _SpecialRealCount;//特殊玩法局数
		int _7Count;//7的个数
		int _handOff;//结算时玩家总的筹码
		bool _isStart;//判断显示是否为游戏中
		float _saveRightAwayTime;//控制即点即停的时间
		int _saveLineBet;//保存单线下注
		LLONG _singleWinnings;
		LLONG _allWinnings;
		float _dt;//记录要延迟的时间
		int _secondMoney;
		GameCheckAward* _lastaward;
		GameCheckAwardNext* _nextaward;
		LLONG _singlePond;//保存单机彩金
	private:
		void getChildNode();
		void BtnCallBack(Ref* pSender, Widget::TouchEventType type);
		void createGameLayer();
		//设置单线的下注数
		void showAloneLineNum(int aloneNum);
		//自动游戏
		void setAutoGame();
		//显示中奖的线条
		void showWinningLine();
		//创建广播框
		void addRadioFrame();

		//游戏结算设置
		virtual void setGameEnd(float dt);

		//动画显示完后清理数据，准备下一局游戏
		void readyNextGame();

		//设置中奖线条的层级
		void setAllLineZorder(int zorder);
		//设置线条状态
		void setLineState();
		//设置红框的层级
		void setRedFrameZorder(int zorder);
		//设置红框的显示状态
		void setRedFrameState(bool isVisib);
		//设置开始/停止的图片状态
		void setStop();
		void setStart();
		//设置自动/取消的图片状态
		void setAuto();
		void setCancel();

		//显示倍率层
		void showBetLayer();
		//显示游戏名称的动画
		void showGameNameAni();
		//显示开场时的倍率动画
		void showGameBetAni();
		//显示明星倍数的动画
		void showStarBetAni();
		//显示全盘动画
		void showAllGameAni();

		//开始滚动的消息
		void sendGameStartRoll();
		//控制即点即停的计时器
		void setRightAwayStop(float dt);

		//开始和下注图片闪动的动画
		void setPlayStartAndBet();
		//停止开始和下注图片闪动的动画
		void setStopStartAndBet();

		void showShareAward();
		
	public:
		//处理游戏结算后的数据
		virtual void setGameEndData() override;
		//向服务器发送游戏结束的消息
		virtual void sendGameOver() override;
		//发送查看下一页数据的消息
		virtual void sendNextPageReq() override;
		//发送查看上一页数据的消息
		virtual void sendLastPageReq() override;

		//设置按钮状态
		virtual void  setBtnState(bool isvisible) override;
		//设置开始前数据清空
		virtual void setGameStartData() override;
		//设置上分的结果显示
		virtual void setOnResult(int money) override;
		//添加开场动画
		virtual void addStartGameAnimate() override;
		//保存中奖的线条
		virtual void saveWinLine(bool winLine[8]) override;
		//保存游戏最高单线投注额
		virtual void setMaxLineBet(int bet) override;
		//保存开奖图形的数据
		virtual void setImageType(int imageType[9]) override;
		//记录时候有二次奖励
		virtual void setSecondGetMoney(int secondMoney) override;
		virtual int getSecondGetMoney() override;
		//保存玩家输赢分数
		virtual void setWinMoney(int money) override;
		virtual int getWinMoney();
		//保存单机彩金
		virtual void saveSinglePond(LLONG money) override;
		//开始转动
		virtual void setRunCell() override; 
		//处理彩金
		virtual void setWinnings(LLONG allHandsel) override;
		//设置自己的金币
		virtual void setMyMoney(LLONG money) override;
		//设置提示文本
		virtual void setPromptText(const std::string& prompt) override;
		//设置掉线提示
		virtual void setOnConnect() override;
		//离开游戏，处理桌子
		virtual void dealLeaveDesk() override;
		//不能退出游戏的提示语
		void isPopGame();
		//显示广播
		virtual void showRadio(const std::string& str) override;
		//显示大奖界面
		virtual void showCheckPrize(int AllCount[18]) override;
		//显示下一页大奖界面
		virtual void showCheckPrizeNext(UINT AllCount[12]) override;
		//判断游戏是否为全盘
		virtual void isAllGame(bool isAll) override;
		virtual bool getAllGame();
		//判断游戏类型（是否为常规游戏）
		virtual void setGameRule(BYTE rule) override;
		virtual BYTE getGameRule();
		//特殊玩法局数
		virtual void setSpecialRestCount(BYTE count) override;
		//特殊玩法总局数
		virtual void setSpecialCount(BYTE count) override;
		virtual BYTE getSpecialRestCount();
		//特殊玩法时，显示特殊玩法倍数的图片
		virtual void setSpecialRateImage(BYTE rate) override;
		//设置奖励分数
		virtual void setAward(int score) override;
		//保存玩家总筹码
		virtual void setAllHandOff(int handoff) override;
		virtual int getAllHandOff();
		//设置7的个数
		virtual void set7Count(int count) override;
		virtual int get7Count();

		//设置服务端回应的游戏结束
		virtual void setGameOver(bool isOver) override;
		//保存所得的单机彩金
		virtual void setSingleWinnings(LLONG winning) override;
		//保存所得的总彩金
		virtual void setAllWinnings(LLONG winning) override;
		//显示断线进来的彩金
		virtual void setHandsel(LLONG winning, LLONG allwinning) override;

		virtual void setRoomInfo(char szRootName[64], BYTE deskId) override;

		virtual void setShareAward(int iShareAward) override;
	};
}
#endif