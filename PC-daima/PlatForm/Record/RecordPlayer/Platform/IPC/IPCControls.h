
#pragma once

#include "sink.h"

//////////////////////////////////////////////////////////////////////////

//IPC ���ݷ�����
class CIPCSendCopyData
{
	//��������
protected:
	HWND							m_hWndServer;						//���մ���
	HWND							m_hWndClient;						//���ʹ���

	//��������
public:
	//���캯��
	CIPCSendCopyData(HWND hWndServer=NULL, HWND hWndClient=NULL);
	//��������
	virtual ~CIPCSendCopyData();

	//�ӿں���
public:
	//�Ƿ�����
	bool IsConnect();
	//���÷��ʹ���
	bool SetClientHwnd(HWND hWndClient);
	//���ý��մ���
	bool SetServerHwnd(HWND hWndServer);
	//���ý��մ���
	bool SetServerHwnd(LPCSTR szClassName);
	//��������
	bool SendData(WORD wMainCmdID, WORD wSubCmdID);
	//��������
	bool SendData(WORD wMainCmdID, WORD wSubCmdID, void * pBuffer, WORD wDataSize);
	//�������ݣ��߼�ʹ�ã�
	bool SendIPCData(DWORD dwIdentifier, void * pBuffer, WORD wDataSize);
};

//////////////////////////////////////////////////////////////////////////

//IPC ���ݽ�����
class CIPCRecvCopyData
{
	//��������
protected:
	IChannelMessageSink				* m_pIChannelMessageSink;				//�ص��ӿ�

	//��������
public:
	//���캯��
	CIPCRecvCopyData();
	//��������
	virtual ~CIPCRecvCopyData();

	//�ӿں���
public:
	//���ûص��ӿ�
	bool SetChannelMessageSink(IChannelMessageSink * pIUnknownEx);
	//COPYDATA ��Ϣ����
	bool OnCopyData(HWND hWndSend, COPYDATASTRUCT * pCopyDataStruct);

	//�߼�����
public:
	//��ȡ���ݣ��߼�����
	bool GetIPCData(IPC_Head & IPCHead, void * & pIPCBuffer, WORD & wDataSize, PCOPYDATASTRUCT pCopyDataStruct);
};

//////////////////////////////////////////////////////////////////////////


