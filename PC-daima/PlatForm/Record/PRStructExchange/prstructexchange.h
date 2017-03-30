#pragma once

#include "../include/struct.h"
#include "comstruct.h"
#include "../../Client/UILibrary2003/ClientComStruct.h"
//#include "GameUserManage.h"

#define MAX_PLAYER_COUNT   180   //����а˸����

class CPRStructExchange
{
public:
	CPRStructExchange(void);
	~CPRStructExchange(void);
	//*************************���ú���*************************/
	/**
	* ¼�������ݽṹת��Ϊ����
	* 
	*/	
	//�ͻ��˺ͷ��������ú���
	/**
	* ת��user�ṹ ��ƽ̨�ṹת��Ϊ¼��ṹ
	*/
	bool ChangeUsrInfoPlat2Re(RecordUserInfoStruct* DestUser,const UserInfoStruct* sourceUser);
	//**************************������ר�ú���************************/

	bool ChangeUserIterPlayToReSrv(RecordUserItemStruct* destitem,UserInfoStruct* sourceUser,BYTE bMyDeskStation);
    
	bool ChangeGameRoomPlatToReSrv(RecordGameInfoStruct* destgameinfo,ManageInfoStruct* sourcmange,BYTE bMyDeskStation);
	//**************************�ͻ���ר�ú���************************/
	bool ChaneUserItemPlatToReClient(RecordUserItemStruct* destitem,const UserItemStruct* souceitem);
	bool ChangeGameRoomPlatToReClient(RecordGameInfoStruct* destgameinfo,GameInfoStruct* sourcegameinfo,TCHAR* szClienDllName,BYTE bMyDeskStation);
	
	//***************************�������ú���*************************************/
	//
	bool ChaneUserItemReToPlatClient(UserItemStruct* destitem,RecordUserItemStruct* souceitem);
	bool ChangeGameRoomReToPlatClient(GameInfoStruct* destgameinfo,RecordGameInfoStruct* sourcegameinfo);
	bool ChangeUsrInfoRe2Plat(UserInfoStruct* DestUser,RecordUserInfoStruct* sourceUser);
	
	//void CleanAllUser() {m_UserManage.CleanUserInfo();}
	//CGameUserManage* GetUserManage() {return &m_UserManage;}

private:
	UINT GetUserSortIndex(UserInfoStruct * pUserItem,BYTE bMyDeskStation);




	//CGameUserManage		m_UserManage;
	

};
