#include "StdAfx.h"
#include "AFCLock.h"

/************************************************************************************************************/

//���캯��
CSignedLockObject::CSignedLockObject(CAFCSignedLock * pLockObject, bool bAutoLock)
{
	m_iLockCount=0;
	m_pLockObject=pLockObject;
	if (bAutoLock) Lock();
	return;
}

//��������
CSignedLockObject::~CSignedLockObject()
{
	while (m_iLockCount>0) UnLock();
	//for (int i=0;i<m_iLockCount;i++) UnLock();
	return;
}

//��������
void CSignedLockObject::Lock()
{
	if (m_pLockObject)
	{
		m_iLockCount++;
		m_pLockObject->Lock();
	}
}

//�������� 
void CSignedLockObject::UnLock()
{
	if (m_pLockObject) 
	{
		m_iLockCount--;
		m_pLockObject->UnLock();
	}
}

/************************************************************************************************************/

//���캯��
CAFCRWLock::CAFCRWLock(void)
{
	m_iReadCount=0L;
	m_hReadLock=::CreateEvent(NULL,TRUE,TRUE,NULL);
	m_hWriteLock[0]=::CreateEvent(NULL,TRUE,TRUE,NULL);
	m_hWriteLock[1]=::CreateEvent(NULL,TRUE,TRUE,NULL);
	::InitializeCriticalSection(&m_csLock);
}

//��������
CAFCRWLock::~CAFCRWLock(void)
{
	::CloseHandle(m_hReadLock);
	::CloseHandle(m_hWriteLock[0]);
	::CloseHandle(m_hWriteLock[1]);
	::DeleteCriticalSection(&m_csLock);
}

//��д
bool CAFCRWLock::LockWrite(DWORD dwWaitTime)
{
	bool bSuccess=false;
	::EnterCriticalSection(&m_csLock);
	::ResetEvent(m_hWriteLock[1]);
	if (::WaitForSingleObject(m_hReadLock,dwWaitTime)!=WAIT_TIMEOUT)
	{
		::ResetEvent(m_hWriteLock[0]);
		bSuccess=TRUE;
	}
	else ::SetEvent(m_hWriteLock[1]);
	::LeaveCriticalSection(&m_csLock);
	return bSuccess;
}

//����
bool CAFCRWLock::LockRead(DWORD dwWaitTime)
{
	bool bSuccess=false;
	::EnterCriticalSection(&m_csLock);
	if (::WaitForMultipleObjects(2,m_hWriteLock,TRUE,dwWaitTime)!=WAIT_TIMEOUT)
	{
		bSuccess=true;
		::InterlockedIncrement(&m_iReadCount);
		::ResetEvent(m_hReadLock);
	}
	::LeaveCriticalSection(&m_csLock);
	return bSuccess;
}

//��д
bool CAFCRWLock::UnLockWrite()
{
	::SetEvent(m_hWriteLock[0]);
	::SetEvent(m_hWriteLock[1]);
	return true;
}

//���
bool CAFCRWLock::UnLockRead()
{
	if (::InterlockedDecrement(&m_iReadCount)<=0) ::SetEvent(m_hReadLock);
 	return true;
}


