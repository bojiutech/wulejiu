#include "Cherry97GameTableLogic.h"
#include "Cherry97GameTableUICallback.h"
#include "Cherry97GameAudio.h"
#include "HNLobbyExport.h"
#include "HNNetExport.h"

static const char  GS_PLAY      =     10;
using namespace HN;

namespace Cherry97
{
	GameTableLogic::GameTableLogic(GameTableUICallback* uiCallback, char deskNo, bool bAutoCreate): 
		_uiCallback(uiCallback), 
		HNGameLogicBase(deskNo, -1, bAutoCreate, uiCallback),
		m_iWiningTime(0),
		_gameState(GS_PLAY)
	{
		initParams();
	}

	void GameTableLogic::initParams()
	{
		
	}

	GameTableLogic::~GameTableLogic()
	{

	}

	void GameTableLogic::dealGameMessage(NetMessageHead* messageHead, void* object, int objectSize)
	{
		if(MDM_GM_GAME_NOTIFY != messageHead->bMainID)
		{
			HNLOG("onGameMessage MainID is error.");
			return;
		}
		CCLOG("==================messageHead->bAssistantID  =  %d",messageHead->bAssistantID);
		switch (messageHead->bAssistantID)
		{
		case S_C_GAME_BEGIN:                         //游戏开始消息
			{
				dealGameStart(object, objectSize);
				break;
			}
		case S_C_SHANG_FEN:                          //上分结果消息
			{
				dealOnResp(object, objectSize);
				break;
			}
		case S_C_ROLL_RESULT:                         //游戏滚动结果消息
			{
				dealRollResp(object, objectSize);
				break;
			}
		case  S_C_UPDATE_POND:                        //更新奖池消息
			{
				dealHandSelResp(object, objectSize);
				break;
			}
		case S_C_GAME_OVER:
			{
				dealGameEnd(object, objectSize);   //游戏结束
				break;
			}
		case S_C_CHECK_PRIZE_RESULT:                  //查看大奖消息
			{
				dealCheckPrize(object, objectSize);
				break;
			}
		case S_C_NEXT_PAGE_RESULT:                  //下一页
			{
				dealCheckPrizeNext(object, objectSize);
				break;
			}
		case S_C_SHARE_AWARD_RESULT:{
			dealShareAwardResult(object, objectSize);
			break;
		}
			
		default:
			break;
		}
	}

	void GameTableLogic::dealShareAwardResult(void* object, int objectSize){
		CHECK_SOCKET_DATA(S_C_ShareAwardResult, objectSize, "S_C_ShareAwardResult is error.");
		S_C_ShareAwardResult* shareAwardResult = (S_C_ShareAwardResult*)object;
		_uiCallback->setOnResult(shareAwardResult->iShangFenMoney);
	}

	void GameTableLogic::dealGameStationResp(void* object, int objectSize)
	{
		S_C_GameStation * pGameStation = (S_C_GameStation *)object;
		SetStationParameter(pGameStation->byGameStation);
		if (GetStationParameter() == GS_WAIT_NEXT)
		{
			_uiCallback->addStartGameAnimate();
		}
		_gameState = GS_WAIT_NEXT;
		//存储最大单线下注额
		_uiCallback->setMaxLineBet(pGameStation->iCellBet);
		//设置用户自己的金币数
		_uiCallback->setMyMoney(pGameStation->i64UserMoney);
		//设置彩金
		_uiCallback->setHandsel(pGameStation->i64SinglePond, pGameStation->i64Pond);

		_uiCallback->setRoomInfo(pGameStation->szGameRoomName, pGameStation->bDeskIndex);

		//设置房间信息

		m_userAllMoney = pGameStation->i64UserMoney;
		return;
	}

	void GameTableLogic::dealOnResp(void* object, int objectSize)
	{
		CHECK_SOCKET_DATA(S_C_ShangFenResult, objectSize, "S_C_ShangFenResult is error.");
		S_C_ShangFenResult* sf = (S_C_ShangFenResult* ) object;
		_uiCallback->setOnResult(sf->iShangFenMoney);
		_uiCallback->setMyMoney(sf->i64UserMoney);
		m_exchangeRate = (sf->iShangFenMoney * 1.0f) / (m_userAllMoney - sf->i64UserMoney);
	}

	void GameTableLogic::dealRollResp(void* object, int objectSize)
	{
		CHECK_SOCKET_DATA(S_C_TypeScroll, objectSize, "S_C_TypeScroll is error.");
		S_C_TypeScroll* sc = (S_C_TypeScroll* ) object;
		_uiCallback->setImageType(sc->iTypeImgid);//保存图形数据
		_uiCallback->setWinMoney(sc->iWinMoney);//保存玩家赢的钱
		_uiCallback->saveWinLine(sc->bWinAreaFlag);//保存赢的线条
		_uiCallback->isAllGame(sc->iAllGame);//判断是否全盘
		_uiCallback->setGameRule(sc->byPlayStly);//保存当前游戏类型
		_uiCallback->setSpecialRestCount(sc->bySpecialRestCount);//保存特殊玩法的局数
		_uiCallback->setSpecialCount(sc->bySpecialCount);//保存特殊玩法的局数
		_uiCallback->setSpecialRateImage(sc->byPlayStly);//设置特殊玩法倍率的显示和隐藏
		_uiCallback->setAward(sc->iExtaPay);//奖励分数
		_uiCallback->setAllHandOff(sc->bShangFenMoney);//保存玩家的总筹码数
		_uiCallback->set7Count(sc->iLogoValue);//保存本局7的个数
		_uiCallback->setRunCell();//图片开始滚动
		_uiCallback->setSingleWinnings(sc->iGetCaiJin);//所中单机彩金
		_uiCallback->setAllWinnings(sc->iZhongCaiJin);//所用房间彩金
		_uiCallback->setSecondGetMoney(sc->iSecondGetMoney);//二次奖励
		_uiCallback->saveSinglePond(sc->iSinglePond);//单机彩金
		_uiCallback->setShareAward(sc->iShareAward);
		_gameState = GS_PLAY;//设置当前状态为游戏中
		SetStationParameter(_gameState);
		//更新platform里面的金币
		m_userAllMoney += (LLONG)sc->bShangFenMoney / m_exchangeRate;

		// 判断是否是入库类型
		auto isNormal = []()->bool
		{
			UINT flag = (RoomLogic()->getRoomRule() & GRR_EXPERCISE_ROOM) || (RoomLogic()->getRoomRule() & GRR_CONTEST);
			bool ret = !(flag != 0);
			return ret;
		};
		if (isNormal())
		{
			PlatformLogic()->loginResult.i64Money = m_userAllMoney;
		}
		
	}

	void GameTableLogic::dealHandSelResp(void* object, int objectSize)
	{
		CHECK_SOCKET_DATA(S_C_Pond, objectSize, "S_C_Pond is error.");
		S_C_Pond* sp = (S_C_Pond*) object;
		if (sp->bFlag)
		{
			_uiCallback->showRadio("恭喜" + StringUtils::format("%d", sp->byStation) + "号桌玩家" + StringUtils::format("%s", sp->szNickName) + "中大奖，获得" + StringUtils::format("%lld", sp->i64GetPond) + "金币！");
		}
		_uiCallback->setWinnings(sp->i64Pond);
	}

	void GameTableLogic::dealCheckPrize(void* object, int objectSize)
	{
		CHECK_SOCKET_DATA(S_C_Check_Prize, objectSize, "S_C_Check_Prize is error.");
		//获取大奖数据
		S_C_Check_Prize* cp = (S_C_Check_Prize*) object;
		_uiCallback->showCheckPrize(cp->iAllGameCount);
	}

	void GameTableLogic::dealCheckPrizeNext(void* object, int objectSize)
	{
		CHECK_SOCKET_DATA(S_C_Next_Prize, objectSize, "S_C_Next_Prize is error.");
		//获取大奖数据
		S_C_Next_Prize* cp = (S_C_Next_Prize*) object;
		_uiCallback->showCheckPrizeNext(cp->iLineGameCount);
	}

	void GameTableLogic::dealGameStart(void* object, int objectSize)
	{
		_gameState = GS_WAIT_NEXT;
		SetStationParameter(_gameState);
	}

	void GameTableLogic::dealGameEnd(void* object, int objectSize)
	{
		CHECK_SOCKET_DATA(S_C_GameEnd, objectSize, "S_C_GameEnd is error.");
		S_C_GameEnd* ge = (S_C_GameEnd*) object;
		_uiCallback->setGameOver(ge->bGameOver);
	}

	void GameTableLogic::dealNextPageResp(void* object, int objectSize)
	{
		CHECK_SOCKET_DATA(S_C_Next_Prize, objectSize, "S_C_Next_Prize is error.");
		S_C_Next_Prize* ge = (S_C_Next_Prize*) object;
	}

	void GameTableLogic::dealUserAgreeResp(MSG_GR_R_UserAgree* agree)
	{

	}

	void GameTableLogic::dealGameStartResp(BYTE bDeskNO)
	{

	}

	void GameTableLogic::dealGameEndResp(BYTE bDeskNO)
	{

	}

	void GameTableLogic::dealUserSitResp(MSG_GR_R_UserSit * userSit, const UserInfoStruct* user)
	{

	}

	void GameTableLogic::dealQueueUserSitMessage(BYTE deskNo, const std::vector<QUEUE_USER_SIT_RESULT*>& users)
	{

	}

	void GameTableLogic::dealUserUpResp(MSG_GR_R_UserUp * userSit, const UserInfoStruct* user)
	{
		//玩家退出游戏
		//stop();
		//_uiCallback->dealLeaveDesk();
	}

	void GameTableLogic::dealGameInfoResp(MSG_GM_S_GameInfo* pGameInfo)
	{

	}

	void GameTableLogic::dealUserCutMessageResp(INT userId, BYTE seatNo)
	{

	}

	void GameTableLogic::dealGamePointResp(void * object, INT objectSize)
	{

	}

	void GameTableLogic::I_R_M_DisConnect()
	{
		_uiCallback->setOnConnect();
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void GameTableLogic::SetStationParameter(char bGameStation)
	{
		m_bGameStation = bGameStation;
	}

	char GameTableLogic::GetStationParameter()
	{
		return m_bGameStation;
	}	
}
