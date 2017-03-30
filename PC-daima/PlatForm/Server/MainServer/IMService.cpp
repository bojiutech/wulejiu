#include "StdAfx.h"
#include "IMService.h"
#include "GameLogonManage.h"

extern CString GetAppPath(bool bFource=true);  //yjj 090317

CIMService::~CIMService(void)
{
}
CIMService::CIMService(CWnd *pWnd)
{
	pParentWnd=pWnd;
	CString s = GetAppPath();
	m_TalkFilter.LoadFilterMessage(s.GetBuffer());
};
/*
Function	:OnNetMessage
Notes		:������Ϣ
Author		:Fred Huang
Date		:2008-04-02
Parameter	:
NetMessageHead	:������Ϣͷ
void *			:����ָ��
UINT			:���ݰ��Ĵ�С
UING			:δʹ�ã�ԭָIP��ַ
UINT			:�ͻ��ڷ�������SOCKET����
return		:void
*/
void CIMService::OnNetMessage(NetMessageHead * pNetHead, void * pData, UINT uSize, ULONG uAccessIP, UINT uIndex, DWORD dwHandleID)
{
	if(pNetHead->bMainID!=MDM_GP_IM)
		return;
	switch(pNetHead->bAssistantID)
	{
	case ASS_IMC_GETCOUNT:
		OnNetGetUserCount(pData,uSize,uIndex,dwHandleID);			//ȡ��������
		break;
	case ASS_IMC_ADDREQUEST:
		OnNetAddRequest(pNetHead, pData,uSize,uIndex,dwHandleID);			//�����Ϊ����
		break;
	case ASS_IMC_ADDREQUESTRESPONSE:
		OnNetAddResponse(pData,uSize,uIndex,dwHandleID);
		break;
	case ASS_IMC_MSG:
		OnNetUserMessage(pData,uSize,uIndex,dwHandleID);
		break;
	case ASS_IMC_SETGROUP:
		OnNetUserSetGroup(pData,uSize,uIndex,dwHandleID);
		break;
	case ASS_IMS_ADDREQUESTRESPONSE:
	case ASS_IMS_MSG:
	case ASS_IMS_NOAC:
		OnNetAddRequest_Z(pNetHead, pData,uSize,uIndex,dwHandleID);	
		break;
	}
}

/*
Function	:OnNetGetUserCount
Notes		:�ͻ�����ȡ�÷������ϵĺ�������
Author		:Fred Huang
Date		:2008-04-02
Parameter	:
NetMessageHead	:������Ϣͷ
void *			:����ָ��
UINT			:���ݰ��Ĵ�С
UING			:δʹ�ã�ԭָIP��ַ
UINT			:�ͻ��ڷ�������SOCKET����
return		:void
*/
void CIMService::OnNetGetUserCount(void * pData, UINT uSize, UINT uIndex, DWORD dwHandleID)
{
	//ȡ������
	CGameLogonManage *pWnd=(CGameLogonManage*)pParentWnd;
	
	MSG_IM_C_COUNT * msg=(MSG_IM_C_COUNT*)pData;
	//��Ҫ�����ݿ���ȡ�ã����ṹ
	IM_GP_I_GETUSERCOUNT im_GetUserCount;
	ZeroMemory(&im_GetUserCount,sizeof(IM_GP_I_GETUSERCOUNT));
	im_GetUserCount.dwUserID=msg->dwUserID;
	im_GetUserCount.dwUserCount=msg->dwUserCount;
	
	pWnd->m_SQLDataManage.PushLine(&im_GetUserCount.DataBaseHead,sizeof(IM_GP_I_GETUSERCOUNT),DTK_GP_IM_GETCOUNT,uIndex,0);

}

/*
Function	:OnNetMessage
Notes		:�û�������Ϣ������ֻ��ֱ��ת��
Author		:Fred Huang
Date		:2008-04-07
Parameter	:
NetMessageHead	:������Ϣͷ
void *			:����ָ��
UINT			:���ݰ��Ĵ�С
UING			:δʹ�ã�ԭָIP��ַ
UINT			:�ͻ��ڷ�������SOCKET����
return		:void
*/
void CIMService::OnNetUserMessage(void * pData, UINT uSize, UINT uIndex, DWORD dwHandleID)
{
	//ȡ������
	CGameLogonManage *pWnd=(CGameLogonManage*)pParentWnd;

	MSG_IM_C_MSG *msg=(MSG_IM_C_MSG*)pData;

	if (!pWnd->IsUserAlreadyLogon(msg->dwRemoteUserID))
	{
		pWnd->SendDataByUser(msg->dwRemoteUserID, pData, uSize, MDM_GP_IM, ASS_IMS_MSG, 0, 0);
		return;
	}

	for(int i=0; i<pWnd->m_UserList.GetCount(); i++)
	{
		LPUSER p = (LPUSER)pWnd->m_UserList.GetAt(i);
		if(p == NULL)
			continue;
		if(p->UserID == msg->dwRemoteUserID)
		{
			msg->szMsg[msg->szMsgLength + 1] = 0;
			//AfxMessageBox(msg->szMsg);
			/*if (!m_TalkFilter.IsAllowableTalk(msg->szMsg,strlen(msg->szMsg)))
			{
				const CHAR* pTemTalk = m_TalkFilter.GetReplaceContent();
				strcpy(msg->szMsg,pTemTalk);
				msg->szMsgLength = strlen(pTemTalk) + 1;
				msg->szMsg[msg->szMsgLength + 1] = 0;
				msg->cbSize=sizeof(MSG_IM_C_MSG)-sizeof(msg->szMsg)+msg->szMsgLength+1;
			}*/

			string str_temp(msg->szMsg);
			m_HNFilter.censor(str_temp,false);
			strcpy(msg->szMsg,str_temp.c_str());
			msg->szMsgLength = strlen(msg->szMsg) + 1;
			msg->szMsg[msg->szMsgLength + 1] = 0;
			msg->cbSize=sizeof(MSG_IM_C_MSG)-sizeof(msg->szMsg)+msg->szMsgLength+1;

			pWnd->m_TCPSocket.SendData(p->iSocketIndex,msg,msg->cbSize,MDM_GP_IM,ASS_IMS_MSG,0,0);
			return;
		}
	}	
	//�û������ߣ��ط�����ͷ���û������ߣ���Ҳ���Բ�����
	//��������ͷ
	//pWnd->m_TCPSocket.SendData(uIndex,msg,msg->cbSize-msg->szMsgLength,MDM_GP_IM,ASS_IMS_USERNOTONLINE,0,dwHandleID);
}

/*
Function	:OnNetAddRequest
Notes		:������Ӻ��ѣ�����ֻ��ת��
Author		:Fred Huang
Date		:2008-04-07
Parameter	:
NetMessageHead	:������Ϣͷ
void *			:����ָ��
UINT			:���ݰ��Ĵ�С
UING			:δʹ�ã�ԭָIP��ַ
UINT			:�ͻ��ڷ�������SOCKET����
return		:void
*/
void CIMService::OnNetAddRequest(NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uIndex, DWORD dwHandleID)
{
	//ȡ������
	CGameLogonManage *pWnd=(CGameLogonManage*)pParentWnd;

	MSG_IM_C_ADDREQUEST *msg=(MSG_IM_C_ADDREQUEST*)pData;

	if (pNetHead->bHandleCode == 0)
	{
		if (!pWnd->IsUserAlreadyLogon(msg->dwRequestedUserID))
		{
			pWnd->SendDataByUser(msg->dwRequestedUserID, pData, uSize, pNetHead->bMainID, pNetHead->bAssistantID, pNetHead->bHandleCode, 0);
			return;
		}
	}
	else
	{
		if (!pWnd->IsUserAlreadyLogonByName(msg->sUserName))
		{
			pWnd->SendDataByUser(msg->dwRequestedUserID, pData, uSize, pNetHead->bMainID, pNetHead->bAssistantID, pNetHead->bHandleCode, 0);
			return;
		}
	}


	if (pNetHead->bHandleCode == 0)
	{
		for(int i=0; i<pWnd->m_UserList.GetCount(); i++)
		{
			LPUSER p = (LPUSER)pWnd->m_UserList.GetAt(i);
			if(p == NULL)
				continue;
			if(p->UserID ==msg->dwRequestedUserID)
			{
				strcpy(msg->sRequestedUserName, p->UserName);
				if (p->iAddFriendType % 65535 == 0)
					pWnd->SendDataByUser(msg->dwRequestedUserID,msg,msg->cbSize,MDM_GP_IM,ASS_IMS_ADDREQUEST,0,0);
				else
					pWnd->SendDataByUser(msg->dwUserID,msg,msg->cbSize,MDM_GP_IM,ASS_IMC_ADDREQUEST,1,0);
				return;
			}
		}	
	}
	else
	{
		for(int i=0; i<pWnd->m_UserList.GetCount(); i++)
		{
			LPUSER p = (LPUSER)pWnd->m_UserList.GetAt(i);
			if(p == NULL)
				continue;
			if(strcmp(p->UserName, msg->sRequestedUserName) == 0)
			{
				msg->dwRequestedUserID = p->UserID;
				if (p->iAddFriendType % 65535 == 0)
					pWnd->SendDataByUser(msg->dwRequestedUserID,msg,msg->cbSize,MDM_GP_IM,ASS_IMS_ADDREQUEST,0,0);
				else
					pWnd->SendDataByUser(msg->dwUserID,msg,msg->cbSize,MDM_GP_IM,ASS_IMC_ADDREQUEST,1,0);
				return;
			}
		}	
	}

	pWnd->m_TCPSocket.SendData(uIndex,msg,msg->cbSize,MDM_GP_IM,ASS_IMC_ADDREQUEST,2,0);

}

/*
Function	:OnNetAddResponse
Notes		:������Ӻ��ѣ�����ֻ��ת���Ļ�Ӧ����ͬ��ʱ��Ҫд�����ݿ��У���ͬ��ʱ��ֱ��ת����Ϣ����
Author		:Fred Huang
Date		:2008-04-07
Parameter	:
NetMessageHead	:������Ϣͷ
void *			:����ָ��
UINT			:���ݰ��Ĵ�С
UING			:δʹ�ã�ԭָIP��ַ
UINT			:�ͻ��ڷ�������SOCKET����
return		:void
*/
void CIMService::OnNetAddResponse(void * pData, UINT uSize, UINT uIndex, DWORD dwHandleID)
{
	//ȡ������
	CGameLogonManage *pWnd=(CGameLogonManage*)pParentWnd;

	MSG_IM_S_ADDRESPONSE *msg=(MSG_IM_S_ADDRESPONSE*)pData;

	//if (!pWnd->IsUserAlreadyLogon(msg->dwRequestedUserID))
	//{
	//	pWnd->SendDataByUser(msg->dwRequestedUserID, pData, uSize, MDM_GP_IM, ASS_IMS_ADDREQUESTRESPONSE, 0, 0);
	//	return;
	//}


	//��ͬ�����Ҳ��һ����Ϸ��¼����ӶԷ�Ϊ���� yjj 090323
	MSG_IM_S_ADDRESPONSE  tempmsg;
	tempmsg.dwRequestedUserID = msg->dwUserID;
	tempmsg.dwUserID = msg->dwRequestedUserID;
	tempmsg.nResponse = msg->nResponse;
	memcpy(tempmsg.sRequestedUserName,msg->sRequirUsrName,sizeof(tempmsg.sRequestedUserName));
	memcpy(tempmsg.sRequirUsrName,msg->sRequestedUserName,sizeof(tempmsg.sRequirUsrName));



	//
	int iCount = 0;

	//ֱ��ת����Ϣ���û�

	LPUSER pUser = NULL;
	LPUSER pUserTarget = NULL;

	pUser = pWnd->GetUserByID(msg->dwUserID);
	if (pUser != NULL) 
		pWnd->m_TCPSocket.SendData(pUser->iSocketIndex,msg,sizeof(MSG_IM_S_ADDRESPONSE),MDM_GP_IM,ASS_IMS_ADDREQUESTRESPONSE,0,0);
	else 
		pWnd->SendDataByUser(msg->dwUserID, msg, sizeof(MSG_IM_S_ADDRESPONSE), MDM_GP_IM, ASS_IMS_ADDREQUESTRESPONSE, 0, 0);
	pUserTarget = pWnd->GetUserByID(tempmsg.dwUserID);
	if (pUserTarget != NULL) 
		pWnd->m_TCPSocket.SendData(pUserTarget->iSocketIndex,&tempmsg,sizeof(MSG_IM_S_ADDRESPONSE),MDM_GP_IM,ASS_IMS_ADDREQUESTRESPONSE,0,0);

	if(msg->nResponse==IDYES)
	{
		IM_GP_I_SETUSER imISetUser;
		imISetUser.dwUserID=msg->dwUserID;
		imISetUser.dwRemoteID=msg->dwRequestedUserID;
		imISetUser.groupID=1;//ͬ���Ϊ���ѣ�ֱ�ӷŵ�������

		pWnd->m_SQLDataManage.PushLine(&imISetUser.DataBaseHead,sizeof(IM_GP_I_SETUSER),DTK_GP_IM_SETUSER,uIndex,0);


		//IM_GP_I_SETUSER imISetUser2;
		//imISetUser2.dwUserID=tempmsg.dwUserID;
		//imISetUser2.dwRemoteID=tempmsg.dwRequestedUserID;
		//imISetUser2.groupID=1;//ͬ���Ϊ���ѣ�ֱ�ӷŵ�������

		//pWnd->m_SQLDataManage.PushLine(&imISetUser2.DataBaseHead,sizeof(IM_GP_I_SETUSER),DTK_GP_IM_SETUSER,uIndex,0);
	}
}

/*
Function	:OnNetUserSetGroup
Notes		:�û��޸���
Author		:Fred Huang
Date		:2008-04-07
Parameter	:
NetMessageHead	:������Ϣͷ
void *			:����ָ��
UINT			:���ݰ��Ĵ�С
UING			:δʹ�ã�ԭָIP��ַ
UINT			:�ͻ��ڷ�������SOCKET����
return		:void
*/
void CIMService::OnNetUserSetGroup(void * pData, UINT uSize, UINT uIndex, DWORD dwHandleID)
{
	//ȡ������
	CGameLogonManage *pWnd=(CGameLogonManage*)pParentWnd;

	MSG_IM_C_SETGROUP *msg=(MSG_IM_C_SETGROUP*)pData;

	//ֱ���޸ķ�����������Ҫ����

	IM_GP_I_SETUSER imISetUser;
	imISetUser.dwUserID=msg->dwUserID;
	imISetUser.dwRemoteID=msg->dwRemoteUserID;
	imISetUser.groupID=msg->groupID;
	pWnd->m_SQLDataManage.PushLine(&imISetUser.DataBaseHead,sizeof(IM_GP_I_SETUSER),DTK_GP_IM_SETUSER,uIndex,0);
#ifdef HWACC
	int a= 8;
#endif
}

void CIMService::OnNetAddRequest_Z(NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uIndex, DWORD dwHandleID)
{
	//ȡ������
	CGameLogonManage *pWnd=(CGameLogonManage*)pParentWnd;
	pWnd->m_TCPSocket.SendData(uIndex, pData, uSize, pNetHead->bMainID, pNetHead->bAssistantID, pNetHead->bHandleCode, 0);
}