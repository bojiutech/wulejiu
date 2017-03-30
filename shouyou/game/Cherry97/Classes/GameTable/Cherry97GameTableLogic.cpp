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
		case S_C_GAME_BEGIN:                         //��Ϸ��ʼ��Ϣ
			{
				dealGameStart(object, objectSize);
				break;
			}
		case S_C_SHANG_FEN:                          //�Ϸֽ����Ϣ
			{
				dealOnResp(object, objectSize);
				break;
			}
		case S_C_ROLL_RESULT:                         //��Ϸ���������Ϣ
			{
				dealRollResp(object, objectSize);
				break;
			}
		case  S_C_UPDATE_POND:                        //���½�����Ϣ
			{
				dealHandSelResp(object, objectSize);
				break;
			}
		case S_C_GAME_OVER:
			{
				dealGameEnd(object, objectSize);   //��Ϸ����
				break;
			}
		case S_C_CHECK_PRIZE_RESULT:                  //�鿴����Ϣ
			{
				dealCheckPrize(object, objectSize);
				break;
			}
		case S_C_NEXT_PAGE_RESULT:                  //��һҳ
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
		//�洢�������ע��
		_uiCallback->setMaxLineBet(pGameStation->iCellBet);
		//�����û��Լ��Ľ����
		_uiCallback->setMyMoney(pGameStation->i64UserMoney);
		//���òʽ�
		_uiCallback->setHandsel(pGameStation->i64SinglePond, pGameStation->i64Pond);

		_uiCallback->setRoomInfo(pGameStation->szGameRoomName, pGameStation->bDeskIndex);

		//���÷�����Ϣ

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
		_uiCallback->setImageType(sc->iTypeImgid);//����ͼ������
		_uiCallback->setWinMoney(sc->iWinMoney);//�������Ӯ��Ǯ
		_uiCallback->saveWinLine(sc->bWinAreaFlag);//����Ӯ������
		_uiCallback->isAllGame(sc->iAllGame);//�ж��Ƿ�ȫ��
		_uiCallback->setGameRule(sc->byPlayStly);//���浱ǰ��Ϸ����
		_uiCallback->setSpecialRestCount(sc->bySpecialRestCount);//���������淨�ľ���
		_uiCallback->setSpecialCount(sc->bySpecialCount);//���������淨�ľ���
		_uiCallback->setSpecialRateImage(sc->byPlayStly);//���������淨���ʵ���ʾ������
		_uiCallback->setAward(sc->iExtaPay);//��������
		_uiCallback->setAllHandOff(sc->bShangFenMoney);//������ҵ��ܳ�����
		_uiCallback->set7Count(sc->iLogoValue);//���汾��7�ĸ���
		_uiCallback->setRunCell();//ͼƬ��ʼ����
		_uiCallback->setSingleWinnings(sc->iGetCaiJin);//���е����ʽ�
		_uiCallback->setAllWinnings(sc->iZhongCaiJin);//���÷���ʽ�
		_uiCallback->setSecondGetMoney(sc->iSecondGetMoney);//���ν���
		_uiCallback->saveSinglePond(sc->iSinglePond);//�����ʽ�
		_uiCallback->setShareAward(sc->iShareAward);
		_gameState = GS_PLAY;//���õ�ǰ״̬Ϊ��Ϸ��
		SetStationParameter(_gameState);
		//����platform����Ľ��
		m_userAllMoney += (LLONG)sc->bShangFenMoney / m_exchangeRate;

		// �ж��Ƿ����������
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
			_uiCallback->showRadio("��ϲ" + StringUtils::format("%d", sp->byStation) + "�������" + StringUtils::format("%s", sp->szNickName) + "�д󽱣����" + StringUtils::format("%lld", sp->i64GetPond) + "��ң�");
		}
		_uiCallback->setWinnings(sp->i64Pond);
	}

	void GameTableLogic::dealCheckPrize(void* object, int objectSize)
	{
		CHECK_SOCKET_DATA(S_C_Check_Prize, objectSize, "S_C_Check_Prize is error.");
		//��ȡ������
		S_C_Check_Prize* cp = (S_C_Check_Prize*) object;
		_uiCallback->showCheckPrize(cp->iAllGameCount);
	}

	void GameTableLogic::dealCheckPrizeNext(void* object, int objectSize)
	{
		CHECK_SOCKET_DATA(S_C_Next_Prize, objectSize, "S_C_Next_Prize is error.");
		//��ȡ������
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
		//����˳���Ϸ
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
