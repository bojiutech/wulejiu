// RecordPlayer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRecordPlayerApp:
// �йش����ʵ�֣������ RecordPlayer.cpp
//

class CRecordPlayerApp : public CWinApp
{
public:
	CRecordPlayerApp();

// ��д
	public:
	virtual BOOL InitInstance();

	void RegisterFile(CString   strFileName) ;  
	void GetFileName(TCHAR* filename,int& iLen);


	


// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRecordPlayerApp theApp;