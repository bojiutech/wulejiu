#pragma once

#ifndef AFCDIALOG_HEAD_FILE
#define AFCDIALOG_HEAD_FILE

#include "StdAfx.h"

using namespace AFC::AFCImage;

namespace AFC
{
	namespace AFCDialog
	{
		/*******************************************************************************************************/

		//�����Ի�����
		class EXT_CLASS CAFCBaseDialog : public CDialog
		{
			//��������
		public:
			//���캯��
			CAFCBaseDialog(UINT uTemplate, CWnd * pParent=NULL);
			//��������
			virtual ~CAFCBaseDialog();
			//��ʼ������
			virtual BOOL OnInitDialog();

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

			//��Ϣӳ��
		protected:
			DECLARE_MESSAGE_MAP()

			//���ܺ���
		protected:
			//�滭����
			void DrawBackFace(CDC * pDC, int iXPos, int iYPos, int iWdith, int iHeight);

			//��Ϣ����
		public:
			//�ػ�����
			afx_msg void OnPaint();
			//�ؼ���ɫ��Ϣ
			LRESULT OnControlColor(WPARAM wparam, LPARAM lparam);
		};

		/*******************************************************************************************************/

		//Ƥ���Ի�����
		class EXT_CLASS CAFCSkinDialog : public CAFCBaseDialog
		{
			//��������
		private:
			bool						m_bMaxSize;						//���
			bool						m_bTitleBar;					//�����־
			HICON						m_hIcon;						//ͼ����
			BYTE						m_bNowDownButton;				//���°�ť 
			BYTE						m_bNowHotButton;				//���ڽ���
			BYTE						m_ButtonState[3];				//��ť״̬
			CRect						m_rcButton[3];					//��ťλ��
			CRect						m_rcNormalSize;					//��ͨλ��
			CString						m_strTitleText;					//��������

			//��������
		public:
			//���캯��
			CAFCSkinDialog(UINT uTemplate, CWnd * pParent=NULL);
			//��������
			virtual ~CAFCSkinDialog();
			//��ʼ������
			virtual BOOL OnInitDialog();

			//���ܺ���
		public:
			//��ʾ��󻯴��� 
			void ShowMaxSize();
			//��ʾ��ԭ���� 
			void ShowRestoreSize();
			//����ͼ��
			bool SetDialogIcon(HICON hIcon, BOOL bBigIcon);
			//���ñ���
			bool SetWindowTitle(const TCHAR * szTitle);
			//���ñ���
			bool EnableTitleBar(bool bEnableBar);
			//��ȡ����߶�
			UINT GetTitleHight();

			//��Ϣӳ��
		protected:
			DECLARE_MESSAGE_MAP()

			//�ڲ�����
		protected:
			//�滭���
			void DrawFrame(CDC * pDC, CRect & ClientRect);
			//�滭������
			void DrawTitleBar(CDC * pDC, CRect & ClientRect);
			//�滭��ť
			void DrawCloseButton(CDC * pDC);
			//�滭��ť
			void DrawMaxRestoreButton(CDC * pDC);
			//�滭��ť
			void DrawMinButton(CDC * pDC);
			//���±���
			bool UpdateTitleBar();

			//��Ϣ����
		public:
			//�ػ�����
			afx_msg void OnPaint();
			//����ƶ���Ϣ
			afx_msg void OnMouseMove(UINT nFlags, CPoint point);
			//����Ҽ�������Ϣ
			afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
			//����Ҽ�������Ϣ
			afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
			//���˫����Ϣ
			afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
			//λ�ñ仯 
			afx_msg void OnSize(UINT nType, int cx, int cy);
			//��������
			afx_msg void OnDestroy();
		};

		/*******************************************************************************************************/

		//����Ի�����
		class EXT_CLASS CAFCRgnDialog : public CAFCBaseDialog
		{
			//��������
		protected:
			CRgn						m_DialogRgn;					//�Ի�������
			CAFCImage					m_BackBitmap;					//�Ի��򱳾�ͼ

			//��������
		public:
			//���캯��
			CAFCRgnDialog(UINT uTemplate, CWnd * pParent=NULL);
			//��������
			virtual ~CAFCRgnDialog();
			//��ʼ������
			virtual BOOL OnInitDialog();

			//��Ϣӳ��
		protected:
			DECLARE_MESSAGE_MAP()

			//���ܺ���
		public:
			//����λͼ
			bool LoadDialogBitmap(HINSTANCE hInstance, UINT uBitmapID, COLORREF crTransparentColor=RGB(0,0,0), COLORREF crTolerance=RGB(0,0,0));
			//����λͼ
			bool LoadDialogBitmap(TCHAR * szFileName, COLORREF crTransparentColor=RGB(0,0,0), COLORREF crTolerance=RGB(0,0,0));

			//��Ϣ����
		public:
			//�ػ�����
			afx_msg void OnPaint();
			//����Ҽ�������Ϣ
			afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		};

		/*******************************************************************************************************/
	};
};

#endif