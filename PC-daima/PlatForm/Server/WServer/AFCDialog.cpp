#include "Stdafx.h"
#include "AFCDialog.h"
#include "AFCFunction.h"
#include "AFCResource.h"

//ʹ�öԻ������ֿռ�
using namespace AFC;
using namespace AFC::AFCDialog;
using namespace AFC::AFCResource;

BEGIN_MESSAGE_MAP(CAFCBaseDialog, CDialog)
	ON_WM_PAINT()
	ON_MESSAGE(WM_CTLCOLORSTATIC,OnControlColor)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CAFCSkinDialog, CAFCBaseDialog)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_SIZE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CAFCRgnDialog, CAFCBaseDialog)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

/*******************************************************************************************************/

//ͼ���С
#define BUTTON_WIDTH					21								//��ť��
#define BUTTON_HIGHT					21								//��ť��
#define TITLE_HIGHT						26								//�����

//��ť��ʶ
#define BST_CLOSE						0								//�رհ�ť
#define BST_RESTORE						1								//��ԭ��ť
#define BST_MIN							2								//��С����ť

//��ť״̬
#define BUT_EXIST						0x01							//��ť����
#define BUT_NORMAL						0x02							//��ť��ͨ
#define BUT_DISABLE						0x04							//��ť��ֹ
#define BUT_MAXSIZE						0x08							//��ť��ֹ

/*******************************************************************************************************/

//���캯��
CAFCBaseDialog::CAFCBaseDialog(UINT uTemplate, CWnd * pParent) : CDialog(uTemplate,pParent)
{
}

//��������
CAFCBaseDialog::~CAFCBaseDialog()
{
}

//��ȡ����
bool CAFCBaseDialog::SafeGetClientRect(UINT uID, CRect & ClientRect)
{
	CWnd * pControlWnd=GetDlgItem(uID);
	if ((pControlWnd!=NULL)&&(pControlWnd->GetSafeHwnd())) 
	{
		pControlWnd->GetClientRect(&ClientRect);
		return true;
	}
	ClientRect.SetRectEmpty();
	return false;
}

//��ȡ����
bool CAFCBaseDialog::SafeGetClientRect(CWnd * pControlWnd, CRect & ClientRect)
{
	if ((pControlWnd!=NULL)&&(pControlWnd->GetSafeHwnd())) 
	{
		pControlWnd->GetClientRect(&ClientRect);
		return true;
	}
	ClientRect.SetRectEmpty();
	return false;
}

//�ƶ�����
bool CAFCBaseDialog::SafeMoveWindow(UINT uID, int x, int y, int iWidth, int iHeight)
{
	CWnd * pControlWnd=GetDlgItem(uID);
	if ((pControlWnd!=NULL)&&(pControlWnd->GetSafeHwnd())) 
	{
		if ((iWidth<=0)||(iHeight<=0)) iWidth=0,iHeight=0;
		pControlWnd->MoveWindow(x,y,iWidth,iHeight);
		return true;
	}
	return false;
}

//�ƶ�����
bool CAFCBaseDialog::SafeMoveWindow(CWnd * pControlWnd, int x, int y, int iWidth, int iHeight)
{
	if ((pControlWnd!=NULL)&&(pControlWnd->GetSafeHwnd())) 
	{
		if ((iWidth<=0)||(iHeight<=0)) iWidth=0,iHeight=0;
		pControlWnd->MoveWindow(x,y,iWidth,iHeight);
		return true;
	}
	return false;
}

//�ػ�����
void CAFCBaseDialog::OnPaint() 
{
	CPaintDC dc(this);

	CRect ClientRect;
	GetClientRect(&ClientRect);
	DrawBackFace(&dc,0,0,ClientRect.Width(),ClientRect.Height());

	return;
}

//�滭����
void CAFCBaseDialog::DrawBackFace(CDC * pDC, int iXPos, int iYPos, int iWdith, int iHeight)
{
	CAFCImageHandle ImageHandle(&CAFCResourceManage::m_TabResource.m_BackPic);
	for (int i=iXPos;i<iWdith;i+=ImageHandle.GetWidth())
	{
		for (int j=iYPos;j<iHeight;j+=ImageHandle.GetHeight())
		{
			ImageHandle.BitBlt(pDC->GetSafeHdc(),i,j);
		}
	}
	return;
}

//�ؼ���ɫ��Ϣ
LRESULT CAFCBaseDialog::OnControlColor(WPARAM wparam, LPARAM lparam)
{
	::SetBkMode((HDC)wparam,TRANSPARENT);
	::SetTextColor((HDC)wparam,CAFCResourceManage::m_DialogResource.m_crTextColor);
	::SetBkColor((HDC)wparam,CAFCResourceManage::m_DialogResource.m_crBackColor);
	return (LRESULT)CAFCResourceManage::m_DialogResource.m_BackBrush.GetSafeHandle();
}

//��ʼ������
BOOL CAFCBaseDialog::OnInitDialog()
{
	__super::OnInitDialog();

	//��ԭ��Դ���
	AfxSetResourceHandle(GetModuleHandle(NULL));

	return TRUE;
}

/*******************************************************************************************************/

//���캯��
CAFCSkinDialog::CAFCSkinDialog(UINT uTemplate, CWnd * pParent) : CAFCBaseDialog(uTemplate,pParent)
{
	m_hIcon=NULL;
	m_bMaxSize=false;
	m_bTitleBar=true;
	m_bNowHotButton=255;
	m_bNowDownButton=255;
	::memset(m_rcButton,0,sizeof(m_rcButton));
	::memset(m_ButtonState,0,sizeof(m_ButtonState));

	return;
}

//��������
CAFCSkinDialog::~CAFCSkinDialog()
{
	//����ͼ��
	if (m_hIcon!=NULL) 
	{
		DestroyIcon(m_hIcon);
		m_hIcon=NULL;
	}
}

//��ʼ������
BOOL CAFCSkinDialog::OnInitDialog()
{
	__super::OnInitDialog();

	//ɾ�����ڱ���ͻ�ȡ����
	m_hIcon=GetIcon(TRUE);
	GetWindowText(m_strTitleText);
	long int lStyte=GetWindowLong(GetSafeHwnd(),GWL_STYLE);
	if ((lStyte&WS_MAXIMIZEBOX)||(lStyte&WS_MINIMIZEBOX)) 
	{
		m_ButtonState[BST_RESTORE]=BUT_EXIST|BUT_DISABLE;
		m_ButtonState[BST_MIN]=BUT_EXIST|BUT_DISABLE;
		if (lStyte&WS_MAXIMIZEBOX) m_ButtonState[BST_RESTORE]=BUT_EXIST|BUT_NORMAL;
		else m_ButtonState[BST_RESTORE]=BUT_EXIST|BUT_DISABLE;
		if (lStyte&WS_MINIMIZEBOX) m_ButtonState[BST_MIN]=BUT_EXIST|BUT_NORMAL;
		else m_ButtonState[BST_MIN]=BUT_EXIST|BUT_DISABLE;
	}
	if (lStyte&WS_SYSMENU) m_ButtonState[BST_CLOSE]=BUT_EXIST|BUT_NORMAL;
	ModifyStyle(WS_CAPTION,0,SWP_DRAWFRAME);
	SetClassLong(m_hWnd,GCL_HBRBACKGROUND,NULL);
	GetClientRect(&m_rcNormalSize);
	MapWindowPoints(GetParent(),&m_rcNormalSize);

	return TRUE;
}

//�ػ�����
void CAFCSkinDialog::OnPaint()
{
	CPaintDC dc(this);
	CRect ClientRect;
	GetClientRect(&ClientRect);
	DrawBackFace(&dc,0,0,ClientRect.Width(),ClientRect.Height());
	DrawFrame(&dc,ClientRect);
	DrawTitleBar(&dc,ClientRect);

	return;
}

//�滭��ť
void CAFCSkinDialog::DrawCloseButton(CDC * pDC)
{
	if (m_ButtonState[BST_CLOSE]&BUT_EXIST)	//�رհ�ť
	{
		if (((m_bNowDownButton==BST_CLOSE)&&(m_bNowHotButton==BST_CLOSE))
			||(m_ButtonState[BST_CLOSE]&BUT_DISABLE)) 
		{
			CAFCImageHandle ImageHandle(&CAFCResourceManage::m_DialogResource.m_CloseDis);
			ImageHandle.BitBlt(pDC->GetSafeHdc(),m_rcButton[0].left,m_rcButton[0].top);
		}
		else if (m_bNowHotButton==BST_CLOSE)
		{
			CAFCImageHandle ImageHandle(&CAFCResourceManage::m_DialogResource.m_CloseFoc);
			ImageHandle.BitBlt(pDC->GetSafeHdc(),m_rcButton[0].left,m_rcButton[0].top);
		}
		else 
		{
			CAFCImageHandle ImageHandle(&CAFCResourceManage::m_DialogResource.m_CloseNor);
			ImageHandle.BitBlt(pDC->GetSafeHdc(),m_rcButton[0].left,m_rcButton[0].top);
		}
	}
	return;
}

//�滭��ť
void CAFCSkinDialog::DrawMaxRestoreButton(CDC * pDC)
{
	if (m_ButtonState[BST_RESTORE]&BUT_EXIST)
	{
		if (m_ButtonState[BST_RESTORE]&BUT_MAXSIZE)	//��ԭ��ť
		{
			if (((m_bNowDownButton==BST_RESTORE)&&(m_bNowHotButton==BST_RESTORE))||(m_ButtonState[BST_RESTORE]&BUT_DISABLE)) 
			{
				CAFCImageHandle ImageHandle(&CAFCResourceManage::m_DialogResource.m_ResDis);
				ImageHandle.BitBlt(pDC->GetSafeHdc(),m_rcButton[BST_RESTORE].left,m_rcButton[BST_RESTORE].top);
			}
			else if (m_bNowHotButton==BST_RESTORE)
			{
				CAFCImageHandle ImageHandle(&CAFCResourceManage::m_DialogResource.m_ResFoc);
				ImageHandle.BitBlt(pDC->GetSafeHdc(),m_rcButton[BST_RESTORE].left,m_rcButton[BST_RESTORE].top);
			}
			else 
			{
				CAFCImageHandle ImageHandle(&CAFCResourceManage::m_DialogResource.m_ResNor);
				ImageHandle.BitBlt(pDC->GetSafeHdc(),m_rcButton[BST_RESTORE].left,m_rcButton[BST_RESTORE].top);
			}
		}
		else	//��󻯰�ť
		{
			if (((m_bNowDownButton==BST_RESTORE)&&(m_bNowHotButton==BST_RESTORE))||(m_ButtonState[BST_RESTORE]&BUT_DISABLE))
			{
				CAFCImageHandle ImageHandle(&CAFCResourceManage::m_DialogResource.m_MaxDis);
				ImageHandle.BitBlt(pDC->GetSafeHdc(),m_rcButton[BST_RESTORE].left,m_rcButton[BST_RESTORE].top);
			}
			else if (m_bNowHotButton==BST_RESTORE) 
			{
				CAFCImageHandle ImageHandle(&CAFCResourceManage::m_DialogResource.m_MaxFoc);
				ImageHandle.BitBlt(pDC->GetSafeHdc(),m_rcButton[BST_RESTORE].left,m_rcButton[BST_RESTORE].top);
			}
			else 
			{
				CAFCImageHandle ImageHandle(&CAFCResourceManage::m_DialogResource.m_MaxNor);
				ImageHandle.BitBlt(pDC->GetSafeHdc(),m_rcButton[BST_RESTORE].left,m_rcButton[BST_RESTORE].top);
			}
		}
	}
	return;
}

//�滭��ť
void CAFCSkinDialog::DrawMinButton(CDC * pDC)
{
	if (m_ButtonState[BST_MIN]&BUT_EXIST)	//��С����ť
	{
		if (((m_bNowDownButton==BST_MIN)&&(m_bNowHotButton==BST_MIN))||(m_ButtonState[BST_MIN]&BUT_DISABLE)) 
		{
			CAFCImageHandle ImageHandle(&CAFCResourceManage::m_DialogResource.m_MinDis);
			ImageHandle.BitBlt(pDC->GetSafeHdc(),m_rcButton[BST_MIN].left,m_rcButton[BST_MIN].top);
		}
		else if (m_bNowHotButton==BST_MIN) 
		{
			CAFCImageHandle ImageHandle(&CAFCResourceManage::m_DialogResource.m_MinFoc);
			ImageHandle.BitBlt(pDC->GetSafeHdc(),m_rcButton[BST_MIN].left,m_rcButton[BST_MIN].top);
		}
		else
		{
			CAFCImageHandle ImageHandle(&CAFCResourceManage::m_DialogResource.m_MinNor);
			ImageHandle.BitBlt(pDC->GetSafeHdc(),m_rcButton[BST_MIN].left,m_rcButton[BST_MIN].top);
		}
	}
	return;
}

//�滭���
void CAFCSkinDialog::DrawFrame(CDC * pDC, CRect & ClientRect)
{
	pDC->Draw3dRect(ClientRect.left,ClientRect.top,ClientRect.right,ClientRect.bottom,
		CAFCResourceManage::m_DialogResource.m_rcTopFrameColor,CAFCResourceManage::m_DialogResource.m_rcButFrameColor);
	pDC->Draw3dRect(ClientRect.left+1,ClientRect.top+1,ClientRect.right-2,ClientRect.bottom-2,
		CAFCResourceManage::m_DialogResource.m_rcTopFrameColor,CAFCResourceManage::m_DialogResource.m_rcButFrameColor);
	return;
}

//�滭������
void CAFCSkinDialog::DrawTitleBar(CDC * pDC, CRect & ClientRect)
{
	if (m_bTitleBar==true)
	{
		//�������� BMP
		CDC MemDC;
		CBitmap BufBmp;
		BufBmp.CreateCompatibleBitmap(pDC,ClientRect.Width(),TITLE_HIGHT);
		MemDC.CreateCompatibleDC(pDC);
		CBitmap * pOldBmp=MemDC.SelectObject(&BufBmp);

		//�滭�����
		CAFCImageHandle ImageHandle(&CAFCResourceManage::m_DialogResource.m_Title);
		ImageHandle.StretchBlt(MemDC.GetSafeHdc(),CRect(0,0,ClientRect.Width(),TITLE_HIGHT));

		//�滭ͼ��
		int iDrawPosX=ClientRect.left+5;
		if (m_hIcon!=NULL)
		{
			int iDrawPosY=(TITLE_HIGHT-16)/2;
			::DrawIconEx(MemDC.GetSafeHdc(),iDrawPosX,iDrawPosY,m_hIcon,16,16,0,NULL,DI_NORMAL|DI_COMPAT);
			iDrawPosX+=26;
		}
		else iDrawPosX=10;

		//�滭����
		if (m_strTitleText.GetLength()!=0)
		{
			int iDrawPosY=(TITLE_HIGHT-10)/2;
			MemDC.SetBkMode(TRANSPARENT);
			MemDC.SetTextColor(CAFCResourceManage::m_DialogResource.m_rcTitleTextColor);
			MemDC.SelectObject(&CAFCResourceManage::m_HFont);
			MemDC.TextOut(iDrawPosX,iDrawPosY,m_strTitleText);
		}

		//�滭��ť
		DrawCloseButton(&MemDC);
		DrawMaxRestoreButton(&MemDC);
		DrawMinButton(&MemDC);

		//�滭��Ļ
		pDC->BitBlt(0,0,ClientRect.Width(),TITLE_HIGHT,&MemDC,0,0,SRCCOPY);
		MemDC.SelectObject(pOldBmp);
		BufBmp.DeleteObject();
	}

	return;
}

//����Ҽ�������Ϣ
void CAFCSkinDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
	__super::OnLButtonDown(nFlags, point);
	
	if ((m_bTitleBar==true)&&(point.y<=TITLE_HIGHT))
	{
		//��ť����
		for (int i=0;i<3;i++)
		{
			if ((m_ButtonState[i]&BUT_EXIST)&&(!(m_ButtonState[i]&BUT_DISABLE))&&(m_rcButton[i].PtInRect(point)))
			{
				//�������� 
				m_bNowDownButton=i;
				::SetCapture(GetSafeHwnd());
				UpdateTitleBar();
				return;
			}
		}

		//ģ�ⰴ����
		if (m_bMaxSize==false) PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
	}
}

//����Ҽ�������Ϣ
void CAFCSkinDialog::OnLButtonUp(UINT nFlags, CPoint point)
{
	__super::OnLButtonUp(nFlags, point);

	//��ť����
	if ((m_bTitleBar==true)&&(m_bNowDownButton!=255))
	{
		::ReleaseCapture();
		if ((m_rcButton[m_bNowDownButton].PtInRect(point))&&(!(m_ButtonState[m_bNowDownButton]&BUT_DISABLE)))
		{
			switch (m_bNowDownButton)
			{
			case BST_CLOSE:		//�رհ�ť
				{
					OnCancel();
					break;
				}
			case BST_RESTORE:	//��ԭ��ť
				{
					if (m_bMaxSize==true) ShowRestoreSize();
					else ShowMaxSize();
					break;
				}
			case BST_MIN:		//��С����ť
				{
					ShowWindow(SW_MINIMIZE);
					break;
				}
			}
		}

		//��������
		m_bNowDownButton=255;
		UpdateTitleBar();
	}
	
	return;
}

//���˫����Ϣ
void CAFCSkinDialog::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	__super::OnLButtonDblClk(nFlags, point);

	//��������
	if ((m_bTitleBar==true)&&(m_ButtonState[BST_RESTORE]&BUT_EXIST)&&(!(m_ButtonState[BST_RESTORE]&BUT_DISABLE)))
	{
		if (m_bMaxSize==true) ShowRestoreSize();
		else ShowMaxSize();
	}
	
	return;
}

//����ƶ���Ϣ
void CAFCSkinDialog::OnMouseMove(UINT nFlags, CPoint point)
{
	__super::OnMouseMove(nFlags, point);

	if ((m_bTitleBar==true)&&((point.y<TITLE_HIGHT)||(m_bNowHotButton!=255)))
	{
		//��ť����
		for (int i=0;i<3;i++)
		{
			if ((m_ButtonState[i]&BUT_EXIST)&&(m_rcButton[i].PtInRect(point)))
			{
				if (m_bNowHotButton==i) return;
				if (m_bNowHotButton!=255)
				{
					m_ButtonState[m_bNowHotButton]|=BUT_NORMAL;
					m_bNowHotButton=255;
				}
				if ((m_ButtonState[i]&BUT_EXIST)&&(!(m_ButtonState[i]&BUT_DISABLE)))
				{
					m_bNowHotButton=i;
					m_ButtonState[m_bNowHotButton]&=~BUT_NORMAL;
				}
				break;
			}
		}
		if (((i==3)&&(m_bNowHotButton!=255))||(i<3))
		{
			if (i==3)
			{
				m_ButtonState[m_bNowHotButton]|=BUT_NORMAL;
				m_bNowHotButton=255;
			}
			UpdateTitleBar();
		}
	}

	return;
}

//λ�ñ仯 
void CAFCSkinDialog::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	//����λ��
	for (int i=0;i<3;i++)
	{
		m_rcButton[i].SetRect(cx-(BUTTON_WIDTH+5)*(i+1),(TITLE_HIGHT-BUTTON_HIGHT)/2+1,
			cx-(BUTTON_WIDTH+5)*(i+1)+BUTTON_WIDTH,(TITLE_HIGHT-BUTTON_HIGHT)/2+BUTTON_HIGHT+1);
	}
	Invalidate(FALSE);
	
	return;
}

//��������
void CAFCSkinDialog::OnDestroy()
{
	__super::OnDestroy();

	//����ͼ��
	if (m_hIcon!=NULL) 
	{
		DestroyIcon(m_hIcon);
		m_hIcon=NULL;
	}

	return;
}

//����ͼ��
bool CAFCSkinDialog::SetDialogIcon(HICON hIcon, BOOL bBigIcon)
{
	//����ͼ��
	if ((m_hIcon!=NULL)&&(m_hIcon!=hIcon)) 
	{
		DestroyIcon(m_hIcon);
		m_hIcon=NULL;
	}

	//����ͼ��
	m_hIcon=hIcon;
	SetIcon(hIcon,bBigIcon);
	UpdateTitleBar();

	return true;
}

//���ñ���
bool CAFCSkinDialog::SetWindowTitle(const TCHAR * szTitle)
{
	//��������
	m_strTitleText.Empty();
	if ((szTitle!=NULL)&&(szTitle[0]!=0)) m_strTitleText=szTitle;
	SetWindowText(m_strTitleText);
	UpdateTitleBar();

	return true;
}

//���ñ���
bool CAFCSkinDialog::EnableTitleBar(bool bEnableBar)
{	
	m_bTitleBar=bEnableBar;
	Invalidate(FALSE);
	return bEnableBar;
}

//��ȡ����߶�
UINT CAFCSkinDialog::GetTitleHight()
{
	return m_bTitleBar?TITLE_HIGHT:0;
}

//���±���
bool CAFCSkinDialog::UpdateTitleBar()
{
	if ((m_bTitleBar==true)&&(GetSafeHwnd()!=NULL))
	{
		CRect ClientRect;
		GetClientRect(&ClientRect);
		CDC * pDC=GetDC();
		DrawTitleBar(pDC,ClientRect);
		ReleaseDC(pDC);
	}
	return true;
}

//��ʾ��󻯴��� 
void CAFCSkinDialog::ShowMaxSize()
{
	//��������
	m_bMaxSize=true;
	m_ButtonState[BST_RESTORE]|=BUT_MAXSIZE;
	MoveWindow(0,0,GetSystemMetrics(SM_CXFULLSCREEN),GetSystemMetrics(SM_CYFULLSCREEN)+GetSystemMetrics(SM_CYCAPTION));
	return;
}

//��ʾ��ԭ���� 
void CAFCSkinDialog::ShowRestoreSize()
{
	m_bMaxSize=false;
	m_ButtonState[BST_RESTORE]&=~BUT_MAXSIZE;
	CWnd * pParentWnd=GetParent();
	if (pParentWnd!=NULL) GetParent()->MoveWindow(m_rcNormalSize);
	else MoveWindow(m_rcNormalSize);

	return;
}

/*******************************************************************************************************/

//���캯��
CAFCRgnDialog::CAFCRgnDialog(UINT uTemplate, CWnd * pParent) : CAFCBaseDialog(uTemplate,pParent)
{
	return;
}

//��������
CAFCRgnDialog::~CAFCRgnDialog()
{
	m_DialogRgn.DeleteObject();
	return;
}

//��ʼ������
BOOL CAFCRgnDialog::OnInitDialog()
{
	__super::OnInitDialog();

	//ɾ�����ڱ���ͻ�ȡ����
	ModifyStyle(WS_CAPTION,0,SWP_DRAWFRAME);
	SetClassLong(m_hWnd,GCL_HBRBACKGROUND,NULL);

	return TRUE;
}

//�ػ�����
void CAFCRgnDialog::OnPaint()
{
	CPaintDC dc(this);

	//�滭��ͼ
	if (m_BackBitmap.IsNull()==false)
	{
		CRect ClientRect;
		GetClientRect(&ClientRect);
		CAFCImageHandle ImageHandle(&m_BackBitmap);
		ImageHandle.BitBlt(dc.GetSafeHdc(),0,0);
	}

	return;
}

//����λͼ
bool CAFCRgnDialog::LoadDialogBitmap(HINSTANCE hInstance, UINT uBitmapID, COLORREF crTransparentColor, COLORREF crTolerance)
{
	if (uBitmapID!=0)
	{
		//��������
		m_BackBitmap.SetLoadInfo(hInstance,uBitmapID,CAFCResourceManage::m_bAutoLock);
		CAFCImageHandle ImageHandle(&m_BackBitmap);
		HRGN hRgn=AFCBmpToRgn(ImageHandle,crTransparentColor,crTolerance);
		if (hRgn!=NULL)
		{
			SetWindowPos(NULL,0,0,ImageHandle.GetWidth(),ImageHandle.GetHeight(),SWP_NOMOVE);
			SetWindowRgn(hRgn,TRUE);
			m_DialogRgn.DeleteObject();
			m_DialogRgn.Attach(hRgn);
			return true;
		}
	}
	return false;
}

//����λͼ
bool CAFCRgnDialog::LoadDialogBitmap(TCHAR * szFileName, COLORREF crTransparentColor, COLORREF crTolerance)
{
	if (szFileName!=NULL)
	{
		//��������
		m_BackBitmap.SetLoadInfo(szFileName,CAFCResourceManage::m_bAutoLock);
		CAFCImageHandle ImageHandle(&m_BackBitmap);
		HRGN hRgn=AFCBmpToRgn(ImageHandle,crTransparentColor,crTolerance);
		if (hRgn!=NULL)
		{
			SetWindowPos(NULL,0,0,ImageHandle.GetWidth(),ImageHandle.GetHeight(),SWP_NOMOVE);
			SetWindowRgn(hRgn,TRUE);
			m_DialogRgn.DeleteObject();
			m_DialogRgn.Attach(hRgn);
			return true;
		}
	}
	return false;
}

//����Ҽ�������Ϣ
void CAFCRgnDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
	__super::OnLButtonDown(nFlags, point);

	//ģ�ⰴ����
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
}

/*******************************************************************************************************/
