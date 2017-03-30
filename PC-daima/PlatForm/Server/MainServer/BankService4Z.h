#pragma once

#ifndef AFC_BANK_SERVICE_HEAD_FILE
#define AFC_BANK_SERVICE_HEAD_FILE

#include "Stdafx.h"
#include "AFCDataBase.h"

#include "BankMessage.h"
#include "Bank4ZMessage.h"
#include "Bank4ZDatabaseMessage.h"

class CGameMainManage;
class CGameLogonManage;

class CBankService4Z
{

public:

	CBankService4Z(CWnd *pWnd);

	~CBankService4Z(void);

public:

	//�յ���������
	bool OnNetMessage(NetMessageHead* pNetHead,void* pData,UINT uSize,ULONG uAccessIP,UINT uIndex,DWORD dwHandleID);

	//������������������
	bool OnDataBaseResult(DataBaseResultLine* pResultData); 

//�������������ʵ��
public:

	//������
	bool OnOpenBankRequest(void* pData,UINT uSize,UINT uIndex,DWORD dwHandleID);

	//��ѯǮ��
	bool OnGetGameWalletRequest(void* pData,UINT uSize,UINT uIndex,DWORD dwHandleID);

	//��ȡǮ
	bool OnCheckMoneyRequest(void* pData,UINT uSize,UINT uIndex,DWORD dwHandleID);

	//ת��
	bool OnTransferRequest(void* pData,UINT uSize,UINT uIndex,DWORD dwHandleID);

	//��ѯ�˵�
	bool OnTransRecordRequest(void* pData,UINT uSize,UINT uIndex,DWORD dwHandleID);

	//�浥ҵ��
	bool OnDepositRequest(void* pData,UINT uSize,UINT uIndex,DWORD dwHandleID);

	//��ѯ�浥
	bool OnQueryDepositsRequest(void* pData,UINT uSize,UINT uIndex,DWORD dwHandleID);

	//�޸���������
	bool OnChangePasswordRequest(void* pData,UINT uSize,UINT uIndex,DWORD dwHandleID);

	//�õ����˲������
	bool OnGetFinanceInfoRequest(void* pData,UINT uSize,UINT uIndex,DWORD dwHandleID);

	//��ҷ����޸�
	bool OnUserSetRebateRequest(void* pData,UINT uSize,UINT uIndex,DWORD dwHandleID);

//������������ʵ��
public:

	//����ҷ����޸Ľ������������sdp
	bool OnGetBankUserSetRebateResponse(DataBaseResultLine* pResultData);

	//����ҷ�����ѯ���ݷ���������sdp
	bool OnGetBankUserRebateResponse(DataBaseResultLine* pResultData);

	//���������ݷ���������sdp
	bool OnGetBankRebateResponse(DataBaseResultLine* pResultData);

	//������
	bool OnOpenBankResponse(DataBaseResultLine* pResultData);

	//��ѯǮ��
	bool OnGetGameWalletResponse(DataBaseResultLine* pResultData);

	//��ȡǮ
	bool OnCheckMoneyResponse(DataBaseResultLine* pResultData);

	//ת��
	bool OnTransferReponse(DataBaseResultLine* pResultData);

	//��ѯ�˵�
	bool OnTransRecordResponse(DataBaseResultLine* pResultData);

	//�浥ҵ��
	bool OnDepositResponse(DataBaseResultLine* pResultData);

	//��ѯ�浥
	bool OnQueryDepositsResponse(DataBaseResultLine* pResultData);

	//�޸���������
	bool OnChangePasswordResponse(DataBaseResultLine* pResultData);

	//��ȡ����״��
	bool OnGetFinanceInfoResponse(DataBaseResultLine* pResultData);


private:

	//������ģ��
	CGameMainManage* m_pMainManage;

	//��½����ģ��
	CGameLogonManage* m_pLogonManage;

	double	m_iVIP_Rate;	//vip������
};

#endif

