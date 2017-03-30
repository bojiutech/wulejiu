// ***************************************************************
//  interface   version:  1.0   ��  date: 08/21/2008
//  -------------------------------------------------------------
//  �ӿ��ļ�������Ϸ�����Ͳ��������õ���
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
/********************************************************************
created:	2008/08/21
created:	21:8:2008   9:53
filename: 	d:\����Ŀ¼\¼��ϵͳ\project\include\interface.h
file path:	d:\����Ŀ¼\¼��ϵͳ\project\include
file base:	interface
file ext:	h
author:		yjj	
purpose:	Ϊ��Ϸƽ̨�ͻ��˻���������ṩ��¼��Ϸ���̵Ľӿ�
*********************************************************************/

#pragma once

//���������õĽӿ�
#define GETFORPLATFORM   "GetRecordForPlatForm"   //�õ�Ϊƽ̨���õĽӿ��ַ���
#define GETFORPLAYER     "GetRecordForPlayer"     // �õ�Ϊ���������õĽӿڵ��ַ���
#include "struct.h"

#define  MAX_MSG_HEAD_LEN   50
#define  MAX_MSG_DATA_LEN   (2000)   //���һ����Ϣ����





//���ýӿ�
class IBaseInterFace
{
public:
	virtual void Release() = 0;//  �ͷŶ���

};
//����Ϸƽ̨���õĽӿ�
class IRecorderForPlatform : public IBaseInterFace
{
public:
	/**
	*�����Ϸ�����Ϣ
	* @param [in] pUsrIterInfo ��Ҫ��ӵ������Ϣ
	*/
	virtual void AddUserInfo(RecordUserItemStruct* pUsrIterInfo) = 0;  //���ĳһ��λ�����
	/**
	*��ӵ���¼�����������λ��
	* @param [in] bDeskStation �Լ�����λ��
	* ����ڷ�������ʹ�õĻ����Լ�����λ��Ҫ��Ϊ2
	*/
    virtual void AddMeDeskStation(BYTE bDeskStation) = 0;  
	/**
	* �����Ϸ������Ϣ
	* @param [in] pGameInfo ����������Ϣ
	*/
	virtual void AddRoomGameInfo(RecordGameInfoStruct* pGameInfo) = 0;
	/**
	* ����������Ϣ���������Ϸ��Ϣ����û��ò����������������Щ��Ϣ�����������Ǵ����˶�������Ϊ������Ϣ����ʼ��
	* ���ô���socket������������Ӧ���ǲ�֧�����������Ϣ��
	* @param [in] pNetHead ��Ϣͷ����
	* @param [in] uHeadSize ��Ϣͷ��С
	* @param [in] pNetData ��Ϣ����
	* @param [in] uDataSize ��Ϣ��С
	*/
	virtual bool AddMsg2Record(void* pNetHead,UINT uHeadSize,void * pNetData, UINT uDataSize) = 0;
	/**
	*  �����б������г�ʼ������������������Ϣ����Ϸ������Ϣ������Ϸ��Ϣ,�൱�ڵ���ClearAllMsg ClearAllUerInfo��ClearRoomGameInfo

	*/
	virtual void InitAll() = 0;
	/**
	* ������е���Ϸ��Ϣ��Ϣ
	*/
	virtual void ClearAllMsg() = 0;
	/**
	* ������е��û���Ϣ
	*/
    virtual void ClearAllUserInfo() = 0;
	/**
	* ��� ��Ϸ������Ϣ  
	*/
	virtual void ClearRoomGameInfo() = 0;
	/**
	*   ѹ���������ļ�  ��Ҫ���ڷ��������棬��ʡ�ռ�
	*/
	virtual bool SaveFileWithZip(const TCHAR* pFileName) = 0;
	/**
	*   ѹ������md5У�鱣���ļ������ڿͻ��˱��棬��ֹ�ļ����ƻ�
	*/
	virtual bool SaveFileWithPassZip(const TCHAR* pFileName) = 0;
	/**
	* ���ı����ļ�����Ҫ�ڲ���ʱ��
	*/
	virtual bool SaveFileWithNone(const TCHAR* pFileName) = 0;
	/**
	* ����ѹ�����ܺ��ַ����ĳ���
	*/
	virtual UINT GetParDataSize() = 0;
	/**
	*  �û�ȡ�������ļ���Ϣ���Լ��������д���ļ����ĵط�,ѹ�������ܺ�ģ��û�������ʲô��ʽ�洢,
	*  ����ǰ�벻Ҫ��д��������
	*/
	virtual void GetParsedData(unsigned char* szStr,UINT uInSize,UINT& uOutSize) = 0;

	/**
	*  �����ļ������ڿͻ�������Ӧ�û�����һ�����������򣬴Ӷ������ļ��������˸о����ڵ��ö˻����һЩ
	*  ��ˣ�Ŀǰֻ��һ���ӿڣ�û��ʵ�ָĹ���
	*/
	virtual void CreateFileName(TCHAR* szFileName) = 0;
	/**
	* ����ͻ��˵���־�ļ�����ֹд���ļ�̫�࣬ĿǰֻԤ��һ�ֽӿڣ���û��ʵ��
	* @param [in] iFileNum �ڿͻ��˱������ٸ���־�ļ�
	*/
	virtual void MangRecordFileInClient(int iFileNum) = 0;



};

//�����������õĽӿ�
class IRecorderForPlayer  : public IBaseInterFace
{
public:

	/**
	*  ��ȡ�Լ����û���Ϣ
	*/
	virtual RecordUserItemStruct* GetMeUserInfo() = 0;
	/**
	* ��ȡĳ��λ�õ������Ϣ  
	*/
	virtual RecordUserItemStruct* GetUserInfo(BYTE bDeskStation) = 0;
	/**
	*  ��ȡ��ҵ�����
	*/
	virtual UINT GetGamePlayerNum() const = 0;
	/**
	*  �õ���Ϸ�����������Ϣ
	*/
	virtual RecordGameInfoStruct* GetRoomGameInfo() = 0;
	/**
	*  �õ���Ϣ����
	*/
	virtual int GetTotalMsgCount() const= 0;
	/**
	*  �õ���Ϣ������
	*/
	virtual void GetMsgInfo(int iIndex,void* ppMsgHead,void* ppMsgData,UINT& uHeadSize,UINT& uDataSize,UINT& iTimeSlot) = 0;
	/**
	*  װ��ѹ�������ļ�
	* @param [in] iIndex ��Ҫ�ĵڼ�����Ϣ
	* @param [out] ppMsgHead ��Ϣͷ��ָ��
	* @param [out] ppMsgData ��Ϣ����ָ��
	* @param [out in] uHeadSize ����ppMsgHead�Ĵ�С��������ֵ��ʵ��С
	* @param [out in] uDataSize ����ppMsgData�Ĵ�С��������ֵ��ʵ��С
	* @param [out] iTimeSlot ����һ��Ϣ��ʱ���
	* @return ����ֵ˵��
	*/
	virtual bool LoadFileWithZip(const TCHAR* filename) = 0;
	/**
	*  װ��ѹ�����ܹ����ļ�
	*/
	virtual bool LoadFileWithPassZip(const TCHAR* filename) = 0;
	/**
	*  װ��û�н��й��κδ�����ļ������ģ�
	*/
	virtual bool LoadFileWithNone(const TCHAR* filename) = 0;

	/**
	*  ͨ���ַ�����������Ϣ�������Ǵ����ݿ��ж���ֱ��װ�벥�������Ǽ���ѹ����ʽ
	*/
	virtual bool LoadStringBuffer(unsigned char * pBuffer,UINT uSize) = 0;
	/**
	* �õ��ͻ��˼��ؿ������.ico �ļ�
	*/
	virtual TCHAR* GetClientDllName() = 0;




};

