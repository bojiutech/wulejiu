#ifndef _HNRoomForPCMessage_H__
#define _HNRoomForPCMessage_H__

#include "HNComStruct.h"
#include "HNNetProtocol/HNRoomMessage.h"

// 房间信息
#define MDM_GR_GAMEBASEINFO             8
#define ASS_GR_GAMEBASEINFO             0

#pragma pack(1)

enum E_U3D_UserType
{
	E_User_VirtualType_human   = 0,
	E_User_VirtualType_AI      = 1,
	E_User_VirtualType_Virtual = 2,
};

//用户信息结构
struct UserItemStruct
{
	bool							bMatchUser;							// 是否比赛
	UINT							uSortIndex;							// 排列索引
	UINT							uConnection;						// 玩家关系
	INT						        dwLogonTime;						// 登陆时间
	UserInfoStruct					GameUserInfo;						// 用户信息
};

//游戏信息
struct GameInfoEx
{
	GameInfoEx()
	{
		bDeskOnwer = true;												// 是否台主
		bGameStation = 0;												// 游戏状态
		memset(&uisMeUserInfo, 0, sizeof(UserInfoStruct));				// 玩家信息
		memset(uisMeUserInfo.GameUserInfo.nickName, 0, sizeof(uisMeUserInfo.GameUserInfo.nickName));
		memset(uisMeUserInfo.GameUserInfo.szName, 0, sizeof(uisMeUserInfo.GameUserInfo.szName));
		uisMeUserInfo.GameUserInfo.dwUserID = 100001;
		uisMeUserInfo.GameUserInfo.bDeskNO = 3;
		uisMeUserInfo.GameUserInfo.bDeskStation = 1;

		dwGamePower = 0;												//用户权限
		dwMasterPower = 0;												//管理权限
		dwRoomRule = 0;													//设置规则
		pOrderName = NULL;												//等级函数

		//设置参数
		bEnableSound     = true;											//允许声音
		bEnableWatch     = false;											//允许旁观
		bShowUserInfo    = true;											//显示进出
		bEnableBackSound = true;										//背景音乐

		//大厅数据
		sprintf(szProcessName, "%zjh.exe"); //进程名字					
		uDeskPeople = 3;												//游戏人数
		uRoomID = 2;													//房间表示
		dwGameMSVer = 2;												//主版本号
		dwGameLSVer = 0;												//副版本号
		uComType = 1;													//游戏类型
		uNameID = 100600302;											//名字表示
		memset(szGameName, 0, sizeof(szGameName));								//游戏名字
		uLessPoint = 0;													//最少经验值
		memset(szGameRoomName, 0, sizeof(szGameRoomName));
		iBasePoint = 1;
		iLowCount = 0;
		i64Chip = 0;
		i64LowChip = 0;
		iRankNum = 0;
		memset(ArrAwards, 0, sizeof(int) * 180);
	}
	//共享信息
	bool			bDeskOnwer;										//是否台主
	BYTE			bGameStation;									//游戏状态
	UserItemStruct  uisMeUserInfo;									//玩家信息
	UINT			dwGamePower;									//用户权限
	UINT       dwMasterPower;										//管理权限
	UINT       dwRoomRule;											//设置规则
	INT        pOrderName;											//等级函数

	//设置参数
	bool       bEnableSound;									//允许声音
	bool       bEnableWatch;											//允许旁观
	bool       bShowUserInfo;											//显示进出
	bool       bEnableBackSound;										//背景音乐

	//大厅数据
	CHAR       szProcessName[31];										//进程名字
	UINT       uDeskPeople;												//游戏人数
	UINT       uRoomID;													//房间表示
	UINT       dwGameMSVer;												//主版本号
	UINT       dwGameLSVer;												//副版本号
	UINT       uComType;												//游戏类型
	UINT       uNameID;													//名字表示
	char       szGameName[61];											//游戏名字
	UINT       uLessPoint;												//最少经验值 
	int        iBasePoint;
	UINT       uUserType;												//用户类型（0普通玩家，1游客）

	//比赛专用
	int        iLowCount;
	LLONG       i64Chip;
	LLONG       i64LowChip;
	int        iRankNum;
	int        ArrAwards[180];
	char      szGameRoomName[61];										//游戏房间名称
};


// 玩家列表
#define MDM_GR_USERINFO                 10
#define ASS_GR_USERINFOLIST             0

// 玩家状态
#define MDM_GR_USERSTATUS      3
#define ASS_GR_USERSTATUS      2

// 控制信息
#define MDM_GR_CONTROL         4
#define ASS_GR_CONTIRL_CLOSE   2


#pragma pack()

#endif	//_HNRoomForPCMessage__
