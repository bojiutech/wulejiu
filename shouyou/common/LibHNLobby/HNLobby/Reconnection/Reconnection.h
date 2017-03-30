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

		// 销毁单例
		static void destroyInstance();

	public:
		Reconnection();

		virtual ~Reconnection();

	public:
		virtual void init();

		// 保存登录信息并检测是否有重连状态
		void saveInfoAndCheckReconnection(const std::string &userName, const std::string &passWord);

		// 进入创建房间
		void doLoginVipRoom(const std::string &password);

	private:
		// 断网消息监听
		void disMsgListens(Ref* ref);

		// 重连
		void reConnection(bool bAuto = true);

	private:
		// 检查重连
		void checkReconnection();

		// 获取重连房间信息
		bool getRoomInfoCallback(HNSocketMessage* socketMessage);

		// 进入创建房间回调
		bool onJoinRoomMessageCallback(HNSocketMessage* socketMessage);

		// 登录房间
		void loginRoom(ComRoomInfo* roomInfo);

		// 延迟重新连接
		void delayReConnection();

	private:
		// 登陆大厅回调
		virtual void onPlatformLoginCallback(bool success, const std::string& message,
			const std::string& name, const std::string& pwd)  override;

	private:
		// 登陆房间回调
		virtual void onRoomLoginCallback(bool success, const std::string& message, UINT roomID, UINT handleCode) override;

		// 坐下回调
		virtual void onRoomSitCallback(bool success, const std::string& message, UINT roomID, BYTE deskNo, BYTE seatNo) override;

	private:
		// 重置参数
		void resetParams();

	private:
		bool _isReconnect = false;		// 是否已经处于重连状态
		bool _isVipRoom = false;		// 当前重连的是vip房间
		std::string _uName = "";		// 玩家登录账号
		std::string _pWord = "";		// 玩家登陆密码
		std::string _deskPsd = "";		// vip桌子密码
		int _MaxConnNums	= 10;		// 最大重连次数
		int _CurConnNums	= 0;		// 当前重连次数

		BYTE _deskNo		= 255;
		BYTE _seatNo		= 255;

		HNPlatformLogin*		_gameLogin		= nullptr;
		HNRoomLogicBase*		_roomLogic		= nullptr;
	};
}

#endif // __HNReconnection_h__