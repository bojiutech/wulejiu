#pragma once


interface IDistriManagerBase
{
public:
	//���ͺ���
	virtual INT32 SendData(UINT uIndex, void * pData, UINT uSize, UINT bMainID, UINT bAssistantID, UINT bHandleCode, DWORD dwHandleID)=0;
	virtual INT32 SendBatchData(void * pData, UINT uSize, UINT bMainID, UINT bAssistantID, UINT bHandleCode)=0;
	virtual INT32 SendNormalData(void * pData, UINT uSize, UINT bMainID, UINT bAssistantID, UINT bHandleCode)=0;

	//������ͺ���
	virtual INT32 SendData(UINT uIndex, UINT bMainID, UINT bAssistantID, UINT bHandleCode, DWORD dwHandleID)=0;

	virtual bool CheckReConnect() = 0;
	virtual bool CheckKeepLive() = 0;
};

interface IDistriManagerNetBase
{
public:
	/// �����û�ID��ȡSocket���
	virtual int GetIndexByID(int iUserID)=0;
	/// ��ͻ��˷��͹㲥����
	virtual int SendBatchDataSelf(void * pData, UINT uBufLen, BYTE bMainID, BYTE bAssistantID, UINT bHandleCode) = 0;
	//���ͺ���
	virtual int SendData(UINT uIndex, void * pData, UINT uBufLen, BYTE bMainID, BYTE bAssistantID, BYTE bHandleCode, DWORD dwHandleID) = 0;
	
	virtual int KickUserSocket(DWORD dwUserID) = 0;

	virtual int GetZid() = 0;

	virtual int GetServerPort() = 0;
	// B�������޷���Z�������б����ҵ����ʱ���ᷴ����Ϣ���������Z����������������ݴ���
	virtual int SendDataFail(UINT uUserID, void * pData, UINT uBufLen, BYTE bMainID, BYTE bAssistantID, UINT bHandleCode, DWORD dwHandleID) = 0;

	//SOCKET ���ݶ�ȡ
	virtual bool OnSocketRead(NetMessageHead * pNetHead, void * pData, UINT uSize, ULONG uAccessIP, UINT uIndex, DWORD dwHandleID) = 0;

};

//rongqiufen20111018
#define ID_DistriManager_WND			23								//SOCKET ���� ID
class CDistriManager :public IDistriManagerBase, public IClientSocketService
{
public:
	CDistriManager::CDistriManager(IDistriManagerNetBase *pNet);
	CDistriManager::~CDistriManager();

	///�ӿں��� 
public:
	///�����ȡ��Ϣ
	virtual bool OnSocketReadEvent(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize, CTCPClientSocket * pClientSocket);
	///����������Ϣ
	virtual bool OnSocketConnectEvent(UINT uErrorCode, CTCPClientSocket * pClientSocket);
	///����ر���Ϣ
	virtual bool OnSocketCloseEvent();

	INT32 Initial();

	INT32 Connect(const char * szServerIP, UINT32 uPort);

	INT32 Connect(UINT32 dwServerIP, UINT32 uPort);
	//���ͺ���
	INT32 SendData(UINT uUserID, void * pData, UINT uSize, UINT bMainID, UINT bAssistantID, UINT bHandleCode, DWORD dwHandleID);
	//������ͺ���
	INT32 SendData(UINT uUserID, UINT bMainID, UINT bAssistantID, UINT bHandleCode, DWORD dwHandleID);

	INT32 SendNormalData(void * pData, UINT uSize, UINT bMainID, UINT bAssistantID, UINT bHandleCode);

	INT32 SendBatchData(void * pData, UINT uSize, UINT bMainID, UINT bAssistantID, UINT bHandleCode);

	void CloseSocket(INT32 nSocketID, bool bNotify);

	virtual bool CheckReConnect();
	virtual bool CheckKeepLive();
private:
	CTCPClientSocket		*m_pSocket;
	IDistriManagerNetBase	*m_pNet;
	int					m_bConnect;			//0��ʾĩ��ʼ���ӣ�1��ʾ�Ѿ��������ӵ�û���أ� 2��ʾ���ӳɹ�
	int					m_nKeepAliveCount;
	CString				m_strHostIP;
};

extern IDistriManagerBase *CreateDistriManager(IDistriManagerNetBase *pNet);
extern void DestoryDistriManager(IDistriManagerBase*);

//rongqiufen20111018end