/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#pragma once

#include "gamemanagesocket.h"
class CGameLogonManage;

class CGameManageModule : public IModuleManageService
{
public:
	CGameManageModule(void);
	virtual ~CGameManageModule(void);
	
	//virtual bool InitService(ManageInfoStruct * pInitData, ServerDllInfoStruct *pDllInfo, HINSTANCE	hDllInstance);
	virtual bool InitService(ManageInfoStruct *pInitData);
	virtual bool UnInitService();
	virtual bool StartService(UINT &errCode);
	virtual bool StoptService();
	virtual bool DeleteService();

	void SetCGameLogonManage(CGameLogonManage* pManager){m_LogonManage.SetCGameLogonManage(pManager);}
	void SetUserCloseSocket(UINT uUserid);

public:
	CGameManageSocket		m_LogonManage;
};