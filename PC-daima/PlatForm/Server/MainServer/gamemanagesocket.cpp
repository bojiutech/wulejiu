/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#include "stdafx.h"
#include <AFCSocket.h>
#include "gamemanagesocket.h"
#include "GameLogonManage.h"

CGameManageSocket::CGameManageSocket()
{

}

CGameManageSocket::~CGameManageSocket()
{
}

bool CGameManageSocket::PreInitParameter(ManageInfoStruct * pInitData, KernelInfoStruct * pKernelData)
{
	pKernelData->bLogonDataBase = FALSE;
	pKernelData->bNativeDataBase = FALSE;
	pKernelData->bStartSQLDataBase = FALSE;

	pKernelData->bStartTCPSocket = TRUE;
	
	pInitData->uListenPort = PORT_GAME_CONNECT_MAIN;
	pInitData->uMaxPeople = 100;
	pInitData->iSocketSecretKey = SECRET_KEY;

	m_pManager = nullptr;
	return true;
}

bool CGameManageSocket::OnStart()
{
	return true;
}

bool CGameManageSocket::OnStop()
{
	return true;
}

bool CGameManageSocket::OnTimerMessage(UINT uTimerID)
{
	return true;
}

bool CGameManageSocket::HandleMessage(NetMessageHead *pNetHead,void *pData,UINT uSize,ULONG uAccessIP,UINT uIndex)
{
	if(MDM_CONNECT == pNetHead->bMainID)
	{
		if(ASS_NET_TEST == pNetHead->bAssistantID)
		{
			m_TCPSocket.SendData(uIndex,MDM_CONNECT,ASS_NET_TEST,0,0);
		}
	}
	m_pManager->OnHandleGMessage(pNetHead,pData,uSize,uAccessIP,uIndex);

	return true;
}

bool CGameManageSocket::OnSocketRead(NetMessageHead * pNetHead, void * pData, UINT uSize, ULONG uAccessIP, UINT uIndex, DWORD dwHandleID)
{
	return HandleMessage(pNetHead,pData,uSize,uAccessIP,uIndex);
}

bool CGameManageSocket::OnSocketClose(ULONG uAccessIP, UINT uSocketIndex, long int lConnectTime)
{
	return true;
}

bool CGameManageSocket::OnSocketConnect(ULONG uAccessIP, UINT uSocketIndex)
{
	//m_TCPSocket.SetLoginFinish(uSocketIndex,true);
	
	return true;
}

bool CGameManageSocket::OnDataBaseResult(DataBaseResultLine * pResultData)
{
	return true;
}

#define REMAIN_MAINID 0
#define REMAIN_ASSID 0
void CGameManageSocket::SetUserCloseSocket(UINT uUserID)
{
	for(UINT i = 0; i<m_VectorRoomInfo.size();++i)
	{
		m_TCPSocket.SendData(m_VectorRoomInfo.at(i).uSocketID,nullptr,0,REMAIN_MAINID,REMAIN_ASSID,uUserID,0);
	}
}
