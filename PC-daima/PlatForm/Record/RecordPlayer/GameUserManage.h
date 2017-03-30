#pragma once

#ifndef GAMEUSERMANAGE_HEAD_H
#define GAMEUSERMANAGE_HEAD_H

#include "StdAfx.h"
//#include "GamePlace.h"

//��Ϸ�û�������
class CGameUserManage : public IFindUserInterface
{
	//��������
protected:
	CPtrArray								m_ActiveUserPtrArray;			//��û�ָ��
	CPtrArray								m_FreeUserPtrArray;				//�����û�ָ��
	CDWordArray								m_MatchUserID;					//�����û� ID

	//��������
public:
	//���캯��
	CGameUserManage(void);
	//��������
	virtual ~CGameUserManage(void);

	//���ܺ���
public:
	//��������
	bool CleanUserInfo();
	//��ȡ��������
	INT_PTR GetOnLineUserCount() { return m_ActiveUserPtrArray.GetCount(); }
	//�����û�
	UserItemStruct * AddGameUser(UserInfoStruct * pUserInfo, UINT uSortIndex, UINT uConnection);
	//ɾ���û�
	bool DeleteGameUser(long int dwUserID);
	//ɾ���û�
	bool DeleteGameUser(UserItemStruct * pUserInfo);
	//���ӱ����û�
	bool AddMatchUser(long int dwUserID);
	//ɾ�������û�
	bool DeleteMatchUser(long int dwUserID);
	//�Ƿ�����û�
	bool IsMatchUser(long int dwUserID);

	//�ӿں���
public:
	//�����û�
	virtual UserItemStruct * FindOnLineUserByIndex(int index);
	//�����û�
	virtual UserItemStruct * FindOnLineUser(long int dwUserID);
	//�����û�
	virtual UserItemStruct * FindOnLineUser(int dwAccID);
	//�����û�
	virtual INT_PTR FindOnLineUser(const TCHAR * szUserName, CPtrArray & ResultPtrArray);
	//�����û�
	virtual INT_PTR FindOnLineUser(BYTE bDeskIndex, CPtrArray & PlayPtrArray, CPtrArray & WatchPtrArray);
};

#endif