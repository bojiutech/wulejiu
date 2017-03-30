#include "Stdafx.h"
#include "BankMessage.h"
#include "PropDatabaseMessage.h"
#include "GameDataBaseHandle.h"

//数据库处理接口
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
	case DTK_GR_BANK_SET_USER_REBATE://玩家修改返利数据
	case DTK_GR_BANK_SET_USER_REBATE_INGAME:
		{
			return OnBankTransferRebate(pSourceData, pSourceData->uHandleKind);
		}
	case DTK_GR_DEMAND_MONEY:								//打开钱柜
	case DTK_GR_DEMAND_MONEY_IN_GAME:						//从游戏界面中打开钱柜
		{
			return OnOpenWallet(pSourceData, pSourceData->uHandleKind);				
		}
	case DTK_GR_CHECKOUT_MONEY:								//取出金币
	case DTK_GR_CHECKOUT_MONEY_INGAME:						//从游戏界面中取出金币
		{	
			return OnCheckOutMoney(pSourceData, pSourceData->uHandleKind);
		}
	case DTK_GR_CHECKIN_MONEY:								//存入金币
	case DTK_GR_CHECKIN_MONEY_INGAME:						//从游戏界面中存入金币
		{
			return OnCheckInMoney(pSourceData, pSourceData->uHandleKind);
		}
	case DTK_GR_TRANSFER_MONEY:								//转帐
	case DTK_GR_TRANSFER_MONEY_INGAME:						//游戏中转帐
		{
			return OnTransferMoney(pSourceData, pSourceData->uHandleKind);
		}
	case DTK_GR_CHANGE_PASSWD:								///< 修改密码
	case DTK_GR_CHANGE_PASSWD_INGAME:						///< 修改密码
		{
			return OnChangePasswd(pSourceData, pSourceData->uHandleKind);
		}
	case DTK_GR_TRANSFER_RECORD:							///< 转帐记录
	case DTK_GR_TRANSFER_RECORD_INGAME:						///< 转帐记录
		{
			return OnTransferRecord(pSourceData, pSourceData->uHandleKind);
		}

	case DTK_GR_UPDATE_INSTANT_MONEY:						//即时更新金币积分
		{
			return OnModifyUserMoney(pSourceData);
		}
	case DTK_GR_UPDATE_CHARM:								//更新魅力值
		{
			return OnUpdateUserCharm(pSourceData);
		}
		//加上ZXJ 的方案
	case DTK_GR_CLEAR_ONLINE_FLAG:	//2009-4-17添加
		{
			return OnClearNetCutUserOnlineFlag(pSourceData);
		}
	case DTK_GR_CONTEST_RETURN_FEE://退回报名费
		{
			return OnContestReturnFee(pSourceData);
		}
	case DTK_GR_USER_RECOME:	//用户断线重连后写W记录 2009-4-28
		{
			return OnReWriteWLoginRecord(pSourceData);
		}
	case DTK_GR_USER_CONTEST_LEFT:
		{
			return OnContestUserLeft(pSourceData);
		}

		//case DTK_GR_GET_BUY_ITEM_DATA:							//获取玩家可购买道俱列表
		//	{
		//		return OnGetBuyItemData(pSourceData);			
		//	}
		//case DTK_GR_BUY_ITEM:										//玩家购买道俱
		//	{
		//		return OnBuyItem(pSourceData);
		//	}
		//case DTK_GR_READ_USER_HOLD_ITEM:						//更新玩家持有道俱
		//	{
		//		return OnGetUserHoldPlatformItemCount(pSourceData);
		//	}
	case DTK_GR_PROP_USE:// DTK_GR_USER_USE_ONE_ITEM:							//玩家使用道俱
		{
			return OnUserUseOneProp(pSourceData);
		}
	case DTK_GPR_PROP_SMALL_BRD:
		{
			return OnUseSmallBoardcast(pSourceData);
		}

	case DTK_GR_LOGON_BY_ID:								//通过用户 ID 登陆
		{
			return OnRoomLogon(pSourceData);
		}
	case DTK_GR_USER_LEFT:									//用户离开房间
		{
			return OnUserLeft(pSourceData);
		}
	case DTK_GR_UPDATE_INFO:								//更新服务器信息
		{
			return OnUpdateServerInfo(pSourceData);
		}
	case DTK_GR_RECORD_GAME:		//记录游戏数据
		{
			return OnRecordGameInfo(pSourceData);
		}
	case DTK_GR_CHECK_CONNECT:		//检测数据库连接
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
	case DTK_GR_CALL_GM:			//呼叫GM
		{
			return OnCallGM(pSourceData);
		}
	case DTK_GR_GAME_POWER:			//管理权限修改
		{
			return OnGamePower(pSourceData);
		}
	case DTK_GR_GM_KICK_USER_RECORD:			//管理员踢人行为纪录
		{
			return OnGMKickUserRecord(pSourceData);
		}
	case DTK_GR_GM_WARNING_USER_RECORD:	//管理员发警告消息行为纪录
		{
			return OnGMWarningUserRecord(pSourceData);
		}
	case DTK_GR_SENDMONEY_TIMES:
		{
			return OnSendUserMoenyByTimes(pSourceData);
		}
	case DTK_GR_UNREGISTER_ONLINE:	//清理用户断线
		{
			return OnUnRegisterOnLine(pSourceData);
		}
	//wushuqun 2009.5.22
	//修改禁止登录问题，修改插入TWLoginRecord 记录时机
	case DTK_GR_WRITE_WLOGINRECORD:
		{
			return OnWriteTWLoginRecord(pSourceData);
		}
	//wushuqun 2009.6.6
	//即时封桌功能
	case DTR_GR_ALONEDESK_INTIME:
		{
			return OnAloneDeskInTime(pSourceData);
		}
	case DTK_GR_ROOM_PW_CHANGE:
		{
			return OnRoomPWChangeRecord(pSourceData);
		}
		//case DTK_GR_USER_OPT://玩家进行好友,坏人操作
		//	{
		//		return UserOpetation(pSourceData);
		//	}
    case DTK_GR_GETNICKNAME_ONID: // PengJiLin, 2010-8-23, 根据用户ID获取昵称
	case DTK_GR_GETNICKNAME_ONID_INGAME:
        {
            return OnGetNickNameOnID(pSourceData);
        }
    case DTK_GR_USE_KICK_PROP:      // PengJiLin, 2010-9-10, 使用踢人卡道具
        {
            return OnUseKickProp(pSourceData, TRUE);
        }
    case DTK_GR_USE_ANTI_KICK_PROP: // PengJiLin, 2010-9-10, 使用防踢卡道具
        {
            return OnUseKickProp(pSourceData, FALSE);
        }
    case DTK_GR_USER_NEW_KICK_USER_PROP:    // PengJiLin, 2010-9-13, 使用踢人卡踢人功能
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



//检测数据库连接
UINT CGameDataBaseHandle::OnCheckDataConnect(DataBaseLineHead * pSourceData)
{
	try 
	{ 
		//检测连接
		m_pDataBaseManage->CheckSQLConnect();

		//处理结果
		DataBaseResultLine ResultHead;
		m_pRusultService->OnDataBaseResultEvent(&ResultHead,DTK_GR_CHECK_CONNECT,0,sizeof(ResultHead),0,0);
	} 
	catch (...) {TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);}

	return 0;
}

//记录游戏信息
UINT CGameDataBaseHandle::OnRecordGameInfo(DataBaseLineHead * pSourceData)
{
	//效验数据
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_GameRecord)) throw DTR_GR_ERROR_UNKNOW;
	DL_GR_I_GameRecord * pGameRecord=(DL_GR_I_GameRecord *)pSourceData;

	// duanxiaohui 20111103 体验场(免费场)不进行游戏记录
	if (m_pInitInfo->dwRoomRule & GRR_EXPERCISE_ROOM || m_pInitInfo->dwRoomRule & GRR_CONTEST || m_pInitInfo->dwRoomRule & GRR_TIMINGCONTEST)
	{
		return 0;
	}
		long int dwNowTime=(long int)time(NULL);
		//更新数据库
		HANDLE hDatabase=m_pDataBaseManage->hDBNative;
		//wushuqun 2009.6.5
		//改变该存储过程为有返回值
		HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_RecordGameInfo_new",true);

		if(hRecord<(HANDLE)0x1000)
			return 0;

		//更新数据库

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
		//检查混战场活动时间是否有效
		int ret=sqlSPGetReturnValue(hDatabase,hRecord);
	
		//为0时不用处理，不存在该混战房间
		// =1 时,表示该混战房间已经不在活动时间内了
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

//2009-4-17添加，用于清除断线用户在线标志
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

//2009-4-28 添加 zxj
UINT CGameDataBaseHandle::OnReWriteWLoginRecord(DataBaseLineHead * pSourceData)
{
	WriteStr("用户断线重连，写W记录");
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


//更新服务器信息
UINT CGameDataBaseHandle::OnUpdateServerInfo(DataBaseLineHead * pSourceData)
{


	//效验数据
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
	//效验数据
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_LogonByIDStruct)) throw DTR_GR_ERROR_UNKNOW;
	DL_GR_I_LogonByIDStruct * pLogonInfo=(DL_GR_I_LogonByIDStruct *)pSourceData;

	//初始化登陆结果
	DL_GR_O_LogonResult UserLogonResult;
	memset(&UserLogonResult,0,sizeof(UserLogonResult));

	//定义变量
	BYTE bRegisterLogon=FALSE;

	int iHandleResult=DTR_GR_LOGON_SUCCESS;

	//IP 效验（每个房间的IP限制）

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
			//如果用户已经在其它房间，返回所在的房间ID
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
		
		//不在混战场活动时间内
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


	//注册登陆信息
	DL_GR_I_RegisterLogon RegUserOnLine;
	DL_GR_O_RegisterLogon RegUserResult;
	memset(&RegUserOnLine,0,sizeof(RegUserOnLine));
	memset(&RegUserResult,0,sizeof(RegUserResult));
	lstrcpy(RegUserOnLine.szAccessIP,szIP);
	RegUserOnLine.dwUserID=pLogonInfo->LogonInfo.dwUserID;
	UserLogonResult.bRegOnline=TRUE;


	//登陆成功
	long int dwGamePower=0,dwMasterPower=0,uMaster=0,uMemberPower=0;
    __int64 i64Money=0;
	long int dwFascination = 0L;//
	UINT uMatch=0;
	UserLogonResult.pUserInfoStruct.bDeskNO=255;///游戏桌号
	UserLogonResult.pUserInfoStruct.bDeskStation=255;//桌子位置
	UserLogonResult.pUserInfoStruct.bUserState=USER_LOOK_STATE;//用户状态
	UserLogonResult.pUserInfoStruct.dwUserIP=pLogonInfo->uAccessIP;//登录IP地址
	UserLogonResult.pUserInfoStruct.dwUserID=pLogonInfo->LogonInfo.dwUserID;//ID 号码

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
	///////////Kylin 20090116 VIP进房间功能
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

	////邮游钻石身份标识 add by huangYuanSong 09.07.14
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
	//根据VIP时间来确定是否是会员
	CString stime;
	stime.Format("%d",CTime::GetCurrentTime());
	int curtime=atoi(stime);
	if(UserLogonResult.pUserInfoStruct.iVipTime>curtime)
	{
		uMemberPower=1;
		UserLogonResult.pUserInfoStruct.bMember=uMemberPower;
	}

	//是否会员房间
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
	
	//比赛房间
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
	
	//登陆房间发现金币不足，自动赠送,限金币场 2013-02-02 wangzhitu	
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

	////得到其他新加的用户信息  yjj 090319
	sqlGetValue(hDatabase,hRecord,"OccuPation",UserLogonResult.pUserInfoStruct.szOccupation,sizeof(UserLogonResult.pUserInfoStruct.szOccupation));
	sqlGetValue(hDatabase,hRecord,"PhoneNum",UserLogonResult.pUserInfoStruct.szPhoneNum,sizeof(UserLogonResult.pUserInfoStruct.szPhoneNum));
	sqlGetValue(hDatabase,hRecord,"AdrProvince",UserLogonResult.pUserInfoStruct.szProvince,sizeof(UserLogonResult.pUserInfoStruct.szProvince));
	sqlGetValue(hDatabase,hRecord,"AdrCity",UserLogonResult.pUserInfoStruct.szCity,sizeof(UserLogonResult.pUserInfoStruct.szCity));
	sqlGetValue(hDatabase,hRecord,"AdrZone",UserLogonResult.pUserInfoStruct.szZone,sizeof(UserLogonResult.pUserInfoStruct.szZone));
	//--
	// duanxiaohui 20111111 获取个性签名
	sqlGetValue(hDatabase,hRecord,"SignDescr",UserLogonResult.pUserInfoStruct.szSignDescr,sizeof(UserLogonResult.pUserInfoStruct.szSignDescr));
	// end duanxiaohui
	//wushuqun 2009.6.6
	//登录房间时即时获取虚拟玩家人数
	sqlGetValue(hDatabase,hRecord,"VirualUser",UserLogonResult.nVirtualUser);
	//
	sqlGetValue(hDatabase,hRecord,"PresentCoinNum",UserLogonResult.nPresentCoinNum); ///< 在线时长送金币 Y.C.YAN
	///< 记录在线时间,百乐门
	CBcfFile f(CBcfFile::GetAppPath() + "Function.bcf");
	CString strValue = f.GetKeyVal("OnlineCoin","Available","0");
	if (0 == atoi(strValue))
	{
		UserLogonResult.nPresentCoinNum = 0;
	}

	//{Added by Zxd 20100629
	/// 用存储过程的返回值来给用户数据结构的isVirtual字段赋值，指示该用户是否为机器人帐号
	sqlGetValue(hDatabase,hRecord,"IsRobot", UserLogonResult.pUserInfoStruct.isVirtual);
	//Added by Zxd 20100629}

	//wushuqun 2009.6.26
	//后台设置的玩家类型,0为普通玩家,1为电视玩家
	sqlGetValue(hDatabase,hRecord,"UserType",UserLogonResult.pUserInfoStruct.userType);
	//VIP由系统自动识别，而不能由后台设定
	CString stimeTmp;
	stimeTmp.Format("%d",CTime::GetCurrentTime());
	int curtimeTmp=atoi(stime);
	if(UserLogonResult.pUserInfoStruct.iVipTime>curtimeTmp)
	{
		//vip会员

		if (UserLogonResult.pUserInfoStruct.userType == 0)
		{
			//设为普通VIP玩家
			UserLogonResult.pUserInfoStruct.userType = 2;
		}
		else if (UserLogonResult.pUserInfoStruct.userType == 1)
		{
			//设为电视VIP玩家
			UserLogonResult.pUserInfoStruct.userType = 3;
		}
		else
		{
			//若后台设置不是0,1,默认为普通玩家
			UserLogonResult.pUserInfoStruct.userType = 0;
		}
	}
	//{{ added by zxd 20100806 判断本用户是否为禁言状态，如是，则记录时间
	int nStatusByGM = 0;
	sqlGetValue(hDatabase,hRecord,"StatusByGM", nStatusByGM);
	if (nStatusByGM == 2)
	{
		COleDateTime CurrentTime = COleDateTime::GetCurrentTime(); ///< 当前时间
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

	// 判断本用户是否为禁言状态，如是，则记录时间}}

	//获取玩家是否是银商 lxl 2010-12-10
	sqlGetValue(hDatabase,hRecord,"Trader",UserLogonResult.pUserInfoStruct.bTrader);

	sqlGetValue(hDatabase,hRecord,"ContestScore",UserLogonResult.pUserInfoStruct.i64ContestScore);

	sqlGetValue(hDatabase,hRecord,"ContestCount",UserLogonResult.pUserInfoStruct.iContestCount);
	sqlGetValue(hDatabase,hRecord,"RankNum",UserLogonResult.pUserInfoStruct.iRankNum);
	sqlGetValue(hDatabase,hRecord,"HeadUrl",UserLogonResult.pUserInfoStruct.szHeadUrl,sizeof(UserLogonResult.pUserInfoStruct.szHeadUrl));//微信图像地址
	sqlGetValue(hDatabase,hRecord,"Jewels",UserLogonResult.pUserInfoStruct.iJewels);//钻石
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
	//添加登陆金币不足赠送 2013-02-02 wangzhitu
	if (ASS_RECEIVE == UserLogonResult.strRecMoney.iResultCode)
	{
		i64Money += UserLogonResult.strRecMoney.i64Money;
	}
	UserLogonResult.pUserInfoStruct.i64Money=i64Money;	
	UserLogonResult.dwGamePower|=dwGamePower;
	UserLogonResult.dwGamePower|=m_pInitInfo->dwUserPower;//游戏附加权限，所有的人都有
	UserLogonResult.dwMasterPower|=dwMasterPower;//总的管理权限
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
	//处理登陆
	m_pRusultService->OnDataBaseResultEvent(&UserLogonResult.ResultHead,DTK_GR_LOGON_BY_ID,iHandleResult,
		sizeof(UserLogonResult),pSourceData->uIndex,pSourceData->dwHandleID);
	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase, hRecord);

	return 0;
}

// PengJiLin, 2010-8-23, 根据用户ID获取昵称
UINT CGameDataBaseHandle::OnGetNickNameOnID(DataBaseLineHead * pSourceData)
{
    // 效验数据
    if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_GetNickNameOnID)) throw DTR_GR_ERROR_UNKNOW;
    DL_GR_I_GetNickNameOnID * pGetNickNameOnID =(DL_GR_I_GetNickNameOnID *)pSourceData;

    // 初始化结果
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
    // 操作失败
    if(ret!=0)
    {
        iHandleResult = DTR_GR_ERROR_UNKNOW;
        if(ret==1)      // ID 不存在
            iHandleResult = DTR_GR_GETNICKNAME_NOTEXIST;
        if(ret==2)      // 昵称为空
            iHandleResult = DTR_GR_GETNICKNAME_ISNULL;

		m_pRusultService->OnDataBaseResultEvent(&GetNickNameOnIDResult.ResultHead,pSourceData->uHandleKind,
                            iHandleResult,sizeof(GetNickNameOnIDResult),pSourceData->uIndex,pSourceData->dwHandleID);
        return 0;
    }

    // 操作成功
    iHandleResult = DTR_GR_GETNICKNAME_SUCCESS;
    GetNickNameOnIDResult.iUserID = pGetNickNameOnID->stGetNickNameOnID.iUserID;    
	m_pRusultService->OnDataBaseResultEvent(&GetNickNameOnIDResult.ResultHead,pSourceData->uHandleKind,iHandleResult,
                            sizeof(GetNickNameOnIDResult),pSourceData->uIndex,pSourceData->dwHandleID);
    return 0;
}

// PengJiLin, 2010-9-10, 使用踢人卡、防踢卡道具
UINT CGameDataBaseHandle::OnUseKickProp(DataBaseLineHead * pSourceData, BOOL bIsKickUser)
{
    // 效验数据
    if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_UseKickProp)) throw DTR_GR_ERROR_UNKNOW;
    DL_GR_I_UseKickProp* pUseKickProp =(DL_GR_I_UseKickProp *)pSourceData;

    // 是踢人卡还是防踢卡
    int iHandleIDNum = DTK_GR_USE_KICK_PROP;
    if(FALSE == bIsKickUser)
    {
        iHandleIDNum = DTK_GR_USE_ANTI_KICK_PROP;
    }

    // 初始化结果
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

    //添加NameID，用于负分清零
    sqlSPAddPara(hDatabase,hRecord,"@GameNameID",0);
    char chNotUse[10] = {0};
    sqlSPAddPara(hDatabase,hRecord,"@GameTable",chNotUse,sizeof(chNotUse));
    //是否负分清零
    sqlSPAddPara(hDatabase,hRecord,"@IsClearMinus", 0);
    //是否大小喇叭 // PengJiLin, 2010-9-10, 置1，会直接返回不做其他处理
    sqlSPAddPara(hDatabase,hRecord,"@IsBoard",1);
    //双倍积分变化

    sqlSPAddPara(hDatabase,hRecord,"@DoubleTime",0);
    //护身符变化
    sqlSPAddPara(hDatabase,hRecord,"@ProtectTime",0);
    //魅力值变化
    sqlSPAddPara(hDatabase,hRecord,"@FasciChange",0);
    sqlSPExec(hDatabase,hRecord,false);

    int ret=sqlSPGetReturnValue(hDatabase,hRecord);
    sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);
    int iHandleResult = DTR_GR_USE_KICKPROP_SUCCESS;

    // 操作失败，没有道具了
    if(0 != ret)
    {
        iHandleResult = DTR_GR_USE_KICKPROP_NULL;
        m_pRusultService->OnDataBaseResultEvent(&UseKickProp.ResultHead, iHandleIDNum, 
                                                iHandleResult, sizeof(DL_GR_O_UseKickProp), 
                                                pSourceData->uIndex, pSourceData->dwHandleID);
        return 0;
    }

    // 操作成功，处理数值
    hRecord=sqlSPSetNameEx(hDatabase,"SP_UseKickProp",true);
    if(hRecord<(HANDLE)0x1000)
        return 0;
    
    sqlSPAddPara(hDatabase,hRecord,"@UserID", pUseKickProp->dwUserID);
    sqlSPAddPara(hDatabase,hRecord,"@PropID", pUseKickProp->iPropID);
    sqlSPAddPara(hDatabase,hRecord,"@bIsKick", bIsKickUser?1:0);  // 0 = 防踢卡, 1 = 踢人卡

    sqlSPExec(hDatabase,hRecord,true);

    ret=sqlSPGetReturnValue(hDatabase,hRecord);
    sqlGetValue(hDatabase,hRecord,"TotalTime", UseKickProp.iTotalTime);
    sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);
    iHandleResult = DTR_GR_USE_KICKPROP_SET_SUCCESS;

    // 操作失败
    if(0 != ret)
    {
        iHandleResult = DTR_GR_USE_KICKPROP_SET_ERROR;
    }

    m_pRusultService->OnDataBaseResultEvent(&UseKickProp.ResultHead, iHandleIDNum, 
                                            iHandleResult, sizeof(DL_GR_O_UseKickProp), 
                                            pSourceData->uIndex, pSourceData->dwHandleID);
    return 0;
}

// PengJiLin, 2010-9-13, 使用踢人卡踢人功能
UINT CGameDataBaseHandle::OnNewKickUserProp(DataBaseLineHead * pSourceData)
{
    // 效验数据
    if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_NewKickUserProp)) throw DTR_GR_ERROR_UNKNOW;
    DL_GR_I_NewKickUserProp* pUseKickProp =(DL_GR_I_NewKickUserProp *)pSourceData;

    // 初始化结果
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
        iHandleResult = DTR_GR_NEW_KICKUSER_NOTIME; // 自己的道具已过期，或者没有道具
        break;
    case 2:
        iHandleResult = DTR_GR_NEW_KICKUSER_HAD_ANTI; // 对方有防踢卡时间
        break;
    case 3:
        iHandleResult = DTR_GR_NEW_KICKUSER_HAD_ANTI; // 对方有VIP时间
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

//效验数据
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

//vip时间检测
//UINT CGameDataBaseHandle::OnVipTimerCheck(DataBaseLineHead *pSourceData)
//{//这个函数可以不要了吧
//	return TRUE;
//
//}

//取款
UINT CGameDataBaseHandle::OnCheckOutMoney(DataBaseLineHead *pSourceData, UINT uCode)
{
	//效验数据
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_CheckOutMoneyWithPwd_t)) throw DTR_GR_ERROR_UNKNOW;//////接受的结构和定义的是否一致
	DL_GR_I_CheckOutMoneyWithPwd_t * pCheckOutMoney=(DL_GR_I_CheckOutMoneyWithPwd_t * )pSourceData;
	DL_GR_O_CheckOutMoney pCheckOutMoneyResult;///结果
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
		sqlSPAddPara(hDatabase,hRecord,"@IsSave",0);	//0-取款,1-存款
		sqlSPAddPara(hDatabase,hRecord,"@MD5Pass",pCheckOutMoney->szMD5Pass, sizeof(pCheckOutMoney->szMD5Pass));//密码

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
		pCheckOutMoneyResult.i64MoneyInBank=i64Bank /*- i64CheckInMoney*/;//取消i64CheckInMoney，服务器返回的已经是操作后的结果 [2016/6/1/15 lwz]
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

//存款
UINT CGameDataBaseHandle::OnCheckInMoney(DataBaseLineHead *pSourceData, UINT uCode)
{
	//效验数据
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_CheckOutMoney)) throw DTR_GR_ERROR_UNKNOW;//////接受的结构和定义的是否一致
	DL_GR_I_CheckOutMoney * pCheckInMoney=(DL_GR_I_CheckOutMoney * )pSourceData;
	DL_GR_O_CheckOutMoney pCheckInMoneyResult;///结果
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
		sqlSPAddPara(hDatabase,hRecord,"@IsSave",1);	//0-取款,1-存款
		sqlSPAddPara(hDatabase,hRecord,"@MD5Pass", "", sizeof(""));//密码

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
		pCheckInMoneyResult.i64MoneyInBank=i64Bank/* + i64CheckInMoney*/;// 取消i64CheckInMoney，服务器返回的已经是操作后的结果 [2016/6/1/15 lwz]
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
//转帐记录
UINT CGameDataBaseHandle::OnTransferRecord(DataBaseLineHead *pSourceData, UINT uCode)
{
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_TransferRecord_t)) throw DTR_GR_ERROR_UNKNOW;//////接受的结构和定义的是否一致
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
		/// 每读取一条记录，就返回一次，直到读取结束，smalldatetime类型的数据在客户端解析
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
//修改密码
UINT CGameDataBaseHandle::OnChangePasswd(DataBaseLineHead *pSourceData, UINT uCode)
{
	//效验数据
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
		sqlSPAddPara(hDatabase,hRecord,"@MD5PassOld",pChangePasswd->stChangePasswd.szMD5PassOld, sizeof(pChangePasswd->stChangePasswd.szMD5PassOld));//旧密码
		sqlSPAddPara(hDatabase,hRecord,"@MD5PassNew",pChangePasswd->stChangePasswd.szMD5PassNew, sizeof(pChangePasswd->stChangePasswd.szMD5PassNew));//新密码
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
		// 只有成功和失败两种结果
		m_pRusultService->OnDataBaseResultEvent(&changePasswdResult.ResultHead,
			uCode, uResult,
			sizeof(changePasswdResult),
			pSourceData->uIndex,pSourceData->dwHandleID);
	}

	return 0;
}
//转帐
UINT CGameDataBaseHandle::OnTransferMoney(DataBaseLineHead *pSourceData, UINT uCode)
{
	//效验数据
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_TransferMoney))
	{
		return 0;
	}
	DL_GR_I_TransferMoney * pTransferMoney=(DL_GR_I_TransferMoney * )pSourceData;
	DL_GR_O_TransferMoney stTransferMoneyResult;///结果
	memset(&stTransferMoneyResult,0,sizeof(stTransferMoneyResult));
	if(pTransferMoney->stTransfer.i64Money <= 0) return 0; 

    // PengJiLin, 2010-8-23, 增加银行“全转”功能

    // PengJiLin, 2011-7-13, 32位数据转到64位数据
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
		sqlSPAddPara(hDatabase,hRecord,"@DestNickName",pTransferMoney->stTransfer.szDestNickName, sizeof(pTransferMoney->stTransfer.szDestNickName));//密码
		//sqlSPAddPara(hDatabase,hRecord,"@DestUser",pTransferMoney->stTransfer.szDestName,sizeof(pTransferMoney->stTransfer.szDestName));
		if(0 == pTransferMoney->stTransfer.uHandleCode)     // PengJiLin, 2010-8-23, 全转功能
           sqlSPAddPara_i64(hDatabase,hRecord,"@TranMoney",pTransferMoney->stTransfer.i64Money);
		sqlSPAddPara(hDatabase,hRecord,"@TranTax",pTransferMoney->stTransfer.bTranTax);
		sqlSPAddPara(hDatabase,hRecord,"@MD5Pass",pTransferMoney->stTransfer.szMD5Pass, sizeof(pTransferMoney->stTransfer.szMD5Pass));//密码

		sqlSPExec(hDatabase,hRecord,true);
		int ret=sqlSPGetReturnValue(hDatabase,hRecord);
		UINT uResult = DTR_GR_TRANSFER_MONEY_SUC;
		switch(ret)
		{
		case 0: ///<转帐成功
			{
			sqlGetValue(hDatabase,hRecord,"DestUserID",pTransferMoney->stTransfer.destUserID);
			sqlGetValue(hDatabase,hRecord,"TranMoney",pTransferMoney->stTransfer.i64Money);
			sqlGetValue(hDatabase,hRecord,"ActualTransfer",pTransferMoney->stTransfer.i64ActualTransfer);
			break;
			}
		case 1:	///<密码错误
			{
			uResult = DTR_GR_OPEN_WALLET_ERROR_PSW;
			break;
			}
		case 2: ///<银行中钱少于多少不能转帐
			{
			uResult = DTR_GR_TRANSFER_TOTAL_NOT_ENOUGH;
			sqlGetValue(hDatabase,hRecord,"LessAllMoney", pTransferMoney->stTransfer.i64ActualTransfer);
			break;
			}
		case 3: ///<单笔转帐必须大于多少
			uResult = DTR_GR_TRANSFER_TOO_LESS;
			sqlGetValue(hDatabase,hRecord,"LessMoney", pTransferMoney->stTransfer.i64ActualTransfer);
			break;
		case 4: ///<单笔转帐是某数的整数倍
			uResult = DTR_GR_TRANSFER_MULTIPLE;
			sqlGetValue(hDatabase,hRecord,"Multiple", u32Data);
            pTransferMoney->stTransfer.i64ActualTransfer = u32Data;
			break;
		case 5: ///<银行里只有多少钱，本次想要转多少钱，不够转
			uResult = DTR_GR_TRANSFER_NO_ENOUGH_MONEY;
			sqlGetValue(hDatabase,hRecord,"TransMoney", pTransferMoney->stTransfer.i64Money);
			sqlGetValue(hDatabase,hRecord,"BankMoney", pTransferMoney->stTransfer.i64ActualTransfer);
			break;
		case 6: ///<目标帐户不存在
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


//提取或者存储返利
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
		if (iRet == 1)//成功
		{
			cmd.bResult = true;		
		}
		else if (iRet == -1)//失败
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

//更新转账返利数据
UINT CGameDataBaseHandle::OnUpdateRebate(DataBaseLineHead * pSourceData)
{
	//效验数据
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_RebateUpDateStruct)) return 0;

	HANDLE hDatabase=m_pDataBaseManage->hDBLogon;
	HANDLE hRecord=sqlExec(m_pDataBaseManage->hDBLogon,TEXT("select * from Web_Config"), true);
	//结果数据定义
	DL_GR_O_RebateUpDateStruct Rebate;
	::memset(&Rebate,0,sizeof(Rebate));
	//处理数据
	int iHandleResult=0;//初始化
	//先检测数据库连接是否还在，不在就再连zht 2012-2-22
	if (0 == hRecord)
	{
		m_pDataBaseManage->SQLConnectReset();

	}
	else
	{
		sqlGetValue(hDatabase,hRecord,TEXT("Min_money"),Rebate.iMin_money);
		sqlGetValue(hDatabase,hRecord,TEXT("VIP_Rate"),Rebate.iVIP_Rate);

		CString sdp;
		sdp.Format("sdp_ 转账 房间 返利数据更新 数据库读取成功 最小转换金额=%I64d,vip返利率=%f",Rebate.iMin_money,Rebate.iVIP_Rate);
		OutputDebugString(sdp);

		iHandleResult=1;//成功
	}
	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);//关闭句柄，防止内存泄露


	m_pRusultService->OnDataBaseResultEvent(&Rebate.ResultHead,DTK_GR_BANK_UPDATE_REBATE,iHandleResult,
		sizeof(Rebate),pSourceData->uIndex,pSourceData->dwHandleID);

	return 0;
}

//更新玩家返利数据
UINT CGameDataBaseHandle::OnUpdateUserRebate(DataBaseLineHead * pSourceData, UINT uCode)
{
	//效验数据
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_UserRebateUpDateStruct)) 
		return 0;
	DL_GR_I_UserRebateUpDateStruct * pCmd=(DL_GR_I_UserRebateUpDateStruct *)pSourceData;
	HANDLE hDatabase=m_pDataBaseManage->hDBLogon;
	CString sql;
	sql.Format("select * from Web_RebateInfo where UserID='%d'", pCmd->iUserID);
	HANDLE hRecord=sqlExec(m_pDataBaseManage->hDBLogon,sql, true);
	//结果数据定义
	DL_GR_O_UserRebateUpDateStruct UserRebate;
	::memset(&UserRebate,0,sizeof(UserRebate));
	//处理数据
	int iHandleResult=0;//初始化
	//先检测数据库连接是否还在，不在就再连
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
		sdp.Format("sdp_ 转账 房间 查询玩家返利数据 数据库读取成功 玩家ID=%d,剩余返利数目=%d,已经取走的数目=%d",UserRebate.iUserID,UserRebate.iTx_Money,UserRebate.iTx_Smony);
		OutputDebugString(sdp);

		iHandleResult=1;//成功
	}
	sqlCloseRecord(hDatabase,hRecord);
	sqlSPClose(hDatabase,hRecord);//关闭句柄，防止内存泄露


	m_pRusultService->OnDataBaseResultEvent(&UserRebate.ResultHead,uCode,iHandleResult,
		sizeof(UserRebate),pSourceData->uIndex,pSourceData->dwHandleID);

	return 0;
}

//打开钱包
UINT CGameDataBaseHandle::OnOpenWallet(DataBaseLineHead *pSourceData, UINT uCode)
{
	//效验数据

	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_UnRegisterUser)) throw DTR_GR_OPEN_WALLET_ERROR;//////接受的结构和定义的是否一致
	DL_GR_I_UnRegisterUser * pOpenWallet=(DL_GR_I_UnRegisterUser * )pSourceData;
	DL_GR_O_OpenWalletResult OpenWallet;///打开结果
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

		//CHAR	szMD5Pass[50];						//加密密码
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
	//效验数据
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_Warn_User_Record)) throw DTR_GR_ERROR_UNKNOW;//////接受的结构和定义的是否一致
	DL_GR_I_Warn_User_Record * pWarningUser=(DL_GR_I_Warn_User_Record *)pSourceData;//结构赋值

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


//管理员踢人动作纪录
UINT CGameDataBaseHandle::OnGMKickUserRecord(DataBaseLineHead * pSourceData)
{
	//效验数据
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_Kick_User_Record))
		throw DTR_GR_ERROR_UNKNOW;//////接受的结构和定义的是否一致
	DL_GR_I_Kick_User_Record * pKickUser=(DL_GR_I_Kick_User_Record *)pSourceData;//结构赋值

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
//管理权限修改
UINT CGameDataBaseHandle::OnGamePower(DataBaseLineHead * pSourceData)
{
	//效验数据
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_PowerSet)) throw DTR_GR_ERROR_UNKNOW;//////接受的结构和定义的是否一致
	DL_GR_I_PowerSet * pPowerSet=(DL_GR_I_PowerSet *)pSourceData;//结构赋值


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
//呼叫GM处理
UINT CGameDataBaseHandle::OnCallGM(DataBaseLineHead * pSourceData)
{
	//效验数据
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_CallGM)) throw DTR_GR_ERROR_UNKNOW;//////接受的结构和定义的是否一致
	DL_GR_I_CallGM * pCallGM=(DL_GR_I_CallGM *)pSourceData;//结构赋值

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
/// 记录修改房间密码
///
/// @param pSourceData
///
/// @ return 0成功返回0

UINT CGameDataBaseHandle::OnRoomPWChangeRecord(DataBaseLineHead * pSourceData)
{
	///< 效验数据
	if (pSourceData->DataLineHead.uSize != sizeof(DL_GR_RoomPWChange))
		throw DTR_GR_ERROR_UNKNOW;
	///< 结构赋值
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
	//效验数据
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

		//修改分数

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
		///< 记录在线时间,百乐门
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
///一次性更新同桌所有用户信息
UINT CGameDataBaseHandle::OnUpdateAllUserResult(DataBaseLineHead * pSourceData)
{
	
	//效验数据
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_AllUserData_t)) throw DTR_GR_ERROR_UNKNOW;
	DL_GR_I_AllUserData_t * pUserResult=(DL_GR_I_AllUserData_t *)pSourceData;

	//需要自动赠送玩家个数 2013-01-28 wangzhitu
	int iAutoNum = 0;	

	// duanxiaohui 20111103 体验场(免费场)不进行金币、积分游戏记录
	if (m_pInitInfo->dwRoomRule & GRR_EXPERCISE_ROOM)
	{
		DebugPrintf("SP_UserInfoUpdateAll执行失败返回值体验场(免费场)不进行金币 m_pInitInfo->dwRoomRule=%d",m_pInitInfo->dwRoomRule);
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
	//重连
	if (!sqlExec(hDatabase,TEXT("select top 1 * from TGameServerInfo")))
	{
		m_pDataBaseManage->SQLConnectReset();
		
		DebugPrintf("SP_UserInfoUpdateAll 重连");
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
	//zht2012-03-31 人数过大时，拆分一下
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
			//发现有玩家需要自动赠送 2013-01-28 wangzhitu
			if (pUserInfo->bISAutoSendMoney)
			{
				iAutoNum++;
			}
		    
			str.Format("wzd iAutoNum=%d",iAutoNum);
			OutputDebugString(str);
			strParam += szTmp;
			
		++pUserInfo;	///< 指针前移
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
		//混战场房间
		char szGameTableTmp[31];
		ZeroMemory(szGameTableTmp, sizeof(szGameTableTmp));
		if (m_pInitInfo->uBattleRoomID > 0)
		{
			//是混战房间
			memcpy(szGameTableTmp,m_pInitInfo->szBattleGameTable,sizeof(szGameTableTmp));
		}
		else
		{
			//普通房间
			memcpy(szGameTableTmp,m_pInitInfo->szGameTable,sizeof(szGameTableTmp));
		}
		bRet = sqlSPAddPara(hDatabase,hRecord,TEXT("@GameTable"),szGameTableTmp,sizeof(szGameTableTmp));
		bRet = sqlSPAddPara(hDatabase,hRecord,TEXT("@PlayTimeCount"),pUserResult->nPlayTime);
		bRet = sqlSPAddPara(hDatabase,hRecord,TEXT("@IsExperciseRoom"),(m_pInitInfo->dwRoomRule & GRR_EXPERCISE_ROOM)?1:0);
		bRet = sqlSPAddPara(hDatabase,hRecord,TEXT("@IsMoneyGame"),(m_pInitInfo->uComType==TY_MONEY_GAME)?1:0);
		bRet = sqlSPAddPara(hDatabase, hRecord, TEXT("@Param"), TempStrParam.GetBuffer(), sizeof(TCHAR) * TempStrParam.GetLength());
	
	
		// PengJiLin, 2011-4-14, 增加房间ID
		bRet = sqlSPAddPara(hDatabase,hRecord,TEXT("@RoomID"),m_pInitInfo->uRoomID);


		int IsExperciseRoom = (m_pInitInfo->dwRoomRule & GRR_EXPERCISE_ROOM)?1:0;
		CString szSQL;

		szSQL.Format(TEXT("nUserCount = %d EXEC SP_UserInfoUpdateAll @UserCount=%d,@NameID=%d,@GameTable='%s',@PlayTimeCount=%d,@IsExperciseRoom=%d,@IsMoneyGame=%d,@Param='%s',@RoomID=%d"),nUserCount,tempUserCount,m_pKernelInfo->uNameID,szGameTableTmp,pUserResult->nPlayTime,IsExperciseRoom
			,(m_pInitInfo->uComType==TY_MONEY_GAME)?1:0,TempStrParam.GetBuffer(),m_pInitInfo->uRoomID);

		bRet = sqlSPExec(hDatabase,hRecord, true);



		// PengJiLin, 2011-4-14, 是否有在线送金币功能
		sqlGetValue(hDatabase,hRecord,"SendMoneyFlag",bHadSendMoney);
		int ret=sqlSPGetReturnValue(hDatabase,hRecord);
		if (ret != 0 || hRecord == NULL || bRet == FALSE)
		{
			DebugPrintf("SP_UserInfoUpdateAll执行失败返回值%d hRecord=%d bRet=%d",ret,hRecord,bRet);
			DebugPrintf("SP_UserInfoUpdateAll参数%s m_ErrorSQLCount=%d i=%d",szSQL.GetBuffer(),m_ErrorSQLCount,i);


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

			DebugPrintf("SP_UserInfoUpdateAll参数%s m_ErrorSQLCount=%d i=%d 超过三次",szSQL.GetBuffer(),m_ErrorSQLCount,i);


		}

		m_ErrorSQLCount = 0;
		sqlCloseRecord(hDatabase,hRecord);

		sqlSPClose(hDatabase, hRecord);

	}

    // PengJiLin, 2011-4-15, 是否有时长、局数送金币
    if(FALSE != bHadSendMoney 
		|| (m_pInitInfo->iTimeLength >= 0 && m_pInitInfo->iSendCount > 0)
		|| iAutoNum > 0) //添加自动赠送
    {
        pUserInfo = pUserResult->pUpdateUserInfo;
        DWORD dwUserID = 0;		
        for (int i=0; i<nUserCount; ++i)
        {
			//2013-01-28 wangzhitu
			bool bISAutoSend = false;

            // 数据库
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
			//需要自动赠送的玩家 2013-01-28 wangzhitu
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
				// 获赠的金币数
				sqlGetValue(hDatabase,hRecord,"SendMoney",stSendMoney.dwGetMoney);
				// 设置多少时长赠送的金币
				sqlGetValue(hDatabase,hRecord,"PlayTimesMoney",stSendMoney.dwMoneyOnTimes);
				// 设置多少局赠送的金币
				sqlGetValue(hDatabase,hRecord,"PlayCountsMoney",stSendMoney.dwMoneyOnCounts);
				// 下一次差多少时长
				sqlGetValue(hDatabase,hRecord,"PlayTimes_Dist",stSendMoney.dwTimesNeed);
				// 下一次差多少局
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

//获取赠送的金币值 //2013-01-28 wangzhitu
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

//比赛开始，做比赛初始化
UINT CGameDataBaseHandle::OnContestBegin(DataBaseLineHead * pSourceData)
{
	//效验数据
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_ContestBegin)) throw DTR_GR_ERROR_UNKNOW;
	DL_GR_I_ContestBegin* _p=(DL_GR_I_ContestBegin *)pSourceData;

	try
	{
		HANDLE hDatabase=m_pDataBaseManage->hDBNative;
		HANDLE hRecord=sqlSPSetName(hDatabase,"SP_ContestBegin", true);
		if(hRecord<(HANDLE)0x1000)
			return 0;

		//修改分数
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

//比赛结束，给获奖玩家颁发奖励
UINT CGameDataBaseHandle::OnContestGameOver(DataBaseLineHead * pSourceData)
{
	//效验数据
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_UserContestRank)) throw DTR_GR_ERROR_UNKNOW;
	try
	{
		HANDLE hDatabase=m_pDataBaseManage->hDBNative;
		HANDLE hRecord=sqlSPSetName(hDatabase,"SP_ContestFinish",true);
		if(hRecord<(HANDLE)0x1000)
			return 0;

		//修改分数
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

///更新用户比赛信息
UINT CGameDataBaseHandle::OnUpdateContestInfo(DataBaseLineHead * pSourceData)
{
	//效验数据
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_UserContestData)) throw DTR_GR_ERROR_UNKNOW;
	DL_GR_I_UserContestData* _p=(DL_GR_I_UserContestData *)pSourceData;

	try
	{
		HANDLE hDatabase=m_pDataBaseManage->hDBNative;
		HANDLE hRecord=sqlSPSetName(hDatabase,"SP_ContestUpdateRecord");
		if(hRecord<(HANDLE)0x1000)
			return 0;

		//修改分数
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

///得到用户比赛信息
UINT CGameDataBaseHandle::OnGetContestInfo(DataBaseLineHead * pSourceData)
{
	//效验数据
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_UserContestRank)) throw DTR_GR_ERROR_UNKNOW;
	DL_GR_I_UserContestRank* _p = (DL_GR_I_UserContestRank*)pSourceData;
	try
	{
		HANDLE hDatabase=m_pDataBaseManage->hDBNative;
		HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_Contest_GetSomebodyRank", true);
		if(hRecord<(HANDLE)0x1000)
			return 0;

		//获取排名
		sqlSPAddPara(hDatabase,hRecord,TEXT("@ContestID"),m_pInitInfo->iContestID);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@MatchID"),m_pInitInfo->iMatchID);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@GameID"),m_pInitInfo->iGameID);
		sqlSPAddPara(hDatabase,hRecord,TEXT("@RoomID"),m_pInitInfo->uRoomID);

		sqlSPExec(hDatabase,hRecord,true);

		int iPeople = sqlSPGetReturnValue(hDatabase,hRecord);//返回值是当前剩余人数		
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
	//效验数据
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_ContestApply)) throw DTR_GR_ERROR_UNKNOW;
	DL_GR_I_ContestApply *pContestApply = (DL_GR_I_ContestApply*)pSourceData;
	
	try
	{
		//以下两个存储过程都是借用网站上面报名的存储过程

		//报名
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
		sqlGetValue(hDatabase, hRecord, ("rs"), DL_OContestApply.iApplyResult);	//执行情况
		
		int iEntryFee = 0;
		sqlGetValue(hDatabase, hRecord, "EntryFee", iEntryFee);
		//判断是否报名成功，如下两句sql放到存储过程中会出错，暂不清楚原因，先拿出来放到此处执行（用“----”标记）
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
		else if(2 == DL_OContestApply.iApplyResult)  //退赛成功，退回报名费
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
	
		//判断是否达到开赛人数，本来可以在一个存储过程中完成的，但是由于只修改机器人代码，所以只好分两次执行
		hDatabase = m_pDataBaseManage->hDBNative;
		hRecord = sqlSPSetNameEx(hDatabase, "proc_TContestPeopleNum", true);//借用网页上报名的存储过程
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
		sqlGetValue(hDatabase, hRecord, TEXT("ynum"), DL_OContestInfo._data.iContestNum);	//执行情况
		sqlGetValue(hDatabase, hRecord, TEXT("isOK"), DL_OContestApply.iContestBegin);	//执行情况
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
	//效验数据
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_UserLeft)) throw DTR_GR_ERROR_UNKNOW;
	DL_GR_I_UserLeft * pUserResult=(DL_GR_I_UserLeft *)pSourceData;

	// duanxiaohui 20111103 体验场(免费场)不进行金币、积分游戏记录
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
	//混战场房间
	char szGameTableTmp[31];
	memset(szGameTableTmp,0,sizeof(szGameTableTmp));
	if (m_pInitInfo->uBattleRoomID > 0)
	{
		//是混战房间
		memcpy(szGameTableTmp,m_pInitInfo->szBattleGameTable,sizeof(szGameTableTmp));
	}
	else
	{
		//普通房间
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


//即时更新分数和金币
UINT CGameDataBaseHandle::OnModifyUserMoney(DataBaseLineHead * pSourceData)
{
	//效验数据
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

//更新魅力值
UINT CGameDataBaseHandle::OnUpdateUserCharm(DataBaseLineHead * pSourceData)
{
	//效验数据
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

	//效验数据
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_SendMonet_By_Times)) throw DTR_GR_ERROR_UNKNOW;
	DL_GR_I_SendMonet_By_Times * pSendMoeny=(DL_GR_I_SendMonet_By_Times *)pSourceData;

	DL_GR_O_SendMonet_By_Times sSendMoenyResult;
	memset(&sSendMoenyResult,0,sizeof(sSendMoenyResult));

	//comroominfo表中关于对送金币的配置
	int iPerMoney = 0;       //一次送多少
	int iDayMoneyTimes = 0;  //一天送多少次
	//int iDayLessMoney = 0;   //金币少于多少就送
	//ComRoomInfo中金币房间的配置
	sSendMoenyResult.dwUserID = pSendMoeny->dwUserID;
	sSendMoenyResult.i64SrcGameMoney = pSendMoeny->i64SrcGameMoney;
	sSendMoenyResult.i64SrcMoneyInBank = pSendMoeny->i64SrcMoneyInBank;
	sSendMoenyResult.dwAllSendTImes = 0;
	sSendMoenyResult.dwSendFailedCause = 0;
	sSendMoenyResult.dwSendGameMoney = 0;
	sSendMoenyResult.dwSendTimes = pSendMoeny->dwGameFinishCount;

	int FinishCount = pSendMoeny->dwGameFinishCount;//获得当前是多少次游戏了

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
//玩家使用道俱
UINT CGameDataBaseHandle::OnUserUseOneProp(DataBaseLineHead *pSourceData)
{

	//////////////////////////////////////////////////////////////////////////
	//效验数据
	//2008-08-11
	if (pSourceData->DataLineHead.uSize != sizeof(DL_GR_I_USEPROP))
		throw DTR_GR_PROP_USE_ERR_PARAM_INVALID;//////接受的结构和定义的是否一致

	DL_GR_I_USEPROP	*useIProp = (DL_GR_I_USEPROP * )pSourceData;
	DL_GR_O_USEPROP useOProp;
	ZeroMemory(&useOProp,sizeof(DL_GR_O_USEPROP));
	memcpy(&useOProp.usingProp,&useIProp->usingProp,sizeof(_TAG_USINGPROP));

	HANDLE hDatabase = m_pDataBaseManage->hDBNative;
	HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_UseProp",true);
	if(hRecord<(HANDLE)0x1000)
		return 0;

	//取值属性
	int attribValue=useIProp->usingProp.nPropValueAttrib;
	//操作属性
	int attribAction=useIProp->usingProp.nPropActionAttrib;
	//以下几个操作需要计算时间
	CString stime;
	stime.Format("%d",CTime::GetCurrentTime());
	int curTime=atoi(stime);

	//影响时间的时间值，以秒为单位
	int		addSecond=attribValue & 0xFFFF;
	addSecond*=3600;//本身是以小时为单位的，所以要再乘上60*60=3600秒
	//双倍积分
	if(attribAction & 0x4)
	{
		if(curTime>useOProp.usingProp.iDoubleTime)
			//如果以前的双倍积分时间已过期，则直接在现在的开始时间上加上相应的时间
			useOProp.usingProp.iDoubleTime=curTime+addSecond;
		else
			//如果以前的双倍积分时间还未到期，则在原有的到期时间上加上相应的时间
			useOProp.usingProp.iDoubleTime+=addSecond;
	}
	//护身符道具，输了不扣分
	if(attribAction & 0x8)
	{
		if(curTime>useOProp.usingProp.iProtectTime)
			//如果以前的护身符时间已过期，则直接在现在的开始时间上加上相应的时间
			useOProp.usingProp.iProtectTime=curTime+addSecond;
		else
			//如果以前的护身符时间还未到期，则在原有的到期时间上加上相应的时间
			useOProp.usingProp.iProtectTime+=addSecond;
	}
	//魅力值变化
	int fasciChange=0;
	if(attribAction & 0x10)
	{
		//魅力值变化量
		fasciChange=(attribValue & 0xFF0000)>>16;
		//增加魅力值还是减少魅力值
		if(attribAction & 0x20)
			fasciChange=-fasciChange;
	}

	sqlSPAddPara(hDatabase,hRecord,"@UserID",useIProp->usingProp.dwUserID);
	sqlSPAddPara(hDatabase,hRecord,"@PropID",useIProp->usingProp.nPropID);
	sqlSPAddPara(hDatabase,hRecord,"@TargetID",useIProp->usingProp.dwTargetUserID);
	//添加NameID，用于负分清零
	sqlSPAddPara(hDatabase,hRecord,"@GameNameID",m_pKernelInfo->uNameID);
	sqlSPAddPara(hDatabase,hRecord,"@GameTable",m_pInitInfo->szGameTable,sizeof(m_pInitInfo->szGameTable));
	//是否负分清零
	sqlSPAddPara(hDatabase,hRecord,"@IsClearMinus", (attribAction & 0x2)?1:0);
	//是否大小喇叭 // PengJiLin, 2010-6-1, 增加 记牌器
	sqlSPAddPara(hDatabase,hRecord,"@IsBoard",(attribAction & 0x80 || attribAction & 0x100 || attribAction & 0x200)?1:0);
	//双倍积分变化
	sqlSPAddPara(hDatabase,hRecord,"@DoubleTime",useOProp.usingProp.iDoubleTime);
	//护身符变化
	sqlSPAddPara(hDatabase,hRecord,"@ProtectTime",useOProp.usingProp.iProtectTime);
	//魅力值变化
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
//20090203 Kylin 防止更新数据库后，用户登陆失败
//清理用户断线
UINT CGameDataBaseHandle::OnUnRegisterOnLine(DataBaseLineHead * pSourceData)
{
	//效验数据
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_UnRegisterUser)) throw DTR_GR_ERROR_UNKNOW;
	DL_GR_I_UnRegisterUser * pUnRegisterUser=(DL_GR_I_UnRegisterUser *)pSourceData;

	//处理数据
	try	{ UnRegisterUserLogon(pUnRegisterUser->dwUserID,false); }
	catch (...) {}

	return 0;
}

//wushuqun 2009.5.22
//修改禁止登录问题，修改插入TWLoginRecord 记录时机
//执行时机：登录房间后发送完游戏房间列表执行
UINT CGameDataBaseHandle::OnWriteTWLoginRecord(DataBaseLineHead * pSourceData)
{
	//效验数据
	if (pSourceData->DataLineHead.uSize!=sizeof(DL_GR_I_WriteWLoginRecord))
	{
		throw DTR_GR_ERROR_UNKNOW;
	}
	DL_GR_I_WriteWLoginRecord * pDlWriteWLogin = (DL_GR_I_WriteWLoginRecord *)pSourceData;
	//处理数据
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
//即时封桌功能
//数据中该房间增加虚拟人数
UINT CGameDataBaseHandle::OnAloneDeskInTime(DataBaseLineHead * pSourceData)
{
	//交验数据
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
			//SP_AloneDeskInTime 存储过程返回值说明
			// 0 :添加房间虚拟人失败
			// 1 :添加房间虚拟人成功
			if (bRet == 0)
			{
				CString str;
				str.Format("房间ID: %d,添加虚拟人数失败",pAloneDeskData->uRoomID);
				::OutputDebugString(str);
			}
			if (bRet == 1)
			{
				//添加虚拟人数成功
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

//删除登陆信息
bool CGameDataBaseHandle::UnRegisterUserLogon(long int dwUserID, bool bAllLogonInfo)
{
	if (m_pInitInfo->szLockTable[0]!=0)
	{
		//删除数据
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
		//20090203 Kylin 防止更新数据库后，用户登陆失败
		HANDLE hDatabase=m_pDataBaseManage->hDBNative;
		HANDLE hRecord=sqlSPSetNameEx(hDatabase,"SP_SetUserOnlineFlag");
		if(hRecord<(HANDLE)0x1000)
			return false;
		sqlSPAddPara(hDatabase,hRecord,"@UserID",dwUserID);
		///////////////////////////////////////////////
		///Kylin 20090201 防止账号同时登陆
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
	sql.Format("delete from TGameCutNetRecord where TableNumber=%d and RoomID=%d",pReveiveData->byDeskIndex, pReveiveData->iRoomID); // 清除短线重连数据
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