#pragma once

#include "sink.h"
#include "DataStorage.h"
#include "IPCControls.h"

//////////////////////////////////////////////////////////////////////////

//�ŵ�ģ����
class CChannelService : public CWnd, public IChannelService, public IChannelMessageSink
{
	//��������
protected:
	HWND							m_hWndServer;						//���մ���
	CDataStorage					m_DataStorage;						//���ݶ���
	CIPCRecvCopyData				m_IPCRecvCopyData;					//IPC ����

	//�ӿ�ָ��
protected:
	IChannelEventSink				* m_pIChannelEventSink;				//�ص��ӿ�
	IChannelMessageSink				* m_pIChannelMessageSink;			//�ص��ӿ�

	//��������
public:
	//���캯��
	CChannelService();
	//��������
	virtual ~CChannelService();

	//�����ӿ�
public:
	//�ͷŶ���
	virtual bool __cdecl Release() { if (IsValid()) delete this; return true; }
	//�Ƿ���Ч
	virtual bool __cdecl IsValid() { return AfxIsValidAddress(this,sizeof(CChannelService))?true:false; }
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//���ýӿ�
public:
	//�����¼�
	virtual bool __cdecl SetChannelEventSink(IChannelEventSink * pIUnknownEx);
	//������Ϣ
	virtual bool __cdecl SetChannelMessageSink(IChannelMessageSink * pIUnknownEx);
	//��ȡ�¼�
	virtual void * __cdecl GetChannelEventSink(const IID & Guid, DWORD dwQueryVer);
	//��ȡ��Ϣ
	virtual void * __cdecl GetChannelMessageSink(const IID & Guid, DWORD dwQueryVer);

	//���ܽӿ�
public:
	//�Ƿ�����
	virtual bool __cdecl IsConnect(bool bEfficacy);
	//��������
	virtual bool __cdecl CreateChannel(HWND hWndServer);
	//�رպ���
	virtual bool __cdecl CloseChannel(bool bNotifyServer, bool bNotifySink);
	//��������
	virtual bool __cdecl SendData(WORD wMainCmdID, WORD wSubCmdID);
	//��������
	virtual bool __cdecl SendData(WORD wMainCmdID, WORD wSubCmdID, void * pBuffer, WORD wDataSize);

	//���ݽӿ�
public:
	//�ŵ����ݴ���
	virtual bool __cdecl OnChannelMessage(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend);

	//��Ϣӳ��
protected:
	//IPC ��Ϣ
	afx_msg LRESULT OnIPCMessage(WPARAM wParam, LPARAM lParam);
	//IPC ��Ϣ
	afx_msg BOOL OnCopyData(CWnd * pWnd, COPYDATASTRUCT * pCopyDataStruct);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
