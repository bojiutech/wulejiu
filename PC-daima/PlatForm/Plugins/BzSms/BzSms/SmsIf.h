/********************************************************************
	created:	2012/04/30
	file base:	ISms
	file ext:	h
	author:		
	
	purpose:	SmsͨѶģ��ӿ�
*********************************************************************/
#ifndef __SMSIF_H__
#define __SMSIF_H__

#pragma once

//Plc�����ӿ�
struct ISms
{
	//���Ͷ���
	virtual HRESULT SendMessage(char* szPhoneNo,char* szMessage) = 0;

	//�ͷŶ���
	virtual void ReleaseObject() = 0;

};

//�����ѯ�ӿ�
struct IMobile
{
	//����ֻ�����������
	virtual HRESULT GetCodeInfo(char* szPhoneNo,char* szUserID,char* szResult) = 0;

	//�ͷŶ���
	virtual void ReleaseObject() = 0;
};


//{31C7E553-0F2A-4df0-940D-89664EA6A9B8}
DEFINE_GUID(CLSID_ZServ_Sms, 
			0x31c7e553, 0xf2a, 0x4df0, 0x94, 0xd, 0x89, 0x66, 0x4e, 0xa6, 0xa9, 0xb8);


#endif // __SMSIF_H__
