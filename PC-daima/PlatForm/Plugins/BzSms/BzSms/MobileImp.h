/********************************************************************
	created:	2012/04/30
	file base:	Sms
	file ext:	h
	author:		
	
	purpose:	PJY SMSͨѶʵ��
*********************************************************************/
#ifndef __MOBILE_IMP_H__
#define __MOBILE_IMP_H__

#pragma once

#include <CGuid.h>
#include <initguid.h>

#include "SmsIf.h"
#include "com_mobile.h"

using namespace MobileCodeWS;

class CMobileImp : public CMobileCodeWST<>,
				   public IMobile
{
public:

	CMobileImp(void);

	virtual ~CMobileImp(void);

//�ӿ�ʵ��
protected:

	//����ֻ�����������
	virtual HRESULT GetCodeInfo(char* szPhoneNo,char* szUserID,char* szResult);

	//�ͷŶ���
	virtual void ReleaseObject();


};

#endif // __MOBILE_IMP_H__
