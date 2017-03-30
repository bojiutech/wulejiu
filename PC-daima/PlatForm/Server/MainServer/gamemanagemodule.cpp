/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#include "stdafx.h"
#include "gamemanagemodule.h"

CGameManageModule::CGameManageModule()
{

}

CGameManageModule::~CGameManageModule()
{

}

bool CGameManageModule::InitService(ManageInfoStruct *pInitData)
{
	try
	{
		return m_LogonManage.Init(pInitData,nullptr);
	}
	catch(CAFCException *pException)
	{
		pException->Delete();
		TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
		return false;
	}
	catch(...)
	{
		TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
		return false;
	}
}

bool CGameManageModule::UnInitService()
{
	try 
	{
		return m_LogonManage.UnInit();
	}
	catch(CAFCException *pException)
	{
		pException->Delete();
		TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
	}
	catch(...)
	{
		TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
	}

	return false;
}

bool CGameManageModule::StartService(UINT &errCode)
{
	try
	{
		return m_LogonManage.Start();
	}
	catch(CAFCException *pException)
	{
		pException->Delete();
		TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
	}
	catch(...)
	{
		TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
	}
	return false;
}

bool CGameManageModule::StoptService()
{
	try
	{
		return m_LogonManage.Stop();
	}
	catch (CAFCException * pException)	{ pException->Delete();TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);	}
	catch (...) {TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);}
	return false;
}

bool CGameManageModule::DeleteService()
{
	try
	{
		delete this;
	}
	catch(...)
	{

	}
	return true;
}

void CGameManageModule::SetUserCloseSocket(UINT uUserid)
{
	m_LogonManage.SetUserCloseSocket(uUserid);
}