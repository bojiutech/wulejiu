// RecordModule.cpp : ���� DLL Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "RecordModule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
	}

	return nRetCode;
}
//DLL ��ں���
//static AFX_EXTENSION_MODULE GameClientDLL = { NULL, NULL };
//
//extern "C" int APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
//{
//	UNREFERENCED_PARAMETER(lpReserved);
//	if (dwReason == DLL_PROCESS_ATTACH)
//	{
//		if (!AfxInitExtensionModule(GameClientDLL, hInstance)) return 0;
//		new CDynLinkLibrary(GameClientDLL);
//	}
//	else if (dwReason == DLL_PROCESS_DETACH)
//	{
//		AfxTermExtensionModule(GameClientDLL);
//	}
//
//	return 1;
//}
