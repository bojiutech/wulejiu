/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/
#ifndef __HNReconnection_h__
#define __HNReconnection_h__

#include "HNNetExport.h"
#include "HNUIExport.h"
#include "HNLogicExport.h"
#include "cocos2d.h"

USING_NS_CC;

namespace HN
{
	class Reconnection 
		: public Ref
		, public HN::IHNPlatformLogin
		, public HN::IHNRoomLogicBase
	{
	public:
		static Reconnection* getInstance();

		// ���ٵ���
		static void destroyInstance();

	public:
		Reconnection();

		virtual ~Reconnection();

	public:
		virtual void init();

		// �����¼��Ϣ������Ƿ�������״̬
		void saveInfoAndCheckReconnection(const std::string &userName, const std::string &passWord);

		// ���봴������
		void doLoginVipRoom(const std::string &password);

	private:
		// ������Ϣ����
		void disMsgListens(Ref* ref);

		// ����
		void reConnection(bool bAuto = true);

	private:
		// �������
		void checkReconnection();

		// ��ȡ����������Ϣ
		bool getRoomInfoCallback(HNSocketMessage* socketMessage);

		// ���봴������ص�
		bool onJoinRoomMessageCallback(HNSocketMessage* socketMessage);

		// ��¼����
		void loginRoom(ComRoomInfo* roomInfo);

		// �ӳ���������
		void delayReConnection();

	private:
		// ��½�����ص�
		virtual void onPlatformLoginCallback(bool success, const std::string& message,
			const std::string& name, const std::string& pwd)  override;

	private:
		// ��½����ص�
		virtual void onRoomLoginCallback(bool success, const std::string& message, UINT roomID, UINT handleCode) override;

		// ���»ص�
		virtual void onRoomSitCallback(bool success, const std::string& message, UINT roomID, BYTE deskNo, BYTE seatNo) override;

	private:
		// ���ò���
		void resetParams();

	private:
		bool _isReconnect = false;		// �Ƿ��Ѿ���������״̬
		bool _isVipRoom = false;		// ��ǰ��������vip����
		std::string _uName = "";		// ��ҵ�¼�˺�
		std::string _pWord = "";		// ��ҵ�½����
		std::string _deskPsd = "";		// vip��������
		int _MaxConnNums	= 10;		// �����������
		int _CurConnNums	= 0;		// ��ǰ��������

		BYTE _deskNo		= 255;
		BYTE _seatNo		= 255;

		HNPlatformLogin*		_gameLogin		= nullptr;
		HNRoomLogicBase*		_roomLogic		= nullptr;
	};
}

#endif // __HNReconnection_h__