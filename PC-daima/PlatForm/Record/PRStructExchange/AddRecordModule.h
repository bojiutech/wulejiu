#pragma once
#include "basemessage.h"
#include "gameroommessage.h"
#include "PRStructExchange.h"
#include "..\include\interface.h"
#include "..\\include\struct.h"
/********************************************************************
	created:	2009/02/24
	created:	24:2:2009   17:25
	filename: 	\Record\PRStructExchange\AddRecordModule.h
	file path:	\project\Record\PRStructExchange
	file base:	AddRecordModule
	file ext:	h
	author:		yjj
	
	purpose:  ���¼�������̵ķ�װ��	
  
  Copyright szbzw 2009 - All Rights Reserved

*********************************************************************/

//��ƽ̨���¼��ģ����
class CAddRecordModule
{
public:
	CAddRecordModule(void);
	~CAddRecordModule(void);

	//���ܺ���	
	/**
	* ����¼��ģ�� ���뷿������
	* @param [in] pAppPath ���г������ڵ�Ŀ¼
	* @param [in] bool bIsRecordAvailable �Ƿ�����¼����
	* @return  �����ɹ�������true,����ʧ�ܣ�����false
	*/
	bool CreatRecorMoudle(const TCHAR* pAppPath,bool bIsRecordAvailable);      //����¼����
	
	/**
	* ��ʼ��¼����bool CGameRoomEx::StartGameClient() �е���
	* @param [in] sourcegameinfo ��Ϸ������Ϣ�ṹ
	* @param [in] szClienDllName ��Ϸico����
	* @param [in] bMyDeskStation �Լ�����λ
	* @return 
	*/
	void InitRecordMoudle(GameInfoStruct* sourcegameinfo,TCHAR* szClienDllName,BYTE bMyDeskStation);      //��ʼ��¼����	
	
	/**
	* ����¼���ļ�����һ����Ϸ��bool CGameRoomEx::OnRoomMessage ASS_GR_GAME_END��֧�±�����Ϸ�������û���ҵ�oncancleʱ����
	* @param [in] pAppPath ��ִ�г��������
	* @param [in] pMyName �Լ��������
	* @param [in] uNameId ��Ϸ��id��
	* @return bool ����ɹ�������true,����ʧ�ܣ�����false
	*/
	bool SaveRecordFile(const TCHAR* pAppPath,const TCHAR* pMyName,UINT uNameId);        //����¼���ļ�
	
	/**
	* ������Ϸ�û���Ϣ����һ����Ϸ��bool CGameRoomEx::OnRoomMessage ASS_GR_GAME_BEGIN��֧�»��߶��߻������ó���ʱ���á�
	* ��ѱ��������е���Ҿ�������¼��ϵͳ�����򲥷��޷�������ԭ
	* @param [in] pUserItem ��Ϸ������Ϣ�ṹ
	* @param [in] pMeUserInfo ��Ϸico����
	* @param [in] bMyDeskStation �Լ�����λ
	* @return 
	*/
	void SetUserInfo2Record(const UserItemStruct* pUserItem,const UserItemStruct* pMeUserInfo); //��¼��ϵͳ�����û���Ϣ

	/**
	* ��¼�����м�����Ϸ��Ϣ CGameRoomEx::OnSocketReadEvent�е���
	* @param [in] pNetHead ��Ϣͷ
	* @param [in] pNetData ��Ϣ����
	* @param [in] uDataSize ��Ϣ��С
	* @return 
	*/
	void AddMsgToRecord(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize);        //��¼��ϵͳ�����Ϸ��Ϣ
	
	/**
	* �жϵ�ǰ����Ϸ״̬
	* @param [in] pGameInfo �Լ��������Ϣ
	* @param [in] pNetHead    ��Ϣͷ
	* @return bool true Ϊ��Ҫ���������Ϣ��falseΪ����Ҫ���������Ϣ
	*/
	bool GetUserGameState(const GameInfoStruct* pGameInfo ,NetMessageHead * pNetHead);
	//��Ա˽�к���
private:
	/**
	* �ͷ�¼��������������������	
	*/
	void ReleaseRecordMoule();    //�ͷ�¼����
	//¼��������
	IRecorderForPlatform           * m_pRecordMoudlePlat;
	HINSTANCE                        m_hRecordInstance;
	bool                             m_bIsRecordAvailable;


};

