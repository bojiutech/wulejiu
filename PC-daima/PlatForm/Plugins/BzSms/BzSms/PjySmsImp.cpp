#include "StdAfx.h"

#include "PjySmsImp.h"

//PJY SMS ͨѶʵ����//////////////////////////////////////////////////////////////////////////////////

CPjySmsImp::CPjySmsImp(void)
{
}

CPjySmsImp::~CPjySmsImp(void)
{
}

//�ӿ�ʵ��////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT CPjySmsImp::SendMessage(char* szPhoneNo,char* szMessage)
{
	CComBSTR bstPhoneNo(szPhoneNo);
	CComBSTR bstMessage(szMessage);
	CComBSTR bstUserID("admin");

	SYSTEMTIME sys_t;
	char szTime[32] = {0};
	::GetLocalTime(&sys_t);
	_stprintf(szTime,"%02d:%02d:%02d",sys_t.wHour,sys_t.wMinute,sys_t.wSecond);
	CComBSTR bstDateTime(szTime);

	return CMessageUtilT::SendMessage(bstPhoneNo,bstMessage,bstDateTime,bstUserID);
}

void CPjySmsImp::ReleaseObject()
{
	OutputTraceStr("Sms: CPjySmsImp::ReleaseObject");
	delete this;
}