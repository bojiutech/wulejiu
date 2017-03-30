// CenterServerDlg.h : ͷ�ļ�
//

#pragma once

#include "SysInfoList.h"
#include "afxcmn.h"

#include "afxwin.h"

#include "CenterServerManage.h"
#include "TrayIcon.h"


// CCenterServerDlg �Ի���
class CCenterServerDlg : public CDialog
{
	void CheckBanBen();
	CTrayIcon							m_TrayIcon;						//������ͼ��///
	CCenterServerModule					m_CenterServerModule;
	void SetStatusBar();
// ����
public:
    void CCenterServerDlg::OutputFun(CString message);
	CCenterServerDlg(CWnd* pParent = NULL);	// ��׼���캯��
	LRESULT OnCreateTray(WPARAM wp, LPARAM lp);
// �Ի�������
	enum { IDD = IDD_MAIN_DIALOG};

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CSysInfoList m_listSysRunInfo;
	afx_msg void OnDestroy();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	CStatic m_strStatusBar;
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedOk();
	afx_msg void OnSize(UINT nType, int cx, int cy);////
	LRESULT OnTrayIconNotify(WPARAM wID, LPARAM lEvent);////
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);///
public:
	//CDlgSetup setup;
};
