#pragma once

#ifndef CMAINFRAME_H_2003
#define CMAINFRAME_H_2003

#include "TrayIcon.h"
#include "ChildView.h"
//#include "LogonDialog.h"
#include "ServiceManage.h"
//#include "..\..\..\SDK\include\common\LicenseValidator.h"

//ע�����
#define REG_LICENSE		TEXT("BZWServer\\WServer\\LicenseKey")
#define IDM_TRAY_NOTIFY_MSG				WM_USER+10			//��������ʾ��Ϣ

//��ȡ������ͼ��
CTrayIcon & AFCGetTrayIcon();

//���ڿ����
class CMainFrame : public CFrameWnd , public IMessageShow
{
	//��������
public:
	CTrayIcon					m_TrayIcon;					//������ͼ��
	CChildView					m_wndView;					//��ͼ����
	LRESULT OnCreateTray(WPARAM wp, LPARAM lp);
	//�ں˱���
	//LicenseValidator CheckLicense;
public:

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CMainFrame)
	
	//��������
public:
	//���캯��
	CMainFrame();
	//��������
	virtual ~CMainFrame();
	//��ʼ����������
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//�����
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void * pExtra, AFX_CMDHANDLERINFO * pHandlerInfo);
	//��ʾ��Ϣ
	virtual bool ShowMessage(const TCHAR * szMessage);

	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	//��Ϣ����
public:
	//������ͼ����Ϣ
	LRESULT OnTrayIconNotify(WPARAM wID, LPARAM lEvent);
	//������ͼ����Ϣ
	LRESULT OnMouseHover(WPARAM wID, LPARAM lEvent);
	//������ͼ����Ϣ
	LRESULT OnMouseLeave(WPARAM wID, LPARAM lEvent);
	//��������
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//���㺯��
	afx_msg void OnSetFocus(CWnd * pOldWnd);
	//λ����Ϣ
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//��½ϵͳ
	afx_msg void OnLogonSystem();
	//��ȡ�����б�
	afx_msg void OnGetRoomList();

	afx_msg void OnTimer(UINT nIDEvent);
	bool m_bMouseTrack;
};


extern CServiceManage					g_Service;					//��Ϸ����

#endif