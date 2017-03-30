#include "StdAfx.h"
#include "DataLine.h"
#include "AFCFunction.h"

//���캯��
CDataLine::CDataLine(UINT uStep, UINT uMaxDataLine, UINT uMaxLength) : m_uMaxLength(uMaxLength)
{
	//��������
	m_uEndPos=0;
	m_uAddPos=0;
	m_uDataSize=0;
	m_uGetDataPos=0;
	m_uStep=uStep;
	m_uBufferLen=0;
	m_pDataBuffer=NULL;
	m_hCompletionPort=NULL;
	m_uMaxDataLine=uMaxDataLine;
}

//��������
CDataLine::~CDataLine(void)
{
	SafeDeleteArray(m_pDataBuffer);
}

//������Ϣ����
UINT CDataLine::AddData(DataLineHead * pDataInfo, UINT uAddSize, UINT uDataKind, void * pAppendData, UINT uAppendAddSize)
{
	if ((m_hCompletionPort!=NULL)||((uAddSize+uAppendAddSize)<=m_uMaxDataLine))
	{
		CSignedLockObject LockObject(&m_csLock,true);

		//��ʼ������
		pDataInfo->uSize=uAddSize;
		pDataInfo->uDataKind=uDataKind;
		if (pAppendData!=NULL) pDataInfo->uSize+=uAppendAddSize;
		else uAppendAddSize=0;

		try
		{
			//Ч�黺����
			if ((m_uDataSize+pDataInfo->uSize)>m_uBufferLen)  throw TEXT("����������");
			else if ((m_uAddPos==m_uEndPos)&&((m_uAddPos+pDataInfo->uSize)>m_uBufferLen)) 
			{
				if (m_uGetDataPos>=pDataInfo->uSize) m_uAddPos=0;
				else throw TEXT("����������");
			}
			else if ((m_uAddPos<m_uEndPos)&&((m_uAddPos+pDataInfo->uSize)>m_uGetDataPos)) throw TEXT("����������");
		}
		catch (...)
		{
			//Ч���Ƿ񳬹���󳤶�
			if ((m_uMaxLength>0)&&((m_uDataSize+pDataInfo->uSize)>m_uMaxLength)) return 0;

			try
			{
				//�����ڴ�
				UINT uNewBufferLen=__min(m_uMaxLength,__max(m_uBufferLen+m_uStep,m_uDataSize+pDataInfo->uSize));
				BYTE * pNewBuffer=new BYTE [uNewBufferLen];
				if (pNewBuffer==NULL) return 0;

				//��������
				if (m_pDataBuffer!=NULL) 
				{
					::CopyMemory(pNewBuffer,m_pDataBuffer+m_uGetDataPos,m_uEndPos-m_uGetDataPos);
					if (m_uEndPos-m_uGetDataPos<m_uDataSize)
						::CopyMemory(pNewBuffer+m_uEndPos-m_uGetDataPos,m_pDataBuffer,m_uAddPos);
				}

				//��������
				SafeDeleteArray(m_pDataBuffer);
				m_pDataBuffer=pNewBuffer;
				m_uBufferLen=uNewBufferLen;
				m_uGetDataPos=0;
				m_uAddPos=m_uDataSize;
				m_uEndPos=m_uDataSize;
			}
			catch (...) { return 0; }
		}

		//��������
		try
		{
			CopyMemory(m_pDataBuffer+m_uAddPos,pDataInfo,uAddSize);
			if (pAppendData!=NULL) ::CopyMemory(m_pDataBuffer+m_uAddPos+uAddSize,pAppendData,uAppendAddSize);
			m_uAddPos+=pDataInfo->uSize;
			m_uDataSize+=pDataInfo->uSize;
			m_uEndPos=__max(m_uEndPos,m_uAddPos);
			::PostQueuedCompletionStatus(m_hCompletionPort,pDataInfo->uSize,NULL,NULL);
			return pDataInfo->uSize;
		}
		catch (...) { }
	}

	return 0;
}

//��ȡ��Ϣ����
UINT CDataLine::GetData(DataLineHead * pDataBuffer, UINT uBufferSize)
{
	CSignedLockObject LockObject(&m_csLock,true);

	if ((m_uDataSize>0)&&(m_pDataBuffer!=NULL))
	{
		//Ч������
		if (m_uGetDataPos==m_uEndPos)
		{
			m_uGetDataPos=0;
			m_uEndPos=m_uAddPos;
		}
		
		//ָ������
		DataLineHead * pDataInfo=(DataLineHead *)(m_pDataBuffer+m_uGetDataPos);
		if (pDataInfo->uSize>uBufferSize)
		{
			m_uGetDataPos+=pDataInfo->uSize;
			m_uDataSize-=pDataInfo->uSize;
			return 0;
		}

		//��������
		try
		{
			CopyMemory(pDataBuffer,pDataInfo,pDataInfo->uSize);
			m_uGetDataPos+=pDataInfo->uSize;
			m_uDataSize-=pDataInfo->uSize;
			return pDataInfo->uSize;
		}
		catch (...) { }
	}

	return 0;
}

//��ȡ��������Ϣ
bool CDataLine::GetBufferInfo(UINT & uDataSize, UINT & uBufferLen, UINT & uMaxLength)
{
	CSignedLockObject LockObject(&m_csLock,true);

	uDataSize=m_uDataSize;
	uBufferLen=m_uBufferLen;
	uMaxLength=m_uMaxLength;

	return true;
}

//������������
bool CDataLine::CleanLineData()
{
	CSignedLockObject LockObject(&m_csLock,true);

	//�������� 
	m_uBufferLen=0;
	m_uAddPos=0;
	m_uEndPos=0;
	m_uGetDataPos=0;
	m_uDataSize=0;
	SafeDeleteArray(m_pDataBuffer);

	return true;
}
