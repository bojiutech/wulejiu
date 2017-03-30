#include "StdAfx.h"
#include "GameDesk.h"
#include "UserPower.h"
#include "GameRoomLogonDT.h"
#include <valarray>
#include "GameRoomMessage.h"
#include"..\common\WriteLog.h"
#include "commonuse.h"
#include "MD5.h"
#include <iphlpapi.h>
#pragma comment(lib, "IPHLPAPI.lib")
//#include "AFCClass.h"
//�궨��
#define IDT_CHECK_DESK				1L										//��ɢ����
#define TIME_PLAY					30L										//Ĭ�ϵȴ�ʱ�䣨�룩
#define TIME_CUT					180000L									//���ߵȴ�ʱ�䣨���룩
#define IDT_USER_CUT				2L										//���߶�ʱ�� ID
#define NET_CUT_TIMES				3										//���ߴ���
//���캯��
CGameDesk::CGameDesk(BYTE bBeginMode) : m_bBeginMode(bBeginMode)
{
	m_bLock=false;
	m_bPlayGame=false;
	m_bMaxPeople=0;
	m_bDeskIndex=0;
	m_szLockPass[0]=0;
	m_dwOwnerUserID=0L;
	m_dwZhuangjiaUserID = 0L;
	m_DeskBasePoint=0;
	m_bGameStation=0;	
	m_bEnableWatch=0;
	m_pDataManage=NULL;
	m_bWaitTime=TIME_PLAY;
	m_dwBeginTime=(long int)time(NULL);
	m_dwTax=0;
	memset(m_bCutGame,0,sizeof(m_bCutGame));
	memset(m_uCutTime,0,sizeof(m_uCutTime));
	memset(m_bConnect,0,sizeof(m_bConnect));
	memset(m_pUserInfo,0,sizeof(m_pUserInfo));
	memset(m_dwScrPoint,0,sizeof(m_dwScrPoint));
	memset(m_pMatchInfo,0,sizeof(m_pMatchInfo));
	memset(m_bBreakCount,0,sizeof(m_bBreakCount));
	memset(m_dwGameUserID,0,sizeof(m_dwGameUserID));
	memset(m_dwChangePoint,0,sizeof(m_dwChangePoint));
	memset(m_dwChangeMoney,0,sizeof(m_dwChangeMoney));
	memset(m_dwTaxCom,0,sizeof(m_dwTaxCom));
	memset(m_GRM_Key,0,sizeof(m_GRM_Key));
	memset(m_GRM_Key_win,0,sizeof(m_GRM_Key_win));
	memset(m_GRM_Key_los,0,sizeof(m_GRM_Key_los));
	m_byDoublePointEffect = 0;

	m_bhavevideo = false;
	m_videoip = "127.0.0.1";
	m_videoport = 6677;
	m_audioport = 7766;

	m_bIsVirtualLock = false; //yjj 090325

	m_iVipGameCount=0;		//�������Ӿ���
	m_bIsBuy=false;			//�Ƿ񱻹���
	m_iDeskMaster=0;
	m_iRunGameCount=0;		//��Ϸ���еľ���
	m_iDissmissAgreePeople=0;
	m_nDeskRunOutID = 0;
	memset(m_szDeskPassWord,0,sizeof(m_szDeskPassWord));
	CString sPath=CBcfFile::GetAppPath();
	CBcfFile fsr(sPath + "SpecialRule.bcf");

	for(int i = 0;i< 10;i++)
	{
		CString cs;
		cs.Format("Fish_%d",i+1);
		m_dwFishGamesNameID[i] = fsr.GetKeyVal(_T("FishType"),cs,0);
	}
	fsr.CloseFile();

	//��ʼ����
	::InitializeCriticalSection(&m_csLock_);//�ټ��� add by wlr 20090714
}

//��������
CGameDesk::~CGameDesk(void)
{
	::DeleteCriticalSection(&m_csLock_);//�ټ��� add by wlr 20090714
}
int CGameDesk::CanSitDesk(MSG_GR_S_UserSit * pUserSit, CGameUserInfo * pUserInfo)
{
	//Ч������ 
	ASSERT(pUserInfo!=NULL);

	CGameUserInfo * pUser = dynamic_cast<CGameUserInfo *>(m_pUserInfo[pUserSit->bDeskStation]);
	//Ч��״̬
	if (pUser !=NULL && DESK_TYPE_BJL!=m_uDeskType)
	{
		//�˴����ٴ���ԭ��
		if (pUser)
		{
			::DebugPrintf("ERR_GR_ALREAD_USER ��¼:��� %s,���״̬:%d,",pUser->m_UserData.nickName,pUser->m_UserData.bUserState);							
		}
		return ERR_GR_ALREAD_USER;
	}

	//�ټ���
	if (DESK_TYPE_BJL==m_uDeskType)
	{
		pUserSit->bDeskStation = FindStation(pUserInfo);

		if (m_bMaxPeople <= pUserSit->bDeskStation)
		{
			return ERR_GR_DESK_FULL;
		}
	}
	else
	{
		bool _flag = true;
		for (BYTE i=0;i<m_bMaxPeople;i++)
		{
			if(m_pUserInfo[i]==NULL) 
			{
				_flag = false;
				break;
			}
		}

		if(IsPlayingByGameStation() && _flag) return ERR_GR_BEGIN_GAME;

		if (m_pUserInfo[pUserSit->bDeskStation]!=NULL)
			return ERR_GR_ALREAD_USER;

		if (m_pDataManage->m_InitData.dwRoomRule & GRR_LIMIT_SAME_IP)
		{
			if (pUserInfo->m_UserData.bGameMaster == 0)
			{
				for (BYTE i = 0; i < m_bMaxPeople; ++i)
				{
					if (m_pUserInfo[i] != NULL)
					{
						if (m_pUserInfo[i]->m_UserData.dwUserIP == pUserInfo->m_UserData.dwUserIP)
						{
							return ERR_GR_IP_SAME;
						}
					}
				}
			}
		}

		int peopleCnt = 0; ///< �鿴һ�������ж��ٸ��ˣ����û��������Ҫ����
		//����IP��ͬ����IPǰ��λ������Ϸ
		for (BYTE i=0;i<m_bMaxPeople;i++)
		{
			ULONG dwUserIP=pUserInfo->m_UserData.dwUserIP;
			if(m_pUserInfo[i]==NULL)
				continue;
			peopleCnt++;
			if (pUserInfo->m_Rule.bIPLimite||m_pUserInfo[i]->m_Rule.bIPLimite)
			{
				//����IPǰ3λ��ͬ������Ϸ������������Լ���ѭ��������
				if((pUserInfo->m_Rule.bIPLimite>=3 || m_pUserInfo[i]->m_Rule.bIPLimite>=3) &&
					FOURTH_IPADDRESS(m_pUserInfo[i]->m_UserData.dwUserIP)==FOURTH_IPADDRESS(dwUserIP))
					return ERR_GR_IP_SAME_3;
				//����IPǰ4λ��ͬ������Ϸ������������Լ���ѭ��������
				//��¼��4λIP
				CString szBuffer;
				int sz1,sz2;
				szBuffer.Format(TEXT("%d"),THIRD_IPADDRESS(dwUserIP));
				sz1 = szBuffer.GetAt(1);
				if(pUserInfo->m_Rule.bIPLimite==4||m_pUserInfo[i]->m_Rule.bIPLimite==4)
				{
					szBuffer.Format(TEXT("%d"),THIRD_IPADDRESS(m_pUserInfo[i]->m_UserData.dwUserIP));
					sz2 = szBuffer.GetAt(1);
					if(sz1==sz2 && 
						FOURTH_IPADDRESS(m_pUserInfo[i]->m_UserData.dwUserIP)==FOURTH_IPADDRESS(dwUserIP))
						return ERR_GR_IP_SAME_4;
				}
			}
		}

		//�ж��Ƿ�����λ��
		if (m_pDataManage->m_InitData.uComType!=TY_MATCH_GAME)
		{
			//��ҳ�����Ч��
			if ((m_pDataManage->m_InitData.uComType==TY_MONEY_GAME)&&
				(m_pDataManage->m_InitData.uLessPoint!=0)&&
				(pUserInfo->m_UserData.i64Money<m_pDataManage->m_InitData.uLessPoint))
			{
				return ERR_GR_POINT_LIMIT;
			}

			//����Ч��
			if (CUserPower::CanThrowPass(pUserInfo->m_dwGamePower) == false && m_bLock)
			{
				if (lstrcmp(m_szLockPass,pUserSit->szPassword) != 0)
					return ERR_GR_PASS_ERROR;
			}

			//�ж��û�����
			if (CUserPower::CanThrowSet(pUserInfo->m_dwGamePower)==false)
			{
				BYTE bErrorCode=0;
				for (BYTE i=0;i<m_bMaxPeople;i++)
				{
					if ((m_pUserInfo[i]!=NULL)&&(m_pUserInfo[i]->IsFixRule(&pUserInfo->m_Rule,
						&pUserInfo->m_UserData,bErrorCode)==false))
						return bErrorCode;
				}
			}
		}
	}
	return ERR_GR_SIT_SUCCESS;
}


//�û�������Ϸ��
BYTE CGameDesk::UserSitDesk(MSG_GR_S_UserSit * pUserSit, CGameUserInfo * pUserInfo)
{
	//Ч������ 
	ASSERT(pUserInfo!=NULL);

	CGameUserInfo * pUser = dynamic_cast<CGameUserInfo *>(m_pUserInfo[pUserSit->bDeskStation]);
	//Ч��״̬
	if (pUser !=NULL && DESK_TYPE_BJL!=m_uDeskType)
	{
		//wushuqun 2009.6.30
		//�˴����ٴ���ԭ��
		if (pUser)
		{
			::DebugPrintf("ERR_GR_ALREAD_USER ��¼:��� %s,���״̬:%d,",pUser->m_UserData.nickName,pUser->m_UserData.bUserState);							
		}

		return ERR_GR_ALREAD_USER;
	}

	if(m_pDataManage->m_bBuyRoom)
	{
		if(strlen(m_szDeskPassWord)<=0 || strlen(pUserSit->szVipPassWord)<=0 || 0!=strcmp(m_szDeskPassWord,pUserSit->szVipPassWord))
		{
			return ERR_GR_ALREAD_USER;
		}
	}

	//�ټ��� add by wlr 20090714
	if (DESK_TYPE_BJL==m_uDeskType)
	{
		pUserSit->bDeskStation = FindStation(pUserInfo);

		if (m_bMaxPeople <= pUserSit->bDeskStation)
		{
			return ERR_GR_DESK_FULL;
		}
	}//end of �ټ��� add by wlr 20090714
	else
	{
		bool _flag = true;
		for (BYTE i=0;i<m_bMaxPeople;i++)
		{
			if(m_pUserInfo[i]==NULL) 
			{
				_flag = false;
				break;
			}
		}
		/// ������Ϸ����Ҫ��������Ҷ�׼���ú�ſ�ʼ��Ϸ�����ֻ�������ж��Ƿ�������Ϸ��
		//���ǲ������������Ϸ�����н�����sdp2014-05-07
		CString ctext;
		ctext.Format("%d",m_pDataManage->m_DllInfo.uNameID);

		if (ctext.Left(3) == "300" && ctext.GetAt(4) == '0')
		{
			if(_flag) 
				return ERR_GR_BEGIN_GAME;
		}
		else
		{
			if(IsPlayingByGameStation() && _flag) 
				return ERR_GR_BEGIN_GAME;
		}

		//Ч��״̬
		if (m_pUserInfo[pUserSit->bDeskStation]!=NULL)
			return ERR_GR_ALREAD_USER;

		//�ж� IP ����///////////////////////////////////
		//����IP��ͬ������Ϸ��bSameIP���Ǵ����Ƿ����˲����IP��ͬ������Ϸ
		//Deleted by JianGuankun��������Ӱ����ҷ������õ��жϣ���ɾ��
		
		//���������IP���䣬�����ϸ���ұȶ�IP,IP������һ�������ͬ,�򷵻�ERR_GR_IP_SAME
		//Added by JianGuankun 2011.11.24
		if (m_pDataManage->m_InitData.dwRoomRule & GRR_LIMIT_SAME_IP)
		{
			if (pUserInfo->m_UserData.bGameMaster == 0)
			{
				for (BYTE i = 0; i < m_bMaxPeople; ++i)
				{
					if (m_pUserInfo[i] != NULL)
					{
						if (m_pUserInfo[i]->m_UserData.dwUserIP == pUserInfo->m_UserData.dwUserIP)
						{
							return ERR_GR_IP_SAME;
						}
					}
				}
			}
		}
		//End Add


		int peopleCnt = 0; ///< �鿴һ�������ж��ٸ��ˣ����û��������Ҫ����
		//����IP��ͬ����IPǰ��λ������Ϸ
		for (BYTE i=0;i<m_bMaxPeople;i++)
		{
			ULONG dwUserIP=pUserInfo->m_UserData.dwUserIP;
			if(m_pUserInfo[i]==NULL)
				continue;
			peopleCnt++;
			if (pUserInfo->m_Rule.bIPLimite||m_pUserInfo[i]->m_Rule.bIPLimite)
			{
				//����IPǰ3λ��ͬ������Ϸ������������Լ���ѭ��������
				if((pUserInfo->m_Rule.bIPLimite>=3 || m_pUserInfo[i]->m_Rule.bIPLimite>=3) &&
					FOURTH_IPADDRESS(m_pUserInfo[i]->m_UserData.dwUserIP)==FOURTH_IPADDRESS(dwUserIP))
					return ERR_GR_IP_SAME_3;
				//����IPǰ4λ��ͬ������Ϸ������������Լ���ѭ��������
				//��¼��4λIP
				CString szBuffer;
				int sz1,sz2;
				szBuffer.Format(TEXT("%d"),THIRD_IPADDRESS(dwUserIP));
				sz1 = szBuffer.GetAt(1);
				if(pUserInfo->m_Rule.bIPLimite==4||m_pUserInfo[i]->m_Rule.bIPLimite==4)
				{
					szBuffer.Format(TEXT("%d"),THIRD_IPADDRESS(m_pUserInfo[i]->m_UserData.dwUserIP));
					sz2 = szBuffer.GetAt(1);
					if(sz1==sz2 && 
						FOURTH_IPADDRESS(m_pUserInfo[i]->m_UserData.dwUserIP)==FOURTH_IPADDRESS(dwUserIP))
						return ERR_GR_IP_SAME_4;
				}
			}
		}
		/////////////////////////////////////////////////////////////////////
		if (0 == peopleCnt)
			m_bLock = false;

		//�ж��Ƿ�����λ��
		if (m_pDataManage->m_InitData.uComType!=TY_MATCH_GAME)
		{
			//��ҳ�����Ч��
			if ((m_pDataManage->m_InitData.uComType==TY_MONEY_GAME)&&
				(m_pDataManage->m_InitData.uLessPoint!=0)&&
				(pUserInfo->m_UserData.i64Money<m_pDataManage->m_InitData.uLessPoint))
				return ERR_GR_POINT_LIMIT;

			//����Ч��
			if ((m_bLock==true)&&(CUserPower::CanThrowPass(pUserInfo->m_dwGamePower)==false))
			{
				if (lstrcmp(m_szLockPass,pUserSit->szPassword)!=0)//20081205
					return ERR_GR_PASS_ERROR;
			}

			//�ж��û�����
			if (CUserPower::CanThrowSet(pUserInfo->m_dwGamePower)==false)
			{
				BYTE bErrorCode=0;
				for (BYTE i=0;i<m_bMaxPeople;i++)
				{
					if ((m_pUserInfo[i]!=NULL)&&(m_pUserInfo[i]->IsFixRule(&pUserInfo->m_Rule,
						&pUserInfo->m_UserData,bErrorCode)==false)) return bErrorCode;
				}
			}
		}

		//���¹���
		UINT uSitCount=0;
		for (BYTE i=0;i<m_bMaxPeople;i++)
		{
			if(m_pUserInfo[i]!=NULL) uSitCount++;
		}


		if (uSitCount==0)
		{
			if (m_pDataManage->m_InitData.uComType==TY_MATCH_GAME)
			{
				m_bLock=false;
				m_dwOwnerUserID=0L;
				//m_DeskBasePoint=0;
			}
			else
			{
				m_bLock=(pUserInfo->m_Rule.bPass==TRUE);
				m_dwOwnerUserID=pUserInfo->m_UserData.dwUserID;
				//m_DeskBasePoint = pUserInfo->m_UserData.uDeskBasePoint;
			}
			if (m_bLock==true)
			{
				CopyMemory(m_szLockPass,pUserInfo->m_Rule.szPass,sizeof(m_szLockPass));
				m_szLockPass[sizeof(m_szLockPass)/sizeof(m_szLockPass[0])-1]=0;
			}
		}
	}
	//�����û�����
	m_bCutGame[pUserSit->bDeskStation] = false;
	m_uCutTime[pUserSit->bDeskStation]=0L;
	m_bConnect[pUserSit->bDeskStation]=false;
	m_pUserInfo[pUserSit->bDeskStation]=pUserInfo;
	m_bEnableWatch&=~(1<<pUserSit->bDeskStation);
	pUserInfo->m_UserData.bDeskNO=m_bDeskIndex;
	pUserInfo->m_UserData.bDeskStation=pUserSit->bDeskStation;
	pUserInfo->m_UserData.bUserState=USER_SITTING;
	
	
	//���ͷ�����Ϣ
	MSG_GR_R_UserSit UserSit;
	UserSit.bLock=m_bLock;
	UserSit.bDeskIndex=m_bDeskIndex;
	UserSit.bDeskStation=pUserSit->bDeskStation;
	UserSit.bUserState=USER_SITTING;
	UserSit.dwUserID=pUserInfo->m_UserData.dwUserID;
	UserSit.bIsDeskOwner=(m_dwOwnerUserID==pUserInfo->m_UserData.dwUserID);//��̨��
	
	if (!m_pDataManage->IsQueueGameRoom())
		m_pDataManage->m_TCPSocket.SendDataBatch(&UserSit,sizeof(UserSit),MDM_GR_USER_ACTION,ASS_GR_USER_SIT,ERR_GR_SIT_SUCCESS);

	KillTimer(IDT_CHECK_DESK);

	return ERR_GR_SIT_SUCCESS;
}


//�ټ���
//desc:����Ұ���λ��
//return:��ҵ�λ�ú�(0,1,2...)
BYTE CGameDesk::FindStation(CGameUserInfo * pUserInfo)
{
	BYTE i;

	::EnterCriticalSection(&m_csLock_);
	try
	{
		for (i=0;i<m_bMaxPeople;i++)
		{
			if(m_pUserInfo[i]!=NULL && m_pUserInfo[i]->m_UserData.bDeskStation == pUserInfo->m_UserData.bDeskStation)
			{
				return i;
			}
		}

		for (i=0;i<m_bMaxPeople;i++)
		{
			if(m_pUserInfo[i]==NULL)
			{
				m_pUserInfo[i]=pUserInfo;
				break;
			}
		}
	}
	catch (...)
	{
		::LeaveCriticalSection(&m_csLock_);
		throw; 
	}

	::LeaveCriticalSection(&m_csLock_);

	return i;
}

//---------------------------------------����Ϊ��ȡ��Ƶ�Ƿ������ļ�����-----------------------
/// ����ȫ�ֱ����еļ��ܷ�ʽ��ȡ�ü��ܺ�������ַ�����MD5
/// �����ﲻ��ָ��ĺϷ������ж�
/// @param szMD5Pass ���ܺ���ַ���
/// @param szSrcPass Դ�ַ���
/// @return ���ܺ���ַ���ָ��
TCHAR *GetCryptedPasswd(TCHAR *szMD5Pass, TCHAR *szSrcPass)
{
	unsigned char szMDTemp[16];
	TCHAR myKey = 'G';
	MD5_CTX Md5;
	Md5.MD5Update((unsigned char *)szSrcPass,lstrlen(szSrcPass));
	Md5.MD5Final(szMDTemp);
	for (int i = 0; i < 16; i ++) 
		wsprintf(&szMD5Pass[i * 2], "%02x", szMDTemp[i]^myKey);
	return szMD5Pass;
}
CString innerGetMac()
{
	CString retMac="";
	PIP_ADAPTER_INFO pAdapterInfo;
	PIP_ADAPTER_INFO pAdapter=NULL;
	DWORD dwRetVal=0;
	pAdapterInfo=(IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
	ULONG ulOutBufLen=sizeof(IP_ADAPTER_INFO);
	if(GetAdaptersInfo(pAdapterInfo,&ulOutBufLen)!=ERROR_SUCCESS)
	{
		free(pAdapterInfo);
		pAdapterInfo=(IP_ADAPTER_INFO*)malloc(ulOutBufLen);
	}
	if((dwRetVal=GetAdaptersInfo(pAdapterInfo,&ulOutBufLen))==NO_ERROR)
	{
		pAdapter=pAdapterInfo;
		CString temp;
		while(pAdapter)
		{
			if(pAdapter->Type==6)//pAdapter->Description�а���"PCI"Ϊ����������//pAdapter->Type��71Ϊ����������
			{
				for(UINT i=0;i<pAdapter->AddressLength;i++)
				{
					temp.Format("%02X",pAdapter->Address[i]);
					retMac+=temp;
					//	printf("%02X%c",pAdapter->Address[i],i==pAdapter->AddressLength-1?��n��:��-��);
				}
				break;
			}
			pAdapter=pAdapter->Next;
		}
	}
	if(pAdapterInfo)
		free(pAdapterInfo);
	return retMac;
}

//��ȡ��������غ���
CString coreGetCode()
{
	CString strRet="";
	CString str=innerGetMac(),s;
	if(str=="")
	{		
		return _T("");
	}

	int r=0;
	int l=str.GetLength();
	for(int i=0;i<l;i+=2)
	{
		int r1=0,r2=0;
		s=str.Mid(i,1);
		if(s>="0" && s<="9")
			r1=atoi(s);
		if(s=="A" || s=="a")	r1=10;
		if(s=="B" || s=="b")	r1=11;
		if(s=="C" || s=="c")	r1=12;
		if(s=="D" || s=="d")	r1=13;
		if(s=="E" || s=="e")	r1=14;
		if(s=="F" || s=="f")	r1=15;
		s=str.Mid(i+1,1);
		if(s>="0" && s<="9")
			r2=atoi(s);
		if(s=="A" || s=="a")	r2=10;
		if(s=="B" || s=="b")	r2=11;
		if(s=="C" || s=="c")	r2=12;
		if(s=="D" || s=="d")	r2=13;
		if(s=="E" || s=="e")	r2=14;
		if(s=="F" || s=="f")	r2=15;

		CString t;
		r+=r1*16+r2;
		srand(r);
		t.Format("%s%04X%s-",str.Mid(l-i-1,1),rand(),str.Mid(l-i-2,1));
		strRet+=t;
	}
	if(strRet.Right(1)=="-")strRet=strRet.Left(strRet.GetLength()-1);
	return strRet;
}
//---------------------------------------����Ϊ��ȡ��Ƶ�Ƿ������ļ�����-----------------------

//��ʼ������
bool CGameDesk::Init(BYTE bDeskIndex, BYTE bMaxPeople, CGameMainManage * pDataManage, UINT	uDeskType)//�ټ���lym
{
	m_bDeskIndex=bDeskIndex;
	m_bMaxPeople=bMaxPeople;
	m_pDataManage=pDataManage;
	if (pDataManage->m_InitData.dwRoomRule&GRR_ENABLE_WATCH) m_bEnableWatch=0xFF;
	if (pDataManage->m_InitData.dwRoomRule&GRR_UNENABLE_WATCH) m_bEnableWatch=0x00;
	//if (pDataManage->m_InitData.dwRoomRule&GRR_STOP_TIME_CONTROL) SetTimer(IDT_TIME_SERVICE_CONTROL, 1000);
	SetTableBasePoint(pDataManage->m_InitData.uBasePoint);
	m_uDeskType = uDeskType;//�ټ��� add by wlr 20090714
	InitDeskGameStation();

	//��ʼ����Ƶ��������Ϣ
	CString s = CINIFile::GetAppPath ();/////����·��
	CString nid;
	nid.Format("%d", m_pDataManage->m_KernelData.uNameID);
	CINIFile f( s +nid +"_s.ini");
	CString strPswd = f.GetKeyVal("videosrv","videocode","");
	CString strSrcCode;//ԭʼ��
	strSrcCode.Format(_T("%s%d"), coreGetCode(), pDataManage->m_KernelData.uNameID);
	TCHAR szMD5Pass[64];	memset(szMD5Pass, 0, 64);
	m_bhavevideo = !strcmp(strPswd, GetCryptedPasswd(szMD5Pass, strSrcCode.GetBuffer(strSrcCode.GetLength())));
	m_bhavevideo &= !m_pDataManage->IsQueueGameRoom();//�����׷���ͱ�������������Ƶ����
	m_videoip = f.GetKeyVal("videosrv","ip",m_videoip.c_str()).GetBuffer();	
	m_videoport = f.GetKeyVal("videosrv","videoport",m_videoport);
	m_audioport = f.GetKeyVal("videosrv","audioport",m_audioport);	

	return true;
}

//����Ƶ��������Ϣ���͵��ͻ���
void CGameDesk::send_video_ip(BYTE bDeskStation)
{
	if (!m_bhavevideo) return;
	SetVideoSrvStruct msg;
	strcpy(msg.szIP, m_videoip.c_str());
	msg.videoport = m_videoport;
	msg.audioport = m_audioport;
	SendGameData(bDeskStation,&msg,sizeof(msg),MDM_GM_GAME_FRAME,ASS_GM_SET_VIDEOADDR,0);
}

//�Ƿ������Թ�
bool CGameDesk::IsEnableWatch(BYTE bDeskStation)
{
	return ((m_bEnableWatch&(1<<bDeskStation))!=0);
}

//���ö�ʱ��
bool CGameDesk::SetTimer(UINT uTimerID, int uElapse)
{
	if (uTimerID>=TIME_SPACE) return false;
	return m_pDataManage->SetTimer(m_bDeskIndex*TIME_SPACE+uTimerID+TIME_START_ID,uElapse);
}

//ɾ����ʱ��
bool CGameDesk::KillTimer(UINT uTimerID)
{
	if (uTimerID>=TIME_SPACE) return false;
	return m_pDataManage->KillTimer(m_bDeskIndex*TIME_SPACE+TIME_START_ID+uTimerID);
}

//��ȡ��Ϸʱ��
long int CGameDesk::GetPlayTimeCount()
{
	if (m_bPlayGame==false) return 0L;
	return (long int)time(NULL)-m_dwBeginTime;
}

//�û������뿪
bool CGameDesk::UserNetCut(BYTE bDeskStation, CGameUserInfo * pLostUserInfo)
{
	//Ч������
	ASSERT(m_bCutGame[bDeskStation]==false);
	ASSERT(m_pUserInfo[bDeskStation]!=NULL);
	ASSERT(m_pUserInfo[bDeskStation]->m_UserData.dwUserID==pLostUserInfo->m_UserData.dwUserID);

	//��������
	m_bCutGame[bDeskStation]=true;
	m_bConnect[bDeskStation]=false;
	m_bBreakCount[bDeskStation]++;
	m_pUserInfo[bDeskStation]=pLostUserInfo;
	
	//�����û�������Ϣ
	if (m_bIsBuy)
	{
		MSG_GR_R_UserCut UserCut;
		UserCut.bDeskNO=m_bDeskIndex;
		UserCut.bDeskStation=bDeskStation;
		UserCut.dwUserID=pLostUserInfo->m_UserData.dwUserID;
		m_pDataManage->m_TCPSocket.SendDataBatch(&UserCut,sizeof(UserCut),MDM_GR_USER_ACTION,ASS_GR_USER_CUT,0);
	}
	
	if(m_bIsBuy)
	{
		int iCutPeople=0;
		for(int i=0;i<m_bMaxPeople;i++)
		{
			if(!m_pUserInfo[i] || !m_bCutGame[i])
			{
				continue;
			}
			iCutPeople++;
		}
		if(iCutPeople>=GetDeskPlayerNum())
		{
			KillTimer(IDT_CHECK_DESK);
			SetTimer(IDT_CHECK_DESK,3*60*1000);
		}
		else
		{
			//m_pDataManage->OnUserNetCutDissmiss(m_pUserInfo[bDeskStation]);
		}
	}
	//�趨��ʱ��
	if (DESK_TYPE_BJL!=m_uDeskType)	// ���ǰټ���������Ϸ�������ö�ʱ��
	{
		if (!m_bIsBuy)
		{
			m_uCutTime[bDeskStation]=(long int)time(NULL);
			SetTimer(IDT_USER_CUT+bDeskStation,TIME_CUT);
		}
	}
	else	// ����ǰټ������͵���Ϸ����ֱ������ҽ���������������ʱ��ID���ң�WServer����
	{
		if ((m_pUserInfo[bDeskStation]!=NULL)&&(m_bCutGame[bDeskStation]==true))
		{
			GameFinish(bDeskStation,GFF_FORCE_FINISH);
		}
	}
	
	return true;
}

//�û���������
bool CGameDesk::UserReCome(BYTE bDeskStation, CGameUserInfo * pNewUserInfo)
{
	//Ч������
	ASSERT(m_bCutGame[bDeskStation]==true);
	ASSERT(m_pUserInfo[bDeskStation]!=NULL);
	ASSERT(m_pUserInfo[bDeskStation]->m_UserData.dwUserID==pNewUserInfo->m_UserData.dwUserID);
	//��¼������������ ���ﲻ�������
	//DL_GR_I_CutNetRecord input_net;
	//input_net.bClear=true;
	//input_net.byDeskIndex=m_bDeskIndex;
	//input_net.iRoomID=m_pDataManage->m_InitData.uRoomID;
	//input_net.iUserID=m_pUserInfo[bDeskStation]->m_UserData.dwUserID;
	//m_pDataManage->m_SQLDataManage.PushLine(&input_net.DataBaseHead, sizeof(input_net), DTK_GR_CUTNETRECORD, 0, 0);
	//��������
	m_bCutGame[bDeskStation]=false;
	m_pUserInfo[bDeskStation]=pNewUserInfo;
	m_pUserInfo[bDeskStation]->m_UserData.bUserState=USER_PLAY_GAME;
	if (DESK_TYPE_BJL!=m_uDeskType)	// ���ǰټ���������Ϸ�������ö�ʱ��
		KillTimer(IDT_USER_CUT+bDeskStation);

	//{�û�����������Ҳ��ҪЩW��¼ 2009-4-28
	DL_GR_I_UserRecome userRecome;
	memset(&userRecome, 0, sizeof(userRecome));
	userRecome.lUserID = pNewUserInfo->m_UserData.dwUserID;
	m_pDataManage->m_SQLDataManage.PushLine(&userRecome.DataBaseHead,sizeof(userRecome),DTK_GR_USER_RECOME,0,0);
	//��ӽ���}

	//���ͷ�����Ϣ
	MSG_GR_R_UserSit UserSit;
	UserSit.bLock=m_bLock;
	UserSit.bDeskIndex=m_bDeskIndex;
	UserSit.bDeskStation=bDeskStation;
	UserSit.bUserState=USER_PLAY_GAME;
	UserSit.dwUserID=pNewUserInfo->m_UserData.dwUserID;
	m_pDataManage->m_TCPSocket.SendDataBatch(&UserSit,sizeof(UserSit),MDM_GR_USER_ACTION,ASS_GR_USER_SIT,ERR_GR_SIT_SUCCESS);

	KillTimer(IDT_CHECK_DESK);

	return true;
}

//���ñ�����Ϣ
bool CGameDesk::SetMatchInfo(BYTE bDeskStation, MatchInfoStruct * pMatchInfo, bool bNotify)
{
	ASSERT(bDeskStation<m_bMaxPeople);
	m_pMatchInfo[bDeskStation]=pMatchInfo;
	return true;
}

//�����������
bool CGameDesk::CleanCutGameInfo()
{
	for (BYTE i=0;i<m_bMaxPeople;i++)
	{
		if ((m_pUserInfo[i]!=NULL)&&(m_bCutGame[i]==true))
		{
			CString str;
			str.Format("cq::--------------1----------------�����������%d����", m_pUserInfo[i]->m_UserData.dwUserID);
			OutputDebugString(str);
			//��������
			if (DESK_TYPE_BJL!=m_uDeskType)	// ���ǰټ���������Ϸ�������ö�ʱ��
				KillTimer(IDT_USER_CUT+i);
			//�û��뿪
			CGameUserInfo * pUserInfo=m_pUserInfo[i];
			MakeUserOffLine(i);
			//������߱�־
			DL_GR_I_ClearOnlineFlag dtClearOnlineFlag;
			memset(&dtClearOnlineFlag, 0, sizeof(dtClearOnlineFlag));
			dtClearOnlineFlag.lUserID = pUserInfo->m_UserData.dwUserID;
			m_pDataManage->m_SQLDataManage.PushLine(&dtClearOnlineFlag.DataBaseHead, sizeof(dtClearOnlineFlag), DTK_GR_CLEAR_ONLINE_FLAG, 0, 0);
		}
		m_bCutGame[i]=false;
		if (m_pDataManage->m_InitData.dwRoomRule & GRR_CONTEST || m_pDataManage->m_InitData.dwRoomRule & GRR_TIMINGCONTEST)
		{
			if (m_pUserInfo[i] == NULL)
				continue;			
			m_pUserInfo[i]=NULL;
		}
	}

	return true;
}
//�������ָ�������������
bool CGameDesk::CleanCutGameInfo(BYTE bDeskStation)
{
	if ((m_pUserInfo[bDeskStation]!=NULL)&&(m_bCutGame[bDeskStation]==true))
	{
		//��������
		if (DESK_TYPE_BJL!=m_uDeskType)	// ���ǰټ���������Ϸ�������ö�ʱ��
			KillTimer(IDT_USER_CUT+bDeskStation);
		CString str;
		str.Format("cq::--------------2----------------�����������%d����", m_pUserInfo[bDeskStation]->m_UserData.dwUserID);
		OutputDebugString(str);
		//�û��뿪
		CGameUserInfo * pUserInfo=m_pUserInfo[bDeskStation];
		MakeUserOffLine(bDeskStation);
		//�����û�����
		//m_pDataManage->CleanUserInfo(pUserInfo);
		//m_pDataManage->m_UserManage.FreeUser(pUserInfo,false);
	}
	m_bCutGame[bDeskStation]=false;

	return true;
}

//��¼��Ϸ��Ϣ
bool CGameDesk::RecoderGameInfo(__int64 *ChangeMoney)
{
	if ((m_pDataManage->m_InitData.dwRoomRule&GRR_RECORD_GAME)!=0L)
	{
		memset(ChangeMoney,0,sizeof(ChangeMoney));
		//��������
		DL_GR_I_GameRecord GameRecord;
		memset(&GameRecord,0,sizeof(GameRecord));

		//д������
		GameRecord.dwTax=m_dwTax;//ÿ�����������ʵ��˰��
		GameRecord.bDeskIndex=m_bDeskIndex;
		GameRecord.uRoomID=m_pDataManage->m_InitData.uRoomID;
		GameRecord.dwBeginTime=m_dwBeginTime;

		int iCount =0;
		for (BYTE i=0;i<m_bMaxPeople;i++)
		{
			//DebugPrintf("m_pUserInfo[%d] = [%d]", i, m_pUserInfo[i]);
			//DebugPrintf("ChangeMoney[%d]=m_dwChangeMoney[%d] = [%d]", i, i, m_dwChangeMoney[i]);
			if(m_pUserInfo[i]== NULL)
				continue;

			ChangeMoney[i]=m_dwChangeMoney[i];
	
			//if (m_dwGameUserID[i]!=0L)
			{
				GameRecord.dwUserID[i]=m_pUserInfo[i]->m_UserData.dwUserID;
				GameRecord.dwScrPoint[i]=m_dwScrPoint[i]+m_dwChangePoint[i];
				GameRecord.dwTaxCom[i]=m_dwTaxCom[i];
				GameRecord.dwChangePoint[i]=m_dwChangePoint[i];
				GameRecord.dwChangeMoney[i]=m_dwChangeMoney[i];

				GameRecord.i64ScrMoney[i]=m_pUserInfo[i]->m_UserData.i64Money;
				iCount++;
			}
		}
		if (iCount > 0)
		{
			return m_pDataManage->m_SQLDataManage.PushLine(&GameRecord.DataBaseHead,sizeof(GameRecord),DTK_GR_RECORD_GAME,0,0);
		}
	}
	return true;
}

/// ������Ϸ��,20��
/// param void
/// return void
void CGameDesk::PresentCoin()
{/*
	DL_GR_I_SendMonet_By_Times sSendMoneyByTimes;//��ǰ�û�ΪҪ�͵��û�
	int iCurrentMoney; ///< ��ǰ�û��Ľ��
	COleDateTimeSpan ts1;
	COleDateTimeSpan ts2;
	COleDateTime CurrentTime = COleDateTime::GetCurrentTime(); ///< ��ǰʱ��
	ts1 = CurrentTime - m_pDataManage->m_InitData.StartPresentTime; ///< ��ǰʱ���Ƿ������ͽ�һʱ���ڡ�
	ts2 = m_pDataManage->m_InitData.EndPresentTime - CurrentTime;
	
	if (ts1.GetSeconds() > 0 &&
		ts2.GetSeconds() > 0 &&
		m_pDataManage->m_InitData.iCoinNum > 0 && ///< ���ͽ��������0
		m_pDataManage->m_InitData.iTimes > 0) ///< һ�����͵Ĵ���
	{
		for (BYTE i=0;i<m_bMaxPeople;i++)
		{
			if (NULL != m_pUserInfo[i])
			{
				iCurrentMoney = m_pUserInfo[i]->m_UserData.dwMoney + m_pUserInfo[i]->m_UserData.dwBank; ///< Ǯ��+����
				if (iCurrentMoney < m_pDataManage->m_InitData.uLowerLimit && ///< ��ǰ�����С���������ֵ��
					m_pDataManage->m_InitData.iTimes > m_pUserInfo[i]->m_UserData.nTimesSent) ///< �������ɴ�����
				{
					memset(&sSendMoneyByTimes,0,sizeof(sSendMoneyByTimes));
					sSendMoneyByTimes.dwUserID = m_pUserInfo[i]->m_UserData.dwUserID;
					sSendMoneyByTimes.dwGameFinishCount = 0;
					sSendMoneyByTimes.dwSrcGameMoney   = m_pUserInfo[i]->m_UserData.dwMoney;//Ǯ
					sSendMoneyByTimes.dwSrcMoneyInBank = m_pUserInfo[i]->m_UserData.dwBank;//����
					
					m_pUserInfo[i]->m_UserData.dwMoney += m_pDataManage->m_InitData.iCoinNum;
					m_pDataManage->m_SQLDataManage.PushLine(&sSendMoneyByTimes.DataBaseHead,sizeof(sSendMoneyByTimes),DTK_GR_SENDMONEY_TIMES,0,0);
					
					SendUserMoneyByTimes senResult;
					memset(&senResult,0,sizeof(senResult));
					senResult.dwAllSendTImes    = m_pDataManage->m_InitData.iTimes;
					senResult.dwSendFailedCause = 0;
					senResult.dwSendGameMoney   = m_pDataManage->m_InitData.iCoinNum;
					senResult.dwSendTimes       = ++m_pUserInfo[i]->m_UserData.nTimesSent;
					senResult.dwSrcGameMoney    = m_pUserInfo[i]->m_UserData.dwMoney;
					senResult.dwSrcMoneyInBank  = m_pUserInfo[i]->m_UserData.dwBank;
					senResult.dwUserID          = m_pUserInfo[i]->m_UserData.dwUserID;

					m_pDataManage->m_TCPSocket.SendDataBatch(&senResult,sizeof(senResult),MDM_GR_MONEY,ASS_GR_SENDMONEY_TIMES,0);
				}
			}
		}
	}*/
}

/// ��һ��__int64ת��Ϊint
int I64ToInt(__int64 i64Value)
{
	__int64 flag = i64Value & 0x8000000000000000;
	if (flag != 0)
	{
		/// �Ǹ���
		if (i64Value<0xFFFFFFFF80000001)
		{
			return 0x80000001;
		}
	}
	else
	{
		if (i64Value>0x7FFFFFFF)
		{
			return 0x7FFFFFFF;
		}
	}
	return i64Value & 0xFFFFFFFF;
}

bool CGameDesk::ChangeUserPointContest(__int64 *arPoint, bool *bCut, int nTaxIndex)
{
	__int64 arLoseMoney[MAX_PEOPLE];
	ZeroMemory(arLoseMoney, sizeof(arLoseMoney));

	MSG_GR_ContestChange _tmp;
	DL_GR_I_UserContestData _p;	
	bool bSomeOneNotEnoughMoney = false;
	// ����ֺܷͽ��
	__int64 i64TotalLosePoint = 0;
	__int64 i64TotalLoseMoney = 0;

	for (int i=0; i<m_bMaxPeople; ++i)
	{
		if (NULL==m_pUserInfo[i])
		{
			continue;
		}
		//�����ܹ������Ǯ
		if (arPoint[i] < 0)
		{			
			arLoseMoney[i] = arPoint[i]* m_pDataManage->m_InitData.uBasePoint;

			if (m_pUserInfo[i]->m_UserData.i64ContestScore < 0-arLoseMoney[i])
			{
				bSomeOneNotEnoughMoney = true;
				if (0 >= m_pUserInfo[i]->m_UserData.i64ContestScore)
				{
					//�������ûǮ
					arLoseMoney[i] = 0;					
				}
				else
				{
					//��������ϵ�Ǯ�۹�
					arLoseMoney[i] = 0 - m_pUserInfo[i]->m_UserData.i64ContestScore;
				}
			}
			m_pUserInfo[i]->m_UserData.i64ContestScore += arLoseMoney[i];
			m_pUserInfo[i]->m_UserData.iContestCount++;
			m_dwChangeMoney[i] = arLoseMoney[i];
			i64TotalLosePoint -= arPoint[i];
			i64TotalLoseMoney -= arLoseMoney[i];

			CString str;
			str.Format("cq:: ����-----User[%d] = %d ContestScore = %I64d arLoseMoney = %I64d",
				i,m_pUserInfo[i]->m_UserData.dwUserID,
				m_pUserInfo[i]->m_UserData.i64ContestScore,
				arLoseMoney[i]);
			OutputDebugString(str);

			_p.iUserID = m_pUserInfo[i]->m_UserData.dwUserID;
			_p.iLowChip = m_pDataManage->m_InitData.i64LowChip;
			_p.iCheckedScore = m_pUserInfo[i]->m_UserData.i64ContestScore;
			_p.ChangePoint = arPoint[i];
			_p.ChangeScore = arLoseMoney[i];
			_p.iContestID = m_pDataManage->m_InitData.iContestID;
			_p.iDeskNo = m_pUserInfo[i]->m_UserData.bDeskNO;
			_p.iSitNo = m_pUserInfo[i]->m_UserData.bDeskStation;
			_p.iRoomID = m_pDataManage->m_InitData.uRoomID;
			_p.iMatchID = m_pDataManage->m_InitData.iMatchID;
			_p.iGameID = m_pDataManage->m_InitData.iGameID;
			m_pDataManage->m_SQLDataManage.PushLine(&_p.DataBaseHead, sizeof(DL_GR_I_UserContestData), DTK_GR_UPDATE_CONTEST_RESULT, 0, 0);
		}
	}
	for (int i=0; i<m_bMaxPeople; ++i)
	{
		if (NULL==m_pUserInfo[i])
		{
			continue;
		}
		if (arPoint[i] > 0)
		{
			arLoseMoney[i] = arPoint[i]* m_pDataManage->m_InitData.uBasePoint;
			if (bSomeOneNotEnoughMoney)
			{
				if (i64TotalLosePoint != 0)
					arLoseMoney[i] = i64TotalLoseMoney*arPoint[i]/i64TotalLosePoint;
				else
					arLoseMoney[i] = 0;
			}
			m_pUserInfo[i]->m_UserData.i64ContestScore += arLoseMoney[i];
			m_pUserInfo[i]->m_UserData.iContestCount++;
			m_dwChangeMoney[i] = arLoseMoney[i];

			CString str;
			str.Format("cq:: ����-----User[%d] = %d ContestScore = %I64d arLoseMoney = %I64d",
				i,m_pUserInfo[i]->m_UserData.dwUserID,
				m_pUserInfo[i]->m_UserData.i64ContestScore,
				arLoseMoney[i]);
			OutputDebugString(str);

			_p.iUserID = m_pUserInfo[i]->m_UserData.dwUserID;
			_p.iLowChip = m_pDataManage->m_InitData.i64LowChip;
			_p.iCheckedScore = m_pUserInfo[i]->m_UserData.i64ContestScore;
			_p.ChangePoint = arPoint[i];
			_p.ChangeScore = arLoseMoney[i];
			_p.iContestID = m_pDataManage->m_InitData.iContestID;
			_p.iDeskNo = m_pUserInfo[i]->m_UserData.bDeskNO;
			_p.iSitNo = m_pUserInfo[i]->m_UserData.bDeskStation;
			_p.iRoomID = m_pDataManage->m_InitData.uRoomID;
			_p.iMatchID = m_pDataManage->m_InitData.iMatchID;
			_p.iGameID = m_pDataManage->m_InitData.iGameID;
			m_pDataManage->m_SQLDataManage.PushLine(&_p.DataBaseHead, sizeof(DL_GR_I_UserContestData), DTK_GR_UPDATE_CONTEST_RESULT, 0, 0);
		}
	}
	DL_GR_I_UserContestRank _p_rank;
	_p_rank.pUserIDs = NULL;
	_p_rank.iIDNums = 0;
	m_pDataManage->m_SQLDataManage.PushLine(&_p_rank.DataBaseHead, sizeof(DL_GR_I_UserContestRank), DTK_GR_GET_CONTEST_RESULT, 0, 0);
	return true;
}

bool CGameDesk::ChangeUserPointContest(int *arPoint, bool *bCut, int nTaxIndex)
{
	int arLoseMoney[MAX_PEOPLE];
	ZeroMemory(arLoseMoney, sizeof(arLoseMoney));

	MSG_GR_ContestChange _tmp;
	DL_GR_I_UserContestData _p;
	DL_GR_I_UserContestRank _p_rank;
	_p_rank.pUserIDs = new int[m_bMaxPeople];
	_p_rank.iIDNums = 0;
	if (_p_rank.pUserIDs)
	{
		::memset(_p_rank.pUserIDs,0,sizeof(int)*m_bMaxPeople);
		_p_rank.iIDNums = m_bMaxPeople;
	}

	OutputDebugString("DServer:CGameDesk::ChangeUserPointContest 32");

	for (int i=0; i<m_bMaxPeople; ++i)
	{
		if (NULL==m_pUserInfo[i])
		{
			continue;
		}

		_p_rank.pUserIDs[i] = m_pUserInfo[i]->m_UserData.dwUserID;

		/// ����Ӧ���߽���Ƿ�
		arLoseMoney[i] = arPoint[i]*m_DeskBasePoint;

		CString str;
		str.Format("DServer: User[%d] = %s ContestScore = %I64d arLoseMoney = %I64d",
			i,m_pUserInfo[i]->m_UserData.szName,
			m_pUserInfo[i]->m_UserData.i64ContestScore,
			arLoseMoney[i]);
		OutputDebugString(str);

		m_pUserInfo[i]->m_UserData.i64ContestScore += arLoseMoney[i];
		m_pUserInfo[i]->m_UserData.iContestCount++;
		m_dwChangeMoney[i] = arLoseMoney[i];


		_p.ChangePoint = arPoint[i];
		_p.ChangeScore = arLoseMoney[i];
		_p.iContestID = m_pDataManage->m_InitData.iContestID;
		_p.iDeskNo = m_pUserInfo[i]->m_UserData.bDeskNO;
		_p.iSitNo = m_pUserInfo[i]->m_UserData.bDeskStation;
		_p.iSitNo = m_pDataManage->m_InitData.uRoomID;
		m_pDataManage->m_SQLDataManage.PushLine(&_p.DataBaseHead, sizeof(DL_GR_I_UserContestData), DTK_GR_UPDATE_CONTEST_RESULT, 0, 0);
	}

	if (_p_rank.iIDNums > 0)
	{
		m_pDataManage->m_SQLDataManage.PushLine(&_p_rank.DataBaseHead, sizeof(DL_GR_I_UserContestRank), DTK_GR_GET_CONTEST_RESULT, 0, 0);
	}

	return true;
}

bool CGameDesk::ChangeUserPointint64(__int64 *arPoint, bool *bCut, int nTaxIndex,int iCount)
{
	/// ���㱾����ϷӮ����Ӯ��ҵ��ܺ�
	/// ���㱾����Ϸ��������ҵ��ܺ�
	/// �ж�ÿ��������ϵĽ���Ƿ��㹻��
	/// ������ҽ�Ҳ���֧������Ӯ��Ҫ��Ӧ��������
	/// ����m_pInfo���������ݣ�����Ϸ�ж�ȡ����ȷ��ֵ
	/// ͳһ��������ҵĽ������������ݿ�
	/// ������Ϣ���ͻ��ˣ���ʾ������Ǯ��ӮǮ��

	if (m_pDataManage->m_InitData.dwRoomRule & GRR_CONTEST || m_pDataManage->m_InitData.dwRoomRule & GRR_TIMINGCONTEST)
	{
		return ChangeUserPointContest(arPoint, bCut, nTaxIndex);
	}

	m_tEndTime = CTime::GetCurrentTime();
	__int64 iSendMoney = -1;
	if (m_pDataManage->m_InitData.iTimeLength >= 0 && m_pDataManage->m_InitData.iSendCount > 0)
	{
		iSendMoney = 0;
		if (m_tEndTime.GetTime() - m_tBeginTime.GetTime() >= m_pDataManage->m_InitData.iTimeLength)
		{
			iSendMoney = m_pDataManage->m_InitData.iSendCount;
		}
	}
	

	/// ȡ��ǰʱ��
	CString stime;
	stime.Format("%d",CTime::GetCurrentTime());
	int curtime=atoi(stime);

	/// �Ƿ�Ϊ��Ҷ�Ҫ��̨�ѵķ������һ�㶼ΪӮ�ҽ�̨��
	bool bIsAllNeedTax = (m_pDataManage->m_InitData.dwRoomRule & GRR_ALL_NEED_TAX) > 0;
	bool bTaxMain = false; ///< �Ƿ�ֻ��ׯ�ҿ�˰��

	bool bNotCostPoint = (m_pDataManage->m_InitData.dwRoomRule & GRR_NOT_COST_POINT) > 0; /// ��ҳ����ۻ���  add by lxl 2010-10-26

	BYTE i=0;	///< ѭ������

	/// ����ֺܷͽ��
	__int64 i64TotalLosePoint = 0;
	__int64 i64TotalWinPoint = 0;
	__int64 i64TotalLoseMoney = 0;
	__int64 i64TotalWinMoney = 0;

	/// ʵ������ж���
	int nTotalPlayerCount = 0;
	/// ����������ĸ�
	BYTE bCutDeskStation = 255;

	for (i=0; i<m_bMaxPeople; ++i)
	{
		if (m_pUserInfo[i] == NULL)
			continue;
		++nTotalPlayerCount;
		if (bCut[i])
		{
			bCutDeskStation = i;
		}

		if (!bTaxMain && nTaxIndex>=0)
		{
			if (i == nTaxIndex) ///< ֻ�۸���ҵ�˰��
			{
				bTaxMain = true;
			}
			if(nTaxIndex > 1000000) ///����ǳ����齫���򣬿���Ҫ��˰����� add by lxl 2010-12-14
			{
				bTaxMain = true;
			}
		}

	}

	__int64 arLoseMoney[MAX_PEOPLE];
	__int64 arTaxCount[MAX_PEOPLE];
	ZeroMemory(arLoseMoney, sizeof(arLoseMoney));
	ZeroMemory(arTaxCount, sizeof(arTaxCount));
	/// �û�ID����
	long arUserID[MAX_PEOPLE];
	ZeroMemory(arUserID, sizeof(arUserID));
	long arLogonTime[MAX_PEOPLE];
	ZeroMemory(arLogonTime, sizeof(arLogonTime));
	/// �Ƿ����˲���Ǯ
	bool bSomeOneNoEnoughMoney = false;

	__int64 i64Tmp = 1;	/// Ϊ�˷�ֹ���磬����һ��int64���͵��������д�ö��ǿ������ת��

	long int dwNowTime=(long int)time(NULL);

	if (m_pDataManage->m_nRate < 100)
	{
		m_pDataManage->m_nRate = 100;
	}


	/// ��ҳ�����Ҫ���㣬
	/// ����Ӧ����֣�����Ӧ�����Ӧ���Ǯ��ͬʱ�������ϵ�Ǯ�Ƿ�֧��
	if(m_pDataManage->m_InitData.uComType == TY_MONEY_GAME)
	{
		for (i=0; i<m_bMaxPeople; ++i)
		{
			if (NULL==m_pUserInfo[i])
			{
				continue;
			}
			/// ����Ӧ���߽���Ƿ�
			if (arPoint[i]<=0)
			{
				if(nTaxIndex > 1000000) //����������==����
				{
					arLoseMoney[i] = arPoint[i];
				}
				else
				{
					arLoseMoney[i] = arPoint[i]*m_DeskBasePoint;	///< ����Ϊ����
				}
					/// �ǲ��Ǵ�Ҷ�Ҫ��˰��������Ӯ
				if (bIsAllNeedTax && (m_pDataManage->m_InitData.uTax>0))
				{
					arTaxCount[i] = i64Tmp * m_pDataManage->m_InitData.uTax;
					arLoseMoney[i] -= arTaxCount[i];
				}

				/// ������ҵ�Ǯ�Ƿ��Ѿ�������
				if (m_pUserInfo[i]->m_UserData.i64Money < (0-arLoseMoney[i])) ///<Ǯ��������
				{
					bSomeOneNoEnoughMoney = true;
					if (m_pUserInfo[i]->m_UserData.i64Money <= 0) ///<�������Ӧ�ò������
					{
						arLoseMoney[i] = 0;	///< һ��Ǯ��û����
					}
					else
					{
						arLoseMoney[i] = 0-m_pUserInfo[i]->m_UserData.i64Money; ///< ��������ϵ�Ǯ���۹�
					}
				}

				/// �ܹ���ķ�����Ǯ����������˲���Ǯ����������Ӯ�ҷ���Ǯ�ı���
				i64TotalLosePoint -= arPoint[i];
				i64TotalLoseMoney -= arLoseMoney[i];
			}
		}
	}

	//�����齫��˰ add by lxl 2010-12-14
	int nCGTax = 0;
	//�����齫��˰Ԥ����  
	if(nTaxIndex > 1000000)
	{
		int nBasePoint; //��������
		int nPointRate; //�����ͽ�ҵı��� 
		int nTax;	    //˰��
		//��nTaxIndex = 1000100�������Ϊ100����1�� = 100�����
		nPointRate = nTaxIndex - 1000000;
		nBasePoint = 50;

		int nCount = 0; //Ҫ��˰������
		//ͳ��Ҫ��˰������,arPoint[8]����ǰ4��Ϊ��һ�����ֵ����4����ʾΪ�Ƿ��˰��1ΪҪ��˰��
		for(int i = 4; i < 8; i++)
		{
			if(arPoint[i] == 1)
				nCount++;
		}

		//��˰���㹫ʽ����˰��� =  ���䱶�� * ���� * ����(����:���) * ˰��
		if(nCount > 0)
		{
			nCGTax = (i64Tmp  * m_DeskBasePoint * nBasePoint * nPointRate * m_pDataManage->m_InitData.uTax / nCount ) / m_pDataManage->m_nRate;
		}
	}

	/// ������Ҹ���Ľ�Ҷ��Ѿ�ȷ�������Կ�ʼ����Ӯ�ҵ�������
	for (i=0; i<m_bMaxPeople; ++i)
	{
		if (NULL==m_pUserInfo[i])
		{
			continue;
		}
		arUserID[i] = m_pUserInfo[i]->m_UserData.dwUserID; ///<����Ч��ҵ�dwUsreID�ŵ�������
		arLogonTime[i] = m_pUserInfo[i]->m_dwLogonTime; ///<����Ч��ҵĵ�¼ʱ��ŵ�������
		/// ӮǮ����Ҫ���¼��㣬����Ѿ��������
		if ((m_pDataManage->m_InitData.uComType == TY_MONEY_GAME) && (arPoint[i]>0) && !bTaxMain)
		{

			/// �ж��Ƿ�����Ҳ���Ǯ�����У���Ӯ������ô��Ǯ
			if (bSomeOneNoEnoughMoney)
			{

				if (i64TotalLosePoint != 0)
					arLoseMoney[i] = i64TotalLoseMoney*arPoint[i]/i64TotalLosePoint;
				else
					arLoseMoney[i] = 0;

			}
			else
			{
				if(nTaxIndex > 1000000) //����������==����
				{
					arLoseMoney[i] = arPoint[i];
				}
				else
				{
					arLoseMoney[i] = arPoint[i]*m_DeskBasePoint;
				}
			}
			i64Tmp = 1;
			/// ����ø�Ӯ���󣬿�˰
			/// ��Ҷ���
			if (bIsAllNeedTax)
			{
				if (m_pDataManage->m_InitData.uTax>0)
				{
					arTaxCount[i] = i64Tmp * m_pDataManage->m_InitData.uTax;
					arLoseMoney[i] -= arTaxCount[i];
			
				}
			}
			else
			{
				if ((m_pDataManage->m_InitData.uTax>0) && (arLoseMoney[i]>=2))
				{	
					arTaxCount[i] = i64Tmp * arLoseMoney[i] * m_pDataManage->m_InitData.uTax/m_pDataManage->m_nRate;
					arLoseMoney[i] -= arTaxCount[i];
				}
			}
		}
		else if ((m_pDataManage->m_InitData.uComType == TY_MONEY_GAME) && (arPoint[i]>0) && bTaxMain)///< ֻ�۸���ҵ�˰
		{

			/// �ж��Ƿ�����Ҳ���Ǯ�����У���Ӯ������ô��Ǯ
			if (bSomeOneNoEnoughMoney)
			{

				if (i64TotalLosePoint != 0)
					arLoseMoney[i] = i64TotalLoseMoney*arPoint[i]/i64TotalLosePoint;
				else
					arLoseMoney[i] = 0;

			}
			
			else
			{
				if(nTaxIndex > 1000000) //����������==����
					arLoseMoney[i] = arPoint[i];
				else
					arLoseMoney[i] = arPoint[i]*m_DeskBasePoint;
			}
			i64Tmp = 1;

			if (i == nTaxIndex && m_pDataManage->m_InitData.uTax>0) ///< ֻ�۸���ҵ�˰��
			{
				if (arLoseMoney[i] >= 2)
				{
					arTaxCount[i] = i64Tmp * arLoseMoney[i] * m_pDataManage->m_InitData.uTax/m_pDataManage->m_nRate;
					//if (arTaxCount[i] == 0)	/// ����Ҫ��1�����
					//{
					//	arTaxCount[i] = 1;
					//}
					arLoseMoney[i] -= arTaxCount[i];
				}
			}
			//�����齫��˰����  add by lxl 2010-12-14
			if(nTaxIndex > 1000000 && m_pDataManage->m_InitData.uTax>0)
			{
				if (arPoint[i+4] == 1 && arLoseMoney[i] >= 2) //�ж��Ƿ�Ҫ��˰
				{
					arTaxCount[i] = nCGTax;
					arLoseMoney[i] -= arTaxCount[i];
				}
			}
		}


		/// ����Ա������ֵ
		m_dwTaxCom[i] = arTaxCount[i];

		if(bNotCostPoint)		//��ҳ����ۻ��� add by lxl 2010-10-26
		{
			m_dwChangePoint[i] = 0;
		}
		else
		{
			m_dwChangePoint[i] = arPoint[i];
		}


		__int64 _sendmoney = 0;
		if (iSendMoney > 0 && arPoint[i]>0) _sendmoney = iSendMoney;

		/// ����m_pUserInfo�������
		m_pUserInfo[i]->ChangePoint(m_dwChangePoint[i], m_dwTaxCom[i], arPoint[i]>0, arPoint[i]<0,arPoint[i]==0, bCut[i], dwNowTime-m_dwBeginTime, arLoseMoney[i]);
		m_pUserInfo[i]->m_UserData.i64Money += _sendmoney;

		/// �����ٴ��жϺ��ٸ�ֵ������
		m_dwChangeMoney[i] = arLoseMoney[i];
	}
	/// ͳһ��������ҵĽ������������ݿ�

	/// �������ѭ�����Ѿ�ͳ�ƹ��������nTotalPlayerCount
	UpdateUserInfo_t *pUpdateUserInfo = NULL;
	int nIndex=0;
	

	pUpdateUserInfo = new UpdateUserInfo_t[nTotalPlayerCount];
	for (i=0; i<m_bMaxPeople; ++i)
	{
		if (NULL == m_pUserInfo[i])
		{
			continue;
		}
		//����֮�󣬽�Ҳ��㷿�����ޣ��Զ����� //2013-08-29	
		__int64 i64Money = m_pUserInfo[i]->m_UserData.i64Money + m_pUserInfo[i]->m_UserData.i64Bank;
		if((i64Money < m_pDataManage->m_InitData.uLessPoint)
			&& (m_pDataManage->m_InitData.uComType == TY_MONEY_GAME))
		{
			pUpdateUserInfo[nIndex].bISAutoSendMoney = true;
		}

		/// ������ֵ
		pUpdateUserInfo[nIndex].dwUserID			= m_pUserInfo[i]->m_UserData.dwUserID;
		pUpdateUserInfo[nIndex].dwOnLineTimeCount	= dwNowTime-m_pUserInfo[i]->m_dwLogonTime;
		__int64 iPoint = arPoint[i];
		//�ж��Ƿ񻹿�����˫������

		if(iPoint>0)
		{	//ʤ���������˫�����֣������*2
			if(m_pUserInfo[i]->m_UserData.iDoublePointTime>curtime)
			{
				//��λ��˫�����ֿ���Ч20081125
				m_byDoublePointEffect |= (1<<i);
				iPoint *= 2;
			}
		}
		else
		{  //ʧ�ܣ�����л����������ֲ��䣬����Ӧ��
			if(m_pUserInfo[i]->m_UserData.iProtectTime>curtime)
				iPoint=0;
		}

		if (bNotCostPoint)//��ҳ����ۻ���  add by lxl 2010-10-26
		{
			pUpdateUserInfo[nIndex].dwChangePoint = 0;
		}
		else 
		{
			pUpdateUserInfo[nIndex].dwChangePoint = iPoint;
		}

		pUpdateUserInfo[nIndex].dwChangeMoney = arLoseMoney[i];
		pUpdateUserInfo[nIndex].dwChangeTaxCom = m_dwTaxCom[i];


		CString _strdebug = "";
		_strdebug.Format("lkpytest UpdateUserInfo_t:%d, %I64d", pUpdateUserInfo[nIndex].dwUserID, pUpdateUserInfo[nIndex].dwChangeMoney);
		OutputDebugString(_strdebug);

		if (arPoint[i]==0)
		{
			pUpdateUserInfo[nIndex].uMidCount = 1;
		}
		else if (arPoint[i]>0)
		{
			pUpdateUserInfo[nIndex].uWinCount = 1;
		}
		else
		{
			pUpdateUserInfo[nIndex].uLostCount = 1;
		}

		pUpdateUserInfo[nIndex].uCutCount = bCut[i]? 1 : 0;
		++nIndex;
	}

	//	if (TY_MONEY_GAME == m_pDataManage->m_InitData.uComType && m_pDataManage->m_bPresentCoin) ///< ��ҳ��������ͽ��
	//	{
	//		PresentCoin();
	//	}

	/// ���������û�����
	UpdateAllUserInfo(pUpdateUserInfo, nTotalPlayerCount, m_tEndTime.GetTime() - m_tBeginTime.GetTime());

	
	m_dwTax = 0;
	/// �����û��������ݵ��ͻ���

	for (i=0; i<m_bMaxPeople; ++i)
	{
		if (NULL == m_pUserInfo[i])
		{
			continue;
		}
		DebugPrintf("UpdateUserInfo������arLoseMoney=[%d]", arLoseMoney[i]);
		/// ��д���ݿ�
		//UpdateUserInfo(m_pUserInfo[i]->m_UserData.dwUserID,
		//	arPoint[i],
		//	arLoseMoney[i],
		//	m_dwTaxCom[i],
		//	bCut[i],
		//	dwNowTime-m_dwBeginTime,
		//	dwNowTime-m_pUserInfo[i]->m_dwLogonTime);

		m_dwTax += m_dwTaxCom[i];

		m_pUserInfo[i]->m_dwLogonTime=(long int)time(NULL);
		//������Ϣ
		MSG_GR_R_UserPoint UserPoint;
		ZeroMemory(&UserPoint, sizeof(UserPoint));
		UserPoint.dwUserID = m_pUserInfo[i]->m_UserData.dwUserID;
		UserPoint.dwPoint = arPoint[i];


		//zht 2011-12-1 �޸�˫�����ֵ�BUG

		if (bNotCostPoint)
		{
			UserPoint.dwPoint = 0;
		}
		else
		{
			if(m_pUserInfo[i]->m_UserData.iDoublePointTime>curtime && arPoint[i]>0)
				UserPoint.dwPoint*=2;
			if(m_pUserInfo[i]->m_UserData.iProtectTime>curtime && arPoint[i]<0)
				UserPoint.dwPoint=0;
		}
		

		//if(bNotCostPoint) //��ҳ����ۻ���	add by lxl 2010-10-26
		//	UserPoint.dwPoint = 0;
		//else
		//	UserPoint.dwPoint = arPoint[i];

		UserPoint.dwMoney = arLoseMoney[i];


		if (arPoint[i] > 0)
			UserPoint.bWinCount = 1;

		if (arPoint[i] < 0)
		{
			UserPoint.bLostCount = 1;
		}

		if (arPoint[i] == 0) 
			UserPoint.bMidCount = 1;

		if (bCut[i] == true) 
			UserPoint.bCutCount = 1;

		if (iSendMoney > 0)
			UserPoint.dwSend = 0;
		else 
			UserPoint.dwSend = -1;
		if (arPoint[i] > 0 && iSendMoney > 0)
		{
			UserPoint.dwSend = iSendMoney;
			UserPoint.dwMoney += iSendMoney;	
		}


		m_pDataManage->m_TCPSocket.SendDataBatch(&UserPoint,sizeof(UserPoint),MDM_GR_ROOM,ASS_GR_USER_POINT,0);
	}

	return true;
}
/// �޸��û�������Ǯ��
/// �ú�����Ҫ��ɵĹ���
/// �������������������û�ʵ����Ӯ�Ľ�������������������m_dwChangeMoney��Ա�У�ͬʱд�����ݿ�
/// @param[in] dwPoint �û��������飬�����СΪm_bMaxPeople������֧�ֵ�����������ɵ����߱�֤���鲻Խ��
/// @param[in] bCut �û��Ƿ�������飬�����СΪm_bMaxPeople������֧�ֵ�����������ɵ����߱�֤���鲻Խ��
/// @param[in] nTaxIndex -1��ʾ��������ҵ�˰������ֻ�۸��û���Ǯ
/// �ú������޸�m_dwChangeMoney[]�����Ա��ֵ
/// ��Ϸ���������������˺����ģ���ͨ��RecordGameInfo������ȡ��ֵ
bool CGameDesk::ChangeUserPoint(int *arPoint, bool *bCut,int nTaxIndex)
{
	/// ���㱾����ϷӮ����Ӯ��ҵ��ܺ�
	/// ���㱾����Ϸ��������ҵ��ܺ�
	/// �ж�ÿ��������ϵĽ���Ƿ��㹻��
	/// ������ҽ�Ҳ���֧������Ӯ��Ҫ��Ӧ��������
	/// ����m_pInfo���������ݣ�����Ϸ�ж�ȡ����ȷ��ֵ
	/// ͳһ��������ҵĽ������������ݿ�
	/// ������Ϣ���ͻ��ˣ���ʾ������Ǯ��ӮǮ��
	if (m_pDataManage->m_InitData.dwRoomRule & GRR_CONTEST || m_pDataManage->m_InitData.dwRoomRule & GRR_TIMINGCONTEST)
	{
		return ChangeUserPointContest(arPoint, bCut, nTaxIndex);
	}


	m_tEndTime = CTime::GetCurrentTime();
	__int64 iSendMoney = -1;
	if (m_pDataManage->m_InitData.iTimeLength >= 0 && m_pDataManage->m_InitData.iSendCount > 0)
	{
		iSendMoney = 0;
		if (m_tEndTime.GetTime() - m_tBeginTime.GetTime() >= m_pDataManage->m_InitData.iTimeLength)
		{
			iSendMoney = m_pDataManage->m_InitData.iSendCount;
		}
	}


	/// ȡ��ǰʱ��
	CString stime;
	stime.Format("%d",CTime::GetCurrentTime());
	int curtime=atoi(stime);

	/// �Ƿ�Ϊ��Ҷ�Ҫ��̨�ѵķ������һ�㶼ΪӮ�ҽ�̨��
	bool bIsAllNeedTax = (m_pDataManage->m_InitData.dwRoomRule & GRR_ALL_NEED_TAX) > 0;
	bool bTaxMain = false; ///< �Ƿ�ֻ��ׯ�ҿ�˰��
	
	bool bNotCostPoint = (m_pDataManage->m_InitData.dwRoomRule & GRR_NOT_COST_POINT) > 0; /// ��ҳ����ۻ���  add by lxl 2010-10-26

	BYTE i=0;	///< ѭ������
	
	/// ����ֺܷͽ��
	__int64 i64TotalLosePoint = 0;
	__int64 i64TotalWinPoint = 0;
	__int64 i64TotalLoseMoney = 0;
	__int64 i64TotalWinMoney = 0;

	/// ʵ������ж���
	int nTotalPlayerCount = 0;
	/// ����������ĸ�
	BYTE bCutDeskStation = 255;

	for (i=0; i<m_bMaxPeople; ++i)
	{
		if (m_pUserInfo[i] == NULL)
			continue;
		++nTotalPlayerCount;
		if (bCut[i])
		{
			bCutDeskStation = i;
		}

		if (!bTaxMain && nTaxIndex>=0)
		{
			if (i == nTaxIndex) ///< ֻ�۸���ҵ�˰��
			{
				bTaxMain = true;
			}
			if(nTaxIndex > 1000000) ///����ǳ����齫���򣬿���Ҫ��˰����� add by lxl 2010-12-14
			{
				bTaxMain = true;
			}
		}

	}

	__int64 arLoseMoney[MAX_PEOPLE];
	__int64 arTaxCount[MAX_PEOPLE];
	ZeroMemory(arLoseMoney, sizeof(arLoseMoney));
	ZeroMemory(arTaxCount, sizeof(arTaxCount));
	/// �û�ID����
	long arUserID[MAX_PEOPLE];
	ZeroMemory(arUserID, sizeof(arUserID));
	long arLogonTime[MAX_PEOPLE];
	ZeroMemory(arLogonTime, sizeof(arLogonTime));
	/// �Ƿ����˲���Ǯ
	bool bSomeOneNoEnoughMoney = false;

	__int64 i64Tmp = 1;	/// Ϊ�˷�ֹ���磬����һ��int64���͵��������д�ö��ǿ������ת��

	long int dwNowTime=(long int)time(NULL);

	if (m_pDataManage->m_nRate < 100)
		m_pDataManage->m_nRate = 100;


	/// ��ҳ�����Ҫ���㣬
	/// ����Ӧ����֣�����Ӧ�����Ӧ���Ǯ��ͬʱ�������ϵ�Ǯ�Ƿ�֧��
	if(m_pDataManage->m_InitData.uComType == TY_MONEY_GAME)
	{
		for (i=0; i<m_bMaxPeople; ++i)
		{
			if (NULL==m_pUserInfo[i])
			{
				continue;
			}
			/// ����Ӧ���߽���Ƿ�
			if (arPoint[i]<=0)
			{
				if(nTaxIndex > 1000000) //����������==����
					arLoseMoney[i] = arPoint[i];
				else
					arLoseMoney[i] = arPoint[i]*m_DeskBasePoint;	///< ����Ϊ����
				/// �ǲ��Ǵ�Ҷ�Ҫ��˰��������Ӯ
				if (bIsAllNeedTax && (m_pDataManage->m_InitData.uTax>0))
				{
					//if (bCutDeskStation == i)/// ��������ǿ�ˣ����ҵ�˰һ�𽻣���������£�uTax�������ٷֱȣ�����ʵʵ���ڵĿ�˰���
					//{
					//	arTaxCount[i] = i64Tmp * m_pDataManage->m_InitData.uTax * nTotalPlayerCount;
					//}
					//else
					//{
					//	arTaxCount[i] = i64Tmp * m_pDataManage->m_InitData.uTax;
					//}
					
					if(bCutDeskStation == 255)
					{
						arTaxCount[i] = i64Tmp * m_pDataManage->m_InitData.uTax;
						arLoseMoney[i] -= arTaxCount[i];
					}
					//�������ǿ���򲻿�̨��
				}

				/// ������ҵ�Ǯ�Ƿ��Ѿ�������
				if (m_pUserInfo[i]->m_UserData.i64Money < (0-arLoseMoney[i])) ///<Ǯ��������
				{
					bSomeOneNoEnoughMoney = true;
					if (m_pUserInfo[i]->m_UserData.i64Money <= 0) ///<�������Ӧ�ò������
					{
						arLoseMoney[i] = 0;	///< һ��Ǯ��û����
					}
					else
					{
						arLoseMoney[i] = 0-m_pUserInfo[i]->m_UserData.i64Money; ///< ��������ϵ�Ǯ���۹�
					}
				}

				/// �ܹ���ķ�����Ǯ����������˲���Ǯ����������Ӯ�ҷ���Ǯ�ı���
				i64TotalLosePoint -= arPoint[i];
				i64TotalLoseMoney -= arLoseMoney[i];
			}
		}
	}

	//�����齫��˰ add by lxl 2010-12-14
	int nCGTax = 0;
	//�����齫��˰Ԥ����  
	if(nTaxIndex > 1000000)
	{
		int nBasePoint; //��������
		int nPointRate; //�����ͽ�ҵı��� 
		int nTax;	    //˰��
		//��nTaxIndex = 1000100�������Ϊ100����1�� = 100�����
		nPointRate = nTaxIndex - 1000000;
		nBasePoint = 50;
		
	    int nCount = 0; //Ҫ��˰������
		//ͳ��Ҫ��˰������,arPoint[8]����ǰ4��Ϊ��һ�����ֵ����4����ʾΪ�Ƿ��˰��1ΪҪ��˰��
		for(int i = 4; i < 8; i++)
		{
			if(arPoint[i] == 1)
			  nCount++;
		}

		//��˰���㹫ʽ����˰��� =  ���䱶�� * ���� * ����(����:���) * ˰��
		if(nCount > 0)
		{
			nCGTax = (i64Tmp  * m_DeskBasePoint * nBasePoint * nPointRate * m_pDataManage->m_InitData.uTax / nCount ) / m_pDataManage->m_nRate;
		}
	}

	/// ������Ҹ���Ľ�Ҷ��Ѿ�ȷ�������Կ�ʼ����Ӯ�ҵ�������
	for (i=0; i<m_bMaxPeople; ++i)
	{
		if (NULL==m_pUserInfo[i])
		{
			continue;
		}
		arUserID[i] = m_pUserInfo[i]->m_UserData.dwUserID; ///<����Ч��ҵ�dwUsreID�ŵ�������
		arLogonTime[i] = m_pUserInfo[i]->m_dwLogonTime; ///<����Ч��ҵĵ�¼ʱ��ŵ�������
		/// ӮǮ����Ҫ���¼��㣬����Ѿ��������
		if ((m_pDataManage->m_InitData.uComType == TY_MONEY_GAME) && (arPoint[i]>0) && !bTaxMain)
		{
			/// �ж��Ƿ�����Ҳ���Ǯ�����У���Ӯ������ô��Ǯ
			if (bSomeOneNoEnoughMoney)
			{
				if (i64TotalLosePoint != 0 && arPoint[i] != 0)
					arLoseMoney[i] = i64TotalLoseMoney/i64TotalLosePoint*arPoint[i];
				else
					arLoseMoney[i] = 0;
			}
			else
			{
				if(nTaxIndex > 1000000) //����������==����
					arLoseMoney[i] = arPoint[i];
				else
					arLoseMoney[i] = arPoint[i]*m_DeskBasePoint;
			}
			i64Tmp = 1;
			/// ����ø�Ӯ���󣬿�˰
			/// ��Ҷ���
			if (bIsAllNeedTax)
			{
				if (m_pDataManage->m_InitData.uTax>0)
				{
					//if (i == bCutDeskStation) ///Ӯ��Ϊǿ�˵��ˡ�Ҫ�۳������˵�̨�ѣ������������Ϸδ�����ʱ�����
					//{
					//	arTaxCount[i] = m_pDataManage->m_InitData.uTax * nTotalPlayerCount;
					//}
					//else
					//{
					//	arTaxCount[i] = m_pDataManage->m_InitData.uTax;
					//}
					//arLoseMoney[i] -= arTaxCount[i];   //̨��ֵҲ���������
					if(bCutDeskStation == 255)
					{
						arTaxCount[i] = i64Tmp * m_pDataManage->m_InitData.uTax;
						arLoseMoney[i] -= arTaxCount[i];
					}
					//�������ǿ���򲻿�̨��

				}
			}
			else
			{
				if ((m_pDataManage->m_InitData.uTax>0) && (arLoseMoney[i]>=2))
				{	
					arTaxCount[i] = i64Tmp * arLoseMoney[i] * m_pDataManage->m_InitData.uTax/m_pDataManage->m_nRate;
			//		if (arTaxCount[i] == 0)	/// ����Ҫ��1�����
			//		{
			//			arTaxCount[i] = 1;
			//		} 2010 5 14 ��ˮ����һ����ҵ�ʱ�򽫲���ˮ
					arLoseMoney[i] -= arTaxCount[i];
				}
			}
		}
		else if ((m_pDataManage->m_InitData.uComType == TY_MONEY_GAME) && (arPoint[i]>0) && bTaxMain)///< ֻ�۸���ҵ�˰
		{
			/// �ж��Ƿ�����Ҳ���Ǯ�����У���Ӯ������ô��Ǯ
			if (bSomeOneNoEnoughMoney)
			{
				if (i64TotalLosePoint != 0 && arPoint[i] != 0)
					arLoseMoney[i] = i64TotalLoseMoney/i64TotalLosePoint*arPoint[i];
				else
					arLoseMoney[i] = 0;
			}
			else
			{
				if(nTaxIndex > 1000000) //����������==����
					arLoseMoney[i] = arPoint[i];
				else
					arLoseMoney[i] = arPoint[i]*m_DeskBasePoint;
			}
			i64Tmp = 1;

			if (i == nTaxIndex && m_pDataManage->m_InitData.uTax>0) ///< ֻ�۸���ҵ�˰��
			{
				if (arLoseMoney[i] >= 2)
				{
					arTaxCount[i] = i64Tmp * arLoseMoney[i] * m_pDataManage->m_InitData.uTax/m_pDataManage->m_nRate;
					//if (arTaxCount[i] == 0)	/// ����Ҫ��1�����
					//{
					//	arTaxCount[i] = 1;
					//}
					arLoseMoney[i] -= arTaxCount[i];
				}
			}
			//�����齫��˰����  add by lxl 2010-12-14
			if(nTaxIndex > 1000000 && m_pDataManage->m_InitData.uTax>0)
			{
				if (arPoint[i+4] == 1 && arLoseMoney[i] >= 2) //�ж��Ƿ�Ҫ��˰
				{
					arTaxCount[i] = nCGTax;
					arLoseMoney[i] -= arTaxCount[i];
				}
			}
		}


		/// ����Ա������ֵ
		m_dwTaxCom[i] = arTaxCount[i];

		if(bNotCostPoint)		//��ҳ����ۻ��� add by lxl 2010-10-26
			m_dwChangePoint[i] = 0;
		else
			m_dwChangePoint[i] = arPoint[i];


		__int64 _sendmoney = 0;
		if (iSendMoney > 0 && arPoint[i]>0) _sendmoney = iSendMoney;
		/// ����m_pUserInfo�������
		m_pUserInfo[i]->ChangePoint(arPoint[i], m_dwTaxCom[i], arPoint[i]>0, arPoint[i]<0,arPoint[i]==0, bCut[i], dwNowTime-m_dwBeginTime, arLoseMoney[i]);
		m_pUserInfo[i]->m_UserData.i64Money += _sendmoney;

		/// �����ٴ��жϺ��ٸ�ֵ������
		m_dwChangeMoney[i] = arLoseMoney[i];
	}
	/// ͳһ��������ҵĽ������������ݿ�

	/// �������ѭ�����Ѿ�ͳ�ƹ��������nTotalPlayerCount
	UpdateUserInfo_t *pUpdateUserInfo = new UpdateUserInfo_t[nTotalPlayerCount];
	int nIndex=0;
	for (i=0; i<m_bMaxPeople; ++i)
	{
		if (NULL == m_pUserInfo[i])
		{
			continue;
		}
		/// ������ֵ
		pUpdateUserInfo[nIndex].dwUserID			= m_pUserInfo[i]->m_UserData.dwUserID;
		pUpdateUserInfo[nIndex].dwOnLineTimeCount	= dwNowTime-m_pUserInfo[i]->m_dwLogonTime;
		int iPoint = arPoint[i];
		//�ж��Ƿ񻹿�����˫������
		if(iPoint>0)
		{	//ʤ���������˫�����֣������*2
			if(m_pUserInfo[i]->m_UserData.iDoublePointTime>curtime)
			{
				//��λ��˫�����ֿ���Ч20081125
				m_byDoublePointEffect |= (1<<i);
				iPoint *= 2;
			}
		}
		else
		{  //ʧ�ܣ�����л����������ֲ��䣬����Ӧ��
			if(m_pUserInfo[i]->m_UserData.iProtectTime>curtime)
				iPoint=0;
		}

		if (bNotCostPoint)//��ҳ����ۻ���  add by lxl 2010-10-26
		{
			pUpdateUserInfo[nIndex].dwChangePoint = 0;
		}
		else 
		{
			pUpdateUserInfo[nIndex].dwChangePoint = iPoint;
		}

		pUpdateUserInfo[nIndex].dwChangeMoney = arLoseMoney[i];
		pUpdateUserInfo[nIndex].dwChangeTaxCom = m_dwTaxCom[i];
		
	
		CString _strdebug = "";
		_strdebug.Format("rqf UpdateUserInfo_t:%d, %d", pUpdateUserInfo[nIndex].dwUserID, pUpdateUserInfo[nIndex].dwChangeMoney);
		OutputDebugString(_strdebug);

		if (arPoint[i]==0)
		{
			pUpdateUserInfo[nIndex].uMidCount = 1;
		}
		else if (arPoint[i]>0)
		{
			pUpdateUserInfo[nIndex].uWinCount = 1;
		}
		else
		{
			pUpdateUserInfo[nIndex].uLostCount = 1;
		}
	
		pUpdateUserInfo[nIndex].uCutCount = bCut[i]? 1 : 0;
		++nIndex;
	}
		
//	if (TY_MONEY_GAME == m_pDataManage->m_InitData.uComType && m_pDataManage->m_bPresentCoin) ///< ��ҳ��������ͽ��
//	{
//		PresentCoin();
//	}

	/// ���������û�����
	UpdateAllUserInfo(pUpdateUserInfo, nTotalPlayerCount, m_tEndTime.GetTime() - m_tBeginTime.GetTime());
	m_dwTax = 0;
	/// �����û��������ݵ��ͻ���

	for (i=0; i<m_bMaxPeople; ++i)
	{
		if (NULL == m_pUserInfo[i])
		{
			continue;
		}
		DebugPrintf("UpdateUserInfo������arLoseMoney=[%d]", arLoseMoney[i]);
		/// ��д���ݿ�
		//UpdateUserInfo(m_pUserInfo[i]->m_UserData.dwUserID,
		//	arPoint[i],
		//	arLoseMoney[i],
		//	m_dwTaxCom[i],
		//	bCut[i],
		//	dwNowTime-m_dwBeginTime,
		//	dwNowTime-m_pUserInfo[i]->m_dwLogonTime);

		m_dwTax += m_dwTaxCom[i];

		m_pUserInfo[i]->m_dwLogonTime=(long int)time(NULL);
		//������Ϣ
		MSG_GR_R_UserPoint UserPoint;
		ZeroMemory(&UserPoint, sizeof(UserPoint));
		UserPoint.dwUserID = m_pUserInfo[i]->m_UserData.dwUserID;
		UserPoint.dwPoint = arPoint[i];

		if(bNotCostPoint)
		{
			UserPoint.dwPoint = 0;
		}
		else
		{
			if(m_pUserInfo[i]->m_UserData.iDoublePointTime>curtime && arPoint[i]>0)
				UserPoint.dwPoint*=2;
			if(m_pUserInfo[i]->m_UserData.iProtectTime>curtime && arPoint[i]<0)
				UserPoint.dwPoint=0;
		}
		
		
		//if(bNotCostPoint) //��ҳ����ۻ���	add by lxl 2010-10-26
		//	UserPoint.dwPoint = 0;
		//else
		//	UserPoint.dwPoint = arPoint[i];

		UserPoint.dwMoney = arLoseMoney[i];
		if (arPoint[i] > 0)
			UserPoint.bWinCount = 1;

		if (arPoint[i] < 0)
		{
			UserPoint.bLostCount = 1;
		}

		if (arPoint[i] == 0) 
			UserPoint.bMidCount = 1;

		if (bCut[i] == true) 
			UserPoint.bCutCount = 1;

		if (iSendMoney > 0)
			UserPoint.dwSend = 0;
		else 
			UserPoint.dwSend = -1;
		if (arPoint[i] > 0 && iSendMoney > 0)
		{
			UserPoint.dwSend = iSendMoney;
			UserPoint.dwMoney += iSendMoney;	
		}

		CString _strdebug = "";
		_strdebug.Format("rqf SendDataBatch:%d, %d", UserPoint.dwUserID, UserPoint.dwMoney);
		OutputDebugString(_strdebug);

		m_pDataManage->m_TCPSocket.SendDataBatch(&UserPoint,sizeof(UserPoint),MDM_GR_ROOM,ASS_GR_USER_POINT,0);
	}

	return true;
}
//�޸��û�����
/*
���������ÿ����Ϸ������ʱ�򱻵��ã������޸��û��ؽ��뷿���𵽴˾ֽ������������ҡ�˰�ա���Ӯ�����ȵĸı��������Щ�ı�ֵ
�����û��˳�����ʱ��OnUserLeft��������ʹ�ã������޸����ݿ����û���Ϣ��������MathchTable��Users���У���
����������ֳ�����ģʽ����IsCheckInMoney���������ƣ���һ��ģʽ��ֱ��ģʽ������Ϸ���ӣ�dll���Ŀ�������gamefinish������ֱ��ָ���û�
��Ҹı�ֵ���ڶ���ģʽ�ɴ˺������ݷ���ֵ�����䱶������Ϸ���ı��������ҵĸı�ֵ��
������
int *dwPoint: �����룩һ��ָ�룬ָ���СΪ8��һά�������飬��¼�˴����û����������飩�ĸı�������������8������ȡ��Ч����������ֵĬ��
Ϊ0��
bool *bCut:�����룩 һ��ָ�룬ָ���СΪ8��һάbool�����飬��¼���û��Ƿ���ߣ��������8������ȡ��Ч����������ֵĬ��false��
int *dwMoneyInput: ģʽ1�£����룩ָ���СΪ8��һά�������飬��¼�˴����û���ң����飩�ĸı�������������8������ȡ��Ч����������ֵ
Ĭ��Ϊ0��
bool IsCheckInMoney: ģʽѡ��,trueΪģʽ1,false Ϊģʽ2(Ĭ��)��

*/
bool CGameDesk::ChangeUserPoint_old(int *dwPoint, bool *bCut,int *dwMoneyInput,bool IsCheckInMoney)//, bool bWin, bool bLost, bool bMid)
{
	//if (m_pDataManage->m_InitData.dwRoomRule & GRR_CONTEST)
	//{
	//	return ChangeUserPointContest(arPoint, bCut, nTaxIndex);
	//}

	//int OrderClass=30;
	//for(int i=0;i<m_bMaxPeople;i++)
	//{
	//	if (m_pUserInfo[i]!=NULL) 
	//	{
	//		//dwPoint[i]*=m_pDataManage->m_InitData.uBasePoint;//��Ϸ�÷�ϵ����N��
	//		OrderClass=__min(GetOrderClass(m_pUserInfo[i]->m_UserData.dwPoint),OrderClass);
	//	}
	//}
	//CString stime;
	//stime.Format("%d",CTime::GetCurrentTime());
	//int curtime=atoi(stime);

	////-----yjj  ����Ƿ�Ϊ�����˶���Ҫ����̨��  090323
	//int kkk = GRR_ALL_NEED_TAX;
	//int kkkk = m_pDataManage->m_InitData.dwRoomRule & GRR_ALL_NEED_TAX;
	//bool bIsAllNeedTax = ((m_pDataManage->m_InitData.dwRoomRule & GRR_ALL_NEED_TAX) ? true : false);
	////-----------

	//long int taxCom=0;
	////////////////////////////////////////////ģʽһ///////////////////////////////////////////
	//if(IsCheckInMoney)//dwMoneyInputΪ�������
	//{
	//	for(int i=0;i<m_bMaxPeople;i++)
	//	{
	//		if (m_pUserInfo[i]!=NULL)
	//		{
	//			//��ҳ�����˰��
	//			if(m_pDataManage->m_InitData.uComType==TY_MONEY_GAME)
	//			{
	//				//yjj 090323̨�ѳ�  ̨��Ϊ�̶�ֵ�����ǰ��ٷֱȳ�
	//				if (bIsAllNeedTax && m_pDataManage->m_InitData.uTax>0)
	//				{
	//					taxCom=m_pDataManage->m_InitData.uTax;
	//					if(taxCom==0) taxCom=1;//����Ϊ1
	//					m_dwTax+=taxCom;//ÿ����˰��
	//					dwMoneyInput[i] = dwMoneyInput[i]-taxCom;//˰��÷�
	//				}
	//				//̨�ѳ�
	//				else if(dwMoneyInput[i]>1&&m_pDataManage->m_InitData.uTax>0)
	//				{
	//					taxCom=dwMoneyInput[i]*m_pDataManage->m_InitData.uTax/100;
	//					if(taxCom==0) taxCom=1;//����Ϊ1
	//					m_dwTax+=taxCom;//ÿ����˰��
	//					dwMoneyInput[i] = dwMoneyInput[i]-taxCom;//˰��÷�
	//				}
	//			}

	//			//��¼����
	//			m_dwChangePoint[m_pUserInfo[i]->m_UserData.bDeskStation]=dwPoint[i];
	//			if(m_pDataManage->m_InitData.uComType==TY_MONEY_GAME)
	//			{
	//				//DebugPrintf("m_dwChangeMoney[%d] = [%d]", m_pUserInfo[i]->m_UserData.bDeskStation, dwMoneyInput[i]);
	//				m_dwChangeMoney[m_pUserInfo[i]->m_UserData.bDeskStation]=dwMoneyInput[i];
	//				m_dwTaxCom[m_pUserInfo[i]->m_UserData.bDeskStation]=taxCom;//����ÿ�˽�˰���

	//			}

	//			//�޸ķ���
	//			long int dwNowTime=(long int)time(NULL);
	//			m_pUserInfo[i]->ChangePoint(dwPoint[i],taxCom,dwPoint[i]>0,dwPoint[i]<0,dwPoint[i]==0,bCut[i],dwNowTime-m_dwBeginTime,dwMoneyInput[i]);
	//			UpdateUserInfo(m_pUserInfo[i]->m_UserData.dwUserID,dwPoint[i],dwMoneyInput[i],
	//				taxCom,bCut[i],dwNowTime-m_dwBeginTime,dwNowTime-m_pUserInfo[i]->m_dwLogonTime);
	//			m_pUserInfo[i]->m_dwLogonTime=(long int)time(NULL);
	//			//������Ϣ
	//			MSG_GR_R_UserPoint UserPoint;
	//			memset(&UserPoint,0,sizeof(UserPoint));
	//			UserPoint.dwUserID=m_pUserInfo[i]->m_UserData.dwUserID;

	//			//wushuqun 2009.6.10
	//			if(m_pUserInfo[i]->m_UserData.iDoublePointTime>curtime && dwPoint[i]>0)
	//				UserPoint.dwPoint*=2;
	//			if(m_pUserInfo[i]->m_UserData.iProtectTime>curtime && dwPoint[i]<0)
	//				UserPoint.dwPoint=0;

	//			UserPoint.dwPoint=dwPoint[i];
	//			UserPoint.dwMoney=dwMoneyInput[i];
	//			if (dwPoint[i]>0) UserPoint.bWinCount=1;
	//			if (dwPoint[i]<0)
	//			{
	//				UserPoint.bLostCount=1;
	//				if(bCut[i]==true)UserPoint.bLostCount=0;
	//			}
	//			if (dwPoint[i]==0) UserPoint.bMidCount=1;
	//			if (bCut[i]==true) UserPoint.bCutCount=1;
	//			m_pDataManage->m_TCPSocket.SendDataBatch(&UserPoint,sizeof(UserPoint),MDM_GR_ROOM,ASS_GR_USER_POINT,0);
	//		}
	//	}
	//	return true;
	//}

	////////////////////////////////////////////////////ģʽ��/////////////////////////////////////////
	//long int dwMoney=0;//��ʼ���ı�Ľ����
	//long int iTotleLosePoint=0,//�������������ܷ�
	//	iTotleLoseMoney=0;//�������������ܽ��
	//long int	iLoseMoney[255];
	//memset(iLoseMoney,0,sizeof(iLoseMoney));
	//bool bSomeOneNoEnoughMoney=false;

	//int aryiTaxCom[255];
	//memset(aryiTaxCom,0,sizeof(aryiTaxCom));

	///*
	//��ҳ��н��������Ϊ�����������˽�Ҳ������˾ֵ�Ӧ��������ȡ�ߴ������н�ң�
	//Ӯ����Ұ��շ�������Ӯ��������ȡ��ҡ�
	//*/
	////���=��Ϸ�����֣�A��* ��Ϸ�÷�ϵ����N��* �������õı���
	////����=��Ϸ�����֣�A��* ��Ϸ�÷�ϵ����N��* �ĸ�������е���ͼ�������Ӧ�ľ���ֵ�ļ�����2^(n-1)
	////�ж��Ƿ����˽�Ҳ���������¼��Ӯ�ı���

	////yjj 090323
	////����ӿ�̨�ѳ�������ֹ��ʤ������ҳ�ˮ��������Ҿ������̨��
	//
	////�õ�ǿ����ҵ���λ�ã���������ǿ�˵Ļ������ĸ��˵�̨��
	//BYTE bCutDeskStation = 255;
	//int iTotaolPlayerCount = 0;  //yjj 090323
	//for (int i=0; i<m_bMaxPeople; i++)
	//{
	//	if (m_pUserInfo[i] == NULL)
	//		continue;
	//	iTotaolPlayerCount++;
	//	if (bCut[i])
	//	{
	//		bCutDeskStation = i;
	//	}

	//}


	//if(m_pDataManage->m_InitData.uComType == TY_MONEY_GAME)//��ҳ�
	//{
	//	for(int j=0;j<m_bMaxPeople;j++)//���������Ӧ���Ľ��
	//	{
	//		//DebugPrintf("------iLoseMoney[%d] = [%d]", j, iLoseMoney[j]);
	//		if (m_pUserInfo[j] == NULL)
	//			continue;
	//		
	//

	//		if(dwPoint[j]<0) 
	//		{
	//			//��¼����ܷ�
	//			iTotleLosePoint-=dwPoint[j];
	//			//����Ӧ����
	//			iLoseMoney[j] = dwPoint[j]*m_DeskBasePoint;//����
	//			//DebugPrintf("����Ӧ����iLoseMoney[%d] = [%d]", j, iLoseMoney[j]);


	//			if(m_pDataManage->m_InitData.uMaxLimite!=0)//�����������ƣ�0Ϊû��
	//				iLoseMoney[j] = max(iLoseMoney[j],0-m_pDataManage->m_InitData.uMaxLimite);

	//			// yjj 090323  ̨���������
	//			int iNeedMoney = iLoseMoney[j];
	//			if (bIsAllNeedTax && m_pDataManage->m_InitData.uTax>0)
	//			{

	//				if (j == bCutDeskStation)
	//				{

	//					aryiTaxCom[j] = m_pDataManage->m_InitData.uTax * iTotaolPlayerCount;
	//					//m_dwTax += taxCom;
	//					iLoseMoney[j] -= taxCom;   //̨��ֵҲ���������
	//				}
	//				else
	//				{
	//					aryiTaxCom[j] = m_pDataManage->m_InitData.uTax;
	//					iLoseMoney[j] -= m_pDataManage->m_InitData.uTax;   //̨��ֵҲ���������
	//				}					

	//			}

	//			iLoseMoney[j]=max(iLoseMoney[j],int(0-m_pUserInfo[j]->m_UserData.dwMoney));//���ϵĽ�Һ�Ӧ�����ıȽ�
	//			if(iLoseMoney[j] >0)
 //                   iLoseMoney[j] = 0;//���û���û����Ϸ�ҿ���������
	//			//��¼����ܽ��
	//			//iTotleLoseMoney -= iNeedMoney; //Modified by zxd
	//			//��־�Ƿ����˽�Ҳ���������Ӯ�����˶��Χ
	//			if(!bSomeOneNoEnoughMoney)
	//			{
	//			    bSomeOneNoEnoughMoney = (iLoseMoney[j]==(dwPoint[j]*m_DeskBasePoint - aryiTaxCom[j])?false:true);
	//				//�����ǲ���Ǯ��˰�ռ�����  yjj 090323
	//				if (bSomeOneNoEnoughMoney && bIsAllNeedTax)
	//				{
	//					aryiTaxCom[j] = iNeedMoney - iLoseMoney[j];
	//					if (aryiTaxCom[j] < 0)
	//					{
	//						aryiTaxCom[j] = 0;
	//					}
	//					//DebugPrintf("�����ǲ���Ǯ��˰�ռ�����iLoseMoney[%d] = [%d]", j, iLoseMoney[j]);
	//				}
	//			}
	//			iTotleLoseMoney -= iLoseMoney[j];
	//		}
	//	}
	//}
	//for(int i=0;i<m_bMaxPeople;i++)
	//{
	//	taxCom=0;
	//	if (m_pUserInfo[i]!=NULL)
	//	{
	//		//
	//		if(m_pDataManage->m_InitData.uBasePoint>0&&m_pDataManage->m_InitData.uBasePoint<1000000)
	//		{
	//			if(m_pDataManage->m_InitData.uComType==TY_MONEY_GAME && m_DeskBasePoint>0)
	//			{
	//				if(dwPoint[i]>0)//Ӯ����
	//				{
	//					if(bSomeOneNoEnoughMoney)//���˷ֲ������˷ⶥֵ
	//					{
	//						//DebugPrintf("�����ǲ���Ǯ��Ӯ����Ҫ��������iLoseMoney[%d] = [%d]", i, iLoseMoney[i]);
	//						//DebugPrintf("iTotleLoseMoney =[%d]dwPoint[i]=[%d]iTotleLosePoint=[%d]",iTotleLoseMoney,dwPoint[i],iTotleLosePoint);
	//						iLoseMoney[i] = iTotleLoseMoney*(dwPoint[i]*16/iTotleLosePoint)/16;	// Ϊ�˷�ֹ���������0���ͱ������������*16��/16
	//						//DebugPrintf("�����ò���Ǯ��Ӯ���˼�������ΪiLoseMoney[%d] = [%d]", i, iLoseMoney[i]);
	//						//iLoseMoney[i] *= dwPoint[i];
	//					}
	//					else 
	//					{
	//						iLoseMoney[i] =dwPoint[i]*m_DeskBasePoint;
	//						//DebugPrintf("û���ò���Ǯ��Ӯ���˲��������룬ΪiLoseMoney[%d] = [%d]", i, iLoseMoney[i]);
	//					}
 //                     

	//					//////////////////////////////////
 //                       //̨�Ѽ��� yjj 090323
	//					if (bIsAllNeedTax && m_pDataManage->m_InitData.uTax>0)
	//					{
	//						if (i == bCutDeskStation) //Ӯ��Ϊǿ�˵��ˡ�Ҫ�۳������˵�̨��
	//						{
	//							taxCom=m_pDataManage->m_InitData.uTax * iTotaolPlayerCount;
	//							iLoseMoney[i] -= taxCom;   //̨��ֵҲ���������
	//							m_dwTax += taxCom;
	//							
	//						}
	//						else
	//						{
	//							iLoseMoney[i] -= m_pDataManage->m_InitData.uTax;   //̨��ֵҲ���������
	//							m_dwTax += m_pDataManage->m_InitData.uTax;
	//							taxCom=m_pDataManage->m_InitData.uTax;

	//						}
	//						//DebugPrintf("//Ӯ��̨�Ѽ���iLoseMoney[%d] = [%d]", i, iLoseMoney[i]);
	//					
	//					}
	//					//��ҳ�����˰��
	//					else if(iLoseMoney[i]>1&&m_pDataManage->m_InitData.uTax>0)
	//					{
	//						taxCom=iLoseMoney[i]*m_pDataManage->m_InitData.uTax/100;
	//						if(taxCom==0)
	//							taxCom=1;//����Ϊ1
	//						m_dwTax+=taxCom;//ÿ����˰��
	//						iLoseMoney[i] = iLoseMoney[i]-taxCom;//˰��÷�
	//						//DebugPrintf("//Ӯ�ҽ�ҳ�����˰��iLoseMoney[%d] = [%d]", i, iLoseMoney[i]);
	//					}
	//				}
	//				////����Ϊ����Ⱥ 2008-07-29���
	//				else 
	//				{
	//					
	//					//yjj ̨�ѳ�����Ӯ����Ҫ����̨��
	//					if (bIsAllNeedTax && m_pDataManage->m_InitData.uTax>0)
	//					{
	//						taxCom=aryiTaxCom[i];
	//						m_dwTax += taxCom;							
	//						
	//					}
	//					//end
	//					if (m_pDataManage->m_InitData.dwRoomRule & GRR_EXPERCISE_ROOM) //���ѵ����
	//					{
	//						//��ֹ��ѵ�������ָ���� ��ѵ�������Խ�Ҽ����ֽ������ݿ�д��
	//						if (m_pUserInfo[ i ]->m_UserData.dwMoney + iLoseMoney[ i ] <= 0)
	//						{
	//							iLoseMoney[ i ]=max(iLoseMoney[ i ],int(0-m_pUserInfo[ i ]->m_UserData.dwMoney));
	//							m_pUserInfo[ i ]->m_UserData.dwMoney = 0;
	//						}
	//					}
	//					//DebugPrintf("��ң�����̨�Ѻ�iLoseMoney[%d] = [%d]", i, iLoseMoney[i]);
	//				}

	//				//��¼����
	//				m_dwChangeMoney[m_pUserInfo[i]->m_UserData.bDeskStation]=iLoseMoney[i];
	//				//DebugPrintf("���ս��m_dwChangeMoney[%d] = iLoseMoney[%d] = [%d]", m_pUserInfo[i]->m_UserData.bDeskStation, i, iLoseMoney[i]);

	//				m_dwTaxCom[m_pUserInfo[i]->m_UserData.bDeskStation]=taxCom;//����ÿ�˽�˰���
	//			}

	//			//��¼����
	//			m_dwChangePoint[m_pUserInfo[i]->m_UserData.bDeskStation]=dwPoint[i];
	//		}

	//		//�޸ı仯����
	//		long int dwNowTime=(long int)time(NULL);
	//		//����ֵ�ڴ˲����κθı�
	//		//dwPoint[i]*=(int)::pow(double(2),(OrderClass-1));//����
	//		m_pUserInfo[i]->ChangePoint(dwPoint[i],taxCom,dwPoint[i]>0,dwPoint[i]<0,dwPoint[i]==0,bCut[i],dwNowTime-m_dwBeginTime,iLoseMoney[i]);

	//		UpdateUserInfo(m_pUserInfo[i]->m_UserData.dwUserID,dwPoint[i],

	//			iLoseMoney[i],taxCom,bCut[i],dwNowTime-m_dwBeginTime,dwNowTime-m_pUserInfo[i]->m_dwLogonTime);
	//		//UpdateUserInfo(m_pUserInfo[i]->m_UserData.dwUserID,dwPoint[i],
	//		//dwMoney,taxCom,bCut[i],dwNowTime-m_dwBeginTime,dwNowTime-m_pUserInfo[i]->m_dwLogonTime);

	//		m_pUserInfo[i]->m_dwLogonTime=(long int)time(NULL);
	//		//������Ϣ
	//		MSG_GR_R_UserPoint UserPoint;
	//		memset(&UserPoint,0,sizeof(UserPoint));
	//		UserPoint.dwUserID = m_pUserInfo[i]->m_UserData.dwUserID;
	//		UserPoint.dwPoint = dwPoint[i];
	//		//Fred Huang,2008-04-27
	//		if(m_pUserInfo[i]->m_UserData.iDoublePointTime>curtime && dwPoint[i]>0)
	//			UserPoint.dwPoint*=2;
	//		if(m_pUserInfo[i]->m_UserData.iProtectTime>curtime && dwPoint[i]<0)
	//			UserPoint.dwPoint=0;

	//		UserPoint.dwMoney = iLoseMoney[i];
	//		if (dwPoint[i] > 0)
	//			UserPoint.bWinCount = 1;

	//		if (dwPoint[i] < 0)
	//		{
	//			UserPoint.bLostCount = 1;
	//			if(bCut[i] == true)
	//				UserPoint.bLostCount = 0;
	//		}

	//		if (dwPoint[i] == 0) 
	//			UserPoint.bMidCount = 1;

	//		if (bCut[i] == true) 
	//			UserPoint.bCutCount = 1;

	//		m_pDataManage->m_TCPSocket.SendDataBatch(&UserPoint,sizeof(UserPoint),MDM_GR_ROOM,ASS_GR_USER_POINT,0);
	//	}
	//}
	return true;
}
//�õ�����ȼ�
int CGameDesk::GetOrderClass(int dwPoint)
{
	static int uBasePoint[19] =
	{
		400,		800,		1600,		3200,
		6400,		12800,		25600,		51200,
		102400,		204800,		409600,		819200,
		1638400,	3276800,	6553600,	13107200,
		26214400,	52428800,	104857600
	};

	for (int i = 0; i < 19; i ++)	
	{
		if (dwPoint < uBasePoint[i]) 
			return i+1;
	}
	return 20;
}

/// ����������ҵ����ݿ�����
/// zxd �� 20100125����
/// @param [in] pUpdateUserInfo������û�����ָ��
/// @param [in] nCount���û����ݸ���
/// @return ��
void CGameDesk::UpdateAllUserInfo(UpdateUserInfo_t * pUpdateUserInfo, int nCount, int iroundtime)
{
	DL_GR_I_AllUserData_t allUserData;
	//UINT								uNameID;			///< ��ϷID
	//TCHAR								szGameTable[64];	///< ��Ϸ��Ϸ��
	//int									nPlayTime;			///< ��Ϸʱ��
	//bool								bIsExperciseRoom;	///< �Ƿ���ϰ��
	//bool								bIsMoneyGame;		///< �Ƿ��ҳ�
	UINT dwNowTime=(UINT)time(NULL);
	allUserData.nUserCount = nCount;
	allUserData.nPlayTime = dwNowTime - m_dwBeginTime;
	allUserData.iRoundPlayTime = iroundtime;
	allUserData.pUpdateUserInfo = pUpdateUserInfo;
	m_pDataManage->m_SQLDataManage.PushLine(&allUserData.DataBaseHead,sizeof(allUserData),DTK_GR_UPDATE_GAME_RESULT_ALLUSER,0,0);
}
void CGameDesk::UpdateUserPoint(BYTE *pbDeskStation,__int64 *arPoint,int nCount)
{
	UpdateUserInfo_t * pUpdateUserInfo = new UpdateUserInfo_t[nCount];    //�˴����ڴ���ڣ����ݿ⴦���߳�ɾ��
    
	MSG_GR_R_UserPoint UserPoint;
	ZeroMemory(&UserPoint, sizeof(UserPoint));
    for(int i=0;i<nCount;i++)
	{
		pUpdateUserInfo[i].dwUserID			 = m_pUserInfo[pbDeskStation[i]]->m_UserData.dwUserID;
		pUpdateUserInfo[i].dwOnLineTimeCount = 0;                                  //�˴�Ҳ����¼
		pUpdateUserInfo[i].dwChangePoint     = 0;
		pUpdateUserInfo[i].dwChangeMoney     = arPoint[i];
		pUpdateUserInfo[i].dwChangeTaxCom    = 0;                                  //�˴����շ�

		UserPoint.dwUserID                   = m_pUserInfo[pbDeskStation[i]]->m_UserData.dwUserID;
		UserPoint.dwMoney                    = arPoint[i];
        UserPoint.dwPoint                    = 0;
		m_pDataManage->m_TCPSocket.SendDataBatch(&UserPoint,sizeof(UserPoint),MDM_GR_ROOM,ASS_GR_USER_POINT,0);
	}

	DL_GR_I_AllUserData_t allUserData;
	allUserData.nUserCount = nCount;
	allUserData.nPlayTime = 0;
	allUserData.pUpdateUserInfo = pUpdateUserInfo;
	m_pDataManage->m_SQLDataManage.PushLine(&allUserData.DataBaseHead,sizeof(allUserData),DTK_GR_UPDATE_GAME_RESULT_ALLUSER,0,0);	
	
	
}
//��¼�û�����
void CGameDesk::UpdateUserInfo(long dwUserID,int iPoint,int Money, int taxCom,bool bcut,long playTime,long logonTime)
{//��Point��ΪiPoint����ΪPoint��MFC�ڲ���һ���࣬��Ȼ�������ƿ���ʹ�ã�������������
 //����������������λ�ã�����Ϊ��������¼�˻��֣������ݷ�������Ӯ�����ж�
	//����vip����
	DL_GR_I_UserLeft m_UserInfo;
	memset(&m_UserInfo,0,sizeof(m_UserInfo));
	m_UserInfo.uWinCount = (iPoint > 0 ? 1:0);
	m_UserInfo.uLostCount =(iPoint < 0 ? 1:0);
	m_UserInfo.uMidCount = (iPoint == 0 ? 1:0);
	m_UserInfo.dwUserID = dwUserID;
	m_UserInfo.dwChangeMoney = Money;
	m_UserInfo.dwChangeTaxCom = taxCom;
	m_UserInfo.uCutCount = bcut;
	m_UserInfo.dwPlayTimeCount = playTime;
	m_UserInfo.dwOnLineTimeCount = logonTime;

	DL_GR_I_SendMonet_By_Times sSendMoneyByTimes;//��ǰ�û�ΪҪ�͵��û�
	memset(&sSendMoneyByTimes,0,sizeof(sSendMoneyByTimes));
	sSendMoneyByTimes.dwUserID =dwUserID;
	sSendMoneyByTimes.dwGameFinishCount+=1;

	for(int i = 0; i < MAX_PEOPLE; i ++)
	{
		if(m_pUserInfo[i] == NULL)
			continue;

		CString stime;
		stime.Format("%d",CTime::GetCurrentTime());        //��ǰ��ʱ�䣬String��ʽ
		int curtime=atoi(stime);                           //ת��Ϊint

		if(dwUserID == m_pUserInfo[i]->m_UserData.dwUserID)
		{
			//�ж��Ƿ�Ϊ��Ա��ԭ�е�˵����Fred Huang��
			//�ж��Ƿ񻹿�����˫������
			if(iPoint>0)
			{	//ʤ���������˫�����֣������*2
				if(m_pUserInfo[i]->m_UserData.iDoublePointTime>curtime)
				{
					//��λ��˫�����ֿ���Ч20081125
					m_byDoublePointEffect |= (1<<i);

					iPoint *= 2;
				}
			}
			else
			{  //ʧ�ܣ�����л����������ֲ��䣬����Ӧ��
				if(m_pUserInfo[i]->m_UserData.iProtectTime>curtime)
					iPoint=0;
			}
			m_UserInfo.dwChangePoint = iPoint;

			sSendMoneyByTimes.i64SrcGameMoney = m_pUserInfo[i]->m_UserData.i64Money;//Ǯ
			sSendMoneyByTimes.i64SrcMoneyInBank = m_pUserInfo[i]->m_UserData.i64Bank;//����
			
			
			break;
		}
	}
	m_pDataManage->m_SQLDataManage.PushLine(&m_UserInfo.DataBaseHead,sizeof(m_UserInfo),DTK_GR_UPDATE_GAME_RESULT,0,0);

	//�����ͽ��
	
	m_pDataManage->m_SQLDataManage.PushLine(&sSendMoneyByTimes.DataBaseHead,sizeof(sSendMoneyByTimes),DTK_GR_SENDMONEY_TIMES,0,0);
	return ;
}
//����
bool CGameDesk::SendGameData(BYTE bDeskStation, BYTE bMainID, BYTE bAssID, BYTE bHandleCode)
{
	ASSERT(bDeskStation <= m_bMaxPeople);
	if (bDeskStation < m_bMaxPeople)
	{
		if ((m_pUserInfo[bDeskStation] != NULL))
		{
			UINT uSocketIndex = m_pUserInfo[bDeskStation]->m_uSocketIndex;
			m_pDataManage->m_TCPSocket.SendData(uSocketIndex,bMainID,bAssID,bHandleCode,m_pUserInfo[bDeskStation]->m_dwHandleID);
		}
	}
	else 
	{
		for (BYTE i = 0; i < m_bMaxPeople; i ++)
		{
			if (m_pUserInfo[i] != NULL)
			{
				UINT uSocketIndex=m_pUserInfo[i]->m_uSocketIndex;
				m_pDataManage->m_TCPSocket.SendData(uSocketIndex,bMainID,bAssID,bHandleCode,m_pUserInfo[i]->m_dwHandleID);
			}
		}
	}
	return true;
}

//�����Թ����� ��������Ϣ���Թ��ߣ�
bool CGameDesk::SendWatchData(BYTE bDeskStation, BYTE bMainID, BYTE bAssID, BYTE bHandleCode)
{
	ASSERT(bDeskStation <= m_bMaxPeople);
	for (INT_PTR i = 0; i< m_WatchUserPtr.GetCount(); i ++)
	{
		CGameUserInfo * pUserInfo = (CGameUserInfo *)m_WatchUserPtr.GetAt(i);
		if (((pUserInfo != NULL)&&(pUserInfo->m_UserData.bUserState != USER_CUT_GAME))
			&&((pUserInfo->m_UserData.bDeskStation == bDeskStation)||(bDeskStation == m_bMaxPeople)))
		{
			m_pDataManage->m_TCPSocket.SendData(pUserInfo->m_uSocketIndex,bMainID,bAssID,bHandleCode,pUserInfo->m_dwHandleID);
		}
	}
	return true;
}

//�������ݺ��� ��������Ϣ����Ϸ�ߣ�
bool CGameDesk::SendGameData(BYTE bDeskStation, void * pData, UINT uSize, BYTE bMainID, BYTE bAssID, BYTE bHandleCode)
{
	ASSERT(bDeskStation <= m_bMaxPeople);
	if (bMainID == MDM_GM_MESSAGE && bAssID == ASS_GM_SYSTEM_MESSAGE_EX)
	{

		GameNoticeMessage* p = (GameNoticeMessage*)pData;
		if (p != NULL)
		{
			m_pDataManage->m_TCPSocket.SendDataBatch(pData, uSize, MDM_GM_GAME_NOTIFY, ASS_GM_MESSAGE_EX,0);

			//��������
			//	�������� 
			MSG_GA_S_Message Message;
			memset(&Message,0,sizeof(Message));
			Message.bFontSize=0;
			Message.bCloseFace=false;
			Message.bShowStation=SHS_TALK_MESSAGE;
			sprintf(Message.szMessage, p->szMessage);
			m_pDataManage->m_TCPSocket.SendDataBatch(&Message,sizeof(Message),MDM_GR_MESSAGE,ASS_GR_SYSTEM_MESSAGE,0);
			return true;
		}
	}
	if (bDeskStation < m_bMaxPeople)
	{
		if ((m_pUserInfo[bDeskStation] != NULL)&&(m_pUserInfo[bDeskStation]->m_UserData.bUserState != USER_CUT_GAME))
		{
			UINT uSocketIndex = m_pUserInfo[bDeskStation]->m_uSocketIndex;
			m_pDataManage->m_TCPSocket.SendData(uSocketIndex,pData,uSize,bMainID,bAssID,bHandleCode,m_pUserInfo[bDeskStation]->m_dwHandleID);
		}
	}
	else 
	{
		for (BYTE i = 0; i < m_bMaxPeople; i ++)
		{
			if ((m_pUserInfo[i] != NULL)&&(m_pUserInfo[i]->m_UserData.bUserState != USER_CUT_GAME))
			{
				m_pDataManage->m_TCPSocket.SendData(m_pUserInfo[i]->m_uSocketIndex,pData,uSize,bMainID,bAssID,bHandleCode,m_pUserInfo[i]->m_dwHandleID);
			}
		}
	}
	return true;
}

//�����Թ����� ��������Ϣ���Թ��ߣ�
bool CGameDesk::SendWatchData(BYTE bDeskStation, void * pData, UINT uSize, BYTE bMainID, BYTE bAssID, BYTE bHandleCode)
{
	ASSERT(bDeskStation <= m_bMaxPeople);
	for (INT_PTR i = 0; i < m_WatchUserPtr.GetCount(); i ++)
	{
		CGameUserInfo * pUserInfo = (CGameUserInfo *)m_WatchUserPtr.GetAt(i);
		if (((pUserInfo!=NULL)&&(pUserInfo->m_UserData.bUserState != USER_CUT_GAME))&&
			((pUserInfo->m_UserData.bDeskStation == bDeskStation)||(bDeskStation == m_bMaxPeople)))
		{
			m_pDataManage->m_TCPSocket.SendData(pUserInfo->m_uSocketIndex,pData,uSize,bMainID,bAssID,bHandleCode,pUserInfo->m_dwHandleID);
		}
	}
	return true;
}

//�����Թ����� ��������Ϣ���Թ��ߣ�
bool CGameDesk::SendWatchDataByID(UINT uSendSocketID, void * pData, UINT uSize, BYTE bMainID, BYTE bAssID, BYTE bHandleCode)
{
	for (INT_PTR i = 0; i < m_WatchUserPtr.GetCount(); i ++)
	{
		CGameUserInfo * pUserInfo = (CGameUserInfo *)m_WatchUserPtr.GetAt(i);
		if ((pUserInfo != NULL)&&(pUserInfo->m_uSocketIndex == uSendSocketID)
			&&(pUserInfo->m_UserData.bUserState != USER_CUT_GAME))
		{
			m_pDataManage->m_TCPSocket.SendData(uSendSocketID,pData,uSize,bMainID,bAssID,bHandleCode,pUserInfo->m_dwHandleID);
			return true;
		}
	}
	return false;
}

//�Ƿ���Զ���
bool CGameDesk::CanNetCut(BYTE bDeskStation)
{
	return m_bBreakCount[bDeskStation] < NET_CUT_TIMES;
}

/// ����������ж�����,Ϊ�Ŷӻ����
int CGameDesk::GetDeskPlayerNum()
{
	int iPeopoleCount = 0;
	for (BYTE i = 0 ; i < m_bMaxPeople; i ++) 
	{
		if (m_pUserInfo[i] != NULL)
		{
			iPeopoleCount++;
		}
	}

	return iPeopoleCount;
}

/// ��������е�һ��û���˵���λ����
///@return ���������ˣ�����-1;���򣬷��ص�һ������λ����
int CGameDesk::GetDeskNoPlayerStation()
{
	int iDeskStation = 0;
	for (BYTE i = 0 ; i < m_bMaxPeople; i ++) 
	{
		if (m_pUserInfo[i] != NULL)
		{
			iDeskStation++;
		}
		else
		{
			break;
		}
	}

	if (iDeskStation < m_bMaxPeople)
	{
		return iDeskStation;
	}
	else
	{
		return -1;
	}	
}

/// �жϴ�������ҵ�ip�Ƿ�����ͬ��,Ϊ�Ŷӻ����
///@return:��ip��ͬ����ҷ���true�����򣬷���false
bool CGameDesk::IsDeskIpSame(CGameUserInfo * pUserInfo)
{
	return false;
	
	if (NULL == pUserInfo)
	{
		return false;
	}

	ULONG dwUserIP=pUserInfo->m_UserData.dwUserIP;
	for (BYTE i=0;i<m_bMaxPeople;i++)
	{
		if(m_pUserInfo[i]==NULL)
			continue;

		//�Ƿ�IP��ͬ
		if ((m_pUserInfo[i]->m_UserData.dwUserIP==dwUserIP)
			/*&& pUserInfo->m_UserData.bGameMaster==0*/) 
		{
			return true;
		}
	}

	for (BYTE i=0;i<m_bMaxPeople-1;i++)
	{
		if (m_pUserInfo[i]==NULL) 
			continue;

		for (BYTE j=i+1;j<m_bMaxPeople;j++)
		{
			if ((m_pUserInfo[j]!=NULL)
				&& (m_pUserInfo[i]->m_UserData.dwUserIP==m_pUserInfo[j]->m_UserData.dwUserIP)
				/*&& pUserInfo->m_UserData.bGameMaster==0*/) 
			{
				return true;
			}
		}
	}

	/////////////////////////////////////////////////////////////////////
	return false;
}

/// ���������е������Ϣ, ���������ָ���Ŀ���λ�ϣ������ָ����λ�������Ϣ
///@param para1:�û���Ϣ��ָ��
///@param para2:��λ����
void CGameDesk::SetDeskUserInfo(CGameUserInfo * pUserInfo, int iDeskStation)
{
	if (iDeskStation < m_bMaxPeople)
	{
		if (NULL != pUserInfo && NULL == m_pUserInfo[iDeskStation])
		{
			m_pUserInfo[iDeskStation] = pUserInfo;
		}

		if (NULL == pUserInfo)
		{
			m_pUserInfo[iDeskStation] = NULL;
		}
	}
	
	return;
}

//�ж��Ƿ���Կ�ʼ��Ϸ
bool CGameDesk::CanBeginGame()
{
	//�ж��������Ƿ�ͬ��
	BYTE bPeopoleCount = 0;
	for (BYTE i = 0 ; i < m_bMaxPeople; i ++) 
	{
		if (m_pUserInfo[i] != NULL)
		{
			bPeopoleCount ++;
			if (m_pUserInfo[i]->m_UserData.bUserState != USER_ARGEE)
				return false;
		}
	}

	//�ж��ʺϿ�ʼ����
	if (bPeopoleCount > 1L)
	{
		if (m_bBeginMode == SYMMETRY_ARGEE)
		{
			if ((bPeopoleCount % 2) != 0) 
				return false;

			if (bPeopoleCount == m_bMaxPeople)
				return true;
			BYTE bHalfCount = m_bMaxPeople/2;

			for (BYTE i = 0; i < bHalfCount; i ++)
			{
				if ((m_pUserInfo[i] == NULL)&&(m_pUserInfo[i + bHalfCount] != NULL)) 
					return false;

				if ((m_pUserInfo[i] != NULL)&&(m_pUserInfo[i + bHalfCount] == NULL)) 
					return false;
			}
			return true;
		}
		else 
		{
			if (m_bBeginMode == FULL_BEGIN) 
				return (bPeopoleCount == m_bMaxPeople);
			else if (m_bBeginMode == ALL_ARGEE) 
				return true;
			//-----------yinyi��6��������4���˿�ʼ---------------------
			else if (m_bBeginMode==FOUR_SIX_ARGEE)
			{
				if(bPeopoleCount >=4)
					return true;
				if (bPeopoleCount == m_bMaxPeople)
					return true;
				return false;
			}
		   //-----------yinyi��6��������4���˿�ʼ---------------------
		}
	}

	return false;
}
/// ǿ��������ߺ���
/// �����Ƿ�����Ϸ�У���ǿ��������ߣ������������д����������ߺ����Ϸ����
/// ��ձ������еĸ������Ϣ�����ý����󣬸�����뿪�����䣬ͬʱm_pUserInfo[bDeskStation]�ᱻ���NULL
/// ��������UserLeftDesk���������ڣ��������Ƿ���������������ϵĽ�����������ڷ��������жϵ�����������������˳����䡣��
/// UserLeftDesk���������ɿͻ��˷���������Ϣ��������������ƽ̨���õĺ�����������Ϸ��������Ĺ�������Ӧ����������Ϸ
/// ����״̬����һ����������˳�������Ϸ�򷿼�
/// 
/// @param bDeskStation ����������е�λ�ú�
/// @return ���bDeskStation���ڱ�����һ�������������m_pUserInfo[bDeskStation]�Ѿ��ǿ�ֵNULL���򷵻�false�����򷵻�true
bool CGameDesk::MakeUserOffLine(BYTE bDeskStation)
{
	/// ���û�ҵ������ң��򷵻� false
	if (bDeskStation>=m_bMaxPeople)
	{
		return false;
	}
	if(m_pUserInfo[bDeskStation] == NULL) 
	{
		return false;
	}

	//�㲥�û��뿪
	MSG_GR_R_UserSit UserSit;
	UserSit.bLock=m_bLock;
	UserSit.bDeskIndex=m_bDeskIndex;
	UserSit.bDeskStation=bDeskStation;
	UserSit.bUserState=USER_LOOK_STATE;
	UserSit.dwUserID=m_pUserInfo[bDeskStation]->m_UserData.dwUserID;
	UserSit.bIsDeskOwner=false;
	m_pDataManage->m_TCPSocket.SendDataBatch(&UserSit,sizeof(UserSit),MDM_GR_USER_ACTION,ASS_GR_USER_UP,ERR_GR_SIT_SUCCESS);
	//�����û�����
	m_pDataManage->AutoAllotDeskDeleteUser(m_pUserInfo[bDeskStation]);
	m_pDataManage->CleanUserInfo(m_pUserInfo[bDeskStation]);
	m_pDataManage->m_UserManage.FreeUser(m_pUserInfo[bDeskStation],false);
	m_pUserInfo[bDeskStation]=NULL;
	return true;
}

//�û��뿪��Ϸ��
BYTE CGameDesk::UserLeftDesk(BYTE bDeskStation, CGameUserInfo * pUserInfo)
{
	if(m_bIsBuy)
	{
		if(GetDeskPlayerNum()<=1)
		{
			KillTimer(IDT_CHECK_DESK);
			SetTimer(IDT_CHECK_DESK,3*60*1000);
		}
		else
		{
			//m_pDataManage->OnUserNetCutDissmiss(m_pUserInfo[bDeskStation]);
		}
	}
	//wushuqun 2009.5.26
	//��ֹ�������ݷ���Խ����ɱ�������27����Ϸ�г��ֹ�
	//��鴫���������ݵ��Ƿ���Ч
	if (bDeskStation < 0 || bDeskStation >= m_bMaxPeople)
	{
		return ERR_GR_SIT_SUCCESS;
	}
	if (! pUserInfo )
	{
		return ERR_GR_SIT_SUCCESS;
	}
	///////////

	if(m_pUserInfo[bDeskStation] == NULL) 
		return ERR_GR_SIT_SUCCESS;
	//Ч������ 
	ASSERT(m_pUserInfo[bDeskStation] == pUserInfo);

	//��������
	m_bConnect[bDeskStation] = false;
	if (IsPlayGame(bDeskStation))
		GameFinish(bDeskStation,GFF_FORCE_FINISH);


	//���¹���
	UINT uSitCount = 0L;
	for (BYTE i = 0; i < m_bMaxPeople; i ++)
	{
		if (m_pUserInfo[i] != NULL) 
			uSitCount ++;
	}
	if (uSitCount == 1)
	{
		m_bLock=false;
		m_szLockPass[0]=0;
	}

	//���ͷ�����Ϣ
	MSG_GR_R_UserSit UserSit;
	UserSit.bLock=m_bLock;
	UserSit.bDeskIndex=m_bDeskIndex;
	UserSit.bDeskStation=bDeskStation;
	UserSit.bUserState=USER_LOOK_STATE;
	UserSit.dwUserID=pUserInfo->m_UserData.dwUserID;
	UserSit.bIsDeskOwner=(m_dwOwnerUserID==m_pUserInfo[bDeskStation]->m_UserData.dwUserID);
	m_pDataManage->m_TCPSocket.SendDataBatch(&UserSit,sizeof(UserSit),MDM_GR_USER_ACTION,ASS_GR_USER_UP,ERR_GR_SIT_SUCCESS);

	//����̨��
	if (m_dwOwnerUserID==m_pUserInfo[bDeskStation]->m_UserData.dwUserID)
	{
		m_dwOwnerUserID=0L;
		//m_DeskBasePoint=0;
		for(int i=0; i<MAX_PEOPLE; i++)
		{
			if(i == bDeskStation)
				continue;
			// ������һ��̨��
			if(m_pUserInfo[i])
			{
				m_dwOwnerUserID = m_pUserInfo[i]->m_UserData.dwUserID;
				//m_DeskBasePoint = m_pUserInfo[i]->m_UserData.uDeskBasePoint;
				break;
			}
		}
	}

	//��������
	m_uCutTime[bDeskStation]=0L;
	m_bConnect[bDeskStation]=false;
	m_pUserInfo[bDeskStation]=NULL;
	m_bEnableWatch&=~(1<<bDeskStation);
	pUserInfo->m_UserData.bDeskNO=255;
	pUserInfo->m_UserData.bDeskStation=255;
	pUserInfo->m_UserData.bUserState=USER_LOOK_STATE;
	//�ж��Ƿ���Կ�ʼ
	if (CanBeginGame()==true) GameBegin(0);

	return ERR_GR_SIT_SUCCESS;
}

//�Թ��û�������Ϸ��
BYTE CGameDesk::WatchUserSitDesk(MSG_GR_S_UserSit* pUserSit, CGameUserInfo * pUserInfo)
{
	//Ч������ 
	if (pUserInfo==NULL) return ERR_GR_ERROR_UNKNOW;
	//�������Թ�
	if(m_pDataManage->m_InitData.dwRoomRule&GRR_UNENABLE_WATCH)
		return ERR_GR_UNENABLE_WATCH;

	//Ѱ���Թ�λ��
	UINT dwWatchStation;
	for (dwWatchStation=0;dwWatchStation<(UINT)m_WatchUserPtr.GetCount();dwWatchStation++)
	{
		if (m_WatchUserPtr.GetAt(dwWatchStation)==NULL)	break;
	}

	//����Ч��
	if ((m_bLock==true)&&(CUserPower::CanThrowPass(pUserInfo->m_dwGamePower)==false))
	{
		if (lstrcmp(m_szLockPass,pUserSit->szPassword)!=0)//20081205
			return ERR_GR_PASS_ERROR;
	}

	//��������
	pUserInfo->m_UserData.bDeskNO=m_bDeskIndex;
	pUserInfo->m_UserData.bDeskStation=pUserSit->bDeskStation;
	pUserInfo->m_UserData.bUserState=USER_WATCH_GAME;
	m_WatchUserPtr.SetAtGrow(dwWatchStation,pUserInfo);

	//���ʹ�����Ϣ
	MSG_GR_R_UserSit UserWatchSit;
	UserWatchSit.bLock=m_bLock;
	UserWatchSit.bDeskIndex=m_bDeskIndex;
	UserWatchSit.bDeskStation=pUserSit->bDeskStation;
	UserWatchSit.bUserState=USER_WATCH_GAME;
	UserWatchSit.dwUserID=pUserInfo->m_UserData.dwUserID;
	m_pDataManage->m_TCPSocket.SendDataBatch(&UserWatchSit,sizeof(UserWatchSit),MDM_GR_USER_ACTION,ASS_GR_WATCH_SIT,ERR_GR_SIT_SUCCESS);

	return ERR_GR_SIT_SUCCESS;
}

//�Թ��û��뿪��Ϸ��
BYTE CGameDesk::WatchUserLeftDesk(BYTE bDeskStation, CGameUserInfo * pUserInfo)
{
	//Ч������ 
	if (pUserInfo==NULL) return ERR_GR_ERROR_UNKNOW;
	UINT dwWatchStation;
	//Ѱ���Թ�λ��
	for (dwWatchStation=0;dwWatchStation<(UINT)m_WatchUserPtr.GetCount();dwWatchStation++)
	{
		CGameUserInfo * pWatchUserInfo=(CGameUserInfo *)m_WatchUserPtr.GetAt(dwWatchStation);
		if (pWatchUserInfo==pUserInfo) break;
	}
	if (dwWatchStation==m_WatchUserPtr.GetCount()) return ERR_GR_ERROR_UNKNOW;

	//���ʹ�����Ϣ
	MSG_GR_R_UserSit UserWatchUp;
	UserWatchUp.bLock=m_bLock;
	UserWatchUp.bDeskIndex=m_bDeskIndex;
	UserWatchUp.bDeskStation=bDeskStation;
	UserWatchUp.bUserState=USER_LOOK_STATE;
	UserWatchUp.dwUserID=pUserInfo->m_UserData.dwUserID;
	m_pDataManage->m_TCPSocket.SendDataBatch(&UserWatchUp,sizeof(UserWatchUp),MDM_GR_USER_ACTION,ASS_GR_WATCH_UP,ERR_GR_SIT_SUCCESS);

	//��������
	pUserInfo->m_UserData.bDeskNO=255;
	pUserInfo->m_UserData.bDeskStation=255;
	pUserInfo->m_UserData.bUserState=USER_LOOK_STATE;
	m_WatchUserPtr.SetAt(dwWatchStation,NULL);

	return ERR_GR_SIT_SUCCESS;
}

//�û�ͬ�⿪ʼ
bool CGameDesk::UserAgreeGame(BYTE bDeskStation)
{
	OutputDebugString("cq::--------ƽ̨-����ˣ��û����ͬ�⿪ʼ��ť��------");

	if (m_pUserInfo[bDeskStation]!=NULL
		&&m_pUserInfo[bDeskStation]->m_UserData.i64Money < m_pDataManage->m_InitData.uLessPoint
		&&m_pDataManage->m_InitData.uComType == TY_MONEY_GAME)
	{
		OutputDebugString("cq::--------ƽ̨-����ˣ��û����ͬ�⿪ʼ�����Ͻ�Ҳ��㣡------");
		UserLeftDesk(bDeskStation,m_pUserInfo[bDeskStation]);
		return true;
	}

    //�Ŷӻ�����������ʱ�����²����Ŷ�
    if(m_pDataManage->IsQueueGameRoom())
    {
		char cKey[10];
		CString sPath=CBcfFile::GetAppPath();
		CBcfFile fsr(sPath + "SpecialRule.bcf");
		sprintf(cKey, "%d", m_pDataManage->m_KernelData.uNameID);
		int HaveZhuang = fsr.GetKeyVal (_T("IsHaveZhuang"), cKey, 0);
		if(
			//{add by rongqiufen 2010.06.29
			///����ׯ��Ϸ����Ϸ���յ�ͬ����Ϣ����ɢ����
			(m_pUserInfo[bDeskStation] != NULL && (HaveZhuang == 0) && (m_pUserInfo[bDeskStation]->m_UserData.bUserState == USER_PLAY_GAME || m_pUserInfo[bDeskStation]->m_UserData.bUserState == USER_SITTING))  || 
			//add by rongqiufen 2010.06.29}
			(GetDeskPlayerNum() < m_bMaxPeople && m_pUserInfo[bDeskStation] != NULL)
			)
        {

			//��������
			m_pUserInfo[bDeskStation]->m_UserData.bUserState=USER_ARGEE;

			//�ȷ�����Ϸͬ����Ϣ, ����Ŷӻ��Զ������Ŷ�

			MSG_GR_R_UserAgree UserAgree;
			UserAgree.bAgreeGame=TRUE;
			UserAgree.bDeskNO=m_bDeskIndex;
			UserAgree.bDeskStation=bDeskStation;
			UINT uSocketIndex = m_pUserInfo[bDeskStation]->m_uSocketIndex;

			if (m_pDataManage->m_InitData.dwRoomRule & GRR_GAME_U3D)
			{
				m_pDataManage->m_TCPSocket.SendDataBatch(&UserAgree,sizeof(UserAgree),MDM_GR_ROOM,ASS_GR_USER_AGREE,0);

				//�ж��Ƿ���Կ�ʼ
				if (CanBeginGame()==true) 
				{
					GameBegin(0);
					return true;
				}
			}
			else
			{
				//�ж��Ƿ���Կ�ʼ
				if (!(m_pDataManage->m_InitData.dwRoomRule&GRR_CONTEST)&& !(m_pDataManage->m_InitData.dwRoomRule&GRR_TIMINGCONTEST) && CanBeginGame()==true) 
				{
					GameBegin(0);
					return true;
				}

				m_pDataManage->m_TCPSocket.SendDataBatch(&UserAgree,sizeof(UserAgree),MDM_GR_ROOM,ASS_GR_USER_AGREE,0);
			}

            //UserLeftDesk(bDeskStation, m_pUserInfo[bDeskStation]);
            return true;
        }
    }

	if ((m_pUserInfo[bDeskStation]!=NULL)
		&&(m_pUserInfo[bDeskStation]->m_UserData.bUserState==USER_DESK_AGREE 
		|| (m_pDataManage->m_InitData.dwRoomRule &GRR_ALL_ON_DESK) != 0))
	{
		//��������
		m_pUserInfo[bDeskStation]->m_UserData.bUserState=USER_ARGEE;


		//������Ϸͬ����Ϣ
		MSG_GR_R_UserAgree UserAgree;
		UserAgree.bAgreeGame=TRUE;
		UserAgree.bDeskNO=m_bDeskIndex;
		UserAgree.bDeskStation=bDeskStation;

		if (m_pDataManage->m_InitData.dwRoomRule & GRR_GAME_U3D)
		{
			m_pDataManage->m_TCPSocket.SendDataBatch(&UserAgree,sizeof(UserAgree),MDM_GR_ROOM,ASS_GR_USER_AGREE,0);

			//�ж��Ƿ���Կ�ʼ
			if (CanBeginGame()==true) 
			{
				GameBegin(0);
				return true;
			}
		}
		else
		{
			//�ж��Ƿ���Կ�ʼ
			if (!(m_pDataManage->m_InitData.dwRoomRule&GRR_CONTEST)&& !(m_pDataManage->m_InitData.dwRoomRule&GRR_TIMINGCONTEST) && CanBeginGame()==true) 
			{
				GameBegin(0);
				return true;
			}

			m_pDataManage->m_TCPSocket.SendDataBatch(&UserAgree,sizeof(UserAgree),MDM_GR_ROOM,ASS_GR_USER_AGREE,0);
		}
		return true;
	}
	else
	{
		//wushuqun 2009.9.5
		if ((m_pUserInfo[bDeskStation]!=NULL) && (m_pDataManage->m_InitData.dwRoomRule &GRR_ALL_ON_DESK)==0)
		{
			//��������
			m_pUserInfo[bDeskStation]->m_UserData.bUserState=USER_ARGEE;

			//������Ϸͬ����Ϣ
			MSG_GR_R_UserAgree UserAgree;
			UserAgree.bAgreeGame=TRUE;
			UserAgree.bDeskNO=m_bDeskIndex;
			UserAgree.bDeskStation=bDeskStation;

			if (m_pDataManage->m_InitData.dwRoomRule & GRR_GAME_U3D)
			{
				m_pDataManage->m_TCPSocket.SendDataBatch(&UserAgree,sizeof(UserAgree),MDM_GR_ROOM,ASS_GR_USER_AGREE,0);

				//�ж��Ƿ���Կ�ʼ
				if (CanBeginGame()==true) 
				{
					GameBegin(0);
					return true;
				}
			}
			else
			{
				//�ж��Ƿ���Կ�ʼ
				if (!(m_pDataManage->m_InitData.dwRoomRule&GRR_CONTEST)&& !(m_pDataManage->m_InitData.dwRoomRule&GRR_TIMINGCONTEST) && CanBeginGame()==true) 
				{
					GameBegin(0);
					return true;
				}

				m_pDataManage->m_TCPSocket.SendDataBatch(&UserAgree,sizeof(UserAgree),MDM_GR_ROOM,ASS_GR_USER_AGREE,0);
			}

			return true;
		}
	}

	return false;
}

//������Ϸ״̬
bool CGameDesk::SendGameStation(BYTE bDeskStation, UINT uSocketID, bool bWatchUser, void * pStationData, UINT uSize)
{
	if (NULL == m_pDataManage)
	{
		return true;
	}

	//��ȡ��Ϸ��Ϣ
	UINT uSendSize=0;
	MSG_GM_S_GameInfo GameInfo;
	GameInfo.bGameStation=m_bGameStation;///< ��Ϸ״̬
	GameInfo.bWatchOther=((m_bEnableWatch&(1<<bDeskStation))!=0);
	GameInfo.bWaitTime=m_bWaitTime;
	GameInfo.bReserve=FALSE;
	if (m_pDataManage->m_szMsgGameLogon[0]!=0)
	{
		lstrcpy(GameInfo.szMessage,m_pDataManage->m_szMsgGameLogon);
		uSendSize=sizeof(GameInfo)-sizeof(GameInfo.szMessage)+(lstrlen(m_pDataManage->m_szMsgGameLogon)+1)*sizeof(char);
	}
	else 
	{
		GameInfo.szMessage[0]=0;
		uSendSize=sizeof(GameInfo)-sizeof(GameInfo.szMessage);
	}

	//������Ϸ��Ϣ

	if (bWatchUser==false) SendGameData(bDeskStation,&GameInfo,uSendSize,MDM_GM_GAME_FRAME,ASS_GM_GAME_INFO,0);
	else SendWatchDataByID(uSocketID,&GameInfo,uSendSize,MDM_GM_GAME_FRAME,ASS_GM_GAME_INFO,0);

	//������Ϸ״̬
	if (bWatchUser==false) SendGameData(bDeskStation,pStationData,uSize,MDM_GM_GAME_FRAME,ASS_GM_GAME_STATION,0);
	else SendWatchDataByID(uSocketID,pStationData,uSize,MDM_GM_GAME_FRAME,ASS_GM_GAME_STATION,0);

	/// �Ŷӻ���Ϸ�Ƿ���Կ�ʼ
	if (m_pDataManage->IsQueueGameRoom() && CanBeginGame())
	{
		for (BYTE i=0; i<m_bMaxPeople; i++)
		{
			if (m_pUserInfo[i]!=NULL)
			{
				if (!m_bConnect[m_pUserInfo[i]->m_UserData.bDeskStation])
				{
					return true;
				}
			}
		}

		GameBegin(0);
	}

	return true;
}

//��Ϸ��ʼ
bool CGameDesk::GameBegin(BYTE bBeginFlag)
{
	if ((m_pDataManage->m_InitData.uLessPoint!=0)&&(m_pDataManage->m_InitData.uComType==TY_MONEY_GAME))
	{
		bool quit=false;
		for (BYTE i=0;i<m_bMaxPeople;i++)
		{
			if (m_pDataManage->m_InitData.dwRoomRule & GRR_CONTEST || m_pDataManage->m_InitData.dwRoomRule & GRR_TIMINGCONTEST)
				break;
			if (m_pUserInfo[i]!=NULL
				//&&((m_pUserInfo[i]->m_UserData.dwMoney < 100*m_DeskBasePoint
				&&((m_pUserInfo[i]->m_UserData.i64Money < (int)m_pDataManage->m_InitData.uLessPoint
				&&m_pDataManage->m_InitData.uComType == TY_MONEY_GAME)
				||m_pDataManage->m_InitData.uComType != TY_MONEY_GAME))
			{
				CString str;
				str.Format("cq::--------------3----------------�����������%d����", m_pUserInfo[i]->m_UserData.dwUserID);
				OutputDebugString(str);
				MakeUserOffLine(i);
				///UserLeftDesk(i,m_pUserInfo[i]);
				quit=true;
			}
		}
		if(quit) return false;
	}
	//��������
	m_bPlayGame = true;
	m_dwBeginTime=(long int)time(NULL);
	m_dwTax=0;
	memset(m_bCutGame,0,sizeof(m_bCutGame));
	memset(m_uCutTime,0,sizeof(m_uCutTime));
	memset(m_bBreakCount,0,sizeof(m_bBreakCount));
	memset(m_dwChangePoint,0,sizeof(m_dwChangePoint));
	memset(m_dwChangeMoney,0,sizeof(m_dwChangeMoney));
	memset(m_dwTaxCom,0,sizeof(m_dwTaxCom));

	m_byDoublePointEffect = 0;

	//��¼��Ϸ
	for (BYTE i=0;i<m_bMaxPeople;i++)
	{
		if (m_pUserInfo[i]!=NULL)
		{
			CString str;
			m_dwGameUserID[i]=m_pUserInfo[i]->m_UserData.dwUserID;
			m_dwScrPoint[i]=m_pUserInfo[i]->m_UserData.dwPoint;
			m_pUserInfo[i]->m_UserData.bUserState=USER_PLAY_GAME;

			//��¼������������
			if (m_bIsBuy && m_iRunGameCount==0)
			{
				DL_GR_I_CutNetRecord input_net;
				input_net.bClear=true;
				input_net.byDeskIndex=m_bDeskIndex;
				input_net.iRoomID=m_pDataManage->m_InitData.uRoomID;
				input_net.iUserID=m_pUserInfo[i]->m_UserData.dwUserID;
				m_pDataManage->m_SQLDataManage.PushLine(&input_net.DataBaseHead, sizeof(input_net), DTK_GR_CUTNETRECORD, 0, 0);
			}

		}
		else
		{
			m_dwScrPoint[i]=0L;
			m_dwGameUserID[i]=0L;
		}
	}

	m_tBeginTime = CTime::GetCurrentTime();
	//���ʹ�����Ϣ
	m_pDataManage->m_TCPSocket.SendDataBatch(NULL,0,MDM_GR_ROOM,ASS_GR_GAME_BEGIN,m_bDeskIndex);

	return true;
}

//��Ϸ����
bool CGameDesk::GameFinish(BYTE bDeskStation, BYTE bCloseFlag)
{
	if (m_pDataManage->m_InitData.dwRoomRule & GRR_CONTEST || m_pDataManage->m_InitData.dwRoomRule & GRR_TIMINGCONTEST)
	{
		return GameFinishContest(bDeskStation, bCloseFlag);
	}
	//��������
	m_bPlayGame=false;
	m_dwBeginTime=(long int)time(NULL);
	m_iDissmissAgreePeople=0;
	if(m_bIsBuy)
	{
		m_iRunGameCount++;
		if (1 == m_iRunGameCount)	//����һ�ֿ۷���
		{

			DL_GR_I_BuyDeskOut input_cleardesk;
			input_cleardesk.byDeskIndex=m_bDeskIndex;
			input_cleardesk.iRoomID=m_pDataManage->m_InitData.uRoomID;
			input_cleardesk.iVipGameCount=m_iVipGameCount;						
			input_cleardesk.iDeskMaster=m_iDeskMaster;							
			memcpy(input_cleardesk.szDeskPassWord,m_szDeskPassWord,sizeof(input_cleardesk.szDeskPassWord));
			m_pDataManage->m_SQLDataManage.PushLine(&input_cleardesk.DataBaseHead, sizeof(input_cleardesk), DTK_GP_DEDUCTROOMCARD, 0, 0);

		}
		if(m_iRunGameCount>=m_iVipGameCount)//���������ѵ���
		{
			m_pDataManage->ClearDeskRunOutInfo(this);
			if(m_pDataManage->OnClearDesk(m_bDeskIndex,m_pDataManage->m_InitData.uRoomID,0))
			{
				DL_GR_I_BuyDeskOut input_cleardesk;
				input_cleardesk.byDeskIndex=m_bDeskIndex;
				input_cleardesk.iRoomID=m_pDataManage->m_InitData.uRoomID;
				input_cleardesk.iVipGameCount=m_iVipGameCount;						
				input_cleardesk.iDeskMaster=m_iDeskMaster;							
				memcpy(input_cleardesk.szDeskPassWord,m_szDeskPassWord,sizeof(input_cleardesk.szDeskPassWord));
				m_pDataManage->m_SQLDataManage.PushLine(&input_cleardesk.DataBaseHead, sizeof(input_cleardesk), DTK_GR_CLEARBUYDESK, 0, 0);
			}
		}
	}
		
	//���ͽ�����Ϣ
	for (BYTE i=0;i<m_bMaxPeople;i++)
	{
		if (m_pUserInfo[i] == NULL)
		{
			continue;
		}
		if (m_pDataManage->IsLeaseTimeOver())
		{
			CString str;
			str.Format("cq::--------------4----------------�����������%d����", m_pUserInfo[i]->m_UserData.dwUserID);
			OutputDebugString(str);
			m_pDataManage->m_TCPSocket.SendData(m_pUserInfo[i]->m_uSocketIndex, MDM_GR_USER_ACTION, ASS_GR_LEASE_TIMEOVER, 0, 0);
			MakeUserOffLine(i);
		}
		// �������Ѿ�ûǮ�ˣ��������뿪����
		if ((m_pUserInfo[i]->m_UserData.i64Money < (int)m_pDataManage->m_InitData.uLessPoint)
			&&(m_pDataManage->m_InitData.uComType == TY_MONEY_GAME))
		{
			if (!m_pDataManage->IsQueueGameRoom())
				MakeUserOffLine(i);		
			continue;
		}
		if ((m_pUserInfo[i] != NULL) && (m_pUserInfo[i]->m_UserData.bUserState != USER_CUT_GAME))
		{
			m_pUserInfo[i]->m_UserData.bUserState = USER_SITTING;
		}
	}	
	//���ʹ�����Ϣ
	m_pDataManage->m_TCPSocket.SendDataBatch(NULL,0,MDM_GR_ROOM,ASS_GR_GAME_END,m_bDeskIndex);
	//�����������
	CleanCutGameInfo();
	return true;
}


bool CGameDesk::GameFinishContest(BYTE bDeskStation, BYTE bCloseFlag)
{
	//��������
	m_bPlayGame=false;
	m_dwBeginTime=(long int)time(NULL);
	m_pDataManage->m_TCPSocket.SendDataBatch(NULL,0,MDM_GR_ROOM,ASS_GR_GAME_END,m_bDeskIndex);
	for (BYTE i=0;i<m_bMaxPeople;i++)
	{
		if (m_pUserInfo[i] == NULL)
		{
			continue;
		}
		if (m_pUserInfo[i]->m_UserData.i64ContestScore < m_pDataManage->m_InitData.i64LowChip)
		{//�����Ҫ����̭���û�
			m_pDataManage->AutoAllotDeskDeleteUser(m_pUserInfo[i]);
		}
	}
	
	//����Ŀǰ���������жϱ����Ƿ����
	bool _bfinish = m_pDataManage->IsContestGameOver();
	//���ͽ�����Ϣ
	for (BYTE i=0;i<m_bMaxPeople;i++)
	{
		if (m_pUserInfo[i] == NULL)
		{
			continue;
		}
		if (m_pUserInfo[i]->m_UserData.i64ContestScore < (int)m_pDataManage->m_InitData.i64LowChip && !_bfinish)
		{
			CString str;
			str.Format("cq::------------�û�%d����̭", m_pUserInfo[i]->m_UserData.dwUserID);
			OutputDebugString(str);
			m_pDataManage->m_TCPSocket.SendData(m_pUserInfo[i]->m_uSocketIndex, MDM_GR_ROOM, ASS_GR_CONTEST_KICK, m_bDeskIndex, 0);	
		}
		else if (_bfinish)
		{
			//�����Ѿ��������������û���û�н�����һ��
			m_pDataManage->m_TCPSocket.SendData(m_pUserInfo[i]->m_uSocketIndex, MDM_GR_ROOM, ASS_GR_CONTEST_WAIT_GAMEOVER, m_bDeskIndex, 0);
		}
		//���ø����ӵ�״̬
		m_pUserInfo[i]->m_UserData.bDeskNO=255;
		m_pUserInfo[i]->m_UserData.bDeskStation=255;
		m_pUserInfo[i]->m_UserData.bUserState=USER_LOOK_STATE;
	}
	//�����������
	CleanCutGameInfo();

	return true;
}

//��ʱ����Ϣ
bool CGameDesk::OnTimer(UINT uTimerID)
{
	if ((uTimerID>=IDT_USER_CUT)&&(uTimerID<(UINT)(IDT_USER_CUT+m_bMaxPeople)))
	{
		//�ȴ�����ʱ�䵽��
		KillTimer(uTimerID);
		int bDeskStation=uTimerID-IDT_USER_CUT;
		if ((m_pUserInfo[bDeskStation]!=NULL)&&(m_bCutGame[bDeskStation]==true))
		{
			GameFinish(bDeskStation,GFF_FORCE_FINISH);
		}
		return true;
	}
	else if (IDT_CHECK_DESK == uTimerID)
	{
		KillTimer(uTimerID);
		m_pDataManage->ClearDeskRunOutInfo(this);

		DL_GR_I_BuyDeskOut input_cleardesk;
		input_cleardesk.byDeskIndex=m_bDeskIndex;
		input_cleardesk.iRoomID=m_pDataManage->m_InitData.uRoomID;
		input_cleardesk.iUserID=m_iDeskMaster;
		
		if(m_pDataManage->OnClearDesk(m_bDeskIndex,m_pDataManage->m_InitData.uRoomID,0))
		{
			DL_GR_I_BuyDeskOut input_cleardesk;
			input_cleardesk.byDeskIndex=m_bDeskIndex;
			input_cleardesk.iRoomID=m_pDataManage->m_InitData.uRoomID;
			input_cleardesk.iVipGameCount=m_iVipGameCount;						
			input_cleardesk.iDeskMaster=m_iDeskMaster;							
			memcpy(input_cleardesk.szDeskPassWord,m_szDeskPassWord,sizeof(input_cleardesk.szDeskPassWord));
			m_pDataManage->m_SQLDataManage.PushLine(&input_cleardesk.DataBaseHead, sizeof(input_cleardesk), DTK_GR_CLEARBUYDESK, 0, 0);
			if(IsPlayGame(0))
			{
				GameFinish(0,GFF_DISSMISS_FINISH);
			}
		}
	}
	return false;
}

//��Ϸ���ݰ�������
bool CGameDesk::HandleFrameMessage(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser)
{
	if (bDeskStation>=m_bMaxPeople|| m_pUserInfo[bDeskStation] == NULL)
	{
		return true;
	}
	ASSERT(pNetHead->bMainID==MDM_GM_GAME_FRAME);
	switch (pNetHead->bAssistantID)
	{
	case ASS_GM_GAME_INFO:		//��Ϸ״̬
		{
			//Ч������
			if (uSize!=sizeof(MSG_GM_S_ClientInfo))
			{
				DebugPrintf("[%d-%d]CGameDesk::HandleFrameMessage(ASS_GM_GAME_INFO)�����ݳ��Ȳ���ȷ[%d��]",
					this->m_pDataManage->m_KernelData.uNameID,
					this->m_pDataManage->m_InitData.uRoomID,
					__LINE__);
				return false;
			}
			MSG_GM_S_ClientInfo * pClientInfo=(MSG_GM_S_ClientInfo *)pData;
			if ((!bWatchUser) && (m_bConnect[bDeskStation]))
			{
				/// �����ٻ�����ʱ�򣬻�������������Ϊ�����ܶ��ߵ����������true��������Modified by zxd 20100301
				DebugPrintf("[%d-%d]CGameDesk::HandleFrameMessage(ASS_GM_GAME_INFO)�У����ӹ����ٴ�����[%d��]",
					this->m_pDataManage->m_KernelData.uNameID,
					this->m_pDataManage->m_InitData.uRoomID,
					__LINE__);
				return true;
			}

			//��������
			if (bWatchUser==false)
			{
				m_bConnect[bDeskStation]=true;
				if (((m_pDataManage->m_InitData.dwRoomRule&GRR_ENABLE_WATCH)==0)&&
					((m_pDataManage->m_InitData.dwRoomRule&GRR_UNENABLE_WATCH)==0))
				{
					if (pClientInfo->bEnableWatch) m_bEnableWatch|=(1<<bDeskStation);
					else m_bEnableWatch&=~(1<<bDeskStation);
				}
			}
			//��ͻ��˷�����Ƶ��������ַ
			send_video_ip(bDeskStation);
			//�����û���Ϸ״̬
			bool bRet = OnGetGameStation(bDeskStation,uSocketID,bWatchUser);

			//����Ƚ�����  ��ʱ��������  
			for (int i = 0;i< 10;++i)
			{
				if (m_pDataManage->m_uNameID == m_dwFishGamesNameID[i])
				{
					m_dwBeginTime=(long int)time(NULL);
					break;
				}
			}
			if (!bRet)
			{
				DebugPrintf("[%d-%d]CGameDesk::HandleFrameMessage(ASS_GM_GAME_INFO)��OnGetGameStation()����false[%d��]",
					this->m_pDataManage->m_KernelData.uNameID,
					this->m_pDataManage->m_InitData.uRoomID,
					__LINE__);
			}
			return bRet;
		}
	case ASS_GM_FORCE_QUIT:		//ǿ���˳�//��ȫ�˳�
		{
			if (bWatchUser==true) return true;
			if(pNetHead->bHandleCode==0)//ǿ���˳�
			{
				if (IsPlayGame(bDeskStation)==true) GameFinish(bDeskStation,GFF_FORCE_FINISH);
			}
			else if(pNetHead->bHandleCode==1)//��ȫ�˳�
			{
				if (IsPlayGame(bDeskStation)==true) GameFinish(bDeskStation,GFF_SAFE_FINISH);
			}
			return true;
		}
	case ASS_GM_NORMAL_TALK:	//��ͨ����
		{
			//��������ͨ����
			if(m_pDataManage->m_InitData.dwRoomRule & GRR_FORBID_GAME_TALK)
				return false;
			//Ч������ 
			MSG_GR_RS_NormalTalk * pNormalTalk=(MSG_GR_RS_NormalTalk *)pData;
// 			if ((uSize<=(sizeof(MSG_GR_RS_NormalTalk)-sizeof(pNormalTalk->szMessage)))||(uSize>sizeof(MSG_GR_RS_NormalTalk))) return true;
// 			if ((pNormalTalk->iLength+1)!=(uSize+sizeof(pNormalTalk->szMessage)-sizeof(MSG_GR_RS_NormalTalk))) return true;

			//��������
			CGameUserInfo * pUserInfo=m_pDataManage->m_UserManage.GetOnLineUserInfo(uSocketID);
			if (pUserInfo==NULL) return false;

			//{{ Added by zxd 20100806
			/// �������ʱ����Ч���򲻷���  
			CString strTime;
			strTime.Format("%d",CTime::GetCurrentTime());
			int curTime=atoi(strTime);
			if (pUserInfo->m_UserData.userInfoEx2 > curTime)
			{
				return true;
			}
			// Added by zxd 20100806}}

			//Ⱥ������
			//pNormalTalk->szMessage[pNormalTalk->iLength]=0;
			pNormalTalk->dwSendID=pUserInfo->m_UserData.dwUserID;

			/*bool bRet = m_pDataManage->m_TalkFilter.IsAllowableTalk(pNormalTalk->szMessage,lstrlen(pNormalTalk->szMessage));

			if (!bRet)
			{
				const CHAR* pTemTalk = m_pDataManage->m_TalkFilter.GetReplaceContent();
				strcpy(pNormalTalk->szMessage,pTemTalk);
				pNormalTalk->iLength = strlen(pTemTalk) + 1;
				pNormalTalk->szMessage[pNormalTalk->iLength]=0;
			}*/

			string str_temp(pNormalTalk->szMessage);
			m_pDataManage->m_HNFilter.censor(str_temp,false);
			strcpy(pNormalTalk->szMessage,str_temp.c_str());
			pNormalTalk->iLength = strlen(pNormalTalk->szMessage) + 1;
			pNormalTalk->szMessage[pNormalTalk->iLength]=0;

			SendGameData(m_bMaxPeople,pNormalTalk,sizeof(MSG_GR_RS_NormalTalk),MDM_GM_GAME_FRAME,ASS_GM_NORMAL_TALK,0);
			SendWatchData(m_bMaxPeople,pNormalTalk,sizeof(MSG_GR_RS_NormalTalk),MDM_GM_GAME_FRAME,ASS_GM_NORMAL_TALK,0);

			return true;
		}
	case ASS_GM_WATCH_SET:		//�Թ�����
		{
			//Ч������
			if (uSize!=sizeof(MSG_GM_WatchSet)) return false;
			MSG_GM_WatchSet * pWatchSet=(MSG_GM_WatchSet *)pData;
			if (bWatchUser==true) return false;

			//��������
			if (((m_pDataManage->m_InitData.dwRoomRule&GRR_ENABLE_WATCH)==0)&&
				((m_pDataManage->m_InitData.dwRoomRule&GRR_UNENABLE_WATCH)==0))
			{
				if (pWatchSet->dwUserID!=0L)
				{
					//��һ�û�
					for (INT_PTR i=0;i<m_WatchUserPtr.GetCount();i++)
					{
						CGameUserInfo * pUserInfo=(CGameUserInfo *)m_WatchUserPtr.GetAt(i);
						if (((pUserInfo!=NULL)&&(pUserInfo->m_UserData.dwUserID==pWatchSet->dwUserID))&&(pUserInfo->m_UserData.bDeskStation==bDeskStation))
						{
							m_pDataManage->m_TCPSocket.SendData(pUserInfo->m_uSocketIndex,MDM_GM_GAME_FRAME,ASS_GM_WATCH_SET,
								pNetHead->bHandleCode,pUserInfo->m_dwHandleID);
							break;
						}
					}
				}
				else 
				{
					//Ⱥ���û�
					if (pNetHead->bHandleCode==TRUE) m_bEnableWatch|=(1<<bDeskStation);
					else m_bEnableWatch&=~(1<<bDeskStation);
					SendWatchData(bDeskStation,MDM_GM_GAME_FRAME,ASS_GM_WATCH_SET,pNetHead->bHandleCode);
				}

				//֪ͨ�仯
				OnWatchSetChange(bDeskStation,pWatchSet->dwUserID,pNetHead->bHandleCode==TRUE);
			}

			return true;
		}
    case ASS_GM_USE_KICK_PROP:      // PengJiLin, 2010-9-10, ʹ�����˿�
        {
            // Ч������ 
            if(uSize != sizeof(MSG_GR_RS_KickProp)) return false;
            MSG_GR_RS_KickProp* pKickProp = (MSG_GR_RS_KickProp* )pData;

            CGameUserInfo * pUserInfo=m_pDataManage->m_UserManage.GetOnLineUserInfo(uSocketID);
            if (pUserInfo==NULL) return false;

            try
            {
                DL_GR_I_UseKickProp DU_KickProp;
                memset(&DU_KickProp, 0, sizeof(DU_KickProp));
                DU_KickProp.dwUserID = pKickProp->dwUserID;
                DU_KickProp.iPropID = pKickProp->iPropID;

                m_pDataManage->m_SQLDataManage.PushLine(&DU_KickProp.DataBaseHead,sizeof(DU_KickProp),DTK_GR_USE_KICK_PROP,
                                                        pUserInfo->m_uSocketIndex, pUserInfo->m_dwHandleID);
            }
            catch(...)
            {TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
            }

            return true;
        }
    case ASS_GM_USE_ANTI_KICK_PROP: // PengJiLin, 2010-9-10, ʹ�÷��߿�
        {
            // Ч������ 
            if(uSize != sizeof(MSG_GR_RS_KickProp)) return false;
            MSG_GR_RS_KickProp* pKickProp = (MSG_GR_RS_KickProp* )pData;

            CGameUserInfo * pUserInfo=m_pDataManage->m_UserManage.GetOnLineUserInfo(uSocketID);
            if (pUserInfo==NULL) return false;

            try
            {
                DL_GR_I_UseKickProp DU_KickProp;
                memset(&DU_KickProp, 0, sizeof(DU_KickProp));
                DU_KickProp.dwUserID = pKickProp->dwUserID;
                DU_KickProp.iPropID = pKickProp->iPropID;

                m_pDataManage->m_SQLDataManage.PushLine(&DU_KickProp.DataBaseHead,sizeof(DU_KickProp),DTK_GR_USE_ANTI_KICK_PROP,
                                                        pUserInfo->m_uSocketIndex, pUserInfo->m_dwHandleID);
            }
            catch(...)
            {TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
            }

            return true;
        }
	}
	return false;
}

//��Ϸ���ݰ�������
bool CGameDesk::HandleNotifyMessage(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser)
{
	ASSERT(pNetHead->bMainID==MDM_GM_GAME_NOTIFY);
	switch (pNetHead->bAssistantID)
	{
	case ASS_GM_AGREE_GAME:		//�û�ͬ��
		{
			//Ч������
			if (bWatchUser==true)
				return false;
			return UserAgreeGame(bDeskStation);					
		}
	//case ASS_PROP:			//�ͻ�,ש����Ϣ
	//	{
	//		if ((bWatchUser)
	//			||(uSize!=sizeof(PropStruct))) 
	//			return FALSE;
	//		PropStruct * pProp = (PropStruct*)pData;
	//		UserUseOneItem(bDeskStation,pProp->recvDeskStation,pProp->iValue);
	//		return true;
	//	}
	}
	return false;
}
//��ʱ�������ݿ�
BOOL CGameDesk::UpdateUserDB(LONG dwUserID,int dwChangeMoney,int dwChangePoint)
{
	if(dwChangeMoney == 0 && dwChangePoint == 0)
		return TRUE;

	CGameUserInfo* UserInfo=m_pDataManage->m_UserManage.FindOnLineUser(dwUserID);

	if(UserInfo==NULL)
		UserInfo = m_pDataManage->m_UserManage.FindNetCutUser(dwUserID);

	if(UserInfo!=NULL)
	{
		//return TRUE;	
		UserInfo->m_UserData.dwPoint += dwChangePoint ;
		//����������
		if(UserInfo->m_UserData.i64Money + dwChangeMoney < 0)
		{
			dwChangeMoney = 0;
			UserInfo->m_UserData.i64Money = 0;
		}
		else
			UserInfo->m_UserData.i64Money += dwChangeMoney; 
	}
	//�������ݿ�
	try
	{
		DL_GR_Update_InstantMoney DT_InstantMoney;
		memset(&DT_InstantMoney,0,sizeof(DT_InstantMoney));
		DT_InstantMoney.dwChangeMoney = dwChangeMoney;
		DT_InstantMoney.dwChangePoint =dwChangePoint;
		DT_InstantMoney.dwUserID = dwUserID;
		DT_InstantMoney.bCutValue = 0;
		m_pDataManage->m_SQLDataManage.PushLine(&DT_InstantMoney.DataBaseHead,sizeof(DT_InstantMoney),DTK_GR_UPDATE_INSTANT_MONEY,0,0);
	}
	catch(...)
	{TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
	}
	//֪ͨ�ͻ���
	MSG_GR_R_InstantUpdate InstantUpdate;
	InstantUpdate.dwUserID = dwUserID;
	InstantUpdate.dwMoney = dwChangeMoney;
	InstantUpdate.dwPoint = dwChangePoint;
	m_pDataManage->m_TCPSocket.SendDataBatch(&InstantUpdate,sizeof(InstantUpdate),MDM_GR_ROOM,ASS_GR_INSTANT_UPDATE,0);
	return true;
}

//����
bool CGameDesk::UserUseProp(BYTE bsendDeskStation,BYTE brecvDeskStation,_TAG_PROP_MOIVE_USE * propMoive)
{
	if(!m_pUserInfo[bsendDeskStation])
		return true;

	if(!m_pUserInfo[brecvDeskStation])
		return true;
	
	for(int i = 0; i < m_bMaxPeople; i ++)
		SendGameData(i,propMoive,sizeof(_TAG_PROP_MOIVE_USE),MDM_GM_GAME_NOTIFY,ASS_PROP,0);
	SendWatchData(m_bMaxPeople,propMoive,sizeof(_TAG_PROP_MOIVE_USE),MDM_GM_GAME_NOTIFY,ASS_PROP,0);
	return true;
}

//rongqiufen
//�޸�ָ���û��ĵ�����Ϣ
int CGameDesk::PropChange(const TPropChange& propChange)
{
	TpropChange_I _p;
	_p.info = propChange;

	m_pDataManage->m_SQLDataManage.PushLine(&_p.DataBaseHead, sizeof(TpropChange_I), DTK_GR_PROP_CHANGE, 0, 0);

	return 0;
}

//���½�������(��Ϸ->ƽ̨)
/// @param iAIHaveWinMoney ������ӮǮ��
/// @return void
void CGameDesk::UpDataRoomPond(__int64 iAIHaveWinMoney)
{
	m_pDataManage->SendRoomPondUpData(iAIHaveWinMoney);
	return;
}

//��ȡ ��ȡ�����ļ�ʱ���õĹؼ���
void CGameDesk::GetGRM_SET_KEY(TCHAR key[])
{
	if (key == NULL)
	{
		return;
	}

	CopyMemory(m_GRM_Key,key,sizeof(m_GRM_Key));
	return;
}

//��ȡ ��ȡ�����ļ�ʱ���õĹؼ���(ʤ��)
void CGameDesk::GetGRM_SET_KEY_Win(TCHAR key[])
{
	if (key == NULL)
	{
		return;
	}

	CopyMemory(m_GRM_Key_win,key,sizeof(m_GRM_Key_win));
	return;
}

//��ȡ ��ȡ�����ļ�ʱ���õĹؼ���(����)
void CGameDesk::GetGRM_SET_KEY_Los(TCHAR key[])
{
	if (key == NULL)
	{
		return;
	}

	CopyMemory(m_GRM_Key_los,key,sizeof(m_GRM_Key_los));
	return;
}