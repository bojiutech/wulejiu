#pragma once

/********************************************************************************************************/

//�����Ի�����
class CBaseDialog : public CDialog
{
	//��������
public:
	//���캯��
	explicit CBaseDialog(UINT uTemplate, CWnd * pParent=NULL);
	//��������
	virtual ~CBaseDialog();

	//���ܺ���
public:
	//��ȡ����
	bool SafeGetClientRect(UINT uID, CRect & ClientRect);
	//��ȡ����
	bool SafeGetClientRect(CWnd * pControlWnd, CRect & ClientRect);
	//�ƶ�����
	bool SafeMoveWindow(UINT uID, int x, int y, int iWidth, int iHeight);
	//�ƶ�����
	bool SafeMoveWindow(CWnd * pControlWnd, int x, int y, int iWidth, int iHeight);

	DECLARE_MESSAGE_MAP()
};

/********************************************************************************************************/

//���ط��������
class CServiceControl : public CBaseDialog
{
	//��������
public:
	CListCtrl				m_StartList;					//���������б�
	CListCtrl				m_InstallList;					//�Ѿ���װ������б�

	//�������� 
public:
	//���캯��
	CServiceControl();
	//��������
	virtual ~CServiceControl();

	//���غ���
public:
	//DDX/DDV ֧��
	virtual void DoDataExchange(CDataExchange * pDX); 
	//��ʼ������
	virtual BOOL OnInitDialog();

	//��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()

	//��Ϣ����
public:
	//λ�ñ仯����
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//������Ϸ���
	afx_msg void OnBnClickedSetCom();
	//������Ϸ����
	afx_msg void OnBnClickedStart();
	//ֹͣ��Ϸ����
	afx_msg void OnBnClickedStop();
	//ˢ����Ϸ����б�
	afx_msg void OnBnClickedReLoad();
	//������Ϸ���
	afx_msg void OnBnClickedUpdateCom();
	//��װ��Ϸ�����
	afx_msg void OnBnClickedSetup();
	//�޸���Ϸ���
	afx_msg void OnBnClickedMotif();

	afx_msg void OnBnClickedRemove();
	//�������з���
	afx_msg void OnBnClickedStartAll();
	//ֹͣ���з���
	afx_msg void OnBnClickedStopAll();

	afx_msg void OnBnClickedDelete();

	afx_msg void OnBnClickedChange();

	afx_msg void OnBnClickedInfo();

	afx_msg void OnBnClickedManage();

	afx_msg void OnBnClickedReloadRoomlist();

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

/********************************************************************************************************/


