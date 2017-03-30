#include "StdAfx.h"
#include "PropService.h"
#include "GameMainManage.h"

CPropService::CPropService(CWnd *pWnd)
{
	pParentWnd=pWnd;
}

CPropService::~CPropService(void)
{
}

bool CPropService::OnNetMessage(NetMessageHead *pNetHead, void* pData, UINT uSize, ULONG uAccessIP, UINT uIndex, DWORD dwHandleID)
{
	ASSERT(pNetHead->bMainID == MDM_GR_PROP);
	switch(pNetHead->bAssistantID)
	{
	case ASS_PROP_USEPROP:
		OnUseProp(pNetHead,pData,uSize,uAccessIP,uIndex,dwHandleID);
		break;
	case ASS_PROP_SMALL_BOARDCASE:
		OnUserSmallBoardcase(pNetHead,pData,uSize,uAccessIP,uIndex,dwHandleID);
		break;
		//case ASS_C_GET_ITEM_DATA:
		//	{
		//		return OnGetItemDataMsg(pNetHead,pData,uSize,uAccessIP,uIndex,dwHandleID);
		//	}
		//case ASS_C_USE_ITEM:
		//	{
		//		return OnUserUseItemMsg(pNetHead,pData,uSize,uAccessIP,uIndex,dwHandleID);
		//	}
		//case ASS_C_GET_BUY_ITEM_DATA:
		//	{
		//		return OnGetBuyItemDataMsg(pNetHead,pData,uSize,uAccessIP,uIndex,dwHandleID);
		//	}
		//case ASS_C_BUY_ITEM_DATA:
		//	{
		//		return OnBuyItemMsg(pNetHead,pData,uSize,uAccessIP,uIndex,dwHandleID);
		//	}
	case ASS_PROP_KICKUSER:
		{
			if(sizeof(_TAG_KICKUSER)!= uSize)
				return true;
			CGameMainManage *pWnd=(CGameMainManage*)pParentWnd;
			CGameUserInfo * pUserInfo = pWnd->m_UserManage.GetOnLineUserInfo(uIndex);
			if(pUserInfo == NULL)
				return true;
			CString stime;
			stime.Format("%d",CTime::GetCurrentTime());        //��ǰ��ʱ�䣬String��ʽ
			int curtime=atoi(stime);                        //ת��Ϊint
			if(pUserInfo->m_UserData.iVipTime < curtime )
				return true;

			_TAG_KICKUSER * pKick = (_TAG_KICKUSER*)pData;
			CGameUserInfo * pDestUserInfo = pWnd->m_UserManage.FindOnLineUser(pKick->dwDestID);
			if(pDestUserInfo == NULL)
				return true;
			if(pUserInfo->m_UserData.bDeskNO == 255)
				return true;
			CGameDesk *pDesk = pWnd->GetDeskObject(pUserInfo->m_UserData.bDeskNO);//*(m_pDesk + pUserInfo->m_UserData.bDeskNO);
			if(pDesk == NULL)
				return true;
			if(pDesk->IsPlayingByGameStation())//��Ϸ������
			{
				//m_TCPSocket.SendData(pDestUserInfo->m_uSocketIndex,pKick,sizeof(tagKickUserMsg),MDM_GR_VIP_MSG,ASS_S_KICK_USER,0,0);
				return true;
			}
			if (pDestUserInfo->m_UserData.bUserState==USER_WATCH_GAME) 
			{ 
				pDesk->WatchUserLeftDesk(pDestUserInfo->m_UserData.bDeskStation,pDestUserInfo); 
			} 
			else  
			{ 
				pDesk->UserLeftDesk(pDestUserInfo->m_UserData.bDeskStation,pDestUserInfo); 
			} 
			//pDesk->UserLeftDesk(pDestUserInfo->m_UserData.bDeskStation,pDestUserInfo);
			//���͸�������Ϣ
			pWnd->m_TCPSocket.SendData(pDestUserInfo->m_uSocketIndex,pKick,sizeof(_TAG_KICKUSER),MDM_GR_PROP,ASS_PROP_KICKUSER,0,0);
			return true;
		}
	}
	return true;
}

bool CPropService::OnUserSmallBoardcase(NetMessageHead *pNetHead, void* pData, UINT uSize, ULONG uAccessIP, UINT uIndex, DWORD dwHandleID)
{
	if(uSize!=sizeof(_TAG_BOARDCAST))
		return true;
	PROP_GPR_I_BOARDCAST iBoardcast;
	ZeroMemory(&iBoardcast,sizeof(PROP_GPR_I_BOARDCAST));

	memcpy(&iBoardcast.boardCast,pData,uSize);
	CGameMainManage *pWnd=(CGameMainManage*)pParentWnd;
	
	//yjj 090323
	/*if (!pWnd->m_TalkFilter.IsAllowableTalk(iBoardcast.boardCast.szMessage,strlen(iBoardcast.boardCast.szMessage)))
	{
		const CHAR* pTemTalk = pWnd->m_TalkFilter.GetReplaceContent();
		strcpy(iBoardcast.boardCast.szMessage,pTemTalk);
	}*/

	string str_temp(iBoardcast.boardCast.szMessage);
	pWnd->m_HNFilter.censor(str_temp,false);
	strcpy(iBoardcast.boardCast.szMessage,str_temp.c_str());
	iBoardcast.boardCast.iLength = strlen(iBoardcast.boardCast.szMessage) + 1;
	iBoardcast.boardCast.szMessage[iBoardcast.boardCast.iLength+1]=0;
	pWnd->m_SQLDataManage.PushLine(&iBoardcast.DataBaseHead,sizeof(PROP_GPR_I_BOARDCAST),DTK_GPR_PROP_SMALL_BRD,uIndex,dwHandleID);
	return true;
}

bool CPropService::OnDataBaseResult(DataBaseResultLine * pResultData)
{
	switch(pResultData->uHandleKind)
	{
	case DTK_GR_PROP_USE://���е�����
		return OnUsePropResult(pResultData);
		break;
	case DTK_GPR_PROP_SMALL_BRD:
		return OnUserSmallBoardcaseResult(pResultData);
		break;
	}
	return true;
}

bool CPropService::OnUseProp(NetMessageHead *pNetHead, void* pData, UINT uSize, ULONG uAccessIP, UINT uIndex, DWORD dwHandleID)
{
	ASSERT(pNetHead->bMainID == MDM_GR_PROP);
	ASSERT(pNetHead->bAssistantID == ASS_PROP_USEPROP);

	CGameMainManage *pWnd=(CGameMainManage*)pParentWnd;
	CGameUserInfo * pUserInfo = pWnd->m_UserManage.GetOnLineUserInfo(uIndex);
	if (pUserInfo == NULL) 
		return false;

	if (uSize != sizeof(_TAG_USINGPROP))
		return false;

	//���ʻ���שͷ�����໥ʹ��
	//long dwDestID = pUserInfo->m_UserData.dwUserID;
	_TAG_USINGPROP *usingProp=(_TAG_USINGPROP*)pData;
	if (NULL == usingProp)//20090522zht
	{
		return true;
	}
	CGameUserInfo *pTargetUserInfo=pWnd->m_UserManage.FindOnLineUser(usingProp->dwTargetUserID);
	if (NULL == pTargetUserInfo)//20090522zht
	{
		pWnd->m_TCPSocket.SendData(uIndex,MDM_GR_PROP,ASS_PROP_USEPROP,DTK_GP_PROP_GIVE_NOTARGETUSER,0);
		return true;
	}
	
	//�ӷ�����ȡ�û�����Ϣ
	usingProp->iDoubleTime=pTargetUserInfo->m_UserData.iDoublePointTime;
	usingProp->iProtectTime=pTargetUserInfo->m_UserData.iProtectTime;
	

	DL_GR_I_USEPROP propIUse;
	memcpy(&propIUse.usingProp,usingProp,sizeof(_TAG_USINGPROP));

	pWnd->m_SQLDataManage.PushLine(&propIUse.DataBaseHead,sizeof(DL_GR_I_USEPROP),DTK_GR_PROP_USE,0,0);
	return true;
}

bool CPropService::OnUserSmallBoardcaseResult(DataBaseResultLine *pResultData)
{
	if(pResultData->LineHead.uSize!=sizeof(PROP_GPR_O_BOARDCAST))
		return true;
	PROP_GPR_O_BOARDCAST * oBoard=(PROP_GPR_O_BOARDCAST*)pResultData;
	CGameMainManage *pWnd=(CGameMainManage*)pParentWnd;

	//oBoard->
	

	pWnd->m_TCPSocket.SendDataBatch(&(oBoard->boardCast), sizeof(_TAG_BOARDCAST),MDM_GR_PROP,ASS_PROP_SMALL_BOARDCASE,pResultData->uHandleRusult);
	return true;
}

bool CPropService::OnUsePropResult(DataBaseResultLine *pResultData)
{
	if (pResultData->LineHead.uSize != sizeof(DL_GR_O_USEPROP))
		return false;

	DL_GR_O_USEPROP	*useOProp = (DL_GR_O_USEPROP * )pResultData;

	CGameMainManage *pWnd=(CGameMainManage*)pParentWnd;

	//ȡ��ʹ���ߵ���Ҷ���
	CGameUserInfo *pPropUseUser = pWnd->m_UserManage.FindOnLineUser(useOProp->usingProp.dwUserID);
	//������ʹ��Ŀ�������Ϊʹ�ö���
	CGameUserInfo *pPropTargetUser=pPropUseUser;

	if (pPropUseUser == NULL)
		return true;
	
	//2�����ԣ��������Ժ�ȡֵ����
	int attribAction=useOProp->usingProp.nPropActionAttrib;
	int attribValue=useOProp->usingProp.nPropValueAttrib;
	

	switch(pResultData->uHandleRusult)
	{
	//δ֪���󣬻����������ݿ��
	case DTR_GR_PROP_USE_ERR_UNKNOW:
		return true;
		break;
	//������Ч
	case DTR_GR_PROP_USE_ERR_PARAM_INVALID:
	//û�е�����
	case DTR_GR_PROP_USE_ERR_NOPROP:
		pWnd->m_TCPSocket.SendData(pPropUseUser->m_uSocketIndex,MDM_GR_PROP,ASS_PROP_USEPROP,pResultData->uHandleRusult,0);
		return true;
		break;
	}
	//ʣ����ʹ�õ��߳ɹ�
	//��С����
	if(attribAction & 0x80 || attribAction & 0x100)
	{
	//	pWnd->m_TCPSocket.SendData(pPropUseUser->m_uSocketIndex,&(useOProp->usingProp),sizeof(_TAG_USINGPROP),MDM_GR_PROP,ASS_PROP_USEPROP,pResultData->uHandleRusult,0);
		return true;
	}

    // PengJiLin, 2010-6-1, ���������ؽ���������޸���ʾ����
    if(attribAction & 0x200)
    {
        pWnd->m_TCPSocket.SendData(pPropUseUser->m_uSocketIndex,&(useOProp->usingProp),sizeof(_TAG_USINGPROP),MDM_GR_PROP,ASS_PROP_USEPROP,pResultData->uHandleRusult,0);
        return true;
    }

	//����Ƕ�������ʹ�ã��������˵�ID�Ų�ͬ��ʹ���ߵ�ID����ȡ�õ���ʹ��Ŀ��Ķ���
	if(attribAction & 0x1 && useOProp->usingProp.dwUserID!=useOProp->usingProp.dwTargetUserID)
		pPropTargetUser=pWnd->m_UserManage.FindOnLineUser(useOProp->usingProp.dwTargetUserID);
	//�������㹦�� yinyi-080910
	if(attribAction & 0x2)
	{
		if(pPropTargetUser->m_UserData.dwPoint<0)
		{
			//wushuqun 2009.6.2
			//�޸��û�ԭ��
			pPropTargetUser->m_dwScrPoint = 0;
			pPropTargetUser->m_UserData.dwPoint=0;
		}
	}
	//����ֵ�仯
	int fasciChange=0;
	if(attribAction & 0x10)
	{
		//����ֵ�仯��
		fasciChange=(attribValue & 0xFF0000)>>16;
		//��������ֵ���Ǽ�������ֵ
		if(attribAction & 0x20)
			fasciChange=-fasciChange;
		pPropTargetUser->m_UserData.dwFascination+=fasciChange;

	}
	//Ӱ�����ʱ��仯,˫������
	if(attribAction & 0x4)
		pPropTargetUser->m_UserData.iDoublePointTime=useOProp->usingProp.iDoubleTime;
	//Ӱ�����ʱ��仯,�����
	if(attribAction & 0x8)
		pPropTargetUser->m_UserData.iProtectTime=useOProp->usingProp.iProtectTime;

	//�򷿼������˷���Ϣ
	pWnd->m_TCPSocket.SendDataBatch(&(useOProp->usingProp), sizeof(_TAG_USINGPROP),MDM_GR_PROP,ASS_PROP_USEPROP,pResultData->uHandleRusult);

	//ֻ����ͬһ�����ӣ��Żᷢ����Ч��
	if(attribAction & 0x40 && pPropUseUser->m_UserData.bDeskNO!=255 && pPropTargetUser->m_UserData.bDeskNO==pPropUseUser->m_UserData.bDeskNO)
	{
		CGameDesk * pGameDesk=pWnd->GetDeskObject(pPropUseUser->m_UserData.bDeskNO);
		if(pGameDesk)
		{
			//����ṹ
			_TAG_PROP_MOIVE_USE propMoive;
			propMoive.dwUserID=pPropUseUser->m_UserData.dwUserID;
			propMoive.dwTargetUserID=pPropTargetUser->m_UserData.dwUserID;
			propMoive.nUserStation=pPropUseUser->m_UserData.bDeskStation;
			propMoive.nTargetUserStation=pPropTargetUser->m_UserData.bDeskStation;
			propMoive.nPropID=useOProp->usingProp.nPropID;
			propMoive.nPropActionAttrib=useOProp->usingProp.nPropActionAttrib;
			propMoive.nPropValueAttrib=useOProp->usingProp.nPropValueAttrib;
			pGameDesk->UserUseProp(pPropUseUser->m_UserData.bDeskStation,pPropTargetUser->m_UserData.bDeskStation,&propMoive);
		}
	}



	return true;
}