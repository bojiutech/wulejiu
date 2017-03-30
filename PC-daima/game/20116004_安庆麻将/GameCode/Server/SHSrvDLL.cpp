/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               // UpGradeDLL.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include <afxdllx.h>
#include "ServerManage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static AFX_EXTENSION_MODULE UpGradeDLLDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// ���ʹ�� lpReserved���뽫���Ƴ�
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("UpGradeDLL.DLL ���ڳ�ʼ����\n");
		
		// ��չ DLL һ���Գ�ʼ��
		if (!AfxInitExtensionModule(UpGradeDLLDLL, hInstance))
			return 0;

		// ���� DLL ���뵽��Դ����
		// ע��: �������չ DLL ��
		//  MFC ���� DLL(�� ActiveX �ؼ�)��ʽ���ӵ�
		//  �������� MFC Ӧ�ó������ӵ�������Ҫ
		//  �����д� DllMain ���Ƴ������������һ��
		//  �Ӵ���չ DLL �����ĵ����ĺ����С�ʹ�ô���չ DLL ��
		//  ���� DLL Ȼ��Ӧ��ʽ
		//  ���øú����Գ�ʼ������չ DLL������
		//  CDynLinkLibrary ���󲻻ḽ�ӵ�
		//  ���� DLL ����Դ���������������ص�
		//  ���⡣

		new CDynLinkLibrary(UpGradeDLLDLL);

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("UpGradeDLL.DLL ������ֹ��\n");

		// �ڵ�����������֮ǰ��ֹ�ÿ�
		AfxTermExtensionModule(UpGradeDLLDLL);
	}
	return 1;   // ȷ��
}

//��ȡ��Ϸ�����Ϣ
extern "C" __declspec(dllexport) BOOL GetServiceInfo(ServerDllInfoStruct * pServiceInfo, UINT uVer)
{
	//Ч����Ϣ
	if ((uVer!=DEV_LIB_VER)||(pServiceInfo==NULL)) return FALSE;

	//д����Ϣ
	memset(pServiceInfo,0,sizeof(ServerDllInfoStruct));
	pServiceInfo->uServiceVer=GAME_MAX_VER;
	pServiceInfo->uNameID=NAME_ID;
	pServiceInfo->uDeskPeople=PLAY_COUNT;
	pServiceInfo->uSupportType=SUPPER_TYPE;
	lstrcpy(pServiceInfo->szGameName,GAMENAME);
	//lstrcpy(pServiceInfo->szGameTable,GAME_TABLE_NAME);
	lstrcpy(pServiceInfo->szDLLFileName,GET_SERVER_DLL_NAME(szTempStr));
	lstrcpy(pServiceInfo->szWriter,TEXT(""));
	lstrcpy(pServiceInfo->szDllNote,TEXT("���� -- ��������Ϸ���"));

	return TRUE;
}

//��ȡ��Ϸ����ӿں���
extern "C" __declspec(dllexport) IModuleManageService * CreateServiceInterface(UINT uVer)
{
	if (uVer==DEV_LIB_VER) 
	{
		try	{ return new CGameModuleTemplate<CServerGameDesk,1,10>; }
		catch (...) {}
	}
	return NULL;
}
