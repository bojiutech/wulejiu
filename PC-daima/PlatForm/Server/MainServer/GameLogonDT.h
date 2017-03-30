#pragma once

#ifndef GAME_LOGON_DT_HEAD_FILE
#define GAME_LOGON_DT_HEAD_FILE

#include "MainManage.h"
#include "GameRoomMessage.h"
/********************************************************************************************/

//	数据库通信数据包定义 

/********************************************************************************************/

//用户注册信息
struct DL_GP_I_Register
{
	DataBaseLineHead				DataBaseHead;						//数据包头
	MSG_GP_S_Register				_data;
};

struct DL_GP_O_Register
{
	DataBaseResultLine				ResultHead;							//结果数据包头
	MSG_GP_S_Register				_data;
};

//用户支付
struct DL_GP_I_PAY
{
	DataBaseLineHead				DataBaseHead;						//数据包头
	MSG_GP_S_Pay					param;
};

struct DL_GP_O_PAY
{
	DataBaseResultLine				ResultHead;							//结果数据包头
	MSG_GP_S_Pay					data;
};

//通过用户支付的RMB来领取金币奖励
struct DL_GP_I_GETMONEY_BY_PAY
{
	DataBaseLineHead				DataBaseHead;
	unsigned long					dwUserID;
};

struct DL_GP_O_GETMONEY_BY_PAY
{
	DataBaseResultLine				ResultHead;
	MSG_GP_S_GetMoney_ByPay			data;
};

//登陆服务器登陆信息
struct DL_GP_I_LogonByNameStruct////////按名登陆信息的结构
{
	DataBaseLineHead					DataBaseHead;						//数据包头
	MSG_GP_S_LogonByNameStruct			LogonInfo;							//登陆信息，又封状了一个结构
	char								szAccessIP[16];						//登陆 IP
	int									gsqPs;
	///////////////////////////
	//// 添加防止账户同时登陆
	int ID;//ZID
	///////////////////////////

};

//锁定机器 zxj 2009-11-13
struct DL_GP_LockAccount
{
	DataBaseLineHead				DataBaseHead;
	MSG_GP_S_LockAccount			LockAccount;
};

///绑定手机号码
struct DL_GP_BindMobile
{
	DataBaseLineHead				DataBaseHead;
	MSG_GP_S_BindMobile				data;
};

//设置用户头像
struct DL_GP_SetLogo
{
	DataBaseLineHead				DataBaseHead;
	MSG_GP_S_SET_LOGO				LogoInfo;
};

//登陆服务器登陆信息
struct DL_GP_I_LogonByAccStruct
{
	DataBaseLineHead					DataBaseHead;						//数据包头
	MSG_GP_S_LogonByAccStruct			LogonInfo;							//登陆信息
	char								szAccessIP[16];						//登陆 IP
};

//登陆服务器登陆信息
struct DL_GP_I_LogonByMobileStruct
{
	DataBaseLineHead					DataBaseHead;						//数据包头
	MSG_GP_S_LogonByMobileStruct		LogonInfo;							//登陆信息
	char								szAccessIP[16];						//登陆 IP
};

//登陆服务器登陆信息
struct DL_GP_I_RegisterStruct
{
	DataBaseLineHead					DataBaseHead;						//数据包头
	MSG_GP_S_RegisterStruct				RegisterInfo;						//注册信息
	char								szAccessIP[16];						//登陆 IP
};
//玩家操作
struct GP_User_Opt_Struct
{
	DataBaseLineHead					DataBaseHead;						//数据包头
	MSG_GP_User_Opt_Struct				stUserOpt;							//玩家操作结构
};
//更新游戏列表请求
struct DL_GP_I_UpdateDataListStruct
{
	DataBaseLineHead					DataBaseHead;						//数据包头
	void								* pGameList;						//列表指针	
};

//登陆服务器登陆信息
struct DL_GP_O_LogonResultStruct
{
	DataBaseResultLine					ResultHead;							//结果数据包头
	MSG_GP_R_LogonResult				LogonResult;						//登陆结果
};

//修改写Z登录记录的时机，确保网络卡的时候，不至于导致用户登录不上 2009-4-30 zxj
struct  DL_GP_WriteZRecord
{
	DataBaseLineHead		DataBaseHead;
	long	int				lUserID;
	int						ZID;
};

//锁定机器结果 zxj 2009-11-12
struct MSG_GP_S_LockAccountResult
{
	DataBaseResultLine					ResultHead;							//结果数据包头
	UINT	dwUserID;
	UINT	dwCommanType;			//请求命令类型
	UINT	dwCommanResult;			//请求的结果
};

//绑定手机结果
struct MSG_GP_S_BindMobileResult
{
	DataBaseResultLine					ResultHead;							//结果数据包头
	UINT	dwUserID;
	UINT	dwCommanType;			//请求命令类型
	UINT	dwCommanResult;			//请求的结果
};

//密码房间 add by lxl 2010-10-08
struct DL_GP_I_EnterCrypticRoom
{
	DataBaseLineHead					DataBaseHead;						//数据包头
	UINT                                uRoomID;						// 房间号
	char								szMD5PassWord[50];				// 房间密码
};
struct DL_GP_O_EnterCrypticRoom
{
	DataBaseResultLine					ResultHead;						//数据包头
	int                                nRet;						// 返回值，0表示成功，-1表示失败
	UINT                               uRoomID;						// 房间号
};

struct DL_GP_O_GetContestRoomID
{
	DataBaseResultLine	ResultHead;		//结果数据包头
	UINT				iGameID;		//游戏ID
	int					iRoomID;		//比赛房间ID
	int					iContestID;		//比赛ID
	int                 iConstestNum;   //已报名人数
	int                 iChampionCount; //夺冠次数
	int                 iBestRank;      //最佳名次
	int                 iJoinCount;     //参赛次数
	int                 iEntryFee;      //入场费用
	int                 iRankAward[3];  //前三名奖励信息
	int                 iAwardType[3];  //前三名奖励类型
};

struct DL_GP_I_GetContestRoomID
{
	DataBaseLineHead					DataBaseHead;				//数据包头
	long int							iUserID;					//用户名
	UINT								iGameID;					//游戏ID
	UINT								iUpPeople;					//达到此人数才开赛
	int									iContestID;					//比赛ID
};

//定时赛比赛开始时间
struct DL_GP_I_GetContestBeginTime
{
	DataBaseLineHead					DataBaseHead;
	UINT								iGameID;		//游戏ID
	int									iContestID;		//比赛ID	
};
struct DL_GP_O_GetContestBeginTime
{
	DataBaseResultLine					ResultHead;
	UINT								iGameID;		//游戏ID
	int									iContestID;		//比赛ID	
	COleDateTime						matchBeginTime;	//比赛开始时间
};

//added by JianGuankun 20111108,用户资料修改
struct DL_GP_I_UserInfoStruct
{
	DataBaseLineHead	DataBaseHead;	//数据包头
	MSG_GP_S_UserInfo   UserInfo;		//用户资料数据
};

struct DL_GR_O_UserInfoStruct
{
	DataBaseResultLine	ResultHead;		//结果数据包头
};

struct DL_GP_I_ChPasswordStruct
{
	DataBaseLineHead	DataBaseHead;	//数据包头
	MSG_GP_S_ChPassword ChPwd;		//用户密码的数据
};

struct DL_GP_O_ChPasswordStruct
{
	DataBaseResultLine	ResultHead;	//数据包头
};

/// 检查版本
struct DL_GR_I_CheckVersion_t
{
	DataBaseLineHead					DataBaseHead;						///<数据包头
	UINT								uType;								///<操作类型
};
struct DL_GP_I_ReceiveMoney
{
	DataBaseLineHead					DataBaseHead;						///<数据包头
	int									iUserID;
};

struct DL_GP_O_ReceiveMoney
{
	DataBaseResultLine					ResultHead;						///<数据包头
	TReceiveMoney						date;
};

struct DL_GP_O_CharmExchangeList
{
	DataBaseResultLine					ResultHead;						///<数据包头
	TCharmExchange_Item					date;
};

struct DL_GP_I_CharmExchange
{
	DataBaseLineHead					DataBaseHead;						///<数据包头
	TCharmExchange						date;
};


struct  DL_GP_I_SetFriendType
{
	DataBaseLineHead					DataBaseHead;						///<数据包头
	int									iUserID;
	int									iType;
};

struct DL_GP_O_GetLogonPeopleCount
{
	DataBaseResultLine					ResultHead;							///<数据包头
	ONLINEUSERSCOUNT					logonUsers;
};
struct DL_GP_O_MailGet
{
	DataBaseResultLine					ResultHead;						///<数据包头
	TMailItem							date;
};

struct DL_GP_I_MailUpdate
{
	DataBaseLineHead					DataBaseHead;						///<数据包头
	int									iMsgID;
};

struct DL_GP_I_GetNickNameID
{
	DataBaseLineHead					DataBaseHead;						///<数据包头
	MSG_GP_NickNameID_t					_data;
};

struct DL_GP_O_GetNickNameID
{
	DataBaseResultLine					ResultHead;							///<数据包头
	MSG_GP_NickNameID_t					_data;
};

//added by JianGuankun 2012.7.12 ,请求得到财务数据
struct DL_GP_I_FinanceInfo
{
	DataBaseLineHead		 DataBaseHead;		//数据包头
	TMSG_GP_BankFinanceInfo  _data;				//财务数据
};

struct DL_GP_O_FinanceInfo
{
	DataBaseResultLine		 ResultHead;		//数据包头
	TMSG_GP_BankFinanceInfo  _data;				//财务数据
};

struct DL_GP_I_LastLoginGame
{
	DataBaseLineHead		DataBaseHead;		//数据包头
	int						iUserID;
};

struct DL_GP_O_LastLoginGame
{
	DataBaseResultLine		ResultHead;		//数据包头
	TLoginGameInfo			_data;
};

// 排行榜
struct DL_GP_I_PaiHangBang
{
	DataBaseLineHead				DataBaseHead;							///<数据包头
	MSG_GP_PaiHangBang_In			_param;								
};
struct DL_GP_O_PaiHangBang
{
	DataBaseResultLine				ResultHead;							///<数据包头
	MSG_GP_MoneyPaiHangBang_Result		_data;
};

//执行签到
struct DL_I_HALL_SIGN
{
	DataBaseLineHead					DataBaseHead;						///<数据包头
	long								dwUserID;
};

struct DL_O_HALL_SIGN_CHECK
{
	DataBaseResultLine					ResultHead;							///<数据包头
	MSG_GP_S_SIGN_CHECK_RESULT			_data;
};

struct DL_O_HALL_SIGN_DO
{
	DataBaseResultLine					ResultHead;							///<数据包头
	MSG_GP_S_SIGN_DO_RESULT				_data;
};

//在线奖励
struct DL_I_HALL_ONLINE_AWARD
{
	DataBaseLineHead					DataBaseLineHead;
	long								dwUserID;
};

struct DL_O_HALL_ONLINE_AWARD_CHECK_RESULT
{
	DataBaseResultLine					ResultHead;							///<数据包头
	MSG_GP_S_ONLINE_AWARD_CHECK_RESULT	_result;
};
struct DL_O_HALL_ONLINE_AWARD_DO_RESULT
{
	DataBaseResultLine					ResultHead;							///<数据包头
	MSG_GP_S_ONLINE_AWARD_DO_RESULT	_result;
};
struct DL_I_HALL_BUY_DESK
{
	DataBaseLineHead					DataBaseLineHead;
	MSG_GP_S_BUY_DESK                   _data;
	DL_I_HALL_BUY_DESK()
	{
		memset(this,0,sizeof(DL_I_HALL_BUY_DESK));
	}
};
struct DL_O_HALL_BUY_DESK_RES
{
	DataBaseResultLine					ResultHead;	
	MSG_GP_S_BUY_DESK_RES               _result;
	DL_O_HALL_BUY_DESK_RES()
	{
		memset(this,0,sizeof(DL_O_HALL_BUY_DESK_RES));
	}
};
struct DL_I_HALL_ENTER_VIPDESK
{
	DataBaseLineHead					DataBaseLineHead;
	MSG_GP_S_ENTER_VIPDESK				_data;
	DL_I_HALL_ENTER_VIPDESK()
	{
		memset(this,0,sizeof(DL_I_HALL_ENTER_VIPDESK));
	}
};
struct DL_O_HALL_ENTER_VIPDESK_RES
{
	DataBaseResultLine					ResultHead;	
	MSG_GP_S_ENTER_VIPDESK_RES			_result;
	DL_O_HALL_ENTER_VIPDESK_RES()
	{
		memset(this,0,sizeof(DL_O_HALL_ENTER_VIPDESK_RES));
	}
};
struct DL_I_HALL_VIPDESK_CONFIG
{
	DataBaseLineHead					DataBaseLineHead;
	MSG_GP_S_VIP_DESK_CONFIG				_data;
	DL_I_HALL_VIPDESK_CONFIG()
	{
		memset(this,0,sizeof(DL_I_HALL_VIPDESK_CONFIG));
	}
};
struct DL_O_HALL_VIPDESK_CONFIG_RES
{
	DataBaseResultLine					ResultHead;	
	MSG_GP_S_VIP_DESK_CONFIG_RES			_result;
	DL_O_HALL_VIPDESK_CONFIG_RES()
	{
		memset(this,0,sizeof(DL_O_HALL_VIPDESK_CONFIG_RES));
	}
};
struct DL_I_HALL_MONEY_TO_JEWEL
{
	DataBaseLineHead					DataBaseLineHead;
	MSG_GP_S_MONEY_TO_JEWEL				_data;
	DL_I_HALL_MONEY_TO_JEWEL()
	{
		memset(this,0,sizeof(DL_I_HALL_MONEY_TO_JEWEL));
	}
};
struct DL_O_HALL_MONEY_TO_JEWEL_RES
{
	DataBaseResultLine					ResultHead;	
	MSG_GP_S_MONEY_TO_JEWEL_RES			_result;
	DL_O_HALL_MONEY_TO_JEWEL_RES()
	{
		memset(this,0,sizeof(DL_O_HALL_MONEY_TO_JEWEL_RES));
	}
};

//获得断线房间信息
struct DL_I_HALL_NETCUT
{
	DataBaseLineHead					DataBaseLineHead;
	MSG_GP_S_GET_CUTNETROOMINFO				_data;
	DL_I_HALL_NETCUT()
	{
		memset(this,0,sizeof(DL_I_HALL_NETCUT));
	}
};
struct DL_O_HALL_NETCUT_RES
{
	DataBaseResultLine								ResultHead;	
	MSG_GP_S_GET_CUTNETROOMINFO_RES					_result;
	DL_O_HALL_NETCUT_RES()
	{
		memset(this,0,sizeof(DL_O_HALL_NETCUT_RES));
	}
};

//代理商
struct MSG_GP_SC_Agent
{
	char		szUserName[64];			//发送消息用户的用户名
	int			iOperaType;			//类型 ；  1-查询代理商是否存在;  2-绑定代理商
	char		szAgentName[100];	//代理商名称
};

struct DL_GP_I_Agent
{
	DataBaseLineHead				DataBaseHead;
	MSG_GP_SC_Agent					tAgent;
};

struct DL_GP_O_Agent
{
	DataBaseResultLine				ResultHead;
};
/********************************************************************************************/

//大厅登陆处理标识
#define DTK_GP_LOGON_BY_NAME			1									//通过名字登陆
#define DTK_GP_LOGON_BY_ACC				2									//通过 ACC登陆
#define DTK_GP_LOGON_BY_MOBILE			3									//通过手机登陆
#define DTK_GP_RIGSTER_USER				4									//用户注册处理
#define DTK_GP_UPDATE_LIST				5									//更新游戏列表
#define DTK_GP_UPDATE_STRING			6									//更新限制字符
#define DTK_GP_CHECK_CONNECT			7									//检测断线连接
//#define DTK_GP_GAME_POWER   			9									//用户权限
#define DTK_GP_CHECK_SELLGAMELIST		9									//检验是否发送销售列表
			
#define DTK_GP_ZRECORD					11									//修改写Z登录记录的时机，确保网络卡的时候，不至于导致用户登录不上

#define DTK_GP_GET_ROOM_LIST_PEOCOUNT	8									//pppp
#define	DTK_GP_LOCK_UNLOCK_ACCOUNT		12									//锁定机器或解除锁定
#define DTK_GP_CHECK_ROOM_PASSWD		10									// 进入密码房间
#define	DTK_GP_PASSWD_SUCC              0									//进入密码成功
#define	DTK_GP_PASSWD_ERROR             1									//进入密码错误

//大厅登陆错误代码
#define DTR_GP_ERROR_UNKNOW				0									//未知错误
#define DTR_GP_DATABASE_CUT				1									//数据库断开
#define DTR_GP_LOGON_SUCCESS			10									//登陆成功
#define DTR_GP_USER_NO_FIND				11									//登陆名字错误
#define DTR_GP_USER_PASS_ERROR			12									//用户密码错误
#define DTR_GP_USER_VALIDATA			13									//用户帐号禁用
#define DTR_GP_USER_IP_LIMITED			14									//登陆 IP 禁止
#define DTR_GP_USER_EXIST				15									//用户已经存在
#define DTR_GP_PASS_LIMITED				16									//密码禁止效验
#define DTR_GP_IP_NO_ORDER				17									//不是指定地址 
#define DTR_GP_LIST_SCUESS				18									//更新列表成功
#define DTR_GP_LIST_ERROR				19									//更新列表失败
#define DTR_GP_STRING_SCUESS			20									//更新名字成功
#define DTR_GP_STRING_ERROR				21									//更新名字失败
#define DTR_GP_USERNICK_EXIST			22									//昵称已经存在

#define DTR_GP_GET_ROOM_LIST_PEOCOUNT_SCUESS			23					//ppp
#define DTR_GP_GET_ROOM_LIST_PEOCOUNT_ERROR				24					//ppp
#define DTR_GP_IP_FULL					25									//此IP已满
#define DTR_GP_USER_NAME_BAD			26									//非法字符
/////////////////////////////
///用户已经登陆
#define DTR_GP_USER_LOGONED				28										//用户已经登陆
////////////////////////////
//#define DTK_GP_USER_OPT				27									//好友坏人操作
#define	DTR_GP_ACCOUNT_LOCKED			29									//本帐号锁定了某台机器，反正不是当前正在登录这台
#define	DTR_GP_LOCK_SUCCESS				30									//锁定成功	
#define	DTR_GP_MATHINE_UNLOCK			31									//帐号根本就没锁定某台机器
#define	DTR_GP_UNLOCK_SUCCESS			32									//解锁成功
#define	DTR_GP_CODE_ERROR				33									//机器码不匹配
#define DTK_GR_CHECK_VERSION			34									//检查版本
#define DTK_GP_GET_SELLGAMELIST			35									//获取销售列表

#define DTK_GP_MATHINELOCK				36

#define DTR_GP_ALLO_PARTY				37									//异地登陆

#define DTR_GP_LOCK_VALID				38									//锁机验证

#define DTR_GP_MOBILE_VALID				39									//手机短信验证

#define DTK_GP_UPDATE_USERINFO_BASE			40									//用户基本资料修改
#define DTR_GP_UPDATE_USERINFO_BASE			41									//用户基本资料修改
#define DTK_GP_UPDATE_USERINFO_DETAIL		42									//用户详细资料修改
#define DTR_GP_UPDATE_USERINFO_DETAIL		43									//用户详细资料修改
#define DTK_GP_UPDATE_USERINFO_PWD			44									//用户密码修改
#define DTR_GP_UPDATE_USERINFO_PWD			45									//用户密码修改
#define DTR_GP_UPDATE_USERINFO_ACCEPT		47									//用户详细资料已这被服务器收受
#define DTR_GP_UPDATE_USERINFO_NOTACCEPT	48									//用户详细资料未这被服务器收受
#define DTK_GP_UPDATE_NICKNAMEID			49									//查询某用户的昵称或ID

#define DTK_GP_RECEIVEMONEY					50									//领取金币	

#define DTK_GP_CHARMEXCHANGE_LIST			51									//魅力值兑换
#define DTK_GP_CHARMEXCHANGE				52									//魅力值兑换


#define	DTK_GP_SETFRIENDTYPE				53									//修改用户好友和聊天的授受类型

#define DTK_GP_MAILLIST_GET					54

#define DTK_GP_MAIL_UPDATE					55

#define DTK_GP_LASTLOGINGAME				56									//最近登录游戏

#define DTK_GP_LOGONPEOPLE_GET				57									//获取登录人数

#define DTK_GP_BIND_MOBILE					58									//手机绑定

#define DTK_GP_SET_LOGO						59									//设置用户头像

#define DTK_GP_GET_CONTEST_ROOMID			60									//获取比赛房间ID

#define DTK_GP_REGISTER					61										//用户注册

#define DTK_GP_PAY						62										//用户支付
#define DTK_GP_GETMONEY_BY_PAY			63										//通过支付的 RMB 获取金币奖励
#define DTK_GP_GETMONEY_BY_PAY_CHECK	64										//查询
#define DTK_GP_PAIHANGBANG				65										//排行榜
#define DTK_GP_SIGNIN_CHECK				66										//查询签到
#define DTK_GP_SIGNIN_DO				67										//执行签到

#define DTK_GP_ONLINE_AWARD_CHECK		68										//查询在线奖励
#define DTK_GP_ONLINE_AWARD_DO			69										//领取在线奖励

#define DTK_GP_GET_TIMINGMATCHBEIGNTIME 70										//获取定时赛比赛开始时间
#define DTK_GP_BUY_DESK					71										//购买桌子
#define DTK_GP_ENTER_VIPDESK			72										//进入VIP桌子
#define DTK_GP_VIPDESK_CONFIG			73										//VIP桌子配置
#define DTK_GP_MONEY_TO_JEWEL           74										//金币兑换钻石

#define DTK_GP_AGENT					75										//代理商

#define DTK_GP_NETCUT					120										//获得断线信息
/********************************************************************************************/

#endif