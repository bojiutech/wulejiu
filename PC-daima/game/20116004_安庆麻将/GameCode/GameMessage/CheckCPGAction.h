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
///³ÔÅö¸Ü¼ì²âÀà
class CheckCPGAction
{
public:
	CheckCPGAction(void);
	~CheckCPGAction(void);
	
public:	
		UserDataEx	*pUserData;//ÓÃ»§Êý¾Ý

		CServerGameDesk *pDesk;//¸¸Àà£¨×À×Ó£©
	
public:

	/////¼òµ¥ºýÅÆ¼ì²â
	//virtual bool CanHu(BYTE station,BYTE zhuapai,BYTE dianpai);
	/////ÏêÏ¸ºýÅÆ¼ì²â
	//virtual bool CanHu(BYTE station,BYTE zhuapai,BYTE dianpai,BYTE hutype[],bool zimo);
	/////ÌýÅÆ¼ì²â
	//virtual bool CanTing(BYTE station,BYTE CanOut[],BYTE pai = 255);

	///ÄÜ·ñ³ÔÅÆ
	virtual bool CanChi(BYTE station,BYTE pai,BYTE Result[][3]);
	///ÄÜ·ñ³ÔÅÆ(Ö»ÅÐ¶Ï)
	virtual bool CanChi(BYTE station,BYTE pai);
	///ÄÜ·ñÅöÅÆ
	virtual bool CanPeng(BYTE station,BYTE pai);
	//ÄÜ·ñ¿²ÅÆ
	virtual bool CanKan(BYTE station,BYTE kan[]);
	//ÄÜ·ñ¿²ÅÆ
	virtual bool CanSaoHu(BYTE station);
	///ÄÜ·ñ¸ÜÅÆ
	virtual bool CanGang(BYTE station,BYTE pai,BYTE Result[][2],bool me=false);

	//void SetDataPoint(UserDataEx *userdata);

	void SetDeskPoint(CServerGameDesk *desk);
};
