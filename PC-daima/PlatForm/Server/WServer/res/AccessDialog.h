#pragma once

#include "StdAfx.h"
#include "AFCLoader.h"

//��Ȩ����
class CAccessDialog : public CDialog
{
	//��������
public:
	TCHAR							m_szServerIP[51];								//������ IP
	TCHAR							m_szServerGUID[37];								//������ ID

	//��������
public:
	//���캯��
	CAccessDialog();
	//��������
	virtual ~CAccessDialog();

	//���غ���
protected:
	//��ʼ������
	virtual BOOL OnInitDialog();
	//ȷ������
	virtual void OnOK();

	//���ܺ���
public:
	//������Ϣ
	bool SetServerInfo(TCHAR * szServerGUID, TCHAR * szServerIP);
	//��ȡ��Ϣ
	bool GetServerInfo(TCHAR * szServerGUID, TCHAR * strServerIP);

	DECLARE_MESSAGE_MAP()
};
