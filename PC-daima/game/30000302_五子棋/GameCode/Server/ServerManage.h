#pragma once

#include "StdAfx.h"

#include <fstream>

/// 定时器 ID
#define TIME_SEND_CARD				30				///< 发牌定时器
#define TIME_WAIT_NT				31				///< 等待反牌
#define TIME_GAME_FINISH			32				///< 游戏结束定时器


/// 扑克数目定义
#define PLAY_TWO_CARD				1				///< 两副扑克
#define PLAY_THREE_CARD				2				///< 三副扑克

/// 游戏结束标志定义
#define GF_NORMAL					10				///< 游戏正常结束
#define GF_SAFE						11				///< 游戏安全结束


//////////////////////////////////////////////////////////////////////////
#define WZQ_FLAG_NONE				0
#define WZQ_FLAG_BLACK				1
#define WZQ_FLAG_WHITE				2
//#define WQ_FLAG_SIDE				3

#define WQ_FLAG_BLACK_CROSS			4
#define WQ_FLAG_WHITE_CROSS			5

#define WZQ_MAX_I					19
#define WZQ_MAX_J					19

#define WQ_BLACK_TIE_MU				(3.75)			///< 黑帖目3又3/4子

enum WQ_PLAY_FLAG
{
	WZQ_BLACK_PLAYER = 0,
	WZQ_WHITE_PLAYER = 1
};

#define WZQ_NUMBER 5								///< 5子棋

///////////////////////////////////////////////////////////////////

/******************************************************************************************************/


/// 象棋
#define XQ_FLAG_NONE				0
#define XQ_FLAG_RED					1
#define XQ_FLAG_BLACK				-1

#define XQ_QIZI_NONE				0
#define XQ_CROSS					8

/// 红方
#define XQ_RED_JU					1
#define XQ_RED_MA					2
#define XQ_RED_PAO					3
#define XQ_RED_JIANG				6
#define XQ_RED_SHI					4
#define XQ_RED_XIANG				5
#define XQ_RED_BIN					7

/// 黑方
#define XQ_BLACK_JU					-1
#define XQ_BLACK_MA					-2
#define XQ_BLACK_PAO				-3
#define XQ_BLACK_JIANG				-6
#define XQ_BLACK_SHI				-4
#define XQ_BLACK_XIANG				-5
#define XQ_BLACK_BIN				-7

#define XQ_MAX_I					(10)
#define XQ_MAX_J					(9)

/******************************************************************************************************/
/******************************************************************************************************/

/*
//逻辑类 //服务器端用这个
class CUpGradeGameLogic
{
	//变量定义
private:
	
	//函数定义
public:
	//构造函数
	CUpGradeGameLogic(void);
	

	//功能函数（公共函数）
public:

	void NumQiZi(float *totalBlack, float *totalWhite, int qi[][21]);
	
private:
		
	int GetEmptyFlag(int pi,int pj,int qi[][21]);
	
};
*/

//*****************************************************************************************

/// 游戏桌类
class CServerGameDesk : public CGameDesk
{
protected:
	/// 游戏基础数据
	BYTE					m_CardCount;						///< 扑克数目（位变量）

	/// 玩家设置数据
	BYTE					m_iLessCount;						///< 最少游戏局数
	BYTE					m_iPlayCardCount;					///< 游戏扑克数目
	BYTE					m_iBeginStation;					///< 游戏开始位置
	BYTE					m_iEndStation;						///< 游戏结束位置
	BYTE					m_iEnableWatch;						///< 是否允许旁观

	int						m_iJuTimeMinute,					///< 局时
							m_iJuTimeSecond,
							m_iBuTimeMinute,					///< 步时
							m_iBuTimeSecond,
							m_iDuMiaoMinute,					///< 读秒
							m_iDuMiaoSecond;
	__int64					m_iGuidandeMoney;					///< 指导费

	/// 运行状态变量
	int						m_PunishPoint[4];					///< 用户罚分
	int						m_iUpGradePeople;					///< 庄家位置
	BYTE					m_iBeenPlayGame;					///< 已经游戏的局数
	BYTE					m_iLeaveArgee;						///< 离开同意标志

	/// 运行信息
	int						m_iGamePoint;						///< 用户游戏分数
	int						m_iOutCardPeople;					///< 现在出牌用户
	int						m_iFirstOutPeople;					///< 先出牌的用户

	//CUpGradeGameLogic		m_Logic;							///< 游戏逻辑
	bool					m_bQueryQuit;						///< 有玩家请求退出

	int						m_iWinFlag;							///< 获胜方
	int						m_iTurePoint[2];					///< 真实得分
	int						m_iWinNum[2];						///< 两家赢的次数，即比分

	bool					m_bFirstRed;
	bool					m_bQiuHe;
	
	int						m_iBoard[19][19];
	int						m_idianmu[19][19];
	int						m_iQiZiNum[2];						///< 统计黑白两方的下的棋子数（用于提子）
	int						m_iQiZiLastNum[2];					///< 上手双方棋子数
	int						m_iTiZiNum[2];

	/// 悔棋数据
	int						m_iLastDeskStation;					///< 上步走棋者的位置
	int						m_iLastBoard[19][19];				///< 上步棋局
	int						m_iLastTiZiNum[2];					///< 上步提子数
	int						m_Endi;								///< 上一步下子位置
	int						m_Endj;								///< 上一步下子位置
	int						m_iBlackStation;					///< 先手位置
	int						m_iWhiteStation;					///< 白手位置

	int						m_iFinishNumCnt;					///< 完成点目
	int						m_iDianMuResult;					///< 点目结果处理
	CString					m_dianmumsg;

	bool                    m_bUserNetCut[PLAY_COUNT];  //用户断线
	UsedTimeInfo			m_stUsedTimeInfo;//已经使用的时间信息
	
	/*
	 以下变量设置为了防止一方网速较慢时，悔棋出错；
	 所做处理：若网速较慢的一方先提出悔棋请求，但对方先下子，则在服务器端直接取消其悔棋请求;
	 Data:   2008.07.17
	*/
	int                     m_playerChessNum[2];				///< 玩家双方所下的棋子数
	bool					m_bIsInHuiquStation[2];				///< 是否处于悔棋状态

	/// 函数定义
public:
	/// 构造函数
	CServerGameDesk(); 
	/// 析构函数
	virtual ~CServerGameDesk();

	/// 重载函数
public:
	/// 游戏开始
	virtual bool GameBegin(BYTE bBeginFlag);
	/// 游戏结束
	virtual bool GameFinish(BYTE bDeskStation, BYTE bCloseFlag);
	/// 判断是否正在游戏
	virtual bool IsPlayGame(BYTE bDeskStation);
	/// 游戏数据包处理函数
	virtual bool HandleNotifyMessage(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser);
	/// 用户离开游戏桌
	virtual BYTE UserLeftDesk(BYTE bDeskStation, CGameUserInfo * pUserInfo);
	//玩家断线处理
	virtual bool UserNetCut(BYTE bDeskStation, CGameUserInfo * pLostUserInfo);
	//用户重新进入游戏
	virtual  bool UserReCome(BYTE bDeskStation, CGameUserInfo * pLostUserInfo);

	/// 重载纯虚函数
public:
	/// 获取游戏状态信息
	virtual bool OnGetGameStation(BYTE bDeskStation, UINT uSocketID, bool bWatchUser);
	/// 重置游戏状态
	virtual bool ReSetGameState(BYTE bLastStation);
	/// 定时器消息
	virtual bool OnTimer(UINT uTimerID);
	/// 处理函数
public:
	/// 用户设置游戏
	BOOL UserSetGame(UserArgeeGame * pGameSet,BYTE desk);
	/// 游戏准备工作
	BOOL GameReady();
	/// 游戏开始
	BOOL BeginPlayUpGrade();	
	/// 用户出牌
	bool UserOutCard(BYTE bDeskStation, int iPlayQi[][21], int chessColor, int iEndI, int iEndJ);
	/// 新加函数
	BOOL UserOutCard(BYTE bDeskStation,int iPlayer,int iEndI,int iEndJ);
	/// 下面的函数在用户悔棋时会出现BUG
	/// 用户出牌新功能函数
	BOOL UserOutCard(BYTE bDeskStation,int iEndI,int iEndJ);
	/// 能否结束(下子者自己检测)
	BOOL CanFinish(BYTE PutStoneDeskStation,BOOL bCanFinish = false);
	/// 服務端來統計是否結束
	BOOL IsFinish(int iEndI,int iEndJ,int Value);
	/// 新一轮开始
	BOOL NewPlayTurn(int iWiner);
	/// 用户请求离开
	bool UserHaveThing(BYTE bDeskStation, char * szMessage);
	/// 同意用户离开
	bool ArgeeUserLeft(BYTE bDeskStation, BOOL bArgee);
	/// 计算结果
	int	GetUpGrade(int iPlayCardCount);
	/// 强制数子
	void ForceNumberZi(int &iWinFlag, CString &strMessage);
	/// 算子
	int Judge(int nX, int nY, char cValue);
	/// 游戏结束
	int CountWinPiont();
	/// 房间倍数
	int GetRoomBasePoint();
	/// 桌子倍数
	int GetDeskBasePoint();
	/// 人头倍数
	int GetHumanBasePoint();
	/// 逃跑扣分
	int GetRunPublish();
	//修改奖池数据1(平台->游戏)
	/// @param bAIWinAndLostAutoCtrl 机器人控制输赢开关
	/// @return 是否成功
	virtual bool SetRoomPond(bool	bAIWinAndLostAutoCtrl);

	//修改奖池数据2(平台->游戏)
	/// @param m_iAIWantWinMoney 机器人输赢控制：机器人赢钱区域1,2,3 4所用断点
	/// @param m_iAIWinLuckyAt 机器人输赢控制：机器人在区域1,2,3,4赢钱的概率
	/// @return 是否成功
	virtual bool SetRoomPondEx(__int64	iAIWantWinMoney[], int	iAIWinLuckyAt[]);

	//修改奖池数据3(平台->游戏)
	/// @param iReSetAIHaveWinMoney 机器人输赢控制：重置机器人已经赢钱的数目
	/// @return 是否成功
	virtual bool SetRoomPondEx(__int64	iReSetAIHaveWinMoney);

	//控制胜负
	/// 判断
	virtual BOOL Judge();
	/// 胜
	virtual BOOL JudgeWiner();
	/// 输
	virtual BOOL JudgeLoser();
	//GRM函数
	//更新奖池数据(游戏->平台)
	/// @return 机器人赢钱数
	virtual void UpDataRoomPond(__int64 iAIHaveWinMoney);
};

/******************************************************************************************************/
