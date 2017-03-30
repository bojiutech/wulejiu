/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #include "StdAfx.h"
#include "ServerManage.h"
#include <shlobj.h>
#include "DebugPrintf.h"

/*------------------------------------------------------------------------------*/
/**
* ���캯��	DWJ
*/
CServerGameDesk::CServerGameDesk(void):CGameDesk(FULL_BEGIN)
{	
	m_uSocketID		= 0;
	m_byGameStation	= GS_WAIT_ARGEE;
	m_byAgreeLeaveNum = 0;//ͬ�������Ϸ���������
	

    sCPGAction.SetDeskPoint(this);	//�����ܼ�ⷽ��(��ȡ����ָ��)

    sCheckHuPai.SetDeskPoint(this);	//���Ƽ�ⷽ��(��ȡ����ָ��)

    m_sThingHandle.SetDeskPoint(this);//�¼�����(��ȡ����ָ��)

}
/*------------------------------------------------------------------------------*/
/**
* ��������
*/
CServerGameDesk::~CServerGameDesk(void)
{
}
/*------------------------------------------------------------------------------*/
/**
* ��ʱ����Ϣ
* @param [in] uTimerID ��ʱ��ID
* @return ���ز�������
*/
bool CServerGameDesk::OnTimer(UINT uTimerID)
{
	if (m_byGameStation >= GS_SEND_CARD && m_byGameStation < GS_WAIT_NEXT)
	{
		m_sThingHandle.OnGameTimer(uTimerID);
	}
	return __super::OnTimer(uTimerID);
}

void CServerGameDesk::KillAllTimer()
{
	KillTimer(TIME_WAIT_MSG);
	KillTimer(TIME_CHECK_GAME_MSG);
	KillTimer(THING_GAME_BEGIN);
	KillTimer(THING_DING_NT);
	KillTimer(THING_TURN_2SEZI_NT);
	KillTimer(THING_BEGIN_OUT);
	KillTimer(THING_SEND_PAI);
	KillTimer(THING_OUT_PAI);
	KillTimer(THING_ZHUA_PAI);
	KillTimer(THING_ENG_HANDLE);
}

/*------------------------------------------------------------------------------*/
/**
* ��ȡ��Ϸ״̬��Ϣ
* @param [in] bDeskStation ���λ��
* @param [in] uSoketID Socket ID
* @param [in] bWatchUser �Թ�
* @return ���ز�������
*/
bool CServerGameDesk::OnGetGameStation(BYTE bDeskStation, UINT uSocketID, bool bWatchUser)
{
	//�����������ʱ��socket
	m_uSocketID = uSocketID;
	//����
	m_RoomId = m_pDataManage->m_InitData.uRoomID;
	
	m_sThingHandle.GetGameStaton(bDeskStation, uSocketID, bWatchUser, m_byGameStation);	

	if (m_bIsBuy) {
		//����ʣ�������Ϣ
		LastRounds lastRoundMsg;
		lastRoundMsg.iLastRounds = m_iVipGameCount - m_iRunGameCount;
		for (int i = 0; i < PLAY_COUNT; i++) {
			SendGameData(i, &lastRoundMsg, sizeof(lastRoundMsg), MDM_GM_GAME_NOTIFY, THING_LAST_ROUNDS, 0);
		}
	}
	return true;
}
/*-------------------------------------------------------------------------------------------------*/
/**
* �����Ϸ���ݰ�������
* @param [in] bDeskStation ���λ��
* @param [in] pNetHead ��Ϣͷ
* @param [in] pData ��Ϣ��
* @param [in] uSize ��Ϣ���Ĵ�С
* @param [in] uSoketID Socket ID
* @param [in] bWatchUser �Թ�
* @return ���ز�������
*/
bool CServerGameDesk::HandleFrameMessage(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser)
{
	if (bDeskStation>=PLAY_COUNT)
	{
		return true;
	}
	ASSERT(pNetHead->bMainID==MDM_GM_GAME_FRAME);
	switch (pNetHead->bAssistantID)
	{
	case ASS_GM_FORCE_QUIT:
	{
		//����ǿ���й� ��ô����ǿ�˽�����Ϸ
		if (sGameData.m_mjRule.bForceTuoGuan)
		{
			return true;
		}
		else
		{
			GameFinish(bDeskStation, GFF_FORCE_FINISH);//ǿ�˽�����Ϸ
		}
		break;
	}
	default:
	{
		break;
	}
	}
	return __super::HandleFrameMessage(bDeskStation,pNetHead,pData,uSize,uSocketID,bWatchUser);
}
/*-------------------------------------------------------------------------------------------------*/
/**
* ��Ϸ���ݰ�������
* @param [in] bDeskStation ���λ��
* @param [in] pNetHead ��Ϣͷ
* @param [in] pData ��Ϣ��
* @param [in] uSize ��Ϣ���Ĵ�С
* @param [in] uSoketID Socket ID
* @param [in] bWatchUser �Թ�
* @return ���ز�������
*/
bool CServerGameDesk::HandleNotifyMessage(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser)
{
	KillTimer(TIME_CHECK_GAME_MSG);
	SetTimer(TIME_CHECK_GAME_MSG,TIME_DEFAULT_HANDLE);//�������ó�ʱ��ʱ��

	switch (pNetHead->bAssistantID)
	{
	case ASS_GM_AGREE_GAME:		//�û�ͬ����Ϸ
		{
			if (bWatchUser)
			{
				return FALSE;
			}
			if(NULL != m_pUserInfo[bDeskStation])
			{
				m_pUserInfo[bDeskStation]->m_UserData.bUserState = USER_ARGEE;  //�����Ϊͬ��״̬
			}
			return __super::HandleNotifyMessage(bDeskStation,pNetHead,pData,uSize,uSocketID,bWatchUser);
		}
	}
	if(pNetHead->bMainID == MDM_GM_GAME_NOTIFY)//������Ϸ��Ϣ
	{
		m_sThingHandle.HandleNotifyMessage(bDeskStation,pNetHead->bAssistantID,(BYTE*)pData,uSize,bWatchUser);
	}
	if(pNetHead->bMainID == 180)
	{
		return true;
	}
	return __super::HandleNotifyMessage(bDeskStation,pNetHead,pData,uSize,uSocketID,bWatchUser);
}

/**
* ������Ϸ״̬
* @param [in] bLastStation ��Ϸ������־
* @return ���ز�������
*/
bool	CServerGameDesk::ReSetGameState(BYTE bLastStation)
{
	return TRUE;
}
/*-------------------------------------------------------------------------------------------------*/
/**
* ��ʼ����Ϸ
* @return ���ز�������
*/
bool	CServerGameDesk::InitDeskGameStation()
{
	CString s = CINIFile::GetAppPath ();/////����·��
	CINIFile f(s + SKIN_FOLDER  + _T("_s.ini"));

	CString key;
	key = TEXT("game");
	m_iBase = f.GetKeyVal(key,"BaseMoney",10); //�׷�����
	m_iFanBase = f.GetKeyVal(key,"FanBase",1);

	key = TEXT("SuperSet");
	int iCount = f.GetKeyVal(key,"SuperCount",0);
	long int iSuperId = 0;
	CString sText;

	for(int i=0; i<iCount; i++)
	{
		sText.Format("SuperID_%d",i);
		iSuperId = f.GetKeyVal(key,sText,0);
		m_vlSuperUserID.push_back(iSuperId);
	}

	//���ط�������
	LoadiniByRoom(m_pDataManage->m_InitData.uRoomID);
	return true;
}
/*-------------------------------------------------------------------------------------------------*/
/**
* ��Ϸ��ʼ
* @param [in] bBeginFlasg ��ʼģʽ��־
*/
bool	CServerGameDesk::GameBegin(BYTE bBeginFlag)
{
	DebugPrintf("-----------------��Ϸ��ʼ-----------------");
	if (__super::GameBegin(bBeginFlag) == false) 
	{
		GameFinish(0,GF_SALE);
		return false;
	}
	m_byGameStation = GS_SEND_CARD;
    sGameData.ApplyThingID = THING_GAME_BEGIN;
	//sGameData.T_TingPai.byAnGangCard = 255;
    //�����¼�
    m_sThingHandle.ApplyAction(THING_GAME_BEGIN,200);
	return true;
}
/*-------------------------------------------------------------------------------------------------*/
/**
* ��Ϸ����
* @param [in] bDeskStation ���λ��
* @param [in] bCloseFlag ��Ϸ������־
* @return ���ز�������
*/
bool CServerGameDesk::GameFinish(BYTE bDeskStation, BYTE bCloseFlag)
{
	KillAllTimer();

	switch (bCloseFlag)
	{
	case GF_NORMAL:		//��Ϸ��������
	{
		DebugPrintf("-----------------��Ϸ����-----------------");
			m_byGameStation = GS_WAIT_NEXT;			
    		//����ʤ������
			for (int i = 0;i < PLAY_COUNT; i ++)
			{
				if (m_pUserInfo[i] != NULL) 
				{
					m_pUserInfo[i]->m_UserData.bUserState = USER_SITTING;
				}
			}

			__int64   i_ChangePoint[PLAY_COUNT];     //����
			__int64   i_ChangeMoney[PLAY_COUNT];     //���
			__int64   i_ReturnMoney[PLAY_COUNT];     //���ؽ��			

			memset(i_ChangePoint, 0, sizeof(i_ChangePoint));
			memset(i_ChangeMoney, 0, sizeof(i_ChangeMoney));
			memset(i_ReturnMoney, 0, sizeof(i_ReturnMoney));

			// ������д�����ݿ�
			bool temp_cut[PLAY_COUNT];
			memset(temp_cut, 0, sizeof(temp_cut));
	
			for(int i=0;i<PLAY_COUNT;++i)
			{
				i_ChangePoint[i] = sGameData.T_CountFen.iZongFen[i];
			}

			// ������Ӯ��˰
			ChangeUserPointint64(i_ChangePoint, temp_cut);
			__super::RecoderGameInfo(i_ChangeMoney);

			//��˰���õĽ��
			for(int i=0;i<PLAY_COUNT;++i)
			{
				sGameData.T_CountFen.i64Money[i] = i_ChangeMoney[i];
				//ʣ�����
				//m_pUserInfo[i]->m_UserData.i64Money += i_ChangeMoney[i];
				//��¼�������
				m_calculateMsg.i64WinMoney[i] += i_ChangeMoney[i];
			}

			sGameData.T_CountFen.bIsShowTax = sGameData.m_bShowTax;//�Ƿ���ʾ�����
			sGameData.T_CountFen.iBasePoint = m_pDataManage->m_InitData.uBasePoint;//����

			sGameData.T_CountFen.byCloseFlag = bCloseFlag;

			//��������
			for (int i=0; i<PLAY_COUNT; i++)
			{
				SendGameData(i, &sGameData.T_CountFen, sizeof(sGameData.T_CountFen), MDM_GM_GAME_NOTIFY, THING_ENG_HANDLE, 0);   
				SendWatchDataEx(i, &sGameData.T_CountFen, sizeof(sGameData.T_CountFen), MDM_GM_GAME_NOTIFY, THING_ENG_HANDLE, 0); 
			}

			if (m_bIsBuy) {
				//����ʣ�������Ϣ
				LastRounds lastRoundMsg;
				lastRoundMsg.iLastRounds = m_iVipGameCount - m_iRunGameCount - 1;
				for (int i = 0; i < PLAY_COUNT; i++) {
					SendGameData(i, &lastRoundMsg, sizeof(lastRoundMsg), MDM_GM_GAME_NOTIFY, THING_LAST_ROUNDS, 0);
				}
				//���ʹ������Ϣ
				if (m_iRunGameCount + 1 >= m_iVipGameCount) {
					BYTE byCount = 0;
					m_calculateMsg.bBestFire = 255;
					for (int i = 0; i < PLAY_COUNT; i++) {
						if (m_calculateMsg.iDianPao[i] > byCount) {
							m_calculateMsg.bBestFire = i;
							byCount = m_calculateMsg.iDianPao[i];
						}
					}

					m_calculateMsg.bWinner = 255;
					byCount = 0;
					for (int i = 0; i < PLAY_COUNT; i++) {
						if (m_calculateMsg.i64WinMoney[i] > byCount) {
							m_calculateMsg.bWinner = i;
							byCount = m_calculateMsg.i64WinMoney[i];
						}
					}

					for (int i = 0; i < PLAY_COUNT; i++) {
						SendGameData(i, &m_calculateMsg, sizeof(m_calculateMsg), MDM_GM_GAME_NOTIFY, THING_CALCULATE_BOARD, 0);
					}

					m_calculateMsg.init();
				}
			}

			bCloseFlag = GF_NORMAL;
			ReSetGameState(bCloseFlag);
			__super::GameFinish(bDeskStation,bCloseFlag);
			return true;
		}
	case GFF_SAFE_FINISH:
		{
			if(bDeskStation==255)
			{
				bDeskStation=0;
			}
			m_byGameStation = GS_WAIT_ARGEE;

			int iBasePoint = m_pDataManage->m_InitData.uBasePoint;//����
			for (int i=0; i<m_bMaxPeople; i++)
			{
				if (m_pUserInfo[i] != NULL) 
					m_pUserInfo[i]->m_UserData.bUserState = USER_SITTING;
			}				
			bCloseFlag	= GFF_FORCE_FINISH;

			//д�����ݿ�				
			__int64 i_ChangePoint[PLAY_COUNT];
			__int64 iWinMoney[8] ={0};
			bool temp_cut[PLAY_COUNT];
			memset(i_ChangePoint,0,sizeof(i_ChangePoint));
			memset(temp_cut,0,sizeof(temp_cut));
	
			ChangeUserPointint64(i_ChangePoint, temp_cut);
			__super::RecoderGameInfo(iWinMoney);
			for (int i=0;i<PLAY_COUNT;i++)
			{
				sGameData.T_CountFen.i64Money[i] = iWinMoney[i]; 
			}
			sGameData.T_CountFen.bIsShowTax = sGameData.m_bShowTax;//�Ƿ���ʾ�����
			
			///������������
			sUserData.CopyHandPai(sGameData.T_CountFen.m_byArHandPai,0,true);
			sGameData.T_CountFen.byCloseFlag = bCloseFlag;
			///��������
			for (int i=0; i<PLAY_COUNT; i++)     
			{
				SendGameData(i, &sGameData.T_CountFen, sizeof(sGameData.T_CountFen), MDM_GM_GAME_NOTIFY, THING_ENG_UN_NORMAL, 0);   
				SendWatchDataEx(i, &sGameData.T_CountFen, sizeof(sGameData.T_CountFen), MDM_GM_GAME_NOTIFY, THING_ENG_UN_NORMAL, 0);
			}
			break;
		}
	case GFF_FORCE_FINISH:
		{
			// Ϊ��������û��뿪������ӵĴ���
			// �жϸ�����Ƿ�ѹ��ע���Ƿ�ׯ��
			if(bDeskStation==255 || m_byGameStation == GS_WAIT_ARGEE || m_byGameStation == GS_WAIT_NEXT)
			{
				return true;
			}
			m_byGameStation = GS_WAIT_ARGEE;//GS_WAIT_SETGAME;
			for (int i = 0; i < PLAY_COUNT; i ++)
			{
				if (m_pUserInfo[i] != NULL) 
					m_pUserInfo[i]->m_UserData.bUserState = USER_SITTING;
			}

			bCloseFlag	= GFF_FORCE_FINISH;
			//int iBasePoint = m_pDataManage->m_InitData.uBasePoint;//����

			//д�����ݿ�				
			__int64 i_ChangePoint[PLAY_COUNT]={0};
			__int64 iWinMoney[8] ={0};
			bool temp_cut[PLAY_COUNT] = {0};
			//���Ի�����
			i_ChangePoint[bDeskStation] = -(__int64)m_pDataManage->m_InitData.uRunPublish;
			temp_cut[bDeskStation] = true;

			ChangeUserPointint64(i_ChangePoint, temp_cut);
			__super::RecoderGameInfo(iWinMoney);
			for (int i=0;i<PLAY_COUNT;i++)
			{
				sGameData.T_CountFen.i64Money[i] = iWinMoney[i]; 
			}
			sGameData.T_CountFen.bIsShowTax = sGameData.m_bShowTax;//�Ƿ���ʾ�����



			///������������
			sUserData.CopyHandPai(sGameData.T_CountFen.m_byArHandPai,0,true);
			sGameData.T_CountFen.byCloseFlag = bCloseFlag;

			///��������
			for (int i=0; i<PLAY_COUNT; i++)     
			{
				SendGameData(i, &sGameData.T_CountFen, sizeof(sGameData.T_CountFen), MDM_GM_GAME_NOTIFY, THING_ENG_UN_NORMAL, 0);   
				SendWatchDataEx(i, &sGameData.T_CountFen, sizeof(sGameData.T_CountFen), MDM_GM_GAME_NOTIFY, THING_ENG_UN_NORMAL, 0);
			}
			ReSetGameState(bCloseFlag);
			__super::GameFinish(bDeskStation,bCloseFlag);
			return true;
		}
	case GFF_DISSMISS_FINISH:
	{
		if (bDeskStation == 255 || m_byGameStation == GS_WAIT_ARGEE || m_byGameStation == GS_WAIT_NEXT)
		{
			return true;
		}
		m_byGameStation = GS_WAIT_ARGEE;
		for (int i = 0; i < PLAY_COUNT; i++)
		{
			if (m_pUserInfo[i] != NULL)
				m_pUserInfo[i]->m_UserData.bUserState = USER_LOOK_STATE;
		}

		//д�����ݿ�				
		__int64 i_ChangePoint[PLAY_COUNT] = { 0 };
		__int64 iWinMoney[8] = { 0 };
		bool temp_cut[PLAY_COUNT] = { 0 };
		//���Ի�����
		i_ChangePoint[bDeskStation] = -(__int64)m_pDataManage->m_InitData.uRunPublish;
		temp_cut[bDeskStation] = true;

		ChangeUserPointint64(i_ChangePoint, temp_cut);
		__super::RecoderGameInfo(iWinMoney);
		 
		break;
	}
	default:
		{
			break;
		}
	}


	// ��������
	ReSetGameState(bCloseFlag);
	return __super::GameFinish(bDeskStation,bCloseFlag);
}
/*-----------------------------------------------------------------------------------*/
/**
* �ж��Ƿ�������Ϸ
* @param [in] bDeskStation ���λ��
* @return ���ص�ǰ��Ϸ״̬
*/
bool	CServerGameDesk::IsPlayGame(BYTE bDeskStation)
{
	if(m_byGameStation >= GS_SEND_CARD && m_byGameStation < GS_WAIT_NEXT)
	{
		return true;
	}
	return false;
}
/*-----------------------------------------------------------------------------------*/
/**
* �û��뿪��Ϸ��
* @return �����û��뿪״̬
*/
BYTE CServerGameDesk::UserLeftDesk(BYTE bDeskStation, CGameUserInfo * pUserInfo)
{
	m_sThingHandle.UserLeftDesk(bDeskStation);
	return __super::UserLeftDesk(bDeskStation,pUserInfo);
}
/*-----------------------------------------------------------------------------------*/
//�����ı��û����������ĺ���
//bool	CServerGameDesk::CanNetCut(BYTE bDeskStation)
//{
//	return true;
//}
/*-----------------------------------------------------------------------------------*/
//�û������뿪
bool	CServerGameDesk::UserNetCut(BYTE bDeskStation, CGameUserInfo * pLostUserInfo)
{
	//����Ϸ�У��ж����йܾͽ����й�
	if (m_byGameStation	>= GS_SEND_CARD && m_byGameStation	< GS_WAIT_NEXT )  
	{
		//m_sThingHandle.UserNetCut(bDeskStation);

		//sUserData.m_byFoceLeavCount = 0;
		//for(int i=0;i<4;++i)
		//{
		//	if(sUserData.m_bFoceLeave[i])//ǿ��
		//	{
		//		sUserData.m_byFoceLeavCount++;
		//	}
		//}
  //      if (sUserData.m_byFoceLeavCount >= PLAY_COUNT && sUserData.m_byFoceLeavCount != 255) //�ļҶ�ǿ���뿪��
  //      {
  //          GameFinish(0,GF_NORMAL); //�û�ǿ���뿪
  //          return true;
  //      }
	}
	//��¼������ң�������ǰ��������ҷ�����Ϣ��
	return __super::UserNetCut(bDeskStation, pLostUserInfo);
}
/*-----------------------------------------------------------------------------------*/
/**
* �������
* @return �����û�����״̬
*/
BYTE	CServerGameDesk::UserSitDesk(MSG_GR_S_UserSit * pUserSit, CGameUserInfo * pUserInfo)
{
	BYTE result = __super::UserSitDesk(pUserSit, pUserInfo);
	return result;
}
/*-----------------------------------------------------------------------------------*/
///������Ϸ��ʱ��
void CServerGameDesk::SetGameTimer(UINT iId,int iTime)
{
	SetTimer(iId,iTime);
}
/*-----------------------------------------------------------------------------------*/
//ɾ��ָ����ʱ��
void CServerGameDesk::KillGameTimer(UINT iId)
{
	KillTimer(iId);
}
/*-----------------------------------------------------------------------------------*/
///������Ϸ״̬
void	CServerGameDesk::SendGameStationEx(BYTE nDeskStation, bool bWatchUser, void * pStationData, UINT uSize)
{
	// ��������
	SendGameStation(nDeskStation,m_uSocketID,bWatchUser,pStationData,uSize);
}
///�������ݺ��� ��������Ϣ����Ϸ�ߣ�
void	CServerGameDesk::SendGameDataEx(BYTE nDeskStation, BYTE bMainID, BYTE bAssID, BYTE bHandleCode)
{
	SendGameData(nDeskStation,MDM_GM_GAME_NOTIFY,bAssID,0) ; 
}
///�����Թ����� ��������Ϣ���Թ��ߣ�
void	CServerGameDesk::SendWatchDataEx(BYTE nDeskStation, BYTE bMainID, BYTE bAssID, BYTE bHandleCode)
{
	SendWatchData(nDeskStation,MDM_GM_GAME_NOTIFY,bAssID,0) ; 
}
///�������ݺ��� ��������Ϣ����Ϸ�ߣ�
void	CServerGameDesk::SendGameDataEx(BYTE nDeskStation, void * pData, UINT uSize, BYTE bMainID, BYTE bAssID, BYTE bHandleCode)
{
	SendGameData(nDeskStation, pData, uSize, MDM_GM_GAME_NOTIFY, bAssID, 0);
}
///�����Թ����� ��������Ϣ���Թ��ߣ�
void	CServerGameDesk::SendWatchDataEx(BYTE nDeskStation, void * pData, UINT uSize, BYTE bMainID, BYTE bAssID, BYTE bHandleCode)
{
	SendWatchData(nDeskStation, pData, uSize, MDM_GM_GAME_NOTIFY, bAssID, 0);
}
/*-----------------------------------------------------------------------------------*/
//���ط�������
void	CServerGameDesk::LoadiniByRoom(int iRoomId)
{
	char key[MAX_PATH];
	CString s = CINIFile::GetAppPath ();/////����·��    
	CINIFile f(s +_T("\\")+SKIN_FOLDER  + _T("_s.ini"));
	sprintf(key,"%d_%d",NAME_ID,iRoomId);

	sGameData.m_mjRule.byAutoOutTime	= f.GetKeyVal(key,TEXT("byAutoOutTime"),sGameData.m_mjRule.byAutoOutTime);	//�Զ�����ʱ��	DWJ
	sGameData.m_mjRule.byOutTime		= f.GetKeyVal(key,TEXT("byOutTime"),sGameData.m_mjRule.byOutTime);			//����ʱ��		DWJ
	sGameData.m_mjRule.byBlockTime		= f.GetKeyVal(key,TEXT("byBlockTime"),sGameData.m_mjRule.byBlockTime);		//����˼��ʱ��	DWJ
	sGameData.m_mjRule.byBeginTime		= f.GetKeyVal(key,TEXT("byBeginTime"),sGameData.m_mjRule.byBeginTime);		//��ʼ�ȴ�ʱ��	DWJ
	sGameData.m_mjRule.bAutoBegin		= f.GetKeyVal(key,TEXT("bAutoBegin"),sGameData.m_mjRule.bAutoBegin);		//ʱ�䵽���Ƿ��Զ���ʼ

	sGameData.m_mjRule.bNetCutTuoGuan	= f.GetKeyVal(key,TEXT("bNetCutTuoGuan"),sGameData.m_mjRule.bNetCutTuoGuan);	//�Ƿ�����й�
	sGameData.m_mjRule.byGamePassNum	= f.GetKeyVal(key,TEXT("GamePassNum"),sGameData.m_mjRule.byGamePassNum);;		//��������

	m_iBase = f.GetKeyVal(key,TEXT("BaseMoney"), m_iBase);
	m_iFanBase = f.GetKeyVal(key,TEXT("FanBase"), m_iFanBase);
	///�����ϲ�·��
	bool  bForceQuitAsAuto = true ; 
	CString szAppPath = CINIFile::GetAppPath();

	CString strBCFFile  ; 
	CString strKeyName  ; 
	strKeyName.Format("%d" ,NAME_ID) ; 
	strBCFFile.Format("%s\\SpecialRule.bcf",szAppPath) ; 

	CBcfFile File(strBCFFile) ;

	if (File.IsFileExist(strBCFFile))
	{
		bForceQuitAsAuto = File.GetKeyVal("ForceQuitAsAuto",strKeyName ,1) ; 
	}
	sGameData.m_mjRule.bForceTuoGuan	= bForceQuitAsAuto;		//�Ƿ�ǿ���й�
}
/*-----------------------------------------------------------------------------*/
//---------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
//�޸Ľ�������1(ƽ̨->��Ϸ)
/// @param bAIWinAndLostAutoCtrl �����˿�����Ӯ����
/// @return �Ƿ�ɹ�
bool CServerGameDesk::SetRoomPond(bool	bAIWinAndLostAutoCtrl)
{
	return false;
}

//�޸Ľ�������2(ƽ̨->��Ϸ)
/// @param m_iAIWantWinMoney ��������Ӯ���ƣ�������ӮǮ����1,2,3 4���öϵ�
/// @param m_iAIWinLuckyAt ��������Ӯ���ƣ�������������1,2,3,4ӮǮ�ĸ���
/// @return �Ƿ�ɹ�
bool CServerGameDesk::SetRoomPondEx(__int64	iAIWantWinMoney[], int	iAIWinLuckyAt[])
{
	return false;
}

//�޸Ľ�������3(ƽ̨->��Ϸ)
/// @param iReSetAIHaveWinMoney ��������Ӯ���ƣ����û������Ѿ�ӮǮ����Ŀ
/// @return �Ƿ�ɹ�
bool CServerGameDesk::SetRoomPondEx(__int64	iReSetAIHaveWinMoney)
{
	return false;
}

//�ж�
BOOL CServerGameDesk::Judge()
{
	if(JudgeWiner())		//�ȴ���ʤ��
	{
		return TRUE;
	}

	if (JudgeLoser())		//��������
	{
		return TRUE;
	}		

	return FALSE;
}
//================================================
//�ж�ʤ��
//================================================
BOOL CServerGameDesk::JudgeLoser()
{
	return FALSE;
}
//================================================
//�ж�ʤ��
//================================================
BOOL CServerGameDesk::JudgeWiner()
{
	return FALSE;
}
//GRM����
//���½�������(��Ϸ->ƽ̨)
/// @return ������ӮǮ��
void CServerGameDesk::UpDataRoomPond(__int64 iAIHaveWinMoney)
{

}

void CServerGameDesk::DissmissRoomBefore()
{
	KillAllTimer();
	//���ʹ������Ϣ
	if (m_bIsBuy && m_iRunGameCount + 1 >= m_iVipGameCount) {
		BYTE byCount = 0;
		m_calculateMsg.bBestFire = 255;
		for (int i = 0; i < PLAY_COUNT; i++) {
			if (m_calculateMsg.iDianPao[i] > byCount) {
				m_calculateMsg.bBestFire = i;
				byCount = m_calculateMsg.iDianPao[i];
			}
		}

		m_calculateMsg.bWinner = 255;
		byCount = 0;
		for (int i = 0; i < PLAY_COUNT; i++) {
			if (m_calculateMsg.i64WinMoney[i] > byCount) {
				m_calculateMsg.bWinner = i;
				byCount = m_calculateMsg.i64WinMoney[i];
			}
		}

		for (int i = 0; i < PLAY_COUNT; i++) {
			SendGameData(i, &m_calculateMsg, sizeof(m_calculateMsg), MDM_GM_GAME_NOTIFY, THING_CALCULATE_BOARD, 0);
		}

		m_calculateMsg.init();
	}
}
