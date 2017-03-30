#ifndef __HNRoomDeskLogic_H__
#define __HNRoomDeskLogic_H__

#include "HNLogic/HNLogicBase.h"
#include "HNNetExport.h"

namespace HN
{
	class IHNRoomDeskLogic
	{
	public:
		virtual void onDeskSitCallback(bool success, const std::string& message, UINT roomID, BYTE deskNo, BYTE seatNo){}
		virtual void onRoomDeskLock(BYTE deskNo) {}
		virtual void onRoomDeskUnLock(BYTE deskNo) {}
		virtual void onRoomUserCome(INT userID){}
		virtual void onRoomUserLeft(INT userID){}
		virtual void onRoomDeskUserCountChanged(){}
	};


	class HNRoomDeskLogic:public HNLogicBase, public IRoomMessageDelegate
	{
	public:
		virtual void start() override;
		virtual void stop() override;
		void requestSit(BYTE deskNo, const std::string& password = "");
		void requestSit(BYTE deskNo, BYTE seatNo, const std::string& password = "");

		// ��������
		void requestQuickSit();

		// ���캯��
		HNRoomDeskLogic(IHNRoomDeskLogic* callback);

		// ��������
		virtual ~HNRoomDeskLogic();
	
		// �û�����
		virtual void I_R_M_UserSit(MSG_GR_R_UserSit * userSit, const UserInfoStruct* user) override;

		// �û�����ʧ��
		virtual void I_R_M_SitError(const std::string& message) override;

		// �û�վ��
		virtual void I_R_M_UserUp(MSG_GR_R_UserUp * userUp, const UserInfoStruct* user) override;

		// ����
		virtual void I_R_M_LockDesk(BYTE deskNo) override;

		// ȡ������
		virtual void I_R_M_UnLockDesk(BYTE deskNo) override;

		// �û�����
		virtual void I_R_M_UserCome(UserInfoStruct* user) override;

		// �û��뿪
		virtual void I_R_M_UserLeft(const UserInfoStruct* user) override;

		// ����Ͽ�
		virtual void I_R_M_DisConnect() override;
	protected:
		IHNRoomDeskLogic* _callback;
		UINT _roomID;
	};
}

#endif