/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #pragma once

#include "../GameMessage/CheckCPGAction.h"
///�����ܼ����(����)
class CheckCPGActionEx:public CheckCPGAction
{
public:
	CheckCPGActionEx(void);
	~CheckCPGActionEx(void);
	
public:	
	
	
public:
	///�ܷ����
	virtual bool CanChi(BYTE station,BYTE pai,BYTE Result[][3]);
	///�ܷ����(ֻ�ж�)
	virtual bool CanChi(BYTE station,BYTE pai);
	///�ܷ�����
	virtual bool CanPeng(BYTE station,BYTE pai);
	//�ܷ���
	virtual bool CanKan(BYTE station,BYTE kan[]);
	//�ܷ���
	virtual bool CanSaoHu(BYTE station);
	///�ܷ����
	virtual bool CanGang(BYTE station,BYTE pai,BYTE Result[][2],bool me=false);

};

//ȫ�ֶ���
//extern CheckCPGActionEx g_CPGAction;