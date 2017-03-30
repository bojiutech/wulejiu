// SysInfoList.cpp : implementation file
//

#include "stdafx.h"
#include "SysInfoList.h"

#include "resource.h"



/////////////////////////////////////////////////////////////////////////////
// CSysInfoList

CSysInfoList::CSysInfoList()
{
	m_nShowMaxLine = 1000;
}

CSysInfoList::~CSysInfoList()
{
}


BEGIN_MESSAGE_MAP(CSysInfoList, CListCtrl)
	//{{AFX_MSG_MAP(CSysInfoList)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSysInfoList message handlers

void CSysInfoList::PreSubclassWindow() 
{
	CListCtrl::PreSubclassWindow();

	//���ÿؼ�������
	DWORD dwStyle = GetWindowLong(GetSafeHwnd(),GWL_STYLE);
	dwStyle=(dwStyle& ~LVS_TYPEMASK)|WS_CHILD | LVS_REPORT;//|LVS_NOCOLUMNHEADER;
	SetWindowLong(GetSafeHwnd(),GWL_STYLE,dwStyle);

	InitListCtrlCols();
	InitImageList();

	DeleteAllItems();
	
}

void CSysInfoList::InitListCtrlCols(void)
{
	//�������У�0����Ϣ���ͣ�1������ʱ�䣬2����Ϣ����
	CRect rect;
	GetClientRect(&rect);
	int nColInterval = rect.Width()/100;

	InsertColumn(0, _T("��Ϣ����"), LVCFMT_LEFT, nColInterval*15);
	InsertColumn(1, _T("ʱ��"), LVCFMT_LEFT, nColInterval*28);
	InsertColumn(2, _T("��Ϣ����"), LVCFMT_LEFT, rect.Width()-41*nColInterval);

}

void CSysInfoList::InitImageList(void)//��ʼ��ͼ���б�
{
	//����listctrl ��ͼ��
	// Create 256 color image lists
	HIMAGELIST 	hList = ImageList_Create(16, 16, ILC_COLOR8 | ILC_MASK, 8, 1);
	m_cImageListSmall.Attach(hList);
	// Load the large icons
	//CBitmap cBmp;
	//cBmp.LoadBitmap(IDB_BMP_MSG_STATUS);
	//m_cImageListSmall.Add(&cBmp, RGB(255,0, 255));
	//cBmp.DeleteObject();
	//SetImageList(&m_cImageListSmall, LVSIL_SMALL);
}
void CSysInfoList::SetMaxItems(int nMaxItem)
{
	m_nShowMaxLine = nMaxItem;
}

void CSysInfoList::DisplayMsg(int eLevel,LPCTSTR szDisplay)
{
	// ʹ�� lvitem ��������
	///////if(!IsWindow(this->m_hWnd ))return;
	LVITEM lvi;
	CString strItem;
	char szMsgType[20];
	COutputDisplay::GetErrorLevelString ((COutputDisplay::ErrorLevel)eLevel,szMsgType);
	int iItemCount=GetItemCount();
	if(iItemCount>1000) DeleteAllItems();
	//int iLevel=eLevel;
	//�����һ��
	lvi.mask =  LVIF_IMAGE | LVIF_TEXT;
	strItem.Format(szMsgType);
	
	lvi.iItem = iItemCount;
	lvi.iSubItem = 0;
	lvi.pszText = szMsgType;//(LPTSTR)(LPCTSTR)(strItem);
	lvi.iImage = eLevel;
	InsertItem(&lvi);
	
	//���õ�һ��
	strItem.Format(_T("%s"), CTime::GetCurrentTime().Format(_T("%Y/%m/%d %H:%M:%S")));
	lvi.iSubItem =1;
	lvi.pszText = (LPTSTR)(LPCTSTR)(strItem);
	SetItem(&lvi);
	
	//���õ�һ��
	lvi.iSubItem =2;
	lvi.pszText = (LPTSTR)szDisplay;
	SetItem(&lvi);
	CSize size(-10,40);		
	Scroll(size);

	//���������Χ��ɾ����һ��
	if(GetItemCount()>m_nShowMaxLine)
		for(int i=0;i<10;i++)
			DeleteItem(0);
}
