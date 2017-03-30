#include "StdAfx.h"
#include "UserInfo.h"
#include "GameRoomMessage.h"
#include "commonuse.h"

//extern void DebugPrintf(const char *p, ...);
/*********************************************************************************************************************/

//���캯��
CGameUserInfo::CGameUserInfo(void)
{
	m_bAccess=false;
	m_dwScrPoint=0L;
	m_dwPlayCount=0L;
	m_dwLogonTime=0L;
	m_dwHandleID=0L;
	m_dwAccessLogID=0l;
	m_dwGamePower=0L;
	m_dwMasterPower=0L;
	m_uSocketIndex=ERROR_SOCKET_INDEX;
	memset(&m_Rule,0,sizeof(m_Rule));
	memset(&m_UserData,0,sizeof(m_UserData));
	memset(m_szMD5Pass,0,sizeof(m_szMD5Pass));
	memset(&m_ChangePoint,0,sizeof(m_ChangePoint));
}

//��������
CGameUserInfo::~CGameUserInfo(void)
{
}

//�����û�״̬
bool CGameUserInfo::SetUserState(BYTE bUserState, BYTE bDeskNO, BYTE bDeskStation, bool bSetDeskStation)
{
	if (m_bAccess)
	{
		if (bSetDeskStation)
		{
			m_UserData.bDeskNO=bDeskNO;
			m_UserData.bDeskStation=bDeskStation;
		}
		m_UserData.bUserState=bUserState;
		return true;
	}
	return false;
}
/// ��һ��__int64ת��Ϊint
extern int I64ToInt(__int64 i64Value);
//�����û�����
bool CGameUserInfo::ChangePoint(__int64 dwPoint, __int64 dwTaxCom,bool bWin, bool bLost, bool bMid, bool bCut, long int dwPlayCount, __int64 &dwMoney)
{
	if (m_bAccess)
	{
		CString stime;
		stime.Format("%d",CTime::GetCurrentTime());
		int curtime=atoi(stime);
		__int64 i64Tmp = 0;

		//��������
		m_UserData.dwExperience++;
		m_dwPlayCount+=dwPlayCount;

		i64Tmp = m_UserData.dwPoint;

		//�޸� �û���Ϣ�ĵĻ���Ӧ�üӱ�
		if(m_UserData.iDoublePointTime>curtime && dwPoint>0)
		{
			i64Tmp += (dwPoint*2);
			m_ChangePoint.dwPoint+=(dwPoint*2);
		}
		else if(m_UserData.iProtectTime>curtime && dwPoint<0)
		{
			i64Tmp += 0;
		}
		else
		{
			i64Tmp += dwPoint;
			m_ChangePoint.dwPoint+=dwPoint;
		}
		m_UserData.dwPoint = I64ToInt(i64Tmp);

		/// Money����
		m_UserData.i64Money += dwMoney;
		int nResultMoney = I64ToInt(i64Tmp);
		if(m_UserData.i64Money<=0)
		{
			m_UserData.i64Money=0;
		}

		/// m_Changepoint.dwMoney����
		i64Tmp = m_ChangePoint.dwMoney;
		i64Tmp +=dwMoney;
		m_ChangePoint.dwMoney = I64ToInt(i64Tmp);
		/// m_ChangePoint.dwTaxCom����
		i64Tmp = m_ChangePoint.dwTaxCom;
		i64Tmp +=dwTaxCom;
		m_ChangePoint.dwTaxCom = I64ToInt(i64Tmp);

		//���÷���
		if (bWin==true)
		{
			m_UserData.uWinCount++;
			m_ChangePoint.uWinCount++;
		}
		if (bLost==true) 
		{
			m_UserData.uLostCount++;
			m_ChangePoint.uLostCount++;
		}
		if (bMid==true) 
		{
			m_UserData.uMidCount++;
			m_ChangePoint.uMidCount++;
		}
		if (bCut==true) 
		{
			m_UserData.uCutCount++;
			m_ChangePoint.uCutCount++;
		}
		return true;
	}
	return false;
}

//�����û�����
bool CGameUserInfo::SetMD5Pass(char szMD5Pass[50])
{
	if (m_bAccess)
	{
		CopyMemory(m_szMD5Pass,szMD5Pass,sizeof(m_szMD5Pass));
		return true;
	}
	return false;
}

//�����û�ԭ����
bool CGameUserInfo::SetUserScrPoint(int dwScrPoint)
{
	if (m_bAccess)
	{
		m_dwScrPoint=dwScrPoint;
		return true;
	}
	return false;
}
bool CGameUserInfo::SetUserSendedMoeny(int dwSendMoney)
{
	if (m_bAccess)
	{
		m_UserData.i64Money+=dwSendMoney;
		return true;
	}
	return false;

}

//{add by rongqiufen 2010.06.29
///���������û����ŶӶ����е�Ȩֵ
int CGameUserInfo::GetWeigth()
{
	///VIP�û���Ȩ
	CBcfFile fConf(CBcfFile::GetAppPath()+"Function.bcf");
	int vipAddWeight = fConf.GetKeyVal("OnlineCoin","VipAddWeight", 0);

	int x = m_SelectWeight;
	if (m_UserData.userType >= 2) 
		x += vipAddWeight * 50;
	return x;
}
//add by rongqiufen 2010.06.29}


//�����û���Ϣ
bool CGameUserInfo::SetUserData(UserInfoStruct & UserInfo, UINT uSocketIndex, DWORD dwHandleID, long int dwGamePower, long int dwMasterPower, long int dwAccessLogID)
{
	m_bAccess=true;
	m_UserData=UserInfo;
	m_dwHandleID=dwHandleID;
	m_uSocketIndex=uSocketIndex;
	m_dwAccessLogID=dwAccessLogID;
	m_dwGamePower=dwGamePower;
	m_dwMasterPower=dwMasterPower;
	m_dwLogonTime=(long int)time(NULL);
	memset(&m_ChangePoint,0,sizeof(m_ChangePoint));


	m_SelectWeight = 0;

	return true;
}

//�����û���Ϣ
bool CGameUserInfo::CleanData()
{
	m_bAccess=false;
	m_dwLogonTime=0L;
	m_dwHandleID=0L;
	m_dwScrPoint=0L;
	m_dwAccessLogID=0L;
	m_dwGamePower=0L;
	m_dwMasterPower=0L;
	m_uSocketIndex=ERROR_SOCKET_INDEX;
	memset(&m_Rule,0,sizeof(m_Rule));
	memset(&m_UserData,0,sizeof(m_UserData));
	memset(m_szMD5Pass,0,sizeof(m_szMD5Pass));
	memset(&m_ChangePoint,0,sizeof(m_ChangePoint));
	return true;
}

//��ȡ�û��ܾ���
UINT CGameUserInfo::GetUserAllCount()
{
	return m_UserData.uWinCount+m_UserData.uLostCount+m_UserData.uMidCount+m_UserData.uCutCount;
}

//��ȡ�û���Ϣ
UserInfoStruct * CGameUserInfo::GetUserData(UserInfoStruct * pUserInfoStruct)
{
	if (m_bAccess)
	{
		if (pUserInfoStruct!=NULL)	*pUserInfoStruct=m_UserData;
		return &m_UserData;
	}
	return NULL;
}

//��ȡ��������
UserChangePoint * CGameUserInfo::GetChangePointInfo(UserChangePoint * pChangePoint)
{
	if (m_bAccess)
	{
		if (pChangePoint!=NULL)	*pChangePoint=m_ChangePoint;
		return &m_ChangePoint;
	}
	return NULL;
}

//�Աȹ����Ƿ��ʺ�
bool CGameUserInfo::IsFixRule(UserRuleStruct * pRule, UserInfoStruct * pCheckUserInfo, BYTE & bErrorResult)
{
	if ((m_bAccess==false)||(pCheckUserInfo==NULL)) return false;

	//������Ч��
	if ((m_Rule.bLimitCut)&&(pCheckUserInfo->uCutCount>0))
	{
		double dwAllCount=(double)(pCheckUserInfo->uWinCount+pCheckUserInfo->uLostCount+pCheckUserInfo->uCutCount);
		if ((BYTE)((double)pCheckUserInfo->uCutCount*100.0/(double)dwAllCount)>m_Rule.bCutPercent) 
		{
			bErrorResult=ERR_GR_CUT_HIGH;
			return false;
		}
	}

    // PengJiLin, 2010-9-14, �ȽϹ����еĻ��ֱȽ��Ƿ��Ϊ��ұȽ�
    if(m_Rule.bLimitPoint & 0x80)
    {
        if (pCheckUserInfo->i64Money>=m_Rule.dwHighPoint)
        {
            bErrorResult=ERR_GR_POINT_HIGH;
            return false;
        }
        if (pCheckUserInfo->i64Money<=m_Rule.dwLowPoint)
        {
            bErrorResult=ERR_GR_POINT_LOW;
            return false;
        }
    }

	if(m_Rule.bLimitPoint & 0x40)
    {
        //����Ч��
		if (pCheckUserInfo->dwPoint>=m_Rule.dwHighPoint)
		{
			bErrorResult=ERR_GR_POINT_HIGH;
			return false;
		}
		if (pCheckUserInfo->dwPoint<=m_Rule.dwLowPoint)
		{
			bErrorResult=ERR_GR_POINT_LOW;
			return false;
		}
    }

	return true;
}

//���ù���
bool CGameUserInfo::SetRule(UserRuleStruct * pRule)
{
	if (m_bAccess==true)	
	{
		m_Rule=*pRule;
		return true;
	}
	return false;
}

/*********************************************************************************************************************/

//���캯��
CGameUserInfoManage::CGameUserInfoManage(void)
{
	m_uOnLineCount=0;
	return;
}

//��������
CGameUserInfoManage::~CGameUserInfoManage(void)
{
	return;
}

//��ʼ������
bool CGameUserInfoManage::Init(UINT uMaxOnLineCount, UINT uMaxNetCutCount, UINT uVipReseverCount)
{
	
	m_uOnLineCount=0;
	if (m_OnLineUserInfo.Init(uMaxOnLineCount,uVipReseverCount)==false) return false;
	if (m_NetCutUserInfo.Init(uMaxNetCutCount,uVipReseverCount)==false) return false;
	return true;
}

//ȡ����ʼ��
bool CGameUserInfoManage::UnInit()
{
	m_uOnLineCount=0;
	m_OnLineUserInfo.UnInit();
	m_NetCutUserInfo.UnInit();
	return true;
}

//�����û�
CGameUserInfo * CGameUserInfoManage::FindOnLineUser(long int dwUserID)
{
	UINT uFindCount=0;
	for (UINT i=0;i<m_OnLineUserInfo.GetPermitCount();i++)
	{
		if (uFindCount>=m_uOnLineCount) return NULL;
		CGameUserInfo * pGameUserInfo=m_OnLineUserInfo.GetArrayItem(i);
		if ((pGameUserInfo!=NULL)&&(pGameUserInfo->IsAccess()))
		{
			if ((pGameUserInfo->m_UserData.dwUserID==dwUserID)) return pGameUserInfo;
			uFindCount++;
		}
	}
	return NULL;
}

//�����û�
CGameUserInfo * CGameUserInfoManage::FindOnLineUser(char * szName)
{
	UINT uFindCount=0;
	for (UINT i=0;i<m_OnLineUserInfo.GetPermitCount();i++)
	{
		if (uFindCount>=m_uOnLineCount) return NULL;
		CGameUserInfo * pGameUserInfo=m_OnLineUserInfo.GetArrayItem(i);
		if ((pGameUserInfo!=NULL)&&(pGameUserInfo->IsAccess()))
		{
			if (lstrcmp(pGameUserInfo->m_UserData.szName,szName)==0) return pGameUserInfo;
			uFindCount++;
		}
	}
	return NULL;
}

//�����û�
CGameUserInfo * CGameUserInfoManage::FindNetCutUser(long int dwUserID)
{
	CGameUserInfo * pGameUserInfo=NULL;
	for (UINT i=0;i<m_NetCutUserInfo.GetActiveCount();i++)
	{
		pGameUserInfo=m_NetCutUserInfo.GetActiveItem(i);
		if ((pGameUserInfo!=NULL)&&(pGameUserInfo->IsAccess())&&
			(pGameUserInfo->m_UserData.dwUserID==dwUserID)) return pGameUserInfo;
	}
	return NULL;
}

//�����û�
CGameUserInfo * CGameUserInfoManage::FindNetCutUser(char * szName)
{
	CGameUserInfo * pGameUserInfo=NULL;
	for (UINT i=0;i<m_NetCutUserInfo.GetActiveCount();i++)
	{
		pGameUserInfo=m_NetCutUserInfo.GetActiveItem(i);
		if ((pGameUserInfo!=NULL)&&(pGameUserInfo->IsAccess()))
		{
			if (lstrcmp(pGameUserInfo->m_UserData.szName,szName)==0) return pGameUserInfo;
		}
	}
	return NULL;
}

//�����û�
CGameUserInfo * CGameUserInfoManage::ActiveUser(UserInfoStruct * pUserInfo, UINT uSocketIndex, DWORD dwHandleID, long int dwGamePower, long int dwMasterPower, long int lAccessLogID)
{
	CGameUserInfo * pActiveUserInfo=m_OnLineUserInfo.GetArrayItem(uSocketIndex);
	if (pActiveUserInfo!=NULL)
	{
		if (pActiveUserInfo->IsAccess()==false) m_uOnLineCount++;
		pActiveUserInfo->SetUserData(*pUserInfo,uSocketIndex,dwHandleID,dwGamePower,dwMasterPower,lAccessLogID);
	}
	return pActiveUserInfo;
}

//�ͷ��û�
bool CGameUserInfoManage::FreeUser(CGameUserInfo * pGameUserInfo, bool bOnLinePeople)
{
	bool bRet = false;
	UINT uUserID = pGameUserInfo->m_UserData.dwUserID;
	if (pGameUserInfo->IsAccess())
	{
		pGameUserInfo->CleanData();
		if (!bOnLinePeople)
		{
			bRet = m_NetCutUserInfo.FreeItem(pGameUserInfo);
		}
		if (!bRet)
		{
			--m_uOnLineCount;
		}
	}
	return bRet;
}

//ע���û�����
CGameUserInfo * CGameUserInfoManage::RegNetCutUser(CGameUserInfo * pNetCutUserInfo)
{
	CGameUserInfo * pRegUserInfo=NULL;
	for (UINT i=0;i<m_NetCutUserInfo.GetActiveCount();i++)
	{
		pRegUserInfo=m_NetCutUserInfo.GetActiveItem(i);
		if (pRegUserInfo->m_UserData.dwUserID==pNetCutUserInfo->m_UserData.dwUserID) return pNetCutUserInfo;
	}
	pRegUserInfo=m_NetCutUserInfo.NewItem();
	if (pRegUserInfo!=NULL)
	{
		CopyMemory(pRegUserInfo,pNetCutUserInfo,sizeof(CGameUserInfo));
		pRegUserInfo->m_dwHandleID=0L;
		pRegUserInfo->m_uSocketIndex=ERROR_SOCKET_INDEX;
		pRegUserInfo->m_UserData.bUserState=USER_CUT_GAME;
	}
	return pRegUserInfo;
}

//��ȡ�û�
CGameUserInfo * CGameUserInfoManage::GetOnLineUserInfo(UINT uIndex)
{
	if (uIndex<m_OnLineUserInfo.GetPermitCount())
	{
		CGameUserInfo * pUserInfo=m_OnLineUserInfo.GetArrayItem(uIndex);
		if ((pUserInfo!=NULL)&&(pUserInfo->IsAccess()))	return pUserInfo;
	}
	return NULL;
}

//��ȡ�����û� 
UINT CGameUserInfoManage::FillOnLineUserInfo(char * pOnLineBuffer, UINT uBufferSize, UINT & uIndex, UINT & uFillCount, bool & bFinish)
{
	////wushuqun 2009.5.22
	//::OutputDebugString("���� CGameUserInfoManage::FillOnLineUserInfo: ��ȡ�����û�-��ʼ");
	//Ѱ�ҿ�������
	UINT uCopyPos=0;
	CGameUserInfo * pGameUserInfo=NULL;
	//wushuqun 2009.5.22
	//�Ż�ѭ��
	//��ȡ������Ŀ
	UINT perMitCount = 0;
	UINT nUserInfoSize = 0;
	perMitCount = m_OnLineUserInfo.GetPermitCount();
	//�û��ṹ���С
	nUserInfoSize = sizeof(UserInfoStruct);

	while ((uIndex < perMitCount)&&(((uCopyPos+1)*nUserInfoSize)<=uBufferSize))
	{
		if (uFillCount>=m_uOnLineCount) break;
		pGameUserInfo=m_OnLineUserInfo.GetArrayItem(uIndex++);
		// �����GM��������������Ϣ
		if ((pGameUserInfo!=NULL)&&(pGameUserInfo->IsAccess()) && (pGameUserInfo->m_UserData.bGameMaster==0))
		{
			UserInfoStruct * pOnLineUser=(UserInfoStruct *)(pOnLineBuffer+uCopyPos*sizeof(UserInfoStruct));
			*pOnLineUser=pGameUserInfo->m_UserData;
			uCopyPos++,uFillCount++;
		}
	}

	//�������
	bFinish=((uFillCount>=m_uOnLineCount)||(uIndex>=m_OnLineUserInfo.GetPermitCount()));
	return uCopyPos;
}

//��ȡ�����û� 
UINT CGameUserInfoManage::FillNetCutUserInfo(char * pNetCutBuffer, UINT uBufferSize, UINT & uBeginPos, bool & bFinish)
{
	//Ѱ�ҿ�������
	UINT uCopyPos=0;
	CGameUserInfo * pGameUserInfo=NULL;
	while (((uCopyPos+1)*sizeof(UserInfoStruct))<=uBufferSize)
	{
		if ((uBeginPos+uCopyPos)>=m_NetCutUserInfo.GetActiveCount()) break;
		pGameUserInfo=m_NetCutUserInfo.GetActiveItem(uBeginPos+uCopyPos);
		if (pGameUserInfo!=NULL) 
		{
			UserInfoStruct * pNetCutUser=(UserInfoStruct *)(pNetCutBuffer+uCopyPos*sizeof(UserInfoStruct));
			*pNetCutUser=pGameUserInfo->m_UserData;
		}
		uCopyPos++;
	}

	//�������
	uBeginPos+=uCopyPos;
	bFinish=(uBeginPos>=m_NetCutUserInfo.GetActiveCount());
	return uCopyPos;
}

/*********************************************************************************************************************/
