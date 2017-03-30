#ifndef __HNRoomLogicBase_H__
#define __HNRoomLogicBase_H__

#include "HNLogic/HNLogicBase.h"

namespace HN
{
	class IHNRoomLogicBase
	{
	public:
		virtual void onRoomLoginCallback(bool success, const std::string& message, UINT roomID, UINT handleCode){}
		virtual void onRoomSitCallback(bool success, const std::string& message, UINT roomID, BYTE deskNo, BYTE seatNo){}
		virtual void onRoomQueueSitCallback(bool success, const std::string& message, UINT roomID, BYTE deskNo){}
		virtual void onRoomSitUpCallback(bool success, const std::string& message, BYTE destNo, BYTE seatNo){}
		virtual void onRoomUserCome(INT userID){}
		virtual void onRoomUserLeft(INT userID){}
		virtual void onRoomDisConnect(const std::string &message){}
		// ��������
		virtual void onPlatformRoomPassEnter(bool success, UINT roomId){}
	};

	class IRoomMessageDelegate;
	/*
	 * redbird room logic base.
	 */
	class HNRoomLogicBase: public HNLogicBase, public IRoomMessageDelegate, public IPlatformMessageDelegate
	{
	public:
		virtual void start() override;
		virtual void stop() override;
		void requestLogin(UINT roomID, bool forced = false);
		void requestSit(BYTE deskNo);
		void requestSit(BYTE deskNo, BYTE seatNo);
		void requestJoinQueue();

		// ��������(deskNo=255��ϵͳ��������)
		void requestQuickSit(BYTE deskNo = 255, std::string password = "");

		// ���ܷ���
		void requestRoomPasword(UINT roomId, const std::string& password);

	public:
		// ������ʼ��
		virtual void I_R_M_ContestInit(NET_ROOM_CONTEST_CHANGE_RESULT* contestChange){}

		// �û�������Ϣ
		virtual void I_R_M_UserContest(NET_ROOM_CONTEST_CHANGE_RESULT* contestChange){}

		// ��������
		virtual void I_R_M_ContestOver(NET_ROOM_CONTEST_AWARD_RESULT* contestAward){}

		// ������̭
		virtual void I_R_M_ContestKick(){}

		// �����ȴ�����
		virtual void I_R_M_ContestWaitOver(){}

		// ��������
		virtual void I_R_M_ContestAwards(std::vector<NET_ROOM_CONTEST_AWARD_RESULT*>* awards){}

		// ������������
		virtual void I_R_M_ContestPeople(NET_ROOM_CONTEST_PEOPLE_RESULT* contestPeople){}

		// ������¼
		virtual void I_R_M_ContestRecord(NET_ROOM_CONTEST_RECORD_RESULT* contestRecord){}

		// ��ͨ����
		virtual void I_R_M_NormalTalk(void* object, INT objectSize){}

		// �û�����
		virtual void I_R_M_UserSit(MSG_GR_R_UserSit * userSit, const UserInfoStruct* user);

		// �û�����ʧ��
		virtual void I_R_M_SitError(const std::string& message) override;

		// �û��Ŷ�����
		virtual void I_R_M_QueueUserSit(BYTE deskNo, const std::vector<QUEUE_USER_SIT_RESULT*>& users);

		// �û�վ��
		virtual void I_R_M_UserUp(MSG_GR_R_UserUp * userUp, const UserInfoStruct* user);

		// �û�����
		virtual void I_R_M_UserCut(INT dwUserID, BYTE bDeskNO, BYTE	bDeskStation) {}

		// �Ͽ�����
		virtual void I_R_M_DisConnect() override;

		// ��������
		virtual void I_R_M_Connect(bool result) override;

		// �����¼
		virtual void I_R_M_Login(bool success, UINT handleCode, const std::string& message) override;

		// ��¼���
		virtual void I_R_M_LoginFinish() override;

		// �û�����
		virtual void I_R_M_UserCome(UserInfoStruct* user) override;

		// �û��뿪
		virtual void I_R_M_UserLeft(const UserInfoStruct* user) override;

		// ������Ϣ
		virtual void I_R_M_GamePoint(void * object, INT objectSize) override;

		// ��������
		virtual void I_P_M_RoomPassword(MSG_GP_S_C_CheckRoomPasswd* pData) override;
	public:
		HNRoomLogicBase(IHNRoomLogicBase* callback);
		virtual ~HNRoomLogicBase();
	protected:
		IHNRoomLogicBase* _callback;
		UINT _roomID;
		bool _forced = false;
	};
}

#endif