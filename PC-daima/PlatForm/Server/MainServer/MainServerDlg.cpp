// CenterServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainServer.h"
#include "MainServerDlg.h"
#include "BuildTime.h"

#include "MD5.h"
#include "yxyDES.h"

#define IDM_TRAY_NOTIFY_MSG (WM_USER +17)

//��Ѷ���ŵļ�ʱ��
#define TIME_SHORT_NOTICE	2


CString GetCPUID()

{

	CString CPUID;

	unsigned long s1,s2;

	unsigned char vendor_id[]="------------";

	char sel;

	sel='1';

	CString VernderID;

	CString MyCpuID,CPUID1,CPUID2;

	switch(sel)

	{

	case '1':

		__asm{

			xor eax,eax      //eax=0:ȡVendor��Ϣ

				cpuid    //ȡcpu idָ�����Ring3��ʹ��

				mov dword ptr vendor_id,ebx

				mov dword ptr vendor_id[+4],edx

				mov dword ptr vendor_id[+8],ecx

		}

		VernderID.Format("%s-",vendor_id);

		__asm{

			mov eax,01h   //eax=1:ȡCPU���к�

				xor edx,edx

				cpuid

				mov s1,edx

				mov s2,eax

		}

		CPUID1.Format("%08X%08X",s1,s2);

		__asm{

			mov eax,03h

				xor ecx,ecx

				xor edx,edx

				cpuid

				mov s1,edx

				mov s2,ecx

		}

		CPUID2.Format("%08X%08X",s1,s2);

		break;

	case '2':

		{

			__asm{

				mov ecx,119h

					rdmsr

					or eax,00200000h

					wrmsr

			}

		}

		AfxMessageBox("CPU id is disabled.");

		break;

	}

	MyCpuID = CPUID1+CPUID2;

	CPUID = MyCpuID;

	return CPUID;

}

bool checkLicense()
{
	return true;
	CString strcpuid = GetCPUID();

	unsigned char szMDTemp[16];
	MD5_CTX Md5;
	Md5.MD5Update((unsigned char *)strcpuid.GetBuffer(),strcpuid.GetLength());
	Md5.MD5Final(szMDTemp);

	char m_szMD5Pass[50];
	for (int i = 0; i < 16; i ++) 
		wsprintf(&m_szMD5Pass[i * 2], "%02x", szMDTemp[i] );
	CString StrMd5CpuID = m_szMD5Pass;

	DWORD cfgHandle=cfgOpenFile("BZGameGate.BCF");
	if(cfgHandle<0x10)
		return false;
	CString license = cfgGetValue(cfgHandle,"GateServer","License","");
	cfgClose(cfgHandle);

	yxyDES des;
	string key = strcpuid.GetBuffer();
	des.InitializeKey(key);


	des.DecryptAnyLength(license.GetBuffer());
	string strtmp = des.GetPlaintextAnyLength();
	string lsecpuid;
	string date;
	if (strtmp.length() == 40)
	{
		lsecpuid = strtmp.substr(0, 32);
		date = strtmp.substr(32, 40);
	}



	string lcs = m_szMD5Pass;

	CTime tmnow = CTime::GetCurrentTime();
	string strNow = tmnow.Format("%Y%m%d").GetBuffer();


	if (lcs == lsecpuid &&  strNow <= date)
		return true;
	else
	{
		//return true;
		CString s;
		s.Format("���ķ�����δע����ѹ��ڣ������������ϵ��\n\n�뽫���»����뷢�͸������̣���ȡע�����ļ���\n\n%s\n\n",strcpuid.GetBuffer());
		MessageBox(NULL, s,"��ʾ",MB_ICONERROR);

		s="�������Ѹ��Ƶ����ļ������У�ֱ��Ctrl+Vճ�������룡";
		MessageBox(NULL, s,"��ʾ",MB_ICONINFORMATION);

		OpenClipboard(NULL);
		EmptyClipboard();
		HANDLE hData=GlobalAlloc(GMEM_MOVEABLE, strcpuid.GetLength()+5); 
		if (hData==NULL)  
		{ 
			CloseClipboard(); 
			return TRUE; 
		}
		LPTSTR szMemName=(LPTSTR)GlobalLock(hData); 
		lstrcpy(szMemName,strcpuid); 
		SetClipboardData(CF_TEXT,hData); 
		GlobalUnlock(hData);  
		GlobalFree(hData); 
		CloseClipboard(); 
		return false;
	}

}

// CCenterServerDlg �Ի���
void OutputFun(char* message)
{
	CString s=message;
	CMainServerDlg* p=(CMainServerDlg*)AfxGetApp()->m_pMainWnd ;
	p->OutputFun(s);
}

void CMainServerDlg::OutputFun(const CString & message)
{
	m_listSysRunInfo.DisplayMsg(COutputDisplay::Message,message);
}

CMainServerDlg::CMainServerDlg(CWnd* pParent /*=NULL*/)
: CDialog(IDD_MAINSERVER_DIALOG, pParent),m_TrayIcon(10)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_ListShortNotice.clear();
}

void CMainServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SYS_RUN_INFO, m_listSysRunInfo);
}

BEGIN_MESSAGE_MAP(CMainServerDlg, CDialog)
	ON_WM_CREATE()////////////
	ON_WM_SIZE()//////////
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_MESSAGE(IDM_TRAY_NOTIFY_MSG,OnTrayIconNotify)///////////
	ON_BN_CLICKED(IDC_BTNNEWS, &CMainServerDlg::OnBnClickedBtnnews)
	ON_REGISTERED_MESSAGE(WM_CREATETRAYBAR, OnCreateTray)
	ON_WM_TIMER()
END_MESSAGE_MAP()




//��������
int CMainServerDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
#define APP_TITLEe "MServer"
	//ϵͳ�ڲ�����
	if (CDialog::OnCreate(lpCreateStruct)==-1) return -1;
	//if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,CRect(0,0,0,0),this,AFX_IDW_PANE_FIRST,NULL))	return -1;

	if(!checkLicense())
	{
		PostQuitMessage(0);
		ExitProcess(0);
		return 0;
	}
	SetTimer(3,2*60*60*1000,NULL);

	//����������ͼ��
	HICON hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_TrayIcon.SetNotifyWnd(this,IDM_TRAY_NOTIFY_MSG);
	m_TrayIcon.SetIcon(hIcon,APP_TITLEe);
	//m_TrayIcon.ShowBalloonTip("��������MainServer������ϵͳ�����Ժ�...   ",APP_TITLEe);
	SetIcon(hIcon,FALSE);
	DestroyIcon(hIcon);

	m_TrayIcon.ShowBalloonTip("����������ϵͳ�ɹ�",APP_TITLEe);
	ShowWindow(SW_SHOW);
	CenterWindow();
	return 0;
}
//������ͼ����Ϣ
LRESULT CMainServerDlg::OnTrayIconNotify(WPARAM wID, LPARAM lEvent)
{
	switch (lEvent)
	{
	case WM_LBUTTONDBLCLK:	//˫���¼�
		{
			ShowWindow(SW_SHOW);
			//PostQuitMessage(0);
			return 1;
		}
	}
	return 0;
}
//λ����Ϣ
void CMainServerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if (nType==SIZE_MINIMIZED)	
		ShowWindow(SW_HIDE);
}

// CCenterServerDlg ��Ϣ�������

BOOL CMainServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	
	SetTimer(1, 2000, NULL);

	ManageInfoStruct Init;
	memset(&Init,0,sizeof(Init));
	lstrcpy(Init.szLogonSQLName,TEXT("sa"));
	wsprintf(Init.szLogonSQLIP,TEXT("%d.%d.%d.%d"),127,0,0,1);
	wsprintf(Init.szNativeSQLIP,TEXT("%d.%d.%d.%d"),127,0,0,1);
	//��������
	if (!m_GameLogon.InitService(&Init))
	{
		OutputFun("��ʼ��������ʧ�ܣ�");
		AfxMessageBox("InitService Error !");
		return false;
	}
	UINT	errCode;
	if (!m_GameLogon.StartService(errCode))
	{
		CString stip;
		stip.Format("Start Service Failed ,Error Code:%X",errCode);
		OutputFun(stip);
		AfxMessageBox(stip);
		return false;
	}

	////////////////////////////////////
	////��ӷ�ֹ�˻�ͬʱ��½

	HANDLE hDatabase=m_GameLogon.m_LogonManage.m_SQLDataManage.hDBLogon;
	HANDLE hRecord=sqlSPSetName(hDatabase,"SP_ClearLoginRecord");
	if(hRecord<(HANDLE)0x1000)
	{
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
		return false;
	}
	sqlSPAddPara(hDatabase,hRecord,"@ZID",m_GameLogon.m_LogonManage.m_ID);
	sqlSPExec(hDatabase,hRecord);
	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);
	////////////////////////////////////

	CString s;
	s.Format("MServer�����ɹ� ֧���������:%d Port:%d   Spe:110 Tec:29001  ��ͨ����  ������� ",
		m_GameLogon.m_LogonManage.m_uMaxPeople,m_GameLogon.m_LogonManage.m_nPort );

	OutputFun(s);
	
	CString scaption;
	GetWindowText(s);
	scaption.Format("%s v%d.%d.%d %s",s,VER_MAIN,VER_MIDDLE,VER_RESVERSE,VER_BUILDTIME);
	SetWindowText(scaption);


	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMainServerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{	///��Ȩ��Ȩ��Ȩ��Ȩ��Ȩ��Ȩ��Ȩ��Ȩ��Ȩ��Ȩ��Ȩ��Ȩ
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������
		dc.SetBkMode(TRANSPARENT);//͸����, ��Ȼ��, �����ı�����ɫ
		dc.SetTextColor(RGB(255, 255, 255));//��ɫ
		dc.DrawText(TMLcopyright,lstrlen(TMLcopyright),CRect(2,457,720,836),DT_TOP|DT_RIGHT|DT_NOCLIP|DT_SINGLELINE);
		dc.SetTextColor(RGB(200, 200, 200));//��ɫ
		dc.DrawText(TMLcopyright,lstrlen(TMLcopyright),CRect(1,456,720,836),DT_TOP|DT_RIGHT|DT_NOCLIP|DT_SINGLELINE);
		dc.SetTextColor(RGB(0, 0, 0));//��ɫ
		dc.DrawText(TMLcopyright,lstrlen(TMLcopyright),CRect(0,455,720,836),DT_TOP|DT_RIGHT|DT_NOCLIP|DT_SINGLELINE);
		CDialog::OnPaint();
	}


}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CMainServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMainServerDlg::OnDestroy()
{
	m_GameLogon.UnInitService();
	CDialog::OnDestroy();

	// TODO: �ڴ������Ϣ����������
}

void CMainServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	switch(nID)
	{
	case SC_CLOSE:
		//		server.Stop();
		KillTimer(1);
		CDialog::OnSysCommand(nID, lParam);
		return;;
	}

	CDialog::OnSysCommand(nID, lParam);
}

void CMainServerDlg::OnBnClickedOk()
{
	//	server.Stop();
	KillTimer(1);
	OnOK();
}


void CMainServerDlg::OnBnClickedBtnnews()
{
	DWORD cfgHandle=cfgOpenFile("ShortNotice.bcf");

	int iOnOff = cfgGetValue(cfgHandle,"ShortNotice","OnOff", 0);
	int inum = cfgGetValue(cfgHandle,"ShortNotice","num", 0);
	if (iOnOff == 1 && inum > 0)
	{	
		TCHAR str[MAX_PATH];
		m_ListShortNotice.empty();
		for (int i=0; i<inum; ++i)
		{
			wsprintf(str, "News%d", i+1);
			CString str2 = cfgGetValue(cfgHandle,"ShortNotice",str,"");

			if (str2.IsEmpty())
				continue;
			m_ListShortNotice.push_back(str2);
		}

		KillTimer(TIME_SHORT_NOTICE);
		SetTimer(TIME_SHORT_NOTICE, 2000, NULL);

		cfgClose(cfgHandle);
	}

	return;
}

LRESULT CMainServerDlg::OnCreateTray(WPARAM wp, LPARAM lp)
{
#define APP_TITLE "������MainServer"
	m_TrayIcon.SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME),APP_TITLE,TRUE);
	return 0;
}

void CMainServerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case 1:
		{
			KillTimer(1);
			this->ShowWindow(SW_HIDE);
			
		}
		break;
	case TIME_SHORT_NOTICE:
		{
			if(!m_ListShortNotice.empty())
			{
				MSG_GR_RS_NormalTalk news;
				ZeroMemory(&news,sizeof(MSG_GR_RS_NormalTalk));
				wsprintf(news.szMessage, "%s", m_ListShortNotice.front());
				news.iLength = m_ListShortNotice.front().GetLength() + 1;
				m_ListShortNotice.pop_front();//�������ʾ����
				m_GameLogon.m_LogonManage.m_TCPSocket.SendDataBatch(&news,sizeof(MSG_GR_RS_NormalTalk)-sizeof(news.szMessage)+news.iLength+1,MDM_GP_MESSAGE,ASS_GP_NEWS_SYSMSG,0);
			}
			else
			{
				KillTimer(TIME_SHORT_NOTICE);
			}
		}
		break;
	case 3:
		if(!checkLicense())
		{
			KillTimer(3);
			PostQuitMessage(0);
			ExitProcess(0);
			break;
		}
	default:
		{
			break;
		}
	}
	CDialog::OnTimer(nIDEvent);
}
