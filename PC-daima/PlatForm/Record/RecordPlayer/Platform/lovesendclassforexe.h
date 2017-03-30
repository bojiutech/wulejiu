////////////////////////////////////////////////////////////////////////////////
// CLoveSendClassForEXE

// ˵����
// ����ƽ̨����CLoveSendClass��ICO��ʽ�Ŀͻ����е���Ϊ
// EXE�ͻ��˳�����IPC��ʽ�뱾�������Ϣ����
// �ͻ���ƽ̨���������ͨѶ�ɱ������
// �����ߣ�		���ܶ�
// �������ڣ�	2009-02-23

#pragma once

#include "IPC\common.h"
#include "IPC\Sink.h"
#include "IPC\ChannelService.h"

#include <list>

#define TIMER_HEART_BEAT		100		// ����ά��IPC�����Ķ�ʱ��
const int HEART_BEAT_SECOND		= 3;	// �������
const int HEART_BEAT_DELAY		= 1;	// ���������ʱ

// �û��������
struct CM_UserState_Send_Times_Money_For_Exe
{
	int dwUserID;
    int                                 dwGetMoney;             // �����Ľ����
    int                                 dwMoneyOnTimes;         // ���ö���ʱ�����͵Ľ��
    int                                 dwMoneyOnCounts;        // ���ö��پ����͵Ľ��
    int                                 dwTimesNeed;            // ��һ�β����ʱ��
    int                                 dwCountsNeed;           // ��һ�β���پ�
};
//�û�״̬�ı�
struct CM_UserState_Change_ForExe
{
	BYTE								bActionCode;			//��������
	BYTE								bDeskStation;			//����λ��
	UserItemStruct						uisUserItem;			//�û�ָ��
};

struct GameInfoStructInExe
{
	GameInfoStructInExe()
	{
		bDeskOnwer = true;							//�Ƿ�̨��
		bGameStation = 0;						//��Ϸ״̬
		memset(&uisMeUserInfo, 0, sizeof(UserItemStruct));			//�����Ϣ
		_tcscpy(uisMeUserInfo.GameUserInfo.nickName, TEXT("����"));
		_tcscpy(uisMeUserInfo.GameUserInfo.szName, TEXT("������"));
		uisMeUserInfo.GameUserInfo.dwUserID = 100001;
		uisMeUserInfo.GameUserInfo.bDeskNO = 3;
		uisMeUserInfo.GameUserInfo.bDeskStation = 1;

		dwGamePower = 0;						//�û�Ȩ��
		dwMasterPower = 0;						//����Ȩ��
		dwRoomRule = 0;							//���ù���
		pOrderName = NULL;						//�ȼ�����

		//���ò���
		bEnableSound = true;						//��������
		bEnableWatch = false;						//�����Թ�
		bShowUserInfo = true;						//��ʾ����
		bEnableBackSound = true;					//��������

		//��������
		_tcscpy(szProcessName, TEXT("10901800.exe"));					//��������
		uDeskPeople = 180;						//��Ϸ����
		uRoomID = 2;							//�����ʾ
		dwGameMSVer = 2;						//���汾��
		dwGameLSVer = 0;						//���汾��
		uComType = 1;							//��Ϸ����
		uNameID = 10901800;							//���ֱ�ʾ
		//uNameID = 10003300;							//���ֱ�ʾ
		_tcscpy(szGameName, TEXT("������"));		//��Ϸ����
		uLessPoint = 0;							//���پ���ֵ
		memset(szGameRoomName, 0, sizeof(szGameRoomName));

		iBasePoint = 1;
		iLowCount = 0;
		i64Chip = 0;
		i64TimeStart = 0;
		i64TimeEnd = 0;
		i64LowChip = 0;
	}
	//IFindUserInterface				* pIFindUser;						//���ҽӿ�
	//������Ϣ
	bool							bDeskOnwer;							//�Ƿ�̨��
	BYTE							bGameStation;						//��Ϸ״̬
	UserItemStruct					uisMeUserInfo;						//�����Ϣ
	long int						dwGamePower;						//�û�Ȩ��
	long int						dwMasterPower;						//����Ȩ��
	long int						dwRoomRule;							//���ù���
	void							*pOrderName;						//�ȼ�����

	//���ò���
	bool							bEnableSound;						//��������
	bool							bEnableWatch;						//�����Թ�
	bool							bShowUserInfo;						//��ʾ����
	bool							bEnableBackSound;					//��������

	//��������
	TCHAR							szProcessName[31];					//��������
	UINT							uDeskPeople;						//��Ϸ����
	UINT							uRoomID;							//�����ʾ
	DWORD							dwGameMSVer;						//���汾��
	DWORD							dwGameLSVer;						//���汾��
	UINT							uComType;							//��Ϸ����
	UINT							uNameID;							//���ֱ�ʾ
	TCHAR							szGameName[61];						//��Ϸ����
	UINT							uLessPoint;							//���پ���ֵ

	bool                            bIsInRecord;                        //�Ƿ���¼���� yjj  090223


	int								iBasePoint;
	//����ר��
	int									iLowCount;
	__int64								i64Chip;
	__int64								i64TimeStart;
	__int64								i64TimeEnd;
	__int64								i64LowChip;

	char						szGameRoomName[61];					//��Ϸ��������
};


class CLoveSendClassForEXE : public CDialog, public IFrameInterface, public IChannelMessageSink
{
	struct MessageToSendStruct
	{
		WORD ipcMain;
		WORD ipcSub;
		BYTE *pBuffer;
		WORD wSize;
	};

	//CRITICAL_SECTION m_csForIPCMessage;

	DECLARE_DYNAMIC(CLoveSendClassForEXE)
public:
	CLoveSendClassForEXE(void);
	virtual ~CLoveSendClassForEXE(void);

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void OnCancel();
	//------------------------------------------------------------------------\\
								���ܺ���
public:
	//��ȡ״̬����
	BYTE GetStationParameter() { return m_pGameInfo->bGameStation; };
	//��ȡ�Լ���Ϣ
	UserInfoStruct * GetMeUserInfo() { return &m_pGameInfo->pMeUserInfo->GameUserInfo; };

	//����������Ϣ����
	int SendGameData(BYTE bMainID, BYTE bAssistantID, BYTE bHandleCode);
	//����������Ϣ����
	int SendGameData(void * pData, UINT uBufLen, BYTE bMainID, BYTE bAssistantID, BYTE bHandleCode);
	//��ܺ���
	virtual bool OnFrameMessage(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize, CTCPClientSocket * pClientSocket);
	////��Ϣ����
	//virtual bool OnSystemMessage(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize, CTCPClientSocket * pClientSocket);
	////�������Ϣ������
	//virtual bool HandlePointMessage(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize, CTCPClientSocket * pClientSocket);
	//������Ϣ
	virtual bool OnPropMessage(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize, CTCPClientSocket * pClientSocket);
	//ʹ�õ���
	virtual bool OnUsePropResult(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize, CTCPClientSocket * pClientSocket);
	//����״̬����
	void SetStationParameter(BYTE bGameStation) { m_pGameInfo->bGameStation=bGameStation; };

	//------------------------------------------------------------------------//

	//------------------------------------------------------------------------\\
					��IFrameInterface�ӿڼ̳еĴ��麯��
public:
	//��ʼ�����״�����ʹ�ã�
	virtual bool InitFrame(GameInfoStruct * pGameInfo, CWnd * pGameRoom);
	//��������
	virtual bool AFCCreateFrame();
	//�رմ���
	virtual bool AFCCloseFrame();
	//��ʾ����
	virtual void AFCShowFrame(int nShow);
	//����windows��Ϣ
	virtual LRESULT SendWindowMessage(UINT msg,WPARAM wParam,LPARAM lParam);
	//ɾ������
	virtual void DeleteFrame();
	//������Ϣ 
	virtual UINT OnControlMessage(UINT uControlCode, void * pControlData, UINT uDataSize);
	//�����ȡ��Ϣ
	virtual bool OnSocketReadEvent(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize, CTCPClientSocket * pClientSocket);
	//������Ϸ������Ϣ
	virtual void ShowMsgInGame(TCHAR * szMsg, BYTE bNewOrSys=0,UINT uSize=0, TCHAR * szFontName=NULL,TCHAR *Title=NULL);
	//��������Ϣ
	virtual void ShowMsgDudu(TCHAR * szSendName, TCHAR * szTargetName,TCHAR * szCharString, COLORREF crTextColor, bool bShowTime, UINT uSize=0, TCHAR * szFontName=NULL,int iDuduType=0);
	//����������Ϣ
	virtual void SendShortMessage(MSG_GR_RS_NormalTalk *pShortMessage);
	//¼��ϵͳ�������á�
	virtual void SetRecordView() {};
	virtual bool GetGameIsStarting(){return true;}
	//------------------------------------------------------------------------//


	//========================================================================\\
									IPC֧��
	//��ʼ��IPC
	bool InitIPC();
	//����IPC
	bool DestroyIPC();
	//�ص��ӿ�
	virtual bool __cdecl OnChannelMessage(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend);
	//IPC�ں�����
	bool OnIPCKernel(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend);
	//����ָ��
	bool OnIPCSocket(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend);
	//EXE�ͻ��������û��嵥
	bool OnIPCUserInfo(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend);
	//�û�ʹ�õ���
	bool OnIPCUseProp(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend);
	// ����IPC��Ϣ
	bool SendIPCMessage(void * pIPCBuffer = NULL, WORD wDataSize = 0);
public:
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	//========================================================================//


protected:
	int		StartGameClient(void);	// ����EXE����
	int		StopGameClient(void);	// ֹͣEXE����

private:
	void TranslateGameInfo(void);		// ��m_pGameInfo������ת�Ƶ�m_GameInfo�У��Ա㷢��EXE����
	void FlushMessage(void);			// ����Ϣ������������ȷ���ȥ
	void SendGlbData(void);				// ����Glb()�������
	void SendBringToTopData(void);		// ֪ͨ��Ϸ���ڣ���������ǰ��
	void SendPlayerData(UserItemStruct *pUserInfo);			// ����ͬ���������
	void ExeClientShutDown(void);		// �ͻ��������ر�

private:
	//========================================================================\\
									IPC֧��
	tagShareMemory*					m_pShareMemory;
	char							m_szShareName[64];
	HANDLE							m_hShareMemory;
	HWND							m_hWndChannel;
	PROCESS_INFORMATION				m_GameProcessInfo;				//������Ϣ
	CIPCRecvCopyData				m_IPCRecvCopyData;
	DWORD							m_dwIPCHeartBeatTick;				// ������¼������Ϣ����ʱ���Tick��
	//========================================================================//

	//========================================================================\\
	//��Ϸ����
private:
	GameInfoStruct						* m_pGameInfo;					//��Ϸ��Ϣָ��
	GameInfoStructInExe					m_GameInfo;						//������EXE�ͻ���ͨѶ�����ݽṹ�����ݴ�m_pGameInfo����
	CWnd								* m_pGameRoom;					//���䴰��
	TCHAR								m_szGameRoomName[61];			//��������

	//UserInfoStruct						*m_CurpUserInfoClicked;		//��ǰ������û�ָ��
	//��Ϸ����
protected:
	bool								m_bWatchMode;					//�Թ�ģʽ
	bool								m_bWatchOther;					//�����Թ�
	BYTE								m_bWaitTime;					//�ȴ�ʱ��
	CPtrArray							m_WatchPtrArray;				//�Թ�ָ������
	//========================================================================//
protected:
	std::list<MessageToSendStruct>		m_lstIPCMessage;				// �����ݴ�IPC��Ϣ�Ķ���
	bool								m_bIsGameValid;					// ��Ϸ�����Ƿ�������
};
