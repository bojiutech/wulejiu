/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #include "../Server/stdafx.h"
#include <afxdllx.h>
#include "../Client/Resource.h"
#include "../Client/ClientGameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static AFX_EXTENSION_MODULE GameClientDLL = { NULL, NULL };

//DLL ��ں���
extern "C" int APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		if (!AfxInitExtensionModule(GameClientDLL, hInstance)) return 0;
		new CDynLinkLibrary(GameClientDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		AfxTermExtensionModule(GameClientDLL);
	}

	return 1;
}

/********************************************************************************************/

//�ȼ��жϺ�������Ϫ�齫��
extern "C" __declspec(dllexport) TCHAR * GetGameOrderName(__int64 dwPoint)
{//lu20080701�ȼ��жϺ���
	static int uBasePoint[21]=
	{
		10,		20,		40,  	80,	
		160,	320,	640,	1280,	
		2560,	5120,	10240,	20480,	
		40960,	81920,	163840,	327680,		
		655360,	1310720,2621440,5242880,	
		10485760	


	};
	static TCHAR * szOrderName[21]=
	{
		TEXT("ƽ��"),TEXT("���"),TEXT("ѧ��"),TEXT("Ѳ��"),
		TEXT("У��"),TEXT("֪��"),TEXT("��ة"),TEXT("����"),
		TEXT("֪��"),TEXT("��ͬ"),TEXT("ͨ��"),TEXT("�̶�"),
		TEXT("����"),TEXT("����"),TEXT("��ʷ"),TEXT("����"),
		TEXT("����"),TEXT("����ʹ"),TEXT("����"),TEXT("��ʦ"),
		TEXT("̫ʦ")
	};
	for (int i=0;i<21;i++)	if (dwPoint<uBasePoint[i]) return szOrderName[i];
	return TEXT("�ʵ�");
}

/********************************************************************************************/

//������Ϸ�ͻ���
//�ͻ�����������
GETCLIENTINFO;
GETGAMEICON(NAME_ID);//lu��ȡ��Ϸͼ��
GETFRAMEINTERFACE(CClientGameDlg)//lu������Ϸ����
GETORDERFUNCTION(GetGameOrderName);//lu��ȡ��ҵȼ�

/********************************************************************************************/
