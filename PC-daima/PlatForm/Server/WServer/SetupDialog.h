#pragma once
#include "afxwin.h"
// CSetupDialog dialog

class CSetupDialog : public CDialog
{
	DECLARE_DYNAMIC(CSetupDialog)

public:
	CSetupDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetupDialog();

// Dialog Data
//	enum { IDD = IDD_SETGAME_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	UINT serInfoID;
public:
	UINT nameID;
public:
	UINT deskPeople;
public:
	UINT supportType;
public:
	UINT sver;
public:
	CString gameName;//��Ϸ����
public:
	CString tableDbName;					//���ݿ������
public:
	CString  dllFileName;					//�ļ�����
public:
	CString writer;						//���������
public:
	CString dllNote;						//��ע��Ϣ
public:
	// //���ID ServerInfoID
	CEdit editSiid;
};
