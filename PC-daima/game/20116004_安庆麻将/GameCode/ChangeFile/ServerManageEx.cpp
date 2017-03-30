/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #include "../Server/stdafx.h"
#include "ServerManageEx.h"
#include "IGameMainManager.h"

extern void ErrorPrintf(const char *p, ...);

//-----------------------------------------------------------------------------
/// ������Ϸ����������
bool CreateGameServer(IGameDesk **ppGameDesk)
{
    *ppGameDesk = new CServerGameDeskEx();
    return true;
}
/// �����Ѿ���������Ϸ����������
void DestroyGameServer(IGameDesk **ppIGameDesk)
{
    delete *ppIGameDesk;
    *ppIGameDesk = NULL;
}

CServerGameDeskEx::CServerGameDeskEx()
{
    m_pUserInfo = new UserInfoForGame_t[PLAY_COUNT];
	m_bMaxPeople = PLAY_COUNT;
}

CServerGameDeskEx::~CServerGameDeskEx()
{
    delete m_pUserInfo;
    m_pUserInfo = NULL;
}

/// ������Ϸ�ڲ���Ϣ
int CServerGameDeskEx::HandleNotifyMessage(int nDeskStation, UINT code, BYTE* pBuffer, int nLen)
{
    // ִ�и����
    CServerGameDesk::HandleNotifyMessage(nDeskStation, code, pBuffer, nLen);
    // �˴������ط�0������Ͽ���ͻ��˵�����
    return 0;
}
/// ��ȡ��Ϸ״̬�������͵��ͻ���
int CServerGameDeskEx::OnGetGameStation(int nDeskStation, UserInfoForGame_t& userInfo)
{
	//����id
	m_RoomId = m_pGameManager->GetRoomID();
	Tstring s = CINIFile::GetAppPath ();/////����·��
	CINIFile pz(s + SKIN_FOLDER  + _T("_s.ini"));
	char key[200];
	sprintf(key,"%d_%d",NAME_ID,m_RoomId);
	sGameData.m_bBaoZhuang	= pz.GetKeyVal(key,TEXT("bBaoZhuang"),0);		//�Ƿ��ׯ

	if(sGameData.m_bBaoZhuang)
	{
		sprintf(key,"�齫-���ã�%d_%d  m_bBaoZhuang=%d ",NAME_ID,m_RoomId,sGameData.m_bBaoZhuang);
		OutputDebugString(key);
	}

    // ִ�и����
    CServerGameDesk::OnGetGameStation(nDeskStation, 0, false);
    return 0;
}
/// �������
int CServerGameDeskEx::UserReCome(int nDeskStation, UserInfoForGame_t& userInfo)
{
    if ( (nDeskStation<0) || (nDeskStation>PLAY_COUNT))
    {
        return -1;
    }
    if (m_pUserInfo[nDeskStation]._dwUserID == userInfo._dwUserID)
    {
        m_pUserInfo[nDeskStation]._bIsNetCut = false;        
    }
    else
    {
        ErrorPrintf("[%d]����λ��Ϊ[%d]�����[%d]��Ӧ�����������[%d]"
            , m_nDeskIndex, nDeskStation, m_pUserInfo[nDeskStation]._dwUserID, userInfo._dwUserID);
        return -1;
    }
	return  CServerGameDesk::UserReCome(nDeskStation, userInfo);

    return 0;
}
/// ��ʱ��ʱ�䵽
int CServerGameDeskEx::OnGameTimer(int nTimerID)
{
    // ִ�и����
    CServerGameDesk::OnTimer(nTimerID);
    return 0;
}

/// ��Ҷ���
int CServerGameDeskEx::UserNetCut(int nDeskStation, UserInfoForGame_t& userInfo)
{
    int nRet = CServerGameDesk::UserNetCut(nDeskStation, userInfo);
    return nRet;
}

/// ���������ĳλ��
int CServerGameDeskEx::UserSitDesk(int nDeskStation, UserInfoForGame_t& userInfo)
{
    if ( (nDeskStation<0) || (nDeskStation>PLAY_COUNT))
    {
        return -1;
    }
    if (m_pUserInfo[nDeskStation]._dwUserID != 0)
    {
        ErrorPrintf("[%d]����λ��Ϊ[%d]�Ѿ������[%d]�����[%d]����ʧ��"
            , m_nDeskIndex, nDeskStation, m_pUserInfo[nDeskStation]._dwUserID, userInfo._dwUserID);
        return -1;
    }
    else
    {
        CopyMemory(&m_pUserInfo[nDeskStation], &userInfo, sizeof(UserInfoForGame_t));
    }
    return 0;    
}   

/// �������
int CServerGameDeskEx::UserLeftDesk(int nDeskStation, UserInfoForGame_t& userInfo)
{
    if ( (nDeskStation<0) || (nDeskStation>PLAY_COUNT))
    {
        return -1;
    }
    /// ���������Ϸ�У����Զ��ߴ���
    /// ��Ϸ���ڽ����У�������������
    if (m_pUserInfo[nDeskStation]._dwUserID == userInfo._dwUserID)
    {
        ZeroMemory(&m_pUserInfo[nDeskStation], sizeof(UserInfoForGame_t));
    }

	return  CServerGameDesk::UserLeftDesk(nDeskStation, userInfo);

    return 0;
}

/// ���ͬ����Ϸ
int CServerGameDeskEx::UserAgreeGame(int nDeskStation, UserInfoForGame_t& userInfo)
{
    if ( (nDeskStation<0) || (nDeskStation>PLAY_COUNT))
    {
        return -1;
    }
    if ((m_bGameStation != GS_WAIT_ARGEE) && (m_bGameStation!=GS_WAIT_NEXT)) 
        return -1;
    /// ������ǵȴ�ͬ��״̬���򷵻�ʧ��    
    if (m_pUserInfo[nDeskStation]._dwUserID == userInfo._dwUserID && !m_pUserInfo[nDeskStation]._bIsAgree)
    {
        m_pUserInfo[nDeskStation]._bIsAgree = true;    
    }
    /// �ж��Ƿ������˶�ͬ����
    int nAgreeCount = 0;
    for (int i=0; i<PLAY_COUNT; ++i)
    {
        if ((m_pUserInfo[i]._dwUserID != 0) && m_pUserInfo[i]._bIsAgree)
        {
            ++nAgreeCount;
        }
    }
    /// ��������˶�ͬ�⿪ʼ������Ϸ��ʼ
    if (nAgreeCount==PLAY_COUNT)    // ���ﻹӦ����״̬�ж�
    {
        GameBegin(0);
    }
    return 0;
}

/// ��Ϸ�Ƿ��ڽ�����
bool CServerGameDeskEx::IsPlayingByGameStation(void)
{
    if ((m_bGameStation != GS_WAIT_ARGEE) && (m_bGameStation!=GS_WAIT_NEXT)) 
        return true;
    return false;
}

/// ĳ��������Ƿ�����Ϸ��
bool CServerGameDeskEx::IsPlayGame(int bDeskStation)
{
    if ((m_bGameStation != GS_WAIT_ARGEE) && (m_bGameStation!=GS_WAIT_NEXT)) 
        return true;
    return false;
}


/// ��ʼ������
int CServerGameDeskEx::InitialDesk(int nDeskNo, int nMaxPeople, IGameMainManager* pIMainManager)
{
	return CServerGameDesk::InitialDesk(nDeskNo, nMaxPeople,pIMainManager);
    /// �ж���������Ƿ񳬳���Χ
    if (nMaxPeople > PLAY_COUNT)
    {
        ErrorPrintf("������������Ϸ�����������");
        return -1;
    }
    m_nDeskIndex = nDeskNo;
    m_pGameManager = pIMainManager;
    /// ��ȡ��Ϸ�����ļ�
//    GameBegin(0);
    return 0;
}


///���ƣ�GameFinish
///��������Ϸ�������ٴ˺����е��üƷֺ�����
///@param 
///@return 
bool CServerGameDeskEx::GameFinish(BYTE nDeskStation, BYTE bCloseFlag)
{
	
	switch(bCloseFlag)
	{
	case GF_NORMAL:		//��Ϸ��������
		{
            //KillAllTimer();
			// ÿ������
            for (int i=0; i<PLAY_COUNT; ++i)
            {
                m_pUserInfo[i]._dWinLost = (i==sGameData.T_CountFen.byUser) ? 1 : 3;
                m_pUserInfo[i]._dUserType = (i==sUserData.m_byNtStation) ? 0 : 1;
            }
			for (int i=0; i<m_bMaxPeople; i++)
			{
				m_pUserInfo[i]._bIsAgree = false;// m_UserData.bUserState = USER_SITTING;
			}
            //sm_pRandomTasks[m_nWhichTask]->CheckInFinish(sGameData.T_CountFen, m_RandomTaskArgs);     /// ÿ���������            
            ////////////////////////////////////////////////////////////////////////////////
            // �������
            for (int i=0; i<PLAY_COUNT; ++i)
            {
                m_pUserInfo[i]._nPoint = sGameData.T_CountFen.iZongFen[i];           
                //m_pUserInfo[i]._bIsCompletedTask = sm_pRandomTasks[m_nWhichTask]->GetIsFinished(i, m_RandomTaskArgs);  // �Ƿ����ÿ����������ChangeUserPoint                
                //sGameData.T_CountFen.bIsFinishTask[i] = m_pUserInfo[i]._bIsCompletedTask;    // �Ƿ����ÿ�������·�����)
            }            
            ResultInfo_t resInfo;            
            resInfo._nDeskIndex = m_nDeskIndex;	///< ���ӱ��
            resInfo._nCount = PLAY_COUNT;		///< �����������������UserInfoForGame_t *arUserInfo����Ĵ�С            
            //resInfo._nTaskIndex = m_nWhichTask;	///< ������Ϸ�����������
            //д���ݿ�
            m_pGameManager->ChangeUserPoint(resInfo, m_pUserInfo);            
            // ���㷵��
            for (int i=0; i<PLAY_COUNT; ++i)
            {
                sGameData.T_CountFen.iZongFen[i] = m_pUserInfo[i]._nPoint;
                sGameData.T_CountFen.iMoney[i] = (int)m_pUserInfo[i]._i64Money;
            }
			//��ȡ������
			for (int i=0; i<PLAY_COUNT; i++)     
			{
				sUserData.CopyGCPData(i,sGameData.T_CountFen.m_UserGCPData[i]);	//��������
				sUserData.CopyOutPai(i,sGameData.T_CountFen.m_byArOutPai[i]);	//����
				sUserData.CopyMenPai(i,sGameData.T_CountFen.m_byArHandPai[i]);
			}
			sUserData.CopyHandPai(sGameData.T_CountFen.m_byArHandPai,0,true);	//��������
			//��������
			for (int i=0; i<PLAY_COUNT; i++)     
			{
				SendGameData(i, &sGameData.T_CountFen, sizeof(sGameData.T_CountFen), MDM_GM_GAME_NOTIFY, THING_ENG_HANDLE, 0);   
				SendWatchData(i, &sGameData.T_CountFen, sizeof(sGameData.T_CountFen), MDM_GM_GAME_NOTIFY, THING_ENG_HANDLE, 0); 
			}
			//Ӧ�÷����ͻ��˺������㣬�Ա�֤�ͻ�����ʾ��ʵ�ʽ���һ��
			if(nDeskStation == 255)
			{//����
				sGameData.T_CountFen.Clear();
				sGameData.T_CountFen.byUser = 255;
			}

			m_bGameStation = GS_WAIT_NEXT;

			OutputDebugString(TEXT("�齫-ͬ�⣺������ GameFinish  ���㴦��"));
		}
		break;
	case GF_SALE:			//��Ϸ��ȫ����
	case GFF_FORCE_FINISH:		//�û������뿪
		{
			
		}
		break;
	}

	OutputDebugString(TEXT("�齫-ͬ�⣺������ GameFinish  ������Ϸ"));

    m_pGameManager->OnGameFinish(m_nDeskIndex);
    return true;
}

///���ƣ�HandleSeziLookBao
///��������ɫ�ӿ����¼�
///@param 
///@return 
void CServerGameDeskEx::HandleSeziLookBao()
{

}
