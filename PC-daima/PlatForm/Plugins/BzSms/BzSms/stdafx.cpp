// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// GK_1205Sms.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

// TODO: �� STDAFX.H ��
// �����κ�����ĸ���ͷ�ļ����������ڴ��ļ�������

int CDECL OutputTraceStr(TCHAR* szFormat,...)
{
	TCHAR   szBuffer[1024];
	va_list pArgList ;

	// The va_start macro (defined in STDARG.H) is usually equivalent to:
	// pArgList = (char *) &szFormat + sizeof (szFormat) ;

	va_start(pArgList,szFormat) ;

	// The last argument to wvsprintf points to the arguments

	_vsntprintf (szBuffer,sizeof(szBuffer)/sizeof(TCHAR),szFormat,pArgList);

	// The va_end macro just zeroes out pArgList for no good reason

	va_end(pArgList);

	OutputDebugString(szBuffer);

	return 0;
}
