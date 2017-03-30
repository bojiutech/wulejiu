#include "StdAfx.h"
#include "AddRecordModule.h"

typedef IRecorderForPlatform * (CreateRecordPlatForm)();

CAddRecordModule::CAddRecordModule(void)
{
	m_hRecordInstance = NULL;
	m_pRecordMoudlePlat = NULL;
	m_bIsRecordAvailable = false;
}

CAddRecordModule::~CAddRecordModule(void)
{
	ReleaseRecordMoule();  //���ĳЩ����
}

//¼�����õ��ĺ���
bool CAddRecordModule::CreatRecorMoudle(const TCHAR* pAppPath,bool bIsRecordAvailable)
{
	if (pAppPath == NULL)
	{
		m_bIsRecordAvailable = false;
		return false;
	}
	m_bIsRecordAvailable = bIsRecordAvailable;
	if (m_bIsRecordAvailable == false)
	{
		return false;
	}
	
	TCHAR filename[600];	
	wsprintf(filename,TEXT("%sRecordModule.dll"),pAppPath);	
	CFileFind ff;
	bool bexist=ff.FindFile(filename);
	if (!bexist)
	{
		m_bIsRecordAvailable = false;
		return false;
	}
	if (m_pRecordMoudlePlat == NULL)
	{
		m_hRecordInstance = LoadLibrary(filename);
		if (m_hRecordInstance == NULL)
		{	
			//AFCCloseFrame();
			return false;
		}

		CreateRecordPlatForm* pCreatPlayer = (CreateRecordPlatForm*)(GetProcAddress(m_hRecordInstance,GETFORPLATFORM));
		if (pCreatPlayer == NULL)
		{

			//throw TEXT("��ʼ������ʧ��!");

			return false;
		}
		m_pRecordMoudlePlat = pCreatPlayer();
		if (m_pRecordMoudlePlat == NULL)
		{		
			//throw TEXT("��ʼ������ʧ��!");
			return false;
		}
	}
	

	m_pRecordMoudlePlat->InitAll();    //��ʼ�����в���

	return true;
}

void CAddRecordModule::InitRecordMoudle(GameInfoStruct* sourcegameinfo,TCHAR* szClienDllName,BYTE bMyDeskStation)      //��ʼ��¼����
{
	if (m_bIsRecordAvailable == false)
	{
		return;
	}
	if (m_pRecordMoudlePlat == NULL)
	{
		return;
	}
	m_pRecordMoudlePlat->InitAll();
	CPRStructExchange exchange;
	RecordGameInfoStruct gaminfo;
	exchange.ChangeGameRoomPlatToReClient(&gaminfo,sourcegameinfo,szClienDllName,bMyDeskStation);
	m_pRecordMoudlePlat->AddRoomGameInfo(&gaminfo);
}
void CAddRecordModule::ReleaseRecordMoule()    //�ͷ�¼����
{
	if (m_pRecordMoudlePlat != NULL)
	{
		m_pRecordMoudlePlat->Release();
	}
	if (m_hRecordInstance != NULL)
	{
		FreeLibrary(m_hRecordInstance);	
	}
}
bool CAddRecordModule::SaveRecordFile(const TCHAR* pAppPath,const TCHAR* pMyName,UINT uNameId)
{
	//Ŀ¼����ṹΪ  ִ��Ŀ¼/log/log_username/time/
	if (m_bIsRecordAvailable == false)
	{
		return false;
	}
	if (pAppPath == NULL || pMyName == NULL)
	{
		return false;
	}
	if (m_pRecordMoudlePlat == NULL)
	{
		return false;
	}

	TCHAR  path[1000];
	wsprintf(path,TEXT("%s"),pAppPath) ;// + TEXT("VideoCfg.ini");

	TCHAR FileName[1000];

	//����log Ŀ¼
	wsprintf(FileName, TEXT("log"),path);
	::CreateDirectory(FileName,NULL);

	//�����û���log
	wsprintf(path,TEXT("%s\\log_%s"),FileName,pMyName);
	::CreateDirectory(path,NULL);

    

	CTime t=CTime::GetCurrentTime();
	CString NowStr=t.Format("%Y%m%d%H%M%S");//��ʽ����ǰʱ��
	CString direct = t.Format("%Y-%m-%d");

	TCHAR FileName2[1000];
	wsprintf(FileName2,TEXT("%s\\%s"),path,direct);
	::CreateDirectory(FileName2,NULL);   //��������Ŀ¼

	TCHAR file[200];
	
	wsprintf(file,TEXT("%d-%s.zxh"),uNameId,NowStr.GetBuffer());
	

	wsprintf(path,TEXT("%s\\%s"),FileName2,file);	//д���ļ�

	m_pRecordMoudlePlat->SaveFileWithPassZip(path);
	//д���ļ�֮�����
	m_pRecordMoudlePlat->ClearAllMsg();
	m_pRecordMoudlePlat->ClearAllUserInfo();

}

void CAddRecordModule::SetUserInfo2Record(const UserItemStruct* pUserItem,const UserItemStruct* pMeUserInfo)
{
	if (m_bIsRecordAvailable == false)
	{
		return;
	}

	if (pUserItem == NULL || pMeUserInfo == NULL)
	{
		return;
	}
	RecordUserItemStruct RUserItem;
	CPRStructExchange exchange;
	exchange.ChaneUserItemPlatToReClient(&RUserItem,pUserItem);
	
	if ((pUserItem->GameUserInfo.dwUserID == pMeUserInfo->GameUserInfo.dwUserID) || 
		(pUserItem->GameUserInfo.bDeskStation == pMeUserInfo->GameUserInfo.bDeskStation && pUserItem->GameUserInfo.bDeskNO == pMeUserInfo->GameUserInfo.bDeskNO) )
	{
		//exchange.ChaneUserItemPlatToReClient(&RUserItem,pMeUserInfo);
		if (pUserItem->GameUserInfo.bDeskStation < MAX_PLAYER_COUNT)
		{
			m_pRecordMoudlePlat->AddMeDeskStation(pUserItem->GameUserInfo.bDeskStation);  //�����Լ�����λ��
		}
		
	}	
	
	m_pRecordMoudlePlat->AddUserInfo(&RUserItem);

}

void CAddRecordModule::AddMsgToRecord(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize)
{
	if (m_bIsRecordAvailable == false)
	{
		return;
	}
	if (m_pRecordMoudlePlat == NULL)
	{
		return;
	}
	//¼����Ϸ��Ϣ�ͳ�����Ϣyjj 090223
	if (pNetHead->bMainID == MDM_GM_GAME_NOTIFY || 
		(pNetHead->bMainID==MDM_GM_GAME_FRAME && (pNetHead->bAssistantID == ASS_GM_GAME_STATION || pNetHead->bAssistantID == ASS_GM_GAME_INFO)))
	{	
		//��¼����������Ϣ
		m_pRecordMoudlePlat->AddMsg2Record(pNetHead,sizeof(NetMessageHead),pNetData,uDataSize);		
	}
}
bool CAddRecordModule::GetUserGameState(const GameInfoStruct* pGameInfo ,NetMessageHead * pNetHead)
{
	if (pGameInfo == NULL || pGameInfo->pMeUserInfo == NULL || pNetHead == NULL)
	{
		return false;
	}
	
	if (pNetHead->bMainID!=MDM_GM_GAME_FRAME || pNetHead->bAssistantID != ASS_GM_GAME_STATION)
	{
		return false;
	}

	if (pGameInfo->bGameStation < 20)
	{
		return false;
	}
	if (pGameInfo->bGameStation == 23) 
	{
		return false;
	}
	return true;

}
