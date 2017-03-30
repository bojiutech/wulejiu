#ifndef __HNGameLogicBase_H__
#define __HNGameLogicBase_H__

#include "HNLogic/HNLogicBase.h"
#include "HNNetExport.h"

namespace HN
{
	/*
	 * @brief: redbird game logic interface.
	 */
	class IHNGameLogicBase
	{
	public:
		virtual void onGameDisconnect(){}
	};

	/*
	 * @brief: redbird game logic.
	 */
	class HNGameLogicBase: public HNLogicBase, public IGameMessageDelegate
	{
	public:
		/*
		 * @brief: will start receive message after called.
		 */
		virtual void start() override;
		/*
		 * @brief: will stop receive message after called.
		 */
		virtual void stop() override;
		/*
		 * @brief: send message to room server from client. 
		 */
		virtual void sendGameInfo();
		virtual void sendUserUp();
		virtual void sendUserSit(BYTE lSeatNo);
		virtual void sendForceQuit();
		virtual void sendAgreeGame();
		virtual void sendChatMsg(const std::string& msg);
	
		//�����׻��Ŷӻ���������Ϸ
		virtual void sendResetGame(bool bReset);
        /*
		 * @brief: translate between view seat no and logic seat no.
		 */
		virtual BYTE viewToLogicSeatNo(BYTE vSeatNO);
		virtual BYTE logicToViewSeatNo(BYTE lSeatNO);

		/*
		 * @brief: get user id from logic seatNo.
		 */
		INT getUserId(BYTE lSeatNo);
		/*
		 * @brief: get my seatNo.
		 */
		BYTE getMySeatNo() const;
		/*
		 * @brief:  get user whether is boy.
		 * @param: 
		 *       lSeatNo is user logic seatNo.
		 * @return: true if it is boy, or false.
		 */
		bool getUserIsBoy(BYTE lSeatNo);
		/*
		 * @brief:  get user's info from userId.
		 * @param:  userID is user's id.
		 * @return: return user's info.
		 */
		UserInfoStruct* getUserByUserID(INT userID);
		/*
		 * @brief:  get user's info from logic seatNo.
		 * @param:  lSeatNo is user's logic seatNo.
		 * @return: return user's info.
		 */
		UserInfoStruct* getUserBySeatNo(BYTE lSeatNo);

		BYTE getGameStatus() const { return _gameStatus; }
		
		void setGameStatus(BYTE status) { _gameStatus = status; }

	public:
		HNGameLogicBase(BYTE deskNo, INT maxPlayers, bool autoCreate, IHNGameLogicBase* callback);
		virtual ~HNGameLogicBase();
	private:
		virtual void loadDeskUsers() final;
	protected:		
		virtual void clearDesk();
	protected:
		/*
		 * framework message deal function.
		 */
		virtual void dealUserAgreeResp(MSG_GR_R_UserAgree* agree);
		virtual void dealGameStartResp(BYTE bDeskNO);
		virtual void dealGameEndResp(BYTE bDeskNO);
		virtual void dealUserSitResp(MSG_GR_R_UserSit * userSit, const UserInfoStruct* user);
		virtual void dealQueueUserSitMessage(BYTE deskNo, const std::vector<QUEUE_USER_SIT_RESULT*>& users);
		virtual void dealUserUpResp(MSG_GR_R_UserUp * userSit, const UserInfoStruct* user);
		virtual void dealGameInfoResp(MSG_GM_S_GameInfo* pGameInfo);
		virtual void dealGameStationResp(void* object, INT objectSize) = 0;
		virtual void dealGameMessage(NetMessageHead* messageHead, void* object, INT objectSize) = 0;
		virtual void dealVIPRoomMessage(NetMessageHead* messageHead, void* object, INT objectSize);
		virtual void dealUserCutMessageResp(INT userId, BYTE seatNo);
		virtual void dealGamePointResp(void * object, INT objectSize);
		virtual void dealUserChatMessage(MSG_GR_RS_NormalTalk* normalTalk);

		// ������ʼ��
		virtual void dealGameContestInit(NET_ROOM_CONTEST_CHANGE_RESULT* contestChange);
		//������Ϣ�㲥
		virtual void dealGameContestNotic(MSG_GR_I_ContestInfo* contestInfo);
		// �û�������Ϣ
		virtual void dealGameUserContset(MSG_GR_ContestChange* contestChange);
		// ��������
		virtual void dealGameContestOver(MSG_GR_ContestAward* contestAward);
		// ������̭
		virtual void dealGameContestKick() ;
		// �ȴ���������
		virtual void dealGameContestWaitOver() ;
		// ��������
		virtual void dealGameContestAwards(NET_ROOM_CONTEST_AWARD_RESULT* contestAward);
		// ��������
		virtual void dealGameContestPeople(NET_ROOM_CONTEST_PEOPLE_RESULT* contestPeople);
		// ���˲�����¼
		virtual void dealGameContestRecord(NET_ROOM_CONTEST_RECORD_RESULT* ContestRecord);

		/////////////////////////////////////////////////////////////////////////////////////////////
		//�����׳�������Ϸ(����ֵΪtrue�ɺ��ԣ�Ϊfalse��ʾ��������������λʧ�ܣ���Ҫ������ʾ��ת�����)
		/////////////////////////////////////////////////////////////////////////////////////////////
		virtual void dealGameResetResult(bool success);
		//�Ŷ��У�����ʾ�Ŷ���������
		virtual void dealGameInline(bool bInline);
		/////////////////////////////////////////////////////////////////////////////////////////////
	protected:
		/* 
		 * init member only once.
		 */
		virtual void initParams();
		/*
		 * refresh member before every game start.
		 */
		virtual void refreshParams();
		/*
		 * get next and last user seat no.
		 * @param:  seatNo find seat no.
		 * @return: return seat no if success, or return INVALID_DESKSTATION
		 */
		/*
		 * @brief:  get next user's logic seatNo.
		 */
		virtual BYTE getNextUserSeatNo(BYTE lSeatNo);
		/*
		 * @brief:  get last user's logic seatNo.
		 */
		virtual BYTE getLastUserSeatNo(BYTE lSeatNo);
	private:
		/*
		 * @brief:  platfrom message.
		 */
		virtual void I_R_M_DisConnect() override;

		// �û�ͬ��
		virtual void I_R_M_UserAgree(MSG_GR_R_UserAgree* agree) override;

		// ��Ϸ��ʼ
		virtual void I_R_M_GameBegin(BYTE bDeskNO) override;

		// ��Ϸ����
		virtual void I_R_M_GameEnd(BYTE bDeskNO) override;

		// ��Ϸ��Ϣ
		virtual void I_R_M_GameInfo(MSG_GM_S_GameInfo* pGameInfo) override;

		// ��Ϸ״̬
		virtual void I_R_M_GameStation(void* object, INT objectSize) override;
		virtual bool onGameMessage(NetMessageHead* messageHead, void* object, INT objectSize) override;

		virtual bool I_R_M_VIP_Room(NetMessageHead* messageHead, void* object, INT objectSize) override;

		// ������Ϣ
		virtual void I_R_M_GamePoint(void * object, INT objectSize) override;
	
		// �Ŷ��û�����
		virtual void I_R_M_QueueUserSit(BYTE deskNo, const std::vector<QUEUE_USER_SIT_RESULT*>& users) override;

		// �û�����
		virtual void I_R_M_UserSit(MSG_GR_R_UserSit * userSit, const UserInfoStruct* user) override;
		
		// �û�վ��
		virtual void I_R_M_UserUp(MSG_GR_R_UserUp * userUp, const UserInfoStruct* user) override;

		// �û�����
		virtual void I_R_M_UserCut(INT dwUserID, BYTE bDeskNO, BYTE	bDeskStation) override;
		
		// ������ʼ��
		virtual void I_R_M_ContestInit(NET_ROOM_CONTEST_CHANGE_RESULT* contestChange) override;

		//������Ϣ�㲥
		virtual void I_R_M_ContestNotic(MSG_GR_I_ContestInfo* contestInfo) override;

		// �û�������Ϣ
		virtual void I_R_M_UserContest(MSG_GR_ContestChange* contestChange) override;

		// ��������
		virtual void I_R_M_ContestOver(MSG_GR_ContestAward* contestAward) override;

		// ������̭
		virtual void I_R_M_ContestKick() override;
		
		// �ȴ���������
		virtual void I_R_M_ContestWaitOver() override;

		// ��������
		virtual void I_R_M_ContestAwards(std::vector<NET_ROOM_CONTEST_AWARD_RESULT*>* awards) override {}

		// ��������
		virtual void I_R_M_ContestPeople(NET_ROOM_CONTEST_PEOPLE_RESULT* contestPeople) override {}

		// ���˲�����¼
		virtual void I_R_M_ContestRecord(NET_ROOM_CONTEST_RECORD_RESULT* contestRecord) override {}

		// ������Ϣ
		virtual void I_R_M_NormalTalk(void* object, INT objectSize) override;

	protected:
		IHNGameLogicBase* _callback;
		HNGameTableUsersData*		_deskUserList;
		BYTE						_deskNo;
		BYTE						_mySeatNo;		
		BYTE						_watchOther;	// �����Թ�
		BYTE						_gameStatus;	// ��Ϸ״̬
		bool						_bReconnect;	// �Ƿ�������״̬
		bool						_bReset;		// �Ƿ�������Ϸ
		// + is clockwise, - is opposite.
		int							_seatOffset;	// ��λƫ����
		// before auto action, player's action time.
		BYTE						_waitTime;		// �ȴ�ʱ��
		// max player count in the table.
		INT							_maxPlayers;
		// if the table is auto created
		bool						_autoCreate;
		std::vector<bool>			_existPlayer;
		std::vector<bool>			_playing;
	};
}

#endif