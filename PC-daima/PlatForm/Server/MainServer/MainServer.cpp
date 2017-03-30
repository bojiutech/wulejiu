// MainServer.cpp : ����Ӧ�ó��������Ϊ��
#include "stdafx.h"
#include "MainServer.h"
#include "MainServerDlg.h"
#include "BzCrashRpt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CCenterServerApp

BEGIN_MESSAGE_MAP(CMainServerApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

//dllģ���
std::map<UINT,HMODULE> g_MuduleMap;

// CCenterServerApp ����

CMainServerApp::CMainServerApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CCenterServerApp ����

CMainServerApp theApp;


// CCenterServerApp ��ʼ��

BOOL CMainServerApp::InitInstance()/////��ʼ��
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControls()�����򣬽��޷��������ڡ�
	InitCommonControls();
	CWinApp::InitInstance();
	AfxOleInit();

	AfxEnableControlContainer();
	
	//�������ģ��------------------------------------------------------------------------

	HMODULE hModual = NULL;
	g_MuduleMap.clear();

	//����SMSͨѶģ�� -Sms.dll
	hModual = ::LoadLibrary(_TEXT("plugin\\Sms.dll"));
	g_MuduleMap.insert(std::pair<UINT,HMODULE>(MODUAL_PLUGIN_Z_SMS,hModual));

	//end--------------------------------------------------------------------------------

	CMainServerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO���ڴ˷��ô����ʱ�á�ȷ�������ر�
		//�Ի���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO���ڴ˷��ô����ʱ�á�ȡ�������ر�
		//�Ի���Ĵ���
	}

	//�ͷ����ģ��------------------------------------------------------------------------

	std::map<UINT,HMODULE>::iterator itMMap = g_MuduleMap.begin();
	for (;itMMap != g_MuduleMap.end(); itMMap++)
	{
		if (itMMap->second)
		{
			::FreeLibrary(itMMap->second);
		}
	}

	//end--------------------------------------------------------------------------------

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	// ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}


//��dllģ����ѯģ����
HMODULE ModuleGetFromMap(UINT uModualID)
{
	std::map<UINT,HMODULE>::iterator itMMap = g_MuduleMap.find(uModualID);
	return (HMODULE)itMMap->second;
}

//��ģ����ȡ������ӿ�

HRESULT ModuleCreateInstance(UINT uModualID,char* szCreateFunName,LPVOID FAR** ppv)
{
	typedef HRESULT (*func_ptr)(LPVOID FAR**);
	HMODULE hModule = ModuleGetFromMap(uModualID);
	if (hModule)
	{
		func_ptr lpFunc = (func_ptr)::GetProcAddress(hModule,szCreateFunName);
		if (lpFunc)
		{
			return lpFunc(ppv);
		}
	}

	return S_FALSE;
}

HRESULT ModuleCreateInstance(UINT uModualID,REFCLSID rclsid,char* szCreateFunName,LPVOID FAR** ppv)
{
	typedef HRESULT (*func_ptr)(REFCLSID,LPVOID FAR**);
	HMODULE hModule = ModuleGetFromMap(uModualID);
	if (hModule)
	{
		func_ptr lpFunc = (func_ptr)::GetProcAddress(hModule,szCreateFunName);
		if (lpFunc)
		{
			return lpFunc(rclsid,ppv);
		}
	}

	return S_FALSE;
}
