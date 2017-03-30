#include "StdAfx.h"
#include "AFCLoader.h"
#include "MainFrm.h"

BEGIN_MESSAGE_MAP(CAFCLoaderApp, CWinApp)
END_MESSAGE_MAP()

#include <windows.h>  
#include <DbgHelp.h>  
#include <stdlib.h>  
#pragma comment(lib, "dbghelp.lib")  

#ifndef _M_IX86  
#error "The following code only works for x86!"  
#endif  

inline BOOL IsDataSectionNeeded(const WCHAR* pModuleName)  
{  
	if(pModuleName == 0)  
	{  
		return FALSE;  
	}  

	WCHAR szFileName[_MAX_FNAME] = L"";  
	_wsplitpath(pModuleName, NULL, NULL, szFileName, NULL);  

	if(wcsicmp(szFileName, L"ntdll") == 0)  
		return TRUE;  

	return FALSE;  
}  

inline BOOL CALLBACK MiniDumpCallback(PVOID                            pParam,  
	const PMINIDUMP_CALLBACK_INPUT   pInput,  
	PMINIDUMP_CALLBACK_OUTPUT        pOutput)  
{  
	if(pInput == 0 || pOutput == 0)  
		return FALSE;  

	switch(pInput->CallbackType)  
	{  
	case ModuleCallback:  
		if(pOutput->ModuleWriteFlags & ModuleWriteDataSeg)  
			if(!IsDataSectionNeeded(pInput->Module.FullPath))  
				pOutput->ModuleWriteFlags &= (~ModuleWriteDataSeg);  
	case IncludeModuleCallback:  
	case IncludeThreadCallback:  
	case ThreadCallback:  
	case ThreadExCallback:  
		return TRUE;  
	default:;  
	}  

	return FALSE;  
}  

inline void CreateMiniDump(PEXCEPTION_POINTERS pep, LPCTSTR strFileName)  
{  
	HANDLE hFile = CreateFile(strFileName, GENERIC_READ | GENERIC_WRITE,  
		FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);  

	if((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))  
	{  
		MINIDUMP_EXCEPTION_INFORMATION mdei;  
		mdei.ThreadId           = GetCurrentThreadId();  
		mdei.ExceptionPointers  = pep;  
		mdei.ClientPointers     = NULL;  

		MINIDUMP_CALLBACK_INFORMATION mci;  
		mci.CallbackRoutine     = (MINIDUMP_CALLBACK_ROUTINE)MiniDumpCallback;  
		mci.CallbackParam       = 0;  

		::MiniDumpWriteDump(::GetCurrentProcess(), ::GetCurrentProcessId(), hFile, MiniDumpNormal, (pep != 0) ? &mdei : 0, NULL, &mci);  

		CloseHandle(hFile);  
	}  
}  

LONG __stdcall MyUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo)  
{  
	CString strPath;
	char szPath[MAX_PATH];
	memset(szPath, 0, MAX_PATH);
	GetCurrentDirectory(MAX_PATH, szPath);
	strPath.ReleaseBuffer();
	strPath.Format("%s\\D-Error\\", szPath);
	CreateDirectory(strPath, NULL);
	CString strFile;
	CTime tm = CTime::GetCurrentTime();
	strFile.Format(_T("%sError%d-%d-%d&%d-%d-%d.dmp"), strPath,tm.GetYear(),tm.GetMonth(),tm.GetDay(),tm.GetHour(),tm.GetMinute(),tm.GetSecond());
	CreateMiniDump(pExceptionInfo, strFile);  
	AfxMessageBox(strPath);
	return EXCEPTION_EXECUTE_HANDLER;  
}  

// �˺���һ���ɹ����ã�֮��� SetUnhandledExceptionFilter �ĵ��ý���Ч  
void DisableSetUnhandledExceptionFilter()  
{  
	void* addr = (void*)GetProcAddress(LoadLibrary("kernel32.dll"),  
		"SetUnhandledExceptionFilter");  

	if (addr)  
	{  
		unsigned char code[16];  
		int size = 0;  

		code[size++] = 0x33;  
		code[size++] = 0xC0;  
		code[size++] = 0xC2;  
		code[size++] = 0x04;  
		code[size++] = 0x00;  

		DWORD dwOldFlag, dwTempFlag;  
		VirtualProtect(addr, size, PAGE_READWRITE, &dwOldFlag);  
		WriteProcessMemory(GetCurrentProcess(), addr, code, size, NULL);  
		VirtualProtect(addr, size, dwOldFlag, &dwTempFlag);  
	}  
}  

void InitMinDump()  
{  
	//ע���쳣������  
	SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);  

	//ʹSetUnhandledExceptionFilter  
	DisableSetUnhandledExceptionFilter();  
} 

//Ӧ�ó������
CAFCLoaderApp theApp;

//���캯��
CAFCLoaderApp::CAFCLoaderApp()
{
}

bool CAFCLoaderApp::CheckBanBen()
{
	return true;
	CString sn ="20071030";////��ֹ����
	
	long in=atol(sn.GetBuffer (sn.GetLength ()));
	if(in<=0) return false;
	int y1=atoi(sn.Mid (0,4)),
		m1   =atoi(sn.Mid (4,2)),
		d1=atoi(sn.Mid (6,2));

	CTime t1(y1,m1,d1,0,0,0);
	time_t ct;  
    time( &ct ) ;

	CTime t2(ct);

	CTimeSpan tsp;
	tsp=t2-t1;//// ��ǰ����  - ��ֹ����

	LONGLONG dd=tsp.GetDays ();

	if(t2>t1)//dd > 0)
	{
		//KillTimer(1);
		//KillTimer(2);
		//KillTimer(3);
		//m_GameLogon.StoptService();
		AfxMessageBox("������������ڵ��ڣ���������ϵ������Ա��ȡ�����汾��������ʾ����ʱ�����ƣ�����˵�����������ѵ�����ȡ�����汾����ѵġ���");
		//CDialog::OnOK ();//theApp.m_pMainWnd->DestroyWindow ();
		return false;
	}
	return true;
}

//��ʼ������
BOOL CAFCLoaderApp::InitInstance()
{
	if(!CheckBanBen()) return true;
	//��ʼ��
	InitCommonControls();
	CWinApp::InitInstance();

	//��ʼ��
	if (!AfxOleInit()||!AfxSocketInit()) return FALSE;
	AfxEnableControlContainer();
	SetRegistryKey(_T("�ӷֲ�����������ϵͳ"));

	//���ó���·��
	TCHAR szModuleName[MAX_PATH];
	DWORD dwLength=GetModuleFileName(AfxGetInstanceHandle(),szModuleName,sizeof(szModuleName));
	szModuleName[dwLength-lstrlen(m_pszExeName)-lstrlen(TEXT(".EXE"))-1]=0;
	SetCurrentDirectory(szModuleName);

	InitMinDump();
	//��������
	
	CMainFrame * pFrame=new CMainFrame;
	m_pMainWnd=pFrame;
	pFrame->LoadFrame(IDR_MAINFRAME,WS_OVERLAPPEDWINDOW,NULL,NULL);
	//pFrame->SetWindowTextA("hepengyu");//SetWindowTitle(TMLcopyright);
	//pFrame->SetTitle(TMLcopyright);
	return TRUE;
}
