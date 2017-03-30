#include "StdAfx.h"
#include "BankService4Z.h"
#include "GameMainManage.h"
#include "GameLogonManage.h"
#include "commonuse.h"


CBankService4Z::CBankService4Z(CWnd *pWnd)
{
	//������ģ��
	m_pMainManage = (CGameMainManage*)pWnd;

	//��½����ģ��
	m_pLogonManage = (CGameLogonManage*)pWnd;

	m_iVIP_Rate = 1.0;
}


CBankService4Z::~CBankService4Z(void)
{

}


bool CBankService4Z::OnNetMessage(NetMessageHead *pNetHead, void* pData, UINT uSize, ULONG uAccessIP, UINT uIndex, DWORD dwHandleID)
{
	if (!m_pMainManage) 
	{
		return true;
	}

	if (pNetHead->bMainID != MDM_GP_BANK)
	{
		return true;
	}

	switch(pNetHead->bAssistantID)
	{
	case ASS_GP_BANK_OPEN:
		{
			return OnOpenBankRequest(pData,uSize,uIndex,dwHandleID);
		}
		break;

	case ASS_GP_BANK_GETGM_WALLET:
		{
			return OnGetGameWalletRequest(pData,uSize,uIndex,dwHandleID);
		}
		break;

	case ASS_GP_BANK_CHECK:
		{
			return OnCheckMoneyRequest(pData,uSize,uIndex,dwHandleID);
		}
		break;
	case HC_GP_BANK_TRANSFER_SET_REBATE_RES:
		{
			return OnUserSetRebateRequest(pData,uSize,uIndex,dwHandleID);
		}
		break;
	case ASS_GP_BANK_TRANSFER:
		{
			return OnTransferRequest(pData,uSize,uIndex,pNetHead->bHandleCode);
		}
		break;

	case ASS_GP_BANK_TRANS_RECORD:
		{
			return OnTransRecordRequest(pData,uSize,uIndex,dwHandleID);
		}
		break;

	case ASS_GP_BANK_DEPOSIT:
		{
			return OnDepositRequest(pData,uSize,uIndex,dwHandleID);
		}
		break;

	case ASS_GP_BANK_QUERY_DEPOITS:
		{
			return OnQueryDepositsRequest(pData,uSize,uIndex,dwHandleID);
		}
		break;

	case ASS_GP_BANK_CHPWD:
		{
			return OnChangePasswordRequest(pData,uSize,uIndex,dwHandleID);
		}
		break;

	case ASS_GP_BANK_FINANCE_INFO:
		{
			return OnGetFinanceInfoRequest(pData,uSize,uIndex,dwHandleID);
		}
		break;

// 	case ASS_BANK_QUERY_DEPOITS:
// 		{
// 			db_bank_op_query_deposit_in _in;
// 			CGameUserInfo* pUserInfo = m_pMainManage->m_UserManage.GetOnLineUserInfo(uIndex);
// 			_in._UserID = pUserInfo->m_UserData.dwUserID;
// 			m_pMainManage->m_SQLDataManage.PushLine(&_in.DataBaseHead, sizeof(db_bank_op_query_deposit_in), DTK_GR_BANK_QUERY_DEPOSIT, uIndex, dwHandleID);
// 			break;
// 		}
	default:
		break;
	}

	return true;
}

bool CBankService4Z::OnDataBaseResult(DataBaseResultLine * pResultData)
{
	if (!m_pMainManage) 
	{
		return true;
	}

	switch(pResultData->uHandleKind)
	{
	case DTK_GP_BANK_SET_USER_REBATE: //����޸ķ�������
		{
			return OnGetBankUserSetRebateResponse(pResultData);
		}
		break;
	case DTK_GP_BANK_UPDATE_USER_REBATE://��ҷ�����ѯ
		{
			return OnGetBankUserRebateResponse(pResultData);
		}
		break;
	case DTK_GP_BANK_UPDATE_REBATE://ת�˷���
		{
			return OnGetBankRebateResponse(pResultData);
		}
		break;
	case DTK_GP_BANK_OPEN:
		{
			return OnOpenBankResponse(pResultData);
		}
		break;

	case DTK_GP_BANK_GETGM_WALLET:
		{
			return OnGetGameWalletResponse(pResultData);
		}
		break;

	case DTK_GP_BANK_CHECK:
		{
			return OnCheckMoneyResponse(pResultData);
		}
		break;

	case DTK_GP_BANK_TRANSFER:
		{
			return OnTransferReponse(pResultData);
		}
		break;

	case DTK_GP_BANK_TRANS_RECORD:
		{
			return OnTransRecordResponse(pResultData);
		}
		break;

	case DTK_GP_BANK_DEPOSIT:
		{
			return OnDepositResponse(pResultData);
		}
		break;

	case DTK_GP_BANK_QUERY_DEPOSIT:
		{
			return OnQueryDepositsResponse(pResultData);
		}
		break;

	case DTK_GP_BANK_CHPWD:
		{
			return OnChangePasswordResponse(pResultData);
		}
		break;

	case DTK_GP_BANK_FINANCE_INFO:
		{
			return OnGetFinanceInfoResponse(pResultData);
		}
		break;
	default:
		break;
	}
	return true;
}

//������///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CBankService4Z::OnOpenBankRequest(void* pData,UINT uSize,UINT uIndex,DWORD dwHandleID)
{
	TMSG_GP_BankOpenReq* pOpenBank = (TMSG_GP_BankOpenReq*)pData;

	//��������
	LPUSER pReqUser = m_pLogonManage->GetUserBySockIdx(uIndex);

	if (!pReqUser)
	{
		return true;
	}

	//��ȡ���ݿ�
	DL_GP_I_BankOpen tagBankOpen;
	memset(&tagBankOpen,0,sizeof(DL_GP_I_BankOpen));
	tagBankOpen.dwUserID = pReqUser->UserID;

	m_pMainManage->m_SQLDataManage.PushLine(&tagBankOpen.DataBaseHead,sizeof(DL_GP_I_BankOpen),
		DTK_GP_BANK_OPEN,uIndex,dwHandleID);

	return true;
}

//��ҷ����޸�sdp
bool CBankService4Z::OnUserSetRebateRequest(void* pData,UINT uSize,UINT uIndex,DWORD dwHandleID)
{
	TMSG_GP_UserRebateSetResult *pCmd=(TMSG_GP_UserRebateSetResult*)pData;

	DL_GP_I_UserRebateSetStruct cmd;
	cmd.bTag = pCmd->bTag;
	cmd.iUserID = pCmd->iUserID;
	cmd.iMoney = pCmd->iMoney;

	m_pMainManage->m_SQLDataManage.PushLine(&cmd.DataBaseHead,sizeof(DL_GP_I_UserRebateSetStruct),
		DTK_GP_BANK_SET_USER_REBATE,uIndex,dwHandleID);

	CString sdp;
	sdp.Format("sdp_ ת�� Z������ ���[����]�����޸� �������� ���ID=%d,ʣ�෵����Ŀ=%d[0��1ȡ(%d)]",cmd.iUserID,cmd.iMoney,cmd.bTag);
	OutputDebugString(sdp);

	return true;
}

//����ҷ����޸Ľ������������sdp
bool CBankService4Z::OnGetBankUserSetRebateResponse(DataBaseResultLine* pResultData)
{
	DL_GP_O_UserRebateSetStruct *pCmd=(DL_GP_O_UserRebateSetStruct*)pResultData;

	TMSG_GP_UserRebateSetResult cmd;//���������ݷ�������
	cmd.iUserID = pCmd->iUserID;					//���ID
	cmd.iMoney = pCmd->iMoney;						//��������Ŀ
	cmd.bTag = pCmd->bTag;							//0 �棬1 ȡ
	cmd.bResult = pCmd->bResult;					//������
	CopyMemory(cmd.Msg, pCmd->Msg, sizeof(cmd.Msg));//��Ϣ
	m_pLogonManage->m_TCPSocket.SendData(pResultData->uIndex,&cmd,sizeof(TMSG_GP_UserRebateSetResult),
		MDM_GP_BANK,ASS_GP_BANK_TRANSFER,HC_GP_BANK_TRANSFER_SET_REBATE_RES,pResultData->dwHandleID);
	CString sdp;
	sdp.Format("sdp_ ת�� Z������ ��ҷ����޸Ľ�� �������� ���ID=%d,ʣ�෵����Ŀ=%d,(1�ɹ���-1ʧ�ܣ�%d��)(��Ϣ��%s)",cmd.iUserID,cmd.iMoney,cmd.bResult,cmd.Msg);
	OutputDebugString(sdp);

	if (true == pCmd->bResult)//ִ�гɹ��Ű����ˢ������
	{
		//��ѯ��ҷ������ݲ���֪���
		DL_GP_I_UserRebateUpDateStruct UserRebate;
		UserRebate.iUserID = pCmd->iUserID;//��ֵ���id
		m_pMainManage->m_SQLDataManage.PushLine(&UserRebate.DataBaseHead, sizeof(UserRebate), DTK_GP_BANK_UPDATE_USER_REBATE, pResultData->uIndex, 0);
	}

	return true;
}

//����ҷ�����ѯ���ݷ���������sdp
bool CBankService4Z::OnGetBankUserRebateResponse(DataBaseResultLine* pResultData)
{
	DL_GP_O_UserRebateUpDateStruct *pCmd=(DL_GP_O_UserRebateUpDateStruct*)pResultData;

	TMSG_GP_UserRebateUpDate cmd;//���������ݷ�������
	cmd.iUserID = pCmd->iUserID;				//���ID
	cmd.iTx_Money = pCmd->iTx_Money;			//ʣ�෵����Ŀ
	cmd.iTx_Smony = pCmd->iTx_Smony;			//�Ѿ�ȡ�ߵ���Ŀ

	m_pLogonManage->m_TCPSocket.SendData(pResultData->uIndex,&cmd,sizeof(TMSG_GP_UserRebateUpDate),
		MDM_GP_BANK,ASS_GP_BANK_TRANSFER,HC_GP_BANK_TRANSFER_UPDATE_USER_REBATE,pResultData->dwHandleID);

	CString sdp;
	sdp.Format("sdp_ ת�� Z������ ��ҷ������ݸ��� �������� ���ID=%d,ʣ�෵����Ŀ=%d,�Ѿ�ȡ�ߵ���Ŀ=%d",cmd.iUserID,cmd.iTx_Money,cmd.iTx_Smony);
	OutputDebugString(sdp);

	return true;
}

//���������ݷ���������sdp
bool CBankService4Z::OnGetBankRebateResponse(DataBaseResultLine* pResultData)
{
	DL_GP_O_RebateUpDateStruct *pCmd=(DL_GP_O_RebateUpDateStruct*)pResultData;

	TMSG_GP_RebateUpDate cmd;//���������ݷ�������
	cmd.iMin_money = pCmd->iMin_money;
	cmd.iVIP_Rate = pCmd->iVIP_Rate;
	m_iVIP_Rate = pCmd->iVIP_Rate;
	CopyMemory(&m_pLogonManage->m_Rebate,&cmd,sizeof(TMSG_GP_RebateUpDate));

	//m_pLogonManage->m_TCPSocket.SendData(pResultData->uIndex,&cmd,sizeof(TMSG_GP_RebateUpDate),
	//	MDM_GP_BANK,ASS_GP_BANK_TRANSFER,HC_GP_BANK_TRANSFER_UPDATE_REBATE,pResultData->dwHandleID);

	CString sdp;
	sdp.Format("sdp_ ת�� Z������ �������ݸ��� �洢���� ��Сת�����=%I64d,vip������=%f",m_pLogonManage->m_Rebate.iMin_money,m_pLogonManage->m_Rebate.iVIP_Rate);
	OutputDebugString(sdp);

	return true;
}

bool CBankService4Z::OnOpenBankResponse(DataBaseResultLine* pResultData)
{
	// ����ͬ��ָ��
	switch (pResultData->uHandleRusult)
	{
	case DTR_GP_BANK_OPEN_ERROR://��Ǯ�����
		{
			m_pLogonManage->m_TCPSocket.SendData(pResultData->uIndex,MDM_GP_BANK,ASS_GP_BANK_OPEN,
				HC_GP_BANK_OPEN_ERR,pResultData->dwHandleID);
			break;
		}		
	case DTR_GP_BANK_OPEN_SUC://��Ǯ��ɹ�
		{
			DL_GP_O_BankOpen* p = (DL_GP_O_BankOpen*)pResultData;
 			m_pLogonManage->m_TCPSocket.SendData(pResultData->uIndex,&p->_data,sizeof(TMSG_GP_BankInfo),
 				MDM_GP_BANK,ASS_GP_BANK_OPEN,HC_GP_BANK_OPEN_SUC,pResultData->dwHandleID);
			break;
		}
	}

	return true;
}

//��ѯǮ��///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CBankService4Z::OnGetGameWalletRequest(void* pData,UINT uSize,UINT uIndex,DWORD dwHandleID)
{
	//��������
	LPUSER pReqUser = m_pLogonManage->GetUserBySockIdx(uIndex);

	if (!pReqUser)
	{
		return true;
	}

	//��ȡ���ݿ�
	DL_GP_I_BankGetWallet _in;
	_in._UserID = pReqUser->UserID;
	m_pMainManage->m_SQLDataManage.PushLine(&_in.DataBaseHead,sizeof(DL_GP_I_BankGetWallet),
		DTK_GP_BANK_GETGM_WALLET,uIndex,dwHandleID);

	return true;
}

bool CBankService4Z::OnGetGameWalletResponse(DataBaseResultLine* pResultData)
{
	DL_GP_O_BankGetWallet* p = (DL_GP_O_BankGetWallet*)pResultData;
	m_pLogonManage->m_TCPSocket.SendData(pResultData->uIndex,&p->_data,sizeof(TMSG_GP_BankWallet),
		MDM_GP_BANK,ASS_GP_BANK_GETGM_WALLET,pResultData->uHandleRusult,0);

	return true;
}


//��ȡǮ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CBankService4Z::OnCheckMoneyRequest(void* pData,UINT uSize,UINT uIndex,DWORD dwHandleID)
{
	TMSG_GP_BankCheck* pCheck = (TMSG_GP_BankCheck*)pData;
	if (!pCheck)
	{
		return true;
	}

	DL_GP_I_BankCheck _in;
	_in._data = *pCheck;
	m_pMainManage->m_SQLDataManage.PushLine(&_in.DataBaseHead,sizeof(DL_GP_I_BankCheck),
		DTK_GP_BANK_CHECK,uIndex,dwHandleID);

	return true;
}

bool CBankService4Z::OnCheckMoneyResponse(DataBaseResultLine* pResultData)
{
	DL_GP_O_BankCheck* p = (DL_GP_O_BankCheck*)pResultData;
	::memset(p->_data._szMD5Pass,0,sizeof(p->_data._szMD5Pass));
	m_pLogonManage->m_TCPSocket.SendData(pResultData->uIndex,&p->_data,sizeof(TMSG_GP_BankCheck),
		MDM_GP_BANK,ASS_GP_BANK_CHECK,pResultData->uHandleRusult,0);

	return true;
}


//ת��///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CBankService4Z::OnTransferRequest(void* pData,UINT uSize,UINT uIndex,DWORD dwHandleID)
{
	//Ч������
	if (uSize != sizeof(TMSG_GP_BankTransfer))
	{
		return true;
	}

	TMSG_GP_BankTransfer* pTransfer = (TMSG_GP_BankTransfer*)pData;

	//��������
	LPUSER pUser = m_pLogonManage->GetUserBySockIdx(uIndex);
	if (!pUser)
	{
		return true;
	}
	
	if(pTransfer->UserID != pUser->UserID)
	{
		return true;
	}

	/// ����Լ�ת���Լ�
	if (pTransfer->UserID == pTransfer->destUserID)
	{
		return true;
	}

	//д�����ݿ�
	DL_GP_I_BankTransfer _in;
	memset(&_in,0,sizeof(DL_GP_I_BankTransfer));
	::memcpy(&_in._data,pTransfer,sizeof(TMSG_GP_BankTransfer));

	//Ӧ����˰
// 	CString stime;
// 	stime.Format("%d",CTime::GetCurrentTime());        //��ǰ��ʱ�䣬String��ʽ
// 	int curtime=atoi(stime);                           //ת��Ϊint

	//if(pUserInfo->m_UserData.iVipTime>curtime)//vip����˰
	//	TransferMoney.stTransfer.uTax = 0;
	//else
	//	TransferMoney.stTransfer.uTax = TransferMoney.stTransfer.uMoney/10;

	//Ĭ������¶�ÿ��ת�˿�˰
	_in._data.bTranTax = 1; 

	CBcfFile fConfig(CBcfFile::GetAppPath()+"Function.bcf");
	CString strBuffer = fConfig.GetKeyVal("SpecificID","Available","0");

	if (atoi(strBuffer)) ///< ָ���˺�ID
	{
		strBuffer = fConfig.GetKeyVal("SpecificID","NormalID","60000000,69999999");
		//int reValue = CGameMainManage::TransferIDCompare(_in._data.UserID,_in._data.destUserID,
		//	atol(strBuffer.Left(strBuffer.Find(",")+1)),
		//	atol(strBuffer.Right(strBuffer.GetLength()-strBuffer.Find(",")-1)));
		int reValue = 0;
		switch (reValue)
		{
		case 0:
			return false; ///< ����ת��

		case 1:
			///< ����ת�ˣ���˰
			_in._data.bTranTax = 1;
			break;

		case 2:
			///< ����ת�ˣ�����˰
			_in._data.bTranTax = 2;
			break;

		case 3:
			///< ɢ����ת��
			_in._data.bTranTax = 3;
			break;

		default :
			break;
		}
	}

	// PengJiLin, 2010-8-23, ��ͨת�˻���ȫת���ܣ�1=ȫת
	_in._data.uHandleCode = dwHandleID;

	m_pMainManage->m_SQLDataManage.PushLine(&_in.DataBaseHead,sizeof(DL_GP_I_BankTransfer),
		DTK_GP_BANK_TRANSFER,uIndex,dwHandleID);
	
	return true;
}

//ת��
bool CBankService4Z::OnTransferReponse(DataBaseResultLine* pResultData)
{
	if (pResultData->LineHead.uSize != sizeof(DL_GP_O_BankTransfer)) 
	{
		m_pLogonManage->m_TCPSocket.SendData(pResultData->uIndex,MDM_GP_BANK,ASS_GP_BANK_TRANSFER,
			HC_GP_BANK_TRANSFER_ERROR,pResultData->dwHandleID);
		return false;
	}
	DL_GP_O_BankTransfer* pTransfer = (DL_GP_O_BankTransfer*)pResultData;
	TMSG_GP_BankTransfer _Result = pTransfer->_data;

	m_pLogonManage->m_TCPSocket.SendData(pResultData->uIndex,&_Result,sizeof(TMSG_GP_BankTransfer),MDM_GP_BANK,ASS_GP_BANK_TRANSFER, 
		pResultData->uHandleRusult,pResultData->dwHandleID);

	//ת�˳ɹ���Ҳ��ת��Ŀ���û�������Ϣ
	if (HC_GP_BANK_TRANSFER_SUC == pResultData->uHandleRusult)
	{
		int nTargetIdx = m_pLogonManage->GetIndexByID(pTransfer->_data.destUserID);
		if (nTargetIdx != -1)
		{
			m_pLogonManage->m_TCPSocket.SendData(nTargetIdx,&_Result,sizeof(TMSG_GP_BankTransfer),MDM_GP_NOTICE_MSG,ASS_GR_TRANSFER_MONEY, 
				ASS_GR_TRANSFER_SUC,0);
		}

		//ת�˳ɹ�������ж�����Ƿ�Ϊvip�����з�������
		LPUSER pUser = NULL;
		pUser = m_pLogonManage->GetUserByID(pTransfer->_data.UserID);
		CString stime;
		stime.Format("%d",CTime::GetCurrentTime());
		int curtime=atoi(stime);
		if(pUser->iVipTime>curtime)
		{
			DL_GP_I_UserRebateSetStruct cmd;
			cmd.bTag = 0;
			cmd.iUserID = pTransfer->_data.UserID;
			double iRate = (pTransfer->_data.i64Money - pTransfer->_data.i64ActualTransfer) * m_iVIP_Rate / 100;
			cmd.iMoney = iRate;

			CString sdp;
			sdp.Format("sdp_ ת�� Z������ ת�˳ɹ�������ж�����Ƿ�Ϊvip�����з������� %d,%lf",cmd.iMoney, iRate);
			OutputDebugString(sdp);

			m_pMainManage->m_SQLDataManage.PushLine(&cmd.DataBaseHead,sizeof(DL_GP_I_UserRebateSetStruct),
				DTK_GP_BANK_SET_USER_REBATE,pResultData->uIndex,pResultData->dwHandleID);

		}
	}

	return true;
}

//��ѯ�˵�///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CBankService4Z::OnTransRecordRequest(void* pData,UINT uSize,UINT uIndex,DWORD dwHandleID)
{
	LPUSER pUser = m_pLogonManage->GetUserBySockIdx(uIndex);

	if (pUser == NULL)
	{
		return false;
	}

	TMSG_GP_BankTranRecordReq* pRecord = (TMSG_GP_BankTranRecordReq*)pData;

	/// ����û��������Լ����û�������ʧ��
	if (pUser->UserID != pRecord->dwUserID)
	{
		return false;
	}

	DL_GP_I_BankTransRecord _in;
	_in._data = *pRecord;

	m_pMainManage->m_SQLDataManage.PushLine(&_in.DataBaseHead,sizeof(DL_GP_I_BankTransRecord),
		DTK_GP_BANK_TRANS_RECORD,uIndex,dwHandleID);

	return true;
}

bool CBankService4Z::OnTransRecordResponse(DataBaseResultLine* pResultData)
{
	if (pResultData->LineHead.uSize != sizeof(DL_GP_O_BankTransRecord)) 
	{
		return false;
	}

	DL_GP_O_BankTransRecord* pTransRecord = (DL_GP_O_BankTransRecord*)pResultData;
	m_pLogonManage->m_TCPSocket.SendData(pResultData->uIndex,&pTransRecord->_data,sizeof(TMSG_GP_BankTranRecord),
		MDM_GP_BANK,ASS_GP_BANK_TRANS_RECORD,HC_GP_BANK_TRANS_RECORD_SUC,pResultData->dwHandleID);

	return true;
}

//�浥ҵ��///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CBankService4Z::OnDepositRequest(void* pData,UINT uSize,UINT uIndex,DWORD dwHandleID)
{
	TMSG_GP_BankDeposit* p = (TMSG_GP_BankDeposit*)pData;
	if (!p)
	{
		return true;
	}
	
	DL_GP_I_BankDeposit _in;
	_in._data = *p;
	m_pMainManage->m_SQLDataManage.PushLine(&_in.DataBaseHead,sizeof(DL_GP_I_BankDeposit),
		DTK_GP_BANK_DEPOSIT,uIndex,dwHandleID);

	return true;
}

//�浥ҵ��
bool CBankService4Z::OnDepositResponse(DataBaseResultLine* pResultData)
{
	DL_GP_O_BankDeposit* p = (DL_GP_O_BankDeposit*)pResultData;
	if (!p)
	{
		return true;
	}

	m_pLogonManage->m_TCPSocket.SendData(pResultData->uIndex, &p->_data,sizeof(TMSG_GP_BankDeposit),
		MDM_GP_BANK,ASS_GP_BANK_DEPOSIT,pResultData->uHandleRusult,0);

	return true;
}

//��ѯ�浥///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CBankService4Z::OnQueryDepositsRequest(void* pData,UINT uSize,UINT uIndex,DWORD dwHandleID)
{
	DL_GP_I_BankQueryDeposit _in;
	LPUSER pUser = m_pLogonManage->GetUserBySockIdx(uIndex);
	if (!pUser)
	{
		return true;
	}

	_in._UserID = pUser->UserID;
	m_pLogonManage->m_SQLDataManage.PushLine(&_in.DataBaseHead,sizeof(DL_GP_I_BankQueryDeposit),
		DTK_GP_BANK_QUERY_DEPOSIT,uIndex,dwHandleID);

	return true;
}

//��ѯ�浥
bool CBankService4Z::OnQueryDepositsResponse(DataBaseResultLine* pResultData)
{
	DL_GP_O_BankQueryDeposit* p = (DL_GP_O_BankQueryDeposit*)pResultData;
	if (!p)
	{
		return true;
	}

	m_pLogonManage->m_TCPSocket.SendData(pResultData->uIndex,&p->_data,sizeof(TMSG_GP_BankQueryDeposit),
		MDM_GP_BANK,ASS_GP_BANK_QUERY_DEPOITS,pResultData->uHandleRusult,0);

	return true;
}

//�޸���������///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CBankService4Z::OnChangePasswordRequest(void* pData,UINT uSize,UINT uIndex,DWORD dwHandleID)
{
	TMSG_GP_BankChPwd* p = (TMSG_GP_BankChPwd*)pData;
	if (!p)
	{
		return true;
	}

	LPUSER pUser = m_pLogonManage->GetUserBySockIdx(uIndex);
	if (!pUser)
	{
		return true;
	}

	if (pUser->UserID != p->_user_id)
	{
		return true;
	}

	DL_GP_I_BankChPwd _in;
	_in._data = *p;
	m_pLogonManage->m_SQLDataManage.PushLine(&_in.DataBaseHead,sizeof(DL_GP_I_BankChPwd),
		DTK_GP_BANK_CHPWD,uIndex,dwHandleID);

	return true;
}

bool CBankService4Z::OnChangePasswordResponse(DataBaseResultLine* pResultData)
{
	DL_GP_O_BankChPwd* p = (DL_GP_O_BankChPwd*)pResultData;
	if (!p)
	{
		return true;
	}

	m_pLogonManage->m_TCPSocket.SendData(pResultData->uIndex,MDM_GP_BANK,ASS_GP_BANK_CHPWD,pResultData->uHandleRusult,0);

	return true;
}

//�õ����˲������
bool CBankService4Z::OnGetFinanceInfoRequest(void* pData,UINT uSize,UINT uIndex,DWORD dwHandleID)
{

	LPUSER pUser = m_pLogonManage->GetUserBySockIdx(uIndex);
	if (!pUser)
	{
		return true;
	}

	DL_GP_I_FinanceInfo _in;
	::memset(&_in,0,sizeof(DL_GP_I_FinanceInfo));
	_in._data.iUserID = pUser->UserID;
	m_pLogonManage->m_SQLDataManage.PushLine(&_in.DataBaseHead,sizeof(DL_GP_I_FinanceInfo),
		DTK_GP_BANK_FINANCE_INFO,uIndex,dwHandleID);

	return true;
}

//��ȡ����״��
bool CBankService4Z::OnGetFinanceInfoResponse(DataBaseResultLine* pResultData)
{
	//Ч������
	DL_GP_O_FinanceInfo* p = (DL_GP_O_FinanceInfo*)pResultData;
	if (!p)
	{
		return true;
	}

	m_pLogonManage->m_TCPSocket.SendData(pResultData->uIndex,&p->_data,sizeof(TMSG_GP_BankFinanceInfo),
		MDM_GP_BANK,ASS_GP_BANK_FINANCE_INFO,pResultData->uHandleRusult,0);

	return true;
}
