#pragma once
#include "AfxTempl.h"
#include "GameSelect.h"
#include "../tinyxml2/tinyxml2.h"

//ϵͳ״̬
#define	STS_NO_LOGON					0x00000001						//û�е�½
#define	STS_LOGON_ING					0x00000002						//��½ϵͳ��
#define	STS_LOGON_FINISH				0x00000004						//��½ϵͳ���
#define	STS_SYSTEM_LOCK					0x00000008						//ϵͳ����

//��������
#define SERVER_ACCESS_DATA				"TEXT(AFCService")//TEXT("ServerAccess")			//���ݿ�����
#define ROOM_EXE_NAME					TEXT("RoomLoader.EXE")			//����װ������

/********************************************************************************************/

//�����Ϣ�ṹ
struct SC_ServiceInfoStruct
{
	UINT								uServiceID;						//��� ID
	UINT								uServiceStation;				//���״̬
	ServerDllInfoStruct					ServiceInfo;					//�����Ϣ
};

//����������Ϣ�ṹ
struct SC_GameRoomInitStruct
{
	//����ģʽ
	UINT								uRunStation;					//����״̬
	HWND								hWndLoader;						//װ�ش���
	HANDLE								hProcessHandle;					//���̾��

	//DLL ģʽ
	HINSTANCE							hDllInstance;					//������
	IModuleManageService				* pIManageService;				//����ӿ�

	//������Ϣ
	bool								bEnable;						//�Ƿ�����
	UINT								uKindID;						//���� ID
	UINT								uSortID;						//���� ID
	UINT								uServiceID;						//��� ID
	TCHAR								szRoomNote[50];					//���䱸ע
	ManageInfoStruct					InitInfo;						//��ʼ����Ϣ
	ServerDllInfoStruct					ServiceInfo;					//�����Ϣ
};

//���ݿ���Ϣ
struct SC_SQLInfoStruct
{
	TCHAR								szSQLIP[16];					//���ݿ��ַ
	TCHAR								szSQLName[61];					//���ݿ��û�����
	TCHAR								szSQLPass[61];					//���ݿ�����
};	

/********************************************************************************************/

//��Ϣ��ʾ�ӿ�
interface IMessageShow
{
	//�ӿں���
public:
	//��ʾ��Ϣ
	virtual bool ShowMessage(const TCHAR * szMessage)=0;
};

/********************************************************************************************/


//������Ϣ��
class CServiceInfo
{
	//��������
public:
	UINT								m_uLogonTimes;					//��½����
	UINT								m_uSystemState;					//ϵͳ״̬
	UINT								m_uModelDlgCount;				//ģ̬�Ի�����Ŀ

	//�û���½��Ϣ
public:
	TCHAR								m_szMD5Pass[50];				//MD5 ����
	TCHAR								m_szName[61];					//�û�����
	TCHAR								m_szServerGUID[37];				//������ GUID
	TCHAR								m_szLogonAddr[51];				//��½�����ַ

	//������������Ϣ 
public:
	TCHAR								m_szSQLName[61];				//SQL ����
	TCHAR								m_szSQLPass[61];				//SQL ����
	TCHAR								m_szSQLAddr[16];				//SQL ��ַ
	TCHAR								m_szServiceIP[16];				//���� IP

	//��������
public:
	//���캯��
	CServiceInfo(void);
	//��������
	~CServiceInfo(void);

	//���ܺ���
public:
	//���뺯��
	bool LoadData();
	//��������
	bool SaveData();
	//�Ƿ�����ϵͳ
	bool IsLockSystem();
	//�Ƿ��½ϵͳ
	bool IsLogonSystem();
	//��ȡ��½����
	UINT GetLogonTimes();
};

/********************************************************************************************/

//�������ϵͳ
class CServiceManage : public IClientSocketService
{
public:
	bool bGetServiceInfo(SC_GameRoomInitStruct * pComRoomInfo);
	void StartAllGames(CListCtrl * pListCtrl);
	//��������
public:
	CString m_ServiceName;

	CString	m_sServerIP;			//������IP
	CString m_sAccount;				//�˻�
	CString m_sPassword;			//����
	CString m_szDatabase;			//���ݿ���
	SHORT	m_nPort;				//���ݿ�˿�
	CString m_sDetectTable;			//��¼�ı���-(����û��)

	TCHAR										m_szError[255];					//������Ϣ
	CServiceInfo								m_Info;							//������Ϣ
	CPtrArray									m_ServiceInfo;					//�����Ϣ
	CPtrArray									m_ComRoomInfo;					//������Ϣ
//	CArray<SC_SQLInfoStruct,SC_SQLInfoStruct>	m_SQLInfo;						//���ݿ���Ϣ

	//���ݿ���Ϣ
protected:
	CString										m_strConnect;					//�����ַ�

    // PengJiLin, 2011-4-2, ָ����Щ��Ϸ�ǿ��õ�
    CGameSelecter                               m_GameSelecter;

	//�ؼ�����
protected:
	IMessageShow								* m_pIMessage;					//��Ϣ�ӿ�
	//CTCPClientSocket							m_ClientSocket;					//�ͻ� SOCKET

	//��������
public:
	//���캯��
	CServiceManage();
	//��������
	virtual ~CServiceManage(void);

	//����ӿں��� 
protected:
	//�����ȡ��Ϣ
	virtual bool OnSocketReadEvent(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize, CTCPClientSocket * pClientSocket);//{return true;}
	//����������Ϣ
	virtual bool OnSocketConnectEvent(UINT uErrorCode, CTCPClientSocket * pClientSocket);//{return true;}
	//����ر���Ϣ
	virtual bool OnSocketCloseEvent();//{return true;}

	//���ú���
public:
	//��ʼ������
	bool Init();
	//������Ϣ�ӿ�
	bool SetMessageInterface(IMessageShow * pIMessage);

	//���ܺ��� 
public:
	//��ȡ������Ϣ
	const TCHAR * const GetLastErrorMsg() { return m_szError; }
	//��½ϵͳ
	bool LogonSystem(const TCHAR * szUserName, const TCHAR * szScrPass);
	
	//�������
public:
	//��������б������ݿ���������������Ϣ������Ϣ����m_ServiceInfo������գ��У�������ͼ�б�
	bool UpdateComDLLList(CListCtrl * pListCtrl);

	//�Ƴ�ȫ������б��Ƴ�ȫ�������m_ServiceInfo,ɾ�����ݿ�ServerDLLInfo��ļ�¼
	bool RemoveDLLList(CListCtrl * pListCtrl);

	//�Ƴ�ָ������б�
	bool RemoveDLLCom(CListCtrl *pListCtrl,SC_ServiceInfoStruct * pServiceInfo);

	////����һ�������¼��ServerDllInfo���У�ͬʱ���µ�����ӵ�m_ServiceInfo��
	bool SetupCom(CListCtrl * pListCtrl,SC_ServiceInfoStruct pServiceInfo);

	////�޸�һ�������¼��ServerDllInfo����,avantp ���޸�ǰ������,pServiceInfo���޸ĺ������
	bool ModifCom(CListCtrl * pListCtrl,SC_ServiceInfoStruct * avantp,SC_ServiceInfoStruct pServiceInfo);

	//���亯��
public:
	//���·�������б�,����ʱ����,������������Ϸ
	bool UpdateServiceInfo(CListCtrl * pListCtrl);
	
	//������Ϸ����
	//SC_GameRoomInitStruct * ConfigGameRoom(SC_ServiceInfoStruct * pServiceInfo);

	//������Ϸ����
	bool StartGameRoom(SC_GameRoomInitStruct * pComRoomInfo);

	//ֹͣ��Ϸ����
	bool StopGameRoom(SC_GameRoomInitStruct * pComRoomInfo);

	//���·����б�
	bool UpdateRoomListInfo(CListCtrl * pListCtrl);

	//�õ����з�����Ϣ
	bool GetRoomListInfo();

	// ɾ�����ݿⷿ����Ϣ 
	bool DeleteGameRoomInfo(SC_GameRoomInitStruct * pComRoomInfo);

	//ע������
	//bool CheckLicense();
public:

	// �����µ���������ڸ��ºͰ�װ�µ����
	bool CopyNewCom(SC_ServiceInfoStruct* pServiceInfo);
	//ˢ����������
	void CountOnLinePeople(CListCtrl * everyDLL, CListCtrl * everyRoom);

	

	CString GetRoomName();

	void ClearRoomTWRecode(int iRoomID);
	
	
};

/********************************************************************************************/
//CString GetCPUID();
//bool checkLicense();