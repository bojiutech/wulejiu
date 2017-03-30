#include "Stdafx.h"
#include "AFCLoader.h"
#include "MainFrm.h"
#include "BuildTime.h"
#include "RegKeyDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define VK_B								66						 //'B'key
#define VK_Z								90						 //'Z'key
#define VK_W								87						 //'W'key


IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_MESSAGE(WM_MOUSEHOVER,OnMouseHover)
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
	ON_MESSAGE(IDM_TRAY_NOTIFY_MSG,OnTrayIconNotify)
	ON_COMMAND(IDM_LOGON_SYSTEM, OnLogonSystem)
	ON_COMMAND(IDM_GET_ROOM_LIST, OnGetRoomList)
	ON_REGISTERED_MESSAGE(WM_CREATETRAYBAR, OnCreateTray)
END_MESSAGE_MAP()

CServiceManage					g_Service;					//��Ϸ����

//��ȡ������ͼ��
CTrayIcon & AFCGetTrayIcon() { return ((CMainFrame *)AfxGetMainWnd())->m_TrayIcon; };

//���캯��
CMainFrame::CMainFrame() : m_TrayIcon(10)
{
	m_bMouseTrack = true;
}

//��������
CMainFrame::~CMainFrame()
{
}

//��������
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	//ϵͳ�ڲ�����
	if (CFrameWnd::OnCreate(lpCreateStruct)==-1) return -1;
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,CRect(0,0,0,0),this,AFX_IDW_PANE_FIRST,NULL))	return -1;

	//����������ͼ��
	HICON hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_TrayIcon.SetNotifyWnd(this,IDM_TRAY_NOTIFY_MSG);
	m_TrayIcon.SetIcon(hIcon,APP_TITLE);
	SetIcon(hIcon,FALSE);
	DestroyIcon(hIcon);
	CenterWindow();

	//��½ϵͳ
	g_Service.m_Info.LoadData();
	g_Service.SetMessageInterface(this);
	g_Service.Init();
	PostMessage(WM_COMMAND,IDM_LOGON_SYSTEM,0);

	CString s,scaption;
	GetWindowText(s);
	scaption.Format("%s v%d.%d.%d %s",s,VER_MAIN,VER_MIDDLE,VER_RESVERSE,VER_BUILDTIME);
	SetWindowText(scaption);	

	//SetTimer(1,6000,NULL);

	return 0;
}

//��Ϣ����
BOOL CMainFrame::PreTranslateMessage(MSG * pMsg)
{
	if (this->GetSafeHwnd()==NULL)
	{
		return TRUE;
	}
	
	
	if (pMsg->message==WM_KEYDOWN)		
	{
		if((GetAsyncKeyState(VK_CONTROL) < 0)
		&& (GetAsyncKeyState(VK_B) < 0) 
		&& (GetAsyncKeyState(VK_Z) < 0) 
		&& (GetAsyncKeyState(VK_W) < 0))
		{
			CString CheckVersionHotKey = "�����к�������Ƽ����޹�˾";
			AfxMessageBox(CheckVersionHotKey);
		
			return TRUE;
		}
	}

	return __super::PreTranslateMessage(pMsg);
}

//��ʼ����������
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs)) return FALSE;
	cs.style=WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|WS_MINIMIZEBOX|WS_MAXIMIZEBOX;
	cs.dwExStyle&=~WS_EX_CLIENTEDGE;
	cs.lpszClass=AfxRegisterWndClass(0);

	return TRUE;
}

//���㺯��
void CMainFrame::OnSetFocus(CWnd * pOldWnd)
{
	m_wndView.SetFocus();
}

//�����
BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo)) return TRUE;

	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

//������ͼ����Ϣ
LRESULT CMainFrame::OnMouseHover(WPARAM wID, LPARAM lEvent)
{
	return 0;
}

//������ͼ����Ϣ
LRESULT CMainFrame::OnMouseLeave(WPARAM wID, LPARAM lEvent)
{
	m_TrayIcon.SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), g_Service.GetRoomName());
	m_bMouseTrack=true;
	return 0;
}

//������ͼ����Ϣ
LRESULT CMainFrame::OnTrayIconNotify(WPARAM wID, LPARAM lEvent)
{
	switch (lEvent)
	{
	case WM_MOUSEMOVE:
		{
			if (m_bMouseTrack)
			{
				TRACKMOUSEEVENT tme;
				tme.cbSize = sizeof(tme); //�ṹ�建������С
				tme.dwFlags = TME_LEAVE|TME_HOVER; //ע��WM_MOUSEHOVER��Ϣ
				tme.dwHoverTime = 10; //WM_MOUSEHOVER��Ϣ�������ʱ��
				tme.hwndTrack = GetSafeHwnd(); //��ǰ���ھ��

				::TrackMouseEvent(&tme); //ע�ᷢ����Ϣ

				m_bMouseTrack = false;
			}
			return 1;
		}
	case WM_LBUTTONDBLCLK:	//˫���¼�
		{
			////if (g_Service.m_Info.IsLogonSystem())
			{
				ShowWindow(SW_SHOWMAXIMIZED);
				SetForegroundWindow();
			}
			return 1;
		}
	case WM_RBUTTONUP:		//�Ҽ���Ϣ
		{
			CMenu Menu;
			Menu.LoadMenu(IDR_MAINFRAME);
			CMenu * pSubMenu=Menu.GetSubMenu(0);
			CPoint MousePoint;
			::GetCursorPos(&MousePoint);	
			SetForegroundWindow();

			//���Ʋ˵�
			if (g_Service.m_Info.IsLockSystem()==false)	pSubMenu->EnableMenuItem(IDM_LOCK_SYSTEM,MF_BYCOMMAND|MF_GRAYED);
			if (g_Service.m_Info.m_uSystemState!=STS_NO_LOGON) pSubMenu->EnableMenuItem(IDM_LOGON_SYSTEM,MF_BYCOMMAND|MF_GRAYED);
			::TrackPopupMenu(pSubMenu->GetSafeHmenu(),0,MousePoint.x,MousePoint.y,0,GetSafeHwnd(),NULL);

			return 1;
		}
	}
	return 0;
}

//λ����Ϣ
void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);
	if (nType==SIZE_MINIMIZED)	ShowWindow(SW_HIDE);
}

//��½ϵͳ
void CMainFrame::OnLogonSystem()
{
	g_Service.LogonSystem("pmb","123");//LogonDialog.m_strName,LogonDialog.m_strPass);
	/*static CLogonDialog	LogonDialog;
	if (LogonDialog.GetSafeHwnd()==NULL)	//������¼����
	{
		if (LogonDialog.DoModal()==IDOK)	//��½ϵͳ
		{
			g_Service.LogonSystem(LogonDialog.m_strName,LogonDialog.m_strPass);
		}
		else if (g_Service.m_Info.GetLogonTimes()==0)	//�˳�ϵͳ
		{
			PostMessage(WM_COMMAND,ID_APP_EXIT,0);
		}
	}
	else	//�Ѿ����ڵ�¼����
	{
		//ShowWindow(SW_HIDE);
		LogonDialog.ShowWindow(SW_SHOW);	
		LogonDialog.SetForegroundWindow();
	}
	return;*/
}

//��ʾ��Ϣ
bool CMainFrame::ShowMessage(const TCHAR * szMessage)
{
	m_TrayIcon.ShowBalloonTip(szMessage,APP_TITLE);
	return true;
}

//��ȡ�����б�
void CMainFrame::OnGetRoomList()
{
	//��ȡע���룬ͨ��ע����ȡ������ȡ�������򵯳�����ע��������벢д�뵽ע���
	//CString strRegKey;
	//CString strLicense;
	//CRegKey LicenseKey;

	//strRegKey.Format(TEXT("%s"),REG_LICENSE);
	////��ע���
	//LicenseKey.Open(HKEY_CURRENT_USER,strRegKey);
	//if (LicenseKey == NULL)
	//{
	//	//MessageBox("������ע����ע�ᣡ");
	//	RegKeyDlg regdlg;
	//	
	//	regdlg.DoModal();
	//	
	//	//����ע����ַ�		
	//	strLicense.Format(TEXT("%s"),regdlg.m_szRegCode);

	//	if(strLicense.GetLength() != 39)
	//	{
	//		AfxMessageBox("ע�����ʽ�������ȡ��ȷע���룡");
	//
	//		DestroyWindow();
	//		return;
	//	}
	//	
	//	LicenseKey.Create(HKEY_CURRENT_USER,strRegKey);
	//	LicenseKey.SetStringValue(TEXT("ComputerKey"),strLicense);
	//	
	//	//AfxMessageBox(strLicense);
	//	
	//}
	//else
	//{
	//	//LicenseKey.DeleteSubKey(LPCTSTR lpszSubKey);
	//	///////ע������/////////
	//	CString activationKey =  _bstr_t("");	
	//	CString computerKey =  _bstr_t("");

	//	////��ȡע����
	//
	// 	TCHAR szBuffer[100];
	// 	ULONG uBufferLength=sizeof(szBuffer);
	// 	LONG uErrorCode=LicenseKey.QueryStringValue(TEXT("ComputerKey"),szBuffer,&uBufferLength);
	// 	if (uErrorCode==ERROR_SUCCESS)
	//	{
	//		computerKey.Format(TEXT("%s"),szBuffer);
	//		//AfxMessageBox(strRegKey);
	//	}
	//	
	//	//LicenseKey.Close();
	//	////ָ�������룬��ʹ��ԭ�е�ע��������ɵ�
	//	CString computerID = coreGetCode();  
	//	bool needsActivation = false;
	//	CString errorMsg = _bstr_t(""); 
	//	//CString *errorMsg = _bstr_t("bzwgame");
	//	LicenseValidator CheckLicense;

	//	bool checked = false;
	//	checked = CheckLicense.ValidateLicense(activationKey, computerKey, computerID, needsActivation, errorMsg);

	//	if (!checked)
	//	{
	//		//AfxMessageBox("ע������󣡣���");
	//		//MessageBox((LPCTSTR)errorMsg);
	//		//	DestroyWindow();
	//		//	return 0;
	//		LicenseKey.DeleteValue(TEXT("ComputerKey"));

	//		RegKeyDlg regdlg;
	//	
	//		regdlg.DoModal();
	//	
	//		//����ע����ַ�		
	//		strLicense.Format(TEXT("%s"),regdlg.m_szRegCode);

	//		if(strLicense.GetLength() != 39)
	//		{
	//			AfxMessageBox("ע�����ʽ�������ȡ��ȷע���룡");
	//
	//			DestroyWindow();
	//			return;
	//		}		
	//	
	//		LicenseKey.SetStringValue(TEXT("ComputerKey"),strLicense);			
	//	}
	//}

	//LicenseKey.Close();

	//������Ϣ
	g_Service.UpdateComDLLList(&m_wndView.m_ServiceControl.m_InstallList);
	g_Service.UpdateServiceInfo(&m_wndView.m_ServiceControl.m_StartList);

	//��ʾ����
	//ShowWindow(SW_SHOWMINIMIZED);//SW_SHOWMINIMIZED);//SW_SHOWMAXIMIZED);
	//SetForegroundWindow();
	//AfxMessageBox("Get room list!");

	return;
}

LRESULT CMainFrame::OnCreateTray(WPARAM wp, LPARAM lp)
{
#define APP_TITLEe "GServer"
	m_TrayIcon.SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME),APP_TITLE,TRUE);
	return 0;
}

//void CMainFrame::OnTimer(UINT nIDEvent)
//{
//	if(nIDEvent == 1)
//	{
//		if(!checkLicense())
//		{
//			PostQuitMessage(0);
//			ExitProcess(0);
//			return;
//		}
//	}
//}