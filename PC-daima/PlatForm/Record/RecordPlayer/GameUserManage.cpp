#include "StdAfx.h"
#include "GameUserManage.h"

//���캯��
CGameUserManage::CGameUserManage(void)
{
	m_FreeUserPtrArray.SetSize(0,10);
	m_ActiveUserPtrArray.SetSize(0,10);
}

//��������
CGameUserManage::~CGameUserManage(void)
{
	CleanUserInfo();
}

//��������
bool CGameUserManage::CleanUserInfo()
{
	for (int i=0;i<m_FreeUserPtrArray.GetCount();i++)
	{
		UserItemStruct * pUserItem=(UserItemStruct *)m_FreeUserPtrArray.GetAt(i);
		if (pUserItem!=NULL) delete pUserItem;
	}
	for (int i=0;i<m_ActiveUserPtrArray.GetCount();i++)
	{
		UserItemStruct * pUserItem=(UserItemStruct *)m_ActiveUserPtrArray.GetAt(i);
		if (pUserItem!=NULL) delete pUserItem;
	}
	m_FreeUserPtrArray.RemoveAll();
	m_ActiveUserPtrArray.RemoveAll();

	return true;
}

//�����û�
UserItemStruct * CGameUserManage::AddGameUser(UserInfoStruct * pUserInfo, UINT uSortIndex, UINT uConnection)
{
	//pUserInfo->bDeskNO =1;
	//pUserInfo->bDeskStation=1;
	try
	{
		//���������û�
		bool bNewItem=false;
		UserItemStruct * pUserItem=FindOnLineUser(pUserInfo->dwUserID);
		if (pUserItem==NULL)
		{
			//���ҿ����û�
			INT_PTR uFreeCount=m_FreeUserPtrArray.GetCount();
			if (uFreeCount>0L)
			{
				bNewItem=true;
				pUserItem=(UserItemStruct *)m_FreeUserPtrArray.GetAt(uFreeCount-1);
				ASSERT(pUserItem!=NULL);
				m_FreeUserPtrArray.RemoveAt(uFreeCount-1);
			}

			//�����ڴ�
			if (pUserItem==NULL)
			{
				bNewItem=true;
				pUserItem=new UserItemStruct;
				ASSERT(pUserItem!=NULL);
			}
		}

		//��д�û���Ϣ
		pUserItem->uSortIndex=uSortIndex;
		pUserItem->uConnection=uConnection;
		pUserItem->GameUserInfo=*pUserInfo;
		pUserItem->dwLogonTime=(long int)time(NULL);
		pUserItem->bMatchUser=IsMatchUser(pUserInfo->dwUserID);
		//�������
		if (bNewItem==true) m_ActiveUserPtrArray.Add(pUserItem);

		return pUserItem;
	}
	catch (...)	{ }
	return NULL;
}

//ɾ���û�
bool CGameUserManage::DeleteGameUser(long int dwUserID)
{
	//�����û�ָ��
	INT_PTR uActiveCount=m_ActiveUserPtrArray.GetCount();
	for (int i=0;i<uActiveCount;i++)
	{
		UserItemStruct * pDeleteUserItem=(UserItemStruct *)m_ActiveUserPtrArray.GetAt(i);
		if ((pDeleteUserItem!=NULL)&&(pDeleteUserItem->GameUserInfo.dwUserID==dwUserID))
		{
			//ɾ���ָ��
			UserItemStruct * pTempItem=(UserItemStruct *)m_ActiveUserPtrArray.GetAt(uActiveCount-1);
			m_ActiveUserPtrArray.SetAt(i,pTempItem);
			m_ActiveUserPtrArray.SetAt(uActiveCount-1,NULL);
			m_ActiveUserPtrArray.RemoveAt(uActiveCount-1);

			//�������ָ��
			memset(pDeleteUserItem,0,sizeof(UserItemStruct));
			m_FreeUserPtrArray.Add(pDeleteUserItem);
			return true;
		}
	}
	return false;
}

//ɾ���û�
bool CGameUserManage::DeleteGameUser(UserItemStruct * pUserInfo)
{
	//���ñ���
	UserItemStruct * pTempItem=NULL;
	INT_PTR uActiveCount=m_ActiveUserPtrArray.GetCount();
	if (uActiveCount>0)	pTempItem=(UserItemStruct *)m_ActiveUserPtrArray.GetAt(uActiveCount-1);

	//�����û�ָ��
	for (int i=0;i<uActiveCount;i++)
	{
		if (((UserItemStruct *)m_ActiveUserPtrArray.GetAt(i))==pUserInfo)
		{
			//ɾ���ָ��
			m_ActiveUserPtrArray.SetAt(i,pTempItem);
			m_ActiveUserPtrArray.SetAt(uActiveCount-1,NULL);
			m_ActiveUserPtrArray.RemoveAt(uActiveCount-1);

			//�������ָ��
			memset(pUserInfo,0,sizeof(UserItemStruct));
			m_FreeUserPtrArray.Add(pUserInfo);
			return true;
		}
	}
	return false;
}

//���ӱ����û�
bool CGameUserManage::AddMatchUser(long int dwUserID)
{
	for (INT_PTR i=0;i<m_MatchUserID.GetCount();i++)
	{
		if (m_MatchUserID.GetAt(i)==dwUserID) return true;
	}
	m_MatchUserID.Add(dwUserID);
	return true;
}

//ɾ�������û�
bool CGameUserManage::DeleteMatchUser(long int dwUserID)
{
	for (INT_PTR i=0;i<m_MatchUserID.GetCount();i++)
	{
		if (m_MatchUserID.GetAt(i)==dwUserID) 
		{
			m_MatchUserID.RemoveAt(i);
			return true;
		}
	}
	return false;
}

//�Ƿ�����û�
bool CGameUserManage::IsMatchUser(long int dwUserID)
{
	for (INT_PTR i=0;i<m_MatchUserID.GetCount();i++)
	{
		if (m_MatchUserID.GetAt(i)==dwUserID) return true;
	}
	return false;
}
//�����û�
UserItemStruct * CGameUserManage::FindOnLineUserByIndex(int index)
{
	return (UserItemStruct *)m_ActiveUserPtrArray.GetAt(index);
}
//�����û�
UserItemStruct * CGameUserManage::FindOnLineUser(int dwAccID)
{
	//�����û�ָ��
	INT_PTR uActiveCount=m_ActiveUserPtrArray.GetCount();
	for (int i=0;i<uActiveCount;i++)
	{
		UserItemStruct * pFindUserItem=(UserItemStruct *)m_ActiveUserPtrArray.GetAt(i);
		if ((pFindUserItem!=NULL)&&(pFindUserItem->GameUserInfo.dwAccID==dwAccID)) return pFindUserItem;
	}
	return NULL;
}

//�����û�
UserItemStruct * CGameUserManage::FindOnLineUser(long int dwUserID)
{
	//�����û�ָ��
	INT_PTR uActiveCount=m_ActiveUserPtrArray.GetCount();
	for (int i=0;i<uActiveCount;i++)
	{
		UserItemStruct * pFindUserItem=(UserItemStruct *)m_ActiveUserPtrArray.GetAt(i);
		if ((pFindUserItem!=NULL)&&(pFindUserItem->GameUserInfo.dwUserID==dwUserID)) 
			return pFindUserItem;
	}
	return NULL;
}

//�����û�
INT_PTR CGameUserManage::FindOnLineUser(const TCHAR * szUserName, CPtrArray & ResultPtrArray)
{
	//�����û�ָ��
	CString strBuffer;
	INT_PTR uActiveCount=m_ActiveUserPtrArray.GetCount(),uFindCount=0;
	for (int i=0;i<uActiveCount;i++)
	{
		UserItemStruct * pFindUserItem=(UserItemStruct *)m_ActiveUserPtrArray.GetAt(i);
		if (pFindUserItem!=NULL)
		{
			strBuffer=pFindUserItem->GameUserInfo.nickName;
			strBuffer.MakeLower();
			if (strBuffer.Compare(szUserName)==0)
			{
				uFindCount++;
				ResultPtrArray.Add(pFindUserItem);
			}
		}
	}
	return uFindCount;
}

//�����û�
INT_PTR CGameUserManage::FindOnLineUser(BYTE bDeskIndex, CPtrArray & PlayPtrArray, CPtrArray & WatchPtrArray)
{
	INT_PTR uActiveCount=m_ActiveUserPtrArray.GetCount(),uFindCount=0;
	for (int i=0;i<uActiveCount;i++)
	{
		UserItemStruct * pFindUserItem=(UserItemStruct *)m_ActiveUserPtrArray.GetAt(i);
		if (pFindUserItem!=NULL)
		{
			if (pFindUserItem->GameUserInfo.bDeskNO==bDeskIndex)
			{
				uFindCount++;
				if (pFindUserItem->GameUserInfo.bUserState==USER_WATCH_GAME) WatchPtrArray.Add(pFindUserItem);
				else PlayPtrArray.Add(pFindUserItem);
			}
		}
	}
	return uFindCount;
}


