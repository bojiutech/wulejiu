#ifndef __Cherry97_Game_Table_Logic_H__
#define __Cherry97_Game_Table_Logic_H__

#include "HNNetExport.h"
#include "HNLogicExport.h"
#include "Cherry97MessageHead.h"
#include "Cherry97GameCell.h"

namespace Cherry97
{
	class GameTableUICallback;

	class GameTableLogic: public HN::HNGameLogicBase
	{
	public:
		GameTableLogic(GameTableUICallback* uiCallback, char deskNo, bool bAutoCreate);
		virtual ~GameTableLogic();	
		virtual void dealGameMessage(NetMessageHead* messageHead, void* object, int objectSize) override;
		char _gameState;

	public:	
		virtual void dealOnResp(void* object, int objectSize);//处理上分
		virtual void dealRollResp(void* object, int objectSize);//处理滚动结果
		virtual void dealHandSelResp(void* object, int objectSize); //处理奖池消息
		virtual void dealCheckPrize(void* object, int objectSize);//处理查看大奖的消息
		virtual void dealCheckPrizeNext(void* object, int objectSize);//处理查看下一页的消息
		virtual void dealGameStart(void* object, int objectSize);//处理游戏开始
		virtual void dealGameEnd(void* object, int objectSize);//处理游戏结束
		virtual void dealNextPageResp(void* object, int objectSize);//处理下一页消息
		virtual void dealShareAwardResult(void* object, int objectSize);
	public:
		//框架消息
		virtual void dealGameStationResp(void* object, int objectSize) override;
		virtual void dealUserAgreeResp(MSG_GR_R_UserAgree* agree) override;
		virtual void dealGameStartResp(BYTE bDeskNO) override;
		virtual void dealGameEndResp(BYTE bDeskNO) override;
		virtual void dealUserSitResp(MSG_GR_R_UserSit * userSit, const UserInfoStruct* user) override;
		virtual void dealQueueUserSitMessage(BYTE deskNo, const std::vector<QUEUE_USER_SIT_RESULT*>& users) override;
		virtual void dealUserUpResp(MSG_GR_R_UserUp * userSit, const UserInfoStruct* user) override;
		virtual void dealGameInfoResp(MSG_GM_S_GameInfo* pGameInfo) override;
		virtual void dealUserCutMessageResp(INT userId, BYTE seatNo) override;
		virtual void dealGamePointResp(void * object, INT objectSize) override;
		virtual void I_R_M_DisConnect() override; 

	public:
		HNGameLogicBase* _gameLogicBase;

	private:
		GameTableUICallback*	_uiCallback;
		LLONG	m_iSingleNoteLimit;     //单个人下注上限
		int     m_bSuperClient;         //玩家是否为超级客户端
		char	m_bGameStation;			///游戏状态
		int     m_iWiningTime;          //开奖时间
	public:
		LLONG   m_userAllMoney = 0;         //记录用户总的金币数
		float   m_exchangeRate = 0.0f;         //兑换比例

	private:
		void SetStationParameter(char bGameStation);//设置游戏状态
		char GetStationParameter();//获取游戏状态

		void initParams();
	};
}


#endif