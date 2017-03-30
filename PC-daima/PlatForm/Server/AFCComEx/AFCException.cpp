#include "StdAfx.h"
#include "AFCException.h"

//��̬��������
bool		CAFCException::m_bShowError=false;					//�Ƿ���ʾ����

//���캯��
CAFCException::CAFCException(TCHAR * szErrorMessage, UINT uErrorCode, bool bAutoDelete)
{
	m_uErrorCode=uErrorCode;
	m_bAutoDelete=bAutoDelete;
	if ((szErrorMessage!=NULL)&&(szErrorMessage[0]!=0))
	{
		if (lstrlen(szErrorMessage)<(sizeof(m_szMessage)/sizeof(m_szMessage[0])))	
			lstrcpy(m_szMessage,szErrorMessage);
		else lstrcpy(m_szMessage,TEXT("�쳣������Ϣ̫��"));
	}
	else lstrcpy(m_szMessage,TEXT("û���쳣��Ϣ"));
	if (m_bShowError==true)	AfxMessageBox(m_szMessage,MB_ICONSTOP);
	return;
}

//��������
CAFCException::~CAFCException(void)
{
}

//��ȡ�������
UINT CAFCException::GetErrorCode() const
{
	if (this!=NULL) return m_uErrorCode;
	return 0;
}

//ɾ������
bool CAFCException::Delete()
{
	if ((this!=NULL)&&(m_bAutoDelete==true))
	{
		delete this;
		return true;
	}
	return false;
}

//��ȡ������Ϣ
TCHAR const * CAFCException::GetErrorMessage(TCHAR * szBuffer, int iBufLength) const
{
	if (this!=NULL)
	{
		//����������Ϣ
		if ((szBuffer!=NULL)&&(iBufLength>0))
		{
			int iCopyLength=__min(iBufLength-1,::lstrlen(m_szMessage));
			szBuffer[iCopyLength]=0;
			::CopyMemory(szBuffer,m_szMessage,iCopyLength*sizeof(TCHAR));
		}
		return m_szMessage;
	}
	return NULL;
}

//�����Ƿ���ʾ����
bool CAFCException::ShowErrorMessage(bool bShowError)
{
	m_bShowError=bShowError;
	return m_bShowError;
}
