#pragma once

#include "../include/interface.h"
#include "interStruct.h"
#include <vector>
#include "MD5.h"
using namespace std;



//¼��������
class CRecorder:public IRecorderForPlatform,public IRecorderForPlayer
{
public:
	CRecorder(void);
	virtual ~CRecorder(void);

public:
	//�ͷŶ���
	void Release() {delete this;}

	//*****************************************************************************

	//��ƽ̨�û����õĽӿ�
	/**
	*�����Ϸ�����Ϣ	
	*/
	virtual void AddUserInfo(RecordUserItemStruct* pUsrIterInfo); //���ĳһ��λ�����
	/**
	*��ӵ���¼�����������λ��
	*/
	virtual void AddMeDeskStation(BYTE bDeskStation);  
	/**
	* �����Ϸ������Ϣ	
	*/
	virtual void AddRoomGameInfo(RecordGameInfoStruct* pGameInfo);
	/**
	* ����������Ϣ���������Ϸ��Ϣ����û��ò����������������Щ��Ϣ�����������Ǵ����˶�������Ϊ������Ϣ����ʼ��
	* ���ô���socket������������Ӧ���ǲ�֧�����������Ϣ��	
	*/
	virtual bool AddMsg2Record(void* pNetHead,UINT uHeadSize,void * pNetData, UINT uDataSize);
	/**
	*  �����б������г�ʼ������������������Ϣ����Ϸ������Ϣ������Ϸ��Ϣ,�൱�ڵ���ClearAllMsg ClearAllUerInfo��ClearRoomGameInfo
	*/
	virtual void InitAll();
	/**
	* ������е���Ϸ��Ϣ��Ϣ
	*/
	virtual void ClearAllMsg();
	/**
	* ������е��û���Ϣ
	*/
	virtual void ClearAllUserInfo();
	/**
	* ��� ��Ϸ������Ϣ  
	*/
	virtual void ClearRoomGameInfo();
	/**
	*   ѹ���������ļ�  ��Ҫ���ڷ��������棬��ʡ�ռ�
	*/
	virtual bool SaveFileWithZip(const TCHAR* pFileName);
	/**
	*   ѹ������md5У�鱣���ļ������ڿͻ��˱��棬��ֹ�ļ����ƻ�
	*/
	virtual bool SaveFileWithPassZip(const TCHAR* pFileName);
	/**
	* ���ı����ļ�����Ҫ�ڲ���ʱ��
	*/
	virtual bool SaveFileWithNone(const TCHAR* pFileName);
	/**
	* ����ѹ�����ܺ��ַ����ĳ���
	*/
	virtual UINT GetParDataSize();
	/**
	*  �����ַ��������û�������ô��ʹ����Щ��Ϣ
	*/
	virtual void GetParsedData(unsigned char* szStr,UINT uInSize,UINT& uOutSize);

	/**
	*  �����ļ������ڿͻ�������Ӧ�û�����һ�����������򣬴Ӷ������ļ��������˸о����ڵ��ö˻����һЩ
	*  ��ˣ�Ŀǰֻ��һ���ӿڣ���û��ʵ��
	*/
	virtual void CreateFileName(TCHAR* szFileName){}
	virtual void MangRecordFileInClient(int iFileNum){}

	//*****************************************************************************
	//�����������õĽӿ�
	/**
	*  ��ȡ�Լ����û���Ϣ
	*/
	virtual RecordUserItemStruct* GetMeUserInfo();
	/**
	* ��ȡĳ��λ�õ������Ϣ  
	*/
	virtual RecordUserItemStruct* GetUserInfo(BYTE bDeskStation);
	/**
	*  ��ȡ��ҵ�����
	*/
	virtual UINT GetGamePlayerNum() const;
	/**
	*  �õ���Ϸ�����������Ϣ
	*/
	virtual RecordGameInfoStruct* GetRoomGameInfo();
	/**
	*  �õ���Ϣ����
	*/
	virtual int GetTotalMsgCount() const;
	/**
	*  �õ���Ϣ������
	*/
	virtual void GetMsgInfo(int iIndex,void* ppMsgHead,void* ppMsgData,UINT& uHeadSize,UINT& uDataSize,UINT& iTimeSlot);
	/**
	*  װ��ѹ�������ļ�	
	*/
	virtual bool LoadFileWithZip(const TCHAR* filename);
	/**
	*  װ��ѹ�����ܹ����ļ�
	*/
	virtual bool LoadFileWithPassZip(const TCHAR* filename);
	/**
	*  װ��û�н��й��κδ�����ļ������ģ�
	*/
	virtual bool LoadFileWithNone(const TCHAR* filename);
	/**
	*  ͨ���ַ�����������Ϣ�������Ǵ����ݿ��ж���ֱ��װ�벥�������Ǽ���ѹ����ʽ
	*/
	virtual bool LoadStringBuffer(unsigned char * pBuffer,UINT uSize);
	/**
	* �õ��ͻ��˼��ؿ������.ico �ļ�
	*/
	virtual TCHAR* GetClientDllName() {return m_FileHead.RoomGameInfo.szClientDLLName;}

private:
	//*****************************************************************************
	//�Լ���Ҫ�Ĺ��ܺ���
	void Md5Data(UINT uFileType); //�����ݽ���md5����
	
	bool Write2File(const TCHAR* pFileName,const unsigned char* pBuffer,UINT uBufferLen);
    bool Write2File(const TCHAR* pFileName);
	bool LoadZip(const TCHAR* filename,UINT uFileType);
	bool CheckMd5();
	
	
private:
	//��Ա����
	//ǰ�������ļ�ͷ
    FileHeadStruct  m_FileHead;
	
	//�ļ���Ϣ
	vector <RecordNetMsgStruct> m_arryMsgList;

	//����Ƿ��ٿ���״̬
	bool m_bEnable;
    //��ǰ������Ϣ������
	int m_iMsgCount;
	//�յ���һ����Ϣ��ʱ��
	UINT m_uMsgRecTime;
};




