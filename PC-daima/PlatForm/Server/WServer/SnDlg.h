#pragma once
#include "Resource.h"

// CSnDlg �Ի���

class CSnDlg : public CDialog
{
	DECLARE_DYNAMIC(CSnDlg)

public:
	CSnDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSnDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedOk();

	int m_Sn;
	bool m_bOK;
};
