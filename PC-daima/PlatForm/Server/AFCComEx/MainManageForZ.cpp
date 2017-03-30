#include "StdAfx.h"
#include "MainManageForZ.h"
#include "AFCException.h"
#include "GameRoomMessage.h"

#pragma warning (disable: 4355)

//�������Ͷ���
#define HD_SOCKET_READ					1							//SOCKET ��ȡ�¼�����			
#define HD_SOCKET_CLOSE					2							//SOCKET �ر��¼�����			
#define HD_DATA_BASE_RESULT				3							//���ݿ�������
#define HD_TIMER_MESSAGE				4							//��ʱ����Ϣ����
extern CString GetAppPath(bool bFource=true); 
extern void DebugPrintf(const char *p, ...);

//�����߳������ṹ
struct WindowThreadStartStruct
{
	//��������
	HANDLE								hEvent;						//�����¼�
	BOOL								bSuccess;					//�����ɹ���־
	CBaseMainManageForZ						* pMainManage;				//���ݹ���ָ��
};

//�����߳������ṹ
struct HandleThreadStartStruct
{
	//��������
	HANDLE								hEvent;						//�����¼�
	HANDLE								hCompletionPort;			//��ɶ˿�
	CBaseMainManageForZ						* pMainManage;				//���ݹ���ָ��
};

//SOCKET �ر�֪ͨ�ṹ����
struct SocketCloseLine
{
	DataLineHead						LineHead;					//����ͷ
	UINT								uIndex;						//SOCKT ����
	ULONG								uAccessIP;					//SOCKET IP
	long int							lConnectTime;				//����ʱ��
};

//SOCKET ��ȡ֪ͨ�ṹ����
struct SocketReadLine
{
	DataLineHead						LineHead;					//����ͷ
	NetMessageHead						NetMessageHead;				//���ݰ�ͷ
	UINT								uHandleSize;				//���ݰ������С
	UINT								uIndex;						//SOCKET ����
	ULONG								uAccessIP;					//SOCKET IP
	DWORD								dwHandleID;					//SOCKET ���� ID
};

//��ʱ����Ϣ�ṹ����
struct WindowTimerLine
{
	DataLineHead						LineHead;					//����ͷ
	UINT								uTimerID;					//��ʱ�� ID
};

/*****************************************************************************************************************/

//���캯��
CBaseMainManageForZ::CBaseMainManageForZ(void)
{
	m_bInit=false;
	m_bRun=false;
	m_hWindow=NULL;
	m_hHandleThread=NULL;
	m_hWindowThread=NULL;
	m_hCompletePort=NULL;
	::memset(&m_DllInfo,0,sizeof(m_DllInfo));
	::memset(&m_InitData,0,sizeof(m_InitData));
	::memset(&m_KernelData,0,sizeof(m_KernelData));
}

//��������	
CBaseMainManageForZ::~CBaseMainManageForZ(void)
{
}

//��ʼ������ 
bool CBaseMainManageForZ::Init(ManageInfoStruct * pInitData, IDataBaseHandleService * pDataHandleService)
{
	if ((this==NULL)||(m_bInit==true)) return false;

	//��������
	UINT uMax=pInitData->uMaxPeople;
	m_InitData=*pInitData;
	if (!PreInitParameter(&m_InitData,&m_KernelData)) throw new CAFCException(TEXT("CBaseMainManageForZ::Init PreInitParameter �������ڴ���"),0x41A);
	if(m_InitData.uMaxPeople<uMax)
		m_InitData.uMaxPeople=uMax;

	//��ʼ�����
	if (m_KernelData.bStartTCPSocket) 
		m_TCPSocket.Init(m_InitData.uMaxPeople,m_InitData.uListenPort,m_KernelData.bMaxVer,m_KernelData.bLessVer,m_InitData.iSocketSecretKey,this);
	if (m_KernelData.bStartSQLDataBase)
	{
		if (pDataHandleService!=NULL)
			pDataHandleService->SetParameter(this,&m_SQLDataManage,&m_InitData,&m_KernelData);
		m_SQLDataManage.Init(&m_InitData,&m_KernelData,pDataHandleService,this);
	}

	//���ýӿ�
	if (OnInit(&m_InitData,&m_KernelData)==false)  
		throw new CAFCException(TEXT("CBaseMainManageForZ::Init OnInit ��������"),0x41B);

	m_bInit=true;
	CString s = GetAppPath();
	m_TalkFilter.LoadFilterMessage(s.GetBuffer());
	return true;
}

//ȡ����ʼ������ 
bool CBaseMainManageForZ::UnInit()
{
	if (this==NULL) return false;
	//////////////////////////////////
	//Kylin 20090209 ��������û����߱��

	//ֹͣ����
	if (m_bRun) Stop();

	//���ýӿ�
	OnUnInit();
	//////////////////////////////////
	//ȡ����ʼ��
	m_bInit=false;
	m_TCPSocket.UnInit();
	m_SQLDataManage.UnInit();

	//��������
	memset(&m_DllInfo,0,sizeof(m_DllInfo));
	memset(&m_InitData,0,sizeof(m_InitData));
	memset(&m_KernelData,0,sizeof(m_KernelData));

	return true;
}

//��������
bool CBaseMainManageForZ::Start()
{	
	if ((this==NULL)||(m_bRun==true)||(m_bInit==false)) return false;
	//�����¼�
	CEvent StartEvent(FALSE,TRUE,NULL,NULL);
	if (StartEvent==NULL) throw new CAFCException(TEXT("CBaseMainManageForZ::Start �¼�����ʧ��"),0x41C);
	//������ɶ˿�
	m_hCompletePort=::CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,NULL,0);
	if (m_hCompletePort==NULL) throw new CAFCException(TEXT("CBaseMainManageForZ::Start m_hCompletePort ����ʧ��"),0x41D);
	m_DataLine.SetCompletionHandle(m_hCompletePort);
	
	//���������߳�
	UINT uThreadID=0;
	HandleThreadStartStruct	ThreadStartData;
	ThreadStartData.pMainManage=this;
	ThreadStartData.hCompletionPort=m_hCompletePort;
	ThreadStartData.hEvent=StartEvent;
	m_hHandleThread=(HANDLE)_beginthreadex(NULL,0,LineDataHandleThread,&ThreadStartData,0,&uThreadID);
	if (m_hHandleThread==NULL) throw new CAFCException(TEXT("CBaseMainManageForZ::Start LineDataHandleThread �߳�����ʧ��"),0x41E);
	WaitForSingleObject(StartEvent,INFINITE);
	
	//�������
	AFCKernelStart();
	
	if (m_KernelData.bStartSQLDataBase)	m_SQLDataManage.Start();
	
	if (m_KernelData.bStartTCPSocket) m_TCPSocket.Start(m_KernelData.uAcceptThreadCount,m_KernelData.uSocketThreadCount);
	
	//���ýӿ�
	if (OnStart()==false) throw new CAFCException(TEXT("CBaseMainManageForZ::Start OnStart ��������"),0x41F);
	
	//��������
	m_bRun=true;
	return true;
}

//ֹͣ����
bool CBaseMainManageForZ::Stop()
{
	if (this==NULL) return false;

	//���ýӿ�
	OnStop();

	//ֹͣ���
	m_bRun=false;
	m_DataLine.SetCompletionHandle(NULL);

	m_TCPSocket.Stop();
	m_SQLDataManage.Stop();

	//�رմ���
	if ((m_hWindow!=NULL)&&(::IsWindow(m_hWindow)==TRUE)) ::SendMessage(m_hWindow,WM_CLOSE,0,0);

	//�ر���ɶ˿�
	if (m_hCompletePort!=NULL)
	{
		::PostQueuedCompletionStatus(m_hCompletePort,0,NULL,NULL);
		::CloseHandle(m_hCompletePort);
		m_hCompletePort=NULL;
	}

	//�˳������߳�
	if ((m_hWindowThread!=NULL)&&(::WaitForSingleObject(m_hWindowThread,3000)==WAIT_TIMEOUT))
	{
		TerminateThread(m_hWindowThread,0);	
		CloseHandle(m_hWindowThread);
		m_hWindowThread=NULL;
	}

	//�˳������߳�
	if ((m_hHandleThread!=NULL)&&(::WaitForSingleObject(m_hHandleThread,3000)==WAIT_TIMEOUT))
	{
		TerminateThread(m_hHandleThread,0);
		CloseHandle(m_hHandleThread);
		m_hHandleThread=NULL;
	}

	return true;
}

//����رմ���
bool CBaseMainManageForZ::OnSocketCloseEvent(ULONG uAccessIP, UINT uIndex, long int lConnectTime)
{
	SocketCloseLine SocketClose;
	SocketClose.lConnectTime=lConnectTime;
	SocketClose.uIndex=uIndex;
	SocketClose.uAccessIP=uAccessIP;
	return (m_DataLine.AddData(&SocketClose.LineHead,sizeof(SocketClose),HD_SOCKET_CLOSE)!=0);
}

//������Ϣ����
bool CBaseMainManageForZ::OnSocketReadEvent(CTCPSocketForZ * pSocket, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uIndex, DWORD dwHandleID)
{
	SocketReadLine SocketRead;
	SocketRead.uHandleSize=uSize;
	SocketRead.uIndex=uIndex;
	SocketRead.dwHandleID=dwHandleID;
	SocketRead.uAccessIP=pSocket->GetConnectData();
	SocketRead.NetMessageHead=*pNetHead;
	return (m_DataLine.AddData(&SocketRead.LineHead,sizeof(SocketRead),HD_SOCKET_READ,pData,uSize)!=0);
}

//��ʱ��֪ͨ��Ϣ
bool CBaseMainManageForZ::WindowTimerMessage(UINT uTimerID)
{
	WindowTimerLine WindowTimer;
	WindowTimer.uTimerID=uTimerID;
	return (m_DataLine.AddData(&WindowTimer.LineHead,sizeof(WindowTimer),HD_TIMER_MESSAGE)!=0);
}

//���ݿ�������
bool CBaseMainManageForZ::OnDataBaseResultEvent(DataBaseResultLine * pResultData, UINT uHandleKind, UINT uHandleResult, UINT uResultSize, UINT uIndex, DWORD dwHandleID)
{
	//��װ����
	pResultData->LineHead.uSize=uResultSize;
	pResultData->uHandleKind=uHandleKind;
	pResultData->uHandleRusult=uHandleResult;
	pResultData->dwHandleID=dwHandleID;
	pResultData->uIndex=uIndex;

	//�������
	return (m_DataLine.AddData(&pResultData->LineHead,uResultSize,HD_DATA_BASE_RESULT)!=0);
}

//�趨��ʱ��
bool CBaseMainManageForZ::SetTimer(UINT uTimerID, UINT uElapse)
{
	if ((m_hWindow!=NULL)&&(IsWindow(m_hWindow)==TRUE))
	{
		::SetTimer(m_hWindow,uTimerID,uElapse,NULL);
		return true;
	}
	return false;
}

//�����ʱ��
bool CBaseMainManageForZ::KillTimer(UINT uTimerID)
{
	if ((m_hWindow!=NULL)&&(::IsWindow(m_hWindow)==TRUE))
	{
		::KillTimer(m_hWindow,uTimerID);
		return true;
	}
	return false;
}

//�ں˳�ʼ������
bool CBaseMainManageForZ::AFCKernelStart()
{
	if ((m_hWindow!=NULL)&&(::IsWindow(m_hWindow)==TRUE)) return false;

	//�����¼�
	CEvent StartEvent(FALSE,TRUE,NULL,NULL);
	if (StartEvent==NULL) throw new CAFCException(TEXT("CBaseMainManageForZ::AFCKernelStart �¼�����ʧ��"),0x420);

	//�����߳�
	WindowThreadStartStruct ThreadData;
	ThreadData.bSuccess=FALSE;
	ThreadData.pMainManage=this;
	ThreadData.hEvent=StartEvent;

	UINT uThreadID=0;
	m_hWindowThread=(HANDLE)::_beginthreadex(NULL,0,WindowMsgThread,&ThreadData,0,&uThreadID);
	if (m_hWindowThread==NULL) throw new CAFCException(TEXT("CBaseMainManageForZ::AFCKernelStart WindowMsgThread �߳̽���ʧ��"),0x421);
	::WaitForSingleObject(ThreadData.hEvent,INFINITE);
	if (ThreadData.bSuccess==FALSE) throw new CAFCException(TEXT("CBaseMainManageForZ::AFCKernelStart WindowMsgThread �߳̽���ʧ��"),0x422);

	return true;
}

//�������ݴ����߳�
unsigned __stdcall CBaseMainManageForZ::LineDataHandleThread(LPVOID pThreadData)
{
	//���ݶ���
	HandleThreadStartStruct		* pData=(HandleThreadStartStruct *)pThreadData;		//�߳���������ָ��
	CBaseMainManageForZ				* pMainManage=pData->pMainManage;					//���ݹ���ָ��
	CDataLine					* m_pDataLine=&pMainManage->m_DataLine;				//���ݶ���ָ��
	HANDLE						hCompletionPort=pData->hCompletionPort;				//��ɶ˿�
	bool						& bRun=pMainManage->m_bRun;							//���б�־

	//�߳����ݶ�ȡ���
	::SetEvent(pData->hEvent);

	//�ص�����
	void						* pIOData=NULL;										//����
	DWORD						dwThancferred=0;									//��������
	ULONG						dwCompleteKey=0L;									//�ص� IO ��ʱ����
	LPOVERLAPPED				OverData;											//�ص� IO ��ʱ����

	//���ݻ���
	BOOL						bSuccess=FALSE;
	BYTE						szBuffer[LD_MAX_PART];
	DataLineHead				* pDataLineHead=(DataLineHead *)szBuffer;

	while (1)
	{
		//�ȴ���ɶ˿�
		bSuccess=::GetQueuedCompletionStatus(hCompletionPort,&dwThancferred,&dwCompleteKey,(LPOVERLAPPED *)&OverData,INFINITE);
		if ((bSuccess==FALSE)||dwThancferred==0) ::_endthreadex(0);	
		//��������
		while(m_pDataLine->GetDataCount())//�������д�����Ϣ����,�᲻��ռ��̫���cpuʱ���ʹ�����߳���ʱ����
		{
			//��������
			try
			{
				//������ɶ˿�����
				if ((bRun==false)||(m_pDataLine->GetData(pDataLineHead,sizeof(szBuffer))==0)) continue;

				switch (pDataLineHead->uDataKind)
				{
				case HD_SOCKET_READ:		//SOCKET ���ݶ�ȡ
					{
						SocketReadLine * pSocketRead=(SocketReadLine *)pDataLineHead;
						try
						{
							bool bSuccess=pMainManage->OnSocketRead(&pSocketRead->NetMessageHead,
								pSocketRead->uHandleSize?pSocketRead+1:NULL,
								pSocketRead->uHandleSize,pSocketRead->uAccessIP,
								pSocketRead->uIndex,pSocketRead->dwHandleID);
							if (bSuccess==false) 
							{
								TRACE("HERE IS FAILED!\n");
								throw ("�������ݰ���������쳣");
							}//
						}
						catch (...)
						{
							TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
							//DebugPrintf("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
							pMainManage->m_TCPSocket.CloseSocket(pSocketRead->uIndex,pSocketRead->dwHandleID);
						}
						break;
					}
				case HD_SOCKET_CLOSE:		//SOCKET �ر�
					{
						SocketCloseLine * pSocketClose=(SocketCloseLine *)pDataLineHead;
						pMainManage->OnSocketClose(pSocketClose->uAccessIP,pSocketClose->uIndex,pSocketClose->lConnectTime);
						break;
					}
				case HD_DATA_BASE_RESULT:	//���ݿ⴦����
					{
						DataBaseResultLine * pDataResult=(DataBaseResultLine *)pDataLineHead;
						pMainManage->OnDataBaseResult(pDataResult);
						break;
					}
				case HD_TIMER_MESSAGE:		//��ʱ����Ϣ
					{
						WindowTimerLine * pTimerMessage=(WindowTimerLine *)pDataLineHead;
						pMainManage->OnTimerMessage(pTimerMessage->uTimerID);
						break;
					}
				}
			}

			catch (...) 
			{ TRACE("CATCH:%s with %s %d\n",__FILE__,__FUNCTION__,__LINE__);
			continue;
			}
		}
	}

	::_endthreadex(0);
	return 0;
}

//WINDOW ��Ϣѭ���߳�
unsigned __stdcall CBaseMainManageForZ::WindowMsgThread(LPVOID pThreadData)
{
	WindowThreadStartStruct * pStartData=(WindowThreadStartStruct *)pThreadData;

	try
	{
		//ע�ᴰ����
		LOGBRUSH		LogBrush;
		WNDCLASS		WndClass;
		TCHAR			szClassName[]=TEXT("CMainManageWindow");

		LogBrush.lbColor=RGB(0,0,0);
		LogBrush.lbStyle=BS_SOLID;
		LogBrush.lbHatch=0;
		WndClass.cbClsExtra=0;
		WndClass.cbWndExtra=0;
		WndClass.hCursor=NULL;
		WndClass.hIcon=NULL;
		WndClass.lpszMenuName=NULL;
		WndClass.lpfnWndProc=WindowProcFunc;
		WndClass.lpszClassName=szClassName;
		WndClass.style=CS_HREDRAW|CS_VREDRAW;
		WndClass.hInstance=NULL;
		WndClass.hbrBackground=(HBRUSH)::CreateBrushIndirect(&LogBrush);
		::RegisterClass(&WndClass);

		//��������
		pStartData->pMainManage->m_hWindow=::CreateWindow(szClassName,NULL,0,0,0,0,0,NULL,NULL,NULL,pStartData->pMainManage);
		if (pStartData->pMainManage->m_hWindow==NULL) throw TEXT("���ڽ���ʧ��");
	}
	catch (...)
	{TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
	//��������
	pStartData->bSuccess=FALSE;
	::SetEvent(pStartData->hEvent);
	_endthreadex(0);
	}

	//�����ɹ�
	pStartData->bSuccess=TRUE;
	::SetEvent(pStartData->hEvent);

	//��Ϣѭ��
	MSG	Message;
	while (::GetMessage(&Message,NULL,0,0))
	{
		if (!::TranslateAccelerator(Message.hwnd,NULL,&Message))
		{
			::TranslateMessage(&Message);
			::DispatchMessage(&Message);
		}
	}

	_endthreadex(0);
	return 0;
}

//���ڻص�����
LRESULT CALLBACK CBaseMainManageForZ::WindowProcFunc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:		//���ڽ�����Ϣ
		{
			DWORD iIndex=TlsAlloc();
			CBaseMainManageForZ * pMainManage=(CBaseMainManageForZ *)(((CREATESTRUCT *)lParam)->lpCreateParams);
			TlsSetValue(iIndex,pMainManage);
			::SetWindowLong(hWnd,GWL_USERDATA,iIndex);
			break;
		}
	case WM_TIMER:		//��ʱ����Ϣ
		{
			DWORD iIndex=::GetWindowLong(hWnd,GWL_USERDATA);
			CBaseMainManageForZ * pMainManage=(CBaseMainManageForZ *)::TlsGetValue(iIndex);
			if ((pMainManage!=NULL)&&(pMainManage->WindowTimerMessage((UINT)wParam)==false)) ::KillTimer(hWnd,(UINT)wParam);
			break;
		}
	case WM_CLOSE:		//���ڹر���Ϣ
		{
			DestroyWindow(hWnd);
			break;
		}
	case WM_DESTROY:	//���ڹر���Ϣ
		{
			DWORD iIndex=::GetWindowLong(hWnd,GWL_USERDATA);
			CBaseMainManageForZ * pMainManage=(CBaseMainManageForZ *)::TlsGetValue(iIndex);
			if (pMainManage!=NULL) pMainManage->m_hWindow=NULL;
			::TlsFree(iIndex);
			PostQuitMessage(0);
			break;
		}
	}
	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}
