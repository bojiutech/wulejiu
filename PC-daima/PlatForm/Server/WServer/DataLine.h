#pragma once

#include "StdAfx.h"
#include "AFCLock.h"

//�����궨��
#define LD_DEF_STEP				4096								//���ݶ��л��岽��
#define LD_MAX_PART				3096								//���ݰ���󳤶�
#define LD_MAX_DATA				650000								//���ݶ�����󳤶�

//���ݶ�����Ϣͷ
struct DataLineHead
{
	UINT						uSize;								//���ݴ�С
	UINT						uDataKind;							//��������
};

//���ݶ�����
class EXT_CLASS CDataLine
{
	//��������
private:
	UINT						m_uStep;							//�����벽��
	UINT						m_uBufferLen;						//����������
	UINT						m_uAddPos;							//���ݲ����
	UINT						m_uEndPos;							//���ݽ�����
	UINT						m_uGetDataPos;						//��ǰ��ȡ��
	UINT						m_uDataSize;						//���ݴ�С
	UINT						m_uMaxDataLine;						//������ݰ���С
	BYTE						* m_pDataBuffer;					//���ݻ�����
	HANDLE						m_hCompletionPort;					//��ɶ˿�
	const UINT					m_uMaxLength;						//������ݳ���
	CAFCSignedLock				m_csLock;							//ͬ����

	//��������
public:
	//���캯��
	CDataLine(UINT uStep=LD_DEF_STEP, UINT uMaxDataLine=LD_MAX_PART, UINT uMaxLength=LD_MAX_DATA);
	//��������
	virtual ~CDataLine(void);

	//���ܺ���
public:
	//��ȡ��
	CAFCSignedLock * GetLock() { return &m_csLock; };
	//��ȡ��������Ϣ
	bool GetBufferInfo(UINT & uDataSize, UINT & uBufferLen, UINT & uMaxLength);
	//������������
	bool CleanLineData();
	//������ɶ˿�
	void SetCompletionHandle(HANDLE hCompletionPort) { m_hCompletionPort=hCompletionPort; }
	//������Ϣ����
	virtual UINT AddData(DataLineHead * pDataInfo, UINT uAddSize, UINT uDataKind, void * pAppendData=NULL, UINT uAppendAddSize=0);
	//��ȡ��Ϣ����
	virtual UINT GetData(DataLineHead * pDataBuffer, UINT uBufferSize);
};

