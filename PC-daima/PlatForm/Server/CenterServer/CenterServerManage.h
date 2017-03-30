#pragma once

#include "AfxTempl.h"
#include "MainManage.h"
#include "GamePlaceMessage.h"

#include "ZServerManager.h"

//�궨�� 
/******************************************************************************************************/

//��Ϸ��½������
class CCenterServerManage : public CBaseMainManage
{
	//��������
public:
///	CServerGameListManage						m_GameList;						//��Ϸ�б�

	//��������
public:
	//���캯��
	CCenterServerManage(void);
	//��������
	virtual ~CCenterServerManage(void);
	//��ȡ��Ϸ�б�
///	CServerGameListManage * GetGameList() { return &m_GameList; };

	//���ܺ���
public:
	//���ݹ���ģ������
	virtual bool OnStart();
	//���ݹ���ģ��ر�
	virtual bool OnStop();

	//������չ�ӿں���
private:
	///���ݹ���ģ���ʼ��
	virtual bool OnInit(ManageInfoStruct * pInitData, KernelInfoStruct * pKernelData);
	///���ݹ���ģ��ж��
	virtual bool OnUnInit();
	//��ȡ��Ϣ����
	virtual bool PreInitParameter(ManageInfoStruct * pInitData, KernelInfoStruct * pKernelData);
	//SOCKET ���ݶ�ȡ
	virtual bool OnSocketRead(NetMessageHead * pNetHead, void * pData, UINT uSize, ULONG uAccessIP, UINT uIndex, DWORD dwHandleID);
	//SOCKET �ر�
	virtual bool OnSocketClose(ULONG uAccessIP, UINT uSocketIndex, long int lConnectTime);
	//���ݿ⴦����
	virtual bool OnDataBaseResult(DataBaseResultLine * pResultData){return true;}
	//��ʱ����Ϣ
	virtual bool OnTimerMessage(UINT uTimerID);

	void RandAServer();
	void GetINIFile();

	///< ���� �������ļ��ж�ȡURL
	///< @param strKey
	///< @Return void
	void GetURL(char* strKey);

	/// ��Function.bcf�ж�ȡ��������
	/// @param void
	/// @return void
	void GetFunction();
	

	class CMainserverList
	{
		void clear();
		CRITICAL_SECTION cs;
	//public:	void ReadINIFile(CString TMLkey);
	public:
		void LoadServerList(DWORD cfgHandle);
		struct Node
		{
			CString IPAddr;
			long Port;
			int id;
		};
		CPtrList m_List;
		void Lock(){}//EnterCriticalSection(&cs);}
		void UnLock(){}//LeaveCriticalSection(&cs);}

		CMainserverList();
		~CMainserverList();
		bool RandAServer(char* ipaddr,long& port);
	};
	//CMainserverList m_MainserverList;
public:
	CenterServerMsg m_msgSendToClient;////��Ϸȫ�ֲ���
	CZServerManager m_ZServerManager;

};

/******************************************************************************************************/

//��Ϸ��½ģ��
class CCenterServerModule : public IModuleManageService
{
	//�������� 
public:
	CCenterServerManage						m_LogonManage;					//��½���ݹ���

	//��������
public:
	//���캯��
	CCenterServerModule(void);
	//��������
	virtual ~CCenterServerModule(void);

	//�ӿں���
public:
	//��ʼ������
	virtual bool InitService(ManageInfoStruct * pInitData);
	//ж�غ���
	virtual bool UnInitService();
	//��ʼ����
	virtual bool StartService(UINT &errCode);
	//ֹͣ����
	virtual bool StoptService();
	//ɾ������
	virtual bool DeleteService();
};

/******************************************************************************************************/
