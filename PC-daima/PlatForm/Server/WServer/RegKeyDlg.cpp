// RegKeyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "resource.h"
#include "RegKeyDlg.h"


// RegKeyDlg �Ի���

IMPLEMENT_DYNAMIC(RegKeyDlg, CDialog)

RegKeyDlg::RegKeyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(RegKeyDlg::IDD, pParent)
{
	m_szRegCode[0] = 0;

}

RegKeyDlg::~RegKeyDlg()
{
}

void RegKeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REGCODE, m_RegCode);
}


BEGIN_MESSAGE_MAP(RegKeyDlg, CDialog)
	ON_BN_CLICKED(IDOK, &RegKeyDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &RegKeyDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// RegKeyDlg ��Ϣ�������

void RegKeyDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_RegCode.GetWindowText(m_szRegCode,sizeof(m_szRegCode))==0)
	{
		MessageBox("������ע���룡");
		GetDlgItem(IDC_REGCODE)->SetFocus();
		return;
	}

	if (strlen(m_szRegCode) != 39)
	{
		MessageBox("ע�����ʽ����ȷ�����������룡");
		GetDlgItem(IDC_REGCODE)->SetFocus();
		return;
	}

	OnOK();
}

void RegKeyDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}
