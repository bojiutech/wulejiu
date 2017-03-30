#include "StdAfx.h"
#include "AFCLoader.h"
#include "AccessDialog.h"
#include "MainFrm.h"

BEGIN_MESSAGE_MAP(CAccessDialog, CDialog)
END_MESSAGE_MAP()

//���캯��
CAccessDialog::CAccessDialog() : CDialog(IDD_ACCESS_SET)
{
	memset(m_szServerIP,0,sizeof(m_szServerIP));
	memset(m_szServerGUID,0,sizeof(m_szServerGUID));
}

//��������
CAccessDialog::~CAccessDialog()
{
}

//��ʼ������
BOOL CAccessDialog::OnInitDialog()
{
	__super::OnInitDialog();
	
	//���ÿؼ�
	((CEdit *)GetDlgItem(IDC_ACCESS_NUM))->LimitText(36);
	((CEdit *)GetDlgItem(IDC_LOGIN_ADDR))->LimitText(50);
	GetDlgItem(IDC_LOGIN_ADDR)->SetWindowText(m_szServerIP);
	GetDlgItem(IDC_ACCESS_NUM)->SetWindowText(m_szServerGUID);

	return TRUE;
}

//ȷ������
void CAccessDialog::OnOK()
{
	//��ȡ����
	GetDlgItem(IDC_LOGIN_ADDR)->GetWindowText(m_szServerIP,sizeof(m_szServerIP));
	GetDlgItem(IDC_ACCESS_NUM)->GetWindowText(m_szServerGUID,sizeof(m_szServerGUID));

	//Ч������
	if ((lstrlen(m_szServerGUID)==0)||(lstrlen(m_szServerIP)==0))///if ((lstrlen(m_szServerGUID)!=36)||(lstrlen(m_szServerIP)==0))
	{
		AFCGetTrayIcon().ShowBalloonTip(TEXT("��������������Ȩ���кź͵�½��������ַ���� [ȡ��] ��ťȡ������"),APP_TITLE);
		GetDlgItem(IDC_ACCESS_NUM)->SetFocus();
		return;
	}

	__super::OnOK();
}

//������Ϣ
bool CAccessDialog::SetServerInfo(TCHAR * szServerGUID, TCHAR * szServerIP)
{
	//��ʼ������
	memset(m_szServerIP,0,sizeof(m_szServerIP));
	memset(m_szServerGUID,0,sizeof(m_szServerGUID));

	//��������
	if ((szServerIP!=NULL)&&(lstrlen(szServerIP)<=50)) lstrcpy(m_szServerIP,szServerIP);
	if ((szServerGUID!=NULL)&&(lstrlen(szServerGUID)<=36)) lstrcpy(m_szServerGUID,szServerGUID);

	//��ʾ����
	if (GetSafeHwnd()!=NULL)
	{
		GetDlgItem(IDC_LOGIN_ADDR)->SetWindowText(m_szServerIP);
		GetDlgItem(IDC_ACCESS_NUM)->SetWindowText(m_szServerGUID);
	}

	return true;
}

//��ȡ��Ϣ
bool CAccessDialog::GetServerInfo(TCHAR * szServerGUID, TCHAR * szServerIP)
{
	//д������
	if ((szServerIP!=NULL)&&(lstrlen(szServerIP)<=50)) lstrcpy(szServerIP,m_szServerIP);
	if ((szServerGUID!=NULL)&&(lstrlen(szServerGUID)<=36)) lstrcpy(szServerGUID,m_szServerGUID);

	return true;
}
