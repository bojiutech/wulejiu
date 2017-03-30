#include "StdAfx.h"
#include "PRStructExchange.h"


//����λ��
#define SK_ENEMY_USER						0								//������������
#define SK_NORMAL_USER						1								//�����������

#define SK_NORMAL_MEMBER					2								//��ͨ��Ա����
#define SK_HIGHT_MEMBER	                    3								//�߼���Ա����
#define SK_SPECIAL_MEMBER					4								//�����α�����
#define SK_FOREVER_MEMBER					5								//���û�Ա����
#define SK_SENIOR_MEMBER					6								//Ԫ���������

#define SK_FRIEND_USER						7								//������������
#define SK_MASTER_USER						8								//������������
#define SK_ME_USER							9								//�Լ���������
#define SK_ALWAYS_USER						10								//�̶���������


#define CM_NORMAL							0								//��ͨ��ϵ




//��������


CPRStructExchange::CPRStructExchange(void)
{

}

CPRStructExchange::~CPRStructExchange(void)
{
}
bool CPRStructExchange::ChangeUsrInfoRe2Plat(UserInfoStruct* DestUser,RecordUserInfoStruct* sourceUser)
{

	if (DestUser == NULL || sourceUser == NULL)
	{
		return false;
	}
	DestUser->bBoy = sourceUser->bBoy;
	DestUser->bDeskNO = sourceUser->bDeskNO;
	DestUser->bDeskStation = sourceUser->bDeskStation;
	DestUser->bGameMaster = sourceUser->bGameMaster;
	DestUser->bLogoID = sourceUser->bLogoID;
	DestUser->bMember = sourceUser->bMember;
	//DestUser->bSayHello = sourceUser->bSayHello;
	DestUser->bUserState = sourceUser->bUserState;
	//DestUser->bUserType = sourceUser->bUserType;
	DestUser->dwAccID = sourceUser->dwAccID;
	DestUser->dwExperience = sourceUser->dwExperience;
	//DestUser->dwMobileNum = sourceUser->dwMobileNum;
	DestUser->i64Money = sourceUser->dwMoney;
	DestUser->dwPoint = sourceUser->dwPoint;
	DestUser->i64Bank = sourceUser->dwBank;   //����
	//DestUser->dwReputation = sourceUser->dwReputation;
	//DestUser->dwScore = sourceUser->dwScore;
	DestUser->dwUserID = sourceUser->dwUserID;
	DestUser->dwUserIP = sourceUser->dwUserIP;
//	DestUser->iAgencyID = sourceUser->iAgencyID;
	UINT uNicksize = sizeof(DestUser->nickName) > sizeof(sourceUser->nickName) ? sizeof(sourceUser->nickName) : sizeof(DestUser->nickName);
	memcpy(DestUser->nickName,sourceUser->nickName,uNicksize);

	uNicksize = sizeof(DestUser->szName) > sizeof(sourceUser->szName) ? sizeof(sourceUser->szName) : sizeof(DestUser->szName);
	memcpy(DestUser->szName,sourceUser->szName,uNicksize);

	uNicksize = sizeof(DestUser->szClassName) > sizeof(sourceUser->szClassName) ? sizeof(sourceUser->szClassName) : sizeof(DestUser->szClassName);
	memcpy(DestUser->szClassName,sourceUser->szClassName,uNicksize);

	DestUser->uDeskBasePoint = sourceUser->uDeskBasePoint;
	DestUser->dwFascination = sourceUser->dwFascination;
	DestUser->iVipTime = sourceUser->iVipTime;
	DestUser->iProtectTime = sourceUser->iVipTime;
	DestUser->iDoublePointTime = sourceUser->iDoublePointTime;
	DestUser->iProtectTime = sourceUser->iProtectTime;

	DestUser->uCutCount = sourceUser->uCutCount;
	DestUser->uLostCount = sourceUser->uLostCount;
	DestUser->uMidCount = sourceUser->uMidCount;
	DestUser->uWinCount = sourceUser->uWinCount;
	return true;
}
bool CPRStructExchange::ChangeUsrInfoPlat2Re(RecordUserInfoStruct* DestUser,const UserInfoStruct* sourceUser)
{
	if (DestUser == NULL || sourceUser == NULL)
	{
		return false;
	}
	DestUser->bBoy = sourceUser->bBoy;
	DestUser->bDeskNO = sourceUser->bDeskNO;
	DestUser->bDeskStation = sourceUser->bDeskStation;
	DestUser->bGameMaster = sourceUser->bGameMaster;
	DestUser->bLogoID = sourceUser->bLogoID;
	DestUser->bMember = sourceUser->bMember;
	DestUser->bSayHello = false;
	DestUser->bUserState = sourceUser->bUserState;
	DestUser->bUserType = 0;
	DestUser->dwAccID = sourceUser->dwAccID;
	DestUser->dwExperience = sourceUser->dwExperience;
	DestUser->dwMobileNum = 0;
	DestUser->dwMoney = sourceUser->i64Money;
	DestUser->dwPoint = sourceUser->dwPoint;
	DestUser->dwReputation = 0;
	DestUser->dwScore = 0;
	DestUser->dwUserID = sourceUser->dwUserID;
	DestUser->dwUserIP = sourceUser->dwUserIP;
	DestUser->iAgencyID = 0;
	UINT uNicksize = sizeof(DestUser->nickName) > sizeof(sourceUser->nickName) ? sizeof(sourceUser->nickName) : sizeof(DestUser->nickName);
	memcpy(DestUser->nickName,sourceUser->nickName,uNicksize);

	uNicksize = sizeof(DestUser->szName) > sizeof(sourceUser->szName) ? sizeof(sourceUser->szName) : sizeof(DestUser->szName);
	memcpy(DestUser->szName,sourceUser->szName,uNicksize);
	DestUser->uCutCount = sourceUser->uCutCount;
	DestUser->uLostCount = sourceUser->uLostCount;
	DestUser->uMidCount = sourceUser->uMidCount;
	DestUser->uWinCount = sourceUser->uWinCount;

	uNicksize = sizeof(DestUser->szClassName) > sizeof(sourceUser->szClassName) ? sizeof(sourceUser->szClassName) : sizeof(DestUser->szClassName);
	memcpy(DestUser->szClassName,sourceUser->szClassName,uNicksize);

	//Ϊ��ƽ̨û�е����ݸ�ֵ
	DestUser->dwBank = sourceUser->i64Bank;	
	DestUser->uDeskBasePoint = sourceUser->uDeskBasePoint;
	DestUser->dwFascination = sourceUser->dwFascination;
	DestUser->iVipTime = sourceUser->iVipTime;
	DestUser->iDoublePointTime = sourceUser->iDoublePointTime;
	DestUser->iProtectTime = sourceUser->iProtectTime;
	return true;
}
//**************************������ר�ú���************************/
bool CPRStructExchange::ChangeUserIterPlayToReSrv(RecordUserItemStruct* destitem,UserInfoStruct* sourceUser,BYTE bMyDeskStation)
{
	if (bMyDeskStation > MAX_PLAYER_COUNT)
	{
		return false;
	}
	if (destitem == NULL || sourceUser == NULL)
	{
		return false;
	}
	bool bRet = ChangeUsrInfoPlat2Re(&destitem->GameUserInfo,sourceUser);
	if (!bRet)
	{
		return bRet;
	}
	destitem->bMatchUser = false; //�����ֱ����û��ͷǱ����û�
	destitem->uSortIndex = GetUserSortIndex(sourceUser,bMyDeskStation);
	destitem->uConnection = CM_NORMAL;     	//��ͨ��ϵ
	return true;



}

bool CPRStructExchange::ChangeGameRoomPlatToReSrv(RecordGameInfoStruct* destgameinfo,ManageInfoStruct* sourcmange,BYTE bMyDeskStation)
{
	if (destgameinfo == NULL ||  sourcmange == NULL)
	{
		return false;
	}
	if (bMyDeskStation >= MAX_PLAYER_COUNT)
	{
		return false;
	}
	destgameinfo->bDeskOnwer = false;
	destgameinfo->bEnableBackSound = false; //�����ű�������
	destgameinfo->bEnableSound = true;   //����Ҫ������
	destgameinfo->bEnableWatch = false; //�������Թ�
	destgameinfo->bGameStation = 0;
	destgameinfo->bMeDeskStation = bMyDeskStation;
	destgameinfo->bShowUserInfo = true;
	destgameinfo->dwGameLSVer = 0; //���������ֵģ�����֤�汾��
	destgameinfo->dwGameMSVer = 0;
	destgameinfo->dwGamePower = 0;
	destgameinfo->dwMasterPower = 0;
	destgameinfo->dwRoomRule = 0;
	destgameinfo->iRoomSelcet = 0;  //����

	//UINT uNicksize = sizeof(destgameinfo->szClientDLLName) > sizeof(sourcmange->szClientDLLName) ? sizeof(sourcmange->szClientDLLName) : sizeof(destgameinfo->szClientDLLName);
	//memcpy(destgameinfo->szClientDLLName,sourcmange->szClientDLLName,uNicksize);
	
	//uNicksize = sizeof(destgameinfo->szGameName) > sizeof(sourcmange->szGameRoomName) ? sizeof(sourcmange->szGameRoomName) : sizeof(destgameinfo->szGameName);
	//memcpy(destgameinfo->szGameName,sourcmange->szGameRoomName,uNicksize);
	//
	//uNicksize = sizeof(destgameinfo->szKindName) > sizeof(sourcmange->szGameRoomName) ? sizeof(sourcmange->szGameRoomName) : sizeof(destgameinfo->szKindName);
	//memcpy(destgameinfo->szKindName,sourcmange->szGameRoomName,uNicksize);

	//uNicksize = sizeof(destgameinfo->szRoomName) > sizeof(sourcmange->szGameRoomName) ? sizeof(sourcmange->szGameRoomName) : sizeof(destgameinfo->szRoomName);
	//memcpy(destgameinfo->szRoomName,sourcmange->szGameRoomName,uNicksize);

	destgameinfo->uComType = sourcmange->uComType;
//	destgameinfo->uDeskPeople = sourcmange->uDeskPeople;
	destgameinfo->uDiMoney = sourcmange->uBasePoint;
	destgameinfo->uLessPoint = 0;
//	destgameinfo->uNameID = sourcmange->uNameID;
	destgameinfo->uRoomID = sourcmange->uRoomID;
	
//	destgameinfo->uTaiMoney = sourcmange->uTai;//̨��//GetTaiShu(sourcmange->uBasePoint);  //����
//	destgameinfo->uKindId = sourcmange->uKindId;
	
	

	
	

}
//**************************�ͻ���ר�ú���************************/
bool CPRStructExchange::ChaneUserItemReToPlatClient(UserItemStruct* destitem,RecordUserItemStruct* souceitem)
{
	if (destitem == NULL || souceitem == NULL)
	{
		return false;
	}
	bool bRet = ChangeUsrInfoRe2Plat(&destitem->GameUserInfo,&souceitem->GameUserInfo);
    if (!bRet)
    {
		return bRet;
    }
	destitem->bMatchUser = souceitem->bMatchUser;
	destitem->dwLogonTime = souceitem->dwLogonTime;
	destitem->uConnection = souceitem->uConnection;
	destitem->uSortIndex = souceitem->uSortIndex;
	//m_UserManage.AddGameUser(destitem->GameUserInfo,destitem->uSortIndex,destitem->uConnection);
	return true;

}
bool CPRStructExchange::ChaneUserItemPlatToReClient(RecordUserItemStruct* destitem,const UserItemStruct* souceitem)
{
	if (destitem == NULL || souceitem == NULL)
	{
		return false;
	}
	bool bRet = ChangeUsrInfoPlat2Re(&destitem->GameUserInfo,&souceitem->GameUserInfo);
	if (!bRet)
	{
		return bRet;
	}
	destitem->bMatchUser = souceitem->bMatchUser;
	destitem->dwLogonTime = souceitem->dwLogonTime;
	destitem->uConnection = souceitem->uConnection;
	destitem->uSortIndex = souceitem->uSortIndex;

	return true;

}


bool CPRStructExchange::ChangeGameRoomReToPlatClient(GameInfoStruct* destgameinfo,RecordGameInfoStruct* sourcegameinfo)
{
	if (destgameinfo == NULL || sourcegameinfo == NULL)
	{
		return false;
	}
	destgameinfo->bDeskOnwer = sourcegameinfo->bDeskOnwer;
	destgameinfo->bEnableSound = sourcegameinfo->bEnableSound;
	destgameinfo->bEnableWatch = sourcegameinfo->bEnableWatch;
	destgameinfo->bGameStation = sourcegameinfo->bGameStation;
	destgameinfo->bShowUserInfo = sourcegameinfo->bShowUserInfo;
	destgameinfo->dwGameLSVer = sourcegameinfo->dwGameLSVer;
	destgameinfo->dwGameMSVer = sourcegameinfo->dwGameMSVer;
	destgameinfo->dwGamePower = sourcegameinfo->dwGamePower;
	destgameinfo->dwMasterPower = sourcegameinfo->dwMasterPower;
	destgameinfo->dwRoomRule = sourcegameinfo->dwRoomRule;
	//destgameinfo->iRoomSelcet = sourcegameinfo->iRoomSelcet;
	destgameinfo->pIFindUser = NULL;
	destgameinfo->pISocketSend = NULL;
	destgameinfo->pMeUserInfo = NULL;
	destgameinfo->pOrderName = NULL;
//	destgameinfo->uKindId = sourcegameinfo->uKindId;

	UINT uNicksize = sizeof(destgameinfo->szGameName) > sizeof(sourcegameinfo->szGameName) ? sizeof(sourcegameinfo->szGameName) : sizeof(destgameinfo->szGameName);
	memcpy(destgameinfo->szGameName,sourcegameinfo->szGameName,uNicksize);

	//uNicksize = sizeof(destgameinfo->szKindName) > sizeof(sourcegameinfo->szKindName) ? sizeof(sourcegameinfo->szKindName) : sizeof(destgameinfo->szKindName);

	//memcpy(destgameinfo->szKindName,sourcegameinfo->szKindName,uNicksize);

//	uNicksize = sizeof(destgameinfo->szRoomName) > sizeof(sourcegameinfo->szRoomName) ? sizeof(sourcegameinfo->szRoomName) : sizeof(destgameinfo->szRoomName);
//	memcpy(destgameinfo->szRoomName,sourcegameinfo->szRoomName,uNicksize);

	destgameinfo->uComType = sourcegameinfo->uComType;
	destgameinfo->uDeskPeople = sourcegameinfo->uDeskPeople;
//	destgameinfo->uDiMoney = sourcegameinfo->uDiMoney;
	destgameinfo->uLessPoint = sourcegameinfo->uLessPoint;
	destgameinfo->uNameID = sourcegameinfo->uNameID;
	destgameinfo->uRoomID = sourcegameinfo->uRoomID;
	//destgameinfo->uTaiMoney = 0;
	return true;

}

bool CPRStructExchange::ChangeGameRoomPlatToReClient(RecordGameInfoStruct* destgameinfo,GameInfoStruct* sourcegameinfo,TCHAR* szClienDllName,BYTE bMyDeskStation)
{
	if (destgameinfo == NULL || sourcegameinfo == NULL)
	{
		return false;
	}
	//if (lstrlen(szClienDllName) == 0)
	//{
	//	return false;
	//}
	//if (bMyDeskStation > MAX_PLAYER_COUNT)
	//{
	//	return false;
	//}
	strcpy(destgameinfo->szClientDLLName,szClienDllName);
	destgameinfo->bMeDeskStation = bMyDeskStation;
	
	
	destgameinfo->bDeskOnwer = sourcegameinfo->bDeskOnwer;
	destgameinfo->bEnableSound = sourcegameinfo->bEnableSound;
	destgameinfo->bEnableWatch = sourcegameinfo->bEnableWatch;
	destgameinfo->bGameStation = sourcegameinfo->bGameStation;
	destgameinfo->bShowUserInfo = sourcegameinfo->bShowUserInfo;
	destgameinfo->dwGameLSVer = sourcegameinfo->dwGameLSVer;
	destgameinfo->dwGameMSVer = sourcegameinfo->dwGameMSVer;
	destgameinfo->dwGamePower = sourcegameinfo->dwGamePower;
	destgameinfo->dwMasterPower = sourcegameinfo->dwMasterPower;
	destgameinfo->dwRoomRule = sourcegameinfo->dwRoomRule;
//	destgameinfo->iRoomSelcet = sourcegameinfo->iRoomSelcet;


	UINT uNicksize = sizeof(destgameinfo->szGameName) > sizeof(sourcegameinfo->szGameName) ? sizeof(sourcegameinfo->szGameName) : sizeof(destgameinfo->szGameName);
	memcpy(destgameinfo->szGameName,sourcegameinfo->szGameName,uNicksize);

	//uNicksize = sizeof(destgameinfo->szKindName) > sizeof(sourcegameinfo->szKindName) ? sizeof(sourcegameinfo->szKindName) : sizeof(destgameinfo->szKindName);

	//memcpy(destgameinfo->szKindName,sourcegameinfo->szKindName,uNicksize);

	//uNicksize = sizeof(destgameinfo->szRoomName) > sizeof(sourcegameinfo->szRoomName) ? sizeof(sourcegameinfo->szRoomName) : sizeof(destgameinfo->szRoomName);
	//memcpy(destgameinfo->szRoomName,sourcegameinfo->szRoomName,uNicksize);

	destgameinfo->uComType = sourcegameinfo->uComType;
	destgameinfo->uDeskPeople = sourcegameinfo->uDeskPeople;
//	destgameinfo->uDiMoney = sourcegameinfo->uDiMoney;
	destgameinfo->uLessPoint = sourcegameinfo->uLessPoint;
	destgameinfo->uNameID = sourcegameinfo->uNameID;
	destgameinfo->uRoomID = sourcegameinfo->uRoomID;
//	destgameinfo->uTaiMoney = sourcegameinfo->uTaiMoney;

	destgameinfo->bEnableBackSound = false;
	return true;

}
UINT CPRStructExchange::GetUserSortIndex(UserInfoStruct * pUserItem,BYTE bMyDeskStation)
{
	if (pUserItem->bDeskStation == bMyDeskStation) return SK_ME_USER;
	if (pUserItem->bGameMaster !=0 ) return SK_MASTER_USER;
	if (pUserItem->bMember == 1) return SK_NORMAL_MEMBER;
	if (pUserItem->bMember == 2) return SK_HIGHT_MEMBER;
	if (pUserItem->bMember == 3) return SK_HIGHT_MEMBER;	                   
	if (pUserItem->bMember == 4) return SK_SPECIAL_MEMBER;				
	if (pUserItem->bMember == 5) return SK_FOREVER_MEMBER;					
	if (pUserItem->bMember == 6) return SK_SENIOR_MEMBER;
	return SK_NORMAL_USER;
}
