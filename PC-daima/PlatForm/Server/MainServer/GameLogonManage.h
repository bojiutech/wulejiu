#pragma once

#include "AfxTempl.h"
#include "MainManageForZ.h"
#include "GameLogonDT.h"
#include "GameListCtrl.h"
//�ϴ�ͷ��
#include "UserCustomLogo.h"
//IM��
#include "IMService.h"
//������
#include "BankService4Z.h"

///{{ Added by zxd 20100722  GM����������ͷ�ļ�
#include "InterfaceForGM.h"
/// Added by zxd 20100722}}
#include "DistriManager.h" // �ֲ�ʽ����
#include "UserManager.h"
///{{ Added by JianGuankun 2012.5.16  �ֻ����Žӿ�
#include "SmsIf.h"
/// Added by JianGuankun 2012.5.16}}
#include "gamemanagemodule.h"
#include "HNFilter.h"
#include <map>
using namespace std;


//�궨�� 
#define TID_UPDATE_LIST							50					//�����б� ID
#define LS_TIME_OUT								6000L				//�б�ʱ��



// ----------------------------------------------------------------------------
// PengJiLin, 2010-6-3, ����ʹ�õ�����DLL�ļ���������(Ÿ��)
// ----------------------------------------------------------------------------

// �ص���Ϣ�ṹ��������
typedef struct msg_head
{
    unsigned long serial_no;        /// ��Ϣ��ˮ��
    int opr_ret;                    /// �������
    unsigned char* data;            /// ��Ϣ��
} MSG_CONTEXT_HEAD, *LPMSG_CONTEXT_HEAD;


typedef struct user_info
{
    char chUserName[50];
    char chMD5PSW[50];

    int iUserIndex;
}USER_INFO, *LPUSER_INFO;


// ��Ϣ����
#define MSG_TYPE_LOGON              1       // ��¼��Ϣ
#define     MSG_OP_LOGON_SUCCESS    0       // �û���¼�ɹ�
#define     MSG_OP_LOGON_INFO_ERROR 66537   // �û������������
#define     MSG_OP_LOGON_USING      66539   // �û��ѵ�¼
#define     MSG_OP_LOGON_NO_USER    66542   // �û�������
#define     MSG_OP_LOGON_FORBID     66547   // �û����ڽ���״̬
#define     MSG_OP_LOGON_OVERDATE   66551   // �û��ѹ���

// ��Ϣ�ص������ӿڶ��壺
typedef void (__stdcall *MSG_CALL)(int msg_type, LPMSG_CONTEXT_HEAD msg_context_ptr);

// ����ָ��˵��

// ��֤�ӿڶ�̬���license
// bCallDesc�����÷���ʶ���������£�
#define KFGAME 66
typedef void (__stdcall *SET_LICENCE_FUNC_PTR)(const char* licence, unsigned char bCallDesc);

// ��ʼ�����ӽӿ�
typedef int (__stdcall *INIT_FUNC_PTR)(MSG_CALL msg_func, int thread_num, int conn_num);

// �ͷŶ�̬��ӿ�
typedef bool (__stdcall *RELEASE_FUNC_PTR)();

// �û��Ϸ�����֤�ӿ�
typedef void (__stdcall *LOGIN_FUNC_PTR)(const char* szUser, const char* szPwd, int iSerialNo);

// ��Ϣ�ص�����
void __stdcall MsgHandleCallback(int msg_type, LPMSG_CONTEXT_HEAD msg_context_ptr);


// Ÿ�� DLL �ļ�����
#define DLL_FILE_NAME_OPETV     "OpetvInterfaceDll.dll"//"ZylDll.dll"


/******************************************************************************************************/

//���ݿ⴦�����
class CServiceDataBaseHandle : public CDataBaseHandle
{
public:
	CServiceDataBaseHandle(void){};
	//��������
private:
	//���ݿ⴦��ӿ�
	virtual UINT HandleDataBase(DataBaseLineHead * pSourceData);


	//��������
private:
	//Ч���ַ�
	bool CheckChar(TCHAR * szChar, bool bStrCheck);

	//������
private:
	/// {{Added by zxd 20100729����GM����
	///GM�������Ϣ��ȡ�Ѿ�����������������ID���ǳƶ�Ӧ��ϵ
	UINT OnGMGetOperatedUser(DataBaseLineHead * pSourceData);
	///GM��ȡ��������
	UINT OnGMGetAwardType(DataBaseLineHead * pSourceData);
	///GM��ȡ����ID�����ƶ�Ӧ��ϵ
	UINT OnGMGetPropInfo(DataBaseLineHead * pSourceData);
	///GM����ҽ��н��Ͳ���
	UINT OnGMOperateToUser(DataBaseLineHead * pSourceData);
	//GM��½����
	UINT OnGMLogon(DataBaseLineHead * pSourceData, UINT uLogonType);
	/// Added by zxd 20100729����GM����}}

	//���ƶ��˿���ע��
	UINT OnOneKeyRegister(DataBaseLineHead * pSourceData, UINT uLogonType);
	//�û����ƶ���֧��
	UINT OnUserPay(DataBaseLineHead* pSourceData);
	//ͨ���ƶ���֧����RMB����ȡ��ҽ���
	//1: ��ѯ  2:��ȡ
	UINT OnGetMoneyByPay(DataBaseLineHead* pSourceData, int type);
	//������½����
	UINT OnPlaceLogon(DataBaseLineHead * pSourceData, UINT uLogonType);
	//������Ϸ�б�
	UINT OnUpdateGameList(DataBaseLineHead * pSourceData);
	//������ݿ�����
	UINT OnCheckDataConnect(DataBaseLineHead * pSourceData);
	//
	UINT OnGetRoomListPeoCount(DataBaseLineHead * pSourceData);
	UINT OnMailListGet(DataBaseLineHead * pSourceData);
	UINT OnMailUpdate(DataBaseLineHead * pSourceData);
	
	UINT OnGetLogonPeopCount(DataBaseLineHead * pSourceData);
	//���ͷ��ID
	void OnUpdateUserLogoID(DataBaseLineHead *pSourceData);
	//���ͷ��ID md5ֵ
	void OnRequestUserLogoMD5(DataBaseLineHead *pSourceData);
	//ȡ��������
	void OnDBIMGetUserCount(DataBaseLineHead * pSourceData);
	//�����������û����߱�־��0
	void OnClearOnlineFlag();
	//�û����߲���
	void OnUserOffline(DataBaseLineHead * pSourceData);
	//���ú�����
	void OnIMSetUser(DataBaseLineHead * pSourceData);
	//��ȡ�û���������ID
	void OnGetContestRoomID(DataBaseLineHead * pSourceData);
	void OnGetTimingMatchBeginTime(DataBaseLineHead *pSourceData);
	//ȡ�õ�����Ϣ
	void OnPropGetList(DataBaseLineHead * pSourceDat);
	void OnPropBuy(DataBaseLineHead * pSourceData);
    void OnPropBuyNew(DataBaseLineHead * pSourceData);  // PengJiLin, 2010-10-13, �̵���ߵļ�ʱ������
	void OnPropGive(DataBaseLineHead *pSourceData);
	void OnPropBigBrd(DataBaseLineHead *pSourceData);
	void OnPropBigBrd_BuyAndUse(DataBaseLineHead *pSourceData);
	void OnUserLockAccount(DataBaseLineHead * pSourceData);	//�������� zxj 2009-11-13
	void OnUserBindMobile(DataBaseLineHead * pSourceData);	//���ֻ�
	void OnPropBuyVIP(DataBaseLineHead * pSourceData);  //���߽��湺��VIP  add by wyl  11-5-21
	void OnSetUserLogo(DataBaseLineHead * pSourceData);//�����û�ͷ��
	//��ͼ�������뷿��  add by lxl  2010-10-08
	void OnCheckRoomPasswd(DataBaseLineHead *pSourceData);

	/// ���汾zxd add for check version20100312
	UINT OnCheckVersion(DataBaseLineHead * pSourceData);
	//�޸�дZ��¼��¼��ʱ����ȷ�����翨��ʱ�򣬲����ڵ����û���¼���� 2009-4-30 zxj
	UINT OnWriteUserLogonRecord(DataBaseLineHead * pSourceData);
	
	//��ȡ�����б�ؼ�   add  wyl
	UINT OnGetSellGameList(DataBaseLineHead * pSourceData);
	//����Ƿ�����Ϣ�б�
	UINT OnCheckSellGameList(DataBaseLineHead * pSourceData);

	//�޸��û���������
	UINT OnUpdateUserInfo(DataBaseLineHead* pSourceData,UINT nType);

	//�޸�����
	UINT OnUpdateUserPwd(DataBaseLineHead* pSourceData);

	UINT OnReceiveMoney(DataBaseLineHead * pSourceData);

	UINT OnCharmExchangeList(DataBaseLineHead * pSourceData);

	UINT OnCharmExchange(DataBaseLineHead * pSourceData);

	UINT OnSetFriendType(DataBaseLineHead * pSourceData);

	//��ѯ��ҵ�ID���ǳ�
	UINT OnQueryUserNickNameID(DataBaseLineHead* pSourceData);

	//�������д���///////////////////

	//������
	UINT OnBankOpen(DataBaseLineHead* pSourceData);

	//��ѯǮ��
	UINT OnBankGetGameWallet(DataBaseLineHead* pSourceData);

	//���д�ȡ
	UINT OnBankCheck(DataBaseLineHead* pSourceData);

	//��ȡ���ߴ洢����
	UINT OnBankTransferRebate(DataBaseLineHead* pSourceData);
	//����ת�˷�������
	UINT OnUpdateRebate(DataBaseLineHead * pSourceData);
	//������ҷ�������
	UINT OnUpdateUserRebate(DataBaseLineHead * pSourceData);
	//����ת��(sdp2014-05-06-���ӷ�������)
	UINT OnBankTransfer(DataBaseLineHead* pSourceData);

	//��ѯ����ת�˼�¼
	UINT OnBankTransRecord(DataBaseLineHead* pSourceData);

	//�浥ҵ��
	UINT OnBankDeposit(DataBaseLineHead* pSourceData);

	//��ѯ�浥
	UINT OnBankQueryDeposits(DataBaseLineHead* pSourceData);

	//�޸���������
	UINT OnBankChangePassword(DataBaseLineHead* pSourceData);

	//��ȡ����״��
	UINT OnBankGetFinanceInfo(DataBaseLineHead* pSourceData);

	//��ȡ�����¼����Ϸ
	UINT OnLastLoginGame(DataBaseLineHead* pSourceData);
	
	///zht 2012-3-6
	HANDLE sqlSPSetNameEx(HANDLE & hHandle,LPCTSTR szSPName,bool bReturnValue = false);


	//��ѯ���а�
	UINT OnPaiHangBang(DataBaseLineHead* pSourceData);
	//ǩ��
	UINT OnSignInDo(DataBaseLineHead* pSourceData);
	UINT OnSignInCheck(DataBaseLineHead* pSourceData);
	//���߽���  
	UINT OnLineAwardCheck(DataBaseLineHead* pSourceData); 
	UINT OnLineAwardDo(DataBaseLineHead* pSourceData); 
	UINT OnBuyDesk(DataBaseLineHead* pSourceData); 
	UINT OnEnterVIPDesk(DataBaseLineHead* pSourceData); 
	UINT OnVIPDeskConfig(DataBaseLineHead* pSourceData); 
	UINT OnMoneyToJewel(DataBaseLineHead* pSourceData);
	UINT OnProcessAgent(DataBaseLineHead* pSourceData);
	UINT OnNetCutInfo(DataBaseLineHead* pSourceData); 
};

/******************************************************************************************************/

//��Ϸ��½������
class CGameLogonManage : public CBaseMainManageForZ
///{{ ʵ������GM�����ߵĹ��ܽӿ�
	, public IGMFunction
	, public IDistriManagerNetBase
/// }}
{
	/// {{ ����GM������
private:
	CGMMessageBase					*m_pGmMessageBase;				///< ����GM��Ϣ�������
	IDistriManagerBase				*m_pDistriManager;
public:
	/// ʵ�ִ�IGMFunction�̳й����Ľӿ�
	/// ��ͻ��˷�������
	virtual int SendDataByUser(UINT uUserID, BYTE bMainID, BYTE bAssistantID, UINT bHandleCode, DWORD dwHandleID)
	{
		int nSockIndex = GetIndexByID(uUserID);
		if(nSockIndex >= 0)
		{
			return SendData(nSockIndex, bMainID, bAssistantID, bHandleCode, dwHandleID);
		}
		else
		{
			return m_pDistriManager->SendData(uUserID, bMainID, bAssistantID, bHandleCode, dwHandleID);
		}
	}
	virtual int SendDataByUser(UINT uUserID, void * pData, UINT uBufLen, BYTE bMainID, BYTE bAssistantID, UINT bHandleCode, DWORD dwHandleID)
	{
		int nSockIndex = GetIndexByID(uUserID);
		if(nSockIndex >= 0)
		{
			return SendData(nSockIndex, pData, uBufLen, bMainID, bAssistantID, bHandleCode, dwHandleID);
		}
		else
		{
			return m_pDistriManager->SendData(uUserID, pData, uBufLen, bMainID, bAssistantID, bHandleCode, dwHandleID);
		}
	}
	virtual int SendData(UINT uIndex, BYTE bMainID, BYTE bAssistantID, BYTE bHandleCode, DWORD dwHandleID)
	{
		return m_TCPSocket.SendData(uIndex, bMainID, bAssistantID, bHandleCode, dwHandleID);
	}
	virtual int SendData(UINT uIndex, void * pData, UINT uBufLen, BYTE bMainID, BYTE bAssistantID, BYTE bHandleCode, DWORD dwHandleID)
	{
		return m_TCPSocket.SendData(uIndex, pData, uBufLen, bMainID, bAssistantID, bHandleCode, dwHandleID);
	}
	/// �����ݿ�ģ�鷢�ͷ�������
	virtual bool PushDataLine(DataBaseLineHead * pData, UINT uSize, UINT uHandleKind, UINT uIndex,DWORD dwHandleID)
	{
		return m_SQLDataManage.PushLine(pData, uSize, uHandleKind, uIndex, dwHandleID);
	}
	/// �ж�ĳ�����Ƿ񻹴���
	virtual bool IsConnectID(UINT uIndex, DWORD dwHandleID)
	{
		return m_TCPSocket.IsConnectID(uIndex, dwHandleID);
	};
	/// ��ͻ��˷��͹㲥����
	virtual int SendBatchData(void * pData, UINT uBufLen, BYTE bMainID, BYTE bAssistantID, BYTE bHandleCode)
	{
		return m_TCPSocket.SendDataBatch(pData, uBufLen, bMainID, bAssistantID, bHandleCode);
	}
	/// �����û�ID��ȡSocket���
	virtual int GetIndexByID(int iUserID)
	{
		for(int i=0; i<m_UserList.GetCount(); i++)
		{
			LPUSER p = (LPUSER)m_UserList.GetAt(i);
			if(p == NULL)
				continue;
			if(p->UserID==iUserID)
			{
				return p->iSocketIndex;
			}
		}
		return -1;
	}

	virtual LPUSER GetUserByID(int iUserID)
	{
		for(int i=0; i<m_UserList.GetCount(); i++)
		{
			LPUSER p = (LPUSER)m_UserList.GetAt(i);
			if(p == NULL)
				continue;
			if(p->UserID==iUserID)
			{
				return p;
			}
		}
		return NULL;
	}


	/// �����û�Socket��Ż�ȡ�û���Ϣ
	virtual LPUSER GetUserBySockIdx(UINT uSockIdx)
	{
		if (m_UserList.GetCount() == 0)
		{
			return NULL;
		}

		for(int i = 0; i < m_UserList.GetCount(); ++i)
		{
			LPUSER p = (LPUSER)m_UserList.GetAt(i);
			if(!p)
			{
				return NULL;
			}
			if(uSockIdx == p->iSocketIndex)
			{
				return p;
			}
		}

		return NULL;
	}

	///����
	/// �ж�ĳ����Ƿ��Ѿ���¼
	virtual bool IsUserAlreadyLogon(DWORD dwUserID)
	{
		for(int i=0; i<m_UserList.GetCount(); i++)
		{
			LPUSER p = (LPUSER)m_UserList.GetAt(i);
			if(p == NULL)
				continue;
			if(p->UserID==dwUserID)
			{
				return true;
			}
		}
		return false;
	}

	///����			2012.11.22
	///	�ж�ĳ����Ƿ��Ѿ���¼��ͨ���û�����
	virtual bool IsUserAlreadyLogonByName(char * const szUserName)
	{
		if (szUserName == NULL)
		{
			return false;
		}
		for (int i=0; i<m_UserList.GetCount(); i++)
		{
			LPUSER p = (LPUSER)m_UserList.GetAt(i);
			if(p == NULL)
				continue;
			if(strcmp(p->UserName, szUserName) == 0)
			{
				return true;
			}
		}
		return false;
	}
	/// �ж�ĳ����Ƿ���GM
	virtual bool IsGameMaster(UINT uIndex)
	{
		for(int i=0; i<m_UserList.GetCount(); i++)
		{
			LPUSER p = (LPUSER)m_UserList.GetAt(i);
			if(p == NULL)
				continue;
			if(p->iSocketIndex == (int)uIndex)
			{
				return p->bIsGameManager;
			}
		}
		return false;
	}
	/// �����ҵ�¼��¼
	virtual bool AddLogonUser(DWORD dwUserID, UINT uIndex, bool bIsGM = false)
	{
		LPUSER p = (LPUSER)new USERS();
		p->iSocketIndex = uIndex;
		p->UserID = dwUserID;
		p->bIsGameManager = bIsGM;
		m_UserList.Add(p);

		MSG_ZDistriInfo info;
		info.dwUserID = dwUserID;
		info.nZID = m_ID;
		m_pDistriManager->SendNormalData(&info, sizeof(info), MDM_ZD_PACKAGE, ASS_ZD_LOGON, HDC_ZD_CONNECT);
		
		return true;
	}
	/// Added by zxd 20100722}}

private:
	void SendRoomListPeoCount();
	//��������
public:
	UINT m_nPort;																//��½�������˿�
	UINT m_uMaxPeople;															//֧���������	
	CString m_strSmsContent;													//��Ѷ��ʽ
	CServerGameListManage						m_GameList;						//��Ϸ�б�
	CPtrArray									m_UserList;						//�û��б�
	///////////////////////////
	////Kylin 20090316 ��ӷ�ֹ�˻�ͬʱ��½
	int m_ID;//ZID
	///////////////////////////

    // PengJiLin, 2010-6-3, �Ƿ��ǵ�����������TRUE = �ǡ�(Ÿ��)
    // ע�⣺����ı�����ʾ��һ�����������ڵ���������״̬����һֱ���ǡ�
    BOOL m_bRunBySoftware;

private:	
	CUserCustomLogo			*m_userCustomLogo;		//ͷ���ϴ�������
	CIMService				*m_imService;			//IM������
	CBankService4Z          *m_pBankService;		//���з�����ҵ��
	ISms					*m_pISms;				//����Ϣ����ӿ� Added by JianGuankun 2012.5.16

	// MServer �� GServerͨ��
	CGameManageModule	*m_pGameManageModule;	
public:
		CString				m_CustomFacePath;		//�û�Ŀ¼
		CString				m_CustomFacePathUpload;	//�û���Ŀ¼
		bool				m_bCustomFaceNeedCheck;	//ͷ���Ƿ���Ҫ���
		BOOL				m_bSendSellGameList;	//2011-5-16, �Ƿ���Ҫ����������Ϸ�б�


		CTalkMessageFilter  m_TalkFilter; //��Ϣ����ϵͳ
		HNFilter            m_HNFilter;

		map<int, TMailItem> m_Mails;

		TMSG_GP_RebateUpDate m_Rebate;//ת�˷���
	//��������
public:
	//���캯��
	CGameLogonManage(void);
	CGameLogonManage(CGameLogonManage&);
	CGameLogonManage & operator = (CGameLogonManage &);
	//��������
	virtual ~CGameLogonManage(void);
	//��ȡ��Ϸ�б�
	const CServerGameListManage * GetGameList() { return &m_GameList; };

	//���ܺ���
public:
	//���ݹ���ģ������
	virtual bool OnStart();
	//���ݹ���ģ��ر�
	virtual bool OnStop();

	virtual bool Init(ManageInfoStruct * pInitData, IDataBaseHandleService * pDataHandleService);

	virtual bool UnInit();

	//������չ�ӿں���
private:
	//��ȡ��Ϣ����
	virtual bool PreInitParameter(ManageInfoStruct * pInitData, KernelInfoStruct * pKernelData);
	//SOCKET ���ݶ�ȡ
	virtual bool OnSocketRead(NetMessageHead * pNetHead, void * pData, UINT uSize, ULONG uAccessIP, UINT uIndex, DWORD dwHandleID);
	//SOCKET �ر�
	virtual bool OnSocketClose(ULONG uAccessIP, UINT uSocketIndex, long int lConnectTime);
	//���ݿ⴦����
	virtual bool OnDataBaseResult(DataBaseResultLine * pResultData);
	//��ʱ����Ϣ
	virtual bool OnTimerMessage(UINT uTimerID);
	//������Ϣ
	void OnPropMessage(NetMessageHead * pNetHead, void * pData, UINT uSize, ULONG uAccessIP, UINT uIndex, DWORD dwHandleID);

	/// {{Added by zxd 20100805 ��ȡ����GM�б�
	void OnPlayer2Gm(NetMessageHead * pNetHead, void * pData, UINT uSize, ULONG uAccessIP, UINT uIndex, DWORD dwHandleID);
	/// Added by zxd 20100805 ��ȡ����GM�б�}}
	CGameManageModule* GetpGameManageModule() { return m_pGameManageModule; }

	void GetINIFile();

	HANDLE sqlSPSetNameEx(HANDLE & hHandle,LPCTSTR szSPName,bool bReturnValue=false);



///////////////////////////////
	/// �����û�ID��ȡSocket���
	/// ��ͻ��˷��͹㲥����

	/// ��ͻ��˷��͹㲥����
	virtual int SendBatchDataSelf(void * pData, UINT uBufLen, BYTE bMainID, BYTE bAssistantID, UINT bHandleCode)
	{
		return m_TCPSocket.SendDataBatch(pData, uBufLen, bMainID, bAssistantID, bHandleCode);
	}

	virtual int KickUserSocket(DWORD dwUserID)
	{
		return 0;
	}

	virtual int GetZid()
	{
		return m_ID;
	}

	virtual int GetServerPort()
	{
		return m_nPort;
	}
	// B�������޷���Z�������б����ҵ����ʱ���ᷴ����Ϣ���������Z����������������ݴ���
	virtual int SendDataFail(UINT uUserID, void * pData, UINT uBufLen, BYTE bMainID, BYTE bAssistantID, UINT bHandleCode, DWORD dwHandleID);

public:
	bool OnHandleGMessage(NetMessageHead *pNetHead, void *pData, UINT uSize, ULONG uAccessIP, UINT uIndex);
///////////////////////////////
};

/******************************************************************************************************/

//��Ϸ��½ģ��
class CGameLogonModule : public IModuleManageService
{
	//�������� 
public:
	CGameLogonManage						m_LogonManage;					//��½���ݹ���
	CServiceDataBaseHandle					m_DataBaseHandle;				//���ݿ����ݴ���ģ��

	//��������
public:
	//���캯��
	CGameLogonModule(void);
	//��������
	virtual ~CGameLogonModule(void);

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
