#include "StdAfx.h"

#include "MobileImp.h"

//PJY SMS ͨѶʵ����//////////////////////////////////////////////////////////////////////////////////

CMobileImp::CMobileImp(void)
{
}

CMobileImp::~CMobileImp(void)
{
}

//�ӿ�ʵ��////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT CMobileImp::GetCodeInfo(char* szPhoneNo,char* szUserID,char* szResult)
{
	CComBSTR bstPhoneNo(szPhoneNo);
	CComBSTR bstUserID(szUserID);
	BSTR bstResult;

	HRESULT hr = CMobileCodeWST::getMobileCodeInfo(bstPhoneNo,bstUserID,&bstResult);
	if (S_OK == hr)
	{
		char* p = _com_util::ConvertBSTRToString((WCHAR*)bstResult);
		if (p)
		{
			::strcpy(szResult,p);
			delete[] p;
		}
	}

	return hr;
}

void CMobileImp::ReleaseObject()
{
	OutputTraceStr("Sms: CMobileImp::ReleaseObject");
	delete this;
}