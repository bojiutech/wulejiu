#ifndef WRITELOG_H
#define WRITELOG_H
#include<stdio.h>
//д��error��ͷ�Ĵ�����־
_declspec(dllexport) void WriteError(TCHAR *pMessage,int iRoomID = 0,int iSmallRoomID = 0);
//д�����ִ�
_declspec(dllexport)  void WriteStr(TCHAR *str,int iRoomID = 0,int iSmallRoomID = 0);
//ɾ����־
_declspec(dllexport)  void Dellog(int iRoomID = 0,int iSmallRoomID = 0);

_declspec(dllexport)  void WriteStr(int iValue);

_declspec(dllexport)  void WriteStr(long int iValue);
#endif