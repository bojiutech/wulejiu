#include "StdAfx.h"
#include "ServerManage.h"
#include "../../../../sdk/include/Common/writelog.h"
#include <math.h>

/*---------------------------------------------------------------------------*/
/*
* 打印日志文件
*/
void DebugPrintf(int iRoomID, const char *p, ...)
{
	return;
	CTime time = CTime::GetCurrentTime();
	char szFilename[256];
	sprintf(szFilename, "%d_%d-%d%d%d-log.txt", NAME_ID, iRoomID, time.GetYear(), time.GetMonth(), time.GetDay());
	FILE *fp = fopen(szFilename, "a");
	if (NULL == fp)
	{
		return;
	}
	va_list arg;
	va_start(arg, p);
	vfprintf(fp, p, arg);
	fprintf(fp,"\n");

	fclose(fp);
}
/*---------------------------------------------------------------------------*/
//构造函数
CServerGameDesk::CServerGameDesk(void):CGameDesk(ALL_ARGEE)
{
	m_bGameStation = GS_WAIT_ARGEE;
	InitializeCriticalSection(&cs);
	m_bLineCount = 0;
	m_bClearPreWin	= true;
	m_i64ShangFenMoney = 0;
	m_i64UserMoney	= 0;		//玩家身上的金币数	
	m_iAllCellMoney	= 0;		//游戏总加注
	m_iAllWinMoney  = 0;        //总体赢钱
	m_i64UserSYMoney = 0;
	m_byPlayStly = 1;
	m_bySpecialRestCount = 0;
	m_i64SystemWinMoney = 0;
	
	m_byReJuShu = 0;             //单机彩金局数三局一循环
	m_iJuShu = 0;                //出大奖局数
	m_iAllFruits=0;              //出全水果局数
	m_i64AllBet = 0;             //全部下注
	m_i64AllWin = 0;            //赢的总数
	m_byFirstCherry = 0;
	m_bySecondCherry = 0;
	m_iGetZhongCai = 0;        //总彩金
	m_shareAward = 0;
	memset(m_i64SinglePond,0,sizeof(m_i64SinglePond));
	memset(m_bWinLine,0,sizeof(m_bWinLine));
	memset(m_iCheckPrize,0,sizeof(m_iCheckPrize));
	memset(m_iLineGameCount,0,sizeof(m_iLineGameCount));
	InitializeCriticalSection(&m_csForIPCMessage);


	BYTE DaJiangInit[18] = {0,0,1,4,0,0,1,7,8,0,0,3,0,0,0,0,0,0};	//需求:大奖初始化
	for (size_t i=0; i<180; i++)
	{
		memcpy(&m_iCheckPrize[i],DaJiangInit,sizeof(DaJiangInit));
	}

	for (int i=0; i<180; i++)
	{
		for (int j=0; j<18; j++)
		{
			m_iCheckPrize[i][j] = DaJiangInit[j];
		}
	}
}
/*---------------------------------------------------------------------------*/
//析构函数
CServerGameDesk::~CServerGameDesk(void)
{
	DeleteCriticalSection(&m_csForIPCMessage);
	DeleteCriticalSection(&cs);

}

/*---------------------------------------------------------------------------*/
bool CServerGameDesk::InitDeskGameStation()
{
	//加载配置文件
	LoadIni();
	LoadExtIni(m_pDataManage->m_InitData.uRoomID);

	return true;
}
/*---------------------------------------------------------------------------*/
//加载ini配置文件
BOOL	CServerGameDesk::LoadIni()
{
	TCHAR skin[MAX_NAME_INFO];
	CString s = CINIFile::GetAppPath ();/////本地路径
	CString temp = _T("");
	temp.Format("%s%s_s.ini",s,GET_SKIN_FOLDER(skin));
// 	if (!CINIFile::IsFileExist(temp))
// 	{
// 		return true;
// 	}
	CINIFile f(temp);
	CString key = TEXT("game");

	m_maxCellBet	= f.GetKeyVal(key,"MaxCellMoney", 50);	  //最大单线下注金额
	m_iPercentRoom      = f.GetKeyVal(key,"PercentRoom",50);          //房间彩金累积，以玩家输分百分之几    
	m_iPercentPerson  = f.GetKeyVal(key,"PercentPerson",30);  //个人彩金，以当前玩家输分百分之几
	m_Variety   = f.GetKeyVal(key,"Variety",500);             //个人彩金可调部分
	G_i64Pond	= f.GetKeyVal(key,"ReSetAIHaveWinMoney", 0);	  //房间彩金金额

	m_iRewardLeve1	= f.GetKeyVal(key,"RewardLeve1", 10);		   //开大奖局数控制		
	m_iRewardLeve2	= f.GetKeyVal(key,"RewardLeve2", 20);		     
	m_iRewardLeve3	= f.GetKeyVal(key,"RewardLeve3", 30);	
	m_iRewardLeve4	= f.GetKeyVal(key,"RewardLeve3", 40);	
	m_iAIWinLuckyAtA1	= f.GetKeyVal(key,"AIWinLuckyAtA1", 1);  //开大奖概率
	m_iAIWinLuckyAtA2	= f.GetKeyVal(key,"AIWinLuckyAtA2", 2);	
	m_iAIWinLuckyAtA3	= f.GetKeyVal(key,"AIWinLuckyAtA3", 3);	
	m_iAIWinLuckyAtA4	= f.GetKeyVal(key,"AIWinLuckyAtA4", 4);

	m_iFruitJuShuA1  = f.GetKeyVal(key,"FruitJuShuA1",20);          //开全水果局数控制
	m_iFruitJuShuA2  = f.GetKeyVal(key,"FruitJuShuA2",30);
	m_iFruitJuShuA3  = f.GetKeyVal(key,"FruitJuShuA3",40);
	m_iFruitJuShuA4  = f.GetKeyVal(key,"FruitJuShuA4",50);
	m_iFruitWinLuckyAtA1 = f.GetKeyVal(key,"FruitWinLuckyAtA1",1);
	m_iFruitWinLuckyAtA2 = f.GetKeyVal(key,"FruitWinLuckyAtA2",2);
	m_iFruitWinLuckyAtA3 = f.GetKeyVal(key,"FruitWinLuckyAtA3",3);
	m_iFruitWinLuckyAtA4 = f.GetKeyVal(key,"FruitWinLuckyAtA4",4);

	m_iDoubleProbability = f.GetKeyVal(key,"DoubleProbability",5);//两倍的概率(x/1000)
	m_iThreeProbability = f.GetKeyVal(key,"ThreeProbability",3);//三倍的概率(x/1000)
	m_iFourProbability = f.GetKeyVal(key,"FourProbability",2);//四倍的概率(x/1000)		

	m_iShangFenMoney = f.GetKeyVal(key,"ShangFenMoney",100);      //每次上多少分
	m_iSecondControl = f.GetKeyVal(key,"AISecondControl",0);       //二次奖励控制开关
	if (m_iSecondControl<0)
	{
		m_iSecondControl=0;
	}

	m_iExchangeRateBS = f.GetKeyVal(key,"ExchangeRateBS",1);        //兑换比例，从大分转小分
	m_iExchangeRateSB = f.GetKeyVal(key,"ExchangeRateSB",1);        //兑换比例，从小分转大分
	if (m_iExchangeRateBS <=0 && m_iExchangeRateSB <=0)
	{
		m_iExchangeRateSB=1;
	}

	m_iAIControlSwitch = f.GetKeyVal(key,"AIControlSwitch",1);     //奖池控制开关
	G_iAIControlHaveMoney = f.GetKeyVal(key,"AIControlHaveMoney",0);   //奖池分数
	
	CString lhx;
	lhx.Format("SG97::当前奖池 %d",G_iAIControlHaveMoney);
	OutputDebugString(lhx);
	m_iMinCaijinFen = f.GetKeyVal(key,"MinCaijinFen",0);
	if (m_iMinCaijinFen < 0)
	{
		m_iMinCaijinFen=1;
	}
	m_iMaxCaijinFen = f.GetKeyVal(key,"MaxCaijinFen",0);
	if (m_iMaxCaijinFen < 0)
	{
		m_iMaxCaijinFen=1;
	}
	if (m_iMinCaijinFen > m_iMaxCaijinFen)
	{
		m_iMaxCaijinFen = m_iMinCaijinFen;
	}
	m_iSpeCaijinFen = f.GetKeyVal(key,"SpeCaijinFen",0);

	CString sText;
	for(int i=0;i<9;++i)
	{
		sText.Format("SecondeAward%d", i+1);
		m_iSecondRewardMoney[i] = f.GetKeyVal(key,sText,0);
	}

	
	int iCount	 = 0;
	long lUserID = 0;
	//指定送总彩金玩家名单
	key = TEXT("SpecUser");
	iCount = f.GetKeyVal(key,"SpecUserCount",1);
	for(int i = 1; i <= iCount; i++)
	{
		sText.Format("SpecUserID%d", i);
		lUserID = f.GetKeyVal(key, sText, 1);
		m_lvSpecifyUserID.push_back(lUserID);
	}

	iCount	 = 0;
	lUserID = 0;
	//超级用户名单
	key = TEXT("SuperUser");
	iCount = f.GetKeyVal(key,"SuperUserCount",1);
	for(int i = 1; i <= iCount; i++)
	{
		sText.Format("SuperUserID%d", i);
		lUserID = f.GetKeyVal(key, sText, 1);
		m_lvSuperUserID.push_back(lUserID);
	}

	m_shareAward = f.GetKeyVal(key,"ShareAward",10000);
	return true;
}
/*---------------------------------------------------------------------------*/
//根据房间ID加载配置文件
BOOL CServerGameDesk::LoadExtIni(int iRoomID)
{

	CString s = CINIFile::GetAppPath ();/////本地路径
	TCHAR skin[MAX_NAME_INFO];
	CString temp;
	temp.Format("%s%s_s.ini",s,GET_SKIN_FOLDER(skin));
	CINIFile f(temp);
	CString key = TEXT("game");

	m_maxCellBet	= f.GetKeyVal(key, "MaxCellMoney", 50);		//单元下注数

	for(int i  =0; i < MAX_SEAT_COUNT; i++){
		m_i64SinglePond[i] = 428549;
	}
	
	return TRUE;
}
/*---------------------------------------------------------------------------*/
//清空该位置的数据
void	CServerGameDesk::IniUserData(BYTE byStation)
{
	m_i64ShangFenMoney = 0;
	m_bySpecialRestCount = 0;
	m_iJuShu = 0;
	m_iAllFruits = 0;
}

/*---------------------------------------------------------------------------*/
bool	CServerGameDesk::OnTimer(UINT uTimerID)
{
	if ((uTimerID >= TIME_MAX) || (uTimerID <= TIME_MIN))
	{
		return __super::OnTimer(uTimerID);
	}

	return true;
}
/*---------------------------------------------------------------------------*/

bool CServerGameDesk::HandleFrameMessage(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser)
{
	switch(pNetHead->bAssistantID)
	{
	case ASS_GM_FORCE_QUIT:		//强行退出//安全退出
		{
			return true;
		}
	}
	return __super::HandleFrameMessage( bDeskStation,  pNetHead,  pData,  uSize,  uSocketID,  bWatchUser);
}

//游戏数据包处理函数
bool CServerGameDesk::HandleNotifyMessage(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser)
{
	if(bWatchUser)
	{
		return true;
	}

	if(bDeskStation < 0 || bDeskStation >= PLAY_COUNT)
	{
		return true;
	}

	switch (pNetHead->bAssistantID)
	{
	case C_S_SHANG_FEN:
		{
			OnHandleShangFen(bDeskStation, pData, uSize);
			return true;
		}
	case C_S_SHARE_AWARD:{
			OnHandleShareAward(bDeskStation,pData,uSize);
			return true;
		}

	case C_S_START_ROLL:		//启动游戏滚动
		{
			if (m_bGameStation == GS_PLAY_GAME)
			{
				return true;
			}
			OnHandleStartRoll(bDeskStation, pData, uSize);
			return true;
		}
	case C_S_CHECK_PRIZE:
		{
			OnHandleCheckPrize(bDeskStation, pData, uSize);
			return true;
		}
	case C_S_NEXT_PAGE_PRIZE:
		{
			OnHandleNextPagePrize(bDeskStation, pData, uSize);
			return true;
		}
	case C_S_GAME_OVER:
		{
			OnHandleGameOver(bDeskStation, pData, uSize);
			return true;
		}
	case C_S_SUPER_SET:
		{
			OnHandleSuperSet(bDeskStation, pData, uSize);
			return true;
		}
	default:
		{
			return true;
		}
	}
	return __super::HandleNotifyMessage(bDeskStation,pNetHead,pData,uSize,uSocketID,bWatchUser);
}
//玩家每次上分的金额
__int64 CServerGameDesk::GetUserSFMoney(BYTE byStation)
{
	if (m_i64UserSYMoney >= 10000000)   //玩家身上金币大于等于一千万，每次上分为十万
	{
		return 100000;
	}
	else if (m_i64UserSYMoney >= 1000000)
	{
		return 10000;
	}
	else if (m_i64UserSYMoney >= 100000)
	{
		return 1000;
	}
	else if (m_i64UserSYMoney >= 1000)
	{
		return 100;
	}
	else if (m_i64UserSYMoney >0)
	{
		return m_i64UserSYMoney;
	}
	else
	{
		return 0;
	}
}
//玩家上分金额
void CServerGameDesk::OnHandleShangFen(BYTE byStation,void* pdata,UINT uSize)
{
	if (uSize != sizeof(C_S_ShangFen))
	{
		return ;
	}
	if (m_bGameStation ==GS_WAIT_START || m_bGameStation==GS_PLAY_GAME || m_bGameStation==GS_WAIT_START)
	{
		return;
	}
	
	C_S_ShangFen* pShangFen = (C_S_ShangFen*)pdata;

	if (pShangFen->bIsShangFen != true)
	{
		return ;
	}
	if (m_i64UserSYMoney <=0 || m_i64UserSYMoney - m_iShangFenMoney < 0 )
	{
		return ;
	}
	if (m_iExchangeRateSB > 0)
	{
		m_i64ShangFenMoney = m_i64ShangFenMoney + m_iShangFenMoney*m_iExchangeRateSB;
		m_i64UserSYMoney -= m_iShangFenMoney;
	}
	else if (m_iExchangeRateBS > 0)
	{
		m_i64ShangFenMoney = m_i64ShangFenMoney + m_iShangFenMoney/m_iExchangeRateBS; 
		m_i64UserSYMoney -= m_iShangFenMoney;
	}

	S_C_ShangFenResult UserShangFen;
	UserShangFen.iShangFenMoney = m_i64ShangFenMoney;
	UserShangFen.i64UserMoney = m_i64UserSYMoney;
	for (int i = 0; i < PLAY_COUNT; i ++) 
	{
		SendGameData(i,&UserShangFen, sizeof(UserShangFen), MDM_GM_GAME_NOTIFY, S_C_SHANG_FEN,0);
	}
	return;
}

void CServerGameDesk::OnHandleShareAward(BYTE byStation,void* pdata,UINT uSize){
	if (uSize != sizeof(C_S_ShareAward))
	{
		return ;
	}
	if (m_bGameStation ==GS_WAIT_START || m_bGameStation==GS_PLAY_GAME || m_bGameStation==GS_WAIT_START)
	{
		return;
	}
	
	C_S_ShareAward* pShareAward = (C_S_ShareAward*)pdata;

	m_i64ShangFenMoney = m_i64ShangFenMoney + pShareAward->iShareAward;

	S_C_ShareAwardResult shareAwardResult;
	shareAwardResult.iShangFenMoney = m_i64ShangFenMoney;
	for (int i = 0; i < PLAY_COUNT; i ++) 
	{
		SendGameData(i,&shareAwardResult, sizeof(shareAwardResult), MDM_GM_GAME_NOTIFY, S_C_SHARE_AWARD_RESULT,0);
	}
	return;
}
//生成玩法
void CServerGameDesk::getRandStyle()
{
	int num;
	if (m_byPlayStly <=1 || m_bySpecialRestCount==0)
	{
		srand(clock());
		num = rand() % 1000;
		if (num >= 0 && num < m_iDoubleProbability) m_byPlayStly = 2;
		else if (num >= m_iDoubleProbability && num < m_iThreeProbability+m_iDoubleProbability) m_byPlayStly = 3;
		else if (num >= m_iThreeProbability+m_iDoubleProbability 
			&& num < m_iFourProbability+m_iThreeProbability+m_iDoubleProbability) m_byPlayStly = 4;
		else if (num >= m_iFourProbability+m_iThreeProbability+m_iDoubleProbability)              m_byPlayStly = 1;

		if (m_byPlayStly > 1)
		{
			m_bySpecialRestCount = 4;                //发送的是剩余局数 加上当局是5局

			TCHAR skin[MAX_NAME_INFO];
			CString s = CINIFile::GetAppPath ();/////本地路径
			CString temp = _T("");
			temp.Format("%s%s_s.ini",s,GET_SKIN_FOLDER(skin));
			if (!CINIFile::IsFileExist(temp))
			{
				return ;
			}
			CINIFile f(temp);
			CString key = TEXT("game");
			m_bySpecialRestCount	= f.GetKeyVal(key,"SpecialRestCount", m_bySpecialRestCount);	  
			m_bySpecialCount = m_bySpecialRestCount+1;
			CString lhx;
			lhx.Format("YT97::getRandStyle %d",m_bySpecialRestCount);
			OutputDebugStringA(lhx);
		}
	}
	else
	{
		--m_bySpecialRestCount;
	}
}
//生成牌
void CServerGameDesk::getRandImgType()
{
	
	int num;
	int x = rand() % 9;
	for(int i=0; i<9; i++)
	{
		num = rand() % 147;
		if (num >= 112 && num < 144)        m_ImgType[i] = 8;
		else if (num >= 80 && num < 112)    m_ImgType[i] = 7;
		else if (num >= 58 && num < 80)     m_ImgType[i] = 6;
		else if (num >= 40 && num < 58)     m_ImgType[i] = 5;
		else if (num >= 25 && num < 40)     m_ImgType[i] = 4;
		else if (num >= 15 && num < 25)     m_ImgType[i] = 3;
		else if (num >= 8 && num < 15)      m_ImgType[i] = 2;
		else if (num >= 4 && num < 8)       m_ImgType[i] = 1;
		else if (num >= 0 && num < 4)       m_ImgType[i] = 0;
	}

// 	m_ImgType[0] = 7;
// 	m_ImgType[1] = 8;
// 	m_ImgType[2] = 7;
// 	m_ImgType[3] = 8;
// 	m_ImgType[4] = 8;
// 	m_ImgType[5] = 8;
// 	m_ImgType[6] = 0;
// 	m_ImgType[7] = 7;
// 	m_ImgType[8] = 7;

}

//随机产生大奖
int  CServerGameDesk::GetDaJiangImgTpye()
{
	int num = rand() % 1300;
	int iType=-1;
	if (num >=0 && num <280)         //出桔子
	{
		return 7;
	}
	else if (num >=280 && num <450)  //出木瓜
	{
		return 6;
	}
	else if (num>=450 &&num<590)     //出铃铛
	{
		return 5;
	}
	else if (num>=590 && num <680)   //出西瓜
	{
		return 4;
	}
	else if (num >=680 && num < 770) //出黄BAR
	{
		return 3;
	}
	else if (num >=770 && num <850)  //出樱桃
	{
		return 8;
	}
	else if (num>=850 && num <908)   //出红BAR
	{
		return 2;
	}
	else if (num >=908 && num <962) //出蓝BAR
	{
		return 1;
	}
	else if (num >962 && num <1012) //出数字7
	{
		return 0;
	}
	else                           //任意BAR
	{
		return -1;
	}
}

/*-----------------------------------------------------------------------------------------------*/
//玩家启动开始滚动
void CServerGameDesk::OnHandleStartRoll(BYTE byStation,void * pData, UINT uSize)
{
	if (uSize != sizeof(C_S_StartRoll))
	{
		m_bySpecialRestCount = 0;
		m_byPlayStly = 1;
		return;
	}
	CString lhx;
	//玩家发送信息结构体
	C_S_StartRoll *startRoll = (C_S_StartRoll*)pData;

	if(startRoll->byDeposit <= 0)
	{
		m_bySpecialRestCount = 0;
		m_byPlayStly = 1;
		return ;
	}

	//如果不够分了直接返回
	if(m_i64ShangFenMoney - startRoll->byDeposit * startRoll->byLines < 0 )
	{
		m_bySpecialRestCount = 0;
		m_byPlayStly = 1;
		return ;
	}
	m_bGameStation = GS_WAIT_START;
	m_iCellMoney = startRoll->byDeposit;                      //单线投注额
	if (m_byPlayStly == 1 )
	{
		m_i64ShangFenMoney -= m_iCellMoney * startRoll->byLines;  //上分金额
	}
	CString str;
	OutputDebugStringA("SG97::======================================================");
	str.Format("SG97::开奖前奖池 %d",G_iAIControlHaveMoney);
	OutputDebugStringA(str);
	//判定是否超端玩家
	bool  bIsSuperUser =  IsSuperUser(byStation);
	if(bIsSuperUser && m_bIsSuccesse)
	{
		//如果是超端玩家
		if(bIsSuperUser)
		{
			//生成玩法
			getRandStyle();
			if (m_bIsSuccesse)
			{
				CopyMemory(m_ImgType,m_bySetSuperImg,sizeof(m_ImgType));

				//记录连起来的线
				GetWinLine();

				//获取游戏结果结构体
				ChecKLine(); 

				//系统奖励
				GetSystemReward();

				//    房间彩金 -    总体赢钱    +    下注值    
				if ((G_i64Pond - m_iAllWinMoney + m_iCellMoney*8) <= 0)
				{
					G_i64Pond = 0;
				}
			}
		}
	}
	else//奖池控制
	{
		srand(clock());
		int iRandom=rand()%100;
		//生成玩法
		getRandStyle();
		//循环10000次
		for(int n = 0; n < 10000; n++)
		{
			//产生牌 
			getRandImgType();

			//记录连起来的线
			GetWinLine();

			//获取游戏结果结构体
			ChecKLine();   

			//系统奖励
			GetSystemReward();

			if (iRandom < 50)
			{
				if (m_iAllWinMoney == 0 )
				{
					break;
				}
			}
			else
			{
				if (!m_bAllGame && iRandom < 85 && (m_iAllWinMoney - m_iCellMoney*8) <0)
				{
					break;
				}
				else if (!m_bAllGame && iRandom < 85 && m_iAIControlSwitch && m_iAllWinMoney < G_iAIControlHaveMoney)
				{
					break;
				}
				else if(!m_bAllGame && !m_iAIControlSwitch && iRandom > 85)
				{
					break;
				}
			}
		}

	}
	//查询是否要出现全盘水果
	m_iGetZhongCai=0;
	bool t_iCanGetAllFruit = false;
	t_iCanGetAllFruit = CheckGetAllFruits();
	
	if(t_iCanGetAllFruit)
	{
		int temp[4] = {4,6,7,8};
		int t_iCardType;
		srand(clock());
		for(int i =0; i < 9; i++)
		{
			t_iCardType = rand() % 4;
			m_ImgType[i] = temp[t_iCardType]; 
		}
		//生成玩法
		//getRandStyle();
		m_byPlayStly=1;
		//记录连起来的线  
		GetWinLine();

		//获取游戏结果结构体
		ChecKLine();   

		//系统奖励
		GetSystemReward();

		m_bAllGame = true;		
		m_iAllFruits = 0;
	}
	//获取总彩金
	GetZhongCai(byStation);

	//======================================================================================
	//是否要种大奖
	bool t_iCanGetAward = false;
	t_iCanGetAward = CheckGainAward();
	
	if(t_iCanGetAward)
	{
		OutputDebugStringA("97SG::开大奖了=====================================================================");
		for(int i=0;i<300;++i)
		{
			srand(clock());
			int t_iCardType = GetDaJiangImgTpye();
			if(t_iCardType >= 0)
			{
				for(int i =0; i < 9; i++)
				{
					m_ImgType[i] = t_iCardType; 
				}
			}
			else
			{
				m_iGetZhongCai=0;   //此杂牌不得总彩金
				int temp[3] = {1,2,3};
				int t_iCardType;
				srand(clock());
				for(int i =0; i < 9; i++)
				{
					t_iCardType = rand() % 3;
					m_ImgType[i] = temp[t_iCardType]; 
				}
			}

			//生成玩法
			//getRandStyle();
			m_byPlayStly=1;
			//记录连起来的线
			GetWinLine();
			//获取游戏结果结构体
			ChecKLine(); 
			//系统奖励
			GetSystemReward();
			if (m_iRewardMoney < m_i64SinglePond[m_bDeskIndex])
			{
				break;
			}
		}
	}
	CString testt;
	testt.Format("97SG::AA 水果图片 %d %d %d",m_ImgType[0],m_ImgType[1],m_ImgType[2]);
	OutputDebugStringA(testt);
	testt.Format("97SG::BB 水果图片 %d %d %d",m_ImgType[3],m_ImgType[4],m_ImgType[5]);
	OutputDebugStringA(testt);
	testt.Format("97SG::CC 水果图片 %d %d %d",m_ImgType[6],m_ImgType[7],m_ImgType[8]);
	OutputDebugStringA(testt);

	//本局盈利计入玩家总盈利当中
	int _iAllMoney = m_iAllWinMoney + m_iExtaPay + m_iRewardMoney + m_iGetZhongCai + m_iSecondGetMoney;      //总盈利等于 得分 + 奖励分数 + 彩金 + 总彩金

	testt.Format("97SG:: %d %d %d",m_iCellMoney * 8,_iAllMoney,G_iAIControlHaveMoney);
	OutputDebugStringA(lhx);
	//========================================================================================================
	//如果开此次奖之后,奖池为负数了,那就不能开此奖了重新洗选择开奖
	if(m_iCellMoney * 8 - _iAllMoney + G_iAIControlHaveMoney < 0 && !(bIsSuperUser && m_bIsSuccesse) && m_iAIControlSwitch)
	{
		OutputDebugStringA("97SG::开奖失效了===========");
		t_iCanGetAllFruit = false;
		t_iCanGetAward = false;

		srand(clock());
		int iRandom=rand()%100;
		//生成玩法
		//getRandStyle();
		//循环10000次
		for(int n = 0; n < 10000; n++)
		{
			//产生牌 
			getRandImgType();
			//记录连起来的线
			GetWinLine();
			//获取游戏结果结构体
			ChecKLine();   
			//系统奖励
			GetSystemReward();
			
			//维持奖池不能为负数
			if((m_iAllWinMoney + m_iExtaPay + m_iRewardMoney + m_iGetZhongCai + m_iSecondGetMoney < m_iCellMoney * 8 + G_iAIControlHaveMoney))
			{
				if (iRandom < 50)
				{
					if (m_iAllWinMoney == 0 )
					{
						break;
					}
				}
				else
				{
					if (!m_bAllGame && iRandom < 85 && (m_iGetZhongCai + m_iAllWinMoney - m_iCellMoney*8) <0)
					{
						break;
					}
					else if (!m_bAllGame && iRandom < 85 && m_iAIControlSwitch && (m_iAllWinMoney + m_iGetZhongCai) < G_iAIControlHaveMoney)
					{
						break;
					}
					else if(!m_bAllGame && !m_iAIControlSwitch && iRandom > 85)
					{
						break;
					}
				}
			}

			if((m_iAllWinMoney + m_iExtaPay + m_iRewardMoney + m_iGetZhongCai + m_iSecondGetMoney < m_iCellMoney * 8 + G_iAIControlHaveMoney) || 
				(m_iAllWinMoney + m_iExtaPay + m_iRewardMoney + m_iGetZhongCai + m_iSecondGetMoney == 0))
			{
				break;
			}

			str.Format("yt97------for----%d %d %d", m_iExtaPay, m_iRewardMoney, m_iAllWinMoney + m_iExtaPay + m_iRewardMoney + m_iGetZhongCai + m_iSecondGetMoney);
			OutputDebugString(str);
		}
	}
	lhx.Format("SG97::G_iAIControlHaveMoney = %d",G_iAIControlHaveMoney);
	OutputDebugStringA(lhx);
	GetSinglePond(); //个人彩金累积

	OutputDebugString("lin----------------一轮游戏开始----------------");
	if (m_iAllWinMoney == 0)
	{
		m_iJuShu++;
		m_iAllFruits++;

		CString str;
		str.Format("yt97-			m_iJuShu=%d & m_iAllFruits=%d", m_iJuShu, m_iAllFruits);
		OutputDebugString(str);
	}
	else if(t_iCanGetAward)
	{
		m_iJuShu = 0;

		CString str;
		str.Format("yt97-			m_iJuShu清空");
		OutputDebugString(str);
	}
	if (t_iCanGetAllFruit)
	{
		m_iAllFruits = 0;

		CString str;
		str.Format("yt97-			m_iAllFruits清空");
		OutputDebugString(str);
	}
	m_i64AllBet +=  m_iCellMoney * 8;                //全部下注
	m_i64AllWin +=  m_iAllWinMoney;                  //赢的总数

	CountPrePageData();                              //统计查看大奖上一页数据
	CountNextPageData();                             //统计查看大奖下一页数据

	//本局盈利计入玩家总盈利当中
	int iAllMoney = m_iAllWinMoney + m_iExtaPay + m_iRewardMoney + m_iGetZhongCai + m_iSecondGetMoney;      //总盈利等于 得分 + 奖励分数 + 彩金 + 总彩金


	str.Format("yt97----------%d %d %d", m_iExtaPay, m_iRewardMoney, iAllMoney);
	OutputDebugString(str);


	m_iAllJiangTip = iAllMoney;
	m_i64ShangFenMoney += iAllMoney;
	
	lhx.Format("SG97::当前开奖了 总金币 = %d 额外奖 = %d 彩金 = %d 总彩金 = %d 二次奖 = %d %d",m_iAllWinMoney,m_iExtaPay,m_iRewardMoney,m_iGetZhongCai,m_iSecondGetMoney,G_iAIControlHaveMoney);
	OutputDebugStringA(lhx);
	
	//奖池金额
	G_iAIControlHaveMoney += m_iCellMoney*8 - iAllMoney;
	if(m_iCellMoney*8 - iAllMoney < 0 && G_iAIControlHaveMoney < 0) 
	{
		OutputDebugString("yt97-这是一个bug");
	}

	
	
	//写入配置文件
	TCHAR tskin[MAX_NAME_INFO];
	CString ts = CINIFile::GetAppPath ();/////本地路径
	CString ttemp = _T("");
	ttemp.Format("%s%s_s.ini",ts,GET_SKIN_FOLDER(tskin));
	CINIFile tf(ttemp);
	CString tkey = TEXT("game");

	m_i64SystemWinMoney = tf.GetKeyVal(tkey, "SystemWinMoney", 0);		//系统分数的统计
	//更新系统金额的统计
	m_i64SystemWinMoney += m_iCellMoney*8 - iAllMoney;
	CString tvalue;
	tvalue.Format("%I64d", m_i64SystemWinMoney);
	tf.SetKeyValString(tkey, "SystemWinMoney", tvalue);		//系统分数的统计

	
	lhx.Format("SG97::一局结束时 %I64d %d %d %d %d %d %d %d",G_iAIControlHaveMoney,m_iAllWinMoney,m_iExtaPay,m_iRewardMoney,m_iGetZhongCai,m_iSecondGetMoney,iAllMoney,m_iCellMoney*8);
	OutputDebugStringA(lhx);

	if(m_bAllGame){
		if(m_bAllFruits){
			m_shareAward = 2000;
		}else if(!m_bAnyBar){
			m_shareAward = 50000;
		}
	}else{
		switch(m_ilogoValue){
		case 9:
			m_shareAward = 50000;
			break;
		case 8:
			m_shareAward = 40000;
			break;
		case 7:
			m_shareAward = 30000;
			break;
		case 6:
			m_shareAward = 20000;
			break;
		case 5:
			m_shareAward = 10000;
			break;
		default:
			m_shareAward = 0;
			break;
		}
	}
	
	S_C_TypeScroll TTypeScroll;		
	TTypeScroll.bAllGame = m_bAllGame;                          //是否全盘	
	TTypeScroll.byPlayStly = m_byPlayStly;                      //1:代表常规游戏  2：代表2倍开奖环节  3：代表3倍开奖环节  4：代表4倍开奖环节	
	TTypeScroll.bySpecialRestCount = m_bySpecialRestCount;      //特殊玩法剩余局数 
	TTypeScroll.bySpecialtCount = m_bySpecialCount;				//特殊玩法总局数
	TTypeScroll.byZhongLine = m_bLineCount;                     //中奖线数
	TTypeScroll.iExtaPay = m_iExtaPay;                          //奖励
	TTypeScroll.iGetCaiJin = m_iRewardMoney;                    //中得单机彩金
	TTypeScroll.iZhongCaiJin = m_iGetZhongCai;                  //所得总彩金
	TTypeScroll.iSecondGetMoney = m_iSecondGetMoney;            //二次奖励
	TTypeScroll.iShangFenMoney = m_i64ShangFenMoney;            //筹码
	TTypeScroll.iWinMoney = m_iAllWinMoney;                     //本局得分
	TTypeScroll.iLogoValue = m_ilogoValue;                      //七的个数
	TTypeScroll.iShareAward = m_shareAward;
	TTypeScroll.iSinglePond = m_i64SinglePond[m_bDeskIndex];
	CopyMemory(TTypeScroll.iTypeImgid,m_ImgType,sizeof(m_ImgType));      //产生的牌
	CopyMemory(TTypeScroll.bWinAreaFlag,m_bWinLine,sizeof(m_bWinLine));  //哪条线是相连
	for (int i = 0; i < PLAY_COUNT; i ++) 
	{
		SendGameData(i,&TTypeScroll, sizeof(TTypeScroll), MDM_GM_GAME_NOTIFY, S_C_ROLL_RESULT,0);
	}

	m_i64SinglePond[m_bDeskIndex] = m_i64SinglePond[m_bDeskIndex] - m_iRewardMoney;
	G_i64Pond = G_i64Pond - m_iGetZhongCai;
	if(G_i64Pond < 0) OutputDebugString("yt97----------This is a bug");
	//更新奖池
	S_C_Pond TPond;
	if (m_bAllGame || (m_ilogoValue>=7 && m_ilogoValue<=9))
	{
		TPond.bFlag = true;
		wsprintf(TPond.szNickName,TEXT("%s"),m_pUserInfo[byStation]->m_UserData.nickName);
	}
	else
	{
		TPond.bFlag = false;
		wsprintf(TPond.szNickName,TEXT("%s"),m_pUserInfo[byStation]->m_UserData.nickName);
	}
	
	TPond.byStation = m_bDeskIndex + 1;       //桌子号
	TPond.i64Pond=G_i64Pond;              //奖池金额
	TPond.i64GetPond = m_iAllJiangTip;   

	m_pDataManage->m_TCPSocket.SendDataBatch(&TPond,sizeof(TPond),MDM_GM_GAME_NOTIFY,S_C_UPDATE_POND,0);

	EnterCriticalSection(&cs);
	TCHAR skin[MAX_NAME_INFO];
	CString s = CINIFile::GetAppPath ();/////本地路径
	CString temp = _T("");
	temp.Format("%s%s_s.ini",s,GET_SKIN_FOLDER(skin));
	CINIFile f(temp);
	CString key = TEXT("game");
	CString csPond;
	csPond.Format("%d",G_i64Pond);
	f.SetKeyValString(key,"ReSetAIHaveWinMoney",csPond);
	if (m_iAIControlSwitch)
	{
		csPond.Format("%d",G_iAIControlHaveMoney);
		f.SetKeyValString(key,"AIControlHaveMoney",csPond);
	}
	LeaveCriticalSection(&cs);

	m_bIsSuccesse = false;
	if (m_bySpecialRestCount == 0)
	{
		m_byPlayStly = 1;
	}
	
	//开始启动游戏
	StartGame();
}

//获取胜利直线
void CServerGameDesk::GetWinLine()
 {
	INT a1 = m_ImgType[0];
	INT a2 = m_ImgType[1];
	INT a3 = m_ImgType[2];
	INT b1 = m_ImgType[3];
	INT b2 = m_ImgType[4];
	INT b3 = m_ImgType[5];
	INT c1 = m_ImgType[6];
	INT c2 = m_ImgType[7];
	INT c3 = m_ImgType[8];
	m_bLineCount = 0;
	memset(m_bWinLine,false,sizeof(m_bWinLine));

	if( (a1==a2 && a1==a3) 
		|| ((a1<4 && a1>0 && a2<4 && a2>0 && a3<4 && a3>0))
		|| (a1==8 && a1==a2 && a1!=a3)
		|| (a1==8 && a1!=a2) )
	{
		m_bWinLine[0] = true;
	}
	if( (b1==b2 && b1==b3) 
		|| ((b1<4 && b1>0 && b2<4 && b2>0 && b3<4 && b3>0))
		|| b1==8 )
	{
		m_bWinLine[1] = true;
	}
	if( (c1==c2 && c1==c3) 
		|| ((c1<4 && c1>0 && c2<4 && c2>0 && c3<4 && c3>0))
		|| (c1==8 && c1==c2 && c1!=c3)
		|| (c1==8 && c1!=c2) )
	{
		m_bWinLine[2] = true;	
	}
	if( (b1==a2 && b1==c3) 
		|| ((b1<4 && b1>0 && a2<4 && a2>0 && c3<4 && c3>0))
		|| b1==8)
	{
		m_bWinLine[3] = true;
	}
	if( (c1==a2 && c1==b3) 
		|| ((c1<4 && c1>0 && a2<4 && a2>0 && b3<4 && b3>0))
		|| c1==8)
	{
		m_bWinLine[4] = true;
	}
	if( (b1==a1 && b1==c1) 
		|| ((b1<4 && b1>0 && a1<4 && a1>0 && c1<4 && c1>0))
		|| b1==8)
	{
		m_bWinLine[5] = true;
	}
	if( (b2==a2 && b2==c2) 
		|| ((b2<4 && b2>0 && a2<4 && a2>0 && c2<4 && c2>0))
		|| b2==8)
	{
		m_bWinLine[6] = true;
	}
	if( (b3==a3 && b3==c3) 
		|| ((b3<4 && b3>0 && a3<4 && a3>0 && c3<4 && c3>0))
		|| b3==8)
	{
		m_bWinLine[7] = true;
	}
}

/*-----------------------------------------------------------------------------------------------*/
//查询是否中奖
bool CServerGameDesk::CheckGainAward()
{
	bool t_bWin = false;
	srand(time(NULL));
	int t_iRandData = rand()%100+1;

	CString lhx;
	lhx.Format("97SG::==================================================================");
	OutputDebugStringA(lhx);
	lhx.Format("97SG:: %d %d %d",G_i64Pond < m_iGetZhongCai,(m_i64SinglePond[m_bDeskIndex] < 10000*m_iCellMoney/10),m_byPlayStly > 1);
	OutputDebugStringA(lhx);
	lhx.Format("97SG:: %d %d %I64d %d",G_i64Pond,m_iGetZhongCai,m_i64SinglePond[m_bDeskIndex],10000*m_iCellMoney/10);
	OutputDebugStringA(lhx);
	if (/*(m_iAIControlSwitch  && G_iAIControlHaveMoney < 44800*m_iCellMoney/10+10000*m_iCellMoney/10+m_iGetZhongCai) ||*/ 
		 G_i64Pond < m_iGetZhongCai || 
		(m_i64SinglePond[m_bDeskIndex] < 10000*m_iCellMoney/10) || 
		m_byPlayStly > 1)  
	{
		m_iGetZhongCai=0;
		return t_bWin;
	}
	
	//m_iJuShu:出大奖局数
	//m_iRewardLeve1:游戏所在的区间
	//m_iAIWinLuckyAtA2:设置的概率
	lhx.Format("97SG::A %d %d %d",m_iJuShu,m_iRewardLeve1,m_iRewardLeve2);
	OutputDebugStringA(lhx);
	if (m_iJuShu >= m_iRewardLeve1 && m_iJuShu < m_iRewardLeve2)
	{
		lhx.Format("97SG::A %d %d ",t_iRandData,m_iAIWinLuckyAtA1);
		OutputDebugStringA(lhx);
		if (t_iRandData < m_iAIWinLuckyAtA1)
		{
			t_bWin = true;
		}
	}
	else if (m_iJuShu >= m_iRewardLeve2 && m_iJuShu < m_iRewardLeve3)
	{
		if (t_iRandData < m_iAIWinLuckyAtA2)
			t_bWin = true;
	}
	else if (m_iJuShu >= m_iRewardLeve3 && m_iJuShu < m_iRewardLeve4)
	{
		if (t_iRandData < m_iAIWinLuckyAtA3)
			t_bWin = true;
	}
	else if (m_iJuShu >= m_iRewardLeve4)
	{
		if (t_iRandData < m_iAIWinLuckyAtA4)
			t_bWin = true;
	}
	else
	{
		m_iGetZhongCai=0;
	}

	if(t_bWin)
	{
		CString lhx;
		lhx.Format("97SG::当前水果局数 %d %d %d",m_iJuShu,t_iRandData,m_iAIControlSwitch);
		OutputDebugStringA(lhx);
	}
	return t_bWin;
}


//====================================================================================================================
//查询是否出全水果
bool    CServerGameDesk::CheckGetAllFruits()
{
	bool t_bWin = false;
	srand(time(NULL));
	int t_iRandData = rand()%100+1;
	CString lhx;
	lhx.Format("SG97::当前概率m_iAIControlSwitch = %d m_byPlayStly = %d m_iAllFruits = %d %d %d %d %d t_iRandData = %d",m_iAIControlSwitch,m_byPlayStly,m_iAllFruits,m_iFruitWinLuckyAtA1,m_iFruitWinLuckyAtA2,m_iFruitWinLuckyAtA3,m_iFruitWinLuckyAtA4,t_iRandData);
	OutputDebugStringA(lhx);
	lhx.Format("SG97::G_iAIControlHaveMoney = %d m_iFruitJuShuA1 = %d m_iFruitJuShuA2 = %d m_iFruitJuShuA3 = %d m_iFruitJuShuA4 = %d",G_iAIControlHaveMoney,m_iFruitJuShuA1,m_iFruitJuShuA2,m_iFruitJuShuA3,m_iFruitJuShuA4);
	OutputDebugStringA(lhx);
	if ((m_iAIControlSwitch  && G_iAIControlHaveMoney < 3080) || m_byPlayStly > 1)   //一个全水果最大是3080
	{
		return t_bWin;
	}
	if (m_iAllFruits >= m_iFruitJuShuA1 && m_iAllFruits < m_iFruitJuShuA2)
	{
		if (t_iRandData < m_iFruitWinLuckyAtA1)
			t_bWin = true;
	}
	else if (m_iAllFruits >= m_iFruitJuShuA2 && m_iAllFruits < m_iFruitJuShuA3)
	{
		if (t_iRandData < m_iFruitWinLuckyAtA2)
			t_bWin = true;
	}
	else if (m_iAllFruits >= m_iFruitJuShuA3 && m_iAllFruits < m_iFruitJuShuA4)
	{
		if (t_iRandData < m_iFruitWinLuckyAtA3)
			t_bWin = true;
	}
	else if (m_iAllFruits >= m_iFruitJuShuA4)
	{
		if (t_iRandData < m_iFruitWinLuckyAtA4)
			t_bWin = true;
	}
	return t_bWin;
}

//单机彩金累积
void    CServerGameDesk::GetSinglePond()
{
	m_byReJuShu++;
	m_byReJuShu = m_byReJuShu%3+1;

	if (m_byReJuShu == 1)
	{
		m_i64SinglePond[m_bDeskIndex] += 3*m_iCellMoney/10;
		G_i64Pond       += 3*m_iCellMoney/10;
	}
	else if (m_byReJuShu == 2)
	{
		m_i64SinglePond[m_bDeskIndex] += 3*m_iCellMoney/10;
		G_i64Pond       += 3*m_iCellMoney/10;
	}
	else if (m_byReJuShu == 3)
	{
		m_i64SinglePond[m_bDeskIndex] += 4*m_iCellMoney/10;
		G_i64Pond       += 4*m_iCellMoney/10;
	}

}

//系统奖励
void CServerGameDesk::GetSystemReward()
{
	//压80分的情况下, 中奖得分有500 分时,  送500 分,  中1000分时 送1000分,1900 分, 就送 1500分
	m_iExtaPay = m_iAllWinMoney / (500*m_iCellMoney/10) * (500*m_iCellMoney/10);
	
	//m_iSecondGetMoney = m_iSecondRewardMoney[m_ImgType[0]*
}

/*-----------------------------------------------------------------------------------------------*/
//查询排列规则是否中奖
void CServerGameDesk::ChecKLine()
{
	m_bLineCount=0;
	m_iAllWinMoney = 0;
	m_iRewardMoney = 0;
	m_ilogoValue = 0;
	m_byAnyBar=0;
	m_byFirstCherry=0;
	m_bySecondCherry=0;
	m_iSecondGetMoney=0;
	m_bAllGame = false;
	m_bAnyBar=false;
	m_bAllFruits=false;
	memset(m_byThreeLine,0,sizeof(m_byThreeLine));
	int reward = 0;//本局分数置零

	INT a1 = m_ImgType[0];
	INT a2 = m_ImgType[1];
	INT a3 = m_ImgType[2];
	INT b1 = m_ImgType[3];
	INT b2 = m_ImgType[4];
	INT b3 = m_ImgType[5];
	INT c1 = m_ImgType[6];
	INT c2 = m_ImgType[7];
	INT c3 = m_ImgType[8];

	/**********************************LOGO特殊奖励，可以和9连或者3连叠加***********************************/

	//获取特殊奖励logo个数
	int logoValue = getLogoValue(m_ImgType);
	m_ilogoValue = logoValue;
	if (logoValue >= 2)
	{
		//特殊奖励分数设置，2个以上才有奖励
		int score[] = {1,1, 2, 5, 20, 40, 60, 80, 100, 200};
		reward = m_iCellMoney * 8 * score[logoValue]*m_byPlayStly;
		if (9 == logoValue)
		{
			m_bAllGame = true;
		}
	}

	/********************************全盘游戏奖励,不和特殊奖励之外的重复******************************************/
	if (isAllGame(m_ImgType))
	{
		//全盘分数设置
		int score[9] = {200,100,90,60,60,40,40,40,80};
		int btshu[9] = {80,70,50,30,20,18,14,10,10};
		//全盘彩金奖励
		int iCaiJin[9] = {10000,10000,10000,10000,10000,5000,5000,5000,10000};
		m_bAllGame = true;
		m_iAllWinMoney = m_iCellMoney * 8 * (btshu[m_ImgType[0]] + score[m_ImgType[0]])*m_byPlayStly; 
		m_iRewardMoney = iCaiJin[m_ImgType[0]]*m_iCellMoney/10;			
		m_iSecondGetMoney = m_iSecondRewardMoney[m_ImgType[0]] * m_iSecondControl;
		return;
	}

	/****************************全盘任意BAR*****************************/
	else if ((a1<4 && a1>0 && a2<4 && a2>0 && a3<4 && a3>0) && 
			 (b1<4 && b1>0 && b2<4 && b2>0 && b3<4 && b3>0) &&
			 (c1<4 && c1>0 && c2<4 && c2>0 && c3<4 && c3>0) )
	{
		m_bAllGame = true;
		m_bAnyBar = true;
		m_iAllWinMoney = m_iCellMoney * 8 * (40 + 10) * m_byPlayStly;
		return;
	}

	/****************************全盘任意水果*****************************/
	else if (((a1<9 && a1>5 || a1==4) && (a2<9 && a2>5 || a2==4) && (a3<9 && a3>5 || a3==4)) && 
		((b1<9 && b1>5 ||b1==4) && (b2<9 && b2>5 || b2==4) && (b3<9 && b3>5 || b3==4)) &&
		((c1<9 && c1>5 ||c1==4) && (c2<9 && c2>5 
		|| c2==4) && (c3<9 && c3>5 || c3==4)))
	{
		m_bAllGame = true;
		m_bAllFruits=true;
		m_iAllWinMoney = 1200 * m_iCellMoney / 10 * m_byPlayStly;
				
	}
	/***********************************************三连**************************************************/

	reward = reward + getLineReward(a1, a2, a3);  //A线
	reward = reward + getLineReward(b1, b2, b3);  //B线
	reward = reward + getLineReward(c1, c2, c3);  //C线
	reward = reward + getLineReward(b1, a2, c3);  //D线
	reward = reward + getLineReward(c1, a2, b3);  //E线
	reward = reward + getLineReward(b1, a1, c1);  //F线
	reward = reward + getLineReward(b2, a2, c2);  //G线
	reward = reward + getLineReward(b3, a3, c3);  //H线

	m_iAllWinMoney = m_iAllWinMoney + reward * m_byPlayStly;
	return;	
}

//统计查看大奖上一页数据
void  CServerGameDesk::CountPrePageData()
{
	if (m_bAllGame)
	{
		if (m_bAllFruits)           //全水果
		{
			m_iCheckPrize[m_bDeskIndex][17]++;
		}
		else if (m_bAnyBar)         //全盘任意bar
		{
			m_iCheckPrize[m_bDeskIndex][8]++;
		}
		else if (m_ImgType[0] == 1)       //蓝BAR
		{
			bool isSame = true;
			for(int i=0; i<9; i++)
			{
				if(m_ImgType[i] != m_ImgType[0]) isSame = false;
			}
			if(isSame) m_iCheckPrize[m_bDeskIndex][0]++;
		}
		else if (m_ImgType[0] == 2)  //红BAR
		{
			bool isSame = true;
			for(int i=0; i<9; i++)
			{
				if(m_ImgType[i] != m_ImgType[0]) isSame = false;
			}
			if(isSame) m_iCheckPrize[m_bDeskIndex][1]++;
		}
		else if (m_ImgType[0] == 8)  //樱桃
		{
			m_iCheckPrize[m_bDeskIndex][2]++;
		}
		else if (m_ImgType[0] == 3)  //黄BAR
		{
			bool isSame = true;
			for(int i=0; i<9; i++)
			{
				if(m_ImgType[i] != m_ImgType[0]) isSame = false;
			}
			if(isSame) m_iCheckPrize[m_bDeskIndex][3]++;
		}
		else if (m_ImgType[0] == 4)  //西瓜
		{
			m_iCheckPrize[m_bDeskIndex][4]++;
		}
		else if (m_ImgType[0] == 5)  //铃铛
		{
			m_iCheckPrize[m_bDeskIndex][5]++;
		}
		else if (m_ImgType[0] == 6)  //木瓜
		{
			m_iCheckPrize[m_bDeskIndex][6]++;
		}
		else if (m_ImgType[0] == 7)  //桔子
		{
			m_iCheckPrize[m_bDeskIndex][7]++;
		}
		else if (m_ImgType[0] == 0)  //7
		{
			m_iCheckPrize[m_bDeskIndex][9]++;
		}
	}
	else
	{
		if (m_ilogoValue >=2)
		{
			int item = 0;

			item = 18 - m_ilogoValue;
			m_iCheckPrize[m_bDeskIndex][item]++;

		}
	}

}

//统计查看大奖下一页数据
void    CServerGameDesk::CountNextPageData()
{
	for(int i=0;i<7;++i)   //前7个数据跟图片对应，后面两个不对应，分开处理
	{
		if (m_byThreeLine[i] > 0)
		{
			m_iLineGameCount[m_bDeskIndex][i] ++;
		}
	}
	if (m_byAnyBar>0)
	{
		m_iLineGameCount[m_bDeskIndex][7] ++;
	}
	if (m_byThreeLine[7] > 0)
	{
		m_iLineGameCount[m_bDeskIndex][8] ++;
	}
	if (m_byThreeLine[8] > 0)
	{
		m_iLineGameCount[m_bDeskIndex][9] ++;
	}
	if (m_bySecondCherry > 0)
	{
		m_iLineGameCount[m_bDeskIndex][10] ++;
	}
	if (m_byFirstCherry > 0)
	{
		m_iLineGameCount[m_bDeskIndex][11] ++;
	}
}

//获取三连奖励
INT CServerGameDesk::getLineReward(INT a, INT b, INT c)
{
	if (a == b && b == c)
	{
		//三连奖励分数设置
		int score[] = {80, 70, 50,30, 20, 18, 14, 10, 10};
		//if (a == 3) type.iThreeSpades = true;   //3个黑桃
		m_bLineCount++;
		m_byThreeLine[a]++;
		return m_iCellMoney * score[a];
	}
	//判断是否为任意BAR
	else if ((a<4 && a>0 && b<4 && b>0 && c<4 && c>0))
	{
		m_bLineCount++;
		m_byAnyBar++;
		return m_iCellMoney * 10;
	}

	//判断是否两个樱桃加一个任意
	else if (a == 8 && (a == b && a != c))
	{
		m_bLineCount++;
		m_bySecondCherry++;
		return m_iCellMoney * 5;
	}
	//判断是否一个樱桃加两个任意
	else if (a == 8 && a != b)
	{
		m_bLineCount++;
		m_byFirstCherry++;
		return m_iCellMoney * 2;
	}
	return 0;
}


//获取特殊奖励LOGO的个数
INT CServerGameDesk::getLogoValue(INT imageValue[])
{
	INT logo = 0;
	for (size_t i = 0; i < 9; i++)
	{
		INT num = imageValue[i];
		if (num == 0)
		{
			logo++;
		}
	}
	return logo;
}

//判断是否全盘游戏
bool CServerGameDesk::isAllGame(INT imageValue[])
{

	int game=1;
	for(int i=1;i<9;++i)
	{
		if(imageValue[0] == imageValue[i])
		{
			++game;
		}
	}
	if (9 == game)
	{
		return true;
	}
	 
	return false;
}

/*-----------------------------------------------------------------------------------------------*/
//获取游戏状态信息
bool	CServerGameDesk::OnGetGameStation(BYTE bDeskStation, UINT uSocketID, bool bWatchUser)
{
	if(bWatchUser)
	{
		return FALSE;
	}

	//超端验证
	if (IsSuperUser(bDeskStation))
	{
		S_C_TagSuperUser TSuperUser;
		TSuperUser.byStation = bDeskStation;
		TSuperUser.bIsSuper	 = true;
		SendGameData(bDeskStation, &TSuperUser,sizeof(TSuperUser),MDM_GM_GAME_NOTIFY, S_C_IS_SUPER_USER,0);
	}
	
	
	//启动游戏
	switch (m_bGameStation)
	{
	case GS_WAIT_SETGAME:		//游戏没有开始状态
	case GS_WAIT_ARGEE:			//等待玩家开始状态
		{
			S_C_GameStation GameStation;
			::memset(&GameStation, 0, sizeof(GameStation));
			//游戏版本核对

			GameStation.byGameStation	= m_bGameStation;			//游戏状态
			GameStation.iCellBet		= m_maxCellBet;				//最大单线投注额
			GameStation.i64Pond = G_i64Pond;                        //房间彩金
			GameStation.i64SinglePond = m_i64SinglePond[m_bDeskIndex];      //单机彩金
			GameStation.iExchangeRateBS =  m_iExchangeRateBS;				//兑换比例，从大分转小分
			GameStation.iExchangeRateSB =  m_iExchangeRateSB;				//兑换比例，从小分转大分
			GameStation.bDeskIndex = m_bDeskIndex + 1;
			wsprintf(GameStation.szGameRoomName,TEXT("%s"),m_pDataManage->m_InitData.szGameRoomName);
			if (NULL != m_pUserInfo[bDeskStation])
			{
				//记录玩家进入时的金币数量
				m_i64UserMoney = m_pUserInfo[bDeskStation]->m_UserData.i64Money;
				m_i64UserSYMoney = m_i64UserMoney;        //保存玩家金币
				GameStation.i64UserMoney = m_i64UserSYMoney;
			}
			
			//给自己发送数据
			SendGameStation(bDeskStation, uSocketID, bWatchUser, &GameStation, sizeof(GameStation));
			S_C_GameBegin TGameBegin;
			TGameBegin.bStart	= true;
			TGameBegin.byGameStation = m_bGameStation;
			//给其他玩家发送玩家开始消息
			for(int i=0; i<PLAY_COUNT; i++)
			{
				if(NULL != m_pUserInfo[i])
				{
					SendGameData(i,&TGameBegin,sizeof(TGameBegin),MDM_GM_GAME_NOTIFY,S_C_GAME_BEGIN,0);
				}
			}
			return TRUE;
		}
	}
	return false;
}
/*-----------------------------------------------------------------------------------------------*/
//开始启动游戏
void	CServerGameDesk::StartGame()
{
	GameBegin(ALL_ARGEE);
}
/*-----------------------------------------------------------------------------------------------*/
//游戏开始
bool CServerGameDesk::GameBegin(BYTE bBeginFlag)
{
	for(int i=0; i<PLAY_COUNT; i++)
	{
		if(NULL != m_pUserInfo[i])
		{
			//所有玩家置为同意状态 
			m_pUserInfo[i]->m_UserData.bUserState = USER_ARGEE;
		}
	}

	if (__super::GameBegin(bBeginFlag)==false) 
	{
		return false;
	}
	
	//重新加载配置文件里面的
	LoadIni();
	m_bGameStation = GS_PLAY_GAME;

	return TRUE;
}
/*-----------------------------------------------------------------------------------------------*/
//重置游戏状态
bool CServerGameDesk::ReSetGameState(BYTE bLastStation)
{
	return true;
}



/*-----------------------------------------------------------------------*/
//游戏结束
bool CServerGameDesk::GameFinish(BYTE bDeskStation, BYTE bCloseFlag)
{
	KillTimer(TIME_MY_TIMER);
	switch (bCloseFlag)
	{
	case GF_NORMAL:				//游戏正常结束
	case GF_SALE:				//游戏安全结束
	case GFF_FORCE_FINISH:		//用户断线离开
		{	
			m_bIsPlaying = false;
			m_bGameStation	=	GS_WAIT_ARGEE;
			ReSetGameState(bCloseFlag);
			__super::GameFinish(bDeskStation,bCloseFlag);

			return true;
		}
	}

	m_bIsPlaying = false;
	//重置数据
	ReSetGameState(bCloseFlag);
	__super::GameFinish(bDeskStation,bCloseFlag);

	return true;
}
/*------------------------------------------------------------------------------*/
//判断是否正在游戏
bool CServerGameDesk::IsPlayGame(BYTE bDeskStation)
{
	if(m_bIsPlaying)
	{
		return false;
	}
	else
	{
		return false;
	}
	return false;
}
/*------------------------------------------------------------------------------*/
///判断此游戏桌是否开始游戏
BOOL CServerGameDesk::IsPlayingByGameStation()
{
	return FALSE;
}
/*------------------------------------------------------------------------------*/
//用户离开游戏桌
BYTE CServerGameDesk::UserLeftDesk(BYTE bDeskStation, CGameUserInfo * pUserInfo)
{
	m_bySpecialRestCount=0;
	m_byPlayStly=1;
	if(m_pUserInfo[bDeskStation])
	{
		__int64 iTmpMoney=0;
		//计算进来的时候和现在金币差额 
		if (m_iExchangeRateSB > 0)
		{
			iTmpMoney = m_i64UserSYMoney + m_i64ShangFenMoney/m_iExchangeRateSB - m_i64UserMoney;
		}
		else if(m_iExchangeRateBS >0)
		{
			iTmpMoney = m_i64UserSYMoney + m_i64ShangFenMoney*m_iExchangeRateBS - m_i64UserMoney;
		}
		
		//写入数据库				
		bool temp_cut[PLAY_COUNT];
		memset(temp_cut,0,sizeof(temp_cut));

		__int64	iTurePoint[PLAY_COUNT];
		memset(iTurePoint,0,sizeof(iTurePoint));
		iTurePoint[bDeskStation] = iTmpMoney;
		
		ChangeUserPointint64(iTurePoint, temp_cut);

		//记录玩家金币变化
		__int64		iChangeMoney[PLAY_COUNT];				//玩家金币
		memset(iChangeMoney, 0 , sizeof(iChangeMoney));
		__super::RecoderGameInfo(iChangeMoney);
	}

	//清空该位置的数据
	IniUserData(bDeskStation);
	
	__super::UserLeftDesk(bDeskStation,pUserInfo);

	//结束游戏
	GameFinish(bDeskStation,GF_NORMAL);
	
	return true;
}
/*------------------------------------------------------------------------------*/
//用户断线
bool CServerGameDesk::UserNetCut(BYTE bDeskStation, CGameUserInfo * pUserInfo)
{
	//断线也算作离开
	UserLeftDesk(bDeskStation,pUserInfo);
	return true;
}
/*------------------------------------------------------------------------------*/
///用户坐到游戏桌
BYTE	CServerGameDesk::UserSitDesk(MSG_GR_S_UserSit * pUserSit, CGameUserInfo * pUserInfo)
{	
	return __super::UserSitDesk(pUserSit,pUserInfo);
}

/*-----------------------------------------------------------------------------------------------*/

//玩家点击查看大奖
void CServerGameDesk::OnHandleCheckPrize(BYTE byStation,void * pData, UINT uSize)
{
	S_C_Check_Prize TCheckPrize;
// 	TCheckPrize.i64AllBet = m_i64AllBet;                  //全部下注;
// 	TCheckPrize.i64AllWin = m_i64AllWin;                  //赢的总数
	::CopyMemory(&TCheckPrize.iAllGameCount,&m_iCheckPrize[m_bDeskIndex],sizeof(TCheckPrize.iAllGameCount));

	CString zlogS,temp;
	zlogS.Format("zlogS::");
	for (int i=0; i<PLAY_COUNT; i++)
	{
		temp.Format("%d,",TCheckPrize.iAllGameCount[i]);
		zlogS.Append(temp);
	}
	OutputDebugString(zlogS);

	//给其他玩家发送玩家开始消息
	for(int i=0; i<PLAY_COUNT; i++)
	{
		if(NULL != m_pUserInfo[i])
		{
			SendGameData(i,&TCheckPrize,sizeof(TCheckPrize),MDM_GM_GAME_NOTIFY,S_C_CHECK_PRIZE_RESULT,0);
		}
	}
}

//玩家点击查看大奖下一页
void CServerGameDesk::OnHandleNextPagePrize(BYTE byStation,void * pData, UINT uSize)
{
	if (uSize != sizeof(C_S_Next_Prize))
	{
		return ;
	}

	S_C_Next_Prize TNextPagePrize;   
	::CopyMemory(&TNextPagePrize.iLineGameCount,m_iLineGameCount[m_bDeskIndex],sizeof(TNextPagePrize.iLineGameCount));

	for(int i=0; i<PLAY_COUNT; i++)
	{
		if(NULL != m_pUserInfo[i])
		{
			SendGameData(i,&TNextPagePrize,sizeof(TNextPagePrize),MDM_GM_GAME_NOTIFY,S_C_NEXT_PAGE_RESULT,0);
		}
	}
}

void CServerGameDesk::OnHandleGameOver(BYTE byStation,void * pData, UINT uSize)
{
	if (sizeof(C_S_GameEnd) != uSize)
	{
		return ;
	}
	m_bGameStation = GS_WAIT_ARGEE;
	m_bLineCount = 0;
	S_C_GameEnd TGameOver;
	TGameOver.bGameOver =  true;

	for(int i=0; i<PLAY_COUNT; i++)
	{
		if(NULL != m_pUserInfo[i])
		{
			SendGameData(i,&TGameOver,sizeof(TGameOver),MDM_GM_GAME_NOTIFY,S_C_GAME_OVER,0);
		}
	}

	return ;
}
//接受客户端的超端设置
void    CServerGameDesk::OnHandleSuperSet(BYTE byStation,void * pData, UINT uSize)
{
	if (sizeof(C_S_TagSuperSet) != uSize)
	{
		return ;
	}
	C_S_TagSuperSet* pTSuperData = (C_S_TagSuperSet*)pData;
	m_bIsSuccesse = pTSuperData->bSuccesse;
	CopyMemory(m_bySetSuperImg,pTSuperData->bySetSuperImg,sizeof(m_bySetSuperImg));
}

//是否超级用户
bool	CServerGameDesk::IsSuperUser(BYTE byStation)
{
	if(byStation < 0 || byStation >= PLAY_COUNT)
	{
		return false;
	}

	int count = m_lvSuperUserID.size();
	for(int i=0; i<count; i++)
	{
		if(m_pUserInfo[byStation])
		{
			if(m_pUserInfo[byStation]->m_UserData.dwUserID == m_lvSuperUserID.at(i))
			{
				return true;
			}
		}
	}
	return false;
}

//是否是指定送彩金玩家
bool    CServerGameDesk::IsSpecifyUser(BYTE byStation)
{
	if(byStation < 0 || byStation >= PLAY_COUNT)
	{
		return false;
	}

	int count = m_lvSpecifyUserID.size();
	for(int i=0; i<count; i++)
	{
		if(m_pUserInfo[byStation])
		{
			if(m_pUserInfo[byStation]->m_UserData.dwUserID == m_lvSpecifyUserID.at(i))
			{
				return true;
			}
		}
	}
	return false;
}

//获取总彩金
void    CServerGameDesk::GetZhongCai(BYTE byStation)
{
	if (IsSpecifyUser(byStation))
	{
		m_iGetZhongCai = m_iSpeCaijinFen;
	}
	else
	{
		srand((unsigned)time(NULL));
		int iRandom= rand()%(m_iMaxCaijinFen-m_iMinCaijinFen+1) + m_iMinCaijinFen ;
		iRandom = iRandom - iRandom % 10;
		m_iGetZhongCai = iRandom;
	}
}

/*------------------------------------------------------------------------------*/

bool CServerGameDesk::SetRoomPond(bool	bAIWinAndLostAutoCtrl)
{
	return false;
}

bool CServerGameDesk::SetRoomPondEx(__int64	iAIWantWinMoney[], int	iAIWinLuckyAt[])
{
	return false;
}

bool CServerGameDesk::SetRoomPondEx(__int64	iReSetAIHaveWinMoney)
{
	return false;
}

BOOL CServerGameDesk::Judge()
{
	return false;
}

BOOL CServerGameDesk::JudgeWiner()
{
	return false;
}

BOOL CServerGameDesk::JudgeLoser()
{
	return false;
}

void CServerGameDesk::saveDeskData(int iDeskId, CString key, CString& value){
	EnterCriticalSection(&cs);
	TCHAR skin[MAX_NAME_INFO];
	CString s = CINIFile::GetAppPath ();/////本地路径

	CString temp = _T("");
	temp.Format("%s%s_s.ini",s,GET_SKIN_FOLDER(skin));
	CINIFile f(temp);
	CString segment = _T("game");
//	segment.Format("desk_%d",iDeskId);
	f.SetKeyValString(segment,key,value);
	LeaveCriticalSection(&cs);
}

int CServerGameDesk::readDeskData(int iDeskId,CString key,int defaultValue){
	TCHAR skin[MAX_NAME_INFO];
	CString s = CINIFile::GetAppPath ();/////本地路径

	CString temp = _T("");
	temp.Format("%s%s_desks.ini",s,GET_SKIN_FOLDER(skin));
	CINIFile f(temp);
	CString segment = _T("");
	segment.Format("desk_%d",iDeskId);
	return f.GetKeyVal(segment,key,defaultValue);
}