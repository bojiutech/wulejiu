#pragma once

#ifndef CAFCLOADERAPP_H_2003
#define CAFCLOADERAPP_H_2003

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"
#include "ServiceManage.h"

//Ӧ�ó�����
class CAFCLoaderApp : public CWinApp
{
	//��������
public:
	bool CheckBanBen();
	//���캯��
	CAFCLoaderApp();
	//��ʼ������
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern	CAFCLoaderApp	theApp;				//Ӧ�ó���
extern	CServiceManage	g_Service;			//��Ϸ����

#endif