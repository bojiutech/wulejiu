#include "DataLine.h"
#include "StdAfx.h"
#include "DataLine.h"
#include "AFCFunction.h"

//���캯��
CDataLine::CDataLine()
{
}

//��������
/*
Function	:~CDataLIne
Memo		:������������������л������ݣ�Ҫ�����ݴ������
Author			:Fred Huang
Add Data		:2008-3-4
Modify Data		:none
*/
CDataLine::~CDataLine(void)
{
	ListItemData *pListItem=NULL;
	while(m_DataList.GetCount()>0)
	{
		pListItem=m_DataList.GetHead();
		m_DataList.RemoveHead();
		delete pListItem->pData;
		delete pListItem;
	}
//	SafeDeleteArray(m_pDataBuffer);
}

//������Ϣ����
/*
Function		:AddData
Memo			:������ѹ�뵽���е���
Author			:Fred Huang
Add Data		:2008-3-4
Modify Data		:none
Parameter		:
[IN]		pDataInfo	:Ҫѹ����е�����ָ��
[IN]		uAddSize	:���ݴ�С
[IN]		uDataKind	:��������
[IN]		pAppendData	:�������ݣ������ǿյ�
[IN]		pAppendAddSize	:�������ݴ�С������Ϊ0����ʱʵ������Ϊ��
Return			:ָѹ����еĴ�С	
*/
UINT CDataLine::AddData(DataLineHead * pDataInfo, UINT uAddSize, UINT uDataKind, void * pAppendData, UINT uAppendAddSize)
{
	CSignedLockObject LockObject(&m_csLock,true);

	if(!m_hCompletionPort)
		return 0;

	ListItemData *pListItem=new ListItemData;//����һ��������

	pListItem->pData=NULL;										//����Ϊ0���Ա�֤����������
	pListItem->stDataHead.uSize=uAddSize;						//���ݴ�С
	pListItem->stDataHead.uDataKind=uDataKind;					//��������
	if(pAppendData)												//����и�������
		pListItem->stDataHead.uSize+=uAppendAddSize;
	pListItem->pData=new BYTE[pListItem->stDataHead.uSize+1];	//�����������ڴ�
	ZeroMemory(pListItem->pData,pListItem->stDataHead.uSize+1);	//����ڴ�
	
	pDataInfo->uDataKind=uDataKind;
	pDataInfo->uSize=pListItem->stDataHead.uSize;

	memcpy(pListItem->pData,pDataInfo,uAddSize);				//����ʵ������
	if(pAppendData!=NULL)										//����и������ݣ�������ʵ�����ݺ���
		memcpy(pListItem->pData+uAddSize,pAppendData,uAppendAddSize);

	m_DataList.AddTail(pListItem);								//�ӵ�����β��

	::PostQueuedCompletionStatus(m_hCompletionPort,pListItem->stDataHead.uSize,NULL,NULL);	//֪ͨ��ɶ˿�

	return pListItem->stDataHead.uSize;		//���ش�С
}

//��ȡ��Ϣ����
/*
Function		:GetData
Memo			:�Ӷ�����ȡ������
Author			:Fred Huang
Add Data		:2008-3-4
Modify Data		:none
Parameter		:
[OUT]		pDataBuffer	:ȡ�����ݵĻ���
[IN]		uBufferSize	:�����С��ȱʡΪ LD_MAX_PART = 3096
Return			:ȡ�����ݵ�ʵ�ʴ�С	
*/
UINT CDataLine::GetData(DataLineHead * pDataBuffer, UINT uBufferSize)
{
	CSignedLockObject LockObject(&m_csLock,true);
	
	memset(pDataBuffer,0,uBufferSize);
	//��������ǿյģ�ֱ�ӷ���
	if(m_DataList.GetCount()<=0)
		return 0;

	//ȡ����
	ListItemData *pListItem=m_DataList.GetHead();
	m_DataList.RemoveHead();

	UINT uDataSize=pListItem->stDataHead.uSize;
	//Ͷ������
	memcpy((void*)pDataBuffer,pListItem->pData,uDataSize);
	
	//ɾ�������е�����
	delete []pListItem->pData;
	delete pListItem;

	return uDataSize;
}

//������������
/*
Function	:CleanLIneData
Memo		:��ն���
Author			:Fred Huang
Add Data		:2008-3-4
Modify Data		:none
Parameter		:
Return			:Wether clean up
*/
bool CDataLine::CleanLineData()
{
	CSignedLockObject LockObject(&m_csLock,true);

	//�������� 
	ListItemData *pListItem=NULL;
	while(m_DataList.GetCount()>0)
	{
		pListItem=m_DataList.GetHead();
		m_DataList.RemoveHead();
		delete pListItem->pData;
		delete pListItem;
	}

	return true;
}

//������������
/*
Function	:GetDataCount
Memo		:Get count of data in list buffer
Author			:Fred Huang
Add Data		:2008-3-5
Modify Data		:none
Parameter		:none
Return			:Count of data in list buffer
*/
INT_PTR CDataLine::GetDataCount(void)
{
	CSignedLockObject LockObject(&m_csLock,true);
	return m_DataList.GetCount();
}
