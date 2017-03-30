#include "StdAfx.h"
#include "ServerManage.h"

/**
 * ���캯��
 */
CServerGameDesk::CServerGameDesk(void) : CGameDesk(FULL_BEGIN)
{
	for (int i=0;i<PLAY_COUNT;i++)
	{
		m_bUserNetCut[i]=false;
	}
	m_Endi = m_Endj = -1;
	m_bQueryQuit=false;
	m_iEnableWatch=0;
	m_iLeaveArgee=0;
	m_iLessCount=0;
	m_iPlayCardCount=0;
	m_iBeginStation=0;
	m_iEndStation=0;
	m_iFirstOutPeople=-1;
	m_iOutCardPeople=-1;
	m_iUpGradePeople=-1;
	m_iBeenPlayGame=0;
	m_iGamePoint=0;
	m_bGameStation=GS_WAIT_SETGAME;
	m_CardCount=PLAY_TWO_CARD;
	m_iGuidandeMoney=0x00;								//ָ����
	::memset(&m_PunishPoint,0,sizeof(m_PunishPoint));
	memset(m_iWinNum, 0, sizeof(m_iWinNum)); //�ȷ�

	memset(m_playerChessNum,0,sizeof(m_playerChessNum));
}

/**
 * ��������
 */
CServerGameDesk::~CServerGameDesk(void)
{
}

/**
 * ��ʱ����Ϣ
 */
bool CServerGameDesk::OnTimer(UINT uTimerID)
{
	switch(uTimerID)
	{
	case TIME_GAME_FINISH:	//������ʱ��
		KillTimer(TIME_GAME_FINISH);
		GameFinish(m_iWinFlag, GF_NORMAL);
	}

	return __super::OnTimer(uTimerID);
}

/**
 * ��ȡ��Ϸ״̬��Ϣ
 */
bool CServerGameDesk::OnGetGameStation(BYTE bDeskStation, UINT uSocketID, bool bWatchUser)
{
	switch (m_bGameStation)
	{
	case GS_WAIT_SETGAME: //��Ϸû�п�ʼ״̬
		{
			GameStation_1 GameStation;
			::memset(&GameStation,0,sizeof(GameStation));
			GameStation.iCardCount=m_CardCount;
			//��Ϸ�汾�˶�
			GameStation.iVersion=DEV_HEIGHT_VERSION;						//��Ϸ�汾��
			GameStation.iVersion2=DEV_LOW_VERSION;
			GameStation.iRoomBasePoint = GetRoomBasePoint();
			GameStation.iRunPublish = GetRunPublish();

			//��������
			SendGameStation(bDeskStation,uSocketID,bWatchUser,&GameStation,sizeof(GameStation));

			MessageStruct Mess;
			ZeroMemory(Mess.Message,200);
			lstrcpy(Mess.Message,"��ӭ���μ���������Ϸ��ף����ÿ��ģ�");
			SendGameData(bDeskStation,&Mess,sizeof(Mess),MDM_GM_GAME_NOTIFY,ASS_MESSAGE,0);

			return TRUE;
		}
	case GS_WAIT_ARGEE:	//�ȴ���ҿ�ʼ״̬
		{
			GameStation_2 GameStation;
			::memset(&GameStation,0,sizeof(GameStation));

			GameStation.iJuTimeMinute = m_iJuTimeMinute;
			GameStation.iJuTimeSecond = m_iJuTimeSecond;
			GameStation.iBuTimeMinute = m_iBuTimeMinute;
			GameStation.iBuTimeSecond = m_iBuTimeSecond;
			GameStation.iDuMiaoMinute = m_iDuMiaoMinute;
			GameStation.iDuMiaoSecond = m_iDuMiaoSecond;
			GameStation.iGuidandeMoney = m_iGuidandeMoney;					//���ӵ�ָ����
			//��Ϸ�汾�˶�
			GameStation.iVersion=DEV_HEIGHT_VERSION;						//��Ϸ�汾��
			GameStation.iVersion2=DEV_LOW_VERSION;
			GameStation.iRoomBasePoint = GetRoomBasePoint();
			GameStation.iRunPublish = GetRunPublish();

			//��������
			SendGameStation(bDeskStation,uSocketID,bWatchUser,&GameStation,sizeof(GameStation));
			return TRUE;
		}
	case GS_SEND_CARD:		//����״̬
	case GS_WAIT_BACK:		//�ȴ������״̬
		{			
			return TRUE;
		}
	case GS_PLAY_GAME:	//��Ϸ��״̬
		{
			GameStation_4 GameStation;
			::memset(&GameStation,0,sizeof(GameStation));
			//��Ϸ�汾�˶�
			GameStation.iVersion=DEV_HEIGHT_VERSION;						//��Ϸ�汾��
			GameStation.iVersion2=DEV_LOW_VERSION;
			GameStation.iPlayCount=m_iLessCount;
			GameStation.iBeenPlayGame=m_iBeenPlayGame;		
			GameStation.iRoomBasePoint = GetRoomBasePoint();
			GameStation.iRunPublish = GetRunPublish();

			GameStation.iJuTimeMinute = m_iJuTimeMinute;
			GameStation.iJuTimeSecond = m_iJuTimeSecond;
			GameStation.iBuTimeMinute = m_iBuTimeMinute;
			GameStation.iBuTimeSecond = m_iBuTimeSecond;
			GameStation.iDuMiaoMinute = m_iDuMiaoMinute;
			GameStation.iDuMiaoSecond = m_iDuMiaoSecond;
			GameStation.iEndI=m_Endi;
			GameStation.iEndJ=m_Endj;
			GameStation.iFirstOutPeople = m_iLastDeskStation;
			GameStation.iOutCardPeople = m_iOutCardPeople;
			GameStation.iUpGradePeople = m_iUpGradePeople;
			GameStation.m_stUsedTimeInfo=m_stUsedTimeInfo;

			memcpy(GameStation.bIsInHuiquStation, m_bIsInHuiquStation, sizeof(m_bIsInHuiquStation));
			//��������
			::CopyMemory(GameStation.iTiZiNum,m_iTiZiNum,sizeof(m_iTiZiNum));
			::CopyMemory(GameStation.iQiZiNum,m_iQiZiNum,sizeof(m_iQiZiNum));

			::CopyMemory(GameStation.iQiZi,m_iBoard,sizeof(m_iBoard));
			int iSendSize=sizeof(GameStation);//-sizeof(GameStation.iUserCardList)+sizeof(BYTE)+iPos;
			SendGameStation(bDeskStation,uSocketID,bWatchUser,&GameStation,iSendSize);

			return TRUE;	
		}
	case GS_WAIT_NEXT:		//�ȴ���һ����Ϸ��ʼ
		{
			GameStation_5 GameStation;
			::memset(&GameStation, 0, sizeof(GameStation));
			//��Ϸ�汾�˶�
			GameStation.iVersion=DEV_HEIGHT_VERSION;						//��Ϸ�汾��
			GameStation.iVersion2=DEV_LOW_VERSION;
			GameStation.iRoomBasePoint = GetRoomBasePoint();
			GameStation.iRunPublish = GetRunPublish();
			GameStation.iPlayCount=m_iLessCount;
			GameStation.iCardCount=m_iPlayCardCount;
			GameStation.iBeginStation=m_iBeginStation;
			GameStation.iEndStation=m_iEndStation;
			GameStation.iWinPoint=0;//m_iPlayNTNum[bDeskStation%2]-m_iBeginStation;			
			GameStation.iPunishPoint=0;//m_PunishPoint[bDeskStation];			
			GameStation.iUpGradePeople=m_iUpGradePeople;		
			//GameStation.iPlayNTNum[0] = 0;
			//GameStation.iPlayNTNum[1]=m_iPlayNTNum[1];		
			GameStation.iBeenPlayGame=m_iBeenPlayGame;		

			//��������
			SendGameStation(bDeskStation,uSocketID,bWatchUser,&GameStation,sizeof(GameStation));
			return TRUE;
		}
	}
	return false;
}

/**
 * ������Ϸ״̬
 */
bool CServerGameDesk::ReSetGameState(BYTE bLastStation)
{
	KillTimer(TIME_GAME_FINISH);

	m_Endi = m_Endj = -1;
	if ((bLastStation==GFF_FORCE_FINISH)||(bLastStation==GF_SAFE))
	{
		m_iLessCount=0;
		m_iPlayCardCount=0;
		m_iBeginStation=0;
		m_iEndStation=0;
		m_iBeenPlayGame=0;
		m_iUpGradePeople=-1;
		//m_Logic.SetNTCardNum(0);
		::memset(m_PunishPoint,0,sizeof(m_PunishPoint));
		memset(m_iWinNum, 0, sizeof(m_iWinNum)); //�ȷ�
	}

	m_bQueryQuit=false;
	m_iLeaveArgee=0;
	m_iGamePoint=0;
	m_iFirstOutPeople=-1;
	m_iOutCardPeople=-1;
	//	m_Logic.SetNTHuaKind(UG_ERROR_HUA);

	return TRUE;
}

/**
 * ��Ϸ��ʼ
 */
bool CServerGameDesk::GameBegin(BYTE bBeginFlag)
{
	if (__super::GameBegin(bBeginFlag)==false) 
		return false;

	memset(m_bIsInHuiquStation, false, sizeof(m_bIsInHuiquStation));

	//����״̬
	m_bQiuHe = false;
	m_bQueryQuit=false;
	m_iBeenPlayGame++;
	//	m_Logic.SetNTHuaKind(UG_ERROR_HUA);
	//m_bGameStation=GS_SEND_CARD;

	m_iFinishNumCnt = 0;
	m_iDianMuResult = 0;

	for (int i = 0; i < WZQ_MAX_I; i++)
		for (int j = 0; j < WZQ_MAX_J; j++)
		{
			//if (i == 0 || j == 0 || i == WZQ_MAX_I - 1 || j == WZQ_MAX_J - 1)
			//{
			//	m_iBoard[i][j] = WQ_FLAG_SIDE;
			//	continue;
			//}
			//else 
			m_iBoard[i][j] = WZQ_FLAG_NONE;
		}

		::memset(m_playerChessNum,0,sizeof(m_playerChessNum));

		::memset(m_iQiZiNum,0,sizeof(m_iQiZiNum));
		::memset(m_iQiZiLastNum,0,sizeof(m_iQiZiLastNum));
		::memset(m_iTiZiNum,0,sizeof(m_iTiZiNum));
		::memset(m_iLastBoard,0,sizeof(m_iLastBoard));
		::memset(m_iLastTiZiNum,0,sizeof(m_iLastTiZiNum));

		//���Ϳ�ʼ��Ϣ
		BeginUpgradeStruct BeginMessage;
		BeginMessage.iNtStation=0;//m_Logic.GetNTCardNum();
		BeginMessage.iStation[0]=0;//m_iPlayNTNum[0];
		BeginMessage.iStation[1]=0;//m_iPlayNTNum[1];
		BeginMessage.iPlayCount=m_iBeenPlayGame;
		BeginMessage.iUpgradeStation = m_iUpGradePeople;

		for (int i = 0; i < 2;i++) 
			SendGameData(i,&BeginMessage,sizeof(BeginMessage),MDM_GM_GAME_NOTIFY,ASS_BEGIN_UPGRADE,0);
		SendWatchData(m_bMaxPeople,&BeginMessage,sizeof(BeginMessage),MDM_GM_GAME_NOTIFY,ASS_BEGIN_UPGRADE,0);

		GameReady();
		//
		BeginPlayUpGrade();

		return TRUE;
}

/**
 * ��Ϸ׼��
 */
BOOL CServerGameDesk::GameReady()
{
	if(-1 == m_iUpGradePeople)
		m_iUpGradePeople= WZQ_BLACK_PLAYER;
	else
	{
		if(m_iUpGradePeople == WZQ_BLACK_PLAYER)		//�����Ⱥ���
			m_iUpGradePeople = WZQ_WHITE_PLAYER;
		else if(m_iUpGradePeople == WZQ_WHITE_PLAYER)
			m_iUpGradePeople = WZQ_BLACK_PLAYER;
	}

	//����,����λ��
	m_iBlackStation = m_iUpGradePeople;
	m_iWhiteStation =(m_iUpGradePeople+1)%2;
	GameReadyStruct GameReady;
	::memset(&GameReady,0,sizeof(GameReady));
	GameReady.iBlackStation=m_iBlackStation;
	GameReady.iWhiteStation=m_iWhiteStation;
	for (int i = 0; i < 2;i++) 
		SendGameData(i,&GameReady,sizeof(GameReady),MDM_GM_GAME_NOTIFY,ASS_GAME_READY,0);
	SendWatchData(m_bMaxPeople,&GameReady,sizeof(GameReady),MDM_GM_GAME_NOTIFY,ASS_GAME_READY,0);

	return TRUE;
}

/**
 * ��Ϸ��ʼ
 */
BOOL CServerGameDesk::BeginPlayUpGrade()
{
	m_bGameStation = GS_PLAY_GAME;
	m_iOutCardPeople = m_iUpGradePeople;
	m_iFirstOutPeople = m_iUpGradePeople;
	m_iGamePoint = 0;

	//���ͻ��˷�����Ϸ��ʼ��Ϣ
	BeginPlayStruct Begin;
	Begin.iOutDeskStation = m_iOutCardPeople;

	Begin.iJuTimeMinute = m_iJuTimeMinute;
	Begin.iJuTimeSecond = m_iJuTimeSecond;
	Begin.iBuTimeMinute = m_iBuTimeMinute;
	Begin.iBuTimeSecond = m_iBuTimeSecond;
	Begin.iDuMiaoMinute = m_iDuMiaoMinute;
	Begin.iDuMiaoSecond = m_iDuMiaoSecond;

	for (int i=0;i<m_bMaxPeople;i++) 
	{
		SendGameData(i, &Begin, sizeof(Begin), MDM_GM_GAME_NOTIFY, ASS_GAME_PLAY, 0);
	}
	SendWatchData(m_bMaxPeople,&Begin,sizeof(Begin),MDM_GM_GAME_NOTIFY,ASS_GAME_PLAY,0);

	return TRUE;
}

/**
 * �¼Ӻ���
 */
BOOL CServerGameDesk::UserOutCard(BYTE bDeskStation,int chessColor,int iEndI,int iEndJ)
{
	//ͳ�Ƶ�ǰ������Ϊ�ڷ����ǰ׷�
	//���浱ǰ���
//	int iValue=(bDeskStation+1)%3;
	m_iLastDeskStation = bDeskStation;
	//������һ����
	::CopyMemory(m_iLastBoard,m_iBoard,sizeof(m_iBoard));
	m_Endi=iEndI;
	m_Endj=iEndJ;
	m_iBoard[iEndI][iEndJ] = chessColor;

	//������Ŀ�ۼ�
	if (bDeskStation <= 1)
	{
		m_playerChessNum[bDeskStation]++;
	}

	//ͳ��������
	PlayChessMsg playChessInfo;
	::memset(&playChessInfo,0,sizeof(playChessInfo));
	playChessInfo.iEndI = iEndI;
	playChessInfo.iEndJ = iEndJ;
	//	playChessInfo.iNextPlayStation =  m_iOutCardPeople;
	playChessInfo.iPlayFlag = bDeskStation; //���ӵ���
	//	::CopyMemory(playChessInfo.iQiZiNum, m_iQiZiNum, sizeof(m_iQiZiNum)); //ÿ���˵�������
	//	::CopyMemory(playChessInfo.iChessArray,iPlayQi,sizeof(playChessInfo.iChessArray));

	for(int i = 0; i < 2; i++)
		SendGameData(i, &playChessInfo, sizeof(playChessInfo), MDM_GM_GAME_NOTIFY, ASS_OUT_CARD_RESULT, 0);
	SendWatchData(m_bMaxPeople,&playChessInfo,sizeof(playChessInfo),MDM_GM_GAME_NOTIFY,ASS_OUT_CARD_RESULT,0);
	//�ܷ����(�ɿͻ���ʵ��)
	//IsFinish(iEndI,iEndJ,iValue);
	//CanFinish();

	//�ж��Ƿ����̣������̻�û������Ϸ�������

	int regretPlayer = (bDeskStation+1) % 2;

	if ( m_playerChessNum[regretPlayer] + m_playerChessNum[bDeskStation] >= 361 )
	{
		m_iWinFlag = -1;
		GameFinish(0,GF_NORMAL);
	}

	return TRUE;
}

/**
 * �û�����(�ڷ���ʾ��λ��,�׷���ʾ��λ��)
 */
BOOL CServerGameDesk::UserOutCard(BYTE bDeskStation,int iEndI,int iEndJ)
{
	//ͳ�Ƶ�ǰ������Ϊ�ڷ����ǰ׷�
	//���浱ǰ���
	int iValue=(bDeskStation+1)%3;
	m_iLastDeskStation = bDeskStation;
	//������һ����
	::CopyMemory(m_iLastBoard,m_iBoard,sizeof(m_iBoard));
	m_Endi=iEndI;
	m_Endj=iEndJ;
	m_iBoard[iEndI][iEndJ] = iValue;
	//ͳ��������
	PlayChessMsg playChessInfo;
	::memset(&playChessInfo,0,sizeof(playChessInfo));
	playChessInfo.iEndI = iEndI;
	playChessInfo.iEndJ = iEndJ;
	//	playChessInfo.iNextPlayStation =  m_iOutCardPeople;
	playChessInfo.iPlayFlag = bDeskStation; //���ӵ���
	//	::CopyMemory(playChessInfo.iQiZiNum, m_iQiZiNum, sizeof(m_iQiZiNum)); //ÿ���˵�������
	//	::CopyMemory(playChessInfo.iChessArray,iPlayQi,sizeof(playChessInfo.iChessArray));

	for(int i = 0; i < 2; i++)
		SendGameData(i, &playChessInfo, sizeof(playChessInfo), MDM_GM_GAME_NOTIFY, ASS_OUT_CARD_RESULT, 0);
	SendWatchData(m_bMaxPeople,&playChessInfo,sizeof(playChessInfo),MDM_GM_GAME_NOTIFY,ASS_OUT_CARD_RESULT,0);
	//�ܷ����(�ɿͻ���ʵ��)
	//IsFinish(iEndI,iEndJ,iValue);
	//CanFinish();
	return TRUE;
}

/**
 * �Ƿ�Y�� 
 */
BOOL CServerGameDesk::IsFinish(int iEndI,int iEndJ,int Value)
{
	if(!Judge(iEndI,iEndJ,Value))
		SetTimer(TIME_GAME_FINISH, 2000);
	return true;
}

/**
 * �ܷ����(��������ȫ���ɿͻ���ʵ��)
 */
BOOL CServerGameDesk::CanFinish(BYTE PutStoneDeskStation,BOOL bCanFinish/*,int iWiner*/)
{
	if(PutStoneDeskStation!=m_iOutCardPeople)
		return true;
	m_iLastDeskStation = PutStoneDeskStation;
	m_iWinFlag = PutStoneDeskStation;
	if(bCanFinish)
	{
		//if(iWiner == -1)
		SetTimer(TIME_GAME_FINISH, 2000);
		return true;
	}

	//��һ��������
	m_iOutCardPeople=(PutStoneDeskStation+1)%2;
	PlayChessMsg playChessInfo;
	::memset(&playChessInfo,0,sizeof(playChessInfo));
	//	playChessInfo.iEndI = iEndI;
	//	playChessInfo.iEndJ = iEndJ;
	//	playChessInfo.iNextPlayStation =  m_iOutCardPeople;
	playChessInfo.iNextPlayStation = m_iOutCardPeople; //���ӵ���
	//	::CopyMemory(playChessInfo.iQiZiNum, m_iQiZiNum, sizeof(m_iQiZiNum)); //ÿ���˵�������
	//	::CopyMemory(playChessInfo.iChessArray,iPlayQi,sizeof(playChessInfo.iChessArray));

	for(int i = 0; i < 2; i++)
		SendGameData(i, &playChessInfo, sizeof(playChessInfo), MDM_GM_GAME_NOTIFY, ASS_OUT_CARD, 0);
	SendWatchData(m_bMaxPeople,&playChessInfo,sizeof(playChessInfo),MDM_GM_GAME_NOTIFY,ASS_OUT_CARD,0);

	return true;
}

/**
 * �û�����
 */
bool CServerGameDesk::UserOutCard(BYTE bDeskStation, int iPlayQi[][21], int iPlayFlag, int iEndI, int iEndJ)
{

	if (bDeskStation != m_iOutCardPeople) return false;

	//���浱ǰ���
	m_iLastDeskStation = bDeskStation;
	::CopyMemory(m_iLastBoard, m_iBoard, sizeof(m_iBoard));
	::CopyMemory(m_iLastTiZiNum, m_iTiZiNum, sizeof(m_iTiZiNum));

	m_Endi = iEndI;
	m_Endj = iEndJ;

	m_iOutCardPeople = (bDeskStation + 1) % 2; //��һ������

	::CopyMemory(m_iBoard, iPlayQi, sizeof(m_iBoard));

	::memset(m_iQiZiNum, 0, sizeof(m_iQiZiNum));

	//ͳ����������
	for (int i = 1; i < WZQ_MAX_I - 1; i++)
	{
		for (int j = 1; j < WZQ_MAX_J - 1; j++)
		{
			switch(m_iBoard[i][j])
			{
			case WZQ_FLAG_BLACK:
				m_iQiZiNum[WZQ_BLACK_PLAYER]++;
				break;

			case WZQ_FLAG_WHITE:
				m_iQiZiNum[WZQ_WHITE_PLAYER]++;
				break;;
			}
		}
	}

	//ͳ��������
	PlayChessMsg playChessInfo;
	::memset(m_iTiZiNum, 0, sizeof(m_iTiZiNum));
	/*
	int iCnt;
	if (bDeskStation == WZQ_BLACK_PLAYER)//�ڷ�����ͳ������׷�����
	{
	iCnt = m_iQiZiLastNum[WZQ_WHITE_PLAYER] - m_iQiZiNum[WZQ_WHITE_PLAYER];
	if (iCnt < 0) iCnt = 0;
	m_iTiZiNum[WZQ_BLACK_PLAYER] += iCnt;
	playChessInfo.iTiZiNum[WZQ_BLACK_PLAYER] = m_iTiZiNum[WZQ_BLACK_PLAYER];
	playChessInfo.iTiZiNum[WZQ_WHITE_PLAYER] = m_iTiZiNum[WZQ_WHITE_PLAYER];
	}
	else if (bDeskStation == WZQ_WHITE_PLAYER)//�׷�����ͳ������ڷ�����
	{
	iCnt = m_iQiZiLastNum[WZQ_BLACK_PLAYER] - m_iQiZiNum[WZQ_BLACK_PLAYER];
	if (iCnt < 0) iCnt = 0;
	m_iTiZiNum[WZQ_WHITE_PLAYER] += iCnt;
	playChessInfo.iTiZiNum[WZQ_WHITE_PLAYER] = m_iTiZiNum[WZQ_WHITE_PLAYER];
	playChessInfo.iTiZiNum[WZQ_BLACK_PLAYER] = m_iTiZiNum[WZQ_BLACK_PLAYER];
	}
	*/

	//int iNextPlayFlag = iPlayFlag;

	::CopyMemory(m_iQiZiLastNum, m_iQiZiNum, sizeof(m_iQiZiNum));

	if( (m_iQiZiNum[WZQ_BLACK_PLAYER] + m_iQiZiNum[WZQ_WHITE_PLAYER]) >= (WZQ_MAX_I-2)*(WZQ_MAX_J-2) )
	{
		m_bQiuHe = true; //����
		m_iWinFlag = -1;
		GameFinish(m_iWinFlag, GF_NORMAL);

		return true;
	}

	/* �Ե�ǰ����λ��Ϊ���㣬�жϰ˸������ͬɫ�����Ƿ��Ѿ�����5��һ�� */
	const int endTime = 2*1000; //ms
	int k = 0,l=0;
	//���ϵ���
	int count_up = 0;

	for(k = iEndI-WZQ_NUMBER+1; k <iEndI+ WZQ_NUMBER; k++) 
	{
		if(k < 1)
		{
			continue; //�����߽�
		}
		if(k > 19)
		{
			break; //�����߽�
		}
		if(m_iBoard[k][iEndJ]%10 != m_iBoard[iEndI][iEndJ]%10)
		{
			count_up = 0;
			continue; //������ͬɫ������
		}
		else if(m_iBoard[k][iEndJ]%10 == m_iBoard[iEndI][iEndJ]%10)
		{
			count_up++; //ͬɫ���ӣ�����
			if(count_up >= WZQ_NUMBER) 
				break;
		}
	}
	if(count_up >= WZQ_NUMBER) 
	{
		m_iWinFlag = bDeskStation;
		SetTimer(TIME_GAME_FINISH, endTime);
		m_iOutCardPeople=-1;
		goto finish;
	}
	//���ϵ���
	count_up = 0;
	for(k = iEndJ-WZQ_NUMBER+1; k <iEndJ+ WZQ_NUMBER; k++) 
	{

		if(k < 1)
		{
			continue; //�����߽�
		}
		if(k > 19)
		{
			break; //�����߽�
		}
		if(m_iBoard[iEndI][k]%10 != m_iBoard[iEndI][iEndJ]%10)
		{
			count_up = 0;
			continue; //������ͬɫ������
		}
		else if(m_iBoard[iEndI][k]%10 == m_iBoard[iEndI][iEndJ]%10)
			count_up++; //ͬɫ���ӣ�����
		if(count_up >= WZQ_NUMBER) 
			break;
	}
	if(count_up >= WZQ_NUMBER) 
	{
		m_iWinFlag = bDeskStation;
		SetTimer(TIME_GAME_FINISH, endTime);
		m_iOutCardPeople=-1;
		goto finish;
	}
	//���ϵ�����
	count_up = 0;
	for(k=iEndI-WZQ_NUMBER+1,l=iEndJ-WZQ_NUMBER+1; k <iEndI+ WZQ_NUMBER&&l<iEndJ+WZQ_NUMBER; k++,l++) 
	{
		if(k < 1||l<1)
		{
			count_up = 0;
			continue; //�����߽�
		}
		if(k > 19||l>19)
		{
			count_up = 0;
			continue; //�����߽�
		}
		if(m_iBoard[k][l]%10 != m_iBoard[iEndI][iEndJ]%10)
		{
			count_up = 0;
			continue; //������ͬɫ������
		}
		else if(m_iBoard[k][l]%10 == m_iBoard[iEndI][iEndJ]%10)
			count_up++; //ͬɫ���ӣ�����
		if(count_up >= WZQ_NUMBER) 
			break;
	}
	if(count_up >= WZQ_NUMBER) 
	{
		m_iWinFlag = bDeskStation;
		SetTimer(TIME_GAME_FINISH, endTime);
		m_iOutCardPeople=-1;
		goto finish;
	}
	//���ϵ�����
	count_up = 0;
	for(k=iEndI+WZQ_NUMBER-1,l=iEndJ-WZQ_NUMBER+1; k >iEndI- WZQ_NUMBER&&l<iEndJ+WZQ_NUMBER; k--,l++) 
	{
		if(k < 1||l<1)
		{
			count_up = 0;
			continue; //�����߽�
		}
		if(k > 19||l>19)
		{
			count_up = 0;
			continue; //�����߽�
		}
		if(m_iBoard[k][l]%10 != m_iBoard[iEndI][iEndJ]%10)
		{
			count_up = 0;
			continue; //������ͬɫ������
		}
		else if(m_iBoard[k][l]%10 == m_iBoard[iEndI][iEndJ]%10)
			count_up++; //ͬɫ���ӣ�����
		if(count_up >= WZQ_NUMBER) 
			break;
	}
	if(count_up >= WZQ_NUMBER) 
	{
		m_iWinFlag = bDeskStation;
		SetTimer(TIME_GAME_FINISH, endTime);
		m_iOutCardPeople=-1;
		goto finish;
	}
finish:
	playChessInfo.iEndI = iEndI;
	playChessInfo.iEndJ = iEndJ;
	playChessInfo.iNextPlayStation =  m_iOutCardPeople;
	playChessInfo.iPlayFlag = bDeskStation; //���ӵ���
	::CopyMemory(playChessInfo.iQiZiNum, m_iQiZiNum, sizeof(m_iQiZiNum)); //ÿ���˵�������
	::CopyMemory(playChessInfo.iChessArray,iPlayQi,sizeof(playChessInfo.iChessArray));

	for(int i = 0; i < 2; i++)
		SendGameData(i, &playChessInfo, sizeof(playChessInfo), MDM_GM_GAME_NOTIFY, ASS_OUT_CARD, 0);
	SendWatchData(m_bMaxPeople,&playChessInfo,sizeof(playChessInfo),MDM_GM_GAME_NOTIFY,ASS_OUT_CARD,0);
	return true;
}

/**
 * ��һ�ֿ�ʼ
 */
BOOL CServerGameDesk::NewPlayTurn(int iWiner)
{
	return TRUE;
}

/**
 * ��Ϸ����
 */
bool CServerGameDesk::GameFinish(BYTE bDeskStation, BYTE bCloseFlag)
{
	// ƽ̨�����벽ʱ���ܻ��ͻ���½�������, ��������ж�
	if (m_bGameStation != GS_PLAY_GAME)
		return true;

	//�õ���С���Ľ��
	long m_dwMaxPoint = 0;
	bool bSetMaxMoney = false;
	/*for (BYTE i=0;i<m_bMaxPeople;i++)
	{
	if (m_pUserInfo[i]!=NULL)
	{
	if (bSetMaxMoney==false)
	{
	bSetMaxMoney=true;
	m_dwMaxPoint=(long int)m_pUserInfo[i]->m_UserData.dwPoint-1;
	}
	else 
	m_dwMaxPoint=__min(m_dwMaxPoint,(long int)m_pUserInfo[i]->m_UserData.dwPoint-1);
	}
	}
	if(m_pDataManage->m_InitData.uComType!=TY_NORMAL_GAME && m_dwMaxPoint<0)
	{
	TRACE("���ִ���Χ���һ������Ϸ�У���ҵĽ����Ϊ������");
	return false;
	}*/
	CString CST;
	CST.Format("wysdebug bCloseFlag===%d,bDeskStation===%d",bCloseFlag,bDeskStation);
	OutputDebugString(CST);

	switch (bCloseFlag)
	{
	case GF_NORMAL: //��Ϸ��������
		{
			int iBasePoint = m_pDataManage->m_InitData.uBasePoint; //����
			int iTruePoint= CountWinPiont();
			//��Ϸ����
			GameEndStruct GameEnd;
			::memset(&GameEnd, 0, sizeof(GameEnd));
			GameEnd.iUpGradeStation = m_iUpGradePeople;
			GameEnd.iGamePoint = m_iGamePoint;
			
			//��һ�����
			if (m_iWinFlag != -1) //���Ǻ���
			{
				//ʤ�ҵıȷ��ۼ�1
				m_iWinNum[m_iWinFlag]++;
				m_iWinNum[(m_iWinFlag+1)%2]--;
			}
			::CopyMemory(GameEnd.iWinNum,m_iWinNum,sizeof(GameEnd.iWinNum));

			for (int i = 0; i < 2; i++)
			{
				if(i==m_iUpGradePeople)
					GameEnd.iTurePoint[i] = iTruePoint;	
				else
					GameEnd.iTurePoint[i] = -iTruePoint;
				GameEnd.iWinNum[i] = m_iWinNum[i]; //�ȷ�
			}
			//m_iUpGradePeople=(m_iUpGradePeople+1)%2;
			//������һ��
			m_bGameStation = GS_WAIT_NEXT;
			for (int i = 0; i < m_bMaxPeople; i++)
			{
				if (m_pUserInfo[i] != NULL) 
					m_pUserInfo[i]->m_UserData.bUserState = USER_SITTING;
			}
			__int64  temp_point[PLAY_COUNT];
			bool     temp_cut[PLAY_COUNT];
			memset(temp_cut,0,sizeof(temp_cut));
			for (int i=0;i<PLAY_COUNT;i++)
			{
				temp_point[i]=GameEnd.iTurePoint[i];//+m_iAwardPoint[i];
			}
			ChangeUserPointint64(temp_point, temp_cut);	//������д�����ݿ���
			__super::RecoderGameInfo(GameEnd.iChangeMoney);
			GameEnd.iDoublePointEffect = GetDoublePointEffect();//20081125

			bool bNotCostPoint = (m_pDataManage->m_InitData.dwRoomRule & GRR_NOT_COST_POINT) > 0;//��ҳ����ۻ���add by xqm 2010-11-18
			if (true == bNotCostPoint)
			{
				memset(GameEnd.iTurePoint,0,sizeof(GameEnd.iTurePoint));
			}
			for (int i=0;i<m_bMaxPeople;i++) 
				SendGameData(i,&GameEnd,sizeof(GameEnd),MDM_GM_GAME_NOTIFY,ASS_CONTINUE_END,0);
			SendWatchData(m_bMaxPeople, &GameEnd, sizeof(GameEnd), MDM_GM_GAME_NOTIFY, ASS_CONTINUE_END, 0);

			__super::GameFinish(bDeskStation,GF_SAFE);
			ReSetGameState(bCloseFlag);
			return true;
		}
	case GF_SAFE: //��Ϸ��ȫ����
		{
			int iBasePoint = m_pDataManage->m_InitData.uBasePoint;//����
			//����÷�
			int iTurePoint = GetUpGrade(m_iPlayCardCount);
			m_bGameStation = GS_WAIT_ARGEE;
			for (int i=0;i<m_bMaxPeople;i++)
			{
				if (m_pUserInfo[i]!=NULL) 
					m_pUserInfo[i]->m_UserData.bUserState=USER_SITTING;
			}
			GameCutStruct CutEnd;
			memset(&CutEnd,0,sizeof(CutEnd));
			CutEnd.bDeskStation=bDeskStation;

			CutEnd.iTurePoint[bDeskStation]=0;
			CutEnd.iTurePoint[(bDeskStation+1)%2]=0;			

			//������Ϣ
			for (int i=0;i<m_bMaxPeople;i++) 
				SendGameData(i,&CutEnd,sizeof(CutEnd),MDM_GM_GAME_NOTIFY,ASS_SALE_END,0);
			SendWatchData(m_bMaxPeople,&CutEnd,sizeof(CutEnd),MDM_GM_GAME_NOTIFY,ASS_SALE_END,0);

			ReSetGameState(bCloseFlag);
			__super::GameFinish(bDeskStation,bCloseFlag);
			return true;
		}
	case GFF_FORCE_FINISH: //�û������뿪----(�û�ǿ��)
		{
		
			m_iWinFlag = (bDeskStation+1)%2;

			int iBasePoint = m_pDataManage->m_InitData.uBasePoint; //����
			int iTruePoint= CountWinPiont();
			//��Ϸ����
			GameEndStruct GameEnd;
			::memset(&GameEnd, 0, sizeof(GameEnd));
			GameEnd.iUpGradeStation = m_iUpGradePeople;
			GameEnd.iGamePoint = m_iGamePoint;

			//��һ�����
			if (m_iWinFlag != -1) //���Ǻ���
			{
				//ʤ�ҵıȷ��ۼ�1
				m_iWinNum[m_iWinFlag]++;
				m_iWinNum[(m_iWinFlag+1)%2]--;
			}
			::CopyMemory(GameEnd.iWinNum,m_iWinNum,sizeof(GameEnd.iWinNum));

			for (int i = 0; i < 2; i++)
			{
				if(i==m_iUpGradePeople)
					GameEnd.iTurePoint[i] = iTruePoint;		//m_iTurePoint[i];
				else
					GameEnd.iTurePoint[i] = -iTruePoint;	//m_iTurePoint[i];
				GameEnd.iWinNum[i] = m_iWinNum[i]; //�ȷ�
			}
			m_bGameStation = GS_WAIT_NEXT;
			for (int i = 0; i < m_bMaxPeople; i++)
			{
				if (m_pUserInfo[i] != NULL) 
					m_pUserInfo[i]->m_UserData.bUserState = USER_SITTING;
			}
			__int64  temp_point[PLAY_COUNT];
			bool     temp_cut[PLAY_COUNT];
			memset(temp_cut,0,sizeof(temp_cut));
			for (int i=0;i<PLAY_COUNT;i++)
			{
				temp_point[i]=GameEnd.iTurePoint[i];//+m_iAwardPoint[i];
			}
			ChangeUserPointint64(temp_point, temp_cut);	//������д�����ݿ���
			__super::RecoderGameInfo(GameEnd.iChangeMoney);
			GameEnd.iDoublePointEffect = GetDoublePointEffect();//20081125

			bool bNotCostPoint = (m_pDataManage->m_InitData.dwRoomRule & GRR_NOT_COST_POINT) > 0;//��ҳ����ۻ���add by xqm 2010-11-18
			if (true == bNotCostPoint)
			{
				memset(GameEnd.iTurePoint,0,sizeof(GameEnd.iTurePoint));
			}
			for (int i=0;i<m_bMaxPeople;i++) 
				SendGameData(i,&GameEnd,sizeof(GameEnd),MDM_GM_GAME_NOTIFY,ASS_CONTINUE_END,0);
			SendWatchData(m_bMaxPeople, &GameEnd, sizeof(GameEnd), MDM_GM_GAME_NOTIFY, ASS_CONTINUE_END, 0);

			ReSetGameState(bCloseFlag);
			__super::GameFinish(bDeskStation,bCloseFlag);
			return true;
		}
	}

	//��������
	ReSetGameState(bCloseFlag);
	__super::GameFinish(bDeskStation,bCloseFlag);
	
	return true;
}

/**
 * �ж��Ƿ�������Ϸ
 */
bool CServerGameDesk::IsPlayGame(BYTE bDeskStation)
{
	if(m_bGameStation>GS_WAIT_ARGEE&&m_bGameStation<GS_WAIT_NEXT)
		return true;
	else
		return false;
	//return __super::IsPlayGame(bDeskStation);
}

/**
 * �û��뿪��Ϸ��
 */
BYTE CServerGameDesk::UserLeftDesk(BYTE bDeskStation, CGameUserInfo * pUserInfo)
{
// 	if (m_bGameStation == GS_PLAY_GAME)
// 	{
// 		m_iWinFlag = (bDeskStation+1)%2;
// 		GameFinish(0, GF_NORMAL);
// 	}

	if(m_pUserInfo[(bDeskStation+1)%2]==NULL)	
		m_bGameStation = GS_WAIT_SETGAME;	
	else
		m_bGameStation = GS_WAIT_ARGEE;

	

	if(m_bGameStation>GS_WAIT_ARGEE)
		GameFinish(bDeskStation,GF_SAFE);

	m_iWinNum[0] = 0;
	m_iWinNum[1] = 0;

	return __super::UserLeftDesk(bDeskStation,pUserInfo);
}
//��Ҷ��ߴ���
bool CServerGameDesk::UserNetCut(BYTE bDeskStation, CGameUserInfo * pLostUserInfo)
{
	CString CST;
	CST.Format("wyshdebug UserNetCut bDeskStation===%d",bDeskStation);
	OutputDebugString(CST);

	m_bUserNetCut[bDeskStation]=true;

	return __super::UserNetCut(bDeskStation,  pLostUserInfo);
}
///�û����½�����Ϸ
bool CServerGameDesk::UserReCome(BYTE bDeskStation, CGameUserInfo * pLostUserInfo)
{
	for(int i=0;i<PLAY_COUNT;i++)
	{
		if(i==bDeskStation)
			continue;
		SendGameData(i,MDM_GM_GAME_NOTIFY,ASS_GET_GAME_USED_TIME,0);
	}
	m_bUserNetCut[bDeskStation]=false;

	return __super::UserReCome(bDeskStation,pLostUserInfo);

}
/**
 * ��Ϸ���ݰ�������
 */
bool CServerGameDesk::HandleNotifyMessage(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser)
{
	switch (pNetHead->bAssistantID)
	{
	case ASS_GM_AGREE_GAME:		//�û�ͬ����Ϸ
		if (bWatchUser) return FALSE;

		if (m_bGameStation==GS_WAIT_SETGAME)	//��������
		{
			if (uSize!=sizeof(UserArgeeGame)) return FALSE;

			UserArgeeGame * pGameSet=(UserArgeeGame *)pData;
			if (!UserSetGame(pGameSet,bDeskStation)) return FALSE;
			__super::HandleNotifyMessage(bDeskStation,pNetHead,pData,uSize,uSocketID,bWatchUser);
			return TRUE;
		}
		if(GS_WAIT_ARGEE==m_bGameStation)
		{
			if(uSize!=sizeof(GuidanceMoney))
				return FALSE;
			GuidanceMoney *pGuidanceMoney=(GuidanceMoney*)pData;
			m_iGuidandeMoney = pGuidanceMoney->iGuidandeMoney;		//ָ����

		}
		//�������
		if ((m_bGameStation!=GS_WAIT_ARGEE)&&(m_bGameStation!=GS_WAIT_NEXT)) 
			return TRUE;
		return __super::HandleNotifyMessage(bDeskStation,pNetHead,pData,uSize,uSocketID,bWatchUser);

	case ASS_OUT_CARD: //�û�����
		{
			if(bWatchUser) return false;
			if(m_bGameStation==GS_WAIT_NEXT || m_bGameStation==GS_WAIT_ARGEE || m_bGameStation==GS_WAIT_SETGAME)
				return true;
			if (uSize != sizeof(PlayChessMsg)) return false;

			PlayChessMsg* pPlayChessInfo = (PlayChessMsg*)pData;
			return UserOutCard(bDeskStation,pPlayChessInfo->iPlayFlag,pPlayChessInfo->iEndI,pPlayChessInfo->iEndJ);			
			//return UserOutCard(bDeskStation,pPlayChessInfo->iChessArray,pPlayChessInfo->iPlayFlag,pPlayChessInfo->iEndI,pPlayChessInfo->iEndJ);
		}
	case ASS_CAN_FINISH://�û����Ӻ�,�ɿͶ�ͳ���Ƿ���Խ���
		{
			if(bWatchUser)
				return false;
			if(m_bGameStation==GS_WAIT_NEXT || m_bGameStation==GS_WAIT_ARGEE || m_bGameStation==GS_WAIT_SETGAME)
				return true;
			if (uSize != sizeof(PlayCheckFinish)) return false;
			PlayCheckFinish* pPlayCheck = (PlayCheckFinish*)pData;
			pPlayCheck->bCanFinish=(!Judge(pPlayCheck->iCurI,pPlayCheck->iCurJ,pPlayCheck->cValue));
			return CanFinish(bDeskStation,pPlayCheck->bCanFinish);			
		}

	case ASS_HAVE_THING:	//���������뿪
		{
			if(bWatchUser) return false;
			HaveThingStruct * pThing=(HaveThingStruct *)pData;
			return UserHaveThing(bDeskStation,pThing->szMessage);
		}
	case ASS_LEFT_RESULT: //ͬ���û��뿪
		{
			if(bWatchUser) return false;
			LeaveResultStruct * pLeave=(LeaveResultStruct *)pData;
			return ArgeeUserLeft(bDeskStation,pLeave->bArgeeLeave);
		}
	case ASS_STOP_THING:
		{
			if(bWatchUser) return false;
			SendGameData((bDeskStation+1)%2,MDM_GM_GAME_NOTIFY,ASS_STOP_THING,0);
			return true;
		}
	case ASS_AGREE_STOP:
		{
			if(bWatchUser) return false;

			StopResultStruct* pStop = (StopResultStruct*)pData;
			if(pStop->bArgee == 1)
			{
				//ͬ��
				StopResultStruct stop;
				stop.bArgee = true;
				SendGameData((bDeskStation+1)%2,&stop,sizeof(stop),MDM_GM_GAME_NOTIFY,ASS_AGREE_STOP,0);

				MessageStruct Mess;
				//memset(&Mess,0,sizeof(Mess));
				//strcpy(Mess.Message,"�мҾ�����������ǰ�����˱��֣�");
				//SendGameData((bDeskStation+1)%2,&Mess,sizeof(Mess),MDM_GM_GAME_NOTIFY,ASS_MESSAGE,0);

				memset(&Mess,0,sizeof(Mess));
				lstrcpy(Mess.Message,"���ĶԼ�������ǰ�������֣�");
				SendWatchData(m_bMaxPeople,&Mess,sizeof(Mess),MDM_GM_GAME_NOTIFY,ASS_MESSAGE,0);
				//������Ϸ
				if (m_bGameStation == GS_PLAY_GAME) 
				{
					m_iWinFlag = -1;
					GameFinish(0,GF_NORMAL);
				}
			}
			else
			{
				StopResultStruct stop;
				stop.bArgee=false;
				SendGameData((bDeskStation+1)%2,&stop,sizeof(stop),MDM_GM_GAME_NOTIFY,ASS_AGREE_STOP,0);
			}
			return true;
		}

	case ASS_SUPER_TIMER://��ʱ����
		{
			if (bWatchUser) return false;

			m_iLastDeskStation = bDeskStation;
			m_iOutCardPeople = (bDeskStation + 1) % 2;
			//for(int i = 0;i < 2;i++) 
				//SendGameData(i,MDM_GM_GAME_NOTIFY,ASS_SUPER_TIMER,m_iOutCardPeople);
			//SendWatchData(m_bMaxPeople,MDM_GM_GAME_NOTIFY,ASS_SUPER_TIMER,m_iOutCardPeople);

			m_iWinFlag = (bDeskStation + 1) % PLAY_COUNT;
			OutputDebugString("wysdebugfoajgoajgogogjoagj");
			GameFinish(bDeskStation,GF_NORMAL);
			return true;
		}

	case ASS_REN_SHU://����
		{
			SendGameData((bDeskStation+1)%2, MDM_GM_GAME_NOTIFY, ASS_REN_SHU, (int)bDeskStation);
			if (m_bGameStation == GS_PLAY_GAME)
			{
				if (bWatchUser) 
					return false;
				int flag = (int)pNetHead->bHandleCode;

				m_iWinFlag = (bDeskStation+1)%2;

				GameFinish(0, GF_NORMAL);
				m_bGameStation = GS_WAIT_ARGEE;  //yinyi �޸�������˳����ֵ�仯������ 080911

			}
			return true;
		}

	case ASS_HUI_QI://����
		{
			if (bDeskStation <= 1)
			{
				int otherPlayer = (bDeskStation+1) % 2; //��һ�����
				if (m_playerChessNum[bDeskStation] < m_playerChessNum[otherPlayer])
				{
					//��������ٽ�������������ֱ�Ӿܾ�����ҵĻ�������
					SendGameData(bDeskStation,MDM_GM_GAME_NOTIFY,ASS_AGREE_HUI_QI,0);
					return true;
				}
			}
			m_bIsInHuiquStation[bDeskStation] = true;
			SendGameData((bDeskStation+1)%2,MDM_GM_GAME_NOTIFY,ASS_HUI_QI,0);
			return true;
		}

	case ASS_AGREE_HUI_QI://����
		{
			int iflag = (int)pNetHead->bHandleCode;

			m_bIsInHuiquStation[(bDeskStation+1)%2] = false;

			if (iflag == 0)	//��ͬ�����
			{
				SendGameData((bDeskStation+1)%2,MDM_GM_GAME_NOTIFY,ASS_AGREE_HUI_QI,iflag);
				return true;
			}
			//ͬ�����󽫻��巽�����岽������
			if (bDeskStation <= 1)
			{
				int regretPlayer = (bDeskStation+1) % 2; //�����������
				if (m_playerChessNum[regretPlayer] > 0)
				{
					m_playerChessNum[regretPlayer]--;
				}
			}

			RegretChessMsg regretInfo;

			m_iOutCardPeople = m_iLastDeskStation;
			regretInfo.iLastDeskStation = m_iLastDeskStation;
			::CopyMemory(regretInfo.iLastTiZiNum,m_iLastTiZiNum,sizeof(m_iLastTiZiNum));
			::CopyMemory(regretInfo.iLastChessArray,m_iLastBoard,sizeof(m_iLastBoard));

			for (int i = 0;i < 2;i++)
				SendGameData(i,&regretInfo,sizeof(regretInfo),MDM_GM_GAME_NOTIFY,ASS_AGREE_HUI_QI,1);

			SendWatchData(m_bMaxPeople,&regretInfo,sizeof(regretInfo),MDM_GM_GAME_NOTIFY,ASS_AGREE_HUI_QI,1);

			::CopyMemory(m_iBoard,m_iLastBoard,sizeof(m_iLastBoard));
			::CopyMemory(m_iTiZiNum,m_iLastTiZiNum,sizeof(m_iLastTiZiNum));

			return true;
		}

	case ASS_AGREE_HUI_QI_PHONE:
		{
			int *iflag = (int*)pData;

			m_bIsInHuiquStation[(bDeskStation+1)%2] = false;

			if (*iflag == 0)	//��ͬ�����
			{
				SendGameData((bDeskStation+1)%2,MDM_GM_GAME_NOTIFY,ASS_AGREE_HUI_QI,*iflag);
				return true;
			}
			//ͬ�����󽫻��巽�����岽������
			if (bDeskStation <= 1)
			{
				int regretPlayer = (bDeskStation+1) % 2; //�����������
				if (m_playerChessNum[regretPlayer] > 0)
				{
					m_playerChessNum[regretPlayer]--;
				}
			}

			RegretChessMsg regretInfo;

			m_iOutCardPeople = m_iLastDeskStation;
			regretInfo.iLastDeskStation = m_iLastDeskStation;
			::CopyMemory(regretInfo.iLastTiZiNum,m_iLastTiZiNum,sizeof(m_iLastTiZiNum));
			::CopyMemory(regretInfo.iLastChessArray,m_iLastBoard,sizeof(m_iLastBoard));

			for (int i = 0;i < 2;i++)
				SendGameData(i,&regretInfo,sizeof(regretInfo),MDM_GM_GAME_NOTIFY,ASS_AGREE_HUI_QI,1);

			SendWatchData(m_bMaxPeople,&regretInfo,sizeof(regretInfo),MDM_GM_GAME_NOTIFY,ASS_AGREE_HUI_QI,1);

			::CopyMemory(m_iBoard,m_iLastBoard,sizeof(m_iLastBoard));
			::CopyMemory(m_iTiZiNum,m_iLastTiZiNum,sizeof(m_iLastTiZiNum));

			return true;
		}
	case ASS_GET_GAME_USED_TIME:
		{
			m_stUsedTimeInfo=*((UsedTimeInfo*)pData);
			return true;
		}

		/*
		case ASS_DIAN_MU://��Ŀ
		SendGameData((bDeskStation+1)%2,MDM_GM_GAME_NOTIFY,ASS_DIAN_MU,0);
		return true;
		*/

		/*
		case ASS_AGREE_DIAN_MU://ͬ���Ŀ
		{
		if (uSize != sizeof(DianMuResultStruct)) return false;
		DianMuResultStruct *dianMuResult = (DianMuResultStruct *) pData;

		if (dianMuResult->bAgree)
		{	
		DianMuResultStruct dianMuInfo;
		dianMuInfo.bAgree = true;
		for (int i = 0;i < 2;i++)
		SendGameData(i,&dianMuInfo,sizeof(dianMuInfo),MDM_GM_GAME_NOTIFY,ASS_AGREE_DIAN_MU,0);
		SendWatchData(m_bMaxPeople,&dianMuInfo,sizeof(dianMuInfo),MDM_GM_GAME_NOTIFY,ASS_AGREE_DIAN_MU,0);
		}
		else
		{
		DianMuResultStruct dianMuInfo;
		dianMuInfo.bAgree = false;
		SendGameData((bDeskStation+1)%2,&dianMuInfo,sizeof(dianMuInfo),MDM_GM_GAME_NOTIFY,ASS_AGREE_DIAN_MU,0);
		}
		return true;
		}
		*/

		/*
		case ASS_NUMBER_ZI://ǿ������
		{
		struct DianMu *p=(struct DianMu *)pData;
		if(m_iFinishNumCnt==0)
		::memcpy(m_idianmu,m_iBoard,sizeof(m_iBoard));
		for(int i=1;i<20;i++)
		{
		for(int j=1;j<20;j++)
		{
		if((p->qi[i][j])==3)
		m_idianmu[i][j]=0;
		}
		}
		m_iFinishNumCnt++;
		if (m_iFinishNumCnt == 2)
		{
		m_iFinishNumCnt=0;
		int i;
		ForceNumberZi(i,m_dianmumsg);
		FinishDianMu finishdm;
		strcpy(finishdm.msg,(LPTSTR)(LPCTSTR) m_dianmumsg);
		::memcpy(finishdm.qi,m_idianmu,sizeof(m_idianmu));
		for (int i = 0; i < 2;i++) 
		SendGameData(i,&finishdm,sizeof(finishdm),MDM_GM_GAME_NOTIFY,ASS_NUMBER_ZI,0);
		SendWatchData(m_bMaxPeople,&finishdm,sizeof(finishdm),MDM_GM_GAME_NOTIFY,ASS_NUMBER_ZI,0);
		}
		return true;
		}
		*/

		/*
		case ASS_DIAN_MU_RESULT://�Ե�Ŀ�������ͬ�⣬������Ŀ���������壩
		{
		int flag = (int) pNetHead->bHandleCode;
		if (flag == 1)//ͬ���Ŀ���
		{
		m_iDianMuResult++;

		if (m_iDianMuResult == 2)//��ͬ����
		{
		int k;
		CString s;
		ForceNumberZi(k,s);

		MessageStruct mess;
		strcpy(mess.Message, (LPTSTR)(LPCTSTR) m_dianmumsg);
		for (int i = 0; i < 2;i++) 
		SendGameData(i,&mess,sizeof(mess),MDM_GM_GAME_NOTIFY,ASS_DIAN_MU_RESULT,flag);
		SendWatchData(m_bMaxPeople,&mess,sizeof(mess),MDM_GM_GAME_NOTIFY,ASS_DIAN_MU_RESULT,flag);

		if (k == -1) m_bQiuHe = true;
		else m_iWinFlag = k;
		GameFinish(0, GF_NORMAL);
		}
		//AfxMessageBox("ͬ���Ŀ���");
		}
		else if (flag == 2)//������Ŀ
		{
		m_iFinishNumCnt = 0;
		m_iDianMuResult = 0;

		for (int i = 0; i < 2;i++) 
		SendGameData(i,MDM_GM_GAME_NOTIFY,ASS_DIAN_MU_RESULT,flag);
		SendWatchData(m_bMaxPeople,MDM_GM_GAME_NOTIFY,ASS_DIAN_MU_RESULT,flag);
		//AfxMessageBox("������Ŀ");
		}
		else if (flag == 3)//��������
		{
		m_iFinishNumCnt = 0;
		m_iDianMuResult = 0;

		for (int i = 0; i < 2;i++) 
		SendGameData(i,MDM_GM_GAME_NOTIFY,ASS_DIAN_MU_RESULT,flag);
		SendWatchData(m_bMaxPeople,MDM_GM_GAME_NOTIFY,ASS_DIAN_MU_RESULT,flag);
		//AfxMessageBox("��������");
		}

		return true;
		}
		*/
	} //end switch.

	return __super::HandleNotifyMessage(bDeskStation,pNetHead,pData,uSize,uSocketID,bWatchUser);
}

/**
 * ����÷�
 */
int	CServerGameDesk::GetUpGrade(int iPlayCardCount)
{
	if (m_bQiuHe)
	{
		m_iTurePoint[0] = 0;
		m_iTurePoint[1] = 0;

		return 0;
	}
	if(m_iWinFlag < 0) return 0;

	m_iTurePoint[m_iWinFlag] = 4;
	m_iTurePoint[(m_iWinFlag+1)%2] = -4;

	m_iWinNum[m_iWinFlag]++; //Ӯ�ҵıȷ�

	return 0;
}

/*
//force number qizi
void CServerGameDesk::ForceNumberZi(int &iWinFlag, CString &strMessage)
{
float totalWhite = 0.0,
totalBlack = 0.0;

m_Logic.NumQiZi(&totalBlack,&totalWhite,m_idianmu);
totalBlack -= WQ_BLACK_TIE_MU;
totalWhite += WQ_BLACK_TIE_MU;

float blackWinMu = totalBlack - totalWhite;
int flag = (blackWinMu > 0.00000) ? 1 : ((blackWinMu == 0.00000) ? 0 : -1);

blackWinMu = (flag > 0) ? blackWinMu : -blackWinMu;
int count = (int) (blackWinMu);//��������
int fraction = (int) ((blackWinMu - count) * 100);//С������
int winFlag = 0;
CString s;

if (flag > 0)//�ڷ�Ӯ
{
winFlag = WZQ_BLACK_PLAYER;
s = TEXT("�ڷ�Ӯ");
goto ret;
}
else if (flag < 0)//�׷�Ӯ
{
winFlag = WZQ_WHITE_PLAYER;
s = TEXT("�׷�Ӯ");
goto ret;
}
else//ƽ��
{
winFlag = -1;
s = TEXT("�˾�Ϊƽ��");
}

ret:if (fraction != 0)
{
CString str;
str.Format("%d",count);
s += str;
switch (fraction)
{
case 25:
s += TEXT("��1/4��");
break;

case 50:
s += TEXT("��1/2��");
break;

case 75:
s += TEXT("��3/4��");
break;
}
}

iWinFlag = winFlag;
strMessage = s;
return;
}
*/

/**
 * �û�������Ϸ
 */
BOOL CServerGameDesk::UserSetGame(UserArgeeGame * pGameSet,BYTE desk)
{
	//Ч������
	if (m_bGameStation!=GS_WAIT_SETGAME) return FALSE;

	//Ч������
	///if (((pGameSet->iPlayCount<=0)||(pGameSet->iPlayCount>99))||
	///	(pGameSet->iBeginStation<2)||(pGameSet->iEndStation>14)||
	///	(pGameSet->iBeginStation>pGameSet->iEndStation)) 
	///	return FALSE;
	///if ((m_CardCount & pGameSet->iCardCount)==0) return FALSE;

	//��������
	//m_iLessCount=pGameSet->iPlayCount;
	//m_iPlayCardCount=2;//(pGameSet->iCardCount&1)?2:3;
	//m_iBeginStation=pGameSet->iBeginStation;
	//m_iEndStation=pGameSet->iEndStation;

	m_bFirstRed = true;
	m_iBeenPlayGame=0;
	m_bGameStation=GS_WAIT_ARGEE;
	//	m_Logic.SetNTCardNum(pGameSet->iBeginStation);
	//	m_Logic.SetNTHuaKind(UG_ERROR_HUA);
	//m_iPlayNTNum[0]=pGameSet->iBeginStation;
	//m_iPlayNTNum[1]=pGameSet->iBeginStation;

	m_iJuTimeMinute = pGameSet->iJuTimeMinute;
	m_iJuTimeSecond = pGameSet->iJuTimeSecond;
	m_iBuTimeMinute = pGameSet->iBuTimeMinute;
	m_iBuTimeSecond = pGameSet->iBuTimeSecond;
	m_iDuMiaoMinute = pGameSet->iDuMiaoMinute;
	m_iDuMiaoSecond = pGameSet->iDuMiaoSecond;
	m_iGuidandeMoney = pGameSet->iGuidandeMoney;		//ָ����
	//������Ϣ
	UserArgeeGame Agree;
	Agree.iJuTimeMinute=pGameSet->iJuTimeMinute;
	Agree.iJuTimeSecond=pGameSet->iJuTimeSecond;
	Agree.iBuTimeMinute=pGameSet->iBuTimeMinute;
	Agree.iBuTimeSecond=pGameSet->iBuTimeSecond;
	Agree.iDuMiaoMinute = pGameSet->iDuMiaoMinute;
	Agree.iDuMiaoSecond = pGameSet->iDuMiaoSecond;
	Agree.iGuidandeMoney=pGameSet->iGuidandeMoney;
	for (int i=0;i<2;i++)
		if(i!=desk)
			SendGameData(i,&Agree,sizeof(Agree),MDM_GM_GAME_NOTIFY,ASS_UG_USER_SET,0);
	SendWatchData(m_bMaxPeople,&Agree,sizeof(Agree),MDM_GM_GAME_NOTIFY,ASS_UG_USER_SET,0);

	return TRUE;
}

/**
 * �û������뿪
 */
bool CServerGameDesk::UserHaveThing(BYTE bDeskStation, char * szMessage)
{
	if (m_bGameStation < GS_SEND_CARD) return true;

	m_iLeaveArgee |= 1<<bDeskStation;
	if (m_iLeaveArgee != 15)
	{
		HaveThingStruct HaveThing;
		HaveThing.pos = bDeskStation;
		::CopyMemory(HaveThing.szMessage, szMessage, 60*sizeof(char));
		for (int i = 0; i < m_bMaxPeople; i++)
		{
			if (i != bDeskStation) 
				SendGameData(i, &HaveThing, sizeof(HaveThing), MDM_GM_GAME_NOTIFY, ASS_HAVE_THING, 0);
		}
	}
	else 
	{
		GameFinish(bDeskStation, GF_SAFE);
	}

	return true;
}

/**
 * ͬ���û��뿪
 */
bool CServerGameDesk::ArgeeUserLeft(BYTE bDeskStation, BOOL bArgee)
{
	if (!bArgee)
	{
		m_bQueryQuit = true;
		LeaveResultStruct Leave;
		Leave.bDeskStation = bDeskStation;
		Leave.bArgeeLeave = bArgee;
		for (int i = 0; i < m_bMaxPeople; i++) 
		{
			if(i != bDeskStation)
				SendGameData(i, &Leave, sizeof(Leave), MDM_GM_GAME_NOTIFY, ASS_LEFT_RESULT, 0);
		}
	}
	else
		GameFinish((bDeskStation+1)%2, GF_SAFE);

	return true;
}


/***********************************************************************************************************/
// �������߼���
/***********************************************************************************************************/

/*
//���캯��
CUpGradeGameLogic::CUpGradeGameLogic(void)
{	
}

void CUpGradeGameLogic::NumQiZi(float *totalBlack, float *totalWhite, int qi[][21])
{
*totalBlack = 0;
*totalWhite = 0;

int black = 0,white = 0;

for(int i = 1; i < WZQ_MAX_I - 1; i++)
for (int j = 1; j < WZQ_MAX_J - 1; j++)
{
if (qi[i][j] > 10)
{	
qi[i][j] -= 10;
}
if (qi[i][j] == WZQ_FLAG_WHITE) white++;
else if (qi[i][j] == WZQ_FLAG_BLACK) black++;
}

for (int i = 1;i < WZQ_MAX_I - 1;i++)
for (int j = 1;j < WZQ_MAX_J - 1;j++)
{
if (qi[i][j] != WZQ_FLAG_NONE) continue;
int ff = GetEmptyFlag(i,j,qi);
if (ff == WZQ_FLAG_WHITE)
{
white++;
qi[i][j] = WQ_FLAG_WHITE_CROSS;
}
else if (ff == WZQ_FLAG_BLACK)
{
black++;
qi[i][j] = WQ_FLAG_BLACK_CROSS;
}
}

*totalBlack = (float) black;
*totalWhite = (float) white;

int remainEmpty = 0;

for (int i = 1;i < WZQ_MAX_I - 1;i++)
for(int j = 1;j < WZQ_MAX_J - 1;j++)
{
if (qi[i][j] == WZQ_FLAG_NONE) remainEmpty++;
}

(*totalBlack) += (float) remainEmpty / 2;
(*totalWhite) += (float) remainEmpty / 2;

return;
}


int CUpGradeGameLogic::GetEmptyFlag(int pi, int pj, int qi[][21])
{
int flag = WZQ_FLAG_NONE;

for (int i = pi + 1;i < WZQ_MAX_I - 1;i++)//bottom
{
int f = qi[i][pj];
if (f == WZQ_FLAG_BLACK)
{
flag = WZQ_FLAG_BLACK;
break;
}
else if (f == WZQ_FLAG_WHITE)
{
flag = WZQ_FLAG_WHITE;
break;
}
}

for (int i = pi - 1;i > 0;i--)//bottom
{
int f = qi[i][pj];
if (f == WZQ_FLAG_BLACK)
{
if (flag == WZQ_FLAG_WHITE) return WZQ_FLAG_NONE;
flag = WZQ_FLAG_BLACK;
break;
}
else if (f == WZQ_FLAG_WHITE)
{
if (flag == WZQ_FLAG_BLACK) return WZQ_FLAG_NONE;
flag = WZQ_FLAG_WHITE;
break;
}
}

for (int j = pj + 1;j < WZQ_MAX_J - 1;j++)//left
{
int f = qi[pi][j];
if (f == WZQ_FLAG_BLACK)
{
if (flag == WZQ_FLAG_WHITE) return WZQ_FLAG_NONE;
flag = WZQ_FLAG_BLACK;
break;
}
else if (f == WZQ_FLAG_WHITE)
{
if (flag == WZQ_FLAG_BLACK) return WZQ_FLAG_NONE;
flag = WZQ_FLAG_WHITE;
break;
}
}

for (int j = pj - 1;j > 0;j--)//right
{
int f = qi[pi][j];
if (f == WZQ_FLAG_BLACK)
{
if (flag == WZQ_FLAG_WHITE) return WZQ_FLAG_NONE;
flag = WZQ_FLAG_BLACK;
break;
}
else if (f == WZQ_FLAG_WHITE)
{
if (flag == WZQ_FLAG_BLACK) return WZQ_FLAG_NONE;
flag = WZQ_FLAG_WHITE;
break;
}
}

return flag;
}
*/

/**
 * ���ܿ۷�
 */
int CServerGameDesk::GetRunPublish()
{
	return m_pDataManage->m_InitData.uRunPublish;
}

/**
 * �Α���A����
 */
int CServerGameDesk::GetRoomBasePoint()
{
	int iBasePoint=m_pDataManage->m_InitData.uBasePoint;//����
	return (iBasePoint>0?iBasePoint:1);
}

/**
 * ���ӱ���
 */
int CServerGameDesk::GetDeskBasePoint()
{
	return 1;//GetTableBasePoint();
}

/**
 * ͳ�Ʊ���
 */
int CServerGameDesk::GetHumanBasePoint()
{
	//��ҳ������бȷֻ���
	//	if(m_pDataManage->m_InitData.uComType == TY_MONEY_GAME)

	__int64 minval=m_pUserInfo[0]->m_UserData.dwPoint;
	for(int i=1;i<PLAY_COUNT;i++)
	{
		minval=min(minval,m_pUserInfo[i]->m_UserData.dwPoint);
	}

	__int64 uBasePoint[22]=
	{
		0,10,30,60,
		100,200,400,640,
		920,1240,2140,4640,
		7390,10390,13640,20640,
		35640,51640,68640,86640,
		108640,138640
	};
	int BasePoint[22]=
	{
		1,2,3,4,
		5,10,12,14,
		16,18,50,55,
		60,65,70,150,
		160,170,180,190,
		200,210
	};
	for (int i=0;i<22;i++)	
		if (minval<uBasePoint[i]) 
			return BasePoint[i];
	return BasePoint[21];
}

/**
 * ͳ��˭ʤ
 */
int CServerGameDesk::CountWinPiont()
{
	//����������Ƿ�ָ����,����������������Ľ��Ҫ�䵱ָ����
	BYTE TempDeskStation = (m_iWinFlag+1)%2;
	__int64 TempUserMoney = 0;

	if (m_pUserInfo[TempDeskStation])
	{

		TempUserMoney = min(m_iGuidandeMoney, m_pUserInfo[TempDeskStation]->m_UserData.i64Money,m_iGuidandeMoney);
	}


	if(m_iWinFlag == -1)	//����
		return 0;
	int win=0;
	if(m_iWinFlag == m_iUpGradePeople)
		return TempUserMoney;

	else
		return -TempUserMoney;
						
	return win;
}

/**
 * ����
 */
int CServerGameDesk::Judge(int nX, int nY, char cValue)
{
	int  nGrade;
	int  i, j, k, l;
	int  nXStart, nXEnd;
	int  nYStart, nYEnd;
	int  nXYStart, nXYEnd;
	int  nYXStart, nYXEnd;
	int  nXStartAdd, nYStartAdd, nXYStartAdd, nYXStartAdd;            
	int  nXEndAdd, nYEndAdd, nXYEndAdd, nYXEndAdd;            
	BOOL bXStartEmpty, bXEndEmpty, bXStartEmpty1, bXEndEmpty1;
	BOOL bYStartEmpty, bYEndEmpty, bYStartEmpty1, bYEndEmpty1;
	BOOL bXYStartEmpty, bXYEndEmpty, bXYStartEmpty1, bXYEndEmpty1;
	BOOL bYXStartEmpty, bYXEndEmpty, bYXStartEmpty1, bYXEndEmpty1;

	nXStart  = nXEnd  = nX;
	nYStart  = nYEnd  = nY;
	nXYStart = nXYEnd = nX;
	nYXStart = nYXEnd = nX;                                           
	nXStartAdd = nYStartAdd = nXYStartAdd = nYXStartAdd = 0;            	
	nXEndAdd = nYEndAdd = nXYEndAdd = nYXEndAdd = 0;            	
	bXStartEmpty = bYStartEmpty = bXYStartEmpty = bYXStartEmpty = FALSE;
	bXEndEmpty = bYEndEmpty = bXYEndEmpty = bYXEndEmpty = FALSE;
	bXStartEmpty1 = bYStartEmpty1 = bXYStartEmpty1 = bYXStartEmpty1 = FALSE;
	bXEndEmpty1 = bYEndEmpty1 = bXYEndEmpty1 = bYXEndEmpty1 = FALSE;

	for (i=nX-1; i>=0; i--)            // <-
	{
		if (m_iBoard[i][nY]==cValue)
			nXStart = i;
		else if (m_iBoard[i][nY]==0) 
		{
			bXStartEmpty = TRUE;
			for (j=i-1; j>=0; j--)            // <-
			{
				if (m_iBoard[j][nY]==cValue)
					nXStartAdd = i-j;
				else if (m_iBoard[j][nY]==0) 
				{
					bXStartEmpty1 = TRUE;
					break;
				}
				else
					break;
			}
			break;
		}                         
		else
			break;
	}
	for (i=nX+1; i<BOARD_LINE_NUMBER; i++)           // ->
	{
		if (m_iBoard[i][nY]==cValue)
			nXEnd = i;
		else if (m_iBoard[i][nY]==0)
		{
			bXEndEmpty = TRUE;     
			for (j=i+1; j<BOARD_LINE_NUMBER; j++)            // ->
			{
				if (m_iBoard[j][nY]==cValue)
					nXEndAdd = j-i;
				else if (m_iBoard[j][nY]==0) 
				{
					bXEndEmpty1 = TRUE;
					break;
				}
				else
					break;
			}
			break;
		}
		else
			break;
	}

	for (i=nY-1; i>=0; i--)            // ^|^
	{
		if (m_iBoard[nX][i]==cValue)
			nYStart = i;
		else if (m_iBoard[nX][i]==0)
		{
			bYStartEmpty = TRUE;   
			for (j=i-1; j>=0; j--)            // <-
			{
				if (m_iBoard[nX][j]==cValue)
					nYStartAdd = i-j;
				else if (m_iBoard[nX][j]==0) 
				{
					bYStartEmpty1 = TRUE;
					break;
				}
				else
					break;
			}
			break;
		}
		else
			break;
	}
	for (i=nY+1; i<BOARD_LINE_NUMBER; i++)           // v|v
	{
		if (m_iBoard[nX][i]==cValue)
			nYEnd = i;
		else if (m_iBoard[nX][i]==0)
		{
			bYEndEmpty = TRUE;     
			for (j=i+1; j<BOARD_LINE_NUMBER; j++)            // ->
			{
				if (m_iBoard[nX][j]==cValue)
					nYEndAdd = j-i;
				else if (m_iBoard[nX][j]==0) 
				{
					bYEndEmpty1 = TRUE;
					break;
				}
				else
					break;
			}
			break;
		}
		else
			break;
	}

	//j = nY;
	for (i=nX-1, j=nY+1; i>=0&&j<BOARD_LINE_NUMBER; i--, j++)            // /'
	{
		//j++;
		if (m_iBoard[i][j]==cValue)
			nXYStart = i;
		else if (m_iBoard[i][j]==0)
		{
			bXYStartEmpty = TRUE; 
			for (k=i-1, l=j+1; k>=0&&l<BOARD_LINE_NUMBER; k--, l++)            // /'
			{
				if (m_iBoard[k][l]==cValue)
					nXYStartAdd = i-k;
				else if (m_iBoard[k][l]==0)
				{
					bXYStartEmpty1 = TRUE; 
					break;
				}
				else
					break;
			}
			break;
		}
		else
			break;
	}   
	//j = nY;
	for (i=nX+1, j=nY-1; i<BOARD_LINE_NUMBER&&j>=0; i++, j--)           // ./
	{      
		//j--;
		if (m_iBoard[i][j]==cValue)
			nXYEnd = i;
		else if (m_iBoard[i][j]==0)
		{
			bXYEndEmpty = TRUE;   
			for (k=i+1, l=j-1; l>=0&&k<BOARD_LINE_NUMBER; l--, k++)            // /'
			{
				if (m_iBoard[k][l]==cValue)
					nXYEndAdd = k-i;
				else if (m_iBoard[k][l]==0)
				{
					bXYEndEmpty1 = TRUE; 
					break;
				}
				else
					break;
			}
			break;
		}
		else
			break;
	}

	//j = nY;
	for (i=nX-1, j=nY-1; i>=0&&j>=0; i--, j--)            // '`
	{
		//j--;
		if (m_iBoard[i][j]==cValue)
			nYXStart = i;
		else if (m_iBoard[i][j]==0)
		{
			bYXStartEmpty = TRUE; 
			for (k=i-1, l=j-1; k>=0&&l>=0; k--, l--)            // /'
			{
				if (m_iBoard[k][l]==cValue)
					nYXStartAdd = i-k;
				else if (m_iBoard[k][l]==0)
				{
					bYXStartEmpty1 = TRUE; 
					break;
				}
				else
					break;
			}
			break;
		}
		else
			break;
	}   
	//j = nY;
	for (i=nX+1, j=nY+1; i<BOARD_LINE_NUMBER&&j<BOARD_LINE_NUMBER; i++, j++)           // `.
	{      
		//j++;
		if (m_iBoard[i][j]==cValue)
			nYXEnd = i;
		else if (m_iBoard[i][j]==0)
		{
			bYXEndEmpty = TRUE;   
			for (k=i+1, l=j+1; l<BOARD_LINE_NUMBER&&k<BOARD_LINE_NUMBER; l++, k++)            // /'
			{
				if (m_iBoard[k][l]==cValue)
					nYXEndAdd = k-i;
				else if (m_iBoard[k][l]==0)
				{
					bYXEndEmpty1 = TRUE; 
					break;
				}
				else
					break;
			}
			break;
		}
		else
			break;
	}

	int nXStep  = nXEnd-nXStart+1;
	int nYStep  = nYEnd-nYStart+1;
	int nXYStep = nXYEnd-nXYStart+1;
	int nYXStep = nYXEnd-nYXStart+1;

	BOOL bX_4 = ((nXStep==4)&&(bXStartEmpty&&bXEndEmpty));
	BOOL bY_4 = ((nYStep==4)&&(bYStartEmpty&&bYEndEmpty));
	BOOL bXY_4 = ((nXYStep==4)&&(bXYStartEmpty&&bXYEndEmpty));
	BOOL bYX_4 = ((nYXStep==4)&&(bYXStartEmpty&&bYXEndEmpty));
	BOOL bX4 = ((nXStep==4)&&(bXStartEmpty||bXEndEmpty));
	BOOL bY4 = ((nYStep==4)&&(bYStartEmpty||bYEndEmpty));
	BOOL bXY4 = ((nXYStep==4)&&(bXYStartEmpty||bXYEndEmpty));
	BOOL bYX4 = ((nYXStep==4)&&(bYXStartEmpty||bYXEndEmpty));

	BOOL bX_3 = ((nXStep==3)&&(bXStartEmpty&&bXEndEmpty));
	BOOL bY_3 = ((nYStep==3)&&(bYStartEmpty&&bYEndEmpty));
	BOOL bXY_3 = ((nXYStep==3)&&(bXYStartEmpty&&bXYEndEmpty));
	BOOL bYX_3 = ((nYXStep==3)&&(bYXStartEmpty&&bYXEndEmpty));

	BOOL bX3 = ((nXStep==3)&&(bXStartEmpty||bXEndEmpty));
	BOOL bY3 = ((nYStep==3)&&(bYStartEmpty||bYEndEmpty));
	BOOL bXY3 = ((nXYStep==3)&&(bXYStartEmpty||bXYEndEmpty));
	BOOL bYX3 = ((nYXStep==3)&&(bYXStartEmpty||bYXEndEmpty));

	BOOL bX_2 = ((nXStep==2)&&(bXStartEmpty&&bXEndEmpty));
	BOOL bY_2 = ((nYStep==2)&&(bYStartEmpty&&bYEndEmpty));
	BOOL bXY_2 = ((nXYStep==2)&&(bXYStartEmpty&&bXYEndEmpty));
	BOOL bYX_2 = ((nYXStep==2)&&(bYXStartEmpty&&bYXEndEmpty));
	BOOL bX2 = ((nXStep==2)&&(bXStartEmpty||bXEndEmpty));
	BOOL bY2 = ((nYStep==2)&&(bYStartEmpty||bYEndEmpty));
	BOOL bXY2 = ((nXYStep==2)&&(bXYStartEmpty||bXYEndEmpty));
	BOOL bYX2 = ((nYXStep==2)&&(bYXStartEmpty||bYXEndEmpty));

	BOOL bX_1 = ((nXStep==1)&&(bXStartEmpty&&bXEndEmpty));
	BOOL bY_1 = ((nYStep==1)&&(bYStartEmpty&&bYEndEmpty));
	BOOL bXY_1 = ((nXYStep==1)&&(bXYStartEmpty&&bXYEndEmpty));
	BOOL bYX_1 = ((nYXStep==1)&&(bYXStartEmpty&&bYXEndEmpty));

	int nXAdd, nYAdd, nXYAdd, nYXAdd;
	nXAdd = nYAdd = nXYAdd = nYXAdd = 0;

	if (nXEndAdd>=nXStartAdd)
	{
		nXAdd = nXEndAdd;
		bXEndEmpty = bXEndEmpty1;
	}
	else                      
	{
		nXAdd = nXStartAdd;
		bXStartEmpty = bXStartEmpty1;
	}

	if (nYEndAdd>=nYStartAdd)
	{
		nYAdd = nYEndAdd;
		bYEndEmpty = bYEndEmpty1;
	}
	else                      
	{
		nYAdd = nYStartAdd;
		bYStartEmpty = bYStartEmpty1;
	}

	if (nXYEndAdd>=nXYStartAdd)
	{
		nXYAdd = nXYEndAdd;
		bXYEndEmpty = bXYEndEmpty1;
	}
	else                      
	{
		nXYAdd = nXYStartAdd;
		bXYStartEmpty = bXYStartEmpty1;
	}

	if (nYXEndAdd>=nYXStartAdd)
	{
		nYXAdd = nYXEndAdd;
		bYXEndEmpty = bYXEndEmpty1;
	}
	else                      
	{
		nYXAdd = nYXStartAdd;
		bYXStartEmpty = bYXStartEmpty1;
	}

	BOOL b1X_4 = ((nXStep+nXAdd>=4)&&(bXStartEmpty&&bXEndEmpty));
	BOOL b1Y_4 = ((nYStep+nYAdd>=4)&&(bYStartEmpty&&bYEndEmpty));
	BOOL b1XY_4 = ((nXYStep+nXYAdd>=4)&&(bXYStartEmpty&&bXYEndEmpty));
	BOOL b1YX_4 = ((nYXStep+nYXAdd>=4)&&(bYXStartEmpty&&bYXEndEmpty));
	BOOL b1X4 = ((nXStep+nXAdd>=4)&&(bXStartEmpty||bXEndEmpty));
	BOOL b1Y4 = ((nYStep+nYAdd>=4)&&(bYStartEmpty||bYEndEmpty));
	BOOL b1XY4 = ((nXYStep+nXYAdd>=4)&&(bXYStartEmpty||bXYEndEmpty));
	BOOL b1YX4 = ((nYXStep+nYXAdd>=4)&&(bYXStartEmpty||bYXEndEmpty));

	BOOL b1X_3 = ((nXStep+nXAdd==3)&&(bXStartEmpty&&bXEndEmpty));
	BOOL b1Y_3 = ((nYStep+nYAdd==3)&&(bYStartEmpty&&bYEndEmpty));
	BOOL b1XY_3 = ((nXYStep+nXYAdd==3)&&(bXYStartEmpty&&bXYEndEmpty));
	BOOL b1YX_3 = ((nYXStep+nYXAdd==3)&&(bYXStartEmpty&&bYXEndEmpty));

	int m_nType = -1;	                           

	////////	
	if (nXStep>=5 || nYStep>=5 || nXYStep>=5 || nYXStep>=5)
	{
		nGrade = 0;
		m_nType = 0;
	}
	////////	
	else if (bX_4 || bY_4 || bXY_4 || bYX_4)
	{
		nGrade = 1;             
		m_nType = 1;
	}
	////////	
	else if ((bX4 && (bY4 || bXY4 || bYX4 || b1Y4 || b1XY4 || b1YX4))||
		(bY4 && (bX4 || bXY4 || bYX4 || b1X4 || b1XY4 || b1YX4))||
		(bXY4 && (bY4 || bX4 || bYX4 || b1Y4 || b1X4 || b1YX4)) ||
		(bYX4 && (bY4 || bXY4 || bX4 || b1Y4 || b1XY4 || b1X4)) ||
		(b1X4 && (bY4 || bXY4 || bYX4 || b1Y4 || b1XY4 || b1YX4))||
		(b1Y4 && (bX4 || bXY4 || bYX4 || b1X4 || b1XY4 || b1YX4))||
		(b1XY4 && (bY4 || bX4 || bYX4 || b1Y4 || b1X4 || bYX4))  ||
		(b1YX4 && (bY4 || bXY4 || bX4 || b1Y4 || b1XY4 || b1X4)))
	{
		nGrade = 2;
		m_nType = 1;
	}		
	/////////
	else if ((bX4 && (bY_3 || bXY_3 || bYX_3 || b1Y_3 || b1XY_3 || b1YX_3))||
		(bY4 && (bX_3 || bXY_3 || bYX_3 || b1X_3 || b1XY_3 || b1YX_3))||
		(bXY4 && (bY_3 || bX_3 || bYX_3 || b1Y_3 || b1X_3 || b1YX_3)) ||
		(bYX4 && (bY_3 || bXY_3 || bX_3 || b1Y_3 || b1XY_3 || b1X_3)) ||
		(b1X4 && (bY_3 || bXY_3 || bYX_3 || b1Y_3 || b1XY_3 || b1YX_3))||
		(b1Y4 && (bX_3 || bXY_3 || bYX_3 || b1X_3 || b1XY_3 || b1YX_3))||
		(b1XY4 && (bY_3 || bX_3 || bYX_3 || b1Y_3 || b1X_3 || b1YX_3)) ||
		(b1YX4 && (bY_3 || bXY_3 || bX_3 || b1Y_3 || b1XY_3 || b1X_3)))
	{
		nGrade = 3;
		m_nType = 1;
	}		
	////////	
	else if ((bX_3 && (bY_3 || bXY_3 || bYX_3 || b1Y_3 || b1XY_3 || b1YX_3))||
		(bY_3 && (bX_3 || bXY_3 || bYX_3 || b1X_3 || b1XY_3 || b1YX_3))||
		(bXY_3 && (bY_3 || bX_3 || bYX_3 || b1Y_3 || b1X_3 || b1YX_3)) ||
		(bYX_3 && (bY_3 || bXY_3 || bX_3 || b1Y_3 || b1XY_3 || b1X_3)) ||
		(b1X_3 && (bY_3 || bXY_3 || bYX_3 || b1Y_3 || b1XY_3 || b1YX_3))||
		(b1Y_3 && (bX_3 || bXY_3 || bYX_3 || b1X_3 || b1XY_3 || b1YX_3))||
		(b1XY_3 && (bY_3 || bX_3 || bYX_3 || b1Y_3 || b1X_3 || b1YX_3)) ||
		(b1YX_3 && (bY_3 || bXY_3 || bX_3 || b1Y_3 || b1XY_3 || b1X_3)))
	{
		nGrade = 4;
		m_nType = 2;
	}		
	////////
	else if ((bXY4 && (bYX_2 || bY_2 || bX_2))||
		(bYX4 && (bXY_2 || bY_2 || bX_2))||
		(bX4 && (bXY_2 || bYX_2 || bY_2))||
		(bY4 && (bXY_2 || bYX_2 || bX_2)))

	{
		nGrade = 5;
		m_nType = 1;
	}		                     
	else if ((bXY4 && (bYX3 || bY3 || bX3))||
		(bYX4 && (bXY3 || bY3 || bX3))||
		(bX4 && (bXY3 || bYX3 || bY3))||
		(bY4 && (bXY3 || bYX3 || bX3)))
	{
		nGrade = 6;
		m_nType = 1;
	}		
	else if ((bXY4 && (bYX_1 || bY_1 || bX_1))||
		(bYX4 && (bXY_1 || bY_1 || bX_1))||
		(bX4 && (bXY_1 || bYX_1 || bY_1))||
		(bY4 && (bXY_1 || bYX_1 || bX_1)))
	{
		nGrade = 7;
		m_nType = 2;
	}		
	else if ((bXY4 && (bYX2 || bY2 || bX2))||
		(bYX4 && (bXY2 || bY2 || bX2))||
		(bX4 && (bXY2 || bYX2 || bY2))||
		(bY4 && (bXY2 || bYX2 || bX2)))

	{
		nGrade = 8;
		m_nType = 1;
	}		
	else if (bXY4 || bYX4 || bX4 || bY4)
	{
		nGrade = 9;
		m_nType = 1;
	}		
	////////
	else if ((bXY_3 && (bYX_2 || bY_2 || bX_2))||
		(bYX_3 && (bXY_2 || bY_2 || bX_2))||
		(bX_3 && (bXY_2 || bYX_2 || bY_2))||
		(bY_3 && (bXY_2 || bYX_2 || bX_2)))
	{
		nGrade = 10;
		m_nType = 2;
	}		
	else if ((bXY_3 && (bYX3 || bY3 || bX3))||
		(bYX_3 && (bXY3 || bY3 || bX3))||
		(bX_3 && (bXY3 || bYX3 || bY3))||
		(bY_3 && (bXY3 || bYX3 || bX3)))
	{
		nGrade = 11;
		m_nType = 2;
	}		
	else if ((bXY_3 && (bYX_1 || bY_1 || bX_1))||
		(bYX_3 && (bXY_1 || bY_1 || bX_1))||
		(bX_3 && (bXY_1 || bYX_1 || bY_1))||
		(bY_3 && (bXY_1 || bYX_1 || bX_1)))
	{
		nGrade = 12;
		m_nType = 2;
	}		
	else if ((bXY_3 && (bYX2 || bY2 || bX2))||
		(bYX_3 && (bXY2 || bY2 || bX2))||
		(bX_3 && (bXY2 || bYX2 || bY2))||
		(bY_3 && (bXY2 || bYX2 || bX2)))
	{
		nGrade = 13;
		m_nType = 2;
	}		
	else if (bXY_3 || bYX_3 || bX_3 || bY_3)
	{
		nGrade = 14;
		m_nType = 2;
	}		           
	////////		
	else if (bXY_2 || bYX_2 || bX_2 || bY_2)
		nGrade = 16;
	////////
	else if (bXY3 || bYX3 || bX3 || bY3)
		nGrade = 17;
	else if (bXY2 || bYX2 || bX2 || bY2)
		nGrade = 18;
	else if (bXY_1 || bYX_1 || bX_1 || bY_1)    
		nGrade = 19; 
	else
		nGrade = 20;

	///////	                
	if (nGrade>15)
		if ((m_iBoard[nX][nY-1]==0 || m_iBoard[nX][nY-1]==cValue) &&
			(m_iBoard[nX+1][nY]==0 || m_iBoard[nX+1][nY]==cValue) &&
			(m_iBoard[nX][nY+1]==0 || m_iBoard[nX][nY+1]==cValue) &&
			(m_iBoard[nX-1][nY]==0 || m_iBoard[nX-1][nY]==cValue) &&
			((nX+2<15 && nY-2>=0 && (m_iBoard[nX+2][nY-2]==0 || m_iBoard[nX+2][nY-2]==cValue) &&
			m_iBoard[nX][nY-2]==cValue && m_iBoard[nX+1][nY-1]==cValue && m_iBoard[nX+2][nY]==cValue) ||
			(nX+2<15 && nY+2<15 && (m_iBoard[nX+2][nY+2]==0 || m_iBoard[nX+2][nY+2]==cValue) &&
			m_iBoard[nX][nY+2]==cValue && m_iBoard[nX+1][nY+1]==cValue && m_iBoard[nX+2][nY]==cValue) ||
			(nX-2>=0 && nY+2<15 && (m_iBoard[nX-2][nY+2]==0 || m_iBoard[nX-2][nY+2]==cValue) &&
			m_iBoard[nX][nY+2]==cValue && m_iBoard[nX-1][nY+1]==cValue && m_iBoard[nX-2][nY]==cValue) || 
			(nX-2>=0 && nY-2>=0 && (m_iBoard[nX-2][nY-2]==0 || m_iBoard[nX-2][nY-2]==cValue) &&
			m_iBoard[nX][nY-2]==cValue && m_iBoard[nX-1][nY-1]==cValue && m_iBoard[nX-2][nY]==cValue)))
			nGrade = 15;
	/////////

	return nGrade;		
}
//---------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
//�޸Ľ�������1(ƽ̨->��Ϸ)
/// @param bAIWinAndLostAutoCtrl �����˿�����Ӯ����
/// @return �Ƿ�ɹ�
bool CServerGameDesk::SetRoomPond(bool	bAIWinAndLostAutoCtrl)
{
	return false;
}

//�޸Ľ�������2(ƽ̨->��Ϸ)
/// @param m_iAIWantWinMoney ��������Ӯ���ƣ�������ӮǮ����1,2,3 4���öϵ�
/// @param m_iAIWinLuckyAt ��������Ӯ���ƣ�������������1,2,3,4ӮǮ�ĸ���
/// @return �Ƿ�ɹ�
bool CServerGameDesk::SetRoomPondEx(__int64	iAIWantWinMoney[], int	iAIWinLuckyAt[])
{
	return false;
}

//�޸Ľ�������3(ƽ̨->��Ϸ)
/// @param iReSetAIHaveWinMoney ��������Ӯ���ƣ����û������Ѿ�ӮǮ����Ŀ
/// @return �Ƿ�ɹ�
bool CServerGameDesk::SetRoomPondEx(__int64	iReSetAIHaveWinMoney)
{
	return false;
}

//�ж�
BOOL CServerGameDesk::Judge()
{
	if(JudgeWiner())		//�ȴ���ʤ��
	{
		return TRUE;
	}

	if (JudgeLoser())		//��������
	{
		return TRUE;
	}		

	return FALSE;
}
//================================================
//�ж�ʤ��
//================================================
BOOL CServerGameDesk::JudgeLoser()
{
	return FALSE;
}
//================================================
//�ж�ʤ��
//================================================
BOOL CServerGameDesk::JudgeWiner()
{
	return FALSE;
}
//GRM����
//���½�������(��Ϸ->ƽ̨)
/// @return ������ӮǮ��
void CServerGameDesk::UpDataRoomPond(__int64 iAIHaveWinMoney)
{

}