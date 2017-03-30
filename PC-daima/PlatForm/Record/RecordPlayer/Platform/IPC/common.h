#ifndef COMMON_H
#define COMMON_H

#pragma once

#pragma pack(push,1)


#define  SafeDeleteArray(pData)	{ try { delete [] pData; } catch (...) { } pData=NULL; } 


#define SOCKET_PACKAGE			2046
#define KIND_LEN				32
#define SERVER_LEN				32
#define MAX_CHAT_LEN			512

#define IPCFILENAME				"AA4F9A47-086F-40a8-856F-83BD017870F6"


//�������
#define	SM_CREATE_ERROR				0									//��������
#define	SM_CREATE_SUCCESS			1									//�����ɹ�
#define	SM_ALREADY_EXIST			2									//�Ѿ�����


//////////////////////////////////////////////////////////////////////////
//���ݰ�������Ϣ
struct CMD_Command
{
	WORD								wMainCmdID;							//��������
	WORD								wSubCmdID;							//��������
};

//////////////////////////////////////////////////////////////////////////

//�ں���������
#define IPC_MAIN_IPC_KERNEL					0							//�ں�����

//�ں���������
#define IPC_SUB_IPC_CLIENT_CONNECT			1							//����֪ͨ
#define IPC_SUB_IPC_SERVER_ACCEPT			2							//Ӧ��֪ͨ
#define IPC_SUB_IPC_CLIENT_CLOSE			3							//�ر�֪ͨ

//////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////

//IPC ���ݶ���
#define IPC_VER							0x0001								//IPC �汾
#define IPC_IDENTIFIER					0x0001								//��ʶ����
#define IPC_PACKAGE						4096								//��� IPC ��
#define IPC_BUFFER						(sizeof(IPC_Head)+IPC_PACKAGE)		//���峤��

//IPC ���ݰ�ͷ
struct IPC_Head
{
	WORD								wVersion;							//IPC �汾
	WORD								wDataSize;							//���ݴ�С
	WORD								wMainCmdID;							//��������
	WORD								wSubCmdID;							//��������
};

//IPC ����ṹ
struct IPC_Buffer
{
	IPC_Head							Head;								//���ݰ�ͷ
	BYTE								cbBuffer[IPC_PACKAGE];				//���ݻ���
};

//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
//IPC �����¼�

#define IPC_MAIN_SOCKET					1								//������Ϣ

#define		IPC_SUB_SOCKET_SEND				1								//���緢��
#define		IPC_SUB_SOCKET_RECV				2								//�������
#define		IPC_SUB_IPC_HEART_BEAT			3								//����֪ͨ

//IPC ������ṹ
struct IPC_SocketPackage
{
	CMD_Command							Command;						//������Ϣ
	BYTE								cbBuffer[SOCKET_PACKAGE];		//���ݻ���
};

//////////////////////////////////////////////////////////////////////////
//IPC ������Ϣ

#define IPC_MAIN_CONFIG					2								//������Ϣ

#define		IPC_SUB_SERVER_INFO				1								//������Ϣ
#define		IPC_SUB_COLUMN_INFO				2								//�б���Ϣ

//��Ϸ��Ϣ
struct IPC_GF_ServerInfo
{
	DWORD								dwUserID;						//�û� I D
	WORD								wTableID;						//���Ӻ���
	WORD								wChairID;						//���Ӻ���
	WORD								wKindID;						//���ͱ�ʶ
	WORD								wServerID;						//�����ʶ
	WORD								wGameGenre;						//��Ϸ����
	WORD								wChairCount;					//������Ŀ
	BYTE								cbHideUserInfo;					//������Ϣ
	DWORD								dwVideoAddr;					//��Ƶ��ַ
	TCHAR								szKindName[KIND_LEN];			//��������
	TCHAR								szServerName[SERVER_LEN];		//��������
};

//////////////////////////////////////////////////////////////////////////
//IPC �û���Ϣ

#define IPC_MAIN_USER					3								//�û���Ϣ

#define		IPC_SUB_USER_COME				1								//�û���Ϣ
#define		IPC_SUB_USER_STATUS				2								//�û�״̬
#define		IPC_SUB_USER_SCORE				3								//�û�����
#define		IPC_SUB_GAME_START				4								//��Ϸ��ʼ
#define		IPC_SUB_GAME_FINISH				5								//��Ϸ����
#define		IPC_SUB_ASK_USER_LIST			6								//����ͬ���û��嵥
#define		IPC_SUB_REPLY_USER_LIST			7								//�ظ�ͬ���û��嵥

//�û�״̬
struct IPC_UserStatus
{
	DWORD								dwUserID;						//�û� I D
	WORD								wNetDelay;						//������ʱ
	BYTE								cbUserStatus;					//�û�״̬
};

//�û�����
struct IPC_UserScore
{
	DWORD								dwUserID;						//�û� I D
//	tagUserScore						UserScore;						//�û�����
};

//////////////////////////////////////////////////////////////////////////
//IPC ������Ϣ

#define IPC_MAIN_CONCTROL				4								//������Ϣ

#define		IPC_SUB_START_FINISH			1								//�������
#define		IPC_SUB_CLOSE_FRAME				2								//�رտ��
#define		IPC_SUB_JOIN_IN_GAME			3								//������Ϸ
#define		IPC_SUB_SHOW_MSG_IN_GAME		4								//��ʾ��Ϸ����Ϣ
#define		IPC_SUB_SHOW_DUDU				5								//��ʾ����Ϣ

//////////////////////////////////////////////////////////////////////////
//IPC ������Ϣ	2008/11/3
#define IPC_MAIN_PROP					5								//��������Ϣ
#define		IPC_SUB_INIT_PROP				1								//��ʼ������
#define		IPC_SUB_INIT_PROP_FINISH		2
#define		IPC_SUB_USE_PROP				3								//ʹ�õ���	
#define		IPC_SUB_BUY_PROP				4								//�������
#define		IPC_SUB_PRESENT_PROP			5								//���������͵���
#define		IPC_SUB_ACCEPT_PROP				6								//���ܱ������͵ĵ���
#define		IPC_SUB_BROADCAST_BIG			7								//��������Ϣ
#define		IPC_SUB_BROADCAST_SMALL			8								//С������Ϣ
#define		IPC_SUB_USE_MOVIE_PROP			9								//ʹ�ö�������	
#define		IPC_SUB_PRESENT_PROP_FAIL		10								//���������͵���ʧ��

//������Ϸ
struct IPC_JoinInGame
{
	WORD								wTableID;						//���Ӻ���
	WORD								wChairID;						//���Ӻ���
};


//�����ڴ涨��
struct tagShareMemory
{
	WORD								wDataSize;						//���ݴ�С
	HWND								hWndGameFrame;					//��ܾ��
	HWND								hWndGamePlaza;					//�㳡���
	HWND								hWndGameServer;					//������
};

// ������EXE������ʾ��Ϸ������Ϣ�Ľṹ
struct MsgInGameStruct 
{
	TCHAR szMsg[1000];
	bool  bIsFontValid;
	TCHAR szFontName[32];
	bool  bIsTitleValid;
	TCHAR szTitle[64];
	BYTE bNewOrSys;
	UINT uSize;
};
// ������EXE��������Ϣ�Ľṹ
struct MsgDuduStruct 
{
	TCHAR szSendName[64];
	TCHAR szTargetName[64];
	TCHAR szCharString[256];
	COLORREF crTextColor;
	bool  bShowTime;
	UINT uSize;
	bool bIsFontValid;
	TCHAR szFontName[64];
	int iDuduType;
};
#pragma pack(pop)

#endif //COMMON_H
