#pragma once

#include "afxcmn.h"


// CAddRoomDialog dialog

class CAddRoomDialog : public CDialog
{
	DECLARE_DYNAMIC(CAddRoomDialog)

public:
	CAddRoomDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddRoomDialog();

	virtual void OnFinalRelease();

// Dialog Data
	//enum { IDD = IDD_DLL_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	// ����ID
	int m_roomID;
public:
	CString m_szGameRoomName;
public:
	// ��½���ݿ�IP
	CIPAddressCtrl m_LogonSQLIP;
public:
	// �������ݿ�IP
	CIPAddressCtrl m_SQLIP;
public:
	// �������ݿ�IP
	CIPAddressCtrl m_NativeSQLIP;
public:
	//��Ϸ����
	int m_uComType;
public:
	// �����˿�
	int m_uListenPort;
public:
	// �ҽ�����
	int m_uKindID;
public:
	// ������
	int m_uDeskCount;
public:
	// �������
	int m_uMaxPeople;
public:
	// ��������
	int m_uBasePoint;
public:
	// ���ٷ���
	int m_uLessPoint;
public:
	// �������
	unsigned int m_dwRoomRule;
};
