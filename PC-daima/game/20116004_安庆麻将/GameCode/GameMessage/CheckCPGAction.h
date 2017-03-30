/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #pragma once

#include "..\ChangeFile\GameDataEx.h"
#include "..\ChangeFile\UserDataEx.h"
class CServerGameDesk;
///�����ܼ����
class CheckCPGAction
{
public:
	CheckCPGAction(void);
	~CheckCPGAction(void);
	
public:	
		UserDataEx	*pUserData;//�û�����

		CServerGameDesk *pDesk;//���ࣨ���ӣ�
	
public:

	/////�򵥺��Ƽ��
	//virtual bool CanHu(BYTE station,BYTE zhuapai,BYTE dianpai);
	/////��ϸ���Ƽ��
	//virtual bool CanHu(BYTE station,BYTE zhuapai,BYTE dianpai,BYTE hutype[],bool zimo);
	/////���Ƽ��
	//virtual bool CanTing(BYTE station,BYTE CanOut[],BYTE pai = 255);

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

	//void SetDataPoint(UserDataEx *userdata);

	void SetDeskPoint(CServerGameDesk *desk);
};
