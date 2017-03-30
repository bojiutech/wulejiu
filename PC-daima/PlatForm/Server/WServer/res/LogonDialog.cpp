#include "Stdafx.h"
#include "MainFrm.h"
#include "LogonDialog.h"
#include "AccessDialog.h"

BEGIN_MESSAGE_MAP(CLogonDialog, CDialog)
	ON_BN_CLICKED(IDC_SETTING, OnBnClickedSetting)
END_MESSAGE_MAP()

//���캯��
CLogonDialog::CLogonDialog(CWnd * pParent)	: CDialog(IDD_LOGON, pParent)
{
}

//��������
CLogonDialog::~CLogonDialog()
{
}

//��ʼ������
BOOL CLogonDialog::OnInitDialog()
{
	__super::OnInitDialog();

	//��ʼ���ؼ�
	GetDlgItem(IDC_NAME)->SetWindowText(g_Service.m_Info.m_szName);
	if (g_Service.m_Info.m_uLogonTimes>0) GetDlgItem(IDC_SETTING)->EnableWindow(FALSE);

	return TRUE;
}

//ȷ������
void CLogonDialog::OnOK()
{
	//Ч���Ƿ�ע��
	if (g_Service.m_Info.m_szServerGUID[0]==0)
	{
		AFCGetTrayIcon().ShowBalloonTip(TEXT("������δ����Ȩʹ�ã��밴ϵͳ [����] ��ť��������Ȩ���к���"),APP_TITLE);
		return;
	}
	if (g_Service.m_Info.m_szLogonAddr[0]==0)
	{
		AFCGetTrayIcon().ShowBalloonTip(TEXT("û�����õ�½��������ַ���밴ϵͳ [����] ��ť�����õ�½��������ַ"),APP_TITLE);
		return;
	}

	//��ȡ����
	GetDlgItem(IDC_NAME)->GetWindowText(m_strName);
	GetDlgItem(IDC_PASS)->GetWindowText(m_strPass);

	//Ч������
	if ((m_strName.GetLength()==0)||(m_strPass.GetLength()==0))
	{
		AFCGetTrayIcon().ShowBalloonTip(TEXT("�������½���ֺ����룬���ܰ����Ƿ��ַ�����ϵͳ�����ַ�"),APP_TITLE);
		GetDlgItem(IDC_NAME)->SetFocus();
		return;
	}

	__super::OnOK();
}

//��Ȩ����
void CLogonDialog::OnBnClickedSetting()
{
	CAccessDialog Access;
	Access.SetServerInfo(g_Service.m_Info.m_szServerGUID,g_Service.m_Info.m_szLogonAddr);
	if (Access.DoModal()!=IDOK) return;
	Access.GetServerInfo(g_Service.m_Info.m_szServerGUID,g_Service.m_Info.m_szLogonAddr);

	return;
}

