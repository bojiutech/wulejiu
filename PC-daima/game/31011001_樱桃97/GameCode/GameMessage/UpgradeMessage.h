#pragma once

#ifndef AFC_SERVER_SHOWHAND_MESSAGE_HEAD_FILE
#define AFC_SERVER_SHOWHAND_MESSAGE_HEAD_FILE

//文件名字定义
#define GAMENAME						TEXT("樱桃97")
#define GAME_DLL_AUTHOR                 TEXT("深圳红鸟网络科技")            //
#define GAME_DLL_NOTE                   TEXT("休闲类 -- 游戏组件")


#define NAME_ID							31011001						//名字 ID
#define KIND_ID							3				                // 名字 ID

//版本定义
#define GAME_MAX_VER					1								//现在最高版本
#define GAME_LESS_VER					1								//现在最低版本
#define GAME_CHANGE_VER					0								//修改版本

//支持类型
#define SUPPER_TYPE						SUP_NORMAL_GAME|SUP_MATCH_GAME|SUP_MONEY_GAME
//游戏信息

#define PLAY_COUNT						1								//游戏人数

//游戏内部开发版本号
#define DEV_HEIGHT_VERSION				3				//内部开发高版本号(每修正一次LOW_VERSIONG+1)
#define DEV_LOW_VERSION					1				//内部开发低版本号

//#define SKIN_FOLDER					TEXT("ddz")	//图片文件夹
//#define SKIN							TEXT("cardskin1")	//两套图片中用一套
#define SKIN_CARD						TEXT("cardskin")		//共用图片文件夹
static TCHAR szTempStr[MAX_PATH] = {0};//暂存字符串，用来获取 dll_name 等的时候使用
#define GET_CLIENT_DLL_NAME(A)			(sprintf(A,"%d",NAME_ID),strcat(A,".ico"))
#define GET_SERVER_DLL_NAME(A)			(sprintf(A,"%d",NAME_ID),strcat(A,".dll"))
#define GET_SKIN_FOLDER(A)              (sprintf(A,"%d",NAME_ID),strcat(A,""))     //获取图片文件夹
#define GET_KEY_NAME(A, B, C, D)		(sprintf(A,"%s%d%s", B, C, D),strcat(A,""))
#define GET_CLIENT_BCF_NAME(A)          (sprintf(A,"%d",NAME_ID),strcat(A,".bcf"))    

#define SUPER_PLAYER                    10                         //超级玩家
#define MAX_NAME_INFO                   256

//游戏状态定义
#define GS_WAIT_SETGAME					0				//等待东家设置状态
#define GS_WAIT_ARGEE					1				//等待同意设置

#define GS_WAIT_START                   20              //等待开始
#define GS_PLAY_GAME					21				//开始游戏中
#define GS_WAIT_NEXT					22				//等待下一盘开始 

/********************************************************************************/
//游戏数据包

/********************************************************************************/
/*-------------------------------------------------------------------------------*/

#pragma pack(1)

///超端数据包
struct	S_C_TagSuperUser
{	
	BYTE		byStation;			///位置
	bool        bIsSuper;           /**< 是否开通 */

	S_C_TagSuperUser()
	{
		byStation = -1;
		bIsSuper = false;
	}
};

//超端设置数据包
struct	C_S_TagSuperSet
{	
	bool		bSuccesse;			//设置是否成功
	int		    bySetSuperImg[9];	

	C_S_TagSuperSet()
	{
		memset(this,0,sizeof(C_S_TagSuperSet));
		bSuccesse = false;
	}
	void	init()
	{
		memset(this,0,sizeof(C_S_TagSuperSet));
		bSuccesse = false;
	}
};

//游戏状态基础数据包
struct  S_C_GameStation
{
	BYTE			byGameStation;					//游戏状态
	int             iExchangeRateBS;				//兑换比例，从大分转小分
	int             iExchangeRateSB;				//兑换比例，从小分转大分
	int				iCellBet;						//最高单线投注额
	__int64			i64UserMoney;					//用户的金币数
	__int64         i64Pond;						//奖池金币
	__int64         i64SinglePond;                    //单机彩金
	char			szGameRoomName[61];
	BYTE			bDeskIndex;							///< 桌子号码
	S_C_GameStation()
	{
		memset(this, 0 , sizeof(S_C_GameStation));
	}
};
/*-------------------------------------------------------------------------------*/

//游戏开始数据包
struct S_C_GameBegin
{
	bool	bStart;
	BYTE    byGameStation;
	S_C_GameBegin()
	{
		memset(this, 0 , sizeof(S_C_GameBegin));
	}
};

struct C_S_ShareAward{
	int iShareAward;
	C_S_ShareAward(){
		memset(this,0,sizeof(C_S_ShareAward));
	}
};

struct S_C_ShareAwardResult{
	int iShangFenMoney;
	S_C_ShareAwardResult(){
		memset(this, 0, sizeof(S_C_ShareAwardResult));
	}
};

//上分
struct C_S_ShangFen
{
	bool  bIsShangFen;      //1：上分   0：下分
	C_S_ShangFen()
	{
		memset(this,0,sizeof(C_S_ShangFen));
	}
};

//上分结果
struct S_C_ShangFenResult
{
	int        iShangFenMoney;   //上分金额
	__int64    i64UserMoney;     //玩家钱
	S_C_ShangFenResult()
	{
		memset(this,0,sizeof(S_C_ShangFenResult));
	}
};

/*-------------------------------------------------------------------------------*/
//开始滚动
struct C_S_StartRoll
{
	//当前单线分数
	INT         byDeposit;
	//投注线数
	BYTE        byLines;
	C_S_StartRoll()
	{
		memset(this,-1,sizeof(C_S_StartRoll));

	}
};

/*-------------------------------------------------------------------------------*/
//滚动信息
struct S_C_TypeScroll
{  
	bool                           bAllGame;              //全盘
	bool                           bWinAreaFlag[8];       //哪条线中奖  0-7：分别对应A-H
	bool                           iLogoResult[9];        //特殊奖励图片7 的位置
	BYTE                           byPlayStly;            //0:代表常规游戏  1：代表2倍开奖环节  2：代表3倍开奖环节  3：代表4倍开奖环节
	BYTE                           bySpecialRestCount;    //特殊玩法剩余局数 
	BYTE                           byZhongLine;           //中奖线数
	int                            iExtaPay;              //额外奖励
	int                            iGetCaiJin;            //所得彩金
	int                            iZhongCaiJin;          //所得总彩金
	int                            iSecondGetMoney;       //所得二次奖励金额
	int                            iTypeImgid[9];         //图形数据
	int                            iShangFenMoney;        //上分金额
	int                            iWinMoney;             //输赢分数
	int                            iLogoValue;            //特殊奖励图片(7)个数     
	__int64                        iSinglePond;           //单机彩机
	int							   iShareAward;			  //分享奖励
	BYTE						   bySpecialtCount;		  //特殊玩法的总局数

	S_C_TypeScroll()
	{
		memset(this,0,sizeof(S_C_TypeScroll));
	}
};
//奖池更新数据包
struct S_C_Pond
{
	bool    bFlag;             //是否中大奖
	BYTE    byStation;         //中奖人桌号     
	char    szNickName[61];    //谁

	__int64 i64GetPond;        //所中金币
	__int64 i64Pond;           //奖池金币
	
	S_C_Pond()
	{
		memset(this,0,sizeof(S_C_Pond));
	}
};

//查看大奖数据
struct S_C_Check_Prize
{
	unsigned int      iAllGameCount[18];          //全盘次数
// 	int               iFlashDian;                 //闪点
// 	__int64           i64AllBet;                  //全部下注
// 	__int64           i64AllWin;                  //赢的总数

	S_C_Check_Prize()
	{
		memset(this,0,sizeof(S_C_Check_Prize));
	}
};

//查看下一页中奖数据
struct C_S_Next_Prize
{
	bool          bFlag;                    //true为查看
	C_S_Next_Prize()
	{
		bFlag = false;
	}
};

//查看下一页中奖数据
struct S_C_Next_Prize
{
	unsigned int     iLineGameCount[12];       //单线中奖次数
	S_C_Next_Prize()
	{
		memset(this,0,sizeof(S_C_Next_Prize));
	}
};

//结束
struct C_S_GameEnd
{
	bool       bGameOver;      //游戏结束
};
//结束结果
struct S_C_GameEnd
{
	bool       bGameOver;      //游戏结束
};

#pragma pack()
/********************************************************************************/

// 数据包处理辅助标识

/**********************************************************************/
#define ASS_VREB_CHECK					179				//用户处理
/**************************服务端——>客户端消息**************************/


#define S_C_GAME_BEGIN					51				//游戏开始

#define S_C_ROLL_RESULT					62				//滚动结果

#define	S_C_UPDATE_POND					63				//更新奖池

#define S_C_SHANG_FEN                   64              //上分消息

#define S_C_CHECK_PRIZE_RESULT          65              //查看大奖结果消息

#define S_C_GAME_OVER                   66              // 游戏结束

#define S_C_IS_SUPER_USER               67              //超端玩家消息

#define S_C_NEXT_PAGE_RESULT            68              //查看大奖下一页结果消息

#define S_C_SHARE_AWARD_RESULT			69			    //分享奖励结果
/**************************客户端——>服务端消息**************************/
#define ASS_C_XIA_FEN                     55               //下分消息

#define C_S_SHANG_FEN                     80               //上分消息
                  
#define C_S_CHECK_PRIZE                   81               //查看大奖

#define C_S_START_ROLL                    82              //启动游戏滚动

#define C_S_GAME_OVER                     83              //游戏结束

#define C_S_SUPER_SET                     84              //超端设置消息

#define C_S_NEXT_PAGE_PRIZE               85              //查看下一页中奖情况

#define C_S_SHARE_AWARD					  86			  //分享奖励
/**********************************************************************/
#endif
