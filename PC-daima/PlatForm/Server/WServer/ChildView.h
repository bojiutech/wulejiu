#pragma once
#include "ServiceControl.h"

//��ͼ������
class CChildView : public CWnd
{
	//�ؼ�����
public:
	CServiceControl							m_ServiceControl;						//�������

	//��������
public:
	//���캯��
	CChildView();
	//��������
	virtual ~CChildView();

	DECLARE_MESSAGE_MAP()

	//���غ���
protected:
	//��ʼ����������
	virtual BOOL PreCreateWindow(CREATESTRUCT & cs);

	//��Ϣ����
protected:
	//�ػ�����
	afx_msg void OnPaint();
	//������Ϣ
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//λ����Ϣ
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

