#pragma once

#ifndef A41A948D_8E6F_405c_AB5B_04AE11E53BD
#define A41A948D_8E6F_405c_AB5B_04AE11E53BD

#include "AFCLock.h"

//���̹�����
class EXT_CLASS CProcessManage
{
	//��������
protected:
	

protected:
	static bool							g_bInit;					//�Ƿ��ʼ��
	static CPtrArray					g_pManageArray;				//���̹���������
	static CAFCSignedLock				g_Lock;						//��Դ������

	//��������
public:
	//���캯��
	CProcessManage(void);
	//��������
	~CProcessManage(void);

	//���ܺ���
public:
	//��������

};

#endif