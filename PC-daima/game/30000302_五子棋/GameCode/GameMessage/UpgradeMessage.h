#pragma once

#ifndef AFC_SERVER_SHOWHAND_MESSAGE_HEAD_FILE
#define AFC_SERVER_SHOWHAND_MESSAGE_HEAD_FILE

#ifdef VIDEO
#define GAMENAME					TEXT("五子棋视频版")
#define NAME_ID						30000302							///< 名字 ID
#else
#define GAMENAME					TEXT("五子棋")
#define NAME_ID						30000302							///< 名字 ID
#endif

/// 文件名字定义
/// 版本定义
#define GAME_MAX_VER				1									///< 现在最高版本
#define GAME_LESS_VER				1									///< 现在最低版本
#define GAME_CHANGE_VER				0									///< 修改版本

/// 支持类型
#define SUPPER_TYPE					SUP_NORMAL_GAME|SUP_MATCH_GAME|SUP_MONEY_GAME
#define GAME_TABLE_NAME				"WZQ"
/// 游戏信息

#define PLAY_COUNT					2									///< 游戏人数

#define MAIN_VERSION                704									///< 主版本号,?年?月
#define ASS_VERSION                 21									///< 辅助版本号,?号


/// 游戏开发版本
#define DEV_HEIGHT_VERSION				8								///< 内部开发高版本号
#define DEV_LOW_VERSION					8								///< 内部开发低版本号

/// 游戏状态定义
#define GS_WAIT_SETGAME					0								///< 等待东家设置状态
#define GS_WAIT_ARGEE					1								///< 等待同意设置
#define GS_SEND_CARD					20								///< 发牌状态
#define GS_WAIT_BACK					21								///< 等待扣压底牌
#define GS_PLAY_GAME					22								///< 游戏中状态
#define GS_WAIT_NEXT					23								///< 等待下一盘开始 

//#define SKIN_FOLDER						TEXT("wzq")					///< 图片文件夹
//#define SKIN							TEXT("cardskin1")				///< 两套图片中用一套
//#define SKIN_CARD						TEXT("card")					///< 共用图片文件夹

#define GET_STRING(NUM)                 #NUM
#define INT_TO_STR(NUM)                 GET_STRING(NUM)
#define CLIENT_DLL_NAME                 TEXT(INT_TO_STR(NAME_ID)##".ico")        ///<  客户端ico名字
#define SKIN_FOLDER                     TEXT("")//TEXT(INT_TO_STR(NAME_ID))      ///<  客户端目录


#define BOARD_LINE_NUMBER				19								///< 棋盘大小
/********************************************************************************/
#define ALLOW_SYSTEM_AUTO				0								///< 系统托管情况0正常,1机器人,2系统托管
//游戏数据包
/********************************************************************************/

//游戏中使用了的时间信息 jph100127
struct UsedTimeInfo
{
	int m_iJuUseTime[2];
	int	m_iBuUseTime[2];
	int	m_iDuUseTime[2];
	UsedTimeInfo()
	{
		memset(m_iJuUseTime,0,sizeof(m_iJuUseTime));
		memset(m_iBuUseTime,0,sizeof(m_iBuUseTime));
		memset(m_iDuUseTime,0,sizeof(m_iDuUseTime));
	}
};

///指导费数据包
struct GuidanceMoney
{
	__int64		iGuidandeMoney;	
};

/// 游戏状态数据包	（ 等待东家设置状态 ）
struct GameStation_1
{

	/// 游戏信息
	BYTE			iCardCount;											///< 扑克数目
	/// 游戏版本
	BYTE				iVersion;										///< 游戏版本号
	BYTE				iVersion2;										///< 游戏版本号
	int					iRoomBasePoint;									///< 房间倍数
	int					iRunPublish;									///< 逃跑扣分

};

/// 游戏状态数据包	（ 等待其他玩家开始 ）
struct GameStation_2
{
	/// 游戏版本
	BYTE				iVersion;										///< 游戏版本号
	BYTE				iVersion2;										///< 游戏版本号
	int					iRoomBasePoint;									///< 房间倍数
	int					iRunPublish;									///< 逃跑扣分

	int			iJuTimeMinute;											///< 局时分
	int			iJuTimeSecond;											///< 局时秒
	int			iBuTimeMinute;											///< 步时分
	int			iBuTimeSecond;											///< 步时秒
	int			iDuMiaoMinute;											///< 读秒分
	int			iDuMiaoSecond;											///< 读秒秒
	__int64		iGuidandeMoney;											///< 引导费
};

/// 游戏状态数据包	（ 游戏正在发牌状态 ）
/// 游戏状态数据包	（ 等待扣押底牌状态 ）
struct GameStation_3
{
	/// 游戏版本
	BYTE				iVersion;						///< 游戏版本号
	BYTE				iVersion2;						///< 游戏版本号
	int					iRoomBasePoint;					///< 房间倍数
	int					iRunPublish;					///< 逃跑扣分
	/// 游戏信息
	BYTE				iBeginStation;					///< 开始位置
	BYTE				iEndStation;					///< 结束位置
	BYTE				iMeStation;
	BYTE				iOtherStation;
	BYTE				iPlayCount;						///< 游戏盘数
	BYTE				iCardCount;						///< 扑克数目

	/// 运行状态变量
	int					iWinPoint;						///< 游戏积分
	int					iPunishPoint;					///< 用户罚分
	int					iUpGradePeople;					///< 庄家位置
	BYTE				iPlayNTNum[2];					///< 各玩家的主牌数目
	BYTE				iBeenPlayGame;					///< 已经游戏的局数

	/// 反牌信息
	int					iNtPeople;						///< 反牌玩家
	BYTE				iNtHua;							///< 反牌花色
	BYTE				iNtCardCount;					///< 反牌牌数

	/// 状态信息
	BYTE				iUserCardCount;					///< 用户手上扑克数目
	BYTE				iUserCard[45];					///< 用户手上的扑克

};

/// 游戏状态数据包	（ 游戏中状态 ）
struct GameStation_4	
{
	/// 游戏版本
	BYTE				iVersion;						///< 游戏版本号
	BYTE				iVersion2;						///< 游戏版本号
	int					iRoomBasePoint;					///< 房间倍数
	int					iRunPublish;					///< 逃跑扣分
	/// 游戏信息
	int			iJuTimeMinute;							///< 局时分
	int			iJuTimeSecond;							///< 局时秒
	int			iBuTimeMinute;							///< 步时分
	int			iBuTimeSecond;							///< 步时秒
	int			iDuMiaoMinute;							///< 读秒分
	int			iDuMiaoSecond;							///< 读秒秒
	__int64		iGuidandeMoney;							///< 游戏指导费

	BYTE				iPlayCount;						///< 游戏盘数
	BYTE				iBeenPlayGame;					///< 已经游戏的局数
	int					iOutCardPeople;					///< 现在出牌用户
	int					iFirstOutPeople;				///< 先出牌的用户
	int					iQiZi[21][21];
	int					iTiZiNum[2];
	int					iQiZiNum[2];					///< 已下棋子数
	int					iEndI;
	int					iEndJ;
	int                 iUpGradePeople;                 ///< 庄家,先手
	UsedTimeInfo		m_stUsedTimeInfo;					//使用过的时间

	bool				bIsInHuiquStation[2];///< 悔棋状态s
};

/// 游戏状态数据包	（ 等待下盘开始状态  ）
struct GameStation_5
{
	/// 游戏版本
	BYTE				iVersion;						///< 游戏版本号
	BYTE				iVersion2;						///< 游戏版本号
	int					iRoomBasePoint;					///< 房间倍数
	int					iRunPublish;					///< 逃跑扣分
	/// 游戏信息
	BYTE				iBeginStation;					///< 开始位置
	BYTE				iEndStation;					///< 结束位置
	BYTE				iPlayCount;						///< 游戏盘数
	BYTE				iCardCount;						///< 扑克数目

	/// 运行状态变量
	int					iWinPoint;						///< 游戏积分
	int					iPunishPoint;					///< 用户罚分
	int					iUpGradePeople;					///< 庄家位置
	BYTE				iPlayNTNum[2];					///< 各玩家的主牌数目
	BYTE				iBeenPlayGame;					///< 已经游戏的局数
};

/// 用户同意游戏
struct UserArgeeGame
{

	int			iJuTimeMinute;							///< 局时分
	int			iJuTimeSecond;							///< 局时秒
	int			iBuTimeMinute;							///< 步时分
	int			iBuTimeSecond;							///< 步时秒
	int			iDuMiaoMinute;							///< 读秒分
	int			iDuMiaoSecond;							///< 读秒秒
	__int64		iGuidandeMoney;							///< 引导费

	//BYTE				iBeginStation;					///< 开始位置
	//BYTE				iEndStation;					///< 结束位置
	//BYTE				iPlayCount;						///< 游戏盘数
	//BYTE				iCardCount;						///< 扑克数目
};

/// 游戏准备,先手位置,白手位置
struct GameReadyStruct
{
	BYTE				iBlackStation;					///< 先手位置
	BYTE				iWhiteStation;					///< 白手位置
};

/// 游戏开始
struct BeginUpgradeStruct
{
	BYTE				iUpgradeStation;				///< 庄家位置
	BYTE				iPlayCount;						///< 游戏回合
	BYTE				iNtStation;						///< 现在的主牌
	BYTE				iStation[2];					///< 主牌的位置
};

/// 发牌数据包
struct SendCardStruct
{
	BYTE				iCard;							///< 牌标号
};

/// 亮主牌数据包  （发向服务器）
struct ClientNtStruct
{
	BYTE				iHuaKind;						///< 牌标号
	BYTE				iCardCount;						///< 反牌数目
};

/// 亮主牌数据包  （发向客户端）
struct ServerNtStruct
{
	BYTE				bDeskStation;					///< 反牌位置
	BYTE				iHuaKind;						///< 花色
};

/// 底牌数据包
struct BackCardStruct
{
	BYTE				iBackCardCount;					///< 扑克数目
	BYTE				iBackCard[8];					///< 底牌数据
};

/// 底牌数据包
struct BackCardExStruct
{
	BYTE				iNtHua;							///< 主牌花色
	BYTE				iGiveBackPeople;				///< 底牌玩家
	BYTE				iBackCardCount;					///< 扑克数目
	BYTE				iBackCard[8];					///< 底牌数据
};

/// 留底牌状态数据包
struct BackStationStruct
{
	BYTE				iNtPeople;						///< 反牌位置	
	BYTE				iGiveBackStation;				///< 留底位置
};

/// 游戏开始数据包
struct BeginPlayStruct
{
	BYTE				iOutDeskStation;				///< 出牌的位置
	int			iJuTimeMinute;											///< 局时分
	int			iJuTimeSecond;											///< 局时秒
	int			iBuTimeMinute;											///< 步时分
	int			iBuTimeSecond;											///< 步时秒
	int			iDuMiaoMinute;											///< 读秒分
	int			iDuMiaoSecond;											///< 读秒秒
	__int64		iGuidandeMoney;											///< 引导费
};

/// 用户出牌数据包 （发向服务器）
struct OutCardStruct
{
	int					iCardCount;						///< 扑克数目
	BYTE				iCardList[39];					///< 扑克信息
};

/// 用户甩牌失败数据包 （发向客户端）
struct OutShowCardStruct
{
	BYTE				iCardCount;						///< 扑克数目
	BYTE				bDeskStation;					///< 当前出牌者
	BYTE				iResultCount;					///< 结果扑克数目
	BYTE				iCardList[78];					///< 扑克信息
};

/// 用户出牌数据包 （发向客户端）
struct OutCardMsg
{
	int					iNextDeskStation;				///< 下一出牌者
	BYTE				iCardCount;						///< 扑克数目
	BYTE				bDeskStation;					///< 当前出牌者
	BYTE				iCardList[39];					///< 扑克信息
};

/// 用户出牌数据包 （发向客户端）
struct BatchOutCardMsg
{
	BYTE				iCardCount;						///< 扑克数目
	BYTE				iCardList[156];					///< 扑克信息
};

/// 玩家的分数据包
struct GamePointStruct
{
	bool				bAdd;
	int					iPoint;							///< 得分数目
};

/// 游戏结束统计数据包
struct GameEndStruct
{
	int					iGamePoint;						///< 游戏得分
	__int64				iTurePoint[4];					///< 庄家得分
	__int64				iChangeMoney[8];				///< 金币
	BYTE				iUpGradeStation;				///< 庄家位置
	BYTE				iDoublePointEffect;				///< 双倍积分卡的有效性 20081125
	int					iWinNum[2];						///< 比分
};

/// 游戏结束统计数据包
struct GameCutStruct
{
	int					bDeskStation;					///< 退出位置
	__int64					iTurePoint[2];					///< 玩家得分
	__int64					iChangeMoney[8];				///< 金币
	BYTE				iDoublePointEffect;				///< 双倍积分卡的有效性
	char				cNickName[PLAY_COUNT][61];		///玩家姓名
};

struct HaveThingStruct
{
	BYTE pos;
	char szMessage[61];
};

struct LeaveResultStruct
{
	BYTE bDeskStation;
	int bArgeeLeave;
};

/// 客户端到服务器
struct MessageStruct	
{
	char Message[200];
};

struct StopResultStruct
{
	bool bArgee;
};

///棋子数据包（发向客户端）
struct PlayChessMsg
{	
	//int					iStartI;
	//int					iStartJ;
	int					iEndI;
	int					iEndJ;
	int					iPlayFlag;
	int					iTiZiNum[2];					///< 提子数
	int					iChessArray[21][21];
	int					iNextPlayStation;
	int					iQiZiNum[2];
};

/// 檢查是否結束
struct PlayCheckFinish
{
	BOOL bCanFinish;
	int iCurI;
	int iCurJ;
	char cValue;
};
/*
struct DianMu
{
int qi[21][21];
};
*/

/*
struct FinishDianMu
{
int qi[21][21];
char msg[50];
};
*/

/// 悔棋数据包(发向客户端)
struct RegretChessMsg
{
	int		iLastChessArray[21][21];					///< 记录上步棋局
	int		iLastTiZiNum[2];							///< 记录上步提子数
	int		iLastDeskStation;							///< 走棋者的位置
};

/*
struct DianMuResultStruct	//点目
{
bool bAgree;
};
*/

/// 游戏结算
struct GameFinishNotify
{
	int	 iUpGradePeople;
	int iGrade2;
	TCHAR name[4][21];
	//	int	iBasePoint;
	BYTE iStyle;										///< 游戏类型是否为强退,还是正常结束
	__int64 	iWardPoint[4];
	//__int64 iTotalPoint[4];
	//int iAwardPoint[4];		//讨赏
	//	int iGetPoint[4];		//各家抓分
	//	int nt;					//定約
	__int64    iMoney[4];
};

/********************************************************************************/
// 数据包处理辅助标识
/********************************************************************************/

#define ASS_UG_USER_SET					50				///< 用户设置游戏
#define ASS_BEGIN_UPGRADE				51				///< 升级游戏开始
#define ASS_SEND_CARD					52				///< 发牌信息
#define ASS_NT_CARD						53				///< 用户反牌
#define ASS_SEND_FINISH					54				///< 发牌完成
#define ASS_BACK_CARD					55				///< 底牌数据
#define ASS_BACK_CARD_EX				56				///< 底牌数据
#define ASS_BACK_CARD_RES				57				///< 底牌数据结果
#define ASS_WAIT_BACK					58				///< 用户留底牌
#define ASS_GAME_PLAY					59				///< 开始游戏
#define ASS_OUT_CARD					60				///< 用户出牌
#define ASS_OUT_CARD_RESULT				61				///< 出牌结果
#define ASS_CAN_FINISH					62				///< 出牌是否可以结束
#define ASS_GAME_READY					63				///< 游戏准备工作
//#define ASS_SHOW_CARD					61				///< 甩牌失败
//#define ASS_BATCH_OUT					62				///< 批量出牌
//#define ASS_GAME_POINT					63			///< 用户分数
//#define ASS_NEW_TURN					64				///< 新一轮开始
#define ASS_CONTINUE_END				65				///< 游戏结束
#define ASS_NO_CONTINUE_END				66				///< 游戏结束
#define ASS_CUT_END						67				///< 用户强行离开
#define ASS_SALE_END					68				///< 游戏安全结束
#define ASS_HAVE_THING					69
#define ASS_LEFT_RESULT					70
#define ASS_MESSAGE						71
#define ASS_STOP_THING					72
#define ASS_AGREE_STOP					73
#define ASS_SUPER_TIMER					74				///< 超时处理
#define ASS_REN_SHU						75				///< 认输
#define ASS_HUI_QI						76				///< 悔棋
#define ASS_AGREE_HUI_QI				77				///< 同意悔棋
#define ASS_AGREE_HUI_QI_PHONE			78				///< 同意悔棋 手机专用
#define ASS_GET_GAME_USED_TIME			95				//获取使用时间

//#define ASS_DIAN_MU						79			///< 点目
//#define ASS_AGREE_DIAN_MU				80				///< 同意点目
//#define ASS_NUMBER_ZI					81				///< 强制数子
//#define ASS_DIAN_MU_RESULT				82			///< 点目结果处理
#define ASS_LOCK_END					83				///< 有胜负之后锁定棋盘

/********************************************************************************/
#endif
