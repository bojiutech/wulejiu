#pragma once
#include "afxwin.h"


// RegKeyDlg �Ի���

class RegKeyDlg : public CDialog
{
	DECLARE_DYNAMIC(RegKeyDlg)

public:
	RegKeyDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RegKeyDlg();

// �Ի�������
	enum { IDD = IDD_REGDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_RegCode;
	TCHAR m_szRegCode[40];
public:
	afx_msg void OnBnClickedOk();
public:
	afx_msg void OnBnClickedCancel();
};
