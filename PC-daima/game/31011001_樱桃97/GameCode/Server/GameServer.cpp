// GameServer.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include <afxdllx.h>
#include "ServerManage.h"
#ifdef _MANAGED
#error ���Ķ� GameServer.cpp �е�˵����ʹ�� /clr ���б���
// ���Ҫ��������Ŀ����� /clr������ִ�����в���:
//	1. �Ƴ������� afxdllx.h �İ���
//	2. ��û��ʹ�� /clr ���ѽ���Ԥ����ͷ��
//	   ��Ŀ���һ�� .cpp �ļ������к��������ı�:
//			#include <afxwin.h>
//			#include <afxdllx.h>
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


static AFX_EXTENSION_MODULE GameServerDLL = { NULL, NULL };

#ifdef _MANAGED
#pragma managed(push, off)
#endif

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// ���ʹ�� lpReserved���뽫���Ƴ�
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("GameServer.DLL ���ڳ�ʼ��!\n");
		
		// ��չ DLL һ���Գ�ʼ��
		if (!AfxInitExtensionModule(GameServerDLL, hInstance))
			return 0;

		// ���� DLL ���뵽��Դ����
		// ע��: �������չ DLL ��
		//  MFC ���� DLL (�� ActiveX �ؼ�)��ʽ���ӵ���
		//  �������� MFC Ӧ�ó������ӵ�������Ҫ
		//  �����д� DllMain ���Ƴ������������һ��
		//  �Ӵ���չ DLL �����ĵ����ĺ����С�ʹ�ô���չ DLL ��
		//  ���� DLL Ȼ��Ӧ��ʽ
		//  ���øú����Գ�ʼ������չ DLL������
		//  CDynLinkLibrary ���󲻻ḽ�ӵ�
		//  ���� DLL ����Դ���������������ص�
		//  ���⡣

		new CDynLinkLibrary(GameServerDLL);

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("GameServer.DLL ������ֹ!\n");

		// �ڵ�����������֮ǰ��ֹ�ÿ�
		AfxTermExtensionModule(GameServerDLL);
	}
	return 1;   // ȷ��
}

//��ȡ��Ϸ�����Ϣ
extern "C" __declspec(dllexport) BOOL GetServiceInfo(ServerDllInfoStruct * pServiceInfo, UINT uVer)
{
	//Ч����Ϣ
	if ((DEV_LIB_VER != uVer) || (NULL == pServiceInfo))
	{
		return FALSE;
	}

	//д����Ϣ
	memset(pServiceInfo,0,sizeof(ServerDllInfoStruct));
	pServiceInfo->uServiceVer=GAME_MAX_VER;
	pServiceInfo->uNameID=NAME_ID;
	pServiceInfo->uDeskPeople=PLAY_COUNT;
	pServiceInfo->uSupportType=SUPPER_TYPE;
	lstrcpy(pServiceInfo->szGameName,GAMENAME);
	lstrcpy(pServiceInfo->szWriter,GAME_DLL_AUTHOR);
	lstrcpy(pServiceInfo->szDllNote,GAME_DLL_NOTE);
	return TRUE;
}

//��ȡ��Ϸ����ӿں���
extern "C" __declspec(dllexport) IModuleManageService * CreateServiceInterface(UINT uVer)
{
	if (DEV_LIB_VER == uVer) 
	{
		try
		{
			return new CGameModuleTemplate<CServerGameDesk,1,10>;
		}
		catch (...)
		{}
	}
	return NULL;
}
#ifdef _MANAGED
#pragma managed(pop)
#endif

