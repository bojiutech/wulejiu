/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #include "stdafx.h"
#include "ThingHandleEx.h"
#include "../server/ServerManage.h"
#include "../server/DebugPrintf.h"

//ȫ�ֶ���
//ThingHandleEx g_ThingHandle;
	
ThingHandleEx::ThingHandleEx(void)
{
}
ThingHandleEx::~ThingHandleEx(void)
{
}
/*-------------------------------------------------------------------------------------------------------------*/
//���������¼�
bool ThingHandleEx::GetGameStaton(BYTE bDeskStation, UINT uSocketID, bool bWatchUser,BYTE GameStation)
{
//	GameStationDataEx GameStationData;
	
	switch (GameStation)
	{
	case GS_WAIT_SETGAME:	//��Ϸû�п�ʼ״̬
	case GS_WAIT_ARGEE:		//�ȴ���ҿ�ʼ״̬
	case GS_WAIT_NEXT:		//�ȴ���һ����Ϸ��ʼ
		{
			GameStation_Wait_Agree TGameStation;

			TGameStation.iVersion		= MAIN_VERSION;
			TGameStation.iVersion2		= ASS_VERSION;

			TGameStation.byGameStation	= GameStation;

			TGameStation.byBeginTime	= pDesk->sGameData.m_mjRule.byBeginTime;	//��ʼ�ȴ�ʱ��
			TGameStation.byOutTime		= pDesk->sGameData.m_mjRule.byOutTime;		//����ʱ��
			TGameStation.byBlockTime	= pDesk->sGameData.m_mjRule.byBlockTime;	//˼��ʱ��

			TGameStation.bForceTuoGuan	= pDesk->sGameData.m_mjRule.bForceTuoGuan;	//ǿ���Ƿ��й�

			for(vector<long int>::iterator it = pDesk->m_vlSuperUserID.begin(); it != pDesk->m_vlSuperUserID.end(); it++)
			{
				if(pDesk->m_pUserInfo[bDeskStation]->m_UserData.dwUserID == *it)
				{
					TGameStation.bIsSuperUser = true;
					break;
				}
			}

			for (int i=0; i<PLAY_COUNT; i++)
			{
				if(NULL != pDesk->m_pUserInfo[i])
				{
					if(pDesk->m_pUserInfo[i]->m_UserData.bUserState == USER_ARGEE)  //�����Ϊͬ��״̬
					{
						TGameStation.bUserAgree[i] = true;
					}
				}
			}
			//��������
			pDesk->SendGameStationEx(bDeskStation,  bWatchUser, &TGameStation, sizeof(TGameStation));
			return true;
		}
	case GS_SEND_CARD:		//����״̬(��δ����)
		{
			GameStationData TGameStation;
			TGameStation.iVersion		= MAIN_VERSION;
			TGameStation.iVersion2		= ASS_VERSION;
			TGameStation.byGameStation	= GameStation;

			TGameStation.byBeginTime	= pDesk->sGameData.m_mjRule.byBeginTime;	//��ʼ�ȴ�ʱ��
			TGameStation.byOutTime		= pDesk->sGameData.m_mjRule.byOutTime;		//����ʱ��
			TGameStation.byBlockTime	= pDesk->sGameData.m_mjRule.byBlockTime;	//˼��ʱ��
			TGameStation.bForceTuoGuan	= pDesk->sGameData.m_mjRule.bForceTuoGuan;	//ǿ���Ƿ��й�

			for(vector<long int>::iterator it = pDesk->m_vlSuperUserID.begin(); it != pDesk->m_vlSuperUserID.end(); it++)
			{
				if(pDesk->m_pUserInfo[bDeskStation]->m_UserData.dwUserID == *it)
				{
					TGameStation.bIsSuperUser = true;
					break;
				}
			}

			TGameStation.byNtStation = pDesk->sGameData.m_byNtStation;
			memcpy(TGameStation.m_bistuoguan,pDesk->sUserData.m_bTuoGuan,sizeof(TGameStation.m_bistuoguan));
			memcpy(TGameStation.m_byArHandPai,pDesk->sUserData.m_byArHandPai,sizeof(TGameStation.m_byArHandPai));
			memcpy(TGameStation.m_iArMenPai,pDesk->sUserData.m_iArMenPai,sizeof(TGameStation.m_iArMenPai));
			//��������
			pDesk->SendGameStationEx(bDeskStation,  bWatchUser, &TGameStation, sizeof(GameStationData));
			return true;
		}
	case GS_PLAY_GAME:	//��Ϸ��״̬
		{
			GameStationDataEx TGameStation;
			TGameStation.iVersion		= MAIN_VERSION;
			TGameStation.iVersion2		= ASS_VERSION;
			TGameStation.byGameStation	= GameStation;

			TGameStation.byBeginTime	= pDesk->sGameData.m_mjRule.byBeginTime;	//��ʼ�ȴ�ʱ��
			TGameStation.byOutTime		= pDesk->sGameData.m_mjRule.byOutTime;		//����ʱ��
			TGameStation.byBlockTime	= pDesk->sGameData.m_mjRule.byBlockTime;	//˼��ʱ��
			TGameStation.bForceTuoGuan	= pDesk->sGameData.m_mjRule.bForceTuoGuan;	//ǿ���Ƿ��й�

			for(vector<long int>::iterator it = pDesk->m_vlSuperUserID.begin(); it != pDesk->m_vlSuperUserID.end(); it++)
			{
				if(pDesk->m_pUserInfo[bDeskStation]->m_UserData.dwUserID == *it)
				{
					TGameStation.bIsSuperUser = true;
					break;
				}
			}
			TGameStation.byNtStation = pDesk->sGameData.m_byNtStation;
			TGameStation.m_byNowOutStation = pDesk->sUserData.m_byNowOutStation;
			TGameStation.m_byNowThing = pDesk->sGameData.m_byThingDoing;
			TGameStation.m_byRemainTime = pDesk->sGameData.m_MjWait.byTime;
			memcpy(TGameStation.m_bistuoguan,pDesk->sUserData.m_bTuoGuan,sizeof(TGameStation.m_bistuoguan));
			memcpy(TGameStation.m_byArHandPai,pDesk->sUserData.m_byArHandPai,sizeof(TGameStation.m_byArHandPai));
			memcpy(TGameStation.m_byArHuaPai,pDesk->sUserData.m_byArHuaPai,sizeof(TGameStation.m_byArHuaPai));
			memcpy(TGameStation.m_iArMenPai,pDesk->sUserData.m_iArMenPai,sizeof(TGameStation.m_iArMenPai));
			memcpy(TGameStation.m_byArOutPai,pDesk->sUserData.m_byArOutPai,sizeof(TGameStation.m_byArOutPai));
			memcpy(TGameStation.m_UserGCPData,pDesk->sUserData.m_UserGCPData,sizeof(TGameStation.m_UserGCPData));
			memcpy(TGameStation.m_bTing,pDesk->sUserData.m_bTing,sizeof(TGameStation.m_bTing));

			TGameStation.lastOutStation = pDesk->sGameData.T_OutPai.byUser;
			TGameStation.lastOutCard = pDesk->sGameData.T_OutPai.byPs;

			//��������
			pDesk->SendGameStationEx(bDeskStation,  bWatchUser, &TGameStation, sizeof(TGameStation));

			//���ͳ�������Ϣ
			if (pDesk->sGameData.T_CPGNotify[bDeskStation].bCanAction) {
				pDesk->SendGameDataEx(bDeskStation, &pDesk->sGameData.T_CPGNotify, sizeof(pDesk->sGameData.T_CPGNotify), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
				pDesk->SendWatchDataEx(bDeskStation, &pDesk->sGameData.T_CPGNotify, sizeof(pDesk->sGameData.T_CPGNotify), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
			}
			return true;
		}
	
	}

    return true;
}
/*---------------------------------------------------------------------------------------------------------*/
///���ղ�������Ϣ
int ThingHandleEx::HandleNotifyMessage(int bDeskStation, UINT code, BYTE* pData, int uSize, bool bWatchUser)
{
	pDesk->KillTimer(TIME_CHECK_GAME_MSG);
	pDesk->SetTimer(TIME_CHECK_GAME_MSG,TIME_DEFAULT_HANDLE);//�������ó�ʱ��ʱ��

	if(bWatchUser)
	{
		return 0;
	}
	pDesk->sUserData.m_byTimeOut[bDeskStation] = 0;
    switch (code)
    {
	case ASS_GM_AGREE_GAME:		//	�յ��û�ͬ����Ϸ��Ϣ	DWJ
		{
			return	ReceiveUserAgreeGame(bDeskStation, pData, uSize,	bWatchUser);
			break;
		}
	case ASS_AUTOCARD:		//�й�		DWJ
		{	
			return ReceiveUserTuoGuan(bDeskStation, pData, uSize, bWatchUser);
			break;
		}
	case THING_OUT_PAI:		//	�û�����	DWJ
		{
			return	ReceiveUserOutCard(bDeskStation, pData, uSize, bWatchUser);
			break;
		}
	case THING_GUO_PAI:		//	��������	DWJ
		{
			return	ReceiveUserPassCheck(bDeskStation, pData, uSize,	bWatchUser);
			break;
		}
	case THING_CHI_PAI:		//	����������	DWJ
		{
			return	ReceiveUserChiCard(bDeskStation, pData, uSize, bWatchUser);
			break;
		}
	case THING_PENG_PAI:	//	�û�����	DWJ
		{
			return	ReceiveUserPengCard(bDeskStation, pData, uSize, bWatchUser);
			break;
		}
	case THING_GANG_PAI:	//	�û�����	DWJ
		{
			return	ReceiveUserGangCard(bDeskStation, pData, uSize, bWatchUser);
			break;
		}
	case THING_TING_PAI:	// �û�����		DWJ
		{
			return	ReceiveUserTingCard(bDeskStation, pData, uSize, bWatchUser);
			break;
		}
	case THING_HU_PAI:		// �û�����		DWJ
		{
			return	ReceiveUserHuCard(bDeskStation, pData, uSize, bWatchUser);
			break;
		}
	case ASS_CHANGE_PAI:	//������һ��� �ֻ����Կ���
		{
			return	ReceiveUserChangeCard(bDeskStation, pData, uSize, bWatchUser);
			break;
		}  
#ifdef MJ_CAN_SETPAI//�����ͻ���ץ�ƣ�����
    case ASS_SUPER://�����ͻ���,����������
        {
			ReceiveSuperChangePai(bDeskStation,pData, uSize, bWatchUser);
        }
        break;
#endif // MJ_CAN_SETPAI
    }
    return 0;
}



//�Ƿ񳬶��û�
bool	ThingHandleEx::IsSuperUser(BYTE bDeskStation)
{
	if (bDeskStation < 0 || bDeskStation >= PLAY_COUNT)
	{
		return false;
	}
	if (NULL == pDesk->m_pUserInfo[bDeskStation])
	{
		return false;
	}
	for(int i=0; i<pDesk->m_vlSuperUserID.size(); i++)
	{
		if (pDesk->m_pUserInfo[bDeskStation]->m_UserData.dwUserID == pDesk->m_vlSuperUserID.at(i))
		{
			return true;
		}
	}
	return false;
}
//��һ���
int		ThingHandleEx::ReceiveUserChangeCard(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser)
{
	if(uSize != sizeof(tagSuperChangeCard))
	{
		return 0;
	}

	tagSuperChangeCard * pChangeCard = (tagSuperChangeCard *)pData;

	if(pChangeCard == NULL || bWatchUser || pDesk->m_byGameStation != GS_PLAY_GAME)
	{
		return 0;
	}

	if (pChangeCard->byChangeCard == 0 || pChangeCard->byChangeCard == 255 || pChangeCard->byNewCard == 0 || pChangeCard->byNewCard == 255)
	{
		return 0;
	}
	//�Ƿ񳬶����
	if (!IsSuperUser(bDeskStation) && 0)
	{
		return 0;
	}
	tagSuperChangeCard TSuperChangeCard;
	//��������������&&��ǽ���������Ʋ��ܻ���
	if (pDesk->sUserData.IsHaveAHandPai(bDeskStation,pChangeCard->byChangeCard) && pDesk->sUserData.IsHaveAMenPai(pChangeCard->byNewCard))
	{
		if (pDesk->sUserData.ChangeAHandPai(bDeskStation,pChangeCard->byChangeCard,pChangeCard->byNewCard) && pDesk->sUserData.ChangeAMenPai(pChangeCard->byNewCard,pChangeCard->byChangeCard))
		{
			TSuperChangeCard.bSuccese = true;
			TSuperChangeCard.byArHandPaiCount = pDesk->sUserData.CopyOneUserHandPai(TSuperChangeCard.byArHandPai,bDeskStation);
		}
	}
	pDesk->SendGameDataEx(bDeskStation, &TSuperChangeCard, sizeof(TSuperChangeCard), MDM_GM_GAME_NOTIFY, ASS_CHANGE_PAI_RESULT, 0);
	pDesk->SendWatchDataEx(bDeskStation, &TSuperChangeCard, sizeof(TSuperChangeCard), MDM_GM_GAME_NOTIFY, ASS_CHANGE_PAI_RESULT, 0);
	return 0;
}

/*---------------------------------------------------------------------------------------------------------*/
/*--------------------���������Ϣ-------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------*/
//�յ��û�ͬ����Ϸ��Ϣ
int		ThingHandleEx::ReceiveUserAgreeGame(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser)
{
	return ThingHandle::ReceiveUserAgreeGame(bDeskStation, pData, uSize, bWatchUser);
}
/*---------------------------------------------------------------------------------------------------------*/
// �յ��й���Ϣ
int		ThingHandleEx::ReceiveUserTuoGuan(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser)
{
	if (pDesk->m_bIsBuy)
	{
		return 0;
	}
	if(uSize != sizeof(UserTouGuan))
	{
		return 0;
	}
	if(bWatchUser || pDesk->m_byGameStation != GS_PLAY_GAME)//������Ϸ�в����й�
	{
		return 0;
	}

	UserTouGuan *pUserTouGuan = (UserTouGuan *)pData;
	if(pUserTouGuan == NULL)
	{
		return 0;
	}

	pDesk->sUserData.m_bTuoGuan[bDeskStation] = pUserTouGuan->bIsTuoGuan;

	// ��������й�״̬
	UserTouGuan	TUserTouGuan;
	TUserTouGuan.byStation	= pUserTouGuan->byStation;
	TUserTouGuan.bIsTuoGuan	= pUserTouGuan->bIsTuoGuan;
	for(int i=0;i<PLAY_COUNT;++i)
	{
		TUserTouGuan.bTuoGuan[i] = pDesk->sUserData.m_bTuoGuan[i];		
	}
	for(int i=0;i<PLAY_COUNT;i++)
	{
		pDesk->SendGameDataEx(i,&TUserTouGuan,sizeof(TUserTouGuan),MDM_GM_GAME_NOTIFY,ASS_AUTOCARD,0);
		pDesk->SendWatchDataEx(i,&TUserTouGuan,sizeof(TUserTouGuan),MDM_GM_GAME_NOTIFY,ASS_AUTOCARD,0);
	}

	//�Ƿ����ڵȴ��Լ����¼� && ���й��¼�
	if(pDesk->sGameData.m_MjWait.byCurChair == pUserTouGuan->byStation && pUserTouGuan->bIsTuoGuan && pDesk->sGameData.m_MjWait.byTime > 1)
	{
		//1����������
		pDesk->sGameData.m_MjWait.byTime = 1;
	}
	return 0;
}
/*---------------------------------------------------------------------------------------------------------*/
// �û�����
int		ThingHandleEx::ReceiveUserOutCard(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser)
{
	if(uSize != sizeof(tagOutPaiEx))
	{
		return 0;
	}
	tagOutPaiEx * pOutCard = (tagOutPaiEx *)pData;

	if(pOutCard == NULL || bWatchUser || pDesk->m_byGameStation != GS_PLAY_GAME)
	{
		return 0;
	}

	if(pOutCard->byPs == 255 || pDesk->sUserData.GetAHandPaiCount(pOutCard->byUser,pOutCard->byPs)==0 || !pDesk->sUserData.IsOutPaiPeople(pOutCard->byUser))
	{
		return 0;
	}

	//��¼�Ѿ���������(��������غ����)
	pDesk->sUserData.m_bHaveOut[bDeskStation] = true;

	if(pDesk->sUserData.CheckIsHuaPai(pOutCard->byPs))
	{
		ExecuteBuHua(bDeskStation,pOutCard->byPs);
		return 0;
	}

	//pDesk->sGameData.T_TingPai.byAnGangCard = 255;

	//��¼����ִ�е��¼�
	pDesk->sGameData.m_byThingDoing = THING_OUT_PAI;
	pDesk->sGameData.m_byLianGang = 0;
	pDesk->sGameData.m_byGangHua = 0;
//	pDesk->sGameData.T_HuPai.Clear();//������Ƽ�¼ 2012-08-15

	//��¼����״̬��ӵ�ڸܿ�
	for(int i=0;i<PLAY_COUNT;i++)
	{
		//if(i != bDeskStation)
		{
			pDesk->sGameData.m_bGangState[i] = false;
		}
	}

	//�������������
	pDesk->sGameData.T_OutPai.Clear();
	pDesk->sGameData.T_OutPai = *pOutCard;
	

	//ɾ��һ������
	pDesk->sUserData.DelleteAHandPai(pOutCard->byUser,pOutCard->byPs);
	//���һ�ų���
	pDesk->sUserData.AddToOutPai(pOutCard->byUser,pOutCard->byPs);
	//������ʱ����
	ClearTempData();

	BYTE byCanOut[MAX_HAND_PAI];
	memset(byCanOut,255,sizeof(byCanOut));
	if(!pDesk->m_bCanTing[bDeskStation]  && pDesk->sCheckHuPai.CanTing(bDeskStation,byCanOut))
	{
		pDesk->m_bCanTing[bDeskStation] = true;
		tagCanTing canTing;
		canTing.byDeskStation = bDeskStation;
		for (int i=0;i<PLAY_COUNT;i++)
		{	
			pDesk->SendGameDataEx(i, &canTing, sizeof(tagCanTing), MDM_GM_GAME_NOTIFY, THING_CAN_TING, 0);
			pDesk->SendWatchDataEx(i, &canTing, sizeof(tagCanTing), MDM_GM_GAME_NOTIFY, THING_CAN_TING, 0);
		}
	}

	pDesk->sUserData.m_byBuGangPai = 255;//���ܵ÷ֵ��ƣ����ڲ��ܣ�ץ���ܲ��ܵ��ƺ����ϲ��ܲ��з֣������޷֣�

	//��ҵ��������
	if(pDesk->sGameData.T_TingPai.bHitTing[pOutCard->byUser] && !pDesk->sUserData.m_bTing[pOutCard->byUser])//��ҵ��������,
	{
		if(CLogicBase::IsHaveInArr(pDesk->sGameData.T_CPGNotify[pOutCard->byUser].m_byTingCanOut,pOutCard->byPs,HAND_CARD_NUM))
		{
			pDesk->sUserData.m_bTing[pOutCard->byUser] = true;
			pDesk->sGameData.T_OutPai.bTing = true;
		}
		else
		{
			pDesk->sUserData.m_bTing[pOutCard->byUser] = false;
		}
		pDesk->sGameData.T_TingPai.bHitTing[pOutCard->byUser] = false;
	}

	//�����ƺ� �������ҵ�����
	pDesk->sUserData.SortHandPai(pOutCard->byUser,false);

	
	for(int i=0;i<PLAY_COUNT;i++)
	{
		//��������
		pDesk->sGameData.T_OutPai.m_byArOutPaiCount[i] = pDesk->sUserData.CopyOutPai(i,pDesk->sGameData.T_OutPai.m_byArOutPai[i]);
		//��ҵ���������
		pDesk->sGameData.T_OutPai.m_byArHandPaiCount[i] = pDesk->sUserData.GetHandPaiCount(i);
		//��ȡ����״̬
		pDesk->sGameData.T_OutPai.bUserTing[i] = pDesk->sUserData.m_bTing[i];
	}

	//���ͳ�������
	for (int i=0;i<PLAY_COUNT;i++)
	{	
		memset(pDesk->sGameData.T_OutPai.m_byArHandPai,255,sizeof(pDesk->sGameData.T_OutPai.m_byArHandPai));
		pDesk->sUserData.CopyHandPai(pDesk->sGameData.T_OutPai.m_byArHandPai,pOutCard->byUser,true);
		//��������
		//pDesk->sUserData.CopyHandPai(pDesk->sGameData.T_OutPai.m_byArHandPai,i,pDesk->sUserData.m_bTing[i]);

		pDesk->SendGameDataEx(i, &pDesk->sGameData.T_OutPai, sizeof(pDesk->sGameData.T_OutPai), MDM_GM_GAME_NOTIFY, THING_OUT_PAI, 0);
		pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_OutPai, sizeof(pDesk->sGameData.T_OutPai), MDM_GM_GAME_NOTIFY, THING_OUT_PAI, 0);
	}

	//������⣺û��������Ӧ��ֱ��ץ��	
	if(!CheckAction(pOutCard->byUser,pOutCard->byPs,2))	//���Ƽ�⶯��
	{
		//û�ж�����ֱ����һ�����ץ��
		ApplyAction(THING_ZHUA_PAI,100);	//������һ���¼�
	}
	else
	{
		//���������Ƹ��ͻ������ 
		for (int i = 0; i < PLAY_COUNT; i++) {
			if (pDesk->sGameData.T_CPGNotify[i].bCanAction) {
				pDesk->SendGameDataEx(i, &pDesk->sGameData.T_CPGNotify, sizeof(pDesk->sGameData.T_CPGNotify), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
				pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_CPGNotify, sizeof(pDesk->sGameData.T_CPGNotify), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
			}
		}
		//if(HaveUserCanDoAction(bDeskStation))
		//{
		//	
		//}
		//else
		//{
		//	//ô�з��������Ƹ��ͻ������ ������ץ���¼�
		//	//û�ж�����ֱ����һ�����ץ��
		//	pDesk->sGameData.ApplyThingID = THING_ZHUA_PAI;
		//	ApplyAction(THING_ZHUA_PAI,100);	//������һ���¼�
		//}

		CString str;
		str.Format("********************%s����%d,��⶯��********************",pDesk->m_pUserInfo[pOutCard->byUser]->m_UserData.szName,pOutCard->byPs);
		DebugPrintf(str);
		LogAction();
	}
	return 0;
}
/*---------------------------------------------------------------------------------------------------------*/
// �յ��û�pass ��Ϣ
int		ThingHandleEx::ReceiveUserPassCheck(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser,bool bAuto)
{
	if (!pDesk->sGameData.T_CPGNotify[bDeskStation].bHaveReturn) {
		pDesk->sGameData.T_CPGNotify[bDeskStation].bHaveReturn = true;
		pDesk->sGameData.T_CPGNotify[bDeskStation].m_byMaxThing = ACTION_NO;
		HandleAction();
	}
//	if(pDesk->sGameData.ApplyThingID != 255 || bWatchUser)//�������¼��Ͳ���Ӧpass��Ϣ
//	{
//		return 0;
//	}
//	//����Ѿ���Ӧ�˴˶��� 
//	if (pDesk->sGameData.T_CPGNotify[bDeskStation].bHaveReturn || !pDesk->sGameData.T_CPGNotify[bDeskStation].bCanAction)
//	{
//		return 0;
//	}
//
//	//��ǰ���ǵȴ������
//	if(pDesk->sGameData.m_MjWait.byCurChair != bDeskStation)
//	{
//		return 0;
//	}
//
///*	if(bDeskStation != pDesk->sUserData.m_byNowOutStation && pDesk->sGameData.T_CPGNotify[bDeskStation].bHu)//����ܺ�û�к���,��¼����
//	{
//		pDesk->sUserData.m_bQiHu[bDeskStation] = true;//����Ƿ�����״̬
//	}
//*/
//	if (pDesk->sGameData.T_CPGNotify[bDeskStation].bPeng)
//	{
//// 		CString str;
//// 		str.Format("chenlog----------���[%d] ������,������ %d",bDeskStation,pDesk->sGameData.T_OutPai.byPs);
//// 		OutputDebugString(str);
//		if (pDesk->sGameData.T_NoPeng[bDeskStation].bHas(pDesk->sGameData.T_OutPai.byPs))
//		{
//			pDesk->sGameData.T_NoPeng[bDeskStation].set(pDesk->sGameData.T_OutPai.byPs);
//		}
//	}
//
//
//	if (pDesk->sGameData.T_CPGNotify[bDeskStation].bHu)
//	{
//// 		CString str;
//// 		str.Format("chenlog----------���[%d] ���Ժ�,������ %d",bDeskStation,pDesk->sGameData.T_OutPai.byPs);
//// 		OutputDebugString(str);
//		if (pDesk->sGameData.T_NoHu[bDeskStation].bHas(pDesk->sGameData.T_OutPai.byPs))
//		{
//			pDesk->sGameData.T_NoHu[bDeskStation].set(pDesk->sGameData.T_OutPai.byPs);
//		}
//	}
//	
//
//
//	pDesk->sGameData.T_CPGNotify[bDeskStation].bHaveReturn = true;//��¼��һ�Ӧ
//	pDesk->sGameData.T_CPGNotify[bDeskStation].Clear();
//
//	//���ع��ƽ����Ϣ���ͻ��� THING_GUO_PAI
//	pDesk->SendGameDataEx(bDeskStation, MDM_GM_GAME_NOTIFY, THING_GUO_PAI, 0);
//	pDesk->SendWatchDataEx(bDeskStation, MDM_GM_GAME_NOTIFY, THING_GUO_PAI, 0);
//
//	//�������Ƿ��п������Ķ���
//	if(HaveUserCanDoAction(bDeskStation))
//	{
//		/*for(int i = 0; i < PLAY_COUNT; i++)
//		{
//		pDesk->SendGameDataEx(i,NULL,0,MDM_GM_GAME_NOTIFY,THING_HAVE_ACTION,0);
//		}*/
//	}
//	else
//	{
//		//�Ƿ����˺�����
//		bool	bHaveHuPai = false;
//		for(int i=0; i<PLAY_COUNT; i++)
//		{
//			if(pDesk->sGameData.T_HuPai.bHaveHu[i])
//			{
//				bHaveHuPai = true;
//				break;
//			}
//		}
//
//		//���˺����� �ͽ���
//		if(bHaveHuPai)
//		{
//			//��Ϸ����
//			pDesk->sGameData.ApplyThingID	= THING_COUNT_FEN;
//			ApplyAction(pDesk->sGameData.ApplyThingID,200);
//		}
//		else
//		{
//			//�Ƿ���ҳ���
//			bool bIsOutPai = false;	
//			for(int i=0;i<PLAY_COUNT;++i)
//			{
//				if(pDesk->sUserData.IsOutPaiPeople(i))//�������
//				{
//					bIsOutPai = true;
//					break;
//				}
//			}
//
//			//����ǳ��� ��ô�ͳ���
//			if(bIsOutPai)
//			{
//				//�����ϵͳ���� ��ôֱ�Ӿͳ�����
//				if(bAuto)
//				{
//					tagOutPaiEx outpai;
//					outpai.Clear();
//					outpai.byUser = bDeskStation;
//					outpai.byPs = pDesk->sUserData.GetLastHandPai(bDeskStation);
//					ReceiveUserOutCard(bDeskStation,&outpai,sizeof(outpai),false);
//				}
//				else
//				{
//					OutputDebugString("dwjsdmj::�������ȡ�����ƺ�Ҫ����--ʱ��Ϊ��ǰ��ʣ��ʱ��");
//					//�������ȡ�����ƺ� ���������������Ƽ�ʱ�� ��Ϊǰ���������������� �������˼�ʱ������ �����Զ����Ƶ�
//					if(pDesk->sGameData.m_MjWait.byTime > 1)
//					{
//						//�����Զ������������
//						SetDoingThing(bDeskStation,THING_OUT_PAI,pDesk->sGameData.m_MjWait.byTime-1);
//					}
//					else
//					{
//						//�����Զ������������
//						SetDoingThing(bDeskStation,THING_OUT_PAI,1);
//					}
//				}
//			}
//			else	//���ǳ��� ����ץ��
//			{
//				//��һ�����ץ��
//				pDesk->sGameData.ApplyThingID = THING_ZHUA_PAI;
//				ApplyAction(THING_ZHUA_PAI,100);	//������һ���¼�
//
//			}
//		}
//	}
//	
	return 0;
}
/*---------------------------------------------------------------------------------------------------------*/
// �û�������Ϣ
int		ThingHandleEx::ReceiveUserChiCard(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser)
{
	if(bWatchUser || pDesk->m_byGameStation != GS_PLAY_GAME)
	{
		return 0;
	}
	if(uSize != sizeof(tagChiPaiEx))
	{
		return 0;
	}
	tagChiPaiEx * pChiCard = (tagChiPaiEx *)pData;
	if(pChiCard == NULL )
	{
		return 0;
	}
	if(!pDesk->sGameData.T_CPGNotify[bDeskStation].bChi)
	{
		return 0;
	}

	if(pChiCard->byPs == 255 )
	{
		return 0;
	}

	if(!pDesk->sGameData.m_mjAction.bChi)
	{
		return 0;
	}

	//��һ������Ŵ�������ͻ����ظ�����
	if (pDesk->sGameData.T_CPGNotify[pChiCard->byUser].bHaveReturn == false) {
		//��¼������ѻظ�����Ϣ
		pDesk->sGameData.T_CPGNotify[pChiCard->byUser].bHaveReturn = true;
		//���¸�������������¼��ǳ�
		pDesk->sGameData.T_CPGNotify[pChiCard->byUser].m_byMaxThing = ACTION_CHI;

		//������
		pDesk->sGameData.T_ChiPai.Clear();
		memcpy(&pDesk->sGameData.T_ChiPai, pChiCard, sizeof(pDesk->sGameData.T_ChiPai));
		HandleAction();
	}
	
	/*//�ж��Ƿ���������ҿ��������ܡ��� ʲô��
	bool bCanChi = true;
	for(int i=0; i<PLAY_COUNT;i++)
	{
		if(i == bDeskStation)
		{
			continue;
		}
		if(pDesk->sGameData.T_CPGNotify[i].bGang || pDesk->sGameData.T_CPGNotify[i].bPeng || pDesk->sGameData.T_CPGNotify[i].bHu)
		{
			bCanChi = false;
			break;
		}
	}

	if(!bCanChi)
	{
		return 0;
	}

	
	//��ʼ����������
	pDesk->sGameData.T_ChiPai.Clear();
	memcpy(&pDesk->sGameData.T_ChiPai, pChiCard, sizeof(pDesk->sGameData.T_ChiPai));

	BYTE NextID=255,StarTime=255;
	HandleChiPai(NextID,StarTime);*/
	return 0;
}
/*---------------------------------------------------------------------------------------------------------*/
// �û�������Ϣ
int		ThingHandleEx::ReceiveUserPengCard(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser)
{
	if(uSize != sizeof(tagPengPaiEx))
	{
		return 0;
	}

	/*bool bCanPeng = true;
	for(int i=0; i<PLAY_COUNT;i++)
	{
		if(i == bDeskStation)
		{
			continue;
		}
		if(pDesk->sGameData.T_CPGNotify[i].bHu)
		{
			bCanPeng = false;
			break;
		}
	}

	if(!bCanPeng)
	{
		return 0;
	}


	tagPengPaiEx * pPengPai = (tagPengPaiEx *)pData;
	if(pPengPai == NULL || bWatchUser ||  pDesk->m_byGameStation != GS_PLAY_GAME)
	{
		return 0;
	}

	if(!pDesk->sGameData.T_CPGNotify[bDeskStation].bPeng || pPengPai->byPs == 255 || !pDesk->sGameData.m_mjAction.bPeng)
	{
		return 0;
	}

	pDesk->sGameData.T_PengPai.Clear();
	memcpy(&pDesk->sGameData.T_PengPai, pPengPai, sizeof(pDesk->sGameData.T_PengPai));

	BYTE NextID=255,StarTime=255;
	HandlePengPai(NextID,StarTime);
*/

	tagPengPaiEx * pPengCard = (tagPengPaiEx *)pData;
	if (pPengCard == NULL || bWatchUser || pDesk->m_byGameStation != GS_PLAY_GAME)
	{
		return 0;
	}
	if (!pDesk->sGameData.T_CPGNotify[bDeskStation].bPeng || pPengCard->byPs == 255 || !pDesk->sGameData.m_mjAction.bPeng)
	{
		return 0;
	}

	//��һ������Ŵ�������ͻ����ظ�����
	if (pDesk->sGameData.T_CPGNotify[pPengCard->byUser].bHaveReturn == false) {
		//��¼������ѻظ�����Ϣ
		pDesk->sGameData.T_CPGNotify[pPengCard->byUser].bHaveReturn = true;
		//���¸�������������¼�����
		pDesk->sGameData.T_CPGNotify[pPengCard->byUser].m_byMaxThing = ACTION_PENG;

		//������
		pDesk->sGameData.T_PengPai.Clear();
		memcpy(&pDesk->sGameData.T_PengPai, pPengCard, sizeof(pDesk->sGameData.T_PengPai));
		HandleAction();
	}

	return 0;
}
/*---------------------------------------------------------------------------------------------------------*/
// �û�������Ϣ
int		ThingHandleEx::ReceiveUserGangCard(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser)
{
	if(uSize != sizeof(tagGangPaiEx))
	{
		return 0;
	}
	/*
	//�ж��Ƿ���������ҿ��Ժ� ʲô��
	bool bCanGang = true;
	for(int i=0; i<PLAY_COUNT;i++)
	{
		if(i == bDeskStation)
		{
			continue;
		}
		if(pDesk->sGameData.T_CPGNotify[i].bHu)
		{
			bCanGang = false;
			break;
		}
	}

	if(!bCanGang)
	{
		return 0;
	}

	tagGangPaiEx * pGangPai = (tagGangPaiEx *)pData;
	if(pGangPai == NULL || bWatchUser ||  pDesk->m_byGameStation != GS_PLAY_GAME)
	{
		return 0;
	}

	if(!pDesk->sGameData.T_CPGNotify[bDeskStation].bGang || pGangPai->byPs == 255 || !pDesk->sGameData.m_mjAction.bGang)
	{
		return 0;
	}

	//��ʼ����������
	pDesk->sGameData.T_GangPai.Clear();
	memcpy(&pDesk->sGameData.T_GangPai, pGangPai, sizeof(pDesk->sGameData.T_GangPai));

	BYTE NextID=255,StarTime=255;
	HandleGangPai(NextID,StarTime);
	*/

	tagGangPaiEx * pGangCard = (tagGangPaiEx *)pData;

	if (pGangCard == NULL || bWatchUser || pDesk->m_byGameStation != GS_PLAY_GAME)
	{
		return 0;
	}
	if (!pDesk->sGameData.T_CPGNotify[bDeskStation].bGang || pGangCard->byPs == 255 || !pDesk->sGameData.m_mjAction.bGang)
	{
		return 0;
	}

	//��һ������Ŵ�������ͻ����ظ�����
	if (pDesk->sGameData.T_CPGNotify[pGangCard->byUser].bHaveReturn == false) {
		//��¼����
		pDesk->sGameData.T_GangPai.Clear();
		memcpy(&pDesk->sGameData.T_GangPai, pGangCard, sizeof(pDesk->sGameData.T_GangPai));
		
		//�ж��Ƿ񲹸�
		/*bool bBuGang = false;
		if (pDesk->sGameData.m_byThingDoing == THING_ZHUA_PAI || THING_ONE_BUHUA == pDesk->sGameData.m_byThingDoing || THING_BEGIN_OUT == pDesk->sGameData.m_byThingDoing)
		{
			for (int i = 0; i<5; i++)
			{
				if (pDesk->sGameData.T_CPGNotify[pGangCard->byUser].m_iGangData[i][0] == ACTION_BU_GANG) {
					bBuGang = true;
					break;
				}
			}
		}*/

		//��¼����
		pDesk->sGameData.T_CPGNotify[pGangCard->byUser].bHaveReturn = true;
		pDesk->sGameData.T_CPGNotify[pGangCard->byUser].m_byMaxThing = ACTION_MING_GANG;
		
		//���Ƽ�����ܺ�
		//if (bBuGang && CheckAction(pGangCard->byUser, pGangCard->byPs, 3))
		//{
		//	bool bHaveSend = false;	//�Ƿ��Ѿ���������Ϣ
		//	BYTE byCanActionDesk = 255;	//���������������
		//	for (int i = 0; i < PLAY_COUNT; i++)
		//	{
		//		if (i == pGangCard->byUser)
		//		{
		//			continue;
		//		}
		//		if (pDesk->sGameData.T_CPGNotify[i].bHu)
		//		{
		//			pDesk->SendGameDataEx(i, &pDesk->sGameData.T_CPGNotify, sizeof(pDesk->sGameData.T_CPGNotify), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
		//			pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_CPGNotify, sizeof(pDesk->sGameData.T_CPGNotify), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
		//			bHaveSend = true;	//�Ƿ��Ѿ���������Ϣ
		//			byCanActionDesk = i;	//���������������
		//			break;
		//		}
		//	}
		//	if (bHaveSend)
		//	{
		//		SetDoingThing(byCanActionDesk, THING_HU_PAI);
		//		return 0;
		//	}
		//}

		//������
		HandleAction();
	}

	return 0;
}


// �û�������Ϣ
int		ThingHandleEx::ReceiveUserTingCard(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser)
{
	if(uSize != sizeof(tagTingPaiEx))
	{
		return 0;
	}

	tagTingPaiEx * pTingCard = (tagTingPaiEx *)pData;
	if(pTingCard == NULL || bWatchUser ||  pDesk->m_byGameStation != GS_PLAY_GAME)
	{
		return 0;
	}
	
	if(!pDesk->sGameData.T_CPGNotify[bDeskStation].bTing || !pDesk->sGameData.m_mjAction.bTing)
	{
		return 0;
	}
	//����Ѿ������� 
	if(pDesk->sUserData.m_bTing[pTingCard->byUser])
	{
		return 0;
	}

	pDesk->sUserData.m_bTing[pTingCard->byUser] = true;

	//��¼����Ѿ����������
	pDesk->sGameData.T_TingPai.bHitTing[pTingCard->byUser] = pTingCard->bTing;

	//֪ͨ�������
	for (int i=0;i<PLAY_COUNT;i++)
	{	
		pDesk->SendGameDataEx(i, &pDesk->sGameData.T_TingPai, sizeof(pDesk->sGameData.T_TingPai), MDM_GM_GAME_NOTIFY, THING_TING_PAI, 0);
		pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_TingPai, sizeof(pDesk->sGameData.T_TingPai), MDM_GM_GAME_NOTIFY, THING_TING_PAI, 0);
	}

	for (int i = 0; i<PLAY_COUNT; i++) {
		//���ж���δ������������
		if (pDesk->sGameData.T_CPGNotify[i].bCanAction) {
			return 0;
		}
	}
	//���ж����Ѵ���������Ҳ�Ѵ�������ץ�ƽ׶�
	ApplyAction(THING_ZHUA_PAI, 100);

	return 0;
}


// �û�������Ϣ
int		ThingHandleEx::ReceiveUserHuCard(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser)
{
	if(uSize != sizeof(tagHuPaiEx))
	{
		return 0;
	}

	tagHuPaiEx * pHuCard = (tagHuPaiEx *)pData;

	if(pHuCard == NULL || bWatchUser || pDesk->m_byGameStation != GS_PLAY_GAME)
	{
		return 0;
	}
	if(!pDesk->sGameData.T_CPGNotify[bDeskStation].bHu)
	{
		return 0;
	}

	//��һ������Ŵ�������ͻ����ظ�����
	if (pDesk->sGameData.T_CPGNotify[pHuCard->byUser].bHaveReturn == false) {
		pDesk->sGameData.T_CPGNotify[pHuCard->byUser].bHaveReturn = true;
		pDesk->sGameData.T_CPGNotify[pHuCard->byUser].m_byMaxThing = ACTION_HU;

		//������ҵ�λ��
		pDesk->sGameData.T_HuPai.byUser = pHuCard->byUser;
		//������
		HandleAction();
	}

	return 0;
}


//�ж��ܷ�����
//�ܴ���Ļ����ر���Ҫ����Ķ������������
bool ThingHandleEx::CanHandleAction() {
	//���ҵ�ǰ����������������¼�
	pDesk->sGameData.m_byMaxAction = ACTION_NO;
	for (int i = 0; i<PLAY_COUNT; i++) {
		//�������ҲҪ���㣬��Ϊ����Һ����ˣ�������ҵĶ���Ҳֻ���Ǻ���
		/*if (pDesk->sUserData.m_bIsHu[i]) {
			continue;
		}*/
		if (pDesk->sGameData.T_CPGNotify[i].bCanAction && pDesk->sGameData.T_CPGNotify[i].m_byMaxThing > pDesk->sGameData.m_byMaxAction) {
			pDesk->sGameData.m_byMaxAction = pDesk->sGameData.T_CPGNotify[i].m_byMaxThing;
		}
	}

	if (pDesk->sGameData.m_byMaxAction == ACTION_NO) {
		return false;
	}

	//�ж�����¼��Ƿ����������
	for (int i = 0; i<PLAY_COUNT; i++) {
		if (pDesk->sUserData.m_bIsHu[i]) {
			continue;
		}
		//���������������¼�
		if (pDesk->sGameData.T_CPGNotify[i].bCanAction && pDesk->sGameData.T_CPGNotify[i].m_byMaxThing == pDesk->sGameData.m_byMaxAction && pDesk->sGameData.T_CPGNotify[i].bHaveReturn) {
			return true;
		}
	}

	return false;
}

/*
* ������
* ����������ҵ������жϸô����Ǹ�����
*/
void ThingHandleEx::HandleAction() {
	BYTE station = 255;
	if (CanHandleAction()) {
		switch (pDesk->sGameData.m_byMaxAction) {
		case ACTION_CHI:
			station = pDesk->sGameData.T_ChiPai.byUser;
			HandleChiPai();
			break;
		case ACTION_PENG:
			station = pDesk->sGameData.T_PengPai.byUser;
			HandlePengPai();
			break;
		case ACTION_AN_GANG:
		case ACTION_BU_GANG:
		case ACTION_MING_GANG:
			station = pDesk->sGameData.T_GangPai.byUser;
			HandleGangPai(pDesk->sGameData.m_byMaxAction);
			break;
		case ACTION_HU:
			HandleHuPai();
			break;
		case ACTION_NO:
			break;
		}
	}

	//���������û������������
	for (int i = 0; i<PLAY_COUNT; i++) {
		if (pDesk->sGameData.T_CPGNotify[i].bCanAction && pDesk->sGameData.T_CPGNotify[i].m_byMaxThing == pDesk->sGameData.m_byMaxAction && pDesk->sGameData.T_CPGNotify[i].bHaveReturn == false) {
			return;
		}
	}

	//��Ϸ�Ƿ����
	if (pDesk->sGameData.m_byMaxAction == ACTION_HU) {
		//���ƣ���Ϸ����
		ApplyAction(THING_COUNT_FEN, 2 * 100);
		return;
	}

	//�������ƶ���û������������
	for (int i = 0; i<PLAY_COUNT; i++) {
		if (pDesk->sGameData.T_CPGNotify[i].bTing) {
			return;
		}
	}

	if (pDesk->sGameData.m_byMaxAction == ACTION_PENG || pDesk->sGameData.m_byMaxAction == ACTION_CHI) {
		//������֮����û�ж���
		if (CheckAction(station, 255, 4)) {
			for (int i = 0; i < PLAY_COUNT; i++) {
				pDesk->SendGameDataEx(i, &pDesk->sGameData.T_CPGNotify, sizeof(pDesk->sGameData.T_CPGNotify), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
				pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_CPGNotify, sizeof(pDesk->sGameData.T_CPGNotify), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
			}
			CString str;
			if (pDesk->sGameData.m_byMaxAction == ACTION_PENG) {
				str.Format("********************%s����%d,��⶯��********************", pDesk->m_pUserInfo[station]->m_UserData.szName, pDesk->sGameData.T_PengPai.byPs);
			}
			else {
				str.Format("********************%s����%d,��⶯��********************", pDesk->m_pUserInfo[station]->m_UserData.szName, pDesk->sGameData.T_ChiPai.byPs);
			}
			DebugPrintf(str);
			LogAction();
			return;
		}
		//���ƻ���ƣ��������״̬
		ApplyAction(THING_OUT_PAI, 100);
	}
	else if (pDesk->sGameData.m_byMaxAction != ACTION_BU_GANG) {
		//���ƻ���ƣ�����ץ��״̬,����Ҫ�ж����ܺ���������
		bool bIsOutPai = false;
		for (int i = 0; i < PLAY_COUNT; ++i)
		{
			if (pDesk->sUserData.IsOutPaiPeople(i))//�������
			{
				bIsOutPai = true;
				break;
			}
		}
		if (bIsOutPai)
		{
			SetDoingThing(station, THING_OUT_PAI);
		}
		else
		{
			ApplyAction(THING_ZHUA_PAI, 100);
		}		
	}
}


BYTE ThingHandleEx::GetCanHuUser(BYTE outst,bool hu[],BYTE hust)//��ȡ�������ҽ������
{

	return ThingHandle::GetCanHuUser(outst,hu, hust);
}

//��ȡ�¼�λ��
BYTE ThingHandleEx::GetNextStation(BYTE station,bool shun)
{
    BYTE re = 255;
    if(shun)//˳ʱ��
    {
        int nLoop = 8;
        re = (station + 1)%PLAY_COUNT;
        while (nLoop-->0)
        {            
            if (!pDesk->sUserData.m_bIsHu[ re ])
            {
                break;
            }
            re = (re + 1)%PLAY_COUNT;
        }
    }
    else
    {
        int nLoop = 8;
        re = (station + 3)%PLAY_COUNT;
        while (nLoop-->0)
        {            
            if (!pDesk->sUserData.m_bIsHu[ re ])
            {
                break;
            }
            re = (re+3)%PLAY_COUNT;
        }
    }
    return re;
}

//������ʱ����
void ThingHandleEx::ClearTempData()
{
	ThingHandle::ClearTempData();
}


///////////�����¼�����///////////////////////////////////////////////////////////////////////////////////////
/*------------------------------------------------------------------------------------------------*/
//�����¼�,typeҪ������¼�	DWJ
void ThingHandleEx::ApplyAction(int type,int time)
{
	if(type >= THING_AUTOOUTCARD && type <= THING_ENG_UN_NORMAL)
	{
		if (pDesk->sGameData.ApplyThingID != 255)
		{
			pDesk->sGameData.ApplyThingID = type;
			pDesk->SetTimer(10, time);
		}
	}

}
/*------------------------------------------------------------------------------*/
///���ƣ�GameCPU
///��������Ϸ�¼��������ģ�
void	ThingHandleEx::GameCPU(int type)
{
    BYTE nextID = 255,time = 255;    
    switch(type)
    {
    case THING_GAME_BEGIN:	//��Ϸ��ʼ�¼�	DWJ
        {
            ExecuteGameBegin(nextID,time);
			break;
        }
    case THING_DING_NT:		//�׾��Զ�Ϊׯ�¼�	DWJ
        {
            ExecuteDongNt(nextID,time);
			break;
        }
	case THING_2SEZI_NT:  //�׾�������ɫ�Ӷ�ׯ���¼�
		{
			ExecuteTwoSeziNt(nextID,time);
			break;
		}
	case THING_2SEZI_DIR:	//��2��ɫ���¼������Ʒ����¼�	DWJ
		{
			ExecuteTwoSeziDir(nextID,time);
			break;
		}
	case THING_2SEZI_DIR_GP:	//��2��ɫ���¼������Ʒ�������Ƶ��¼�	DWJ
		{
			ExecuteTwoSeziDirGp(nextID,time);
			break;
		}
	case THING_SEND_PAI:	//�����¼�	DWJ
		{
			ExecuteSendPai(nextID,time);
			break;
		}
	case THING_ALL_BUHUA:	//Ϊ������Ҳ����¼�	DWJ
		{
			ExecuteAllBuHua(nextID,time);
			break;
		}
	case THING_BEGIN_OUT:	//ׯ�ҿ�ʼ����֪ͨ�¼�	DWJ
		{
			pDesk->m_byGameStation = GS_PLAY_GAME;
			ExecuteBeginOut(nextID,time);
			break;
		}
	case THING_ZHUA_PAI:	//���ץ��	DWJ
		{
			ExecuteZhuaPai(nextID,time);
			break;
		}
	case THING_ONE_BUHUA:	//�������ץ�����ƺ󲹻��¼�
		{
			ExecuteOneBuHua(nextID,time);
			break;
		}
	case THING_COUNT_FEN:	//����¼�
		{
			ExecuteCountFen(nextID,time);
			break;
		}
	case THING_ENG_HANDLE://���������¼�
		{
			ExecuteNormalEnd(nextID,time);
			break;
		}
    case THING_ENG_UN_NORMAL://�쳣���������¼�
        {
		ExecuteUnNormalEnd(nextID, time);
		break;
        }
	case THING_AUTOOUTCARD:
	{
		tagOutPaiEx outpai;
		outpai.Clear();
		outpai.byUser = pDesk->sUserData.m_byNowOutStation;
		outpai.byPs = pDesk->sGameData.T_ZhuaPai.byPs;
		ReceiveUserOutCard(pDesk->sUserData.m_byNowOutStation, &outpai, sizeof(outpai), false);
		break;
	}
    }
   // pDesk->sGameData.ApplyThingID = nextID;
    ApplyAction(nextID,time*100);//������һ���¼�
}
/*-------------------------------------------------------------------------------------------------*/
///��ʼ�¼�����	DWJ
void	ThingHandleEx::ExecuteGameBegin(BYTE &nextID,BYTE &time)
{   
	//��ʼ����Ϸ���ݺ��������
    pDesk->sGameData.InitData();

    pDesk->sUserData.InitData();

	memset(pDesk->m_bCanTing,0,sizeof(bool)*4);
	pDesk->KillTimer(TIME_WAIT_MSG);
	//pDesk->SetTimer(TIME_WAIT_MSG,1000);//�������ó�ʱ��ʱ��

	pDesk->sGameData.m_byThingDoing = THING_GAME_BEGIN;

	//ׯ�Ҳ����� ��ִ�����һ��ׯ���¼�
	if(pDesk->sGameData.m_byNtStation == 255)
	{
		pDesk->sGameData.m_iHuangZhuangCount = 0;
		//���һ�������ׯ
		nextID = THING_2SEZI_NT;//THING_DING_NT;
	}
	else 
	{
		nextID = THING_2SEZI_DIR_GP;//��ɫ�ӷ���
	}
	/*pDesk->sGameData.m_byNtStation = 0;
	nextID = THING_DING_NT;*/
	time	= 1;

	// ׯ��λ��
    pDesk->sGameData.T_Begin.byNt = pDesk->sGameData.m_byNtStation;	
	pDesk->sGameData.T_Begin.iHuangZhuangCount = pDesk->sGameData.m_iHuangZhuangCount;	
	//��������
    memset(pDesk->sGameData.T_Begin.byMenPai,0,sizeof(pDesk->sGameData.T_Begin.byMenPai));
	//���Ϳ�ʼ��Ϣ
	for (int i=0;i<PLAY_COUNT;i++)
	{
		pDesk->SendGameDataEx(i,&pDesk->sGameData.T_Begin,sizeof(pDesk->sGameData.T_Begin),MDM_GM_GAME_NOTIFY,THING_GAME_BEGIN,0);
		pDesk->SendWatchDataEx(i,&pDesk->sGameData.T_Begin,sizeof(pDesk->sGameData.T_Begin),MDM_GM_GAME_NOTIFY,THING_GAME_BEGIN,0);
	}
}
/*-------------------------------------------------------------------------------------------------*/
///�Ե�һ�����Ϊׯ�ң��Զ�Ϊׯ�¼���	DWJ
void	ThingHandleEx::ExecuteDongNt(BYTE &nextID,BYTE &time)
{	
	pDesk->sGameData.m_byThingDoing = THING_DING_NT;

	//������һ���¼�Ϊ ��ɸ��ȷ�����Ʒ�λ�¼�
	nextID = THING_2SEZI_DIR;
	time = 2;	//200������

	//���������
	pDesk->sGameData.T_DongNt.Clear();
	// ׯ��λ��	
	pDesk->sGameData.T_DongNt.byNt = pDesk->sGameData.m_byNtStation;	
	pDesk->sGameData.T_DongNt.iHuangZhuangCount = pDesk->sGameData.m_iHuangZhuangCount;

	for (int i=0;i<PLAY_COUNT;i++)
	{
		pDesk->SendGameDataEx(i,&pDesk->sGameData.T_DongNt,sizeof(pDesk->sGameData.T_DongNt),MDM_GM_GAME_NOTIFY,THING_DING_NT,0);
		pDesk->SendWatchDataEx(i,&pDesk->sGameData.T_DongNt,sizeof(pDesk->sGameData.T_DongNt),MDM_GM_GAME_NOTIFY,THING_DING_NT,0);
	}
}
/*-------------------------------------------------------------------------------------------------*/
///��2��ɫ��ȷ�����Ʒ��򣨵�����ȷ������	DWJ
void	ThingHandleEx::ExecuteTwoSeziDir(BYTE &nextID,BYTE &time)	
{
	pDesk->sGameData.m_byThingDoing = THING_2SEZI_DIR;
	///��2��ɫ��ȷ������λ���¼�
	nextID	= THING_2SEZI_DIR_GP;//׼��ִ�����ڶ���ɫ��ȷ�����ƶ����¼�
	time	= 30; //3000ms = 3S

	//���������
	pDesk->sGameData.T_TwoSeziDir.Clear();
	//��ɸ����ҵ�λ�� = ׯ�ҵ�λ��
	pDesk->sGameData.T_TwoSeziDir.byUser = pDesk->sGameData.m_byNtStation;
	pDesk->sGameData.T_TwoSeziDir.byNt = pDesk->sGameData.m_byNtStation;
	CLogicBase::GetSeziData(&pDesk->sGameData.T_TwoSeziDir.bySezi0,&pDesk->sGameData.T_TwoSeziDir.bySezi1);

	//��¼���Ƶķ���(1Ϊ�Լ� ��ʱ����)
	pDesk->sUserData.m_MenPai.byGetPaiDir = (pDesk->sGameData.T_TwoSeziDir.bySezi1 + pDesk->sGameData.T_TwoSeziDir.bySezi0 +  pDesk->sGameData.T_TwoSeziDir.byUser - 1)%4;
	//���Ʒ���
	pDesk->sGameData.T_TwoSeziDir.byDirection = pDesk->sUserData.m_MenPai.byGetPaiDir;

	//�����������ͻ���
	for (int i=0;i<PLAY_COUNT;i++)
	{
		pDesk->SendGameDataEx(i, &pDesk->sGameData.T_TwoSeziDir, sizeof(pDesk->sGameData.T_TwoSeziDir), MDM_GM_GAME_NOTIFY, THING_2SEZI_DIR, 0);
	}
	pDesk->SendWatchDataEx(PLAY_COUNT, &pDesk->sGameData.T_TwoSeziDir, sizeof(pDesk->sGameData.T_TwoSeziDir), MDM_GM_GAME_NOTIFY, THING_2SEZI_DIR, 0);
}
/*-------------------------------------------------------------------------------------------------*/
///��2��ɫ��ȷ�����Ʒ�������ƶ����������ͷ���С�������DWJ
void	ThingHandleEx::ExecuteTwoSeziDirGp(BYTE &nextID,BYTE &time)	
{   
	SetDoingThing(0,THING_2SEZI_DIR_GP);//����ִ���¼�

	pDesk->sGameData.m_byThingDoing = THING_2SEZI_DIR_GP;
	//���������
	pDesk->sGameData.T_TwoSeziDirAndGetPai.Clear();
	///��2��ɫ��ȷ������λ�ã������ͣ������Ƶ㣨��С�㣩�¼�	
	pDesk->sGameData.T_TwoSeziDirAndGetPai.byUser = pDesk->sGameData.m_byNtStation;
	//ҡ����
	CLogicBase::GetSeziData(&pDesk->sGameData.T_TwoSeziDirAndGetPai.bySezi0,&pDesk->sGameData.T_TwoSeziDirAndGetPai.bySezi1);

	//���Ƶ��� = (��һ��ɸ�ӵ��ܺ�+�������ɸ�ӵ�����)	DWJTEST (�ĸ�ɸ�ӵ���>18��ô��)
	pDesk->sGameData.T_TwoSeziDirAndGetPai.bySezi0 = pDesk->sGameData.T_TwoSeziDirAndGetPai.bySezi0%6+1;
	pDesk->sGameData.T_TwoSeziDirAndGetPai.bySezi1 = pDesk->sGameData.T_TwoSeziDirAndGetPai.bySezi1%6+1;
	//���Ʒ���
	pDesk->sUserData.m_MenPai.byGetPaiDir = (pDesk->sGameData.m_byNtStation+pDesk->sGameData.T_TwoSeziDirAndGetPai.bySezi1 + pDesk->sGameData.T_TwoSeziDirAndGetPai.bySezi0-1)%4;
	//���Ƶ���
	pDesk->sUserData.m_MenPai.byGetPai = min(pDesk->sGameData.T_TwoSeziDirAndGetPai.bySezi0, pDesk->sGameData.T_TwoSeziDirAndGetPai.bySezi1);

	pDesk->sGameData.T_TwoSeziDirAndGetPai.byDirection = pDesk->sUserData.m_MenPai.byGetPaiDir;
	pDesk->sGameData.T_TwoSeziDirAndGetPai.byGetPai = pDesk->sUserData.m_MenPai.byGetPai;

	//֪ͨ�ͻ���
	for (int i=0;i<PLAY_COUNT;i++)
	{
		pDesk->SendGameDataEx(i, &pDesk->sGameData.T_TwoSeziDirAndGetPai, sizeof(pDesk->sGameData.T_TwoSeziDirAndGetPai), MDM_GM_GAME_NOTIFY, THING_2SEZI_DIR_GP, 0);
	}
	pDesk->SendWatchDataEx(PLAY_COUNT, &pDesk->sGameData.T_TwoSeziDirAndGetPai, sizeof(pDesk->sGameData.T_TwoSeziDirAndGetPai), MDM_GM_GAME_NOTIFY, THING_2SEZI_DIR_GP, 0);

	//��һ�������¼�
	nextID = THING_SEND_PAI;
	time = 60;

}
/*-------------------------------------------------------------------------------------------------*/
///����	
void	ThingHandleEx::ExecuteSendPai(BYTE &nextID,BYTE &time)	
{
	pDesk->sGameData.m_byThingDoing = THING_SEND_PAI;//��¼���ڷ������¼�

	///��ǰץ�Ʒ���true ˳ʱ�룬false ��ʱ��
	pDesk->sUserData.m_bZhuaPaiDir = true;    
	///�����¼�
	pDesk->sGameData.T_SendPai.byDo = 1;	 
	//������
	DisPatchCard();

	//�·�������ҵ�13����
	for(int i=0;i<PLAY_COUNT;i++)
	{
		for(int j=0;j<MAX_HAND_PAI-1;++j)
		{
			GetPai(i,true,1);
		}
	}

	//ׯ���ٶ�ץһ����
	BYTE card = 255;
	card=GetPai(pDesk->sGameData.m_byNtStation,true,1);

	//��������
	ChangeMenPai();
	pDesk->sGameData.T_SendPai.Clear();
	for(int i=0;i<PLAY_COUNT;++i)
	{
		pDesk->sUserData.CopyMenPai(i,pDesk->sGameData.T_SendPai.byMenPai[i]);//��������

		//���������
		if(i == pDesk->sGameData.m_byNtStation)
		{
			pDesk->sGameData.T_SendPai.m_byArHandPaiCount[i] = 14;
		}
		else
		{
			pDesk->sGameData.T_SendPai.m_byArHandPaiCount[i] = 13;
		}
	}

	//dwjtesttest
	/*pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][0] = 1;
	pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][1] = 1;
	pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][2] = 1;
	pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][3] = 1;
	pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][4] = 5;
	pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][5] = 6;
	pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][6] = 7;
	pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][7] = 18;
	pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][8] = 19;
	pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][9] = 12;
	pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][10] = 13;
	pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][11] = 4;
	pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][12] = 22;
	pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][13] = 22;

	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+1)%PLAY_COUNT][0] = 1;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+1)%PLAY_COUNT][1] = 2;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+1)%PLAY_COUNT][2] = 3;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+1)%PLAY_COUNT][3] = 4;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+1)%PLAY_COUNT][4] = 5;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+1)%PLAY_COUNT][5] = 6;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+1)%PLAY_COUNT][6] = 11;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+1)%PLAY_COUNT][7] = 12;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+1)%PLAY_COUNT][8] = 13;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+1)%PLAY_COUNT][9] = 14;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+1)%PLAY_COUNT][10] = 15;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+1)%PLAY_COUNT][11] = 16;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+1)%PLAY_COUNT][12] = 28;

	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+2)%PLAY_COUNT][0] = 1;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+2)%PLAY_COUNT][1] = 2;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+2)%PLAY_COUNT][2] = 3;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+2)%PLAY_COUNT][3] = 4;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+2)%PLAY_COUNT][4] = 5;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+2)%PLAY_COUNT][5] = 6;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+2)%PLAY_COUNT][6] = 11;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+2)%PLAY_COUNT][7] = 12;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+2)%PLAY_COUNT][8] = 13;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+2)%PLAY_COUNT][9] = 14;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+2)%PLAY_COUNT][10] = 15;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+2)%PLAY_COUNT][11] = 16;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+2)%PLAY_COUNT][12] = 28;

	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+3)%PLAY_COUNT][0] = 1;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+3)%PLAY_COUNT][1] = 2;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+3)%PLAY_COUNT][2] = 3;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+3)%PLAY_COUNT][3] = 4;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+3)%PLAY_COUNT][4] = 5;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+3)%PLAY_COUNT][5] = 6;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+3)%PLAY_COUNT][6] = 11;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+3)%PLAY_COUNT][7] = 12;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+3)%PLAY_COUNT][8] = 13;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+3)%PLAY_COUNT][9] = 14;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+3)%PLAY_COUNT][10] = 15;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+3)%PLAY_COUNT][11] = 16;
	pDesk->sUserData.m_byArHandPai[(pDesk->sGameData.m_byNtStation+3)%PLAY_COUNT][12] = 28;*/
	

	//���ĸ���ҷַ����е���
	for(int i=0;i<PLAY_COUNT;i++)
	{	
		//��������
		pDesk->sUserData.CopyHandPai(pDesk->sGameData.T_SendPai.m_byArHandPai,i,false);
		pDesk->SendGameDataEx(i, &pDesk->sGameData.T_SendPai, sizeof(pDesk->sGameData.T_SendPai), MDM_GM_GAME_NOTIFY, THING_SEND_PAI, 0);
		pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_SendPai, sizeof(pDesk->sGameData.T_SendPai), MDM_GM_GAME_NOTIFY, THING_SEND_PAI, 0);
	}


	//�����������Ƿ��л��� 
	//bool bNeedBuHua = false;
	//for(int i=0;i<PLAY_COUNT;i++)
	//{
	//	if(pDesk->sUserData.IsHuaPaiInHand(i))
	//	{
	//		bNeedBuHua = true;
	//		break;
	//	}
	//}

	//���벹���׶� ������û�л�
	nextID = THING_BEGIN_OUT;//THING_ALL_BUHUA;
	time = 50;

}
/*-------------------------------------------------------------------------------------------------*/
///��ȡ������	DWJ
void	ThingHandleEx::DisPatchCard()
{
	//����
	BYTE index=0;
	BYTE byAllCard[300][2];
	memset(byAllCard, 255, sizeof(byAllCard));

	if (pDesk->sGameData.m_mjRule.bHaveWan)//����
	{
		for (int j = 0; j < 9; j++)
		{
			byAllCard[index][0] = stcArr_A_Mj_W[j];
			byAllCard[index++][1] = 4;
		}
	}
	if (pDesk->sGameData.m_mjRule.bHaveBing)//�б�
	{
		for (int j = 0; j < 9; j++)
		{
			byAllCard[index][0] = stcArr_A_Mj_B[j];
			byAllCard[index++][1] = 4;
		}
	}
	if (pDesk->sGameData.m_mjRule.bHaveTiao)//����
	{
		for (int j = 0; j < 9; j++)
		{
			byAllCard[index][0] = stcArr_A_Mj_T[j];
			byAllCard[index++][1] = 4;
		}
	}
	if (pDesk->sGameData.m_mjRule.bHaveBaiBan)//�аװ�
	{
		byAllCard[index][0] = stcArr_A_Mj_ZI[0];
		byAllCard[index++][1] = 4;
	}
	if (pDesk->sGameData.m_mjRule.bHaveFaCai)//�з���
	{
		byAllCard[index][0] = stcArr_A_Mj_ZI[1];
		byAllCard[index++][1] = 4;
	}
	if (pDesk->sGameData.m_mjRule.bHaveHongZhong)//�к���
	{
		byAllCard[index][0] = stcArr_A_Mj_ZI[2];
		byAllCard[index++][1] = 4;
	}
	if (pDesk->sGameData.m_mjRule.bHaveFengPai)//�ж�������
	{
		for (int j = 0; j < 4; j++)
		{
			byAllCard[index][0] = stcArr_A_Mj_FENG[j];
			byAllCard[index++][1] = 4;
		}
	}

	if (pDesk->sGameData.m_mjRule.bHaveFlower)//�л���
	{
		for (int i = 0; i < 8; i++)
		{
			byAllCard[index][0] = stcArr_A_Mj_Other[i];
			byAllCard[index++][1] = 1;
		}
	}

	memset(pDesk->sUserData.m_MenPai.byMenPai, 255, sizeof(pDesk->sUserData.m_MenPai.byMenPai));

	CString s = CINIFile::GetAppPath();
	CINIFile f(s + SKIN_FOLDER + _T("_s.ini"));
	CString key = TEXT("game");
	CString sName = TEXT("setcard");
	BOOL iSetCard = f.GetKeyVal(key, sName, FALSE);

	BYTE card;
	BOOL isFind;
	BYTE pIndex = 0;

	key = TEXT("card");

	if (iSetCard) {
		for (int j = 0; j < 300; j++) {
			isFind = false;
			sName.Format("card_%d", j);
			card = f.GetKeyVal(key, sName, 255);
			if (card == 255 || card == 0) {
				break;
			}
			for (int k = 0; k < index; k++) {
				if (card == byAllCard[k][0]) {
					if (byAllCard[k][1] > 0) {
						isFind = true;
						pDesk->sUserData.m_MenPai.byMenPai[pIndex++] = byAllCard[k][0];
						byAllCard[k][1]--;
					}
					break;
				}
			}
			if (!isFind) {
				break;
			}
		}
	}

	//������������
	BYTE beginInx = pIndex;

	for (int i = 0; i < index; i++) {
		for (int j = 0; j < byAllCard[i][1]; j++) {
			pDesk->sUserData.m_MenPai.byMenPai[pIndex++] = byAllCard[i][0];
		}
	}

	//������
	srand(GetTickCount());
	BYTE temp=255,data=0;
	for(int i=beginInx;i<pIndex;i++)
	{
		temp = rand()%(pIndex -i)+i;
		data = pDesk->sUserData.m_MenPai.byMenPai[temp];
		pDesk->sUserData.m_MenPai.byMenPai[temp] = pDesk->sUserData.m_MenPai.byMenPai[i];
		pDesk->sUserData.m_MenPai.byMenPai[i] = data;
	}

	///////////////	DWJ???
//	pDesk->sUserData.m_MenPai.byGetPai = pDesk->sUserData.m_MenPai.byGetPai%13;
	//pDesk->sUserData.m_MenPai.byGetPaiDir = pDesk->sUserData.m_MenPai.byGetPaiDir%4;
	//if(pDesk->sUserData.m_MenPai.byGetPaiDir == 255)
	//{
	//	pDesk->sUserData.m_MenPai.byGetPaiDir = pDesk->sGameData.m_byNtStation;
	//}
	//pDesk->sUserData.m_MenPai.byGetPaiDir = pDesk->sUserData.m_MenPai.byGetPaiDir%4;

	int dun = 0,num=0;
	dun = pIndex/8;
	num = (dun*pDesk->sUserData.m_MenPai.byGetPaiDir + pDesk->sUserData.m_MenPai.byGetPai)*2;
	if(num == 0)
	{
		num=2;
	}
	pDesk->sUserData.m_MenPai.byStartIndex = iSetCard ? 0 : num;//������ʼ����
	pDesk->sUserData.m_MenPai.byEndIndex = iSetCard ? pIndex - 1 : (num - 1 + pIndex) % pIndex;	//���ƽ�������
	pDesk->sUserData.m_MenPai.byAllPaiNum = pIndex;//�����Ƶ�����
}
/*----------------------------------------------------------------------------------------------------*/
///������ץһ����
///@param station ץ����ҵ�λ�� , head  �Ƿ��ǰ��ץ,type ץ������ 0 ����ץ�ƣ�1��ʼǰ���ƣ�2��ǰ����ץ�ƣ�3����
BYTE ThingHandleEx::GetPai(int station,bool head,BYTE type,BYTE *pIndex)
{
	return ThingHandle::GetPai(station, head, type,pIndex);
}
/*----------------------------------------------------------------------------------------------------*/
///������ת����������,�������������е�����ת����ÿ����ҵ�����������
void ThingHandleEx::ChangeMenPai()
{
	for(int i=0;i<MEN_CARD_NUM;++i)//0λ�õ�����
	{
		if(pDesk->sUserData.m_MenPai.byMenPai[i] != 255)
		{
			pDesk->sUserData.m_iArMenPai[0][i] = 0;
		}
		else
		{
			pDesk->sUserData.m_iArMenPai[0][i] = 255;
		}
	}
	for(int i=MEN_CARD_NUM;i<(2*MEN_CARD_NUM);++i)//1λ�õ�����
	{
		if(pDesk->sUserData.m_MenPai.byMenPai[i] != 255)
		{
			pDesk->sUserData.m_iArMenPai[1][i-MEN_CARD_NUM] = 0;
		}
		else
		{
			pDesk->sUserData.m_iArMenPai[1][i-MEN_CARD_NUM] = 255;
		}
	}
	for(int i=(2*MEN_CARD_NUM);i<(3*MEN_CARD_NUM);++i)//2λ�õ�����
	{
		if(pDesk->sUserData.m_MenPai.byMenPai[i] != 255)
		{
			pDesk->sUserData.m_iArMenPai[2][i-(2*MEN_CARD_NUM)] = 0;
		}
		else
		{
			pDesk->sUserData.m_iArMenPai[2][i-(2*MEN_CARD_NUM)] = 255;
		}
	}
	for(int i=(3*MEN_CARD_NUM);i<(4*MEN_CARD_NUM);++i)//3λ�õ�����
	{
		if(pDesk->sUserData.m_MenPai.byMenPai[i] != 255)
		{
			pDesk->sUserData.m_iArMenPai[3][i-(3*MEN_CARD_NUM)] = 0;
		}
		else
		{
			pDesk->sUserData.m_iArMenPai[3][i-(3*MEN_CARD_NUM)] = 255;
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/
///������Ҳ����¼�	DWJ
void	ThingHandleEx::ExecuteAllBuHua(BYTE &nextID,BYTE &time)	
{
	pDesk->sGameData.m_byThingDoing = THING_ALL_BUHUA;

	//����ղ�������
	pDesk->sGameData.T_AllBuHua.Clear();
	
	for(int i=0;i<PLAY_COUNT;i++)
	{
		//if(!pDesk->sUserData.IsHuaPaiInHand(i))
		//{
		//	continue;
		//}
		//while(pDesk->sUserData.IsHuaPaiInHand(i))
		//{
		//	int num = pDesk->sUserData.MoveHuaPaiFormHand(i);
		//	for(int j=0;j<num;j++)
		//	{
		//		GetPai(i,false,1);//��ʼǰ����ץ��
		//	}
		//}

		//if(i == pDesk->sGameData.m_byNtStation)
		//{
		//	pDesk->sGameData.T_AllBuHua.m_byArHandPaiCount[i] = 14;
		//}
		//else
		//{
		//	pDesk->sGameData.T_AllBuHua.m_byArHandPaiCount[i] = 13;
		//}
	}

	//ȡ���ƺ� ��ʱת������
	ChangeMenPai();
	//��������
	for(int i=0;i<PLAY_COUNT;i++)
	{
		pDesk->sUserData.CopyHuaPai(i,pDesk->sGameData.T_AllBuHua.m_byArHuaPai[i]);
	}


	///����������
	for (int i=0;i<PLAY_COUNT;i++)
	{		
		pDesk->SendGameDataEx(i, &pDesk->sGameData.T_AllBuHua, sizeof(pDesk->sGameData.T_AllBuHua), MDM_GM_GAME_NOTIFY, THING_ALL_BUHUA, 0);
		pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_AllBuHua, sizeof(pDesk->sGameData.T_AllBuHua), MDM_GM_GAME_NOTIFY, THING_ALL_BUHUA, 0);
	}
	///��һ��ʱ����� ��ʼ�����¼�
	nextID = THING_BEGIN_OUT;
	time = 10;
	//ApplyAction(nextID,1500);
}
/*----------------------------------------------------------------------------------------------------*/
///��ʼ����֪ͨ�¼�	DWJ
void	ThingHandleEx::ExecuteBeginOut(BYTE &nextID,BYTE &time)
{    
	pDesk->sGameData.m_byThingDoing = THING_BEGIN_OUT;//��¼���ڷ������¼�


	///��ʼ����֪ͨ�¼� 
	pDesk->sGameData.T_BeginOutPai.byNt		= pDesk->sGameData.m_byNtStation;//ׯ��λ��
	pDesk->sGameData.T_BeginOutPai.byUser	= pDesk->sGameData.m_byNtStation;//ׯ��λ��
	pDesk->sUserData.m_byNowOutStation		= pDesk->sGameData.m_byNtStation;//����λ��

	//ת������
	ChangeMenPai();
	//��������
	for(int i=0;i<PLAY_COUNT;i++)
	{
		pDesk->sUserData.CopyMenPai(i,pDesk->sGameData.T_BeginOutPai.byMenPai[i]);//��������
		if(i == pDesk->sGameData.m_byNtStation)
		{
			pDesk->sGameData.T_BeginOutPai.m_byArHandPaiCount[i] = 14;
		}
		else
		{
			pDesk->sGameData.T_BeginOutPai.m_byArHandPaiCount[i] = 13;
		}
		//����������ҵ�����
		pDesk->sUserData.SortHandPai(i,false);
	}

	
	//����֪ͨ
	for (int i=0;i<PLAY_COUNT;i++)
	{	
		memset(pDesk->sGameData.T_BeginOutPai.m_byArHandPai,255,sizeof(pDesk->sGameData.T_BeginOutPai.m_byArHandPai));
		pDesk->sUserData.CopyHandPai(pDesk->sGameData.T_BeginOutPai.m_byArHandPai,i,false);
		pDesk->SendGameDataEx(i, &pDesk->sGameData.T_BeginOutPai, sizeof(pDesk->sGameData.T_BeginOutPai), MDM_GM_GAME_NOTIFY, THING_BEGIN_OUT, 0);
	}
	pDesk->SendWatchDataEx(PLAY_COUNT, &pDesk->sGameData.T_BeginOutPai, sizeof(pDesk->sGameData.T_BeginOutPai), MDM_GM_GAME_NOTIFY, THING_BEGIN_OUT, 0);


	//��⶯��
	if(CheckAction(pDesk->sGameData.m_byNtStation,pDesk->sUserData.GetLastHandPai(pDesk->sUserData.m_byNowOutStation),0))//֪ͨ���Ƽ�⶯��
	{
		//�����ץ�ƺ��ж���(�ͻ���������ʾ����ʱʱ���)
		pDesk->sGameData.T_CPGNotify[pDesk->sUserData.m_byNowOutStation].bZhuaPai	 = true;
		pDesk->SendGameDataEx(pDesk->sGameData.m_byNtStation, &pDesk->sGameData.T_CPGNotify ,sizeof(pDesk->sGameData.T_CPGNotify), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
		pDesk->SendWatchDataEx(pDesk->sGameData.m_byNtStation, &pDesk->sGameData.T_CPGNotify ,sizeof(pDesk->sGameData.T_CPGNotify), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);

		//����к��ƶ�����ô�����������Զ������ʱ��
		if(pDesk->sGameData.T_CPGNotify[pDesk->sGameData.m_byNtStation].bHu)
		{
			//û�ж��� ����ִ���¼� �Զ�������ʱ�����ʱ��
			SetDoingThing(pDesk->sGameData.m_byNtStation,THING_HU_PAI,pDesk->sGameData.m_mjRule.byOutTime);
		}
		else
		{
			//û�ж��� ����ִ���¼� �Զ�������ʱ�����ʱ��
			SetDoingThing(pDesk->sGameData.m_byNtStation,THING_BEGIN_OUT);
		}
		CString str;
		str.Format("********************%֪ͨׯ��%s��ʼ����,��⶯��********************", pDesk->m_pUserInfo[pDesk->sGameData.m_byNtStation]->m_UserData.szName);
		DebugPrintf(str);
		LogAction();
	}
	else
	{
		//û�ж��� ����ִ���¼� �Զ�������ʱ�����ʱ��
		SetDoingThing(pDesk->sGameData.m_byNtStation,THING_BEGIN_OUT);
	}
}

/*--------------------------------------------------------------------------------------------------*/
///������station��ǰ������Щ����	DWJ
///������station ���λ��,pai �����Ҵ�����ƣ�type ���� ���� 0 ץ�ƣ�1�ܿ���2 ���ڣ�3���� 4���ƺ���
bool ThingHandleEx::CheckAction(int station,BYTE pai,BYTE type)
{
	for(int i=0;i<PLAY_COUNT;++i)
	{
		pDesk->sGameData.T_CPGNotify[i].Clear();//����
	}

	bool action = false;
	switch(type)
	{
	case 0://����
	case 1://�ܿ�
		{
			//��
			if(pDesk->sCheckHuPai.CanHu(station,pai,pDesk->sGameData.T_CPGNotify[station].byHuType,true)/* && pDesk->sUserData.m_bTing[station]*/)
			{
				pDesk->sGameData.T_CPGNotify[station].bHu = true;
				pDesk->sGameData.T_CPGNotify[station].m_iHuPs = pDesk->sUserData.GetLastHandPai(station);
				pDesk->sGameData.T_CPGNotify[station].m_byDianPao = station;
			}
			//��(�����˾Ͳ��ܸ���)
			if(!pDesk->sUserData.m_bTing[station] && pDesk->sCPGAction.CanGang(station,pai,pDesk->sGameData.T_CPGNotify[station].m_iGangData ,true))
			{
				pDesk->sGameData.T_CPGNotify[station].bGang = true;
			}
			//��
			/*if(!pDesk->sUserData.m_bTing[station] && CanTingDWJ(station))
			{
				pDesk->sGameData.T_CPGNotify[station].bTing = true;
			}*/
			if(pDesk->sGameData.T_CPGNotify[station].bHu || pDesk->sGameData.T_CPGNotify[station].bGang || pDesk->sGameData.T_CPGNotify[station].bTing)
			{
				action=true;
				pDesk->sGameData.T_CPGNotify[station].bCanAction = true;
				pDesk->sGameData.T_CPGNotify[station].byUser = station;
				pDesk->sGameData.T_CPGNotify[station].byPs = pai;
			}
		}
		break;
	case 2://����
		{
			for(int i=0;i<PLAY_COUNT;++i)
			{
				if (pDesk->sUserData.m_bIsHu[i] || pDesk->sUserData.m_bFoceLeave[i])        // �Ѻ������,���߶���״̬
				{
					continue;
				}

				if(i==station)
				{
					continue;
				}
				//����¼��Ƿ��ܳ�
				//��
				if(!pDesk->sUserData.m_bTing[i] && GetNextStation(station)==i)
				{
					if(pDesk->sCPGAction.CanChi(i,pai,pDesk->sGameData.T_CPGNotify[i].m_iChi))
					{					
						pDesk->sGameData.T_CPGNotify[i].bChi = true;
						pDesk->sGameData.T_CPGNotify[i].m_byMaxThing = ACTION_CHI;
					}
				}
				//��
				if(!pDesk->sUserData.m_bTing[i] && pDesk->sCPGAction.CanPeng(i,pai))
				{	
					/*if (pDesk->sGameData.T_NoPeng[i].bHas(pai))
					{
						if (pDesk->sGameData.T_NoPeng[i].bCanPeng(pai))
						{
							pDesk->sGameData.T_CPGNotify[i].bPeng = true;
							pDesk->sGameData.T_CPGNotify[i].m_byMaxThing = ACTION_PENG;
						}		
					}
					else
					{
						pDesk->sGameData.T_NoPeng[i].add(pai);

						pDesk->sGameData.T_CPGNotify[i].bPeng = true;
						pDesk->sGameData.T_CPGNotify[i].m_byMaxThing = ACTION_PENG;
					}*/

					pDesk->sGameData.T_CPGNotify[i].bPeng = true;
					pDesk->sGameData.T_CPGNotify[i].m_byMaxThing = ACTION_PENG;
				}
				//��
				if(!pDesk->sUserData.m_bTing[i] && pDesk->sCPGAction.CanGang(i,pai,pDesk->sGameData.T_CPGNotify[i].m_iGangData,false))
				{
					pDesk->sGameData.T_CPGNotify[i].bGang = true;
					pDesk->sGameData.T_CPGNotify[i].m_byMaxThing = ACTION_MING_GANG;

				}
				//��
				//������� ���ܺ�
				if(!pDesk->sUserData.m_bQiHu[i] &&/* pDesk->sUserData.m_bTing[i] &&*/pDesk->sCheckHuPai.CanHu(i,pai,pDesk->sGameData.T_CPGNotify[i].byHuType,false))
				{
					/*if (pDesk->sGameData.T_NoHu[i].bHas(pai))
					{
						if (pDesk->sGameData.T_NoHu[i].bCanHu(pai))
						{
							pDesk->sGameData.T_CPGNotify[i].bHu = true;
							pDesk->sGameData.T_CPGNotify[i].m_byMaxThing = ACTION_HU;
							pDesk->sGameData.T_CPGNotify[i].m_iHuPs = pai;
							pDesk->sGameData.T_CPGNotify[i].m_byDianPao = station;
						}		
					}
					else
					{
						pDesk->sGameData.T_NoHu[i].add(pai);
						pDesk->sGameData.T_CPGNotify[i].bHu = true;
						pDesk->sGameData.T_CPGNotify[i].m_byMaxThing = ACTION_HU;
						pDesk->sGameData.T_CPGNotify[i].m_iHuPs = pai;
						pDesk->sGameData.T_CPGNotify[i].m_byDianPao = station;
					}*/
					pDesk->sGameData.T_CPGNotify[i].bHu = true;
					pDesk->sGameData.T_CPGNotify[i].m_byMaxThing = ACTION_HU;
					pDesk->sGameData.T_CPGNotify[i].m_iHuPs = pai;
					pDesk->sGameData.T_CPGNotify[i].m_byDianPao = station;
				}
				if(pDesk->sGameData.T_CPGNotify[i].bChi || pDesk->sGameData.T_CPGNotify[i].bHu || pDesk->sGameData.T_CPGNotify[i].bPeng || pDesk->sGameData.T_CPGNotify[i].bGang || pDesk->sGameData.T_CPGNotify[i].bTing)
				{
					action=true;
					pDesk->sGameData.T_CPGNotify[i].bCanAction = true;
					pDesk->sGameData.T_CPGNotify[i].byUser = station;
					pDesk->sGameData.T_CPGNotify[i].byPs = pai;
				}
			}
		}
		break;
	case 3://����
		{
			for(int i=0;i<PLAY_COUNT;++i)
			{
				if (pDesk->sUserData.m_bIsHu[i]|| pDesk->sUserData.m_bFoceLeave[i])        // �Ѻ������,���߶���״̬
				{
					continue;
				}
				if(i==station)
				{
					//�ָ�������ҵĲ��ܶ���
					/*pDesk->sGameData.T_CPGNotify[i].m_byMaxThing = ACTION_BU_GANG;
					pDesk->sGameData.T_CPGNotify[i].bCanAction = true;
					pDesk->sGameData.T_CPGNotify[i].bHaveReturn = true;*/
					continue;
				}
				if(pDesk->sUserData.m_bQiHu[i] )
				{
					OutputDebugString("���ܼ�⣺�������������ܺ�");
				}
				//�� ������ �������ܺ�
				if(!pDesk->sUserData.m_bQiHu[i] &&/* pDesk->sUserData.m_bTing[i] && */pDesk->sCheckHuPai.CanHu(i,pai,pDesk->sGameData.T_CPGNotify[i].byHuType,false))
				{
					//������������
					pDesk->sCheckHuPai.SetAHupaiType(HUPAI_TYPE_QIANG_GANG, pDesk->sGameData.T_CPGNotify[i].byHuType);
		
					pDesk->sGameData.T_CPGNotify[i].bHu = true;
					pDesk->sGameData.T_CPGNotify[i].m_iHuPs = pai;//��¼������
					pDesk->sGameData.T_CPGNotify[i].m_byDianPao = station;		
					pDesk->sGameData.T_CPGNotify[i].bQiangGang = true; //���ܺ�

					pDesk->sGameData.T_CPGNotify[i].m_byMaxThing = ACTION_HU;
					action=true;
					pDesk->sGameData.T_CPGNotify[i].bCanAction = true;
					pDesk->sGameData.T_CPGNotify[i].byUser = station;
					pDesk->sGameData.T_CPGNotify[i].byPs = pai;
				}
			}
		}
		break;
	case 4:	//���ƺ���(���ƺ�ֻ�����͸� ���ܺ�)
		{
			//��(�����˾Ͳ��ܸ���)
			if(!pDesk->sUserData.m_bTing[station] && pDesk->sCPGAction.CanGang(station,pai,pDesk->sGameData.T_CPGNotify[station].m_iGangData ,true))
			{
				pDesk->sGameData.T_CPGNotify[station].bGang = true;
			}
			/*if(!pDesk->sUserData.m_bTing[station])
			{
				if(CanTingDWJ(station))
				{
					pDesk->sGameData.T_CPGNotify[station].bTing = true;
				}
			}*/
			if(pDesk->sGameData.T_CPGNotify[station].bGang || pDesk->sGameData.T_CPGNotify[station].bTing)
			{
				action=true;
				pDesk->sGameData.T_CPGNotify[station].bCanAction = true;
			}
			break;
		}
	}
	if(action)
	{
		return true;
	}
	return false;
}
/*--------------------------------------------------------------------------------------------------*/
//����ܷ�����	DWJ
bool	ThingHandleEx::CanTingDWJ(BYTE byDeskStation)
{
	if(byDeskStation < 0 || byDeskStation >= PLAY_COUNT)
	{
		return false;
	}
	//�ȿ�����������
	BYTE	byUserHandCards[HAND_CARD_NUM] = {0};
	memcpy(byUserHandCards, &pDesk->sUserData.m_byArHandPai[byDeskStation],sizeof(byUserHandCards));

	int iCardCount = pDesk->sUserData.GetHandPaiCount(byDeskStation);

	BYTE	byTingCanOut[HAND_CARD_NUM];//�����ܴ����
	memset(byTingCanOut,255,sizeof(byTingCanOut));

	BYTE	byDelValue = 255;
	for(int i = 0; i< iCardCount; i++)
	{
		memcpy(&pDesk->sUserData.m_byArHandPai[byDeskStation], byUserHandCards, sizeof(pDesk->sUserData.m_byArHandPai[byDeskStation]));
		//��ȥ��һ���� �ж��ܷ����� 
		byDelValue	= pDesk->sUserData.m_byArHandPai[byDeskStation][i];
		pDesk->sUserData.m_byArHandPai[byDeskStation][i] = 255;
		//����ҵ�������
		pDesk->sUserData.SortHandPai(i,false);

		//�����ж��ܷ�����
		if(pDesk->sGameData.m_mjAction.bTing && !pDesk->sUserData.m_bTing[byDeskStation])//���û������
		{
			//pDesk->sGameData.T_CPGNotify[byDeskStation].bTing = pDesk->sCheckHuPai.CanTing(byDeskStation,pDesk->sGameData.T_CPGNotify[byDeskStation].m_byTingCanOut);
			if(pDesk->sCheckHuPai.CanTing(byDeskStation,pDesk->sGameData.T_CPGNotify[byDeskStation].m_byTingCanOut))
			{
				for(int x=0; x<HAND_CARD_NUM;x++)
				{
					if(byTingCanOut[x] == 255)
					{
						byTingCanOut[x] = byDelValue;
						break;
					}
				}
				//break;
			}
			else
			{

			}
		}
	}

	//���������ܴ���Ƶ�����
	memcpy(pDesk->sGameData.T_CPGNotify[byDeskStation].m_byTingCanOut, byTingCanOut, sizeof(pDesk->sGameData.T_CPGNotify[byDeskStation].m_byTingCanOut));
	//���ԭ��ҵ�ԭʼ������
	memcpy(&pDesk->sUserData.m_byArHandPai[byDeskStation], byUserHandCards, sizeof(pDesk->sUserData.m_byArHandPai[byDeskStation]));

	//�ж��ܷ�����
	for(int i=0; i<HAND_CARD_NUM;i++)
	{
		if(pDesk->sGameData.T_CPGNotify[byDeskStation].m_byTingCanOut[i] != 255)
		{
			pDesk->sGameData.T_CPGNotify[byDeskStation].bCanAction = true;
			pDesk->sGameData.T_CPGNotify[byDeskStation].bTing = true;
			return true;
		}
	}
	return false;
}
/*--------------------------------------------------------------------------------------------------*/
///����������Ϣ�����	DWJ
bool	ThingHandleEx::HaveUserCanDoAction(BYTE byIgnoreStation)
{
	bool bHaveSend = false;	//�Ƿ��Ѿ���������Ϣ
	BYTE byCanActionDesk = 255;	//���������������
	tagHaveAction haveAccion;
	if(!bHaveSend)
	{
		//�������ȼ��������ȷ�
		for(int i=0;i<PLAY_COUNT;i++)
		{
			if(i == byIgnoreStation || pDesk->sUserData.m_bFoceLeave[i])
			{
				continue;
			}

			//���ȸ��ܺ��Ƶ���ҷ��Ͷ�����Ϣ 
			if(pDesk->sGameData.T_CPGNotify[i].bHu)
			{
				haveAccion.byStation = pDesk->sGameData.T_CPGNotify[i].byUser;
				pDesk->SendGameDataEx(i, &pDesk->sGameData.T_CPGNotify, sizeof(pDesk->sGameData.T_CPGNotify), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
				pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_CPGNotify, sizeof(pDesk->sGameData.T_CPGNotify), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
				byCanActionDesk = i;
				bHaveSend = true;
				break;
			}
		}
		if(bHaveSend)
		{
			for(int i = 0; i < PLAY_COUNT; i++)
			{
				if(pDesk->sGameData.T_CPGNotify[i].bHu)
				{
					continue;
				}
				pDesk->SendGameDataEx(i, &haveAccion, sizeof(tagHaveAction), MDM_GM_GAME_NOTIFY, THING_HAVE_ACTION, 0);
			}
			SetDoingThing(byCanActionDesk,THING_HU_PAI);//����ִ���¼�
		}
		
	}
	//û�з��ͺ�����Ϣ ��ô�����ȷ��͸� ����������Ϣ
	if(!bHaveSend)
	{
		//�������ȼ��������ȷ�
		for(int i=0;i<PLAY_COUNT;i++)
		{
			if(i == byIgnoreStation || pDesk->sUserData.m_bFoceLeave[i])
			{
				continue;
			}
			//�����ȸ��ܸܡ����Ƶ���ҷ��Ͷ�����Ϣ 
			if(pDesk->sGameData.T_CPGNotify[i].bGang || pDesk->sGameData.T_CPGNotify[i].bPeng)
			{
				haveAccion.byStation = pDesk->sGameData.T_CPGNotify[i].byUser;
				pDesk->SendGameDataEx(i, &pDesk->sGameData.T_CPGNotify, sizeof(pDesk->sGameData.T_CPGNotify), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
				pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_CPGNotify, sizeof(pDesk->sGameData.T_CPGNotify), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
				byCanActionDesk = i;
				bHaveSend = true;
				break;
			}
		}
		if(bHaveSend)
		{
			for(int i = 0; i < PLAY_COUNT; i++)
			{
				if(pDesk->sGameData.T_CPGNotify[i].bGang || pDesk->sGameData.T_CPGNotify[i].bPeng)
				{
					continue;
				}
				pDesk->SendGameDataEx(i, &haveAccion, sizeof(tagHaveAction), MDM_GM_GAME_NOTIFY, THING_HAVE_ACTION, 0);
			}
			SetDoingThing(byCanActionDesk,THING_GANG_PAI);//����ִ���¼�
		}
	}

	//û�з��ͺ����ܡ�����Ϣ �ټ�鷢�ͳ�����Ϣ
	if(!bHaveSend)
	{
		//�������ȼ��������ȷ�
		for(int i=0;i<PLAY_COUNT;i++)
		{
			if(i == byIgnoreStation || pDesk->sUserData.m_bFoceLeave[i])
			{
				continue;
			}
			//�����ȸ��ܸܡ����Ƶ���ҷ��Ͷ�����Ϣ 
			if(pDesk->sGameData.T_CPGNotify[i].bChi)
			{
				haveAccion.byStation = pDesk->sGameData.T_CPGNotify[i].byUser;
				pDesk->SendGameDataEx(i, &pDesk->sGameData.T_CPGNotify, sizeof(pDesk->sGameData.T_CPGNotify), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
				pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_CPGNotify, sizeof(pDesk->sGameData.T_CPGNotify), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
				byCanActionDesk = i;
				bHaveSend = true;
				break;
			}
		}
		if(bHaveSend)
		{
			for(int i = 0; i < PLAY_COUNT; i++)
			{
				if(pDesk->sGameData.T_CPGNotify[i].bChi)
				{
					continue;
				}
				pDesk->SendGameDataEx(i, &haveAccion, sizeof(tagHaveAction), MDM_GM_GAME_NOTIFY, THING_HAVE_ACTION, 0);
			}
			SetDoingThing(byCanActionDesk,THING_CHI_PAI);//����ִ���¼�
		}
	}

	return bHaveSend;
}
/*--------------------------------------------------------------------------------------------------*/
///ץ���¼�
void	ThingHandleEx::ExecuteZhuaPai(BYTE &nextID,BYTE &time)	
{
	///ץ�����¼�
	nextID = 255;
	BYTE card = 255;
	if (pDesk->sUserData.m_MenPai.GetMenPaiNum() <= pDesk->sGameData.m_mjRule.byGamePassNum)
	{
		//������պ�����Ϣ
		pDesk->sGameData.T_HuPai.Clear();
		//ץ������ ��ֽ�����Ϸ
		nextID = THING_COUNT_FEN;
		time = 2;
	}
	else
	{
		switch(pDesk->sGameData.m_byThingDoing){
		case THING_OUT_PAI:
		case THING_HU_PAI:
			{
				pDesk->sUserData.m_byNowOutStation = GetNextStation(pDesk->sGameData.T_OutPai.byUser);
				pDesk->sUserData.m_bZhuaPaiDir = true;
				break;
			}
		case THING_GANG_PAI:
			{
				pDesk->sUserData.m_byNowOutStation = pDesk->sGameData.T_GangPai.byUser;
				pDesk->sUserData.m_bZhuaPaiDir = false;
				break;
			}
		case THING_ONE_BUHUA:
			{
				pDesk->sUserData.m_byNowOutStation = pDesk->sGameData.T_OneBuHua.byUser;
				pDesk->sUserData.m_bZhuaPaiDir = false;
				break;
			}
		default:
			{
				return;
			}
		}

		pDesk->sGameData.m_byThingDoing = THING_ZHUA_PAI;//��¼���ڷ������¼�

		//����ץ������
		pDesk->sGameData.T_ZhuaPai.Clear();

		pDesk->sGameData.T_ZhuaPai.byUser = pDesk->sUserData.m_byNowOutStation;
		card = GetPai(pDesk->sUserData.m_byNowOutStation,pDesk->sUserData.m_bZhuaPaiDir,0,&pDesk->sGameData.T_ZhuaPai.byGetPaiIndex);//����ץ��
		pDesk->sGameData.T_ZhuaPai.byPs = card;		//ץ�Ƶ�ֵ

		//ץ������ǿ�ƽ���
		if(card==255 && (pDesk->sUserData.m_MenPai.GetMenPaiNum())<=pDesk->sGameData.m_mjRule.byGamePassNum)
		{
			//������պ�����Ϣ
			pDesk->sGameData.T_HuPai.Clear();

			//ץ������ ��ֽ�����Ϸ
			nextID = THING_COUNT_FEN;
			time = 2;
			
			return;
		}


		ChangeMenPai();//ת������

		for(int i=0;i<PLAY_COUNT;i++)
		{
			//��������
			pDesk->sUserData.CopyMenPai(i,pDesk->sGameData.T_ZhuaPai.byMenPai[i]);
			//�����������
			pDesk->sGameData.T_ZhuaPai.m_byArHandPaiCount[i] = pDesk->sUserData.GetHandPaiCount(i);
		}

		//����ץ������
		for (int i=0;i<PLAY_COUNT;i++)
		{			
			//��������
			memset(pDesk->sGameData.T_ZhuaPai.m_byArHandPai,255,sizeof(pDesk->sGameData.T_ZhuaPai.m_byArHandPai));
			pDesk->sUserData.CopyHandPai(pDesk->sGameData.T_ZhuaPai.m_byArHandPai,i,true);
			
			pDesk->SendGameDataEx(i, &pDesk->sGameData.T_ZhuaPai, sizeof(pDesk->sGameData.T_ZhuaPai), MDM_GM_GAME_NOTIFY, THING_ZHUA_PAI, 0);
			pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_ZhuaPai, sizeof(pDesk->sGameData.T_ZhuaPai), MDM_GM_GAME_NOTIFY, THING_ZHUA_PAI, 0);
		}

		//�������
		if (!CheckAction(pDesk->sUserData.m_byNowOutStation, card, 0))//ץ�Ƽ�⶯��
		{
			if (pDesk->sUserData.m_bTuoGuan[pDesk->sUserData.m_byNowOutStation] || pDesk->sUserData.m_bTing[pDesk->sUserData.m_byNowOutStation])
			{
				//�йܻ������Զ�����
				ApplyAction(THING_AUTOOUTCARD, 2000);
			}
			else
			{
				//û�ж��� ��ô���������Ƽ�ʱ��
				SetDoingThing(pDesk->sUserData.m_byNowOutStation, THING_OUT_PAI);
			}
		}
		else
		{
			//����Ǻ��� ��ô���� �Զ�������Ӧ��ʱ��
			if(pDesk->sGameData.T_CPGNotify[pDesk->sUserData.m_byNowOutStation].bHu)
			{
				if (pDesk->sUserData.m_bTing[pDesk->sUserData.m_byNowOutStation])
				{
					tagHuPaiEx hu;
					hu.Clear();
					hu.byUser = pDesk->sUserData.m_byNowOutStation;
					ReceiveUserHuCard(pDesk->sUserData.m_byNowOutStation, &hu, sizeof(hu), false);
					return;
				}
				else
				{
					SetDoingThing(pDesk->sUserData.m_byNowOutStation, THING_HU_PAI, pDesk->sGameData.m_mjRule.byOutTime);
				}
			}
			else //�������� ������ �Զ����Ƽ�ʱ��
			{
				SetDoingThing(pDesk->sUserData.m_byNowOutStation,THING_OUT_PAI,pDesk->sGameData.m_mjRule.byOutTime);
			}
			//�����ץ�ƺ��ж���(�ͻ���������ʾ����ʱʱ���)
			pDesk->sGameData.T_CPGNotify[pDesk->sUserData.m_byNowOutStation].bZhuaPai = true;
			pDesk->SendGameDataEx(pDesk->sUserData.m_byNowOutStation, &pDesk->sGameData.T_CPGNotify, sizeof(pDesk->sGameData.T_CPGNotify), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
			pDesk->SendWatchDataEx(pDesk->sUserData.m_byNowOutStation, &pDesk->sGameData.T_CPGNotify, sizeof(pDesk->sGameData.T_CPGNotify), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
			
			CString str;
			str.Format("********************%sץ��%d,��⶯��********************", pDesk->m_pUserInfo[pDesk->sUserData.m_byNowOutStation]->m_UserData.szName, card);
			DebugPrintf(str);
			LogAction();
		}
	}

	//20131218
//	����ץ�ƺͲ������ж�������ʱ�����--�ͻ�����ʾ����ͷ���˴������

	//��¼����״̬��ӵ�ڸܿ��͸ܺ���
	for(int i=0;i<PLAY_COUNT;++i)
	{
		if(i != pDesk->sUserData.m_byNowOutStation)
		{
			pDesk->sGameData.m_bGangState[i] = false;
		}
	}

	pDesk->sGameData.T_NoPeng[pDesk->sUserData.m_byNowOutStation].clr();
	pDesk->sGameData.T_NoHu[pDesk->sUserData.m_byNowOutStation].clr();

// 	CString str;
// 	str.Format("chenlog----------���[%d]���ƣ������������Ϣ",pDesk->sUserData.m_byNowOutStation);
// 	OutputDebugString(str);
}

void  ThingHandleEx::ExecuteBuHua(BYTE byDeskStation,BYTE byCard)
{
	pDesk->sGameData.m_byThingDoing = THING_ONE_BUHUA;
	//��ղ�������
	pDesk->sGameData.T_OneBuHua.Clear();
	///������Ҳ�����λ�ü�ץ����ҵ�λ��
	pDesk->sGameData.T_OneBuHua.byUser = byDeskStation;//pDesk->sGameData.T_ZhuaPai.byUser;
	pDesk->sGameData.T_OneBuHua.byPs = byCard;

	pDesk->sUserData.MoveHuaPaiFormHand(byDeskStation,byCard);
	pDesk->sGameData.m_bGangState[byDeskStation] = true;
	pDesk->sGameData.m_byLianGang++;
	pDesk->sGameData.m_byGangHua++;

	for(int i=0;i<PLAY_COUNT;i++)
	{
		//��������
		pDesk->sUserData.CopyHuaPai(i,pDesk->sGameData.T_OneBuHua.m_byArHuaPai[i]);
		//��������
		pDesk->sGameData.T_OneBuHua.m_byArHandPaiCount[i] = pDesk->sUserData.GetHandPaiCount(i);
	}
	///����������
	for (int i=0;i<PLAY_COUNT;i++)
	{			
		memset(pDesk->sGameData.T_OneBuHua.m_byArHandPai,255,sizeof(pDesk->sGameData.T_OneBuHua.m_byArHandPai));
		pDesk->sUserData.CopyHandPai(pDesk->sGameData.T_OneBuHua.m_byArHandPai,i,true);
		pDesk->SendGameDataEx(i, &pDesk->sGameData.T_OneBuHua, sizeof(pDesk->sGameData.T_OneBuHua), MDM_GM_GAME_NOTIFY, THING_ONE_BUHUA, 0);
		pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_OneBuHua, sizeof(pDesk->sGameData.T_OneBuHua), MDM_GM_GAME_NOTIFY, THING_ONE_BUHUA, 0);
	}
	ApplyAction(THING_ZHUA_PAI,100);
}
/*--------------------------------------------------------------------------------------------------*/
///������Ҳ����¼�
void	ThingHandleEx::ExecuteOneBuHua(BYTE &nextID,BYTE &time)
{	
	nextID = THING_ZHUA_PAI;
	time = 5;
	pDesk->sGameData.m_byThingDoing = THING_ONE_BUHUA;
	
	//��ղ�������
	pDesk->sGameData.T_OneBuHua.Clear();
	///������Ҳ�����λ�ü�ץ����ҵ�λ��
	pDesk->sGameData.T_OneBuHua.byUser = pDesk->sUserData.m_byNowOutStation;//pDesk->sGameData.T_ZhuaPai.byUser;

	pDesk->sUserData.MoveHuaPaiFormHand(pDesk->sUserData.m_byNowOutStation,pDesk->sUserData.m_byNeedBuHua);

	for(int i=0;i<PLAY_COUNT;i++)
	{
		//��������
		pDesk->sUserData.CopyHuaPai(i,pDesk->sGameData.T_OneBuHua.m_byArHuaPai[i]);
		//��������
		//pDesk->sUserData.CopyMenPai(i,pDesk->sGameData.T_OneBuHua.byMenPai[i]);

		//��������
		pDesk->sGameData.T_OneBuHua.m_byArHandPaiCount[i] = pDesk->sUserData.GetHandPaiCount(i);
		
	}
	///����������
	for (int i=0;i<PLAY_COUNT;i++)
	{			
		memset(pDesk->sGameData.T_OneBuHua.m_byArHandPai,255,sizeof(pDesk->sGameData.T_OneBuHua.m_byArHandPai));
		pDesk->sUserData.CopyHandPai(pDesk->sGameData.T_OneBuHua.m_byArHandPai,i,true);
		pDesk->SendGameDataEx(i, &pDesk->sGameData.T_OneBuHua, sizeof(pDesk->sGameData.T_OneBuHua), MDM_GM_GAME_NOTIFY, THING_ONE_BUHUA, 0);
		pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_OneBuHua, sizeof(pDesk->sGameData.T_OneBuHua), MDM_GM_GAME_NOTIFY, THING_ONE_BUHUA, 0);
	}
	//ApplyAction(THING_ZHUA_PAI,50);
	//�������
	//if(!CheckAction(pDesk->sUserData.m_byNowOutStation,pDesk->sGameData.T_OneBuHua.byPs,0))
	//{
	//	//û�ж��� ��ô���������Ƽ�ʱ��
	//	SetDoingThing(pDesk->sUserData.m_byNowOutStation,THING_OUT_PAI);
	//}
	//else
	//{
	//	//��Ϊ��ץ���ж��� ��������˼��ʱ���ǳ���ʱ��
	//	//pDesk->sGameData.T_CPGNotify[pDesk->sUserData.m_byNowOutStation].byBlockTime = pDesk->sGameData.m_mjRule.byOutTime;
	//	//�����ץ�ƺ��ж���(�ͻ���������ʾ����ʱʱ���)
	//	pDesk->sGameData.T_CPGNotify[pDesk->sUserData.m_byNowOutStation].bZhuaPai	 = true;
	//	pDesk->SendGameDataEx(pDesk->sUserData.m_byNowOutStation, &pDesk->sGameData.T_CPGNotify, sizeof(pDesk->sGameData.T_CPGNotify), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
	//	pDesk->SendWatchDataEx(pDesk->sUserData.m_byNowOutStation, &pDesk->sGameData.T_CPGNotify, sizeof(pDesk->sGameData.T_CPGNotify), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);


	//	//����Ǻ��� ��ô���� �Զ�������Ӧ��ʱ��
	//	if(pDesk->sGameData.T_CPGNotify[pDesk->sUserData.m_byNowOutStation].bHu)
	//	{
	//		SetDoingThing(pDesk->sUserData.m_byNowOutStation,THING_HU_PAI,pDesk->sGameData.m_mjRule.byOutTime);
	//	}
	//	else //�������� ������ �Զ����Ƽ�ʱ��
	//	{
	//		SetDoingThing(pDesk->sUserData.m_byNowOutStation,THING_OUT_PAI,pDesk->sGameData.m_mjRule.byOutTime);
	//	}
	//}
}

/*--------------------------------------------------------------------------------------------------*/
///����¼�
void	ThingHandleEx::ExecuteCountFen(BYTE &nextID,BYTE &time)
{	
	//��¼����ִ�е��¼�
	pDesk->sGameData.m_byThingDoing = THING_COUNT_FEN;

	pDesk->sGameData.T_CountFen.bIsLiuJu	= pDesk->sGameData.T_HuPai.bIsLiuJu;		//�Ƿ�����
	pDesk->sGameData.T_CountFen.bZiMo		= pDesk->sGameData.T_HuPai.bZimo;			//�Ƿ�����
	pDesk->sGameData.T_CountFen.byUser		= pDesk->sGameData.T_HuPai.byUser;			//�������λ��
	pDesk->sGameData.T_CountFen.byUserNum	= pDesk->sGameData.T_HuPai.byUserNum;		//������ҵĸ���	
	pDesk->sGameData.T_CountFen.byDianPao	= pDesk->sGameData.T_HuPai.byDianPao;		//������ҵ�λ��
	pDesk->sGameData.T_CountFen.bQiangGang	= pDesk->sGameData.T_HuPai.bQiangGang;		//�Ƿ�����
	pDesk->sGameData.T_CountFen.byHuUserNum	= pDesk->sGameData.T_HuPai.byUserNum;		//������ҵĸ���
	pDesk->sGameData.T_CountFen.bGangKai	= pDesk->sGameData.T_HuPai.bGangKai;		//�Ǹܿ�
	pDesk->sGameData.T_CountFen.iBase		= pDesk->m_iBase;
	pDesk->sGameData.T_CountFen.iFanBase	= pDesk->m_iFanBase;
	for(int i=0;i<PLAY_COUNT;i++)
	{
		//��¥���
		pDesk->sGameData.T_CountFen.bMingPai[i] = pDesk->sUserData.m_bTing[i];
		//���Ƶ����
		pDesk->sGameData.T_CountFen.m_bIsHu[i] = pDesk->sGameData.T_HuPai.bHaveHu[i];
		//��������
		for(int j=0;j<MAX_HUPAI_TYPE;j++)
		{
			pDesk->sGameData.T_CountFen.byHuType[i][j] = pDesk->sGameData.T_HuPai.byHuType[i][j];
		}
	}
	//�׷�
	int iBase = pDesk->m_iBase;
	int iFanBase = pDesk->m_iFanBase;
	//����
	if(pDesk->sGameData.T_HuPai.bIsLiuJu)
	{
		for(int i=0; i<PLAY_COUNT; i++)
		{
			pDesk->sGameData.T_CountFen.iZongFen[i] = 0;
		}
		//������Ҷ����۷� ֻ��ȡ ̨��
		for(int i=0; i<PLAY_COUNT; i++)
		{
			pDesk->sGameData.T_CountFen.iZongFen[i] = 0;
		}
		//��һ���¼�����Ϸ�����¼�
		nextID = THING_ENG_HANDLE;
		time = 5;
	}
	else
	{
		//��һ���¼�����Ϸ�����¼�
		nextID = THING_ENG_HANDLE;
		time = 5;
		//��ׯ������0
		pDesk->sGameData.m_iHuangZhuangCount = 0;
		int iHuaCount	= 0;	//������
		int iFanCount	= 0;	//����
		int iZongFen	= 0;	//�ܷ�

		//ֻ��һ���˺���
		if(1 == pDesk->sGameData.T_HuPai.byUserNum)
		{
			DebugPrintf("*******************��ʼ���*********************");

			//���������ҷ����ͻ���
			CountFanAndHua(pDesk->sGameData.T_HuPai.byUser,iHuaCount, iFanCount);
			//���� and ����
			pDesk->sGameData.T_CountFen.iFanCount[pDesk->sGameData.T_HuPai.byUser] = iFanCount;
			pDesk->sGameData.T_CountFen.iHuaCount[pDesk->sGameData.T_HuPai.byUser] = iHuaCount;
			//������ҵ��ܷ�
			iZongFen = iBase + (iHuaCount+iFanCount)*iFanBase;

			CString str;
			str.Format("�����֣�%d�����ʣ�%d�����Ʒ�����%d�����÷�����%d���ܷ�����%d", iBase, iFanBase, iFanCount, iHuaCount,iZongFen);
			DebugPrintf_debug(str);

			DebugPrintf("*******************��ֽ���*********************");

			//�Ƿ�����
			if(pDesk->sGameData.T_CountFen.bZiMo)
			{
				for(int i=0; i<PLAY_COUNT; i++)
				{
					if(i == pDesk->sGameData.T_HuPai.byUser)
					{
						continue;
					}	
					pDesk->sGameData.T_CountFen.iZongFen[i] -= (iZongFen);

					if(pDesk->sUserData.m_byChengBao[i][pDesk->sGameData.T_HuPai.byUser] > 2)//������Ǯ
					{
						pDesk->sGameData.T_CountFen.huDetail.byFanBao[i] = pDesk->sGameData.T_HuPai.byUser;
						pDesk->sGameData.T_CountFen.iFanCount[i] = iFanCount;
						pDesk->sGameData.T_CountFen.iHuaCount[i] = iHuaCount;

						int iBaoBase = 0;
						if (pDesk->sUserData.m_byPengChengBao[i][pDesk->sGameData.T_HuPai.byUser] == 4)
						{
							iBaoBase = 40*iFanBase;
							pDesk->sGameData.T_CountFen.byFanBaoType[i] = e_FAN_PENG_4;
						}
						else if (pDesk->sUserData.m_byPengChengBao[i][pDesk->sGameData.T_HuPai.byUser] == 3)
						{
							iBaoBase = 20*iFanBase;
							pDesk->sGameData.T_CountFen.byFanBaoType[i] = e_FAN_PENG_3;
						}

						else if (pDesk->sUserData.m_byPengChengBao[i][pDesk->sGameData.T_HuPai.byUser] < 3)
						{
							if(pDesk->sUserData.m_byChengBao[i][pDesk->sGameData.T_HuPai.byUser] == 4)
							{
								iBaoBase = 20*iFanBase;
								pDesk->sGameData.T_CountFen.byFanBaoType[i] = e_FAN_CHI_4;
							}
							else if(pDesk->sUserData.m_byChengBao[i][pDesk->sGameData.T_HuPai.byUser] == 3)
							{
								iBaoBase = 10*iFanBase;
								pDesk->sGameData.T_CountFen.byFanBaoType[i] = e_FAN_CHI_3;
							}
						}


						pDesk->sGameData.T_CountFen.iZongFen[i]-= iBaoBase ;
						pDesk->sGameData.T_CountFen.iZongFen[pDesk->sGameData.T_HuPai.byUser] += iBaoBase;

						pDesk->sGameData.T_CountFen.iFanBaoFen[i] = iBaoBase;

						CString str;
						str.Format("chenlog---------Server  ���� ���[%d]  ������[%d] ����[%d] ����[%d]  ",
							i,pDesk->sGameData.T_HuPai.byUser,pDesk->sUserData.m_byPengChengBao[i][pDesk->sGameData.T_HuPai.byUser]
						,pDesk->sUserData.m_byChengBao[i][pDesk->sGameData.T_HuPai.byUser]);
						OutputDebugStringA(str);
					}
					if(pDesk->sUserData.m_byChengBao[pDesk->sGameData.T_HuPai.byUser][i] > 2)//˳����Ǯ
					{
						pDesk->sGameData.T_CountFen.huDetail.byShunBao[i] = pDesk->sGameData.T_HuPai.byUser;
						pDesk->sGameData.T_CountFen.iFanCount[i] = iFanCount;
						pDesk->sGameData.T_CountFen.iHuaCount[i] = iHuaCount;

						int iBaoBase = 0;
						if (pDesk->sUserData.m_byPengChengBao[pDesk->sGameData.T_HuPai.byUser][i] == 4)
						{
							iBaoBase = 20*iFanBase;
							pDesk->sGameData.T_CountFen.byShunBaoType[i] = e_SHUN_PENG_4;
						}
						else if (pDesk->sUserData.m_byPengChengBao[pDesk->sGameData.T_HuPai.byUser][i] == 3)
						{
							iBaoBase = 10*iFanBase;
							pDesk->sGameData.T_CountFen.byShunBaoType[i] = e_SHUN_PENG_3;
						}
						else if (pDesk->sUserData.m_byPengChengBao[pDesk->sGameData.T_HuPai.byUser][i] < 3)
						{
							if(pDesk->sUserData.m_byChengBao[pDesk->sGameData.T_HuPai.byUser][i] == 4)
							{
								iBaoBase = 10*iFanBase;
								pDesk->sGameData.T_CountFen.byShunBaoType[i] = e_SHUN_CHI_4;
							}
							else if(pDesk->sUserData.m_byChengBao[pDesk->sGameData.T_HuPai.byUser][i] == 3)
							{
								iBaoBase = 5*iFanBase;
								pDesk->sGameData.T_CountFen.byShunBaoType[i] = e_SHUN_CHI_3;
							}
						}


						pDesk->sGameData.T_CountFen.iZongFen[i]-= iBaoBase;
						pDesk->sGameData.T_CountFen.iZongFen[pDesk->sGameData.T_HuPai.byUser] += iBaoBase;

						pDesk->sGameData.T_CountFen.iShunBaoFen[i] = iBaoBase;

						CString str;
						str.Format("chenlog---------Server  ˳�� ���[%d]  ������[%d] ����[%d] ����[%d]  ",
							i,pDesk->sGameData.T_HuPai.byUser,pDesk->sUserData.m_byPengChengBao[pDesk->sGameData.T_HuPai.byUser][i]
						,pDesk->sUserData.m_byChengBao[pDesk->sGameData.T_HuPai.byUser][i]);
						OutputDebugStringA(str);
					}
				}
				//������ҵĵ÷�
				pDesk->sGameData.T_CountFen.iZongFen[pDesk->sGameData.T_HuPai.byUser] += (3*iZongFen);		
			}
			else	//��������
			{
				//������ҵĵ÷�
				pDesk->sGameData.T_CountFen.iZongFen[pDesk->sGameData.T_HuPai.byDianPao] -= (iZongFen);
				pDesk->sGameData.T_CountFen.iZongFen[pDesk->sGameData.T_HuPai.byUser] += iZongFen;
			}
			//������� �¾ֵ�ׯ
			pDesk->sGameData.m_byNtStation = pDesk->sGameData.T_HuPai.byUser;
		}
		else	//һ�ڶ���
		{
			for(int i=0; i<PLAY_COUNT; i++)
			{
				if(i == pDesk->sGameData.T_HuPai.byDianPao)
				{
					continue;
				}
				pDesk->sGameData.m_byNtStation = i;
				//��ʼ������
				iHuaCount  = 0;	//������
				iFanCount  = 0;  //����
				iZongFen	= 0;//�ܷ�

				if(pDesk->sGameData.T_HuPai.bHaveHu[i])
				{
					//���㷬���ͻ���
					CountFanAndHua(i,iHuaCount, iFanCount);
					//���� and ����
					pDesk->sGameData.T_CountFen.iFanCount[i] = iFanCount;
					pDesk->sGameData.T_CountFen.iHuaCount[i] = iHuaCount;

					iZongFen = iBase + (iHuaCount + iFanCount)*iFanBase;
					if(pDesk->sGameData.T_HuPai.byUserNum<3)
					{
						//������� ����Ӯ��
						pDesk->sGameData.T_CountFen.iZongFen[i] += iZongFen;
						//������ҵķ�
						pDesk->sGameData.T_CountFen.iZongFen[pDesk->sGameData.T_HuPai.byDianPao] -= iZongFen;
					}
					else
					{
						//������� ����Ӯ��
						pDesk->sGameData.T_CountFen.iZongFen[i] -= iZongFen;
						//������ҵķ�
						pDesk->sGameData.T_CountFen.iZongFen[pDesk->sGameData.T_HuPai.byDianPao] += iZongFen;
					}
				}
			}
			//һ�ڶ��� ������ҵ�ׯ
			//pDesk->sGameData.m_byNtStation = pDesk->sGameData.T_HuPai.byDianPao;
		}
	}
}
/*--------------------------------------------------------------------------------------------------*/
//���㷬���ͻ���
void	ThingHandleEx::CountFanAndHua(BYTE byDeskStation, int &iHuaCount, int &iFanCount)
{
	bool bZiMo = false;
	for (int i = 0; i < MAX_HUPAI_TYPE; i++)
	{
		if (pDesk->sGameData.T_HuPai.byHuType[byDeskStation][i] == HUPAI_ZI_MO)
		{
			bZiMo = true;
			break;
		}
	}

	if (pDesk->sGameData.T_HuPai.bQiangGang)
	{
		pDesk->sCheckHuPai.SetAHupaiType(HUPAI_QIANG_GANG_HU, pDesk->sCheckHuPai.m_byHuType);
	}

	CString str;
	//�������ͷ�����������
	for (int i = 0; i<MAX_HUPAI_TYPE; i++)
	{
		if (pDesk->sGameData.T_HuPai.byHuType[byDeskStation][i] == 255)
		{
			continue;
		}
		if (pDesk->sGameData.T_HuPai.byHuType[byDeskStation][i] == HUPAI_AN_QI_DUI)	//С�߶�
		{
			if (bZiMo)
			{
				iFanCount += 10;
				pDesk->sGameData.T_CountFen.huDetail.byQiDui[byDeskStation] = 10;
				str.Format("����С�߶ԣ�10������ǰ������%d", iFanCount);
			}
			else
			{
				iFanCount += 5;
				pDesk->sGameData.T_CountFen.huDetail.byQiDui[byDeskStation] = 5;
				str.Format("����С�߶ԣ�5������ǰ������%d", iFanCount);
			}
			DebugPrintf(str);
		}
		if (pDesk->sGameData.T_HuPai.byHuType[byDeskStation][i] == HUPAI_PENG_PENG_HU)		//������
		{
			if (bZiMo)
			{
				iFanCount += 10;
				pDesk->sGameData.T_CountFen.huDetail.byPengPengHu[byDeskStation] = 10;
				str.Format("������������10������ǰ������%d", iFanCount);
			}
			else
			{
				iFanCount += 5;
				pDesk->sGameData.T_CountFen.huDetail.byPengPengHu[byDeskStation] = 5;
				str.Format("������������5������ǰ������%d", iFanCount);
			}
			DebugPrintf(str);
		}
		if (pDesk->sGameData.T_HuPai.byHuType[byDeskStation][i] == HUPAI_QIXING_BUKAO) //����ʮ����
		{
			iFanCount += 10;
			pDesk->sGameData.T_CountFen.huDetail.byQiXing[byDeskStation] = 10;
			str.Format("����ʮ���ã�10������ǰ������%d", iFanCount);
			DebugPrintf(str);
		}
		if (pDesk->sGameData.T_HuPai.byHuType[byDeskStation][i] == HUPAI_QUAN_BUKAO)	//ʮ����
		{
			iFanCount += 5;
			pDesk->sGameData.T_CountFen.huDetail.byShiSanLan[byDeskStation] = 5;
			str.Format("ʮ���ã�5������ǰ������%d", iFanCount);
			DebugPrintf(str);
		}
		if (pDesk->sGameData.T_HuPai.byHuType[byDeskStation][i] == HUPAI_DA_DIAOCHE)	//�����
		{
			if (bZiMo)
			{
				iFanCount += 10;
				pDesk->sGameData.T_CountFen.huDetail.byDiaoChe[byDeskStation] = 10;
				str.Format("�����������10������ǰ������%d", iFanCount);
			}
			else
			{
				iFanCount += 5;
				pDesk->sGameData.T_CountFen.huDetail.byDiaoChe[byDeskStation] = 5;
				str.Format("���ڴ������5������ǰ������%d", iFanCount);
			}
			DebugPrintf(str);
		}
		if (pDesk->sGameData.T_HuPai.byHuType[byDeskStation][i] == HUPAI_TYPE_GANG_KAI)// �ܿ�
		{
			iFanCount += 3 * pDesk->sGameData.m_byLianGang;
			pDesk->sGameData.T_CountFen.huDetail.byGangHua[byDeskStation] = 3 * pDesk->sGameData.m_byLianGang;
			str.Format("%d���ܣ�ÿ�����ϻ�3������ǰ������%d", pDesk->sGameData.m_byLianGang, iFanCount);
			DebugPrintf(str);
		}
		if (pDesk->sGameData.T_HuPai.byHuType[byDeskStation][i] == HUPAI_TYPE_DI_HU)	// �غ�
		{
			iFanCount += 10;
			pDesk->sGameData.T_CountFen.huDetail.byDiHu[byDeskStation] = 10;
			str.Format("�غ���10������ǰ������%d", iFanCount);
			DebugPrintf(str);
		}
		if (pDesk->sGameData.T_HuPai.byHuType[byDeskStation][i] == HUPAI_TYPE_TIAN_HU)// ���
		{
			iFanCount += 10;
			pDesk->sGameData.T_CountFen.huDetail.byTianHu[byDeskStation] = 10;
			str.Format("�����10������ǰ������%d", iFanCount);
			DebugPrintf(str);
		}
		if (pDesk->sGameData.T_HuPai.byHuType[byDeskStation][i] == HUPAI_NO_HUA)//�޻���
		{
			pDesk->sGameData.T_CountFen.huDetail.byNoHua[byDeskStation] = 5;
			iFanCount += 5;
			str.Format("�޻�����5������ǰ������%d", iFanCount);
			DebugPrintf(str);
		}
		if (pDesk->sGameData.T_HuPai.byHuType[byDeskStation][i] == HUPAI_QIANG_GANG_HU)
		{
			iHuaCount += 5;
			pDesk->sGameData.T_CountFen.huDetail.byQiangGang[byDeskStation] = 5;
			pDesk->sGameData.T_CountFen.huDetail.byBianPai[byDeskStation] = 2;
			str.Format("���ܺ���3������ǰ������%d", iFanCount);
			DebugPrintf(str);
		}
		if (pDesk->sGameData.T_HuPai.byHuType[byDeskStation][i] == HUPAI_HU_PAI)//ƽ��
		{
			/*if (pDesk->sUserData.m_byArHuaPai[byDeskStation][0] == 255
			&& byDeskStation == pDesk->sUserData.m_byNowOutStation)
			{
			pDesk->sGameData.T_CountFen.huDetail.byNoHua[byDeskStation] = 5;
			iFanCount += 5;
			}*/
		}

		//���÷���
		if (pDesk->sGameData.T_HuPai.byHuType[byDeskStation][i] == HUPAI_BIAN_PAI)
		{
			iHuaCount += 2;
			pDesk->sGameData.T_CountFen.huDetail.byBianPai[byDeskStation] = 2;
			str.Format("���ƣ�2������ǰ���ã�%d", iHuaCount);
			DebugPrintf(str);
		}
		if (pDesk->sGameData.T_HuPai.byHuType[byDeskStation][i] == HUPAI_DIAN_DIAO)
		{
			iHuaCount += 2;
			pDesk->sGameData.T_CountFen.huDetail.byDianDiao[byDeskStation] = 2;
			str.Format("��������2������ǰ���ã�%d", iHuaCount);
			DebugPrintf(str);
		}
		if (pDesk->sGameData.T_HuPai.byHuType[byDeskStation][i] == HUPAI_KAI_PAI)
		{
			iHuaCount += 2;
			pDesk->sGameData.T_CountFen.huDetail.byKaPai[byDeskStation] = 2;
			str.Format("���ƣ�2������ǰ���ã�%d", iHuaCount);
			DebugPrintf(str);
		}
		if (pDesk->sGameData.T_HuPai.byHuType[byDeskStation][i] == HUPAI_MEN_QIAN_QING)
		{
			iHuaCount += 2;
			pDesk->sGameData.T_CountFen.huDetail.byMenQing[byDeskStation] = 2;
			str.Format("��ǰ�壬2������ǰ���ã�%d", iHuaCount);
			DebugPrintf(str);
		}
		if (pDesk->sGameData.T_HuPai.byHuType[byDeskStation][i] == HUPAI_LIANG_DUI)
		{
			iHuaCount += 2;
			pDesk->sGameData.T_CountFen.huDetail.byLiangDui[byDeskStation] = 2;
			str.Format("���ԣ�2������ǰ���ã�%d", iHuaCount);
			DebugPrintf(str);
		}
		if (pDesk->sGameData.T_HuPai.byHuType[byDeskStation][i] == HUPAI_THREE_NAN)
		{
			iHuaCount += 1;
			pDesk->sGameData.T_CountFen.huDetail.byThreeNan[byDeskStation] = 1;
			str.Format("�����Ϸ磬1������ǰ���ã�%d", iHuaCount);
			DebugPrintf(str);
		}
		if (pDesk->sGameData.T_HuPai.byHuType[byDeskStation][i] == HUPAI_THREE_XI)
		{
			iHuaCount += 1;
			pDesk->sGameData.T_CountFen.huDetail.byThreeXi[byDeskStation] = 1;
			str.Format("�������磬1������ǰ���ã�%d", iHuaCount);
			DebugPrintf(str);
		}
		if (pDesk->sGameData.T_HuPai.byHuType[byDeskStation][i] == HUPAI_THREE_BEI)
		{
			iHuaCount += 1;
			pDesk->sGameData.T_CountFen.huDetail.byThreeBei[byDeskStation] = 1;
			str.Format("���ű��磬1������ǰ���ã�%d", iHuaCount);
			DebugPrintf(str);
		}
	}

	//���㻨��
	for (int i = 0; i<HUA_CARD_NUM; i++)
	{
		if (pDesk->sUserData.m_byArHuaPai[byDeskStation][i] != 255)
		{
			iHuaCount += 1;
			pDesk->sGameData.T_CountFen.huDetail.byHua[byDeskStation] += 1;
			str.Format("�л�����1������ǰ���ã�%d", iHuaCount);
			DebugPrintf(str);
		}
	}
	iHuaCount -= pDesk->sGameData.m_byGangHua;
	pDesk->sGameData.T_CountFen.huDetail.byHua[byDeskStation] -= pDesk->sGameData.m_byGangHua;
	str.Format("��%d���ܻ�����%d������ǰ���ã�%d", pDesk->sGameData.m_byGangHua, pDesk->sGameData.m_byGangHua, iHuaCount);
	DebugPrintf(str);

	//���㶫�磬�з���
	if (pDesk->sUserData.GetAHuaCount(byDeskStation, CMjEnum::MJ_TYPE_FD)>3)
	{
		iFanCount += 4;
		pDesk->sGameData.T_CountFen.huDetail.byFourDong[byDeskStation] += 4;
		str.Format("���Ŷ��磬4������ǰ������%d", iHuaCount);
		DebugPrintf(str);
	}
	if (pDesk->sUserData.GetAHuaCount(byDeskStation, CMjEnum::MJ_TYPE_ZHONG)>3)
	{
		iFanCount += 4;
		pDesk->sGameData.T_CountFen.huDetail.byFourZhong[byDeskStation] += 4;
		str.Format("�����У�4������ǰ������%d", iHuaCount);
		DebugPrintf(str);
	}
	if (pDesk->sUserData.GetAHuaCount(byDeskStation, CMjEnum::MJ_TYPE_FA)>3)
	{
		iFanCount += 4;
		pDesk->sGameData.T_CountFen.huDetail.byFourFa[byDeskStation] += 4;
		str.Format("���ŷ���4������ǰ������%d", iHuaCount);
		DebugPrintf(str);
	}
	if (pDesk->sUserData.GetAHuaCount(byDeskStation, CMjEnum::MJ_TYPE_BAI)>3)
	{
		iFanCount += 4;
		pDesk->sGameData.T_CountFen.huDetail.byFourBai[byDeskStation] += 4;
		str.Format("���Űף�4������ǰ������%d", iHuaCount);
		DebugPrintf(str);
	}

	//�������
	for (int i = 0; i<5; i++)
	{
		if (pDesk->sUserData.m_UserGCPData[byDeskStation][i].byType == AT_QUADRUPLET_CONCEALED)
		{//����
			if (pDesk->sUserData.m_UserGCPData[byDeskStation][i].byData[0] > CMjEnum::MJ_TYPE_FD && pDesk->sUserData.m_UserGCPData[byDeskStation][i].byData[0] < CMjEnum::MJ_TYPE_ZHONG)
			{
				iHuaCount += 4;
				if (pDesk->sUserData.m_UserGCPData[byDeskStation][i].byData[0] == CMjEnum::MJ_TYPE_FN)
					pDesk->sGameData.T_CountFen.huDetail.byNanGang[byDeskStation] += 4;
				if (pDesk->sUserData.m_UserGCPData[byDeskStation][i].byData[0] == CMjEnum::MJ_TYPE_FX)
					pDesk->sGameData.T_CountFen.huDetail.byXiGang[byDeskStation] += 4;
				if (pDesk->sUserData.m_UserGCPData[byDeskStation][i].byData[0] == CMjEnum::MJ_TYPE_FB)
					pDesk->sGameData.T_CountFen.huDetail.byBeiGang[byDeskStation] += 4;
				str.Format("�������磬4������ǰ���ã�%d", iHuaCount);
				DebugPrintf(str);
			}
			else
			{
				iHuaCount += 3;
				pDesk->sGameData.T_CountFen.huDetail.byAnGang[byDeskStation] += 3;
				str.Format("���ְ��ܣ�3������ǰ���ã�%d", iHuaCount);
				DebugPrintf(str);
			}
		}
		else if (pDesk->sUserData.m_UserGCPData[byDeskStation][i].byType == AT_QUADRUPLET_REVEALED || pDesk->sUserData.m_UserGCPData[byDeskStation][i].byType == AT_QUADRUPLET)
		{//����
		 /*if(pDesk->sUserData.m_UserGCPData[byDeskStation][i].byData[0] > CMjEnum::MJ_TYPE_FD && pDesk->sUserData.m_UserGCPData[byDeskStation][i].byData[0] < CMjEnum::MJ_TYPE_ZHONG)
		 {
		 iHuaCount +=4;
		 if(pDesk->sUserData.m_UserGCPData[byDeskStation][i].byData[0] == CMjEnum::MJ_TYPE_FN)
		 pDesk->sGameData.T_CountFen.huDetail.byNanGang_an[byDeskStation] += 4;
		 if(pDesk->sUserData.m_UserGCPData[byDeskStation][i].byData[0] == CMjEnum::MJ_TYPE_FX)
		 pDesk->sGameData.T_CountFen.huDetail.byXiGang_an[byDeskStation] += 4;
		 if(pDesk->sUserData.m_UserGCPData[byDeskStation][i].byData[0] == CMjEnum::MJ_TYPE_FB)
		 pDesk->sGameData.T_CountFen.huDetail.byBeiGang_an[byDeskStation] += 4;
		 }
		 else
		 {*/
			iHuaCount += 2;
			pDesk->sGameData.T_CountFen.huDetail.byMingGang[byDeskStation] += 2;
			//}
			str.Format("���ܣ�2������ǰ���ã�%d", iHuaCount);
			DebugPrintf(str);
		}
	}
}

/*--------------------------------------------------------------------------------------------------*/
///������Ϸ�����¼�
void ThingHandleEx::ExecuteNormalEnd(BYTE &nextID,BYTE &time)
{    
	//��ǰִ���¼�
	pDesk->sGameData.m_byThingDoing = THING_ENG_HANDLE;

	pDesk->sUserData.CopyHandPai(pDesk->sGameData.T_CountFen.m_byArHandPai,0,true);
	
	//��������
	for(int i=0; i<PLAY_COUNT; i++)
	{
		pDesk->sGameData.T_CountFen.m_byArHandPaiCount[i] = pDesk->sUserData.GetHandPaiCount(i);
	}
	//���Ƴ�����
	//memcpy(pDesk->sGameData.T_CountFen.m_UserGCPData, pDesk->sUserData.m_UserGCPData, sizeof(pDesk->sGameData.T_CountFen.m_UserGCPData));

	pDesk->KillTimer(TIME_CHECK_GAME_MSG);
	//����ƽ̨������Ϸ�ӿ�
	pDesk->GameFinish(pDesk->sGameData.T_HuPai.byUser,GF_NORMAL);

	pDesk->KillTimer(TIME_WAIT_MSG);
	this->ReSetOutTime();
}




































///�쳣��Ϸ�����¼��¼�
void ThingHandleEx::ExecuteUnNormalEnd(BYTE &nextID,BYTE &time)
{
	ThingHandle::ExecuteUnNormalEnd(nextID,time);
}

///�����Զ�������
void ThingHandleEx::NetCutAutoHandle()
{
	if (pDesk->m_bIsBuy) {
		return;
	}
	//ThingHandle::NetCutAutoHandle();
	switch(pDesk->sGameData.m_byThingDoing)
	{			        				         
	case THING_2SEZI_NT://�׾���2��ɫ�ӵĵ�����Ϊׯ�¼�		   
	case THING_2SEZI_NT_GP://�׾���2��ɫ�Ӷ�ׯ�Һ����Ƶ��¼�	
	case THING_TURN_2SEZI_NT://�׾�������2��ɫ�Ӷ�ׯ���¼�		
	case THING_2SEZI_DIR://��2��ɫ���¼������Ʒ����¼�		
	case THING_2SEZI_DIR_GP://��2��ɫ���¼������Ʒ�������Ƶ��¼�
	case THING_2SEZI_GP://��2��ɫ���¼������Ƶ��¼�												
	case THING_2SEZI_JING://��2��ɫ�Ӷ������¼�			
	case THING_1SEZI_JIN://��1��ɫ�Ӷ������¼�
		{
			for(int i=0;i<PLAY_COUNT;++i)
			{
				if(!pDesk->sUserData.m_bSiziFinish[i] && pDesk->sUserData.m_bFoceLeave[i])//�����û�з�������Ϣ
				{
					ReceiveSeziFinish(i,NULL,0,false);
				}
			}
		}break;
	case THING_ALL_BUHUA://Ϊ������Ҳ����¼�
		{
		}
		break;
	case THING_ONE_BUHUA://������Ҳ����¼�	
	case THING_CHI_PAI://�����¼�
	case THING_PENG_PAI://�����¼�
	case THING_GANG_PAI://�����¼�
		{
			if(pDesk->sUserData.m_bFoceLeave[pDesk->sUserData.m_byNowOutStation])//���������Ҷ���
			{
				AutoOutOrGet();//������ҳ���
			}
		}
		break;
	case THING_BEGIN_OUT://ׯ�ҿ�ʼ����֪ͨ�¼�	
		{
			if(pDesk->sUserData.m_bFoceLeave[pDesk->sGameData.m_byNtStation])//���ׯ�Ҷ���
			{
				AutoOutOrGet();
			}
		}
		break;
	case THING_OUT_PAI://�����¼�
		{
			for(int i=0;i<PLAY_COUNT;++i)
			{
				if(pDesk->sUserData.m_bFoceLeave[i] && pDesk->sUserData.m_byNowOutStation != i)//�����Ҷ���
				{
					ReceiveUserPassCheck(i,NULL,0,false);//���ͷ�����Ϣ
				}
			}
		}
		break;
	case THING_ZHUA_PAI://ץ���¼�
		{
			OutputDebugString("��ʱ����NetCutAutoHandle 000");
			if(pDesk->sUserData.m_bFoceLeave[pDesk->sUserData.m_byNowOutStation])//���������Ҷ���
			{
				AutoOutOrGet();
			}
		}
		
	}
}

void ThingHandleEx::LogAction()
{
	CString str;
	for (int i = 0; i < PLAY_COUNT; i++) {
		if (pDesk->sGameData.T_CPGNotify[i].bCanAction) {
			str.Format("���%s�ж�����", pDesk->m_pUserInfo[i]->m_UserData.szName);
			if (pDesk->sGameData.T_CPGNotify[i].bPeng) {
				str.AppendFormat("��%d ", pDesk->sGameData.T_CPGNotify[i].byPs);
			}
			if (pDesk->sGameData.T_CPGNotify[i].bChi) {
				str.AppendFormat("��%d ", pDesk->sGameData.T_CPGNotify[i].byPs);
			}
			if (pDesk->sGameData.T_CPGNotify[i].bGang) {
				str.Append("��");
				for(int j=0;j<4;j++){
					if (pDesk->sGameData.T_CPGNotify[i].m_iGangData[i][1] == 255) {
						break;
					}
					str.AppendFormat("%d,", pDesk->sGameData.T_CPGNotify[i].m_iGangData[j][1]);
				}
				str.Append(" ");
			}
			if (pDesk->sGameData.T_CPGNotify[i].bHu) {
				str.AppendFormat("��%d", pDesk->sGameData.T_CPGNotify[i].m_iHuPs);
			}
			DebugPrintf(str);
		}
	}
	DebugPrintf("**************************��⶯�����*************************");
}



//-------------------------------------------��������------------------------------------------------------//
/*---------------------------------------------------------------------------------------------------------*/
///�����¼�
void	ThingHandleEx::HandleChiPai()
{	

	pDesk->sGameData.m_byThingDoing = THING_CHI_PAI;//��¼����ִ�е��¼�
	///�������¼�
//	pDesk->sGameData.T_ChiPai = pDesk->sGameData.temp_ChiPai;//��ȡ����
//	pDesk->sUserData.m_byNowOutStation = pDesk->sGameData.temp_ChiPai.byUser;

	//��ӳ���
	GCPStructEx chi;
	chi.Init();
	chi.byType		= AT_COLLECT;	//��������
	chi.iBeStation	= pDesk->sGameData.T_OutPai.byUser;	//���Ե���� ����֮ǰ���Ƶ����
	chi.iOutpai		= pDesk->sGameData.T_OutPai.byPs;	//���Ե�������
	chi.iStation	= pDesk->sGameData.T_ChiPai.byUser;	//���Ƶ����

	pDesk->sUserData.m_byChengBao[chi.iStation][chi.iBeStation]++;
	pDesk->sUserData.m_byChiChengBao[chi.iStation][chi.iBeStation]++;
	//��������
	for(int i=0;i<3;i++)
	{	
		chi.byData[i] = pDesk->sGameData.T_ChiPai.byChiPs[i];
		if(pDesk->sGameData.T_ChiPai.byChiPs[i] == pDesk->sGameData.T_ChiPai.byPs)
		{
			continue;
		}
		//ɾ������
		pDesk->sUserData.DelleteAHandPai(pDesk->sGameData.T_ChiPai.byUser,pDesk->sGameData.T_ChiPai.byChiPs[i]);
	}

	//ɾ��������ҵ����һ����
	pDesk->sUserData.DelleteLastOutPai(pDesk->sGameData.T_OutPai.byUser);
	//�����������
	pDesk->sUserData.AddToGCP(chi.iStation,&chi);

	//������������
	pDesk->sUserData.CopyGCPData(chi.iStation,pDesk->sGameData.T_ChiPai.m_UserGCPData[chi.iStation]);
	//����������ҵĳ�������
	pDesk->sGameData.T_ChiPai.m_byArOutPaiCount[chi.iBeStation] = pDesk->sUserData.CopyOutPai(chi.iBeStation,pDesk->sGameData.T_ChiPai.m_byArOutPai[chi.iBeStation]);

	//������ҵ���������
	pDesk->sGameData.T_ChiPai.m_byArHandPaiCount[chi.iStation] = pDesk->sUserData.GetHandPaiCount(chi.iStation);

	//֪ͨ�������
	for (int i=0;i<PLAY_COUNT;i++)
	{	
		memset(pDesk->sGameData.T_ChiPai.m_byArHandPai,255,sizeof(pDesk->sGameData.T_PengPai.m_byArHandPai));
		pDesk->sUserData.CopyHandPai(pDesk->sGameData.T_ChiPai.m_byArHandPai,i,true);

		pDesk->SendGameDataEx(i, &pDesk->sGameData.T_ChiPai, sizeof(pDesk->sGameData.T_ChiPai), MDM_GM_GAME_NOTIFY, THING_CHI_PAI, 0);
		pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_ChiPai, sizeof(pDesk->sGameData.T_ChiPai), MDM_GM_GAME_NOTIFY, THING_CHI_PAI, 0);
	}

	//�������ҵ�������������
	pDesk->sGameData.T_CPGNotify[chi.iStation].Clear();

	//��ǰ���Ƶ����
	pDesk->sUserData.m_byNowOutStation = chi.iStation;

// 	//�����ƺ��⶯��
 	//if(CheckAction(pDesk->sUserData.m_byNowOutStation,pDesk->sUserData.GetLastHandPai(pDesk->sUserData.m_byNowOutStation),4))//���Ƽ�⶯��
 	//{
 	//	//�����ץ�ƺ��ж���(�ͻ���������ʾ����ʱʱ���)
 	//	pDesk->sGameData.T_CPGNotify[pDesk->sUserData.m_byNowOutStation].bZhuaPai	 = true;
 	//	pDesk->SendGameDataEx(pDesk->sUserData.m_byNowOutStation, &pDesk->sGameData.T_CPGNotify ,sizeof(pDesk->sGameData.T_CPGNotify), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
 	//	pDesk->SendWatchDataEx(pDesk->sUserData.m_byNowOutStation, &pDesk->sGameData.T_CPGNotify ,sizeof(pDesk->sGameData.T_CPGNotify), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
 	//}
	//�����ƺ�ֱ��������ʱ���Ƽ�ʱ��(��Ϊ�����ƺ󲻿����к��Ƶ����)
	SetDoingThing(pDesk->sUserData.m_byNowOutStation,THING_OUT_PAI);

}
/*---------------------------------------------------------------------------------------------------------*/
///�����¼�
void	ThingHandleEx::HandlePengPai()	
{
	pDesk->sGameData.m_byThingDoing = THING_PENG_PAI;//��¼����ִ�е��¼�
	
	
	//�������¼�
	GCPStructEx peng;
	peng.Init();
	peng.byType		= AT_TRIPLET;	//������
	peng.iStation	= pDesk->sGameData.T_PengPai.byUser;	//���������λ��
	peng.iBeStation	= pDesk->sGameData.T_OutPai.byUser;		//��������� ����֮ǰ���Ƶ����
	peng.iOutpai	= pDesk->sGameData.T_OutPai.byPs;		//������������

	pDesk->sUserData.m_byChengBao[peng.iStation][peng.iBeStation]++;
	pDesk->sUserData.m_byPengChengBao[peng.iStation][peng.iBeStation]++;
	//��������������
	for(int i=0;i<3;i++)
	{
		peng.byData[i] = pDesk->sGameData.T_OutPai.byPs;
	}

	//�������ɾ�����һ�ų���
	pDesk->sUserData.DelleteLastOutPai(peng.iBeStation);
	//ɾ��������ҵ�����������
	for(int i=0;i<2;i++)
	{	
		pDesk->sUserData.DelleteAHandPai(peng.iStation, peng.iOutpai);
	}
	
	//�������
	pDesk->sUserData.AddToGCP(peng.iStation,&peng);

	//������������
	pDesk->sUserData.CopyGCPData(peng.iStation,pDesk->sGameData.T_PengPai.m_UserGCPData[peng.iStation]);
	//����������ҵĳ�������
	pDesk->sGameData.T_PengPai.m_byArOutPaiCount[peng.iBeStation] = pDesk->sUserData.CopyOutPai(peng.iBeStation,pDesk->sGameData.T_PengPai.m_byArOutPai[peng.iBeStation]);

	//������ҵ���������
	pDesk->sGameData.T_PengPai.m_byArHandPaiCount[peng.iStation] = pDesk->sUserData.GetHandPaiCount(peng.iStation);

	//֪ͨ�������
	for (int i=0;i<PLAY_COUNT;i++)
	{	
		memset(pDesk->sGameData.T_PengPai.m_byArHandPai,255,sizeof(pDesk->sGameData.T_PengPai.m_byArHandPai));
		pDesk->sUserData.CopyHandPai(pDesk->sGameData.T_PengPai.m_byArHandPai,i,true);

		pDesk->SendGameDataEx(i, &pDesk->sGameData.T_PengPai, sizeof(pDesk->sGameData.T_PengPai), MDM_GM_GAME_NOTIFY, THING_PENG_PAI, 0);
		pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_PengPai, sizeof(pDesk->sGameData.T_PengPai), MDM_GM_GAME_NOTIFY, THING_PENG_PAI, 0);
	}
	//�������ҵ�������������
	pDesk->sGameData.T_CPGNotify[peng.iStation].Clear();

	//��ǰ���Ƶ����
	pDesk->sUserData.m_byNowOutStation = peng.iStation;

	//���ƺ��⶯��
 	//if(CheckAction(pDesk->sUserData.m_byNowOutStation,pDesk->sUserData.GetLastHandPai(pDesk->sUserData.m_byNowOutStation),4))//���Ƽ�⶯��
 	//{
 	//	//�����ץ�ƺ��ж���(�ͻ���������ʾ����ʱʱ���)
 	//	pDesk->sGameData.T_CPGNotify[pDesk->sUserData.m_byNowOutStation].bZhuaPai	 = true;
 	//	pDesk->SendGameDataEx(pDesk->sUserData.m_byNowOutStation, &pDesk->sGameData.T_CPGNotify ,sizeof(pDesk->sGameData.T_CPGNotify), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
 	//	pDesk->SendWatchDataEx(pDesk->sUserData.m_byNowOutStation, &pDesk->sGameData.T_CPGNotify ,sizeof(pDesk->sGameData.T_CPGNotify), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
 	//}
	//�����ƺ�ֱ��������ʱ���Ƽ�ʱ��(��Ϊ�����ƺ󲻿����к��Ƶ����)
	SetDoingThing(pDesk->sUserData.m_byNowOutStation,THING_OUT_PAI);
}

/*---------------------------------------------------------------------------------------------------------*/
///���¼�
void	ThingHandleEx::HandleGangPai(BYTE & gangType)
{
	/*���ж���ʲô���͵ĸ�*/
	BYTE byGangType = 255;
	for (int i = 0; i < 5; i++)
	{
		if (pDesk->sGameData.T_CPGNotify[pDesk->sGameData.T_GangPai.byUser].m_iGangData[i][1] == pDesk->sGameData.T_GangPai.byPs) {
			byGangType = pDesk->sGameData.T_CPGNotify[pDesk->sGameData.T_GangPai.byUser].m_iGangData[i][0];
			break;
		}
	}
	gangType = byGangType;

	//if (pDesk->sGameData.m_byThingDoing == THING_OUT_PAI)
	//{
	//	byGangType = AT_QUADRUPLET_REVEALED;
	//}
	//else if (pDesk->sGameData.m_byThingDoing == THING_ZHUA_PAI || THING_ONE_BUHUA == pDesk->sGameData.m_byThingDoing || THING_BEGIN_OUT == pDesk->sGameData.m_byThingDoing)
	//{
	//	//�����ץ��״̬ || ����״̬ || ��ʼ����״̬ ��ô��ȥ�ж��ǰ��� ���ǲ���
	//	for (int i = 0; i<5; i++)
	//	{
	//		//�����������и����� && ��������
	//		if (pDesk->sUserData.m_UserGCPData[pDesk->sGameData.T_GangPai.byUser][i].byData[0] == pDesk->sGameData.T_GangPai.byPs && pDesk->sUserData.m_UserGCPData[pDesk->sGameData.T_GangPai.byUser][i].byType == ACTION_PENG)
	//		{
	//			byGangType = AT_QUADRUPLET;
	//			break;
	//		}
	//	}
	//	if (byGangType != AT_QUADRUPLET)
	//	{
	//		byGangType = AT_QUADRUPLET_CONCEALED;
	//	}
	//}

	pDesk->sUserData.m_byNowOutStation = pDesk->sGameData.T_GangPai.byUser;

	//��������
	GCPStructEx gang;
	gang.Init();
	gang.byType		= byGangType;	//������
	gang.iStation	= pDesk->sGameData.T_GangPai.byUser;	//���������λ��
	gang.iBeStation	= pDesk->sGameData.T_GangPai.byBeGang;	//���ܵ���� ����֮ǰ���Ƶ����
	gang.iOutpai	= pDesk->sGameData.T_GangPai.byPs;		//���ܵ�������

	pDesk->sUserData.m_byChengBao[gang.iStation][gang.iBeStation]++;
	pDesk->sUserData.m_byPengChengBao[gang.iStation][gang.iBeStation]++;
	//��������
	for(int i=0; i<4; i++)
	{
		gang.byData[i] = pDesk->sGameData.T_GangPai.byPs;
	}

	switch (byGangType)
	{
	case ACTION_MING_GANG:
	{
		//ɾ��������ҵ�����3����
		for (int i = 0; i < 3; i++)
		{
			pDesk->sUserData.DelleteAHandPai(gang.iStation, gang.iOutpai);
		}

		//ɾ������������һ�ų���
		pDesk->sUserData.DelleteLastOutPai(gang.iBeStation);
		//����������ҵĳ�������
		pDesk->sGameData.T_GangPai.m_byArOutPaiCount[gang.iBeStation] = pDesk->sUserData.CopyOutPai(gang.iBeStation, pDesk->sGameData.T_GangPai.m_byArOutPai[gang.iBeStation]);

		//��¼��������ڸ���״̬(�����ж��Ƿ�ܿ�) ֻ�������� ����ܿ�
		pDesk->sGameData.m_bGangState[gang.iStation] = true;
		gang.byType = AT_QUADRUPLET_REVEALED;
		break;
	}
	case ACTION_BU_GANG:
	{
		//ɾ��������ҵ�����1����
		for (int i = 0; i < 1; i++)
		{
			pDesk->sUserData.DelleteAHandPai(gang.iStation, gang.iOutpai);
		}
		//ɾ����Ӧ����
		pDesk->sUserData.DelleteAGCPData(gang.iStation, ACTION_PENG, gang.iOutpai);

		gang.byType = AT_QUADRUPLET;
		break;
	}
	case ACTION_AN_GANG:
	{
		//ɾ��������ҵ�����4����
		for (int i = 0; i < 4; i++)
		{
			pDesk->sUserData.DelleteAHandPai(gang.iStation, gang.iOutpai);
		}
		gang.byType = AT_QUADRUPLET_CONCEALED;

		//��¼���ܵ������ڸܺ���
		//pDesk->sGameData.T_TingPai.byAnGangCard = gang.iOutpai;

		break;
	}
	default:
		break;
	}
	
	//��¼������Ϣ���ڴ����
	if (byGangType == ACTION_AN_GANG/*AT_QUADRUPLET_CONCEALED*/) {
		pDesk->m_calculateMsg.iAnGan[gang.iStation]++;
	}
	else {
		pDesk->m_calculateMsg.iMingGan[gang.iStation]++;
	}

	//��Ӹ�������
	pDesk->sUserData.AddToGCP(gang.iStation,&gang);

	//������������
	pDesk->sUserData.CopyGCPData(gang.iStation,pDesk->sGameData.T_GangPai.m_UserGCPData[gang.iStation]);

	//������ҵ���������
	pDesk->sGameData.T_GangPai.m_byArHandPaiCount[gang.iStation] = pDesk->sUserData.GetHandPaiCount(gang.iStation);
//	pDesk->sUserData.m_bIsGangPao[pDesk->sGameData.temp_GangPai.byUser] = true;//���ڸܺ��ڵ�״̬
	pDesk->sGameData.m_byLianGang++;
	//֪ͨ�������
	for (int i=0;i<PLAY_COUNT;i++)
	{	
		memset(pDesk->sGameData.T_GangPai.m_byArHandPai,255,sizeof(pDesk->sGameData.T_GangPai.m_byArHandPai));
		pDesk->sUserData.CopyHandPai(pDesk->sGameData.T_GangPai.m_byArHandPai,i,true);
		
		pDesk->SendGameDataEx(i, &pDesk->sGameData.T_GangPai, sizeof(pDesk->sGameData.T_GangPai), MDM_GM_GAME_NOTIFY, THING_GANG_PAI, 0);
		pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_GangPai, sizeof(pDesk->sGameData.T_GangPai), MDM_GM_GAME_NOTIFY, THING_GANG_PAI, 0);
	}

	pDesk->sGameData.m_byThingDoing = THING_GANG_PAI;//��¼����ִ�е��¼�


	//�������ҵ�������������
	pDesk->sGameData.T_CPGNotify[gang.iStation].Clear();

	//��ǰ���Ƶ����
	pDesk->sUserData.m_byNowOutStation = gang.iStation;

	////����ǲ��ܾ�Ҫ����Ƿ��������ܺ� 
	if(byGangType == ACTION_BU_GANG/*AT_QUADRUPLET*/ )//���Ƽ�����ܺ�
	{
		bool bHaveSend = false;	//�Ƿ��Ѿ���������Ϣ
		BYTE byCanActionDesk = 255;	//���������������
		if (CheckAction(gang.iStation, gang.iOutpai, 3)) {
			//�������ܺ� ��ô�ͷ���������Ϣ
			for (int i = 0; i < PLAY_COUNT; i++)
			{
				if (i == gang.iStation)
				{
					continue;
				}
				if (pDesk->sGameData.T_CPGNotify[i].bHu)
				{
					CString str;
					str.Format("********************%s����%d,��⶯��********************", pDesk->m_pUserInfo[gang.iStation]->m_UserData.szName, gang.iOutpai);
					DebugPrintf(str);
					LogAction();

					pDesk->SendGameDataEx(i, &pDesk->sGameData.T_CPGNotify, sizeof(pDesk->sGameData.T_CPGNotify), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
					pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_CPGNotify, sizeof(pDesk->sGameData.T_CPGNotify), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
					bHaveSend = true;	//�Ƿ��Ѿ���������Ϣ
					byCanActionDesk = i;	//���������������
					break;
				}
			}
		}
		if (bHaveSend)
		{
			SetDoingThing(byCanActionDesk, THING_HU_PAI);
		}
		else
		{
			//ץ���¼�
			ApplyAction(THING_ZHUA_PAI, 100);
		}
	}
}

void ThingHandleEx::HandleHuPai()
{
	//���˵���
	if (pDesk->sGameData.m_byThingDoing == THING_OUT_PAI && pDesk->sGameData.T_OutPai.byUser != 255)
	{
		pDesk->sGameData.T_HuPai.byDianPao = pDesk->sGameData.T_OutPai.byUser;
		pDesk->sGameData.T_HuPai.byPs = pDesk->sGameData.T_OutPai.byPs;
	}
	else if (pDesk->sGameData.m_byThingDoing == THING_GANG_PAI && pDesk->sGameData.T_GangPai.byUser != 255)	//���ܺ�
	{
		pDesk->sGameData.T_HuPai.bQiangGang = true;
		pDesk->sGameData.T_HuPai.byDianPao = pDesk->sGameData.T_GangPai.byUser;
		pDesk->sGameData.T_HuPai.byPs = pDesk->sGameData.T_GangPai.byPs;
	}
	else if ((pDesk->sGameData.m_byThingDoing == THING_ZHUA_PAI) || (pDesk->sGameData.m_byThingDoing == THING_ONE_BUHUA) || (pDesk->sGameData.m_byThingDoing == THING_BEGIN_OUT))	//����
	{
		pDesk->sGameData.T_HuPai.bZimo = true;
		pDesk->sGameData.T_HuPai.byDianPao = 255;
		pDesk->sGameData.T_HuPai.byPs = 255;
		//�Ƿ�ܿ�
		if (pDesk->sGameData.m_bGangState[pDesk->sGameData.T_HuPai.byUser])
		{
			pDesk->sGameData.T_HuPai.bGangKai = true;
			//�ܿ��� �Ÿ���ҵ���
			//pDesk->sGameData.T_HuPai.byDianPao = pDesk->sGameData.T_OutPai.byUser;
		}
	}
	if (!pDesk->sGameData.T_HuPai.bZimo)
		pDesk->sUserData.AddToHandPai(pDesk->sGameData.T_HuPai.byUser, pDesk->sGameData.T_HuPai.byPs);

	//��ʶ����Һ�����
	pDesk->sGameData.T_HuPai.bHaveHu[pDesk->sGameData.T_HuPai.byUser] = true;
	pDesk->sGameData.T_HuPai.byUserNum++;
	pDesk->sUserData.m_bIsHu[pDesk->sGameData.T_HuPai.byUser] = true;

	//��ȡ��������
	for (int i = 0; i<MAX_HUPAI_TYPE; i++)
	{
		pDesk->sGameData.T_HuPai.byHuType[pDesk->sGameData.T_HuPai.byUser][i] = pDesk->sGameData.T_CPGNotify[pDesk->sGameData.T_HuPai.byUser].byHuType[i];
	}
	//������ҵ���������
	for (int j = 0; j < PLAY_COUNT; j++)
	{
		for (int i = 0; i<HAND_CARD_NUM; i++)
		{
			pDesk->sGameData.T_HuPai.m_byArHandPai[j][i] = pDesk->sUserData.m_byArHandPai[j][i];
		}
		//������ҵ���������
		pDesk->sGameData.T_HuPai.m_byArHandPaiCount[j] = pDesk->sUserData.GetHandPaiCount(j);
	}

	//�������ҵ�������������
	//pDesk->sGameData.T_CPGNotify[pDesk->sGameData.T_HuPai.byUser].Clear();

	//��¼������Ϣ���ڴ����
	if (pDesk->sGameData.T_HuPai.bZimo) {
		pDesk->m_calculateMsg.iZimo[pDesk->sGameData.T_HuPai.byUser]++;
	}
	else {
		pDesk->m_calculateMsg.iJiePao[pDesk->sGameData.T_HuPai.byUser]++;
		pDesk->m_calculateMsg.iDianPao[pDesk->sGameData.T_HuPai.byDianPao]++;
	}

	//֪ͨ��Һ�����
	for (int i = 0; i<PLAY_COUNT; i++)
	{
		pDesk->SendGameDataEx(i, &pDesk->sGameData.T_HuPai, sizeof(pDesk->sGameData.T_HuPai), MDM_GM_GAME_NOTIFY, THING_HU_PAI, 0);
		pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_HuPai, sizeof(pDesk->sGameData.T_HuPai), MDM_GM_GAME_NOTIFY, THING_HU_PAI, 0);
	}

	pDesk->sGameData.T_HuPai.bIsLiuJu = false;

}

/*--------------------------------------------------------------------------------------*/
/*	��ʱ������Ⱥ
/*--------------------------------------------------------------------------------------*/
/// �����ʱ����Ϣ	DWJ
void	ThingHandleEx::OnGameTimer(UINT uTimerID)
{
	switch(uTimerID)
	{
	case 10://�¼���ʱ��id
		{
			pDesk->KillTimer(uTimerID);
			GameCPU(pDesk->sGameData.ApplyThingID);
			break;  
		}
	case TIME_WAIT_MSG: // �����¼�����Ӧ���ǳ�ʱ�Զ�����ϵͳ�Զ�����
		{
			//OutTimeHandle();
			break;
		}
	}
}

/*--------------------------------------------------------------------------------------*/
//	���õ�ǰ���ڷ������¼�	DWJ
void	ThingHandleEx::SetDoingThing(BYTE byStation,BYTE thing, BYTE byTime)
{
	pDesk->sGameData.m_byWatingThing = thing;
	// �ָ���ʱ����
	ReSetOutTime();
	switch(thing)
	{		
	case THING_BEGIN_OUT://ׯ�ҿ�ʼ����֪ͨ�¼�		
		{
			if(255 == byTime)
			{
				SetOutTime(byStation,pDesk->sGameData.m_mjRule.byOutTime,thing,true);
			}
			else
			{
				SetOutTime(byStation,byTime,thing,true);
			}
			
			break;
		}
	case THING_OUT_PAI://�����¼�
		{
			//������ �����й��� 1�����
			if(pDesk->sUserData.m_bTing[byStation] || pDesk->sUserData.m_bTuoGuan[byStation])
			{
				SetOutTime(byStation,pDesk->sGameData.m_mjRule.byAutoOutTime,thing,true);
			}
			else
			{
				if(255 == byTime)
				{
					SetOutTime(byStation,pDesk->sGameData.m_mjRule.byOutTime,thing,true);
				}
				else
				{
					SetOutTime(byStation,byTime,thing,true);
				}
			}
			break;
		}
	case THING_CHI_PAI:		//�����¼�				DWJ
	case THING_PENG_PAI:	//�����¼�				DWJ
	case THING_GANG_PAI:	//�����¼�				DWJ
		{
			//������ �����й��� 1�봦��
			if(pDesk->sUserData.m_bTing[byStation] || pDesk->sUserData.m_bTuoGuan[byStation])
			{
				SetOutTime(byStation,pDesk->sGameData.m_mjRule.byAutoOutTime,thing,true);
			}
			else
			{
				if(255 == byTime)
				{
					SetOutTime(byStation,pDesk->sGameData.m_mjRule.byBlockTime,thing,true);
				}
				else
				{
					SetOutTime(byStation,byTime,thing,true);
				}
			}
			break;
		}
	case THING_HU_PAI:		//�����¼�				DWJ
		{
			//�й��� 1�����
			if(pDesk->sUserData.m_bTuoGuan[byStation])
			{
				SetOutTime(byStation,pDesk->sGameData.m_mjRule.byAutoOutTime,thing,true);
			}
			else
			{
				if(255 == byTime)
				{
					SetOutTime(byStation,pDesk->sGameData.m_mjRule.byBlockTime,thing,true);
				}
				else
				{
					SetOutTime(byStation,byTime,thing,true);
				}
			}
			break;
		}
	}
}
/*--------------------------------------------------------------------------------------*/
/// �ָ���ʱ����	DWJ
void	ThingHandleEx::ReSetOutTime()
{
	pDesk->sGameData.m_MjWait.Clear();
}
/*--------------------------------------------------------------------------------------*/
/// ���ó�ʱ����
void	ThingHandleEx::SetOutTime(BYTE station,BYTE time,BYTE thing,bool effect)
{
	pDesk->sGameData.m_MjWait.byWaitThing	= thing;
	pDesk->sGameData.m_MjWait.byCurChair	= station;
	pDesk->sGameData.m_MjWait.byTime		= time + 1;
	pDesk->sGameData.m_MjWait.bEffect		= effect;
}
/*--------------------------------------------------------------------------------------*/
/// ��ʱ����
void	ThingHandleEx::OutTimeHandle()
{
	if(!pDesk->sGameData.m_MjWait.bEffect || pDesk->sGameData.m_MjWait.byCurChair == 255 || pDesk->sGameData.m_MjWait.byTime == 255)
	{
		return;
	}
	if(pDesk->sGameData.m_MjWait.byWaitThing != pDesk->sGameData.m_byWatingThing)
	{
		return;
	}
	if(pDesk->sGameData.m_MjWait.byTime == 255)
	{
		return;
	}
	pDesk->sGameData.m_MjWait.byTime -= 1;
	if(pDesk->sGameData.m_MjWait.byTime == 0)
	{
		this->AutoHandle();
	}
}
/*--------------------------------------------------------------------------------------*/
//��Ҵ���ʱ��ϵͳ�Զ�����	DWJ
void	ThingHandleEx::AutoHandle()
{
	switch(pDesk->sGameData.m_byWatingThing)
	{	
	case THING_BEGIN_OUT:	//ׯ�ҿ�ʼ�����Զ�������Ӧ
		{
			//ϵͳ������ҳ���
			AutoOutOrGet();
			break;
		}
	case THING_OUT_PAI:		//����Զ�����		DWJ
		{
			//ϵͳ������ҳ���
			AutoOutOrGet();
			break;
		}
	case THING_CHI_PAI:		//�Զ�������Ӧ		DWJ
	case THING_PENG_PAI:	//�Զ�������Ӧ		DWJ
	case THING_GANG_PAI:	//�Զ�������Ӧ		DWJ
		{
			//ϵͳ���������������
			AutoDoAction();
			break;
		}
	case THING_HU_PAI:		//�Զ�������Ӧ		DWJ
		{
			AutoHuPai();
			break;
		}
	}
}
/*--------------------------------------------------------------------------------------*/
///�Զ�������ƻ���ץ��
void	ThingHandleEx::AutoOutOrGet()
{
	bool haveout = false;
	for(int i=0;i<PLAY_COUNT;++i)
	{
		if(!pDesk->sUserData.IsOutPaiPeople(i))//�������
		{
			continue;
		}
		haveout = true;
		if(!pDesk->sUserData.m_bTing[i] && !pDesk->sUserData.m_bTuoGuan[i] && pDesk->sUserData.m_byTimeOut[i] < 3)
			pDesk->sUserData.m_byTimeOut[i]++;
		tagOutPaiEx outpai;
		outpai.Clear();
		outpai.byUser = i;
		outpai.byPs = pDesk->sUserData.GetLastHandPai(i);
		ReceiveUserOutCard(i,&outpai,sizeof(outpai),false);

		if(pDesk->sUserData.m_byTimeOut[i]>1 && !pDesk->sUserData.m_bTuoGuan[i] && !pDesk->sUserData.m_bTing[i] && !pDesk->m_bIsBuy)
		{
			UserTouGuan tuoGuan;
			tuoGuan.bIsTuoGuan = true;
			tuoGuan.byStation = i;
			ReceiveUserTuoGuan(i,&tuoGuan,sizeof(UserTouGuan),false);
		}
		break;

	}
	//û�г��Ƶ���ң�����ץ���¼�
	if(!haveout)
	{
		ApplyAction(THING_ZHUA_PAI,200);//������һ���¼�
	}
}

/*--------------------------------------------------------------------------------------*/
//	�Զ�������	DWJ
void	ThingHandleEx::AutoDoAction()
{
	//����Ҫ��������͸��ͻ��� ���߿ͻ��� ��ʱ���� ϵͳ�Զ�������
	ReceiveUserPassCheck(pDesk->sGameData.m_MjWait.byCurChair,NULL,0,false,true);
}
/*--------------------------------------------------------------------------------------*/
//	�Զ��������	DWJ
void	ThingHandleEx::AutoHuPai()
{
	//�������
	tagHuPaiEx hu;
	hu.Clear();
	hu.byUser	= pDesk->sGameData.m_MjWait.byCurChair;
	ReceiveUserHuCard(pDesk->sGameData.m_MjWait.byCurChair, &hu, sizeof(hu), false);
}