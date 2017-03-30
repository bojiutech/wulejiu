/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #include "stdafx.h"
#include "ThingHandle.h"
#include "../server/ServerManage.h"

ThingHandle::ThingHandle(void)
{	
}

ThingHandle::~ThingHandle(void)
{
}
/*------------------------------------------------------------------------------*/
//���������ָ��
void ThingHandle::SetDeskPoint(CServerGameDesk *desk)
{
	pDesk = desk;
}
/*------------------------------------------------------------------------------*/
//���������¼�������������Ӿͻ�ͨ���ýӿڻ�ȡ��Ϸ������
bool ThingHandle::GetGameStaton(BYTE bDeskStation, bool bWatchUser,BYTE GameStation)
{
	GameStationDataEx GameStationData;
	::memset(&GameStationData, 0, sizeof(GameStationData));
	GameStationData.iVersion	=  MAIN_VERSION;
	GameStationData.iVersion2	= ASS_VERSION;
	//��ȡ���䱶�����ܷ���

	GameStationData.byGameStation = pDesk->m_byGameStation;		 //��Ϸ״̬
	//��������ȡ���й�
	pDesk->sUserData.m_bTuoGuan[bDeskStation] = false;
	for(int i=0;i<4;++i)
	{
		memset(GameStationData.m_byArHandPai,255,sizeof(GameStationData.m_byArHandPai));

		pDesk->sUserData.CopyGCPData(i,GameStationData.m_UserGCPData[i]);
		pDesk->sUserData.CopyOutPai(i,GameStationData.m_byArOutPai[i]);
		pDesk->sUserData.CopyMenPai(i,GameStationData.m_iArMenPai[i]);
		pDesk->sUserData.CopyHuaPai(i,GameStationData.m_byArHuaPai[i]);
		//GameStationData.m_bTing[i] = pDesk->sUserData.m_bTing[i];
		GameStationData.m_bistuoguan[i] = pDesk->sUserData.m_bTuoGuan[i];
	}
	pDesk->sUserData.CopyHandPai(GameStationData.m_byArHandPai,bDeskStation,false);
	//GameStationData.m_byOtherOutPai = pDesk->sUserData.m_byOtherOutPai;
	GameStationData.m_byThingDoing = pDesk->sGameData.m_byThingDoing;
	//GameStationData.byQuanFeng = pDesk->sUserData.m_byQuanFeng;
	GameStationData.byNtStation = pDesk->sGameData.m_byNtStation;
	GameStationData.m_byNowOutStation = pDesk->sUserData.m_byNowOutStation;
	//GameStationData.m_StrJing = pDesk->sUserData.m_StrJing;

	//GameStationData.byAutoOutTime = pDesk->sGameData.m_mjRule.byAutoOutTime;		//�Զ�����ʱ��
	GameStationData.byOutTime = pDesk->sGameData.m_mjRule.byOutTime;				//����ʱ��
	//GameStationData.byThinkTime = pDesk->sGameData.m_mjRule.byBlockTime;			//˼��ʱ��
	GameStationData.byBeginTime = pDesk->sGameData.m_mjRule.byBeginTime;			//��ʼ�ȴ�ʱ��
	//GameStationData.bAutoBegin =  pDesk->sGameData.m_mjRule.bAutoBegin;			//ʱ�䵽���Ƿ��Զ���ʼ

	if(!bWatchUser)
	{
		pDesk->sUserData.m_bFoceLeave[bDeskStation] = false;
		//��������ȡ���й�
		pDesk->sUserData.m_bTuoGuan[bDeskStation] = false;
		//pDesk->sUserData.Isu
	}
	OutputDebugString(TEXT("�齫-������������ OnGetGameStation  "));
	switch (pDesk->m_byGameStation)
	{
	case GS_WAIT_SETGAME:		//��Ϸû�п�ʼ״̬
		{
			//��������
			pDesk->SendGameStationEx(bDeskStation, bWatchUser, &GameStationData, sizeof(GameStationData));
			MessageStruct Mess;
			ZeroMemory(Mess.Message, 200);
			lstrcpy(Mess.Message, TEXT("�gӭ�����錢�Α�,ף������_�ģ�"));
			pDesk->SendGameDataEx(bDeskStation, &Mess, sizeof(Mess), MDM_GM_GAME_NOTIFY, ASS_MESSAGE, 0);
			return true;
		}
	case GS_WAIT_ARGEE:			//�ȴ���ҿ�ʼ״̬
	case GS_SEND_CARD:		//����״̬(��δ����)
		{
			//��������
			pDesk->SendGameStationEx(bDeskStation,  bWatchUser, &GameStationData, sizeof(GameStationData));
			return true;
		}
	case GS_PLAY_GAME:	//��Ϸ��״̬
		{
			//��������
			pDesk->SendGameStationEx(bDeskStation,  bWatchUser, &GameStationData, sizeof(GameStationData));
			if(pDesk->sGameData.T_CPGNotify[bDeskStation].m_byMaxThing > ACTION_NO && pDesk->sGameData.T_CPGNotify[bDeskStation].m_byMaxThing <= ACTION_HU)//����г����ܾͽ��д���
			{
				pDesk->SendGameDataEx(bDeskStation, &pDesk->sGameData.T_CPGNotify[bDeskStation], sizeof(pDesk->sGameData.T_CPGNotify[bDeskStation]), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
			}
			return true;
		}
	case GS_WAIT_NEXT:		//�ȴ���һ����Ϸ��ʼ
		{
			//��������
			pDesk->SendGameStationEx(bDeskStation,  bWatchUser, &GameStationData, sizeof(GameStationData));
			return true;
		}
	}
	return true;
}

///���ղ�������Ϣ
int ThingHandle::HandleNotifyMessage(int bDeskStation, UINT code, BYTE* pData, int uSize, bool bWatchUser)
{
	pDesk->KillTimer(TIME_CHECK_GAME_MSG);
	pDesk->SetTimer(TIME_CHECK_GAME_MSG,TIME_DEFAULT_HANDLE);//�������ó�ʱ��ʱ��

	switch (code)
	{
	case ASS_GM_SHORT_STOP:
		{
			return 0;
		}
		break;
	case ASS_SEZIFINISH:	//ɫ�Ӷ�������
		{
			return ReceiveSeziFinish(bDeskStation, pData, uSize, bWatchUser);
		}
	case ASS_AUTOCARD://�й�
		{	
			return ReceiveUserTuoGuan(bDeskStation, pData, uSize, bWatchUser);
		}
		break;
	case THING_OUT_PAI:
		{
			// �û�����
			return ReceiveUserOutCard(bDeskStation, pData, uSize, bWatchUser);
		}
		break;
	case ASS_PASS_CHECK:		
		{
			return ReceiveUserPassCheck(bDeskStation, pData, uSize,   bWatchUser);
		}
		break;
	case ASS_GM_AGREE_GAME:		
		{
			//�յ��û�ͬ����Ϸ��Ϣ
			return ReceiveUserAgreeGame(bDeskStation, pData, uSize,   bWatchUser);
		}
		break;
	case THING_CHI_PAI:	
		{
			// �û�����
			return ReceiveUserChiCard(bDeskStation, pData, uSize, bWatchUser);
		}
		break;
	case THING_PENG_PAI:
		{// �û�����
			return ReceiveUserPengCard(bDeskStation, pData, uSize, bWatchUser);
		}
		break;;
	case THING_GANG_PAI:
		{// �û�����
			return ReceiveUserGangCard(bDeskStation, pData, uSize, bWatchUser);
		}
		break;
	case THING_TING_PAI:
		{// �û�����
			return ReceiveUserTingCard(bDeskStation, pData, uSize, bWatchUser);
		}
		break;
	case THING_HU_PAI:		
		{// �û�����
			return ReceiveUserHuCard(bDeskStation, pData, uSize, bWatchUser);
		}
		break;
	case ASS_HAVE_THING:	
		{//���������뿪
			return ReceiveUserHaveThing(bDeskStation, pData, uSize,   bWatchUser);
		}
		break;
	case ASS_LEFT_RESULT: 
		{//ͬ���û��뿪
			return ReceiveArgeeUserLeft(bDeskStation, pData, uSize,   bWatchUser);
		}
		break;
	case ASS_EXIT://�ȴ���ʼһ�¾�ʱ�˳�
		{
			if(pDesk->m_byGameStation==23)
				return pDesk->GameFinish(bDeskStation,GF_SALE);
			else
				return 0;
		}
		break;
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

////////////////////////////////////////���������Ϣ//////////////////////////////////////////////////////

// �յ��û�ɫ�Ӷ���������Ϣ
int ThingHandle::ReceiveSeziFinish(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser)
{
	if(!pDesk->sUserData.m_bWaitSezi || bWatchUser)//�Ƿ���ȴ�ɫ�Ӷ�������״̬
		return 0;
	pDesk->sUserData.m_bSiziFinish[bDeskStation] = true;

	char strbug[800];
	wsprintf(strbug,TEXT("�齫-�¼��������� ReceiveSeziFinish  λ�� bDeskStation =%d ApplyThingID=%d"),bDeskStation,pDesk->sGameData.ApplyThingID);
	OutputDebugString(strbug);

	for(int i=0;i<PLAY_COUNT;i++)
	{
		if(!pDesk->sUserData.m_bSiziFinish[i])//�����û�з���ɫ�ӽ�����Ϣ
			return 0;
	}


	//�������ʱ��
	memset(pDesk->sUserData.m_bSiziFinish,0,sizeof(pDesk->sUserData.m_bSiziFinish));
	pDesk->sUserData.m_bWaitSezi = false;

	ApplyAction(0,500);
	return 0;
}

// �յ��й���Ϣ
int ThingHandle::ReceiveUserTuoGuan(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser)
{
	if(bWatchUser)
		return 0;
	if(bWatchUser || pDesk->m_byGameStation > GS_PLAY_GAME || pDesk->m_byGameStation < GS_SEND_CARD)//������Ϸ�в����й�
		return 0;

 //   UserTouGuan *pCmd = (UserTouGuan *)pData;
	//UserTouGuan touguan;
	//touguan.desk = bDeskStation;
	//touguan.touguang = pCmd->touguang;

	//pDesk->sUserData.m_bTuoGuan[bDeskStation]=touguan.touguang;
	//for(int i=0;i<PLAY_COUNT;++i)
	//{
	//	touguan.bTuoGuan[i] = pDesk->sUserData.m_bTuoGuan[i];		// ��������й�״̬
	//}
	//for(int i=0;i<PLAY_COUNT;i++)
	//{
	//	pDesk->SendGameDataEx(i,&touguan,sizeof(Usertouguan),MDM_GM_GAME_NOTIFY,ASS_AUTOCARD,0);
	//	pDesk->SendWatchDataEx(i,&touguan,sizeof(Usertouguan),MDM_GM_GAME_NOTIFY,ASS_AUTOCARD,0);
	//}
	return 0;
}

// �û�����
int ThingHandle::ReceiveUserOutCard(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser)
{
	tagOutPaiEx * pOutCard = (tagOutPaiEx *)pData;

	if(pOutCard == NULL || bWatchUser || pDesk->m_byGameStation != GS_PLAY_GAME)
	{
		return 0;
	}
	if(pOutCard->byPs == 255 || pDesk->sUserData.GetAHandPaiCount(bDeskStation,pOutCard->byPs)==0 || !pDesk->sUserData.IsOutPaiPeople(bDeskStation))
	{
		return 0;
	}

	pDesk->sGameData.T_OutPai = * pOutCard;
	pDesk->sGameData.m_byThingDoing = THING_OUT_PAI;//��¼����ִ�е��¼�
	pDesk->sGameData.m_byMaxAction = ACTION_NO;
	pDesk->sUserData.m_byOtherOutPai = pOutCard->byPs;
	//ɾ��һ������
	pDesk->sUserData.DelleteAHandPai(bDeskStation,pOutCard->byPs);
	//���һ�ų���
	pDesk->sUserData.AddToOutPai(bDeskStation,pOutCard->byPs);
	//��¼�Ѿ���������
	pDesk->sUserData.m_bHaveOut[bDeskStation] = true;
	//������ʱ����
	ClearTempData();

	//��ҵ��������
	if(pDesk->sGameData.T_TingPai.bHitTing[bDeskStation] && !pDesk->sUserData.m_bTing[bDeskStation])//��ҵ��������,
	{
		pDesk->sGameData.T_TingPai.bHitTing[bDeskStation] = false;
		if(CLogicBase::IsHaveInArr(pDesk->sGameData.T_CPGNotify[bDeskStation].m_byTingCanOut,pOutCard->byPs,HAND_CARD_NUM))
		{
			pDesk->sUserData.m_bTing[bDeskStation] = true;
//			pDesk->sGameData.T_OutPai.bTing = true;
		}
		else
		{
			pDesk->sUserData.m_bTing[bDeskStation] = false;
			pDesk->sGameData.T_TingPai.bHitTing[bDeskStation] = false;
		}
	}
	//��������
	for(int i=0;i<PLAY_COUNT;++i)
	{
		pDesk->sUserData.CopyOutPai(i,pDesk->sGameData.T_OutPai.m_byArOutPai[i]);
	}
	///��ǰץ�Ʒ���true ˳ʱ�룬false ��ʱ��
	pDesk->sUserData.m_bZhuaPaiDir = true;
	for(int i=0;i<PLAY_COUNT;i++)//��ȡ����״̬
	{
//		pDesk->sGameData.T_OutPai.bUserTing[i] = pDesk->sUserData.m_bTing[i];
	}
	//���ͳ�������
	for (int i=0;i<PLAY_COUNT;i++)
	{	
		memset(pDesk->sGameData.T_OutPai.m_byArHandPai,255,sizeof(pDesk->sGameData.T_OutPai.m_byArHandPai));
		pDesk->sUserData.CopyHandPai(pDesk->sGameData.T_OutPai.m_byArHandPai,i,false);
		pDesk->SendGameDataEx(i, &pDesk->sGameData.T_OutPai, sizeof(pDesk->sGameData.T_OutPai), MDM_GM_GAME_NOTIFY, THING_OUT_PAI, 0);
		pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_OutPai, sizeof(pDesk->sGameData.T_OutPai), MDM_GM_GAME_NOTIFY, THING_OUT_PAI, 0);
	}

	//������⣺û��������Ӧ��ֱ��ץ��
	if(!CheckAction(bDeskStation,pOutCard->byPs,2))
	{//û�ж�����ֱ����һ�����ץ��
		pDesk->sGameData.ApplyThingID = THING_ZHUA_PAI;
		ApplyAction(THING_ZHUA_PAI,500);	//������һ���¼�
	}
	else
	{
		for (int i=0;i<PLAY_COUNT;i++)
		{	
			if(i==bDeskStation || pDesk->sUserData.m_bFoceLeave[i] || pDesk->sGameData.T_CPGNotify[i].m_byMaxThing == ACTION_NO)
				continue;
			pDesk->SendGameDataEx(i, &pDesk->sGameData.T_CPGNotify[i], sizeof(pDesk->sGameData.T_CPGNotify[i]), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
			pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_CPGNotify[i], sizeof(pDesk->sGameData.T_CPGNotify[i]), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
		}
		if(pDesk->sGameData.m_mjRule.bNetCutTuoGuan)
		{
			NetCutAutoHandle();
		}
	}
	pDesk->sUserData.m_byApplyMaxAction = ACTION_NO;//��ҵ�ǰ���������¼�������������󣬻ָ�����

	return 0;
}

// �յ��û�pass ��Ϣ
int ThingHandle::ReceiveUserPassCheck(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser)
{
	if(pDesk->sGameData.ApplyThingID != 255 || bWatchUser)//�������¼��Ͳ���Ӧpass��Ϣ
		return 0;

	pDesk->sGameData.T_CPGNotify[bDeskStation].bHaveReturn = true;//��¼��һ�Ӧ
	pDesk->sGameData.T_CPGNotify[bDeskStation].m_byMaxThing = ACTION_NO;//�ı���������������
	CheckNextAction();	
	return 0;
}

//�յ��û�ͬ����Ϸ��Ϣ
int ThingHandle::ReceiveUserAgreeGame(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser)
{
	//�û�ͬ����Ϸ
	if (bWatchUser || (pDesk->m_byGameStation != GS_WAIT_ARGEE) && (pDesk->m_byGameStation != GS_WAIT_NEXT)) 
		return 0;
	for(int i=0;i<HAND_CARD_NUM;i++)
	{
		pDesk->SendGameDataEx(i, MDM_GM_GAME_NOTIFY, ASS_GM_AGREE_GAME, 0);
		pDesk->SendWatchDataEx(i, MDM_GM_GAME_NOTIFY, ASS_GM_AGREE_GAME, 0);
	}
	return 0;
}

//���������뿪
int ThingHandle::ReceiveUserHaveThing(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser)
{
	if(bWatchUser)				return 0;
	HaveThingStruct * pThing=(HaveThingStruct *)pData;
	if (pDesk->m_byGameStation<GS_SEND_CARD) return 0;
	//{//�����û������뿪
	HaveThingStruct HaveThing;
	HaveThing.pos = bDeskStation;
	::CopyMemory(HaveThing.szMessage,pThing->szMessage,60*sizeof(char));
	for (int i=0;i<PLAY_COUNT;i++)
	{
		if (i!=bDeskStation) pDesk->SendGameDataEx(i,&HaveThing,sizeof(HaveThing),MDM_GM_GAME_NOTIFY,ASS_HAVE_THING,0);
	}
	return 0;
}

//ͬ���û��뿪
int ThingHandle::ReceiveArgeeUserLeft(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser)
{
	if(bWatchUser)				return false;
	LeaveResultStruct * pLeave=(LeaveResultStruct *)pData;
	if (pLeave->bArgeeLeave)
	{
		pDesk->sUserData.m_byAgreeLeaveNum++;
	}
	else
	{
		pDesk->sUserData.m_byAgreeLeaveNum = 0;//ͬ�������Ϸ���������
	}
	if(pDesk->sUserData.m_byAgreeLeaveNum<(PLAY_COUNT-1))
	{//������ҷ���

		LeaveResultStruct Leave;
		Leave.bDeskStation=bDeskStation;
		Leave.bArgeeLeave=pLeave->bArgeeLeave;
		for (int i=0;i<PLAY_COUNT;i++) 
			if (i!=bDeskStation) pDesk->SendGameDataEx(i,&Leave,sizeof(Leave),MDM_GM_GAME_NOTIFY,ASS_LEFT_RESULT,0);
	}
	else 
	{
		pDesk->sUserData.m_byAgreeLeaveNum = 0;
		pDesk->GameFinish(255,GF_SALE);		
	}
	return 0;
}

// �û�������Ϣ
int ThingHandle::ReceiveUserChiCard(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser)
{

	tagChiPaiEx * pChiCard = (tagChiPaiEx *)pData;
	if(pChiCard == NULL || bWatchUser || pDesk->m_byGameStation != GS_PLAY_GAME)
		return 0;
	if(bDeskStation == pDesk->sUserData.m_byNowOutStation || !pDesk->sGameData.T_CPGNotify[bDeskStation].bChi || pChiCard->byPs == 255 || !pDesk->sGameData.m_mjAction.bChi)
	{//���Ϸ�����
		return 0;
	}
	if(pDesk->sUserData.m_byApplyMaxAction < ACTION_CHI)
	{
		pDesk->sUserData.m_byApplyMaxAction = ACTION_CHI;//��ҵ�ǰ���������¼�
	}
	pDesk->sGameData.temp_ChiPai.Clear();
	pDesk->sGameData.temp_ChiPai = * pChiCard;//��¼��ʱ��������

	pDesk->sGameData.T_CPGNotify[pChiCard->byUser].bHaveReturn = true;//��¼��һ�Ӧ
	pDesk->sGameData.T_CPGNotify[pChiCard->byUser].m_byMaxThing = ACTION_CHI;//�ı���������������
	if(pDesk->sGameData.m_byMaxAction < ACTION_CHI)
	{
		pDesk->sGameData.m_byMaxAction = ACTION_CHI;
	}
	//�����һ������
	CheckNextAction();
	return 0;
}

// �û�������Ϣ
int ThingHandle::ReceiveUserPengCard(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser)
{
	tagPengPaiEx * pPengCard = (tagPengPaiEx *)pData;
	if(pPengCard == NULL || bWatchUser ||  pDesk->m_byGameStation != GS_PLAY_GAME)
		return 0;
	if(bDeskStation == pDesk->sUserData.m_byNowOutStation || !pDesk->sGameData.T_CPGNotify[bDeskStation].bPeng || pPengCard->byPs == 255 || !pDesk->sGameData.m_mjAction.bPeng)
	{//���Ϸ�����
		return 0;
	}
	if(pDesk->sUserData.m_byApplyMaxAction < ACTION_PENG)
	{
		pDesk->sUserData.m_byApplyMaxAction = ACTION_PENG;//��ҵ�ǰ���������¼�
	}
	pDesk->sGameData.temp_PengPai.Clear();
	pDesk->sGameData.temp_PengPai = * pPengCard;//��¼��ʱ��������
	pDesk->sGameData.T_CPGNotify[pPengCard->byUser].bHaveReturn = true;//��¼��һ�Ӧ
	pDesk->sGameData.T_CPGNotify[pPengCard->byUser].m_byMaxThing = ACTION_PENG;//�ı���������������
	if(pDesk->sGameData.m_byMaxAction < ACTION_PENG)
	{
		pDesk->sGameData.m_byMaxAction = ACTION_PENG;
	}
	//�����һ������
	CheckNextAction();
	return 0;
}

// �û�������Ϣ
int ThingHandle::ReceiveUserGangCard(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser)
{
	tagGangPaiEx * pGangCard = (tagGangPaiEx *)pData;
	if(pGangCard == NULL || bWatchUser || pDesk->m_byGameStation != GS_PLAY_GAME)
		return 0;
	if(!pDesk->sGameData.T_CPGNotify[bDeskStation].bGang || pGangCard->byPs == 255 || !pDesk->sGameData.m_mjAction.bGang)
	{//���Ϸ�����
		return 0;
	}

	bool action = false;
	pDesk->sGameData.temp_GangPai.Clear();
	pDesk->sGameData.temp_GangPai = * pGangCard;//��¼��ʱ��������
	if(pGangCard->byType == ACTION_BU_GANG)
	{
		action = CheckAction(pGangCard->byUser,pGangCard->byPs,3);//����Ƿ��н�ȡ���ܵĶ��������Ƶ�
	}
	if(pGangCard->byType == ACTION_MING_GANG)//���ܣ���¼����
	{
		pDesk->sGameData.T_CPGNotify[pGangCard->byUser].bHaveReturn = true;//��¼��һ�Ӧ
		pDesk->sGameData.T_CPGNotify[pGangCard->byUser].m_byMaxThing = ACTION_MING_GANG;//�ı���������������
		if(pDesk->sGameData.m_byMaxAction < ACTION_MING_GANG)
		{
			pDesk->sGameData.m_byMaxAction = ACTION_MING_GANG;
		}
	}

	switch(pGangCard->byType)
	{
	case ACTION_AN_GANG:
		{
			if(pDesk->sUserData.m_byApplyMaxAction < ACTION_AN_GANG)
			{
				pDesk->sUserData.m_byApplyMaxAction = ACTION_AN_GANG;//��ҵ�ǰ���������¼�
			}
			//���ܿ��Լ�ʱִ�ж���
			BYTE NextID=255,StarTime=255;//�¸��¼���id,255ʱΪ�����¼���Ҫ�ͻ����أ�StarTime�೤ʱ���ʼִ�У�100����Ϊ��λ��
			HandleGangPai(NextID,StarTime);//�����¼�����
			pDesk->sGameData.ApplyThingID = NextID;
			ApplyAction(NextID,StarTime*100);//������һ���¼�
			//���͸�����Ϣ
			for (int i=0;i<PLAY_COUNT;i++)
			{	
				pDesk->sUserData.CopyHandPai(pDesk->sGameData.T_GangPai.m_byArHandPai,i,false);
				pDesk->SendGameDataEx(i, &pDesk->sGameData.T_GangPai, sizeof(pDesk->sGameData.T_GangPai), MDM_GM_GAME_NOTIFY, THING_GANG_PAI, 0);
				pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_GangPai, sizeof(pDesk->sGameData.T_GangPai), MDM_GM_GAME_NOTIFY, THING_GANG_PAI, 0);
			}
		}
		break;
	case ACTION_BU_GANG:
		{
			if(pDesk->sUserData.m_byApplyMaxAction < ACTION_BU_GANG)
			{
				pDesk->sUserData.m_byApplyMaxAction = ACTION_BU_GANG;//��ҵ�ǰ���������¼�
			}
			if(!action)//�������ܣ�ֱ�Ӵ���
			{
				BYTE NextID=255,StarTime=255;//�¸��¼���id,255ʱΪ�����¼���Ҫ�ͻ����أ�StarTime�೤ʱ���ʼִ�У�100����Ϊ��λ��
				HandleGangPai(NextID,StarTime);//�����¼�����
				pDesk->sGameData.ApplyThingID = NextID;
				ApplyAction(NextID,StarTime*100);//������һ���¼�
				for (int i=0;i<PLAY_COUNT;i++)
				{	
					pDesk->sUserData.CopyGCPData(i,pDesk->sGameData.T_GangPai.m_UserGCPData[i]);
				}
				//���͸�����Ϣ
				for (int i=0;i<PLAY_COUNT;i++)
				{						
					pDesk->sUserData.CopyHandPai(pDesk->sGameData.T_GangPai.m_byArHandPai,i,false);
					pDesk->SendGameDataEx(i, &pDesk->sGameData.T_GangPai, sizeof(pDesk->sGameData.T_GangPai), MDM_GM_GAME_NOTIFY, THING_GANG_PAI, 0);
					pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_GangPai, sizeof(pDesk->sGameData.T_GangPai), MDM_GM_GAME_NOTIFY, THING_GANG_PAI, 0);
				}
			}
			else///�������ܣ�����������Ϣ�����˼��
			{
				for (int i=0;i<PLAY_COUNT;i++)
				{	
					if(!pDesk->sGameData.T_CPGNotify[i].bCanAction || pDesk->sUserData.m_bFoceLeave[i])
						continue;
					pDesk->SendGameDataEx(i, &pDesk->sGameData.T_CPGNotify[i], sizeof(pDesk->sGameData.T_CPGNotify[i]), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
					pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_CPGNotify[i], sizeof(pDesk->sGameData.T_CPGNotify[i]), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
				}
				if(pDesk->sGameData.m_mjRule.bNetCutTuoGuan)
				{
					NetCutAutoHandle();
				}
				return true;
			}
		}
		break;
	case ACTION_MING_GANG://����
		{
			if(pDesk->sUserData.m_byApplyMaxAction < ACTION_MING_GANG)
			{
				pDesk->sUserData.m_byApplyMaxAction = ACTION_MING_GANG;//��ҵ�ǰ���������¼�
			}
			//�����һ������
			CheckNextAction();
			return true;
		}
		break;
	}

	return 0;
}

// �û�������Ϣ
int ThingHandle::ReceiveUserTingCard(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser)
{
	tagTingPaiEx * pTingCard = (tagTingPaiEx *)pData;
	if(pTingCard == NULL || bWatchUser || pDesk->m_byGameStation != GS_PLAY_GAME)
		return 0;
	if(!pDesk->sGameData.T_CPGNotify[bDeskStation].bTing || !pDesk->sGameData.m_mjAction.bTing)
	{//���Ϸ�����
		return 0;
	}
	if(pDesk->sUserData.m_byApplyMaxAction < ACTION_TING)
	{
		pDesk->sUserData.m_byApplyMaxAction = ACTION_TING;//��ҵ�ǰ���������¼�
	}
	pDesk->sGameData.T_TingPai.bHitTing[pTingCard->byUser] = true;
	//֪ͨ�������
	for (int i=0;i<PLAY_COUNT;i++)
	{	
		pDesk->SendGameDataEx(i, &pDesk->sGameData.T_TingPai, sizeof(pDesk->sGameData.T_TingPai), MDM_GM_GAME_NOTIFY, THING_TING_PAI, 0);
		pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_TingPai, sizeof(pDesk->sGameData.T_TingPai), MDM_GM_GAME_NOTIFY, THING_TING_PAI, 0);
	}
	return 0;
}

// �û�������Ϣ
int ThingHandle::ReceiveUserHuCard(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser)
{
	tagHuPaiEx * pHuCard = (tagHuPaiEx *)pData;
	if(pHuCard == NULL || bWatchUser || pDesk->m_byGameStation != GS_PLAY_GAME)
		return 0;
	if(!pDesk->sGameData.T_CPGNotify[bDeskStation].bHu)
	{//���Ϸ�����
		return 0;
	}

	if(pDesk->sUserData.m_byApplyMaxAction < ACTION_HU)
	{
		pDesk->sUserData.m_byApplyMaxAction = ACTION_HU;//��ҵ�ǰ���������¼�
	}

	if(bDeskStation == pDesk->sUserData.m_byNowOutStation)//��ǰ������Һ���(����)
	{
		pDesk->sGameData.T_HuPai.bZimo = true;
	}
	pDesk->sGameData.T_HuPai.byDianPao = pHuCard->byDianPao;
	pDesk->sGameData.T_HuPai.bHaveHu[pHuCard->byUser] = true;
	pDesk->sGameData.T_HuPai.byUserNum++;
//	pDesk->sGameData.T_HuPai.byNt = pDesk->sGameData.m_byNtStation;		//ׯ��λ��
	pDesk->sGameData.T_HuPai.byPs = pHuCard->byPs;				//���ڵ���ֵ

	pDesk->sGameData.T_CPGNotify[pHuCard->byUser].bHaveReturn = true;//��¼��һ�Ӧ
	pDesk->sGameData.T_CPGNotify[pHuCard->byUser].m_byMaxThing = ACTION_HU;//�ı���������������

	if(pDesk->sGameData.T_HuPai.byUser == 255)
	{
		pDesk->sGameData.T_HuPai.byUser = pHuCard->byUser;
	}
	else if(!pDesk->sGameData.T_HuPai.bZimo)//ѡ�񿿺�������������Һ���
	{//���ں��ƣ������ж����ҿ��Ժ���
		pDesk->sGameData.T_HuPai.byUser = GetCanHuUser(pDesk->sUserData.m_byNowOutStation,pDesk->sGameData.T_HuPai.bHaveHu,pDesk->sGameData.T_HuPai.byUser);//��ȡ�������ҽ������
	}

	if(pDesk->sGameData.m_byMaxAction < ACTION_HU)
	{
		pDesk->sGameData.m_byMaxAction = ACTION_HU;
	}
	for(int i=0;i<MAX_HUPAI_TYPE;++i)
	{
		pDesk->sGameData.T_HuPai.byHuType[pHuCard->byUser][i] = pDesk->sGameData.T_CPGNotify[pHuCard->byUser].byHuType[i];
	}
	for(int i=0;i<HAND_CARD_NUM;++i)
	{
		pDesk->sGameData.T_HuPai.m_byArHandPai[pHuCard->byUser][i] = pDesk->sUserData.m_byArHandPai[pHuCard->byUser][i];
	}
	for(int i=0;i<4;++i)
	{
//		pDesk->sUserData.CopyGCPData(i,pDesk->sGameData.T_HuPai.m_UserGCPData[i]);
	}

	if(pDesk->sGameData.T_HuPai.bZimo)//���������������
	{
		BYTE NextID=255,StarTime=255;//�¸��¼���id,255ʱΪ�����¼���Ҫ�ͻ����أ�StarTime�೤ʱ���ʼִ�У�100����Ϊ��λ��
		HandleHuPai(NextID,StarTime);//�����¼�����
		pDesk->sGameData.ApplyThingID = NextID;
		ApplyAction(NextID,StarTime*100);//������һ���¼�
		//���ͺ���֪ͨ
		///֪ͨ��Һ�����
		memset(pDesk->sGameData.T_HuPai.m_byArHandPai,255,sizeof(pDesk->sGameData.T_HuPai.m_byArHandPai));
		pDesk->sUserData.CopyHandPai(pDesk->sGameData.T_HuPai.m_byArHandPai,0,true);
		for (int i=0;i<PLAY_COUNT;i++)
		{	
			//pDesk->sUserData.CopyGCPData(i,pDesk->sGameData.T_HuPai.m_UserGCPData[i]);
			pDesk->SendGameDataEx(i, &pDesk->sGameData.T_HuPai, sizeof(pDesk->sGameData.T_HuPai), MDM_GM_GAME_NOTIFY, THING_HU_PAI, 0);
			pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_HuPai, sizeof(pDesk->sGameData.T_HuPai), MDM_GM_GAME_NOTIFY, THING_HU_PAI, 0);
		}
	}
	else
	{
		//�����һ������
		CheckNextAction();
	}
	return 0;
}

///�յ������ͻ�����������Ϣ
void ThingHandle::ReceiveSuperChangePai(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser)
{
	if(bWatchUser || bDeskStation<0 || bDeskStation>3)
		return;
	SuperStruct *Super =(SuperStruct* )pData;
	bool cpg = false;
	pDesk->sUserData.m_SetData[bDeskStation].Init();
	pDesk->sUserData.m_SetData[bDeskStation].bySetType = Super->bySetType;
	pDesk->sUserData.m_SetData[bDeskStation].mjcount = Super->mjcount;
	for(int i=0;i<Super->mjcount;++i)
	{
		pDesk->sUserData.m_SetData[bDeskStation].mjdata[i] = Super->mjdata[i];
		pDesk->sUserData.m_SetData[bDeskStation].handdata[i] = Super->handdata[i];
	}
	//�������ͣ�0 �������ƣ�1��ѡ���ƣ�2�����Լ�����һ���ƣ�3������ǿ����һ����
	switch(Super->bySetType)
	{
	case 0://����������
		{
			pDesk->sUserData.ChangeAllHandPai(bDeskStation,Super->mjdata,Super->mjcount);
			///����ǵ�ǰ������ң���Ⲣ���ؼ����
			if(bDeskStation == pDesk->sUserData.m_byNowOutStation)//����������ǵ�ǰ�������
			{
				if(CheckAction(bDeskStation,pDesk->sUserData.GetLastHandPai(bDeskStation),0))
				{
					cpg = true;
				}
			}
		}
		break;
	case 1://����������
		{
			pDesk->sUserData.ChangeSomeHandPai(bDeskStation,Super->mjdata,Super->handdata,Super->mjcount);
			///����ǵ�ǰ������ң���Ⲣ���ؼ����
			if(bDeskStation == pDesk->sUserData.m_byNowOutStation)//����������ǵ�ǰ�������
			{
				if(CheckAction(bDeskStation,pDesk->sUserData.GetLastHandPai(bDeskStation),0))
				{
					cpg = true;
				}
			}
		}	
		break;
	case 2://�����Լ�����һ����
		{	
			pDesk->sUserData.m_bySetMoPai[bDeskStation]	 = Super->mjdata[0];
		}
		break;
	case 3://������ǽ����һ����
		{
			pDesk->sUserData.SetGameNextPai(Super->mjdata[0]);
		}
		break;
	}
	if(Super->bySetType == 0 || Super->bySetType == 1)
	{
		SuperStruct superdata = *Super;
		for(int i=0;i<HAND_CARD_NUM;i++)
		{
			superdata.mjdata[i] = pDesk->sUserData.m_byArHandPai[bDeskStation][i];//�����������ݷ��͸��ͻ��˸���

		}
		pDesk->SendGameDataEx(bDeskStation, &superdata, sizeof(SuperStruct), MDM_GM_GAME_NOTIFY, ASS_SUPER, 0);
		pDesk->SendWatchDataEx(bDeskStation, &superdata, sizeof(SuperStruct), MDM_GM_GAME_NOTIFY, ASS_SUPER, 0);
	}
	if(cpg && bDeskStation == pDesk->sUserData.m_byNowOutStation)//���ƺ��ܽ��г����ܲ���
	{
		if(!pDesk->sUserData.m_bFoceLeave[bDeskStation])
		{
			pDesk->sGameData.T_CPGNotify[bDeskStation].bZhuaPai = true;
			pDesk->SendGameDataEx(bDeskStation, &pDesk->sGameData.T_CPGNotify[bDeskStation], sizeof(tagCPGNotifyEx), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
			pDesk->SendWatchDataEx(bDeskStation, &pDesk->sGameData.T_CPGNotify[bDeskStation], sizeof(tagCPGNotifyEx), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
		}
	}
}


///���ƣ�CheckNextAction
///�����������һ������
void ThingHandle::CheckNextAction()
{
	if(!IsCanHandle())
	{
		return ;
	}	
	BYTE NextID=255,StarTime=255;//�¸��¼���id,255ʱΪ�����¼���Ҫ�ͻ����أ�StarTime�೤ʱ���ʼִ�У�100����Ϊ��λ��

	switch(pDesk->sGameData.m_byMaxAction)//ȷ������һ������Ӧ�¼����ԣ������ܣ���
	{
	case ACTION_CHI:				//���ƶ���
		{
			HandleChiPai(NextID,StarTime);
			//֪ͨ�������
			for (int i=0;i<PLAY_COUNT;i++)
			{	
				memset(pDesk->sGameData.T_ChiPai.m_byArHandPai,255,sizeof(pDesk->sGameData.T_ChiPai.m_byArHandPai));
				pDesk->sUserData.CopyHandPai(pDesk->sGameData.T_ChiPai.m_byArHandPai,i,false);
				pDesk->SendGameDataEx(i, &pDesk->sGameData.T_ChiPai, sizeof(pDesk->sGameData.T_ChiPai), MDM_GM_GAME_NOTIFY, THING_CHI_PAI, 0);
				pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_ChiPai, sizeof(pDesk->sGameData.T_ChiPai), MDM_GM_GAME_NOTIFY, THING_CHI_PAI, 0);
			}
			//�ж��Ƿ�������
			if(pDesk->sGameData.m_mjAction.bTing && pDesk->sGameData.T_CPGNotify[pDesk->sGameData.T_ChiPai.byUser].bTing)//������
			{//������������
				pDesk->sGameData.T_CPGNotify[pDesk->sGameData.T_ChiPai.byUser].byUser = pDesk->sGameData.T_ChiPai.byUser;
				pDesk->sGameData.T_CPGNotify[pDesk->sGameData.T_ChiPai.byUser].bZhuaPai = true;
				pDesk->SendGameDataEx(pDesk->sGameData.T_ChiPai.byUser, &pDesk->sGameData.T_CPGNotify[pDesk->sGameData.T_ChiPai.byUser], sizeof(tagCPGNotifyEx), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
				pDesk->SendWatchDataEx(pDesk->sGameData.T_ChiPai.byUser, &pDesk->sGameData.T_CPGNotify[pDesk->sGameData.T_ChiPai.byUser], sizeof(tagCPGNotifyEx), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
			}
		}
		break;
	case ACTION_PENG:				//���ƶ���
		{
			HandlePengPai(NextID,StarTime);
			//֪ͨ�������
			for (int i=0;i<PLAY_COUNT;i++)
			{	
				memset(pDesk->sGameData.T_PengPai.m_byArHandPai,255,sizeof(pDesk->sGameData.T_PengPai.m_byArHandPai));
				pDesk->sUserData.CopyHandPai(pDesk->sGameData.T_PengPai.m_byArHandPai,i,false);
				pDesk->SendGameDataEx(i, &pDesk->sGameData.T_PengPai, sizeof(pDesk->sGameData.T_PengPai), MDM_GM_GAME_NOTIFY, THING_PENG_PAI, 0);
				pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_PengPai, sizeof(pDesk->sGameData.T_PengPai), MDM_GM_GAME_NOTIFY, THING_PENG_PAI, 0);
			}

			//�ж��Ƿ�������
			if(pDesk->sGameData.m_mjAction.bTing && pDesk->sGameData.T_CPGNotify[pDesk->sGameData.T_PengPai.byUser].bTing)//������
			{//������������
				pDesk->sGameData.T_CPGNotify[pDesk->sGameData.T_PengPai.byUser].byUser = pDesk->sGameData.T_PengPai.byUser;
				pDesk->sGameData.T_CPGNotify[pDesk->sGameData.T_PengPai.byUser].bZhuaPai = true;
				pDesk->SendGameDataEx(pDesk->sGameData.T_PengPai.byUser, &pDesk->sGameData.T_CPGNotify[pDesk->sGameData.T_PengPai.byUser], sizeof(tagCPGNotifyEx), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
				pDesk->SendWatchDataEx(pDesk->sGameData.T_PengPai.byUser, &pDesk->sGameData.T_CPGNotify[pDesk->sGameData.T_PengPai.byUser], sizeof(tagCPGNotifyEx), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
			}
		}
		break;
	case ACTION_BU_GANG://���ܶ���
	case ACTION_MING_GANG:			//���ܶ���
		{
			HandleGangPai(NextID,StarTime);
			//֪ͨ�������
			for (int i=0;i<PLAY_COUNT;i++)
			{	
				memset(pDesk->sGameData.T_GangPai.m_byArHandPai,255,sizeof(pDesk->sGameData.T_GangPai.m_byArHandPai));
				pDesk->sUserData.CopyHandPai(pDesk->sGameData.T_GangPai.m_byArHandPai,i,false);
				pDesk->SendGameDataEx(i, &pDesk->sGameData.T_GangPai, sizeof(pDesk->sGameData.T_GangPai), MDM_GM_GAME_NOTIFY, THING_GANG_PAI, 0);
				pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_GangPai, sizeof(pDesk->sGameData.T_GangPai), MDM_GM_GAME_NOTIFY, THING_GANG_PAI, 0);
			}
		}
		break;
	case ACTION_CHI_TNG:			//���ԣ��Ժ����ƣ�
		{
		}
		break;
	case ACTION_HU:					//������
		{
			HandleHuPai(NextID,StarTime);

			///֪ͨ��Һ�����
			memset(pDesk->sGameData.T_HuPai.m_byArHandPai,255,sizeof(pDesk->sGameData.T_HuPai.m_byArHandPai));
			if(!pDesk->sGameData.T_HuPai.bZimo)
			{
				pDesk->sUserData.AddToHandPai(pDesk->sGameData.T_HuPai.byUser,pDesk->sGameData.T_HuPai.byPs);//
			}
			pDesk->sUserData.CopyHandPai(pDesk->sGameData.T_HuPai.m_byArHandPai,0,true);
			for (int i=0;i<PLAY_COUNT;i++)
			{	
				pDesk->sUserData.CopyOutPai(i,pDesk->sGameData.T_HuPai.m_byArOutPai[i]);
			}
			for (int i=0;i<PLAY_COUNT;i++)
			{	
//				pDesk->sUserData.CopyGCPData(i,pDesk->sGameData.T_HuPai.m_UserGCPData[i]);
				pDesk->SendGameDataEx(i, &pDesk->sGameData.T_HuPai, sizeof(pDesk->sGameData.T_HuPai), MDM_GM_GAME_NOTIFY, THING_HU_PAI, 0);
				pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_HuPai, sizeof(pDesk->sGameData.T_HuPai), MDM_GM_GAME_NOTIFY, THING_HU_PAI, 0);
			}
		}
		break;
	case ACTION_NO:
		{
			if(pDesk->sGameData.m_byThingDoing == THING_OUT_PAI)//�����¼�
			{
				NextID = THING_ZHUA_PAI;//ִ��ץ���¼�
				StarTime = 2;
			}
		}
		break;
	}
	pDesk->sGameData.ApplyThingID = NextID;
	ApplyAction(NextID,StarTime*100);//������һ���¼�

}

///����Ƿ���Խ�����һ������
bool ThingHandle::IsCanHandle()
{
	int num = 0, re = 0;
	BYTE max = ACTION_NO;
	BYTE station = pDesk->sGameData.T_OutPai.byUser;

	if(pDesk->sGameData.m_byThingDoing == THING_GANG_PAI)//�����¼�
	{//�������ܺ��Ȳ���
		station = pDesk->sGameData.T_GangPai.byUser;
		for(int i=0;i<4;++i)//���ҳ�����¼�
		{
			if(i==station || pDesk->sGameData.T_CPGNotify[i].m_byMaxThing <= max || pDesk->sGameData.T_CPGNotify[i].m_byMaxThing==255)
				continue;
			max = pDesk->sGameData.T_CPGNotify[i].m_byMaxThing;
		}
		if(max == ACTION_NO)
		{
			pDesk->sGameData.m_byMaxAction = ACTION_BU_GANG;//����ִ���겹��
			return true;
		}
		//�����Ƿ��������Ӧ
		for(int i=0;i<PLAY_COUNT;++i)//����¼�������������¼���Ӧ�ĸ���
		{
			if(i==station)
				continue;
			if(max == pDesk->sGameData.T_CPGNotify[i].m_byMaxThing && pDesk->sGameData.T_CPGNotify[i].m_byMaxThing!=255)
			{
				num++;
				if(pDesk->sGameData.T_CPGNotify[i].bHaveReturn)
					re++;
			}
		}
		if(num == re)//����Ӧ��
		{
			pDesk->sGameData.m_byMaxAction = max;
			return true;
		}
	}
	else//һ����Ƽ��
	{
		for(int i=0;i<PLAY_COUNT;++i)//���ҳ�����¼�
		{
			if(i==station || pDesk->sGameData.T_CPGNotify[i].m_byMaxThing <= max || pDesk->sGameData.T_CPGNotify[i].m_byMaxThing==255)
				continue;
			max = pDesk->sGameData.T_CPGNotify[i].m_byMaxThing;
		}
		if(max == ACTION_NO)
		{
			pDesk->sGameData.m_byMaxAction = ACTION_NO;
			return true;
		}
		for(int i=0;i<PLAY_COUNT;++i)//����¼�������������¼���Ӧ�ĸ���
		{
			if(i==station)
				continue;
			if(max == pDesk->sGameData.T_CPGNotify[i].m_byMaxThing && pDesk->sGameData.T_CPGNotify[i].m_byMaxThing!=255)
			{
				num++;
				if(pDesk->sGameData.T_CPGNotify[i].bHaveReturn)
					re++;
			}
		}
		if(num == re)//����Ӧ��
		{
			pDesk->sGameData.m_byMaxAction = max;
			return true;
		}
	}
	return false;
}


BYTE ThingHandle::GetCanHuUser(BYTE outst,bool hu[],BYTE hust)//��ȡ�������ҽ������
{
	BYTE station = outst;
	for(int i=0;i<PLAY_COUNT-1;++i)
	{
		station = GetNextStation(station);
		if(hu[station])
			return station;
	}
	return hust;
}

///��ȡ�¼�λ��
BYTE ThingHandle::GetNextStation(BYTE station,bool shun)
{
	BYTE re = 255;
	if(shun)//˳ʱ��
	{
		re = (station + 1)%PLAY_COUNT;
	}
	else
	{
		re = (station + 3)%PLAY_COUNT;
	}
	return re;
}

///������ʱ����
void ThingHandle::ClearTempData()
{
	//�������¼�,��ʱ����
	pDesk->sGameData.temp_ChiPai.Clear();
	//�������¼�,��ʱ����
	pDesk->sGameData.temp_PengPai.Clear();
	//�������¼�,��ʱ����
	pDesk->sGameData.temp_GangPai.Clear();	
	//�����������
	pDesk->sGameData.T_GangPai.Clear();	
}

///////////�����¼�����///////////////////////////////////////////////////////////////////////////////////////


//�����¼�,typeҪ������¼�
void ThingHandle::ApplyAction(int type,int time)
{
	if(pDesk->sGameData.ApplyThingID != 255)
	{
		pDesk->SetTimer(101,time);
	}
}

///���ƣ�GameCPU
///��������Ϸ�¼��������ģ�
///@param typeҪ������¼�����
///@return 
void ThingHandle::GameCPU(int type)
{

	BYTE nextID = 255,time = 255;
	switch(type)
	{
	case THING_2SEZI_NT	://�׾���2��ɫ�ӵĵ�����Ϊׯ�¼�
		{
			ExecuteTwoSeziNt(nextID,time);
		}
		break;
	case THING_2SEZI_NT_GP://�׾���2��ɫ�Ӷ�ׯ�Һ����Ƶ��¼�
		{
			ExecuteTwoSeziNtAndDir(nextID,time);
		}
		break;
	case THING_TURN_2SEZI_NT://�׾�������2��ɫ�Ӷ�ׯ���¼�
		{
			ExecuteTurnSeziNt(nextID,time);
		}
		break;
	case THING_2SEZI_DIR://��2��ɫ���¼������Ʒ����¼�
		{
			ExecuteTwoSeziDir(nextID,time);
		}
		break;
	case THING_2SEZI_DIR_GP	://��2��ɫ���¼������Ʒ�������Ƶ��¼�
		{
			ExecuteTwoSeziDirGp(nextID,time);
		}
		break;
	case THING_2SEZI_GP	://��2��ɫ���¼������Ƶ��¼�
		{
			ExecuteTwoSeziGp(nextID,time);
		}
		break;
	case THING_2SEZI_NT_DIR_GP://��ɫ��ȷ��ׯ�ҷ������
		{
			ExecuteTwoSeziNtDirGp(nextID,time);
		}
		break;
	case THING_SEND_PAI://�����¼�
		{
			ExecuteSendPai(nextID,time);
		}
		break;
	case THING_2SEZI_JING://��2��ɫ�Ӷ������¼�
		{
			ExecuteTwoSeziMakeJing(nextID,time);
		}
		break;
	case THING_ALL_BUHUA://Ϊ������Ҳ����¼�
		{
			OutputDebugString("�齫��������  Ϊ������Ҳ����¼�");
			ExecuteAllBuHua(nextID,time);
		}
		break;
	case THING_ONE_BUHUA://�������ץ�����ƺ󲹻��¼�
		{
			OutputDebugString("�齫��������  ������Ҳ����¼�");
			ExecuteOneBuHua(nextID,time);
		}
		break;
	case THING_BEGIN_OUT://ׯ�ҿ�ʼ����֪ͨ�¼�
		{
			pDesk->m_byGameStation = GS_PLAY_GAME;
			ExecuteBeginOut(nextID,time);
		}
		break;
	case THING_ZHUA_PAI	://ץ���¼�
		{	
			OutputDebugString("�齫-�¼���������  THING_ZHUA_PAI ץ���¼�");
			ExecuteZhuaPai(nextID,time);
		}
		break;
	case THING_COUNT_FEN://����¼�
		{
			OutputDebugString("�齫��������  ����¼�");
			ExecuteCountFen(nextID,time);
		}
		break;
	case THING_ENG_HANDLE://���������¼�
		{
			OutputDebugString("new:������  ץ���¼� ���������¼�");
			ExecuteNormalEnd(nextID,time);
		}
		break;
	case THING_ENG_UN_NORMAL://�쳣���������¼�
		{
			OutputDebugString("�齫��������  �쳣���������¼�");
			ExecuteUnNormalEnd(nextID,time);
		}
		break;
	}
	pDesk->sGameData.ApplyThingID = nextID;
	ApplyAction(nextID,time*100);//������һ���¼�

}


///��ʼ�¼�����
void ThingHandle::ExecuteGameBegin(BYTE &nextID,BYTE &time)
{
	pDesk->KillTimer(TIME_WAIT_MSG);
	//pDesk->SetTimer(TIME_WAIT_MSG,1000);//�������ó�ʱ��ʱ��

	nextID = 255;
	time = 10;
	pDesk->sGameData.m_byThingDoing = THING_GAME_BEGIN;

	pDesk->sGameData.InitData();//��ʼ������
	pDesk->sUserData.InitData();
	pDesk->sGameData.SetThingNext();//���ú���¼�
	pDesk->sGameData.m_byThingDoing = pDesk->sGameData.T_Begin.byNo;//��¼���ڷ����¼�

	if(pDesk->sGameData.m_byNtStation!=255)
	{//�Ѿ�����ׯ��
		nextID = THING_2SEZI_DIR_GP;//��ɫ�ӷ���
	}
	else 
	{
		pDesk->sGameData.m_byNtStation = 0;
		nextID = THING_DING_NT;//ִ���Զ�Ϊׯ�¼�
	}
	pDesk->sGameData.T_Begin.byNt = pDesk->sGameData.m_byNtStation;			// ׯ��λ��				
	pDesk->sGameData.T_Begin.byQuanFeng =  pDesk->sUserData.m_byQuanFeng;	// Ȧ������			
	memset(pDesk->sGameData.T_Begin.byMenPai,255,sizeof(pDesk->sGameData.T_Begin.byMenPai));

	for(int i=0;i<4;i++)
	{
		for(int j=0;j<pDesk->sGameData.m_mjRule.byAllMjCount/4;j++)
		{
			pDesk->sGameData.T_Begin.byMenPai[i][j] = 0; //����
		}
	}

	pDesk->sUserData.m_MenPai.byGetPaiDir = pDesk->sGameData.m_byNtStation;
	///��ǰץ�Ʒ���true ˳ʱ�룬false ��ʱ��
	pDesk->sUserData.m_bZhuaPaiDir = true;

	pDesk->sUserData.m_MenPai.byGetPaiDir = pDesk->sGameData.m_byNtStation;//���Ʒ���(ÿ�ֳ�ʼ��Ϊׯ����ǰ����)


	//���Ϳ�ʼ��Ϣ
	for (int i=0;i<PLAY_COUNT;i++)
	{
		pDesk->SendGameDataEx(i,&pDesk->sGameData.T_Begin,sizeof(pDesk->sGameData.T_Begin),MDM_GM_GAME_NOTIFY,THING_GAME_BEGIN,0);
		pDesk->SendWatchDataEx(i,&pDesk->sGameData.T_Begin,sizeof(pDesk->sGameData.T_Begin),MDM_GM_GAME_NOTIFY,THING_GAME_BEGIN,0);
	}
}
/*----------------------------------------------------------------------------------------------------------------------------------*/
///�Ե�һ�����Ϊׯ�ң��Զ�Ϊׯ�¼���
void ThingHandle::ExecuteDongNt(BYTE &nextID,BYTE &time)
{
	pDesk->sGameData.m_byThingDoing = THING_DING_NT;

	//������һ���¼�Ϊ ��ɸ��ȷ�����Ʒ�λ�¼�
	nextID = THING_2SEZI_DIR;
	time = 2;	//200������

	// ׯ��λ��	
	pDesk->sGameData.T_DongNt.byNt = pDesk->sGameData.m_byNtStation;			

	for (int i=0;i<PLAY_COUNT;i++)
	{
		pDesk->SendGameDataEx(i,&pDesk->sGameData.T_DongNt,sizeof(pDesk->sGameData.T_DongNt),MDM_GM_GAME_NOTIFY,THING_DING_NT,0);
		pDesk->SendWatchDataEx(i,&pDesk->sGameData.T_DongNt,sizeof(pDesk->sGameData.T_DongNt),MDM_GM_GAME_NOTIFY,THING_DING_NT,0);
	}
}
/*----------------------------------------------------------------------------------------------------------------------------------*/
///��2��ɫ��ȷ��ׯ�ң������ͣ�
void ThingHandle::ExecuteTwoSeziNt(BYTE &nextID,BYTE &time)	
{
	pDesk->sGameData.m_byThingDoing = THING_2SEZI_NT;
	nextID = THING_2SEZI_DIR_GP;
	time = 2;	//200������
	///��2��ɫ�ӵĵ�����Ϊׯ�¼�
	pDesk->sGameData.T_TwoSeziNt.byUser = 0;//ׯ��λ��
	pDesk->sGameData.T_TwoSeziNt.byDo = 10;//�¼�����
	//pDesk->sUserData.m_MenPai.byGetPaiDir = pDesk->sGameData.m_byNtStation;
	if(pDesk->sGameData.m_byNtStation != 255)
	{//�Ѿ���ׯ���˾Ͳ���ɫ����
		return;
	}
	time = 50;	//5����
	CLogicBase::GetSeziData(&pDesk->sGameData.T_TwoSeziNt.bySezi0,&pDesk->sGameData.T_TwoSeziNt.bySezi1);
	pDesk->sGameData.m_byNtStation = (pDesk->sGameData.T_TwoSeziNt.bySezi0 + pDesk->sGameData.T_TwoSeziNt.bySezi1 - 1)%4;

	pDesk->sGameData.T_TwoSeziNt.byNt = pDesk->sGameData.m_byNtStation;

	pDesk->sGameData.ApplyThingID = nextID;

	ApplyAction(nextID,5000);//������һ���¼�
	for (int i=0;i<PLAY_COUNT;i++)
	{
		pDesk->SendGameDataEx(i, &pDesk->sGameData.T_TwoSeziNt, sizeof(pDesk->sGameData.T_TwoSeziNt), MDM_GM_GAME_NOTIFY, THING_2SEZI_NT, 0);
	}
	pDesk->SendWatchDataEx(PLAY_COUNT, &pDesk->sGameData.T_TwoSeziNt, sizeof(pDesk->sGameData.T_TwoSeziNt), MDM_GM_GAME_NOTIFY, THING_2SEZI_NT, 0);
	//���õȴ�ɫ�Ӷ�������״̬
	memset(pDesk->sUserData.m_bSiziFinish,0,sizeof(pDesk->sUserData.m_bSiziFinish));
	pDesk->sUserData.m_bWaitSezi = true;
}

///��2��ɫ��ȷ��ׯ�Һ����Ʒ��򣨵�����ׯ�ң���㷽��,δʹ�ã�
void ThingHandle::ExecuteTwoSeziNtAndDir(BYTE &nextID,BYTE &time)
{

}

///������ɫ��ȷ��ׯ��
void ThingHandle::ExecuteTurnSeziNt(BYTE &nextID,BYTE &time)	
{
	pDesk->sGameData.m_byThingDoing = THING_TURN_2SEZI_NT;
	///������2��ɫ��ȷ��ׯ��
	CLogicBase::GetSeziData(&pDesk->sGameData.T_TurnSeziNt.bySezi0,&pDesk->sGameData.T_TurnSeziNt.bySezi1);

	nextID = THING_2SEZI_DIR_GP;
	pDesk->sGameData.ApplyThingID = nextID;
	ApplyAction(nextID,5000);//������һ���¼�
	pDesk->sUserData.m_MenPai.byGetPaiDir = pDesk->sGameData.m_byNtStation;//���Ʒ���(ÿ�ֳ�ʼ��Ϊׯ����ǰ����)
	for (int i=0;i<PLAY_COUNT;i++)
	{
		pDesk->SendGameDataEx(i, &pDesk->sGameData.T_TurnSeziNt, sizeof(pDesk->sGameData.T_TurnSeziNt), MDM_GM_GAME_NOTIFY, THING_TURN_2SEZI_NT, 0);
	}
	pDesk->SendWatchDataEx(PLAY_COUNT, &pDesk->sGameData.T_TurnSeziNt, sizeof(pDesk->sGameData.T_TurnSeziNt), MDM_GM_GAME_NOTIFY, THING_TURN_2SEZI_NT, 0);	
	//���õȴ�ɫ�Ӷ�������״̬
	memset(pDesk->sUserData.m_bSiziFinish,0,sizeof(pDesk->sUserData.m_bSiziFinish));
	pDesk->sUserData.m_bWaitSezi = true;
}

///��2��ɫ��ȷ��ׯ��+���Ʒ���+���ƶ�����������ׯ�ң���㷽��С�������
void ThingHandle::ExecuteTwoSeziNtDirGp(BYTE &nextID,BYTE &time)	
{
	pDesk->sGameData.m_byThingDoing = THING_2SEZI_NT_GP;
	///��2��ɫ��ȷ��ׯ�Һ����Ƶ�λ���¼�
	nextID = THING_SEND_PAI;

	pDesk->sGameData.T_TwoSeziNtAndGetPai.byUser = 0;
	CLogicBase::GetSeziData(&pDesk->sGameData.T_TwoSeziNtAndGetPai.bySezi0,&pDesk->sGameData.T_TwoSeziNtAndGetPai.bySezi1);
	if(pDesk->sGameData.m_byNtStation!=255)
	{//�Ѿ�����ׯ��
		pDesk->sGameData.T_TwoSeziNtAndGetPai.byUser = pDesk->sGameData.m_byNtStation;
	}
	else
	{
		pDesk->sGameData.m_byNtStation = (pDesk->sGameData.T_TwoSeziNtAndGetPai.bySezi0 + pDesk->sGameData.T_TwoSeziNtAndGetPai.bySezi1)%4;
	}
	pDesk->sGameData.T_TwoSeziNtAndGetPai.byNt = pDesk->sGameData.m_byNtStation;
	pDesk->sGameData.T_TwoSeziNtAndGetPai.byGetPai = pDesk->sGameData.T_TwoSeziNtAndGetPai.bySezi0;
	pDesk->sUserData.m_MenPai.byGetPaiDir = pDesk->sGameData.T_TwoSeziNtAndGetPai.bySezi1%4;
	if(pDesk->sGameData.T_TwoSeziNtAndGetPai.bySezi0>pDesk->sGameData.T_TwoSeziNtAndGetPai.bySezi1)
	{
		pDesk->sGameData.T_TwoSeziNtAndGetPai.byGetPai = pDesk->sGameData.T_TwoSeziNtAndGetPai.bySezi1;
		pDesk->sUserData.m_MenPai.byGetPaiDir = pDesk->sGameData.T_TwoSeziNtAndGetPai.bySezi0%4;
	}

	pDesk->sGameData.ApplyThingID = nextID;
	ApplyAction(nextID,5000);//������һ���¼�
	pDesk->sUserData.m_MenPai.byGetPaiDir = pDesk->sGameData.m_byNtStation;//���Ʒ���(ÿ�ֳ�ʼ��Ϊׯ����ǰ����)
	for (int i=0;i<PLAY_COUNT;i++)
	{
		pDesk->SendGameDataEx(i, &pDesk->sGameData.T_TwoSeziNtAndGetPai, sizeof(pDesk->sGameData.T_TwoSeziNtAndGetPai), MDM_GM_GAME_NOTIFY, THING_2SEZI_NT, 0);
	}
	pDesk->SendWatchDataEx(PLAY_COUNT, &pDesk->sGameData.T_TwoSeziNtAndGetPai, sizeof(pDesk->sGameData.T_TwoSeziNtAndGetPai), MDM_GM_GAME_NOTIFY, THING_2SEZI_NT, 0);	
	//���õȴ�ɫ�Ӷ�������״̬
	memset(pDesk->sUserData.m_bSiziFinish,0,sizeof(pDesk->sUserData.m_bSiziFinish));
	pDesk->sUserData.m_bWaitSezi = true;
}
/*--------------------------------------------------------------------------------------*/
///��2��ɫ��ȷ�����Ʒ��򣨵�����ȷ������	DWJ
void ThingHandle::ExecuteTwoSeziDir(BYTE &nextID,BYTE &time)	
{
	pDesk->sGameData.m_byThingDoing = THING_2SEZI_DIR;
	///��2��ɫ��ȷ������λ���¼�
	nextID = THING_2SEZI_GP;//׼��ִ����ɫ��ȷ�����ƶ����¼�

	pDesk->sGameData.T_TwoSeziDir.byUser = pDesk->sGameData.m_byNtStation;
	pDesk->sGameData.T_TwoSeziDir.byNt = pDesk->sGameData.m_byNtStation;
	CLogicBase::GetSeziData(&pDesk->sGameData.T_TwoSeziDir.bySezi0,&pDesk->sGameData.T_TwoSeziDir.bySezi1);
	pDesk->sUserData.m_MenPai.byGetPaiDir = (pDesk->sGameData.T_TwoSeziDir.bySezi1 + pDesk->sGameData.T_TwoSeziDir.bySezi0)%4;
	pDesk->sGameData.T_TwoSeziDir.byDirection = pDesk->sUserData.m_MenPai.byGetPaiDir;

	pDesk->sGameData.ApplyThingID = nextID;
	ApplyAction(nextID,5000);//������һ���¼�
	for (int i=0;i<PLAY_COUNT;i++)
	{
		pDesk->SendGameDataEx(i, &pDesk->sGameData.T_TwoSeziDir, sizeof(pDesk->sGameData.T_TwoSeziDir), MDM_GM_GAME_NOTIFY, THING_2SEZI_DIR, 0);
	}
	pDesk->SendWatchDataEx(PLAY_COUNT, &pDesk->sGameData.T_TwoSeziDir, sizeof(pDesk->sGameData.T_TwoSeziDir), MDM_GM_GAME_NOTIFY, THING_2SEZI_DIR, 0);
	//���õȴ�ɫ�Ӷ�������״̬
	memset(pDesk->sUserData.m_bSiziFinish,0,sizeof(pDesk->sUserData.m_bSiziFinish));
	pDesk->sUserData.m_bWaitSezi = true;
}
/*--------------------------------------------------------------------------------------*/
///��2��ɫ��ȷ�����Ʒ�������ƶ����������ͷ���С�������
void ThingHandle::ExecuteTwoSeziDirGp(BYTE &nextID,BYTE &time)	
{
	pDesk->sGameData.m_byThingDoing = THING_2SEZI_DIR_GP;
	///��2��ɫ��ȷ������λ�ã������ͣ������Ƶ㣨��С�㣩�¼�	
	nextID = THING_SEND_PAI;
	pDesk->sGameData.T_TwoSeziDirAndGetPai.byUser = pDesk->sGameData.m_byNtStation;
	CLogicBase::GetSeziData(&pDesk->sGameData.T_TwoSeziDirAndGetPai.bySezi0,&pDesk->sGameData.T_TwoSeziDirAndGetPai.bySezi1);
	pDesk->sGameData.T_TwoSeziDirAndGetPai.bySezi0 = pDesk->sGameData.T_TwoSeziDirAndGetPai.bySezi0%6+1;
	pDesk->sGameData.T_TwoSeziDirAndGetPai.bySezi1 = pDesk->sGameData.T_TwoSeziDirAndGetPai.bySezi1%6+1;
	//���Ʒ���
	pDesk->sUserData.m_MenPai.byGetPaiDir = (pDesk->sGameData.T_TwoSeziDirAndGetPai.bySezi1 + pDesk->sGameData.T_TwoSeziDirAndGetPai.bySezi0)%4-1;
	//���Ƶ���
	pDesk->sUserData.m_MenPai.byGetPai = pDesk->sGameData.T_TwoSeziDirAndGetPai.bySezi0-1;
	if(pDesk->sGameData.T_TwoSeziDirAndGetPai.bySezi0 > pDesk->sGameData.T_TwoSeziDirAndGetPai.bySezi1)
	{
		pDesk->sUserData.m_MenPai.byGetPai = pDesk->sGameData.T_TwoSeziDirAndGetPai.bySezi1-1;
	}
	pDesk->sGameData.T_TwoSeziDirAndGetPai.byGetPai = pDesk->sUserData.m_MenPai.byGetPai;

	pDesk->sGameData.ApplyThingID = nextID;
	ApplyAction(nextID,5000);//������һ���¼�
	for (int i=0;i<PLAY_COUNT;i++)
	{
		pDesk->SendGameDataEx(i, &pDesk->sGameData.T_TwoSeziDirAndGetPai, sizeof(pDesk->sGameData.T_TwoSeziDirAndGetPai), MDM_GM_GAME_NOTIFY, THING_2SEZI_DIR_GP, 0);
	}
	pDesk->SendWatchDataEx(PLAY_COUNT, &pDesk->sGameData.T_TwoSeziDirAndGetPai, sizeof(pDesk->sGameData.T_TwoSeziDirAndGetPai), MDM_GM_GAME_NOTIFY, THING_2SEZI_DIR_GP, 0);
	//���õȴ�ɫ�Ӷ�������״̬
	memset(pDesk->sUserData.m_bSiziFinish,0,sizeof(pDesk->sUserData.m_bSiziFinish));
	pDesk->sUserData.m_bWaitSezi = true;
}

///��2��ɫ��ȷ�����ƶ����������Ͷ�����
void ThingHandle::ExecuteTwoSeziGp(BYTE &nextID,BYTE &time)	
{
	pDesk->sGameData.m_byThingDoing = THING_2SEZI_GP;
	///��2��ɫ��ȷ�����ƶ����¼�
	nextID = THING_SEND_PAI	;//׼��ִ�з����¼�		
	pDesk->sGameData.T_TwoSeziGetPai.byUser = pDesk->sGameData.m_byNtStation;
	CLogicBase::GetSeziData(&pDesk->sGameData.T_TwoSeziGetPai.bySezi0,&pDesk->sGameData.T_TwoSeziGetPai.bySezi1);
	pDesk->sUserData.m_MenPai.byGetPai = (pDesk->sGameData.T_TwoSeziGetPai.bySezi1 + pDesk->sGameData.T_TwoSeziGetPai.bySezi0)%12;
	pDesk->sGameData.T_TwoSeziGetPai.byGetPai = pDesk->sUserData.m_MenPai.byGetPai;

	pDesk->sGameData.ApplyThingID = nextID;
	ApplyAction(nextID,5000);//������һ���¼�
	for (int i=0;i<PLAY_COUNT;i++)
	{
		pDesk->SendGameDataEx(i, &pDesk->sGameData.T_TwoSeziGetPai, sizeof(pDesk->sGameData.T_TwoSeziGetPai), MDM_GM_GAME_NOTIFY, THING_2SEZI_GP, 0);
	}
	pDesk->SendWatchDataEx(PLAY_COUNT, &pDesk->sGameData.T_TwoSeziGetPai, sizeof(pDesk->sGameData.T_TwoSeziGetPai), MDM_GM_GAME_NOTIFY, THING_2SEZI_GP, 0);
	//���õȴ�ɫ�Ӷ�������״̬
	memset(pDesk->sUserData.m_bSiziFinish,0,sizeof(pDesk->sUserData.m_bSiziFinish));
	pDesk->sUserData.m_bWaitSezi = true;
}

///��ע�¼���ȷ��ׯ�Һ󣬿���ͨ��ѡ���ע������Ӯ��
void ThingHandle::ExecuteAddNote(BYTE &nextID,BYTE &time)	
{
}

///����
void ThingHandle::ExecuteSendPai(BYTE &nextID,BYTE &time)	
{
	///��ǰץ�Ʒ���true ˳ʱ�룬false ��ʱ��
	pDesk->sUserData.m_bZhuaPaiDir = true;
	pDesk->sGameData.m_byThingDoing = THING_SEND_PAI;
	///�����¼�
	pDesk->sGameData.T_SendPai.byDo = 1;	//
	nextID = THING_BEGIN_OUT;//��һ���¼��Ĵ��ţ���ʼ����
	time = 5;
	//������
	DisPatchCard();

	for(int i=0;i<PLAY_COUNT;i++)
	{
		for(int j=0;j<MAX_HAND_PAI-1;++j)
		{
			GetPai(i,true,1);
		}
	}

	//ׯ�Ҷ�ץһ����
	BYTE card = 255;
	card=GetPai(pDesk->sGameData.m_byNtStation,true,1);
	//��������
	ChangeMenPai();
	for(int i=0;i<PLAY_COUNT;++i)
	{
		pDesk->sUserData.CopyMenPai(i,pDesk->sGameData.T_SendPai.byMenPai[i]);//��������
		pDesk->sUserData.SortHandPai(i,false);
	}

	//��������ׯ�ҵ��ƣ��������
#ifdef MJ_CAN_SETPAI

    CString s = CINIFile::GetAppPath ();/////����·��    
	CINIFile f(s +_T("\\")+SKIN_FOLDER  + _T("_s.ini"));

	pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][0] = f.GetKeyVal("test","pai1",pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][0]);
	pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][1] = f.GetKeyVal("test","pai2",pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][1]);
	pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][2] = f.GetKeyVal("test","pai3",pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][2]);
	pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][3] = f.GetKeyVal("test","pai4",pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][3]);
	pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][4] = f.GetKeyVal("test","pai5",pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][4]);
	pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][5] = f.GetKeyVal("test","pai6",pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][5]);
	pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][6] = f.GetKeyVal("test","pai7",pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][6]);
	pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][7] = f.GetKeyVal("test","pai8",pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][7]);
	pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][8] = f.GetKeyVal("test","pai9",pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][8]);
	pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][9] = f.GetKeyVal("test","pai10",pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][9]);
	pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][10] = f.GetKeyVal("test","pai11",pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][10]);
	pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][11] = f.GetKeyVal("test","pai12",pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][11]);
	pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][12] = f.GetKeyVal("test","pai13",pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][12]);
	pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][13] = f.GetKeyVal("test","pai14",pDesk->sUserData.m_byArHandPai[pDesk->sGameData.m_byNtStation][13]);

	OutputDebugString("Ѫս�齫�������� ExecuteSendPai ");

#endif //

	for(int i=0;i<PLAY_COUNT;i++)
	{	
		memset(pDesk->sGameData.T_SendPai.m_byArHandPai,255,sizeof(pDesk->sGameData.T_SendPai.m_byArHandPai));
		pDesk->sUserData.CopyHandPai(pDesk->sGameData.T_SendPai.m_byArHandPai,i,false);
		pDesk->SendGameDataEx(i, &pDesk->sGameData.T_SendPai, sizeof(pDesk->sGameData.T_SendPai), MDM_GM_GAME_NOTIFY, THING_SEND_PAI, 0);
		pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_SendPai, sizeof(pDesk->sGameData.T_SendPai), MDM_GM_GAME_NOTIFY, THING_SEND_PAI, 0);
	}
	pDesk->sGameData.ApplyThingID = nextID;
	//ApplyAction(nextID,500);//������һ���¼�



}

///��2��ɫ�Ӷ����¼�
void ThingHandle::ExecuteTwoSeziMakeJing(BYTE &nextID,BYTE &time)	
{
	pDesk->sGameData.m_byThingDoing = THING_2SEZI_JING;
	///��ɫ��2��ɫ�Ӷ������¼�
	nextID = THING_SEND_PAI;
	pDesk->sGameData.T_TwoSeziJing.byUser = pDesk->sGameData.m_byNtStation;
	CLogicBase::GetSeziData(&pDesk->sGameData.T_TwoSeziJing.bySezi0,&pDesk->sGameData.T_TwoSeziJing.bySezi1);

	int num = pDesk->sGameData.T_TwoSeziJing.bySezi0 + pDesk->sGameData.T_TwoSeziJing.bySezi1;
	num = num%13;//����ɫ��ֵ���ܳ���12
	if(num <0 )
	{
		num = -num;
	}
	num = (2*num +1);
	if(pDesk->sUserData.m_MenPai.byEndIndex>=num)
	{
		pDesk->sUserData.m_MenPai.byCaiShenIndex = pDesk->sUserData.m_MenPai.byEndIndex -num;
	}
	else
	{
		pDesk->sUserData.m_MenPai.byCaiShenIndex = pDesk->sUserData.m_MenPai.byAllPaiNum + pDesk->sUserData.m_MenPai.byEndIndex + 1 - num;
	}
	pDesk->sUserData.m_StrJing.Init();
	if(pDesk->sUserData.m_StrJing.AddJing(pDesk->sUserData.m_MenPai.byMenPai[pDesk->sUserData.m_MenPai.byCaiShenIndex]))
	{
	}

	if(pDesk->sUserData.m_MenPai.byMenPai[pDesk->sUserData.m_MenPai.byCaiShenIndex] == 255)//
	{
		pDesk->sUserData.m_MenPai.byCaiShenIndex = pDesk->sUserData.m_MenPai.byEndIndex;
		pDesk->sUserData.m_StrJing.Init();
		pDesk->sUserData.m_StrJing.AddJing(pDesk->sUserData.m_MenPai.byMenPai[pDesk->sUserData.m_MenPai.byCaiShenIndex]);
	}
	//ɾ�������Ĳ�����
	pDesk->sUserData.m_MenPai.byMenPai[pDesk->sUserData.m_MenPai.byCaiShenIndex] = 255;

#ifdef MJ_CAN_SETPAI
    CString s = CINIFile::GetAppPath ();/////����·��    
	CINIFile f(s +_T("\\")+SKIN_FOLDER  + _T("_s.ini"));
	pDesk->sUserData.m_StrJing.byPai[0] = f.GetKeyVal("test","baopai",pDesk->sUserData.m_StrJing.byPai[0]);
	
#endif //MJ_CAN_SETPAI
	pDesk->sGameData.T_TwoSeziJing.m_StrJing = pDesk->sUserData.m_StrJing;

	pDesk->sGameData.ApplyThingID = nextID;
	ApplyAction(nextID,5000);//������һ���¼�
	for (int i=0;i<PLAY_COUNT;i++)
	{
		pDesk->SendGameDataEx(i, &pDesk->sGameData.T_TwoSeziJing, sizeof(pDesk->sGameData.T_TwoSeziJing), MDM_GM_GAME_NOTIFY, THING_2SEZI_JING, 0);
	}
	pDesk->SendWatchDataEx(PLAY_COUNT, &pDesk->sGameData.T_TwoSeziJing, sizeof(pDesk->sGameData.T_TwoSeziJing), MDM_GM_GAME_NOTIFY, THING_2SEZI_JING, 0);
	//���õȴ�ɫ�Ӷ�������״̬
	memset(pDesk->sUserData.m_bSiziFinish,0,sizeof(pDesk->sUserData.m_bSiziFinish));
	pDesk->sUserData.m_bWaitSezi = true;
}

///������Ҳ����¼�
void ThingHandle::ExecuteAllBuHua(BYTE &nextID,BYTE &time)	
{
	pDesk->sGameData.m_byThingDoing = THING_ALL_BUHUA;
	///������Ҳ����¼�
	nextID = THING_BEGIN_OUT;
	for(int i=0;i<PLAY_COUNT;i++)
	{
		if(!pDesk->sUserData.IsHuaPaiInHand(i))
			continue;
		while(pDesk->sUserData.IsHuaPaiInHand(i))
		{
			int num = 1;//pDesk->sUserData.MoveHuaPaiFormHand(i);
			for(int j=0;j<num;j++)
			{
				GetPai(i,false,1);//��ʼǰ����ץ��
			}
		}
	}
	ApplyAction(nextID,500);//������һ���¼�
	///����������
	for (int i=0;i<PLAY_COUNT;i++)
	{		
		memset(pDesk->sGameData.T_AllBuHua.m_byArHandPai,255,sizeof(pDesk->sGameData.T_AllBuHua.m_byArHandPai));
		pDesk->sUserData.CopyHandPai(pDesk->sGameData.T_AllBuHua.m_byArHandPai,i,false);
		pDesk->SendGameDataEx(i, &pDesk->sGameData.T_AllBuHua, sizeof(pDesk->sGameData.T_AllBuHua), MDM_GM_GAME_NOTIFY, THING_ALL_BUHUA, 0);
		pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_AllBuHua, sizeof(pDesk->sGameData.T_AllBuHua), MDM_GM_GAME_NOTIFY, THING_ALL_BUHUA, 0);
	}
	pDesk->sGameData.ApplyThingID = nextID;
	ApplyAction(nextID,1500);
}

///������Ҳ����¼�
void ThingHandle::ExecuteOneBuHua(BYTE &nextID,BYTE &time)
{
	nextID = 255;
	pDesk->sGameData.m_byThingDoing = THING_ONE_BUHUA;
	///������Ҳ����¼�	
	pDesk->sGameData.T_OneBuHua.byUser = pDesk->sUserData.m_byNowOutStation;
	while(pDesk->sUserData.IsHuaPaiInHand(pDesk->sUserData.m_byNowOutStation))
	{
		int num = 1;//pDesk->sUserData.MoveHuaPaiFormHand(pDesk->sUserData.m_byNowOutStation);
		for(int i=0;i<num;i++)
		{
			pDesk->sGameData.T_OneBuHua.byPs = GetPai(pDesk->sUserData.m_byNowOutStation,false,3);//����ץ��
		}
	}
	for(int i=0;i<4;i++)
	{
		pDesk->sUserData.CopyMenPai(i,pDesk->sGameData.T_OneBuHua.byMenPai[i]);//��������
		pDesk->sUserData.CopyHuaPai(i,pDesk->sGameData.T_OneBuHua.m_byArHuaPai[i]);//��������
	}
	pDesk->sGameData.ApplyThingID = nextID;
	ApplyAction(nextID,200);//������һ���¼�
	///����������
	for (int i=0;i<PLAY_COUNT;i++)
	{			
		memset(pDesk->sGameData.T_OneBuHua.m_byArHandPai,255,sizeof(pDesk->sGameData.T_OneBuHua.m_byArHandPai));
		pDesk->sUserData.CopyHandPai(pDesk->sGameData.T_OneBuHua.m_byArHandPai,i,false);
		pDesk->SendGameDataEx(i, &pDesk->sGameData.T_OneBuHua, sizeof(pDesk->sGameData.T_OneBuHua), MDM_GM_GAME_NOTIFY, THING_ONE_BUHUA, 0);
		pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_OneBuHua, sizeof(pDesk->sGameData.T_OneBuHua), MDM_GM_GAME_NOTIFY, THING_ONE_BUHUA, 0);
	}
}


///��ʼ����֪ͨ�¼�
void ThingHandle::ExecuteBeginOut(BYTE &nextID,BYTE &time)
{
	pDesk->sGameData.m_byThingDoing = THING_BEGIN_OUT;
	///��ʼ����֪ͨ�¼�
	//T_BeginOutPai;	
	pDesk->sGameData.T_BeginOutPai.byNt = pDesk->sGameData.m_byNtStation;//ׯ��λ��
	pDesk->sGameData.T_BeginOutPai.byUser = pDesk->sGameData.m_byNtStation;//ׯ��λ��
//	pDesk->sGameData.T_BeginOutPai.m_StrJing = pDesk->sUserData.m_StrJing;//����
	pDesk->sUserData.m_byNowOutStation = pDesk->sGameData.m_byNtStation;//����λ��
	for(int i=0;i<4;i++)
	{
		pDesk->sUserData.CopyMenPai(i,pDesk->sGameData.T_BeginOutPai.byMenPai[i]);//��������
	}
	ChangeMenPai();//ת������
	//��⶯��
	pDesk->sGameData.T_CPGNotify[pDesk->sGameData.m_byNtStation].Clear();
	CheckAction(pDesk->sGameData.m_byNtStation,pDesk->sUserData.GetLastHandPai(pDesk->sUserData.m_byNowOutStation),0);

	//if(pDesk->sUserData.m_bFoceLeave[pDesk->sGameData.m_byNtStation] && pDesk->sGameData.m_mjRule.bNetCutTuoGuan)//���ׯ�Ҷ���,�����ж����й�
	//{
	//	//NetCutAutoHandle(pDesk->sGameData.m_byNtStation);
	//}
	pDesk->sGameData.ApplyThingID = 255;
	ApplyAction(pDesk->sGameData.ApplyThingID,200);//������һ���¼�
	//����֪ͨ
	for (int i=0;i<PLAY_COUNT;i++)
	{	
		pDesk->SendGameDataEx(i, &pDesk->sGameData.T_BeginOutPai, sizeof(pDesk->sGameData.T_BeginOutPai), MDM_GM_GAME_NOTIFY, THING_BEGIN_OUT, 0);
	}
	pDesk->SendWatchDataEx(PLAY_COUNT, &pDesk->sGameData.T_BeginOutPai, sizeof(pDesk->sGameData.T_BeginOutPai), MDM_GM_GAME_NOTIFY, THING_BEGIN_OUT, 0);

	if(!pDesk->sUserData.m_bFoceLeave[ pDesk->sGameData.T_BeginOutPai.byUser])
	{
		pDesk->sGameData.T_CPGNotify[pDesk->sGameData.m_byNtStation].bZhuaPai = true;
		pDesk->SendGameDataEx(pDesk->sGameData.m_byNtStation, &pDesk->sGameData.T_CPGNotify[pDesk->sGameData.m_byNtStation], sizeof(tagCPGNotifyEx), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
		pDesk->SendWatchDataEx(pDesk->sGameData.m_byNtStation, &pDesk->sGameData.T_CPGNotify[pDesk->sGameData.m_byNtStation], sizeof(tagCPGNotifyEx), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
	}
	else//���ߴ���
	{
		NetCutAutoHandle();
	}
}

///ץ���¼�
void ThingHandle::ExecuteZhuaPai(BYTE &nextID,BYTE &time)	
{
	///ץ�����¼�
	nextID = 255;
	BYTE card = 255;
	if(pDesk->sUserData.m_MenPai.GetMenPaiNum()<=pDesk->sGameData.m_mjRule.byGamePassNum)
	{
		nextID = THING_ENG_HANDLE;
	}
	else
	{
		if(pDesk->sGameData.m_byThingDoing == THING_OUT_PAI)//�����¼�
		{
			pDesk->sUserData.m_byNowOutStation = GetNextStation(pDesk->sUserData.m_byNowOutStation);//ץ��λ��
		}

		pDesk->sGameData.m_byThingDoing = THING_ZHUA_PAI;//��¼���ڷ������¼�

		pDesk->sGameData.T_ZhuaPai.byUser = pDesk->sUserData.m_byNowOutStation;//ׯ��λ��
		card = GetPai(pDesk->sUserData.m_byNowOutStation,pDesk->sUserData.m_bZhuaPaiDir,0);//����ץ��
		pDesk->sGameData.T_ZhuaPai.byPs = card;		//ץ�Ƶ�ֵ

		if(card == 255 && ( pDesk->sUserData.m_MenPai.GetMenPaiNum()<=pDesk->sGameData.m_mjRule.byGamePassNum +2))
		{//�������⣬��ʱ���
			nextID = THING_ENG_HANDLE;
			return;
		}

		///���������Ҫץ����(�������汾)
		if(pDesk->sUserData.m_SetData[pDesk->sUserData.m_byNowOutStation].bySetType==2)
		{		
			pDesk->sUserData.DelleteAHandPai(pDesk->sUserData.m_byNowOutStation,card);
			card = pDesk->sUserData.m_SetData[pDesk->sUserData.m_byNowOutStation].mjdata[0];
			pDesk->sUserData.AddToHandPai(pDesk->sUserData.m_byNowOutStation,card);

			pDesk->sUserData.m_SetData[pDesk->sUserData.m_byNowOutStation].Init();
		}
		if(pDesk->sGameData.m_mjRule.bHaveFlower && pDesk->sUserData.CheckIsHuaPai(card))
		{
			//���Ʋ���
			nextID = THING_ONE_BUHUA;
			time = 5;
			pDesk->sGameData.T_ZhuaPai.bHead = false;		//ץ�Ƶķ���
			pDesk->sGameData.T_ZhuaPai.bCanOutPai = false;	//ץ�ƺ��Ƿ���Գ���
		}
		else
		{
			//�������
			pDesk->sGameData.T_CPGNotify[pDesk->sUserData.m_byNowOutStation].Clear();
			CheckAction(pDesk->sUserData.m_byNowOutStation,card,0);
			if(pDesk->sUserData.m_bTuoGuan[pDesk->sUserData.m_byNowOutStation])//����й�
			{
				pDesk->sGameData.T_CPGNotify[pDesk->sUserData.m_byNowOutStation].bChi = false;
				memset(pDesk->sGameData.T_CPGNotify[pDesk->sUserData.m_byNowOutStation].m_iChi,255,sizeof(pDesk->sGameData.T_CPGNotify[pDesk->sUserData.m_byNowOutStation].m_iChi));
				pDesk->sGameData.T_CPGNotify[pDesk->sUserData.m_byNowOutStation].bPeng = false;
			}
			if(pDesk->sUserData.m_bTing[pDesk->sUserData.m_byNowOutStation] && !pDesk->sGameData.m_mjAction.bGangAfterTing)
			{
				pDesk->sGameData.T_CPGNotify[pDesk->sUserData.m_byNowOutStation].bGang = false;
				memset(pDesk->sGameData.T_CPGNotify[pDesk->sUserData.m_byNowOutStation].m_iGangData,255,sizeof(pDesk->sGameData.T_CPGNotify[pDesk->sUserData.m_byNowOutStation].m_iGangData));
			}

		}
		ChangeMenPai();//ת������
		for(int i=0;i<4;i++)
		{
			pDesk->sUserData.CopyMenPai(i,pDesk->sGameData.T_ZhuaPai.byMenPai[i]);//��������
			pDesk->sUserData.CopyHuaPai(i,pDesk->sGameData.T_ZhuaPai.m_byArHuaPai[i]);//��������
			pDesk->sUserData.CopyOutPai(i,pDesk->sGameData.T_ZhuaPai.m_byArOutPai[i]);//��������
		}
	}

	pDesk->sGameData.ApplyThingID = nextID;
	ApplyAction(nextID,200);//������һ���¼�
	BYTE pai = pDesk->sGameData.T_ZhuaPai.byPs ;
	///����������
	for (int i=0;i<PLAY_COUNT;i++)
	{			
		pDesk->sGameData.T_ZhuaPai.byPs = 255;
		memset(pDesk->sGameData.T_ZhuaPai.m_byArHandPai,255,sizeof(pDesk->sGameData.T_ZhuaPai.m_byArHandPai));
		pDesk->sUserData.CopyHandPai(pDesk->sGameData.T_ZhuaPai.m_byArHandPai,i,false);
		if(pDesk->sGameData.T_ZhuaPai.byUser == i)
		{
			pDesk->sGameData.T_ZhuaPai.byPs = pai;
		}
		pDesk->SendGameDataEx(i, &pDesk->sGameData.T_ZhuaPai, sizeof(pDesk->sGameData.T_ZhuaPai), MDM_GM_GAME_NOTIFY, THING_ZHUA_PAI, 0);
		pDesk->SendWatchDataEx(i, &pDesk->sGameData.T_ZhuaPai, sizeof(pDesk->sGameData.T_ZhuaPai), MDM_GM_GAME_NOTIFY, THING_ZHUA_PAI, 0);
	}
	pDesk->sGameData.T_ZhuaPai.byPs = pai;
	if(nextID == 255)
	{//id=255˵����û������Ҳ���ǲ��������Է��ͳ�����֪ͨ��������߾�ֱ�ӳ���
		if(pDesk->sGameData.m_mjRule.bNetCutTuoGuan && pDesk->sUserData.m_bFoceLeave[ pDesk->sGameData.T_ZhuaPai.byUser])
		{
			NetCutAutoHandle();
		}
		else if(!pDesk->sUserData.m_bFoceLeave[ pDesk->sGameData.T_ZhuaPai.byUser])
		{
			pDesk->sGameData.T_CPGNotify[pDesk->sGameData.T_ZhuaPai.byUser].byUser = pDesk->sGameData.T_ZhuaPai.byUser;
			pDesk->sGameData.T_CPGNotify[pDesk->sGameData.T_ZhuaPai.byUser].bZhuaPai = true;
			pDesk->SendGameDataEx(pDesk->sGameData.T_ZhuaPai.byUser, &pDesk->sGameData.T_CPGNotify[pDesk->sGameData.T_ZhuaPai.byUser], sizeof(tagCPGNotifyEx), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);
			pDesk->SendWatchDataEx(pDesk->sGameData.T_ZhuaPai.byUser, &pDesk->sGameData.T_CPGNotify[pDesk->sGameData.T_ZhuaPai.byUser], sizeof(tagCPGNotifyEx), MDM_GM_GAME_NOTIFY, THING_CPG_NOTIFY, 0);

		}
	}
}

///����¼�
void ThingHandle::ExecuteCountFen(BYTE &nextID,BYTE &time)
{
	pDesk->sGameData.m_byThingDoing = THING_COUNT_FEN;
	///����¼�
	nextID = THING_ENG_HANDLE;//��һ���¼�����Ϸ�����¼�
	time = 2;	
	for(int i=0;i<PLAY_COUNT;i++)
	{
//		pDesk->sGameData.T_CountFen.bHu[i] = pDesk->sGameData.T_HuPai.bHaveHu[i];
		//��ȡ��������
		for(int j=0;j<MAX_HUPAI_TYPE;j++)
		{
			pDesk->sGameData.T_CountFen.byHuType[i][j] = pDesk->sGameData.T_HuPai.byHuType[i][j];
		}
	}
//	pDesk->sGameData.T_CountFen.bDH = pDesk->sGameData.T_HuPai.bDuoXiang;
	pDesk->sGameData.T_CountFen.bZiMo = pDesk->sGameData.T_HuPai.bZimo;
	pDesk->sGameData.T_CountFen.byUser = pDesk->sGameData.T_HuPai.byUser;	
	pDesk->sGameData.T_CountFen.byDianPao = pDesk->sGameData.T_HuPai.byDianPao;		
//	pDesk->sGameData.T_CountFen.byPs = pDesk->sGameData.T_HuPai.byPs;	
	pDesk->sGameData.T_CountFen.byNt = pDesk->sGameData.m_byNtStation;
	if(pDesk->sGameData.T_CountFen.bZiMo )
	{
		pDesk->sGameData.T_CountFen.byDianPao = pDesk->sGameData.T_CountFen.byUser;
	}


	memset(pDesk->sGameData.T_CountFen.m_byArHandPai,255,sizeof(pDesk->sGameData.T_CountFen.m_byArHandPai));
	memset(pDesk->sGameData.T_HuPai.m_byArHandPai,255,sizeof(pDesk->sGameData.T_HuPai.m_byArHandPai));

	pDesk->sUserData.CopyHandPai(pDesk->sGameData.T_CountFen.m_byArHandPai,pDesk->sGameData.T_HuPai.byUser,true);
	pDesk->sUserData.CopyHandPai(pDesk->sGameData.T_HuPai.m_byArHandPai,pDesk->sGameData.T_HuPai.byUser,true);

	
}

///������Ϸ�����¼�
void ThingHandle::ExecuteNormalEnd(BYTE &nextID,BYTE &time)
{
	pDesk->KillTimer(TIME_WAIT_MSG);

	pDesk->sGameData.m_byThingDoing = THING_ENG_HANDLE;
	///��Ϸ���������¼�
//	pDesk->sGameData.T_CountFen.byLianZhuang = pDesk->sUserData.m_byLianZhuang;
	//ȷ��ׯ��
	if(pDesk->sGameData.m_mjRule.byNextNtType == 0)
	{///ׯӮ��ׯ�������¼���ׯ
//		if(!pDesk->sGameData.T_CountFen.bHu[pDesk->sGameData.m_byNtStation] || pDesk->sGameData.T_CountFen.byUser==255)//������û��ׯ�һ�������
		{
			pDesk->sGameData.m_byNtStation = GetNextStation(pDesk->sGameData.m_byNtStation);
			pDesk->sUserData.m_byLianZhuang = 1;
		}
//		else 
		{
			pDesk->sUserData.m_byLianZhuang++;
		}
	}
	else if(pDesk->sGameData.m_mjRule.byNextNtType == 1)
	{///ׯӮ��������ׯ�������¼���ׯ
//		if(!pDesk->sGameData.T_CountFen.bHu[pDesk->sGameData.m_byNtStation] && pDesk->sGameData.T_CountFen.byUser!=255)//������û��ׯ�һ�������
		{
			pDesk->sGameData.m_byNtStation = GetNextStation(pDesk->sGameData.m_byNtStation);
			pDesk->sUserData.m_byLianZhuang = 1;
		}
//		else 
		{
			pDesk->sUserData.m_byLianZhuang++;
		}
	}
	else if(pDesk->sGameData.m_mjRule.byNextNtType == 2)
	{///˭Ӯ˭��ׯ�����ֻ�ׯӮׯ����ׯ
		if(pDesk->sGameData.T_CountFen.byUser!=pDesk->sGameData.m_byNtStation)
		{
			pDesk->sGameData.m_byNtStation = pDesk->sGameData.T_CountFen.byUser;
			pDesk->sUserData.m_byLianZhuang = 1;
		}
		else
		{
			pDesk->sUserData.m_byLianZhuang++;
		}
	}
	else if(pDesk->sGameData.m_mjRule.byNextNtType == 3)
	{///˭Ӯ˭��ׯ�������¼���ׯ
		if(pDesk->sGameData.T_CountFen.byUser==255)//����
		{
			pDesk->sGameData.m_byNtStation = GetNextStation(pDesk->sGameData.m_byNtStation);
			pDesk->sUserData.m_byLianZhuang = 1;
		}
		else
		{
			if(pDesk->sGameData.m_byNtStation == pDesk->sGameData.T_CountFen.byUser)
			{
				pDesk->sUserData.m_byLianZhuang++;
			}
			else
			{
				pDesk->sUserData.m_byLianZhuang = 1;
			}
			pDesk->sGameData.m_byNtStation = pDesk->sGameData.T_CountFen.byUser;

		}
	}
	else if(pDesk->sGameData.m_mjRule.byNextNtType == 4)
	{//���ܽṹ��������¼���ׯ
		pDesk->sGameData.m_byNtStation = GetNextStation(pDesk->sGameData.m_byNtStation);
		pDesk->sUserData.m_byLianZhuang = 1;
	}
//	pDesk->sGameData.T_CountFen.byNextNt = pDesk->sGameData.m_byNtStation;

	//����ƽ̨������Ϸ�ӿ�
	pDesk->GameFinish(pDesk->sGameData.T_HuPai.byUser,GF_NORMAL);
}

///�쳣��Ϸ�����¼��¼�
void ThingHandle::ExecuteUnNormalEnd(BYTE &nextID,BYTE &time)
{
	pDesk->KillTimer(TIME_WAIT_MSG);
	//����ƽ̨������Ϸ�ӿ�
	pDesk->GameFinish(255,GF_SAFE);
}


///��ȡ�����ݣ�
void ThingHandle::DisPatchCard()
{
	//����
	BYTE index=0;
	memset(pDesk->sUserData.m_MenPai.byMenPai,255,sizeof(pDesk->sUserData.m_MenPai.byMenPai));//
	for(int i=0;i<4;i++)
	{
		if(pDesk->sGameData.m_mjRule.bHaveWan)//����
		{
			for(int j=0;j<9;j++)
			{
				pDesk->sUserData.m_MenPai.byMenPai[index] = stcArr_A_Mj_W[j];
				index++;
			}
		}
		if(pDesk->sGameData.m_mjRule.bHaveBing)//�б�
		{
			for(int j=0;j<9;j++)
			{
				pDesk->sUserData.m_MenPai.byMenPai[index] = stcArr_A_Mj_B[j];
				index++;
			}
		}
		if(pDesk->sGameData.m_mjRule.bHaveTiao)//����
		{
			for(int j=0;j<9;j++)
			{
				pDesk->sUserData.m_MenPai.byMenPai[index] = stcArr_A_Mj_T[j];
				index++;
			}
		}
		if(pDesk->sGameData.m_mjRule.bHaveBaiBan)//�аװ�
		{
			pDesk->sUserData.m_MenPai.byMenPai[index] = stcArr_A_Mj_ZI[0];
			index++;
		}
		if(pDesk->sGameData.m_mjRule.bHaveFaCai)//�з���
		{
			pDesk->sUserData.m_MenPai.byMenPai[index] = stcArr_A_Mj_ZI[1];
			index++;
		}
		if(pDesk->sGameData.m_mjRule.bHaveHongZhong)//�к���
		{
			pDesk->sUserData.m_MenPai.byMenPai[index] = stcArr_A_Mj_ZI[2];
			index++;
		}
		if(pDesk->sGameData.m_mjRule.bHaveFengPai)//�ж�������
		{
			for(int j=0;j<4;j++)
			{
				pDesk->sUserData.m_MenPai.byMenPai[index] = stcArr_A_Mj_FENG[j];
				index++;
			}
		}
	}
	if(pDesk->sGameData.m_mjRule.bHaveFlower)//�л���
	{
		for(int i=0;i<8;i++)
		{
			pDesk->sUserData.m_MenPai.byMenPai[index] = stcArr_A_Mj_Other[i];
			index++;
		}
	}
	///������
	srand(GetTickCount());
	BYTE temp=255,data=0;
	for(int i=0;i<index;i++)
	{
		temp = rand()%(index-i)+i;
		data = pDesk->sUserData.m_MenPai.byMenPai[temp];
		pDesk->sUserData.m_MenPai.byMenPai[temp] = pDesk->sUserData.m_MenPai.byMenPai[i];
		pDesk->sUserData.m_MenPai.byMenPai[i] = data;
	}
	///////////////
	pDesk->sUserData.m_MenPai.byGetPai = pDesk->sUserData.m_MenPai.byGetPai%13;
	//pDesk->sUserData.m_MenPai.byGetPaiDir = pDesk->sUserData.m_MenPai.byGetPaiDir%4;
	if(pDesk->sUserData.m_MenPai.byGetPaiDir == 255)
	{
		pDesk->sUserData.m_MenPai.byGetPaiDir = pDesk->sGameData.m_byNtStation;
	}
	pDesk->sUserData.m_MenPai.byGetPaiDir = pDesk->sUserData.m_MenPai.byGetPaiDir%4;

	int dun = 0,num=0;
	dun = index/8;
	num = (dun*pDesk->sUserData.m_MenPai.byGetPaiDir + pDesk->sUserData.m_MenPai.byGetPai)*2;
	if(num == 0)
		num=2;
	pDesk->sUserData.m_MenPai.byStartIndex = num;//������ʼ����
	pDesk->sUserData.m_MenPai.byEndIndex = num-1;	//���ƽ�������
	pDesk->sUserData.m_MenPai.byAllPaiNum = index;//�����Ƶ�����

	CString str="";
	str.Format(" ������� �¼�DisPatchCard ��ǽ�� dun=%d ��ʼλ��%d ��=%d  ����%d ����%d",dun,pDesk->sUserData.m_MenPai.byStartIndex,pDesk->sUserData.m_MenPai.byMenPai[num],pDesk->sUserData.m_MenPai.byGetPaiDir,pDesk->sUserData.m_MenPai.byGetPai);
	OutputDebugString(str);

	str.Format(" ������� �¼�DisPatchCard dun=%d num%d ����%d ����%d",dun,num,pDesk->sUserData.m_MenPai.byGetPaiDir,pDesk->sUserData.m_MenPai.byGetPai);
	OutputDebugString(str);
}


///���ƣ�ChangeMenPai
///������ת����������,�������������е�����ת����ÿ����ҵ�����������
///@param 
///@return 
void ThingHandle::ChangeMenPai()
{
	int num = 0;
	int index=0;
	num = pDesk->sUserData.m_MenPai.byAllPaiNum/4;
	for(int i=0;i<4;i++)
	{
		memset(pDesk->sUserData.m_iArMenPai[i],255,sizeof(pDesk->sUserData.m_iArMenPai[i]));
		for(int j=i*num;j<(i+1)*num ;j++)
		{
			if(pDesk->sUserData.m_MenPai.byMenPai[j] != 255)
			{
				pDesk->sUserData.m_iArMenPai[i][j-i*num] = 0;
				if(pDesk->sUserData.m_MenPai.byCaiShenIndex == j && pDesk->sUserData.m_MenPai.byCaiShenIndex != 255)
				{
					pDesk->sUserData.m_iArMenPai[i][j-i*num] = pDesk->sUserData.m_MenPai.byMenPai[j];
				}
			}
			else
			{
				pDesk->sUserData.m_iArMenPai[i][j-i*num] = 255;
			}
		}
	}
}

///���ƣ�GetPai
///������ץһ����
///@param station ץ����ҵ�λ�� , head  �Ƿ��ǰ��ץ,type ץ������ 0 ����ץ�ƣ�1��ʼǰ���ƣ�2��ǰ����ץ�ƣ�3����
///@return ץ������ֵ
BYTE ThingHandle::GetPai(int station,bool head,BYTE type,BYTE *pIndex)
{
	BYTE paiIndex = 255;//��ץ�Ƶ�λ��
	if(pDesk->sGameData.m_byThingDoing == THING_ZHUA_PAI && pDesk->sUserData.GetHandPaiCount(station) %3 == 2)//��ҵ������㹻
	{
		OutputDebugString("�齫-���ƣ�������㹻 ������һ����ɾ��");
		pDesk->sUserData.DelleteAHandPai(station,pDesk->sUserData.GetLastHandPai(station));
		//return 255;
	}

	int num=0;//��������
	BYTE card=255;
	while(card==255 && num<10)
	{
		if(head)//��ǰץ
		{
			if(pDesk->sUserData.m_MenPai.byStartIndex>=pDesk->sUserData.m_MenPai.byAllPaiNum)
			{
				pDesk->sUserData.m_MenPai.byStartIndex = 0;
			}
			paiIndex = pDesk->sUserData.m_MenPai.byStartIndex;//��ץ�Ƶ�λ��
			card=pDesk->sUserData.m_MenPai.byMenPai[pDesk->sUserData.m_MenPai.byStartIndex];
			pDesk->sUserData.m_MenPai.byMenPai[pDesk->sUserData.m_MenPai.byStartIndex] = 255;
			pDesk->sUserData.m_MenPai.byStartIndex++;
		}
		else//�Ӻ���ץ
		{
			if(pDesk->sUserData.m_MenPai.byEndIndex == pDesk->sUserData.m_MenPai.byCaiShenIndex)
			{
				if(pDesk->sUserData.m_MenPai.byEndIndex == 0)
				{
					paiIndex = pDesk->sUserData.m_MenPai.byAllPaiNum-1;//��ץ�Ƶ�λ��
					card = pDesk->sUserData.m_MenPai.byMenPai[pDesk->sUserData.m_MenPai.byAllPaiNum-1];
					pDesk->sUserData.m_MenPai.byMenPai[pDesk->sUserData.m_MenPai.byAllPaiNum-1] = pDesk->sUserData.m_MenPai.byMenPai[0];
					pDesk->sUserData.m_MenPai.byEndIndex=pDesk->sUserData.m_MenPai.byAllPaiNum-1;
					pDesk->sUserData.m_MenPai.byEndIndex=pDesk->sUserData.m_MenPai.byEndIndex;
				}
				else
				{
					paiIndex = pDesk->sUserData.m_MenPai.byEndIndex-1;//��ץ�Ƶ�λ��
					card = pDesk->sUserData.m_MenPai.byMenPai[pDesk->sUserData.m_MenPai.byEndIndex-1];
					pDesk->sUserData.m_MenPai.byMenPai[pDesk->sUserData.m_MenPai.byEndIndex-1] = pDesk->sUserData.m_MenPai.byMenPai[pDesk->sUserData.m_MenPai.byEndIndex];
					pDesk->sUserData.m_MenPai.byMenPai[pDesk->sUserData.m_MenPai.byEndIndex] = 255;
					pDesk->sUserData.m_MenPai.byEndIndex--;
					pDesk->sUserData.m_MenPai.byEndIndex=pDesk->sUserData.m_MenPai.byEndIndex;
				}
			}
			else
			{
				paiIndex = pDesk->sUserData.m_MenPai.byEndIndex;//��ץ�Ƶ�λ��
				card = pDesk->sUserData.m_MenPai.byMenPai[pDesk->sUserData.m_MenPai.byEndIndex];
				pDesk->sUserData.m_MenPai.byMenPai[pDesk->sUserData.m_MenPai.byEndIndex] = 255;
				if(pDesk->sUserData.m_MenPai.byEndIndex == 0)
				{
					pDesk->sUserData.m_MenPai.byEndIndex = pDesk->sUserData.m_MenPai.byAllPaiNum-1;
				}
				else
				{
					pDesk->sUserData.m_MenPai.byEndIndex--;
				}
			}
		}
#ifdef MJ_CAN_SETPAI

		if (pDesk->sUserData.m_bySetMoPai[station] != 255)
		{
			card = pDesk->sUserData.m_bySetMoPai[station];
			pDesk->sUserData.m_bySetMoPai[station] = 255;
		}

#endif //MJ_CAN_SETPAI

		//if(station == pDesk->sGameData.m_byNtStation && pDesk->sGameData.m_byThingDoing == THING_ZHUA_PAI)
		//{
		//	card = pDesk->sUserData.m_StrJing.byPai[0];
		//}
		pDesk->sUserData.AddToHandPai(station,card);
	}
		num++;
	if(pIndex != NULL)
	{
		*pIndex = paiIndex;//��ץ�Ƶ�λ��
	}
	return card;
}

///������station��ǰ������Щ����
///���ƣ�CheckAction
///������station ���λ��,pai �����Ҵ�����ƣ�type ���� ���� 0 ץ�ƣ�1�ܿ���2 ���ڣ�3����
///@param 
///@return true ����������false ����������
bool ThingHandle::CheckAction(int station,BYTE pai,BYTE type)
{
	for(int i=0;i<4;++i)
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
			if(pDesk->sCheckHuPai.CanHu(station,pai,pDesk->sGameData.T_CPGNotify[station].byHuType,true))
			{
				pDesk->sGameData.T_CPGNotify[station].bHu = true;
				pDesk->sGameData.T_CPGNotify[station].m_iHuPs = pDesk->sUserData.GetLastHandPai(station);
				pDesk->sGameData.T_CPGNotify[station].m_byDianPao = station;
			}
			//��
			if(!pDesk->sUserData.m_bTing[station] && pDesk->sCPGAction.CanGang(station,pai,pDesk->sGameData.T_CPGNotify[station].m_iGangData,true))
			{
				pDesk->sGameData.T_CPGNotify[station].bGang = true;
			}
			//��
			if(pDesk->sGameData.m_mjAction.bTing && !pDesk->sUserData.m_bTing[station])//���û������
			{
				pDesk->sGameData.T_CPGNotify[station].bTing = pDesk->sCheckHuPai.CanTing(station,pDesk->sGameData.T_CPGNotify[station].m_byTingCanOut);
			}
			if(pDesk->sGameData.T_CPGNotify[station].bHu || pDesk->sGameData.T_CPGNotify[station].bGang || pDesk->sGameData.T_CPGNotify[station].bTing)
			{
				action=true;
				pDesk->sGameData.T_CPGNotify[station].bCanAction = true;
			}
		}
		break;
	case 2://����
		{
			for(int i=0;i<PLAY_COUNT;++i)
			{
				if(i==station)
					continue;
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
				if(pDesk->sCheckHuPai.CanHu(i,pai,pDesk->sGameData.T_CPGNotify[i].byHuType,false))
				{
					pDesk->sGameData.T_CPGNotify[i].bHu = true;
					pDesk->sGameData.T_CPGNotify[i].m_byMaxThing = ACTION_HU;
					pDesk->sGameData.T_CPGNotify[i].m_iHuPs = pai;
					pDesk->sGameData.T_CPGNotify[i].m_byDianPao = station;
				}

				if(pDesk->sGameData.T_CPGNotify[i].bHu || pDesk->sGameData.T_CPGNotify[i].bPeng || pDesk->sGameData.T_CPGNotify[i].bChi || pDesk->sGameData.T_CPGNotify[i].bGang || pDesk->sGameData.T_CPGNotify[i].bTing)
				{
					action=true;
					pDesk->sGameData.T_CPGNotify[i].bCanAction = true;
				}
			}
		}
		break;
	case 3://����
		{
			for(int i=0;i<PLAY_COUNT;++i)
			{
				if(i==station)
					continue;
				//��
				if(pDesk->sCheckHuPai.CanHu(i,pai,pDesk->sGameData.T_CPGNotify[i].byHuType,false))
				{
					pDesk->sGameData.T_CPGNotify[i].bHu = true;
					pDesk->sGameData.T_CPGNotify[i].m_iHuPs = pai;//��¼������
					pDesk->sGameData.T_CPGNotify[i].m_byDianPao = station;
				}
				if(pDesk->sGameData.T_CPGNotify[i].bHu )
				{
					action=true;
					pDesk->sGameData.T_CPGNotify[i].bCanAction = true;
				}
			}
		}
		break;
	}
	if(action)
	{
		return true;
	}
	return false;
}


///�����Զ�������
void ThingHandle::NetCutAutoHandle()
{
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
				tagOutPaiEx outpai;
				outpai.Clear();
				outpai.byUser = pDesk->sGameData.m_byNtStation;
				outpai.byPs = pDesk->sUserData.GetLastHandPai(pDesk->sGameData.m_byNtStation);
			OutputDebugString("�����齫�� THING_BEGIN_OUT   ReceiveUserOutCard");
				ReceiveUserOutCard(pDesk->sGameData.m_byNtStation,&outpai,sizeof(outpai),false);
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
			if(pDesk->sUserData.m_bFoceLeave[pDesk->sUserData.m_byNowOutStation])//���������Ҷ���
			{
				tagOutPaiEx outpai;
				outpai.Clear();
				outpai.byUser = pDesk->sUserData.m_byNowOutStation;
				outpai.byPs = pDesk->sUserData.GetLastHandPai(pDesk->sUserData.m_byNowOutStation);
				ReceiveUserOutCard(pDesk->sUserData.m_byNowOutStation,&outpai,sizeof(outpai),false);
			}
		}
		break;
	case THING_TING_PAI://�����¼�
		{
			if(pDesk->sUserData.m_bFoceLeave[pDesk->sUserData.m_byNowOutStation])//���������Ҷ���
			{
				tagOutPaiEx outpai;
				outpai.Clear();
				outpai.byUser = pDesk->sUserData.m_byNowOutStation;
				outpai.byPs = pDesk->sUserData.GetLastHandPai(pDesk->sUserData.m_byNowOutStation);

			OutputDebugString("�����齫�� THING_TING_PAI   ReceiveUserOutCard");

				ReceiveUserOutCard(pDesk->sUserData.m_byNowOutStation,&outpai,sizeof(outpai),false);
			}
		}
		break;
	}
}

//�������Զ�����2������û���յ��κ���Ϸ��Ϣ����Ϊ����Ϸ���������ñ����������ݵ�ǰִ���¼�����ҵ�״̬�����Զ������ָ���Ϸ����
void ThingHandle::AutoHandle()
{
	switch(pDesk->sGameData.m_byThingDoing)
	{			        				         
	case THING_2SEZI_NT://�׾���2��ɫ�ӵĵ�����Ϊׯ�¼�		   
	case THING_2SEZI_NT_GP://�׾���2��ɫ�Ӷ�ׯ�Һ����Ƶ��¼�	
	case THING_TURN_2SEZI_NT://�׾�������2��ɫ�Ӷ�ׯ���¼�		
	case THING_2SEZI_DIR://��2��ɫ���¼������Ʒ����¼�		
	case THING_2SEZI_DIR_GP://��2��ɫ���¼������Ʒ�������Ƶ��¼�
	case THING_2SEZI_GP://��2��ɫ���¼������Ƶ��¼�												
	case THING_2SEZI_JING://��2��ɫ�Ӷ������¼�			
		{//����ɫ�ӽ�����Ϣ
			for(int i=0;i<PLAY_COUNT;++i)
			{
				if(!pDesk->sUserData.m_bSiziFinish[i])//�����û�з�������Ϣ
				{
					ReceiveSeziFinish(i,NULL,0,false);
				}
			}
		}
		break;
	case THING_ALL_BUHUA://Ϊ������Ҳ����¼�
		{//ִ�п�ʼ�����¼�
			pDesk->sGameData.ApplyThingID = THING_BEGIN_OUT;
			ApplyAction(pDesk->sGameData.ApplyThingID,200);//������һ���¼�
		}
		break;
	case THING_ONE_BUHUA://������Ҳ����¼�	
	case THING_BEGIN_OUT://ׯ�ҿ�ʼ����֪ͨ�¼�	
	case THING_OUT_PAI://�����¼�
	case THING_CHI_PAI://�����¼�
	case THING_PENG_PAI://�����¼�
	case THING_ZHUA_PAI://ץ���¼�
	case THING_GANG_PAI://�����¼�
		{
			OutputDebugString("�����齫�� AutoHandle �Զ����ƴ��� 00");
			//������ҳ���
			AutoOutOrGet();
		}
		break;
	case THING_HU_PAI://���¼�	
		{
			pDesk->sGameData.ApplyThingID = THING_COUNT_FEN;
			ApplyAction(pDesk->sGameData.ApplyThingID,200);//������һ���¼�
		}
		break;
	case THING_COUNT_FEN://����¼�	
		{
			pDesk->sGameData.ApplyThingID = THING_ENG_HANDLE;
			ApplyAction(pDesk->sGameData.ApplyThingID,200);//������һ���¼�
		}
		break;
	case THING_ENG_HANDLE://���������¼�
	case THING_ENG_UN_NORMAL://���������������¼�
		{

		}
		break;
	}
}

///�Զ�������ƻ���ץ��
void ThingHandle::AutoOutOrGet()
{
	bool haveout = false;
	for(int i=0;i<PLAY_COUNT;++i)
	{
		if(pDesk->sUserData.IsOutPaiPeople(i))//�������
		{
			haveout = true;

			tagOutPaiEx outpai;
			outpai.Clear();
			outpai.byUser = i;
			outpai.byPs = pDesk->sUserData.GetLastHandPai(i);

			OutputDebugString("�����齫�� AutoOutOrGet   ReceiveUserOutCard");

			ReceiveUserOutCard(i,&outpai,sizeof(outpai),false);
			break;
		}
	}
	if(!haveout)//û�г��Ƶ���ң�����ץ���¼�
	{
		pDesk->sGameData.ApplyThingID = THING_ZHUA_PAI;
		ApplyAction(pDesk->sGameData.ApplyThingID,200);//������һ���¼�
	}
}

//////////////////////////////��������//////////////////////////////////////////////////////


///�����¼�
void ThingHandle::HandleChiPai(BYTE &nextID,BYTE &time)
{	
	pDesk->sGameData.m_byThingDoing = THING_CHI_PAI;//��¼����ִ�е��¼�
	///�������¼�
	pDesk->sGameData.T_ChiPai = pDesk->sGameData.temp_ChiPai;//��ȡ����
	pDesk->sUserData.m_byNowOutStation = pDesk->sGameData.temp_ChiPai.byUser;
	//��ӳ���
	GCPStructEx chi;
	chi.Init();
	chi.byType = ACTION_CHI;
	chi.iBeStation = pDesk->sGameData.temp_ChiPai.byBeChi;
	chi.iOutpai = pDesk->sGameData.temp_ChiPai.byPs;
	chi.iStation = pDesk->sGameData.temp_ChiPai.byUser;

	BYTE station = pDesk->sGameData.temp_ChiPai.byUser;

	for(int i=0;i<3;i++)
	{	
		chi.byData[i] = pDesk->sGameData.temp_ChiPai.byChiPs[i];
		if(pDesk->sGameData.temp_ChiPai.byChiPs[i] == pDesk->sGameData.temp_ChiPai.byPs)
			continue;
		pDesk->sUserData.DelleteAHandPai(pDesk->sGameData.temp_ChiPai.byUser,pDesk->sGameData.temp_ChiPai.byChiPs[i]);//ɾ������
	}
	pDesk->sUserData.DelleteLastOutPai(pDesk->sGameData.T_OutPai.byUser);
	pDesk->sUserData.AddToGCP(chi.iStation,&chi);

	for(int i=0;i<PLAY_COUNT;++i)
	{
		pDesk->sUserData.CopyGCPData(i,pDesk->sGameData.T_ChiPai.m_UserGCPData[i]);
		pDesk->sUserData.CopyOutPai(i,pDesk->sGameData.T_ChiPai.m_byArOutPai[i]);
	}
	pDesk->sGameData.m_byMaxAction = ACTION_NO;

	//�ж��Ƿ�������
	if(pDesk->sGameData.m_mjAction.bTing)//������
	{
		if(pDesk->sCheckHuPai.CanTing(station,pDesk->sGameData.T_CPGNotify[station].m_byTingCanOut))//����ܷ�����
		{
			pDesk->sGameData.T_CPGNotify[station].bTing = true;
		}
	}
	pDesk->sUserData.m_byApplyMaxAction = ACTION_NO;//��ҵ�ǰ���������¼�������������󣬻ָ�����
}

///�����¼�
void ThingHandle::HandlePengPai(BYTE &nextID,BYTE &time)	
{
	pDesk->sGameData.m_byThingDoing = THING_PENG_PAI;//��¼����ִ�е��¼�
	///�������¼�
	pDesk->sGameData.T_PengPai = pDesk->sGameData.temp_PengPai;//��ȡ����
	pDesk->sUserData.m_byNowOutStation = pDesk->sGameData.temp_PengPai.byUser;
	//�������¼�
	GCPStructEx peng;
	peng.Init();

	peng.byType = ACTION_PENG;
	peng.iBeStation = pDesk->sGameData.temp_PengPai.byBePeng;
	peng.iOutpai = pDesk->sGameData.temp_PengPai.byPs;
	peng.iStation = pDesk->sGameData.temp_PengPai.byUser;
	BYTE station = pDesk->sGameData.temp_PengPai.byUser;

	//�������ɾ�����һ�ų���
	pDesk->sUserData.DelleteLastOutPai(pDesk->sGameData.T_OutPai.byUser);
	for(int i=0;i<2;i++)
	{	
		pDesk->sUserData.DelleteAHandPai(pDesk->sGameData.temp_PengPai.byUser,pDesk->sGameData.temp_PengPai.byPs);//ɾ������
	}
	for(int i=0;i<3;i++)
	{
		peng.byData[i] = pDesk->sGameData.temp_PengPai.byPs;
	}

	pDesk->sUserData.AddToGCP(pDesk->sGameData.temp_PengPai.byUser,&peng);//�������

	for(int i=0;i<PLAY_COUNT;++i)
	{
		pDesk->sUserData.CopyGCPData(i,pDesk->sGameData.T_PengPai.m_UserGCPData[i]);
		pDesk->sUserData.CopyOutPai(i,pDesk->sGameData.T_PengPai.m_byArOutPai[i]);
	}

	//�ж��Ƿ�������
	if(pDesk->sGameData.m_mjAction.bTing)//������
	{
		if(pDesk->sCheckHuPai.CanTing(station,pDesk->sGameData.T_CPGNotify[station].m_byTingCanOut))//����ܷ�����
		{
			pDesk->sGameData.T_CPGNotify[station].bTing = true;
		}
	}

	pDesk->sGameData.m_byMaxAction = ACTION_NO;
	pDesk->sUserData.m_byApplyMaxAction = ACTION_NO;//��ҵ�ǰ���������¼�������������󣬻ָ�����
}

///���¼�
void ThingHandle::HandleGangPai(BYTE &nextID,BYTE &time)	
{
	pDesk->sGameData.m_byThingDoing = THING_GANG_PAI;//��¼����ִ�е��¼�
	nextID = THING_ZHUA_PAI;
	time = 3;
	///�������¼�
	pDesk->sGameData.T_GangPai = pDesk->sGameData.temp_GangPai;//��ȡ����
	pDesk->sUserData.m_byNowOutStation = pDesk->sGameData.temp_GangPai.byUser;

	GCPStructEx gang;
	gang.Init();
	gang.iBeStation = pDesk->sGameData.temp_GangPai.byBeGang;
	gang.iOutpai = pDesk->sGameData.temp_GangPai.byPs;
	gang.iStation = pDesk->sGameData.temp_GangPai.byUser;

	gang.byData[0] = pDesk->sGameData.temp_GangPai.byPs;
	gang.byData[1] = pDesk->sGameData.temp_GangPai.byPs;
	gang.byData[2] = pDesk->sGameData.temp_GangPai.byPs;
	gang.byData[3] = pDesk->sGameData.temp_GangPai.byPs;

	switch(pDesk->sGameData.temp_GangPai.byType)
	{
	case ACTION_AN_GANG://����
		{
			for(int i=0;i<4;++i)
			{	
				pDesk->sUserData.DelleteAHandPai(pDesk->sGameData.temp_GangPai.byUser,pDesk->sGameData.temp_GangPai.byPs);//ɾ������
			}
			gang.byType = AT_QUADRUPLET_CONCEALED;

			////�������(����Ƿ񻹴��ڰ���)
			//CheckAction(pDesk->sGameData.temp_GangPai.byUser,255,1);
		}
		break;
	case ACTION_MING_GANG://����
		{
			for(int i=0;i<3;++i)
			{	
				pDesk->sUserData.DelleteAHandPai(pDesk->sGameData.temp_GangPai.byUser,pDesk->sGameData.temp_GangPai.byPs);//ɾ������
			}
			gang.byType = AT_QUADRUPLET_REVEALED;
			pDesk->sUserData.DelleteLastOutPai(pDesk->sGameData.temp_GangPai.byUser);//�������ɾ�����һ�ų���
		}
		break;
	case ACTION_BU_GANG://����
		{
			pDesk->sUserData.DelleteAHandPai(pDesk->sGameData.temp_GangPai.byUser,pDesk->sGameData.temp_GangPai.byPs);//ɾ������
			pDesk->sUserData.DelleteAGCPData(pDesk->sGameData.temp_GangPai.byUser,ACTION_PENG,pDesk->sGameData.temp_GangPai.byPs);//ɾ����Ӧ����
			gang.byType = AT_QUADRUPLET;
		}
		break;
	}
	pDesk->sUserData.AddToGCP(pDesk->sGameData.temp_GangPai.byUser,&gang);

	for(int i=0;i<PLAY_COUNT;++i)
	{
		pDesk->sUserData.CopyGCPData(i,pDesk->sGameData.T_GangPai.m_UserGCPData[i]);
		pDesk->sUserData.CopyOutPai(i,pDesk->sGameData.T_GangPai.m_byArOutPai[i]);
	}

	if(pDesk->sGameData.temp_GangPai.byType == ACTION_AN_GANG)
	{
		//CheckAction(pDesk->sGameData.temp_GangPai.byUser,255,0);
		pDesk->sGameData.T_CPGNotify[pDesk->sGameData.temp_GangPai.byUser].bHu = false;
		pDesk->sGameData.T_CPGNotify[pDesk->sGameData.temp_GangPai.byUser].bTing = false;
		pDesk->sGameData.T_CPGNotify[pDesk->sGameData.temp_GangPai.byUser].bKan = false;
		pDesk->sGameData.T_CPGNotify[pDesk->sGameData.temp_GangPai.byUser].bSaoHu = false;
	}
	pDesk->sGameData.m_byMaxAction = ACTION_NO;
	///��ǰץ�Ʒ���true ˳ʱ�룬false ��ʱ��
	pDesk->sUserData.m_bZhuaPaiDir = false;
	pDesk->sUserData.m_byApplyMaxAction = ACTION_NO;//��ҵ�ǰ���������¼�������������󣬻ָ�����
}

///���¼�
void ThingHandle::HandleTingPai(BYTE &nextID,BYTE &time)
{
	pDesk->sGameData.m_byThingDoing = THING_TING_PAI;//��¼����ִ�е��¼�
	///�������¼�
	//T_TingPai;	
	pDesk->sGameData.m_byMaxAction = ACTION_NO;
	pDesk->sUserData.m_byApplyMaxAction = ACTION_NO;//��ҵ�ǰ���������¼�������������󣬻ָ�����
}

///���¼�
void ThingHandle::HandleHuPai(BYTE &nextID,BYTE &time)	
{
	pDesk->sGameData.m_byThingDoing = THING_HU_PAI;//��¼����ִ�е��¼�
	///�������¼�
	//T_HuPai;	
	nextID = THING_COUNT_FEN;
	time = 2;
	memset(pDesk->sGameData.T_HuPai.m_byArHandPai,255,sizeof(pDesk->sGameData.T_HuPai.m_byArHandPai));
	pDesk->sUserData.CopyHandPai(pDesk->sGameData.T_HuPai.m_byArHandPai,0,true);
	pDesk->sGameData.m_byMaxAction = ACTION_NO;
	pDesk->sUserData.m_byApplyMaxAction = ACTION_NO;//��ҵ�ǰ���������¼�������������󣬻ָ�����
	OutputDebugString("����  �����¼�����");
}

///���
void ThingHandle::HandleCountFen(BYTE &nextID,BYTE &time)
{
	pDesk->sGameData.m_byThingDoing = THING_COUNT_FEN;
	///����¼�
	nextID = THING_ENG_HANDLE;
	for(int i=0;i<PLAY_COUNT;i++)
	{
//		pDesk->sGameData.T_CountFen.bHu[i] = pDesk->sGameData.T_HuPai.bHaveHu[i];
		//��ȡ��������
		for(int j=0;j<MAX_HUPAI_TYPE;j++)
		{
			pDesk->sGameData.T_CountFen.byHuType[i][j] = pDesk->sGameData.T_HuPai.byHuType[i][j];
		}
	}
//	pDesk->sGameData.T_CountFen.bDH = pDesk->sGameData.T_HuPai.bDuoXiang;
	pDesk->sGameData.T_CountFen.bZiMo = pDesk->sGameData.T_HuPai.bZimo;
	pDesk->sGameData.T_CountFen.byUser = pDesk->sGameData.T_HuPai.byUser;	
	pDesk->sGameData.T_CountFen.byDianPao = pDesk->sGameData.T_HuPai.byDianPao;		
//	pDesk->sGameData.T_CountFen.byPs = pDesk->sGameData.T_HuPai.byPs;	
	pDesk->sGameData.T_CountFen.byNt = pDesk->sGameData.m_byNtStation;
	if(pDesk->sGameData.T_CountFen.bZiMo )
	{
		pDesk->sGameData.T_CountFen.byDianPao = pDesk->sGameData.T_CountFen.byUser;
	}


	memset(pDesk->sGameData.T_CountFen.m_byArHandPai,255,sizeof(pDesk->sGameData.T_CountFen.m_byArHandPai));
	memset(pDesk->sGameData.T_HuPai.m_byArHandPai,255,sizeof(pDesk->sGameData.T_HuPai.m_byArHandPai));

	pDesk->sUserData.CopyHandPai(pDesk->sGameData.T_CountFen.m_byArHandPai,pDesk->sGameData.T_HuPai.byUser,true);
	pDesk->sUserData.CopyHandPai(pDesk->sGameData.T_HuPai.m_byArHandPai,pDesk->sGameData.T_HuPai.byUser,true);



	pDesk->sGameData.ApplyThingID = nextID;
	ApplyAction(nextID,200);//������һ���¼�
	pDesk->sUserData.m_byApplyMaxAction = ACTION_NO;//��ҵ�ǰ���������¼�������������󣬻ָ�����
}


/////////////////////////��������////////////////////////////////////////////////////////////
/// ��Ҷ���
void ThingHandle::UserNetCut(BYTE bDeskStation)
{
	OutputDebugString("�齫-���ߣ�UserNetCut");

	pDesk->sUserData.m_byFoceLeavCount++;			///���������
	pDesk->sUserData.m_bFoceLeave[bDeskStation] = true;
	if(pDesk->sUserData.m_byFoceLeavCount == 255)
	{
		pDesk->sUserData.m_byFoceLeavCount=0;
	}
	//�����й���Ϣ
	/*Usertouguan touguan;
	touguan.desk=bDeskStation;
	touguan.touguang=true;
	pDesk->sUserData.m_bTuoGuan[bDeskStation]=true;
	for(int i=0;i<PLAY_COUNT;++i)
	{
	touguan.bTuoGuan[i] = pDesk->sUserData.m_bTuoGuan[i];
	}
	for(int i=0;i<PLAY_COUNT;i++)
	pDesk->SendGameDataEx(i,&touguan,sizeof(Usertouguan),MDM_GM_GAME_NOTIFY,ASS_AUTOCARD,0);
	pDesk->SendWatchDataEx(PLAY_COUNT,&touguan,sizeof(Usertouguan),MDM_GM_GAME_NOTIFY,ASS_AUTOCARD,0);*/

	NetCutAutoHandle();
		///���ߴ���
}
/*----------------------------------------------------------------------*/
/// �������
void	ThingHandle::UserLeftDesk(BYTE bDeskStation)
{
	//����뿪�� �����µ�һ��
	pDesk->sGameData.m_byNtStation = 255;
	pDesk->sGameData.m_iHuangZhuangCount = 0;
}
/*----------------------------------------------------------------------*/
/// �������
void ThingHandle::UserReCome(BYTE bDeskStation)
{
	/*Usertouguan touguan;
	touguan.desk=bDeskStation;
	touguan.touguang=false;
	pDesk->sUserData.m_bTuoGuan[bDeskStation]=false;

	for(int i=0;i<PLAY_COUNT;++i)
	{
		touguan.bTuoGuan[i] = pDesk->sUserData.m_bTuoGuan[i];
	}

	for(int i=0;i<PLAY_COUNT;i++)
		pDesk->SendGameDataEx(i,&touguan,sizeof(Usertouguan),MDM_GM_GAME_NOTIFY,ASS_AUTOCARD,0);
	pDesk->SendWatchDataEx(PLAY_COUNT,&touguan,sizeof(Usertouguan),MDM_GM_GAME_NOTIFY,ASS_AUTOCARD,0);

	if(pDesk->sUserData.m_byFoceLeavCount == 255)
	{
		pDesk->sUserData.m_byFoceLeavCount=0;
	}
	if(pDesk->sUserData.m_byFoceLeavCount>0)
	{
		pDesk->sUserData.m_byFoceLeavCount--;			///���������
	}
	pDesk->sUserData.m_bFoceLeave[bDeskStation] = false;*/
}

/// �����ʱ����Ϣ
void ThingHandle::OnGameTimer(UINT uTimerID)
{
	switch(uTimerID)
	{
	case 10://�¼���ʱ��id
		{
			pDesk->KillTimer(uTimerID);
			GameCPU(pDesk->sGameData.ApplyThingID);
		}
		break;
	case TIME_CHECK_GAME_MSG://��Ϣ��ʱ���Զ�����
		{
			//pDesk->KillTimer(uTimerID);
			AutoHandle();
		}
		break;

	}

}



/// ���ó�ʱ����
void ThingHandle::SetOutTime(BYTE station,BYTE time,BYTE thing,bool effect)
{
	pDesk->sGameData.m_MjWait.byWaitThing = thing;
	pDesk->sGameData.m_MjWait.byCurChair = station;
	pDesk->sGameData.m_MjWait.byTime = time + 2;
	pDesk->sGameData.m_MjWait.bEffect = effect;
}
/// �ָ���ʱ����
void ThingHandle::ReSetOutTime()
{
	pDesk->sGameData.m_MjWait.Clear();
}
/// ��ʱ����
void ThingHandle::OutTimeHandle()
{
	if(!pDesk->sGameData.m_MjWait.bEffect || pDesk->sGameData.m_MjWait.byCurChair == 255 || pDesk->sGameData.m_MjWait.byTime == 255)
	{
		return;
	}
	if(pDesk->sGameData.m_MjWait.byWaitThing != pDesk->sGameData.m_byThingDoing)
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






