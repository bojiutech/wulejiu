#pragma once

//#ifndef CTRAYICON_H_2003
//#define CTRAYICON_H_2003
const UINT WM_CREATETRAYBAR =  RegisterWindowMessage(_T("TaskbarCreated"));
//������ͼ����
class CTrayIcon
{
	//��������
protected:
	NOTIFYICONDATA				m_NotifyData;			//֪ͨ��Ϣ

	//��������
public:
	//���캯��
	explicit CTrayIcon(UINT uID);
	//��������
	~CTrayIcon();
	//������Ϣ������
	void SetNotifyWnd(CWnd * pNotifyWnd, UINT uMessage);

	//���ܺ���
public:
	//����ͼ��
	BOOL SetIcon(HICON hIcon, LPCTSTR szTip,BOOL bForce=FALSE);
	//��ʾ��ʾ
	BOOL ShowBalloonTip(LPCTSTR szMesssage, LPCTSTR szTitle, UINT uTimeout=5, DWORD dwInfoFlags=NIIF_INFO);
};

//#endif 