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
///吃碰杠检测类(重载)
class CheckCPGActionEx:public CheckCPGAction
{
public:
	CheckCPGActionEx(void);
	~CheckCPGActionEx(void);
	
public:	
	
	
public:
	///能否吃牌
	virtual bool CanChi(BYTE station,BYTE pai,BYTE Result[][3]);
	///能否吃牌(只判断)
	virtual bool CanChi(BYTE station,BYTE pai);
	///能否碰牌
	virtual bool CanPeng(BYTE station,BYTE pai);
	//能否坎牌
	virtual bool CanKan(BYTE station,BYTE kan[]);
	//能否坎牌
	virtual bool CanSaoHu(BYTE station);
	///能否杠牌
	virtual bool CanGang(BYTE station,BYTE pai,BYTE Result[][2],bool me=false);

};

//全局对象
//extern CheckCPGActionEx g_CPGAction;