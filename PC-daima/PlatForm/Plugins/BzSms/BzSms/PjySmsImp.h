/********************************************************************
	created:	2012/04/30
	file base:	Sms
	file ext:	h
	author:		
	
	purpose:	PJY SMSͨѶʵ��
*********************************************************************/
#ifndef __PJY_IMP_H__
#define __PJY_IMP_H__

#pragma once

#include <CGuid.h>
#include <initguid.h>

#include "SmsIf.h"
#include "com_1885128pjy.h"

using namespace MessageUtil;

class CPjySmsImp : public CMessageUtilT<>,
				   public ISms
{
public:

	CPjySmsImp(void);

	virtual ~CPjySmsImp(void);

//�ӿ�ʵ��
protected:

	//���Ͷ���
	virtual HRESULT SendMessage(char* szPhoneNo,char* szMessage);

	//�ͷŶ���
	virtual void ReleaseObject();


};

#endif // __PJY_IMP_H__
