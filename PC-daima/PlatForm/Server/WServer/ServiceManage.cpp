#include "StdAfx.h"
#include <SYS/Stat.h>
///#include "ServiceSet.h"
#include "ServiceManage.h"
#include "MainFrm.h"
#include "MD5.h"
#include "yxyDES.h"
#include "resource.h"

#include"../Common/CommonUse.h"



//���캯��
CServiceManage::CServiceManage(void)// : m_ClientSocket(this)
{
	m_szError[0]=0;
	m_pIMessage=NULL;

	tinyxml2::XMLDocument doc;
	if (tinyxml2::XMLError::XML_SUCCESS != doc.LoadFile("HNGameLocal.xml"))
	{
		AfxMessageBox("Load HNGameLocal.xml Error-2",0);
		m_ServiceName	= "HNGame";
		m_sServerIP		= "127.0.0.1";	//������IP
		m_sAccount		= "sa";			//�˻�
		m_sPassword		= "sa";			//����
		m_szDatabase	= "hn2.0";		//���ݿ���
		m_nPort			= 1433;			//���ݿ�˿�
		m_sDetectTable	= TEXT("");		//��¼�ı���-(����û��)
		return;
	}

	tinyxml2::XMLElement* element1 = doc.FirstChildElement("SQLSERVER");
	if (NULL == element1)
	{
		AfxMessageBox("Load HNGameLocal.xml Error-2-1",0);
		return;
	}
	for (const tinyxml2::XMLElement* xml_SqlServer = element1->FirstChildElement(); xml_SqlServer; xml_SqlServer = xml_SqlServer->NextSiblingElement()) 
	{
		//���ݿ�IP��ַ
		if (!strcmp(xml_SqlServer->Value(), "DBSERVER")) 
		{
			m_sServerIP = xml_SqlServer->Attribute("key");
		}
		else if (!strcmp(xml_SqlServer->Value(), "DBPORT")) 
		{
			//�˿�
			CString sPort = xml_SqlServer->Attribute("key");
			m_nPort = _ttoi(sPort);
		}
		else if (!strcmp(xml_SqlServer->Value(), "DATABASE")) 
		{
			//���ݿ���
			m_szDatabase = xml_SqlServer->Attribute("key");
		}

		else if (!strcmp(xml_SqlServer->Value(), "DBACCOUNT")) 
		{
			//���ݿ��¼�ʺ�
			m_sAccount = xml_SqlServer->Attribute("key");
		}
		else if (!strcmp(xml_SqlServer->Value(), "DBPASSWORD")) 
		{
			//���ݿ��¼����
			m_sPassword = xml_SqlServer->Attribute("key");
		}
	}
	m_sDetectTable=TEXT("");


	element1 = doc.FirstChildElement("SERVERSET");
	if (NULL == element1)
	{
		AfxMessageBox("Load HNGameLocal.xml Error-2-2",0);
		return;
	}
	for (const tinyxml2::XMLElement* xml_SqlServer = element1->FirstChildElement(); xml_SqlServer; xml_SqlServer = xml_SqlServer->NextSiblingElement()) 
	{
		//���ݿ�IP��ַ
		if (!strcmp(xml_SqlServer->Value(), "ServiceName")) 
		{
			m_ServiceName = xml_SqlServer->Attribute("key");
		}
	}
}

/********************************************************************************************************/

//DLL �ӿں�������
typedef IModuleManageService * (CreateServiceInterface)(UINT uVer);
typedef BOOL (GetServiceInfo)(ServerDllInfoStruct * pServiceInfo, UINT uVer);




//��½ϵͳ
bool CServiceManage::LogonSystem(const TCHAR * szUserName, const TCHAR * szScrPass)
{
	return AfxGetMainWnd()->PostMessage(WM_COMMAND,IDM_GET_ROOM_LIST,0);
}

/********************************************************************************************************/

void CServiceManage::StartAllGames(CListCtrl * pListCtrl)
{
	for(int i=0;i<m_ComRoomInfo.GetSize();i++)
	{
	   SC_GameRoomInitStruct * p=(SC_GameRoomInitStruct *)m_ComRoomInfo.GetAt(i);
	   if(!p)continue;

       // PengJiLin, 2011-4-2, ָ����Щ��Ϸ�ǿ��õ�
       if(FALSE == m_GameSelecter.GameIsUsable(p->ServiceInfo.uNameID))
       {
           p->hDllInstance = NULL;
           p->hProcessHandle = NULL;
           memset(&(p->InitInfo), 0, sizeof(p->InitInfo));
           continue;
       }

	#ifdef BZ_LICENSE
		if(coreGetGameLicense(p->ServiceInfo.uNameID)==p->ServiceInfo.uNameID)
	#else
		if (true)
	#endif // BZ_LICENSE
	   {
	   //���ظ�������õ������ӿں�����ַ
	   if(!bGetServiceInfo(p))
	   {
		   CString strMessage;
		   strMessage.Format(TEXT("�����Ӧ�Ŀ�%s�����ڣ�%s"),p->ServiceInfo.szDLLFileName,g_Service.GetLastErrorMsg());
		   if (m_pIMessage!=NULL) m_pIMessage->ShowMessage(strMessage);//������Ϣ��ȡ���"));
		   //AfxMessageBox(strMessage,MB_ICONSTOP);
		   continue;
	   }
	   if(!StartGameRoom(p))continue;
	   }
	   else
	   {
		   CString s=p->ServiceInfo.szGameName;
		   if(s.Left(7)!="δ��֤_")
		   {
			   s="δ��֤_"+s;
			   if(s.GetLength()>60)
				   s=s.Left(60);
		   }	
		   strcpy(p->ServiceInfo.szGameName,s);
	   }
	}
	//UpdateRoomListInfo(pListCtrl);
	if (m_pIMessage!=NULL) m_pIMessage->ShowMessage(TEXT("���������������ʵ���������!"));
}


//������Ϸ����
bool CServiceManage::bGetServiceInfo(SC_GameRoomInitStruct * pComRoomInfo)
{
	////ע������////
	//bool bCheck = false;
	//bCheck = CheckLicense();
	//if(!bCheck)
	//{
	//	return false;
	//}

	//AfxMessageBox("GetServiceInfo!");

	try
	{
		if ((pComRoomInfo->hDllInstance!=NULL)||(pComRoomInfo->pIManageService!=NULL)) return true;

		#ifdef BZ_LICENSE
			if(coreGetGameLicense(pComRoomInfo->ServiceInfo.uNameID)!=pComRoomInfo->ServiceInfo.uNameID)
		#else
			if (false)
		#endif // BZ_LICENSE
		{
			CString s=pComRoomInfo->ServiceInfo.szGameName;
			if(s.Left(7)!="δ��֤_")
			{
				s="δ��֤_"+s;
				if(s.GetLength()>60)
					s=s.Left(60);
			}	
			strcpy(pComRoomInfo->ServiceInfo.szGameName,s);		
			return false;
		}
		//�ж��ļ�
		struct stat FileStat;
		if (stat(pComRoomInfo->ServiceInfo.szDLLFileName,&FileStat)!=0) 
			return false;
			//throw TEXT("���������");

		//�������
		pComRoomInfo->hDllInstance=AfxLoadLibrary(pComRoomInfo->ServiceInfo.szDLLFileName);
		int _err = GetLastError();
		if (pComRoomInfo->hDllInstance==NULL) 
		{
			CString cs;
			cs.Format("chs [Server] ����Dllʧ�� Code:%d",_err);
			OutputDebugString(cs);
			return false;//throw TEXT("���װ��ʧ��");
		}

		//��ȡ����ӿ�
		CreateServiceInterface * pCreateServiceInterface=(CreateServiceInterface *)GetProcAddress(pComRoomInfo->hDllInstance,TEXT("CreateServiceInterface"));
		if (pCreateServiceInterface==NULL) 
			return false;//throw TEXT("�Ƿ����");
		pComRoomInfo->pIManageService=pCreateServiceInterface(DEV_LIB_VER);
		if (pComRoomInfo->pIManageService==NULL)
			return false;//throw TEXT("�������ӿڻ�ȡʧ�ܣ���������Դ����");


		GetServiceInfo * pGetServiceInfo=(GetServiceInfo *)GetProcAddress(pComRoomInfo->hDllInstance,TEXT("GetServiceInfo"));
		if (pGetServiceInfo==NULL) 
			return false;//throw TEXT("�Ƿ����");

        // PengJiLin, 2011-4-2, ָ����Щ��Ϸ�ǿ��õ�
        ServerDllInfoStruct ServiceDllInfo;
        if(FALSE == pGetServiceInfo(&ServiceDllInfo,DEV_LIB_VER)) return false;
        if(FALSE == m_GameSelecter.GameIsUsable(ServiceDllInfo.uNameID)) return false;

		//Ч�����
		///ServerDllInfoStruct ServiceDllInfo;
		//ServerDllInfoStruct * temp;
		//if (pGetServiceInfo(temp,DEV_LIB_VER)==FALSE) throw TEXT("��ȡ�����Ϣʧ��");


	}
	catch (...)
	{
		TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
		return false;
	}

	return true;
}

//������Ϸ����
bool CServiceManage::StartGameRoom(SC_GameRoomInitStruct * pComRoomInfo)
{
	////ע������////
	//bool bCheck = false;
	//bCheck = CheckLicense();
	//if(!bCheck)
	//{
	//	return false;
	//}

	try
	{
	
		UINT errCode=0;
		//�������
		if (pComRoomInfo->pIManageService->InitService(&pComRoomInfo->InitInfo)==false) throw TEXT("�����ʼ������");
		if (pComRoomInfo->pIManageService->StartService(errCode)==false) throw TEXT("�����������");
		//pListCtrl->setSetItemText(pListCtrl->,3,TEXT("����"));


		return true;
	}
	catch (TCHAR * szError) { lstrcpy(m_szError,szError); TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);}
	catch (CAFCException * pException)
	{ TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
		pException->GetErrorMessage(m_szError,sizeof(m_szError));
		pException->Delete();	
	}
	catch (...)	{ lstrcpy(m_szError,TEXT("����δ֪�쳣����")); TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);}

	//������Դ
	if (pComRoomInfo->pIManageService!=NULL)
	{
		pComRoomInfo->pIManageService->StoptService();
		pComRoomInfo->pIManageService->UnInitService();
		pComRoomInfo->pIManageService->DeleteService();
		pComRoomInfo->pIManageService=NULL;
	}
	if (pComRoomInfo->hDllInstance!=NULL)
	{
		AfxFreeLibrary(pComRoomInfo->hDllInstance);
		pComRoomInfo->hDllInstance=NULL;
	}

	return false;
}

//���·����б�,����ʱ����,������������Ϸ
bool CServiceManage::UpdateServiceInfo(CListCtrl * pListCtrl)
{
	//�����ݿ�õ�������Ϣ
	GetRoomListInfo();

	//���ظ�������õ������ӿں�����ַ
	//for(int i = 0;i<=m_ComRoomInfo.GetUpperBound();i++)
	//{
	//	SC_GameRoomInitStruct * p=(SC_GameRoomInitStruct *)m_ComRoomInfo.GetAt(i);
	//	if(!bGetServiceInfo(p))continue;
	//}
	
	//���ýӿں�����������Ϸ
    StartAllGames(pListCtrl);
	//�������з����б�
	UpdateRoomListInfo(pListCtrl);
	return false;
}

//���캯��
CServiceInfo::CServiceInfo(void)
{
	m_uLogonTimes=0;
	m_uModelDlgCount=0;
	m_uSystemState=STS_NO_LOGON;
	memset(m_szName,0,sizeof(m_szName));
	memset(m_szMD5Pass,0,sizeof(m_szMD5Pass));
	memset(m_szServiceIP,0,sizeof(m_szServiceIP));
	memset(m_szServerGUID,0,sizeof(m_szServerGUID));
	memset(m_szSQLName,0,sizeof(m_szSQLName));
	memset(m_szSQLPass,0,sizeof(m_szSQLPass));
	memset(m_szSQLAddr,0,sizeof(m_szSQLAddr));
	memset(m_szLogonAddr,0,sizeof(m_szLogonAddr));

}

//��������
CServiceInfo::~CServiceInfo(void)
{
	SaveData();
}

//��ʼ������
bool CServiceInfo::LoadData()
{
	CString strBuffer;

	//��ȡ��½����
	strBuffer=AfxGetApp()->GetProfileString(TEXT("ServerInfo"),TEXT("Name"),TEXT("Administrator"));
	if (strBuffer.GetLength()>20) strBuffer.GetBufferSetLength(20);
	lstrcpy(m_szName,strBuffer);

	//��ȡ��½��ַ
	strBuffer=AfxGetApp()->GetProfileString(TEXT("ServerInfo"),TEXT("LogonAddr"),TEXT("127.0.0.1"));
	if (strBuffer.GetLength()>(sizeof(m_szLogonAddr)-1)) strBuffer.GetBufferSetLength((sizeof(m_szLogonAddr)-1));
	lstrcpy(m_szLogonAddr,strBuffer);

	//��ȡ GUID
	strBuffer=AfxGetApp()->GetProfileString(TEXT("ServerInfo"),TEXT("GUID"));
	if (strBuffer.GetLength()>36) strBuffer.GetBufferSetLength(36);
	lstrcpy(m_szServerGUID,strBuffer);

	return true;
}

//��������
bool CServiceInfo::SaveData()
{
	if (m_szName[0]!=0) AfxGetApp()->WriteProfileString(TEXT("ServerInfo"),TEXT("Name"),m_szName);
	if (m_szServerGUID[0]!=0) AfxGetApp()->WriteProfileString(TEXT("ServerInfo"),TEXT("GUID"),m_szServerGUID);
	if (m_szLogonAddr[0]!=0) AfxGetApp()->WriteProfileString(TEXT("ServerInfo"),TEXT("LogonAddr"),m_szLogonAddr);
	return true;
}

//�Ƿ��½ϵͳ
bool CServiceInfo::IsLogonSystem()
{
	bool bLogon=((m_uSystemState==STS_SYSTEM_LOCK)||(m_uSystemState==STS_LOGON_FINISH));
	return bLogon;
}

//�Ƿ�����ϵͳ
bool CServiceInfo::IsLockSystem()
{
	bool bLock=(m_uSystemState==STS_SYSTEM_LOCK);
	return bLock;
}

//��ȡ��½����
UINT CServiceInfo::GetLogonTimes() 
{ 
	return m_uLogonTimes; 
}

/********************************************************************************************************/


//��������
CServiceManage::~CServiceManage(void)
{
	//������Դ
	for (INT_PTR i=0;i<m_ServiceInfo.GetCount();i++)
	{
		SC_ServiceInfoStruct * pServiceInfo=(SC_ServiceInfoStruct *)(SC_ServiceInfoStruct *)m_ServiceInfo.GetAt(i);
		if (pServiceInfo!=NULL)
		{
			delete pServiceInfo;
			m_ServiceInfo.SetAt(i,NULL);
		}
	}
	for (INT_PTR i=0;i<m_ComRoomInfo.GetCount();i++)
	{
		SC_GameRoomInitStruct * pComRoomInfo=(SC_GameRoomInitStruct *)m_ComRoomInfo.GetAt(i);
		if (pComRoomInfo!=NULL)
		{
			if (pComRoomInfo->pIManageService!=NULL)
			{
				pComRoomInfo->pIManageService->StoptService();
				pComRoomInfo->pIManageService->UnInitService();
				pComRoomInfo->pIManageService->DeleteService();
				pComRoomInfo->pIManageService=NULL;

				ClearRoomTWRecode(pComRoomInfo->InitInfo.uRoomID);
			}
			if (pComRoomInfo->hDllInstance!=NULL) 
			{
				AfxFreeLibrary(pComRoomInfo->hDllInstance);
				pComRoomInfo->hDllInstance=NULL;
			}
			delete pComRoomInfo;
			m_ComRoomInfo.SetAt(i,NULL);
		}
	}

	return;
}

//������Ϣ�ӿ�
bool CServiceManage::SetMessageInterface(IMessageShow * pIMessage)
{
	m_pIMessage=pIMessage; 
	return true;
}
//��������б�
bool CServiceManage::UpdateComDLLList(CListCtrl * pListCtrl)
{
	
	//HANDLE hDatabase=sqlAddConnection("BZGameLocal.BCF");
	HANDLE hDatabase=sqlAddConnection(m_sServerIP,m_sAccount,m_sPassword,m_szDatabase,m_nPort);
	if(hDatabase<(HANDLE)0x1000)
	{
		
		return false;
	}

	HANDLE hRecord=sqlSPSetName(hDatabase,"SP_GetGameServerList",true);
	if(hRecord<(HANDLE)0x1000)
	{
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
		return false;
	}

	sqlSPExec(hDatabase,hRecord,true);
	//д������ǰӦ��ռ�¼
	pListCtrl->DeleteAllItems();
	m_ServiceInfo.RemoveAll();

	//��ȡ����
	TCHAR szBuffer[50];

	while(!sqlEndOfFile(hDatabase,hRecord))
	{
		//�������
		SC_ServiceInfoStruct * pServiceInfo=new SC_ServiceInfoStruct;
		memset(pServiceInfo,0,sizeof(SC_ServiceInfoStruct));
		m_ServiceInfo.Add(pServiceInfo);

		//��ȡ����
		sqlGetValue(hDatabase,hRecord,TEXT("ServerInfoID"),pServiceInfo->uServiceID);
		sqlGetValue(hDatabase,hRecord,TEXT("NameID"),pServiceInfo->ServiceInfo.uNameID);
		sqlGetValue(hDatabase,hRecord,TEXT("DeskPeople"),pServiceInfo->ServiceInfo.uDeskPeople);
		sqlGetValue(hDatabase,hRecord,TEXT("SupportType"),pServiceInfo->ServiceInfo.uSupportType);
		sqlGetValue(hDatabase,hRecord,TEXT("ServiceVer"),pServiceInfo->ServiceInfo.uServiceVer);
		sqlGetValue(hDatabase,hRecord,TEXT("GameName"),pServiceInfo->ServiceInfo.szGameName,sizeof(pServiceInfo->ServiceInfo.szGameName));
		sqlGetValue(hDatabase,hRecord,TEXT("GameTable"),pServiceInfo->ServiceInfo.szGameTable,sizeof(pServiceInfo->ServiceInfo.szGameTable));
		sqlGetValue(hDatabase,hRecord,TEXT("DLLFileName"),pServiceInfo->ServiceInfo.szDLLFileName,sizeof(pServiceInfo->ServiceInfo.szDLLFileName));
		//sqlGetValue(hDatabase,hRecord,TEXT("Writer"),pServiceInfo->ServiceInfo.szWriter,sizeof(pServiceInfo->ServiceInfo.szWriter));
		//sqlGetValue(hDatabase,hRecord,TEXT("DllNote"),pServiceInfo->ServiceInfo.szDllNote,sizeof(pServiceInfo->ServiceInfo.szDllNote));

        // PengJiLin, 2011-4-2, ָ����Щ��Ϸ�ǿ��õ�
        if(FALSE == m_GameSelecter.GameIsUsable(pServiceInfo->ServiceInfo.uNameID))
        {
            memset(pServiceInfo,0,sizeof(SC_ServiceInfoStruct));
            sqlMoveNext(hDatabase,hRecord);
            continue;
        }

		//д������
		struct stat FileStat;
		int iItem=pListCtrl->InsertItem(pListCtrl->GetItemCount(),ltoa(pServiceInfo->uServiceID,szBuffer,10));
		pListCtrl->SetItem(iItem,1,1,pServiceInfo->ServiceInfo.szGameName,0,0,0,0);
		if (stat(pServiceInfo->ServiceInfo.szDLLFileName,&FileStat)==0) 
		{
			pListCtrl->SetItem(iItem,2,1,TEXT("�Ѱ�װ"),0,0,0,0);
			pServiceInfo->uServiceStation = 1;
		}
		else 
		{
			pListCtrl->SetItem(iItem,2,1,TEXT("δ��װ"),0,0,0,0);
			pServiceInfo->uServiceStation = 0;
		}
		pListCtrl->SetItem(iItem,3,1,ltoa(pServiceInfo->ServiceInfo.uServiceVer,szBuffer,10),0,0,0,0);
		pListCtrl->SetItem(iItem,4,1,ltoa(pServiceInfo->ServiceInfo.uDeskPeople,szBuffer,10),0,0,0,0);
		pListCtrl->SetItem(iItem,5,1,pServiceInfo->ServiceInfo.szGameTable,0,0,0,0);
		pListCtrl->SetItem(iItem,6,1,pServiceInfo->ServiceInfo.szDLLFileName,0,0,0,0);
		//pListCtrl->SetItem(iItem,7,1,pServiceInfo->ServiceInfo.szDllNote,0,0,0,0);
		pListCtrl->SetItemData(iItem,(DWORD_PTR)pServiceInfo);
		//pList->SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE,LVS_EX_FULLROWSELECT,LVS_EX_FULLROWSELECT);
		//pList->InsertColumn(0,TEXT("��� ID"),LVCFMT_LEFT,60);
		//pList->InsertColumn(1,TEXT("�������"),LVCFMT_LEFT,100);
		//pList->InsertColumn(2,TEXT("���״̬"),LVCFMT_LEFT,80);
		//pList->InsertColumn(3,TEXT("�汾����"),LVCFMT_LEFT,60);
		//pList->InsertColumn(4,TEXT("��Ϸ����"),LVCFMT_LEFT,60);
		//pList->InsertColumn(5,TEXT("Ĭ����Ϣ��"),LVCFMT_LEFT,100);
		//pList->InsertColumn(6,TEXT("ģ������"),LVCFMT_LEFT,150);
		sqlMoveNext(hDatabase,hRecord);
	}

    // PengJiLin, 2011-4-21, �� TWLoginRecord ������ݣ�����������޷���½
    sqlCloseRecord(hDatabase, hRecord);
    sqlSPClose(hDatabase, hRecord);

    hRecord=sqlSPSetName(hDatabase,"SP_ClearTWLoginRecord");
    if(hRecord>=(HANDLE)0x1000)
    {
        sqlSPAddPara(hDatabase,hRecord,"@ServiceName",m_ServiceName,m_ServiceName.GetLength());
        sqlSPExec(hDatabase,hRecord);
        sqlCloseRecord(hDatabase, hRecord);
        sqlSPClose(hDatabase, hRecord);
    }

	sqlCloseConnection(hDatabase);

	return true;

}


//��ʼ������
bool CServiceManage::Init()
{
	return true;
}



//ֹͣ��Ϸ����
bool CServiceManage::StopGameRoom(SC_GameRoomInitStruct * pComRoomInfo)
{
	try
	{
		//�ж�״̬
		if ((pComRoomInfo->hDllInstance==NULL)||(pComRoomInfo->pIManageService==NULL)) return true;

		//ֹͣ���
		if (pComRoomInfo->pIManageService->StoptService()==false) throw TEXT("���ֹͣ����");
		if (pComRoomInfo->pIManageService->UnInitService()==false) throw TEXT("���ж�ش���");
		if (pComRoomInfo->pIManageService->DeleteService()==false) throw TEXT("����������");
		pComRoomInfo->pIManageService=NULL;

		//ж�����
		AfxFreeLibrary(pComRoomInfo->hDllInstance);
		pComRoomInfo->hDllInstance=NULL;

		ClearRoomTWRecode(pComRoomInfo->InitInfo.uRoomID);

		return true;
	}
	catch (TCHAR * szError) { lstrcpy(m_szError,szError);TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__); }
	catch (...)	{ lstrcpy(m_szError,TEXT("����δ֪�쳣����")); TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);}

	//������Դ
	if (pComRoomInfo->pIManageService!=NULL)
	{
		pComRoomInfo->pIManageService->StoptService();
		pComRoomInfo->pIManageService->UnInitService();
		pComRoomInfo->pIManageService->DeleteService();
		pComRoomInfo->pIManageService=NULL;

		ClearRoomTWRecode(pComRoomInfo->InitInfo.uRoomID);
	}
	if (pComRoomInfo->hDllInstance!=NULL)
	{
		AfxFreeLibrary(pComRoomInfo->hDllInstance);
		pComRoomInfo->hDllInstance=NULL;
	}

	return false;
}

/********************************************************************************************************/

//�����ȡ��Ϣ
bool CServiceManage::OnSocketReadEvent(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize, CTCPClientSocket * pClientSocket)
{
	switch (pNetHead->bMainID)
	{
	case MDM_CONNECT:		//������Ϣ
		{
			switch (pNetHead->bAssistantID)
			{
			case ASS_NET_TEST:			//������
				{
					if (uDataSize!=0) return false;
					pClientSocket->SendData(MDM_CONNECT,ASS_NET_TEST,0);
					return true;
				}
			case ASS_CONNECT_SUCCESS:	//���ӳɹ�
				{
					MSG_S_ConnectSuccess * pVerInfo=(MSG_S_ConnectSuccess *)pNetData;

					//�汾Ч��
					if (GAME_MAX_VER<pVerInfo->bLessVer) 
					{
						if (m_pIMessage!=NULL) m_pIMessage->ShowMessage(TEXT("��Ϸ�������汾̫���ˣ��޷�����ʹ��..."));
						pClientSocket->CloseSocket(false);
						return false;
					}

					//���͵�½��Ϣ
					MSG_SL_S_LogonByNameInfo MSGLogonInfo;
					lstrcpy(MSGLogonInfo.szName,m_Info.m_szName);
					lstrcpy(MSGLogonInfo.szMD5Pass,m_Info.m_szMD5Pass);
					lstrcpy(MSGLogonInfo.szServerGUID,m_Info.m_szServerGUID);
					pClientSocket->SendData(&MSGLogonInfo,sizeof(MSGLogonInfo),MDM_SL_SERVICE,ASS_SL_LOGON_BY_NAME,0);

					return true;
				}
			}
			return false;
		}
	case MDM_SL_SERVICE:	//�����½����
		{
			switch (pNetHead->bAssistantID)
			{
			case ASS_SL_LOGON_SUCCESS:	//��½�ɹ�
				{
					//Ч������
					if (uDataSize!=sizeof(MSG_SL_R_ConnectInfo)) return false;
					MSG_SL_R_ConnectInfo * pConnectInfo=(MSG_SL_R_ConnectInfo *)pNetData;

					//��������
					pClientSocket->CloseSocket(false);
					m_Info.m_uLogonTimes++;
					m_Info.m_uSystemState=STS_LOGON_FINISH;
					lstrcpy(m_Info.m_szSQLName,pConnectInfo->szSQLName);
					lstrcpy(m_Info.m_szSQLPass,pConnectInfo->szSQLPass);
					lstrcpy(m_Info.m_szSQLAddr,pConnectInfo->szSQLAddr);
					lstrcpy(m_Info.m_szServiceIP,pConnectInfo->szServiceIP);
					if (m_pIMessage!=NULL) m_pIMessage->ShowMessage(TEXT("�û���ϢЧ��ɹ������ڶ�ȡ������Ϣ..."));
					AfxGetMainWnd()->PostMessage(WM_COMMAND,IDM_GET_ROOM_LIST,0);

					return true;
				}
			case ASS_SL_LOGON_ERROR:	//��½ʧ��
				{
					//Ч������
					if (uDataSize!=0) return false;

					//��������
					CString strMessage=TEXT("��½����δ֪��������ϵͳ����...");
					switch (pNetHead->bHandleCode)
					{
					case ERR_SL_GUID_ERROR: 
						{  
							strMessage=TEXT("ϵͳ��Ȩ�Ŵ��󣬵�½ʧ��...");
							break;	
						}
					case ERR_SL_LOGON_IP_ERROR: 
						{ 
							strMessage=TEXT("����Ȩ�Ų����ڴ˷������ϵ�½����½ʧ��...");
							break;	
						}
					case ERR_SL_LOGON_NAME_ERROR: 
						{	
							strMessage=TEXT("��½���ִ��󣬵�½ʧ��...");
							break;	
						}
					case ERR_SL_LOGON_NAME_LIMIT: 
						{	
							strMessage=TEXT("��½���Ѿ������ã���½ʧ��...");
							break;	
						}
					case ERR_SL_LOGON_PASS_ERROR: 
						{ 
							strMessage=TEXT("��½������󣬵�½ʧ��...");
							break; 
						}
					}
					
					//��ʾ������Ϣ
					pClientSocket->CloseSocket(false);
					m_Info.m_uSystemState=STS_NO_LOGON;
					if (m_pIMessage!=NULL) m_pIMessage->ShowMessage(strMessage);
					AfxGetMainWnd()->PostMessage(WM_COMMAND,IDM_LOGON_SYSTEM,0);

					return true;
				}
			}
			return false;
		}
	}
	return false;
}

//����������Ϣ
bool CServiceManage::OnSocketConnectEvent(UINT uErrorCode, CTCPClientSocket * pClientSocket)
{
	if (uErrorCode!=0)
	{
		if (m_Info.m_uSystemState==STS_LOGON_ING) m_Info.m_uSystemState=STS_NO_LOGON;
		if (m_pIMessage!=NULL) m_pIMessage->ShowMessage(TEXT("��½������û���������볢��������½������..."));
		AfxGetMainWnd()->PostMessage(WM_COMMAND,IDM_LOGON_SYSTEM,0);
	}
	return true;
}

//����ر���Ϣ
bool CServiceManage::OnSocketCloseEvent()
{
	if (m_Info.IsLogonSystem()==false)
	{
		m_Info.m_uSystemState=STS_NO_LOGON;
		if (m_pIMessage!=NULL) m_pIMessage->ShowMessage(TEXT("���ڵ�½��������æ�����Ժ��ٴε�½..."));
		AfxGetMainWnd()->PostMessage(WM_COMMAND,IDM_LOGON_SYSTEM,0);
	}
	return true;
}

//����һ�������¼��ServerDllInfo���У�ͬʱ���µ�����ӵ�m_ServiceInfo��
bool CServiceManage::SetupCom(CListCtrl * pListCtrl,SC_ServiceInfoStruct pServiceInfo)
{

	//HANDLE hDatabase=sqlAddConnection("BZGameLocal.BCF");
	HANDLE hDatabase=sqlAddConnection(m_sServerIP,m_sAccount,m_sPassword,m_szDatabase,m_nPort);
	if(hDatabase<(HANDLE)0x1000)
	{
		
		return false;
	}
	HANDLE hRecord=sqlSPSetName(hDatabase,"SP_AddGameServer",true);
	if(hRecord<(HANDLE)0x1000)
	{
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
		return false;
	}

	sqlSPAddPara(hDatabase,hRecord,"@ServerInfoID",pServiceInfo.uServiceID);
	sqlSPAddPara(hDatabase,hRecord,"@NameID",pServiceInfo.ServiceInfo.uNameID);
	sqlSPAddPara(hDatabase,hRecord,"@DeskPeople",pServiceInfo.ServiceInfo.uDeskPeople);
	sqlSPAddPara(hDatabase,hRecord,"@SuppoerType",pServiceInfo.ServiceInfo.uSupportType);
	sqlSPAddPara(hDatabase,hRecord,"@ServerVer",pServiceInfo.ServiceInfo.uServiceVer);
	sqlSPAddPara(hDatabase,hRecord,"@GameName",pServiceInfo.ServiceInfo.szGameName,sizeof(pServiceInfo.ServiceInfo.szGameName));
	sqlSPAddPara(hDatabase,hRecord,"@GameTable",pServiceInfo.ServiceInfo.szGameTable,sizeof(pServiceInfo.ServiceInfo.szGameTable));
	sqlSPAddPara(hDatabase,hRecord,"@DllFileName",pServiceInfo.ServiceInfo.szDLLFileName,sizeof(pServiceInfo.ServiceInfo.szDLLFileName));

	sqlSPExec(hDatabase,hRecord);

	int ret=sqlSPGetReturnValue(hDatabase,hRecord);
	sqlCloseConnection(hDatabase);

	if(ret==1)
	{
		if (m_pIMessage!=NULL) m_pIMessage->ShowMessage("�����½����������ServerInfoID��ͬ�����,��������д! :-) ");//AfxMessageBox("�����½����������ServerInfoID��ͬ�����,��������д! :-) ");
		return false;
	}

	m_ServiceInfo.Add(&pServiceInfo);//ͬʱ���µ�����ӵ�m_ServiceInfo��
	UpdateComDLLList(pListCtrl);
	return true;

}

////�޸�һ�������¼��ServerDllInfo����
bool CServiceManage::ModifCom(CListCtrl * pListCtrl,SC_ServiceInfoStruct * avantp,SC_ServiceInfoStruct pServiceInfo)
{
	//HANDLE hDatabase=sqlAddConnection("BZGameLocal.BCF");
	HANDLE hDatabase=sqlAddConnection(m_sServerIP,m_sAccount,m_sPassword,m_szDatabase,m_nPort);
	if(hDatabase<(HANDLE)0x1000)
		return false;
	HANDLE hRecord=sqlSPSetName(hDatabase,"SP_EditGameServer",true);
	if(hRecord<(HANDLE)0x1000)
	{
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
		return false;
	}


	sqlSPAddPara(hDatabase,hRecord,"@ServerInfoID",pServiceInfo.uServiceID);
	sqlSPAddPara(hDatabase,hRecord,"@NameID",pServiceInfo.ServiceInfo.uNameID);
	sqlSPAddPara(hDatabase,hRecord,"@DeskPeople",pServiceInfo.ServiceInfo.uDeskPeople);
	sqlSPAddPara(hDatabase,hRecord,"@SuppoerType",pServiceInfo.ServiceInfo.uSupportType);
	sqlSPAddPara(hDatabase,hRecord,"@ServerVer",pServiceInfo.ServiceInfo.uServiceVer);
	sqlSPAddPara(hDatabase,hRecord,"@GameName",pServiceInfo.ServiceInfo.szGameName,sizeof(pServiceInfo.ServiceInfo.szGameName));
	sqlSPAddPara(hDatabase,hRecord,"@GameTable",pServiceInfo.ServiceInfo.szGameTable,sizeof(pServiceInfo.ServiceInfo.szGameTable));
	sqlSPAddPara(hDatabase,hRecord,"@DllFileName",pServiceInfo.ServiceInfo.szDLLFileName,sizeof(pServiceInfo.ServiceInfo.szDLLFileName));

	sqlSPExec(hDatabase,hRecord);

	int ret=sqlSPGetReturnValue(hDatabase,hRecord);
	sqlCloseConnection(hDatabase);
	//ʹ���ظ�ID
	if (ret==1)
	{
		if (m_pIMessage!=NULL) m_pIMessage->ShowMessage("ServerDllInfo �����޴�ServerInfoID��ͬ�����,��ˢ�����! ");
		//AfxMessageBox("ServerDllInfo �����޴�ServerInfoID��ͬ�����,��ˢ�����! ");
		return false;
	}

	for(int i=0;i<= m_ServiceInfo.GetUpperBound();i++)
	{
		SC_ServiceInfoStruct *p;
		p = (SC_ServiceInfoStruct *) m_ServiceInfo.GetAt(i);
		if(p->uServiceID==pServiceInfo.uServiceID)
		{
			m_ServiceInfo.RemoveAt(i);//ɾ���ɵļ�¼(Ҫô?)
			break;
		}
	}
	m_ServiceInfo.Add(&pServiceInfo);//ͬʱ���µ�����ӵ�m_ServiceInfo��
	UpdateComDLLList(pListCtrl);
	return true;

}

// �����µ�DLL�⵽��װĿ¼�����ڸ��ºͰ�װ�µ����
bool CServiceManage::CopyNewCom(SC_ServiceInfoStruct* pServiceInfo)
{
	if(AfxMessageBox("�����µĶ�̬���ļ���WLocalService.exe���ڵ�Ŀ¼��Ȼ���ok���Զ�������Ӧ�ķ��䡣",IDOK)==IDOK)
		return true;
	return false;
}

//�Ƴ�ȫ������б��m_ServiceInfo,ɾ�����ݿ�ServerDLLInfo��ļ�¼
bool CServiceManage::RemoveDLLList(CListCtrl * pListCtrl)
{
	if(!m_ServiceInfo.IsEmpty())//�Ƿ��м�¼
		return true;
	while(!m_ServiceInfo.IsEmpty())
	{
		RemoveDLLCom(pListCtrl,(SC_ServiceInfoStruct *)m_ServiceInfo.GetAt(m_ServiceInfo.GetUpperBound()));
	}
	//UpdateComDLLList(pListCtrl);
	return true;
}

//�Ƴ�ָ������б��m_ServiceInfo��ɾ�������ݿ�ServerDLLInfo��ļ�¼
bool CServiceManage::RemoveDLLCom(CListCtrl *pListCtrl,SC_ServiceInfoStruct *pServiceInfo)
{
	
	if(m_ServiceInfo.IsEmpty())//�Ƿ��м�¼
	{
		lstrcpy(m_szError,TEXT("����б��¼����û���κ����"));
		return false;
	}
	//����Ҫɾ���ļ�¼
	for(int i=0;i<= m_ServiceInfo.GetUpperBound();i++)
	{
		SC_ServiceInfoStruct* ptem;
		ptem = (SC_ServiceInfoStruct *)(m_ServiceInfo.GetAt(i)); 
		
		//�ҵ���¼
		if(ptem->uServiceID == pServiceInfo->uServiceID)
		{

			//HANDLE hDatabase=sqlAddConnection("BZGameLocal.bcf");
			HANDLE hDatabase=sqlAddConnection(m_sServerIP,m_sAccount,m_sPassword,m_szDatabase,m_nPort);
			if(hDatabase>(HANDLE)0x1000)
			{
				TCHAR szSQL[200];
				wsprintf(szSQL,TEXT("DELETE FROM TGameServerInfo WHERE ServerInfoID = %d"), pServiceInfo->uServiceID);
				sqlExec(hDatabase,szSQL);
			}
			m_ServiceInfo.RemoveAt(i);//ͬʱ�Ƴ������еļ�¼
				pListCtrl->DeleteItem(i);
			return true;
		}
	}
	//û�м�¼
	lstrcpy(m_szError,TEXT("�б������޴������¼"));
	return false;
}


// ɾ�����ݿⷿ����Ϣ 
bool CServiceManage::DeleteGameRoomInfo(SC_GameRoomInitStruct * pComRoomInfo)
{
	try
	{

		//HANDLE hDatabase=sqlAddConnection("BZGameLocal.bcf");
		HANDLE hDatabase=sqlAddConnection(m_sServerIP,m_sAccount,m_sPassword,m_szDatabase,m_nPort);
		if(hDatabase<(HANDLE)0x1000)
		{
			
			return false;
		}
		HANDLE hRecord=sqlSPSetName(hDatabase,"SP_EraseRoomInfo");
		if(hRecord<(HANDLE)0x1000)
		{
			sqlCloseRecord(hDatabase,hRecord);
			sqlSPClose(hDatabase,hRecord);
			return false;
		}

		sqlSPAddPara(hDatabase,hRecord,"@RoomID",pComRoomInfo->InitInfo.uRoomID);

		sqlSPExec(hDatabase,hRecord);

		sqlCloseConnection(hDatabase);

		SC_GameRoomInitStruct *p;
		for(int i = 0;i<=m_ComRoomInfo.GetUpperBound();i++)
		{
			p=(SC_GameRoomInitStruct *)m_ComRoomInfo.GetAt(i);
			if(p->uServiceID==pComRoomInfo->uServiceID && p->InitInfo.szGameRoomName==pComRoomInfo->InitInfo.szGameRoomName)
			{
				m_ComRoomInfo.RemoveAt(i);
				break;
			}
		}

		if (m_pIMessage!=NULL) m_pIMessage->ShowMessage(TEXT("ɾ���������ʵ����Ϣ��ɣ�"));
		return true;
	}
	catch (...) 
	{ TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
		if (m_pIMessage!=NULL) m_pIMessage->ShowMessage(TEXT("ɾ���������ʵ����Ϣ���������Ժ��ٴγ���..."));
	}
	return false;
}

///desc�����������Ϸ������Ϣ//W_0002.2
bool CServiceManage::GetRoomListInfo()
{
	////ע������////
	//bool bCheck = false;
	//bCheck = CheckLicense();
	//if(!bCheck)
	//{
	//	return false;
	//}

	//AfxMessageBox("GetRoomListInfo!");

	//HANDLE hDatabase=sqlAddConnection("BZGameLocal.BCF");
	HANDLE hDatabase=sqlAddConnection(m_sServerIP,m_sAccount,m_sPassword,m_szDatabase,m_nPort);
	if(hDatabase<(HANDLE)0x1000)
		return false;
	HANDLE hRecord=sqlSPSetName(hDatabase,"SP_GetRoomList");
	if(hRecord<(HANDLE)0x1000)
		return false;

	try
	{

		sqlSPAddPara(hDatabase,hRecord,"@ServiceName",m_ServiceName,m_ServiceName.GetLength());
		sqlSPExec(hDatabase,hRecord,true);
		while(!sqlEndOfFile(hDatabase,hRecord))
		{
			bool goOn=false,update=false;
			UINT ui=0,uID=0,uPort=0;//�޷���
			__int64 i64 = 0;
			//INT ui=0;//����
			//�������
			SC_GameRoomInitStruct * pGameRoomInitInfo=new SC_GameRoomInitStruct;
			memset(pGameRoomInitInfo,0,sizeof(SC_GameRoomInitStruct));

            // PengJiLin, 2011-4-2, ָ����Щ��Ϸ�ǿ��õ�
            sqlGetValue(hDatabase,hRecord,TEXT("NameID"),ui);
			pGameRoomInitInfo->InitInfo.iGameID = ui;
            if(FALSE == m_GameSelecter.GameIsUsable(ui))
            {
                sqlMoveNext(hDatabase,hRecord);
                delete pGameRoomInitInfo;
                continue;
            }

			//�Ѿ���ȡ���Ĳ���
			sqlGetValue(hDatabase,hRecord,TEXT("ServerInfoID"),uID);
			sqlGetValue(hDatabase,hRecord,TEXT("SocketPort"),uPort);
			for(int i=0;i<m_ComRoomInfo.GetCount();i++)
			{
				SC_GameRoomInitStruct * p;
				p = (SC_GameRoomInitStruct *)m_ComRoomInfo.GetAt(i);
				//�����ķ���
				if(p->uServiceID==uID&&p->InitInfo.uListenPort==uPort&&p->hDllInstance!=NULL&&p->pIManageService!=NULL)
				{

					goOn=true;
					break;
				}
				//ֹͣ�ķ���
				if(p->uServiceID==uID&&p->InitInfo.uListenPort==uPort&&p->hDllInstance==NULL&&p->pIManageService==NULL)
				{
					update=true;
					delete pGameRoomInitInfo;
					pGameRoomInitInfo=p;
					break;
				}
			}
			if(goOn)
			{
				//�ƶ���һ��
				sqlMoveNext(hDatabase,hRecord);
				continue;
			}
			if(!update)
				m_ComRoomInfo.Add(pGameRoomInitInfo);
			//��ȡ������Ϣ
			sqlGetValue(hDatabase,hRecord,TEXT("IDSort"),ui);
			pGameRoomInitInfo->uSortID=ui;
			sqlGetValue(hDatabase,hRecord,TEXT("KindID"),ui);
			pGameRoomInitInfo->uKindID=ui;
			sqlGetValue(hDatabase,hRecord,TEXT("EnableRoom"),pGameRoomInitInfo->bEnable);

			sqlGetValue(hDatabase,hRecord,TEXT("ServerInfoID"),ui);

			pGameRoomInitInfo->uServiceID=ui;////////////////
			//sqlGetValue(hDatabase,hRecord,TEXT("Note"),pGameRoomInitInfo->szRoomNote,sizeof(pGameRoomInitInfo->szRoomNote));
			//��ȡ�����Ϣ
			sqlGetValue(hDatabase,hRecord,TEXT("NameID"),ui);
			pGameRoomInitInfo->ServiceInfo.uNameID=ui;////////////
			sqlGetValue(hDatabase,hRecord,TEXT("DeskPeople"),ui);
			pGameRoomInitInfo->ServiceInfo.uDeskPeople=ui;
			sqlGetValue(hDatabase,hRecord,TEXT("SupportType"),ui);
			pGameRoomInitInfo->ServiceInfo.uSupportType=ui;
			sqlGetValue(hDatabase,hRecord,TEXT("ServiceVer"),ui);
			pGameRoomInitInfo->ServiceInfo.uServiceVer=ui;
			sqlGetValue(hDatabase,hRecord,TEXT("GameName"),pGameRoomInitInfo->ServiceInfo.szGameName,sizeof(pGameRoomInitInfo->ServiceInfo.szGameName));
			sqlGetValue(hDatabase,hRecord,TEXT("GameTable"),pGameRoomInitInfo->ServiceInfo.szGameTable,sizeof(pGameRoomInitInfo->ServiceInfo.szGameTable));
			sqlGetValue(hDatabase,hRecord,TEXT("DLLFileName"),pGameRoomInitInfo->ServiceInfo.szDLLFileName,sizeof(pGameRoomInitInfo->ServiceInfo.szDLLFileName));
			//sqlGetValue(hDatabase,hRecord,TEXT("Writer"),pGameRoomInitInfo->ServiceInfo.szWriter,sizeof(pGameRoomInitInfo->ServiceInfo.szWriter));
			//sqlGetValue(hDatabase,hRecord,TEXT("DllNote"),pGameRoomInitInfo->ServiceInfo.szDllNote,sizeof(pGameRoomInitInfo->ServiceInfo.szDllNote));

			//��ȡ������Ϣ
			pGameRoomInitInfo->InitInfo.uNameID=pGameRoomInitInfo->ServiceInfo.uNameID;
			sqlGetValue(hDatabase,hRecord,TEXT("RoomRule"),ui);
			pGameRoomInitInfo->InitInfo.dwRoomRule=ui;
			sqlGetValue(hDatabase,hRecord,TEXT("UserPower"),ui);
			pGameRoomInitInfo->InitInfo.dwUserPower=ui;
			sqlGetValue(hDatabase,hRecord,TEXT("GameTypeID"),ui);
			pGameRoomInitInfo->InitInfo.uComType=ui;
			sqlGetValue(hDatabase,hRecord,TEXT("BasePoint"),ui);
			pGameRoomInitInfo->InitInfo.uBasePoint=ui;
			sqlGetValue(hDatabase,hRecord,TEXT("LessPoint"),ui);
			pGameRoomInitInfo->InitInfo.uLessPoint=ui;
			sqlGetValue(hDatabase,hRecord,TEXT("MaxPoint"),ui);
			pGameRoomInitInfo->InitInfo.uMaxPoint=ui;
			sqlGetValue(hDatabase,hRecord,TEXT("MaxLimite"),ui);
			pGameRoomInitInfo->InitInfo.uMaxLimite=ui;
			sqlGetValue(hDatabase,hRecord,TEXT("RunPublish"),ui);
			pGameRoomInitInfo->InitInfo.uRunPublish=ui;				
			sqlGetValue(hDatabase,hRecord,TEXT("Tax"),ui);
			pGameRoomInitInfo->InitInfo.uTax=ui;
			sqlGetValue(hDatabase,hRecord,TEXT("SocketPort"),ui);
			pGameRoomInitInfo->InitInfo.uListenPort=ui;
			sqlGetValue(hDatabase,hRecord,TEXT("MaxPeople"),ui);
			pGameRoomInitInfo->InitInfo.uMaxPeople=ui;
			pGameRoomInitInfo->InitInfo.iSocketSecretKey = SECRET_KEY;
			/////////////////////////////////////////////////////////
			/////////Kylin 20090116 Vip��½����
			sqlGetValue(hDatabase,hRecord,TEXT("VipResever"),ui);
			pGameRoomInitInfo->InitInfo.uVipReseverCount=ui;
			/////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////
			//20081211 , Fred Huang  Start
			sqlGetValue(hDatabase,hRecord,TEXT("VirtualUser"),ui);
			pGameRoomInitInfo->InitInfo.uVirtualUser=ui;
			sqlGetValue(hDatabase,hRecord,TEXT("VirtualGameTime"),ui);
			pGameRoomInitInfo->InitInfo.uVirtualGameTime=ui;
			//20081211 , Fred Huang  Stop
			//////////////////////////////////////////////////////////////////////////

			//wushuqun 2009.6.5
			//�����Ϸ��ս��--begin
			sqlGetValue(hDatabase,hRecord,TEXT("BattleRoomID"),ui);
			pGameRoomInitInfo->InitInfo.uBattleRoomID = ui;
			sqlGetValue(hDatabase,hRecord,TEXT("BattleMatchTable"),pGameRoomInitInfo->InitInfo.szBattleGameTable,
				sizeof(pGameRoomInitInfo->InitInfo.szBattleGameTable));
			////////////////--end

			///< ���«�������Ƿ�VIP���䣨VIP�����������룩
			sqlGetValue(hDatabase,hRecord,TEXT("VIPRoom"),ui);
			pGameRoomInitInfo->InitInfo.bVIPRoom = (ui!=0);

			sqlGetValue(hDatabase,hRecord,TEXT("DeskCount"),ui);
			pGameRoomInitInfo->InitInfo.uDeskCount=ui;
			sqlGetValue(hDatabase,hRecord,TEXT("RoomID"),ui);
			pGameRoomInitInfo->InitInfo.uRoomID=ui;
			sqlGetValue(hDatabase,hRecord,TEXT("StopLogon"),ui);
			pGameRoomInitInfo->InitInfo.uStopLogon=0;
			sqlGetValue(hDatabase,hRecord,TEXT("RoomName"),pGameRoomInitInfo->InitInfo.szGameRoomName,sizeof(pGameRoomInitInfo->InitInfo.szGameRoomName));
			sqlGetValue(hDatabase,hRecord,TEXT("ServerIP"),m_Info.m_szServiceIP,sizeof(m_Info.m_szServiceIP));
			sqlGetValue(hDatabase,hRecord,TEXT("TableLock"),pGameRoomInitInfo->InitInfo.szLockTable,sizeof(pGameRoomInitInfo->InitInfo.szLockTable));
			//wushuqun 2009.6.5
			if (pGameRoomInitInfo->InitInfo.uBattleRoomID > 0)
			{
				memcpy(pGameRoomInitInfo->InitInfo.szGameTable,
					pGameRoomInitInfo->InitInfo.szBattleGameTable,
					sizeof(pGameRoomInitInfo->InitInfo.szBattleGameTable));
			}
			else
			{
				sqlGetValue(hDatabase,hRecord,TEXT("TableMatch"),pGameRoomInitInfo->InitInfo.szGameTable,sizeof(pGameRoomInitInfo->InitInfo.szGameTable));
			}
			////////////////////
			sqlGetValue(hDatabase,hRecord,TEXT("TableIPRule"),pGameRoomInitInfo->InitInfo.szIPRuleTable,sizeof(pGameRoomInitInfo->InitInfo.szIPRuleTable));
			sqlGetValue(hDatabase,hRecord,TEXT("TableUserNameRule"),pGameRoomInitInfo->InitInfo.szNameRuleTable,sizeof(pGameRoomInitInfo->InitInfo.szNameRuleTable));
			//sqlGetValue(hDatabase,hRecord,TEXT("CenterSQLIP"),pGameRoomInitInfo->InitInfo.szSQLIP,sizeof(pGameRoomInitInfo->InitInfo.szSQLIP));
			//sqlGetValue(hDatabase,hRecord,TEXT("LogonSQLIP"),pGameRoomInitInfo->InitInfo.szLogonSQLIP,sizeof(pGameRoomInitInfo->InitInfo.szLogonSQLIP));
			//sqlGetValue(hDatabase,hRecord,TEXT("NativaSQLIP"),pGameRoomInitInfo->InitInfo.szNativeSQLIP,sizeof(pGameRoomInitInfo->InitInfo.szNativeSQLIP));
			// ���Ӱټ������� add by wlr 20090714

			//{{ Add by lxl 2010-10-08 ��������
			sqlGetValue(hDatabase,hRecord,TEXT("RoomPassword"),pGameRoomInitInfo->InitInfo.szRoomPassWord,sizeof(pGameRoomInitInfo->InitInfo.szRoomPassWord));
			/// ���ǲ��ǰټ������͵���Ϸ
			char cKey[10];
			CString sPath=CBcfFile::GetAppPath();
			int iResult = 0;
			if (CBcfFile::IsFileExist(sPath + "SpecialRule.bcf"))
			{
				CBcfFile fsr( sPath + "SpecialRule.bcf");
				sprintf(cKey, "%d", pGameRoomInitInfo->ServiceInfo.uNameID);
				iResult = fsr.GetKeyVal (_T("BJLType"), cKey, 0);
			}
			
			if (iResult!=0)
			{
				pGameRoomInitInfo->InitInfo.uDeskType = DESK_TYPE_BJL;
			}
			else
			{
				pGameRoomInitInfo->InitInfo.uDeskType = DESK_TYPE_NORMAL;
			}
			//end of add by wlr 20090714



			//����rongqiufen20120106
			if (pGameRoomInitInfo->InitInfo.dwRoomRule & GRR_CONTEST || pGameRoomInitInfo->InitInfo.dwRoomRule & GRR_TIMINGCONTEST)
			{
				CTime _Now = CTime::GetCurrentTime();
				int nYear = 0, nMonth = 0, nDate = 0, nHour = 0, nMin = 0, nSec = 0, nss = 0;  
				CString temp;
			//	sqlGetValue(hDatabase, hRecord, TEXT("StartTime"), temp);
				if (temp != "")
				{
					sscanf(temp.GetBuffer(), TEXT("%d-%d-%d %d:%d:%d.%d"), &nYear, &nMonth, &nDate, &nHour, &nMin, &nSec, &nss);

					CTime _t(nYear, nMonth, nDate, nHour, nMin, nSec); 
					pGameRoomInitInfo->InitInfo.i64TimeStart = _t.GetTime();
				}
				else
				{
					pGameRoomInitInfo->InitInfo.i64TimeStart = 0;
				}
			//	sqlGetValue(hDatabase, hRecord, TEXT("EndTime"), temp);
				if (temp != "")
				{
					sscanf(temp.GetBuffer(), TEXT("%d-%d-%d %d:%d:%d.%d"), &nYear, &nMonth, &nDate, &nHour, &nMin, &nSec, &nss);

					CTime _t(nYear, nMonth, nDate, nHour, nMin, nSec); 
					pGameRoomInitInfo->InitInfo.i64TimeEnd = _t.GetTime();
				}
				else
				{
					pGameRoomInitInfo->InitInfo.i64TimeEnd = 0;
				}
				
				sqlGetValue(hDatabase,hRecord,TEXT("Chip"), pGameRoomInitInfo->InitInfo.i64Chip);
				sqlGetValue(hDatabase,hRecord,TEXT("LowChip"), pGameRoomInitInfo->InitInfo.i64LowChip);
				sqlGetValue(hDatabase,hRecord,TEXT("LowCount"), ui);
				pGameRoomInitInfo->InitInfo.iLowCount = ui; 
				sqlGetValue(hDatabase,hRecord,TEXT("ContestID"), ui);
				pGameRoomInitInfo->InitInfo.iContestID = ui; 
				sqlGetValue(hDatabase,hRecord,TEXT("Timeout"), ui);
				pGameRoomInitInfo->InitInfo.iTimeout = ui;
				sqlGetValue(hDatabase,hRecord,TEXT("LeastPeople"), ui);
				pGameRoomInitInfo->InitInfo.iLeasePeople = ui;
				sqlGetValue(hDatabase,hRecord,TEXT("UpPeople"), ui);
				pGameRoomInitInfo->InitInfo.iUpPeople = ui;
				pGameRoomInitInfo->InitInfo.uLessPoint = 0;
			}
			//���޷���ID��ʱ��
			sqlGetValue(hDatabase,hRecord,TEXT("tenancyID"), pGameRoomInitInfo->InitInfo.iLeaseID);
			if (pGameRoomInitInfo->InitInfo.iLeaseID != 0)
			{
				int nYear = 0, nMonth = 0, nDate = 0, nHour = 0, nMin = 0, nSec = 0, nss = 0;  
				CString temp;
				sqlGetValue(hDatabase, hRecord, TEXT("OpenRoomDate"), temp);
				if (temp != "")
				{
					sscanf(temp.GetBuffer(), TEXT("%d-%d-%d %d:%d:%d.%d"), &nYear, &nMonth, &nDate, &nHour, &nMin, &nSec, &nss);

					CTime _t(nYear, nMonth, nDate, nHour, nMin, nSec); 
					pGameRoomInitInfo->InitInfo.i64LeaseTimeStart = _t.GetTime();
				}
				else
				{
					pGameRoomInitInfo->InitInfo.i64LeaseTimeStart = 0;
				}
				int idays = 0;
				sqlGetValue(hDatabase,hRecord,TEXT("AppleyDays"),idays);
				pGameRoomInitInfo->InitInfo.i64LeaseTimeEnd = pGameRoomInitInfo->InitInfo.i64LeaseTimeStart + idays * 24 * 60 * 60;
			}

			//ÿ��ʱ���ͽ��
			sqlGetValue(hDatabase,hRecord,TEXT("SendTimeLength"), pGameRoomInitInfo->InitInfo.iTimeLength);
			sqlGetValue(hDatabase,hRecord,TEXT("SendCount"), pGameRoomInitInfo->InitInfo.iSendCount);

			sqlMoveNext(hDatabase,hRecord);
		}
		sqlCloseConnection(hDatabase);

		return true;
	}
	catch (...) 
	{ 
		TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
		if (m_pIMessage!=NULL) 
			m_pIMessage->ShowMessage(TEXT("�������ʵ����Ϣ��ȡ���������Ժ��ٴγ���..."));
	}

}

bool CServiceManage::UpdateRoomListInfo(CListCtrl * pListCtrl)
{
	////ע������////
	//bool bCheck = false;
	//bCheck = CheckLicense();
	//if(!bCheck)
	//{
	//	return false;
	//}

	SC_GameRoomInitStruct * pGameRoomInitInfo;
	//ȥ�����м�¼
	pListCtrl->DeleteAllItems();
	//��ȡ����
	TCHAR szBuffer[50];
	for(int i=0;i<=m_ComRoomInfo.GetUpperBound();i++)
	{
		pGameRoomInitInfo = (SC_GameRoomInitStruct *) m_ComRoomInfo.GetAt(i);
		int iItem=pListCtrl->InsertItem(pListCtrl->GetItemCount(),ltoa(pGameRoomInitInfo->InitInfo.uRoomID,szBuffer,10));
		pListCtrl->SetItem(iItem,1,1,pGameRoomInitInfo->InitInfo.szGameRoomName,0,0,0,0);
		pListCtrl->SetItem(iItem,2,1,pGameRoomInitInfo->ServiceInfo.szGameName,0,0,0,0);
		if(pGameRoomInitInfo->hDllInstance==NULL||pGameRoomInitInfo->pIManageService==NULL)
			pListCtrl->SetItem(iItem,3,1,TEXT("ֹͣ"),0,0,0,0);
		else 
			pListCtrl->SetItem(iItem,3,1,TEXT("����"),0,0,0,0);
		pListCtrl->SetItem(iItem,4,1,_ltoa(pGameRoomInitInfo->InitInfo.uComType,szBuffer,10),0,0,0,0);
		pListCtrl->SetItem(iItem,5,1,_ltoa(pGameRoomInitInfo->bEnable,szBuffer,10),0,0,0,0);
		pListCtrl->SetItem(iItem,6,1,m_Info.m_szServiceIP,0,0,0,0);
		pListCtrl->SetItem(iItem,7,1,ltoa(pGameRoomInitInfo->InitInfo.uListenPort,szBuffer,10),0,0,0,0);
		pListCtrl->SetItem(iItem,8,1,ltoa(pGameRoomInitInfo->InitInfo.uDeskCount,szBuffer,10),0,0,0,0);
		pListCtrl->SetItem(iItem,9,1,ltoa(0,szBuffer,10),0,0,0,0);
		pListCtrl->SetItem(iItem,10,1,ltoa(pGameRoomInitInfo->InitInfo.uMaxPeople,szBuffer,10),0,0,0,0);
		pListCtrl->SetItem(iItem,11,1,ltoa(pGameRoomInitInfo->InitInfo.uLessPoint,szBuffer,10),0,0,0,0);
		pListCtrl->SetItem(iItem,12,1,ltoa(pGameRoomInitInfo->InitInfo.uBasePoint,szBuffer,10),0,0,0,0);
		pListCtrl->SetItem(iItem,13,1,ltoa(pGameRoomInitInfo->InitInfo.uMaxLimite,szBuffer,10),0,0,0,0);
		pListCtrl->SetItem(iItem,14,1,ltoa(pGameRoomInitInfo->InitInfo.dwRoomRule,szBuffer,10),0,0,0,0);
		pListCtrl->SetItem(iItem,15,1,ltoa(pGameRoomInitInfo->InitInfo.dwUserPower,szBuffer,10),0,0,0,0);
		pListCtrl->SetItem(iItem,16,1,pGameRoomInitInfo->InitInfo.szSQLIP,0,0,0,0);
		pListCtrl->SetItem(iItem,17,1,pGameRoomInitInfo->InitInfo.szLogonSQLIP,0,0,0,0);
		pListCtrl->SetItem(iItem,18,1,pGameRoomInitInfo->InitInfo.szNativeSQLIP,0,0,0,0);
		pListCtrl->SetItem(iItem,19,1,ltoa(pGameRoomInitInfo->uKindID,szBuffer,10),0,0,0,0);
		pListCtrl->SetItem(iItem,20,1,ltoa(pGameRoomInitInfo->ServiceInfo.uNameID,szBuffer,10),0,0,0,0);
		pListCtrl->SetItem(iItem,22,1,pGameRoomInitInfo->InitInfo.szGameTable,0,0,0,0);
		pListCtrl->SetItem(iItem,23,1,pGameRoomInitInfo->InitInfo.szLockTable,0,0,0,0);
		pListCtrl->SetItem(iItem,24,1,pGameRoomInitInfo->InitInfo.szIPRuleTable,0,0,0,0);
		pListCtrl->SetItem(iItem,25,1,pGameRoomInitInfo->InitInfo.szNameRuleTable,0,0,0,0);
		pListCtrl->SetItem(iItem,26,1,ltoa(pGameRoomInitInfo->uSortID,szBuffer,10),0,0,0,0);
		pListCtrl->SetItem(iItem,27,1,ltoa(pGameRoomInitInfo->uServiceID,szBuffer,10),0,0,0,0);
		pListCtrl->SetItem(iItem,28,1,pGameRoomInitInfo->ServiceInfo.szDLLFileName,0,0,0,0);
		pListCtrl->SetItem(iItem,29,1,pGameRoomInitInfo->szRoomNote,0,0,0,0);
		pListCtrl->SetItem(iItem,30,1,ltoa(pGameRoomInitInfo->ServiceInfo.uDeskPeople,szBuffer,10),0,0,0,0);
		if(pGameRoomInitInfo->InitInfo.uStopLogon)
			pListCtrl->SetItem(iItem,31,1,"Yes",0,0,0,0);
		else pListCtrl->SetItem(iItem,31,1,"No",0,0,0,0);
		if(pGameRoomInitInfo->InitInfo.uComType==TY_MONEY_GAME)
			pListCtrl->SetItem(iItem,33,1,ltoa(pGameRoomInitInfo->InitInfo.uTax,szBuffer,10),0,0,0,0);
		else pListCtrl->SetItem(iItem,33,1,"��",0,0,0,0);
		pListCtrl->SetItem(iItem,34,1,ltoa(pGameRoomInitInfo->InitInfo.uRunPublish,szBuffer,10),0,0,0,0);
		pListCtrl->SetItemData(iItem,(DWORD_PTR)pGameRoomInitInfo);		
	}
	return true;
}

void CServiceManage::CountOnLinePeople(CListCtrl * everyDLL, CListCtrl * everyRoom)
{
	static int licCount=0;
	if(++licCount>=10)
		licCount=0;
	try
	{
		//HANDLE hDatabase=sqlAddConnection("BZGameLocal.BCF");
		HANDLE hDatabase=sqlAddConnection(m_sServerIP,m_sAccount,m_sPassword,m_szDatabase,m_nPort);
		if(hDatabase<(HANDLE)0x1000)
			return;
		HANDLE hRecord=sqlSPSetName(hDatabase,"SP_GetRoomList");
		if(hRecord<(HANDLE)0x1000)
			return;


		sqlSPSetName(hDatabase,"SP_GetOnlinePeopleCount");
		sqlSPAddPara(hDatabase,hRecord,"@ServiceName",m_ServiceName,sizeof(m_ServiceName));
		sqlSPExec(hDatabase,hRecord);

		TCHAR szBuffer[50];
		while(!sqlEndOfFile(hDatabase,hRecord))
		{
			UINT uServerInfoID=0,uSocketPort=0,uOnLineCount=0;//�޷���

			//��ȡServerInfoID��Ϣ
			sqlGetValue(hDatabase,hRecord,TEXT("ServerInfoID"),uServerInfoID);
			//��ȡsocketPort
			sqlGetValue(hDatabase,hRecord,TEXT("SocketPort"),uSocketPort);
			for(int i=0;i<m_ComRoomInfo.GetCount();i++)
			{
				SC_GameRoomInitStruct * p;
				p = (SC_GameRoomInitStruct *)m_ComRoomInfo.GetAt(i);
				if(uServerInfoID==p->uServiceID&&uSocketPort==p->InitInfo.uListenPort)
				{
					sqlGetValue(hDatabase,hRecord,TEXT("OnLineCount"),uOnLineCount);
					everyRoom->SetItem(i,9,1,ltoa(uOnLineCount,szBuffer,10),0,0,0,0);
				}
			}
			sqlMoveNext(hDatabase,hRecord);
		}
		sqlCloseConnection(hDatabase);

		return;
	}
	catch (...) 
	{ 
		TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
	}
	return ;
}


CString CServiceManage::GetRoomName()
{
	CString _r = "";
	for(int i=0;i<m_ComRoomInfo.GetCount();i++)
	{
		SC_GameRoomInitStruct * p;
		p = (SC_GameRoomInitStruct *)m_ComRoomInfo.GetAt(i);
		_r += p->InitInfo.szGameRoomName;
		if (i != m_ComRoomInfo.GetCount() - 1)
			_r += "\n\r";
	}
	return _r;
}

void CServiceManage::ClearRoomTWRecode(int iRoomID)
{
	//HANDLE hDatabase=sqlAddConnection("BZGameLocal.BCF");
	HANDLE hDatabase=sqlAddConnection(m_sServerIP,m_sAccount,m_sPassword,m_szDatabase,m_nPort);
	if(hDatabase<(HANDLE)0x1000)
		return;

	HANDLE hRecord=sqlSPSetName(hDatabase,"SP_GetGameServerList",true);
	if(hRecord<(HANDLE)0x1000)
		return;

	sqlCloseRecord(hDatabase, hRecord);
    sqlSPClose(hDatabase, hRecord);

    hRecord=sqlSPSetName(hDatabase,"SP_ClearRoomTWLoginRecord");
    if(hRecord>=(HANDLE)0x1000)
    {
		sqlSPAddPara(hDatabase,hRecord,"@RoomID", iRoomID);
        sqlSPExec(hDatabase,hRecord);
        sqlCloseRecord(hDatabase, hRecord);
        sqlSPClose(hDatabase, hRecord);
    }
	sqlCloseConnection(hDatabase);
}