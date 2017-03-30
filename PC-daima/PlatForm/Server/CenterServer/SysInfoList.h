#pragma once

//������ʾ��
class COutputDisplay
{
public:
	COutputDisplay(){};
	virtual ~COutputDisplay(){};
	enum ErrorLevel 
	{//������ʾʱ����Ϣ����
		Message,//��ͨ��Ϣ
		Success, //ִ�гɹ�
		GeneralWarn,
		FatalWarn,
		GeneralError,
		FatalError,
	};
public:
	//���
	virtual BOOL PutLine(ErrorLevel eLevel,LPCSTR pszOutput){return FALSE;};
	//�õ��������͵�����
	//pszOut��������������ݣ��ַ������ȱ������20
	static void GetErrorLevelString(ErrorLevel eLevel,char* pszOut)
	{
		ASSERT(eLevel<=FatalError);
		static char szDesc[6][12]={"��Ϣ","ִ�гɹ�","��ͨ����","���ؾ���","��ͨ����","���ش���"};
		lstrcpy(pszOut,szDesc[(int)eLevel]);
	};
};

/////////////////////////////////////////////////////////////////////////////
// CSysInfoList window
class CSysInfoList : public CListCtrl
{
// Construction
public:
	CSysInfoList();

// Attributes
public:
	CImageList m_cImageListSmall;
// Operations
public:
	//���ô˺�����ʾ��Ϣ
	void DisplayMsg(int eMsgLevel,LPCTSTR szDisplay);
	void SetMaxItems(int nMaxItem);
protected:
	//��ʼ���б�ͷ
	void InitListCtrlCols(void);
	//��ʼ��ͼ���б�
	void InitImageList(void);
	//�����ʾ��Ŀ
	int m_nShowMaxLine;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSysInfoList)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSysInfoList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSysInfoList)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
