// MainServer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ������


// CCenterServerApp:
// �йش����ʵ�֣������ MainServer.cpp
//

#include <map>
using namespace std;

//��dllģ����ѯģ����
HMODULE ModuleGetFromMap(UINT);

//��ģ����ȡ������ӿ�
HRESULT ModuleCreateInstance(UINT,char*,LPVOID FAR**);
HRESULT ModuleCreateInstance(UINT,REFCLSID,char*,LPVOID FAR**);

class CMainServerApp : public CWinApp
{
public:
	CMainServerApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMainServerApp theApp;
