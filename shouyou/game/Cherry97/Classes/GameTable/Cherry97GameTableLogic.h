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
		virtual void dealOnResp(void* object, int objectSize);//�����Ϸ�
		virtual void dealRollResp(void* object, int objectSize);//����������
		virtual void dealHandSelResp(void* object, int objectSize); //��������Ϣ
		virtual void dealCheckPrize(void* object, int objectSize);//����鿴�󽱵���Ϣ
		virtual void dealCheckPrizeNext(void* object, int objectSize);//����鿴��һҳ����Ϣ
		virtual void dealGameStart(void* object, int objectSize);//������Ϸ��ʼ
		virtual void dealGameEnd(void* object, int objectSize);//������Ϸ����
		virtual void dealNextPageResp(void* object, int objectSize);//������һҳ��Ϣ
		virtual void dealShareAwardResult(void* object, int objectSize);
	public:
		//�����Ϣ
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
		LLONG	m_iSingleNoteLimit;     //��������ע����
		int     m_bSuperClient;         //����Ƿ�Ϊ�����ͻ���
		char	m_bGameStation;			///��Ϸ״̬
		int     m_iWiningTime;          //����ʱ��
	public:
		LLONG   m_userAllMoney = 0;         //��¼�û��ܵĽ����
		float   m_exchangeRate = 0.0f;         //�һ�����

	private:
		void SetStationParameter(char bGameStation);//������Ϸ״̬
		char GetStationParameter();//��ȡ��Ϸ״̬

		void initParams();
	};
}


#endif