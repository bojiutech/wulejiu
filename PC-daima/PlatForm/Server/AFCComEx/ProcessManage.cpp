#include "StdAfx.h"
#include "ProcessManage.h"

//��������
bool						CProcessManage::g_bInit=false;				//�Ƿ��ʼ��
CPtrArray					CProcessManage::g_pManageArray;				//���̹���������
CAFCSignedLock				CProcessManage::g_Lock;						//��Դ������

//���캯��
CProcessManage::CProcessManage(void)
{
//	g_Lock.Lock();
	if (!g_bInit)
	{
		g_bInit=true;
		g_pManageArray.SetSize(10);
	}
	g_pManageArray.Add(this);
//	g_Lock.UnLock();
	return;
}

//��������
CProcessManage::~CProcessManage(void)
{
//	g_Lock.Lock();
	int uCount=(int)g_pManageArray.GetUpperBound();
	for (int i=0;i<uCount;i++)
	{
		if (g_pManageArray.GetAt(i)==this) 
		{
			g_pManageArray.RemoveAt(i);
			break;
		}
	}
//	g_Lock.UnLock();
	return;
}
