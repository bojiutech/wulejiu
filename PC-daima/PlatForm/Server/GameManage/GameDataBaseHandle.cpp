#include "Stdafx.h"
#include "BankMessage.h"
#include "PropDatabaseMessage.h"
#include "GameDataBaseHandle.h"

//���ݿ⴦��ӿ�
UINT CGameDataBaseHandle::HandleDataBase(DataBaseLineHead * pSourceData)
{
	switch (pSourceData->uHandleKind)
	{
	case DTK_GR_BANK_UPDATE_REBATE:
		{
			return 	OnUpdateRebate(pSourceData);
		}
	case DTK_GR_BANK_UPDATE_USER_REBATE:
	case DTK_GR_BANK_UPDATE_USER_REBATE_INGAME:
		{
			return OnUpdateUserRebate(pSourceData, pSourceData->uHandleKind);
		}
	case DTK_GR_BANK_SET_USER_REBATE://����޸ķ�������
	case DTK_GR_BANK_SET_USER_REBATE_INGAME:
		{
			return OnBankTransferRebate(pSourceData, pSourceData->uHandleKind);
		}
	case DTK_GR_DEMAND_MONEY:								//��Ǯ��
	case DTK_GR_DEMAND_MONEY_IN_GAME:						//����Ϸ�����д�Ǯ��
		{
			return OnOpenWallet(pSourceData, pSourceData->uHandleKind);				
		}
	case DTK_GR_CHECKOUT_MONEY:								//ȡ�����
	case DTK_GR_CHECKOUT_MONEY_INGAME:						//����Ϸ������ȡ�����
		{	
			return OnCheckOutMoney(pSourceData, pSourceData->uHandleKind);
		}
	case DTK_GR_CHECKIN_MONEY:								//������
	case DTK_GR_CHECKIN_MONEY_INGAME:						//����Ϸ�����д�����
		{
			return OnCheckInMoney(pSourceData, pSourceData->uHandleKind);
		}
	case DTK_GR_TRANSFER_MONEY:								//ת��
	case DTK_GR_TRANSFER_MONEY_INGAME:						//��Ϸ��ת��
		{
			return OnTransferMoney(pSourceData, pSourceData->uHandleKind);
		}
	case DTK_GR_CHANGE_PASSWD:								///< �޸�����
	case DTK_GR_CHANGE_PASSWD_INGAME:						///< �޸�����
		{
			return OnChangePasswd(pSourceData, pSourceData->uHandleKind);
		}
	case DTK_GR_TRANSFER_RECORD:							///< ת�ʼ�¼
	case DTK_GR_TRANSFER_RECORD_INGAME:						///< ת�ʼ�¼
		{
			return OnTransferRecord(pSourceData, pSourceData->uHandleKind);
		}

	case DTK_GR_UPDATE_INSTANT_MONEY:						//��ʱ���½�һ���
		{
			return OnModifyUserMoney(pSourceData);
		}
	case DTK_GR_UPDATE_CHARM:								//��������ֵ
		{
			return OnUpdateUserCharm(pSourceData);
		}
		//����ZXJ �ķ���
	case DTK_GR_CLEAR_ONLINE_FLAG:	//2009-4-17���
		{
			return OnClearNetCutUserOnlineFlag(pSourceData);
		}
	case DTK_GR_CONTEST_RETURN_FEE://�˻ر�����
		{
			return OnContestReturnFee(pSourceData);
		}
	case DTK_GR_USER_RECOME:	//�û�����������дW��¼ 2009-4-28
		{
			return OnReWriteWLoginRecord(pSourceData);
		}
	case DTK_GR_USER_CONTEST_LEFT:
		{
			return OnContestUserLeft(pSourceData);
		}

		//case DTK_GR_GET_BUY_ITEM_DATA:							//��ȡ��ҿɹ�������б�
		//	{
		//		return OnGetBuyItemData(pSourceData);			
		//	}
		//case DTK_GR_BUY_ITEM:										//��ҹ������
		//	{
		//		return OnBuyItem(pSourceData);
		//	}
		//case DTK_GR_READ_USER_HOLD_ITEM:						//������ҳ��е���
		//	{
		//		return OnGetUserHoldPlatformItemCount(pSourceData);
		//	}
	case DTK_GR_PROP_USE:// DTK_GR_USER_USE_ONE_ITEM:							//���ʹ�õ���
		{
			return OnUserUseOneProp(pSourceData);
		}
	case DTK_GPR_PROP_SMALL_BRD:
		{
			return OnUseSmallBoardcast(pSourceData);
		}

	case DTK_GR_LOGON_BY_ID:								//ͨ���û� ID ��½
		{
			return OnRoomLogon(pSourceData);
		}
	case DTK_GR_USER_LEFT:									//�û��뿪����
		{
			return OnUserLeft(pSourceData);
		}
	case DTK_GR_UPDATE_INFO:								//���·�������Ϣ
		{
			return OnUpdateServerInfo(pSourceData);
		}
	case DTK_GR_RECORD_GAME:		//��¼��Ϸ����
		{
			return OnRecordGameInfo(pSourceData);
		}
	case DTK_GR_CHECK_CONNECT:		//������ݿ�����
		{
			return OnCheckDataConnect(pSourceData);
		}
	case DTK_GR_CONTEST_BEGIN:
		{
			return OnContestBegin(pSourceData);
		}
	case DTK_GR_CONTEST_GAME_OVER:
		{
			return OnContestGameOver(pSourceData);
		}
	case DTK_GR_UPDATE_GAME_RESULT:
		{
			return OnUpdateUserResult(pSourceData);
		}
	case DTK_GR_UPDATE_GAME_RESULT_ALLUSER:
		{
			return OnUpdateAllUserResult(pSourceData);
		}
	case DTK_GR_UPDATE_CONTEST_RESULT:
		{
			return OnUpdateContestInfo(pSourceData);
		}
	case DTK_GR_GET_CONTEST_RESULT:
		{
			return OnGetContestInfo(pSourceData);
		}
	case DTK_GR_CONTEST_APPLY:
		{
			return OnContestApply(pSourceData);
		}
	case DTK_GR_CALL_GM:			//����GM
		{
			return OnCallGM(pSourceData);
		}
	case DTK_GR_GAME_POWER:			//����Ȩ���޸�
		{
			return OnGamePower(pSourceData);
		}
	case DTK_GR_GM_KICK_USER_RECORD:			//����Ա������Ϊ��¼
		{
			return OnGMKickUserRecord(pSourceData);
		}
	case DTK_GR_GM_WARNING_USER_RECORD:	//����Ա��������Ϣ��Ϊ��¼
		{
			return OnGMWarningUserRecord(pSourceData);
		}
	case DTK_GR_SENDMONEY_TIMES:
		{
			return OnSendUserMoenyByTimes(pSourceData);
		}
	case DTK_GR_UNREGISTER_ONLINE:	//�����û�����
		{
			return OnUnRegisterOnLine(pSourceData);
		}
	//wushuqun 2009.5.22
	//�޸Ľ�ֹ��¼���⣬�޸Ĳ���TWLoginRecord ��¼ʱ��
	case DTK_GR_WRITE_WLOGINRECORD:
		{
			return OnWriteTWLoginRecord(pSourceData);
		}
	//wushuqun 2009.6.6
	//��ʱ��������
	case DTR_GR_ALONEDESK_INTIME:
		{
			return OnAloneDeskInTime(pSourceData);
		}
	case DTK_GR_ROOM_PW_CHANGE:
		{
			return OnRoomPWChangeRecord(pSourceData);
		}
		//case DTK_GR_USER_OPT://��ҽ��к���,���˲���
		//	{
		//		return UserOpetation(pSourceData);
		//	}
    case DTK_GR_GETNICKNAME_ONID: // PengJiLin, 2010-8-23, �����û�ID��ȡ�ǳ�
	case DTK_GR_GETNICKNAME_ONID_INGAME:
        {
            return OnGetNickNameOnID(pSourceData);
        }
    case DTK_GR_USE_KICK_PROP:      // PengJiLin, 2010-9-10, ʹ�����˿�����
        {
            return OnUseKickProp(pSourceData, TRUE);
        }
    case DTK_GR_USE_ANTI_KICK_PROP: // PengJiLin, 2010-9-10, ʹ�÷��߿�����
        {
            return OnUseKickProp(pSourceData, FALSE);
        }
    case DTK_GR_USER_NEW_KICK_USER_PROP:    // PengJiLin, 2010-9-13, ʹ�����˿����˹���
        {
            return OnNewKickUserProp(pSourceData);
        }
	case DTK_GR_BANK_NORMAL:
		{
			return OnBankOperateNormal(pSourceData);
		}
	case DTK_GR_BANK_TRANSFER:
		{
			return OnBankOperateTransfer(pSourceData);
		}
	case DTK_GR_BANK_DEPOSIT:
		{
			return OnBankOperateDeposit(pSourceData);
		}
	case DTK_GR_BANK_WALLET:
		{
			return OnBankGetWallet(pSourceData);
		}
        break;
	case DTK_GR_BANK_QUERY_DEPOSIT:
		{
			return OnBankQueryDeposits(pSourceData);
		}
		break;
	case DTK_GR_PROP_CHANGE:
		{
			return OnPropChange(pSourceData);
		}
		break;
	case DTK_GR_TIMINGMATCH_GETQUEQUEUSERS:
		{
			return FillTimingMatchQueueUser(pSourceData);
		}break;
	case DTK_GR_FINDDESKBUYSTATION:
		{
			return OnFindBuyDeskStation(pSourceData);
		}break;
	case DTK_GR_CLEARBUYDESK:
		{
			return OnClearBuyDesk(pSourceData);
		}break;
	case DTK_GR_CUTNETRECORD:
		{
			return OnCutNet(pSourceData);
		}break;
	case DTK_GP_DEDUCTROOMCARD:
		{
			return OnDeductRoomCard(pSourceData);
		} break;
	}
	return 0;
}



//������ݿ�����
UINT CGameDataBaseHandle::OnCheckDataConnect(DataBaseLineHead * pSourceData)
{
	try 
	{ 
		//�������
		m_pDataBaseManage->CheckSQLConnect();

		//������
		DataBaseResultLine ResultHead;
		m_pRusultService->OnDataBaseResultEvent(&ResultHead,DTK_GR_CHECK_CONNECT,0,sizeof(ResultHead),0,0);
	} 
	catch (...) {TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);}

	return 0;
}

//��¼��Ϸ��Ϣ
UINT CGameDataBaseHandle::OnRecordGameInfo(DataBaseLineHead * pSourceData)
{
	//Ч������
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_GameRecord)) throw DTR_GR_ERROR_UNKNOW;
	DL_GR_I_GameRecord * pGameRecord=(DL_GR_I_GameRecord *)pSourceData;

	// duanxiaohui 20111103 ���鳡(��ѳ�)��������Ϸ��¼
	if (m_pInitInfo->dwRoomRule & GRR_EXPERCISE_ROOM || m_pInitInfo->dwRoomRule & GRR_CONTEST || m_pInitInfo->dwRoomRule & GRR_TIMINGCONTEST)
	{
		return 0;
	}
		long int dwNowTime=(long int)time(NULL);
		//�������ݿ�
		HANDLE hDatabase=m_pDataBaseManage->hDBNative;
		//wushuqun 2009.6.5
		//�ı�ô洢����Ϊ�з���ֵ
		HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_RecordGameInfo_new",true);

		if(hRecord<(HANDLE)0x1000)
			return 0;

		//�������ݿ�

		sqlSPAddPara(hDatabase,hRecord,TEXT("@GameTime"),dwNowTime-pGameRecord->dwBeginTime );
		sqlSPAddPara(hDatabase,hRecord,TEXT("@RoomID"),pGameRecord->uRoomID );
		sqlSPAddPara(hDatabase,hRecord,TEXT("@DeskIndex"),pGameRecord->bDeskIndex );
		sqlSPAddPara(hDatabase,hRecord,TEXT("@Tax"),pGameRecord->dwTax );
		//TCHAR szParam[4096];
		CString strParam = "";
		TCHAR szTmp[128];
		int nUserCount = 0;
		CString dwjlog;
		for (int i=0; i<MAX_PEOPLE; ++i)
		{
			if (pGameRecord->dwUserID[i]==0)
			{
				continue;
			}
			wsprintf(szTmp, TEXT("%d,%I64d,%I64d,%I64d,%I64d,%I64d,")
				, pGameRecord->dwUserID[i]
				, pGameRecord->dwScrPoint[i]
				, pGameRecord->dwChangePoint[i]
				, pGameRecord->i64ScrMoney[i]
				, pGameRecord->dwChangeMoney[i]
				, pGameRecord->dwTaxCom[i]
			);
			//_tcscat(szParam, szTmp);
			strParam += szTmp;
			++nUserCount;
		}

		sqlSPAddPara(hDatabase,hRecord,TEXT("@UserCount"), nUserCount );
		bool bRet = sqlSPAddPara(hDatabase, hRecord, TEXT("@Param"), strParam.GetBuffer(), sizeof(TCHAR) * strParam.GetLength());

		sqlSPExec(hDatabase,hRecord);
		
		//wushuqun 2009.6.5
		//����ս���ʱ���Ƿ���Ч
		int ret=sqlSPGetReturnValue(hDatabase,hRecord);
	
		//Ϊ0ʱ���ô��������ڸû�ս����
		// =1 ʱ,��ʾ�û�ս�����Ѿ����ڻʱ������
		if (ret == 1)
		{
			int iHandleResult = DTR_GR_BATTLEROOM_TIMEOUT_ERROR;
			DL_GR_O_BattleRecordResult BattleRecordRet;
			memset(& BattleRecordRet,0,sizeof(BattleRecordRet));
			BattleRecordRet.uRoomID = pGameRecord->uRoomID;
			BattleRecordRet.uRecordResult = DTR_GR_BATTLEROOM_TIMEOUT_ERROR;

			m_pRusultService->OnDataBaseResultEvent(&BattleRecordRet.ResultHead,DTK_GR_BATTLEROOM_RES,iHandleResult,
				sizeof(BattleRecordRet),pSourceData->uIndex,pSourceData->dwHandleID);
			sqlCloseRecord(hDatabase,hRecord);
			sqlSPClose(hDatabase,hRecord);
			return 0;
		}
		////////////////////////////
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
		return 0;

	return 0;
}

//2009-4-17��ӣ�������������û����߱�־
UINT CGameDataBaseHandle::OnClearNetCutUserOnlineFlag(DataBaseLineHead * pSourceData)
{
	DL_GR_I_ClearOnlineFlag *pClearOnlineFlag = (DL_GR_I_ClearOnlineFlag*)pSourceData;
	if(pClearOnlineFlag == NULL )
		return -1;

	HANDLE hDatabase=m_pDataBaseManage->hDBNative;
	HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_DeleteAbnormalFlag");
	if(hRecord<(HANDLE)0x1000)
		return 0;
	sqlSPAddPara(hDatabase,hRecord,"@UserID", pClearOnlineFlag->lUserID);
	if(m_pInitInfo->dwRoomRule & GRR_CONTEST || m_pInitInfo->dwRoomRule & GRR_TIMINGCONTEST)
		sqlSPAddPara(hDatabase,hRecord,"@MatchID", m_pInitInfo->iMatchID);
	else 
		sqlSPAddPara(hDatabase,hRecord,"@MatchID", 0);
	
	sqlSPExec(hDatabase,hRecord);
	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);
	return 0;
}

//2009-4-28 ��� zxj
UINT CGameDataBaseHandle::OnReWriteWLoginRecord(DataBaseLineHead * pSourceData)
{
	WriteStr("�û�����������дW��¼");
	DL_GR_I_UserRecome * pUserRecome = (DL_GR_I_UserRecome*)pSourceData;
	if( pSourceData == NULL )
		return -1;
	/*
	TCHAR szSQL[128];
	memset(szSQL, 0, sizeof(TCHAR));
	wsprintf(szSQL, TEXT("INSERT INTO [TWLoginRecord] ([UserID],[WID]) VALUES (%d,%d)"), pUserRecome->lUserID, m_pInitInfo->uRoomID);
	m_pDataBaseManage->m_DataBaseCenter.Execute(szSQL);
	*/

	HANDLE hDatabase=m_pDataBaseManage->hDBNative;
	HANDLE hRecord=sqlSPSetNameEx(hDatabase, "SP_InsertAbnormalOffline");
	if(hRecord<(HANDLE)0x1000)
		return 0;
	sqlSPAddPara(hDatabase,hRecord,"@UserID", pUserRecome->lUserID);
	sqlSPAddPara(hDatabase,hRecord,"@RoomID", m_pInitInfo->uRoomID);
	sqlSPExec(hDatabase,hRecord);
	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);
	return 0;
}

UINT CGameDataBaseHandle::OnContestReturnFee(DataBaseLineHead * pSourceData)
{
	DL_GR_I_ContestReturnFee * _p = (DL_GR_I_ContestReturnFee*)pSourceData;
	if(_p == NULL )
		return -1;
	HANDLE hDatabase=m_pDataBaseManage->hDBNative;
	HANDLE hRecord=sqlSPSetName(hDatabase, "SP_ContestReturnFee");
	if(hRecord<(HANDLE)0x1000)
		return 0;
	sqlSPAddPara(hDatabase,hRecord,"@UserID", _p->iUserID);
	sqlSPAddPara(hDatabase,hRecord,"@ContestID", _p->iContestID);
	sqlSPAddPara(hDatabase,hRecord,"@RoomID", _p->iRoomID);
	sqlSPAddPara(hDatabase,hRecord,"@GameID", _p->iGameID);

	sqlSPExec(hDatabase,hRecord);
	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase, hRecord);
	return 0;
}

UINT CGameDataBaseHandle::OnContestUserLeft(DataBaseLineHead * pSourceData)
{
	DL_GR_I_ContestUserLeft * _p = (DL_GR_I_ContestUserLeft*)pSourceData;
	if(_p == NULL )
		return -1;
	/*
	TCHAR szSQL[128];
	memset(szSQL, 0, sizeof(TCHAR));
	wsprintf(szSQL, TEXT("INSERT INTO [TWLoginRecord] ([UserID],[WID]) VALUES (%d,%d)"), pUserRecome->lUserID, m_pInitInfo->uRoomID);
	m_pDataBaseManage->m_DataBaseCenter.Execute(szSQL);
	*/
	HANDLE hDatabase=m_pDataBaseManage->hDBNative;
	HANDLE hRecord=sqlSPSetName(hDatabase, "SP_ContestUserLeft");
	if(hRecord<(HANDLE)0x1000)
		return 0;
	sqlSPAddPara(hDatabase,hRecord,"@UserID", _p->iUserID);
	sqlSPAddPara(hDatabase,hRecord,"@ContestID", _p->iContestID);
	sqlSPExec(hDatabase,hRecord);
	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);
	return 0;
}


//���·�������Ϣ
UINT CGameDataBaseHandle::OnUpdateServerInfo(DataBaseLineHead * pSourceData)
{


	//Ч������
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_UpdateServerInfo)) throw DTR_GR_ERROR_UNKNOW;
	DL_GR_I_UpdateServerInfo * pUpdateInfo=(DL_GR_I_UpdateServerInfo *)pSourceData;

	DebugPrintf1(pUpdateInfo->uRoomID, "OnUpdateServerInfo uRoomID = %d uOnLineUserCount = %d", pUpdateInfo->uRoomID, pUpdateInfo->uOnLineUserCount);


	HANDLE hDatabase=m_pDataBaseManage->hDBNative;
	HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_UpdateRoomOnlinePeople");
	if(hRecord<(HANDLE)0x1000)
	{
// 		if (!sqlExec(hDatabase,TEXT("select top 1 * from TGameServerInfo")))
// 		{
// 			DebugPrintf1(pUpdateInfo->uRoomID, "OnUpdateServerInfo hDatabase Error");
// 
// 		}
		DebugPrintf1(pUpdateInfo->uRoomID, "OnUpdateServerInfo hRecord Error");
		return 0;
	}

	pUpdateInfo->uOnLineUserCount=pUpdateInfo->uOnLineUserCount;
	pUpdateInfo->uOnLineUserCount=__min(pUpdateInfo->uOnLineUserCount,m_pInitInfo->uMaxPeople);

	sqlSPAddPara(hDatabase,hRecord,"@OnlineCount",pUpdateInfo->uOnLineUserCount);
	sqlSPAddPara(hDatabase,hRecord,"@RoomID",pUpdateInfo->uRoomID);
	sqlSPExec(hDatabase,hRecord);
	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase, hRecord);
	return 0;
}


UINT CGameDataBaseHandle::OnRoomLogon(DataBaseLineHead * pSourceData)
{
	//Ч������
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_LogonByIDStruct)) throw DTR_GR_ERROR_UNKNOW;
	DL_GR_I_LogonByIDStruct * pLogonInfo=(DL_GR_I_LogonByIDStruct *)pSourceData;

	//��ʼ����½���
	DL_GR_O_LogonResult UserLogonResult;
	memset(&UserLogonResult,0,sizeof(UserLogonResult));

	//�������
	BYTE bRegisterLogon=FALSE;

	int iHandleResult=DTR_GR_LOGON_SUCCESS;

	//IP Ч�飨ÿ�������IP���ƣ�

	TCHAR szIP[16];
	CTCPSocketManage::ULongToIP(pLogonInfo->uAccessIP,szIP);

	HANDLE hDatabase=m_pDataBaseManage->hDBNative;
	HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_UserLoginRoom",true);
	if(hRecord<(HANDLE)0x1000)
	{
		iHandleResult=DTR_GR_DATABASE_CUT;
		m_pRusultService->OnDataBaseResultEvent(&UserLogonResult.ResultHead,DTK_GR_LOGON_BY_ID,iHandleResult,
			sizeof(UserLogonResult),pSourceData->uIndex,pSourceData->dwHandleID);
		return 0;
	}
	
	sqlSPAddPara(hDatabase,hRecord,TEXT("@UserID"),pLogonInfo->LogonInfo.dwUserID);
	sqlSPAddPara(hDatabase,hRecord,TEXT("@PassMD5"),pLogonInfo->LogonInfo.szMD5Pass,sizeof(pLogonInfo->LogonInfo.szMD5Pass));
	sqlSPAddPara(hDatabase,hRecord,TEXT("@LoginIP"),szIP,sizeof(szIP));
	sqlSPAddPara(hDatabase,hRecord,TEXT("@RoomID"),m_pInitInfo->uRoomID);
	sqlSPAddPara(hDatabase,hRecord,TEXT("@KernelNameID"),pLogonInfo->LogonInfo.uNameID);
	sqlSPAddPara(hDatabase,hRecord,TEXT("@MatchTable"),m_pInitInfo->szGameTable,sizeof(m_pInitInfo->szGameTable));
	sqlSPAddPara(hDatabase,hRecord,TEXT("@IPRuleTable"),m_pInitInfo->szIPRuleTable,sizeof(m_pInitInfo->szIPRuleTable));
	sqlSPAddPara(hDatabase,hRecord,TEXT("@NameRuleTable"),m_pInitInfo->szNameRuleTable,sizeof(m_pInitInfo->szNameRuleTable));
	sqlSPAddPara(hDatabase,hRecord,TEXT("@LockTable"),m_pInitInfo->szLockTable,sizeof(m_pInitInfo->szLockTable));
	sqlSPAddPara(hDatabase,hRecord,TEXT("@MatchID"),1==m_pInitInfo->iRoomState?m_pInitInfo->iMatchID:0);
	sqlSPAddPara(hDatabase,hRecord,TEXT("@RoomState"),m_pInitInfo->iRoomState);

	sqlSPExec(hDatabase,hRecord,true);

	int ret=sqlSPGetReturnValue(hDatabase,hRecord);	
	
	if(ret!=0)
	{
		iHandleResult = DTR_GR_ERROR_UNKNOW;
		if(ret==1)
			iHandleResult = DTR_GR_USER_IP_LIMITED;
		if(ret==2)
			iHandleResult = DTR_GR_USER_VALIDATA;
		if(ret==11)
		{
			//����û��Ѿ����������䣬�������ڵķ���ID
			DL_GR_O_LogonError _p;
			sqlGetValue(hDatabase,hRecord,"OldGameRoom", _p.uRoomID);
			sqlGetValue(hDatabase,hRecord,"RoomName", _p.szGameRoomName, sizeof(_p.szGameRoomName));
			iHandleResult = DTR_GR_IN_OTHER_ROOM;
			m_pRusultService->OnDataBaseResultEvent(&_p.ResultHead,DTK_GR_LOGON_BY_ID,iHandleResult,
				sizeof(DL_GR_O_LogonError),pSourceData->uIndex,pSourceData->dwHandleID);
			sqlCloseRecord(hDatabase,hRecord);
			sqlSPClose(hDatabase, hRecord);
			return 0;
		}
		if(ret==3)
			iHandleResult = DTR_GR_USER_NO_FIND;
		if(ret==4)
			iHandleResult = DTR_GR_USER_PASS_ERROR;
		
		//���ڻ�ս���ʱ����
		if(ret==5)
		{
			iHandleResult = DTR_GR_BATTLEROOM_TIMEOUT;
		}
		if (ret == 9)
			iHandleResult = DTR_GR_CONTEST_NOSIGNUP;
		if (ret == 10)
			iHandleResult = DTR_GR_CONTEST_TIMEROUT;
		if (ret == 12)
			iHandleResult = DTR_GR_CONTEST_NOSTART;
		if (ret == 13)
			iHandleResult = DTR_GR_CONTEST_OVER;
		if (ret == 14)
			iHandleResult = DTR_GR_CONTEST_BEGUN;
		if (ret != 9 && ret != 12)
		{
			m_pRusultService->OnDataBaseResultEvent(&UserLogonResult.ResultHead,DTK_GR_LOGON_BY_ID,iHandleResult,
				sizeof(UserLogonResult),pSourceData->uIndex,pSourceData->dwHandleID);
			sqlCloseRecord(hDatabase,hRecord);
			sqlSPClose(hDatabase, hRecord);
			return 0;
		}
	}


	//ע���½��Ϣ
	DL_GR_I_RegisterLogon RegUserOnLine;
	DL_GR_O_RegisterLogon RegUserResult;
	memset(&RegUserOnLine,0,sizeof(RegUserOnLine));
	memset(&RegUserResult,0,sizeof(RegUserResult));
	lstrcpy(RegUserOnLine.szAccessIP,szIP);
	RegUserOnLine.dwUserID=pLogonInfo->LogonInfo.dwUserID;
	UserLogonResult.bRegOnline=TRUE;


	//��½�ɹ�
	long int dwGamePower=0,dwMasterPower=0,uMaster=0,uMemberPower=0;
    __int64 i64Money=0;
	long int dwFascination = 0L;//
	UINT uMatch=0;
	UserLogonResult.pUserInfoStruct.bDeskNO=255;///��Ϸ����
	UserLogonResult.pUserInfoStruct.bDeskStation=255;//����λ��
	UserLogonResult.pUserInfoStruct.bUserState=USER_LOOK_STATE;//�û�״̬
	UserLogonResult.pUserInfoStruct.dwUserIP=pLogonInfo->uAccessIP;//��¼IP��ַ
	UserLogonResult.pUserInfoStruct.dwUserID=pLogonInfo->LogonInfo.dwUserID;//ID ����

	sqlGetValue(hDatabase,hRecord,"UserName",UserLogonResult.pUserInfoStruct.szName,sizeof(UserLogonResult.pUserInfoStruct.szName));
	sqlGetValue(hDatabase,hRecord,"NickName",UserLogonResult.pUserInfoStruct.nickName,sizeof(UserLogonResult.pUserInfoStruct.nickName));
	int bb;
	sqlGetValue(hDatabase,hRecord,"sex",bb);
	UserLogonResult.pUserInfoStruct.bBoy=(bb==0)?false:true;
	sqlGetValue(hDatabase,hRecord,"Member",uMemberPower);
	UserLogonResult.pUserInfoStruct.bMember=uMemberPower;
	sqlGetValue(hDatabase,hRecord,"LogoID",UserLogonResult.pUserInfoStruct.bLogoID);
	sqlGetValue(hDatabase,hRecord,"Master",uMaster);
	//////////////////////////////////////////
	///////////Kylin 20090116 VIP�����书��
	UserLogonResult.pUserInfoStruct.bGameMaster=(BYTE)uMaster;
	//////////////////////////////////////////
	sqlGetValue(hDatabase,hRecord,"MasterPower",dwMasterPower);
	UserLogonResult.dwGamePower=dwMasterPower;
	sqlGetValue(hDatabase,hRecord,"Fascination",dwFascination);
	UserLogonResult.pUserInfoStruct.dwFascination=dwFascination;
	int iTime=0;
	sqlGetValue(hDatabase,hRecord,"viptime",iTime);
	UserLogonResult.pUserInfoStruct.iVipTime=iTime;
	sqlGetValue(hDatabase,hRecord,"DoublePointTime",iTime);
	UserLogonResult.pUserInfoStruct.iDoublePointTime=iTime;
	sqlGetValue(hDatabase,hRecord,"ProtectTime",iTime);
	UserLogonResult.pUserInfoStruct.iProtectTime=iTime;
	sqlGetValue(hDatabase,hRecord,"MatchMember",uMatch);

	////������ʯ��ݱ�ʶ add by huangYuanSong 09.07.14
	int iDiamondTime=0;
	sqlGetValue(hDatabase,hRecord,"DiamondTime",iDiamondTime);

	CString strTime;
	strTime.Format("%d",CTime::GetCurrentTime());
	int curTime=atoi(strTime);
	if(iDiamondTime>curTime)
	{
		UserLogonResult.pUserInfoStruct.userInfoEx1=iDiamondTime;
	}
	else
	{
		UserLogonResult.pUserInfoStruct.userInfoEx1=0;
	}	

	//wushuqun 2009.6.1
	//����VIPʱ����ȷ���Ƿ��ǻ�Ա
	CString stime;
	stime.Format("%d",CTime::GetCurrentTime());
	int curtime=atoi(stime);
	if(UserLogonResult.pUserInfoStruct.iVipTime>curtime)
	{
		uMemberPower=1;
		UserLogonResult.pUserInfoStruct.bMember=uMemberPower;
	}

	//�Ƿ��Ա����
	if (m_pInitInfo->dwRoomRule&GRR_MEMBER_ROOM)
	{
		if (uMemberPower==0 && uMaster==0) 
		{
			iHandleResult = DTR_GR_ONLY_MEMBER;
			m_pRusultService->OnDataBaseResultEvent(&UserLogonResult.ResultHead,DTK_GR_LOGON_BY_ID,iHandleResult,
				sizeof(UserLogonResult),pSourceData->uIndex,pSourceData->dwHandleID);
			sqlCloseRecord(hDatabase,hRecord);
			sqlSPClose(hDatabase, hRecord);

			return 0;
		}
	}
	
	//��������
	if (m_pInitInfo->uComType==2&&m_pInitInfo->dwRoomRule&GRR_MATCH_REG)
	{
		if (uMatch==0 && uMaster==0) 
		{
			iHandleResult = DTR_GR_MATCH_LOGON;
			m_pRusultService->OnDataBaseResultEvent(&UserLogonResult.ResultHead,DTK_GR_LOGON_BY_ID,iHandleResult,
				sizeof(UserLogonResult),pSourceData->uIndex,pSourceData->dwHandleID);
			sqlCloseRecord(hDatabase,hRecord);
			sqlSPClose(hDatabase, hRecord);

			return 0;
		}
	}
	sqlGetValue(hDatabase,hRecord,("LessPoint"),UserLogonResult.strRecMoney.iLessPoint);
	sqlGetValue(hDatabase,hRecord,"Wallet",i64Money);
	if(m_pInitInfo->uComType==TY_MONEY_GAME && (m_pInitInfo->dwRoomRule & GRR_EXPERCISE_ROOM))
	{
		sqlGetValue(hDatabase,hRecord,"ExercisePoint",i64Money);
		UserLogonResult.pUserInfoStruct.i64Chip=i64Money;
	}
	
	//��½���䷢�ֽ�Ҳ��㣬�Զ�����,�޽�ҳ� 2013-02-02 wangzhitu	
	if ((0 == ret) && (TY_MONEY_GAME == m_pInitInfo->uComType))
	{
		if (i64Money < UserLogonResult.strRecMoney.iLessPoint)
		{
			//UserLogonResult.strRecMoney.bISAuto = true;
			DWORD dwUserID = pLogonInfo->LogonInfo.dwUserID;		
			GetWalletMoney(UserLogonResult.strRecMoney,dwUserID);
		}
	}

	sqlGetValue(hDatabase,hRecord,"BankMoney",UserLogonResult.pUserInfoStruct.i64Bank);
	sqlGetValue(hDatabase,hRecord,"GamePower",dwGamePower);
	UserLogonResult.dwGamePower=dwGamePower;
	sqlGetValue(hDatabase,hRecord,"MasterPowerInRoom",dwMasterPower);

	sqlGetValue(hDatabase,hRecord,"Win",UserLogonResult.pUserInfoStruct.uWinCount);
	sqlGetValue(hDatabase,hRecord,"Lost",UserLogonResult.pUserInfoStruct.uLostCount);
	sqlGetValue(hDatabase,hRecord,"Cut",UserLogonResult.pUserInfoStruct.uCutCount);
	sqlGetValue(hDatabase,hRecord,"Mid",UserLogonResult.pUserInfoStruct.uMidCount);
	sqlGetValue(hDatabase,hRecord,"Point",UserLogonResult.pUserInfoStruct.dwPoint);

	////�õ������¼ӵ��û���Ϣ  yjj 090319
	sqlGetValue(hDatabase,hRecord,"OccuPation",UserLogonResult.pUserInfoStruct.szOccupation,sizeof(UserLogonResult.pUserInfoStruct.szOccupation));
	sqlGetValue(hDatabase,hRecord,"PhoneNum",UserLogonResult.pUserInfoStruct.szPhoneNum,sizeof(UserLogonResult.pUserInfoStruct.szPhoneNum));
	sqlGetValue(hDatabase,hRecord,"AdrProvince",UserLogonResult.pUserInfoStruct.szProvince,sizeof(UserLogonResult.pUserInfoStruct.szProvince));
	sqlGetValue(hDatabase,hRecord,"AdrCity",UserLogonResult.pUserInfoStruct.szCity,sizeof(UserLogonResult.pUserInfoStruct.szCity));
	sqlGetValue(hDatabase,hRecord,"AdrZone",UserLogonResult.pUserInfoStruct.szZone,sizeof(UserLogonResult.pUserInfoStruct.szZone));
	//--
	// duanxiaohui 20111111 ��ȡ����ǩ��
	sqlGetValue(hDatabase,hRecord,"SignDescr",UserLogonResult.pUserInfoStruct.szSignDescr,sizeof(UserLogonResult.pUserInfoStruct.szSignDescr));
	// end duanxiaohui
	//wushuqun 2009.6.6
	//��¼����ʱ��ʱ��ȡ�����������
	sqlGetValue(hDatabase,hRecord,"VirualUser",UserLogonResult.nVirtualUser);
	//
	sqlGetValue(hDatabase,hRecord,"PresentCoinNum",UserLogonResult.nPresentCoinNum); ///< ����ʱ���ͽ�� Y.C.YAN
	///< ��¼����ʱ��,������
	CBcfFile f(CBcfFile::GetAppPath() + "Function.bcf");
	CString strValue = f.GetKeyVal("OnlineCoin","Available","0");
	if (0 == atoi(strValue))
	{
		UserLogonResult.nPresentCoinNum = 0;
	}

	//{Added by Zxd 20100629
	/// �ô洢���̵ķ���ֵ�����û����ݽṹ��isVirtual�ֶθ�ֵ��ָʾ���û��Ƿ�Ϊ�������ʺ�
	sqlGetValue(hDatabase,hRecord,"IsRobot", UserLogonResult.pUserInfoStruct.isVirtual);
	//Added by Zxd 20100629}

	//wushuqun 2009.6.26
	//��̨���õ��������,0Ϊ��ͨ���,1Ϊ�������
	sqlGetValue(hDatabase,hRecord,"UserType",UserLogonResult.pUserInfoStruct.userType);
	//VIP��ϵͳ�Զ�ʶ�𣬶������ɺ�̨�趨
	CString stimeTmp;
	stimeTmp.Format("%d",CTime::GetCurrentTime());
	int curtimeTmp=atoi(stime);
	if(UserLogonResult.pUserInfoStruct.iVipTime>curtimeTmp)
	{
		//vip��Ա

		if (UserLogonResult.pUserInfoStruct.userType == 0)
		{
			//��Ϊ��ͨVIP���
			UserLogonResult.pUserInfoStruct.userType = 2;
		}
		else if (UserLogonResult.pUserInfoStruct.userType == 1)
		{
			//��Ϊ����VIP���
			UserLogonResult.pUserInfoStruct.userType = 3;
		}
		else
		{
			//����̨���ò���0,1,Ĭ��Ϊ��ͨ���
			UserLogonResult.pUserInfoStruct.userType = 0;
		}
	}
	//{{ added by zxd 20100806 �жϱ��û��Ƿ�Ϊ����״̬�����ǣ����¼ʱ��
	int nStatusByGM = 0;
	sqlGetValue(hDatabase,hRecord,"StatusByGM", nStatusByGM);
	if (nStatusByGM == 2)
	{
		COleDateTime CurrentTime = COleDateTime::GetCurrentTime(); ///< ��ǰʱ��
		COleDateTime timeNoTalk;
		
		sqlGetValue(hDatabase,hRecord,"StatusTime", timeNoTalk);
		if(timeNoTalk>CurrentTime)
		{
			SYSTEMTIME systime;
			VariantTimeToSystemTime(timeNoTalk, &systime);
			CTime timeTmp(systime);

			CString strTimeNoTalk;
			strTimeNoTalk.Format("%d", timeTmp);
			UserLogonResult.pUserInfoStruct.userInfoEx2 = atoi(strTimeNoTalk);
			//bool bOutOfDate = curTime > UserLogonResult.pUserInfoStruct.userInfoEx2;
		}
	}
	else
	{
		UserLogonResult.pUserInfoStruct.userInfoEx2 = 0;
	}

	// �жϱ��û��Ƿ�Ϊ����״̬�����ǣ����¼ʱ��}}

	//��ȡ����Ƿ������� lxl 2010-12-10
	sqlGetValue(hDatabase,hRecord,"Trader",UserLogonResult.pUserInfoStruct.bTrader);

	sqlGetValue(hDatabase,hRecord,"ContestScore",UserLogonResult.pUserInfoStruct.i64ContestScore);

	sqlGetValue(hDatabase,hRecord,"ContestCount",UserLogonResult.pUserInfoStruct.iContestCount);
	sqlGetValue(hDatabase,hRecord,"RankNum",UserLogonResult.pUserInfoStruct.iRankNum);
	sqlGetValue(hDatabase,hRecord,"HeadUrl",UserLogonResult.pUserInfoStruct.szHeadUrl,sizeof(UserLogonResult.pUserInfoStruct.szHeadUrl));//΢��ͼ���ַ
	sqlGetValue(hDatabase,hRecord,"Jewels",UserLogonResult.pUserInfoStruct.iJewels);//��ʯ
	int nYear = 0, nMonth = 0, nDate = 0, nHour = 0, nMin = 0, nSec = 0, nss = 0;  
	CString temp;
//	sqlGetValue(hDatabase, hRecord, TEXT("StartTime"), temp);
	if (temp != "")
	{
		sscanf(temp.GetBuffer(), TEXT("%d-%d-%d %d:%d:%d.%d"), &nYear, &nMonth, &nDate, &nHour, &nMin, &nSec, &nss);

		CTime _t(nYear, nMonth, nDate, nHour, nMin, nSec); 
		UserLogonResult.pUserInfoStruct.timeLeft = _t.GetTime();
	}
	else
	{
		UserLogonResult.pUserInfoStruct.timeLeft = 0;
	}
	//��ӵ�½��Ҳ������� 2013-02-02 wangzhitu
	if (ASS_RECEIVE == UserLogonResult.strRecMoney.iResultCode)
	{
		i64Money += UserLogonResult.strRecMoney.i64Money;
	}
	UserLogonResult.pUserInfoStruct.i64Money=i64Money;	
	UserLogonResult.dwGamePower|=dwGamePower;
	UserLogonResult.dwGamePower|=m_pInitInfo->dwUserPower;//��Ϸ����Ȩ�ޣ����е��˶���
	UserLogonResult.dwMasterPower|=dwMasterPower;//�ܵĹ���Ȩ��
	CopyMemory(UserLogonResult.szMD5Pass, pLogonInfo->LogonInfo.szMD5Pass, sizeof(UserLogonResult.szMD5Pass));
	UserLogonResult.bGRMRoomID = m_pInitInfo->uNameID;
	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase, hRecord);
	if(0==ret && !UserLogonResult.pUserInfoStruct.isVirtual)
	{
		hRecord=sqlSPSetNameEx(hDatabase,"SP_FindBuyDeskStation",true);
		if(hRecord<(HANDLE)0x1000)
		{
			sqlCloseRecord(hDatabase,hRecord);
			sqlSPClose(hDatabase,hRecord);
			return 0;
		}
		sqlSPAddPara(hDatabase,hRecord,"@RoomID",m_pInitInfo->uRoomID);
		if(!sqlSPExec(hDatabase,hRecord,true))
		{
			sqlCloseRecord(hDatabase,hRecord);
			sqlSPClose(hDatabase,hRecord);
			return 0;
		}
		DL_GR_O_FindDeskBuyStationResult out_data;
		int iRecordCount = sqlGetRecordCount(hDatabase,hRecord);
		int iTableNumber=0,iVipCount=0,iUserID=0;
		bool iIsBuy=false;
		char szPassWord[20];
		for(int i=0;i<iRecordCount;i++)
		{
			iTableNumber=0;
			iVipCount=0;
			iUserID=0;
			iIsBuy=false;
			char szPassWord[20];
			memset(szPassWord,0,sizeof(szPassWord));
			sqlGetValue(hDatabase,hRecord,"DeskNumber",iTableNumber);
			sqlGetValue(hDatabase,hRecord,"VipCount",iVipCount);
			sqlGetValue(hDatabase,hRecord,"IsBuy",iIsBuy);
			sqlGetValue(hDatabase,hRecord,"UserID",iUserID);
			sqlGetValue(hDatabase,hRecord,"DeskPassWord",szPassWord,sizeof(szPassWord));
			if(iTableNumber<0 || iTableNumber>=100)
			{
				continue;
			}
			out_data.bIsBuy[iTableNumber]=iIsBuy;
			out_data.iVipCount[iTableNumber]=iVipCount;
			out_data.iUserID[iTableNumber]=iUserID;
			memcpy(out_data.szDeskPassWord[iTableNumber],szPassWord,sizeof(szPassWord));
			sqlMoveNext(hDatabase, hRecord);
		}
		m_pRusultService->OnDataBaseResultEvent(&out_data.ResultHead, DTK_GR_FINDDESKBUYSTATION,0, sizeof(out_data), pSourceData->uIndex, pSourceData->dwHandleID);
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
	}
	//�����½
	m_pRusultService->OnDataBaseResultEvent(&UserLogonResult.ResultHead,DTK_GR_LOGON_BY_ID,iHandleResult,
		sizeof(UserLogonResult),pSourceData->uIndex,pSourceData->dwHandleID);
	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase, hRecord);

	return 0;
}

// PengJiLin, 2010-8-23, �����û�ID��ȡ�ǳ�
UINT CGameDataBaseHandle::OnGetNickNameOnID(DataBaseLineHead * pSourceData)
{
    // Ч������
    if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_GetNickNameOnID)) throw DTR_GR_ERROR_UNKNOW;
    DL_GR_I_GetNickNameOnID * pGetNickNameOnID =(DL_GR_I_GetNickNameOnID *)pSourceData;

    // ��ʼ�����
    DL_GR_O_GetNickNameOnIDResult GetNickNameOnIDResult;
    memset(&GetNickNameOnIDResult,0,sizeof(GetNickNameOnIDResult));

    int iHandleResult=DTR_GR_LOGON_SUCCESS;

    HANDLE hDatabase=m_pDataBaseManage->hDBNative;
    HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_GetNickNameOnID",true);
    if(hRecord<(HANDLE)0x1000)
    {
        sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
        iHandleResult=DTR_GR_DATABASE_CUT;
		m_pRusultService->OnDataBaseResultEvent(&GetNickNameOnIDResult.ResultHead,pSourceData->uHandleKind,
                            iHandleResult,sizeof(GetNickNameOnIDResult),pSourceData->uIndex,pSourceData->dwHandleID);
        return 0;
    }

    sqlSPAddPara(hDatabase,hRecord,TEXT("@UserID"),pGetNickNameOnID->stGetNickNameOnID.iUserID);
    sqlSPExec(hDatabase,hRecord,true);
    int ret=sqlSPGetReturnValue(hDatabase,hRecord);
    sqlGetValue(hDatabase,hRecord,"NickName",GetNickNameOnIDResult.szNickName,sizeof(GetNickNameOnIDResult.szNickName));
    sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);
    // ����ʧ��
    if(ret!=0)
    {
        iHandleResult = DTR_GR_ERROR_UNKNOW;
        if(ret==1)      // ID ������
            iHandleResult = DTR_GR_GETNICKNAME_NOTEXIST;
        if(ret==2)      // �ǳ�Ϊ��
            iHandleResult = DTR_GR_GETNICKNAME_ISNULL;

		m_pRusultService->OnDataBaseResultEvent(&GetNickNameOnIDResult.ResultHead,pSourceData->uHandleKind,
                            iHandleResult,sizeof(GetNickNameOnIDResult),pSourceData->uIndex,pSourceData->dwHandleID);
        return 0;
    }

    // �����ɹ�
    iHandleResult = DTR_GR_GETNICKNAME_SUCCESS;
    GetNickNameOnIDResult.iUserID = pGetNickNameOnID->stGetNickNameOnID.iUserID;    
	m_pRusultService->OnDataBaseResultEvent(&GetNickNameOnIDResult.ResultHead,pSourceData->uHandleKind,iHandleResult,
                            sizeof(GetNickNameOnIDResult),pSourceData->uIndex,pSourceData->dwHandleID);
    return 0;
}

// PengJiLin, 2010-9-10, ʹ�����˿������߿�����
UINT CGameDataBaseHandle::OnUseKickProp(DataBaseLineHead * pSourceData, BOOL bIsKickUser)
{
    // Ч������
    if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_UseKickProp)) throw DTR_GR_ERROR_UNKNOW;
    DL_GR_I_UseKickProp* pUseKickProp =(DL_GR_I_UseKickProp *)pSourceData;

    // �����˿����Ƿ��߿�
    int iHandleIDNum = DTK_GR_USE_KICK_PROP;
    if(FALSE == bIsKickUser)
    {
        iHandleIDNum = DTK_GR_USE_ANTI_KICK_PROP;
    }

    // ��ʼ�����
    DL_GR_O_UseKickProp UseKickProp;
    memset(&UseKickProp,0,sizeof(UseKickProp));

    UseKickProp.dwUserID = pUseKickProp->dwUserID;
    UseKickProp.iPropID = pUseKickProp->iPropID;

    HANDLE hDatabase = m_pDataBaseManage->hDBNative;
    HANDLE hRecord = sqlSPSetNameEx(hDatabase,"SP_UseProp",true);
    if(hRecord<(HANDLE)0x1000) return 0;

    sqlSPAddPara(hDatabase,hRecord,"@UserID", pUseKickProp->dwUserID);
    sqlSPAddPara(hDatabase,hRecord,"@PropID", pUseKickProp->iPropID);
    sqlSPAddPara(hDatabase,hRecord,"@TargetID", 0);

    //���NameID�����ڸ�������
    sqlSPAddPara(hDatabase,hRecord,"@GameNameID",0);
    char chNotUse[10] = {0};
    sqlSPAddPara(hDatabase,hRecord,"@GameTable",chNotUse,sizeof(chNotUse));
    //�Ƿ񸺷�����
    sqlSPAddPara(hDatabase,hRecord,"@IsClearMinus", 0);
    //�Ƿ��С���� // PengJiLin, 2010-9-10, ��1����ֱ�ӷ��ز�����������
    sqlSPAddPara(hDatabase,hRecord,"@IsBoard",1);
    //˫�����ֱ仯

    sqlSPAddPara(hDatabase,hRecord,"@DoubleTime",0);
    //������仯
    sqlSPAddPara(hDatabase,hRecord,"@ProtectTime",0);
    //����ֵ�仯
    sqlSPAddPara(hDatabase,hRecord,"@FasciChange",0);
    sqlSPExec(hDatabase,hRecord,false);

    int ret=sqlSPGetReturnValue(hDatabase,hRecord);
    sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);
    int iHandleResult = DTR_GR_USE_KICKPROP_SUCCESS;

    // ����ʧ�ܣ�û�е�����
    if(0 != ret)
    {
        iHandleResult = DTR_GR_USE_KICKPROP_NULL;
        m_pRusultService->OnDataBaseResultEvent(&UseKickProp.ResultHead, iHandleIDNum, 
                                                iHandleResult, sizeof(DL_GR_O_UseKickProp), 
                                                pSourceData->uIndex, pSourceData->dwHandleID);
        return 0;
    }

    // �����ɹ���������ֵ
    hRecord=sqlSPSetNameEx(hDatabase,"SP_UseKickProp",true);
    if(hRecord<(HANDLE)0x1000)
        return 0;
    
    sqlSPAddPara(hDatabase,hRecord,"@UserID", pUseKickProp->dwUserID);
    sqlSPAddPara(hDatabase,hRecord,"@PropID", pUseKickProp->iPropID);
    sqlSPAddPara(hDatabase,hRecord,"@bIsKick", bIsKickUser?1:0);  // 0 = ���߿�, 1 = ���˿�

    sqlSPExec(hDatabase,hRecord,true);

    ret=sqlSPGetReturnValue(hDatabase,hRecord);
    sqlGetValue(hDatabase,hRecord,"TotalTime", UseKickProp.iTotalTime);
    sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);
    iHandleResult = DTR_GR_USE_KICKPROP_SET_SUCCESS;

    // ����ʧ��
    if(0 != ret)
    {
        iHandleResult = DTR_GR_USE_KICKPROP_SET_ERROR;
    }

    m_pRusultService->OnDataBaseResultEvent(&UseKickProp.ResultHead, iHandleIDNum, 
                                            iHandleResult, sizeof(DL_GR_O_UseKickProp), 
                                            pSourceData->uIndex, pSourceData->dwHandleID);
    return 0;
}

// PengJiLin, 2010-9-13, ʹ�����˿����˹���
UINT CGameDataBaseHandle::OnNewKickUserProp(DataBaseLineHead * pSourceData)
{
    // Ч������
    if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_NewKickUserProp)) throw DTR_GR_ERROR_UNKNOW;
    DL_GR_I_NewKickUserProp* pUseKickProp =(DL_GR_I_NewKickUserProp *)pSourceData;

    // ��ʼ�����
    DL_GR_O_UseNewKickUserProp UseKickProp;
    memset(&UseKickProp,0,sizeof(UseKickProp));

    UseKickProp.dwDestIndex = pUseKickProp->dwDestIndex;
    UseKickProp.dwDestHandleID = pUseKickProp->dwDestHandleID;
    UseKickProp.dwUserID = pUseKickProp->dwUserID;
    UseKickProp.dwDestID = pUseKickProp->dwDestID;

    HANDLE hDatabase = m_pDataBaseManage->hDBNative;
    HANDLE hRecord = sqlSPSetNameEx(hDatabase,"SP_NewKickUserProp",true);
    if(hRecord<(HANDLE)0x1000) return 0;

    sqlSPAddPara(hDatabase,hRecord,"@UserID", pUseKickProp->dwUserID);
    sqlSPAddPara(hDatabase,hRecord,"@TargetID", pUseKickProp->dwDestID);
    sqlSPExec(hDatabase,hRecord);

    int ret=sqlSPGetReturnValue(hDatabase,hRecord);
    sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);
    int iHandleResult = DTR_GR_NEW_KICKUSER_SUCCESS;
    switch(ret)
    {
    case 1:
        iHandleResult = DTR_GR_NEW_KICKUSER_NOTIME; // �Լ��ĵ����ѹ��ڣ�����û�е���
        break;
    case 2:
        iHandleResult = DTR_GR_NEW_KICKUSER_HAD_ANTI; // �Է��з��߿�ʱ��
        break;
    case 3:
        iHandleResult = DTR_GR_NEW_KICKUSER_HAD_ANTI; // �Է���VIPʱ��
        break;
    }

    m_pRusultService->OnDataBaseResultEvent(&UseKickProp.ResultHead, DTK_GR_USER_NEW_KICK_USER_PROP, 
                                        iHandleResult, sizeof(DL_GR_O_UseNewKickUserProp), 
                                        pSourceData->uIndex, pSourceData->dwHandleID);

	return 0;
}


UINT CGameDataBaseHandle::OnBankOperateNormal(DataBaseLineHead * pSourceData)
{
	try
	{
		int iHandleCode = DTR_GR_ERROR_UNKNOW;
		db_bank_op_normal_in* _p = (db_bank_op_normal_in*)pSourceData;
		db_bank_op_normal_out _out;
		ZeroMemory(&_out, sizeof(_out));
		_out._data = _p->_data;

		HANDLE hDatabase=m_pDataBaseManage->hDBNative;
		HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_BankOpNormal", true);

		bool b=sqlSPAddPara(hDatabase,hRecord,"@UserID", _p->_data._user_id);
		b = sqlSPAddPara(hDatabase,hRecord,"@GameID", _p->_data._game_id);
		b = sqlSPAddPara(hDatabase,hRecord,"@OperateType", _p->_data._operate_type);
		b = sqlSPAddPara_i64(hDatabase,hRecord,"@Money", _p->_data._money);
		b = sqlSPAddPara(hDatabase,hRecord,"@MD5Pass", _p->_data._szMD5Pass,sizeof(_p->_data._szMD5Pass));

		sqlSPExec(hDatabase,hRecord, true);
		int iRet = sqlSPGetReturnValue(hDatabase, hRecord);
		iHandleCode = iRet;

		if (iHandleCode == HC_BANK_OP_SUC)
		{
			sqlGetValue(hDatabase,hRecord, "MoneyOp", _out._data._money);
		}

		m_pRusultService->OnDataBaseResultEvent(&_out.ResultHead, DTK_GR_BANK_NORMAL, iHandleCode,
			sizeof(db_bank_op_normal_out), pSourceData->uIndex, pSourceData->dwHandleID);
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
	}
	catch(...)
	{
		TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
	}

	return 0;
}

UINT CGameDataBaseHandle::OnBankOperateTransfer(DataBaseLineHead * pSourceData)
{
	try
	{
		int iHandleCode = DTR_GR_ERROR_UNKNOW;
		db_bank_op_transfer_in* _p = (db_bank_op_transfer_in*)pSourceData;
		db_bank_op_transfer_out _out;
		ZeroMemory(&_out, sizeof(_out));
		_out._data = _p->_data;

		HANDLE hDatabase=m_pDataBaseManage->hDBNative;
		HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_BankOpTransfer", true);

		bool b=sqlSPAddPara(hDatabase,hRecord,"@UserID1", _p->_data._user_id1);
		b = sqlSPAddPara(hDatabase,hRecord,"@UserID2", _p->_data._user_id2);
		CString s;
		s.Format("%I64d", _p->_data._money);
		sqlSPAddPara(hDatabase,hRecord,"@Money", s.GetBuffer(), sizeof(TCHAR)*s.GetLength());

		sqlSPExec(hDatabase,hRecord, true);
		int iRet = sqlSPGetReturnValue(hDatabase, hRecord);
		iHandleCode = iRet;

		if (iHandleCode == 0)
		{
			//sqlGetValue(hDatabase,hRecord, "MoneyOp", _out._data._money);
		}

		m_pRusultService->OnDataBaseResultEvent(&_out.ResultHead, DTK_GR_BANK_TRANSFER, iHandleCode,
			sizeof(db_bank_op_normal_out), pSourceData->uIndex, iRet);
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
	}
	catch(...)
	{
		TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
	}

	return 0;
}

UINT CGameDataBaseHandle::OnBankOperateDeposit(DataBaseLineHead * pSourceData)
{
	try
	{
		int iHandleCode = DTR_GR_ERROR_UNKNOW;
		db_bank_op_deposit_in* _p = (db_bank_op_deposit_in*)pSourceData;
		db_bank_op_deposit_out _out;
		ZeroMemory(&_out, sizeof(_out));
		_out._data = _p->_data;

		//HANDLE hDatabase=m_pDataBaseManage->hDBNative;
		//HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_BankOpDeposit", true);

		//bool b=sqlSPAddPara(hDatabase,hRecord,"@UserID", _p->_data._user_id);
		//b = sqlSPAddPara(hDatabase,hRecord,"@OperateType", _p->_data._operate_type);
		//CString s;
		//s.Format("%I64d", _p->_data._money);
		//sqlSPAddPara(hDatabase,hRecord,"@Money", s.GetBuffer(), sizeof(TCHAR)*s.GetLength());

		//sqlSPExec(hDatabase,hRecord, true);
		//int iRet = sqlSPGetReturnValue(hDatabase, hRecord);
		//iHandleCode = iRet;

		//if (iHandleCode == 0)
		//{
		//	CString tmp;
		//	sqlGetValue(hDatabase,hRecord, "DepositID", tmp);
		//	strcpy(_out._data._deposit_id, tmp.GetBuffer());
		//	sqlGetValue(hDatabase,hRecord, "DepositPassWord", tmp);
		//	strcpy(_out._data._deposit_password, tmp.GetBuffer());

		//}

		HANDLE hDatabase;
		HANDLE hRecord;
		int iRet;

		if (_p->_data._operate_type == 1)
		{
			hDatabase=m_pDataBaseManage->hDBNative;
			hRecord=sqlSPSetNameEx(hDatabase,"SP_Bank_NewDeposit", true);

			bool b=sqlSPAddPara(hDatabase,hRecord,"@CreaterUserID", _p->_data._user_id);
			b = sqlSPAddPara_i64(hDatabase,hRecord,"@Money", _p->_data._money);
			sqlSPAddPara(hDatabase,hRecord,"@MD5Pass",_p->_data._szMD5Pass,sizeof(_p->_data._szMD5Pass));

			sqlSPExec(hDatabase,hRecord, true);
			iRet = sqlSPGetReturnValue(hDatabase, hRecord);
			iHandleCode = iRet;

			if (iHandleCode == 0)
			{
				CString tmp;
				sqlGetValue(hDatabase,hRecord, "DepositID", tmp);
				strcpy(_out._data._deposit_id, tmp.GetBuffer());
				sqlGetValue(hDatabase,hRecord, "DepositPassWord", tmp);
				strcpy(_out._data._deposit_password, tmp.GetBuffer());
				_out._data._state = 0;
				sqlGetValue(hDatabase,hRecord, "CDSC", _out._data._csds);
				sqlGetValue(hDatabase,hRecord, "Money", _out._data._money);
			}
		}
		else if (_p->_data._operate_type == 2)
 		{
			hDatabase=m_pDataBaseManage->hDBNative;
			hRecord=sqlSPSetNameEx(hDatabase,"SP_Bank_UseDeposit", true);

			bool b=sqlSPAddPara(hDatabase,hRecord,"@UserID", _p->_data._user_id);
			CString s = _p->_data._deposit_id;
			sqlSPAddPara(hDatabase,hRecord,"@DepositID", s.GetBuffer(), sizeof(TCHAR)*s.GetLength());
			s = _p->_data._deposit_password;
			sqlSPAddPara(hDatabase,hRecord,"@DepositPwd", s.GetBuffer(), sizeof(TCHAR)*s.GetLength());

			sqlSPExec(hDatabase,hRecord, true);
			iRet = sqlSPGetReturnValue(hDatabase, hRecord);
			iHandleCode = iRet;

			if (iHandleCode == 0)
			{
				_out._data._state = 1;
				sqlGetValue(hDatabase, hRecord, "UserID", _out._data._user_id);
				sqlGetValue(hDatabase, hRecord, "NickName", _out._data._szNickName,sizeof(_out._data._szNickName));
				sqlGetValue(hDatabase, hRecord, "Money", _out._data._money);
			}
		}

		m_pRusultService->OnDataBaseResultEvent(&_out.ResultHead, DTK_GR_BANK_DEPOSIT, iHandleCode,
			sizeof(db_bank_op_deposit_out), pSourceData->uIndex, iRet);
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
	}
	catch(...)
	{
		TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
	}

	return 0;
}

UINT CGameDataBaseHandle::OnPropChange(DataBaseLineHead * pSourceData)
{
	//if (!(m_pInitInfo.dwRoomRule & GRR_UNITY3D))
	//{
	//	return true;
	//}

//Ч������
	if (pSourceData->DataLineHead.uSize!=sizeof(TpropChange_I)) throw DTR_GR_ERROR_UNKNOW;
	TpropChange_I * _p = (TpropChange_I *)pSourceData;

	if (_p == NULL) return 0;

	TpropChange_O _q;
	try
	{
		HANDLE hDatabase = m_pDataBaseManage->hDBNative;
		HANDLE hRecord = sqlSPSetName(hDatabase, "SP_PropChange", true);
		if(hRecord>(HANDLE)0x1000)
		{
			sqlSPAddPara(hDatabase,hRecord,"@UserId", _p->info.iUserId);
			sqlSPAddPara(hDatabase,hRecord,"@PropId", _p->info.iPropId);
			sqlSPAddPara(hDatabase,hRecord,"@PropCount", _p->info.iPropCount);
			sqlSPAddPara(hDatabase,hRecord,"@OpType", _p->info.iOpType);
			sqlSPExec(hDatabase,hRecord,true);
			int ret=sqlSPGetReturnValue(hDatabase,hRecord);
			int iHandleResult = ret;

			_q.info = _p->info; 
			_q.info.iPropCount = 0;

			if (!sqlEndOfFile(hDatabase,hRecord))
			{
				sqlGetValue(hDatabase,hRecord,"PropCount", _q.info.iPropCount);
			}

			sqlCloseRecord(hDatabase,hRecord);
			sqlSPClose(hDatabase,hRecord);

			m_pRusultService->OnDataBaseResultEvent(&_q.ResultHead, DTK_GR_PROP_CHANGE, 
				iHandleResult, sizeof(TpropChange_O), 
				pSourceData->uIndex, pSourceData->dwHandleID);
		}
	}
	catch (...) {}
	return 0;
}
UINT CGameDataBaseHandle::OnBankQueryDeposits(DataBaseLineHead * pSourceData)
{
	try
	{
		int iHandleCode = DTR_GR_ERROR_UNKNOW;
		db_bank_op_query_deposit_in* _p = (db_bank_op_query_deposit_in*)pSourceData;
		db_bank_op_query_deposit_out _out;
		ZeroMemory(&_out, sizeof(_out));

		HANDLE hDatabase=m_pDataBaseManage->hDBNative;
		HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_Bank_QueryDeposits", true);

		bool b=sqlSPAddPara(hDatabase,hRecord,"@UserID", _p->_UserID);

		sqlSPExec(hDatabase,hRecord, true);
		int iRet = sqlSPGetReturnValue(hDatabase, hRecord);
		iHandleCode = iRet;

		int nSeriNo = 0;

		while(!sqlEndOfFile(hDatabase,hRecord))
		{
			ZeroMemory(&_out,sizeof(db_bank_op_query_deposit_out));

			_out._data._serial_no = nSeriNo++;
			sqlGetValue(hDatabase,hRecord,"DepositID",_out._data._deposit_id,sizeof(_out._data._deposit_id));
			sqlGetValue(hDatabase,hRecord,"DepositPassWord",_out._data._deposit_password,sizeof(_out._data._deposit_password));
			sqlGetValue(hDatabase,hRecord,"Money",_out._data._money);
			sqlGetValue(hDatabase,hRecord,"UserID",_out._data._user_id);
			sqlGetValue(hDatabase,hRecord,"GreateTime",_out._data._create_time);
			sqlGetValue(hDatabase,hRecord,"CDSC",_out._data._csds);
			sqlGetValue(hDatabase,hRecord,"State",_out._data._state);
			sqlGetValue(hDatabase,hRecord,"UsedUserID",_out._data._used_user_id);

			m_pRusultService->OnDataBaseResultEvent(&_out.ResultHead, DTK_GR_BANK_QUERY_DEPOSIT, 0, sizeof(db_bank_op_query_deposit_out),pSourceData->uIndex,pSourceData->dwHandleID);
			sqlMoveNext(hDatabase,hRecord);
		}

		ZeroMemory(&_out,sizeof(db_bank_op_query_deposit_out));
		m_pRusultService->OnDataBaseResultEvent(&_out.ResultHead, DTK_GR_BANK_QUERY_DEPOSIT, 1, sizeof(db_bank_op_query_deposit_out), pSourceData->uIndex, pSourceData->dwHandleID);
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
	}
	catch(...)
	{
		TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
	}

	return 0;
}

UINT CGameDataBaseHandle::OnBankGetWallet(DataBaseLineHead * pSourceData)
{
	try
	{
		int iHandleCode = DTR_GR_ERROR_UNKNOW;
		db_bank_op_wallet_in* _p = (db_bank_op_wallet_in*)pSourceData;
		db_bank_game_wallet_out _out;
		ZeroMemory(&_out, sizeof(_out));

		HANDLE hDatabase=m_pDataBaseManage->hDBNative;
		HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_BankOpWallet", true);

		bool b=sqlSPAddPara(hDatabase,hRecord,"@UserID", _p->_UserID);

		sqlSPExec(hDatabase,hRecord, true);
		int iRet = sqlSPGetReturnValue(hDatabase, hRecord);
		iHandleCode = iRet;

		while(!sqlEndOfFile(hDatabase,hRecord))
		{
			ZeroMemory(&_out,sizeof(db_bank_game_wallet_out));

			//sqlGetValue(hDatabase,hRecord,"UserID", _out._data._user_id);
			sqlGetValue(hDatabase,hRecord,"GameID",_out._data._game_id);
			sqlGetValue(hDatabase,hRecord,"ComName",_out._data._game_name,sizeof(_out._data._game_name));
			sqlGetValue(hDatabase,hRecord,"WalletMoney",_out._data._money);

			m_pRusultService->OnDataBaseResultEvent(&_out.ResultHead, DTK_GR_BANK_WALLET, 0, sizeof(db_bank_game_wallet_out),pSourceData->uIndex,pSourceData->dwHandleID);
			sqlMoveNext(hDatabase,hRecord);
		}

		ZeroMemory(&_out,sizeof(db_bank_game_wallet_out));
		m_pRusultService->OnDataBaseResultEvent(&_out.ResultHead, DTK_GR_BANK_WALLET, 1, sizeof(db_bank_game_wallet_out), pSourceData->uIndex, pSourceData->dwHandleID);
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
	}
	catch(...)
	{
		TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
	}

	return 0;
}

//vipʱ����
//UINT CGameDataBaseHandle::OnVipTimerCheck(DataBaseLineHead *pSourceData)
//{//����������Բ�Ҫ�˰�
//	return TRUE;
//
//}

//ȡ��
UINT CGameDataBaseHandle::OnCheckOutMoney(DataBaseLineHead *pSourceData, UINT uCode)
{
	//Ч������
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_CheckOutMoneyWithPwd_t)) throw DTR_GR_ERROR_UNKNOW;//////���ܵĽṹ�Ͷ�����Ƿ�һ��
	DL_GR_I_CheckOutMoneyWithPwd_t * pCheckOutMoney=(DL_GR_I_CheckOutMoneyWithPwd_t * )pSourceData;
	DL_GR_O_CheckOutMoney pCheckOutMoneyResult;///���
	memset(&pCheckOutMoneyResult,0,sizeof(pCheckOutMoneyResult));
	if(pCheckOutMoney->i64Count<0) return 0; 

	try
	{
		__int64 i64Bank=0,i64Money=0,i64CheckInMoney = 0;

		HANDLE hDatabase=m_pDataBaseManage->hDBNative;
		HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_BankMoneyOpera",true);
		if(hRecord<(HANDLE)0x1000)
			return 0;

		sqlSPAddPara(hDatabase,hRecord,"@UserID",pCheckOutMoney->dwUserID);
		CString s;
		s.Format("%I64d", pCheckOutMoney->i64Count);
		sqlSPAddPara(hDatabase,hRecord,"@MoneyQuantitys", s.GetBuffer(), sizeof(TCHAR)*s.GetLength());
		sqlSPAddPara(hDatabase,hRecord,"@RoomID",m_pInitInfo->uRoomID);
		sqlSPAddPara(hDatabase,hRecord,"@IsSave",0);	//0-ȡ��,1-���
		sqlSPAddPara(hDatabase,hRecord,"@MD5Pass",pCheckOutMoney->szMD5Pass, sizeof(pCheckOutMoney->szMD5Pass));//����

		sqlSPExec(hDatabase,hRecord,true);

		int ret=sqlSPGetReturnValue(hDatabase,hRecord);
		
		if(ret!=0)
		{
			sqlCloseRecord(hDatabase,hRecord);	// zxj dfw 2009-11-12
			sqlSPClose(hDatabase,hRecord);
			if (ret == 5)
			{
				throw DTR_GR_CHECKOUT_MONEY_INV;
			}
			else
			{
				throw DTR_GR_ERROR_UNKNOW;
			}
			
		}
		 
		sqlGetValue(hDatabase,hRecord,"MoneyInBank",i64Bank);
		sqlGetValue(hDatabase,hRecord,"MoneyChange",i64CheckInMoney);
		sqlGetValue(hDatabase,hRecord,"MoneyInWallet",i64Money);

		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);

		pCheckOutMoneyResult.dwUserID=pCheckOutMoney->dwUserID;
		pCheckOutMoneyResult.i64CheckOut=i64CheckInMoney;
		pCheckOutMoneyResult.i64MoneyInBank=i64Bank /*- i64CheckInMoney*/;//ȡ��i64CheckInMoney�����������ص��Ѿ��ǲ�����Ľ�� [2016/6/1/15 lwz]
		pCheckOutMoneyResult.i64MoneyInRoom=i64Money/* + i64CheckInMoney*/;
		throw DTR_GR_CHECKOUT_MONEY_SUC;

	}
	catch (int iHandleResult)
	{TRACE("EXCEPT CATCH:%s with %s\n",__FILE__,__FUNCTION__);
	m_pRusultService->OnDataBaseResultEvent(&pCheckOutMoneyResult.ResultHead, uCode, iHandleResult,
		sizeof(pCheckOutMoneyResult),pSourceData->uIndex,pSourceData->dwHandleID);
	}
	return 0;
}

//���
UINT CGameDataBaseHandle::OnCheckInMoney(DataBaseLineHead *pSourceData, UINT uCode)
{
	//Ч������
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_CheckOutMoney)) throw DTR_GR_ERROR_UNKNOW;//////���ܵĽṹ�Ͷ�����Ƿ�һ��
	DL_GR_I_CheckOutMoney * pCheckInMoney=(DL_GR_I_CheckOutMoney * )pSourceData;
	DL_GR_O_CheckOutMoney pCheckInMoneyResult;///���
	memset(&pCheckInMoneyResult,0,sizeof(pCheckInMoneyResult));
	if(pCheckInMoney->i64Count<0) return 0; 


	try
	{
		__int64 i64Bank=0,i64Money=0, i64CheckInMoney = 0;

		HANDLE hDatabase=m_pDataBaseManage->hDBNative;
		HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_BankMoneyOpera",true);
		if(hRecord<(HANDLE)0x1000)
			return 0;

		sqlSPAddPara(hDatabase,hRecord,"@UserID",pCheckInMoney->dwUserID);
		//TCHAR _num[32];
		//ZeroMemory(_num, sizeof(_num));
		//_i64tow(pCheckInMoney->i64Count, _num, 10);
		CString s;
		s.Format("%I64d", pCheckInMoney->i64Count);
		sqlSPAddPara(hDatabase,hRecord,"@MoneyQuantitys", s.GetBuffer(), sizeof(TCHAR)*s.GetLength());
		sqlSPAddPara(hDatabase,hRecord,"@RoomID",m_pInitInfo->uRoomID);
		sqlSPAddPara(hDatabase,hRecord,"@IsSave",1);	//0-ȡ��,1-���
		sqlSPAddPara(hDatabase,hRecord,"@MD5Pass", "", sizeof(""));//����

		sqlSPExec(hDatabase,hRecord,true);

		int ret=sqlSPGetReturnValue(hDatabase,hRecord);

		if(ret!=0)
		{
			sqlCloseRecord(hDatabase,hRecord);	// zxj dfw 2009-11-12
			sqlSPClose(hDatabase,hRecord);
			if (ret == 5)
			{
				throw DTR_GR_CHECKIN_MONEY_INV;
			}
			else
			{
				throw DTR_GR_ERROR_UNKNOW;
			}
		}

		sqlGetValue(hDatabase,hRecord,"MoneyInBank",i64Bank);
		sqlGetValue(hDatabase,hRecord,"MoneyChange",i64CheckInMoney);
		sqlGetValue(hDatabase,hRecord,"MoneyInWallet",i64Money);
		s.Format("CheckIn MoneyInBank = %I64d, MoneyChange = %I64d, MoneyInWallet = %I64d", i64Bank, i64CheckInMoney, i64Money);
		OutputDebugString(s);
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);

		pCheckInMoneyResult.dwUserID=pCheckInMoney->dwUserID;
		pCheckInMoneyResult.i64CheckOut=i64CheckInMoney;
		pCheckInMoneyResult.i64MoneyInBank=i64Bank/* + i64CheckInMoney*/;// ȡ��i64CheckInMoney�����������ص��Ѿ��ǲ�����Ľ�� [2016/6/1/15 lwz]
		pCheckInMoneyResult.i64MoneyInRoom=i64Money /*- i64CheckInMoney*/;
		throw DTR_GR_CHECKIN_MONEY_SUC;

	}
	catch (int iHandleResult)
	{TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
		m_pRusultService->OnDataBaseResultEvent(&pCheckInMoneyResult.ResultHead, uCode, iHandleResult,
			sizeof(pCheckInMoneyResult),pSourceData->uIndex,pSourceData->dwHandleID);
	}
	return 0;
}
//ת�ʼ�¼
UINT CGameDataBaseHandle::OnTransferRecord(DataBaseLineHead *pSourceData, UINT uCode)
{
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_TransferRecord_t)) throw DTR_GR_ERROR_UNKNOW;//////���ܵĽṹ�Ͷ�����Ƿ�һ��
	DL_GR_I_TransferRecord_t *pTransferRecord = (DL_GR_I_TransferRecord_t *)pSourceData;
	DL_GR_O_TransferRecord_t stTransferRecordResult;
	ZeroMemory(&stTransferRecordResult, sizeof(DL_GR_O_TransferRecord_t));
	if (pTransferRecord->stTransfer.dwUserID == 0)
	{
		return 0;
	}
	{
		HANDLE hDatabase=m_pDataBaseManage->hDBNative;
		HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_GetTransferRecord",true);
		if(hRecord<(HANDLE)0x1000)
			return 0;
		sqlSPAddPara(hDatabase,hRecord,"@UserID",pTransferRecord->stTransfer.dwUserID);
		sqlSPExec(hDatabase,hRecord,true);
		int ret=sqlSPGetReturnValue(hDatabase,hRecord);
		if (ret>0)
		{
			sqlCloseRecord(hDatabase,hRecord);
			sqlSPClose(hDatabase,hRecord);
			return 0;
		}
		/// ÿ��ȡһ����¼���ͷ���һ�Σ�ֱ����ȡ������smalldatetime���͵������ڿͻ��˽���
		int nSeriNo = 0;
		while(!sqlEndOfFile(hDatabase,hRecord))
		{
			stTransferRecordResult.transferRecord.nSeriNo = nSeriNo++;
			sqlGetValue(hDatabase,hRecord,"UserID", stTransferRecordResult.transferRecord.dwUserID);
			sqlGetValue(hDatabase,hRecord,"DestUserID", stTransferRecordResult.transferRecord.destUserID);
			sqlGetValue(hDatabase,hRecord,"TransferMoney", stTransferRecordResult.transferRecord.i64Money);
			sqlGetValue(hDatabase,hRecord,"ActualTransfer", stTransferRecordResult.transferRecord.i64ActualTransfer);
			sqlGetValue(hDatabase,hRecord,"TransTime", stTransferRecordResult.transferRecord.oleDateTime);

			m_pRusultService->OnDataBaseResultEvent(&stTransferRecordResult.ResultHead,
				uCode, DTR_GR_OPEN_WALLET_SUC,
				sizeof(stTransferRecordResult),
				pSourceData->uIndex,pSourceData->dwHandleID);
			sqlMoveNext(hDatabase,hRecord);
		}
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
	}

	return 0;
}
//�޸�����
UINT CGameDataBaseHandle::OnChangePasswd(DataBaseLineHead *pSourceData, UINT uCode)
{
	//Ч������
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_ChangePasswd_t))
	{
		return 0;
	}
	DL_GR_I_ChangePasswd_t *pChangePasswd = (DL_GR_I_ChangePasswd_t *)pSourceData;
	DL_GR_O_ChangePasswd_t changePasswdResult;

	{
		HANDLE hDatabase=m_pDataBaseManage->hDBNative;
		HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_ChangeBankPasswd",true);
		if(hRecord<(HANDLE)0x1000)
			return 0;
		sqlSPAddPara(hDatabase,hRecord,"@UserID",pChangePasswd->stChangePasswd.UserID);
		sqlSPAddPara(hDatabase,hRecord,"@MD5PassOld",pChangePasswd->stChangePasswd.szMD5PassOld, sizeof(pChangePasswd->stChangePasswd.szMD5PassOld));//������
		sqlSPAddPara(hDatabase,hRecord,"@MD5PassNew",pChangePasswd->stChangePasswd.szMD5PassNew, sizeof(pChangePasswd->stChangePasswd.szMD5PassNew));//������
		sqlSPExec(hDatabase,hRecord,true);

		int nRet = sqlSPGetReturnValue(hDatabase,hRecord);
		changePasswdResult.nResult = nRet;
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
		UINT uResult = DTR_GR_OPEN_WALLET_SUC;
		if (nRet != 0)
		{
			uResult = DTR_GR_OPEN_WALLET_ERROR_PSW;
		}
		// ֻ�гɹ���ʧ�����ֽ��
		m_pRusultService->OnDataBaseResultEvent(&changePasswdResult.ResultHead,
			uCode, uResult,
			sizeof(changePasswdResult),
			pSourceData->uIndex,pSourceData->dwHandleID);
	}

	return 0;
}
//ת��
UINT CGameDataBaseHandle::OnTransferMoney(DataBaseLineHead *pSourceData, UINT uCode)
{
	//Ч������
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_TransferMoney))
	{
		return 0;
	}
	DL_GR_I_TransferMoney * pTransferMoney=(DL_GR_I_TransferMoney * )pSourceData;
	DL_GR_O_TransferMoney stTransferMoneyResult;///���
	memset(&stTransferMoneyResult,0,sizeof(stTransferMoneyResult));
	if(pTransferMoney->stTransfer.i64Money <= 0) return 0; 

    // PengJiLin, 2010-8-23, �������С�ȫת������

    // PengJiLin, 2011-7-13, 32λ����ת��64λ����
    UINT u32Data = 0;

	try
	{
		HANDLE hDatabase=m_pDataBaseManage->hDBNative;
		HANDLE hRecord;
        if(1 == pTransferMoney->stTransfer.uHandleCode)
        {
            hRecord=sqlSPSetNameEx(hDatabase,"SP_TransferAllMoney",true);
        }
        else
        {
            hRecord=sqlSPSetNameEx(hDatabase,"SP_TransferMoney",true);
        }
        
		if(hRecord<(HANDLE)0x1000)
			return 0;
		sqlSPAddPara(hDatabase,hRecord,"@UserID",pTransferMoney->stTransfer.UserID);
		sqlSPAddPara(hDatabase,hRecord,"@UseDestID",pTransferMoney->stTransfer.bUseDestID?1:0);
		sqlSPAddPara(hDatabase,hRecord,"@DestUserID",pTransferMoney->stTransfer.destUserID);
		sqlSPAddPara(hDatabase,hRecord,"@DestNickName",pTransferMoney->stTransfer.szDestNickName, sizeof(pTransferMoney->stTransfer.szDestNickName));//����
		//sqlSPAddPara(hDatabase,hRecord,"@DestUser",pTransferMoney->stTransfer.szDestName,sizeof(pTransferMoney->stTransfer.szDestName));
		if(0 == pTransferMoney->stTransfer.uHandleCode)     // PengJiLin, 2010-8-23, ȫת����
           sqlSPAddPara_i64(hDatabase,hRecord,"@TranMoney",pTransferMoney->stTransfer.i64Money);
		sqlSPAddPara(hDatabase,hRecord,"@TranTax",pTransferMoney->stTransfer.bTranTax);
		sqlSPAddPara(hDatabase,hRecord,"@MD5Pass",pTransferMoney->stTransfer.szMD5Pass, sizeof(pTransferMoney->stTransfer.szMD5Pass));//����

		sqlSPExec(hDatabase,hRecord,true);
		int ret=sqlSPGetReturnValue(hDatabase,hRecord);
		UINT uResult = DTR_GR_TRANSFER_MONEY_SUC;
		switch(ret)
		{
		case 0: ///<ת�ʳɹ�
			{
			sqlGetValue(hDatabase,hRecord,"DestUserID",pTransferMoney->stTransfer.destUserID);
			sqlGetValue(hDatabase,hRecord,"TranMoney",pTransferMoney->stTransfer.i64Money);
			sqlGetValue(hDatabase,hRecord,"ActualTransfer",pTransferMoney->stTransfer.i64ActualTransfer);
			break;
			}
		case 1:	///<�������
			{
			uResult = DTR_GR_OPEN_WALLET_ERROR_PSW;
			break;
			}
		case 2: ///<������Ǯ���ڶ��ٲ���ת��
			{
			uResult = DTR_GR_TRANSFER_TOTAL_NOT_ENOUGH;
			sqlGetValue(hDatabase,hRecord,"LessAllMoney", pTransferMoney->stTransfer.i64ActualTransfer);
			break;
			}
		case 3: ///<����ת�ʱ�����ڶ���
			uResult = DTR_GR_TRANSFER_TOO_LESS;
			sqlGetValue(hDatabase,hRecord,"LessMoney", pTransferMoney->stTransfer.i64ActualTransfer);
			break;
		case 4: ///<����ת����ĳ����������
			uResult = DTR_GR_TRANSFER_MULTIPLE;
			sqlGetValue(hDatabase,hRecord,"Multiple", u32Data);
            pTransferMoney->stTransfer.i64ActualTransfer = u32Data;
			break;
		case 5: ///<������ֻ�ж���Ǯ��������Ҫת����Ǯ������ת
			uResult = DTR_GR_TRANSFER_NO_ENOUGH_MONEY;
			sqlGetValue(hDatabase,hRecord,"TransMoney", pTransferMoney->stTransfer.i64Money);
			sqlGetValue(hDatabase,hRecord,"BankMoney", pTransferMoney->stTransfer.i64ActualTransfer);
			break;
		case 6: ///<Ŀ���ʻ�������
			uResult = DTR_GR_TRANSFER_MONEY_NO_DEST;
			break;
		case 7:
			uResult = DTR_GR_TRANSFER_TOO_MANY_TIME;
			break;
		default:
			return 0;
		}
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
		::memcpy(&(stTransferMoneyResult.stTransfer),&(pTransferMoney->stTransfer),sizeof(MSG_GR_S_TransferMoney));
		m_pRusultService->OnDataBaseResultEvent(&stTransferMoneyResult.ResultHead,
			 uCode, uResult, sizeof(stTransferMoneyResult), pSourceData->uIndex,pSourceData->dwHandleID);
	}
	catch (...)
	{
		return 0;
	}
	return 0;
}


//��ȡ���ߴ洢����
UINT CGameDataBaseHandle::OnBankTransferRebate(DataBaseLineHead* pSourceData, UINT uCode)
{
	try
	{
		DL_GR_I_UserRebateSetStruct* pCmd = (DL_GR_I_UserRebateSetStruct*)pSourceData;
		DL_GR_O_UserRebateSetStruct cmd;
		HANDLE hDatabase=m_pDataBaseManage->hDBLogon;
		HANDLE hRecord=sqlSPSetNameEx(hDatabase,"proc_RebateUpdate", true);
		bool b = sqlSPAddPara(hDatabase,hRecord,"@UserID", pCmd->iUserID);
		b = sqlSPAddPara(hDatabase,hRecord,"@TypeN", pCmd->bTag);
		b = sqlSPAddPara_i64(hDatabase,hRecord,"@num", pCmd->iMoney);

		sqlSPExec(hDatabase,hRecord, true);
		int iRet = sqlSPGetReturnValue(hDatabase, hRecord);
		cmd.bTag = pCmd->bTag;
		cmd.iUserID = pCmd->iUserID;
		if (iRet == 1)//�ɹ�
		{
			cmd.bResult = true;		
		}
		else if (iRet == -1)//ʧ��
		{
			cmd.bResult = false;
		}
		else
		{
			return 0;
		}
		sqlGetValue(hDatabase,hRecord, "Msg", cmd.Msg, sizeof(cmd.Msg));
		cmd.iMoney = 0;

		m_pRusultService->OnDataBaseResultEvent(&cmd.ResultHead,uCode,iRet,
			sizeof(DL_GR_O_UserRebateSetStruct),pSourceData->uIndex,pSourceData->dwHandleID);
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
	}
	catch(...)
	{
		TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
	}

	return 0;
}

//����ת�˷�������
UINT CGameDataBaseHandle::OnUpdateRebate(DataBaseLineHead * pSourceData)
{
	//Ч������
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_RebateUpDateStruct)) return 0;

	HANDLE hDatabase=m_pDataBaseManage->hDBLogon;
	HANDLE hRecord=sqlExec(m_pDataBaseManage->hDBLogon,TEXT("select * from Web_Config"), true);
	//������ݶ���
	DL_GR_O_RebateUpDateStruct Rebate;
	::memset(&Rebate,0,sizeof(Rebate));
	//��������
	int iHandleResult=0;//��ʼ��
	//�ȼ�����ݿ������Ƿ��ڣ����ھ�����zht 2012-2-22
	if (0 == hRecord)
	{
		m_pDataBaseManage->SQLConnectReset();

	}
	else
	{
		sqlGetValue(hDatabase,hRecord,TEXT("Min_money"),Rebate.iMin_money);
		sqlGetValue(hDatabase,hRecord,TEXT("VIP_Rate"),Rebate.iVIP_Rate);

		CString sdp;
		sdp.Format("sdp_ ת�� ���� �������ݸ��� ���ݿ��ȡ�ɹ� ��Сת�����=%I64d,vip������=%f",Rebate.iMin_money,Rebate.iVIP_Rate);
		OutputDebugString(sdp);

		iHandleResult=1;//�ɹ�
	}
	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);//�رվ������ֹ�ڴ�й¶


	m_pRusultService->OnDataBaseResultEvent(&Rebate.ResultHead,DTK_GR_BANK_UPDATE_REBATE,iHandleResult,
		sizeof(Rebate),pSourceData->uIndex,pSourceData->dwHandleID);

	return 0;
}

//������ҷ�������
UINT CGameDataBaseHandle::OnUpdateUserRebate(DataBaseLineHead * pSourceData, UINT uCode)
{
	//Ч������
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_UserRebateUpDateStruct)) 
		return 0;
	DL_GR_I_UserRebateUpDateStruct * pCmd=(DL_GR_I_UserRebateUpDateStruct *)pSourceData;
	HANDLE hDatabase=m_pDataBaseManage->hDBLogon;
	CString sql;
	sql.Format("select * from Web_RebateInfo where UserID='%d'", pCmd->iUserID);
	HANDLE hRecord=sqlExec(m_pDataBaseManage->hDBLogon,sql, true);
	//������ݶ���
	DL_GR_O_UserRebateUpDateStruct UserRebate;
	::memset(&UserRebate,0,sizeof(UserRebate));
	//��������
	int iHandleResult=0;//��ʼ��
	//�ȼ�����ݿ������Ƿ��ڣ����ھ�����
	if (0 == hRecord)
	{
		m_pDataBaseManage->SQLConnectReset();
	}
	else
	{
		sqlGetValue(hDatabase,hRecord,TEXT("UserID"),UserRebate.iUserID);
		sqlGetValue(hDatabase,hRecord,TEXT("Tx_Money"),UserRebate.iTx_Money);
		sqlGetValue(hDatabase,hRecord,TEXT("Tx_Smony"),UserRebate.iTx_Smony);

		CString sdp;
		sdp.Format("sdp_ ת�� ���� ��ѯ��ҷ������� ���ݿ��ȡ�ɹ� ���ID=%d,ʣ�෵����Ŀ=%d,�Ѿ�ȡ�ߵ���Ŀ=%d",UserRebate.iUserID,UserRebate.iTx_Money,UserRebate.iTx_Smony);
		OutputDebugString(sdp);

		iHandleResult=1;//�ɹ�
	}
	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);//�رվ������ֹ�ڴ�й¶


	m_pRusultService->OnDataBaseResultEvent(&UserRebate.ResultHead,uCode,iHandleResult,
		sizeof(UserRebate),pSourceData->uIndex,pSourceData->dwHandleID);

	return 0;
}

//��Ǯ��
UINT CGameDataBaseHandle::OnOpenWallet(DataBaseLineHead *pSourceData, UINT uCode)
{
	//Ч������

	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_UnRegisterUser)) throw DTR_GR_OPEN_WALLET_ERROR;//////���ܵĽṹ�Ͷ�����Ƿ�һ��
	DL_GR_I_UnRegisterUser * pOpenWallet=(DL_GR_I_UnRegisterUser * )pSourceData;
	DL_GR_O_OpenWalletResult OpenWallet;///�򿪽��
	memset(&OpenWallet,0,sizeof(OpenWallet));

	try
	{
		HANDLE hDatabase=m_pDataBaseManage->hDBNative;
		HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_GetMoney",true);
		if(hRecord<(HANDLE)0x1000)
			return 0;

		sqlSPAddPara(hDatabase,hRecord,"@UserID",pOpenWallet->dwUserID);
	
		sqlSPExec(hDatabase,hRecord,true);
		
		int ret=sqlSPGetReturnValue(hDatabase,hRecord);

		if(ret!=0)
		{
			sqlCloseRecord(hDatabase,hRecord);	// zxj dfw 2009-11-12
			sqlSPClose(hDatabase,hRecord);
			throw DTR_GR_OPEN_WALLET_ERROR;
		}

		//CHAR	szMD5Pass[50];						//��������
		//ZeroMemory(szMD5Pass,sizeof(szMD5Pass));

		//sqlGetValue(hDatabase,hRecord,"TwoPassword",szMD5Pass,sizeof(szMD5Pass));
		sqlGetValue(hDatabase,hRecord,"MoneyInBank",OpenWallet.stUserBank.i64Bank);
		sqlGetValue(hDatabase,hRecord,"TwoPassword",OpenWallet.stUserBank.szTwoPassword,sizeof(OpenWallet.stUserBank.szTwoPassword));
		sqlGetValue(hDatabase,hRecord,"BankVer",OpenWallet.stUserBank.nVer);

		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
		//if (lstrcmp(szMD5Pass,pOpenWallet->szMD5Pass)!=0) 
		//	throw DTR_GR_OPEN_WALLET_ERROR_PSW;
		OpenWallet.stUserBank.dwUserID=pOpenWallet->dwUserID;
		throw DTR_GR_OPEN_WALLET_SUC;

	}
	catch (int iHandleResult)
	{TRACE("EXCEPT CATCH:%s with %s\n",__FILE__,__FUNCTION__);
		m_pRusultService->OnDataBaseResultEvent(&OpenWallet.ResultHead, uCode, iHandleResult,
			sizeof(OpenWallet),pSourceData->uIndex,pSourceData->dwHandleID);
	}
	return 0;
}


UINT CGameDataBaseHandle::OnGMWarningUserRecord(DataBaseLineHead * pSourceData)
{
	//Ч������
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_Warn_User_Record)) throw DTR_GR_ERROR_UNKNOW;//////���ܵĽṹ�Ͷ�����Ƿ�һ��
	DL_GR_I_Warn_User_Record * pWarningUser=(DL_GR_I_Warn_User_Record *)pSourceData;//�ṹ��ֵ

	HANDLE hDatabase=m_pDataBaseManage->hDBNative;
	HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_GMWarring",true);
	if(hRecord<(HANDLE)0x1000)
		return 0;

	sqlSPAddPara(hDatabase,hRecord,TEXT("@GMID"),pWarningUser->dwGMID);
	sqlSPAddPara(hDatabase,hRecord,TEXT("@UserID"),pWarningUser->dwTargetID);

	sqlSPExec(hDatabase,hRecord);
	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);
	return 0;
}


//����Ա���˶�����¼
UINT CGameDataBaseHandle::OnGMKickUserRecord(DataBaseLineHead * pSourceData)
{
	//Ч������
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_Kick_User_Record))
		throw DTR_GR_ERROR_UNKNOW;//////���ܵĽṹ�Ͷ�����Ƿ�һ��
	DL_GR_I_Kick_User_Record * pKickUser=(DL_GR_I_Kick_User_Record *)pSourceData;//�ṹ��ֵ

	HANDLE hDatabase=m_pDataBaseManage->hDBNative;
	HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_GMKickUser",true);
	if(hRecord<(HANDLE)0x1000)
		return 0;

	
	sqlSPAddPara(hDatabase,hRecord,TEXT("@GMID"),pKickUser->GMID);
	sqlSPAddPara(hDatabase,hRecord,TEXT("@UserName"),pKickUser->szTargetUserName,sizeof(pKickUser->szTargetUserName));
	sqlSPExec(hDatabase,hRecord);
	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);
	return 0;
}
//����Ȩ���޸�
UINT CGameDataBaseHandle::OnGamePower(DataBaseLineHead * pSourceData)
{
	//Ч������
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_PowerSet)) throw DTR_GR_ERROR_UNKNOW;//////���ܵĽṹ�Ͷ�����Ƿ�һ��
	DL_GR_I_PowerSet * pPowerSet=(DL_GR_I_PowerSet *)pSourceData;//�ṹ��ֵ


	HANDLE hDatabase=m_pDataBaseManage->hDBNative;
	HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_SetGamePower");
	if(hRecord<(HANDLE)0x1000)
		return 0;

	int nEveryValid=0,nOnlyRoomValid=0;
	if(pPowerSet->bBindKind&0x04)
		nEveryValid=1;
	else if(pPowerSet->bBindKind&0x01)
		nOnlyRoomValid=1;

	sqlSPAddPara(hDatabase,hRecord,TEXT("@UserID"),pPowerSet->dwUserID);
	sqlSPAddPara(hDatabase,hRecord,TEXT("@GMID"),pPowerSet->dwGMID);
	sqlSPAddPara(hDatabase,hRecord,TEXT("@PowerValue"),pPowerSet->dwGamePower);
	sqlSPAddPara(hDatabase,hRecord,TEXT("@PowerTime"),pPowerSet->uLockTime);
	sqlSPAddPara(hDatabase,hRecord,TEXT("@NameID"),m_pKernelInfo->uNameID);

	sqlSPAddPara(hDatabase,hRecord,TEXT("@EveryValid"),nEveryValid);
	sqlSPAddPara(hDatabase,hRecord,TEXT("@OnlyRoomValid"),nOnlyRoomValid);
	sqlSPAddPara(hDatabase,hRecord,TEXT("@GameTable"),m_pInitInfo->szGameTable,sizeof(m_pInitInfo->szGameTable));

	sqlSPExec(hDatabase,hRecord);

	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);
	int iHandleResult=DTK_GR_GAME_POWER_SUCCESS;
	if(pPowerSet->dwGamePower==0) 
		iHandleResult= DTK_GR_GAME_POWER_RELEASE;


	DataBaseResultLine DT_GamePowerSetResult;
	::memset(&DT_GamePowerSetResult,0,sizeof(DT_GamePowerSetResult));
	m_pRusultService->OnDataBaseResultEvent(&DT_GamePowerSetResult,DTK_GR_GAME_POWER_RESULT,iHandleResult,
		sizeof(DT_GamePowerSetResult),pSourceData->uIndex,pSourceData->dwHandleID);


	return 0;

}
//����GM����
UINT CGameDataBaseHandle::OnCallGM(DataBaseLineHead * pSourceData)
{
	//Ч������
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_CallGM)) throw DTR_GR_ERROR_UNKNOW;//////���ܵĽṹ�Ͷ�����Ƿ�һ��
	DL_GR_I_CallGM * pCallGM=(DL_GR_I_CallGM *)pSourceData;//�ṹ��ֵ

	try
	{
		HANDLE hDatabase=m_pDataBaseManage->hDBNative;
		HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_RecordCallGM",true);
		sqlSPAddPara(hDatabase,hRecord,"@UserID",pCallGM->dwUserID);
		sqlSPAddPara(hDatabase,hRecord,"@UserName",pCallGM->szName,sizeof(pCallGM->szName));
		sqlSPAddPara(hDatabase,hRecord,"@RoomID",m_pInitInfo->uRoomID);
		sqlSPAddPara(hDatabase,hRecord,"@NameID",m_pKernelInfo->uNameID);
		sqlSPAddPara(hDatabase,hRecord,"@RoomType",m_pInitInfo->uComType);
		sqlSPAddPara(hDatabase,hRecord,"@DeskNumber",pCallGM->uDeskNO+1);
		sqlSPAddPara(hDatabase,hRecord,"@DeskStation",pCallGM->uDeskStation);
		sqlSPAddPara(hDatabase,hRecord,"@CallType",pCallGM->bCallReason);
		sqlSPAddPara(hDatabase,hRecord,"@CallMsg",pCallGM->szMsg,sizeof(pCallGM->szMsg));

		sqlSPExec(hDatabase,hRecord,false);
		int ret=sqlSPGetReturnValue(hDatabase,hRecord);

		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
		if(ret==1)
			throw DTK_GR_CALL_GM_IN_ONE_MI;
		throw DTK_GR_CALL_GM_SUCCESS;
	}
	catch (int iHandleResult)
	{TRACE("EXCEPT CATCH:%s with %s\n",__FILE__,__FUNCTION__);
		DataBaseResultLine DT_CallGMResult;
		::memset(&DT_CallGMResult,0,sizeof(DT_CallGMResult));
		m_pRusultService->OnDataBaseResultEvent(&DT_CallGMResult,DTK_GR_CALL_GM_RESULT,iHandleResult,
			sizeof(DT_CallGMResult),pSourceData->uIndex,pSourceData->dwHandleID);
	}
	return 0;
}

///
/// ��¼�޸ķ�������
///
/// @param pSourceData
///
/// @ return 0�ɹ�����0

UINT CGameDataBaseHandle::OnRoomPWChangeRecord(DataBaseLineHead * pSourceData)
{
	///< Ч������
	if (pSourceData->DataLineHead.uSize != sizeof(DL_GR_RoomPWChange))
		throw DTR_GR_ERROR_UNKNOW;
	///< �ṹ��ֵ
	DL_GR_RoomPWChange * pRoomPW =(DL_GR_RoomPWChange *)pSourceData;

	try
	{
		HANDLE hDatabase = m_pDataBaseManage->hDBNative;
		HANDLE hRecord   = sqlSPSetNameEx(hDatabase,"SP_RoomPWChangeRecord",true);

		sqlSPAddPara(hDatabase,hRecord,"@UserID",pRoomPW->dwUserID);
		sqlSPAddPara(hDatabase,hRecord,"@RoomID",pRoomPW->dwRoomID);

		sqlSPExec(hDatabase,hRecord,false);
		sqlSPGetReturnValue(hDatabase,hRecord);

		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
	}
	catch (...)
	{
		TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
	}
	return 0;
}

UINT CGameDataBaseHandle::OnUserLeft(DataBaseLineHead * pSourceData)
{
	//Ч������
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_UserLeft)) throw DTR_GR_ERROR_UNKNOW;
	DL_GR_I_UserLeft * pUserLeft=(DL_GR_I_UserLeft *)pSourceData;

	try
	{
		HANDLE hDatabase=m_pDataBaseManage->hDBNative;
		HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_RecordUserLeft");
		if(hRecord<(HANDLE)0x1000)
			return 0;

		int IsRoomRecord=0;
		UINT uAllCount=pUserLeft->uWinCount+pUserLeft->uLostCount+pUserLeft->uMidCount+pUserLeft->uCutCount;

		if((pUserLeft->dwChangePoint!=0L)||(uAllCount>0L)||(pUserLeft->dwChangeMoney!=0L))
			if ((m_pInitInfo->dwRoomRule|GRR_RECORD_GAME)!=0)
				IsRoomRecord=1;

		//�޸ķ���

		sqlSPAddPara(hDatabase,hRecord,TEXT("@UserID"),pUserLeft->dwUserID);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@GameTable"),m_pInitInfo->szGameTable,sizeof(m_pInitInfo->szGameTable));
		sqlSPAddPara(hDatabase,hRecord,TEXT("@OnlineTimeCount"),pUserLeft->dwOnLineTimeCount);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@UserIsMaster"),pUserLeft->uMaster);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@NameID"),m_pKernelInfo->uNameID);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@RoomID"),m_pInitInfo->uRoomID);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@IsRoomRecord"),IsRoomRecord);

		sqlSPAddPara(hDatabase,hRecord,TEXT("@SrcPoint"),pUserLeft->dwScrPoint);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@ChangePoint"),pUserLeft->dwChangePoint);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@ChangeMoney"),pUserLeft->dwChangeMoney);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@ChangeTax"),pUserLeft->dwChangeTaxCom);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@ResultPoint"),pUserLeft->dwResultPoint);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@ChangeWin"),pUserLeft->uWinCount);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@ChangeLost"),pUserLeft->uLostCount);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@ChangeMid"),pUserLeft->uMidCount);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@ChangeCut"),pUserLeft->uCutCount);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@ClearLogonInfo"),1);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@LockTable"),m_pInitInfo->szLockTable,sizeof(m_pInitInfo->szLockTable));
	
		sqlSPExec(hDatabase,hRecord);

		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
		///< ��¼����ʱ��,������
		CBcfFile f(CBcfFile::GetAppPath() + "Function.bcf");
		CString strValue = f.GetKeyVal("OnlineCoin","Available","0");
		if (atoi(strValue))
		{
			hRecord = sqlSPSetNameEx(hDatabase,"SP_RecordOnlineTime");
			if(hRecord<(HANDLE)0x1000)
				return 0;
			sqlSPAddPara(hDatabase,hRecord,"@UserID",pUserLeft->dwUserID);
			sqlSPExec(hDatabase,hRecord);
			sqlCloseRecord(hDatabase,hRecord);
			sqlSPClose(hDatabase,hRecord);
		}
	}
	catch (...) {TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);}

	return 0;
}
///һ���Ը���ͬ�������û���Ϣ
UINT CGameDataBaseHandle::OnUpdateAllUserResult(DataBaseLineHead * pSourceData)
{
	
	//Ч������
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_AllUserData_t)) throw DTR_GR_ERROR_UNKNOW;
	DL_GR_I_AllUserData_t * pUserResult=(DL_GR_I_AllUserData_t *)pSourceData;

	//��Ҫ�Զ�������Ҹ��� 2013-01-28 wangzhitu
	int iAutoNum = 0;	

	// duanxiaohui 20111103 ���鳡(��ѳ�)�����н�ҡ�������Ϸ��¼
	if (m_pInitInfo->dwRoomRule & GRR_EXPERCISE_ROOM)
	{
		DebugPrintf("SP_UserInfoUpdateAllִ��ʧ�ܷ���ֵ���鳡(��ѳ�)�����н�� m_pInitInfo->dwRoomRule=%d",m_pInitInfo->dwRoomRule);
		delete []pUserResult->pUpdateUserInfo;
		pUserResult->pUpdateUserInfo = NULL;
		return 0;
	}
	// end duanxiaohui

	UpdateUserInfo_t *pUserInfo = pUserResult->pUpdateUserInfo;
	int nUserCount = pUserResult->nUserCount;
	int moneyGame=0;
	if(m_pInitInfo->uComType==TY_MONEY_GAME)
		moneyGame=1;

	


	HANDLE hDatabase=m_pDataBaseManage->hDBNative;
	HANDLE hRecord= NULL;
	//����
	if (!sqlExec(hDatabase,TEXT("select top 1 * from TGameServerInfo")))
	{
		m_pDataBaseManage->SQLConnectReset();
		
		DebugPrintf("SP_UserInfoUpdateAll ����");
		hDatabase=m_pDataBaseManage->hDBNative;

	}
	
	CString strParam = "";
	CString strParam1 = "";
	CString strParam2 = "";
	CString strParam3 = "";
	int nUserCount0 = 0;
	int nUserCount1 = 0;
	int nUserCount2 = 0;
	int nUserCount3 = 0;
	TCHAR szTmp[256];
	//__int64 temp = 1000000000000000000;
	int tempUserCount=0;
	CString TempStrParam="";
	CString str(""); //2013-01-29 test 
	//zht2012-03-31 ��������ʱ�����һ��
	for (int i=0; i<nUserCount; i++)
	{
			wsprintf(szTmp, TEXT("%d,%d,%I64d,%I64d,%I64d,%d,%d,%d,%d,")
			, pUserInfo->dwUserID
			, pUserInfo->dwOnLineTimeCount
			, pUserInfo->dwChangePoint
			, pUserInfo->dwChangeMoney
			, pUserInfo->dwChangeTaxCom
			, pUserInfo->uWinCount
			, pUserInfo->uLostCount
			, pUserInfo->uMidCount
			, pUserInfo->uCutCount
			);
			//�����������Ҫ�Զ����� 2013-01-28 wangzhitu
			if (pUserInfo->bISAutoSendMoney)
			{
				iAutoNum++;
			}
		    
			str.Format("wzd iAutoNum=%d",iAutoNum);
			OutputDebugString(str);
			strParam += szTmp;
			
		++pUserInfo;	///< ָ��ǰ��
	}
	
	bool bRet  = FALSE;
	int bHadSendMoney = FALSE; 

	int i = 0;
	//for (int i=0; i<4 && nUserCount>i*50;i++ )
	{

		hRecord=sqlSPSetNameEx(hDatabase,"SP_UserInfoUpdateAll", true);
		if(hRecord<(HANDLE)0x1000)
		{
			DebugPrintf("SP_UserInfoUpdateAll hRecord<(HANDLE)0x1000");
			delete []pUserResult->pUpdateUserInfo;
			pUserResult->pUpdateUserInfo = NULL;
			return 0;
		}
	
		tempUserCount = nUserCount;
		TempStrParam = strParam;
		bRet = sqlSPAddPara(hDatabase,hRecord,TEXT("@UserCount"), tempUserCount );
		bRet = sqlSPAddPara(hDatabase,hRecord,TEXT("@NameID"),m_pKernelInfo->uNameID);
		//��ս������
		char szGameTableTmp[31];
		ZeroMemory(szGameTableTmp, sizeof(szGameTableTmp));
		if (m_pInitInfo->uBattleRoomID > 0)
		{
			//�ǻ�ս����
			memcpy(szGameTableTmp,m_pInitInfo->szBattleGameTable,sizeof(szGameTableTmp));
		}
		else
		{
			//��ͨ����
			memcpy(szGameTableTmp,m_pInitInfo->szGameTable,sizeof(szGameTableTmp));
		}
		bRet = sqlSPAddPara(hDatabase,hRecord,TEXT("@GameTable"),szGameTableTmp,sizeof(szGameTableTmp));
		bRet = sqlSPAddPara(hDatabase,hRecord,TEXT("@PlayTimeCount"),pUserResult->nPlayTime);
		bRet = sqlSPAddPara(hDatabase,hRecord,TEXT("@IsExperciseRoom"),(m_pInitInfo->dwRoomRule & GRR_EXPERCISE_ROOM)?1:0);
		bRet = sqlSPAddPara(hDatabase,hRecord,TEXT("@IsMoneyGame"),(m_pInitInfo->uComType==TY_MONEY_GAME)?1:0);
		bRet = sqlSPAddPara(hDatabase, hRecord, TEXT("@Param"), TempStrParam.GetBuffer(), sizeof(TCHAR) * TempStrParam.GetLength());
	
	
		// PengJiLin, 2011-4-14, ���ӷ���ID
		bRet = sqlSPAddPara(hDatabase,hRecord,TEXT("@RoomID"),m_pInitInfo->uRoomID);


		int IsExperciseRoom = (m_pInitInfo->dwRoomRule & GRR_EXPERCISE_ROOM)?1:0;
		CString szSQL;

		szSQL.Format(TEXT("nUserCount = %d EXEC SP_UserInfoUpdateAll @UserCount=%d,@NameID=%d,@GameTable='%s',@PlayTimeCount=%d,@IsExperciseRoom=%d,@IsMoneyGame=%d,@Param='%s',@RoomID=%d"),nUserCount,tempUserCount,m_pKernelInfo->uNameID,szGameTableTmp,pUserResult->nPlayTime,IsExperciseRoom
			,(m_pInitInfo->uComType==TY_MONEY_GAME)?1:0,TempStrParam.GetBuffer(),m_pInitInfo->uRoomID);

		bRet = sqlSPExec(hDatabase,hRecord, true);



		// PengJiLin, 2011-4-14, �Ƿ��������ͽ�ҹ���
		sqlGetValue(hDatabase,hRecord,"SendMoneyFlag",bHadSendMoney);
		int ret=sqlSPGetReturnValue(hDatabase,hRecord);
		if (ret != 0 || hRecord == NULL || bRet == FALSE)
		{
			DebugPrintf("SP_UserInfoUpdateAllִ��ʧ�ܷ���ֵ%d hRecord=%d bRet=%d",ret,hRecord,bRet);
			DebugPrintf("SP_UserInfoUpdateAll����%s m_ErrorSQLCount=%d i=%d",szSQL.GetBuffer(),m_ErrorSQLCount,i);


			if (m_ErrorSQLCount < 5)
			{
				sqlCloseRecord(hDatabase,hRecord);

				sqlSPClose(hDatabase, hRecord);

				Sleep(20);
				m_ErrorSQLCount++;
				OnUpdateAllUserResult(pSourceData);
				
				return 0;
			}

			delete []pUserResult->pUpdateUserInfo;
			pUserResult->pUpdateUserInfo = NULL;

			DebugPrintf("SP_UserInfoUpdateAll����%s m_ErrorSQLCount=%d i=%d ��������",szSQL.GetBuffer(),m_ErrorSQLCount,i);


		}

		m_ErrorSQLCount = 0;
		sqlCloseRecord(hDatabase,hRecord);

		sqlSPClose(hDatabase, hRecord);

	}

    // PengJiLin, 2011-4-15, �Ƿ���ʱ���������ͽ��
    if(FALSE != bHadSendMoney 
		|| (m_pInitInfo->iTimeLength >= 0 && m_pInitInfo->iSendCount > 0)
		|| iAutoNum > 0) //����Զ�����
    {
        pUserInfo = pUserResult->pUpdateUserInfo;
        DWORD dwUserID = 0;		
        for (int i=0; i<nUserCount; ++i)
        {
			//2013-01-28 wangzhitu
			bool bISAutoSend = false;

            // ���ݿ�
            hDatabase=m_pDataBaseManage->hDBNative;
            hRecord=sqlSPSetNameEx(hDatabase,"SP_SendMoney");
            if(hRecord<(HANDLE)0x1000) break;

            dwUserID = pUserInfo->dwUserID;

            DL_GR_O_SendMoney_On_TC stSendMoney;
            memset(&stSendMoney, 0, sizeof(stSendMoney));

            bRet = sqlSPAddPara(hDatabase,hRecord,TEXT("@RoomID"), m_pInitInfo->uRoomID );
            bRet = sqlSPAddPara(hDatabase,hRecord,TEXT("@UserID"), dwUserID );

			__int64 iroundmoney = 0;
			if (m_pInitInfo->iTimeLength >= 0 && m_pInitInfo->iSendCount > 0)
			{
				if (m_pInitInfo->iTimeLength <= pUserResult->iRoundPlayTime && pUserInfo->dwChangePoint > 0)
				{
					iroundmoney = m_pInitInfo->iSendCount;
				}
			}

			bRet = sqlSPAddPara(hDatabase,hRecord,TEXT("@RoundSendMoney"), iroundmoney);
			bRet = sqlSPAddPara(hDatabase,hRecord,TEXT("@IsRoundSend"), bHadSendMoney?0:1);

			

            sqlSPExec(hDatabase,hRecord, true);
			stSendMoney.dwUserID = dwUserID;
			//��Ҫ�Զ����͵���� 2013-01-28 wangzhitu
			if (pUserInfo->bISAutoSendMoney)
			{	
				str.Format("wzd userid=%d in GetWalletMoney",dwUserID);
				OutputDebugString(str);
				bISAutoSend = true;
				//stSendMoney.strAutoSendMoney.bISAuto = true;
				GetWalletMoney(stSendMoney.strAutoSendMoney,dwUserID);				
				str.Format("wzd userid=%d out GetWalletMoney ,getmoney=%d,Result=%d,sendNO.=%d",dwUserID,stSendMoney.strAutoSendMoney.i64Money
					,stSendMoney.strAutoSendMoney.iResultCode,stSendMoney.strAutoSendMoney.iCount);
				OutputDebugString(str);
			}

			stSendMoney.strAutoSendMoney.bISOpen = bHadSendMoney;

			++pUserInfo;	
		    	
			if ((bHadSendMoney) || (bISAutoSend))
			{				
				// �����Ľ����
				sqlGetValue(hDatabase,hRecord,"SendMoney",stSendMoney.dwGetMoney);
				// ���ö���ʱ�����͵Ľ��
				sqlGetValue(hDatabase,hRecord,"PlayTimesMoney",stSendMoney.dwMoneyOnTimes);
				// ���ö��پ����͵Ľ��
				sqlGetValue(hDatabase,hRecord,"PlayCountsMoney",stSendMoney.dwMoneyOnCounts);
				// ��һ�β����ʱ��
				sqlGetValue(hDatabase,hRecord,"PlayTimes_Dist",stSendMoney.dwTimesNeed);
				// ��һ�β���پ�
				sqlGetValue(hDatabase,hRecord,"PlayCounts_Dist",stSendMoney.dwCountsNeed);

				// test
				CString strTemp = "";
				strTemp.Format("wzd PengJiLin, Serve User[%d], Money[%d], PTM[%d], PCM[%d], PTD[%d], PCD[%d]",
								stSendMoney.dwUserID,
								stSendMoney.dwGetMoney,
								stSendMoney.dwMoneyOnTimes,
								stSendMoney.dwMoneyOnCounts,
								stSendMoney.dwTimesNeed,
								stSendMoney.dwCountsNeed);
         

				m_pRusultService->OnDataBaseResultEvent(&stSendMoney.ResultHead,DTK_GR_SEND_MONEY_ON_TIMES_COUNTS,
														0,sizeof(stSendMoney),0,0);
			}
			sqlCloseRecord(hDatabase,hRecord);
			sqlSPClose(hDatabase, hRecord);
        }
    }
	else
	{
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase, hRecord);
	}
	delete []pUserResult->pUpdateUserInfo;
	pUserResult->pUpdateUserInfo = NULL;
	return 0;
}

//��ȡ���͵Ľ��ֵ //2013-01-28 wangzhitu
void CGameDataBaseHandle::GetWalletMoney(RECEIVEMONEY &strRecMoney,DWORD dwUserID)
{
	try
	{	
		HANDLE hDatabase=CDataBaseHandle::m_pDataBaseManage->hDBLogon;
		HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_ReceiveMoney", true);

		bool b=sqlSPAddPara(hDatabase,hRecord,"@UserID", dwUserID);
		     b = sqlSPAddPara(hDatabase,hRecord,"@ISWalletMoney", true);

		sqlSPExec(hDatabase,hRecord, true);
		strRecMoney.iResultCode = sqlSPGetReturnValue(hDatabase, hRecord);		

		sqlGetValue(hDatabase,hRecord,TEXT("ReceiveCount"),strRecMoney.iCount);
		sqlGetValue(hDatabase,hRecord,TEXT("ReceiveMoney"),strRecMoney.i64Money);
		sqlGetValue(hDatabase,hRecord,TEXT("MinMoney"),strRecMoney.i64MinMoney);
		sqlGetValue(hDatabase,hRecord,TEXT("ReceiveTotal"),strRecMoney.iTotal);
		sqlGetValue(hDatabase,hRecord,TEXT("SpaceTime"),strRecMoney.iTime);			
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);

	}
	catch(...)
	{
		TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
	}
}

//������ʼ����������ʼ��
UINT CGameDataBaseHandle::OnContestBegin(DataBaseLineHead * pSourceData)
{
	//Ч������
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_ContestBegin)) throw DTR_GR_ERROR_UNKNOW;
	DL_GR_I_ContestBegin* _p=(DL_GR_I_ContestBegin *)pSourceData;

	try
	{
		HANDLE hDatabase=m_pDataBaseManage->hDBNative;
		HANDLE hRecord=sqlSPSetName(hDatabase,"SP_ContestBegin", true);
		if(hRecord<(HANDLE)0x1000)
			return 0;

		//�޸ķ���
		sqlSPAddPara(hDatabase,hRecord,TEXT("@ContestID"), _p->iContestID);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@GameID"), _p->uNameID);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@RoomID"), _p->uRoomID);

		if(!sqlSPExec(hDatabase,hRecord,true))
		{
			sqlCloseRecord(hDatabase,hRecord);
			sqlSPClose(hDatabase,hRecord);
			throw DTR_GR_ERROR_UNKNOW;
			return false;
		}

		int ret=sqlSPGetReturnValue(hDatabase,hRecord);
		if (0 >= ret)
		{
			sqlCloseRecord(hDatabase,hRecord);
			sqlSPClose(hDatabase,hRecord);
			throw DTR_GR_ERROR_UNKNOW;
		}
		DL_GR_O_ContestBegin DL_OContest;
		DL_OContest.uMatchID = ret;
		DL_OContest.iUserNum = sqlGetRecordCount(hDatabase, hRecord);
		if (0 >= DL_OContest.iUserNum)
		{
			sqlCloseRecord(hDatabase,hRecord);
			sqlSPClose(hDatabase,hRecord);
			throw DTR_GR_ERROR_UNKNOW;
		}
		DL_OContest.pUserIDs = new int[sizeof(int)*DL_OContest.iUserNum];
		int iCount = 0;
		while(!sqlEndOfFile(hDatabase,hRecord))
		{
			sqlGetValue(hDatabase,hRecord,TEXT("UserID"), *(DL_OContest.pUserIDs+iCount));
			sqlMoveNext(hDatabase,hRecord);
			++iCount;
		}
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
		m_pRusultService->OnDataBaseResultEvent(&DL_OContest.ResultHead,DTK_GR_CONTEST_BEGIN_RESULT,0,sizeof(DL_GR_O_ContestBegin),pSourceData->uIndex,pSourceData->dwHandleID);
	}
	catch (...)
	{
		m_pInitInfo->iRoomState = 0;
		TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
	}

	return 0;
}

//����������������Ұ䷢����
UINT CGameDataBaseHandle::OnContestGameOver(DataBaseLineHead * pSourceData)
{
	//Ч������
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_UserContestRank)) throw DTR_GR_ERROR_UNKNOW;
	try
	{
		HANDLE hDatabase=m_pDataBaseManage->hDBNative;
		HANDLE hRecord=sqlSPSetName(hDatabase,"SP_ContestFinish",true);
		if(hRecord<(HANDLE)0x1000)
			return 0;

		//�޸ķ���
		sqlSPAddPara(hDatabase,hRecord,TEXT("@ContestID"),m_pInitInfo->iContestID);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@GameID"),m_pInitInfo->iGameID);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@RoomID"),m_pInitInfo->uRoomID);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@MatchID"),m_pInitInfo->iMatchID);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@LeastPeople"),m_pInitInfo->iLeasePeople);

		if(!sqlSPExec(hDatabase,hRecord,true))
		{
			sqlCloseRecord(hDatabase,hRecord);
			sqlSPClose(hDatabase,hRecord);
			throw DTR_GR_ERROR_UNKNOW;
			return false;
		}

		int ret=sqlSPGetReturnValue(hDatabase,hRecord);

		m_pInitInfo->iRoomState = 0;
		DL_GR_O_ContestGameOver DL_OContestGameOver;
		while(!sqlEndOfFile(hDatabase,hRecord))
		{
			ZeroMemory(&DL_OContestGameOver,sizeof(DL_GR_O_ContestGameOver));

			sqlGetValue(hDatabase,hRecord,"UserID",DL_OContestGameOver.oAward.dwUserID);
			DL_OContestGameOver.oAward.iAward = ret;
			m_pRusultService->OnDataBaseResultEvent(&DL_OContestGameOver.ResultHead,DTK_GR_CONTEST_GAME_OVER_RESULT,0,sizeof(DL_GR_O_ContestGameOver),pSourceData->uIndex,pSourceData->dwHandleID);
			sqlMoveNext(hDatabase,hRecord);
		}
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
	}
	catch (...)
	{
		m_pInitInfo->iRoomState = 0;
		TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
	}

	return 0;
}

///�����û�������Ϣ
UINT CGameDataBaseHandle::OnUpdateContestInfo(DataBaseLineHead * pSourceData)
{
	//Ч������
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_UserContestData)) throw DTR_GR_ERROR_UNKNOW;
	DL_GR_I_UserContestData* _p=(DL_GR_I_UserContestData *)pSourceData;

	try
	{
		HANDLE hDatabase=m_pDataBaseManage->hDBNative;
		HANDLE hRecord=sqlSPSetName(hDatabase,"SP_ContestUpdateRecord");
		if(hRecord<(HANDLE)0x1000)
			return 0;

		//�޸ķ���
		sqlSPAddPara(hDatabase,hRecord,TEXT("@UserID"), _p->iUserID);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@ContestID"), _p->iContestID);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@LowChip"), _p->iLowChip);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@CheckedScore"), _p->iCheckedScore);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@ContestScore"), _p->ChangeScore);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@ContestPoint"), _p->ChangePoint);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@DeskNo"), _p->iDeskNo);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@SitNO"), _p->iSitNo);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@RoomID"), _p->iRoomID);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@MatchID"), _p->iMatchID);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@GameID"), _p->iGameID);

		sqlSPExec(hDatabase,hRecord);
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);

	}
	catch (...) {TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);}

	return 0;
}

///�õ��û�������Ϣ
UINT CGameDataBaseHandle::OnGetContestInfo(DataBaseLineHead * pSourceData)
{
	//Ч������
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_UserContestRank)) throw DTR_GR_ERROR_UNKNOW;
	DL_GR_I_UserContestRank* _p = (DL_GR_I_UserContestRank*)pSourceData;
	try
	{
		HANDLE hDatabase=m_pDataBaseManage->hDBNative;
		HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_Contest_GetSomebodyRank", true);
		if(hRecord<(HANDLE)0x1000)
			return 0;

		//��ȡ����
		sqlSPAddPara(hDatabase,hRecord,TEXT("@ContestID"),m_pInitInfo->iContestID);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@MatchID"),m_pInitInfo->iMatchID);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@GameID"),m_pInitInfo->iGameID);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@RoomID"),m_pInitInfo->uRoomID);

		sqlSPExec(hDatabase,hRecord,true);

		int iPeople = sqlSPGetReturnValue(hDatabase,hRecord);//����ֵ�ǵ�ǰʣ������		
		DL_GR_O_UserContestRank _out;
		while(!sqlEndOfFile(hDatabase,hRecord))
		{
			ZeroMemory(&_out,sizeof(DL_GR_O_UserContestRank));

			sqlGetValue(hDatabase,hRecord,"UserID",_out._data.dwUserID);
			sqlGetValue(hDatabase,hRecord,"RankNum",_out._data.iRankNum);
			sqlGetValue(hDatabase,hRecord,"ContestScore",_out._data.i64ContestScore);
			sqlGetValue(hDatabase,hRecord,"ContestCount",_out._data.iContestCount);
			_out._data.iRemainPeople = iPeople;

			if (_out._data.iRankNum > 0)
			{
				m_pRusultService->OnDataBaseResultEvent(&_out.ResultHead,DTK_GR_GET_CONTEST_RESULT,0,sizeof(DL_GR_O_UserContestRank),pSourceData->uIndex,pSourceData->dwHandleID);
			}

			sqlMoveNext(hDatabase,hRecord);
		}

		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);

	}
	catch (...) {TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);}

	return 0;
}

UINT CGameDataBaseHandle::OnContestApply(DataBaseLineHead * pSourceData)
{
	//Ч������
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_ContestApply)) throw DTR_GR_ERROR_UNKNOW;
	DL_GR_I_ContestApply *pContestApply = (DL_GR_I_ContestApply*)pSourceData;
	
	try
	{
		//���������洢���̶��ǽ�����վ���汨���Ĵ洢����

		//����
		HANDLE hDatabase = m_pDataBaseManage->hDBNative;
		HANDLE hRecord = sqlSPSetName(hDatabase, "SP_ContestApply");
		if (hRecord < (HANDLE)0x1000)
			return 0;
				
		sqlSPAddPara(hDatabase, hRecord, TEXT("@gameID"), m_pInitInfo->iGameID);
		sqlSPAddPara(hDatabase, hRecord, TEXT("@UserID"), pContestApply->iUserID);
		sqlSPAddPara(hDatabase, hRecord, TEXT("@TypeID"), pContestApply->iTypeID);
		sqlSPAddPara(hDatabase, hRecord, TEXT("@roomID"), m_pInitInfo->uRoomID);
		sqlSPAddPara(hDatabase, hRecord, TEXT("@ContestID"), m_pInitInfo->iContestID);
		
		if(!sqlSPExec(hDatabase,hRecord,true))
		{
			sqlCloseRecord(hDatabase,hRecord);
			sqlSPClose(hDatabase,hRecord);
			throw DTR_GR_ERROR_UNKNOW;
			return 0;
		}

		DL_GR_O_ContestApply DL_OContestApply;
		DL_GR_O_ContestInfo DL_OContestInfo;
		DL_OContestApply.iUserID = pContestApply->iUserID;
		sqlGetValue(hDatabase, hRecord, ("rs"), DL_OContestApply.iApplyResult);	//ִ�����
		
		int iEntryFee = 0;
		sqlGetValue(hDatabase, hRecord, "EntryFee", iEntryFee);
		//�ж��Ƿ����ɹ�����������sql�ŵ��洢�����л�����ݲ����ԭ�����ó����ŵ��˴�ִ�У��á�----����ǣ�
		/*------------------------------------------------------------------*/
		if (1 == DL_OContestApply.iApplyResult)
		{
			CString strSql;
			if (iEntryFee > 0)
			{
				strSql.Format("update TUserInfo set WalletMoney=WalletMoney-%d where userid=%d", iEntryFee, pContestApply->iUserID);
				if (!sqlExec(hDatabase, strSql))
				{
					m_pDataBaseManage->SQLConnectReset();
					sqlCloseRecord(hDatabase,hRecord);
					sqlSPClose(hDatabase,hRecord);
					throw DTR_GR_ERROR_UNKNOW;
				}
			}
			CTime tm = CTime::GetCurrentTime();
			strSql.Format("insert into TSignUp values(%d,%d,%d,%d,0,'%d-%d-%d %d:%d:%d',%d)", 
				m_pInitInfo->iGameID, m_pInitInfo->iContestID, m_pInitInfo->uRoomID, pContestApply->iUserID, 
				tm.GetYear(), tm.GetMonth(), tm.GetDay(), tm.GetHour(), tm.GetMinute(), tm.GetSecond(), iEntryFee);
			if (!sqlExec(hDatabase, strSql))
			{
				m_pDataBaseManage->SQLConnectReset();
				sqlCloseRecord(hDatabase,hRecord);
				sqlSPClose(hDatabase,hRecord);
				throw DTR_GR_ERROR_UNKNOW;
			}
		}
		else if(2 == DL_OContestApply.iApplyResult)  //�����ɹ����˻ر�����
		{

			CString strSql;
			if (iEntryFee > 0)
			{
				strSql.Format("update TUserInfo set WalletMoney=WalletMoney+%d where userid=%d", iEntryFee, pContestApply->iUserID);
				if (!sqlExec(hDatabase, strSql))
				{
					m_pDataBaseManage->SQLConnectReset();
					sqlCloseRecord(hDatabase,hRecord);
					sqlSPClose(hDatabase,hRecord);
					throw DTR_GR_ERROR_UNKNOW;
				}
			}
			
			strSql.Format("delete TSignUp where gameNameid=%d and ContestID=%d and roomid=%d and userid=%d", 
				m_pInitInfo->iGameID, m_pInitInfo->iContestID, m_pInitInfo->uRoomID, pContestApply->iUserID);
			if (!sqlExec(hDatabase, strSql))
			{
				m_pDataBaseManage->SQLConnectReset();
				sqlCloseRecord(hDatabase,hRecord);
				sqlSPClose(hDatabase,hRecord);
				throw DTR_GR_ERROR_UNKNOW;
			}
		}
		/*------------------------------------------------------------------*/
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
	
		//�ж��Ƿ�ﵽ��������������������һ���洢��������ɵģ���������ֻ�޸Ļ����˴��룬����ֻ�÷�����ִ��
		hDatabase = m_pDataBaseManage->hDBNative;
		hRecord = sqlSPSetNameEx(hDatabase, "proc_TContestPeopleNum", true);//������ҳ�ϱ����Ĵ洢����
		if (hRecord < (HANDLE)0x1000)
			return 0;

		sqlSPAddPara(hDatabase, hRecord, TEXT("@gameID"), m_pInitInfo->iGameID);
		sqlSPAddPara(hDatabase, hRecord, TEXT("@roomID"), m_pInitInfo->uRoomID);
		sqlSPAddPara(hDatabase, hRecord, TEXT("@contestID"), m_pInitInfo->iContestID);
		if(!sqlSPExec(hDatabase,hRecord,true))
		{
			sqlCloseRecord(hDatabase,hRecord);
			sqlSPClose(hDatabase,hRecord);
			throw DTR_GR_ERROR_UNKNOW;
			return 0;
		}
		DL_OContestApply.iUserID = pContestApply->iUserID;
		sqlGetValue(hDatabase, hRecord, TEXT("ynum"), DL_OContestInfo._data.iContestNum);	//ִ�����
		sqlGetValue(hDatabase, hRecord, TEXT("isOK"), DL_OContestApply.iContestBegin);	//ִ�����
		DL_OContestInfo._data.iContestBegin = DL_OContestApply.iContestBegin;

		m_pRusultService->OnDataBaseResultEvent(&DL_OContestApply.ResultHead,DTK_GR_CONTEST_APPLY,0,sizeof(DL_OContestApply),pSourceData->uIndex,pSourceData->dwHandleID);	
		if(2 == DL_OContestApply.iApplyResult || 1 == DL_OContestApply.iApplyResult)
		{
			m_pRusultService->OnDataBaseResultEvent(&DL_OContestInfo.ResultHead,DTK_GR_CONTEST_BROADCAST,0,sizeof(DL_OContestInfo),pSourceData->uIndex,pSourceData->dwHandleID);	
		}
		
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
		
		return 0;
	}
	catch (...) 
	{
		TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
	}
	return 0;
}

UINT CGameDataBaseHandle::OnUpdateUserResult(DataBaseLineHead * pSourceData)
{
	//Ч������
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_UserLeft)) throw DTR_GR_ERROR_UNKNOW;
	DL_GR_I_UserLeft * pUserResult=(DL_GR_I_UserLeft *)pSourceData;

	// duanxiaohui 20111103 ���鳡(��ѳ�)�����н�ҡ�������Ϸ��¼
	if (m_pInitInfo->dwRoomRule & GRR_EXPERCISE_ROOM || m_pInitInfo->dwRoomRule & GRR_CONTEST || m_pInitInfo->dwRoomRule & GRR_TIMINGCONTEST)
	{
		return 0;
	}
	// end duanxiaohui
	
	int moneyGame=0;
	if(m_pInitInfo->uComType==TY_MONEY_GAME)
		moneyGame=1;

	HANDLE hDatabase=m_pDataBaseManage->hDBNative;
	HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_UserInfoUpdate");
	if(hRecord<(HANDLE)0x1000)
		return 0;
	//DebugPrintf("dwUserID=[%d],Point = [%d]ChangeMoney = [%d]",
	//	pUserResult->dwUserID,
	//	pUserResult->dwChangePoint,
	//	pUserResult->dwChangeMoney
	//	);
	sqlSPAddPara(hDatabase,hRecord,TEXT("@UserID"),pUserResult->dwUserID);
	sqlSPAddPara(hDatabase,hRecord,TEXT("@NameID"),m_pKernelInfo->uNameID);
	sqlSPAddPara(hDatabase,hRecord,TEXT("@OnlineTime"),pUserResult->dwOnLineTimeCount);
	sqlSPAddPara(hDatabase,hRecord,TEXT("@IsMoneyGame"),moneyGame);
	//wushuqun 2009.6.5
	//��ս������
	char szGameTableTmp[31];
	memset(szGameTableTmp,0,sizeof(szGameTableTmp));
	if (m_pInitInfo->uBattleRoomID > 0)
	{
		//�ǻ�ս����
		memcpy(szGameTableTmp,m_pInitInfo->szBattleGameTable,sizeof(szGameTableTmp));
	}
	else
	{
		//��ͨ����
		memcpy(szGameTableTmp,m_pInitInfo->szGameTable,sizeof(szGameTableTmp));
	}
    sqlSPAddPara(hDatabase,hRecord,TEXT("@GameTable"),szGameTableTmp,sizeof(szGameTableTmp));
	///////////////////////////////////

	//sqlSPAddPara(hDatabase,hRecord,TEXT("@GameTable"),m_pInitInfo->szGameTable,sizeof(m_pInitInfo->szGameTable));
	sqlSPAddPara(hDatabase,hRecord,TEXT("@Point"),pUserResult->dwChangePoint);
	sqlSPAddPara(hDatabase,hRecord,TEXT("@Money"),pUserResult->dwChangeMoney);
	sqlSPAddPara(hDatabase,hRecord,TEXT("@TaxCom"),pUserResult->dwChangeTaxCom);
	sqlSPAddPara(hDatabase,hRecord,TEXT("@Win"),pUserResult->uWinCount);
	sqlSPAddPara(hDatabase,hRecord,TEXT("@Lost"),pUserResult->uLostCount);
	sqlSPAddPara(hDatabase,hRecord,TEXT("@Mid"),pUserResult->uMidCount);
	sqlSPAddPara(hDatabase,hRecord,TEXT("@Cut"),pUserResult->uCutCount);
	sqlSPAddPara(hDatabase,hRecord,TEXT("@PlayTimeCount"),pUserResult->dwPlayTimeCount);
	sqlSPAddPara(hDatabase,hRecord,TEXT("@IsExperciseRoom"),(m_pInitInfo->dwRoomRule & GRR_EXPERCISE_ROOM || m_pInitInfo->dwRoomRule & GRR_CONTEST ||m_pInitInfo->dwRoomRule & GRR_TIMINGCONTEST)?1:0);
	sqlSPExec(hDatabase,hRecord);
	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);
	return 0;
}


//��ʱ���·����ͽ��
UINT CGameDataBaseHandle::OnModifyUserMoney(DataBaseLineHead * pSourceData)
{
	//Ч������
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_Update_InstantMoney)) throw DTR_GR_ERROR_UNKNOW;
	DL_GR_Update_InstantMoney * pUserResult = (DL_GR_Update_InstantMoney *)pSourceData;

	int cut=0;
	if(pUserResult->bCutValue)
		cut=1;

	HANDLE hDatabase=m_pDataBaseManage->hDBNative;
	HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_ChangeMoneyInTime");
	if(hRecord<(HANDLE)0x1000)
		return 0;

	sqlSPAddPara(hDatabase,hRecord,TEXT("@UserID"),pUserResult->dwUserID);
	sqlSPAddPara(hDatabase,hRecord,TEXT("@GameNameID"),m_pKernelInfo->uNameID);
	sqlSPAddPara(hDatabase,hRecord,TEXT("@GameTable"),m_pInitInfo->szGameTable,sizeof(m_pInitInfo->szGameTable));
	sqlSPAddPara(hDatabase,hRecord,TEXT("@Wallet"),pUserResult->dwChangeMoney);
	sqlSPAddPara(hDatabase,hRecord,TEXT("@Point"),pUserResult->dwChangePoint);
	sqlSPAddPara(hDatabase,hRecord,TEXT("@Cut"),cut);

	sqlSPExec(hDatabase,hRecord);
	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);
	return 0;
}

//��������ֵ
UINT CGameDataBaseHandle::OnUpdateUserCharm(DataBaseLineHead * pSourceData)
{
	//Ч������
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_AddCharm)) throw DTR_GR_ERROR_UNKNOW;
	DL_GR_I_AddCharm * pCharm = (DL_GR_I_AddCharm *)pSourceData;

	TCHAR szSQL[1000];
	if(pCharm->iCharmValue != 0)
	{
		wsprintf(szSQL,TEXT("UPDATE TUserInfo SET Fascination=Fascination+%d WHERE UserID=%ld"),pCharm->iCharmValue,pCharm->dwUserID);
		HANDLE hDatabase=m_pDataBaseManage->hDBNative;
		sqlExec(hDatabase,szSQL);
	}
	return 0;
}


UINT CGameDataBaseHandle::OnUseSmallBoardcast(DataBaseLineHead * pSourceData)
{
	PROP_GPR_I_BOARDCAST *iBoard=(PROP_GPR_I_BOARDCAST*)pSourceData;
	PROP_GPR_O_BOARDCAST oBoard;
	memcpy(&oBoard.boardCast,&iBoard->boardCast,sizeof(_TAG_BOARDCAST));

	HANDLE hDatabase=m_pDataBaseManage->hDBNative;
	HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_UsePropForSelf",true);
	if(hRecord<(HANDLE)0x1000)
		return 0;

	sqlSPAddPara(hDatabase,hRecord,"@UserID",iBoard->boardCast.dwUserID);
	sqlSPAddPara(hDatabase,hRecord,"@PropID",iBoard->boardCast.nPropID);
	sqlSPAddPara(hDatabase,hRecord,"@PropCount",1);

	sqlSPExec(hDatabase,hRecord,false);

	int ret=sqlSPGetReturnValue(hDatabase,hRecord);

	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);
	int iHandleResult=DTK_GR_PROP_USE_SUCCEED;
	if(ret!=0)
		iHandleResult=DTR_GR_PROP_USE_ERR_NOPROP;

	m_pRusultService->OnDataBaseResultEvent(&oBoard.ResultHead,DTK_GPR_PROP_SMALL_BRD,iHandleResult,sizeof(PROP_GPR_O_BOARDCAST),pSourceData->uIndex,pSourceData->dwHandleID);

	return 0;
}

UINT CGameDataBaseHandle::OnSendUserMoenyByTimes(DataBaseLineHead *pSourceData)
{
	//QR

	//Ч������
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_SendMonet_By_Times)) throw DTR_GR_ERROR_UNKNOW;
	DL_GR_I_SendMonet_By_Times * pSendMoeny=(DL_GR_I_SendMonet_By_Times *)pSourceData;

	DL_GR_O_SendMonet_By_Times sSendMoenyResult;
	memset(&sSendMoenyResult,0,sizeof(sSendMoenyResult));

	//comroominfo���й��ڶ��ͽ�ҵ�����
	int iPerMoney = 0;       //һ���Ͷ���
	int iDayMoneyTimes = 0;  //һ���Ͷ��ٴ�
	//int iDayLessMoney = 0;   //������ڶ��پ���
	//ComRoomInfo�н�ҷ��������
	sSendMoenyResult.dwUserID = pSendMoeny->dwUserID;
	sSendMoenyResult.i64SrcGameMoney = pSendMoeny->i64SrcGameMoney;
	sSendMoenyResult.i64SrcMoneyInBank = pSendMoeny->i64SrcMoneyInBank;
	sSendMoenyResult.dwAllSendTImes = 0;
	sSendMoenyResult.dwSendFailedCause = 0;
	sSendMoenyResult.dwSendGameMoney = 0;
	sSendMoenyResult.dwSendTimes = pSendMoeny->dwGameFinishCount;

	int FinishCount = pSendMoeny->dwGameFinishCount;//��õ�ǰ�Ƕ��ٴ���Ϸ��

	HANDLE hDatabase=m_pDataBaseManage->hDBNative;
	HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_SendMoney",true);
	if(hRecord<(HANDLE)0x1000)
		return 0;


	sqlSPAddPara(hDatabase,hRecord,"@RoomID",m_pInitInfo->uRoomID);
	sqlSPAddPara(hDatabase,hRecord,"@UserID",pSendMoeny->dwUserID);

	sqlSPExec(hDatabase,hRecord,true);

	sSendMoenyResult.dwSendFailedCause=sqlSPGetReturnValue(hDatabase,hRecord);

	if(sSendMoenyResult.dwSendFailedCause==0)
	{
		sqlGetValue(hDatabase,hRecord,"TMoney",sSendMoenyResult.dwSendGameMoney);
		sqlGetValue(hDatabase,hRecord,"DaySendTimes",sSendMoenyResult.dwSendTimes);
		sqlGetValue(hDatabase,hRecord,"DayMoneyTimes",sSendMoenyResult.dwAllSendTImes);
	}

	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);

	m_pRusultService->OnDataBaseResultEvent(&sSendMoenyResult.ResultHead,DTK_GR_SENDMONEY_TIMES,sSendMoenyResult.dwSendFailedCause,
		sizeof(sSendMoenyResult),pSourceData->uIndex,pSourceData->dwHandleID);
	return 0;
}
//���ʹ�õ���
UINT CGameDataBaseHandle::OnUserUseOneProp(DataBaseLineHead *pSourceData)
{

	//////////////////////////////////////////////////////////////////////////
	//Ч������
	//2008-08-11
	if (pSourceData->DataLineHead.uSize != sizeof(DL_GR_I_USEPROP))
		throw DTR_GR_PROP_USE_ERR_PARAM_INVALID;//////���ܵĽṹ�Ͷ�����Ƿ�һ��

	DL_GR_I_USEPROP	*useIProp = (DL_GR_I_USEPROP * )pSourceData;
	DL_GR_O_USEPROP useOProp;
	ZeroMemory(&useOProp,sizeof(DL_GR_O_USEPROP));
	memcpy(&useOProp.usingProp,&useIProp->usingProp,sizeof(_TAG_USINGPROP));

	HANDLE hDatabase = m_pDataBaseManage->hDBNative;
	HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_UseProp",true);
	if(hRecord<(HANDLE)0x1000)
		return 0;

	//ȡֵ����
	int attribValue=useIProp->usingProp.nPropValueAttrib;
	//��������
	int attribAction=useIProp->usingProp.nPropActionAttrib;
	//���¼���������Ҫ����ʱ��
	CString stime;
	stime.Format("%d",CTime::GetCurrentTime());
	int curTime=atoi(stime);

	//Ӱ��ʱ���ʱ��ֵ������Ϊ��λ
	int		addSecond=attribValue & 0xFFFF;
	addSecond*=3600;//��������СʱΪ��λ�ģ�����Ҫ�ٳ���60*60=3600��
	//˫������
	if(attribAction & 0x4)
	{
		if(curTime>useOProp.usingProp.iDoubleTime)
			//�����ǰ��˫������ʱ���ѹ��ڣ���ֱ�������ڵĿ�ʼʱ���ϼ�����Ӧ��ʱ��
			useOProp.usingProp.iDoubleTime=curTime+addSecond;
		else
			//�����ǰ��˫������ʱ�仹δ���ڣ�����ԭ�еĵ���ʱ���ϼ�����Ӧ��ʱ��
			useOProp.usingProp.iDoubleTime+=addSecond;
	}
	//��������ߣ����˲��۷�
	if(attribAction & 0x8)
	{
		if(curTime>useOProp.usingProp.iProtectTime)
			//�����ǰ�Ļ����ʱ���ѹ��ڣ���ֱ�������ڵĿ�ʼʱ���ϼ�����Ӧ��ʱ��
			useOProp.usingProp.iProtectTime=curTime+addSecond;
		else
			//�����ǰ�Ļ����ʱ�仹δ���ڣ�����ԭ�еĵ���ʱ���ϼ�����Ӧ��ʱ��
			useOProp.usingProp.iProtectTime+=addSecond;
	}
	//����ֵ�仯
	int fasciChange=0;
	if(attribAction & 0x10)
	{
		//����ֵ�仯��
		fasciChange=(attribValue & 0xFF0000)>>16;
		//��������ֵ���Ǽ�������ֵ
		if(attribAction & 0x20)
			fasciChange=-fasciChange;
	}

	sqlSPAddPara(hDatabase,hRecord,"@UserID",useIProp->usingProp.dwUserID);
	sqlSPAddPara(hDatabase,hRecord,"@PropID",useIProp->usingProp.nPropID);
	sqlSPAddPara(hDatabase,hRecord,"@TargetID",useIProp->usingProp.dwTargetUserID);
	//���NameID�����ڸ�������
	sqlSPAddPara(hDatabase,hRecord,"@GameNameID",m_pKernelInfo->uNameID);
	sqlSPAddPara(hDatabase,hRecord,"@GameTable",m_pInitInfo->szGameTable,sizeof(m_pInitInfo->szGameTable));
	//�Ƿ񸺷�����
	sqlSPAddPara(hDatabase,hRecord,"@IsClearMinus", (attribAction & 0x2)?1:0);
	//�Ƿ��С���� // PengJiLin, 2010-6-1, ���� ������
	sqlSPAddPara(hDatabase,hRecord,"@IsBoard",(attribAction & 0x80 || attribAction & 0x100 || attribAction & 0x200)?1:0);
	//˫�����ֱ仯
	sqlSPAddPara(hDatabase,hRecord,"@DoubleTime",useOProp.usingProp.iDoubleTime);
	//������仯
	sqlSPAddPara(hDatabase,hRecord,"@ProtectTime",useOProp.usingProp.iProtectTime);
	//����ֵ�仯
	sqlSPAddPara(hDatabase,hRecord,"@FasciChange",fasciChange);
	sqlSPExec(hDatabase,hRecord,false);

	int ret=sqlSPGetReturnValue(hDatabase,hRecord);

	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);

	int iHandleResult=DTK_GR_PROP_USE_SUCCEED;
	if(ret!=0)
		iHandleResult=DTR_GR_PROP_USE_ERR_NOPROP;

	m_pRusultService->OnDataBaseResultEvent(&useOProp.ResultHead,DTK_GR_PROP_USE,iHandleResult,sizeof(DL_GR_O_USEPROP),pSourceData->uIndex,pSourceData->dwHandleID);

	return 0;

}
//////////////////////////////
//20090203 Kylin ��ֹ�������ݿ���û���½ʧ��
//�����û�����
UINT CGameDataBaseHandle::OnUnRegisterOnLine(DataBaseLineHead * pSourceData)
{
	//Ч������
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_UnRegisterUser)) throw DTR_GR_ERROR_UNKNOW;
	DL_GR_I_UnRegisterUser * pUnRegisterUser=(DL_GR_I_UnRegisterUser *)pSourceData;

	//��������
	try	{ UnRegisterUserLogon(pUnRegisterUser->dwUserID,false); }
	catch (...) {}

	return 0;
}

//wushuqun 2009.5.22
//�޸Ľ�ֹ��¼���⣬�޸Ĳ���TWLoginRecord ��¼ʱ��
//ִ��ʱ������¼�����������Ϸ�����б�ִ��
UINT CGameDataBaseHandle::OnWriteTWLoginRecord(DataBaseLineHead * pSourceData)
{
	//Ч������
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_WriteWLoginRecord))
	{
		throw DTR_GR_ERROR_UNKNOW;
	}
	DL_GR_I_WriteWLoginRecord * pDlWriteWLogin = (DL_GR_I_WriteWLoginRecord *)pSourceData;
	//��������
	try
	{
		HANDLE hDatabase = m_pDataBaseManage->hDBNative;
		HANDLE hRecord = sqlSPSetNameEx(hDatabase, "SP_InsertWLoginRecord");
		if(hRecord>(HANDLE)0x1000)
		{
			sqlSPAddPara(hDatabase,hRecord,"@UserID", pDlWriteWLogin->dwUserID);
			sqlSPAddPara(hDatabase,hRecord,"@RoomID", pDlWriteWLogin->uRoomID);
			sqlSPExec(hDatabase,hRecord);
			sqlCloseRecord(hDatabase,hRecord);
			sqlSPClose(hDatabase,hRecord);
		}
	}
	catch (...) {}

	return 0;
}

//wushuqun 2009.6.6
//��ʱ��������
//�����и÷���������������
UINT CGameDataBaseHandle::OnAloneDeskInTime(DataBaseLineHead * pSourceData)
{
	//��������
	if (pSourceData->DataLineHead.uSize != sizeof(DL_GR_I_ALone_Data))
	{
		throw DTR_GR_ERROR_UNKNOW;;
	}
	DL_GR_I_ALone_Data * pAloneDeskData = (DL_GR_I_ALone_Data * )pSourceData;
	try
	{
		HANDLE hDatabase = m_pDataBaseManage->hDBNative;
		HANDLE hRecord = sqlSPSetNameEx(hDatabase, "SP_AloneDeskInTime",true);
		if(hRecord>(HANDLE)0x1000)
		{
			sqlSPAddPara(hDatabase,hRecord,"@RoomID", pAloneDeskData->uRoomID);
			sqlSPAddPara(hDatabase,hRecord,"@RoomVirtualPeople", pAloneDeskData->bDeskPeople);
			sqlSPExec(hDatabase,hRecord);
			int bRet = ::sqlSPGetReturnValue(hDatabase,hRecord);
			//SP_AloneDeskInTime �洢���̷���ֵ˵��
			// 0 :��ӷ���������ʧ��
			// 1 :��ӷ��������˳ɹ�
			if (bRet == 0)
			{
				CString str;
				str.Format("����ID: %d,�����������ʧ��",pAloneDeskData->uRoomID);
				::OutputDebugString(str);
			}
			if (bRet == 1)
			{
				//������������ɹ�
			}
			sqlCloseRecord(hDatabase,hRecord);
			sqlSPClose(hDatabase,hRecord);
		}
	}
	catch(...)
	{
	}
	return 0;
}

//ɾ����½��Ϣ
bool CGameDataBaseHandle::UnRegisterUserLogon(long int dwUserID, bool bAllLogonInfo)
{
	if (m_pInitInfo->szLockTable[0]!=0)
	{
		//ɾ������
		//TCHAR szSQL[1000];
		//if (bAllLogonInfo==true)
		//	wsprintf(szSQL,TEXT("DELETE from %s WHERE RoomID=%ld"),m_pInitInfo->szLockTable[0],m_pInitInfo->uRoomID);
		//else 
		//	wsprintf(szSQL,TEXT("DELETE from %s WHERE UserID=%ld AND RoomID=%ld"),m_pInitInfo->szLockTable,dwUserID,m_pInitInfo->uRoomID);
		//if (m_pDataBaseManage->m_DataBaseLogon.Execute(szSQL)==false)
		//{
		//	m_pDataBaseManage->m_DataBaseNative.ShowError(true);
		//}
		//////////////////////////////
		//20090203 Kylin ��ֹ�������ݿ���û���½ʧ��
		HANDLE hDatabase=m_pDataBaseManage->hDBNative;
		HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_SetUserOnlineFlag");
		if(hRecord<(HANDLE)0x1000)
			return false;
		sqlSPAddPara(hDatabase,hRecord,"@UserID",dwUserID);
		///////////////////////////////////////////////
		///Kylin 20090201 ��ֹ�˺�ͬʱ��½
		sqlSPAddPara(hDatabase,hRecord,"@FlagID",-2);
		///////////////////////////////////////////////
		sqlSPExec(hDatabase,hRecord);
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);

		//////////////////////////////

	}

	return true;
}

HANDLE CGameDataBaseHandle::sqlSPSetNameEx(HANDLE & hHandle,LPCTSTR szSPName,bool bReturnValue)
{

	bool bIsDBNative = false;;
	if(hHandle == m_pDataBaseManage->hDBNative)
	{
		bIsDBNative = true;
	}

	if (bIsDBNative)
	{
		hHandle = m_pDataBaseManage->hDBNative;
	}
	else
	{
		hHandle = m_pDataBaseManage->hDBLogon;
	}

	if (!sqlExec(hHandle,TEXT("select top 1 * from TGameServerInfo")))
	{
		m_pDataBaseManage->SQLConnectReset();

	}

	return  sqlSPSetName(hHandle,szSPName,bReturnValue);

}

UINT CGameDataBaseHandle::FillTimingMatchQueueUser(DataBaseLineHead *pSourceData)
{
	DL_GR_I_TimingMatchUsers *pQueryInfo = (DL_GR_I_TimingMatchUsers*)pSourceData;
	if(!pQueryInfo)
		return 0;
	HANDLE hDatabase=m_pDataBaseManage->hDBLogon;
	HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_GetTimingMatchUsers",true);
	if(hRecord<(HANDLE)0x1000)
	{
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
		return 0;
	}
	sqlSPAddPara(hDatabase,hRecord,"@gameID", pQueryInfo->iGameID);
	sqlSPAddPara(hDatabase,hRecord,"@roomID", pQueryInfo->iRoomID);
	sqlSPAddPara(hDatabase,hRecord,"@contestID",pQueryInfo->iContestID);

	if(!sqlSPExec(hDatabase,hRecord,true))
	{
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
		return 0;
	}
	int iRecordCount = sqlGetRecordCount(hDatabase,hRecord);
	DL_GR_O_TimingMatchUsers outMatchUsers;
	memset(&outMatchUsers,0,sizeof(DL_GR_O_TimingMatchUsers));
	outMatchUsers.iUserCount = iRecordCount;
	int icounter = 0;

	while(!sqlEndOfFile(hDatabase,hRecord))
	{
		if(icounter >= 100)
			break;
		sqlGetValue(hDatabase,hRecord,"UserID",outMatchUsers.iArrayUserid[icounter]);

		sqlMoveNext(hDatabase, hRecord);
		++icounter;
	}
	m_pRusultService->OnDataBaseResultEvent(&outMatchUsers.ResultHead, DTK_GR_TIMINGMATCH_GETQUEQUEUSERS, 0, sizeof(DL_GR_O_TimingMatchUsers), pSourceData->uIndex, pSourceData->dwHandleID);
	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);

	return 0;
}

int CGameDataBaseHandle::OnFindBuyDeskStation(DataBaseLineHead *pSourceData)
{
	DL_GR_I_FindDeskBuyStation *pReveiveData = (DL_GR_I_FindDeskBuyStation *)pSourceData;
	if(!pReveiveData)
	{
		return 0;
	}
	HANDLE hDatabase=m_pDataBaseManage->hDBNative;
	HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_FindBuyDeskStation",true);
	if(hRecord<(HANDLE)0x1000)
	{
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
		return 0;
	}
	sqlSPAddPara(hDatabase,hRecord,"@RoomID",pReveiveData->iRoomID);
	if(!sqlSPExec(hDatabase,hRecord,true))
	{
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
		return 0;
	}
	DL_GR_O_FindDeskBuyStationResult out_data;
	int iRecordCount = sqlGetRecordCount(hDatabase,hRecord);
	int iTableNumber=0,iVipCount=0,iUserID=0;
	bool iIsBuy=false;
	char szPassWord[20];
	for(int i=0;i<iRecordCount;i++)
	{
		iTableNumber=0;
		iVipCount=0;
		iUserID=0;
		iIsBuy=false;
		char szPassWord[20];
		memset(szPassWord,0,sizeof(szPassWord));
		sqlGetValue(hDatabase,hRecord,"DeskNumber",iTableNumber);
		sqlGetValue(hDatabase,hRecord,"VipCount",iVipCount);
		sqlGetValue(hDatabase,hRecord,"IsBuy",iIsBuy);
		sqlGetValue(hDatabase,hRecord,"UserID",iUserID);
		sqlGetValue(hDatabase,hRecord,"DeskPassWord",szPassWord,sizeof(szPassWord));
		if(iTableNumber<0 || iTableNumber>=100)
		{
			continue;
		}
		out_data.bIsBuy[iTableNumber]=iIsBuy;
		out_data.iVipCount[iTableNumber]=iVipCount;
		out_data.iUserID[iTableNumber]=iUserID;
		memcpy(out_data.szDeskPassWord[iTableNumber],szPassWord,sizeof(szPassWord));
		sqlMoveNext(hDatabase, hRecord);
	}
	m_pRusultService->OnDataBaseResultEvent(&out_data.ResultHead, DTK_GR_FINDDESKBUYSTATION,0, sizeof(out_data), pSourceData->uIndex, pSourceData->dwHandleID);
	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);
}
int CGameDataBaseHandle::OnClearBuyDesk(DataBaseLineHead *pSourceData)
{
	DL_GR_I_BuyDeskOut *pReveiveData = (DL_GR_I_BuyDeskOut *)pSourceData;
	if(!pReveiveData)
	{
		return 0;
	}
	HANDLE hDatabase=m_pDataBaseManage->hDBNative;
	CString sql="";
	sql.Format("delete from TBuyGameDeskRecord where RoomID=%d and TableNumber=%d",pReveiveData->iRoomID,pReveiveData->byDeskIndex);
	HANDLE hRecord=sqlExec(hDatabase,sql);
	if(!hRecord)
	{
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
		return 0;
	}
	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);
	sql.Format("insert into TBuyGameDeskRecordDelete(RoomID,TableNumber,DeleteTime) values(%d,%d,getdate())",pReveiveData->iRoomID,pReveiveData->byDeskIndex);
	hRecord=sqlExec(hDatabase,sql);
	if(!hRecord)
	{
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
		return 0;
	}
	sql.Format("delete from TGameCutNetRecord where TableNumber=%d and RoomID=%d",pReveiveData->byDeskIndex, pReveiveData->iRoomID); // ���������������
	hRecord=sqlExec(hDatabase,sql);
	if(!hRecord)
	{
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
		return 0;
	}
	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);
	/*DL_GR_O_BuyDeskOutResult out_data;
	out_data.iRoomID=pReveiveData->iRoomID;
	out_data.byDeskIndex=pReveiveData->byDeskIndex;
	out_data.iUserID=pReveiveData->iUserID;
	m_pRusultService->OnDataBaseResultEvent(&out_data.ResultHead,DTK_GR_CLEARBUYDESK,0, sizeof(out_data), pSourceData->uIndex, pSourceData->dwHandleID);*/
	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);
}

int CGameDataBaseHandle::OnCutNet(DataBaseLineHead *pSourceData)
{
	DL_GR_I_CutNetRecord *pReveiveData = (DL_GR_I_CutNetRecord *)pSourceData;
	if(!pReveiveData)
	{
		return 0;
	}
	HANDLE hDatabase=m_pDataBaseManage->hDBNative;
	CString sql="";
	if(pReveiveData->bClear)
	{
		sql.Format("delete from TGameCutNetRecord where UserID=%d and RoomID=%d",pReveiveData->iUserID,pReveiveData->iRoomID);
	}
	else
	{
		sql.Format("insert into TGameCutNetRecord(UserID,RoomID,TableNumber) values(%d,%d,%d)",pReveiveData->iUserID,pReveiveData->iRoomID,pReveiveData->byDeskIndex);
	}
	HANDLE hRecord=sqlExec(hDatabase,sql);
	if(!hRecord)
	{
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
		return 0;
	}
	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);
}

int CGameDataBaseHandle::OnDeductRoomCard(DataBaseLineHead *pSourceData)
{
	DL_GR_I_BuyDeskOut *pReveiveData = (DL_GR_I_BuyDeskOut *)pSourceData;
	
	HANDLE hDatabase = m_pDataBaseManage->hDBNative;
	CString sql="";
	int Jewels=0;
	sql.Format("select NeedJewels from TVIPDeskToCount where BuyGameCount=%d", pReveiveData->iVipGameCount);
	HANDLE hRecord = sqlExec(hDatabase,sql,true);
	if(!hRecord)
	{
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
		return 0;
	}
	sqlGetValue(hDatabase, hRecord, "NeedJewels", Jewels);
	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);

	sql.Format("update Web_Users set Jewels=Jewels-%d where UserID=%d", Jewels,pReveiveData->iDeskMaster);
	hRecord = sqlExec(hDatabase,sql);
	if(!hRecord)
	{
		sqlCloseRecord(hDatabase,hRecord);
		sqlSPClose(hDatabase,hRecord);
		return 0;
	}
	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);
}