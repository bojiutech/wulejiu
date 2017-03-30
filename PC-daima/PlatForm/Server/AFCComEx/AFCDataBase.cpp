#include "StdAfx.h"
#include "Math.h"
#include "AFCDataBase.h"
#include "AFCFunction.h"
#include "AFCSocket.h"
#include "OleDBErr.h"



extern void DebugPrintf(const char *p, ...);
//***********************************************************************************************//
void DebugPrintf(const char *p, ...)
{
	char szFilename[256];
	sprintf( szFilename, "DebugInfo\\PlatformServer.txt");
	FILE *fp = fopen( szFilename, "a" );
	if (NULL == fp)
	{
		return;
	}
	va_list arg;
	va_start( arg, p );
	fprintf(fp,"[%s]--", CTime::GetCurrentTime().Format("%H:%M:%S"));
	vfprintf(fp, p, arg );
	fprintf(fp,"\n");
	fclose(fp);
}

//�����߳̽ṹ����
struct ThreadStartStruct
{
	//��������
	HANDLE						hEvent;									//�˳��¼�
	HANDLE						hCompletionPort;						//��ɶ˿�
	CAFCDataBaseManage			* pDataManage;							//���ݿ������ָ��
};

//���캯��
CAFCDataBaseManage::CAFCDataBaseManage()
{
	m_bInit=false;
	m_bRun=false;
	m_hThread=NULL;
	m_hCompletePort=NULL;
	m_pInitInfo=NULL;
	m_pKernelInfo=NULL;
	m_pHandleService=NULL;

	hDBLogon=NULL;
	hDBNative=NULL;

	m_sqlClass = 0;
	m_nPort = 0;
	m_bsqlInit = FALSE;

	m_pConnection.CreateInstance(__uuidof(Connection));
	m_pRecordset.CreateInstance(_uuidof(Recordset));//��ʼ��Recordsetָ��
	
}

//��������
CAFCDataBaseManage::~CAFCDataBaseManage(void)
{
}

//��ʼ����
bool CAFCDataBaseManage::Start()
{
	if ((this==NULL)||(m_bRun==true)||(m_bInit==false)) throw new CAFCException(TEXT("CAFCDataBaseManage::Start û�г�ʼ������"),0x401);
	
	//�����¼�
	CEvent StartEvent(FALSE,TRUE,NULL,NULL);
	if (StartEvent==NULL) throw new CAFCException(TEXT("CAFCDataBaseManage::Start �¼�����ʧ��"),0x402);

	//������ɶ˿�
	m_hCompletePort=CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,NULL,0);
	if (m_hCompletePort==NULL) 
		throw new CAFCException(TEXT("CAFCDataBaseManage::Start m_hCompletePort ����ʧ��"),0x403);
	m_DataLine.SetCompletionHandle(m_hCompletePort);
		
	//ͨ�� sqlengine �������ݿ�	
	SQLConnectReset();
	SQLConnect();

	int x=0;
	//�������ݴ����߳�
	unsigned dwThreadID=0;
	ThreadStartStruct ThreadStartData;
	ThreadStartData.pDataManage=this;
	ThreadStartData.hEvent=StartEvent;
	ThreadStartData.hCompletionPort=m_hCompletePort;
	m_hThread=(HANDLE)_beginthreadex(NULL,0,DataServiceThread,&ThreadStartData,0,&dwThreadID);
	if (m_hThread==NULL) throw new CAFCException(TEXT("CAFCDataBaseManage::Start DataServerThread �߳̽���ʧ��"),0x407);
	WaitForSingleObject(StartEvent,INFINITE);
	ResetEvent(StartEvent);

	//�����ɹ�
	m_bRun=true;
	return true;
}

//ֹͣ����
bool CAFCDataBaseManage::Stop()
{
	//��������
	bool bFlush=m_bRun;
	m_bRun=false;
	m_DataLine.SetCompletionHandle(NULL);

	//�ر���ɶ˿�
	if (m_hCompletePort!=NULL)
	{
		//�˳������߳�
		if (m_hThread!=NULL) 
		{
			PostQueuedCompletionStatus(m_hCompletePort,0,NULL,NULL);
			CloseHandle(m_hThread);
			m_hThread=NULL;
		}
		CloseHandle(m_hCompletePort);
		m_hCompletePort=NULL;
	}

	//�ر����ݿ�����
	if (m_pKernelInfo!=NULL)
	{
		sqlCloseConnection(hDBLogon);
		sqlCloseConnection(hDBNative);
	}

	return true;
}

//ȡ����ʼ��
bool CAFCDataBaseManage::UnInit()
{
	//ֹͣ����
	if (m_bRun) Stop();
	m_DataLine.CleanLineData();

	//�ָ�����
	m_bInit=false;
	m_pInitInfo=NULL;
	m_hThread=NULL;
	m_hCompletePort=NULL;
	m_pKernelInfo=NULL;
	m_pHandleService=NULL;

	//if (m_pConnection->State)
	//	m_pConnection->Close();
	return true;
}

//���봦�����
bool CAFCDataBaseManage::PushLine(DataBaseLineHead * pData, UINT uSize, UINT uHandleKind, UINT uIndex,DWORD dwHandleID)
{
	//��������
	pData->dwHandleID=dwHandleID;
	pData->uIndex=uIndex;
	pData->uHandleKind=uHandleKind;
	return (m_DataLine.AddData(&pData->DataLineHead,uSize,0)!=0);
}

//���ݿ⴦���߳�
unsigned __stdcall CAFCDataBaseManage::DataServiceThread(LPVOID pThreadData)
{
	//���ݶ���
	ThreadStartStruct		* pData=(ThreadStartStruct *)pThreadData;		//�߳���������ָ��
	CAFCDataBaseManage		* pDataManage=pData->pDataManage;				//���ݿ����ָ��
	CDataLine				* pDataLine=&pDataManage->m_DataLine;			//���ݶ���ָ��
	IDataBaseHandleService	* pHandleService=pDataManage->m_pHandleService;	//���ݴ���ӿ�
	HANDLE					hCompletionPort=pData->hCompletionPort;			//��ɶ˿�

	//�߳����ݶ�ȡ���
	::SetEvent(pData->hEvent);

	//�ص�����
	void					* pIOData=NULL;									//����
	DWORD					dwThancferred=0;								//��������
	ULONG					dwCompleteKey=0L;								//�ص� IO ��ʱ����
	LPOVERLAPPED			OverData;										//�ص� IO ��ʱ����

	//���ݻ���
	BOOL					bSuccess=FALSE;
	BYTE					szBuffer[LD_MAX_PART];

	while (TRUE)
	{
		//�ȴ���ɶ˿�
		bSuccess=GetQueuedCompletionStatus(hCompletionPort,&dwThancferred,&dwCompleteKey,(LPOVERLAPPED *)&OverData,INFINITE);
		if ((bSuccess==FALSE)||dwThancferred==0)
		{
			_endthreadex(0);
			return 0;
		}
		while(pDataLine->GetDataCount())
		{
			DebugPrintf("pDataLine->GetDataCount()=%d",pDataLine->GetDataCount());
			try
			{
				//������ɶ˿�����
				if (pDataLine->GetData((DataLineHead *)szBuffer,sizeof(szBuffer))<sizeof(DataBaseLineHead))
					continue;
				pHandleService->HandleDataBase((DataBaseLineHead *)szBuffer);
			}
			catch (...) 
			{ 
				TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
				continue; 
			}
		}
	}

	_endthreadex(0);
	return 0;
}


///�������ݿ�
bool CAFCDataBaseManage::SQLConnectReset()
{
	if (m_bsqlInit == FALSE)
	{
		tinyxml2::XMLDocument doc;
		if (tinyxml2::XMLError::XML_SUCCESS != doc.LoadFile("HNGameLocal.xml"))
		{
			AfxMessageBox("Load HNGameLocal.xml Error-0",0);
			return false;
		}
		tinyxml2::XMLElement* element1 = doc.FirstChildElement("SQLSERVER");
		if (NULL == element1)
		{
			AfxMessageBox("Load HNGameLocal.xml Error-0-1",0);
			return false;
		}
		for (const tinyxml2::XMLElement* xml_SqlServer = element1->FirstChildElement(); xml_SqlServer; xml_SqlServer = xml_SqlServer->NextSiblingElement()) 
		{
			//���ݿ�IP��ַ
			if (!strcmp(xml_SqlServer->Value(), "DBSERVER")) 
			{
				m_szServer = xml_SqlServer->Attribute("key");
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
				m_szAccount = xml_SqlServer->Attribute("key");
			}
			else if (!strcmp(xml_SqlServer->Value(), "DBPASSWORD")) 
			{
				//���ݿ��¼����
				m_szPassword = xml_SqlServer->Attribute("key");
			}
		}
		m_szDetectTable=TEXT("");
		m_bsqlInit = TRUE;
	}
	if(m_pKernelInfo->bNativeDataBase)
	{
		sqlCloseConnection(hDBNative);
		hDBNative = sqlAddConnection( m_szServer, m_szAccount, m_szPassword, m_szDatabase,m_nPort, m_sqlClass, m_szDetectTable);
		if(hDBNative<(HANDLE)0x1000)
		{
			hDBNative=0;
			throw new CAFCException(TEXT("CAFCDataBaseManage::Start ���ӱ������ݿ�ʧ��"),0x424);
		}
	}

	if(m_pKernelInfo->bLogonDataBase)
	{
		sqlCloseConnection(hDBLogon);
		hDBLogon = sqlAddConnection( m_szServer, m_szAccount, m_szPassword, m_szDatabase,m_nPort, m_sqlClass, m_szDetectTable);
		if(hDBLogon<(HANDLE)0x1000)
		{
			hDBLogon=0;
			throw new CAFCException(TEXT("CAFCDataBaseManage::Start ���ӵ�½���ݿ�ʧ��"),0x425);
		}
	}
}

//�����������
bool CAFCDataBaseManage::CheckSQLConnect()
{

	return true;
	//if ((m_bRun==true)&&(m_pKernelInfo->bStartSQLDataBase==TRUE))
	//{
	//	//��������
	//	HRESULT hResult=S_OK;
	//	bool bReConnect=false;

	//	//����½���ݿ�
	//	if (m_pKernelInfo->bLogonDataBase==TRUE)
	//	{
	//		if ((m_DataBaseLogon.Execute(TEXT("select top 1 * from TGameServerInfo"),hResult)==false)&&(hResult!=DB_E_ERRORSINCOMMAND))
	//		{
	//			bReConnect=true;
	//			m_DataBaseLogon.Close();
	//			m_DataBaseLogon.Open(m_strLogonDataConnect);
	//		}
	//	}

	//	//��Ȿ�����ݿ�
	//	if (m_pKernelInfo->bNativeDataBase==TRUE)
	//	{
	//		if ((m_DataBaseNative.Execute(TEXT("select top 1 * from TGameServerInfo"),hResult)==false)&&(hResult!=DB_E_ERRORSINCOMMAND))
	//		{
	//			bReConnect=true;
	//			m_DataBaseNative.Close();
	//			m_DataBaseNative.Open(m_strNativeDataConnect);
	//		}
	//	}

	//	return bReConnect;
	//}

	return false;
}

void CAFCDataBaseManage::SQLConnect()
{
	if (m_bsqlInit == FALSE)
	{
		tinyxml2::XMLDocument doc;
		if (tinyxml2::XMLError::XML_SUCCESS != doc.LoadFile("HNGameLocal.xml"))
		{
			AfxMessageBox("Load HNGameLocal.xml Error-1",0);
			return ;
		}
		tinyxml2::XMLElement* element1 = doc.FirstChildElement("SQLSERVER");
		if (NULL == element1)
		{
			AfxMessageBox("Load HNGameLocal.xml Error-1-1",0);
			return ;
		}
		for (const tinyxml2::XMLElement* xml_SqlServer = element1->FirstChildElement(); xml_SqlServer; xml_SqlServer = xml_SqlServer->NextSiblingElement()) 
		{
			//���ݿ�IP��ַ
			if (!strcmp(xml_SqlServer->Value(), "DBSERVER")) 
			{
				m_szServer = xml_SqlServer->Attribute("key");
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
				m_szAccount = xml_SqlServer->Attribute("key");
			}
			else if (!strcmp(xml_SqlServer->Value(), "DBPASSWORD")) 
			{
				//���ݿ��¼����
				m_szPassword = xml_SqlServer->Attribute("key");
			}
		}
		m_szDetectTable=TEXT("");
		m_bsqlInit = TRUE;
	}


	CString str;
	if (m_nPort==0)
		str.Format("Provider=sqloledb;Network Library=DBMSSOCN;Initial Catalog=%s;User ID=%s;Password=%s;Data Source=%s"
		,m_szDatabase.GetBuffer(),m_szAccount.GetBuffer(),m_szPassword.GetBuffer(),m_szServer.GetBuffer());
	else
		str.Format("Provider=sqloledb;Network Library=DBMSSOCN;Initial Catalog=%s;User ID=%s;Password=%s;Data Source=%s,%d"
		,m_szDatabase.GetBuffer(),m_szAccount.GetBuffer(),m_szPassword.GetBuffer(),m_szServer.GetBuffer(),m_nPort);


	if (m_pConnection->State != adStateClosed)
		m_pConnection->Close();

	try
	{
		m_pConnection->Open(_bstr_t(str),"","",adModeUnknown);
	}
	catch(_com_error e)
	{
		DebugPrintf("�������ݿ�ʧ�ܣ�����");
		if (m_pConnection->State != adStateClosed)
			m_pConnection->Close();

	}
	
}

bool CAFCDataBaseManage::SQLExec(const TCHAR * szSQL)
{
	CString strSql;
	bool bCon = true;
	try
	{
		strSql.Format("select top 1 * from TGameServerInfo");
		BSTR bstrSQL = strSql.AllocSysString(); 
		m_pRecordset->Open(bstrSQL,(IDispatch*)m_pConnection,adOpenDynamic,adLockOptimistic,adCmdText);
		if (m_pRecordset-> State == adStateOpen) 
			m_pRecordset-> Close(); 
	}
	catch (...)
	{
		bCon = false;
	}

	if(!bCon)
	{
		SQLConnect();
	}


	bool bRet =  SUCCEEDED(m_pRecordset->Open(szSQL,(IDispatch*)m_pConnection,adOpenDynamic,adLockOptimistic,adCmdText));

	if ((m_pRecordset->GetState()!=adStateClosed)) m_pRecordset->Close();

	return bRet;

}

//***********************************************************************************************//

//���캯��
CDataBaseHandle::CDataBaseHandle(void)
{
	m_pInitInfo=NULL;
	m_pKernelInfo=NULL;
	m_pRusultService=NULL;
	m_pDataBaseManage=NULL;
}

//�������� 
CDataBaseHandle::~CDataBaseHandle(void)
{
}

//���ò���
bool CDataBaseHandle::SetParameter(IDataBaseResultService * pRusultService, CAFCDataBaseManage * pDataBaseManage, ManageInfoStruct * pInitData, KernelInfoStruct * pKernelData)
{
	m_pInitInfo=pInitData;
	m_pKernelInfo=pKernelData;
	m_pRusultService=pRusultService;
	m_pDataBaseManage=pDataBaseManage;
	return true;
}



//��ʼ������
bool CAFCDataBaseManage::Init(ManageInfoStruct * pInitInfo, KernelInfoStruct * pKernelInfo, 
							  IDataBaseHandleService * pHandleService,IDataBaseResultService * pResultService)
{
	//Ч�����
	if ((this==NULL)||(m_bInit==true)||(m_bRun==true))	throw new CAFCException(TEXT("CAFCDataBaseManage::Init ״̬Ч��ʧ��"),0x408);

	//��������
	m_pInitInfo=pInitInfo;
	m_pKernelInfo=pKernelInfo;
	m_pHandleService=pHandleService;
	m_DataLine.CleanLineData();

	//��������
	m_bInit=true;
	return true;
}





//***********************************************************************************************//
