/********************************************************************
	created:	2012/04/30
	file base:	Sms
	file ext:	h
	author:		
	
	purpose:	entinfo.cn SMSͨѶʵ��
*********************************************************************/
#ifndef __ENTINFO_IMP_H__
#define __ENTINFO_IMP_H__

#pragma once

#include <CGuid.h>
#include <initguid.h>

#include "SmsIf.h"
#include "EntinfoSmsImp.h"

using namespace WebService;

class CEntinfoSmsImp : public CWebServiceT<>,
				   public ISms
{
public:

	CEntinfoSmsImp(void);

	virtual ~CEntinfoSmsImp(void);

//�ӿ�ʵ��
protected:

	//���Ͷ���
	virtual HRESULT SendMessage(char* szPhoneNo,char* szMessage);

	//�ͷŶ���
	virtual void ReleaseObject();


};

#endif // __PJY_IMP_H__
