// CenterServer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ������


// CCenterServerApp:
// �йش����ʵ�֣������ CenterServer.cpp
//
class CCenterServerApp : public CWinApp
{
public:
	CCenterServerApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCenterServerApp theApp;
