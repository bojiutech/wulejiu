#pragma once

#include "common.h"

//�ŵ���Ϣ���ӽӿ�
interface IChannelMessageSink
{
	//�ŵ����ݴ���
	virtual bool __cdecl OnChannelMessage(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend)=NULL;
};


//�ŵ��¼����ӽӿ�
interface IChannelEventSink
{
	//������Ϣ
	virtual bool __cdecl OnChannelConnect(HWND hWndSend)=NULL;
	//Ӧ����Ϣ
	virtual bool __cdecl OnChannelAccept(HWND hWndSend)=NULL;
	//�Ͽ���Ϣ
	virtual bool __cdecl OnChannelClose(HWND hWndSend, bool bInitiative)=NULL;
};


//�ŵ�ģ��ӿ�
interface IChannelService
{
	//�����¼�
	virtual bool __cdecl SetChannelEventSink(IChannelEventSink * pIUnknownEx)=NULL;
	//������Ϣ
	virtual bool __cdecl SetChannelMessageSink(IChannelMessageSink * pIUnknownEx)=NULL;
	//��ȡ�¼�
	virtual void * __cdecl GetChannelEventSink(const IID & Guid, DWORD dwQueryVer)=NULL;
	//��ȡ��Ϣ
	virtual void * __cdecl GetChannelMessageSink(const IID & Guid, DWORD dwQueryVer)=NULL;
	//�Ƿ�����
	virtual bool __cdecl IsConnect(bool bEfficacy)=NULL;
	//��������
	virtual bool __cdecl CreateChannel(HWND hWndServer)=NULL;
	//�رպ���
	virtual bool __cdecl CloseChannel(bool bNotifyServer, bool bNotifySink)=NULL;
	//��������
	virtual bool __cdecl SendData(WORD wMainCmdID, WORD wSubCmdID)=NULL;
	//��������
	virtual bool __cdecl SendData(WORD wMainCmdID, WORD wSubCmdID, void * pBuffer, WORD wDataSize)=NULL;
};
