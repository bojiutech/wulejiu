#pragma once

#include "Stdafx.h"
#include "AFCLoader.h"

//��¼�Ի�����
class CLogonDialog : public CDialog
{
	//��������
public:
	CString							m_strName;						//�û����� 
	CString							m_strPass;						//�û�����

public:
	//���캯��
	CLogonDialog(CWnd * pParent=NULL);
	//�������� 
	virtual ~CLogonDialog();

	//���غ���
protected:
	//��ʼ������
	virtual BOOL OnInitDialog();
	//ȷ������
	virtual void OnOK();

	//��Ϣ����
public:
	//��Ȩ����
	afx_msg void OnBnClickedSetting();

	DECLARE_MESSAGE_MAP()
};
