#ifndef _CHERRY97_MESSAGEHEAD_H_
#define _CHERRY97_MESSAGEHEAD_H_
#include "HNBaseType.h"

namespace Cherry97
{
	#pragma pack(1)
	enum 
	{
		NAME_ID = 31011001,
		PLAY_COUNT = 1,
	};

	//游戏状态定义
	const int  GS_WAIT_SETGAME	=  0;				//等待东家设置状态
	const int  GS_WAIT_ARGEE	=  1;				//等待同意设置
	const int  GS_WAIT_START	=  20;		    	//等待开始
	const int  GS_PLAY_GAME		=  21;				//开始游戏中
	const int  GS_WAIT_NEXT		=  22;			    //等待下一盘开始 

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
		LLONG			i64UserMoney;					//用户的金币数
		LLONG           i64Pond;						//奖池金币
		LLONG           i64SinglePond;                  //单机彩金
		char			szGameRoomName[61];
		BYTE			bDeskIndex;
		int				iShareAward;
		S_C_GameStation()
		{
			memset(this, 0 , sizeof(S_C_GameStation));
		}
	};

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

	struct  C_S_ShareAward{
		int iShareAward;
		C_S_ShareAward(){
			memset(this, 0, sizeof(C_S_ShareAward));
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
		int      iShangFenMoney;   //上分金额
		LLONG    i64UserMoney;     //玩家钱
		S_C_ShangFenResult()
		{
			memset(this,0,sizeof(S_C_ShangFenResult));
		}
	};

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

	//滚动信息
	struct S_C_TypeScroll
	{
		bool                 iAllGame;          //全盘
		bool                 bWinAreaFlag[8];   //哪条线中奖  0-7：分别对应A-H
		bool                 iLogoResult[9];    //特殊奖励图片（7）的位置
		BYTE                 byPlayStly;        //1:代表常规游戏  2:代表2倍奖励  3:代表3倍奖励  4:代表4倍奖励
		BYTE                 bySpecialRestCount;//特殊玩法剩余局数
		BYTE                 byZhongLine;       //中奖线数
		int                  iExtaPay;          //额外奖励
		int                  iGetCaiJin;        //所得彩金
		int                  iZhongCaiJin;      //所得总彩金
		int                  iSecondGetMoney;   //所得二次奖励金额
		int                  iTypeImgid[9];     //图形数据
		int                  bShangFenMoney;    //上分金额
		int                  iWinMoney;         //输赢分数
		int                  iLogoValue;        //特殊奖励图片（7）个数
		LLONG	             iSinglePond;       //单机彩金
		int					 iShareAward;		//分享奖励
		BYTE				bySpecialCount;//特殊玩法总局数
		S_C_TypeScroll()
		{
			memset(this,0,sizeof(S_C_TypeScroll));
		}
	};
	//奖池更新数据包
	struct S_C_Pond 
	{
		bool                  bFlag;              //是否中大奖
		BYTE                  byStation;          //中奖人桌号
		char                  szNickName[61];     //中奖玩家昵称
		LLONG                 i64GetPond;         //中奖金币
		LLONG                 i64Pond;            //奖池金币
		S_C_Pond()
		{
			memset(this,0,sizeof(S_C_Pond));
		}
	};
	//查看大奖数据
	struct S_C_Check_Prize
	{
		int               iAllGameCount[18];     //全盘次数
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
		UINT     iLineGameCount[12];       //单线中奖次数
		S_C_Next_Prize()
		{
			memset(this,0,sizeof(S_C_Next_Prize));
		}
	};
	//结束
	struct C_S_GameEnd
	{
		bool bGameOver;    //游戏结束
	};
	//结束结果
	struct S_C_GameEnd
	{
		bool bGameOver;    //游戏结束
	};

	// 数据包处理辅助标识
	/**********************************************************************/
	const int ASS_VREB_CHECK = 179;				//用户处理
	/**************************服务端——>客户端消息**************************/
	const int S_C_GAME_BEGIN = 51;				//游戏开始

	const int S_C_ROLL_RESULT = 62;				//滚动结果

	const int S_C_UPDATE_POND = 63;			    //更新奖池

	const int S_C_SHANG_FEN = 64;               //上分消息

	const int S_C_CHECK_PRIZE_RESULT = 65;      //查看大奖结果消息

	const int S_C_GAME_OVER = 66;               //游戏结束

	const int S_C_IS_SUPER_USER = 67;           //超端玩家消息

	const int S_C_NEXT_PAGE_RESULT = 68;        //查看大奖下一页结果消息

	const int S_C_SHARE_AWARD_RESULT = 69;
	/**************************客户端——>服务端消息**************************/
	const int ASS_C_XIA_FEN = 55;               //下分消息

	const int C_S_SHANG_FEN = 80;               //上分消息

	const int C_S_CHECK_PRIZE = 81;             //查看大奖

	const int C_S_START_ROLL = 82;              //启动游戏滚动

	const int C_S_GAME_OVER   = 83;             //游戏结束

	const int C_S_SUPER_SET  =  84;             //超端设置消息

	const int C_S_NEXT_PAGE_PRIZE =  85;        //查看下一页中奖情况

	const int C_S_SHARE_AWARD = 86;		    //分享奖励


	#pragma pack()
}
#endif
