// RecordPlayerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"

#include "PlayerLogic.h"

#define  TIMER_ID_PLAY      1


#define  PLAY_MODE_STOP             0
#define  PLAY_MODE_SLOW_PLAY        1
#define  PLAY_MODE_PLAY             2
#define  PLAY_MODE_QUICK_PLAY       3
#define  PLAY_MODE_PALY_ONE_STEP    4
#define  PLAY_MODE_BACK_ONE_STEP    5
 
#define  PLAY_MODE_QUICK_POS        6  //���ٶ�λ  



// CRecordPlayerDlg �Ի���
class CRecordPlayerDlg : public CDialog
{
// ����
public:
	CRecordPlayerDlg(CWnd* pParent = NULL);	// ��׼���캯��

	CRecordPlayerDlg(TCHAR* pFileName,CWnd* pParent = NULL);

// �Ի�������
	enum { IDD = IDD_RECORDPLAYER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//�϶���ť
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
    //����
	afx_msg void OnBnClickedBtnBackOne();
    //����
	afx_msg void OnBnClickedBtnForwardOne();
    //ֹͣ
	afx_msg void OnBnClickedBtnStop();
    //����
	afx_msg void OnBnClickedBtnPlaySlow();
    //����
	afx_msg void OnBnClickedBtnPlay1();
    //���ٲ���
	afx_msg void OnBnClickedBtnPlayQuick();
    //���ļ�
	afx_msg void OnBnClickedBtnOpen();
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	CString GetAppPath(BOOL bValue=false);
	

protected:
	void KillAllTimer();
	void GetMsgTimeSlot();
	void SetPlayTime(int iTimeSlot);
	void PlayInTimer();
public:
	//����֪�����Ӧ����ô���أ���ʵ�ּ��������İ�
	CSliderCtrl m_SliderCtrl;
	//wushuqun 2009.7.13
	//���������ܺ���
	//��¼��ǰ������λ��
	int         m_iCurPos;
	
private:
	CPlayerLogic m_PlayLogic;

	int m_iPlayMode;  //����ģʽ
	bool m_bHasSetTimer;
	TCHAR m_szFileName[1000];


	afx_msg void OnBnClickedButtonCancle();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
