#include "StdAfx.h"
#include "UserPower.h"
#include "GameMainManage.h"
#include "GameRoomMessage.h"
#include "AFCException.h"
#include "AutoAllotDesk.h"

//�궨��
//CGameDesk
#define IDT_CHECK_DESK								1L					//��ɢ����
//
#define IDT_WRITE_SERVER_INFO						7					//���·�������Ϣ��ʱ��
#define IDT_CHECK_DATA_CONNECT						2					//����������Ӷ�ʱ��
#define IDT_UPDATE_ROOM_PEOPLE						3					//ǿ�Ƹ��·����û���������

#define IDT_QUEUE_GAME								4					/// �Ŷӻ���ʱ��
#define IDT_CONTEST_GAMEOVER						5
#define IDT_LEASE_TIMEOVER							6					///���޷���

#define IDT_CONNECT_OTHERSERVER_SOCKET				8					//ά�����������������ӵļ�ʱ��

#define IDT_TIMING_CONTEST_BEGIN					20					///��ʱ�� ��ʼID
#define IDT_TIMING_CONTEST_END						40					///��ʱ�� ����ID
#define IDT_TIMING_CONTEST_INFO						41					//��ʱ��������ǰ1����֪ͨ��ʱ��
#define IDT_CONTEST_KICK							1000

#define VIP_CHECK_TIME								60000				//1���Ӽ��һ��
#define EXPERCISE_MONEY								5000000				//���ѵ������Ǯ��

///���ڱ�������־�Ƿ��������ö�ʱ��������Ϊȫ�ֱ����Ǳ�����Ϸ���±���
static int	m_iResetTime = 0;


/*******************************************************************************************************/

//ע���û���½
//���캯��
CGameMainManage::CGameMainManage(void)
{
	m_bStopLogon=false;
	m_pDesk=NULL;
	m_uDeskCount=0;
	m_uMatchUserCount=0;
	m_pMatchUser=NULL;
	m_pMatchInfo=NULL;
	m_pDeskArray=NULL;
	m_szMsgRoomLogon[0]=0;
	m_szMsgGameLogon[0]=0;
//	m_ItemDate = NULL;
	m_PropService=NULL;
	m_pBankService = NULL;
	m_lVIPID = -1;  ///< ���÷��������ID
	m_uVIPIndex = 0;
	memset(m_szVIPPassWord,0,sizeof(m_szVIPPassWord));

	m_vectDeskRunOutMsg.clear();
	m_vectDeskRunOutAgree.clear();
	
	CBcfFile f(CBcfFile::GetAppPath() + "Function.bcf");
	CString strValue = f.GetKeyVal("TaxRate","Rate","100");
	m_nRate = atoi(strValue);
	strValue = f.GetKeyVal("PresentCoinPerDay","Available","0");
	m_bPresentCoin = (atoi(strValue)!=0);

	m_pIAutoAllotDesk = NULL;
	m_iVIP_Rate = 1.0;
	m_uNameID = 0;
	m_iApplyDissVipDeskUser=0;
	m_bBuyRoom=false;
}

//��������	
CGameMainManage::~CGameMainManage(void)
{
	m_uDeskCount=0;
	SafeDeleteArray(m_pDesk);
	SafeDeleteArray(m_pMatchUser);
	SafeDeleteArray(m_pMatchInfo);
	SafeDeleteArray(m_pDeskArray);
	//if(m_ItemDate) 
	//	delete m_ItemDate;
	if(m_PropService)
		delete m_PropService;
	if (m_pBankService)
		delete m_pBankService;
	m_pGameUserInfoList.clear();
	m_GRMUserID.clear();
	m_GRMRoomID.clear();
}

//���ݹ���ģ���ʼ��
bool CGameMainManage::OnInit(ManageInfoStruct * pInitData, KernelInfoStruct * pKernelData)
{
	try
	{
		DebugPrintf1(m_InitData.uRoomID, "���gOnInit()");
		//��ʼ���û�����Ϸ����
		m_uMatchUserCount=0;
		m_szMsgRoomLogon[0]=0;
		m_szMsgGameLogon[0]=0;
		m_RoomLimited.RemoveAll();
		m_GameLimited.RemoveAll();
		lstrcpy(m_szMsgRoomLogon,TEXT("��ӭ�㣬ף������������ÿ��ģ����ִ����￪ʼ��"));
		lstrcpy(m_szMsgGameLogon,TEXT("��ӭ�㣬ף������������ÿ��ģ����ִ����￪ʼ��"));

		//m_pMainServerSocket = new CMainServerSocket(this);

		//m_ItemDate=new CAFCItemData((CWnd*)this);		
		m_PropService=new CPropService((CWnd*)this);
		m_pBankService = new CBankService((CWnd*)this);
		m_uNameID = pKernelData->uNameID;
		if (m_UserManage.Init(pInitData->uMaxPeople,pInitData->uMaxPeople,pInitData->uVipReseverCount)==false) return false;
		if (InitGameDesk(pInitData->uDeskCount, pInitData->uDeskType)==false) return false;//�ټ���lym

		if (m_KernelData.uDeskPeople != 0)
		{
			for(int i=0; m_InitData.uVirtualUser,i<(m_InitData.uVirtualUser/m_KernelData.uDeskPeople); i++) ///< ����W������������������������ӡ�
			{
				CGameDesk * pDesk = *(m_pDesk + i);
				pDesk->VirtualLockDesk();
			}
		}

		CString _NameID;
		_NameID.Format("%d", pKernelData->uNameID);
		CBcfFile fConfig(CBcfFile::GetAppPath()+"SpecialRule.bcf");
		//pKernelData->uMinDeskPeople = pKernelData->uDeskPeople;
		pKernelData->uMinDeskPeople = fConfig.GetKeyVal("MinDeskPeople", _NameID, (int)pKernelData->uDeskPeople);

		CBcfFile f(CBcfFile::GetAppPath()+"SpecialRule.bcf");
		m_iQueueTime = f.GetKeyVal("Queuer","QueuerTime", 10);

		////�Ȳ����Ƿ���ڸ÷��䣬�������������������sdp2014-05-20
		if (!IsExistGRMRoom(pKernelData->uNameID))
		{
			CBcfFile f(CBcfFile::GetAppPath()+"GRMInfo.bcf");
			bool bRoomGRM = f.GetKeyVal("ManageGameID",_NameID, 0);
			if (bRoomGRM)//ֻ��ȷ����Ч�����
			{
				m_GRMRoomID.push_back(pKernelData->uNameID);
			}
		}

		if (IsQueueGameRoom())
		{
			m_pIAutoAllotDesk = CreateAutoAllotDesk(m_KernelData.uDeskPeople, m_InitData.uDeskCount);
			if (m_InitData.dwRoomRule &GRR_CONTEST || m_InitData.dwRoomRule &GRR_TIMINGCONTEST)
			{//���ڴ�����ʱ�������Ŷ�
				m_pIAutoAllotDesk->SetMinQueuePeople(m_InitData.iLeasePeople);
			}
			//���ݽ�����1-���Ӻţ�3-�ֱ�Ϊ3��Int�ͣ���λ�ţ���ʼ��������ʼ����
			m_pQueueUserSitBuffer = new BYTE[(pKernelData->uDeskPeople*3+1)*sizeof(int)];
		}

		return true;
	}
	catch (CAFCException * pException)	{ pException->Delete();TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);	}
	catch (...) {TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);}
	return false;
}

//���ݹ���ģ��ж��
bool CGameMainManage::OnUnInit()
{
	DebugPrintf1(m_InitData.uRoomID, "���gOnUnInit()");
		/// ������Զ������ķ��䣬���ⴴ���Ķ�����Ҫ�ͷ�
	if (IsQueueGameRoom())
	{
		SafeDeleteArray(m_pQueueUserSitBuffer);
		DestroyAutoAllotDesk(m_pIAutoAllotDesk);
	}

	for(int i=0;i<m_UserManage.GetOnLineUserCount();i++)
	{
		CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(i);
		if (pUserInfo!=NULL) 
		{
			CleanUserInfo(pUserInfo);
		}

	}
	
	//��������
	m_uDeskCount=0;
	m_uMatchUserCount=0;
	m_szMsgRoomLogon[0]=0;
	m_szMsgGameLogon[0]=0;
	SafeDeleteArray(m_pDesk);
	SafeDeleteArray(m_pMatchInfo);
	SafeDeleteArray(m_pDeskArray);
	SafeDeleteArray(m_pMatchUser);
	m_UserManage.UnInit();
	m_RoomLimited.RemoveAll();
	m_GameLimited.RemoveAll();

	return true;
}

//���ݹ���ģ������
bool CGameMainManage::OnStart()
{
	HANDLE hDatabase=m_SQLDataManage.hDBNative;
	HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_RoomStartProcess");
	if(hRecord<(HANDLE)0x1000)
		return false;

	sqlSPAddPara(hDatabase,hRecord,"@RoomID",m_InitData.uRoomID);
	sqlSPAddPara(hDatabase,hRecord,"@LockTable",m_InitData.szLockTable,sizeof(m_InitData.szLockTable));

	sqlSPExec(hDatabase,hRecord,true);

	if(!sqlEndOfFile(hDatabase,hRecord))
	{
		sqlGetValue(hDatabase,hRecord,"RoomWelcome",m_szMsgRoomLogon,sizeof(m_szMsgRoomLogon));
		sqlGetValue(hDatabase,hRecord,"RallWelcome",m_szMsgGameLogon,sizeof(m_szMsgGameLogon));
	}
	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);
	
	CString strSql;

	strSql.Format("select EnableBuy from TGameRoomInfo where RoomID=%d",m_InitData.uRoomID);
	hRecord=sqlExec(hDatabase,strSql,true);
	sqlGetValue(hDatabase,hRecord,"EnableBuy",m_bBuyRoom);
	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);
	//��ȡ��������
	int *pTemp = NULL;
	int *pTemp1 = NULL;
	COleDateTime MatchStartTime;
	strSql.Format(TEXT("select a.GiveNum, a.GiveType, b.StartTime from Web_MatchAwardConfig a inner join TContestInfo b on a.TypeID=b.SendTypeID and b.ContestID=%d"), m_InitData.iContestID);
	sqlExec(hDatabase, strSql, true);
	m_InitData.iRankNum = sqlGetRecordCount(hDatabase,hRecord);
	if (0 < m_InitData.iRankNum)
	{
		m_InitData.pAwards = new int[m_InitData.iRankNum];
		pTemp = m_InitData.pAwards;
		m_InitData.pAwardTypes = new int[m_InitData.iRankNum];
		pTemp1 = m_InitData.pAwardTypes;
	}	
	while (!sqlEndOfFile(hDatabase,hRecord))
	{
		sqlGetValue(hDatabase,hRecord,"GiveNum",*(m_InitData.pAwards++));
		sqlGetValue(hDatabase,hRecord,"GiveType",*(m_InitData.pAwardTypes++));
		sqlGetValue(hDatabase,hRecord,"StartTime",MatchStartTime);
		sqlMoveNext(hDatabase,hRecord);
	}
	sqlCloseRecord(hDatabase,hRecord);    
	sqlSPClose(hDatabase,hRecord);
	if (pTemp)
	{
		m_InitData.pAwards = pTemp;
	}
	if (pTemp1)
	{
		m_InitData.pAwardTypes = pTemp1;
	}
	//��������ʱ����ձ���������ʹ�õı�����	
	strSql.Format(TEXT("delete from TSignUp where GameNameID = %d and RoomID=%d"), m_InitData.iGameID, m_InitData.uRoomID);
	sqlExec(hDatabase, strSql);	

	//����ת�˷�������sdp
	DL_GR_I_RebateUpDateStruct Rebate;
	m_SQLDataManage.PushLine(&Rebate.DataBaseHead,sizeof(Rebate),DTK_GR_BANK_UPDATE_REBATE,0,0);

	DebugPrintf1(m_InitData.uRoomID, "���gOnStart()");
	SetTimer(IDT_WRITE_SERVER_INFO,60000L);
	SetTimer(IDT_CHECK_DATA_CONNECT,60000L);
	SetTimer(IDT_CONNECT_OTHERSERVER_SOCKET, 5000L);

	//���Ŷӻ����䣬�����Ŷӻ���ʱ��
	if (IsQueueGameRoom() && !(m_InitData.dwRoomRule & GRR_CONTEST) && !(m_InitData.dwRoomRule & GRR_TIMINGCONTEST))
	{
		SetTimer(IDT_QUEUE_GAME, m_iQueueTime * 1000);
		m_InitData.iRoomState = 1;
	}
	/*
	if (m_InitData.dwRoomRule & GRR_CONTEST)
	{
		SetTimer(IDT_CONTEST_GAMEOVER, 10000);
	}*/

	if (m_InitData.iLeaseID != 0)
	{
		SetTimer(IDT_LEASE_TIMEOVER, 10000);
	}
	if(m_InitData.dwRoomRule & GRR_TIMINGCONTEST)
	{
		OnStartTimingMatchTimer(MatchStartTime);
	}
	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);
	return true;
}

HANDLE CGameMainManage::sqlSPSetNameEx(HANDLE &hHandle,LPCTSTR szSPName,bool bReturnValue)
{

	bool bIsDBNative = false;;
	if(hHandle == m_SQLDataManage.hDBNative)
	{
		bIsDBNative = true;
	}

	if (bIsDBNative)
	{
		hHandle = m_SQLDataManage.hDBNative;
	}
	else
	{
		hHandle = m_SQLDataManage.hDBLogon;
	}

	if (!sqlExec(hHandle,TEXT("select top 1 * from TGameServerInfo")))
	{
		m_SQLDataManage.SQLConnectReset();

	}

	return  sqlSPSetName(hHandle,szSPName,bReturnValue);

}

//���ݹ���ģ��ر�
bool CGameMainManage::OnStop()
{
	//ɾ����ʱ��
	//KillTimer(IDT_RE_WRITE_DATA);
	for (UINT i=0;i<m_uDeskCount;i++)
	{
		if (*(m_pDesk+i))
		{
			(*(m_pDesk+i))->GameFinish(0,GFF_SAFE_FINISH);
		}
	}
	DebugPrintf1(m_InitData.uRoomID, "���gOnStop()");
	KillTimer(IDT_WRITE_SERVER_INFO);
	KillTimer(IDT_CHECK_DATA_CONNECT);
	//KillTimer(ID_CHECK_VIP_TIMER);
	KillTimer(IDT_QUEUE_GAME);
	return true;
}

/// GM��Ϣ����ģ��
bool CGameMainManage::OnGMSocketMessage(NetMessageHead * pNetHead, void * pData, UINT uSize, ULONG uAccessIP, UINT uIndex, DWORD dwHandleID)
{
	if (pNetHead->bAssistantID == ASS_GM_MESSAGE_PRINTLOG) //��ӡ�����־
	{
		GM_MSG_PrintLog_t* pPrintLogCmd = (GM_MSG_PrintLog_t*)pData;
		if (m_InitData.uRoomID == pPrintLogCmd->uRoomID)
		{
			PrintUsersLog();
		}
		return true;
	}

	if(pNetHead->bAssistantID != ASS_GM_MESSAGE_OPERATE_ACT)
	{
		return true;
	}
	//Ч������
	if ((NULL == pData)||(uSize!=sizeof(GM_OperateByID_t))) return false;///��֤�ṹ�Ƿ�һ��

	/// ��֤������Ȩ��
	CGameUserInfo * pOperator=m_UserManage.GetOnLineUserInfo(uIndex);
	if ((NULL == pOperator) || (pOperator->m_UserData.bGameMaster==0))
	{
		return false;
	}

	//����
	GM_OperateByID_t * pOperation=(GM_OperateByID_t *)pData;
	//DebugPrintf("����[%d]���[%d]ʱ��[%d]", pOperation->iOperation, pOperation->iUserID, pOperation->iWorkMinutes);

	/// �ҵ��û�
	CGameUserInfo *pUserInfo = this->m_UserManage.FindOnLineUser(pOperation->iUserID);
	if (NULL == pUserInfo)
	{
		pUserInfo = this->m_UserManage.FindNetCutUser(pOperation->iUserID);
		if (NULL == pUserInfo)
		{
			return true;
		}
	}
	/// ��������ڴ�ֱ�ӷ���
	if (pOperation->iWorkMinutes == 0)
	{
		pUserInfo->m_UserData.userInfoEx2 = 0;
		return true;
	}
	switch(pOperation->iOperation)
	{
	case GM_ACT_AWORD:		//1	///< �������������浽�����У���ʵʱд���û�Ǯ���������Ϣ���͵�Z������
		break;
	case GM_ACT_NO_TALK:	//2	///< ���ԣ���������������ǰ��ĳ�����У�GM�����߿ͻ�����ͬʱ���������ڵ�W��������������Ϣ
		{
			/// ִ�н���
			CTime tm = CTime::GetCurrentTime();
			tm += pOperation->iWorkMinutes*60;
			CString strTime;
			strTime.Format("%d", tm);
			pUserInfo->m_UserData.userInfoEx2 = atoi(strTime);
			break;
		}
	case GM_ACT_KICK_OUT:	//3	///< �߳����䣬��������������ǰ��ĳ�����У�GM�����߿ͻ�����ͬʱ���������ڵ�W��������������Ϣ
	case GM_ACT_BANDON_ID:	//4	///< ��ֹ��¼������ţ���������������ǰ��ĳ�����У�GM�����߿ͻ���ͬʱ���������ڵ�W��������������Ϣ
		{
			bool bAlreadyCut = false;
			CGameUserInfo *pUserInfo = this->m_UserManage.FindOnLineUser(pOperation->iUserID);
			if (NULL == pUserInfo)
			{
				bAlreadyCut = true;
				pUserInfo = this->m_UserManage.FindNetCutUser(pOperation->iUserID);
				if (NULL == pUserInfo)
				{
					break;
				}
			}
			//m_TCPSocket.SendData(pUserInfo->m_uSocketIndex, MDM_GP_PLAYER_2_GM, ASS_GR_MSG_BE_BANDID, 0, pUserInfo->m_dwHandleID);
			/// һ�㲻�����ǽ����������Ϊ���߳����ŵģ������ܵ�¼��W������
			if (pOperation->iWorkMinutes>0)
			{
				/// �ж��Ƿ��Ѿ�����Ϸ��
				if (pUserInfo->m_UserData.bDeskNO != 255)
				{
					CGameDesk *pDesk = *(m_pDesk+pUserInfo->m_UserData.bDeskNO);
					// ��������ֶΣ����ڱ�־λ�����λ��1����ʱ��ֵ���������ô�����
					pUserInfo->m_UserData.userInfoEx2 |= 0x80000000;
					//if ((pUserInfo->m_UserData.bUserState == USER_PLAY_GAME) || (pUserInfo->m_UserData.bUserState == USER_CUT_GAME))
					if(pDesk->IsPlayingByGameStation())
					{
						/// ������������Ϸ�����Ѿ����ߣ�������Ҷ��ߣ�����Ϸ�������Զ�����������
						if ((pUserInfo->m_UserData.bUserState == USER_PLAY_GAME) || (pUserInfo->m_UserData.bUserState == USER_CUT_GAME))
						{
							if (!bAlreadyCut)
							{
								m_UserManage.RegNetCutUser(pUserInfo);
							}
							pDesk->UserNetCut(pUserInfo->m_UserData.bDeskStation, pUserInfo);
						}
						else
						{
							pDesk->WatchUserLeftDesk(pUserInfo->m_UserData.bDeskStation,pUserInfo);
							//�����û�����
							CleanUserInfo(pUserInfo);
							m_UserManage.FreeUser(pUserInfo, false);
							m_TCPSocket.CloseSocket(pUserInfo->m_uSocketIndex, 0);
						}
					}
					else
					{
						pDesk->UserLeftDesk(pUserInfo->m_UserData.bDeskStation,pUserInfo);
						//�����û�����
						CleanUserInfo(pUserInfo);
						m_UserManage.FreeUser(pUserInfo, false);
						m_TCPSocket.CloseSocket(pUserInfo->m_uSocketIndex, 0);
					}
				}
				else
				{
					//�����û�����
					CleanUserInfo(pUserInfo);
					m_UserManage.FreeUser(pUserInfo, false);
					m_TCPSocket.CloseSocket(pUserInfo->m_uSocketIndex, 0);
				}
			}
			break;
		}
	default:
		break;
	}
	return true;
}

//SOCKET ���ݶ�ȡ
bool CGameMainManage::OnSocketRead(NetMessageHead * pNetHead, void * pData, UINT uSize, ULONG uAccessIP, UINT uIndex, DWORD dwHandleID)
{
	/// {{Added by zxd 20100722 GM��Ϣ�������
	if (MDM_GAMEMASTER_MESSAGE == pNetHead->bMainID)
	{
		return OnGMSocketMessage(pNetHead,pData,uSize,uAccessIP,uIndex,dwHandleID);
	}
	/// Added by zxd 20100722}}
	try
	{
	switch (pNetHead->bMainID)
	{
		//�źż���
	case MDM_GR_NETSIGNAL:
		{
			m_TCPSocket.SendData(uIndex,pData,uSize,MDM_GR_NETSIGNAL,0,0,dwHandleID);
			return true;
		}
	case MDM_GR_LOGON:			//�����½
		{
			return OnUserLogonMessage(pNetHead,pData,uSize,uAccessIP,uIndex,dwHandleID);
		}
	case MDM_GR_USER_ACTION:	//�û�����
		{
			return OnUserActionMessage(pNetHead,pData,uSize,uAccessIP,uIndex,dwHandleID);
		}
	case MDM_GR_ROOM:			//������Ϣ
		{
			return OnRoomMessage(pNetHead,pData,uSize,uAccessIP,uIndex,dwHandleID);
		}
	case MDM_GR_MANAGE:			//������Ϣ
		{
			return OnManageMessage(pNetHead,pData,uSize,uAccessIP,uIndex,dwHandleID);
		}
	case MDM_GR_MONEY:	//Ǯ����
		{
			return OnAboutMoney(pNetHead,pData,uSize,uAccessIP,uIndex,dwHandleID);
		}
	case MDM_GM_GAME_FRAME:		//�����Ϣ
	case MDM_GM_GAME_NOTIFY:	//��Ϸ��Ϣ
		{
			//Ч���û�
			CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
			if (pUserInfo==NULL)
			{
				DebugPrintf("CGameMainManage::OnSocketRead()δ�ҵ��������[uIndex=%d][%d��]", uIndex, __LINE__);
				return false;
			}
			if ((pUserInfo->m_UserData.bDeskNO>=m_uDeskCount)||(pUserInfo->m_UserData.bDeskStation>=m_KernelData.uDeskPeople))
			{
				DebugPrintf("CGameMainManage::OnSocketRead()����[%d]����λ��[%d]�Ƿ�[%d��]",
					pUserInfo->m_UserData.bDeskNO,
					pUserInfo->m_UserData.bDeskStation,
					__LINE__);
				return true;
			}

			//�������� 
			bool bWatchUser=(pUserInfo->m_UserData.bUserState==USER_WATCH_GAME);
			CGameDesk * pGameDesk=*(m_pDesk+pUserInfo->m_UserData.bDeskNO);
			bool bRet = false;
			TCHAR szFunctionName[16];
			if (pNetHead->bMainID==MDM_GM_GAME_NOTIFY)
			{
				if (ASS_GR_VOIEC == pNetHead->bAssistantID)
				{
					return OnVoiceInfo(pNetHead, pData, uSize, uAccessIP, uIndex, dwHandleID);
				}
				else
				{
					_tcscpy(szFunctionName, "Notify");
					bRet = pGameDesk->HandleNotifyMessage(pUserInfo->m_UserData.bDeskStation,pNetHead,pData,uSize,uIndex,bWatchUser);
				}
			}
			else if (pNetHead->bMainID==MDM_GM_GAME_FRAME)
			{
				_tcscpy(szFunctionName, "Frame");
				bRet = pGameDesk->HandleFrameMessage(pUserInfo->m_UserData.bDeskStation,pNetHead,pData,uSize,uIndex,bWatchUser);
			}
			if (!bRet)
			{
				DebugPrintf("CGameMainManage::OnSocketRead()��pGameDesk->Handle%sMessage()����ֵΪfalse[bMainID=%d, bAssID=%d][uIndex=%d][%d��]",
					szFunctionName, pNetHead->bMainID, pNetHead->bAssistantID, uIndex, __LINE__);
			}
			return bRet;		
		}
	case MDM_GR_MESSAGE:	//����ϵͳ��Ϣ
		{
			MSG_GR_RS_NormalTalk * pNormalTalk=(MSG_GR_RS_NormalTalk *)pData;
			if ((uSize<=(sizeof(MSG_GR_RS_NormalTalk)-sizeof(pNormalTalk->szMessage)))||(uSize>sizeof(MSG_GR_RS_NormalTalk))) return false;
			if ((pNormalTalk->iLength+1)!=(uSize+sizeof(pNormalTalk->szMessage)-sizeof(MSG_GR_RS_NormalTalk))) return false;

			MSG_GA_S_Message Message;
			memset(&Message,0,sizeof(Message));

			//��������
			Message.bFontSize=0;
			Message.bCloseFace=0;
			Message.bShowStation=pNormalTalk->szMessage[0]==64?2:1;
			/*if (m_TalkFilter.IsAllowableTalk(pNormalTalk->szMessage,lstrlen(pNormalTalk->szMessage)))
			{
				lstrcpy(Message.szMessage,pNormalTalk->szMessage);
			}
			else
			{
				const TCHAR* pTemTalk = m_TalkFilter.GetReplaceContent();
				strcpy(Message.szMessage,pTemTalk);

			}*/

			string str_temp(pNormalTalk->szMessage);
			m_HNFilter.censor(str_temp,false);
			strcpy(pNormalTalk->szMessage,str_temp.c_str());
			pNormalTalk->iLength = strlen(pNormalTalk->szMessage) + 1;
			pNormalTalk->szMessage[pNormalTalk->iLength + 1] = 0;

			if (pNetHead->bAssistantID==ASS_GR_SYSTEM_MESSAGE)
				m_TCPSocket.SendDataBatch(&Message,sizeof(Message),MDM_GR_MESSAGE,ASS_GR_SYSTEM_MESSAGE,0);
			return true;
		}
	case MDM_GM_MESSAGE:	//����ϵͳ��Ϣ
		{
			MSG_GR_RS_NormalTalk * pNormalTalk=(MSG_GR_RS_NormalTalk *)pData;
			if ((uSize<=(sizeof(MSG_GR_RS_NormalTalk)-sizeof(pNormalTalk->szMessage)))||(uSize>sizeof(MSG_GR_RS_NormalTalk))) return false;
			if ((pNormalTalk->iLength+1)!=(uSize+sizeof(pNormalTalk->szMessage)-sizeof(MSG_GR_RS_NormalTalk))) return false;

			MSG_GA_S_Message Message;
			memset(&Message,0,sizeof(Message));

			//��������
			Message.bFontSize=0;
			Message.bCloseFace=0;
			Message.bShowStation=1;
			/*if (m_TalkFilter.IsAllowableTalk(pNormalTalk->szMessage,lstrlen(pNormalTalk->szMessage)))
			{
				lstrcpy(Message.szMessage,pNormalTalk->szMessage);
			}
			else
			{
				const TCHAR* pTemTalk = m_TalkFilter.GetReplaceContent();
				strcpy(Message.szMessage,pTemTalk);
			}*/

			string str_temp(pNormalTalk->szMessage);
			m_HNFilter.censor(str_temp,false);
			strcpy(pNormalTalk->szMessage,str_temp.c_str());
			pNormalTalk->iLength = strlen(pNormalTalk->szMessage) + 1;
			pNormalTalk->szMessage[pNormalTalk->iLength + 1] = 0;

			if (pNetHead->bAssistantID==ASS_GM_SYSTEM_MESSAGE)
				m_TCPSocket.SendDataBatch(&Message,sizeof(Message),MDM_GM_MESSAGE,ASS_GM_SYSTEM_MESSAGE,0);

			return true;
		}
	case MDM_GR_POINT://�����
		{
			return OnPointMessage(pNetHead,pData,uSize,uAccessIP,uIndex,dwHandleID);
		}
	case MDM_GR_FRIEND_MANAGE://����
		{
			return OnFriendManageMsg(pNetHead,pData,uSize,uAccessIP,uIndex,dwHandleID);
		}

	case MDM_GR_QUEUE_MSG://�Ŷ�
		{
			return OnQueueMsg(pNetHead,pData,uSize,uAccessIP,uIndex,dwHandleID);
		}
	case MDM_GR_PROP://vip����Ҳ����PROP��
		{
            // PengJiLin, 2010-9-13, ���˿����˹���
            if(ASS_PROP_NEW_KICKUSER == pNetHead->bAssistantID)
            {
                return OnNewKickUserProp(pNetHead, pData, uSize, uAccessIP, uIndex, dwHandleID);
            }

			if(m_PropService)
			{				
				return m_PropService->OnNetMessage(pNetHead,pData,uSize,uAccessIP,uIndex,dwHandleID);
			}
			return true;
		}
	case MDM_BANK:
		{
			if (m_pBankService)
			{
				return m_pBankService->OnNetMessage(pNetHead, pData, uSize, uAccessIP, uIndex, dwHandleID);
			}
		}
	case MDM_GR_DESKRUNOUT://���ӽ�ɢ
		{
			return OnDeskDissmiss(pNetHead,pData,uSize,uAccessIP,uIndex,dwHandleID);
		}break;
	}
	}
	catch (...)
	{
		DebugPrintf("GameMainManage OnSocketRead�쳣[bMainID = %d][%d��]", pNetHead->bMainID, __LINE__);
		return false;
	}
	return false;
}



//������½������½ÿ�����䣩

//�û���������
bool CGameMainManage::OnUserActionMessage(NetMessageHead * pNetHead, void * pData, UINT uSize, ULONG uAccessIP, UINT uIndex, DWORD dwHandleID)
{
	TRACE("USER ACTION MESSAGE:%d with %d\n",pNetHead->bMainID,pNetHead->bAssistantID);
	if(pNetHead->bMainID!=MDM_GR_USER_ACTION)
		return false;
	
	switch (pNetHead->bAssistantID)
	{
	case ASS_GR_USER_HIT_BEGIN:
		{
			MSG_GM_WatchSet UserAgreeID;
			CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
			if(pUserInfo!=NULL)
			{
				pUserInfo->m_UserData.bUserState=USER_DESK_AGREE;
				UserAgreeID.dwUserID = pUserInfo->m_UserData.dwUserID;
				m_TCPSocket.SendDataBatch(&UserAgreeID,sizeof(MSG_GM_WatchSet),MDM_GR_USER_ACTION,ASS_GR_USER_HIT_BEGIN,0);
				return true;
			}
			else
				return false;
		}
	case ASS_GR_SET_TABLE_BASEPOINT:
		{
			if(uSize!=sizeof(MSG_GR_S_SetDeskBasePoint)) return false;
			MSG_GR_S_SetDeskBasePoint* setBasePoint=(MSG_GR_S_SetDeskBasePoint*)pData;

			CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
			if(pUserInfo->m_UserData.bDeskNO!=255)
			{
				CGameDesk * pNewDesk=*(m_pDesk+pUserInfo->m_UserData.bDeskNO);
				if(pNewDesk->GetTableOwnerID()==setBasePoint->dwUserID)//����
				{
					setBasePoint->bDeskOwner=1;
					pNewDesk->SetTableBasePoint(setBasePoint->iDeskBasePoint);
				}
			}else 
				setBasePoint->bDeskOwner=0;
			if(pUserInfo==NULL)
			{
				//����ʧ����Ϣ
				m_TCPSocket.SendData(uIndex,MDM_GR_USER_ACTION,ASS_GR_SET_TABLE_BASEPOINT,0,dwHandleID);
				return false;
			}
			else 
			{
				pUserInfo->m_UserData.uDeskBasePoint=setBasePoint->iDeskBasePoint;
				m_TCPSocket.SendDataBatch(setBasePoint,uSize,MDM_GR_USER_ACTION,ASS_GR_SET_TABLE_BASEPOINT,1);
			}
			return true;
		}
	case ASS_GR_USER_UP:		//�û�����
	case ASS_GR_WATCH_UP:		//�Թ�����
		{
			//Ч�����ݺϷ���
			if (uSize!=0) return false;
			CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
			if (pUserInfo==NULL) return false;
			//�ж��Ƿ�����뿪
			if (pUserInfo->m_UserData.bDeskNO!=255)
			{

				if (IsUserPlayGame(pUserInfo)==true) 
				{
					m_TCPSocket.SendData(uIndex,MDM_GR_USER_ACTION,ASS_GR_SIT_ERROR,ERR_GR_CAN_NOT_LEFT,dwHandleID);
					return true;
				}
				UserLeftDesk(pUserInfo);

			}
			return true;
		}
	case ASS_GR_USER_SIT:		//�û�������Ϸ
	case ASS_GR_WATCH_SIT:		//�û��Թ���Ϸ
		{
			//Ч������
			if (uSize!=sizeof(MSG_GR_S_UserSit)) return false;
			MSG_GR_S_UserSit * pUserSitInfo=(MSG_GR_S_UserSit *)pData;
			CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
			if (pUserInfo==NULL) return false;
			if ((pUserSitInfo->bDeskIndex>=m_uDeskCount)||(pUserSitInfo->bDeskStation>=m_KernelData.uDeskPeople)) return false;

			//�����Ƿ���������Ϣ
			if ((pUserInfo->m_UserData.bDeskNO==pUserSitInfo->bDeskIndex)&&
				(pUserInfo->m_UserData.bDeskStation==pUserSitInfo->bDeskStation)) 
			{
				m_TCPSocket.SendData(uIndex,MDM_GR_USER_ACTION,ASS_GR_SIT_CUTRESIT,ERR_GR_ALREAD_USER,dwHandleID);
				return true;
			}

			//�����û��뿪ԭλ��
			if (pUserInfo->m_UserData.bDeskNO!=255)
			{
				if (IsUserPlayGame(pUserInfo)==true)
				{
					if(m_InitData.uComType==TY_MATCH_GAME) return true;
					m_TCPSocket.SendData(uIndex,MDM_GR_USER_ACTION,ASS_GR_SIT_ERROR,ERR_GR_CAN_NOT_LEFT,dwHandleID);
					return true;
				}
				UserLeftDesk(pUserInfo);
			}

			//�����û�����λ��
			BYTE bErrorCode=ERR_GR_ERROR_UNKNOW;
			CGameDesk * pNewDesk=*(m_pDesk+pUserSitInfo->bDeskIndex);
			/// {{ added by zxd 20100902 ��������������ˣ���������
			if (pNewDesk->IsVirtualLock())
			{
				m_TCPSocket.SendData(uIndex,MDM_GR_USER_ACTION,ASS_GR_SIT_ERROR,ERR_GR_ALREAD_USER,dwHandleID);
				return true;
			}
			/// added by zxd 20100902 ��������������ˣ���������}}
			if (pNetHead->bAssistantID==ASS_GR_USER_SIT) 
				bErrorCode=pNewDesk->UserSitDesk(pUserSitInfo,pUserInfo);
			else 
				bErrorCode=pNewDesk->WatchUserSitDesk(pUserSitInfo,pUserInfo);

			if (bErrorCode!=ERR_GR_SIT_SUCCESS)	
			{
				m_TCPSocket.SendData(uIndex,MDM_GR_USER_ACTION,ASS_GR_SIT_ERROR,bErrorCode,dwHandleID);
			}
			return true;
		}
	case ASS_GR_JOIN_QUEUE:	///<���û������Ŷӻ�
		{
			///�����Ŷӻ�����
			if (!IsQueueGameRoom())
			{
				return true;
			}

			if (uSize!=0) 
			{
				return false;
			}

			CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
			if (pUserInfo==NULL) 
			{
				return false;
			}

			if ((m_InitData.dwRoomRule & GRR_CONTEST) && 1 != m_InitData.iRoomState)
			{
				//���ñ�����ʼ��־
				m_InitData.iRoomState = 1;
				//�����ݿ��ȡ����ID����֪ͨ������ʼ
				DL_GR_I_ContestBegin DL_ContestBegin;
				DL_ContestBegin.uNameID = m_InitData.iGameID;
				DL_ContestBegin.uRoomID = m_InitData.uRoomID;
				DL_ContestBegin.iContestID = m_InitData.iContestID;
				m_SQLDataManage.PushLine(&DL_ContestBegin.DataBaseHead, sizeof(DL_ContestBegin), DTK_GR_CONTEST_BEGIN, uIndex, dwHandleID);					
			}
			if (!(m_InitData.dwRoomRule & GRR_CONTEST) && !(m_InitData.dwRoomRule & GRR_TIMINGCONTEST))
			{
				m_pGameUserInfoList.remove(pUserInfo);		//ɾ�������Ŷӵ���ң���ֹͬһ�û��ŶӶ��
				m_pGameUserInfoList.push_back(pUserInfo);
				AutoAllotDeskAddUser(pUserInfo);
			}
			return true;
		}
	case ASS_GR_QUIT_QUEUE:///<�����뿪�Ŷӻ�
		{
			///�����Ŷӻ�����
			if (!IsQueueGameRoom())
			{
				return true;
			}

			if (uSize!=0) 
			{
				return false;
			}

			CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
			if (pUserInfo==NULL)
			{
				return false;
			}

			//int dwUserID = pUserInfo->m_UserData.dwUserID;
			m_pGameUserInfoList.remove(pUserInfo);	//ɾ�������Ŷӵ����

			AutoAllotDeskDeleteUser(pUserInfo);

			return true;
		}
	case ASS_GR_CONTEST_APPLY:
		{
			if (!(m_InitData.dwRoomRule & GRR_CONTEST) && !(m_InitData.dwRoomRule & GRR_TIMINGCONTEST))
			{
				return false;
			}
			
			if (sizeof(MSG_GR_I_ContestApply) != uSize && 0 != uSize)
			{
				return false;
			}
			DL_GR_I_ContestApply DL_ContestApply;
			if (0 == uSize)
			{
				CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
				if (pUserInfo==NULL) 
				{
					return false;
				}
				DL_ContestApply.iUserID = pUserInfo->m_UserData.dwUserID;
				DL_ContestApply.iTypeID = 0;//Ĭ��Ϊ����
			}
			else
			{
				MSG_GR_I_ContestApply *_in = (MSG_GR_I_ContestApply*)pData;
				
				DL_ContestApply.iUserID = _in->iUserID;
				DL_ContestApply.iTypeID = _in->iTypeID;
			}

			m_SQLDataManage.PushLine(&DL_ContestApply.DataBaseHead, sizeof(DL_ContestApply), DTK_GR_CONTEST_APPLY, uIndex, dwHandleID);
			return true;
		}
	case ASS_GR_FAST_JOIN_IN://��������
		{
			return OnUserAction_FastSit(pNetHead,pData,uSize,uAccessIP,uIndex,dwHandleID);
		}
	}
	return false;
}

//�ҳ������������
/*CGameDesk * CGameMainManage::findBestDesk()
{
TCHAR sz[50];

int maxPeople=0,maxPeopleDesk=0;
for(int i=0;i<m_uDeskCount;i++)
{
//wsprintf(sz,"%d",maxPeopleDesk);

CGameDesk * pNewDesk=*(m_pDesk+i);
int uSitCount=0;
for (BYTE j=0;j<pNewDesk->m_bMaxPeople;j++)
{
if (pNewDesk->m_pUserInfo[j]==NULL) 
continue;
else 
{
BYTE temp=pNewDesk->m_pUserInfo[j]->m_UserData.bUserState;
if ((temp==USER_LOOK_STATE)||(temp==USER_SITTING)||(temp==USER_ARGEE)) uSitCount++;
}
}
if(uSitCount>maxPeople&&uSitCount!=pNewDesk->m_bMaxPeople)
{
maxPeople=uSitCount;
maxPeopleDesk=i;
}
}

return *(m_pDesk+maxPeopleDesk);
}*/

//Ǯ���˴���
bool CGameMainManage::OnAboutMoney(NetMessageHead * pNetHead, void * pData, UINT uSize, ULONG uAccessIP, UINT uIndex, DWORD dwHandleID)
{
	ASSERT(pNetHead->bMainID==MDM_GR_MONEY);
	switch (pNetHead->bAssistantID)
	{
	case ASS_GR_PAY_MONEY:
		{
			//��Ǯ����ֱ�������ݿ���ۣ������ϵ�Ǯ

			//Ч������
			if(uSize!=sizeof(MSG_GR_S_Pay)) return false;
			MSG_GR_S_Pay* pPayMoney=(MSG_GR_S_Pay*)pData;
			//��������
			CGameUserInfo* pUserInfo = m_UserManage.FindOnLineUser(pPayMoney->UserID);
			if(pUserInfo==NULL)
				return false;

			if(pPayMoney->uCount + pUserInfo->m_UserData.i64Money < 0)//���ϵ�Ǯ����
			{
				m_TCPSocket.SendData(uIndex,MDM_GR_MONEY,ASS_GR_PAY_MONEY,0,dwHandleID);//
				return true;
			}

			pUserInfo->m_ChangePoint.dwMoney +=  pPayMoney->uCount;
			pUserInfo->m_UserData.i64Money +=  pPayMoney->uCount;
			//�ཿ�Ǯ
			DL_GR_I_UserLeft m_UserInfo;
			memset(&m_UserInfo,0,sizeof(m_UserInfo));
			m_UserInfo.dwUserID = pPayMoney->UserID;
			m_UserInfo.dwChangeMoney = pPayMoney->uCount;
			m_SQLDataManage.PushLine(&m_UserInfo.DataBaseHead,sizeof(m_UserInfo),DTK_GR_UPDATE_GAME_RESULT,0,0);

			m_TCPSocket.SendDataBatch(pPayMoney,uSize,MDM_GR_MONEY,ASS_GR_PAY_MONEY,1);//�ɹ�
			return true;
		}
	case ASS_GR_REFLASH_MONEY:
		{
			//Ч������
			if(uSize!=sizeof(MSG_GR_S_RefalshMoney)) return false;
			MSG_GR_S_RefalshMoney* pReflashMoney=(MSG_GR_S_RefalshMoney*)pData;
			if(pNetHead->bHandleCode==0)//ͬ�����
			{
				if(m_InitData.uComType!=TY_MONEY_GAME) return false;

				//��������
				CGameUserInfo * pUserInfo=m_UserManage.FindOnLineUser(pReflashMoney->dwUserID);
				if (pUserInfo==NULL) return false;
				else
				{
					pUserInfo->m_UserData.i64Money = pReflashMoney->i64Money;
					if(pUserInfo->m_UserData.i64Money<0) 
					{
						pUserInfo->m_UserData.i64Money=0; 
						pReflashMoney->i64Money=0;
					}

				}
				m_TCPSocket.SendDataBatch(pReflashMoney,uSize,MDM_GR_ROOM,ASS_GR_USER_POINT,10);
				return true;
			}else if(pNetHead->bHandleCode==1)//ͬ������
			{
				//��������
				CGameUserInfo * pUserInfo=m_UserManage.FindOnLineUser(pReflashMoney->dwUserID);
				if (pUserInfo==NULL) return false;
				else
				{
					pUserInfo->m_UserData.dwPoint = pReflashMoney->i64Money;
				}
				m_TCPSocket.SendDataBatch(pReflashMoney,uSize,MDM_GR_ROOM,ASS_GR_USER_POINT,11);
				return true;
			}
		}
	case ASS_GR_OPEN_WALLET_INGAME:		///< ��Ϸ�д����н��� 
		{
			//Ч������
			//if(uSize!=sizeof(MSG_GR_OpenBank))
			//	return false;
			MSG_GR_OpenBank * pOpenBank=(MSG_GR_OpenBank *)pData;

			//��������
			CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
			if (pUserInfo==NULL) return false;

			//��ȡ���ݿ�
			DL_GR_I_UnRegisterUser OpenWallet;
			memset(&OpenWallet,0,sizeof(OpenWallet));
			OpenWallet.dwUserID = pUserInfo->m_UserData.dwUserID;
			//lstrcpy(OpenWallet.szMD5Pass,pOpenBank->szMD5Pass);
			m_SQLDataManage.PushLine(&OpenWallet.DataBaseHead,sizeof(OpenWallet),DTK_GR_DEMAND_MONEY_IN_GAME,uIndex,dwHandleID);
			return true;
		}
	case ASS_GR_OPEN_WALLET:			///< �ڴ�����Ǯ��
		{
			MSG_GR_OpenBank * pOpenBank=(MSG_GR_OpenBank *)pData;

			//��������
			CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
			if (pUserInfo==NULL) return false;

			//��ȡ���ݿ�
			DL_GR_I_UnRegisterUser OpenWallet;
			memset(&OpenWallet,0,sizeof(OpenWallet));
			OpenWallet.dwUserID = pUserInfo->m_UserData.dwUserID;
			//lstrcpy(OpenWallet.szMD5Pass,pOpenBank->szMD5Pass);
			m_SQLDataManage.PushLine(&OpenWallet.DataBaseHead,sizeof(OpenWallet),DTK_GR_DEMAND_MONEY,uIndex,dwHandleID);
			return true;
		}
	case ASS_GR_CHECK_OUT:			//ȡ
		{
			//Ч������
			if (uSize!=sizeof(MSG_GR_S_CheckMoneyWithPwd_t)) return false;
			MSG_GR_S_CheckMoneyWithPwd_t* pCheckOut=(MSG_GR_S_CheckMoneyWithPwd_t *)pData;

			//��������
			CGameUserInfo* pTargetUserInfo=m_UserManage.FindOnLineUser(pCheckOut->UserID);

			//��ȫ��֤�����ڻ����˹���һ��uIndex�����Ի����˲����밲ȫ��֤
			//Add by JianGuankun 2012.2.1
			if (pTargetUserInfo == NULL)
			{
				return false;
			}

			if (!pTargetUserInfo->m_UserData.isVirtual)
			{
				CGameUserInfo* pUserInfo = m_UserManage.GetOnLineUserInfo(uIndex);
				if (pUserInfo == NULL)
				{
					return false;
				}

				if (pCheckOut->UserID != pUserInfo->m_UserData.dwUserID)
				{
					return false;
				}
			}

			//end add

			//if (pTargetUserInfo==NULL||pCheckOut->UserID!=pUserInfo->m_UserData.dwUserID) return false;

			/// ������������Ϸ�У��ǰ�������Ϸ��ׯ��(����)������ȡǮ add by lxl 2010-12-6
			if (pTargetUserInfo->m_UserData.bUserState == USER_PLAY_GAME 
				|| pTargetUserInfo->m_UserData.bUserState == USER_CUT_GAME
				|| ((m_InitData.dwRoomRule & GRR_GAME_U3D) && IsUserPlayGame(pTargetUserInfo))
				)
			{
				if(pTargetUserInfo->m_UserData.bDeskNO != 255)
				{
					CGameDesk *pDesk = *(m_pDesk+pTargetUserInfo->m_UserData.bDeskNO);

					if(!pDesk->IsBJLGameType())
					{		
						m_TCPSocket.SendData(uIndex, MDM_GR_MONEY, ASS_GR_CHECK_OUT, ASS_GR_CHECKOUT_ERROR_PLAYING, dwHandleID);
						return true;
					}

					CBcfFile f(CBcfFile::GetAppPath() + "Function.bcf");
					int drawMoneyInGame = f.GetKeyVal("DrawMoneyInGame","Available",0);
					if(drawMoneyInGame)
					{
						if(pDesk->IsZhuangjia(pTargetUserInfo->m_UserData.dwUserID))
						{
							m_TCPSocket.SendData(uIndex, MDM_GR_MONEY, ASS_GR_CHECK_OUT, ASS_GR_CHECKOUT_ERROR_PLAYING, dwHandleID);
							return true;
						}
					}

				}
			}


			//д�����ݿ�
			DL_GR_I_CheckOutMoneyWithPwd_t CheckOut;
			memset(&CheckOut,0,sizeof(CheckOut));
			CheckOut.dwUserID=pCheckOut->UserID;
			CheckOut.i64Count=pCheckOut->i64Count;
			CopyMemory(CheckOut.szMD5Pass, pCheckOut->szMD5Pass, sizeof(CheckOut.szMD5Pass));
			m_SQLDataManage.PushLine(&CheckOut.DataBaseHead,sizeof(CheckOut),DTK_GR_CHECKOUT_MONEY,uIndex,dwHandleID);
			return true;
		}
	case ASS_GR_CHECK_OUT_INGAME:	// ��Ϸ��ȡ
		{
			//Ч������
			if (uSize!=sizeof(MSG_GR_S_CheckMoneyWithPwd_t)) return false;
			MSG_GR_S_CheckMoneyWithPwd_t * pCheckOut=(MSG_GR_S_CheckMoneyWithPwd_t *)pData;

			//��������
			CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
			if (pUserInfo==NULL) return false;
			CGameUserInfo * pTargetUserInfo=m_UserManage.FindOnLineUser(pCheckOut->UserID);
			if (pTargetUserInfo==NULL||pCheckOut->UserID!=pUserInfo->m_UserData.dwUserID) return false;

			/// ������������Ϸ�У����Ƿǰ�������Ϸ������ȡǮ add by lxl 2010-12-6
			if (pUserInfo->m_UserData.bUserState == USER_PLAY_GAME 
				|| pUserInfo->m_UserData.bUserState == USER_CUT_GAME
				|| ((m_InitData.dwRoomRule & GRR_GAME_U3D) && IsUserPlayGame(pTargetUserInfo))
				)
			{
				if(pUserInfo->m_UserData.bDeskNO != 255)
				{
					CGameDesk *pDesk = *(m_pDesk+pUserInfo->m_UserData.bDeskNO);
					if(!pDesk->IsBJLGameType())
					{		
						m_TCPSocket.SendData(uIndex, MDM_GR_MONEY, ASS_GR_CHECK_OUT_INGAME, ASS_GR_CHECKOUT_ERROR_PLAYING, dwHandleID);
						return true;
					}

					CBcfFile f(CBcfFile::GetAppPath() + "Function.bcf");
					int drawMoneyInGame = f.GetKeyVal("DrawMoneyInGame","Available",0);
					if(drawMoneyInGame)
					{
						if(pDesk->IsZhuangjia(pUserInfo->m_UserData.dwUserID))
						{
							m_TCPSocket.SendData(uIndex, MDM_GR_MONEY, ASS_GR_CHECK_OUT_INGAME, ASS_GR_CHECKOUT_ERROR_PLAYING, dwHandleID);
							return true;
						}
					}
				}
			}


			//д�����ݿ�
			DL_GR_I_CheckOutMoneyWithPwd_t CheckOut;
			memset(&CheckOut,0,sizeof(CheckOut));
			CheckOut.dwUserID=pCheckOut->UserID;
			CheckOut.i64Count=pCheckOut->i64Count;
			CopyMemory(CheckOut.szMD5Pass, pCheckOut->szMD5Pass, sizeof(CheckOut.szMD5Pass));
			m_SQLDataManage.PushLine(&CheckOut.DataBaseHead,sizeof(CheckOut),DTK_GR_CHECKOUT_MONEY_INGAME,uIndex,dwHandleID);
			return true;

		}
	case ASS_GR_CHECK_IN:			//��Ǯ
		{
			//Ч������
			if (uSize!=sizeof(MSG_GR_S_CheckMoney)) return false;
			MSG_GR_S_CheckMoney * pCheckIn=(MSG_GR_S_CheckMoney *)pData;

			//��������
			CGameUserInfo* pTargetUserInfo=m_UserManage.FindOnLineUser(pCheckIn->UserID);

			//��ȫ��֤�����ڻ����˹���һ��uIndex�����Ի����˲����밲ȫ��֤
			//Add by JianGuankun 2012.2.1
			if (pTargetUserInfo == NULL)
			{
				return false;
			}
			
			if (!pTargetUserInfo->m_UserData.isVirtual)
			{
				CGameUserInfo* pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
				if (pUserInfo == NULL)
				{
					return false;
				}
				if (pCheckIn->UserID != pUserInfo->m_UserData.dwUserID)
				{
					return false;
				}
			}
			//end add

			/// ������������Ϸ�У����ô�Ǯ
			/// todo

			if (pTargetUserInfo->m_UserData.bUserState == USER_PLAY_GAME
				|| pTargetUserInfo->m_UserData.bUserState == USER_CUT_GAME
				|| ((m_InitData.dwRoomRule & GRR_GAME_U3D) && IsUserPlayGame(pTargetUserInfo))
				)
			{
				m_TCPSocket.SendData(uIndex, MDM_GR_MONEY, ASS_GR_CHECK_IN, ASS_GR_CHECKIN_ERROR_PLAYING, dwHandleID);
				return true;
			}

			/// �ټ�������Ϸ����������ׯ�ң����ô�Ǯ add by lxl 2010-11-5
			//�ж��Ƿ�����Ϸ���ӣ�ֻ������Ϸ�в��п�����ׯ��
			if(pTargetUserInfo->m_UserData.bDeskNO != 255)
			{
				CGameDesk* pDesk = *(m_pDesk + pTargetUserInfo->m_UserData.bDeskNO);
				if(pDesk->IsZhuangjia(pTargetUserInfo->m_UserData.dwUserID))
				{
					m_TCPSocket.SendData(uIndex, MDM_GR_MONEY, ASS_GR_CHECK_IN_INGAME, ASS_GR_CHECKIN_ZHUANGJIA, dwHandleID);
					return true;
				}
			}

			//д�����ݿ�
			DL_GR_I_CheckOutMoney CheckIn;
			memset(&CheckIn,0,sizeof(CheckIn));
			CheckIn.dwUserID=pCheckIn->UserID;
			CheckIn.i64Count= pCheckIn->i64Count;
			m_SQLDataManage.PushLine(&CheckIn.DataBaseHead,sizeof(CheckIn),DTK_GR_CHECKIN_MONEY,uIndex,dwHandleID);
			return true;

		}
	case ASS_GR_CHECK_IN_INGAME:	//��Ϸ�д�Ǯ
		{
			//Ч������
			if (uSize!=sizeof(MSG_GR_S_CheckMoney)) return false;
			MSG_GR_S_CheckMoney * pCheckIn=(MSG_GR_S_CheckMoney *)pData;

			//��������
			CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
			if (pUserInfo==NULL) return false;
			CGameUserInfo * pTargetUserInfo=m_UserManage.FindOnLineUser(pCheckIn->UserID);
			if (pTargetUserInfo==NULL||pCheckIn->UserID!=pUserInfo->m_UserData.dwUserID) return false;
			/// ������������Ϸ�У����ô�Ǯ
			/// todo
			if (pUserInfo->m_UserData.bUserState == USER_PLAY_GAME
				|| pUserInfo->m_UserData.bUserState == USER_CUT_GAME
				|| ((m_InitData.dwRoomRule & GRR_GAME_U3D) && IsUserPlayGame(pTargetUserInfo))
				)
			{
				m_TCPSocket.SendData(uIndex, MDM_GR_MONEY, ASS_GR_CHECK_IN_INGAME, ASS_GR_CHECKIN_ERROR_PLAYING, dwHandleID);
				return true;
			}

			/// �ټ�������Ϸ����������ׯ�ң����ô�Ǯ add by lxl 2010-11-5
			//�ж��Ƿ�����Ϸ���ӣ�ֻ������Ϸ�в��п�����ׯ��
			if(pUserInfo->m_UserData.bDeskNO != 255)
			{
				CGameDesk *pDesk = *(m_pDesk+pUserInfo->m_UserData.bDeskNO);
				if(pDesk->IsZhuangjia(pUserInfo->m_UserData.dwUserID))
				{
					m_TCPSocket.SendData(uIndex, MDM_GR_MONEY, ASS_GR_CHECK_IN_INGAME, ASS_GR_CHECKIN_ZHUANGJIA, dwHandleID);
					return true;
				}
			}

			//д�����ݿ�
			DL_GR_I_CheckOutMoney CheckIn;
			memset(&CheckIn,0,sizeof(CheckIn));
			CheckIn.dwUserID=pCheckIn->UserID;
			CheckIn.i64Count=pCheckIn->i64Count;
			m_SQLDataManage.PushLine(&CheckIn.DataBaseHead,sizeof(CheckIn),DTK_GR_CHECKIN_MONEY_INGAME,uIndex,dwHandleID);
			return true;

		}
	case ASS_GR_TRANSFER_SET_REBATE_RES:
		{
			return OnUserSetRebateRequest(pData,uSize,uIndex,dwHandleID);
		}
	case ASS_GR_TRANSFER_MONEY:			//ת��
		{
			//Ч������
			if (uSize!=sizeof(MSG_GR_S_TransferMoney)) return false;
			MSG_GR_S_TransferMoney * pTransferMoney=(MSG_GR_S_TransferMoney *)pData;

			//��������
			CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
			if (pUserInfo==NULL)
				return false;
			if(pTransferMoney->UserID != pUserInfo->m_UserData.dwUserID)
				return false;

			/// ����Լ�ת���Լ�
			if (pTransferMoney->UserID == pTransferMoney->destUserID)
			{
				return false;
			}

			//д�����ݿ�
			DL_GR_I_TransferMoney TransferMoney;
			memset(&TransferMoney,0,sizeof(TransferMoney));
			::memcpy(&TransferMoney.stTransfer,pTransferMoney,sizeof(MSG_GR_S_TransferMoney));
			//Ӧ����˰
			CString stime;
			stime.Format("%d",CTime::GetCurrentTime());        //��ǰ��ʱ�䣬String��ʽ
			int curtime=atoi(stime);                           //ת��Ϊint

			//if(pUserInfo->m_UserData.iVipTime>curtime)//vip����˰
			//	TransferMoney.stTransfer.uTax = 0;
			//else
			//	TransferMoney.stTransfer.uTax = TransferMoney.stTransfer.uMoney/10;

			TransferMoney.stTransfer.bTranTax = 1; ///< Ĭ������¶�ÿ��ת�˿�˰

			CBcfFile fConfig(CBcfFile::GetAppPath()+"Function.bcf");
			CString strBuffer = fConfig.GetKeyVal("SpecificID","Available","0");
			if (atoi(strBuffer)) ///< ָ���˺�ID
			{
				strBuffer = fConfig.GetKeyVal("SpecificID","NormalID","60000000,69999999");
				int reValue = TransferIDCompare(TransferMoney.stTransfer.UserID,TransferMoney.stTransfer.destUserID,
					atol(strBuffer.Left(strBuffer.Find(",")+1)),
					atol(strBuffer.Right(strBuffer.GetLength()-strBuffer.Find(",")-1)));

				switch (reValue)
				{
				case 0:
					return false; ///< ����ת��

				case 1:
					///< ����ת�ˣ���˰
					TransferMoney.stTransfer.bTranTax = 1;
					break;

				case 2:
					///< ����ת�ˣ�����˰
					TransferMoney.stTransfer.bTranTax = 2;
					break;

				case 3:
					///< ɢ����ת��
					TransferMoney.stTransfer.bTranTax = 3;
					break;

				default :
					break;
				}
			}

            // PengJiLin, 2010-8-23, ��ͨת�˻���ȫת���ܣ�1=ȫת
            TransferMoney.stTransfer.uHandleCode = pNetHead->bHandleCode;

			m_SQLDataManage.PushLine(&TransferMoney.DataBaseHead,sizeof(TransferMoney),DTK_GR_TRANSFER_MONEY,uIndex,dwHandleID);
			return true;
		}
	case ASS_GR_TRANSFER_MONEY_INGAME:	//��Ϸ��ת��
		{
			//Ч������
			if (uSize!=sizeof(MSG_GR_S_TransferMoney)) return false;
			MSG_GR_S_TransferMoney * pTransferMoney=(MSG_GR_S_TransferMoney *)pData;

			//��������
			CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
			if (pUserInfo==NULL)
				return false;
			if(pTransferMoney->UserID != pUserInfo->m_UserData.dwUserID)
				return false;

			/// ����Լ�ת���Լ�
			if (pTransferMoney->UserID == pTransferMoney->destUserID)
			{
				return false;
			}

			//д�����ݿ�
			DL_GR_I_TransferMoney TransferMoney;
			memset(&TransferMoney,0,sizeof(TransferMoney));
			::memcpy(&TransferMoney.stTransfer,pTransferMoney,sizeof(MSG_GR_S_TransferMoney));
			//Ӧ����˰
			CString stime;
			stime.Format("%d",CTime::GetCurrentTime());        //��ǰ��ʱ�䣬String��ʽ
			int curtime=atoi(stime);                           //ת��Ϊint

			//if(pUserInfo->m_UserData.iVipTime>curtime)//vip����˰
			//	TransferMoney.stTransfer.uTax = 0;
			//else
			//	TransferMoney.stTransfer.uTax = TransferMoney.stTransfer.uMoney/10;

			TransferMoney.stTransfer.bTranTax = 1; ///< Ĭ������¶�ÿ��ת�˿�˰

			CBcfFile fConfig(CBcfFile::GetAppPath()+"Function.bcf");
			CString strBuffer = fConfig.GetKeyVal("SpecificID","Available","0");
			if (atoi(strBuffer)) ///< ָ���˺�ID
			{
				strBuffer = fConfig.GetKeyVal("SpecificID","NormalID","60000000,69999999");
				int reValue = TransferIDCompare(TransferMoney.stTransfer.UserID,TransferMoney.stTransfer.destUserID,
					atol(strBuffer.Left(strBuffer.Find(",")+1)),
					atol(strBuffer.Right(strBuffer.GetLength()-strBuffer.Find(",")-1)));

				switch (reValue)
				{
				case 0:
					return false; ///< ����ת��

				case 1:
					///< ����ת�ˣ���˰
					TransferMoney.stTransfer.bTranTax = 1;
					break;

				case 2:
					///< ����ת�ˣ�����˰
					TransferMoney.stTransfer.bTranTax = 2;
					break;

				case 3:
					///< ɢ����ת��
					TransferMoney.stTransfer.bTranTax = 3;
					break;

				default :
					break;
				}
			}

			m_SQLDataManage.PushLine(&TransferMoney.DataBaseHead,sizeof(TransferMoney),DTK_GR_TRANSFER_MONEY_INGAME,uIndex,dwHandleID);
			return true;
		}
	case ASS_GR_CHANGE_PASSWD:
		{
			if (uSize != sizeof(MSG_GR_S_ChangePasswd_t))
			{
				 return false;
			}
			MSG_GR_S_ChangePasswd_t *pChangePasswd = (MSG_GR_S_ChangePasswd_t *)pData;

			/// �������ݣ��ҳ��û��������͵��ô洢���̵�ָ�������
			CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
			if (pUserInfo==NULL)
				return false;
			if(pChangePasswd->UserID != pUserInfo->m_UserData.dwUserID)
				return false;
			/// 
			DL_GR_I_ChangePasswd_t changePasswd;
			changePasswd.stChangePasswd.UserID = pUserInfo->m_UserData.dwUserID;
			_tcscpy(changePasswd.stChangePasswd.szMD5PassNew, pChangePasswd->szMD5PassNew);
			_tcscpy(changePasswd.stChangePasswd.szMD5PassOld, pChangePasswd->szMD5PassOld);
			m_SQLDataManage.PushLine(&changePasswd.DataBaseHead,sizeof(changePasswd),DTK_GR_CHANGE_PASSWD,uIndex,dwHandleID);

			return true;
		}
	case ASS_GR_TRANSFER_RECORD:
		{
			CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
			if (pUserInfo==NULL)
			{
				return false;
			}
			MSG_GR_S_TransferRecord_t *pTransferRecord = (MSG_GR_S_TransferRecord_t *)pData;
			/// ����û��������Լ����û�������ʧ��
			if (pUserInfo->m_UserData.dwUserID != pTransferRecord->dwUserID)
			{
				return false;
			}
			DL_GR_I_TransferRecord_t transferRecord;
			transferRecord.stTransfer.dwUserID = pUserInfo->m_UserData.dwUserID;
			m_SQLDataManage.PushLine(&transferRecord.DataBaseHead,sizeof(transferRecord),DTK_GR_TRANSFER_RECORD,uIndex,dwHandleID);
			/// "SP_GetTransferRecord"
			break;
		}
	case ASS_GR_TRANSFER_RECORD_INGAME:
		{
			CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
			if (pUserInfo==NULL)
			{
				return false;
			}
			MSG_GR_S_TransferRecord_t *pTransferRecord = (MSG_GR_S_TransferRecord_t *)pData;
			/// ����û��������Լ����û�������ʧ��
			if (pUserInfo->m_UserData.dwUserID != pTransferRecord->dwUserID)
			{
				return false;
			}
			DL_GR_I_TransferRecord_t transferRecord;
			transferRecord.stTransfer.dwUserID = pUserInfo->m_UserData.dwUserID;
			m_SQLDataManage.PushLine(&transferRecord.DataBaseHead,sizeof(transferRecord),DTK_GR_TRANSFER_RECORD_INGAME,uIndex,dwHandleID);
			/// "SP_GetTransferRecord"
			break;
		}
	}
	return true;
}

//��ҷ����޸�sdp
bool CGameMainManage::OnUserSetRebateRequest(void* pData,UINT uSize,UINT uIndex,DWORD dwHandleID)
{
	MSG_GR_UserRebateSetResult *pCmd=(MSG_GR_UserRebateSetResult*)pData;

	DL_GR_I_UserRebateSetStruct cmd;
	cmd.bTag = pCmd->bTag;
	cmd.iUserID = pCmd->iUserID;
	cmd.iMoney = pCmd->iMoney;

	m_SQLDataManage.PushLine(&cmd.DataBaseHead,sizeof(DL_GR_I_UserRebateSetStruct),
		DTK_GR_BANK_SET_USER_REBATE,uIndex,dwHandleID);

	CString sdp;
	sdp.Format("sdp_ ת�� ���� ���[����]�����޸� �������� ���ID=%d,ʣ�෵����Ŀ=%d[0��1ȡ(%d)]",cmd.iUserID,cmd.iMoney,cmd.bTag);
	OutputDebugString(sdp);

	return true;
}

/// ת���û�ID�Ƚ�
/// @param UserID ����Լ���ID��UserIDDestĿ��ID,ɢ��ID NomalIDFrom��ʼ��ɢ��ID NomalIDEnd����
///@return  0����ת�ˣ�1 ����ת��,��˰��2 ����ת��,����˰.3 ����ת�˶�Ϊ��ָ�������ת�˽��
int CGameMainManage::TransferIDCompare(long UserID,long UserIDDest,long NomalIDFrom,long NomalIDEnd)
{
	char BufID[12]     = {0};
	char BufIDDest[12] = {0};

	BOOL specificID     = TRUE;  ///< �Ƿ�ָ��ID��21111100 21111000���Լ���ID��
	BOOL specificIDDest = TRUE;  ///< �Ƿ�ָ��ID��21111100 21111000���Է���ID��
	BOOL sameNumID      = TRUE;  ///< �Ƿ�����ID��11111 444444���Լ���ID��
	BOOL sameNumIDDest  = TRUE;  ///< �Ƿ�����ID��11111 444444���Է���ID��
	BOOL sameID         = TRUE;  ///< ����ID�Ƿ���ͬ
	int CntZero         = 0;   ///< 0�ĸ���
	int CntZeroDest     = 0;   ///< 0�ĸ���
	int Len             = 0;   ///< ID����
	int LenDest         = 0;   ///< ID����
	int CntSame         = 0;   ///< �Լ�ID���Է�ID��ͬ�ĸ���

	if ((UserID>NomalIDFrom && UserID<NomalIDEnd) && (UserIDDest>NomalIDFrom && UserIDDest<NomalIDEnd))///< ɢ��
	{
		return 3;
	}

	if (UserID<NomalIDFrom && UserIDDest<NomalIDFrom)
	{
		sprintf(BufID,"%ld",UserID);
		sprintf(BufIDDest,"%ld",UserIDDest);

		for (int i=0; 0!=BufID[i] || 0!=BufIDDest[i]; i++)
		{
			if (0!=BufID[i])
			{
				if (specificID)
				{
					if ('0' == BufID[i])
					{
						CntZero++;
					}
					else if ('0' != BufID[i] && 0 != CntZero)
					{
						specificID = FALSE; ///< ����ָ��ID(���ǿͻ�ָ��ID)
					}

					if (i > 0 && BufID[0] != BufID[i] && sameNumID) ///< �Ƿ�����ID
					{
						sameNumID = FALSE;
					}
				}
				Len++;

				if (BufID[i] == BufIDDest[i] && sameID)
				{
					CntSame++;
				}
				else
				{
					sameID = FALSE;
				}
			}

			if (0!=BufIDDest[i])
			{
				if (specificIDDest)
				{
					if ('0' == BufIDDest[i])
					{
						CntZeroDest++;
					}
					else if ('0'!=BufIDDest[i] && 0!=CntZeroDest)
					{
						specificIDDest = FALSE; ///< ����ָ��ID(���ǿͻ�ָ��ID)
					}

					if (i > 0 && BufIDDest[0] != BufIDDest[i] && sameNumIDDest) ///< �Ƿ�����ID
					{
						sameNumIDDest = FALSE;
					}
				}
				LenDest++;
			}
		}

		char BufFromID[12] = {0};
		int  LenFromID     = 0;

		sprintf(BufFromID,"%ld",NomalIDFrom);
		LenFromID = strlen(BufFromID);
		if (LenFromID != LenDest) ///< ���Ȳ�������ָ��ID
		{
			specificIDDest = FALSE;
		}

		if (LenFromID != Len) ///< ���Ȳ�������ָ��ID
		{
			specificID = FALSE;
		}

		if (sameNumID && sameNumIDDest) ///< ����ID��������
		{
		//	if (Len>=LenDest && LenDest>4)
			if (Len>4 && LenDest>4) ///< ��������ID������໥ת��--�߻� ��
			{
				return 2;
			}
		}
		else if (sameNumID && Len>4 && !sameNumIDDest && specificIDDest) ///< �Լ�ID�����ţ��Է�ID��ָ���˺�
		{
			if (CntZeroDest < Len-1)
			{
				if (2 == Len-CntZeroDest)
				{
					if ('4' == BufIDDest[LenFromID-CntZeroDest-1])
					{
						return 0;
					}
				}

				if (CntZeroDest>0 || '4'==BufIDDest[LenFromID-1])
					return 2;
				else 
					return 1; ///< ����ת�˿�˰
			}
			else
			{
				return 0;
			}
		}
		else if (sameNumIDDest && LenDest>4 && !sameNumID && specificID) ///< �Է�������ID���Լ���ָ���˺�
		{
			if (CntZero < LenDest-1)
			{
				if (2 == LenDest-CntZero)
				{
					if ('4' == BufID[LenFromID-CntZero-1]) ///< ���Ǹ�ְ��������IDͬ�ȼ�
					{
						return 0;
					}
				}

				if (CntZero>0 || '4'==BufID[LenFromID-1])
					return 2;
				else
					return 2;
			}
			else ///< �Է�����С�����ļ��𣬲���ת�ˡ�
			{
				return 0;
			}
		}

		if (specificID && specificIDDest)
		{
			for (int i=Len-1; i>=CntSame; i--)
			{
				if ((BufID[i] != BufIDDest[i]) && CntSame == i)
				{
					if ('0' == BufID[i])///< ��ְ
					{
						if ('4' == BufIDDest[i]) ///< ��ְ��ְת��
						{
							return 2;
						}
						else ///< ���¼�
						{
							if (CntZeroDest > 0) ///< �ڼ�����ת��
								return 2;
							else
								return 1;
						}
					}
					else if ('4' == BufID[i]) ///< ��ְ
					{
						if ('0' == BufIDDest[i]) ///< ��ְ����ְת�ˣ�����˰
						{
							return 2;
						}
						else ///< ��ְ���¼�
						{
							if (CntZeroDest > 0) ///< �ڼ�����ת��
								return 2;
							else
								return 1;
						}
					}
					else
					{
						if ('0' == BufIDDest[i] || '4' == BufIDDest[i]) ///< ���ϼ�ת��
						{
							if (CntZero > 0) ///< �ڼ�����ת��
								return 2;
							else
								return 2; ///< �����ת�˲���˰ 2010 5.7 �޸�����;
						}
						else ///< ƽ��
						{
							if (Len-1 - CntSame) ///< ������ƽ��ת��
							{
								return 2;
							}
							else
							{
								return 0;
							}
						}
					}
				}
				else if (BufID[i] != BufIDDest[i] && CntSame != i)///< ����ͬһ�ϼ�
				{
					return 0;
				}
				else if (BufID[i]==BufIDDest[i] && '0'!=BufID[i])///< ����ͬһ�ϼ�
				{
					return 0;
				}
			}
		}
		else if (!specificID && !specificIDDest && specificID && specificIDDest)
		{
			return 3; ///< ���������ر�ID��ת�ˡ�
		}
		else ///< ����ת�ˡ�
		{
			return 0;
		}
	}

	///< ������ɢ��������֮��ת��
	int RetUserID;
	int RetUserIDDest;
	RetUserID = GetIDInformation(UserID,NomalIDFrom,NomalIDEnd);
	RetUserIDDest = GetIDInformation(UserIDDest,NomalIDFrom,NomalIDEnd);

	if (-1==RetUserID && RetUserIDDest<-1) ///< ɢ��������ת��
	{
		return 2; ///< ����˰
	}
	else if (RetUserID<-1 && -1==RetUserIDDest) ///< ���Ÿ�ɢ��ת��
	{
		return 1; ///< ��˰
	}

	return 0;
}

/// ��ȡ���ID��Ϣ���Ƿ�ɢ�����ر��˺ţ�ָ���˺�
/// @param UserID ���ID,NomalIDFromɢ��ID��ʼ��NomalIDEndɢ��ID����
/// @return 0��10��ָ���˺ź����0�ĸ�����-1Ϊɢ����-2Ϊ��Ч�˺ţ�-5Ϊ5���ţ�-6Ϊ6����
int CGameMainManage::GetIDInformation(long UserID,long NomalIDFrom,long NomalIDEnd)
{
	char BufID[12]     = {0};
	int CntZero        = 0;   ///< 0�ĸ���
	int len            = 0;
	BOOL sameNumID     = TRUE;  ///< �Ƿ�����ID��11111 444444���Լ���ID��

	if (UserID>NomalIDFrom && UserID<NomalIDEnd) ///< ɢ��
	{
		return -1;
	}

	if (UserID < NomalIDFrom)
	{
		sprintf(BufID,"%ld",UserID);

		for (int i=0; 0!=BufID[i]; i++)
		{
			if ('0'==BufID[i])
			{
				CntZero++;
			}
			else if ('0'!=BufID[i] && 0!=CntZero) ///< ��Ч�˺�
			{
				return -2;
			}
			
			if (i>0 && BufID[0]!=BufID[i] && sameNumID)
			{
				sameNumID = FALSE;
			}
			len++;
		}

		if (sameNumID) ///< ������ID
		{
			if (len >= 5)
				return -len;
			else
				return -2; ///< ��Ч�˺�
		}

		char BufIDFrom[12] = {0};
		sprintf(BufIDFrom,"%ld",NomalIDFrom);
		if (strlen(BufIDFrom) == len)
		{
			if ('4' == BufID[len-CntZero-1]) ///< ��ְ
			{
				return CntZero+1; ///< 4�ڵ�����CntZero+1λ
			}
			return CntZero;
		}
		else
			return -2; ///< ��Ч�˺�
	}

	return -2; ///< ��Ч�˺�
}

/// ��ȡĳ����Ϸ����ָ��
const CGameDesk* CGameMainManage::GetGameDesk(BYTE bDeskNo)
{
	if (bDeskNo >= m_uDeskCount || m_uDeskCount < 0)
	{
		return NULL;
	}

	return *(m_pDesk + bDeskNo);
}

/// ��ӡ����������ҵ���Ϣ
/// Added By JianGuankun 2011.12.5
void CGameMainManage::PrintUsersLog()
{
	CString strPath = CBcfFile::GetAppPath();
	//f.open("");

	TCHAR szPathName[MAX_PATH];
	TCHAR szPath[MAX_PATH];
	TCHAR szName[MAX_PATH];
	SYSTEMTIME t;

	memset(szPathName,NULL,MAX_PATH);
	::GetCurrentDirectory(MAX_PATH,szPath);
	::strcat(szPath,"\\wlogs");
	::CreateDirectory(szPath,NULL);

	::GetLocalTime(&t);

	//�γ���־ID
	wsprintf(szName,TEXT("%03d_%02d%02d_%02d%02d%02d"),m_InitData.uRoomID,
		t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond);


	wsprintf(szPathName,TEXT("%s\\%s.log"),szPath,szName);

	CFile f;
	if (!f.Open(szPathName,CFile::modeReadWrite|CFile::modeCreate|CFile::modeNoTruncate))
	{
		return;
	}

	//�����־ͷ
	CString strOutput;
	strOutput.Format("��־: ����ID = %d ʱ�� = %02d.%02d %02d:%02d:%02d"
		,m_InitData.uRoomID,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond);
	Writeline(&f,strOutput);

	Writeline(&f,"===============================================================================================================");

	Writeline(&f,"");

	strOutput.Format("������������%d",m_UserManage.m_uOnLineCount);
	Writeline(&f,strOutput);

	Writeline(&f,"");

	CAFCPtrArray<CGameUserInfo>* pUserList = &m_UserManage.m_OnLineUserInfo;

	strOutput.Format("--��������б�--------------------------------------------------------------------------------------------------------",
		pUserList->GetPermitCount());
	Writeline(&f,strOutput);

	Writeline(&f,"");

	int uFindCount = 0;

	for (int i = 0; i < pUserList->GetPermitCount(); ++i)
	{
		CGameUserInfo* pUserInfo = pUserList->GetArrayItem(i);
		if (pUserInfo)
		{
			strOutput.Format("  ID:%-9d Name:%-20s NickName:%-30s Access = %1d Network = (%05d,%05d) Station = (%03d,%03d,%03d)",
				pUserInfo->m_UserData.dwUserID,pUserInfo->m_UserData.szName,pUserInfo->m_UserData.nickName,pUserInfo->m_bAccess,
				pUserInfo->m_uSocketIndex,pUserInfo->m_dwHandleID,
				pUserInfo->m_UserData.bDeskNO,pUserInfo->m_UserData.bDeskStation,pUserInfo->m_UserData.bUserState);
			Writeline(&f,strOutput);
			if (pUserInfo->IsAccess())
			{
				uFindCount++;
			}
		}
	}

	Writeline(&f,"");
	strOutput.Format("--(��%d��)--",uFindCount);
	Writeline(&f,strOutput);
	Writeline(&f,"");

	pUserList = &m_UserManage.m_NetCutUserInfo;

	strOutput.Format("--��������б�--------------------------------------------------------------------------------------------------------",
		pUserList->GetPermitCount());
	Writeline(&f,strOutput);

	Writeline(&f,"");

	uFindCount = 0;

	for (int i = 0; i < pUserList->GetPermitCount(); ++i)
	{
		CGameUserInfo* pUserInfo = pUserList->GetArrayItem(i);
		if (pUserInfo)
		{
			strOutput.Format("  ID:%-9d Name:%-20s NickName:%-30s Access = %1d Network = (%05d,%05d) Station = (%03d,%03d,%03d)",
				pUserInfo->m_UserData.dwUserID,pUserInfo->m_UserData.szName,pUserInfo->m_UserData.nickName,pUserInfo->m_bAccess,
				pUserInfo->m_uSocketIndex,pUserInfo->m_dwHandleID,
				pUserInfo->m_UserData.bDeskNO,pUserInfo->m_UserData.bDeskStation,pUserInfo->m_UserData.bUserState);
			Writeline(&f,strOutput);
			if (pUserInfo->IsAccess())
			{
				uFindCount++;
			}
		}
	}

	Writeline(&f,"");
	strOutput.Format("--(��%d��)--",uFindCount);
	Writeline(&f,strOutput);

	Writeline(&f,"");
	Writeline(&f,"ע�ͣ�ID,Name,NickName,Access,Network = (SocketIndex,HandleCode),Station = (DeskNO,DeskStation,UserState)");
	Writeline(&f,"");

	f.Close();

	return;
}

//д��־
bool CGameMainManage::Writeline(CFile* p,CString str)
{
	if (p == NULL)
	{
		return false;
	}

	p->Write(str.GetBuffer(),str.GetLength());
	p->Write(_TEXT("\r\n"),2);

	return true;
}


//������Ϣ����
bool CGameMainManage::OnManageMessage(NetMessageHead * pNetHead, void * pData, UINT uSize, ULONG uAccessIP, UINT uIndex, DWORD dwHandleID)
{
	ASSERT(pNetHead->bMainID==MDM_GR_MANAGE);
	switch (pNetHead->bAssistantID)
	{
	case ASS_GR_ALONE_DESK://����
		{	
			if(uSize!=sizeof(MSG_GR_SR_MatchDelete)) return false;
			MSG_GR_SR_MatchDelete *aloneDesk=(MSG_GR_SR_MatchDelete*) pData;
			CGameDesk * pDesk=*(m_pDesk+aloneDesk->bDeskIndex);
			//if(aloneDesk->bDeskStation==1) pDesk->LockDesk();  
			if(aloneDesk->bDeskStation==1) pDesk->VirtualLockDesk();//yjj 090325

			//wushuqun 2009.6.6
			//��ʱ��������
			if (pDesk)
			{
				DL_GR_I_ALone_Data aloneDeskData;
				memset(& aloneDeskData,0,sizeof(aloneDeskData));
				//����������
				aloneDeskData.bDeskIndex = pDesk->m_bDeskIndex;
				//������ʶ
				aloneDeskData.bDeskStation = aloneDesk->bDeskStation;
				//��������������
				aloneDeskData.bDeskPeople = pDesk->m_bMaxPeople;
				//����ID��
				aloneDeskData.uRoomID = pDesk->m_pDataManage->m_InitData.uRoomID;
				//д���ݿ��¼
				m_SQLDataManage.PushLine(&aloneDeskData.DataBaseHead,sizeof(aloneDeskData),DTR_GR_ALONEDESK_INTIME,uIndex,dwHandleID);
			}
			m_TCPSocket.SendDataBatch(NULL,0,MDM_GR_DESK,aloneDesk->bDeskIndex,aloneDesk->bDeskStation);
			return true;

		}
	case ASS_GR_DEALONE_DESK://
		{
			if(uSize!=sizeof(MSG_GR_SR_MatchDelete)) return false;
			MSG_GR_SR_MatchDelete *aloneDesk=(MSG_GR_SR_MatchDelete*) pData;
			CGameDesk * pDesk=*(m_pDesk+aloneDesk->bDeskIndex);
			//if(aloneDesk->bDeskStation==2) pDesk->UnlockDesk();  
			if(aloneDesk->bDeskStation==2) pDesk->UnVirtualLockDesk();//yjj 090325

			//wushuqun 2009.6.6
			//��ʱ���������
			if (pDesk)
			{
				DL_GR_I_ALone_Data aloneDeskData;
				memset(& aloneDeskData,0,sizeof(aloneDeskData));
				//����������
				aloneDeskData.bDeskIndex = pDesk->m_bDeskIndex;
				//������ʶ
				aloneDeskData.bDeskStation = aloneDesk->bDeskStation;
				//��������������,�����ʱ������Ϊ��
				aloneDeskData.bDeskPeople =  pDesk->m_bMaxPeople;

				aloneDeskData.bDeskPeople = -aloneDeskData.bDeskPeople;
				//����ID��
				aloneDeskData.uRoomID = pDesk->m_pDataManage->m_InitData.uRoomID;
				//д���ݿ��¼
				m_SQLDataManage.PushLine(&aloneDeskData.DataBaseHead,sizeof(aloneDeskData),DTR_GR_ALONEDESK_INTIME,uIndex,dwHandleID);
			}

			m_TCPSocket.SendDataBatch(NULL,0,MDM_GR_DESK,aloneDesk->bDeskIndex,aloneDesk->bDeskStation);
			return true;
		}
	case ASS_GR_WARN_MSG:			//������Ϣ
		{
			//Ч������
			MSG_GR_SR_Warning * pWarningUser=(MSG_GR_SR_Warning *)pData;
			if ((uSize<=(sizeof(MSG_GR_SR_Warning)-sizeof(pWarningUser->szWarnMsg)))||(uSize>sizeof(MSG_GR_SR_Warning))) return false;
			//if ((pWarningUser->uLength+1)!=(uSize+sizeof(pWarningUser->szWarnMsg)-sizeof(MSG_GR_SR_Warning))) return false;

			//��������
			CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
			if ((pUserInfo==NULL)||(CUserPower::CanSendWarning(pUserInfo->m_dwMasterPower)==false)) return false;
			CGameUserInfo * pTargetUserInfo=m_UserManage.FindOnLineUser(pWarningUser->dwTargetID);
			if (pTargetUserInfo==NULL) return true;
			pWarningUser->szWarnMsg[pWarningUser->uLength]=0;

			//��������
			m_TCPSocket.SendData(pTargetUserInfo->m_uSocketIndex,pWarningUser,uSize,MDM_GR_MANAGE,ASS_GR_WARN_MSG,0,pTargetUserInfo->m_dwHandleID);

			//д�����ݿ�
			DL_GR_I_Warn_User_Record WarningUserRecord;
			memset(&WarningUserRecord,0,sizeof(WarningUserRecord));
			WarningUserRecord.dwGMID=pUserInfo->m_UserData.dwUserID;
			WarningUserRecord.dwTargetID=pWarningUser->dwTargetID;
			lstrcpy(WarningUserRecord.szWarnMsg,pWarningUser->szWarnMsg);
			m_SQLDataManage.PushLine(&WarningUserRecord.DataBaseHead,sizeof(WarningUserRecord),DTK_GR_GM_WARNING_USER_RECORD,uIndex,dwHandleID);
			return true;
		}
	case ASS_GR_CUT_USER:			//���û�����//��ȫ����û���Ϸ
		{
			//Ч������
			if (uSize!=sizeof(MSG_GR_S_CutUser)) return false;
			MSG_GR_S_CutUser * pCutUser=(MSG_GR_S_CutUser *)pData;

			//��������
			CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
			if ((pUserInfo==NULL)||(CUserPower::CanCutUser(pUserInfo->m_dwMasterPower)==false)) return false;
			CGameUserInfo * pTargetUserInfo=m_UserManage.FindOnLineUser(pCutUser->dwTargetID);
			if (pTargetUserInfo==NULL) return true;

			//��������
			if (CUserPower::CanHideAction(pUserInfo->m_dwMasterPower)==true)
				pCutUser->dwUserID=0L;
			else 
				pCutUser->dwUserID=pUserInfo->m_UserData.dwUserID;
			if(pNetHead->bHandleCode==0)//���û�����
				m_TCPSocket.SendData(pTargetUserInfo->m_uSocketIndex,MDM_GR_MANAGE,ASS_GR_CUT_USER,0,pTargetUserInfo->m_dwHandleID);
			else if(pNetHead->bHandleCode==1)//��ȫ����û���Ϸ
				m_TCPSocket.SendData(pTargetUserInfo->m_uSocketIndex,MDM_GR_MANAGE,ASS_GR_CUT_USER,1,pTargetUserInfo->m_dwHandleID);

			//д�����ݿ�
			DL_GR_I_Kick_User_Record DT_KickUserRecord;
			memset(&DT_KickUserRecord,0,sizeof(DT_KickUserRecord));
			lstrcpy(DT_KickUserRecord.szTargetUserName,pTargetUserInfo->m_UserData.szName);
			DT_KickUserRecord.GMID=pUserInfo->m_UserData.dwUserID;
			m_SQLDataManage.PushLine(&DT_KickUserRecord.DataBaseHead,sizeof(DT_KickUserRecord),DTK_GR_GM_KICK_USER_RECORD,uIndex,dwHandleID);
			return true;
		}
	case ASS_GR_POWER_SET://����Ȩ��
		{
			//Ч������
			if (uSize!=sizeof(MSG_GR_SR_GamePowerSet)) return false;
			MSG_GR_SR_GamePowerSet * pPowerSet=(MSG_GR_SR_GamePowerSet *)pData;

			//��������
			CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
			if ((pUserInfo==NULL)||(pUserInfo->m_dwMasterPower==0L)) return false;
			CGameUserInfo * pTargetUserInfo=m_UserManage.FindOnLineUser(pPowerSet->dwUserID);
			if (pTargetUserInfo!=NULL)
			{
				//����Ȩ��
				CUserPower::SetCanRoomTalk(pTargetUserInfo->m_dwGamePower,CUserPower::CanRoomTalk(pPowerSet->dwGamePowerID));
				CUserPower::SetCanGameTalk(pTargetUserInfo->m_dwGamePower,CUserPower::CanGameTalk(pPowerSet->dwGamePowerID));
				CUserPower::SetCanSendMessage(pTargetUserInfo->m_dwGamePower,CUserPower::CanSendMessage(pPowerSet->dwGamePowerID));
				CUserPower::SetCanWatchGame(pTargetUserInfo->m_dwGamePower,CUserPower::CanWatchGame(pPowerSet->dwGamePowerID));
				CUserPower::SetCanPlayGame(pTargetUserInfo->m_dwGamePower,CUserPower::CanPlayGame(pPowerSet->dwGamePowerID));
				CUserPower::SetCanLimiteIP(pTargetUserInfo->m_dwGamePower,CUserPower::CanLimiteIP(pPowerSet->dwGamePowerID));

				//��������
				pPowerSet->dwGamePowerID=pTargetUserInfo->m_dwGamePower;
				pPowerSet->dwMasterPowerID=pTargetUserInfo->m_dwMasterPower;
				m_TCPSocket.SendData(pTargetUserInfo->m_uSocketIndex,pPowerSet,sizeof(MSG_GR_SR_GamePowerSet),MDM_GR_MANAGE,ASS_GR_POWER_SET,
					RES_GR_GAME_POWER_SET_RETURN,pTargetUserInfo->m_dwHandleID);

				//д�����ݿ�
				DL_GR_I_PowerSet DT_PowerSet;
				memset(&DT_PowerSet,0,sizeof(DT_PowerSet));
				DT_PowerSet.dwGMID=pUserInfo->m_UserData.dwUserID;
				DT_PowerSet.dwGamePower=pTargetUserInfo->m_dwGamePower;
				DT_PowerSet.dwMasterPower=pTargetUserInfo->m_dwMasterPower;
				DT_PowerSet.dwUserID=pPowerSet->dwUserID;
				DT_PowerSet.uLockTime=pPowerSet->uLockTime;
				DT_PowerSet.bBindKind = pPowerSet->bBindKind;
				m_SQLDataManage.PushLine(&DT_PowerSet.DataBaseHead,sizeof(DT_PowerSet),DTK_GR_GAME_POWER,uIndex,dwHandleID);
			}
			return true;
		}
	case ASS_GR_CALL_GM://����GM
		{
			//Ч������
			if (uSize!=sizeof(MSG_GR_Call_GM)) return false;
			MSG_GR_Call_GM * pcallGM=(MSG_GR_Call_GM *)pData;

			//��������
			CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
			if (pUserInfo==NULL) return false;
			DL_GR_I_CallGM dl_callGM;
			dl_callGM.dwUserID=pUserInfo->m_UserData.dwUserID;
			lstrcpy(dl_callGM.szName,pUserInfo->m_UserData.szName);
			dl_callGM.uDeskNO=pUserInfo->m_UserData.bDeskNO;
			dl_callGM.uDeskStation=pUserInfo->m_UserData.bDeskStation;
			dl_callGM.bCallReason=pcallGM->bCallReason;
			dl_callGM.szMsg[pcallGM->uLength]=0;
			lstrcpy(dl_callGM.szMsg,pcallGM->szMsg);
			m_SQLDataManage.PushLine(&dl_callGM.DataBaseHead,sizeof(dl_callGM),DTK_GR_CALL_GM,uIndex,dwHandleID);
			return true;
		}
	case ASS_GR_GRM_SET://��������������޸���Ϣ sdp2014-05-20
		{
			//Ч������
			if (uSize!=sizeof(MSG_GR_GRM_Set)) 
				return false;
			MSG_GR_GRM_Set * pCmd = (MSG_GR_GRM_Set *)pData;

			//������������� sdp2014-05-20
			CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
			if (pUserInfo==NULL) return false;

			if (!IsExistGRMUserID(pCmd->dwUserID) || !IsExistGRMRoom(m_uNameID))
			{
				//���ͽ����Ϣ���ͻ���
				m_TCPSocket.SendData(uIndex,pCmd,sizeof(MSG_GR_GRM_Set),MDM_GR_MANAGE,ASS_GR_GRM_SET_RES,RES_GR_GRM_SET_RES_ERR3,0);
				return true;
			}

			//�������ݽ����޸�
			//��������
			CString s = CINIFile::GetAppPath ();/////����·��
			CString temp = _T("");
			CString key;
			key.Format("%s",GRM_SET_KEY);
			temp.Format("%s%d_s.ini",s,m_uNameID);
			CINIFile f(temp);
			CString sTemp;

			bool bResult_Success = RES_GR_GRM_SET_RES_SUC;//�������

			CString sdp;
			sdp.Format("sdp_ GRM S �յ� ��������������޸���Ϣ-------%d", pCmd->bAIWinAndLostAutoCtrl);
			OutputDebugString(sdp);

			if (pCmd->bAIWinAndLostAutoCtrl)//���ƽ���
			{
				//֪ͨ��Ϸ������޸�
				//֪ͨ������������Ϸ������޸�

				for (UINT i=0;i<m_uDeskCount;i++)
				{
					if (!(*(m_pDesk+i))->SetRoomPond(1)
						|| !(*(m_pDesk+i))->SetRoomPondEx(pCmd->iAIWantWinMoney, pCmd->iAIWinLuckyAt))
					{
						//���ͽ����Ϣ���ͻ���
						m_TCPSocket.SendData(uIndex,pCmd,sizeof(MSG_GR_GRM_Set),MDM_GR_MANAGE,ASS_GR_GRM_SET_RES,RES_GR_GRM_SET_RES_ERR1,0);
						return true;
					}
				}


				//���������˿�����Ӯ���ء�д�������ļ�����
				sTemp.Format("%d",pCmd->bAIWinAndLostAutoCtrl);
				f.SetKeyValString(key,"AIWinAndLostAutoCtrl",sTemp);

				//�������û������Ѿ�ӮǮ����Ŀ��д�������ļ�����
				sTemp.Format("%I64d",pCmd->iReSetAIHaveWinMoney);
				f.SetKeyValString(key,"ReSetAIHaveWinMoney",sTemp);

				//����������ӮǮ����1,2,3 4���öϵ㡿д�������ļ�����
				sTemp.Format("%I64d",pCmd->iAIWantWinMoney[0]);
				f.SetKeyValString(key,"AIWantWinMoneyA1",sTemp);
				sTemp.Format("%I64d",pCmd->iAIWantWinMoney[1]);
				f.SetKeyValString(key,"AIWantWinMoneyA2",sTemp);
				sTemp.Format("%I64d",pCmd->iAIWantWinMoney[2]);
				f.SetKeyValString(key,"AIWantWinMoneyA3",sTemp);

				//����������������1,2,3,4ӮǮ�ĸ��ʡ�д�������ļ�����
				sTemp.Format("%d",pCmd->iAIWinLuckyAt[0]);
				f.SetKeyValString(key,"AIWinLuckyAtA1",sTemp);
				sTemp.Format("%d",pCmd->iAIWinLuckyAt[1]);
				f.SetKeyValString(key,"AIWinLuckyAtA2",sTemp);
				sTemp.Format("%d",pCmd->iAIWinLuckyAt[2]);
				f.SetKeyValString(key,"AIWinLuckyAtA3",sTemp);
				sTemp.Format("%d",pCmd->iAIWinLuckyAt[3]);
				f.SetKeyValString(key,"AIWinLuckyAtA4",sTemp);
			}
			else//�����ƽ���
			{
				//֪ͨ������������Ϸ������޸�
				for (UINT i=0;i<m_uDeskCount;i++)
				{
					if (!(*(m_pDesk+i))->SetRoomPond(0))
					{
						//���ͽ����Ϣ���ͻ���
						m_TCPSocket.SendData(uIndex,pCmd,sizeof(MSG_GR_GRM_Set),MDM_GR_MANAGE,ASS_GR_GRM_SET_RES,RES_GR_GRM_SET_RES_ERR1,0);
						return true;
					}
				}

				//���������˿�����Ӯ���ء�д�������ļ�����
				sTemp.Format("%d",pCmd->bAIWinAndLostAutoCtrl);
				f.SetKeyValString(key,"AIWinAndLostAutoCtrl",sTemp);
			}

			//�����Ӯ��������
			if (pCmd->bWinProbCtrl)
			{
				//��Ϸ��ʼ��ʱ����Ϸ���ȡ�����ļ����Դ˴�����֪ͨ��Ϸ
				CString sTemp2;
				key.Format("%s",GRM_SET_KEY_WIN);
				sTemp.Format("%d",20);
				f.SetKeyValString(key,"count",sTemp);
				for (int i = 0; i < 20; ++i)
				{
					if (pCmd->dwUserID_win[i] <= 0)
					{
						//���������˿�����Ӯ���ء�д�������ļ�����
						sTemp.Format("%ld",0);
						sTemp2.Format("UserID%d",i);
						f.SetKeyValString(key,sTemp2,sTemp);
						sTemp.Format("%d",0);
						sTemp2.Format("prob%d",i);
						f.SetKeyValString(key,sTemp2,sTemp);
					}
					else
					{
						//���������˿�����Ӯ���ء�д�������ļ�����
						sTemp.Format("%ld",pCmd->dwUserID_win[i]);
						sTemp2.Format("UserID%d",i);
						f.SetKeyValString(key,sTemp2,sTemp);
						sTemp.Format("%d",pCmd->iProb_win[i]);
						sTemp2.Format("prob%d",i);
						f.SetKeyValString(key,sTemp2,sTemp);
					}
				}
				key.Format("%s",GRM_SET_KEY_LOS);
				sTemp.Format("%d",20);
				f.SetKeyValString(key,"count",sTemp);
				for (int i = 0; i < 20; ++i)
				{
					if (pCmd->dwUserID_los[i] <= 0)
					{
						//���������˿�����Ӯ���ء�д�������ļ�����
						sTemp.Format("%ld",0);
						sTemp2.Format("UserID%d",i);
						f.SetKeyValString(key,sTemp2,sTemp);
						sTemp.Format("%d",0);
						sTemp2.Format("prob%d",i);
						f.SetKeyValString(key,sTemp2,sTemp);
					}
					else
					{
						//���������˿�����Ӯ���ء�д�������ļ�����
						sTemp.Format("%ld",pCmd->dwUserID_los[i]);
						sTemp2.Format("UserID%d",i);
						f.SetKeyValString(key,sTemp2,sTemp);
						sTemp.Format("%d",pCmd->iProb_los[i]);
						sTemp2.Format("prob%d",i);
						f.SetKeyValString(key,sTemp2,sTemp);
					}
				}
			}
			else
			{
				key.Format("%s",GRM_SET_KEY_WIN);
				sTemp.Format("%d",0);
				f.SetKeyValString(key,"count",sTemp);
				key.Format("%s",GRM_SET_KEY_LOS);
				sTemp.Format("%d",0);
				f.SetKeyValString(key,"count",sTemp);
			}

			/////////////////////////////
			sdp.Format("sdp_ GRM S ���� ��������������޸���Ϣ��");
			OutputDebugString(sdp);

			//���ͽ����Ϣ���ͻ���
			m_TCPSocket.SendData(uIndex,pCmd,sizeof(MSG_GR_GRM_Set),MDM_GR_MANAGE,ASS_GR_GRM_SET_RES,bResult_Success,0);

			return true;
		}
	case ASS_GR_GRM_UPDATA:
		{
			CString sdp;
			sdp.Format("sdp_ GRM S �յ� ������������ݸ�����Ϣ��");
			OutputDebugString(sdp);

			SendRoomPondUpDataALL();
			return true;
		}
	}
	return false;
}

//֪ͨ����Ա�ͻ��˽����Ѿ�����
void CGameMainManage::SendRoomPondUpData(__int64 iAIHaveWinMoney)
{
	MSG_GR_GRM_UpData cmd;
	cmd.iAIHaveWinMoney = iAIHaveWinMoney;

	for (int i = 0; i < m_UserManage.m_OnLineUserInfo.GetPermitCount(); ++i)
	{
		CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(i);
		if (pUserInfo == NULL) 
			continue;

		if (IsExistGRMUserID(pUserInfo->m_UserData.dwUserID))
		{
			//���ͽ��ظ�����Ϣ���ͻ���
			m_TCPSocket.SendData(pUserInfo->m_uSocketIndex, &cmd,sizeof(MSG_GR_GRM_UpData),MDM_GR_MANAGE, ASS_GR_GRM_UPDATA, RES_GR_GRM_UP1, 0);
		}
	}

	return;
}

//֪ͨ����Ա�ͻ�����������
void CGameMainManage::SendRoomPondUpDataALL()
{
	MSG_GR_GRM_UpData cmd;
	CString s = CINIFile::GetAppPath ();/////����·��
	CString temp;
	temp.Format("%s%d_s.ini",s,m_uNameID);
	CINIFile f( temp);
	CString key;
	key.Format("%s",GRM_SET_KEY);
	cmd.bAIWinAndLostAutoCtrl = f.GetKeyVal(key,"AIWinAndLostAutoCtrl",0);
	cmd.iAIHaveWinMoney = f.GetKeyVal(key,"AIHaveWinMoney ",__int64(0));
	cmd.iReSetAIHaveWinMoney	= f.GetKeyVal(key,"ReSetAIHaveWinMoney ",__int64(0)); 

	cmd.iAIWantWinMoney[0]	= f.GetKeyVal(key,"AIWantWinMoneyA1 ",__int64(500000));
	cmd.iAIWantWinMoney[1]	= f.GetKeyVal(key,"AIWantWinMoneyA2 ",__int64(5000000));
	cmd.iAIWantWinMoney[2]	= f.GetKeyVal(key,"AIWantWinMoneyA3 ",__int64(50000000));
	cmd.iAIWinLuckyAt[0]	= f.GetKeyVal(key,"AIWinLuckyAtA1 ",90);
	cmd.iAIWinLuckyAt[1]	= f.GetKeyVal(key,"AIWinLuckyAtA2 ",70);
	cmd.iAIWinLuckyAt[2]	= f.GetKeyVal(key,"AIWinLuckyAtA3 ",50);
	cmd.iAIWinLuckyAt[3]	= f.GetKeyVal(key,"AIWinLuckyAtA4 ",30);

	//��Ӯ���ʿ���
	cmd.bWinProbCtrl = false;
	key.Format("%s",GRM_SET_KEY_WIN);//Ӯ���ͳ��
	int count = f.GetKeyVal(key,"count",0);
	if(count > 0 )
	{		
		cmd.bWinProbCtrl = true;
	}

	TCHAR szName[21];
	int probability = 0;
	long int dwUserID = 0;			///ID ����

	for(int i = 0; i < 20; i ++)
	{
		wsprintf(szName,"UserID%d",i);
		cmd.dwUserID_win[i] = f.GetKeyVal(key,szName,0);

		wsprintf(szName,"prob%d",i);
		cmd.iProb_win[i] = f.GetKeyVal(key,szName,0);
	}

	key.Format("%s",GRM_SET_KEY_LOS);//�����ͳ��
	count = f.GetKeyVal(key,"count",0);
	if(count > 0 )
	{
		cmd.bWinProbCtrl = true;
	}

	probability = 0;
	dwUserID = 0;			///ID ����

	for(int i = 0; i < 20; i ++)
	{
		wsprintf(szName,"UserID%d",i);
		cmd.dwUserID_los[i] = f.GetKeyVal(key,szName,0);

		wsprintf(szName,"prob%d",i);
		cmd.iProb_los[i] = f.GetKeyVal(key,szName,0);
	}

	for (int i = 0; i < m_UserManage.m_OnLineUserInfo.GetPermitCount(); ++i)
	{
		CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(i);
		if (pUserInfo == NULL) 
			continue;

		if (IsExistGRMUserID(pUserInfo->m_UserData.dwUserID))
		{
			//���ͽ��ظ�����Ϣ���ͻ���
			m_TCPSocket.SendData(pUserInfo->m_uSocketIndex, &cmd,sizeof(MSG_GR_GRM_UpData),MDM_GR_MANAGE, ASS_GR_GRM_UPDATA, RES_GR_GRM_UP2, 0);
		}
	}

	return;
}

//����д���
bool CGameMainManage::OnPointMessage(NetMessageHead * pNetHead, void * pData, UINT uSize, ULONG uAccessIP, UINT uIndex, DWORD dwHandleID)
{
	switch (pNetHead->bAssistantID)
	{
	case ASS_GR_OPEN_POINT:
		{
			DL_GR_I_OpenPoint op;
			CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
			if (pUserInfo==NULL)
				return false;			
			op.dwUserID = pUserInfo->m_UserData.dwUserID;
			m_SQLDataManage.PushLine(&op.DataBaseHead,sizeof(op),DTK_GR_OPEN_POINT,uIndex,dwHandleID);
		}
		return true;
	case ASS_GR_GET_POINT:
		{
			DL_GR_I_GetPoint getpoint;
			CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
			if (pUserInfo==NULL)
				return false;	
			if(uSize != sizeof(MSG_GR_S_GetPoint))
				return false;
			MSG_GR_S_GetPoint *pGetPoint = (MSG_GR_S_GetPoint *)pData;
			getpoint.dwUserID = pUserInfo->m_UserData.dwUserID;
			getpoint.dwsrcPoint = pUserInfo->m_UserData.dwPoint;
			getpoint.dwPoint = pGetPoint->dwPoint;
			m_SQLDataManage.PushLine(&getpoint.DataBaseHead,sizeof(getpoint),DTK_GR_GET_POINT,uIndex,dwHandleID);
		}
		return true;
	}
	return false;
}

//���Ѵ���
bool CGameMainManage::OnFriendManageMsg(NetMessageHead *pNetHead, void* pData, UINT uSize, ULONG uAccessIP, UINT uIndex, DWORD dwHandleID)
{
	CGameUserInfo * pSenderUserInfo = m_UserManage.GetOnLineUserInfo(uIndex);
	if (pSenderUserInfo == NULL) 
		return false;
	return true;
}

//�ŶӴ���
bool CGameMainManage::OnQueueMsg(NetMessageHead *pNetHead, void* pData, UINT uSize, ULONG uAccessIP, UINT uIndex, DWORD dwHandleID)
{
	ASSERT(pNetHead->bMainID == MDM_GR_QUEUE_MSG);
	switch(pNetHead->bAssistantID)//�Ŷ���Ϣ����
	{
	case ASS_GR_ADD_QUEUE://�����Ŷ�
		MSG_GR_Queue stQueue;
		memset(&stQueue,0,sizeof(stQueue));
		m_TCPSocket.SendData(uIndex,&stQueue,sizeof(stQueue),MDM_GR_QUEUE_MSG,ASS_GR_ADD_QUEUE_RESULT,0,0);
		break;
	case ASS_GR_AGREE_PLAN_SIT://ͬ������(ϵͳ������λ)
		break;
	case ASS_GR_REFUSE_PLAN_SIT://��ͬ����ĳλ����
		break;
	}
	return true;
}

bool CGameMainManage::IsContestGameOver()
{
	
	if (!(m_InitData.dwRoomRule & GRR_CONTEST) && !(m_InitData.dwRoomRule & GRR_TIMINGCONTEST))
		return false;
	//�����û��ʼ�������򲻴����Ƿ����������˵��
	
	if (1 != m_InitData.iRoomState)
		return false;
	
	int iRemainPeople = 0;
	if (m_pIAutoAllotDesk)
	{
		iRemainPeople = m_pIAutoAllotDesk->GetQueueUserCount();
		
	}
	CString str;
	str.Format("cq::��ǰ����=%d,��������=%d", iRemainPeople, m_InitData.iLeasePeople);
	OutputDebugString(str);
	//�жϱ����Ƿ�����������ǣ������������е���������ָ������ʱ����������
	if (iRemainPeople <= m_InitData.iLeasePeople)
	{
		
		KillTimer(IDT_QUEUE_GAME);
		AutoAllotDeskDeleteAll();
		//�ж��Ƿ����û�����Ϸ��
		int nDeskNo = 0;
		CGameDesk* pGameDesk = NULL;
		bool bResetState = true;
		while(nDeskNo < m_InitData.uDeskCount)
		{
			pGameDesk=*(m_pDesk+nDeskNo++);
			if (pGameDesk != NULL && pGameDesk->IsPlayingByGameStation())
			{
				bResetState = false;
				break;
			}
		}
		if (bResetState)
		{
			OutputDebugString("cq::---------------��������----------------------------");			
			m_InitData.iRoomState = 0;
			//�����ݿⷢ�ͱ���������Ϣ�������������
			DL_GR_I_UserContestRank _p;//�˲���������
			m_SQLDataManage.PushLine(&_p.DataBaseHead,sizeof(DL_GR_I_UserContestRank),DTK_GR_CONTEST_GAME_OVER,0,0);			
		}
		return true;
	}
	if (0 == m_iResetTime)
	{//��m_iQueueTimeָ����ʱ���ڣ�������������ӽ�����������ŵ�ͬһ��ʱ��������������֮�����ø��ж�����������һ��ʹ��
		m_iResetTime = 1;
		
		SetTimer(IDT_QUEUE_GAME, m_iQueueTime*1000);
		
	}
	return false;
}

bool CGameMainManage::IsLeaseTimeOver()
{
	if (m_InitData.iLeaseID != 0)
	{
		CTime _t = CTime::GetCurrentTime();
		if (_t.GetTime() > m_InitData.i64LeaseTimeEnd) return true;
	}
	return false;
}

///�Ŷӻ�����
void CGameMainManage::queuerGame()
{
    static int* pArray = NULL;
		
	if (IsLeaseTimeOver()) return;

    // PengJiLin, 2010-5-20
    if(m_pGameUserInfoList.size() < m_uQueuerMaxPeople) return;    
    if(NULL == pArray) pArray = new int [m_uQueuerMaxPeople];

	int iDeskIndex = -1;						//��������
	int iDeskStation = 0;						//��λ����
	int iADeskPlayerNum = 0;					//�����е�����
	bool isGameing = false;						//�����Ƿ�ʼ��Ϸ��
	//bool isADeskGameBegin = false;				//�Ƿ��������Ŷӳɹ�������ʼ��Ϸ��
	BYTE bErrorCode=ERR_GR_ERROR_UNKNOW;
	
	CGameUserInfo* pGameUserInfo = NULL;
	CGameDesk* pGameDesk = NULL;
	
	list<CGameUserInfo*> tempList;				//����ԭ�����Ŷ�list
	list<CGameUserInfo*> sitdownList;			//�����Ѿ����µ����
	list<CGameUserInfo*>::iterator iter1;


	//{���� rongqiufen 2010.06.29
	//�Ƿ��ų��ɹ�
	bool hasSucceed = false;

	int iDeskPlayerNum = (*m_pDesk)->m_bMaxPeople;
	if(m_pGameUserInfoList.size() >= m_uQueuerPeople + iDeskPlayerNum)
	{
		srand(unsigned(time(0)));
		///ÿ֧������������Ȩ0-49
		for (iter1 = m_pGameUserInfoList.begin(); iter1 != m_pGameUserInfoList.end(); iter1++)
		{
			if ((*iter1)->m_UserData.bDeskNO == 255) 
			{
				if ((*iter1)->GetWeigth() < MAXLONG - 50) 
				{
					int r = rand() % 50;
					(*iter1)->m_SelectWeight += r;
				}
			}
		}
		{
			///��Ȩֵ��������Ȩֵ�ߵĻ����Ƚ��д���
			m_pGameUserInfoList.sort(compare());
        //���� rongqiufen}

			//CString s1, s2;
			//s1 = "";
			//s1 = "";
			//for (iter1 = m_pGameUserInfoList.begin(); iter1 != m_pGameUserInfoList.end(); ++iter1)
			//{
			//	s2.Format("(%s, %d)", (*iter1)->m_UserData.szName, (*iter1)->GetWeigth());
			//	s1 += " | " + s2;
			//}
			//ouf<<s1<<endl;

			 // PengJiLin, 2010-5-20, �������ֻʹ��һ�Σ��ڶ��λ��ߵ����λ������������
			 // ͬʱ���ⲻ��һ��������ӵ�����
			BOOL bUseOnce = FALSE;
			//����û�п�ʼ��Ϸ������
			while (m_pGameUserInfoList.size() >= m_uQueuerPeople + iDeskPlayerNum && (1 + iDeskIndex) < m_uDeskCount)
			{
				iADeskPlayerNum = 0;
				isGameing = true;
				pGameDesk = NULL;

				++iDeskIndex;
				pGameDesk=*(m_pDesk+iDeskIndex);
				
				if (NULL != pGameDesk)
				{
					isGameing = pGameDesk->IsPlayingByGameStation();
					if (!isGameing)
					{
						//isADeskGameBegin = false;
						//��������ж�����
						iADeskPlayerNum = pGameDesk->GetDeskPlayerNum();

						/// ��������δ�������������˺�û����
						if (iADeskPlayerNum < pGameDesk->m_bMaxPeople)
						{
							int iQueueSitDownNum = 0;	//һ���������Ŷ����µ�����					
							tempList = m_pGameUserInfoList;

							// PengJiLin, 2010-5-20
							UINT iCount = 0;

							//һ���Ŷ�һ������
							for (iter1 = tempList.begin(); iter1 != tempList.end(); ++iter1)
							{
								pGameUserInfo = *iter1;						
								iDeskStation = pGameDesk->GetDeskNoPlayerStation();		//��ȡ���ڵĿ���λ����

								if (-1 == iDeskStation)//������
								{
									break;
								}

								if (NULL != pGameUserInfo)
								{
									if (pGameUserInfo->m_UserData.bDeskNO == 255)//û����������
									{
										//�ж��������Ƿ���ip��ͬ�����
										if (pGameDesk->IsDeskIpSame(pGameUserInfo))
										{
											continue;
										}

										//// PengJiLin, 2010-5-20, �����޳���λ��
										//if((pArray[iCount] == -1) && (FALSE == bUseOnce))
										//{
										//	++iCount;
										//	continue;
										//}

										++iQueueSitDownNum;
										pGameUserInfo->m_UserData.bUserState = USER_ARGEE; //USER_SITTING;
										pGameUserInfo->m_UserData.bDeskNO = iDeskIndex;
										pGameUserInfo->m_UserData.bDeskStation=iDeskStation;								
										pGameDesk->SetDeskUserInfo(pGameUserInfo, iDeskStation);

										//���Ŷӻ���ɾ���Ѿ�������λ�����
										m_pGameUserInfoList.remove(pGameUserInfo);
										//�����Ѿ����µ����
										sitdownList.push_back(pGameUserInfo);
			
										if (iQueueSitDownNum == pGameDesk->m_bMaxPeople)
										{
											break;//������
										}
									}
								}
							}//end of for

							// PengJiLin, 2010-5-20
							bUseOnce = TRUE;
							
							//���������ˣ��������ˡ������˵����
							if (0 < iQueueSitDownNum)
							{
								//�Ƿ��������
								if (pGameDesk->CanBeginGame())
								{
									//pGameDesk->GameBegin(0);
									//CString s;
									//s.Format("%d, %d", IsUserPlayGame(pGameDesk->m_pUserInfo[0]), pGameDesk->m_pUserInfo[0]->m_UserData.bUserState);
									//AfxMessageBox(s);
									//��һ�������Ŷӳɹ�����ʼ��Ϸ�ˣ�����client�����¡���Ϸ��ʼ��Ϣ����sitdownList��ȡ�����Ϣ
									//���ͷ���������Ϣ
									for (iter1 = sitdownList.begin(); iter1 != sitdownList.end(); ++iter1)
									{
										pGameUserInfo = NULL;
										pGameUserInfo = *iter1;
										if (NULL != pGameUserInfo)
										{
											hasSucceed = true;
											pGameUserInfo->m_SelectWeight = 0;
											MSG_GR_R_UserSit UserSit;
											memset(&UserSit, 0, sizeof(UserSit));
											UserSit.dwUserID = pGameUserInfo->m_UserData.dwUserID;
											UserSit.bDeskIndex = pGameUserInfo->m_UserData.bDeskNO;
											UserSit.bDeskStation = pGameUserInfo->m_UserData.bDeskStation;
											UserSit.bUserState = USER_SITTING;
											m_TCPSocket.SendDataBatch(&UserSit,sizeof(UserSit),MDM_GR_USER_ACTION,ASS_GR_QUEUE_USER_SIT,ERR_GR_SIT_SUCCESS);
										}
									}							
									//end of ��client����Ϣ
									//pGameDesk->GameBegin(0);
								}
								else//�����ŶӺ��ܿ�ʼ��Ϸ����ԭ֮ǰ���õ�һЩ��Ϣ
								{
									for (iter1 = sitdownList.begin(); iter1 != sitdownList.end(); ++iter1)
									{
										pGameUserInfo = NULL;
										pGameUserInfo = *iter1;
										if (NULL != pGameUserInfo)
										{
											pGameDesk->SetDeskUserInfo(NULL, pGameUserInfo->m_UserData.bDeskStation);//�����λ�ϵ������Ϣ
											pGameUserInfo->m_UserData.bDeskNO=255;
											pGameUserInfo->m_UserData.bDeskStation=255;
											pGameUserInfo->m_UserData.bUserState=USER_LOOK_STATE;
										}
									}						
									m_pGameUserInfoList.swap(tempList);//�Ŷ�ʧ�ܻ�ԭ��list
								}

								tempList.clear();
								sitdownList.clear();
							}
						}//end of if (iADeskPlayerNum < pGameDesk->m_bMaxPeople)
					}//end of if (!isGameing)
				}//end of if (NULL != pGameDesk)			
			}// end of while (m_pGameUserInfoList.size() > 0 && (1 + iDeskIndex) < m_uDeskCount)
		}
	

		//{���� rongqiufen 2010.06.29
		///�����ŶӲ��ɹ��Ľ��м�Ȩ
		if (hasSucceed)
		{
			for (iter1 = m_pGameUserInfoList.begin(); iter1 != m_pGameUserInfoList.end(); iter1++)
			{
				if ((*iter1)->m_UserData.bDeskNO == 255) 
				{
					if ((*iter1)->GetWeigth() < MAXLONG - 50) 
						(*iter1)->m_SelectWeight += 30;
				}
			}
		}
       //���� rongqiufen}

		//s1 = "---";
		//for (iter1 = m_pGameUserInfoList.begin(); iter1 != m_pGameUserInfoList.end(); ++iter1)
		//{
		//	s2.Format("%s, %d", (*iter1)->m_UserData.szName, (*iter1)->GetWeigth());
		//	s1 += " | " + s2;
		//}
		//ouf<<s1<<endl;
	}

/*

	
    // PengJiLin, 2010-5-20, ���Ŷӻ�λ������޳�
    memset(pArray, 0, m_uQueuerMaxPeople);
    if(m_uQueuerMaxPeople > m_KernelData.uDeskPeople)
    {
        int iCount = m_uQueuerMaxPeople - m_KernelData.uDeskPeople;
        for(int i = 0; i < iCount; ++i)
        {
            UINT uIndex = (UINT)rand() % m_uQueuerMaxPeople;

            if(pArray[uIndex] == 0) pArray[uIndex] = -1;
            else
            {
                for(int i = 0; i < m_uQueuerMaxPeople; ++i)
                {
                    if(pArray[i] == 0)
                    {
                        pArray[i] = -1;
                        break;
                    }
                }
            }
        }
    }

    // PengJiLin, 2010-5-20, �������ֻʹ��һ�Σ��ڶ��λ��ߵ����λ������������
    // ͬʱ���ⲻ��һ��������ӵ�����
    BOOL bUseOnce = FALSE;

	//����û�п�ʼ��Ϸ������
	while (m_pGameUserInfoList.size() > 0 && (1 + iDeskIndex) < m_uDeskCount)
	{
		iADeskPlayerNum = 0;
		isGameing = true;
		pGameDesk = NULL;

		++iDeskIndex;
		pGameDesk=*(m_pDesk+iDeskIndex);
		
		if (NULL != pGameDesk)
		{
			isGameing = pGameDesk->IsPlayingByGameStation();
			if (!isGameing)
			{
				//isADeskGameBegin = false;
				//��������ж�����
				iADeskPlayerNum = pGameDesk->GetDeskPlayerNum();

				/// ��������δ�������������˺�û����
				if (iADeskPlayerNum < pGameDesk->m_bMaxPeople)
				{
					int iQueueSitDownNum = 0;	//һ���������Ŷ����µ�����					
					tempList = m_pGameUserInfoList;

                    // PengJiLin, 2010-5-20
                    UINT iCount = 0;

					//һ���Ŷ�һ������
					for (iter1 = tempList.begin(); iter1 != tempList.end(); ++iter1)
					{
						pGameUserInfo = *iter1;						
						iDeskStation = pGameDesk->GetDeskNoPlayerStation();		//��ȡ���ڵĿ���λ����

						if (-1 == iDeskStation)//������
						{
							break;
						}

						if (NULL != pGameUserInfo)
						{
							if (pGameUserInfo->m_UserData.bDeskNO == 255)//û����������
							{
								//�ж��������Ƿ���ip��ͬ�����
								if (pGameDesk->IsDeskIpSame(pGameUserInfo))
								{
									continue;
								}

                                // PengJiLin, 2010-5-20, �����޳���λ��
                                if((pArray[iCount] == -1) && (FALSE == bUseOnce))
                                {
                                    ++iCount;
                                    continue;
                                }

								++iQueueSitDownNum;
								pGameUserInfo->m_UserData.bUserState = USER_ARGEE; //USER_SITTING;
								pGameUserInfo->m_UserData.bDeskNO = iDeskIndex;
								pGameUserInfo->m_UserData.bDeskStation=iDeskStation;								
								pGameDesk->SetDeskUserInfo(pGameUserInfo, iDeskStation);

								//���Ŷӻ���ɾ���Ѿ�������λ�����
								m_pGameUserInfoList.remove(pGameUserInfo);
								//�����Ѿ����µ����
								sitdownList.push_back(pGameUserInfo);
	
								if (iQueueSitDownNum == pGameDesk->m_bMaxPeople)
								{
									break;//������
								}
							}
						}
					}//end of for

                    // PengJiLin, 2010-5-20
                    bUseOnce = TRUE;
					
					//���������ˣ��������ˡ������˵����
					if (0 < iQueueSitDownNum)
					{
						//�Ƿ��������
						if (pGameDesk->CanBeginGame())
						{
							//��һ�������Ŷӳɹ�����ʼ��Ϸ�ˣ�����client�����¡���Ϸ��ʼ��Ϣ����sitdownList��ȡ�����Ϣ
							//���ͷ���������Ϣ
							for (iter1 = sitdownList.begin(); iter1 != sitdownList.end(); ++iter1)
							{
								pGameUserInfo = NULL;
								pGameUserInfo = *iter1;
								if (NULL != pGameUserInfo)
								{
									MSG_GR_R_UserSit UserSit;
									memset(&UserSit, 0, sizeof(UserSit));
									UserSit.dwUserID=pGameUserInfo->m_UserData.dwUserID;
									UserSit.bDeskIndex=pGameUserInfo->m_UserData.bDeskNO;
									UserSit.bDeskStation=pGameUserInfo->m_UserData.bDeskStation;
									UserSit.bUserState=USER_SITTING;
									m_TCPSocket.SendDataBatch(&UserSit,sizeof(UserSit),MDM_GR_USER_ACTION,ASS_GR_QUEUE_USER_SIT,ERR_GR_SIT_SUCCESS);
								}
							}							
							//end of ��client����Ϣ
							//pGameDesk->GameBegin(0);
						}
						else//�����ŶӺ��ܿ�ʼ��Ϸ����ԭ֮ǰ���õ�һЩ��Ϣ
						{
							for (iter1 = sitdownList.begin(); iter1 != sitdownList.end(); ++iter1)
							{
								pGameUserInfo = NULL;
								pGameUserInfo = *iter1;
								if (NULL != pGameUserInfo)
								{
									pGameDesk->SetDeskUserInfo(NULL, pGameUserInfo->m_UserData.bDeskStation);//�����λ�ϵ������Ϣ
									pGameUserInfo->m_UserData.bDeskNO=255;
									pGameUserInfo->m_UserData.bDeskStation=255;
									pGameUserInfo->m_UserData.bUserState=USER_LOOK_STATE;
								}
							}						
							m_pGameUserInfoList.swap(tempList);//�Ŷ�ʧ�ܻ�ԭ��list
						}

						tempList.clear();
						sitdownList.clear();
					}
				}//end of if (iADeskPlayerNum < pGameDesk->m_bMaxPeople)
			}//end of if (!isGameing)
		}//end of if (NULL != pGameDesk)			
	}// end of while (m_pGameUserInfoList.size() > 0 && (1 + iDeskIndex) < m_uDeskCount)
*/	
	return;
}

//�û����䴦��
bool CGameMainManage::OnRoomMessage(NetMessageHead * pNetHead, void * pData, UINT uSize, ULONG uAccessIP, UINT uIndex, DWORD dwHandleID)
{
	ASSERT(pNetHead->bMainID==MDM_GR_ROOM);
	switch (pNetHead->bAssistantID)
	{
	case ASS_GR_NORMAL_TALK:	//��ͨ����
		{
			MSG_GR_RS_NormalTalk * pNormalTalk=(MSG_GR_RS_NormalTalk *)pData;
			/*if(!coreProcess(pNormalTalk->szMessage))
				return false;*/
			if(m_InitData.dwRoomRule& GRR_FORBID_ROOM_TALK)//��ֹ��������
				return false;
			//Ч������ 
			//MSG_GR_RS_NormalTalk * pNormalTalk=(MSG_GR_RS_NormalTalk *)pData;
			if ((uSize<=(sizeof(MSG_GR_RS_NormalTalk)-sizeof(pNormalTalk->szMessage)))||(uSize>sizeof(MSG_GR_RS_NormalTalk))) return false;
			if ((pNormalTalk->iLength+1)!=(uSize+sizeof(pNormalTalk->szMessage)-sizeof(MSG_GR_RS_NormalTalk))) return false;

			//��������
			CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
			if (pUserInfo==NULL) return false;

			//{{ Added by zxd 20100806
			/// �������ʱ����Ч���򲻷���
			CString strTime;
			strTime.Format("%d",CTime::GetCurrentTime());
			int curTime=atoi(strTime);
			if (pUserInfo->m_UserData.userInfoEx2 > curTime)
			{
				return true;
			}
			// Added by zxd 20100806}}

			//Ⱥ������
			pNormalTalk->szMessage[pNormalTalk->iLength]=0;
			pNormalTalk->dwSendID=pUserInfo->m_UserData.dwUserID;
			
			/*if (!m_TalkFilter.IsAllowableTalk(pNormalTalk->szMessage,lstrlen(pNormalTalk->szMessage)))
			{
				const TCHAR* pTemTalk = m_TalkFilter.GetReplaceContent();
				strcpy(pNormalTalk->szMessage,pTemTalk);
				pNormalTalk->iLength = strlen(pTemTalk) + 1;
				pNormalTalk->szMessage[pNormalTalk->iLength]=0;

				//AfxMessageBox(pNormalTalk->szMessage);
			}*/

			string str_temp(pNormalTalk->szMessage);
			m_HNFilter.censor(str_temp,false);
			strcpy(pNormalTalk->szMessage,str_temp.c_str());
			pNormalTalk->iLength = strlen(pNormalTalk->szMessage) + 1;
			pNormalTalk->szMessage[pNormalTalk->iLength + 1] = 0;
			m_TCPSocket.SendDataBatch(pNormalTalk,sizeof(MSG_GR_RS_NormalTalk)-sizeof(pNormalTalk->szMessage)+pNormalTalk->iLength+1,MDM_GR_ROOM,ASS_GR_NORMAL_TALK,0);

			return true;
		}
	case ASS_GR_SHORT_MSG:		//����Ϣ����
		{
			//Ч������
			MSG_GR_RS_NormalTalk * pNormalTalk=(MSG_GR_RS_NormalTalk *)pData;
			if ((uSize<=(sizeof(MSG_GR_RS_NormalTalk)-sizeof(pNormalTalk->szMessage)))||(uSize>sizeof(MSG_GR_RS_NormalTalk))) return false;
			if ((pNormalTalk->iLength+1)!=(uSize+sizeof(pNormalTalk->szMessage)-sizeof(MSG_GR_RS_NormalTalk))) return false;

			//��������
			CGameUserInfo * pSendUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
			CGameUserInfo * pRecvUserInfo=m_UserManage.FindOnLineUser(pNormalTalk->dwTargetID);
			if ((pSendUserInfo==NULL)||(pRecvUserInfo==NULL)) return true;
			pNormalTalk->szMessage[pNormalTalk->iLength]=0;
			pNormalTalk->dwSendID=pSendUserInfo->m_UserData.dwUserID;

			/*if (!m_TalkFilter.IsAllowableTalk(pNormalTalk->szMessage,lstrlen(pNormalTalk->szMessage)))
			{
				const TCHAR* pTemTalk = m_TalkFilter.GetReplaceContent();
				strcpy(pNormalTalk->szMessage,pTemTalk);
				pNormalTalk->iLength = strlen(pTemTalk) + 1;
				pNormalTalk->szMessage[pNormalTalk->iLength]=0;

				//AfxMessageBox(pNormalTalk->szMessage);
				//return true;
			}*/

			string str_temp(pNormalTalk->szMessage);
			m_HNFilter.censor(str_temp,false);
			strcpy(pNormalTalk->szMessage,str_temp.c_str());
			pNormalTalk->iLength = strlen(pNormalTalk->szMessage) + 1;
			pNormalTalk->szMessage[pNormalTalk->iLength + 1] = 0;

			//��������
			m_TCPSocket.SendData(pSendUserInfo->m_uSocketIndex,pNormalTalk,sizeof(MSG_GR_RS_NormalTalk)-sizeof(pNormalTalk->szMessage)+pNormalTalk->iLength+1,MDM_GR_ROOM,ASS_GR_SHORT_MSG,0,pSendUserInfo->m_dwHandleID);
			m_TCPSocket.SendData(pRecvUserInfo->m_uSocketIndex,pNormalTalk,sizeof(MSG_GR_RS_NormalTalk)-sizeof(pNormalTalk->szMessage)+pNormalTalk->iLength+1,MDM_GR_ROOM,ASS_GR_SHORT_MSG,0,pRecvUserInfo->m_dwHandleID);

			return true;
		}
	case ASS_GR_ROOM_SET:		//��������
		{
			//Ч������
			if (uSize!=sizeof(MSG_GR_S_UserSet)) return false;
			MSG_GR_S_UserSet * pUserSetInfo=(MSG_GR_S_UserSet *)pData;

			//��������
			CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
			if (pUserInfo==NULL) return false;
			pUserSetInfo->m_Rule.szPass[sizeof(pUserSetInfo->m_Rule.szPass)/sizeof(pUserSetInfo->m_Rule.szPass[0])-1]=0;
			pUserInfo->m_Rule=pUserSetInfo->m_Rule;

            // PengJiLin, 2010-9-14, �ȽϹ����еĻ��ֱȽ��Ƿ��Ϊ��ұȽ�
//             CBcfFile fConfig(CBcfFile::GetAppPath()+"Function.bcf");
//             int iGold = fConfig.GetKeyVal("CommFunc","UseGoldValue",0);
//             if(iGold > 0 && pUserInfo->m_Rule.bLimitPoint != 0)
//             {
//                 pUserInfo->m_Rule.bLimitPoint |= 0x80;
//             }

			return true;
		}
	case ASS_GR_INVITEUSER:		//�����û�
		{
			//Ч������
			if (uSize!=sizeof(MSG_GR_SR_InviteUser)) return false;
			MSG_GR_SR_InviteUser * pInviteUser=(MSG_GR_SR_InviteUser *)pData;

			//��������
			CGameUserInfo * pSendUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
			CGameUserInfo * pRecvUserInfo=m_UserManage.FindOnLineUser(pInviteUser->dwTargetID);
			if ((pSendUserInfo==NULL)||(pRecvUserInfo==NULL)) return true;
			if (pSendUserInfo->m_UserData.bDeskNO==255) return true;
			pNetHead->bHandleCode=pSendUserInfo->m_UserData.bDeskNO;
			pInviteUser->dwUserID=pSendUserInfo->m_UserData.dwUserID;

			//��������
			m_TCPSocket.SendData(pRecvUserInfo->m_uSocketIndex,pInviteUser,uSize,MDM_GR_ROOM,ASS_GR_INVITEUSER,
				pNetHead->bHandleCode,pRecvUserInfo->m_dwHandleID);

			return true;
		}
	case ASS_GR_ROOM_PASSWORD_SET:
		{
			BOOL bRecord = FALSE;
			char bufID[12] = {0};
			CGameUserInfo * pSendUserInfo = m_UserManage.GetOnLineUserInfo(uIndex);

			CBcfFile fConfig(CBcfFile::GetAppPath()+"Function.bcf");
			CString strBuffer = fConfig.GetKeyVal("SpecificID","Available","");
			if (atoi(strBuffer)) ///< ָ���˺�ID
			{
				if (0 ==_tcslen(m_szVIPPassWord)) ///< VIP��������Ϊ��ʼ����
				{
					strBuffer = fConfig.GetKeyVal("SpecificID","NormalID","60000000,69999999");

					int iVIP = GetIDInformation(pSendUserInfo->m_UserData.dwUserID,
						atol(strBuffer.Left(strBuffer.Find(",")+1)),
						atol(strBuffer.Right(strBuffer.GetLength()-strBuffer.Find(",")-1)));

					if ((iVIP>0 && iVIP<7) || (iVIP>-9 && iVIP<-4))
					{
						if (uSize>50)
							break;
						
						m_lVIPID = pSendUserInfo->m_UserData.dwUserID;
						
						bRecord = TRUE;
					}
				}
				else if (pSendUserInfo->m_UserData.dwUserID == m_lVIPID)
				{
					bRecord = TRUE;
				}

				///< �������ݿ�,��¼���������޸�.
				if (bRecord)
				{
					wsprintf(bufID,"%ld",m_lVIPID);
					memcpy(m_szVIPPassWord,pData,uSize);
					m_szVIPPassWord[uSize] = 0;
					m_TCPSocket.SendDataBatch(bufID,strlen(bufID),MDM_GR_ROOM,ASS_GR_ROOM_PASSWORD_SET,dwHandleID);

					DL_GR_RoomPWChange pRoomPW;
					pRoomPW.dwUserID = pSendUserInfo->m_UserData.dwUserID;
					pRoomPW.dwRoomID = m_InitData.uRoomID;
					m_SQLDataManage.PushLine(&pRoomPW.DataBaseHead,sizeof(DL_GR_RoomPWChange),DTK_GR_ROOM_PW_CHANGE,uIndex,dwHandleID);
				}
			}
			
			return true;
		}
    case ASS_GR_GET_NICKNAME_ONID:  // PengJiLin, 2010-8-23, ����ID��ȡ�ǳ�
        {
            // Ч������
            if (uSize!=sizeof(MSG_GR_S_GetNickNameOnID_t)) return false;
            MSG_GR_S_GetNickNameOnID_t *pGetNickNameOnID =(MSG_GR_S_GetNickNameOnID_t *)pData;

            // �������ݿ�
            DL_GR_I_GetNickNameOnID stGetNickNameOnID;
            stGetNickNameOnID.stGetNickNameOnID.iUserID = pGetNickNameOnID->iUserID;
            m_SQLDataManage.PushLine(&stGetNickNameOnID.DataBaseHead,sizeof(stGetNickNameOnID),DTK_GR_GETNICKNAME_ONID,uIndex,dwHandleID);

            return true;
        }
    break;
    case ASS_GR_GET_NICKNAME_ONID_INGAME:  // lxl, 2010-11-17, ����ID��ȡ�ǳ�
        {
            // Ч������
			OutputDebugString("��Ϸ�л�ȡID�ǳ�");
            if (uSize!=sizeof(MSG_GR_S_GetNickNameOnID_t)) return false;
            MSG_GR_S_GetNickNameOnID_t *pGetNickNameOnID =(MSG_GR_S_GetNickNameOnID_t *)pData;

            // �������ݿ�
            DL_GR_I_GetNickNameOnID stGetNickNameOnID;
            stGetNickNameOnID.stGetNickNameOnID.iUserID = pGetNickNameOnID->iUserID;
            m_SQLDataManage.PushLine(&stGetNickNameOnID.DataBaseHead,sizeof(stGetNickNameOnID),DTK_GR_GETNICKNAME_ONID_INGAME,uIndex,dwHandleID);

            return true;
        }
    break;
    case ASS_GR_OWNER_T_ONE_LEFT_ROOM:      // PengJiLin, 2010-8-26, ����������뿪����
        {
            //Ч������
            if (uSize!=sizeof(MSG_GR_S_CutUser)) return false;
            MSG_GR_S_CutUser * pCutUser=(MSG_GR_S_CutUser *)pData;

            CGameUserInfo * pTargetUserInfo=m_UserManage.FindOnLineUser(pCutUser->dwTargetID);
            if (pTargetUserInfo==NULL) return true;

            char bufID[12] = {0};
            wsprintf(bufID,"%ld",pCutUser->dwTargetID);
            m_TCPSocket.SendData(pTargetUserInfo->m_uSocketIndex, bufID, sizeof(bufID),
                                MDM_GR_ROOM,ASS_GR_OWNER_T_ONE_LEFT_ROOM,0,pTargetUserInfo->m_dwHandleID);

            return true;
        }
        break;

	case ASS_GR_AVATAR_LOGO_CHANGE: //JianGuankun 2012.6.28,�����ĳ���logo����ı�
		{
			//Ч������
			if (uSize!=sizeof(MSG_GR_AvatarChange)) return false;
			MSG_GR_AvatarChange* pAvatarChange = (MSG_GR_AvatarChange*)pData;

			CGameUserInfo * pTargetUserInfo = m_UserManage.FindOnLineUser(pAvatarChange->dwUserID);
			if (pTargetUserInfo == NULL) return true;

			pTargetUserInfo->GetUserData(NULL)->bLogoID = pAvatarChange->nNewLogoID;

			m_TCPSocket.SendDataBatch(pAvatarChange,sizeof(MSG_GR_AvatarChange),MDM_GR_ROOM,ASS_GR_AVATAR_LOGO_CHANGE,0);

			return true;
		}
		break;
	}
	return false;
}

//�û���½���� 
bool CGameMainManage::OnUserLogonMessage(NetMessageHead * pNetHead, void * pData, UINT uSize, ULONG uAccessIP, UINT uIndex, DWORD dwHandleID)
{
	ASSERT(pNetHead->bMainID==MDM_GR_LOGON);
	switch (pNetHead->bAssistantID)
	{
	case ASS_GR_IS_VIPROOM: ///< ƽ̨�ͻ��˷��Ͳ�ѯ�Ƿ�VIP����
		{
			if (m_InitData.bVIPRoom) ///< �����뷿��
			{
				if (0 == m_UserManage.GetGameRoomCount()) ///< �����ڷ���
				{
					m_lVIPID = -1;
				memset(m_szVIPPassWord,0,sizeof(m_szVIPPassWord));
				m_TCPSocket.SendData(uIndex,MDM_GR_LOGON,ASS_GR_LOGON_SUCCESS,ASS_GR_VIP_NO_PW,dwHandleID);
			}
				else ///< �����ڷ���
				{
					if (0 != strlen(m_szVIPPassWord)) ///< �����Ѿ���������
					{
						CGameUserInfo * pGameUserInfo = m_UserManage.FindOnLineUser(m_lVIPID);
						if (NULL == pGameUserInfo) ///< ����������˲��ڷ���
						{
							if (atol((char*)pData) == m_lVIPID) ///< �ǵ�һ�����÷���������û�������Ҫ��������.
							{
								if (!m_bIsVIPLogon)
								{
									m_bIsVIPLogon = TRUE;
									m_uVIPIndex = uIndex;
									m_TCPSocket.SendData(uIndex,MDM_GR_LOGON,ASS_GR_LOGON_SUCCESS,ASS_GR_VIP_NO_PW,dwHandleID);
								}
								else ///< �Ѿ��и��û�������ID���޸ķ��������ID�ˡ�
								{
									m_TCPSocket.SendData(uIndex,MDM_GR_LOGON,ASS_GR_LOGON_SUCCESS,ASS_GR_VIP_PW,dwHandleID);
								}
							}
							else ///< ��������������ˣ���Ҫ�������롣
							{
								m_TCPSocket.SendData(uIndex,MDM_GR_LOGON,ASS_GR_LOGON_SUCCESS,ASS_GR_VIP_PW,dwHandleID);
							}
						}
						else ///< ������������ڷ��䣬��������Ҫ�������롣
						{
							m_TCPSocket.SendData(uIndex,MDM_GR_LOGON,ASS_GR_LOGON_SUCCESS,ASS_GR_VIP_PW,dwHandleID);
						}
					}
					else ///< ����û����������,����Ҫ��������
					{
						m_TCPSocket.SendData(uIndex,MDM_GR_LOGON,ASS_GR_LOGON_SUCCESS,ASS_GR_VIP_NO_PW,dwHandleID);
					}
				}
			}
			else ///< �������뷿��,����Ҫ�������롣
			{
				m_TCPSocket.SendData(uIndex,MDM_GR_LOGON,ASS_GR_LOGON_SUCCESS,ASS_GR_NO_VIP,dwHandleID);
			}

			return true;
		}

	case ASS_GR_VIPROOM_PW: ///< ƽ̨�ͻ��˷���VIP��������
		{
			if (uSize < 50)
			{
				TCHAR Password[50] = {0};
				memcpy(Password,pData,uSize);
				
				if (0 == lstrcmp(m_szVIPPassWord,Password))
				{
					m_TCPSocket.SendData(uIndex,MDM_GR_LOGON,ASS_GR_LOGON_SUCCESS,ASS_GR_VIPROOM_PW_RIGHT,dwHandleID);
					return true;
				}
			}

			m_TCPSocket.SendData(uIndex,MDM_GR_LOGON,ASS_GR_LOGON_ERROR,ERR_GR_USER_PASS_ERROR,dwHandleID);
			return true;
		}

	case ASS_GR_LOGON_BY_ID:		//ͨ�� ID ��½
		{
			//Ч������
			if (uSize!=sizeof(MSG_GR_S_RoomLogon)) return false;
			MSG_GR_S_RoomLogon * pLogonInfo=(MSG_GR_S_RoomLogon *)pData;
			if (pLogonInfo->uNameID!=m_KernelData.uNameID) return false;
			pLogonInfo->szMD5Pass[sizeof(pLogonInfo->szMD5Pass)/sizeof(pLogonInfo->szMD5Pass[0])-1]=0;
			m_bStopLogon=m_InitData.uStopLogon;
			//�жϵ�½״̬
			if (m_bStopLogon)
			{
				SendRoomMessage(uIndex,dwHandleID,TEXT("��Ϸ�����Ѿ���ͣ���룡"),SHS_MESSAGE_BOX|SHS_SYSTEM_SHOW,0,TRUE);
				m_TCPSocket.SendData(uIndex,MDM_GR_LOGON,ASS_GR_LOGON_ERROR,ERR_GR_STOP_LOGON,dwHandleID);
				return true;
			}

			//���������û�
			CGameUserInfo * pGameUserInfo=NULL;m_UserManage.FindOnLineUser(pLogonInfo->dwUserID);
			if (pGameUserInfo!=NULL)
			{
				if (pLogonInfo->bForced)
				{
					int SocketID = pGameUserInfo->GetSocketIndex();
					m_TCPSocket.CloseSocket(SocketID,0);
					OnSocketClose(uAccessIP,SocketID,0);
				}
				else
				{
					m_TCPSocket.SendData(uIndex,MDM_GR_LOGON,ASS_GR_LOGON_ERROR,ERR_GR_ACCOUNTS_IN_USE,dwHandleID);
					return true;
				}
			}

			if (m_InitData.bVIPRoom &&			 ///< �����뷿��
				0!=strlen(m_szVIPPassWord) &&	 ///< �Ѿ���������
				NULL==pGameUserInfo &&			 ///< ����������˲��ڷ���
				m_bIsVIPLogon &&
				m_uVIPIndex==uIndex &&			 ///< ����������˵��׽�������
				m_lVIPID!=pLogonInfo->dwUserID)  ///< ���˵�ID����VIP ID
			{
				m_bIsVIPLogon = FALSE;
				m_TCPSocket.SendData(uIndex,MDM_GR_LOGON,ASS_GR_LOGON_ERROR,ERR_GR_STOP_LOGON,dwHandleID);
				return 0;
			}
			else if (m_InitData.bVIPRoom &&
				0!=strlen(m_szVIPPassWord) &&
				NULL==pGameUserInfo &&
				m_bIsVIPLogon &&
				m_uVIPIndex==uIndex &&
				m_lVIPID==pLogonInfo->dwUserID)
			{
				m_bIsVIPLogon = FALSE;
			}

			pGameUserInfo=m_UserManage.FindOnLineUser(pLogonInfo->dwUserID);
			if (pGameUserInfo!=NULL)
			{
				m_TCPSocket.CloseSocket(pGameUserInfo->m_uSocketIndex, 0);
				m_TCPSocket.SendData(uIndex,MDM_GR_LOGON,ASS_GR_LOGON_ERROR,ERR_GR_ACCOUNTS_IN_USE,dwHandleID);
				return true;
			}

			//���Ҷ����û�
			CGameUserInfo * pLostUserInfo=m_UserManage.FindNetCutUser(pLogonInfo->dwUserID);
			if (pLostUserInfo!=NULL)
			{
				//Ч���û�����
				if (lstrcmp(pLostUserInfo->m_szMD5Pass,pLogonInfo->szMD5Pass)!=0) 
				{
					m_TCPSocket.SendData(uIndex,MDM_GR_LOGON,ASS_GR_LOGON_ERROR,ERR_GR_USER_PASS_ERROR,dwHandleID);
					return true;
				}
				if ((pLostUserInfo->m_UserData.userInfoEx2 & 0x80000000) > 0)
				{
					m_TCPSocket.SendData(uIndex,MDM_GR_LOGON,ASS_GR_LOGON_ERROR,ERR_GR_STOP_LOGON,dwHandleID);
					return true;
				}

				CTime _t = CTime::GetCurrentTime();
				if ( (m_InitData.dwRoomRule & GRR_CONTEST||m_InitData.dwRoomRule & GRR_TIMINGCONTEST )&& (pLostUserInfo->m_UserData.timeLeft + m_InitData.iTimeout * 60 < _t.GetTime()))
				{
					m_TCPSocket.SendData(uIndex,MDM_GR_LOGON,ASS_GR_LOGON_ERROR,ERR_GR_CONTEST_TIMEOUT,dwHandleID);
					return true;
				}

				//�����û�����
				pLostUserInfo->m_UserData.bUserState=USER_PLAY_GAME;
				pGameUserInfo=m_UserManage.ActiveUser(&pLostUserInfo->m_UserData,uIndex,dwHandleID,pLostUserInfo->m_dwGamePower,
					pLostUserInfo->m_dwMasterPower,pLostUserInfo->m_dwAccessLogID);

				//д���û�������Ϣ
				pGameUserInfo->SetMD5Pass(pLogonInfo->szMD5Pass);
				pGameUserInfo->m_ChangePoint=pLostUserInfo->m_ChangePoint;
				pGameUserInfo->SetUserScrPoint(pLostUserInfo->m_dwScrPoint);

				//���ͷ�����Ϣ
				if (SendRoomInfo(pGameUserInfo,uIndex,dwHandleID,NULL)==false)
					return false;

				//����״̬����
				ASSERT(pGameUserInfo->m_UserData.bDeskNO!=255);
				if (pGameUserInfo->m_UserData.bDeskNO!=255)
				{
					CGameDesk * pGameDesk=*(m_pDesk+pGameUserInfo->m_UserData.bDeskNO);
					pGameDesk->UserReCome(pGameUserInfo->m_UserData.bDeskStation,pGameUserInfo);
				}


				AutoAllotDeskAddUser(pGameUserInfo);
				//�����������
				m_UserManage.FreeUser(pLostUserInfo,false);
				SetTimer(IDT_UPDATE_ROOM_PEOPLE,100);//20081201
				return true;
			}

			//�������ݿ�
			DL_GR_I_LogonByIDStruct DL_Logon;
			DL_Logon.uAccessIP=uAccessIP;
			DL_Logon.LogonInfo=*pLogonInfo;
			m_SQLDataManage.PushLine(&DL_Logon.DataBaseHead,sizeof(DL_Logon),DTK_GR_LOGON_BY_ID,uIndex,dwHandleID);
			OutputDebugString("chshttp----------------1");
			return true;
		}
	}
	return false;
}

//�÷����Ƿ��������������
bool CGameMainManage::IsExistGRMRoom(UINT iRoomID)
{
	if (m_GRMRoomID.empty())
		return false;
	std::vector<UINT>::iterator it;
	it = std::find( m_GRMRoomID.begin(), m_GRMRoomID.end(), iRoomID );
	if (it != m_GRMRoomID.end())
	{
		return true;
	}

	return false;
}

//������Ƿ����ʹ�÷��������
bool CGameMainManage::IsExistGRMUserID(long int UserID)
{
	if (m_GRMUserID.empty())
		return false;
	std::vector<long int>::iterator it;
	it = std::find( m_GRMUserID.begin(), m_GRMUserID.end(), UserID );
	if (it != m_GRMUserID.end())
	{
		return true;
	}

	return false;
}

//�뿪���Ӻ���
bool CGameMainManage::UserLeftDesk(CGameUserInfo * pUserInfo)
{
	//��ȡ����
	CGameDesk * pLeftDesk=*(m_pDesk+pUserInfo->m_UserData.bDeskNO);

	//CString s;
	//s.Format("%d",IsUserPlayGame(pUserInfo)); 
	//AfxMessageBox(s);

    // PengJiLin, 2010-9-17, �Ŷӻ����ܣ��������桰��ɢ���ӡ���һ�δ��룬
    // ��Ϊ����һ������뿪������������Ҷ��������ҹر���Ϸ���棬������
    // ��ҿ������Լ��Ľ���򲢱��������Ŷ�״̬

	//{���� rongqiufen 2010.06.29
	///������Ŷӻ���������Ϸ������������ ��ɢ���ӣ� �����������˽����Ŷ�׼��״̬           
	if (IsQueueGameRoom() && !IsUserPlayGame(pUserInfo))
	{
		pLeftDesk->UserLeftDesk(pUserInfo->m_UserData.bDeskStation,pUserInfo);
		MSG_GR_R_UserAgree UserAgree;
		for (int i = 0; i < pLeftDesk->m_bMaxPeople; i++)
		{
			if (pLeftDesk->m_pUserInfo[i] != NULL)
			{
				CGameUserInfo *p = m_UserManage.FindOnLineUser(pLeftDesk->m_pUserInfo[i]->m_UserData.dwUserID);
				
				//pLeftDesk->UserLeftDesk(pLeftDesk->m_pUserInfo[i]->m_UserData.bDeskStation, pLeftDesk->m_pUserInfo[i]);
				if (p  != pUserInfo)
				{
					 UINT uSocketIndex = p->m_uSocketIndex;
					 m_TCPSocket.SendData(uSocketIndex,&p->m_UserData.dwUserID,sizeof(int),MDM_GR_ROOM,ASS_GR_ROOM_QUEUE_READY, 0, 0);
				}
			}
		}
		return true;
	}
	//���� rongqiufen 2010.06.29}

	if (pUserInfo->m_UserData.bUserState==USER_WATCH_GAME)
	{
		pLeftDesk->WatchUserLeftDesk(pUserInfo->m_UserData.bDeskStation,pUserInfo);
	}
	else 
	{
		pLeftDesk->UserLeftDesk(pUserInfo->m_UserData.bDeskStation,pUserInfo);
	}

	//���ñ���
	pUserInfo->m_UserData.bDeskNO=255;
	pUserInfo->m_UserData.bDeskStation=255;
	pUserInfo->m_UserData.bUserState=USER_LOOK_STATE;


	//{���� rongqiufen
	//ǿ�˷�Ȩ
	CBcfFile fConf(CBcfFile::GetAppPath()+"Function.bcf");
	int fleeSubWeight = fConf.GetKeyVal("OnlineCoin","FleeSubWeight", 0);

	pUserInfo->m_SelectWeight = fleeSubWeight * 50;
	//���� rongqiufen}


	return true;
}
//�û��Ƿ���Ϸ
bool CGameMainManage::IsUserPlayGame(CGameUserInfo * pUserInfo)
{
	if ((pUserInfo->m_UserData.bDeskNO!=255)&&(pUserInfo->m_UserData.bUserState!=USER_WATCH_GAME))
	{
		CGameDesk * pGameDesk=*(m_pDesk+pUserInfo->m_UserData.bDeskNO);
		return pGameDesk->IsPlayGame(pUserInfo->m_UserData.bDeskStation) || (pGameDesk->m_bIsBuy &&pGameDesk->m_iRunGameCount>0) ;
	}
	return false;
}
//�û��Ƿ���Ϸ
bool CGameMainManage::IsUserPlayGameByStation(CGameUserInfo * pUserInfo)
{
	if ((pUserInfo->m_UserData.bDeskNO!=255)&&(pUserInfo->m_UserData.bUserState!=USER_WATCH_GAME))
	{
		CGameDesk * pGameDesk=*(m_pDesk+pUserInfo->m_UserData.bDeskNO);
		return pGameDesk->IsPlayingByGameStation() || (pGameDesk->m_bIsBuy &&pGameDesk->m_iRunGameCount>0);
	}
	return false;
}

//�Ƿ���������
bool CGameMainManage::IsLimitedTalk(CGameUserInfo * pUserInfo, bool bRoom)
{
	if (bRoom==true)
	{
		for (INT_PTR i=0;i<m_RoomLimited.GetCount();i++)
		{
			if (m_RoomLimited.GetAt(i).dwUserID==pUserInfo->m_UserData.dwUserID) return true;
		}
	}
	else
	{
		for (INT_PTR i=0;i<m_GameLimited.GetCount();i++)
		{
			if (m_GameLimited.GetAt(i).dwUserID==pUserInfo->m_UserData.dwUserID) return true;
		}
	}
	return false;
}

//SOCKET �ر�
bool CGameMainManage::OnSocketClose(ULONG uAccessIP, UINT uSocketIndex, long int lConnectTime)
{
	CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uSocketIndex);
	int nDeskIndex = -1; // Ӧ�ü�¼��ʱ��������Ϣ GameDesk::LeftDesk����Ϊ255 ������������ʱ�޷����������Ϣ 
	if (pUserInfo!=NULL)
	{
		//�Ƿ�����Ϸ��
		CGameUserInfo * pNetCutUserInfo=NULL;
		CGameUserInfo *pAlreadyCutUserInfo = m_UserManage.FindNetCutUser(pUserInfo->m_UserData.dwUserID);
		if (pUserInfo->m_UserData.bDeskNO!=255) 
		{
			//ע������û�
			CGameDesk * pGameDesk=*(m_pDesk+pUserInfo->m_UserData.bDeskNO);
			nDeskIndex = pUserInfo->m_UserData.bDeskNO;
			/// �����ж��Ƿ���Զ��ߣ�Ӧ�����κ�ʱ�򶼿��Զ��ߣ���������ڰ�������Ϸ�п���ʱǿ�ˣ��ᵼ�²����㣬ZXD 20100317
			//if ((IsUserPlayGameByStation(pUserInfo)==true)&&(pGameDesk->CanNetCut(pUserInfo->m_UserData.bDeskStation)==true))
			if (IsUserPlayGame(pUserInfo))
			{
				if (pAlreadyCutUserInfo == NULL)
				{
					pNetCutUserInfo=m_UserManage.RegNetCutUser(pUserInfo);
				}
				else
				{
					pNetCutUserInfo=pAlreadyCutUserInfo;
				}
			}
			if (pNetCutUserInfo!=NULL && pUserInfo->m_UserData.bUserState != USER_WATCH_GAME)
			{
				pGameDesk->UserNetCut(pNetCutUserInfo->m_UserData.bDeskStation,pNetCutUserInfo);
				CTime t = CTime::GetCurrentTime();
				pNetCutUserInfo->m_UserData.timeLeft = t.GetTime();
				//pGameDesk->GameFinish(pNetCutUserInfo->m_UserData.bDeskStation, GFF_FORCE_FINISH);
			}
			else
			{
				UserLeftDesk(pUserInfo);

				//������߱�־
				DL_GR_I_ClearOnlineFlag dtClearOnlineFlag;
				memset(&dtClearOnlineFlag, 0, sizeof(dtClearOnlineFlag));
				dtClearOnlineFlag.lUserID = pUserInfo->m_UserData.dwUserID;
				m_SQLDataManage.PushLine(&dtClearOnlineFlag.DataBaseHead, sizeof(dtClearOnlineFlag), DTK_GR_CLEAR_ONLINE_FLAG, 0, 0);
				//��ӽ���}
			}
		}
		else if((m_InitData.dwRoomRule & GRR_CONTEST) || (m_InitData.dwRoomRule & GRR_TIMINGCONTEST))
		{
			DL_GR_I_ClearOnlineFlag dtClearOnlineFlag;
			memset(&dtClearOnlineFlag, 0, sizeof(dtClearOnlineFlag));
			dtClearOnlineFlag.lUserID = pUserInfo->m_UserData.dwUserID;
			m_SQLDataManage.PushLine(&dtClearOnlineFlag.DataBaseHead, sizeof(dtClearOnlineFlag), DTK_GR_CLEAR_ONLINE_FLAG, 0, 0);
		}
		
		
		//�û���û�����¾��뿪��
		if (pNetCutUserInfo==NULL)
		{
			m_pGameUserInfoList.remove(pUserInfo);	//ɾ�������Ŷӵ����
			CleanUserInfo(pUserInfo);
		}
		

		if ((m_InitData.dwRoomRule & GRR_CONTEST) && m_InitData.iRoomState == 0)
		{
			//����Ǳ������䣬��δ��������ҪΪ���û��˻ر�����
			DL_GR_I_ContestReturnFee dtReturnFee;
			memset(&dtReturnFee, 0, sizeof(dtReturnFee));
			dtReturnFee.iUserID = pUserInfo->m_UserData.dwUserID;
			dtReturnFee.iGameID = m_InitData.iGameID;
			dtReturnFee.iRoomID = m_InitData.uRoomID;
			dtReturnFee.iContestID = m_InitData.iContestID;
			m_SQLDataManage.PushLine(&dtReturnFee.DataBaseHead, sizeof(dtReturnFee), DTK_GR_CONTEST_RETURN_FEE, 0, 0);
		}

		if (m_pIAutoAllotDesk)
		{
			AutoAllotDeskDeleteUser(pUserInfo);	//ɾ�������Ŷӵ����
		}
		//����ǵ�����ң������¼��뵽�ŶӶ�����
		/*if (pNetCutUserInfo!=NULL && (m_InitData.dwRoomRule & GRR_CONTEST))
		{
			AutoAllotDeskAddUser(pNetCutUserInfo);
		}*/
		//�����û�
		m_UserManage.FreeUser(pUserInfo,true);
		OutputDebugString("cq::�û������");
		SetTimer(IDT_UPDATE_ROOM_PEOPLE,100);//20081201
	}
	else
	{
		OutputDebugString("cq::���û����ߣ����Ǹ��û������Ѿ������");
	}
	return false;
}

//���ݿ⴦����
bool CGameMainManage::OnDataBaseResult(DataBaseResultLine * pResultData)
{
	switch (pResultData->uHandleKind)
	{
	case DTK_GR_BANK_UPDATE_REBATE:
		{
			return OnGetBankRebateResponse(pResultData);
		}
	case DTK_GR_BANK_UPDATE_USER_REBATE:
	case DTK_GR_BANK_UPDATE_USER_REBATE_INGAME:
		{
			return OnGetBankUserRebateResponse(pResultData, pResultData->uHandleKind);
		}
	case DTK_GR_BANK_SET_USER_REBATE://����޸ķ�������
	case DTK_GR_BANK_SET_USER_REBATE_INGAME:
		{
			return OnGetBankUserSetRebateResponse(pResultData, pResultData->uHandleKind);
		}
	case DTK_GR_DEMAND_MONEY_IN_GAME:	//����Ϸ�����Ǯ��
	case DTK_GR_DEMAND_MONEY:	//��Ǯ��
		{
			return OnAboutMoneyResult(pResultData, pResultData->uHandleKind);
		}
	case DTK_GR_CHECKIN_MONEY:	//���䣭��Ǯ��
	case DTK_GR_CHECKIN_MONEY_INGAME:	//���䣭��Ǯ��
		{
			return OnCheckInMoney(pResultData, pResultData->uHandleKind);
		}
	case DTK_GR_CHECKOUT_MONEY_INGAME: //��Ϸ��ȡǮ<��Ǯ��
	case DTK_GR_CHECKOUT_MONEY: //����<��Ǯ��
		{
			return OnCheckOutMoney(pResultData, pResultData->uHandleKind);
		}
	case DTK_GR_TRANSFER_MONEY://ת��
	case DTK_GR_TRANSFER_MONEY_INGAME://��Ϸ��ת��
		{
			return OnTransferMoney(pResultData, pResultData->uHandleKind);
		}
	case DTK_GR_CHANGE_PASSWD:		 ///<�޸�����
	case DTK_GR_CHANGE_PASSWD_INGAME:///<��Ϸ���޸�����
		{
			return OnChangePasswd(pResultData, pResultData->uHandleKind);
		}
	case DTK_GR_TRANSFER_RECORD:			///<ת�ʼ�¼
	case DTK_GR_TRANSFER_RECORD_INGAME:		///<��Ϸ��ת�ʼ�¼
		{
			return OnTransferRecord(pResultData, pResultData->uHandleKind);
		}
	case DTK_GR_LOGON_BY_ID:	//�����½
		{
			return OnRoomLogonResult(pResultData);
		}
	case DTK_GR_CHECK_CONNECT:	//�������
		{
			return OnCheckConnect(pResultData);
		}
	case DTK_GR_CALL_GM_RESULT://�������ܽ��
		{
			return OnCallGMResult(pResultData);
		}
	case DTK_GR_GAME_POWER_RESULT://������ϷȨ��
		{
			return OnGamePowerSetResult(pResultData);
		}	
	case DTK_GPR_PROP_SMALL_BRD:
	case DTK_GR_PROP_USE://ʹ�õ��� 
		{
			return m_PropService->OnDataBaseResult(pResultData);
		}
	case DTK_GR_SENDMONEY_TIMES:
		{
			return SendUserMoenyByTimesResult(pResultData);		
		}
    case DTK_GR_SEND_MONEY_ON_TIMES_COUNTS:     //����ʱ���������ͽ��
        {
            return OnSendMoneyOnTimesAndCounts(pResultData);
        }

		//wushuqun 2009.6.5
		//��ս������Ϸ��¼���
	case DTK_GR_BATTLEROOM_RES:
		{
			return OnBattleRoomRecord(pResultData);		
		}
	//case DTK_GR_READ_USER_HOLD_ITEM://���е�����
	//case DTK_GR_USER_USE_ONE_ITEM://ʹ�õ�����
	//case DTK_GR_GET_BUY_ITEM_DATA://�򿪹����б���
	//case DTK_GR_BUY_ITEM:			//�������
	////case DTK_GR_CHECK_VIP_TIMER://vipʱ����
	//	{
	//		return m_ItemDate->OnDataBaseResult(pResultData);
	//	}

		//case DTK_GR_FRIEND_MANAGE://���ѹ���
		//	{
		//		return OnFriendManageDBOperateResult(pResultData);
		//	}
		//case DTK_GR_BUFFER_IM_MESSAGE://������Ϣ
		//	{
		//		return OnBufferIMMessageDBOperateResult(pResultData);
		//	}
    case DTK_GR_GETNICKNAME_ONID:
	case DTK_GR_GETNICKNAME_ONID_INGAME:
    {
        return OnGetNickNameOnIDResult(pResultData);
    }
    case DTK_GR_USE_KICK_PROP:  // PengJiLin, 2010-9-10, ���˿�
    {
        return OnUseKickPropResult(pResultData, TRUE);
    }
    case DTK_GR_USE_ANTI_KICK_PROP: // PengJiLin, 2010-9-10, ���߿�
    {
        return OnUseKickPropResult(pResultData, FALSE);
    }
    case DTK_GR_USER_NEW_KICK_USER_PROP:    // PengJiLin, 2010-9-13, ʹ�����˿�����
    {
        return OnNewKickUserPropResult(pResultData);        
    }
	case DTK_GR_BANK_NORMAL:
	case DTK_GR_BANK_TRANSFER:
	case DTK_GR_BANK_DEPOSIT:
	case DTK_GR_BANK_WALLET:
	case DTK_GR_BANK_QUERY_DEPOSIT:
	{
		if (m_pBankService != NULL)
		{
			m_pBankService->OnDataBaseResult(pResultData);
		}
	}
    break;
	case DTK_GR_GET_CONTEST_RESULT: //JianGuankun,2012.7.16��ȡ������ǰ�������ɼ���
		{
			return OnGetContestRankResult(pResultData);
		}
		break;
	case DTK_GR_CONTEST_BEGIN_RESULT:
		{
			OnGetContestBeginResult(pResultData);
		}
		break;
	case DTK_GR_CONTEST_APPLY:
		{
			OnGetContestApplyResult(pResultData);
		}
		break;
	case DTK_GR_CONTEST_BROADCAST:
		{
			OnBroadCastConstestInfo(pResultData);
		}break;
	case DTK_GR_CONTEST_GAME_OVER_RESULT:
		{
			OnGetContestGameOverResult(pResultData);
		}
		break;
	case DTK_GR_PROP_CHANGE:
		{
			return OnPropChangeResult(pResultData);
		}
		break;
	case DTK_GR_TIMINGMATCH_GETQUEQUEUSERS:
		{
			return OnTimingMatchBeginFillQueue(pResultData);
		}break;
	case DTK_GR_FINDDESKBUYSTATION:
		{
			return OnFindBuyDeskStationResult(pResultData);
		}break;
	}
	return false;
}

//��ȡָ����������
CGameDesk * CGameMainManage::GetDeskObject(BYTE bIndex)
{
	return 	*(m_pDesk+bIndex);
}

//wushuqun 2009.6.5
//��ս�����¼�������
bool CGameMainManage::OnBattleRoomRecord(DataBaseResultLine * pResultData)
{
	if (pResultData->uHandleRusult == DTR_GR_BATTLEROOM_TIMEOUT_ERROR)
	{
		//��ս�����Ѳ�����Чʱ����
		DL_GR_O_BattleRecordResult * battleRoomRet = (DL_GR_O_BattleRecordResult * )pResultData;

		//֪ͨ�ͻ��˻�ս�����ʱ���Ѿ���Ч
		BattleRoomRecordRes BattleRoomResult;
		memset(& BattleRoomResult,0,sizeof(BattleRoomResult));
		BattleRoomResult.uRoomID = battleRoomRet->uRoomID;
		BattleRoomResult.uRecordResult = RES_BATTLEROOM_TIMEOUT_ERROR;
		
		m_TCPSocket.SendDataBatch(&BattleRoomResult,sizeof(BattleRoomResult),MDM_GR_ROOM,ASS_GR_BATTLEROOM_RESULT,0);
	}
	return true;
}

//�����û�����
bool CGameMainManage::CleanUserInfo(CGameUserInfo * pUserInfo)
{
	//������Ϣ
	MSG_GR_R_UserLeft UserLeft;
	UserLeft.dwUserID=pUserInfo->m_UserData.dwUserID;
	if (pUserInfo->m_UserData.bGameMaster==0)
	{
		m_TCPSocket.SendDataBatch(&UserLeft,sizeof(UserLeft),MDM_GR_USER_ACTION,ASS_GR_USER_LEFT,0);
	}

	//��¼�û�����
	DL_GR_I_UserLeft DT_UserLeft;
	DT_UserLeft.dwUserID=pUserInfo->m_UserData.dwUserID;
	DT_UserLeft.uMaster=pUserInfo->m_UserData.bGameMaster;
	DT_UserLeft.dwScrPoint=pUserInfo->m_dwScrPoint;
	DT_UserLeft.dwChangePoint=pUserInfo->m_ChangePoint.dwPoint;
	DT_UserLeft.dwChangeMoney=pUserInfo->m_ChangePoint.dwMoney;
	DT_UserLeft.dwChangeTaxCom=pUserInfo->m_ChangePoint.dwTaxCom;
	DT_UserLeft.dwResultPoint=pUserInfo->m_UserData.dwPoint;
	DT_UserLeft.uWinCount=pUserInfo->m_ChangePoint.uWinCount;
	DT_UserLeft.uLostCount=pUserInfo->m_ChangePoint.uLostCount;
	DT_UserLeft.uMidCount=pUserInfo->m_ChangePoint.uMidCount;
	DT_UserLeft.uCutCount=pUserInfo->m_ChangePoint.uCutCount;
	DT_UserLeft.dwAccessLogID=pUserInfo->m_dwAccessLogID;
	DT_UserLeft.dwPlayTimeCount=pUserInfo->m_dwPlayCount;
	DT_UserLeft.uAccessIP=pUserInfo->m_UserData.dwUserIP;
	DT_UserLeft.dwOnLineTimeCount=(long int)time(NULL)-pUserInfo->m_dwLogonTime;
	m_SQLDataManage.PushLine(&DT_UserLeft.DataBaseHead,sizeof(DT_UserLeft),DTK_GR_USER_LEFT,0,0);
	SetTimer(IDT_UPDATE_ROOM_PEOPLE,1000);

	return true;
}

//���ͷ�����Ϣ
bool CGameMainManage::SendRoomMessage(UINT uSocketIndex, DWORD dwHandleID, TCHAR * szMessage, BYTE bShowStation, BYTE bFontSize, BYTE bCloseFace)
{
	//�������� 
	MSG_GA_S_Message Message;
	memset(&Message,0,sizeof(Message));

	//Ч������
	UINT uLength=lstrlen(szMessage);
	if (uLength>=sizeof(Message.szMessage)/sizeof(TCHAR)) return false;
	UINT uSendSize=sizeof(Message)-sizeof(Message.szMessage)+sizeof(TCHAR)*(uLength+1);

	//��������
	Message.bFontSize=bFontSize;
	Message.bCloseFace=bCloseFace;
	Message.bShowStation=bShowStation;
	lstrcpy(Message.szMessage,szMessage);
	if (uSocketIndex==m_InitData.uMaxPeople) m_TCPSocket.SendDataBatch(&Message,uSendSize,MDM_GR_MESSAGE,ASS_GR_SYSTEM_MESSAGE,0);
	else m_TCPSocket.SendData(uSocketIndex,&Message,uSendSize,MDM_GR_MESSAGE,ASS_GR_SYSTEM_MESSAGE,0,dwHandleID);

	return true;
}

//������Ϸ��Ϣ
bool CGameMainManage::SendGameMessage(UINT uSocketIndex, DWORD dwHandleID, TCHAR * szMessage, BYTE bShowStation, BYTE bFontSize, BYTE bCloseFace)
{
	//�������� 
	MSG_GA_S_Message Message;
	memset(&Message,0,sizeof(Message));

	//Ч������
	UINT uLength=lstrlen(szMessage);
	if (uLength>=sizeof(Message.szMessage)/sizeof(TCHAR)) return false;
	UINT uSendSize=sizeof(Message)-sizeof(Message.szMessage)+sizeof(TCHAR)*(uLength+1);

	//��������
	Message.bFontSize=bFontSize;
	Message.bCloseFace=bCloseFace;
	Message.bShowStation=bShowStation;
	lstrcpy(Message.szMessage,szMessage);
	if (uSocketIndex==m_InitData.uMaxPeople) m_TCPSocket.SendDataBatch(&Message,uSendSize,MDM_GM_MESSAGE,ASS_GM_SYSTEM_MESSAGE,0);
	else m_TCPSocket.SendData(uSocketIndex,&Message,uSendSize,MDM_GM_MESSAGE,ASS_GM_SYSTEM_MESSAGE,0,dwHandleID);

	return true;
}

//���ͱ�����Ϣ
bool CGameMainManage::SendMatchInfo(UINT uSocketIndex, DWORD dwHandleID)
{
	if ((m_uMatchUserCount!=0L)&&(m_pMatchUser!=NULL))
	{
		//��������
		UINT uBeenSendCount=0L;
		while (uBeenSendCount<m_uMatchUserCount)
		{
			UINT uSendCount=__min(m_uMatchUserCount-uBeenSendCount,MAX_SEND_SIZE/sizeof(MSG_GR_SR_MatchUser));
			m_TCPSocket.SendData(uSocketIndex,m_pMatchUser+uBeenSendCount,sizeof(MSG_GR_SR_MatchUser)*uSendCount,
				MDM_GR_MATCH_INFO,ASS_GR_MATCH_USER,0,dwHandleID);
			uBeenSendCount+=uSendCount;
		};
	}

	return true;
}

//���ͷ�����Ϣ
bool CGameMainManage::SendRoomInfo(CGameUserInfo * pUserInfo, UINT uSocketIndex, DWORD dwHandleID,DL_GR_O_LogonResult * pLogonResult)
{
	//���͵�½�ɹ���Ϣ
	MSG_GR_R_LogonResult MSGLogonResult;
	MSGLogonResult.uLessPoint=m_InitData.uLessPoint;
	MSGLogonResult.uMaxPoint=m_InitData.uMaxPoint;
	MSGLogonResult.dwGamePower=pUserInfo->m_dwGamePower;
	MSGLogonResult.dwMasterPower=pUserInfo->m_dwMasterPower;
	MSGLogonResult.pUserInfoStruct=pUserInfo->m_UserData;
	MSGLogonResult.dwRoomRule=m_InitData.dwRoomRule;
	MSGLogonResult.nPresentCoinNum = 0; ///< ���ͽ������
	MSGLogonResult.nVirtualUser = m_InitData.uVirtualUser; ///< �����������
	MSGLogonResult.pUserInfoStruct.dwTax = m_InitData.uTax;  /// add by wyl; 11-5-16

	MSGLogonResult.i64Chip = m_InitData.i64Chip;
	MSGLogonResult.i64LowChip = m_InitData.i64LowChip;
	MSGLogonResult.iLowCount = m_InitData.iLowCount;
	MSGLogonResult.i64TimeStart = m_InitData.i64TimeStart;
	MSGLogonResult.i64TimeEnd = m_InitData.i64TimeEnd;
	MSGLogonResult.iTimeout = m_InitData.iTimeout;
	MSGLogonResult.iBasePoint = m_InitData.uBasePoint;

	CString sdp;
	sdp.Format("sdp_ GRM S ���ͷ�����Ϣ-------1");
	OutputDebugString(sdp);

	//��½��Ҳ����Զ����� --2013-02-02 wangzhitu
	if (NULL != pLogonResult)
	{
		MSGLogonResult.strRecMoney = pLogonResult->strRecMoney;	
	}

	if ((m_InitData.dwRoomRule & GRR_CONTEST || m_InitData.dwRoomRule & GRR_TIMINGCONTEST ) && pUserInfo->m_UserData.iContestCount == 0 ) 
	{
		pUserInfo->m_UserData.i64ContestScore = m_InitData.i64Chip;
	}


	if (NULL != pLogonResult)
	{
		MSGLogonResult.nVirtualUser    = pLogonResult->nVirtualUser; ///< ��ʱ��ȡ���������������
		MSGLogonResult.nPresentCoinNum = pLogonResult->nPresentCoinNum; ///< ���ͽ������

		if (0 != pLogonResult->bGRMRoomID)
		{
			MSGLogonResult.bGRMRoom = true;
		}
		else
		{
			MSGLogonResult.bGRMRoom = false;
		}

		MSGLogonResult.bGRMUser = pLogonResult->bGRMUser;

		if (MSGLogonResult.bGRMUser && MSGLogonResult.bGRMRoom)
		{
			CString s = CINIFile::GetAppPath ();/////����·��
			CString temp;
			temp.Format("%s%d_s.ini",s,m_uNameID);
			CINIFile f( temp);
			CString key;
			key.Format("%s",GRM_SET_KEY);
			MSGLogonResult.GRM_Updata.bAIWinAndLostAutoCtrl = f.GetKeyVal(key,"AIWinAndLostAutoCtrl",0);
			MSGLogonResult.GRM_Updata.iAIHaveWinMoney = f.GetKeyVal(key,"AIHaveWinMoney ",__int64(0));
			MSGLogonResult.GRM_Updata.iReSetAIHaveWinMoney	= f.GetKeyVal(key,"ReSetAIHaveWinMoney ",__int64(0)); 

			MSGLogonResult.GRM_Updata.iAIWantWinMoney[0]	= f.GetKeyVal(key,"AIWantWinMoneyA1 ",__int64(500000));
			MSGLogonResult.GRM_Updata.iAIWantWinMoney[1]	= f.GetKeyVal(key,"AIWantWinMoneyA2 ",__int64(5000000));
			MSGLogonResult.GRM_Updata.iAIWantWinMoney[2]	= f.GetKeyVal(key,"AIWantWinMoneyA3 ",__int64(50000000));
			MSGLogonResult.GRM_Updata.iAIWinLuckyAt[0]	= f.GetKeyVal(key,"AIWinLuckyAtA1 ",90);
			MSGLogonResult.GRM_Updata.iAIWinLuckyAt[1]	= f.GetKeyVal(key,"AIWinLuckyAtA2 ",70);
			MSGLogonResult.GRM_Updata.iAIWinLuckyAt[2]	= f.GetKeyVal(key,"AIWinLuckyAtA3 ",50);
			MSGLogonResult.GRM_Updata.iAIWinLuckyAt[3]	= f.GetKeyVal(key,"AIWinLuckyAtA4 ",30);

			//��Ӯ���ʿ���
			MSGLogonResult.GRM_Updata.bWinProbCtrl = false;
			key.Format("%s",GRM_SET_KEY_WIN);//Ӯ���ͳ��
			int count = f.GetKeyVal(key,"count",0);
			if(count > 0 )
			{
				MSGLogonResult.GRM_Updata.bWinProbCtrl = true;
			}
			TCHAR szName[21];
			int probability = 0;
			long int dwUserID = 0;			///ID ����

			for(int i = 0; i < 20; i ++)
			{
				wsprintf(szName,"UserID%d",i);
				MSGLogonResult.GRM_Updata.dwUserID_win[i] = f.GetKeyVal(key,szName,0);

				wsprintf(szName,"prob%d",i);
				MSGLogonResult.GRM_Updata.iProb_win[i] = f.GetKeyVal(key,szName,0);
			}

			key.Format("%s",GRM_SET_KEY_LOS);//�����ͳ��
			count = f.GetKeyVal(key,"count",0);
			if(count > 0 )
			{
				MSGLogonResult.GRM_Updata.bWinProbCtrl = true;
			}

			probability = 0;
			dwUserID = 0;			///ID ����

			for(int i = 0; i < count; i ++)
			{
				wsprintf(szName,"UserID%d",i);

				MSGLogonResult.GRM_Updata.dwUserID_los[i] = f.GetKeyVal(key,szName,0);

				wsprintf(szName,"prob%d",i);
				MSGLogonResult.GRM_Updata.iProb_los[i] = f.GetKeyVal(key,szName,0);
			}

			sdp.Format("sdp_ GRM s ���ͷ�����Ϣ ���ļ��Ƿ����˽���=%d",MSGLogonResult.GRM_Updata.bAIWinAndLostAutoCtrl);
			OutputDebugString(sdp);

			for (int i=0;i<20;++i)
			{
				sdp.Format("sdp_ GRM s ��Ӯ����[Ӯ]=��%d��%ld��%d��",i,MSGLogonResult.GRM_Updata.dwUserID_win[i],MSGLogonResult.GRM_Updata.iProb_win[i]);
				OutputDebugString(sdp);
			}
			for (int i=0;i<20;++i)
			{
				sdp.Format("sdp_ GRM s ��Ӯ����[��]=��%d��%ld��%d��",i,MSGLogonResult.GRM_Updata.dwUserID_los[i],MSGLogonResult.GRM_Updata.iProb_los[i]);
				OutputDebugString(sdp);
			}
		}
	}

	if (NULL != pLogonResult)
	{
		
		m_TCPSocket.SendData(uSocketIndex,&MSGLogonResult,sizeof(MSGLogonResult),MDM_GR_LOGON,ASS_GR_LOGON_SUCCESS,
			pLogonResult->ResultHead.uHandleRusult,dwHandleID);
	}
	else
	{
		
		m_TCPSocket.SendData(uSocketIndex,&MSGLogonResult,sizeof(MSGLogonResult),MDM_GR_LOGON,ASS_GR_LOGON_SUCCESS,
			ERR_GR_LOGON_SUCCESS,dwHandleID);
	}
	




	//���������û���Ϣ
	bool bFinish=false;
	UINT uFillCount=0,uIndex=0;
	char bBuffer[MAX_SEND_SIZE];
	do
	{
		UINT uCopyPos=m_UserManage.FillOnLineUserInfo(bBuffer,sizeof(bBuffer),uIndex,uFillCount,bFinish);
		if (bFinish) 
		{
			if (m_TCPSocket.SendData(uSocketIndex,bBuffer,(UINT)uCopyPos*sizeof(UserInfoStruct),
				MDM_GR_USER_LIST,ASS_GR_ONLINE_USER,ERR_GR_LIST_FINISH,dwHandleID)!=uCopyPos*sizeof(UserInfoStruct))
			{
				return false;
			}
		}
		else 
		{
			if (m_TCPSocket.SendData(uSocketIndex,bBuffer,(UINT)uCopyPos*sizeof(UserInfoStruct),
				MDM_GR_USER_LIST,ASS_GR_ONLINE_USER,ERR_GR_LIST_PART,dwHandleID)!=uCopyPos*sizeof(UserInfoStruct))
			{			
				return false;
			}
			::Sleep(10);
		}
	} while (bFinish==false);

	//���Ͷ����û���Ϣ
	bFinish=false;
	UINT uBeginPos=0;
	do
	{
		UINT uCopyPos=m_UserManage.FillNetCutUserInfo(bBuffer,sizeof(bBuffer),uBeginPos,bFinish);
		if (bFinish) 
		{
			if (m_TCPSocket.SendData(uSocketIndex,bBuffer,(UINT)uCopyPos*sizeof(UserInfoStruct),
				MDM_GR_USER_LIST,ASS_GR_NETCUT_USER,ERR_GR_LIST_FINISH,dwHandleID)!=uCopyPos*sizeof(UserInfoStruct))
				return false;
		}
		else 
		{
			if (m_TCPSocket.SendData(uSocketIndex,bBuffer,(UINT)uCopyPos*sizeof(UserInfoStruct),
				MDM_GR_USER_LIST,ASS_GR_NETCUT_USER,ERR_GR_LIST_PART,dwHandleID)!=(UINT)uCopyPos*sizeof(UserInfoStruct))
				return false;
		}
	} while (bFinish==false);

	//����������Ϣ(�����ݿ���ȥ���������Ƿ񱻹���)
	MSG_GR_DeskStation DeskStation;
	memset(&DeskStation,0,sizeof(DeskStation));
	for (UINT i=0;i<m_uDeskCount;i++)
	{
		if ((*(m_pDesk+i))->IsLock()==true) 
			DeskStation.bDeskLock[i/8]|=(1<<(i%8));
		if ((*(m_pDesk+i))->IsVirtualLock()==true) 
			DeskStation.bVirtualDesk[i/8]|=(1<<(i%8));
		if ((*(m_pDesk+i))->IsPlayingByGameStation())
			DeskStation.bDeskStation[i/8]|=(1<<(i%8));
		if(i < 100) 
			DeskStation.iBasePoint[i]=(*(m_pDesk+i))->GetTableBasePoint();
		DeskStation.bIsBuy[i]=(*(m_pDesk+i))->m_bIsBuy;//�����Ƿ񱻹���
	}
	m_TCPSocket.SendData(uSocketIndex,&DeskStation,sizeof(DeskStation),MDM_GR_USER_LIST,ASS_GR_DESK_STATION,m_uDeskCount,dwHandleID);

	//�����û�������Ϣ
	MSG_GR_R_UserCome UserCome;
	UserCome.pUserInfoStruct=pUserInfo->m_UserData;
	if (pUserInfo->m_UserData.bGameMaster==0)
	{
		m_TCPSocket.SendDataBatch(&UserCome,sizeof(UserCome),MDM_GR_USER_ACTION,ASS_GR_USER_COME,0);
	}

	//������ɵ�½��Ϣ
	m_TCPSocket.SendData(uSocketIndex,MDM_GR_LOGON,ASS_GR_SEND_FINISH,0,dwHandleID);

	//������Ϣ
	if (m_szMsgRoomLogon[0]!=0) SendRoomMessage(uSocketIndex,dwHandleID,m_szMsgRoomLogon);

	return true;
}

//������Ӵ���
bool CGameMainManage::OnCheckConnect(DataBaseResultLine * pResultData)
{
	if (m_bRun==true) SetTimer(IDT_CHECK_DATA_CONNECT,60000L);
	return true;
}

//�����½����
bool CGameMainManage::OnRoomLogonResult(DataBaseResultLine * pResultData)
{
	CString str;
	str.Format("chshttp-----------rs=%d", pResultData->uHandleRusult);
	OutputDebugString(str);

	BYTE bHandleCode=ERR_GR_ERROR_UNKNOW;
	switch (pResultData->uHandleRusult)
	{
	case DTR_GR_CONTEST_NOSIGNUP:
	case DTR_GR_CONTEST_NOSTART:
	case DTR_GR_LOGON_SUCCESS:		//��½�ɹ�
		{
			//Ч������
			if (pResultData->LineHead.uSize!=sizeof(DL_GR_O_LogonResult)) return false;
			DL_GR_O_LogonResult * pLogonResult=(DL_GR_O_LogonResult *)pResultData;

			try
			{

				if (m_InitData.dwRoomRule & GRR_CONTEST || m_InitData.dwRoomRule & GRR_TIMINGCONTEST)
				{
					if (pResultData->uHandleRusult == DTR_GR_CONTEST_NOSIGNUP)
					{
						bHandleCode=ERR_GR_CONTEST_NOSIGNUP;
					}
					else if (pResultData->uHandleRusult == DTR_GR_CONTEST_NOSTART)
					{
						bHandleCode=ERR_GR_CONTEST_NOTSTRAT;
					}
					else
					{
					/*	if (pLogonResult->pUserInfoStruct.i64ContestScore < m_InitData.i64LowChip)
						{
							bHandleCode=ERR_GR_CONTEST_KICK;
						}*/
// 						CTime _t = CTime::GetCurrentTime();
// 						if (_t.GetTime() < m_InitData.i64TimeStart)
// 						{
// 							bHandleCode=ERR_GR_CONTEST_NOTSTRAT;
// 						}
// 						if (_t.GetTime() > m_InitData.i64TimeEnd)
// 						{
// 							bHandleCode=ERR_GR_CONTEST_OVER;
// 							break;
// 						}
					}
					
				}


				//�ж��Ƿ񻹴�������
				if (m_TCPSocket.IsConnectID(pResultData->uIndex,pResultData->dwHandleID)==false) throw DTR_GR_ERROR_UNKNOW;

				//���������û�
				CGameUserInfo * pGameUser=m_UserManage.FindOnLineUser(pLogonResult->pUserInfoStruct.dwUserID);
				if (pGameUser!=NULL)
				{
					m_TCPSocket.CloseSocket(pGameUser->m_uSocketIndex, 0);
					bHandleCode=ERR_GR_ACCOUNTS_IN_USE;
					break;
				}

				//Ч���û���Ŀ
				if ((pLogonResult->pUserInfoStruct.bMember==0)&&((m_UserManage.GetGameRoomCount())>=m_UserManage.m_OnLineUserInfo.GetPermitCount()-m_UserManage.m_OnLineUserInfo.GetVipReseverCount()))
				{
					bHandleCode=ERR_GR_PEOPLE_FULL;
					break;
				}
				//������ҽ���ʱ������һ�����룬�� 10000 �����������ڼ����Ӯ�Ķ�����������˻�����������ʣ��Ķ����㡣
				pLogonResult->pUserInfoStruct.i64Chip=10000;
				//�����û�����
				pGameUser=m_UserManage.ActiveUser(&pLogonResult->pUserInfoStruct,pResultData->uIndex,pResultData->dwHandleID,pLogonResult->dwGamePower,pLogonResult->dwMasterPower,0);
				if (pGameUser==NULL) throw DTR_GR_ERROR_UNKNOW;
				SetTimer(IDT_UPDATE_ROOM_PEOPLE,100);//20081201

				//�����û���Ϣ
				pGameUser->SetMD5Pass(pLogonResult->szMD5Pass);
				pGameUser->SetUserScrPoint(pLogonResult->pUserInfoStruct.dwPoint);

				//����Ȩ��
				if (IsLimitedTalk(pGameUser,true)==true) CUserPower::SetCanRoomTalk(pGameUser->m_dwGamePower,false);
				if (IsLimitedTalk(pGameUser,false)==true) CUserPower::SetCanGameTalk(pGameUser->m_dwGamePower,false);

				//������������� sdp2014-05-20
				//�Ȳ����Ƿ���ڸù���Ա�û������������������������
				if (!IsExistGRMUserID(pLogonResult->pUserInfoStruct.dwUserID))
				{
					CBcfFile f(CBcfFile::GetAppPath()+"GRMInfo.bcf");
					CString _UserID;
					_UserID.Format("%ld",pLogonResult->pUserInfoStruct.dwUserID);
					bool bUserGRM = f.GetKeyVal("UserID",_UserID, 0);

					if (bUserGRM)//ֻ��ȷ����Ч�����
					{
						m_GRMUserID.push_back(pLogonResult->pUserInfoStruct.dwUserID);
						pLogonResult->bGRMUser = true;
					}
				}
				else
				{
					pLogonResult->bGRMUser = true;
				}

				if (!IsExistGRMRoom(pLogonResult->bGRMRoomID))
				{
					pLogonResult->bGRMRoomID = 0;
				}

				//���ͷ�����Ϣ

				//wushuqun 2009.6.6
				//���Ӽ�ʱ��ȡ����������Ҳ���
				pLogonResult->ResultHead.uHandleRusult = bHandleCode;
				if (SendRoomInfo(pGameUser,pResultData->uIndex,pResultData->dwHandleID,pLogonResult)==false)
				{
					throw DTR_GR_ERROR_UNKNOW;
				}

				//wushuqun 2009.5.22
				//�޸Ľ�ֹ��¼���⣬�޸Ĳ���TWLoginRecord ��¼ʱ��
				::OutputDebugString("���� OnRoomLogonResult: DTR_GR_LOGON_SUCCESS");
				DL_GR_I_WriteWLoginRecord DlWriteWLogin;
				DlWriteWLogin.dwUserID = pGameUser->m_UserData.dwUserID;
				DlWriteWLogin.uRoomID = m_InitData.uRoomID;
				m_SQLDataManage.PushLine(&DlWriteWLogin.DataBaseHead,sizeof(DlWriteWLogin),DTK_GR_WRITE_WLOGINRECORD,0,0);

				//////////////

			}
			catch (...)
			{
				TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
				///////////////////////////////
				//20090203 Kylin ��ֹ�������ݿ���û���½ʧ��
				if (pLogonResult->bRegOnline==TRUE)
				{
					DL_GR_I_UnRegisterUser UnRegisterUser;
					UnRegisterUser.dwUserID=pLogonResult->pUserInfoStruct.dwUserID;
					m_SQLDataManage.PushLine(&UnRegisterUser.DataBaseHead,sizeof(UnRegisterUser),DTK_GR_UNREGISTER_ONLINE,0,0);
				}
				///////////////////////////////
				return false;
			}

			return true;
		}
	case DTR_GR_IN_OTHER_ROOM:		//����������
		{
			//Ч������
			if (pResultData->LineHead.uSize!=sizeof(DL_GR_O_LogonError)) return false;
			DL_GR_O_LogonError * pLogonResult=(DL_GR_O_LogonError *)pResultData;

			//��������
			MSG_GR_R_OtherRoom MSGOtherRoom;
			ZeroMemory(&MSGOtherRoom, sizeof(MSG_GR_R_OtherRoom));
			if (pLogonResult != NULL)
			{
				MSGOtherRoom.iRoomID = pLogonResult->uRoomID;
				lstrcpy(MSGOtherRoom.szGameRoomName,pLogonResult->szGameRoomName);
			}
			m_TCPSocket.SendData(pResultData->uIndex,&MSGOtherRoom,sizeof(MSGOtherRoom),MDM_GR_LOGON,
				ASS_GR_LOGON_ERROR,ERR_GR_IN_OTHER_ROOM,pResultData->dwHandleID);

			return true;
		}
	case DTR_GR_USER_NO_FIND: {	bHandleCode=ERR_GR_USER_NO_FIND; break; }
	case DTR_GR_USER_PASS_ERROR: { bHandleCode=ERR_GR_USER_PASS_ERROR; break; }
	case DTR_GR_USER_VALIDATA: { bHandleCode=ERR_GR_STOP_LOGON; break; }
	case DTR_GR_USER_IP_LIMITED: { bHandleCode=ERR_GR_USER_IP_LIMITED; break; }
	case DTR_GR_IP_NO_ORDER: { bHandleCode=ERR_GR_IP_NO_ORDER; break; }
	case DTR_GR_ONLY_MEMBER: { bHandleCode=ERR_GR_ONLY_MEMBER; break; }
	case DTR_GR_MATCH_LOGON: { bHandleCode=ERR_GR_MATCH_LOGON; break; }	
	case DTR_GR_OVER_TIMER:{bHandleCode=ERR_GR_TIME_OVER;break;}//��Ϸʱ�䵽��
	//wushuqun 2009.6.5
	//���ڻ�ս���ʱ����
	case DTR_GR_BATTLEROOM_TIMEOUT:
		{
			bHandleCode=ERR_GR_BATTLEROOM_OUTTIME;
			break;
		}
// 	case DTR_GR_CONTEST_NOSIGNUP:
// 		{
// 			bHandleCode = ERR_GR_CONTEST_NOSIGNUP;
// 			break;
// 		}
	case DTR_GR_CONTEST_TIMEROUT:
		{
			bHandleCode = ERR_GR_CONTEST_TIMEOUT;
			break;
		}
// 	case DTR_GR_CONTEST_NOSTART:
// 		{
// 			bHandleCode = ERR_GR_CONTEST_NOTSTRAT;
// 			break;
// 		}
	case DTR_GR_CONTEST_OVER:
		{
			bHandleCode = ERR_GR_CONTEST_OVER;
			break;
		}

	case DTR_GR_CONTEST_BEGUN:
		{
			bHandleCode = ERR_GR_CONTEST_BEGUN;
			break;
		}
	}

	//Ĭ�ϴ���
	m_TCPSocket.SendData(pResultData->uIndex,MDM_GR_LOGON,ASS_GR_LOGON_ERROR,bHandleCode,pResultData->dwHandleID);

	return true;
}

// PengJiLin, 2010-8-23, �����û�ID��ȡ�ǳ�
bool CGameMainManage::OnGetNickNameOnIDResult(DataBaseResultLine * pResultData)
{
    BYTE bHandleCode=ERR_GR_ERROR_UNKNOW;
	
	//add by lxl 2010-11-17 ��Ϸ�л�ȡ�ǳ����⴦��
	int nMainID = MDM_GR_ROOM;
	int nAssistantID = ASS_GR_GET_NICKNAME_ONID;
	if(pResultData->uHandleKind == DTK_GR_GETNICKNAME_ONID_INGAME)
	{
		nMainID = MDM_GR_ROOM2GAME;
		nAssistantID = ASS_GR_GET_NICKNAME_ONID_INGAME;
	}

    switch (pResultData->uHandleRusult)
    {
    case DTR_GR_GETNICKNAME_SUCCESS:
        {
            //Ч������
            if (pResultData->LineHead.uSize!=sizeof(DL_GR_O_GetNickNameOnIDResult)) return false;
            DL_GR_O_GetNickNameOnIDResult* pGetNickNameOnID =(DL_GR_O_GetNickNameOnIDResult *)pResultData;

            //��������
            bHandleCode = RES_GR_GETNICKNAME_SUCCESS;
            MSG_GR_S_GetNickNameOnID_t stGetNickNameOnID;
            stGetNickNameOnID.iUserID = pGetNickNameOnID->iUserID;
            lstrcpy(stGetNickNameOnID.szNickName, pGetNickNameOnID->szNickName);
            m_TCPSocket.SendData(pResultData->uIndex,&stGetNickNameOnID,sizeof(stGetNickNameOnID),
                            nMainID, nAssistantID,bHandleCode,pResultData->dwHandleID);

            return true;
        }
        break;
    case DTR_GR_GETNICKNAME_NOTEXIST:
        {
            bHandleCode=RES_GR_GETNICKNAME_NOTEXIST;
        }
        break;
    case DTR_GR_GETNICKNAME_ISNULL:
        {
            bHandleCode=RES_GR_GETNICKNAME_ISNULL;
        }
        break;
    default:
        {
            bHandleCode=ERR_GR_ERROR_UNKNOW;
        }
        break;
    }
    m_TCPSocket.SendData(pResultData->uIndex, nMainID, nAssistantID, 
                        bHandleCode, pResultData->dwHandleID);

    return true;
}

// PengJiLin, 2010-9-10, ���˿������߿�����
bool CGameMainManage::OnUseKickPropResult(DataBaseResultLine * pResultData, BOOL bIsKickUser)
{
    int iHandleIDNum = ASS_GM_USE_KICK_PROP;
    if(FALSE == bIsKickUser)
    {
        iHandleIDNum = ASS_GM_USE_ANTI_KICK_PROP;
    }

    BYTE bHandleCode=ERR_GR_ERROR_UNKNOW;
    switch (pResultData->uHandleRusult)
    {
    case DTR_GR_USE_KICKPROP_NULL:      // û�е���
        {
            bHandleCode = ERR_GR_KICK_PROP_NULL;
        }
        break;
    case DTR_GR_USE_KICKPROP_SET_ERROR: // ����ʱ�����
        {
            bHandleCode = ERR_GR_KICK_SET_TIME_FAIL;
        }
        break;
    case DTR_GR_USE_KICKPROP_SET_SUCCESS:   // ����ʱ��ɹ�
        {
            bHandleCode = ERR_GR_KICK_SET_TIME_SUCCESS;
        }
        break;
    }

    DL_GR_O_UseKickProp* pUseKickProp = (DL_GR_O_UseKickProp*)pResultData;
    MSG_GR_RS_KickProp KickProp;
    memset(&KickProp, 0, sizeof(KickProp));
    KickProp.dwUserID = pUseKickProp->dwUserID;
    KickProp.iPropID = pUseKickProp->iPropID;
    KickProp.iTotalTime = pUseKickProp->iTotalTime;

    m_TCPSocket.SendData(pResultData->uIndex, &KickProp, sizeof(KickProp), MDM_GM_GAME_FRAME, 
                         iHandleIDNum, bHandleCode, pResultData->dwHandleID);
    return true;
}

// PengJiLin, 2010-9-13, ʹ�����˿�����
bool CGameMainManage::OnNewKickUserPropResult(DataBaseResultLine * pResultData)
{
    DL_GR_O_UseNewKickUserProp* pNewKickProp = (DL_GR_O_UseNewKickUserProp*)pResultData;

    BYTE bHandleCode = ERR_GR_ERROR_UNKNOW;
    switch (pResultData->uHandleRusult)
    {
    case DTR_GR_NEW_KICKUSER_SUCCESS:
        bHandleCode = ERR_GR_NEW_KICKUSER_SUCCESS;
        break;
    case DTR_GR_NEW_KICKUSER_NOTIME:
        bHandleCode = ERR_GR_NEW_KICKUSER_NOTIME;
        break;
    case DTR_GR_NEW_KICKUSER_HAD_ANTI:
        bHandleCode = ERR_GR_NEW_KICKUSER_HAD_ANTI;
        break;
    case DTR_GR_NEW_KICKUSER_HAD_VIP:
        bHandleCode = ERR_GR_NEW_KICKUSER_HAD_VIP;
        break;
    }

    _TAG_NEW_KICKUSER stKick;
    stKick.dwUserID = pNewKickProp->dwUserID;
    stKick.dwDestID = pNewKickProp->dwDestID;

    // �����ɹ�
    if(ERR_GR_NEW_KICKUSER_SUCCESS == bHandleCode)
    {
        CGameUserInfo * pUserInfo = m_UserManage.GetOnLineUserInfo(pResultData->uIndex);
        if(pUserInfo == NULL) return true;
        CGameUserInfo * pDestUserInfo = m_UserManage.FindOnLineUser(pNewKickProp->dwDestID);
        if(pDestUserInfo == NULL) return true;
        if(pUserInfo->m_UserData.bDeskNO == 255)return true;

        CGameDesk *pDesk = GetDeskObject(pUserInfo->m_UserData.bDeskNO);
        if(pDesk == NULL) return true;

        if(pDesk->IsPlayingByGameStation()) //��Ϸ������
        {
            bHandleCode = ERR_GR_NEW_KICKUSER_PLAYING;
        }
        else
        {
            if (pDestUserInfo->m_UserData.bUserState==USER_WATCH_GAME) 
            { 
                pDesk->WatchUserLeftDesk(pDestUserInfo->m_UserData.bDeskStation,pDestUserInfo); 
            } 
            else  
            { 
                pDesk->UserLeftDesk(pDestUserInfo->m_UserData.bDeskStation,pDestUserInfo); 
            }
        } 
    }

    // ���Լ�����Ϣ
    m_TCPSocket.SendData(pResultData->uIndex, &stKick, sizeof(stKick), MDM_GR_PROP, ASS_PROP_NEW_KICKUSER, 
                         bHandleCode, pResultData->dwHandleID);

    // ��Ŀ�귢��Ϣ
    m_TCPSocket.SendData(pNewKickProp->dwDestIndex, &stKick, sizeof(stKick), MDM_GR_PROP, ASS_PROP_NEW_KICKUSER, 
                        bHandleCode, pNewKickProp->dwDestHandleID);

    return true;
}


// PengJiLin, 2010-9-13, ���˿����˹���
bool CGameMainManage::OnNewKickUserProp(NetMessageHead *pNetHead, void* pData, UINT uSize, 
                                        ULONG uAccessIP, UINT uIndex, DWORD dwHandleID)
{
    if(uSize != sizeof(_TAG_NEW_KICKUSER))return false;
    _TAG_NEW_KICKUSER* pNewKickUser = (_TAG_NEW_KICKUSER*)pData;

    CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
    if(pUserInfo == NULL) return false;
    CGameUserInfo* pDestUserInfo = m_UserManage.FindOnLineUser(pNewKickUser->dwDestID);
    if(NULL == pDestUserInfo) return false;

    DL_GR_I_NewKickUserProp KickProp;
    memset(&KickProp, 0, sizeof(KickProp));
    KickProp.dwUserID = pNewKickUser->dwUserID;
    KickProp.dwDestID = pNewKickUser->dwDestID;
    KickProp.dwDestIndex = pDestUserInfo->m_uSocketIndex;
    KickProp.dwDestHandleID = pDestUserInfo->m_dwHandleID;
    m_SQLDataManage.PushLine(&KickProp.DataBaseHead, sizeof(KickProp), DTK_GR_USER_NEW_KICK_USER_PROP, 
                              uIndex, dwHandleID);
    return true;
}

//Ǯ����
bool CGameMainManage::OnAboutMoneyResult(DataBaseResultLine * pResultData, UINT uCode)
{
	// ����ͬ��ָ��
	UINT uCmd = ASS_GR_OPEN_WALLET;
	if (DTK_GR_DEMAND_MONEY_IN_GAME==uCode)
	{
		uCmd = ASS_GR_OPEN_WALLET_INGAME;
	}
	BYTE bHandleCode=ERR_GR_ERROR_UNKNOW;
	switch (pResultData->uHandleRusult)
	{
	case DTR_GR_OPEN_WALLET_ERROR://��Ǯ�����
		{
			bHandleCode=ASS_GR_OPEN_WALLET_ERROR;
			m_TCPSocket.SendData(pResultData->uIndex, MDM_GR_MONEY, uCmd, bHandleCode, pResultData->dwHandleID);
			break;
		}
	case DTR_GR_OPEN_WALLET_ERROR_PSW://��Ǯ������������
		{
			bHandleCode = ASS_GR_OPEN_WALLET_ERROR_PSW;
			m_TCPSocket.SendData(pResultData->uIndex, MDM_GR_MONEY, uCmd, bHandleCode, pResultData->dwHandleID);
			break;
		}		
	case DTR_GR_OPEN_WALLET_SUC://��Ǯ��ɹ�
		{
			bHandleCode=ASS_GR_OPEN_WALLET_SUC;
			DL_GR_O_OpenWalletResult *pOpenWalletResult=(DL_GR_O_OpenWalletResult*) pResultData;
			MSG_GR_UserBank UserBank = pOpenWalletResult->stUserBank;

			//�����к�����ڴ��е�������ֵ
			//Added by JianGuankun 2012.1.10
			CGameUserInfo* pUserInfo = m_UserManage.FindOnLineUser(UserBank.dwUserID);
			if (pUserInfo)
			{
				pUserInfo->m_UserData.i64Bank = UserBank.i64Bank;
			}
			//End Add

// 			memset(&UserBank,0,sizeof(UserBank));
// 			UserBank.i64Bank=pOpenWalletResult->stUserBank.i64Bank;
			m_TCPSocket.SendData(pResultData->uIndex,&UserBank,sizeof(UserBank),MDM_GR_MONEY, uCmd, bHandleCode,pResultData->dwHandleID);
			break;
		}

	}

	return true;
}

//���������ݷ���������sdp
bool CGameMainManage::OnGetBankRebateResponse(DataBaseResultLine* pResultData)
{
	DL_GR_O_RebateUpDateStruct *pCmd=(DL_GR_O_RebateUpDateStruct*)pResultData;

	m_iVIP_Rate = pCmd->iVIP_Rate;

	CString sdp;
	sdp.Format("sdp_ ת�� ���� �������ݸ��� �洢���� ��Сת�����=%I64d,vip������=%f",pCmd->iMin_money,pCmd->iVIP_Rate);
	OutputDebugString(sdp);

	return true;
}

//����ҷ�����ѯ���ݷ���������sdp
bool CGameMainManage::OnGetBankUserRebateResponse(DataBaseResultLine* pResultData, UINT uCode)
{
	// ����ͬ��ָ��
	UINT uCmd = ASS_GR_TRANSFER_UPDATE_USER_REBATE;
	if (DTK_GR_BANK_UPDATE_USER_REBATE_INGAME==uCode)
	{
		uCmd = ASS_GR_TRANSFER_UPDATE_USER_REBATE_INGAME;
	}
	DL_GR_O_UserRebateUpDateStruct *pCmd=(DL_GR_O_UserRebateUpDateStruct*)pResultData;

	MSG_GR_UserRebateUpDate cmd;//���������ݷ�������
	cmd.iUserID = pCmd->iUserID;				//���ID
	cmd.iTx_Money = pCmd->iTx_Money;			//ʣ�෵����Ŀ
	cmd.iTx_Smony = pCmd->iTx_Smony;			//�Ѿ�ȡ�ߵ���Ŀ

	m_TCPSocket.SendData(pResultData->uIndex, &cmd, sizeof(MSG_GR_UserRebateUpDate), MDM_GR_MONEY, uCmd, 0, pResultData->dwHandleID);

	CString sdp;
	sdp.Format("sdp_ ת�� ���� ��ҷ������ݸ��� �������� ���ID=%d,ʣ�෵����Ŀ=%d,�Ѿ�ȡ�ߵ���Ŀ=%d",cmd.iUserID,cmd.iTx_Money,cmd.iTx_Smony);
	OutputDebugString(sdp);

	return true;
}

//����ҷ����޸Ľ������������sdp
bool CGameMainManage::OnGetBankUserSetRebateResponse(DataBaseResultLine* pResultData, UINT uCode)
{
	// ����ͬ��ָ��
	UINT uCmd = ASS_GR_TRANSFER_SET_REBATE_RES;
	if (DTK_GR_BANK_SET_USER_REBATE_INGAME==uCode)
	{
		uCmd = ASS_GR_TRANSFER_SET_REBATE_RES_INGAME;
	}
	DL_GR_O_UserRebateSetStruct *pCmd=(DL_GR_O_UserRebateSetStruct*)pResultData;

	MSG_GR_UserRebateSetResult cmd;//���������ݷ�������
	cmd.iUserID = pCmd->iUserID;					//���ID
	cmd.iMoney = pCmd->iMoney;						//��������Ŀ
	cmd.bTag = pCmd->bTag;							//0 �棬1 ȡ
	cmd.bResult = pCmd->bResult;					//������
	CopyMemory(cmd.Msg, pCmd->Msg, sizeof(cmd.Msg));//��Ϣ

	m_TCPSocket.SendData(pResultData->uIndex, &cmd, sizeof(MSG_GR_UserRebateSetResult), MDM_GR_MONEY, uCmd, 0, pResultData->dwHandleID);

	CString sdp;
	sdp.Format("sdp_ ת�� ���� ��ҷ����޸Ľ�� �������� ���ID=%d,ʣ�෵����Ŀ=%d,(1�ɹ���-1ʧ�ܣ�%d��)(��Ϣ��%s)",cmd.iUserID,cmd.iMoney,cmd.bResult,cmd.Msg);
	OutputDebugString(sdp);

	if (true == pCmd->bResult)//ִ�гɹ��Ű����ˢ������
	{
		UINT uHandleKind = DTK_GR_BANK_UPDATE_USER_REBATE;
		if (DTK_GR_BANK_SET_USER_REBATE_INGAME==uCode)
		{
			uHandleKind = DTK_GR_BANK_UPDATE_USER_REBATE_INGAME;
		}

		//��ѯ��ҷ������ݲ���֪���
		DL_GR_I_UserRebateUpDateStruct UserRebate;
		UserRebate.iUserID = pCmd->iUserID;//��ֵ���id
		m_SQLDataManage.PushLine(&UserRebate.DataBaseHead, sizeof(UserRebate), uHandleKind, pResultData->uIndex, 0);
	}

	return true;
}

//���䣭��Ǯ��
bool CGameMainManage::OnCheckInMoney(DataBaseResultLine * pResultData, UINT uCode)
{
	// ����ͬ��ָ��
	UINT uCmd = ASS_GR_CHECK_IN;
	if (DTK_GR_CHECKIN_MONEY_INGAME==uCode)
	{
		uCmd = ASS_GR_CHECK_IN_INGAME;
	}

	BYTE bHandleCode=ERR_GR_ERROR_UNKNOW;
	switch (pResultData->uHandleRusult)
	{
	case DTR_GR_ERROR_UNKNOW://
		{
			bHandleCode=ASS_GR_CHECKIN_ERROR;
			m_TCPSocket.SendData(pResultData->uIndex, MDM_GR_MONEY, uCmd, bHandleCode, pResultData->dwHandleID);
			break;
		}
	case DTR_GR_CHECKIN_MONEY_INV:
		{
			bHandleCode=ASS_GR_CHECKIN_ERROR_PLAYING;
			m_TCPSocket.SendData(pResultData->uIndex, MDM_GR_MONEY, uCmd, bHandleCode, pResultData->dwHandleID);
			break;
		}
	case DTR_GR_CHECKIN_MONEY_SUC://����ɹ�
		{
			bHandleCode=ASS_GR_CHECKIN_SUC;
			//Ч������
			if (pResultData->LineHead.uSize!=sizeof(DL_GR_O_CheckOutMoney)) 
			{
				bHandleCode=ASS_GR_CHECKIN_ERROR;
				m_TCPSocket.SendData(pResultData->uIndex, MDM_GR_MONEY, uCmd, bHandleCode, pResultData->dwHandleID);
				return false;
			}
			DL_GR_O_CheckOutMoney * pCheckInResult=(DL_GR_O_CheckOutMoney *)pResultData;

			//�޸��û�����

			CGameUserInfo * pUserInfo=m_UserManage.FindOnLineUser(pCheckInResult->dwUserID);
			if (pUserInfo==NULL) return false;
			else
			{
				pUserInfo->m_UserData.i64Money-=pCheckInResult->i64CheckOut;
				pUserInfo->m_UserData.i64Bank+=pCheckInResult->i64CheckOut;//2008-06-24,Fred Huang
			}

			MSG_GR_CheckMoney CheckInMoney;
			memset(&CheckInMoney,0,sizeof(CheckInMoney));
			CheckInMoney.i64CheckOut=pCheckInResult->i64CheckOut;
			CheckInMoney.i64MoneyInBank=pCheckInResult->i64MoneyInBank;
			CheckInMoney.i64MoneyInRoom=pCheckInResult->i64MoneyInRoom;
			CheckInMoney.dwUserID=pCheckInResult->dwUserID;
			CheckInMoney.uGameID = m_KernelData.uNameID;
			m_TCPSocket.SendDataBatch(&CheckInMoney,sizeof(CheckInMoney),MDM_GR_MONEY,uCmd,bHandleCode);
			break;
		}
	}

	return true;
}

//���䣼��Ǯ��
bool CGameMainManage::OnCheckOutMoney(DataBaseResultLine * pResultData, UINT uCode)
{
	// ����ͬ��ָ��
	UINT uCmd = ASS_GR_CHECK_OUT;
	if (DTK_GR_CHECKOUT_MONEY_INGAME==uCode)
	{
		uCmd = ASS_GR_CHECK_OUT_INGAME;
	}

	BYTE bHandleCode=ERR_GR_ERROR_UNKNOW;
	switch (pResultData->uHandleRusult)
	{
	case DTR_GR_ERROR_UNKNOW://
		{
			bHandleCode=ASS_GR_CHECKOUT_ERROR;
			m_TCPSocket.SendData(pResultData->uIndex, MDM_GR_MONEY, uCmd, bHandleCode, pResultData->dwHandleID);
			break;
		}
	case DTR_GR_CHECKOUT_MONEY_INV:
		{
			bHandleCode=ASS_GR_CHECKOUT_ERROR_PLAYING;
			m_TCPSocket.SendData(pResultData->uIndex, MDM_GR_MONEY, uCmd, bHandleCode, pResultData->dwHandleID);
			break;
		}
	case DTR_GR_CHECKOUT_MONEY_SUC://ȡ���ɹ�
		{
			bHandleCode=ASS_GR_CHECKOUT_SUC;
			//Ч������
			if (pResultData->LineHead.uSize!=sizeof(DL_GR_O_CheckOutMoney)) 
			{
				bHandleCode=ASS_GR_CHECKOUT_ERROR;
				m_TCPSocket.SendData(pResultData->uIndex, MDM_GR_MONEY, uCmd, bHandleCode, pResultData->dwHandleID);
				return false;
			}
			DL_GR_O_CheckOutMoney * pCheckOutResult=(DL_GR_O_CheckOutMoney *)pResultData;


			CGameUserInfo * pUserInfo=m_UserManage.FindOnLineUser(pCheckOutResult->dwUserID);
			if (pUserInfo==NULL) return false;
			else
			{
				pUserInfo->m_UserData.i64Money+=pCheckOutResult->i64CheckOut;
				pUserInfo->m_UserData.i64Bank-=pCheckOutResult->i64CheckOut;//2008-06-24,Fred Huang
			}

			MSG_GR_CheckMoney CheckOutMoney;
			memset(&CheckOutMoney,0,sizeof(CheckOutMoney));
			CheckOutMoney.i64CheckOut=pCheckOutResult->i64CheckOut;
			CheckOutMoney.i64MoneyInBank=pCheckOutResult->i64MoneyInBank;
			CheckOutMoney.i64MoneyInRoom=pCheckOutResult->i64MoneyInRoom;
			CheckOutMoney.dwUserID=pCheckOutResult->dwUserID;
			CheckOutMoney.uGameID = m_KernelData.uNameID;
			m_TCPSocket.SendDataBatch(&CheckOutMoney,sizeof(CheckOutMoney),MDM_GR_MONEY,uCmd,bHandleCode);
			break;
		}
	}

	return true;
}
//ת�ʼ�¼���
bool CGameMainManage::OnTransferRecord(DataBaseResultLine * pResultData, UINT uCode)
{
	UINT uCmd = ASS_GR_TRANSFER_RECORD;
	if (DTK_GR_TRANSFER_RECORD_INGAME == uCode)
	{
		uCmd = ASS_GR_TRANSFER_RECORD_INGAME;
	}
	if (pResultData->LineHead.uSize!=sizeof(DL_GR_O_TransferRecord_t)) 
	{
		return false;
	}
	DL_GR_O_TransferRecord_t *pTransferRecordResult = (DL_GR_O_TransferRecord_t *)pResultData;
	MSG_GR_R_TransferRecord_t transferRecord;
	transferRecord.nSeriNo			= pTransferRecordResult->transferRecord.nSeriNo;
	transferRecord.dwUserID			= pTransferRecordResult->transferRecord.dwUserID;
	transferRecord.destUserID		= pTransferRecordResult->transferRecord.destUserID;
	transferRecord.i64Money			= pTransferRecordResult->transferRecord.i64Money;
	transferRecord.i64ActualTransfer	= pTransferRecordResult->transferRecord.i64ActualTransfer;
	transferRecord.oleDateTime		= pTransferRecordResult->transferRecord.oleDateTime;

	BYTE bHandleCode=ASS_GR_TRANSFER_SUC;

	m_TCPSocket.SendData(pResultData->uIndex, &transferRecord, sizeof(transferRecord), MDM_GR_MONEY, uCmd, bHandleCode, pResultData->dwHandleID);

	return true;
}

/// �޸�����
bool CGameMainManage::OnChangePasswd(DataBaseResultLine * pResultData, UINT uCode)
{
	// ����ͬ��ָ��
	UINT uCmd = ASS_GR_CHANGE_PASSWD;
	if (DTK_GR_CHANGE_PASSWD_INGAME==uCode)
	{
		uCmd = ASS_GR_CHANGE_PASSWD_INGAME;
	}
	BYTE bHandleCode=ERR_GR_ERROR_UNKNOW;
	if (pResultData->LineHead.uSize!=sizeof(DL_GR_O_ChangePasswd_t)) 
	{
		bHandleCode=ASS_GR_PASSWORD_ERROR;
		m_TCPSocket.SendData(pResultData->uIndex, MDM_GR_MONEY, uCmd, bHandleCode, pResultData->dwHandleID);
		return true;
	}
	
	if (pResultData->uHandleRusult != DTR_GR_OPEN_WALLET_SUC)
	{
		bHandleCode=ASS_GR_PASSWORD_ERROR;
		m_TCPSocket.SendData(pResultData->uIndex, MDM_GR_MONEY, uCmd, bHandleCode, pResultData->dwHandleID);
	}
	else
	{
		bHandleCode=ASS_GR_OPEN_WALLET_SUC;
		m_TCPSocket.SendData(pResultData->uIndex, MDM_GR_MONEY, uCmd, bHandleCode, pResultData->dwHandleID);
	}
	
	return true;
}

/// ת��
bool CGameMainManage::OnTransferMoney(DataBaseResultLine * pResultData, UINT uCode)
{
	// ����ͬ��ָ��
	UINT uCmd = ASS_GR_TRANSFER_MONEY;
	if (DTK_GR_TRANSFER_MONEY_INGAME==uCode)
	{
		uCmd = ASS_GR_TRANSFER_MONEY_INGAME;
	}

	BYTE bHandleCode=ERR_GR_ERROR_UNKNOW;
	if (pResultData->LineHead.uSize!=sizeof(DL_GR_O_TransferMoney)) 
	{
		bHandleCode=ASS_GR_TRANSFER_ERROR;
		m_TCPSocket.SendData(pResultData->uIndex, MDM_GR_MONEY, uCmd, bHandleCode, pResultData->dwHandleID);
		return false;
	}
	DL_GR_O_TransferMoney * pTransferMoney=(DL_GR_O_TransferMoney *)pResultData;
	MSG_GR_S_TransferMoney TransferMoney;
	TransferMoney.destUserID = pTransferMoney->stTransfer.destUserID;
	TransferMoney.i64Money = pTransferMoney->stTransfer.i64Money;
	TransferMoney.UserID = pTransferMoney->stTransfer.UserID;
	TransferMoney.bUseDestID = pTransferMoney->stTransfer.bUseDestID;
	strcpy(TransferMoney.szNickName, pTransferMoney->stTransfer.szNickName);		//�����ǳ���Ϣ add by lxl 2010-11-10
	strcpy(TransferMoney.szDestNickName, pTransferMoney->stTransfer.szDestNickName);
	TransferMoney.i64ActualTransfer = pTransferMoney->stTransfer.i64ActualTransfer;
	switch (pResultData->uHandleRusult)
	{
	case DTR_GR_OPEN_WALLET_ERROR_PSW: //�������
		{
			bHandleCode=ASS_GR_PASSWORD_ERROR;
			m_TCPSocket.SendData(pResultData->uIndex, &TransferMoney, sizeof(TransferMoney), MDM_GR_MONEY, uCmd, bHandleCode, pResultData->dwHandleID);
			break;
		}
	case DTR_GR_TRANSFER_TOTAL_NOT_ENOUGH:	///< ���д��̫�٣�������ת��
		{
			bHandleCode=ASS_GR_TRANSFER_TOTAL_LESS;
			m_TCPSocket.SendData(pResultData->uIndex, &TransferMoney, sizeof(TransferMoney), MDM_GR_MONEY, uCmd, bHandleCode, pResultData->dwHandleID);
			break;
		}
	case DTR_GR_TRANSFER_TOO_LESS:			///<����ת�ʶ�̫С
		{
			bHandleCode=ASS_GR_TRANSFER_TOO_LESS;
			m_TCPSocket.SendData(pResultData->uIndex, &TransferMoney, sizeof(TransferMoney), MDM_GR_MONEY, uCmd, bHandleCode, pResultData->dwHandleID);
			break;
		}
	case DTR_GR_TRANSFER_MULTIPLE:			///<����ת�ʶ������ĳ����������
		{
			bHandleCode=ASS_GR_TRANSFER_MULTIPLE;
			m_TCPSocket.SendData(pResultData->uIndex, &TransferMoney, sizeof(TransferMoney), MDM_GR_MONEY, uCmd, bHandleCode, pResultData->dwHandleID);
			break;
		}
	case DTR_GR_TRANSFER_NO_ENOUGH_MONEY:	///<���д��㱾��ת��
		{
			bHandleCode=ASS_GR_TRANSFER_NOT_ENOUGH;
			m_TCPSocket.SendData(pResultData->uIndex, &TransferMoney, sizeof(TransferMoney), MDM_GR_MONEY, uCmd, bHandleCode, pResultData->dwHandleID);
			break;
		}
	case DTR_GR_TRANSFER_TOO_MANY_TIME:  ///< ɢ���䵱��ת������ﵽһ���޶�
		{
			bHandleCode = ASS_GR_TRANSFER_TOO_MANY_TIME;
			m_TCPSocket.SendData(pResultData->uIndex, &TransferMoney, sizeof(TransferMoney), MDM_GR_MONEY, uCmd, bHandleCode, pResultData->dwHandleID);
			break;
		}
	case DTR_GR_TRANSFER_MONEY_NO_DEST:		///< Ŀ�겻����
		{
			bHandleCode=ASS_GR_TRANSFER_NO_DEST;
			m_TCPSocket.SendData(pResultData->uIndex, &TransferMoney, sizeof(TransferMoney), MDM_GR_MONEY, uCmd, bHandleCode, pResultData->dwHandleID);
			break;
		}
	case DTR_GR_ERROR_UNKNOW://ת��ʧ��
		{
			bHandleCode=ASS_GR_TRANSFER_ERROR;
			m_TCPSocket.SendData(pResultData->uIndex, &TransferMoney, sizeof(TransferMoney), MDM_GR_MONEY, uCmd, bHandleCode, pResultData->dwHandleID);
			break;
		}
	case DTR_GR_TRANSFER_MONEY_SUC://ת�ʳɹ�
		{
			bHandleCode=ASS_GR_TRANSFER_SUC;
			//Ч������
			CGameUserInfo * pUserInfo=m_UserManage.FindOnLineUser(pTransferMoney->stTransfer.UserID);
			if (pUserInfo==NULL)
			{
				return false;
			}

			m_TCPSocket.SendData(pResultData->uIndex,&TransferMoney,sizeof(TransferMoney),MDM_GR_MONEY,uCmd,bHandleCode, pResultData->dwHandleID);
			///// Ҳ��ת��Ŀ���û�������Ϣ
			//CGameUserInfo *pDestUserInfo = m_UserManage.FindOnLineUser(pTransferMoney->stTransfer.destUserID);
			//if (pDestUserInfo !=NULL)
			//{
			//	m_TCPSocket.SendData(pDestUserInfo->m_uSocketIndex,&TransferMoney,sizeof(TransferMoney),MDM_GR_MONEY,uCmd,bHandleCode, pResultData->dwHandleID);
			//}

			//ת�˳ɹ�������ж�����Ƿ�Ϊvip�����з�������
			CString stime;
			stime.Format("%d",CTime::GetCurrentTime());
			int curtime=atoi(stime);
			if(pUserInfo->m_UserData.iVipTime>curtime)
			{
				DL_GR_I_UserRebateSetStruct cmd;
				cmd.bTag = 0;
				cmd.iUserID = pTransferMoney->stTransfer.UserID;
				double iRate = (pTransferMoney->stTransfer.i64Money - pTransferMoney->stTransfer.i64ActualTransfer) * m_iVIP_Rate / 100;
				cmd.iMoney = iRate;

				CString sdp;
				sdp.Format("sdp_ ת�� ���� ת�˳ɹ�������ж�����Ƿ�Ϊvip�����з������� %d,%lf",cmd.iMoney, iRate);
				OutputDebugString(sdp);

				UINT uHandleKind = DTK_GR_BANK_SET_USER_REBATE;
				if (DTK_GR_TRANSFER_MONEY_INGAME==uCode)
				{
					uHandleKind = DTK_GR_BANK_SET_USER_REBATE_INGAME;
				}

				m_SQLDataManage.PushLine(&cmd.DataBaseHead,sizeof(DL_GR_I_UserRebateSetStruct),
					uHandleKind,pResultData->uIndex,pResultData->dwHandleID);
			}

			break;
		}
	}

	return true;
}
bool CGameMainManage::SendUserMoenyByTimesResult(DataBaseResultLine * pResultData)
{

	//���ͽ�ҳɹ�
	if (pResultData->uHandleRusult == 0)
	{
		//BYTE bHandleCode = 0;
		//
		//SendUserMoneyByTimes senResult;
		//memset(&senResult,0,sizeof(senResult));
		////memcpy(&senResult,pResultData,sizeof(senResult));
		//DL_GR_O_SendMonet_By_Times* pSendMoeny = (DL_GR_O_SendMonet_By_Times*)pResultData;
		//senResult.dwAllSendTImes = pSendMoeny->dwAllSendTImes;
		//senResult.dwSendFailedCause = pSendMoeny->dwSendFailedCause;
		//senResult.dwSendGameMoney = pSendMoeny->dwSendGameMoney;
		//senResult.dwSendTimes = pSendMoeny->dwSendTimes;
		//senResult.dwSrcGameMoney = pSendMoeny->dwSrcGameMoney;
		//senResult.dwSrcMoneyInBank = pSendMoeny->dwSrcMoneyInBank;
		//senResult.dwUserID = pSendMoeny->dwUserID;
		//CGameUserInfo* pGameUser = m_UserManage.FindOnLineUser(senResult.dwUserID);
		//if (pGameUser != NULL)
		//{
		//	pGameUser->SetUserSendedMoeny(senResult.dwSendGameMoney);
		//	m_TCPSocket.SendDataBatch(&senResult,sizeof(senResult),MDM_GR_MONEY,ASS_GR_SENDMONEY_TIMES,bHandleCode);
		//}
		
		///< �Ѿ���void CGameDesk::PresentCoin()�з��͸��ͻ��ˡ�
	}
	return true;

}

// PengJiLin, 2011-4-15, ����ʱ���������ͽ��
bool CGameMainManage::OnSendMoneyOnTimesAndCounts(DataBaseResultLine * pResultData)
{
    SendMoneyOnTimesAndCounts sendResult;
    memset(&sendResult,0,sizeof(sendResult));

    DL_GR_O_SendMoney_On_TC* pSendMoeny = (DL_GR_O_SendMoney_On_TC*)pResultData;

    sendResult.dwUserID = pSendMoeny->dwUserID;
    sendResult.dwGetMoney = pSendMoeny->dwGetMoney;
    sendResult.dwMoneyOnTimes = pSendMoeny->dwMoneyOnTimes;
    sendResult.dwMoneyOnCounts = pSendMoeny->dwMoneyOnCounts;
    sendResult.dwTimesNeed = pSendMoeny->dwTimesNeed;
    sendResult.dwCountsNeed = pSendMoeny->dwCountsNeed;	

    
    CGameUserInfo* pGameUser = m_UserManage.FindOnLineUser(sendResult.dwUserID);
    if (pGameUser != NULL)
    {
			
		if (pSendMoeny->strAutoSendMoney.bISOpen)
		{
			m_TCPSocket.SendDataBatch(&sendResult,sizeof(sendResult),MDM_GR_MONEY,ASS_GR_SENDMONEY_TIMES,0);
		}

		//2013-01-29 ������Զ����ͣ�ˢ���û������Ϣ
		if (ASS_RECEIVE == pSendMoeny->strAutoSendMoney.iResultCode)
		{
			CString str("");
			
			MSG_GR_R_UserPoint strMSGUserPoint;
			ZeroMemory(&strMSGUserPoint, sizeof(strMSGUserPoint));
			strMSGUserPoint.dwUserID = pSendMoeny->dwUserID;
			strMSGUserPoint.dwMoney = pSendMoeny->strAutoSendMoney.i64Money;
			strMSGUserPoint.strAutoSendMoney = pSendMoeny->strAutoSendMoney;
			pGameUser->SetUserSendedMoeny(strMSGUserPoint.dwMoney); 
			str.Format("send to client,userid=%d,getmoney=%d,ResultCode=%d,GetNum=%d",strMSGUserPoint.dwUserID,pSendMoeny->strAutoSendMoney.i64Money,
				pSendMoeny->strAutoSendMoney.iResultCode,pSendMoeny->strAutoSendMoney.iCount);
			OutputDebugString(str);
			m_TCPSocket.SendDataBatch(&strMSGUserPoint,sizeof(strMSGUserPoint),MDM_GR_ROOM,ASS_GR_USER_POINT,0);			
		}        
        
    }

    return true;
}

bool CGameMainManage::OnGetContestApplyResult(DataBaseResultLine *pResultData)
{
	DL_GR_O_ContestApply *pOContestApply = (DL_GR_O_ContestApply*)pResultData;
	if (NULL == pOContestApply)
		return false;
	CGameUserInfo* pUserInfo = m_UserManage.FindOnLineUser(pOContestApply->iUserID);
	if (NULL == pUserInfo)
		return true;
	MSG_GR_O_ContestApply msgContestApply;
	msgContestApply.iApplyResult = pOContestApply->iApplyResult;
	msgContestApply.iContestBegin = pOContestApply->iContestBegin;
	m_TCPSocket.SendData(pUserInfo->m_uSocketIndex,&msgContestApply, sizeof(msgContestApply), MDM_GR_USER_ACTION, ASS_GR_CONTEST_APPLY, 0, 0);

	//��ʱ��Ҫ������Ϣ
	if(m_InitData.dwRoomRule & GRR_TIMINGCONTEST)
	{
		MSG_GR_MatchSignInfo matchsignInfo;
		matchsignInfo.iGameID = m_InitData.iGameID;
		matchsignInfo.iContestID = m_InitData.iContestID;
		matchsignInfo.iRoomID = m_InitData.uRoomID;
		matchsignInfo.iApplyResutl = pOContestApply->iApplyResult;
		matchsignInfo.matchBeginTime = m_MatchbeginTime;

		COleDateTime nowTime = COleDateTime::GetCurrentTime();
		COleDateTimeSpan tmDiff = (m_MatchbeginTime - nowTime);
		matchsignInfo.lsec = (long)tmDiff.GetTotalSeconds();

		m_TCPSocket.SendData(pUserInfo->m_uSocketIndex,&matchsignInfo, sizeof(MSG_GR_MatchSignInfo), MDM_GR_ROOM, ASS_GR_CONTEST_SIGNRECORD, 0, 0);
	}

	if(1 == pOContestApply->iContestBegin)
	{
		if ((m_InitData.dwRoomRule & GRR_CONTEST) && 1 != m_InitData.iRoomState)
		{
			//���ñ�����ʼ��־
			m_InitData.iRoomState = 1;
			//�����ݿ��ȡ����ID����֪ͨ������ʼ
			DL_GR_I_ContestBegin DL_ContestBegin;
			DL_ContestBegin.uNameID = m_InitData.iGameID;
			DL_ContestBegin.uRoomID = m_InitData.uRoomID;
			DL_ContestBegin.iContestID = m_InitData.iContestID;
			m_SQLDataManage.PushLine(&DL_ContestBegin.DataBaseHead, sizeof(DL_ContestBegin), DTK_GR_CONTEST_BEGIN, pResultData->uIndex, pResultData->dwHandleID);					
		}
	}

	return true;
}

bool CGameMainManage::OnBroadCastConstestInfo(DataBaseResultLine * pResultData)
{
	DL_GR_O_ContestInfo *pOContestInfo = (DL_GR_O_ContestInfo*)pResultData;
	if (NULL == pOContestInfo)
		return false;
	MSG_GR_I_ContestInfo msgContestInfo;
	msgContestInfo.iContestNum = pOContestInfo->_data.iContestNum;
	msgContestInfo.iContestBegin = pOContestInfo->_data.iContestBegin;
	m_TCPSocket.SendDataBatch(&msgContestInfo,sizeof(msgContestInfo),MDM_GR_ROOM,ASS_GR_CONTEST_APPLYINFO,0);

	return true;
}

//�����ʼ������
bool CGameMainManage::RandRank(int *pData, int iLen)
{
	if (!pData || 0 >= iLen)
		return false;
	int index;
	srand(time(NULL));
	for (int i = 0; i <iLen; i++)
	{
		index = rand() % (iLen - i) + i;//��ȡ������� 
		if (index != i)
		{//��������ֵ����
			pData[i] ^= pData[index];
			pData[index] ^= pData[i];
			pData[i] ^= pData[index];
		}
	}
	return true;
}

//������ʼǰ�������ݿ��ȡ����ID
bool CGameMainManage::OnGetContestBeginResult(DataBaseResultLine *pResultData)
{
	DL_GR_O_ContestBegin *p = (DL_GR_O_ContestBegin*)pResultData;

	if (!p || 0 >= p->iUserNum || p->iUserNum >= 255)
	{
		return true;
	}

	m_InitData.iMatchID = p->uMatchID;

	m_iResetTime = 0;
	CGameUserInfo * pUserInfo = NULL;
	//��������ʼ����
	int pRankNum[255];
	for (int i=0; i<p->iUserNum; ++i)
	{
		pRankNum[i] = i+1;
	}
	RandRank(pRankNum, p->iUserNum);
	int* pTemp = pRankNum;
	for (int i=0; i<p->iUserNum; ++i)
	{
		pUserInfo = m_UserManage.FindOnLineUser(*(p->pUserIDs+i));
		if (pUserInfo==NULL)
		{
			continue;
		}
		//���ó�ʼ������ʣ������
		pUserInfo->m_UserData.iRankNum = *(pTemp++);
		pUserInfo->m_UserData.iRemainPeople = p->iUserNum;
		AutoAllotDeskAddUser(pUserInfo);
		MSG_GR_ContestChange oContest;
		oContest.dwUserID = pUserInfo->m_UserData.dwUserID;
		oContest.iRankNum = pUserInfo->m_UserData.iRankNum;
		oContest.iRemainPeople = pUserInfo->m_UserData.iRemainPeople;
		m_TCPSocket.SendData(pUserInfo->m_uSocketIndex, &oContest, sizeof(MSG_GR_ContestChange), MDM_GR_ROOM, ASS_GR_INIT_CONTEST, 0, 0);
	}
	delete []p->pUserIDs;
	p->pUserIDs = NULL;

	//������ʼ��֪ͨ�÷���δ�����û��˳�
	m_TCPSocket.SendDataBatch(NULL,0,MDM_GR_ROOM,ASS_GR_CAHNGE_ROOM,0);
	KillTimer(IDT_QUEUE_GAME);
	SetTimer(IDT_QUEUE_GAME, m_iQueueTime*1000);
	return true;
}

bool CGameMainManage::OnGetContestGameOverResult(DataBaseResultLine *pResultData)
{
	DL_GR_O_ContestGameOver *p = (DL_GR_O_ContestGameOver*)pResultData;

	if (!p)
		return false;

	//�����û��Ľ�����Ϣ
	CGameUserInfo* pUser = m_UserManage.FindOnLineUser(p->oAward.dwUserID);
	if (!pUser)
		return false;
	if (m_InitData.pAwards && pUser->m_UserData.iRankNum<=m_InitData.iRankNum && 0 < pUser->m_UserData.iRankNum&&p->oAward.iAward==0)
	{
		pUser->m_UserData.iAward = m_InitData.pAwards[pUser->m_UserData.iRankNum-1];
		p->oAward.iAward = pUser->m_UserData.iAward;

		pUser->m_UserData.iAwardType = m_InitData.pAwardTypes[pUser->m_UserData.iRankNum-1];
		p->oAward.iAwardType = pUser->m_UserData.iAwardType;
	}
	else if(p->oAward.iAward==1)
	{
		p->oAward.iAward = -1;
	}
	//�������û����ͽ�����Ϣ
	m_TCPSocket.SendData(pUser->m_uSocketIndex,&p->oAward,sizeof(MSG_GR_ContestAward),MDM_GR_ROOM,ASS_GR_CONTEST_GAMEOVER,0,0);
	return true;
}

//��ȡ������ǰ�������ɼ���
bool CGameMainManage::OnGetContestRankResult(DataBaseResultLine* pResultData)
{
	DL_GR_O_UserContestRank* pRank = (DL_GR_O_UserContestRank*)pResultData;

	CGameUserInfo* pUser = m_UserManage.FindOnLineUser(pRank->_data.dwUserID);
	if (!pUser)
	{
		CString str;
		str.Format("cq::�û�%dΪ�գ���������������������", pRank->_data.dwUserID);
		OutputDebugString(str);
		return true;
	}
	//���������û��ı�����Ϣ
	pUser->m_UserData.iRankNum = pRank->_data.iRankNum;
	pUser->m_UserData.iRemainPeople = m_pIAutoAllotDesk->GetQueueUserCount();
	pUser->m_UserData.i64ContestScore = pRank->_data.i64ContestScore;
	pUser->m_UserData.iContestCount = pRank->_data.iContestCount;
	//���û��ı�����Ϣ���͵��ͻ���
	CString str;
	str.Format("cq::���ͱ�����Ϣ���ͻ���---�û�%d�÷�=%I64d������=%d,��������=%d", 
		pRank->_data.dwUserID,
		pRank->_data.i64ContestScore,
		pRank->_data.iRankNum,
		pRank->_data.iRemainPeople);
	OutputDebugString(str);	
	//m_TCPSocket.SendData(pUser->m_uSocketIndex,&pRank->_data,sizeof(MSG_GR_ContestChange),MDM_GR_ROOM,ASS_GR_USER_CONTEST,0,0);
	m_TCPSocket.SendDataBatch(&pRank->_data,sizeof(MSG_GR_ContestChange),MDM_GR_ROOM,ASS_GR_USER_CONTEST,0);

	return true;
}

bool CGameMainManage::OnPropChangeResult(DataBaseResultLine *  pResultData)
{
	if (!(m_InitData.dwRoomRule & GRR_GAME_U3D))
	{
		return true;
	}
	TpropChange_O* _p = (TpropChange_O*)pResultData;

	if (_p != NULL)
	{
		CGameUserInfo * pUserInfo = m_UserManage.FindOnLineUser(_p->info.iUserId);//m_UserManage.FillOnLineUserInfo(_p->info.iUserId);
		if (pUserInfo != NULL)
		{
			TPropChange _q;
			_q = _p->info;

			if (pUserInfo->m_UserData.bDeskNO != 255)
			{
				
				//IU3DDesk * pDesk = dynamic_cast<IU3DDesk*>(m_pDeskInfo[pUserInfo->m_UserData.bDeskNO]._pIDesk);
				CGameDesk *pDesk = *(m_pDesk+pUserInfo->m_UserData.bDeskNO);
				if (pDesk != NULL)
				{
					pDesk->PropInfo(_q);
				}
			}
		}
	}

	return true;
}
//������ϷȨ�޽������
bool CGameMainManage::OnGamePowerSetResult(DataBaseResultLine * pResultData)
{
	BYTE bHandleCode=ERR_GR_ERROR_UNKNOW;
	switch(pResultData->uHandleRusult)
	{
	case DTK_GR_GAME_POWER_SUCCESS:		//���гɹ�
		{
			bHandleCode=RES_GR_GAME_POWER_SET_SUCCESS;
			break;
		}
	case DTK_GR_GAME_POWER_RELEASE:   //������Ƴɹ�
		{
			bHandleCode=RES_GR_GAME_POWER_SET_RELEASE;
			break;
		}
	case DTR_GR_ERROR_UNKNOW:
	case DTK_GR_GAME_POWER_FAIL:
		{
			bHandleCode=RES_GR_GAME_POWER_SET_FAIL;
			break;
		}
	}
	m_TCPSocket.SendData(pResultData->uIndex,MDM_GR_MANAGE,ASS_GR_POWER_SET,bHandleCode,pResultData->dwHandleID);
	return true;
}

//���ѹ���
bool CGameMainManage::OnFriendManageDBOperateResult(DataBaseResultLine *pResultData)
{
	return true;
}
//��������
bool CGameMainManage::OnBufferIMMessageDBOperateResult(DataBaseResultLine *pResultData)
{
	return true;
}
//���й���Ա�������
bool CGameMainManage::OnCallGMResult(DataBaseResultLine * pResultData)
{

	switch(pResultData->uHandleRusult)
	{
	case DTK_GR_CALL_GM_SUCCESS:		//���гɹ�
		{
			m_TCPSocket.SendData(pResultData->uIndex,MDM_GR_MANAGE,ASS_GR_CALL_GM_SUCCESS,0,pResultData->dwHandleID);
			break;
		}
	case DTK_GR_CALL_GM_IN_ONE_MI:		//�����ڣ������ڳ�������
		{
			m_TCPSocket.SendData(pResultData->uIndex,MDM_GR_MANAGE,ASS_GR_CALL_GM_FAIL,1,pResultData->dwHandleID);
			break;
		}
	case DTR_GR_ERROR_UNKNOW:
	case DTK_GR_CALL_GM_FAIL:
		{

			m_TCPSocket.SendData(pResultData->uIndex,MDM_GR_MANAGE,ASS_GR_CALL_GM_FAIL,0,pResultData->dwHandleID);
			break;
		}
	}
	return true;
}
//��ʱ����Ϣ
bool CGameMainManage::OnTimerMessage(UINT uTimerID)
{
	//��Ϸ��ʱ��
	if (uTimerID>=TIME_START_ID)
	{
		BYTE bDeskIndex=(BYTE)((uTimerID-TIME_START_ID)/TIME_SPACE);
		if (bDeskIndex<m_InitData.uDeskCount) 
		{
			return (*(m_pDesk+bDeskIndex))->OnTimer((uTimerID-TIME_START_ID)%TIME_SPACE);
		}
	}

	//��ʱ����ʱ��
	if(uTimerID >= IDT_TIMING_CONTEST_BEGIN && uTimerID <= IDT_TIMING_CONTEST_END)
	{
		KillTimer(uTimerID);
		//1.�����Ŷ��û�	;2.���ͱ�����ʼ��Ϣ
		DL_GR_I_TimingMatchUsers TimingMatchInfo;
		TimingMatchInfo.iContestID = m_InitData.iContestID;
		TimingMatchInfo.iGameID = m_InitData.iGameID;
		TimingMatchInfo.iRoomID = m_InitData.uRoomID;
		m_SQLDataManage.PushLine(&TimingMatchInfo.DataBaseHead,sizeof(DL_GR_I_TimingMatchUsers),DTK_GR_TIMINGMATCH_GETQUEQUEUSERS,0,0);
	}

	//�ڲ���ʱ��
	switch (uTimerID)
	{
	case IDT_WRITE_SERVER_INFO:		//���·�������Ϣ
		{
			DebugPrintf1(m_InitData.uRoomID, "OnTimerMessage��IDT_WRITE_SERVER_INFO uNameID =%d uRoomID = %d uOnLineUserCount = %d SQLQueueCount = %d", m_KernelData.uNameID, m_InitData.uRoomID, m_UserManage.GetGameRoomCount(), m_SQLDataManage.m_DataLine.GetDataCount());
			//��������
			DL_GR_I_UpdateServerInfo UpdateInfo;
			UpdateInfo.uRoomID=m_InitData.uRoomID;
			UpdateInfo.uNameID=m_KernelData.uNameID;
			UpdateInfo.uOnLineUserCount=m_UserManage.GetGameRoomCount();
			m_SQLDataManage.PushLine(&UpdateInfo.DataBaseHead,sizeof(UpdateInfo),DTK_GR_UPDATE_INFO,0,0);

			return true;
		}
	case IDT_CHECK_DATA_CONNECT:	//������ݿ�����
		{
			//KillTimer(IDT_CHECK_DATA_CONNECT);
			DataBaseLineHead DataBaseHead;
			m_SQLDataManage.PushLine(&DataBaseHead,sizeof(DataBaseHead),DTK_GR_CHECK_CONNECT,0,0);
			return true;
		}
	case IDT_UPDATE_ROOM_PEOPLE:		//���·�������Ϣ
		{
			//��������
			KillTimer(IDT_UPDATE_ROOM_PEOPLE);
			DL_GR_I_UpdateServerInfo UpdateInfo;
			UpdateInfo.uRoomID=m_InitData.uRoomID;
			UpdateInfo.uNameID=m_KernelData.uNameID;
			UpdateInfo.uOnLineUserCount=m_UserManage.GetGameRoomCount();
			m_SQLDataManage.PushLine(&UpdateInfo.DataBaseHead,sizeof(UpdateInfo),DTK_GR_UPDATE_INFO,0,0);
			return true;
		}
	case IDT_QUEUE_GAME: /// �Ŷӻ���ʱ����������Ҳ�������
		{
			KillTimer(IDT_QUEUE_GAME);
			NewQueueGame();
			m_iResetTime = 0;

			if (IsQueueGameRoom() && !(m_InitData.dwRoomRule & GRR_CONTEST) && !(m_InitData.dwRoomRule & GRR_TIMINGCONTEST))
			{
				SetTimer(IDT_QUEUE_GAME, m_iQueueTime * 1000);
			}
			return true;
		}
	case IDT_LEASE_TIMEOVER:
		{
			KillTimer(IDT_LEASE_TIMEOVER);
			if (IsLeaseTimeOver())
			{
				for (int i = 0; i < m_UserManage.m_OnLineUserInfo.GetPermitCount(); ++i)
				{
					CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(i);
					if (pUserInfo!=NULL && !IsUserPlayGameByStation(pUserInfo)) 
					{
						AutoAllotDeskDeleteUser(pUserInfo);
						m_pGameUserInfoList.remove(pUserInfo);
						m_TCPSocket.SendData(pUserInfo->m_uSocketIndex, MDM_GR_USER_ACTION, ASS_GR_LEASE_TIMEOVER, 0, 0);

						//m_TCPSocket.CloseSocket(pUserInfo->m_uSocketIndex, 0);
						CleanUserInfo(pUserInfo);
						m_UserManage.FreeUser(pUserInfo, true);
					}
				}
			}
			SetTimer(IDT_LEASE_TIMEOVER, 10000);
			return true;
		}
	case IDT_TIMING_CONTEST_INFO:
		{
			
		}break;
	case IDT_CONNECT_OTHERSERVER_SOCKET:
		{
			return OnTimerMessageForUpdateToOtherServer(uTimerID);
		}break;
	}
	return false;
}

// ������������������Ϣ
bool CGameMainManage::OnTimerMessageForUpdateToOtherServer(UINT uTimerID)
{
	if (uTimerID != IDT_CONNECT_OTHERSERVER_SOCKET)
		return false;

	//if (nullptr != m_pMainServerSocket)
	//{
	//	m_pMainServerSocket->CheckReConnect();
	//	m_pMainServerSocket->CheckKeepLive();

	//}
}


///�ж��Ƿ����Ŷӻ�����
///@return true:���Ŷӻ����䣻false�������Ŷӻ�����
bool CGameMainManage::IsQueueGameRoom()
{
	return m_InitData.dwRoomRule & GRR_QUEUE_GAME || m_InitData.dwRoomRule & GRR_CONTEST || m_InitData.dwRoomRule & GRR_TIMINGCONTEST;
}

//��ʼ����Ϸ��
bool CGameMainManage::InitGameDesk(UINT uDeskCount, UINT uDeskType)
{
	//������Ϸ����
	UINT uDeskClassSize=0;
	m_pDeskArray=CreateDeskObject(uDeskCount,uDeskClassSize);
	if ((m_pDeskArray==NULL)||(uDeskClassSize==0))
		throw new CAFCException(TEXT("CGameMainManage::InitGameDesk �ڴ�����ʧ��"),0x418);

	//�����ڴ�
	m_uDeskCount=uDeskCount;
	m_pDesk=new CGameDesk * [m_uDeskCount];
	if (m_pDesk==NULL)
	{
		throw new CAFCException(TEXT("CGameMainManage::InitGameDesk �ڴ�����ʧ��"),0x419);
	}

    // PengJiLin, 2010-5-20, �Ŷӻ��������ó������ﵽʱ�ſ�ʼ��������
    // С�����ӵ�������ʹ�����ӵ�����������ʹ�����õ�����
    CBcfFile fConf(CBcfFile::GetAppPath()+"Function.bcf");
    m_uQueuerMaxPeople = fConf.GetKeyVal("OnlineCoin","QueuerMaxPeople",0);

	//{add rongqiufen 2010.06.29
	///���ŶӶ���������>=m_uQueuerPeople + ÿ����Ϸ��ʱ��ʼ�Ŷ�
	m_uQueuerPeople = m_uQueuerMaxPeople;	

    if(m_uQueuerMaxPeople < m_KernelData.uDeskPeople) m_uQueuerMaxPeople = m_KernelData.uDeskPeople;
    srand((unsigned)time(NULL));

	//����ָ��
	for (UINT i=0;i<m_uDeskCount;i++)
	{
		*(m_pDesk+i)=(CGameDesk *)((char *)m_pDeskArray+i*uDeskClassSize);
		(*(m_pDesk+i))->GetGRM_SET_KEY(GRM_SET_KEY);
		(*(m_pDesk+i))->GetGRM_SET_KEY_Win(GRM_SET_KEY_WIN);
		(*(m_pDesk+i))->GetGRM_SET_KEY_Los(GRM_SET_KEY_LOS);
		(*(m_pDesk+i))->Init(i,m_KernelData.uDeskPeople,this,uDeskType);//�ټ���
	}

	return true;
}


/// �����Զ���������
IAutoAllotDesk *CGameMainManage::CreateAutoAllotDesk(int iDeskPeopleCount, int iDeskCount)
{
	return new CAutoAllotDesk(iDeskPeopleCount, iDeskCount, m_KernelData.uMinDeskPeople);
}

///�Ŷӻ�����û�
int CGameMainManage::AutoAllotDeskAddUser(CGameUserInfo *pInfo)
{
	if (m_pIAutoAllotDesk)
	{
		m_pIAutoAllotDesk->Add(pInfo);	///< �����Ŷӵ����
	}
	return 0;
}

///�Ŷӻ�ɾ���û�
int CGameMainManage::AutoAllotDeskDeleteUser(CGameUserInfo *pInfo)
{
	if (m_pIAutoAllotDesk)
	{
		m_pIAutoAllotDesk->Delete(pInfo);
	}
	return 0;
}

int CGameMainManage::AutoAllotDeskDeleteAll()
{
	if (m_pIAutoAllotDesk)
	{
		m_pIAutoAllotDesk->DeleteAll();
	}
	return 0;
}

void CGameMainManage::NewQueueGame()
{
	if (NULL == m_pIAutoAllotDesk || 1 != m_InitData.iRoomState)
	{
		return;
	}
	int nCount = 0;
	int *pArrDesk = NULL;
	m_pIAutoAllotDesk->AllotDesk(nCount, pArrDesk, (m_InitData.dwRoomRule&GRR_CONTEST || m_InitData.dwRoomRule&GRR_TIMINGCONTEST));
	if (nCount <= 0 || NULL == pArrDesk)
	{
		IsContestGameOver();
		return;
	}
	/// Ŀ������
	int nDeskNo=0;
	int *pQueueUserSit = (int*)m_pQueueUserSitBuffer;
	CGameUserInfo *pUserInfo = NULL;
	int nMaxQueue = nCount*m_KernelData.uDeskPeople;
	CGameDesk* pGameDesk = NULL;
	for (int i=0; i<nCount; ++i)
	{
		/// �ҿ���
		while(nDeskNo < m_InitData.uDeskCount)
		{
			pGameDesk=*(m_pDesk+nDeskNo);
			if (pGameDesk != NULL && pGameDesk->GetDeskPlayerNum() ==0) break;
			nDeskNo++;
		}
			/// û�ҵ����˳�ѭ��
		if (((UINT)nDeskNo>=m_InitData.uDeskCount)||(pGameDesk->GetDeskPlayerNum() != 0))
		{
			CString str;
			str.Format("cq::����ʱ������=%d,��������=%d��������������=%d", nDeskNo, m_InitData.uDeskCount, pGameDesk->GetDeskPlayerNum());
			OutputDebugString(str);
			int nPos = i*m_KernelData.uDeskPeople;
			while (nPos<nMaxQueue)
			{
				pUserInfo = m_UserManage.FindOnLineUser(pArrDesk[nPos++]);
				m_pIAutoAllotDesk->Add(pUserInfo);
			}
			break;
		}
		int bDeskStation=0;
		int iusercount = 0;
		pQueueUserSit[0] = nDeskNo;
		vector<CGameUserInfo*> pDeskUserArr;
		pDeskUserArr.clear();
		/// ÿ���������
		for (bDeskStation=0; bDeskStation<m_KernelData.uDeskPeople; ++bDeskStation)
		{
			pQueueUserSit[1+bDeskStation*3] = pArrDesk[i*m_KernelData.uDeskPeople + bDeskStation];
			
			pUserInfo = m_UserManage.FindOnLineUser(pQueueUserSit[1+bDeskStation*3]);
			if (NULL == pUserInfo)
			{				
				continue;
			}
			if ((pUserInfo->m_UserData.bDeskNO < m_InitData.uDeskCount) || (pUserInfo->m_UserData.bDeskStation < m_KernelData.uDeskPeople))
			{
				// ����Ѿ������ˣ��������ڶ���
				break;
			}
			else
			{
				pDeskUserArr.push_back(pUserInfo);
			}
			iusercount++;
		}
		/// �ж����������Ƿ�ʧ��
		if (pDeskUserArr.size() <= m_KernelData.uDeskPeople && pDeskUserArr.size() >= m_KernelData.uMinDeskPeople)
		{
			for (bDeskStation=0; bDeskStation<pDeskUserArr.size(); ++bDeskStation)
			{
				pUserInfo = pDeskUserArr[bDeskStation];
				if (NULL != pUserInfo)
				{
					MSG_GR_S_UserSit  UserSitInfo;
					UserSitInfo.bDeskIndex = nDeskNo;
					UserSitInfo.bDeskStation = bDeskStation;
					pGameDesk->UserSitDesk(&UserSitInfo, pUserInfo);

					pUserInfo->m_UserData.bDeskNO		= nDeskNo;
					pUserInfo->m_UserData.bDeskStation	= bDeskStation;
					pUserInfo->m_UserData.bUserState = USER_LOOK_STATE;
					pUserInfo->m_UserData.iMatchID = m_InitData.iMatchID;
					//��������
					pQueueUserSit[1+bDeskStation*3+1] = pUserInfo->m_UserData.iRankNum;
					//���ñ���ʣ������
					pQueueUserSit[1+bDeskStation*3+2] = pUserInfo->m_UserData.iRemainPeople;					
					pGameDesk->SetDeskUserInfo(pUserInfo, bDeskStation);
					
					if (!(m_InitData.dwRoomRule & GRR_CONTEST) && !(m_InitData.dwRoomRule & GRR_TIMINGCONTEST))
					{
						m_pIAutoAllotDesk->Delete(pUserInfo);
					}
				}
			}
			if (1 != m_InitData.iRoomState)
				return;
			CString str;
			str.Format("cq::���ڵ�%d���������=%d��Sit0=%d, Sit1=%d, Sit2=%d", nDeskNo, iusercount, 
				pDeskUserArr[0]->m_UserData.dwUserID,
				pDeskUserArr[1]->m_UserData.dwUserID,
				pDeskUserArr[2]->m_UserData.dwUserID);
			OutputDebugString(str);
			//�㲥�����λ����Ϣ
			m_TCPSocket.SendDataBatch(m_pQueueUserSitBuffer, (m_KernelData.uDeskPeople*3+1)*sizeof(int),MDM_GR_USER_ACTION,ASS_GR_QUEUE_USER_SIT,ERR_GR_SIT_SUCCESS);

			for (bDeskStation=0; bDeskStation<pDeskUserArr.size(); ++bDeskStation)
			{
				pGameDesk->UserAgreeGame(bDeskStation);
			}
		}
		else
		{
			if (pDeskUserArr.size() == 0)
				return;
			/// ���ǿ���ҷŻش���ģ��
			for (bDeskStation=0; bDeskStation<pDeskUserArr.size()/*m_KernelData.uDeskPeople*/; ++bDeskStation)
			{
				pUserInfo = pDeskUserArr[bDeskStation];
				if (NULL != pUserInfo)
				{
					pGameDesk->UserLeftDesk(bDeskStation, pUserInfo);
					OutputDebugString("cq::����ʧ��");
					pUserInfo->m_UserData.bDeskNO = 255;
					pUserInfo->m_UserData.bDeskStation = 255;
					m_pIAutoAllotDesk->Add(pUserInfo);
				}
			}
		}
	}
	return;
}

//������ʱ����ʱ��
void CGameMainManage::OnStartTimingMatchTimer(COleDateTime MatchStartTime)
{
	

	int icounter = 0;
	
	MatchStartTime;

	m_MatchbeginTime = MatchStartTime;

	COleDateTime nowTime = COleDateTime::GetCurrentTime();
	CString cs;
	if(MatchStartTime > nowTime)
	{
		COleDateTimeSpan tmDiff = (MatchStartTime - nowTime);
		long lsec = (long)tmDiff.GetTotalSeconds();

		if(lsec <=100)
		{
			AfxMessageBox(TEXT("��ʱ��������ʱ��൱ǰʱ�� ��������� 100�룬�����ʱ�䣬�Ӵ����󣬲�������Ϸ������"));
		}
			
		//��ʱ��������ʱ��
		SetTimer(IDT_TIMING_CONTEST_BEGIN+icounter,lsec*1000);
	}
	
}

//��ʱ��������ʼǰ1���ӣ�֪ͨ��Ϣ
void CGameMainManage::OnBeforeMatchBeginInfo()
{

}

bool CGameMainManage::OnTimingMatchBeginFillQueue(DataBaseResultLine * pResultData)
{
	DL_GR_O_TimingMatchUsers *pUserList = (DL_GR_O_TimingMatchUsers*)pResultData;
	if(!pUserList)
	{
		return false;
	}
	int iPlayerCount = pUserList->iUserCount;

	for (int i = 0; i < iPlayerCount; i++)
	{
		CGameUserInfo *puser = m_UserManage.FindOnLineUser(pUserList->iArrayUserid[i]);
		if(puser && m_pIAutoAllotDesk)
		{
			m_pIAutoAllotDesk->Add(puser);
		}
		else if (puser == nullptr) //����δ������Ϸ��ұ�����Ϣ
		{
			DL_GR_I_ContestApply DL_ContestApply;

			DL_ContestApply.iUserID = pUserList->iArrayUserid[i];
			DL_ContestApply.iTypeID = 1;

			m_SQLDataManage.PushLine(&DL_ContestApply.DataBaseHead, sizeof(DL_ContestApply), DTK_GR_CONTEST_APPLY, pResultData->uIndex, 0);
		}
	}

	//�����ݿ��ȡ������ţ���֪ͨ������ʼ
	//���ñ�����ʼ��־
	m_InitData.iRoomState = 1;
	DL_GR_I_ContestBegin DL_ContestBegin;
	DL_ContestBegin.uNameID = m_InitData.iGameID;
	DL_ContestBegin.uRoomID = m_InitData.uRoomID;
	DL_ContestBegin.iContestID = m_InitData.iContestID;
	m_SQLDataManage.PushLine(&DL_ContestBegin.DataBaseHead, sizeof(DL_ContestBegin), DTK_GR_CONTEST_BEGIN, pResultData->uIndex, 0);

	CString cs;
	cs.Format("chs [Server]��ʱ�� -----��ǰ���������������%d��  �������Կ�ʼ��������Ϣ���ͻ���.-----",m_pIAutoAllotDesk->GetQueueUserCount());
	OutputDebugString(cs);

	return true;
}
bool CGameMainManage::OnFindBuyDeskStationResult(DataBaseResultLine * pResultData)
{
	DL_GR_O_FindDeskBuyStationResult *pReceiveData= (DL_GR_O_FindDeskBuyStationResult*)pResultData;
	if(!pReceiveData)
	{
		return false;
	}
	CGameDesk *pGameDesk=NULL;
	for (UINT i=0;i<m_uDeskCount;i++)
	{
		pGameDesk=(*(m_pDesk+i));
		if(!pGameDesk)
		{
			continue;
		}
		pGameDesk->m_bIsBuy=pReceiveData->bIsBuy[i];
		pGameDesk->m_iVipGameCount=pReceiveData->iVipCount[i];
		pGameDesk->m_iDeskMaster=pReceiveData->iUserID[i];
		memcpy(pGameDesk->m_szDeskPassWord,pReceiveData->szDeskPassWord[i],sizeof(pGameDesk->m_szDeskPassWord));
		
	}
}
bool CGameMainManage::OnUserAction_FastSit(NetMessageHead * pNetHead, void * pData, UINT uSize, ULONG uAccessIP, UINT uIndex, DWORD dwHandleID)
{
	if (IsQueueGameRoom())
	{//�Ŷӻ��������տ���������Ϣ
		return true;
	}
	CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
	if (pUserInfo==NULL)
	{
		return false;
	}
	MSG_GR_S_UserSit *pSitData = (MSG_GR_S_UserSit *)pData;

	BYTE bErrorCode=ERR_GR_ERROR_UNKNOW;
	if (255 != pSitData->bDeskIndex)
	{
		CGameDesk* pGameDesk = *(m_pDesk + pSitData->bDeskIndex);
		if (pGameDesk == nullptr)
		{
			return false;
		}
		if (pGameDesk->GetDeskPlayerNum() >= pGameDesk->m_bMaxPeople)
		{
			SendErrorUserSit(uIndex, ERR_GR_DESK_FULL,dwHandleID);
		}
		else
		{
			for (int j=0; j!=m_KernelData.uDeskPeople; ++j)
			{
				pSitData->bDeskStation = j;
				int iRes=pGameDesk->CanSitDesk(pSitData, pUserInfo);
			
				if (ERR_GR_ALREAD_USER != iRes)
				{
					if (ERR_GR_SIT_SUCCESS == iRes)
					{
						bErrorCode=pGameDesk->UserSitDesk(pSitData,pUserInfo);
						if (ERR_GR_SIT_SUCCESS != bErrorCode)
						{
							SendErrorUserSit(uIndex, bErrorCode,dwHandleID);
							return true;
						}
						else
						{
							return true;
						}
					}
					else
					{
						SendErrorUserSit(uIndex, iRes,dwHandleID);
						return true;
					}
				}

			}
		}
	}
	else
	{
		//�����û��뿪ԭλ��
		if (pUserInfo->m_UserData.bDeskNO!=255)
		{
			if (IsUserPlayGame(pUserInfo)==true)
			{
				if(m_InitData.uComType==TY_MATCH_GAME) return true;
				m_TCPSocket.SendData(uIndex,MDM_GR_USER_ACTION,ASS_GR_SIT_ERROR,ERR_GR_CAN_NOT_LEFT,dwHandleID);
				return true;
			}
			UserLeftDesk(pUserInfo);
		}

		//�����û�����λ��
		BYTE bErrorCode=ERR_GR_ERROR_UNKNOW;
		CGameDesk* pGameDesk = NULL;
		MSG_GR_S_UserSit UserSit,UserFinalSit;
		ZeroMemory(&UserFinalSit,sizeof(UserFinalSit));
		UserFinalSit.bDeskIndex = 255;
		bool bDeskFlag=false;
		//������
		for (int i=0; i!=m_InitData.uDeskCount; ++i)
		{	
			pGameDesk = *(m_pDesk + i);
			if (pGameDesk == NULL)
			{
				continue;
			}

			if (pGameDesk->IsLock() || pGameDesk->IsVirtualLock())
			{
				continue;
			}

			//����λ
			UserSit.bDeskIndex = i;
			for (int j=0; j!=m_KernelData.uDeskPeople; ++j)
			{
				UserSit.bDeskStation = j;
				if (ERR_GR_SIT_SUCCESS == pGameDesk->CanSitDesk(&UserSit, pUserInfo))
				{
					if (UserFinalSit.bDeskIndex == 255)
					{
						UserFinalSit.bDeskIndex = i;
						UserFinalSit.bDeskStation = j;
						bDeskFlag=true;
						break;
					}
					else
					{
						CGameDesk* pGameDeskOld = *(m_pDesk + UserFinalSit.bDeskIndex);
						if (pGameDesk->GetDeskPlayerNum() > pGameDeskOld->GetDeskPlayerNum())
						{
							UserFinalSit.bDeskIndex = i;
							UserFinalSit.bDeskStation = j;
							bDeskFlag=true;
							break;
						}
					}
				}
			}
			if(bDeskFlag)
			{
				break;
			}
		}

		if (UserFinalSit.bDeskIndex == 255)
		{
			//û���ҵ�
			SendErrorUserSit(uIndex, ERR_GR_FAST_SIT,dwHandleID);
			return true;
		}

		pGameDesk = *(m_pDesk+UserFinalSit.bDeskIndex);

		if (nullptr == pGameDesk)
		{
			//û���ҵ�
			SendErrorUserSit(uIndex, ERR_GR_FAST_SIT,dwHandleID);
		}
		else
		{
			bErrorCode=pGameDesk->UserSitDesk(pSitData,pUserInfo);
			if (ERR_GR_SIT_SUCCESS != bErrorCode)
			{
				//û���ҵ�
				SendErrorUserSit(uIndex, bErrorCode,dwHandleID);
			}
		}
	}

	return true;
}

///��ʾ�������´�����Ϣ
void CGameMainManage::SendErrorUserSit(UINT uIndex, UINT bHandleCode, DWORD dwHandleID)
{
	CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
	if (pUserInfo)
	{
		//�������´�����Ϣ
		MSG_GR_R_UserSit UserSit;
		//UserSit.bLock=0;
		UserSit.bDeskIndex=pUserInfo->m_UserData.bDeskNO;
		UserSit.bDeskStation=pUserInfo->m_UserData.bDeskStation;
		UserSit.bUserState=pUserInfo->m_UserData.bUserState;
		UserSit.dwUserID=pUserInfo->m_UserData.dwUserID;
		//UserSit.bIsDeskOwner=0;//��̨��
		m_TCPSocket.SendData(uIndex, &UserSit,sizeof(UserSit),MDM_GR_USER_ACTION,ASS_GR_SIT_ERROR,bHandleCode,dwHandleID);
	}
}
//���������ɹ��������
bool CGameMainManage::OnVoiceInfo(NetMessageHead *pNetHead, void* pData, UINT uSize, ULONG uAccessIP, UINT uIndex, DWORD dwHandleID)
{
	if(pNetHead->bMainID!=MDM_GM_GAME_NOTIFY || pNetHead->bAssistantID!=ASS_GR_VOIEC)
		return false;

	if(uSize!=sizeof(VoiceInfo)) return false;
	VoiceInfo* pCmd=(VoiceInfo*)pData;

	m_TCPSocket.SendDataBatch(pCmd,sizeof(VoiceInfo),MDM_GM_GAME_NOTIFY,ASS_GR_VOIEC,RES_GR_VOIEC_SUC);

	return true;
}
//�û����䴦��
bool CGameMainManage::OnDeskDissmiss(NetMessageHead * pNetHead, void * pData, UINT uSize, ULONG uAccessIP, UINT uIndex, DWORD dwHandleID)
{
	switch (pNetHead->bAssistantID)
	{
	case ASS_GR_DESKRUNOUT://�����ɢ����
		{
			//Ч���û�
			CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
			if(!pUserInfo)
			{
				return false;
			}
			CGameDesk * pGameDesk=GetDeskInfo(pUserInfo->m_UserData.bDeskNO);
			if(!pGameDesk)
			{
				return false;
			}

			if(pGameDesk->IsPlayGame(0))
			{
				AddDeskRunOutInfo(pGameDesk);

				m_iApplyDissVipDeskUser=pUserInfo->m_UserData.dwUserID;
				pGameDesk->m_iDissmissAgreePeople=0;
				pGameDesk->m_nDeskRunOutID = pUserInfo->m_UserData.dwUserID;
				for(int i=0;i<pGameDesk->m_bMaxPeople;i++)
				{
					if(!pGameDesk->m_pUserInfo[i])
					{
						continue;
					}
					VipDeskDismissNotify desk_notify;
					desk_notify.iUserID=pUserInfo->m_UserData.dwUserID;
					m_TCPSocket.SendData(pGameDesk->m_pUserInfo[i]->m_uSocketIndex,&desk_notify,sizeof(desk_notify),MDM_GR_DESKRUNOUT,ASS_GR_DISSMISS_AGREE,0,0);
				}
			}
			else
			{
				if(pGameDesk->m_iDeskMaster==pUserInfo->m_UserData.dwUserID)
				{
					ClearDeskRunOutInfo(pGameDesk);
					if(OnClearDesk(pGameDesk->m_bDeskIndex,m_InitData.uRoomID,pUserInfo->m_UserData.dwUserID))
					{
						DL_GR_I_BuyDeskOut input_cleardesk;
						input_cleardesk.byDeskIndex=pGameDesk->m_bDeskIndex;
						input_cleardesk.iRoomID=m_InitData.uRoomID;
						input_cleardesk.iUserID=pUserInfo->m_UserData.dwUserID;
						input_cleardesk.iVipGameCount=pGameDesk->m_iVipGameCount;						
						input_cleardesk.iDeskMaster=pGameDesk->m_iDeskMaster;							
						memcpy(input_cleardesk.szDeskPassWord,pGameDesk->m_szDeskPassWord,sizeof(input_cleardesk.szDeskPassWord));
						m_SQLDataManage.PushLine(&input_cleardesk.DataBaseHead, sizeof(input_cleardesk), DTK_GR_CLEARBUYDESK, 0, 0);
						if(pGameDesk->IsPlayGame(0))
						{
							pGameDesk->GameFinish(0,GFF_DISSMISS_FINISH);
						}
						else
						{
							for(int i=0;i<pGameDesk->m_bMaxPeople;i++)
							{
								if(!pGameDesk->m_pUserInfo[i])
								{
									continue;
								}
								pGameDesk->UserLeftDesk(pGameDesk->m_pUserInfo[i]->m_UserData.bDeskStation,pGameDesk->m_pUserInfo[i]);
							}

						}
					}
					
				}
				else//��ɢʧ��
				{
					VipDeskRunOut desk_runout;
					m_TCPSocket.SendData(pUserInfo->m_uSocketIndex,&desk_runout,sizeof(desk_runout),MDM_GR_DESKRUNOUT,ASS_GR_DESKRUNOUT,0,0);
				}
			}
			return true;
		}break;
	case ASS_GR_DISSMISS_AGREE:
		{
			VipDeskDismissAgree *pReceiveData=(VipDeskDismissAgree *)pData;
			if(!pReceiveData)
			{
				return false;	
			}
			//Ч���û�
			CGameUserInfo * pUserInfo=m_UserManage.GetOnLineUserInfo(uIndex);
			if(!pUserInfo)
			{
				return false;
			}
			CGameDesk * pGameDesk=GetDeskInfo(pUserInfo->m_UserData.bDeskNO);
			if(!pGameDesk)
			{
				return false;
			}
			AddDeskRunOutAgreeInfo(pGameDesk, pUserInfo, pReceiveData->bAgree);
			if(pReceiveData->bAgree)
			{
				pGameDesk->m_iDissmissAgreePeople++;
				VipDeskDismissAgreeRes tAgreeData;
				tAgreeData.bAgree=pReceiveData->bAgree;
				tAgreeData.iUserID=pUserInfo->m_UserData.dwUserID;
				for(int i=0;i<pGameDesk->m_bMaxPeople;i++)
				{
					if(!pGameDesk->m_pUserInfo[i])
					{
						continue;
					}
					m_TCPSocket.SendData(pGameDesk->m_pUserInfo[i]->m_uSocketIndex,&tAgreeData,sizeof(tAgreeData),MDM_GR_DESKRUNOUT,ASS_GR_DISSMISS_AGREE_RES,0,0);
				}
				if(pGameDesk->m_iDissmissAgreePeople>=(pGameDesk->GetDeskPlayerNum()-1))
				{
					if(pGameDesk->IsPlayGame(0))
					{
						pGameDesk->GameFinish(0,GFF_DISSMISS_FINISH);
					}
					else
					{
						for(int i=0;i<pGameDesk->m_bMaxPeople;i++)
						{
							if(!pGameDesk->m_pUserInfo[i])
							{
								continue;
							}
							pGameDesk->UserLeftDesk(pGameDesk->m_pUserInfo[i]->m_UserData.bDeskStation,pGameDesk->m_pUserInfo[i]);
						}

					}
					ClearDeskRunOutInfo(pGameDesk);
					if(OnClearDesk(pGameDesk->m_bDeskIndex,m_InitData.uRoomID,m_iApplyDissVipDeskUser))
					{
						DL_GR_I_BuyDeskOut input_cleardesk;
						input_cleardesk.byDeskIndex=pGameDesk->m_bDeskIndex;
						input_cleardesk.iRoomID=m_InitData.uRoomID;
						input_cleardesk.iUserID=m_iApplyDissVipDeskUser;
						input_cleardesk.iVipGameCount=pGameDesk->m_iVipGameCount;						
						input_cleardesk.iDeskMaster=pGameDesk->m_iDeskMaster;							
						memcpy(input_cleardesk.szDeskPassWord,pGameDesk->m_szDeskPassWord,sizeof(input_cleardesk.szDeskPassWord));
						m_SQLDataManage.PushLine(&input_cleardesk.DataBaseHead, sizeof(input_cleardesk), DTK_GR_CLEARBUYDESK, 0, 0);
						
					}
				}
			}
			else // �ܾ���ɢ ��ɢʧ��
			{
				ClearDeskRunOutInfo(pGameDesk);
				VipDeskRunOut desk_runout;
				for(int i=0;i<pGameDesk->m_bMaxPeople;i++)
				{
					if(!pGameDesk->m_pUserInfo[i])
					{
						continue;
					}
					m_TCPSocket.SendData(pGameDesk->m_pUserInfo[i]->m_uSocketIndex,&desk_runout,sizeof(desk_runout),MDM_GR_DESKRUNOUT,ASS_GR_DESKRUNOUT,0,0);
				}
			}
			return true;
		}break;
	case ASS_GR_GETDESKMASTER:
		{
			VipDeskInfo *pReceiveData=(VipDeskInfo *)pData;
			if(!pReceiveData)
			{
				return false;	
			}
			VipDeskInfoResult data;
			CGameDesk * pGameDesk=GetDeskInfo(pReceiveData->byDeskIndex);
			if(pGameDesk)
			{
				data.byDeskIndex=pReceiveData->byDeskIndex;
				data.iMasterID=pGameDesk->m_iDeskMaster;
				data.iPlayCount=pGameDesk->m_iVipGameCount;
				memcpy(data.szPassWord,pGameDesk->m_szDeskPassWord,sizeof(data.szPassWord));
			}
			m_TCPSocket.SendData(uIndex,&data,sizeof(data),MDM_GR_DESKRUNOUT,ASS_GR_GETDESKMASTER,0,0);

			CGameUserInfo* pNewUserInfo = m_UserManage.GetOnLineUserInfo(uIndex);
			if (pGameDesk->m_nDeskRunOutID > 0)
			{
				VipDeskDismissNotify desk_notify;
				desk_notify.iUserID=pGameDesk->m_nDeskRunOutID;
				m_TCPSocket.SendData(pNewUserInfo->m_uSocketIndex,&desk_notify,sizeof(desk_notify),MDM_GR_DESKRUNOUT,ASS_GR_DISSMISS_AGREE,0,0);
				// ����ͬ���ɢ����
				auto iter = find_if(m_vectDeskRunOutAgree.begin(), m_vectDeskRunOutAgree.end(), [=](struct DeskRunOutAgree obj){ return pGameDesk->m_bDeskIndex== obj.nDeskIndex;});
				if (iter != m_vectDeskRunOutAgree.end())
				{
					vector<long int>::iterator iterUser = iter->vectUserID.begin();
					if (iterUser != iter->vectUserID.end())
					{
						int i = 0;
						for (iterUser; iterUser != iter->vectUserID.end(); iterUser++)
						{
							VipDeskDismissAgreeRes tAgreeData;
							tAgreeData.bAgree=iter->vectAgree[i];
							tAgreeData.iUserID=*iterUser;
							m_TCPSocket.SendData(pNewUserInfo->m_uSocketIndex,&tAgreeData,sizeof(tAgreeData),MDM_GR_DESKRUNOUT,ASS_GR_DISSMISS_AGREE_RES,0,0);
							i++;
						}
					}
				}
			}

			return true;
		}break;
	}
	return false;	
}
//�û����߽�ɢ����
void CGameMainManage::OnUserNetCutDissmiss(CGameUserInfo * pUserInfo)
{
	//Ч���û�
	if(!pUserInfo)
	{
		return;
	}
	CGameDesk * pGameDesk=GetDeskInfo(pUserInfo->m_UserData.bDeskNO);
	if(!pGameDesk)
	{
		return;
	}
	m_iApplyDissVipDeskUser=pUserInfo->m_UserData.dwUserID;
	pGameDesk->m_iDissmissAgreePeople=0;
	for(int i=0;i<pGameDesk->m_bMaxPeople;i++)
	{
		if(!pGameDesk->m_pUserInfo[i])
		{
			continue;
		}
		VipDeskDismissNotify desk_notify;
		desk_notify.iUserID=pUserInfo->m_UserData.dwUserID;
		m_TCPSocket.SendData(pGameDesk->m_pUserInfo[i]->m_uSocketIndex,&desk_notify,sizeof(desk_notify),MDM_GR_DESKRUNOUT,ASS_GR_DISSMISS_AGREE,0,0);
	}
	pGameDesk->m_nDeskRunOutID = pUserInfo->m_UserData.dwUserID;
	AddDeskRunOutInfo(pGameDesk);

}
//�õ�����ָ��
CGameDesk *CGameMainManage::GetDeskInfo(BYTE byDeskNo)
{
	CGameDesk *pDesk=NULL;
	if(byDeskNo>=0 && byDeskNo<m_uDeskCount)
	{
		pDesk=*(m_pDesk+byDeskNo);
	}
	return pDesk;
}
bool CGameMainManage::OnClearDesk(BYTE byDeskIndex,int iRoomID,int iUserID)
{
	CGameDesk * pDesk=GetDeskInfo(byDeskIndex);
	if(pDesk)
	{
		pDesk->m_bIsBuy=false;
		pDesk->m_iVipGameCount=0;
		pDesk->m_iRunGameCount=0;
		pDesk->m_iDeskMaster=0;
		memset(pDesk->m_szDeskPassWord,0,sizeof(pDesk->m_szDeskPassWord));
		VipDeskRunOut desk_runout;
		desk_runout.byDeskIndex=byDeskIndex;
		desk_runout.bSuccess=true;
		desk_runout.iUserID=iUserID;
		for(int i=0;i<pDesk->m_bMaxPeople;i++)
		{
			if(!pDesk->m_pUserInfo[i])
			{
				continue;
			}
			m_TCPSocket.SendData(pDesk->m_pUserInfo[i]->m_uSocketIndex,&desk_runout,sizeof(desk_runout),MDM_GR_DESKRUNOUT,ASS_GR_DESKRUNOUT,0,0);
			pDesk->MakeUserOffLine(i);
		}

		pDesk->KillTimer(IDT_CHECK_DESK);

		return true;
	}
	return false;
}

void CGameMainManage::ClearDeskRunOutInfo(CGameDesk* pGameDesk)
{
	assert(pGameDesk != NULL);
	auto iter = find_if(m_vectDeskRunOutMsg.begin(), m_vectDeskRunOutMsg.end(), [=](struct DeskRunOutMsg obj){ return pGameDesk->m_bDeskIndex== obj.nDeskIndex;});
	if (iter != m_vectDeskRunOutMsg.end())
		iter->bRunOut = false;

	auto iterAgree = find_if(m_vectDeskRunOutAgree.begin(), m_vectDeskRunOutAgree.end(), [=](struct DeskRunOutAgree obj){ return pGameDesk->m_bDeskIndex== obj.nDeskIndex;});
	if (iterAgree != m_vectDeskRunOutAgree.end())
	{
		iterAgree->vectUserID.clear(); // ���ͬ������Ϣ
		iterAgree->vectAgree.clear();
	}
	pGameDesk->m_nDeskRunOutID = 0;
}

void CGameMainManage::AddDeskRunOutInfo(CGameDesk* pGameDesk)
{
	assert(pGameDesk != NULL);
	auto iter = find_if(m_vectDeskRunOutMsg.begin(), m_vectDeskRunOutMsg.end(), [=](struct DeskRunOutMsg obj){ return pGameDesk->m_bDeskIndex== obj.nDeskIndex;});
	if (iter == m_vectDeskRunOutMsg.end())
	{
		struct DeskRunOutMsg deskRunOut;
		deskRunOut.nDeskIndex = pGameDesk->m_bDeskIndex; // ���Ӻ���
		deskRunOut.bRunOut = true;
		m_vectDeskRunOutMsg.push_back(deskRunOut);
	}
	else
	{
		iter->bRunOut = true;
	}
}

void CGameMainManage::AddDeskRunOutAgreeInfo(CGameDesk* pGameDesk, CGameUserInfo* pUserInfo, bool bAgree)
{
	assert(pGameDesk != NULL);
	assert(pUserInfo != NULL);
	int agree = bAgree ? 1 : 0; // ͬ��1 ��ͬ��0
	auto iter = find_if(m_vectDeskRunOutAgree.begin(), m_vectDeskRunOutAgree.end(), [=](struct DeskRunOutAgree obj){ return pGameDesk->m_bDeskIndex== obj.nDeskIndex;});
	if (iter == m_vectDeskRunOutAgree.end())
	{
		struct DeskRunOutAgree obj;
		obj.nDeskIndex = pGameDesk->m_bDeskIndex;
		obj.vectUserID.push_back(pUserInfo->m_UserData.dwUserID);
		obj.vectAgree.push_back(agree);
		m_vectDeskRunOutAgree.push_back(obj);
	}
	else
	{
		iter->vectUserID.push_back(pUserInfo->m_UserData.dwUserID);
		iter->vectAgree.push_back(agree);
	}
}

void CGameMainManage::OnUpdateRoomInfo()
{
	//��������
	DL_GR_I_UpdateServerInfo UpdateInfo;
	UpdateInfo.uRoomID=m_InitData.uRoomID;
	UpdateInfo.uNameID=m_KernelData.uNameID;
	UpdateInfo.uOnLineUserCount=m_UserManage.GetGameRoomCount();
	m_SQLDataManage.PushLine(&UpdateInfo.DataBaseHead,sizeof(UpdateInfo),DTK_GR_UPDATE_INFO,0,0);
}