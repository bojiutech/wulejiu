#include "StdAfx.h"
#include "AFCSocket.h"
#include "AFCException.h"
#include "AFCFunction.h"

/**************************************************************************************************************/

//���Ʊ�ʶ
#define SOCKET_SND				1								//SOCKET ����
#define SOCKET_REV				2								//SOCKET ����
#define SOCKET_CLO				3								//SOCKET �˳�

//��ʱʱ��
#define	TIME_OUT				3000							

#define ID_SOCKET_WND			10								//SOCKET ���� ID
#define WM_SOCKET_MESSAGE		WM_USER+12						//SOCKET ��Ϣ

/**************************************************************************************************************/
const char POLICYFILEREQUESET[MAX_PATH]	= TEXT("<policy-file-request/>");
const char POLICYFILERESPONSE[2000]  = "<?xml version=\"1.0\"?> \
									   <!DOCTYPE cross-domain-policy SYSTEM \"http://www.macromedia.com/xml/dtds/cross-domain-policy.dtd\"> \
									   <cross-domain-policy> \
									   <allow-access-from domain=\"*\" to-ports=\"*\" /> \
									   </cross-domain-policy>";

///static int MaxConnectCount=3;

//���ɿ��� SOCKET
CTCPSocket * CTCPSocketManage::TCPSocketNew()
{
	////if(m_SocketPtrArray.GetActiveCount() > MaxConnectCount)return NULL;
	if (m_bRun)
	{
		CSignedLockObject LockObject(m_SocketPtrArray.GetArrayLock(),true);
		return m_SocketPtrArray.NewItem();
	}
	return NULL;
}


//�ͷŻ SOCKET
bool CTCPSocketManage::TCPSocketDelete(CTCPSocket * pSocket)
{
	if (pSocket!=NULL)
	{
		CSignedLockObject LockObject(m_SocketPtrArray.GetArrayLock(),true);
		pSocket->CloseSocket();
		return m_SocketPtrArray.FreeItem(pSocket);
	}
	return false;
}



//SOCKET ����Ӧ���߳�
unsigned __stdcall CTCPSocketManage::ThreadAccept(LPVOID pThreadData)
{
	//���ݶ���
	ThreadStartStruct	* pStartData=(ThreadStartStruct *)pThreadData;			//�߳���������ָ��
	CTCPSocketManage	* pSocketManage=pStartData->pSocketManage;				//����ָ��
	HANDLE				hCompletionPort=pStartData->hCompletionPort;			//��ɶ˿�

	sockaddr_in			SocketAddr;
	int					iAddrBuferLen=sizeof(SocketAddr);
	SOCKET				hSocket=INVALID_SOCKET;
	CTCPSocket			* pNewTCPSocket=NULL;
	HANDLE				hAcceptCompletePort=NULL;
	SOCKET				hListenScoket=pStartData->pSocketManage->m_ListenSocket.GetSafeSocket();

	//���ӷ�������
	MSG_S_ConnectSuccess ConncetSuccess;
	ConncetSuccess.bMaxVer=pSocketManage->m_bMaxVer;
	ConncetSuccess.bLessVer=pSocketManage->m_bLessVer;

	//�߳����ݶ�ȡ���
	SetEvent(pStartData->hThreadEvent);

	while (1)
	{
		try
		{

			//��������
			hSocket=::WSAAccept(hListenScoket,(sockaddr *)&SocketAddr,&iAddrBuferLen,NULL,NULL);
			if (hSocket==INVALID_SOCKET) 
			{
				int iErrorCode=WSAGetLastError();
				_endthreadex(0);
			}

			//��������
			pNewTCPSocket=pSocketManage->TCPSocketNew();
			if ((pNewTCPSocket!=NULL)&&(pNewTCPSocket->Attach(hSocket,SocketAddr,GetHandleID())))
			{
				hAcceptCompletePort=::CreateIoCompletionPort((HANDLE)hSocket,hCompletionPort,(ULONG_PTR)pNewTCPSocket,0);
				if ((hAcceptCompletePort==NULL)||(!pNewTCPSocket->RecvData())) throw TEXT("Accept False");

				if (pNewTCPSocket->m_pManage->GetListenPort() != FLASH_SERVER_PORT)
				{
					//�������ӳɹ���Ϣ
					MSG_S_ConnectSuccess Message;
					Message.bLessVer=MAKELONG(3,4);
					Message.bReserve[0]=0;
					Message.bMaxVer=MAKELONG(3,4);
					Message.bReserve[1]=0;
					//�˴���hSocket���м��ܣ��ɿͻ��˽��ܲ��ڰ�ͷ��bReserve�ֶ��з�����У�顣����SECRET_KEYΪ��Կ�ɿͻ��Լ�������
					Message.i64CheckCode = (int)hSocket * 23 + pSocketManage->m_iSecretKey;

					pNewTCPSocket->SendData(&Message,sizeof(Message),MDM_CONNECT,ASS_CONNECT_SUCCESS, 0, pNewTCPSocket->GetHandleID());
				}
			}
			else
			{
				//û�п��е�SOCKET�ˣ��ж�Ϊ������
				NetMessageHead netHead;
				ZeroMemory(&netHead,sizeof(NetMessageHead));
				netHead.bMainID=100;//MDM_GR_LOGON
				netHead.bAssistantID=3;//ASS_GR_LOGON_ERROR
				netHead.bHandleCode=10;//ERR_GR_PEOPLE_FULL
				netHead.uMessageSize=sizeof(NetMessageHead);
				netHead.bReserve=0;
				
				sendto(hSocket,(char *)&netHead,sizeof(NetMessageHead),0,(sockaddr*)&SocketAddr,sizeof(SocketAddr));
				throw TEXT("Accept False");
			}
		}
		catch (...)
		{TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
			::closesocket(hSocket);
			if (pNewTCPSocket!=NULL) pSocketManage->TCPSocketDelete(pNewTCPSocket);
		}
	}

	return 0;
}
























//���캯��
CUDPSocket::CUDPSocket(void)
{
	m_hSocket=INVALID_SOCKET;
}

//��������
CUDPSocket::~CUDPSocket(void)
{
	if (m_hSocket!=INVALID_SOCKET) ::closesocket(m_hSocket);
}

//���ͺ���
int	CUDPSocket::SendData(void * pData, UINT uSize, TCHAR szSendIP[])
{
	return uSize;
}

//���պ���
int CUDPSocket::RecvData()
{
	return 0;
}

/**************************************************************************************************************/

//���캯��
CListenSocket::CListenSocket(void)
{
	m_hSocket=INVALID_SOCKET;
}

//��������
CListenSocket::~CListenSocket(void)
{
	CloseSocket();
}

//���� SOCKET
bool CListenSocket::Create()
{
	m_hSocket=::WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,NULL,0,WSA_FLAG_OVERLAPPED);
	return (m_hSocket!=INVALID_SOCKET);
}

//�󶨵�ַ
bool CListenSocket::Bind(UINT uPort)
{
	struct sockaddr_in SocketAddr;
	::memset(&SocketAddr,0,sizeof(SocketAddr));
	SocketAddr.sin_family=AF_INET;
	SocketAddr.sin_addr.s_addr=INADDR_ANY;
	SocketAddr.sin_port=htons(uPort);
	return (::bind(m_hSocket,(SOCKADDR*)&SocketAddr,sizeof(SocketAddr))!=SOCKET_ERROR);
}

//��������
bool CListenSocket::Listen()
{
	return (::listen(m_hSocket,200)!=SOCKET_ERROR);
}

//�ر� SOCKET
bool CListenSocket::CloseSocket()
{
	closesocket(m_hSocket);
	m_hSocket=INVALID_SOCKET;
	return true;
}

/**************************************************************************************************************/

BEGIN_MESSAGE_MAP(CTCPClientSocket, CWnd)
	ON_MESSAGE(WM_SOCKET_MESSAGE,OnSocketNotifyMesage)
END_MESSAGE_MAP()

//���캯��
CTCPClientSocket::CTCPClientSocket(IClientSocketService * pIService)
{
	m_iReadBufLen=0;
	m_pIService=pIService;
	m_bConnectState=NO_CONNECT;
	m_hSocket=INVALID_SOCKET;
	if (AfxGetMainWnd()!=NULL) InitSocketWnd();
}

//��������
CTCPClientSocket::~CTCPClientSocket()
{
	CloseSocket(false);
	CloseSocketWnd();
}

//��ʼ�� SOCKET
bool CTCPClientSocket::InitSocketWnd()
{
	try
	{
		if (GetSafeHwnd()==NULL)
		{	
			if (!Create(NULL,NULL,WS_CHILD,CRect(0,0,0,0),AfxGetMainWnd(),ID_SOCKET_WND,NULL))	return false;
		}
	}
	catch (...) {TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);}
	return true;
}

//�ر� SOCKET ����
bool CTCPClientSocket::CloseSocketWnd()
{
	if (GetSafeHwnd()!=NULL) DestroyWindow();
	return true;
}

//SOCKET ��Ϣ�������
LRESULT	CTCPClientSocket::OnSocketNotifyMesage(WPARAM wParam, LPARAM lParam)
{
	switch (WSAGETSELECTEVENT(lParam))
	{
	case FD_CONNECT:	//������Ϣ
		{
			UINT uErrorCode=WSAGETSELECTERROR(lParam);
			if (uErrorCode==0) m_bConnectState=CONNECTED;
			else CloseSocket(false);
			if (m_pIService!=NULL) m_pIService->OnSocketConnectEvent(uErrorCode,this);
			return 0;
		}
	case FD_READ:	//��ȡ����
		{
			//��ȡ��������
			int iLen=::recv(m_hSocket,(char *)(m_szBuffer+m_iReadBufLen),sizeof(m_szBuffer)-m_iReadBufLen,0);
			if (iLen==SOCKET_ERROR)
			{ 
				CloseSocket(true);
				return 0; 
			}

			//��������
			try
			{
				m_iReadBufLen+=iLen;
				BYTE szNetBuffer[MAX_SEND_SIZE+NET_HEAD_SIZE];
				do
				{
					//Ч������
					NetMessageHead * pNetHead=(NetMessageHead *)m_szBuffer;
					if ((m_iReadBufLen<sizeof(NetMessageHead))||(m_iReadBufLen<(int)pNetHead->uMessageSize)) return 0;

					//��������
					UINT uMessageSize=pNetHead->uMessageSize;
					if (uMessageSize>sizeof(szNetBuffer)) throw TEXT("���ݰ�����");
					::CopyMemory(szNetBuffer,m_szBuffer,uMessageSize);

					//ɾ������
					::MoveMemory(m_szBuffer,m_szBuffer+uMessageSize,(m_iReadBufLen-uMessageSize)*sizeof(BYTE));
					m_iReadBufLen-=uMessageSize;

					//��������
					uMessageSize-=sizeof(NetMessageHead);
					NetMessageHead * pHandleNetData=(NetMessageHead *)szNetBuffer;
					if (m_pIService->OnSocketReadEvent(pHandleNetData,uMessageSize?pHandleNetData+1:NULL,uMessageSize,this)==false)
					{
						CloseSocket(true);
						return 0;
					}
				} while ((m_iReadBufLen>0)&&(m_hSocket!=INVALID_SOCKET));
			}
			catch (...)	{ CloseSocket(true);TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__); }
			return 0;
		}
	case FD_CLOSE:	//�ر���Ϣ
		{
			CloseSocket();
			return 0;
		}
	}
	return 0;
}

//���ӷ�����
bool CTCPClientSocket::Connect(const TCHAR * szServerIP, UINT uPort)
{
	long dwServerIP=inet_addr(szServerIP);
	if (dwServerIP==INADDR_NONE)
	{
		LPHOSTENT lpHost=::gethostbyname(szServerIP);
		if (lpHost==NULL) return false;
		dwServerIP=((LPIN_ADDR)lpHost->h_addr)->s_addr;
	}
	return Connect(dwServerIP,uPort);
}

//���ӷ�����
bool CTCPClientSocket::Connect(long int dwServerIP, UINT uPort)
{
	//Ч������
	if (dwServerIP==INADDR_NONE) return false;

	//��ʼ������
	InitSocketWnd();
	m_hSocket=::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (m_hSocket==INVALID_SOCKET) return false;
	if (::WSAAsyncSelect(m_hSocket,GetSafeHwnd(),WM_SOCKET_MESSAGE,FD_READ|FD_CONNECT|FD_CLOSE)==SOCKET_ERROR) return false;

	//���ͷ�������ַ
	sockaddr_in SocketAddr;
	SocketAddr.sin_family=AF_INET;
	SocketAddr.sin_port=htons(uPort);
	SocketAddr.sin_addr.S_un.S_addr=dwServerIP;

	//���Ӳ���
	if ((::connect(m_hSocket,(sockaddr *)&SocketAddr,sizeof(SocketAddr))==SOCKET_ERROR)
		&&(::WSAGetLastError()!=WSAEWOULDBLOCK))
	{
		CloseSocket(false);
		return false;
	}

	//��������
	m_bConnectState=CONNECTING;
	return true;
}

//�ر� SOCKET
bool CTCPClientSocket::CloseSocket(bool bNotify)
{
	bool bClose=(m_hSocket!=INVALID_SOCKET);
	m_bConnectState=NO_CONNECT;
	if (m_hSocket!=INVALID_SOCKET)
	{
		::WSAAsyncSelect(m_hSocket,this->GetSafeHwnd(),WM_SOCKET_MESSAGE,0);
		::closesocket(m_hSocket);
		m_hSocket=INVALID_SOCKET;
		m_iReadBufLen=0;
	}
	if ((bNotify==true)&&(bClose==true)&&(m_pIService!=NULL)) m_pIService->OnSocketCloseEvent();
	return bClose;
}

//���ͺ���
int CTCPClientSocket::SendData(void * pData, UINT uSize, BYTE bMainID, BYTE bAssistantID, BYTE bHandleCode)
{
	if ((m_hSocket!=INVALID_SOCKET)&&(uSize<=MAX_SEND_SIZE))
	{
		//��������
		int iErrorCode=0;
		char bSendBuffer[MAX_SEND_SIZE+NET_HEAD_SIZE];
		UINT uSendSize=uSize+sizeof(NetMessageHead),uSended=0;

		//�������
		NetMessageHead * pNetHead=(NetMessageHead *)bSendBuffer;
		pNetHead->uMessageSize=uSendSize;
		pNetHead->bMainID=bMainID;
		pNetHead->bAssistantID=bAssistantID;
		pNetHead->bHandleCode=bHandleCode;
		pNetHead->bReserve = m_iCheckCode;

		if (uSize>0) ::CopyMemory(bSendBuffer+sizeof(NetMessageHead),pData,uSize);

		//��������
		do
		{
			iErrorCode=::send(m_hSocket,bSendBuffer+uSended,uSendSize-uSended,0);
			if (iErrorCode==SOCKET_ERROR) 
			{
				if (::WSAGetLastError()==WSAEWOULDBLOCK) return uSize;
				else return SOCKET_ERROR;
			}
			uSended+=iErrorCode;
		} while (uSended<uSendSize);

		return uSize;
	}
	return SOCKET_ERROR;
}

//������ͺ���
int CTCPClientSocket::SendData(BYTE bMainID, BYTE bAssistantID, BYTE bHandleCode)
{
	return SendData(NULL,0,bMainID,bAssistantID,bHandleCode);
}

//����У���룬��������Կ
void CTCPClientSocket::SetCheckCode(__int64 iCheckCode, int isecretkey)
{
	m_iCheckCode = (iCheckCode - isecretkey) / 23;
}

/**************************************************************************************************************/

//���캯��
CTCPSocket::CTCPSocket(void)
{
	m_bSending=false;
	m_uIndex=0;
	m_dwHandleID=0;
	m_lBeginTime=0;
	m_dwSendBuffLen=0;
	m_dwRecvBuffLen=0;
	m_hSocket=INVALID_SOCKET;
	m_pManage=NULL;
	memset(&m_SocketAddr,0,sizeof(m_SocketAddr));
	memset(&m_SendOverData,0,sizeof(m_SendOverData));
	memset(&m_RecvOverData,0,sizeof(m_RecvOverData));
	m_SendOverData.uOperationType=SOCKET_SND;
	m_RecvOverData.uOperationType=SOCKET_REV;
}

//��������
CTCPSocket::~CTCPSocket(void)
{
	CloseSocket();
}

//�ϲ� SOCKET
bool CTCPSocket::Attach(SOCKET hSocket, sockaddr_in & Addr, DWORD dwHandleID)
{
	//��������
	CSignedLockObject RecvLock(&m_csRecvLock,true);
	CSignedLockObject SendLock(&m_csSendLock,true);

	//Ч������ 
	if (hSocket==INVALID_SOCKET) return false;

	//��¼����
	m_bSending=false;
	m_dwSendBuffLen=0;
	m_dwRecvBuffLen=0;
	m_hSocket=hSocket;
	m_SocketAddr=Addr;
	m_dwHandleID=dwHandleID;
	m_lBeginTime=(long int)time(NULL);
	m_SendOverData.uOperationType=SOCKET_SND;
	m_RecvOverData.uOperationType=SOCKET_REV;

	return true;
}

//�ر� SOCKET
bool CTCPSocket::CloseSocket()
{
	//��������
	CSignedLockObject RecvLock(&m_csRecvLock,true);
	CSignedLockObject SendLock(&m_csSendLock,true);

	bool bClose=(m_hSocket!=INVALID_SOCKET);
	::closesocket(m_hSocket);
	m_bSending=false;
	m_dwHandleID=0;
	m_lBeginTime=0;
	m_dwSendBuffLen=0;
	m_dwRecvBuffLen=0;
	m_hSocket=INVALID_SOCKET;
	memset(&m_SocketAddr,0,sizeof(m_SocketAddr));
	memset(&m_SendOverData,0,sizeof(m_SendOverData));
	memset(&m_RecvOverData,0,sizeof(m_RecvOverData));
	m_SendOverData.uOperationType=SOCKET_SND;
	m_RecvOverData.uOperationType=SOCKET_REV;

	return bClose;
}

//�������ݺ���
int CTCPSocket::SendData(BYTE bMainID, BYTE bAssistantID, BYTE bHandleCode, DWORD dwHandleID)
{
	//��������
	CSignedLockObject SendLock(&m_csSendLock,true);

	//Ч������
	if (dwHandleID==0) dwHandleID=m_dwHandleID;
	if ((m_dwHandleID==0)||(m_hSocket==INVALID_SOCKET)||(dwHandleID!=m_dwHandleID)) return SOCKET_ERROR;
	if (sizeof(NetMessageHead)>(SED_SIZE-m_dwSendBuffLen)) return SOCKET_ERROR;

	//��������
	NetMessageHead * pNetHead=(NetMessageHead *)(m_szSendBuf+m_dwSendBuffLen);
	pNetHead->bReserve=0;
	pNetHead->bMainID=bMainID;
	pNetHead->bAssistantID=bAssistantID;
	pNetHead->bHandleCode=bHandleCode;
	pNetHead->uMessageSize=sizeof(NetMessageHead);
	m_dwSendBuffLen+=sizeof(NetMessageHead);
	return CheckSendData()?sizeof(NetMessageHead):0;
}

//�������ݺ���
int CTCPSocket::SendData(void * pData, UINT uBufLen, BYTE bMainID, BYTE bAssistantID, BYTE bHandleCode, DWORD dwHandleID)
{
	if (uBufLen<=MAX_SEND_SIZE)
	{
		//��������
		UINT uSendSize=sizeof(NetMessageHead)+uBufLen;
		CSignedLockObject SendLock(&m_csSendLock,true);

		//Ч������
		if (dwHandleID==0) dwHandleID=m_dwHandleID;
		if ((m_dwHandleID==0)||(m_hSocket==INVALID_SOCKET)||(dwHandleID!=m_dwHandleID))
		{
			////wushuqun 2009.5.22
			//::OutputDebugString("���� SendData: (m_dwHandleID==0)||(m_hSocket==INVALID_SOCKET)||(dwHandleID!=m_dwHandleID) ��������ʧ����");
			return SOCKET_ERROR;
		}
		if (uSendSize>(SED_SIZE-m_dwSendBuffLen))
		{
			//CString str;
			//str.Format("uSendSize :%d,��������С %d K,��ʹ�� %d K",
			//	uSendSize,SED_SIZE / 1024 ,m_dwSendBuffLen / 1024);
			////wushuqun 2009.5.22
			//::OutputDebugString("���� SendData: uSendSize>(SED_SIZE-m_dwSendBuffLen ��������ʧ����");
			//::OutputDebugString(str);
			return SOCKET_ERROR;
		}

		//��������
		NetMessageHead * pNetHead=(NetMessageHead *)(m_szSendBuf+m_dwSendBuffLen);
		pNetHead->bMainID=bMainID;
		pNetHead->bAssistantID=bAssistantID;
		pNetHead->bHandleCode=bHandleCode;
		pNetHead->uMessageSize=uSendSize;
		pNetHead->bReserve=0;
		if (pData!=NULL) CopyMemory(pNetHead+1,pData,uBufLen);
		m_dwSendBuffLen+=uSendSize;
		return CheckSendData()?uBufLen:0;
	
	}
	////wushuqun 2009.5.22
	//::OutputDebugString("���� SendData: uBufLen > MAX_SEND_SIZE��������ʧ����");
	return 0;
}

//�������ݺ���
int CTCPSocket::SendData(const char * pData, UINT uBufLen)
{
	if (uBufLen<=MAX_SEND_SIZE)
	{
		//��������
		CSignedLockObject SendLock(&m_csSendLock,true);

		//Ч������
		if (m_hSocket==INVALID_SOCKET)
		{
			return SOCKET_ERROR;
		}
		if (uBufLen>(SED_SIZE-m_dwSendBuffLen))
		{
			return SOCKET_ERROR;
		}

		//��������
		m_dwSendBuffLen+=uBufLen;

		CopyMemory(m_szSendBuf, pData, m_dwSendBuffLen);

		return CheckSendData()?uBufLen:0;
	}

	return 0;
}

//��ⷢ�����ݺ���
bool CTCPSocket::CheckSendData()
{
	//��������
	CSignedLockObject SendLock(&m_csSendLock,true);

	if ((m_bSending==false)&&(m_dwSendBuffLen>0))
	{
		DWORD dwThancferred=0;
		m_bSending=true;
		m_SendOverData.dwHandleID=m_dwHandleID;
		m_SendOverData.WSABuffer.buf=m_szSendBuf;
		m_SendOverData.WSABuffer.len=m_dwSendBuffLen;
		if ((::WSASend(m_hSocket,&m_SendOverData.WSABuffer,1,&dwThancferred,0,(LPWSAOVERLAPPED)&m_SendOverData,NULL)==SOCKET_ERROR)
			&&(::WSAGetLastError()!=WSA_IO_PENDING))
		{
			////wushuqun 2009.5.22
			//::OutputDebugString("���� CheckSendData: ��������ʧ����");

			m_bSending=false;
			return false;
		}
	}
	return true;
}

//������ɺ���
bool CTCPSocket::OnSendCompleted(DWORD dwThancferred, DWORD dwHandleID)
{
	CSignedLockObject SendLock(&m_csSendLock,true);
	if ((dwHandleID==0)||(m_dwHandleID!=dwHandleID)) return true;

	//��������
	m_bSending=false;
	if ((dwThancferred>0)&&(m_dwSendBuffLen>=dwThancferred))
	{
		m_dwSendBuffLen-=dwThancferred;
		::MoveMemory(m_szSendBuf,&m_szSendBuf[dwThancferred],m_dwSendBuffLen*sizeof(m_szSendBuf[0]));
		return CheckSendData();
	}

	return false;
}

//������ɺ���
bool CTCPSocket::OnRecvCompleted(DWORD dwHandleID)
{
	//��������
	CSignedLockObject RecvLock(&m_csRecvLock,true);

	//Ч������
	if ((m_dwHandleID==0)||(m_dwHandleID!=dwHandleID))	return false;

	try
	{
		//��������
		int iRecvCode=::recv(m_hSocket,m_szRecvBuf+m_dwRecvBuffLen,RCV_SIZE-m_dwRecvBuffLen,0);
			TRACE(TEXT("RECEIVE DATA SIZE:%d\n"),iRecvCode);
		if (iRecvCode>0)
		{
			//��������
			if (m_pManage->GetListenPort() == FLASH_SERVER_PORT)	
			{
				if (0 == strcmp(POLICYFILEREQUESET, m_szRecvBuf+m_dwRecvBuffLen))
				{
					m_pManage->SendData(m_uIndex, POLICYFILERESPONSE, sizeof(POLICYFILERESPONSE)+1);
				}
			}
			else
			{
				m_dwRecvBuffLen+=iRecvCode;
				NetMessageHead * pNetHead=(NetMessageHead *)m_szRecvBuf;
				if(pNetHead->bMainID==200)
				{
					m_pManage->CloseSocket(this,m_dwHandleID);
					return false;
				}
				while ((m_dwRecvBuffLen>=sizeof(NetMessageHead))&&(m_dwRecvBuffLen>=pNetHead->uMessageSize))
				{
					//Ч������
					if (pNetHead->uMessageSize<sizeof(NetMessageHead)) throw ("�Ƿ����ݰ�");

					///У����
					if (pNetHead->bReserve != (int)m_hSocket) throw("�Ƿ����ݰ�");

					//�������
					UINT uMessageSize=pNetHead->uMessageSize;
					UINT uHandleSize=uMessageSize-sizeof(NetMessageHead);
					if (uMessageSize>MAX_SEND_SIZE) throw TEXT("���ݰ�̫��");
					if (m_pManage->OnNetMessage(this,pNetHead,uHandleSize?pNetHead+1:NULL,uHandleSize,m_uIndex,m_dwHandleID)==false)
						throw TEXT("���ݴ���ʧ��");

					//ɾ����������
					::MoveMemory(m_szRecvBuf,m_szRecvBuf+uMessageSize,m_dwRecvBuffLen-uMessageSize);
					m_dwRecvBuffLen-=uMessageSize;
				}
			}
			return RecvData();
		}
	}
	catch (...) 
	{
		TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
		DWORD dwErr=::GetLastError();
	}
	m_pManage->CloseSocket(this,m_dwHandleID);

	return false;
}

//Ͷ�ݽ��� IO
bool CTCPSocket::RecvData()
{
	CSignedLockObject RecvLock(&m_csRecvLock,true);
	DWORD dwThancferred=0,dwFlags=0;
	m_RecvOverData.dwHandleID=m_dwHandleID;
	m_RecvOverData.WSABuffer.buf=m_szRecvBuf+m_dwRecvBuffLen;
	m_RecvOverData.WSABuffer.len=0;
	if ((::WSARecv(m_hSocket,&m_RecvOverData.WSABuffer,1,&dwThancferred,&dwFlags,(LPWSAOVERLAPPED)&m_RecvOverData,NULL))
		&&(::WSAGetLastError()!=WSA_IO_PENDING))
	{
		m_pManage->CloseSocket(this,m_dwHandleID);
		return false;
	}
	return true;
}

//�ж��Ƿ�����
bool CTCPSocket::IsConnectID(DWORD dwHandleID)
{
	if ((dwHandleID!=m_dwHandleID)||(m_dwHandleID==0)||(m_hSocket==INVALID_SOCKET)) return false;
	return true;
}

/**************************************************************************************************************/

//���캯��
CTCPSocketManage::CTCPSocketManage()
{
	m_bRun=false;
	m_bInit=false;
	m_bCheckConnect=true;
	m_bMaxVer=0;
	m_bLessVer=0;
	m_uListenPort=0;
	m_uRSThreadCount=0;
	m_uBatchCerrenPos=0;
	m_uBatchLineCount=0;
	m_uCheckTime=15000;			//�ʼ��15000���������˸ĳ�5000�������� fuckfuckfuck
	m_pKeep=NULL;
	m_hEventThread=NULL;
	m_hCompletionPortRS=NULL;
	m_hCompletionPortBatch=NULL;
	m_hThreadKeep=NULL;
	m_hThreadAccept=NULL;
	ZeroMemory(m_SendLine,sizeof(m_SendLine));
///	 m_CurConnectCount=0;
	return;
}

//��������
CTCPSocketManage::~CTCPSocketManage()
{
	SafeDeleteArray(m_pKeep);
	return;
}

//��ʼ��
bool CTCPSocketManage::Init(UINT uMaxCount, UINT uListenPort, BYTE bMaxVer, BYTE bLessVer, int iSecretKey, IServerSocketService * pService)
{
	//Ч�����
	if ((this==NULL)||(m_bInit==true)||(m_bRun==true)) throw new CAFCException(TEXT("CTCPSocketManage::Init ״̬Ч��ʧ��"),0x409);
	if ((uMaxCount==0)||(uListenPort==0)) throw new CAFCException(TEXT("CTCPSocketManage::Init �������Ч��ʧ��"),0x40A);

	//���ò���
	m_bInit=true;
	m_pService=pService;
	m_bMaxVer=bMaxVer;
	m_bLessVer=bLessVer;
	m_uListenPort=uListenPort;
	m_iSecretKey = iSecretKey;
	::ZeroMemory(m_SendLine,sizeof(m_SendLine));

	//�����ڴ�
	m_pKeep=new BYTE [uMaxCount];
	if (m_pKeep==NULL) throw new CAFCException(TEXT("CTCPSocketManage::Init �����ڴ�ʧ��"),0x40B);
	::ZeroMemory(m_pKeep,sizeof(BYTE)*uMaxCount);

	//���� SOCKET ����
	if (m_SocketPtrArray.Init(uMaxCount,uMaxCount)==false) throw new CAFCException(TEXT("CTCPSocket ��ʼ��ʧ��"),0x40C);
	for (UINT i=0;i<uMaxCount;i++)
	{
		m_SocketPtrArray.GetArrayItem(i)->SetIndex(i);
		m_SocketPtrArray.GetArrayItem(i)->SetSocketManagePtr(this);
	}
	return true;
}

//ȡ����ʼ��
bool CTCPSocketManage::UnInit()
{
	if (this==NULL) return false;

	//�������� 
	m_bInit=false;
	m_pService=NULL;
	m_uBatchCerrenPos=0;
	m_uBatchLineCount=0;
	m_uListenPort=0;
	ZeroMemory(m_SendLine,sizeof(m_SendLine));

	//�����ڴ�
	m_SocketPtrArray.UnInit();
	SafeDeleteArray(m_pKeep);

	return true;
}

//��ʼ����
bool CTCPSocketManage::Start(UINT uAcceptThreadCount, UINT uSocketThradCount)
{
	if ((this==NULL)||(m_bInit==false)||(m_bRun==true)) throw new CAFCException(TEXT("CTCPSocketManage::Start û�г�ʼ������"),0x40D);

	//��ȡϵͳ��Ϣ
	SYSTEM_INFO SystemInfo;
	::GetSystemInfo(&SystemInfo);
	if (uSocketThradCount==0) uSocketThradCount=SystemInfo.dwNumberOfProcessors*2;
	
	//�����¼�
	m_hEventThread=::CreateEvent(NULL,TRUE,false,NULL);
	if (m_hEventThread==NULL) throw new CAFCException(TEXT("CTCPSocketManage::Start m_hEventThread ����ʧ��"),0x40E);

	//������ɶ˿�
	m_hCompletionPortRS=::CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,NULL,SystemInfo.dwNumberOfProcessors);
	if (m_hCompletionPortRS==NULL) throw new CAFCException(TEXT("CTCPSocketManage::Start m_hCompletionPortRS ����ʧ��"),0x40F);

	//��������������ɶ˿�
	m_hCompletionPortBatch=::CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,NULL,SystemInfo.dwNumberOfProcessors);
	if (m_hCompletionPortBatch==NULL) throw new CAFCException(TEXT("CTCPSocketManage::Start m_hCompletionPortBatch ����ʧ��"),0x410);

	//��������
	UINT				uThreadID=0;
	HANDLE				hThreadHandle=NULL;
	ThreadStartStruct	ThreadStartData;
	ThreadStartData.pSocketManage=this;

	//������д�߳�
	ThreadStartData.hThreadEvent=m_hEventThread;
	ThreadStartData.hCompletionPort=m_hCompletionPortRS;
	for (UINT i=0;i<uSocketThradCount;i++)
	{
		hThreadHandle=(HANDLE)::_beginthreadex(NULL,0,ThreadRSSocket,&ThreadStartData,0,&uThreadID);
		if (hThreadHandle==NULL) throw new CAFCException(TEXT("CTCPSocketManage::Start ThreadStartData �߳̽���ʧ��"),0x411);
		m_uRSThreadCount++;
		::WaitForSingleObject(m_hEventThread,INFINITE);
		::ResetEvent(m_hEventThread);
		::CloseHandle(hThreadHandle);
	}

	//��������SOCKET
	if (!m_ListenSocket.Create())  throw new CAFCException(TEXT("CTCPSocketManage::Start ���罨��ʧ��"),0x412);
	if (!m_ListenSocket.Bind(m_uListenPort))  throw new CAFCException(TEXT("CTCPSocketManage::Start �����ʧ��"),0x413);
	if (!m_ListenSocket.Listen()) throw new CAFCException(TEXT("CTCPSocketManage::Start �������ʧ��"),0x414);

	//����Ӧ���߳�
	ThreadStartData.hCompletionPort=m_hCompletionPortRS;
	ThreadStartData.hThreadEvent=m_hEventThread;
	m_hThreadAccept=(HANDLE)::_beginthreadex(NULL,0,ThreadAccept,&ThreadStartData,0,&uThreadID);
	if (m_hThreadAccept==NULL) throw new CAFCException(TEXT("CTCPSocketManage::Start ThreadAccept �߳̽���ʧ��"),0x415);
	::WaitForSingleObject(m_hEventThread,INFINITE);
	::ResetEvent(m_hEventThread);

	//����ά���߳�
	ThreadStartData.hCompletionPort=NULL;
	ThreadStartData.hThreadEvent=m_hEventThread;
	m_hThreadKeep=(HANDLE)::_beginthreadex(NULL,0,ThreadKeepActive,&ThreadStartData,0,&uThreadID);
	if (m_hThreadKeep==NULL) throw new CAFCException(TEXT("CTCPSocketManage::Start ThreadKeepActive �߳̽���ʧ��"),0x416);
	::WaitForSingleObject(m_hEventThread,INFINITE);
	::ResetEvent(m_hEventThread);

	//�������������߳�
	ThreadStartData.hCompletionPort=m_hCompletionPortBatch;
	ThreadStartData.hThreadEvent=m_hEventThread;
	hThreadHandle=(HANDLE)::_beginthreadex(NULL,0,ThreadBatchSend,&ThreadStartData,0,&uThreadID);
	if (hThreadHandle==NULL) throw new CAFCException(TEXT("CTCPSocketManage::Start ThreadBatchSend �߳̽���ʧ��"),0x417);
	::WaitForSingleObject(m_hEventThread,INFINITE);
	::ResetEvent(m_hEventThread);

	//�ر��¼�
	m_bRun=true;
	return true;
}

//ֹͣ����
bool CTCPSocketManage::Stop()
{
	if (this==NULL) return false;

	//�ر� SOCKET
	m_bRun=false;
	m_ListenSocket.CloseSocket();

	//�˳�Ӧ���߳�
	if (m_hThreadAccept!=NULL) 
	{
		DWORD dwCode=::WaitForSingleObject(m_hThreadAccept,TIME_OUT);
		if (dwCode==WAIT_TIMEOUT) ::TerminateThread(m_hThreadAccept,1);
		::CloseHandle(m_hThreadAccept);
		m_hThreadAccept=NULL;
	}

	//�ر���ɶ˿�
	if (m_hCompletionPortRS!=NULL)
	{
		for (UINT i=0;i<m_uRSThreadCount;i++)
		{
			::PostQueuedCompletionStatus(m_hCompletionPortRS,0,NULL,NULL);
			::WaitForSingleObject(m_hEventThread,TIME_OUT);
			::ResetEvent(m_hEventThread);
		}
		m_uRSThreadCount=0;
		::CloseHandle(m_hCompletionPortRS);
		m_hCompletionPortRS=NULL;
	}

	//�ر�ά���߳�
	if (m_hThreadKeep!=NULL)
	{
		if (::WaitForSingleObject(m_hEventThread,TIME_OUT)==WAIT_TIMEOUT) ::TerminateThread(m_hThreadKeep,0);
		::CloseHandle(m_hThreadKeep);
		m_hThreadKeep=NULL;
	}

	//�ر����������߳�
	if (m_hCompletionPortBatch!=NULL)
	{
		::PostQueuedCompletionStatus(m_hCompletionPortBatch,0,NULL,NULL);
		::WaitForSingleObject(m_hEventThread,TIME_OUT);
		::ResetEvent(m_hEventThread);
		::CloseHandle(m_hCompletionPortBatch);
		m_hCompletionPortBatch=NULL;
	}

	//�ر� SOCKET
	for (UINT i=0;i<m_SocketPtrArray.GetPermitCount();i++) 
	{
		m_SocketPtrArray.GetArrayItem(i)->CloseSocket();
	}

	//�ر��¼�
	if (m_hEventThread!=NULL)
	{
		::CloseHandle(m_hEventThread);
		m_hEventThread=NULL;
	}

	return true;
}

//�������ݺ���
int CTCPSocketManage::SendData(UINT uIndex,const char * pData, UINT uBufLen)
{
	if ((uIndex<m_SocketPtrArray.GetPermitCount())&&(m_bRun==true))
	{
		if (nullptr != m_SocketPtrArray.GetArrayItem(uIndex))
		{
			return m_SocketPtrArray.GetArrayItem(uIndex)->SendData(pData,uBufLen);
		}
	}
	return 0;
}

//�������ݺ���
int CTCPSocketManage::SendData(UINT uIndex, BYTE bMainID, BYTE bAssistantID, BYTE bHandleCode, DWORD dwHandleID)
{
	if ((uIndex<m_SocketPtrArray.GetPermitCount())&&(m_bRun==true))
	{
		return m_SocketPtrArray.GetArrayItem(uIndex)->SendData(bMainID,bAssistantID,bHandleCode,dwHandleID);
	}
	return 0;
}

//�������ݺ���
int CTCPSocketManage::SendData(UINT uIndex, void * pData, UINT uBufLen, BYTE bMainID, BYTE bAssistantID, BYTE bHandleCode, DWORD dwHandleID)
{
	//::OutputDebugString("���� CTCPSocketManage::SendData: ��������-1");

	if ((uIndex<m_SocketPtrArray.GetPermitCount())&&(m_bRun==true))
	{
		return m_SocketPtrArray.GetArrayItem(uIndex)->SendData(pData,uBufLen,bMainID,bAssistantID,bHandleCode,dwHandleID);
	}
	//::OutputDebugString("���� CTCPSocketManage::SendData: ��������-2");
	return 0;
}

//�������ݺ���
int CTCPSocketManage::SendData(CTCPSocket * pSocket, void * pData, UINT uBufLen, BYTE bMainID, BYTE bAssistantID, BYTE bHandleCode, DWORD dwHandleID)
{
	if ((pSocket!=NULL)&&(m_bRun==true)) 
	{
		return pSocket->SendData(pData,uBufLen,bMainID,bAssistantID,bHandleCode,dwHandleID);
	}
	return 0;
}

//�������ͺ���
int CTCPSocketManage::SendDataBatch(void * pData, UINT uSize, BYTE bMainID, BYTE bAssistantID, BYTE bHandleCode)
{
	//Ч������
	if ((m_bRun==false)||(uSize>(sizeof(m_SendLine[0].szSendData)-sizeof(NetMessageHead)))) return 0;

	CSignedLockObject BatchLock(&m_csBacthSend,true);
	if (m_uBatchLineCount>=uBatchLineSize) return 0;

	//д�뻺��
	UINT m_uWritePos=(m_uBatchCerrenPos+m_uBatchLineCount)%uBatchLineSize;
	m_SendLine[m_uWritePos].NetHead.bMainID=bMainID;
	m_SendLine[m_uWritePos].NetHead.bAssistantID=bAssistantID;
	m_SendLine[m_uWritePos].NetHead.bHandleCode=bHandleCode;
	m_SendLine[m_uWritePos].NetHead.uMessageSize=uSize+sizeof(NetMessageHead);
	m_SendLine[m_uWritePos].NetHead.bReserve=0;
	if (uSize>0) CopyMemory(m_SendLine[m_uWritePos].szSendData,pData,uSize);

	//���������߳�
	m_uBatchLineCount++;
	PostQueuedCompletionStatus(m_hCompletionPortBatch,uSize+sizeof(NetMessageHead),NULL,NULL);
	
	return uSize;
}

//�ر�����
bool CTCPSocketManage::CloseSocket(UINT uIndex, DWORD dwHandleID)
{ 
	if (uIndex<m_SocketPtrArray.GetPermitCount()) 
	{
		return CloseSocket(m_SocketPtrArray.GetArrayItem(uIndex),dwHandleID);
	}
	return false;
}

//�ر�����
bool CTCPSocketManage::CloseSocket(CTCPSocket * pSocket, DWORD dwHandleID) 
{ 
	if (pSocket!=NULL)
	{
		CSignedLockObject RecvLock(pSocket->GetRecvLock(),true);
		CSignedLockObject SendLock(pSocket->GetSendLock(),true);

		//Ч������
		if (dwHandleID==0) dwHandleID=pSocket->m_dwHandleID;
		if ((pSocket->m_dwHandleID==0)||(dwHandleID!=pSocket->m_dwHandleID)) return false;

		//��������
		ULONG dwAccessIP=pSocket->GetConnectData();
		long int lConnectTime=(long int)time(NULL)-pSocket->GetBeginTime();
		*(m_pKeep+pSocket->m_uIndex)=0;

		//�رմ���
		if ((pSocket->CloseSocket()==true)&&(m_pService!=NULL))	m_pService->OnSocketCloseEvent(dwAccessIP,pSocket->m_uIndex,lConnectTime);
		
		//������Ϣ
		TCPSocketDelete(pSocket);

		return true;
	}
	return false;
}

//�ж��Ƿ�����
bool CTCPSocketManage::IsConnectID(UINT uIndex, DWORD dwHandleID)
{
	if (uIndex>=m_SocketPtrArray.GetPermitCount()) return false;
	return m_SocketPtrArray.GetArrayItem(uIndex)->IsConnectID(dwHandleID);
}



//��Ϣ������
bool CTCPSocketManage::OnNetMessage(CTCPSocket * pSocket, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uIndex, DWORD dwHandleID)
{
	*(m_pKeep+uIndex)=0;
	//Ч�������������
	if ((pNetHead->bMainID==MDM_CONNECT)&&(pNetHead->bAssistantID==ASS_NET_TEST)) 
	{
		//*(m_pKeep+uIndex)=0;  ��ǰ����Ƿ������,����Ӧ�����յ��κ���Ϣ��Ӧ�ð�������0
		return true;
	}
	if (m_pService!=NULL) return m_pService->OnSocketReadEvent(pSocket,pNetHead,pData,uSize,uIndex,dwHandleID);
	return false;
}


//SOCKET ���ݽ����߳�
unsigned __stdcall CTCPSocketManage::ThreadRSSocket(LPVOID pThreadData)
{
	//���ݶ���
	ThreadStartStruct	* pStartData=(ThreadStartStruct *)pThreadData;			//�߳���������ָ��
	CTCPSocketManage	* pSocketManage=pStartData->pSocketManage;				//����ָ��
	HANDLE				hCompletionPort=pStartData->hCompletionPort;			//��ɶ˿�
	HANDLE				hEvent=pStartData->hThreadEvent;						//�¼�

	//�߳����ݶ�ȡ���
	::SetEvent(hEvent);

	//�ص�����
	DWORD							dwThancferred=0;							//��������
	CTCPSocket						* pTCPSocket=NULL;							//��ɼ�
	CTCPSocket::OverLappedStruct	* pOverData=NULL;							//�ص�����

	while (1)
	{
		try
		{
			//�ȴ���ɶ˿�
			dwThancferred=0;
			pTCPSocket=NULL;
			pOverData=NULL;
			::GetQueuedCompletionStatus(hCompletionPort,&dwThancferred,(PULONG_PTR)&pTCPSocket,(LPOVERLAPPED *)&pOverData,INFINITE);
			if ((pTCPSocket==NULL)||(pOverData==NULL))
			{
				if ((pTCPSocket==NULL)&&(pOverData==NULL)) ::SetEvent(hEvent);
				_endthreadex(0);
			}

			//������ɶ˿�
			if ((dwThancferred==0)&&(pOverData->uOperationType==SOCKET_SND))
			{
				//SOCKET �ر�
				pSocketManage->CloseSocket(pTCPSocket,pOverData->dwHandleID);
				continue;
			}

			switch (pOverData->uOperationType)
			{
			case SOCKET_REV:	//SOCKET ���ݶ�ȡ
				{
					pTCPSocket->OnRecvCompleted(pOverData->dwHandleID);
					break;
				}
			case SOCKET_SND:	//SOCKET ���ݷ���
				{
					pTCPSocket->OnSendCompleted(dwThancferred,pOverData->dwHandleID);
					break;
				}
			}
		}
		catch (...) 
		{
			TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
		}
	}

	return 0;
}

//SOCKET �������������߳�
unsigned __stdcall CTCPSocketManage::ThreadBatchSend(LPVOID pThreadData)
{
	//���ݶ���
	ThreadStartStruct		* pStartData=(ThreadStartStruct *)pThreadData;					//�߳���������ָ��
	CTCPSocketManage		* pSocketManage=pStartData->pSocketManage;						//����ָ��
	UINT					uMaxCount=pSocketManage->m_SocketPtrArray.GetPermitCount();		//�����Ŀ
	HANDLE					hCompletionPort=pStartData->hCompletionPort;					//��ɶ˿�
	HANDLE					hEvent=pStartData->hThreadEvent;								//�¼�
	
	//�������
	SetEvent(pStartData->hThreadEvent);


	//��ʱ����
	NetMessageHead			* pNetHead=NULL;												//���ݰ�ͷ
	CTCPSocket				* pSendSocket=pSocketManage->m_SocketPtrArray.GetArrayItem(0);	//���� SOCKET
	UINT					* puSendCount=&pSocketManage->m_uBatchLineCount;				//��ǰ����

	DWORD					dwThancferred=0;												//��������
	ULONG					dwCompleteKey=0L;												//�ص� IO ��ʱ����
	LPOVERLAPPED			OverData;														//�ص� IO ��ʱ����

	while (1)
	{
		try
		{
			//��ȡ��������
			dwThancferred=0;
			GetQueuedCompletionStatus(hCompletionPort,&dwThancferred,&dwCompleteKey,(LPOVERLAPPED *)&OverData,INFINITE);
			if (dwThancferred==0)
			{
				SetEvent(hEvent);
				_endthreadex(0);
			}

			//��������
			BatchSendLineStruct * pBatchData=&pSocketManage->m_SendLine[pSocketManage->m_uBatchCerrenPos];
			for (UINT i=0;i<uMaxCount;i++) 
			{
				if ((pSendSocket+i)->IsConnect())
				{
					(pSendSocket+i)->SendData(pBatchData->szSendData,pBatchData->NetHead.uMessageSize-sizeof(NetMessageHead),
						pBatchData->NetHead.bMainID,pBatchData->NetHead.bAssistantID,pBatchData->NetHead.bHandleCode,0);
				}
			}

			//��������
			{
				CSignedLockObject BatchLock(&pSocketManage->m_csBacthSend,true);
				pSocketManage->m_uBatchCerrenPos=(pSocketManage->m_uBatchCerrenPos+1)%uBatchLineSize;
				pSocketManage->m_uBatchLineCount--;
			}
		}
		catch (...) {TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);}
	}

	return 0;
}

//SOCKET ά���߳�
unsigned __stdcall CTCPSocketManage::ThreadKeepActive(LPVOID pThreadData)
{
	//���ݶ���
	ThreadStartStruct		* pStartData=(ThreadStartStruct *)pThreadData;		//����ָ��
	CTCPSocketManage		* pSocketManage=pStartData->pSocketManage;			//����ָ��
	HANDLE					m_hThreadEvent=pStartData->hThreadEvent;			//�߳��¼�
	
	//�������
	::SetEvent(m_hThreadEvent);

	//���ݶ���
	UINT uCheckCount=0;
	::Sleep(pSocketManage->m_uCheckTime);

	while (1)
	{
		//���Ͳ�������
		pSocketManage->SendDataBatch(NULL,0,MDM_CONNECT,ASS_NET_TEST,0);

		//����˳���־
		uCheckCount=0;
		while (uCheckCount<pSocketManage->m_uCheckTime)
		{
			if (!pSocketManage->m_bRun) 
			{
				SetEvent(m_hThreadEvent);
				_endthreadex(0);
			}
			::Sleep(1000);
			uCheckCount+=1000;
		}

		//Ч����������
		if ((pSocketManage->m_bCheckConnect)&&(pSocketManage->m_bRun)&&(pSocketManage->m_SocketPtrArray.GetArrayItem(0)!=NULL))
		{
			for (int i=(pSocketManage->m_SocketPtrArray.GetPermitCount()-1);i>=0;i--)
			{
				if (pSocketManage->m_SocketPtrArray.GetArrayItem(i)->IsConnect())
				{
					if ((*(pSocketManage->m_pKeep+i))>=3) //�������3�μ�������Ͽ��ÿͻ�����
						pSocketManage->CloseSocket(i,0);
					else 
						(*(pSocketManage->m_pKeep+i))++;//С��3�ζ��������������+1
				}
			}
		}
	}

	return 0;
}

//��ȡʱ�亯��
unsigned __int64 CTCPSocketManage::AFCGetTimer()
{
	_asm _emit 0x0F;
	_asm _emit 0x31;
}

//��ȡ���� ID ����
DWORD CTCPSocketManage::GetHandleID()
{
	static long int dwBaseID=1L;
	if (dwBaseID>3000000L) dwBaseID=1L;
	return ::InterlockedIncrement(&dwBaseID);
}

//��ȡ���� IP ��ַ
bool CTCPSocketManage::GetLoaclIPAddr(TCHAR szAddrBuffer[], UINT uStation)
{
	if (szAddrBuffer==NULL) return false;

	TCHAR szHostName[51];
	::gethostname(szHostName,sizeof(szHostName));
	HOSTENT * pHostInfo=::gethostbyname(szHostName);
	if (pHostInfo!=NULL)
	{
		LPIN_ADDR * pAddrList=(LPIN_ADDR *)(pHostInfo->h_addr_list); 
		LPIN_ADDR In_Addr=*pAddrList;

		UINT uCount=0;
		szAddrBuffer[0]=0;
		while (In_Addr!=NULL)
		{
			if (uCount==uStation)
			{
				lstrcpy(szAddrBuffer,inet_ntoa(*In_Addr));
				return true;
			}
			uCount++;
			pAddrList++;
			In_Addr=*pAddrList;
		}
	}
	return false;
}

//��ֵ�� IP �ַ�
TCHAR * CTCPSocketManage::ULongToIP(ULONG dwIP, TCHAR * szIP)
{
	wsprintf(szIP,TEXT("%d.%d.%d.%d"),FOURTH_IPADDRESS(dwIP),THIRD_IPADDRESS(dwIP),SECOND_IPADDRESS(dwIP),FIRST_IPADDRESS(dwIP));
	return szIP;
}

//��ȡָ��index��������Ϣ
string CTCPSocketManage::GetServerInfo(UINT uIndex)
{
	string s = "";
	for (UINT i=0;i<m_SocketPtrArray.GetPermitCount();i++) 
	{
		if(m_SocketPtrArray.GetArrayItem(i)->m_uIndex == uIndex)
		{
			//memcpy(pSocket, &(m_SocketPtrArray.GetArrayItem(i)->m_SocketAddr), sizeof(sockaddr_in));
			s = inet_ntoa(m_SocketPtrArray.GetArrayItem(i)->m_SocketAddr.sin_addr);
			return s;
		}
	}
	return s;
}

/**************************************************************************************************************/
//////////////////////////////////////////////////////////////
// ����ΪרΪZ������׼����Socket���ʵ��

/**************************************************************************************************************/
//���ɿ��� SOCKET
CTCPSocketForZ * CTCPSocketManageForZ::TCPSocketNew()
{
	////if(m_SocketPtrArray.GetActiveCount() > MaxConnectCount)return NULL;
	if (m_bRun)
	{
		CSignedLockObject LockObject(m_SocketPtrArray.GetArrayLock(),true);
		return m_SocketPtrArray.NewItem();
	}
	return NULL;
}


//�ͷŻ SOCKET
bool CTCPSocketManageForZ::TCPSocketDelete(CTCPSocketForZ * pSocket)
{
	if (pSocket!=NULL)
	{
		CSignedLockObject LockObject(m_SocketPtrArray.GetArrayLock(),true);
		pSocket->CloseSocket();
		return m_SocketPtrArray.FreeItem(pSocket);
	}
	return false;
}



//SOCKET ����Ӧ���߳�
unsigned __stdcall CTCPSocketManageForZ::ThreadAccept(LPVOID pThreadData)
{
	//���ݶ���
	ThreadStartStruct	* pStartData=(ThreadStartStruct *)pThreadData;			//�߳���������ָ��
	CTCPSocketManageForZ	* pSocketManage=pStartData->pSocketManage;				//����ָ��
	HANDLE				hCompletionPort=pStartData->hCompletionPort;			//��ɶ˿�

	sockaddr_in			SocketAddr;
	int					iAddrBuferLen=sizeof(SocketAddr);
	SOCKET				hSocket=INVALID_SOCKET;
	CTCPSocketForZ			* pNewTCPSocket=NULL;
	HANDLE				hAcceptCompletePort=NULL;
	SOCKET				hListenScoket=pStartData->pSocketManage->m_ListenSocket.GetSafeSocket();

	//���ӷ�������
	MSG_S_ConnectSuccess ConncetSuccess;
	ConncetSuccess.bMaxVer=pSocketManage->m_bMaxVer;
	ConncetSuccess.bLessVer=pSocketManage->m_bLessVer;

	//�߳����ݶ�ȡ���
	SetEvent(pStartData->hThreadEvent);

	while (1)
	{
		try
		{

			//��������
			hSocket=::WSAAccept(hListenScoket,(sockaddr *)&SocketAddr,&iAddrBuferLen,NULL,NULL);
			if (hSocket==INVALID_SOCKET) 
			{
				int iErrorCode=WSAGetLastError();
				_endthreadex(0);
			}

			//��������
			pNewTCPSocket=pSocketManage->TCPSocketNew();
			if ((pNewTCPSocket!=NULL)&&(pNewTCPSocket->Attach(hSocket,SocketAddr,GetHandleID())))
			{
				hAcceptCompletePort=::CreateIoCompletionPort((HANDLE)hSocket,hCompletionPort,(ULONG_PTR)pNewTCPSocket,0);
				if ((hAcceptCompletePort==NULL)||(!pNewTCPSocket->RecvData())) throw TEXT("Accept False");

				//�������ӳɹ���Ϣ

				MSG_S_ConnectSuccess Message;
				Message.bLessVer=MAKELONG(3,4);
				Message.bReserve[0]=0;
				Message.bMaxVer=MAKELONG(3,4);
				Message.bReserve[1]=0;
				//�˴���hSocket���м��ܣ��ɿͻ��˽��ܲ��ڰ�ͷ��bReserve�ֶ��з�����У�顣����SECRET_KEYΪ��Կ�ɿͻ��Լ�������
				Message.i64CheckCode = (int)hSocket * 23 + pSocketManage->m_iSecretKey;

				pNewTCPSocket->SendData(&Message,sizeof(Message),MDM_CONNECT,ASS_CONNECT_SUCCESS,0,pNewTCPSocket->GetHandleID());

			}
			else
			{
				//û�п��е�SOCKET�ˣ��ж�Ϊ������
				NetMessageHead netHead;
				ZeroMemory(&netHead,sizeof(NetMessageHead));
				netHead.bMainID=100;//MDM_GR_LOGON
				netHead.bAssistantID=3;//ASS_GR_LOGON_ERROR
				netHead.bHandleCode=10;//ERR_GR_PEOPLE_FULL
				netHead.uMessageSize=sizeof(NetMessageHead);
				netHead.bReserve=0;

				sendto(hSocket,(char *)&netHead,sizeof(NetMessageHead),0,(sockaddr*)&SocketAddr,sizeof(SocketAddr));
				throw TEXT("Accept False");
			}
		}
		catch (...)
		{TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
		::closesocket(hSocket);
		if (pNewTCPSocket!=NULL) pSocketManage->TCPSocketDelete(pNewTCPSocket);
		}
	}

	return 0;
}

//���캯��
CTCPSocketForZ::CTCPSocketForZ(void)
{
	m_bSending=false;
	m_uIndex=0;
	m_dwHandleID=0;
	m_lBeginTime=0;
	m_dwSendBuffLen=0;
	m_dwRecvBuffLen=0;
	m_hSocket=INVALID_SOCKET;
	m_pManage=NULL;
	memset(&m_SocketAddr,0,sizeof(m_SocketAddr));
	memset(&m_SendOverData,0,sizeof(m_SendOverData));
	memset(&m_RecvOverData,0,sizeof(m_RecvOverData));
	m_SendOverData.uOperationType=SOCKET_SND;
	m_RecvOverData.uOperationType=SOCKET_REV;
}

//��������
CTCPSocketForZ::~CTCPSocketForZ(void)
{
	CloseSocket();
}

//�ϲ� SOCKET
bool CTCPSocketForZ::Attach(SOCKET hSocket, sockaddr_in & Addr, DWORD dwHandleID)
{
	//��������
	CSignedLockObject RecvLock(&m_csRecvLock,true);
	CSignedLockObject SendLock(&m_csSendLock,true);

	//Ч������ 
	if (hSocket==INVALID_SOCKET) return false;

	//��¼����
	m_bSending=false;
	m_dwSendBuffLen=0;
	m_dwRecvBuffLen=0;
	m_hSocket=hSocket;
	m_SocketAddr=Addr;
	m_dwHandleID=dwHandleID;
	m_lBeginTime=(long int)time(NULL);
	m_SendOverData.uOperationType=SOCKET_SND;
	m_RecvOverData.uOperationType=SOCKET_REV;

	return true;
}

//�ر� SOCKET
bool CTCPSocketForZ::CloseSocket()
{
	//��������
	CSignedLockObject RecvLock(&m_csRecvLock,true);
	CSignedLockObject SendLock(&m_csSendLock,true);

	bool bClose=(m_hSocket!=INVALID_SOCKET);
	::closesocket(m_hSocket);
	m_bSending=false;
	m_dwHandleID=0;
	m_lBeginTime=0;
	m_dwSendBuffLen=0;
	m_dwRecvBuffLen=0;
	m_hSocket=INVALID_SOCKET;
	memset(&m_SocketAddr,0,sizeof(m_SocketAddr));
	memset(&m_SendOverData,0,sizeof(m_SendOverData));
	memset(&m_RecvOverData,0,sizeof(m_RecvOverData));
	m_SendOverData.uOperationType=SOCKET_SND;
	m_RecvOverData.uOperationType=SOCKET_REV;

	return bClose;
}

//�������ݺ���
int CTCPSocketForZ::SendData(BYTE bMainID, BYTE bAssistantID, BYTE bHandleCode, DWORD dwHandleID)
{
	//��������
	CSignedLockObject SendLock(&m_csSendLock,true);

	//Ч������
	if (dwHandleID==0) dwHandleID=m_dwHandleID;
	if ((m_dwHandleID==0)||(m_hSocket==INVALID_SOCKET)||(dwHandleID!=m_dwHandleID)) return SOCKET_ERROR;
	if (sizeof(NetMessageHead)>(SED_SIZE_Z-m_dwSendBuffLen)) return SOCKET_ERROR;

	//��������
	NetMessageHead * pNetHead=(NetMessageHead *)(m_szSendBuf+m_dwSendBuffLen);
	pNetHead->bReserve=0;
	pNetHead->bMainID=bMainID;
	pNetHead->bAssistantID=bAssistantID;
	pNetHead->bHandleCode=bHandleCode;
	pNetHead->uMessageSize=sizeof(NetMessageHead);
	m_dwSendBuffLen+=sizeof(NetMessageHead);
	return CheckSendData()?sizeof(NetMessageHead):0;
}

//�������ݺ���
int CTCPSocketForZ::SendData(void * pData, UINT uBufLen, BYTE bMainID, BYTE bAssistantID, BYTE bHandleCode, DWORD dwHandleID)
{
	if (uBufLen<=MAX_SEND_SIZE)
	{
		//��������
		UINT uSendSize=sizeof(NetMessageHead)+uBufLen;
		CSignedLockObject SendLock(&m_csSendLock,true);

		//Ч������
		if (dwHandleID==0) dwHandleID=m_dwHandleID;
		if ((m_dwHandleID==0)||(m_hSocket==INVALID_SOCKET)||(dwHandleID!=m_dwHandleID)) return SOCKET_ERROR;
		if (uSendSize>(SED_SIZE_Z-m_dwSendBuffLen)) return SOCKET_ERROR;

		//��������
		NetMessageHead * pNetHead=(NetMessageHead *)(m_szSendBuf+m_dwSendBuffLen);
		pNetHead->bMainID=bMainID;
		pNetHead->bAssistantID=bAssistantID;
		pNetHead->bHandleCode=bHandleCode;
		pNetHead->uMessageSize=uSendSize;
		pNetHead->bReserve=0;
		if (pData!=NULL) CopyMemory(pNetHead+1,pData,uBufLen);
		m_dwSendBuffLen+=uSendSize;
		return CheckSendData()?uBufLen:0;
	}
	return 0;
}

//��ⷢ�����ݺ���
bool CTCPSocketForZ::CheckSendData()
{
	//��������
	CSignedLockObject SendLock(&m_csSendLock,true);

	if ((m_bSending==false)&&(m_dwSendBuffLen>0))
	{
		DWORD dwThancferred=0;
		m_bSending=true;
		m_SendOverData.dwHandleID=m_dwHandleID;
		m_SendOverData.WSABuffer.buf=m_szSendBuf;
		m_SendOverData.WSABuffer.len=m_dwSendBuffLen;
		if ((::WSASend(m_hSocket,&m_SendOverData.WSABuffer,1,&dwThancferred,0,(LPWSAOVERLAPPED)&m_SendOverData,NULL)==SOCKET_ERROR)
			&&(::WSAGetLastError()!=WSA_IO_PENDING))
		{
			m_bSending=false;
			return false;
		}
	}
	else
	{
		return true;
	}
	return true;
}

//������ɺ���
bool CTCPSocketForZ::OnSendCompleted(DWORD dwThancferred, DWORD dwHandleID)
{
	CSignedLockObject SendLock(&m_csSendLock,true);
	if ((dwHandleID==0)||(m_dwHandleID!=dwHandleID)) return true;

	//��������
	m_bSending=false;
	if ((dwThancferred>0)&&(m_dwSendBuffLen>=dwThancferred))
	{
		m_dwSendBuffLen-=dwThancferred;
		::MoveMemory(m_szSendBuf,&m_szSendBuf[dwThancferred],m_dwSendBuffLen*sizeof(m_szSendBuf[0]));
		return CheckSendData();
	}

	return false;
}

//������ɺ���
bool CTCPSocketForZ::OnRecvCompleted(DWORD dwHandleID)
{
	//��������
	CSignedLockObject RecvLock(&m_csRecvLock,true);

	//Ч������
	if ((m_dwHandleID==0)||(m_dwHandleID!=dwHandleID))	return false;

	try
	{
		//��������
		int iRecvCode=::recv(m_hSocket,m_szRecvBuf+m_dwRecvBuffLen,RCV_SIZE_Z-m_dwRecvBuffLen,0);
		TRACE(TEXT("RECEIVE DATA SIZE:%d\n"),iRecvCode);
		if (iRecvCode>0)
		{
			//��������
			m_dwRecvBuffLen+=iRecvCode;
			NetMessageHead * pNetHead=(NetMessageHead *)m_szRecvBuf;
			if(pNetHead->bMainID==200)
			{
				m_pManage->CloseSocket(this,m_dwHandleID);
				return false;
			}
			while ((m_dwRecvBuffLen>=sizeof(NetMessageHead))&&(m_dwRecvBuffLen>=pNetHead->uMessageSize))
			{
				//Ч������
				if (pNetHead->uMessageSize<sizeof(NetMessageHead)) throw ("�Ƿ����ݰ�");
				///У����
				if (pNetHead->bReserve != (int)m_hSocket) throw("�Ƿ����ݰ�");

				//�������
				UINT uMessageSize=pNetHead->uMessageSize;
				UINT uHandleSize=uMessageSize-sizeof(NetMessageHead);
				if (uMessageSize>MAX_SEND_SIZE) throw TEXT("���ݰ�̫��");
				if (m_pManage->OnNetMessage(this,pNetHead,uHandleSize?pNetHead+1:NULL,uHandleSize,m_uIndex,m_dwHandleID)==false)
					throw TEXT("���ݴ���ʧ��");

				//ɾ����������
				::MoveMemory(m_szRecvBuf,m_szRecvBuf+uMessageSize,m_dwRecvBuffLen-uMessageSize);
				m_dwRecvBuffLen-=uMessageSize;
			}
			return RecvData();
		}
	}
	catch (...) 
	{
		TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
		DWORD dwErr=::GetLastError();
	}
	m_pManage->CloseSocket(this,m_dwHandleID);

	return false;
}

//Ͷ�ݽ��� IO
bool CTCPSocketForZ::RecvData()
{
	CSignedLockObject RecvLock(&m_csRecvLock,true);
	DWORD dwThancferred=0,dwFlags=0;
	m_RecvOverData.dwHandleID=m_dwHandleID;
	m_RecvOverData.WSABuffer.buf=m_szRecvBuf+m_dwRecvBuffLen;
	m_RecvOverData.WSABuffer.len=0;
	if ((::WSARecv(m_hSocket,&m_RecvOverData.WSABuffer,1,&dwThancferred,&dwFlags,(LPWSAOVERLAPPED)&m_RecvOverData,NULL))
		&&(::WSAGetLastError()!=WSA_IO_PENDING))
	{
		m_pManage->CloseSocket(this,m_dwHandleID);
		return false;
	}
	return true;
}

//�ж��Ƿ�����
bool CTCPSocketForZ::IsConnectID(DWORD dwHandleID)
{
	if ((dwHandleID!=m_dwHandleID)||(m_dwHandleID==0)||(m_hSocket==INVALID_SOCKET)) return false;
	return true;
}

/**************************************************************************************************************/

//���캯��
CTCPSocketManageForZ::CTCPSocketManageForZ()
{
	m_bRun=false;
	m_bInit=false;
	m_bCheckConnect=true;
	m_bMaxVer=0;
	m_bLessVer=0;
	m_uListenPort=0;
	m_uRSThreadCount=0;
	m_uBatchCerrenPos=0;
	m_uBatchLineCount=0;
	m_uCheckTime=15000;			//�ʼ��15000���������˸ĳ�5000�������� fuckfuckfuck
	m_pKeep=NULL;
	m_hEventThread=NULL;
	m_hCompletionPortRS=NULL;
	m_hCompletionPortBatch=NULL;
	m_hThreadKeep=NULL;
	m_hThreadAccept=NULL;
	ZeroMemory(m_SendLine,sizeof(m_SendLine));
	///	 m_CurConnectCount=0;
	return;
}

//��������
CTCPSocketManageForZ::~CTCPSocketManageForZ()
{
	SafeDeleteArray(m_pKeep);
	return;
}

//��ʼ��
bool CTCPSocketManageForZ::Init(UINT uMaxCount, UINT uListenPort, BYTE bMaxVer, BYTE bLessVer, int iSecretKey, IServerSocketServiceForZ * pService)
{
	//Ч�����
	if ((this==NULL)||(m_bInit==true)||(m_bRun==true)) throw new CAFCException(TEXT("CTCPSocketManageForZ::Init ״̬Ч��ʧ��"),0x409);
	if ((uMaxCount==0)||(uListenPort==0)) throw new CAFCException(TEXT("CTCPSocketManageForZ::Init �������Ч��ʧ��"),0x40A);

	//���ò���
	m_bInit=true;
	m_pService=pService;
	m_bMaxVer=bMaxVer;
	m_bLessVer=bLessVer;
	m_uListenPort=uListenPort;
	m_iSecretKey = iSecretKey;
	::ZeroMemory(m_SendLine,sizeof(m_SendLine));

	//�����ڴ�
	m_pKeep=new BYTE [uMaxCount];
	if (m_pKeep==NULL) throw new CAFCException(TEXT("CTCPSocketManageForZ::Init �����ڴ�ʧ��"),0x40B);
	::ZeroMemory(m_pKeep,sizeof(BYTE)*uMaxCount);

	//���� SOCKET ����
	if (m_SocketPtrArray.Init(uMaxCount,uMaxCount)==false) throw new CAFCException(TEXT("CTCPSocketForZ ��ʼ��ʧ��"),0x40C);
	for (UINT i=0;i<uMaxCount;i++)
	{
		m_SocketPtrArray.GetArrayItem(i)->SetIndex(i);
		m_SocketPtrArray.GetArrayItem(i)->SetSocketManagePtr(this);
	}
	return true;
}

//ȡ����ʼ��
bool CTCPSocketManageForZ::UnInit()
{
	if (this==NULL) return false;

	//�������� 
	m_bInit=false;
	m_pService=NULL;
	m_uBatchCerrenPos=0;
	m_uBatchLineCount=0;
	m_uListenPort=0;
	ZeroMemory(m_SendLine,sizeof(m_SendLine));

	//�����ڴ�
	m_SocketPtrArray.UnInit();
	SafeDeleteArray(m_pKeep);

	return true;
}

//��ʼ����
bool CTCPSocketManageForZ::Start(UINT uAcceptThreadCount, UINT uSocketThradCount)
{
	if ((this==NULL)||(m_bInit==false)||(m_bRun==true)) throw new CAFCException(TEXT("CTCPSocketManageForZ::Start û�г�ʼ������"),0x40D);

	//��ȡϵͳ��Ϣ
	SYSTEM_INFO SystemInfo;
	::GetSystemInfo(&SystemInfo);
	if (uSocketThradCount==0) uSocketThradCount=SystemInfo.dwNumberOfProcessors*2;

	//�����¼�
	m_hEventThread=::CreateEvent(NULL,TRUE,false,NULL);
	if (m_hEventThread==NULL) throw new CAFCException(TEXT("CTCPSocketManageForZ::Start m_hEventThread ����ʧ��"),0x40E);

	//������ɶ˿�
	m_hCompletionPortRS=::CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,NULL,SystemInfo.dwNumberOfProcessors);
	if (m_hCompletionPortRS==NULL) throw new CAFCException(TEXT("CTCPSocketManageForZ::Start m_hCompletionPortRS ����ʧ��"),0x40F);

	//��������������ɶ˿�
	m_hCompletionPortBatch=::CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,NULL,SystemInfo.dwNumberOfProcessors);
	if (m_hCompletionPortBatch==NULL) throw new CAFCException(TEXT("CTCPSocketManageForZ::Start m_hCompletionPortBatch ����ʧ��"),0x410);

	//��������
	UINT				uThreadID=0;
	HANDLE				hThreadHandle=NULL;
	ThreadStartStruct	ThreadStartData;
	ThreadStartData.pSocketManage=this;

	//������д�߳�
	ThreadStartData.hThreadEvent=m_hEventThread;
	ThreadStartData.hCompletionPort=m_hCompletionPortRS;
	for (UINT i=0;i<uSocketThradCount;i++)
	{
		hThreadHandle=(HANDLE)::_beginthreadex(NULL,0,ThreadRSSocket,&ThreadStartData,0,&uThreadID);
		if (hThreadHandle==NULL) throw new CAFCException(TEXT("CTCPSocketManageForZ::Start ThreadStartData �߳̽���ʧ��"),0x411);
		m_uRSThreadCount++;
		::WaitForSingleObject(m_hEventThread,INFINITE);
		::ResetEvent(m_hEventThread);
		::CloseHandle(hThreadHandle);
	}

	//��������SOCKET
	if (!m_ListenSocket.Create())  throw new CAFCException(TEXT("CTCPSocketManageForZ::Start ���罨��ʧ��"),0x412);
	if (!m_ListenSocket.Bind(m_uListenPort))  throw new CAFCException(TEXT("CTCPSocketManageForZ::Start �����ʧ��"),0x413);
	if (!m_ListenSocket.Listen()) throw new CAFCException(TEXT("CTCPSocketManageForZ::Start �������ʧ��"),0x414);

	//����Ӧ���߳�
	ThreadStartData.hCompletionPort=m_hCompletionPortRS;
	ThreadStartData.hThreadEvent=m_hEventThread;
	m_hThreadAccept=(HANDLE)::_beginthreadex(NULL,0,ThreadAccept,&ThreadStartData,0,&uThreadID);
	if (m_hThreadAccept==NULL) throw new CAFCException(TEXT("CTCPSocketManageForZ::Start ThreadAccept �߳̽���ʧ��"),0x415);
	::WaitForSingleObject(m_hEventThread,INFINITE);
	::ResetEvent(m_hEventThread);

	//����ά���߳�
	ThreadStartData.hCompletionPort=NULL;
	ThreadStartData.hThreadEvent=m_hEventThread;
	m_hThreadKeep=(HANDLE)::_beginthreadex(NULL,0,ThreadKeepActive,&ThreadStartData,0,&uThreadID);
	if (m_hThreadKeep==NULL) throw new CAFCException(TEXT("CTCPSocketManageForZ::Start ThreadKeepActive �߳̽���ʧ��"),0x416);
	::WaitForSingleObject(m_hEventThread,INFINITE);
	::ResetEvent(m_hEventThread);

	//�������������߳�
	ThreadStartData.hCompletionPort=m_hCompletionPortBatch;
	ThreadStartData.hThreadEvent=m_hEventThread;
	hThreadHandle=(HANDLE)::_beginthreadex(NULL,0,ThreadBatchSend,&ThreadStartData,0,&uThreadID);
	if (hThreadHandle==NULL) throw new CAFCException(TEXT("CTCPSocketManageForZ::Start ThreadBatchSend �߳̽���ʧ��"),0x417);
	::WaitForSingleObject(m_hEventThread,INFINITE);
	::ResetEvent(m_hEventThread);

	//�ر��¼�
	m_bRun=true;
	return true;
}

//ֹͣ����
bool CTCPSocketManageForZ::Stop()
{
	if (this==NULL) return false;

	//�ر� SOCKET
	m_bRun=false;
	m_ListenSocket.CloseSocket();

	//�˳�Ӧ���߳�
	if (m_hThreadAccept!=NULL) 
	{
		DWORD dwCode=::WaitForSingleObject(m_hThreadAccept,TIME_OUT);
		if (dwCode==WAIT_TIMEOUT) ::TerminateThread(m_hThreadAccept,1);
		::CloseHandle(m_hThreadAccept);
		m_hThreadAccept=NULL;
	}

	//�ر���ɶ˿�
	if (m_hCompletionPortRS!=NULL)
	{
		for (UINT i=0;i<m_uRSThreadCount;i++)
		{
			::PostQueuedCompletionStatus(m_hCompletionPortRS,0,NULL,NULL);
			::WaitForSingleObject(m_hEventThread,TIME_OUT);
			::ResetEvent(m_hEventThread);
		}
		m_uRSThreadCount=0;
		::CloseHandle(m_hCompletionPortRS);
		m_hCompletionPortRS=NULL;
	}

	//�ر�ά���߳�
	if (m_hThreadKeep!=NULL)
	{
		if (::WaitForSingleObject(m_hEventThread,TIME_OUT)==WAIT_TIMEOUT) ::TerminateThread(m_hThreadKeep,0);
		::CloseHandle(m_hThreadKeep);
		m_hThreadKeep=NULL;
	}

	//�ر����������߳�
	if (m_hCompletionPortBatch!=NULL)
	{
		::PostQueuedCompletionStatus(m_hCompletionPortBatch,0,NULL,NULL);
		::WaitForSingleObject(m_hEventThread,TIME_OUT);
		::ResetEvent(m_hEventThread);
		::CloseHandle(m_hCompletionPortBatch);
		m_hCompletionPortBatch=NULL;
	}

	//�ر� SOCKET
	for (UINT i=0;i<m_SocketPtrArray.GetPermitCount();i++) 
	{
		m_SocketPtrArray.GetArrayItem(i)->CloseSocket();
	}

	//�ر��¼�
	if (m_hEventThread!=NULL)
	{
		::CloseHandle(m_hEventThread);
		m_hEventThread=NULL;
	}

	return true;
}

//�������ݺ���
int CTCPSocketManageForZ::SendData(UINT uIndex, BYTE bMainID, BYTE bAssistantID, BYTE bHandleCode, DWORD dwHandleID)
{
	if ((uIndex<m_SocketPtrArray.GetPermitCount())&&(m_bRun==true))
	{
		return m_SocketPtrArray.GetArrayItem(uIndex)->SendData(bMainID,bAssistantID,bHandleCode,dwHandleID);
	}
	return 0;
}

//�������ݺ���
int CTCPSocketManageForZ::SendData(UINT uIndex, void * pData, UINT uBufLen, BYTE bMainID, BYTE bAssistantID, BYTE bHandleCode, DWORD dwHandleID)
{
	if ((uIndex<m_SocketPtrArray.GetPermitCount())&&(m_bRun==true))
	{
		return m_SocketPtrArray.GetArrayItem(uIndex)->SendData(pData,uBufLen,bMainID,bAssistantID,bHandleCode,dwHandleID);
	}
	return 0;
}

//�������ݺ���
int CTCPSocketManageForZ::SendData(CTCPSocketForZ * pSocket, void * pData, UINT uBufLen, BYTE bMainID, BYTE bAssistantID, BYTE bHandleCode, DWORD dwHandleID)
{
	if ((pSocket!=NULL)&&(m_bRun==true)) 
	{
		return pSocket->SendData(pData,uBufLen,bMainID,bAssistantID,bHandleCode,dwHandleID);
	}
	return 0;
}

//�������ͺ���
int CTCPSocketManageForZ::SendDataBatch(void * pData, UINT uSize, BYTE bMainID, BYTE bAssistantID, BYTE bHandleCode)
{
	//Ч������
	if ((m_bRun==false)||(uSize>(sizeof(m_SendLine[0].szSendData)-sizeof(NetMessageHead)))) return 0;

	CSignedLockObject BatchLock(&m_csBacthSend,true);
	if (m_uBatchLineCount>=uBatchLineSize) return 0;

	//д�뻺��
	UINT m_uWritePos=(m_uBatchCerrenPos+m_uBatchLineCount)%uBatchLineSize;
	m_SendLine[m_uWritePos].NetHead.bMainID=bMainID;
	m_SendLine[m_uWritePos].NetHead.bAssistantID=bAssistantID;
	m_SendLine[m_uWritePos].NetHead.bHandleCode=bHandleCode;
	m_SendLine[m_uWritePos].NetHead.uMessageSize=uSize+sizeof(NetMessageHead);
	m_SendLine[m_uWritePos].NetHead.bReserve=0;
	if (uSize>0) CopyMemory(m_SendLine[m_uWritePos].szSendData,pData,uSize);

	//���������߳�
	m_uBatchLineCount++;
	PostQueuedCompletionStatus(m_hCompletionPortBatch,uSize+sizeof(NetMessageHead),NULL,NULL);

	return uSize;
}

//�ر�����
bool CTCPSocketManageForZ::CloseSocket(UINT uIndex, DWORD dwHandleID)
{ 
	if (uIndex<m_SocketPtrArray.GetPermitCount()) 
	{
		return CloseSocket(m_SocketPtrArray.GetArrayItem(uIndex),dwHandleID);
	}
	return false;
}

//�ر�����
bool CTCPSocketManageForZ::CloseSocket(CTCPSocketForZ * pSocket, DWORD dwHandleID) 
{ 
	if (pSocket!=NULL)
	{
		CSignedLockObject RecvLock(pSocket->GetRecvLock(),true);
		CSignedLockObject SendLock(pSocket->GetSendLock(),true);

		//Ч������
		if (dwHandleID==0) dwHandleID=pSocket->m_dwHandleID;
		if ((pSocket->m_dwHandleID==0)||(dwHandleID!=pSocket->m_dwHandleID)) return false;

		//��������
		ULONG dwAccessIP=pSocket->GetConnectData();
		long int lConnectTime=(long int)time(NULL)-pSocket->GetBeginTime();
		*(m_pKeep+pSocket->m_uIndex)=0;

		//�رմ���
		if ((pSocket->CloseSocket()==true)&&(m_pService!=NULL))	m_pService->OnSocketCloseEvent(dwAccessIP,pSocket->m_uIndex,lConnectTime);

		//������Ϣ
		TCPSocketDelete(pSocket);

		return true;
	}
	return false;
}

//�ж��Ƿ�����
bool CTCPSocketManageForZ::IsConnectID(UINT uIndex, DWORD dwHandleID)
{
	if (uIndex>=m_SocketPtrArray.GetPermitCount()) return false;
	return m_SocketPtrArray.GetArrayItem(uIndex)->IsConnectID(dwHandleID);
}



//��Ϣ������
bool CTCPSocketManageForZ::OnNetMessage(CTCPSocketForZ * pSocket, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uIndex, DWORD dwHandleID)
{
	*(m_pKeep+uIndex)=0;
	//Ч�������������
	if ((pNetHead->bMainID==MDM_CONNECT)&&(pNetHead->bAssistantID==ASS_NET_TEST)) 
	{
		//*(m_pKeep+uIndex)=0; ��ǰ����Ƿ������,����Ӧ�����յ��κ���Ϣ��Ӧ�ð�������0
		return true;
	}
	if (m_pService!=NULL) return m_pService->OnSocketReadEvent(pSocket,pNetHead,pData,uSize,uIndex,dwHandleID);
	return false;
}


//SOCKET ���ݽ����߳�
unsigned __stdcall CTCPSocketManageForZ::ThreadRSSocket(LPVOID pThreadData)
{
	//���ݶ���
	ThreadStartStruct	* pStartData=(ThreadStartStruct *)pThreadData;			//�߳���������ָ��
	CTCPSocketManageForZ	* pSocketManage=pStartData->pSocketManage;				//����ָ��
	HANDLE				hCompletionPort=pStartData->hCompletionPort;			//��ɶ˿�
	HANDLE				hEvent=pStartData->hThreadEvent;						//�¼�

	//�߳����ݶ�ȡ���
	::SetEvent(hEvent);

	//�ص�����
	DWORD							dwThancferred=0;							//��������
	CTCPSocketForZ						* pTCPSocket=NULL;							//��ɼ�
	CTCPSocketForZ::OverLappedStruct	* pOverData=NULL;							//�ص�����

	while (1)
	{
		try
		{
			//�ȴ���ɶ˿�
			dwThancferred=0;
			pTCPSocket=NULL;
			pOverData=NULL;
			::GetQueuedCompletionStatus(hCompletionPort,&dwThancferred,(PULONG_PTR)&pTCPSocket,(LPOVERLAPPED *)&pOverData,INFINITE);
			if ((pTCPSocket==NULL)||(pOverData==NULL))
			{
				if ((pTCPSocket==NULL)&&(pOverData==NULL)) ::SetEvent(hEvent);
				_endthreadex(0);
			}

			//������ɶ˿�
			if ((dwThancferred==0)&&(pOverData->uOperationType==SOCKET_SND))
			{
				//SOCKET �ر�
				pSocketManage->CloseSocket(pTCPSocket,pOverData->dwHandleID);
				continue;
			}

			switch (pOverData->uOperationType)
			{
			case SOCKET_REV:	//SOCKET ���ݶ�ȡ
				{
					pTCPSocket->OnRecvCompleted(pOverData->dwHandleID);
					break;
				}
			case SOCKET_SND:	//SOCKET ���ݷ���
				{
					pTCPSocket->OnSendCompleted(dwThancferred,pOverData->dwHandleID);
					break;
				}
			}
		}
		catch (...) 
		{
			TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
		}
	}

	return 0;
}

//SOCKET �������������߳�
unsigned __stdcall CTCPSocketManageForZ::ThreadBatchSend(LPVOID pThreadData)
{
	//���ݶ���
	ThreadStartStruct		* pStartData=(ThreadStartStruct *)pThreadData;					//�߳���������ָ��
	CTCPSocketManageForZ		* pSocketManage=pStartData->pSocketManage;						//����ָ��
	UINT					uMaxCount=pSocketManage->m_SocketPtrArray.GetPermitCount();		//�����Ŀ
	HANDLE					hCompletionPort=pStartData->hCompletionPort;					//��ɶ˿�
	HANDLE					hEvent=pStartData->hThreadEvent;								//�¼�

	//�������
	SetEvent(pStartData->hThreadEvent);


	//��ʱ����
	NetMessageHead			* pNetHead=NULL;												//���ݰ�ͷ
	CTCPSocketForZ				* pSendSocket=pSocketManage->m_SocketPtrArray.GetArrayItem(0);	//���� SOCKET
	UINT					* puSendCount=&pSocketManage->m_uBatchLineCount;				//��ǰ����

	DWORD					dwThancferred=0;												//��������
	ULONG					dwCompleteKey=0L;												//�ص� IO ��ʱ����
	LPOVERLAPPED			OverData;														//�ص� IO ��ʱ����

	while (1)
	{
		try
		{
			//��ȡ��������
			dwThancferred=0;
			GetQueuedCompletionStatus(hCompletionPort,&dwThancferred,&dwCompleteKey,(LPOVERLAPPED *)&OverData,INFINITE);
			if (dwThancferred==0)
			{
				SetEvent(hEvent);
				_endthreadex(0);
			}

			//��������
			BatchSendLineStruct * pBatchData=&pSocketManage->m_SendLine[pSocketManage->m_uBatchCerrenPos];
			for (UINT i=0;i<uMaxCount;i++) 
			{
				if ((pSendSocket+i)->IsConnect())
				{
					(pSendSocket+i)->SendData(pBatchData->szSendData,pBatchData->NetHead.uMessageSize-sizeof(NetMessageHead),
						pBatchData->NetHead.bMainID,pBatchData->NetHead.bAssistantID,pBatchData->NetHead.bHandleCode,0);
				}
			}

			//��������
			{
				CSignedLockObject BatchLock(&pSocketManage->m_csBacthSend,true);
				pSocketManage->m_uBatchCerrenPos=(pSocketManage->m_uBatchCerrenPos+1)%uBatchLineSize;
				pSocketManage->m_uBatchLineCount--;
			}
		}
		catch (...) {TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);}
	}

	return 0;
}

//SOCKET ά���߳�
unsigned __stdcall CTCPSocketManageForZ::ThreadKeepActive(LPVOID pThreadData)
{
	//���ݶ���
	ThreadStartStruct		* pStartData=(ThreadStartStruct *)pThreadData;		//����ָ��
	CTCPSocketManageForZ		* pSocketManage=pStartData->pSocketManage;			//����ָ��
	HANDLE					m_hThreadEvent=pStartData->hThreadEvent;			//�߳��¼�

	//�������
	::SetEvent(m_hThreadEvent);

	//���ݶ���
	UINT uCheckCount=0;
	::Sleep(pSocketManage->m_uCheckTime);

	while (1)
	{
		//���Ͳ�������
		pSocketManage->SendDataBatch(NULL,0,MDM_CONNECT,ASS_NET_TEST,0);

		//����˳���־
		uCheckCount=0;
		while (uCheckCount<pSocketManage->m_uCheckTime)
		{
			if (!pSocketManage->m_bRun) 
			{
				SetEvent(m_hThreadEvent);
				_endthreadex(0);
			}
			::Sleep(1000);
			uCheckCount+=1000;
		}

		//Ч����������
		if ((pSocketManage->m_bCheckConnect)&&(pSocketManage->m_bRun)&&(pSocketManage->m_SocketPtrArray.GetArrayItem(0)!=NULL))
		{
			for (int i=(pSocketManage->m_SocketPtrArray.GetPermitCount()-1);i>=0;i--)
			{
				if (pSocketManage->m_SocketPtrArray.GetArrayItem(i)->IsConnect())
				{
					if ((*(pSocketManage->m_pKeep+i))>=3) //�������3�μ�������Ͽ��ÿͻ�����
						pSocketManage->CloseSocket(i,0);
					else 
						(*(pSocketManage->m_pKeep+i))++;//С��3�ζ��������������+1
				}
			}
		}
	}

	return 0;
}

//��ȡʱ�亯��
unsigned __int64 CTCPSocketManageForZ::AFCGetTimer()
{
	_asm _emit 0x0F;
	_asm _emit 0x31;
}

//��ȡ���� ID ����
DWORD CTCPSocketManageForZ::GetHandleID()
{
	static long int dwBaseID=1L;
	if (dwBaseID>3000000L) dwBaseID=1L;
	return ::InterlockedIncrement(&dwBaseID);
}

//��ȡ���� IP ��ַ
bool CTCPSocketManageForZ::GetLoaclIPAddr(TCHAR szAddrBuffer[], UINT uStation)
{
	if (szAddrBuffer==NULL) return false;

	TCHAR szHostName[51];
	::gethostname(szHostName,sizeof(szHostName));
	HOSTENT * pHostInfo=::gethostbyname(szHostName);
	if (pHostInfo!=NULL)
	{
		LPIN_ADDR * pAddrList=(LPIN_ADDR *)(pHostInfo->h_addr_list); 
		LPIN_ADDR In_Addr=*pAddrList;

		UINT uCount=0;
		szAddrBuffer[0]=0;
		while (In_Addr!=NULL)
		{
			if (uCount==uStation)
			{
				lstrcpy(szAddrBuffer,inet_ntoa(*In_Addr));
				return true;
			}
			uCount++;
			pAddrList++;
			In_Addr=*pAddrList;
		}
	}
	return false;
}

//��ֵ�� IP �ַ�
TCHAR * CTCPSocketManageForZ::ULongToIP(ULONG dwIP, TCHAR * szIP)
{
	wsprintf(szIP,TEXT("%d.%d.%d.%d"),FOURTH_IPADDRESS(dwIP),THIRD_IPADDRESS(dwIP),SECOND_IPADDRESS(dwIP),FIRST_IPADDRESS(dwIP));
	return szIP;
}
