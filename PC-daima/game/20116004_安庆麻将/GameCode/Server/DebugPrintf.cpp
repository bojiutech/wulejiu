/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               //////////////////////////////////////////////////////////////////////////
/// ������Ϣ��������Ϣ�����������
/// ���У�DebugPrintf���ڵ��Ը���ʱ�����Ϣ������ʱ�����޸ĺ����壬��д�ļ�ֱ�ӷ���
/// ErrorPrintf���ڳ������쳣״�������������ʱҲһ������������ٴ���ʱ�ṩ��Ϣ

#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include "Debug_new.h"
#include "stdafx.h"
#define DEBUGFILE_NAME 20116004

/**
* @brief ��ȡ���г�������·�������ַ���ĩβ���ӷ�б��
*/ 
char *G_GetAppPath()
{
    static char s_Path[MAX_PATH];
    static bool s_bIsReady = false;
    if (!s_bIsReady)
    {
        ZeroMemory(s_Path,sizeof(s_Path));
        DWORD dwLength=GetModuleFileNameA(GetModuleHandle(NULL), s_Path, sizeof(s_Path));
        char *p = /*_tcsrchr*/strrchr(s_Path, '\\');
        *p = '\0';
        s_bIsReady = true;
    }
    return s_Path;
}
/// ��ӡ������Ϣ
void DebugPrintf_debug(const char *p, ...)
{
    char szTimeStr[32];
    char szDateStr[32];
	char szFilename[256];
	SYSTEMTIME sysTime;

	GetLocalTime(&sysTime);

    sprintf( szFilename, "%s\\server-log\\%d_%d%d%d.txt", G_GetAppPath(), DEBUGFILE_NAME,sysTime.wYear,sysTime.wMonth,sysTime.wDay);

    FILE *fp = fopen( szFilename, "a" );
    if (NULL == fp)
    {
        return;
    }

    va_list arg;
    va_start( arg, p );
    GetTimeFormatA( LOCALE_USER_DEFAULT, TIME_FORCE24HOURFORMAT, &sysTime, "HH:mm:ss", szTimeStr, 32);
    GetDateFormatA( LOCALE_USER_DEFAULT, LOCALE_USE_CP_ACP, &sysTime, "yyyy-MM-dd", szDateStr, 32);
    fprintf(fp, "[%s %s]--", szDateStr, szTimeStr);
    vfprintf(fp, p, arg );
    fprintf(fp,"\n");
    fclose(fp);
}


/// ��ӡ������Ϣ
void ErrorPrintf_debug(const char *p, ...)
{
    char szTimeStr[32];
    char szDateStr[32];
    char szFilename[256];
    sprintf( szFilename, "%s\\Log\\%dLogic.txt", G_GetAppPath(), DEBUGFILE_NAME);
    FILE *fp = fopen( szFilename, "a" );
    if (NULL == fp)
    {
        return;
    }
    va_list arg;
    va_start( arg, p );
    SYSTEMTIME sysTime;
    GetLocalTime(&sysTime);
    GetTimeFormatA( LOCALE_USER_DEFAULT, TIME_FORCE24HOURFORMAT, &sysTime, "HH:mm:ss", szTimeStr, 32);
    GetDateFormatA( LOCALE_USER_DEFAULT, LOCALE_USE_CP_ACP, &sysTime, "yyyy-MM-dd", szDateStr, 32);
    fprintf(fp, "[%s %s]--", szDateStr, szTimeStr);
    vfprintf(fp, p, arg );
    fprintf(fp,"\n");
    fclose(fp);
}

/// ��ӡ������Ϣ
void LBWOutputDebugString_debug(const char *lpszFormat, ...)
{
    va_list pArg;
    va_start(pArg, lpszFormat);
    char szMessage[1024] = { 0 };
    _vsnprintf(szMessage, 1023, lpszFormat, pArg);
    va_end(pArg);
    OutputDebugStringA(szMessage);
}
