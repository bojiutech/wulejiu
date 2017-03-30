#pragma once
//#include "e:\work\d_platform(2.2)����\sdk\include\servercommon\mainmanage.h"

#include <vector>
#include <set>
using namespace std;

#include "basemessage.h"
#include "MainManage.h"



struct ZSvrNode_st
{
	CString szIPAddr;				//������Ip��ַ
	long	lPort;					//�������˿�
	int		nZid;					//������ID
	UINT	uSocket;				//Z��������B��������Socket��

	set<UINT>	onlineUserSocket;	//�����������û�


	ZSvrNode_st()
		:szIPAddr(_T(""))
		,lPort(0)
		,nZid(0)
		,uSocket(0)
	{
	}
};

class CMainserverList
{
	CString m_strHostIP;
	void clear();
	CRITICAL_SECTION cs;
public:
	vector<ZSvrNode_st> m_List;
	void Lock(){}
	void UnLock(){}

	//����SocketID����Ӧ������
	ZSvrNode_st* GetServerBySocket(UINT uSocket);
	//����UserId����Ӧ������
	ZSvrNode_st* find(DWORD dUserId);
	//���һ��Z������
	bool InsertServer(CString szIP, long lPort, int nZid, UINT uSocket);
	//ɾ��һ��Z������
	bool RemoveServer(UINT uSocket);
	//���Ժ���
	void PrintDebug();

	CMainserverList();
	~CMainserverList();
	bool RandAServer(char* ipaddr,UINT& port);
};


class CZServerManager :
	public CBaseMainManage
{
public:
	CZServerManager(void);
public:
	~CZServerManager(void);

private:
	//��ȡ��Ϣ����
	virtual bool PreInitParameter(ManageInfoStruct * pInitData, KernelInfoStruct * pKernelData);
	//SOCKET ���ݶ�ȡ
	virtual bool OnSocketRead(NetMessageHead * pNetHead, void * pData, UINT uSize, ULONG uAccessIP, UINT uIndex, DWORD dwHandleID);
	//SOCKET �ر�
	virtual bool OnSocketClose(ULONG uAccessIP, UINT uSocketIndex, long int lConnectTime);
	//���ݿ⴦����
	virtual bool OnDataBaseResult(DataBaseResultLine * pResultData){return true;}
	//��ʱ����Ϣ
	virtual bool OnTimerMessage(UINT uTimerID){return true;}

public:
	CMainserverList							m_MainserverList;

};