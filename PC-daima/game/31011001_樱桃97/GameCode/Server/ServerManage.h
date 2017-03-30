#pragma once

#include "../../../../sdk/include/ServerCommon/GameDesk.h"

//定时器 ID
#define TIME_MY_TIMER				20				//公用定时器，只有这个定时器是实际定时器，其余都是从这个定时器经过判断来的
#define MY_ELAPSE					250				// 定时器间隔
#define TIMER_COUNT					11				// 用到的定时器数目
/*---------------------------------------------------------------------*/
// 下列为游戏中使用到的定时器，由上面的TIME_MY_TIMER计数进行统一处理
#define	TIME_MIN					30				//最小计时器ID
#define	TIME_MAX					50				//最大计时器ID
/*---------------------------------------------------------------------*/

//游戏结束标志定义
#define GF_NORMAL					10				//游戏正常结束
#define GF_SALE						11				//游戏安全结束
/*---------------------------------------------------------------------*/

#define MAX_SEAT_COUNT              180              //房间坐位数量

//奖池控制参数
static int     G_i64Pond=0;                    //房间彩金
static int     G_iAIControlHaveMoney=0;          //奖池
static __int64         m_i64SinglePond[MAX_SEAT_COUNT];                //个人彩金
static unsigned int    m_iCheckPrize[MAX_SEAT_COUNT][18];              //记录查看大奖第一页数据
static unsigned int    m_iLineGameCount[MAX_SEAT_COUNT][12];           //记录查看大奖下一页数据
static CRITICAL_SECTION	cs;

/*---------------------------------------------------------------------*/
//游戏桌类
class CServerGameDesk : public CGameDesk
{
	CRITICAL_SECTION m_csForIPCMessage;

private:	
	int             m_iShangFenMoney;               //每次上多少分

	int				m_iAIWinLuckyAtA1;				//区域1中奖概率
	int				m_iAIWinLuckyAtA2;				//区域2中奖概率
	int				m_iAIWinLuckyAtA3;				//区域3中奖概率
	int				m_iAIWinLuckyAtA4;				//超出区域3中奖概率

	int			    m_iRewardLeve1;					//游戏局数 增加大奖概率
	int			    m_iRewardLeve2;					//游戏局数 增加大奖概率
	int			    m_iRewardLeve3;					//游戏局数 增加大奖概率
	int             m_iRewardLeve4;                 //游戏局数 增加大奖概率

	int             m_iFruitJuShuA1;                //开全水果局数控制区域1
	int             m_iFruitJuShuA2;                //开全水果局数控制区域2
	int             m_iFruitJuShuA3;                //开全水果局数控制区域3
	int             m_iFruitJuShuA4;                //开全水果局数控制区域4
	int             m_iFruitWinLuckyAtA1;           //中全水果概率区域1
	int             m_iFruitWinLuckyAtA2;           //中全水果概率区域2
	int             m_iFruitWinLuckyAtA3;           //中全水果概率区域3
	int             m_iFruitWinLuckyAtA4;           //中全水果概率区域4

	int             m_iAIControlSwitch;             //奖池控制开关
	int             m_iMinCaijinFen;                //总彩金送给玩家最低分数值
	int             m_iMaxCaijinFen;                //总彩金送给玩家的最大分数值
	int             m_iSpeCaijinFen;                //总彩金送给指定玩家分数值
       		
	int             m_iCaiJin[9];//全盘彩金奖励
	int             m_iSecondControl;               //控制二次奖励开关

	bool		    m_bIsPlaying;			        //游戏是否已经开始
	BYTE            m_byReJuShu;                    //单机局数加分：第一次， 加3分 第 二 次也是 加 3分， 第 三 次， 加4分
	int             m_iJuShu;                       //出大奖局数
	int             m_iAllFruits;                   //出全水果局数
private:		/*可配置项*/

	bool			m_bClearPreWin;		            //是否自动清空上轮赢钱数	
	int             m_maxCellBet;                   //最大单线下注数
	int             m_iPercentRoom;                 //房间彩金累积，以玩家输分百分之几
	int             m_iPercentPerson;               //个人彩金，以当前玩家输分百分之几
	int             m_Variety;                      //个人彩金可调部分

	vector  <long>  m_lvSpecifyUserID;              //指定送总彩玩家列表

	vector	<long>	m_lvSuperUserID;	            //超级用户列表
	bool            m_bIsSuccesse;                  //超端设置是否成功
	int             m_bySetSuperImg[9];             //超端设置数据

private:
	bool            m_bAllGame;                     //全盘
	bool            m_bWinLine[8];                  //哪个线可以连起来
	BYTE            m_byPlayStly;                   //1:代表常规游戏  2：代表2倍开奖环节  3：代表3倍开奖环节  4：代表4倍开奖环节
	BYTE            m_bySpecialRestCount;           //特殊玩法剩余局数 
	BYTE			m_bySpecialCount;				//特殊玩法总局数
	BYTE			m_bLineCount;		            //中奖线数
	int             m_iAllCellMoney;				//游戏总加注	
	int             m_ImgType[9];                   //图形排列
	int				m_iAllWinMoney;			        //总体赢钱
	int             m_iCellMoney;		            //单线下注数	
	int             m_iExtaPay;                     //额外奖励
	int             m_iAllJiangTip;                 //所中大奖提示分值
	__int64         m_i64ShangFenMoney;             //玩家上分金额
	__int64         m_i64UserMoney;					//玩家身上原本的金币数	
	__int64         m_i64UserSYMoney;               //玩家上分筹码后的金币数

	int				m_iDoubleProbability;			//两倍的概率(x/1000)
	int				m_iThreeProbability;			//三倍的概率(x/1000)
	int				m_iFourProbability;				//四倍的概率(x/1000)
	
	int             m_ilogoValue;                   //七的个数
	int             m_iGetZhongCai;                 //获得的总彩金金币分值
	int             m_iRewardMoney;                 //彩金奖励金币数
	int             m_iSecondGetMoney;              //二次奖励得到的钱
	int             m_iSecondRewardMoney[9];           //二次奖励金币数  依次是：数字七，木瓜，桔子，蓝BAR,樱桃，铃，黄BAR,西瓜，红BAR

	int             m_iAllGameCount[12];          //全盘次数
	__int64         m_i64AllBet;                  //全部下注
	__int64         m_i64AllWin;                  //赢的总数

	__int64			m_i64SystemWinMoney;			//系统的赢钱统计（仅仅是客户用于查看）

	int             m_iExchangeRateBS;              //兑换比例，从大分转小分
	int             m_iExchangeRateSB;             //兑换比例，从小分转大分
	BYTE            m_byThreeLine[9];             //三连情况
	BYTE            m_byAnyBar;                   //当局出现ANYBAR
	BYTE            m_byFirstCherry;              //一个樱桃
	BYTE            m_bySecondCherry;             //两个樱桃
	bool            m_bAnyBar;                    //全盘任意bar
	bool            m_bAllFruits;                 //全盘水果
	int             m_iGetSinglePond;             //从数据库取得单机彩机
	int				m_shareAward;				  //分享奖励 
public:
	//构造函数
	CServerGameDesk(); 
	//析构函数
	virtual ~CServerGameDesk();

	//重载函数
public:
	//游戏开始
	virtual bool	GameBegin(BYTE bBeginFlag);
	//游戏结束
	virtual bool	GameFinish(BYTE bDeskStation, BYTE bCloseFlag);
	//判断是否正在游戏
	virtual bool	IsPlayGame(BYTE bDeskStation);
	///判断此游戏桌是否开始游戏
	virtual BOOL	IsPlayingByGameStation();
	//游戏数据包处理函数
	virtual bool	HandleNotifyMessage(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser);
	//框架消息处理函数
	virtual bool	HandleFrameMessage(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser);
	//用户离开游戏桌
	virtual BYTE	UserLeftDesk(BYTE bDeskStation, CGameUserInfo * pUserInfo);
	///用户坐到游戏桌
	virtual BYTE	UserSitDesk(MSG_GR_S_UserSit * pUserSit, CGameUserInfo * pUserInfo);
	//用户断线
	virtual bool	UserNetCut(BYTE bDeskStation, CGameUserInfo * pUserInfo);
	//初始化桌子信息
	virtual bool	InitDeskGameStation();
	//获取游戏状态信息
	virtual bool	OnGetGameStation(BYTE bDeskStation, UINT uSocketID, bool bWatchUser);
	//重置游戏状态
	virtual bool	ReSetGameState(BYTE bLastStation);
	//定时器消息
	virtual bool	OnTimer(UINT uTimerID);

	virtual  bool SetRoomPond(bool	bAIWinAndLostAutoCtrl);
	virtual  bool SetRoomPondEx(__int64	iAIWantWinMoney[], int	iAIWinLuckyAt[]);
	virtual  bool SetRoomPondEx(__int64	iReSetAIHaveWinMoney);
	/// 判断
	virtual BOOL Judge();
	/// 胜
	virtual BOOL JudgeWiner();
	/// 输
	virtual BOOL JudgeLoser();

private:
	//玩家上分金额
	void OnHandleShangFen(BYTE byStation,void *pdata,UINT uSize);
	//玩家每次上分的金额
	__int64 GetUserSFMoney(BYTE byStation=0);
	//玩家启动滚动
	void OnHandleStartRoll(BYTE byStation,void * pData, UINT uSize);
	//生成玩法
	void getRandStyle();
	//生成牌
	void getRandImgType();
	//随机产生大奖
	int  GetDaJiangImgTpye();
	//玩家点击查看大奖
	void OnHandleCheckPrize(BYTE byStation,void * pData, UINT uSize);
	//玩家点击查看大奖下一页
	void OnHandleNextPagePrize(BYTE byStation,void * pData, UINT uSize);
	//接受客户端游戏结束
	void OnHandleGameOver(BYTE byStation,void * pData, UINT uSize);
	//接受客户端的超端设置
	void OnHandleSuperSet(BYTE byStation,void * pData, UINT uSize);

	void OnHandleShareAward(BYTE byStation, void* pData, UINT uSize);
	//获取分数
	void ChecKLine();
	//系统奖励
	void GetSystemReward();
	//连起来的线
	void GetWinLine();
	//查询是否中大奖
	bool  CheckGainAward();
	//查询是否出全水果
	bool  CheckGetAllFruits();
	//获取特殊奖励LOGO的个数
	INT getLogoValue(INT imageValue[]);
	//判断是否全盘游戏
	bool isAllGame(INT imageValue[]);
	//获取三连奖励
	INT getLineReward(INT a, INT b, INT c);  

private:
	//开始启动游戏
	void	StartGame();
	//是否超级用户
	bool	IsSuperUser(BYTE byStation);
	//是否是指定送彩金玩家
	bool    IsSpecifyUser(BYTE byStation);
	//获取总彩金
	void    GetZhongCai(BYTE byStation);
	
	//处理函数
private:
	//清空该位置的数据
	void	IniUserData(BYTE byStation);
	//读取静态变量
	BOOL	LoadIni();	
	//根据房间ID加载底注和上限
	BOOL	LoadExtIni(int iRoomID);
	//单机彩金累积
	void    GetSinglePond();
	//统计查看大奖上一页数据
	void    CountPrePageData();
	//统计查看大奖下一页数据
	void    CountNextPageData();

	void saveDeskData(int iDeskId, CString key, CString& value);

	int readDeskData(int iDeskId,CString key, int defaultValue);
};

/******************************************************************************************************/
