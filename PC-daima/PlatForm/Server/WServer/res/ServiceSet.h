#pragma once

#include "StdAfx.h"
#include "Resource.h"
#include "ServiceManage.h"

//������������
class CServiceSet : public CDialog
{
	//��������
protected:
	UINT								m_KindID;						//���� ID
	TCHAR								m_szServiceIP[16];				//���� IP
	SC_ServiceInfoStruct				m_ServiceInfo;					//�������
	SC_GameRoomInitStruct				m_GameRoomInit;					//��ʼ������

	//�ؼ�����
public:
	CComboBox							m_ComType;						//��Ϸ����
	CComboBox							m_GameKind;						//�ҽ�����
	CServiceManage						* m_pServiceManage;				//�������
	CIPAddressCtrl						m_CenterSQLIP;					//���ķ����� IP
	CIPAddressCtrl						m_LogonSQLIP;					//��½������ IP
	CIPAddressCtrl						m_NativeSQLIP;					//���ط����� IP

	//�������� 
public:
	//���캯��
	CServiceSet(SC_ServiceInfoStruct & ServiceInfo, CServiceManage * pServiceManage);
	//��������
	virtual ~CServiceSet();

	DECLARE_MESSAGE_MAP()

	//���غ���
protected:
	//DDX/DDV ֧��
	virtual void DoDataExchange(CDataExchange * pDX);
	//��ʼ������
	virtual BOOL OnInitDialog();
	//ȷ������
	virtual void OnOK();

	//���ܺ���
public:
	//��ȡ���ò���
	SC_GameRoomInitStruct * GetGameRoomConfigData() { return &m_GameRoomInit; }
};
