// SetDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SetDlg.h"
#include ".\setdlg.h"


// CSetDlg �Ի���

IMPLEMENT_DYNAMIC(CSetDlg, CDialog)
CSetDlg::CSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetDlg::IDD, pParent)
	, m_edit1(_T("4010"))
	, m_edit7(_T("5"))
{
}

CSetDlg::~CSetDlg()
{
}

void CSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_EDIT7, m_edit7);
}


BEGIN_MESSAGE_MAP(CSetDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CSetDlg ��Ϣ�������

void CSetDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AfxMessageBox("�������ƵĹ���ͳһ������������");
}
