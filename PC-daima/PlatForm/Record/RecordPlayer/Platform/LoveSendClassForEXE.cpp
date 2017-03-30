// LoveSendClassForExe.cpp : ʵ���ļ�


#include "StdAfx.h"
#include "LoveSendClassForEXE.h"
#include "../PlayerLogic.h"

// CLoveSendClassForEXE

void DebugPrintf(const char *p, ...)
{
	char szFilename[256];
	sprintf( szFilename, "E:\\bzw\\DebugInfo\\DevForExe.txt" );
	va_list arg;
	va_start( arg, p );
	FILE *fp = fopen( szFilename, "a" );
	if (NULL == fp)
	{
		return;
	}
	vfprintf(fp, p, arg );
	fprintf(fp,"\n");
	fclose(fp);
}

IMPLEMENT_DYNAMIC(CLoveSendClassForEXE, CDialog)

CLoveSendClassForEXE::CLoveSendClassForEXE(void)
{
	m_hWndChannel = NULL;
	m_bWatchMode=true;
	m_bWatchOther=false;
}

CLoveSendClassForEXE::~CLoveSendClassForEXE(void)
{
}

BEGIN_MESSAGE_MAP(CLoveSendClassForEXE, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_COPYDATA()
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// ��ʼ�����˳�ǰ��EXE����
int CLoveSendClassForEXE::OnInitDialog()
{
	// ��ʼ������������Ϣ������е��ٽ���
	//InitializeCriticalSection(&m_csForIPCMessage);
	m_lstIPCMessage.clear();
	InitIPC();
	StartGameClient();
	ShowWindow(SW_HIDE);
	return 0;
}
void CLoveSendClassForEXE::OnDestroy()
{
	StopGameClient();
	DestroyIPC();
	// ��ʼ������������Ϣ������е��ٽ���
	//DeleteCriticalSection(&m_csForIPCMessage);
}

//============================================================================\\
// ���������������Ϣ

//���ͺ���
int CLoveSendClassForEXE::SendGameData(void * pData, UINT uBufLen, BYTE bMainID, BYTE bAssistantID, BYTE bHandleCode)
{
	return 0;
	if (m_pGameInfo->pMeUserInfo->GameUserInfo.bDeskNO==255) 
		return 0;
	return m_pGameInfo->pISocketSend->SendGameData(pData,uBufLen,bMainID,bAssistantID,bHandleCode);
}
//���ͺ���
int CLoveSendClassForEXE::SendGameData(BYTE bMainID, BYTE bAssistantID, BYTE bHandleCode)
{
	return 0;
	return m_pGameInfo->pISocketSend->SendGameData(bMainID,bAssistantID,bHandleCode);
}
// ���������������Ϣ
//============================================================================//



//----------------------------------------------------------------------------\\
// ��IFrameInterface�ӿڼ̳еĴ��麯��

//��ʼ��
bool CLoveSendClassForEXE::InitFrame(GameInfoStruct * pGameInfo, CWnd * pGameRoom)
{
	m_pGameInfo=pGameInfo;
	TranslateGameInfo();
	CIPCSendCopyData SendCopyData(m_hWndChannel,m_hWnd);
	SendCopyData.SendData(IPC_MAIN_CONFIG, IPC_SUB_SERVER_INFO, &m_GameInfo, sizeof(m_GameInfo));
	m_pGameRoom=pGameRoom;
	m_pGameRoom->SendMessage(IDM_GET_ROOMNAME,0,(LPARAM)&(m_szGameRoomName[0]));
	return true;
}

//��������
bool CLoveSendClassForEXE::AFCCreateFrame()
{
	if (GetSafeHwnd()==NULL) 
	{
		AfxSetResourceHandle(GetModuleHandle(FACE_DLL_NAME));
		Create(IDD_NULL, m_pGameRoom);
		AfxSetResourceHandle(GetModuleHandle(NULL));
	}
	else
	{
		//		if(InitIPC())
		StartGameClient();
	}

	return false;
}
//�رմ���
bool CLoveSendClassForEXE::AFCCloseFrame()
{
	StopGameClient();
	//DestroyIPC();
	if (GetSafeHwnd()!=NULL) 
	{
		ShowWindow (SW_HIDE);
		//DestroyWindow();
	}
	//CWnd * winApp=AfxGetApp()->m_pMainWnd;
	//if(winApp && winApp->m_hWnd)
	//	winApp->PostMessage(WM_USER+100,3,0);
	return false;
}
//��ʾ����
void CLoveSendClassForEXE::AFCShowFrame(int nShow)
{
	// ֪ͨ�ͻ���EXE������ʾ
	ShowWindow(SW_HIDE);
	return;
}
//����windows��Ϣ
LRESULT CLoveSendClassForEXE::SendWindowMessage(UINT msg,WPARAM wParam,LPARAM lParam)
{
	//---------�˴�Ӧ��֪ͨ�ͻ���EXE����
	////�����˵��ߺ󣬵��߸���
	if((msg>WM_USER+150) && (msg<WM_USER+155))
	{
		SendPlayerData(this->m_pGameInfo->pMeUserInfo);
		SendGlbData();
		return 0;
	}
	if (msg==WM_BRING_GAMEWND_TO_TOP)
	{
		SendBringToTopData();
	}

	////�ڵ������ʹ���˵���
	//if(msg==WM_USER+152)
	//{
	//	UsePropItem(wParam);
	//	return 0;
	//}
	return SendMessage(msg,wParam,lParam);
}
//ɾ������
void CLoveSendClassForEXE::DeleteFrame()
{
	StopGameClient();
	if (GetSafeHwnd() != NULL)
		OnCancel();
	delete this;
}

//������Ϣ�����Խ����ڲ������ĵ��ã���CGameRoomExͨ���ӿ�ָ����ã�pControlData����ܴ���ָ��
//�����Ȱ�ָ��������ȡ����������EXE���̣���������
UINT CLoveSendClassForEXE::OnControlMessage(UINT uControlCode, void * pControlData, UINT uDataSize)
{
	int nBufferLen = 0;
	BYTE *pBuffer = NULL;
	//��������
	switch (uControlCode)
	{
	case CM_USER_SEND_TIMES_MONEY: // �û��������
		{
			//send to game talking
			// ���ݽṹ��Ҳ��ָ�룬����ֱ�Ӵ�����͵�EXE����
			int nBufferLen = sizeof(UINT) + sizeof(CM_UserState_Send_Times_Money_For_Exe);
			BYTE *pBuffer = new BYTE[nBufferLen];

			memcpy( pBuffer, &uControlCode, sizeof(UINT) );
			CM_UserState_Send_Times_Money_For_Exe *pDes = (CM_UserState_Send_Times_Money_For_Exe *)(pBuffer + sizeof(UINT));
			CM_UserState_Send_Times_Money *pSrc = (CM_UserState_Send_Times_Money*)pControlData;
// 			pDes->dwUserID = pSrc->dwUserID;
// 			pDes->iSendMoney = pSrc->dwGetMoney;
// 			pDes->iSendTimes = pSrc->dwMoneyOnTimes;
// 			pDes->iLastTimes = pSrc->dwTimesNeed;
			memcpy(pDes,pSrc,sizeof(CM_UserState_Send_Times_Money));

			FlushMessage();
			CIPCSendCopyData SendCopyData(m_hWndChannel,m_hWnd);
			SendCopyData.SendData(IPC_MAIN_USER, IPC_SUB_USER_SCORE, (void*)pBuffer, (WORD)nBufferLen);

			delete [] pBuffer;
			pBuffer = NULL;
			break;
		}
	case CM_USER_STATE:		//�û�״̬�ı�
		{
			// ���ݽṹ�ﺬ��ָ�룬�����Ȱ�ָ��������ȡ�������ٴ�����͵�EXE����
			//Ч������
			if (uDataSize!=sizeof(CM_UserState_Change)) return 1;
			CM_UserState_Change * pStateChange=(CM_UserState_Change *)pControlData;
			// ʵ��Ҫ����������һ���ṹ
			//			CM_UserState_Change_ForExe *pBuffer = new CM_UserState_Change_ForExe;
			int nBufferLen = sizeof(UINT) + sizeof(CM_UserState_Change_ForExe);
			BYTE *pBuffer = new BYTE[nBufferLen];
			CM_UserState_Change_ForExe *p = (CM_UserState_Change_ForExe *)(pBuffer + sizeof(UINT));
			UINT *pControlCode = (UINT*)pBuffer;
			*pControlCode =uControlCode;
			p->bActionCode = pStateChange->bActionCode;
			p->bDeskStation = pStateChange->bDeskStation;

			if (pStateChange->pUserItem != NULL)
			{
				//// �ȸ��±�������
				//UserItemStruct *pThisUserItem = m_pGameInfo->pIFindUser->FindOnLineUser(pStateChange->pUserItem->GameUserInfo.dwUserID);
				//if (NULL != pThisUserItem)
				//{
				//	memcpy( pThisUserItem, pStateChange->pUserItem, sizeof(UserItemStruct) );
				//}
				// ��֪ͨEXE��Ϸ����
				memcpy( &p->uisUserItem, pStateChange->pUserItem, sizeof(UserItemStruct) );
			}
			//////////////////////////////////////////////////////////////////////////
			//add by ���ܶ�

			// ������Լ�����Ϣ
			if (p->uisUserItem.GameUserInfo.dwUserID == m_pGameInfo->pMeUserInfo->GameUserInfo.dwUserID)
			{
				// �Լ���������Ϣ������Ҫ����
				if ((p->bActionCode == ASS_GR_USER_UP)
					||(p->bActionCode == ASS_GR_WATCH_UP)
					||(p->bActionCode == ASS_GR_USER_LEFT)
					||(p->bActionCode == ASS_GR_USER_CUT)
					)
				{
					delete [] pBuffer;
					pBuffer = NULL;
					break;
				}
			}

			//////////////////////////////////////////////////////////////////////////
			// ����ͻ��˻�û����������Ӧ���������Ϣ�ݴ�����
			if (NULL == m_hWndChannel || m_GameInfo.uisMeUserInfo.GameUserInfo.bDeskStation == 255)
			{
				MessageToSendStruct msg;
				msg.ipcMain = IPC_MAIN_USER;
				msg.ipcSub = IPC_SUB_USER_STATUS;
				msg.pBuffer = pBuffer;
				msg.wSize = nBufferLen;

				DebugPrintf("�οͻ��˻�û���������ݴ���Ϣ, uControlCode = [%d], p->bActionCode = [%d], msg.pBuffer =[%X], msg.wSize = [%d]",
					*((UINT*)pBuffer),
					p->bActionCode,
					msg.pBuffer,
					msg.wSize
					);
				//EnterCriticalSection(&m_csForIPCMessage);
				m_lstIPCMessage.push_back(msg);
				//LeaveCriticalSection(&m_csForIPCMessage);
			}
			else
			{
				DebugPrintf("�οͻ����Ѿ�������������Ϣ, p->bActionCode = [%d]", p->bActionCode);
				FlushMessage();
				CIPCSendCopyData SendCopyData(m_hWndChannel,m_hWnd);
				SendCopyData.SendData(IPC_MAIN_USER, IPC_SUB_USER_STATUS, (void*)pBuffer, (WORD)nBufferLen);
				delete [] pBuffer;
				pBuffer = NULL;
			}
			////���ͻ�ȡ��Ϣ
			//MSG_GM_S_ClientInfo ClientInfo;
			//ClientInfo.bEnableWatch=m_pGameInfo->bEnableWatch;
			//SendGameData(&ClientInfo,sizeof(ClientInfo),MDM_GM_GAME_FRAME,ASS_GM_GAME_INFO,0);

			break;
		}
	default:
		break;
	}
	return 0;
}
//�����ȡ��Ϣ
bool CLoveSendClassForEXE::OnSocketReadEvent(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize, CTCPClientSocket * pClientSocket)
{
	//���˴���
	if (m_pGameInfo->pMeUserInfo->GameUserInfo.bDeskNO==255) 
		return true;
	//������Ϣ
	switch (pNetHead->bMainID)
	{
	case MDM_GM_GAME_FRAME:		//�����Ϣ
		{
			OnFrameMessage(pNetHead,pNetData,uDataSize,pClientSocket);
			break;
		}
	case MDM_GR_PROP:
		{
			OnPropMessage(pNetHead,pNetData,uDataSize,pClientSocket);
			break;
		}
	}
	//wushuqun 2009.6.18
	//�˴���MDM_GR_NETSIGNAL��ϢΪIPCģ����Ϣ
	NetMessageHead virNetMsg;
	memset(& virNetMsg,0,sizeof(NetMessageHead));
	virNetMsg.bMainID = MDM_GR_NETSIGNAL;
	virNetMsg.bAssistantID =  MDM_GR_NETSIGNAL;
	virNetMsg.bHandleCode = MDM_GR_NETSIGNAL;
	int nBufferLen1 = sizeof(NetMessageHead);
	BYTE *pBuffer1 = new BYTE[nBufferLen1];
	memcpy( pBuffer1, &virNetMsg, sizeof(NetMessageHead) );
	SendIPCMessage( pBuffer1, nBufferLen1 );

	////////////////////////////////////////

	// �����������Ϣ�����涼��ʵʵ���ڵ����ݣ�����Ҫ������\
	ֱ�Ӱ�pNetHead��pNetData�ϲ���ͨ��IPCת������
	int nBufferLen = sizeof(NetMessageHead) + uDataSize;
	BYTE *pBuffer = new BYTE[nBufferLen];

	memcpy( pBuffer, pNetHead, sizeof(NetMessageHead) );
	memcpy( pBuffer + sizeof(NetMessageHead), pNetData, uDataSize );
	SendIPCMessage( pBuffer, nBufferLen );

	return true;
}
//�����Ϣ����������Ҫ�ı�m_pGameInfo��״̬
bool CLoveSendClassForEXE::OnFrameMessage(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize, CTCPClientSocket * pClientSocket)
{
	ASSERT(pNetHead->bMainID==MDM_GM_GAME_FRAME);
	switch (pNetHead->bAssistantID)
	{
	case ASS_GM_GAME_INFO:		//��Ϸ��Ϣ
		{
			//Ч������
			MSG_GM_S_GameInfo * pGameInfo=(MSG_GM_S_GameInfo *)pNetData;

			//��������
			m_bWatchOther=(pGameInfo->bWatchOther==TRUE);
			m_bWaitTime=pGameInfo->bWaitTime;
			m_bWatchMode=(m_pGameInfo->pMeUserInfo->GameUserInfo.bUserState==USER_WATCH_GAME);
			SetStationParameter(pGameInfo->bGameStation);
			return true;
		}
	}
	return false;
}
//������Ϣ
bool CLoveSendClassForEXE::OnPropMessage(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize, CTCPClientSocket * pClientSocket)
{
	switch(pNetHead->bAssistantID)
	{
	case ASS_PROP_USEPROP:
		return OnUsePropResult(pNetHead,pNetData,uDataSize,pClientSocket);
	default:
		break;
	}
	return true;
}
//���������Ϣ
bool CLoveSendClassForEXE::OnUsePropResult(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize, CTCPClientSocket * pClientSocket)
{
	if(pNetHead->bHandleCode!=DTK_GR_PROP_USE_SUCCEED)
		return true;
	if(sizeof(_TAG_USINGPROP)!= uDataSize)
		return false;
	_TAG_USINGPROP * usingProp = (_TAG_USINGPROP *)pNetData;
	UserItemStruct *pUserInfo =m_pGameInfo->pIFindUser->FindOnLineUser(usingProp->dwTargetUserID);
	UserItemStruct *pUserInfoUsed =m_pGameInfo->pIFindUser->FindOnLineUser(usingProp->dwUserID);
	if(pUserInfo == NULL)
		return true;

	int attribAction=usingProp->nPropActionAttrib;
	int attribValue=usingProp->nPropValueAttrib;
	//˫������
	if(attribAction & 0x4)
	{
		pUserInfo->GameUserInfo.iDoublePointTime=usingProp->iDoubleTime;
	}
	if(attribAction & 0x8)
	{
		pUserInfo->GameUserInfo.iProtectTime=usingProp->iProtectTime;
	}

	if(attribAction & 0x10)
	{
		int fasciChange=(attribValue & 0xFF0000)>>16;
		if(attribAction & 0x20)
		{
			fasciChange=-fasciChange;
		}
		//pUserInfo->GameUserInfo.dwFascination+=fasciChange;
	}
	if(attribAction & 0x2)
	{
		if(usingProp->dwTargetUserID==m_pGameInfo->pMeUserInfo->GameUserInfo.dwUserID)
		{
			if(m_pGameInfo->pMeUserInfo->GameUserInfo.dwPoint<0)
				m_pGameInfo->pMeUserInfo->GameUserInfo.dwPoint=0;
		}
		if (pUserInfoUsed->GameUserInfo.dwPoint<0)
		{
			pUserInfoUsed->GameUserInfo.dwPoint = 0;
		}
	}
	FlushMessage();
	SendPlayerData(pUserInfo);
	// ������Լ�
	if ((pUserInfoUsed->GameUserInfo.dwUserID==m_pGameInfo->pMeUserInfo->GameUserInfo.dwUserID)
		||(pUserInfo->GameUserInfo.dwUserID==m_pGameInfo->pMeUserInfo->GameUserInfo.dwUserID))
	{
		SendGlbData();
	}
	this->GetParent()->BringWindowToTop();
	return true;
}

//������Ϸ������Ϣ
void CLoveSendClassForEXE::ShowMsgInGame(TCHAR * szMsg, BYTE bNewOrSys, UINT uSize, TCHAR * szFontName,TCHAR *Title)
{
	MsgInGameStruct msg;
	// ��Ϣ������Ϊ��
	if (NULL == szMsg)
	{
		return;
	}
	_tcscpy(msg.szMsg, szMsg);
	msg.bIsFontValid = false;
	msg.bIsTitleValid = false;
	if (NULL != szFontName)
	{
		msg.bIsFontValid = true;
		_tcscpy(msg.szFontName, szFontName);
	}
	if (NULL != Title)
	{
		msg.bIsTitleValid = true;
		_tcscpy(msg.szTitle, Title);
	}
	msg.bNewOrSys	= bNewOrSys;
	msg.uSize		= uSize;
	FlushMessage();
	CIPCSendCopyData SendCopyData(m_hWndChannel,m_hWnd);
	SendCopyData.SendData(IPC_MAIN_CONCTROL, IPC_SUB_SHOW_MSG_IN_GAME, (void*)&msg, sizeof(msg));

}

//��������Ϣ
void CLoveSendClassForEXE::ShowMsgDudu(TCHAR * szSendName,
									   TCHAR * szTargetName,
									   TCHAR * szCharString,
									   COLORREF crTextColor,
									   bool bShowTime,
									   UINT uSize,
									   TCHAR * szFontName,
									   int iDuduType)
{
	MsgDuduStruct msgDudu;
	msgDudu.bIsFontValid = false;
	_tcscpy(msgDudu.szSendName, szSendName);
	_tcscpy(msgDudu.szTargetName, szTargetName);
	_tcscpy(msgDudu.szCharString, szCharString);
	msgDudu.crTextColor = crTextColor;
	msgDudu.bShowTime = bShowTime;
	msgDudu.uSize = uSize;
	msgDudu.iDuduType = iDuduType;
	if (NULL != szFontName)
	{
		msgDudu.bIsFontValid = true;
		_tcscpy(msgDudu.szFontName, szFontName);
	}
	FlushMessage();
	CIPCSendCopyData SendCopyData(m_hWndChannel,m_hWnd);
	SendCopyData.SendData(IPC_MAIN_CONCTROL, IPC_SUB_SHOW_DUDU, (void*)&msgDudu, sizeof(msgDudu));
}

//����������Ϣ
void CLoveSendClassForEXE::SendShortMessage(MSG_GR_RS_NormalTalk *pShortMessage)
{
}


//----------------------------------------------------------------------------//


//============================================================================\\
//IPC֧�֡�
//========
// ����IPC
bool CLoveSendClassForEXE::DestroyIPC()
{
	UnmapViewOfFile(m_pShareMemory);
	m_pShareMemory = NULL;
	CloseHandle(m_hShareMemory);
	m_hShareMemory = NULL;
	KillTimer(TIMER_HEART_BEAT);
	return true;
}
//��ʼ��IPC
bool CLoveSendClassForEXE::InitIPC()
{
	//���������ڴ�(������Ը�������������Ϸ��ID,������IP,�˿ڵ���Ϊ�ļ���ʶ��)
	//sprintf(m_szShareName,"0x%s%ld%ld",IPCFILENAME,time(NULL),rand()%100);
	time_t this_time;
	time(&this_time);
	sprintf(m_szShareName,"0x%s%ld%ld", IPCFILENAME, this_time, rand()%100);

	//	strcpy(m_szShareName,"123456");

	m_hShareMemory=(HANDLE)CreateFileMapping((HANDLE)0xFFFFFFFFFFFF,NULL,PAGE_READWRITE,0,sizeof(tagShareMemory),m_szShareName);

	if (m_hShareMemory==NULL) 
	{
		AfxMessageBox("�����ڴ��ļ�ʧ��!");

		if(GetLastError()==ERROR_ALREADY_EXISTS)
			AfxMessageBox("�ڴ��ļ��Ѿ�����!");

		return false;
	}

	m_pShareMemory=(tagShareMemory *)MapViewOfFile(m_hShareMemory,FILE_MAP_ALL_ACCESS,0,0,0);

	//���ù����ڴ�
	memset(m_pShareMemory,0,sizeof(tagShareMemory));
	m_pShareMemory->wDataSize=sizeof(tagShareMemory);
	m_pShareMemory->hWndGamePlaza	=	m_hWnd;
	m_pShareMemory->hWndGameServer	=	m_hWnd;


	if (m_IPCRecvCopyData.SetChannelMessageSink(this)==false) 
		return false;

	TRACE("���������ڴ� [%s]  ��ɡ�",m_szShareName );

	return true;
}

// IPC�ص��ӿ�
bool __cdecl CLoveSendClassForEXE::OnChannelMessage(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend)
{
	m_dwIPCHeartBeatTick = GetTickCount();
	switch (pHead->wMainCmdID)
	{
	case IPC_MAIN_IPC_KERNEL:		//�ں���Ϣ
		{
			return OnIPCKernel(pHead,pIPCBuffer,wDataSize,hWndSend);
		}
	case IPC_MAIN_SOCKET:			//�����¼�
		{
			return OnIPCSocket(pHead,pIPCBuffer,wDataSize,hWndSend);
		}
	case IPC_MAIN_USER:
		{
			return OnIPCUserInfo(pHead,pIPCBuffer,wDataSize,hWndSend);
		}
	case IPC_MAIN_CONFIG:
		{
			DebugPrintf("IPC_MAIN_CONFIGʱFlushMessage()");
			// ����ǰ���е���Ϣ����ʱ����
			FlushMessage();
			// ��Glb()��Ĳ������ݣ����û�������Ϣ����ַ����Ϣ���ͳ�ȥ
			// �յ�EXE�������Ļظ�����֪ͨ��Ϸ�����Ѿ�����
			if (IPC_SUB_SERVER_INFO == pHead->wSubCmdID)
			{
				// ��������Ϸ
				AfxGetApp()->m_pMainWnd->PostMessage(WM_USER+100,2,0);
			}
			return true;
		}
	case IPC_MAIN_PROP:
		{
			return OnIPCUseProp(pHead,pIPCBuffer,wDataSize,hWndSend);
		}
	default:
		break;
	}
	return false;
}

//IPC�ں�����
bool CLoveSendClassForEXE::OnIPCKernel(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend)
{
	ASSERT(pHead->wMainCmdID==IPC_MAIN_IPC_KERNEL);
	switch (pHead->wSubCmdID)
	{
	case IPC_SUB_IPC_CLIENT_CONNECT:	//������Ϣ
		{
			TRACE("IPC_SUB_IPC_CLIENT_CONNECT");

			//���ñ���
			m_hWndChannel=hWndSend;			//��ȡ�ͻ���channel���ھ��
			// ����������ʱ��
			SetTimer(TIMER_HEART_BEAT, HEART_BEAT_SECOND*1000, NULL);

			TranslateGameInfo();
			// ����Ϸ���ڳ�ʼ����ص����ݷ��ͳ�ȥ������б�
			CIPCSendCopyData SendCopyData(m_hWndChannel,m_hWnd);
			SendCopyData.SendData(IPC_MAIN_CONFIG, IPC_SUB_SERVER_INFO, &m_GameInfo, sizeof(m_GameInfo));
			SendGlbData();
			FlushMessage();
			m_dwIPCHeartBeatTick = GetTickCount();
			return true;
		}
	case IPC_SUB_IPC_CLIENT_CLOSE:		//��EXE���������Ĺر���Ϣ
		{
			// �ͻ��������Ͽ�
			ExeClientShutDown();
			
			if (m_pGameInfo->uNameID == 10000300
				|| m_GameInfo.uNameID == 11200405
				|| m_GameInfo.uNameID == 20013400
				|| m_GameInfo.uNameID == 20014410)//090514a1JJ ǿ���߳�����
			{
				if (m_pGameInfo->pMeUserInfo!=NULL && m_pGameInfo->pMeUserInfo->GameUserInfo.bUserState == USER_PLAY_GAME)
				{
					//Mod-�����й����⴦��-20090512
					m_pGameRoom->PostMessage(IDM_QUIT_ROOM_MSG,0,0);
				}
				/*CString str111;
				const GameInfoStruct * const pG = m_pGameInfo;
				str111.Format("UserInfo=%d UserState=%d GameStation=%d", (int)(pG->pMeUserInfo), pG->pMeUserInfo->GameUserInfo.bUserState,
					pG->bGameStation);
				AfxMessageBox(str111);*/
			}
			return true;
		}
	case IPC_SUB_CLOSE_FRAME:	// ƽ̨������EXE�ͻ���ʱ����EXE��Ӧ����Ϣ
		{
			AfxGetApp()->m_pMainWnd->PostMessage(WM_USER+100,3,0);
			break;
		}
	}
	return false;
}
//����ָ��
bool CLoveSendClassForEXE::OnIPCSocket(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend)
{
	return true;
	struct SendGameDataStruct 
	{
		BYTE bMainID;
		BYTE bAssistantID;
		BYTE bHandleCode;
	};
	ASSERT(pHead->wMainCmdID==IPC_MAIN_SOCKET);
	switch (pHead->wSubCmdID)
	{
	case IPC_SUB_SOCKET_SEND:	//������Ϣ
		{
			//Ч�����ݺ�ת����������
			//SendGameData();
			if (sizeof(SendGameDataStruct)==wDataSize)
			{
				SendGameDataStruct *pMsg = (SendGameDataStruct *)pIPCBuffer;
				m_pGameInfo->pISocketSend->SendGameData(pMsg->bMainID,
					pMsg->bAssistantID,
					pMsg->bHandleCode);
			}
			else
			{
				SendGameDataStruct *pMsg = (SendGameDataStruct *)pIPCBuffer;
				void *pData = (BYTE*)pIPCBuffer + sizeof(SendGameDataStruct);
				m_pGameInfo->pISocketSend->SendGameData(pData,
					wDataSize-sizeof(SendGameDataStruct),
					pMsg->bMainID,
					pMsg->bAssistantID,
					pMsg->bHandleCode);
			}

			return true;
		}
	case TIMER_HEART_BEAT:
		{
			// ��¼ʱ��
			m_dwIPCHeartBeatTick = GetTickCount();
			return true;
		}
	}
	return false;
}
//����ָ��
bool CLoveSendClassForEXE::OnIPCUserInfo(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend)
{
	ASSERT(pHead->wMainCmdID==IPC_MAIN_USER);
	switch (pHead->wSubCmdID)
	{
	case IPC_SUB_ASK_USER_LIST:	//�����嵥��Ϣ
		{
			//Ч������
			//ASSERT(wDataSize>=sizeof(CMD_Command));
			//if (wDataSize<sizeof(CMD_Command))
			//{
			//	return false;
			//}
			// ���ݴ��������ţ���ȡͬ������嵥
			BYTE bDeskNo = *(BYTE*)pIPCBuffer;
			CPtrArray PlayUser,WatchUser;
			m_pGameInfo->pIFindUser->FindOnLineUser(bDeskNo,PlayUser,WatchUser);
			// UserItemStruct�ĳ���ͦ�����ּ��δ�ȥ��ÿ�δ������ṹ
			FlushMessage();
			CIPCSendCopyData SendUserData(m_hWndChannel,m_hWnd);
			for (INT_PTR i=0;i<PlayUser.GetCount();i++)
			{
				UserItemStruct * pUserItem=(UserItemStruct *)PlayUser.GetAt(i);
				if (pUserItem!=NULL)
				{
					SendUserData.SendData(IPC_MAIN_USER, IPC_SUB_REPLY_USER_LIST, (void*)pUserItem, sizeof(UserItemStruct));
				}
			}
			// �����ԹۺͲμ���Ϸ����EXE�˸���pUserItem->GameUserInfo.bUserState���ж����Թۻ��ǲ���
			for (INT_PTR i=0;i<WatchUser.GetCount();i++)
			{
				UserItemStruct * pUserItem=(UserItemStruct *)WatchUser.GetAt(i);
				if (pUserItem!=NULL) 
				{
					SendUserData.SendData(IPC_MAIN_USER, IPC_SUB_REPLY_USER_LIST, (void*)pUserItem, sizeof(UserItemStruct));
				}
			}

			m_bIsGameValid = true;
			return true;
		}
		//////////////////////////////////////////////////////////////////////////
		//add by ���ܶ�
	case IPC_SUB_GAME_START:	// ����Ϸ�������ĸı���Ϸ״̬����Ϣ
		{
			BYTE bStation = *(BYTE*)pIPCBuffer;
			this->SetStationParameter(bStation);
			break;
		}
		//////////////////////////////////////////////////////////////////////////
	}
	return false;
}
//����ָ��
bool CLoveSendClassForEXE::OnIPCUseProp(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend)
{
	ASSERT(pHead->wMainCmdID==IPC_MAIN_PROP);
	switch (pHead->wSubCmdID)
	{
	case IPC_SUB_BROADCAST_BIG:	//�㲥�����ִ�С����С��pIPCBuffer���ж�
		{
			BYTE *pBuffer = (BYTE*)pIPCBuffer;
			_TAG_BOARDCAST *pBroad = (_TAG_BOARDCAST *)pBuffer;
			int nBroadcastType = *((int*)(pBuffer + sizeof(_TAG_BOARDCAST)));
			// �������ͣ�������Ӧ����
			if (nBroadcastType == BRD_MSG_BIG)
			{
				//GetMainRoom()->m_TCPSocket.SendData(pBroad,sizeof(_TAG_BOARDCAST),MDM_GP_PROP,ASS_PROP_BIG_BOARDCASE,0);
			}
			else
			{
				//SendGameData(pBroad,sizeof(_TAG_BOARDCAST),MDM_GR_PROP,ASS_PROP_SMALL_BOARDCASE,0);
			}
			return true;
		}
	case IPC_SUB_BUY_PROP:	// �����
		{
			if (wDataSize != sizeof(_TAG_PROP_BUY))
			{
				return false;
			}
			_TAG_PROP_BUY *pPropBuy = (_TAG_PROP_BUY *)pIPCBuffer;
			//GetMainRoom()->m_TCPSocket.SendData(pPropBuy, wDataSize, MDM_GP_PROP, ASS_PROP_BUY, 0);
			//DebugPrintf("GetMainRoom()->m_TCPSocket.SendData(pPropBuy, %d, MDM_GP_PROP, ASS_PROP_BUY, 0);", wDataSize);
			return true;
		}
	case IPC_SUB_PRESENT_PROP:	// �͵��߸�����
		{
			if (wDataSize != sizeof(_TAG_PROP_GIVE))
			{
				return false;
			}
			_TAG_PROP_GIVE *pPropGive = (_TAG_PROP_GIVE *)pIPCBuffer;
			//GetMainRoom()->m_TCPSocket.SendData(pPropGive, sizeof(_TAG_PROP_GIVE), MDM_GP_PROP, ASS_PROP_GIVE, 0);
			DebugPrintf("[%s]��[%s][%d]��[%d]��ֵ[%d]---Dev",
				pPropGive->szUser, pPropGive->szTargetUser, pPropGive->nGiveCount, pPropGive->nPropID, pPropGive->iPropValue);

			return true;
		}
	}
	return false;
}
// ����IPC��Ϣ
bool CLoveSendClassForEXE::SendIPCMessage(void * pIPCBuffer, WORD wDataSize)
{
	//////////////////////////////////////////////////////////////////////////
	// ����ͻ��˻�û����������Ӧ���������Ϣ�ݴ�����
	//m_bIsGameValid = true;

	if ( !m_bIsGameValid || NULL == m_hWndChannel)
	{
		DebugPrintf("�οͻ��˻�û���������ݴ���ϢSendIPCMessage()");
		MessageToSendStruct msg;
		msg.ipcMain = IPC_MAIN_SOCKET;
		msg.ipcSub = IPC_SUB_SOCKET_SEND;
		msg.pBuffer = (BYTE*)pIPCBuffer;
		msg.wSize = wDataSize;
		//EnterCriticalSection(&m_csForIPCMessage);
		m_lstIPCMessage.push_back(msg);
		//LeaveCriticalSection(&m_csForIPCMessage);
		return false;
	}
	else
	{
//		DebugPrintf("�οͻ����Ѿ�������������Ϣ, SendIPCMessage()");
		FlushMessage();
		CIPCSendCopyData SendCopyData(m_hWndChannel,m_hWnd);
		SendCopyData.SendData(IPC_MAIN_SOCKET, IPC_SUB_SOCKET_SEND, pIPCBuffer, wDataSize);
		delete [] pIPCBuffer;
		pIPCBuffer = NULL;
		return true;
	}
}
// 
BOOL CLoveSendClassForEXE::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	if (m_IPCRecvCopyData.OnCopyData(pWnd->GetSafeHwnd(), pCopyDataStruct)==true) 
		return TRUE;

	return CWnd::OnCopyData(pWnd, pCopyDataStruct);
}

// IPC֧�֡�
//============================================================================//


//�˳�����ʱ��Ҫ֪ͨ������������Ѿ������˿ͻ��˳��򣬻���Ҫ��EXE����ص�
void CLoveSendClassForEXE::OnCancel()
{
	//��ѯ״̬
	if ((m_bWatchMode==false)&&GetStationParameter() >= 20 && GetStationParameter() < 23)//!CanLeftDesk())
	{
		SendGameData(MDM_GM_GAME_FRAME,ASS_GM_FORCE_QUIT,0);
	}
	if (m_pGameInfo->pMeUserInfo->GameUserInfo.bDeskNO!=255) 
		SendGameData(MDM_GR_USER_ACTION,ASS_GR_USER_UP,0);

	return;
}

/// ֹͣEXE����
int CLoveSendClassForEXE::StopGameClient()
{
	if (NULL ==m_hWndChannel)
		return -1;

	m_bIsGameValid = false;
	//�رտͻ��˳���ͨ��������Ϣ
	CIPCSendCopyData SendCopyData(m_hWndChannel,m_hWnd);
	SendCopyData.SendData(IPC_MAIN_CONCTROL,IPC_SUB_CLOSE_FRAME);

	// ���ԭ���
	m_hWndChannel = NULL;

	//	OnCancel();
	return 0;
}

// ����EXE����
int CLoveSendClassForEXE::StartGameClient()
{
	//�ж��Ƿ��Ѿ�����
	ASSERT(m_pShareMemory!=NULL);

	if( NULL != m_hWndChannel )
	{
		return -1;
	}
	TranslateGameInfo();
	//����������
	CString strCommonLine;
	strCommonLine.Format(TEXT("%d/%s /RoomToken:%s"),
		//m_pGameInfo->szProcessName,
		m_pGameInfo->uNameID,
		"GameLauncher.exe",
		m_szShareName);	// ����Ϸ��Ϣ����EXE�����������

	//������Ϸ�ͻ���
	STARTUPINFO StartInfo;
	memset(&StartInfo,0,sizeof(StartInfo));
	StartInfo.cb=sizeof(StartInfo);
	StartInfo.wShowWindow=SW_SHOWMAXIMIZED;
	BOOL bSuccess=CreateProcess(NULL,strCommonLine.GetBuffer(),NULL,NULL,FALSE,CREATE_DEFAULT_ERROR_MODE,NULL,NULL,&StartInfo,&m_GameProcessInfo);
	strCommonLine.ReleaseBuffer();
	if (bSuccess==FALSE)
	{
		memset(&m_GameProcessInfo,0,sizeof(m_GameProcessInfo));
		return SM_CREATE_ERROR;
	}
	return 0;
}

void CLoveSendClassForEXE::TranslateGameInfo(void)
{
	m_GameInfo.bDeskOnwer		= m_pGameInfo->bDeskOnwer;
	m_GameInfo.bGameStation		= m_pGameInfo->bGameStation;						//��Ϸ״̬
	memcpy(&m_GameInfo.uisMeUserInfo, m_pGameInfo->pMeUserInfo, sizeof(m_GameInfo.uisMeUserInfo));	//�����Ϣ
	m_GameInfo.dwGamePower		= m_pGameInfo->dwGamePower;							//�û�Ȩ��
	m_GameInfo.dwMasterPower	= m_pGameInfo->dwMasterPower;						//����Ȩ��
	m_GameInfo.dwRoomRule		= m_pGameInfo->dwRoomRule;							//���ù���

	m_GameInfo.bEnableSound		= m_pGameInfo->bEnableSound;						//��������
	m_GameInfo.bEnableWatch		= m_pGameInfo->bEnableWatch;						//�����Թ�
	m_GameInfo.bShowUserInfo	= m_pGameInfo->bShowUserInfo;						//��ʾ����
	m_GameInfo.bEnableBackSound = m_pGameInfo->bEnableBackSound;					//��������

	m_GameInfo.uDeskPeople		= m_pGameInfo->uDeskPeople;						//��Ϸ����
	m_GameInfo.uRoomID			= m_pGameInfo->uRoomID;							//�����ʾ
	m_GameInfo.dwGameMSVer		= m_pGameInfo->dwGameMSVer;						//���汾��
	m_GameInfo.dwGameLSVer		= m_pGameInfo->dwGameLSVer;						//���汾��
	m_GameInfo.uComType			= m_pGameInfo->uComType;						//��Ϸ����
	m_GameInfo.uNameID			= m_pGameInfo->uNameID;							//���ֱ�ʾ
	m_GameInfo.uLessPoint		= m_pGameInfo->uLessPoint;						//���پ���ֵ
	_tcscpy(m_GameInfo.szProcessName, m_pGameInfo->szProcessName);				//�������֣��硰zjh.exe��
	_tcscpy(m_GameInfo.szGameName, m_pGameInfo->szGameName);					//��Ϸ���֣��硰���𻨡�

	m_GameInfo.pOrderName		= NULL;								//�ȼ�������EXE�˱�����ã������в���

	//wushuqun 2009.6.3
	m_GameInfo.bIsInRecord = m_pGameInfo->bIsInRecord;
}

// ����Ϣ������������ȷ���ȥ
void CLoveSendClassForEXE::FlushMessage(void)
{
	if (!m_bIsGameValid)
	{
		DebugPrintf("�ͻ���δ׼���ã����أ��ݲ�����Ϣ");
		return;
	}
	
	//EnterCriticalSection(&m_csForIPCMessage);
	CIPCSendCopyData SendCopyData(m_hWndChannel,m_hWnd);
	if (m_lstIPCMessage.size()==0)
	{
		return;
	}
	try
	{
		
		std::list<MessageToSendStruct>::iterator it = m_lstIPCMessage.begin();
		while (it!=m_lstIPCMessage.end())
		{
			CM_UserState_Change_ForExe *p = (CM_UserState_Change_ForExe *)(it->pBuffer + sizeof(UINT));
			UINT *pTemp = (UINT*)(it->pBuffer);
			DebugPrintf("FlushMessage, uControlCode =[%d] actCode=[%d]", *pTemp, p->bActionCode);
			SendCopyData.SendData(it->ipcMain, it->ipcSub, it->pBuffer, it->wSize);
			delete []it->pBuffer;
			it->pBuffer = NULL;
			m_lstIPCMessage.pop_front();
			it = m_lstIPCMessage.begin();
		}
	}
	catch (...)
	{
		//LeaveCriticalSection(&m_csForIPCMessage);
		exit(-1);
	}
	//LeaveCriticalSection(&m_csForIPCMessage);
}
void CLoveSendClassForEXE::SendGlbData(void)
{
	// �����м���������Ҫ��� \\
	1������\
	2����ҳ\
	3����ַ

	CIPCSendCopyData SendCopyData(m_hWndChannel,m_hWnd);
	// ȡ����������ݣ��Ǹ�ָ�����飬��Ҫ���������ٷ���
	int nPropCount = Glb().userPropLibrary.GetCount();
	if (nPropCount>0)
	{
		// ��Glb()�л�ȡ����ָ�룬��������
		_TAG_USERPROP *userProp=NULL;
		for (int curPropIndex=0; curPropIndex<nPropCount; ++curPropIndex)
		{
			userProp=Glb().userPropLibrary.GetAt(curPropIndex);
			SendCopyData.SendData(IPC_MAIN_PROP, IPC_SUB_INIT_PROP, userProp, sizeof(_TAG_USERPROP));
		}
	}
	SendCopyData.SendData(IPC_MAIN_PROP, IPC_SUB_INIT_PROP_FINISH, &nPropCount, sizeof(int)); // ��ʾ���ͽ���
	return;
}
void CLoveSendClassForEXE::SendBringToTopData(void)
{
	// ��ͬ��ĳ��������ٴδ��͹�ȥ����Ϊ��ʹ�õ��ߵ�ʱ��������ݻ��б仯
	FlushMessage();
	CIPCSendCopyData SendCopyData(m_hWndChannel,m_hWnd);
	SendCopyData.SendData(IPC_MAIN_CONCTROL, IPC_SUB_JOIN_IN_GAME, 0, 0);
	return;
}
void CLoveSendClassForEXE::SendPlayerData(UserItemStruct *pUserInfo)
{
	// ��ͬ��ĳ��������ٴδ��͹�ȥ����Ϊ��ʹ�õ��ߵ�ʱ��������ݻ��б仯
	FlushMessage();
	CIPCSendCopyData SendCopyData(m_hWndChannel,m_hWnd);
	SendCopyData.SendData(IPC_MAIN_USER, IPC_SUB_USER_COME, pUserInfo, sizeof(UserItemStruct));
	return;
}
void CLoveSendClassForEXE::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{
	case TIMER_HEART_BEAT:
		{
			if (NULL==m_hWndChannel)
			{
				KillTimer(TIMER_HEART_BEAT);
				return;
			}
			DWORD dwThisTick = GetTickCount();
			if (dwThisTick - m_dwIPCHeartBeatTick > (HEART_BEAT_DELAY+HEART_BEAT_SECOND)*1000) // ������ʱ
			{
				//��ʾEXE���Ѿ�ֹͣ�ˣ����������ִ�������ģ����ߣ�ģ��EXE�ͻ��������ر�
				//������ģ��EXE�������˷��͹ر���Ϣ
				SendGameData(MDM_GM_GAME_FRAME,ASS_GM_FORCE_QUIT,0);
				ExeClientShutDown();
				this->SetStationParameter(0);

				//Mod-�����й����⴦��-20090512
				if (m_GameInfo.uNameID == 10000300
					|| m_GameInfo.uNameID == 11200405
					|| m_GameInfo.uNameID == 20013400
					|| m_GameInfo.uNameID == 20014410)
				{
					if (m_pGameInfo->pMeUserInfo!=NULL && m_pGameInfo->pMeUserInfo->GameUserInfo.bUserState == USER_PLAY_GAME)
					{
						//Mod-�����й����⴦��-20090512
						m_pGameRoom->PostMessage(IDM_QUIT_ROOM_MSG,0,0);
					}
				}
			}
			else
			{
				FlushMessage();
				CIPCSendCopyData SendCopyData(m_hWndChannel,m_hWnd);
				SendCopyData.SendData(IPC_MAIN_SOCKET, IPC_SUB_IPC_HEART_BEAT, NULL, 0);
			}
			break;
		}
	default:
		break;
	}
}

void CLoveSendClassForEXE::ExeClientShutDown()
{
	// ���ԭ���
	if (NULL != m_hWndChannel)
	{
		m_hWndChannel = NULL;

		//EnterCriticalSection(&m_csForIPCMessage);
		// �����Ϣ�����������
		std::list<MessageToSendStruct>::iterator itBegin = m_lstIPCMessage.begin();
		std::list<MessageToSendStruct>::iterator itEnd = m_lstIPCMessage.end();
		std::list<MessageToSendStruct>::iterator it = m_lstIPCMessage.begin();
		for (; it != m_lstIPCMessage.end(); ++it)
		{
			DebugPrintf("ɾ�����������Ϣ");
			delete []it->pBuffer;
			it->pBuffer = NULL;
		}
		m_lstIPCMessage.clear();
		//LeaveCriticalSection(&m_csForIPCMessage);
	}

	// ��������������������Ϣ
	OnCancel();
	AfxGetApp()->m_pMainWnd->PostMessage(WM_USER+100,3,0);
	KillTimer(TIMER_HEART_BEAT);
}
