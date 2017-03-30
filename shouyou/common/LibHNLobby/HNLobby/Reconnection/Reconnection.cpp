/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/


#include "Reconnection.h"
#include "../GamePlatform.h"
#include "../GamePrompt.h"
#include "../GameMenu/GameMenu.h"

namespace HN
{
	static const int OUTTIME_TAG = 12;			// 超时检测标签

	static Reconnection* logic = nullptr;

	Reconnection* Reconnection::getInstance()
	{
		if (nullptr == logic)
		{
			logic = new (std::nothrow) Reconnection();
			if (logic) logic->init();
		}
		return logic;
	}

	void Reconnection::destroyInstance()
	{
		if (!logic) CC_SAFE_DELETE(logic);
	}

	Reconnection::Reconnection()
	{
		_gameLogin = new HNPlatformLogin(this);
		_roomLogic = new HNRoomLogicBase(this);
	}

	Reconnection::~Reconnection()
	{
		_gameLogin->stop();
		_roomLogic->stop();
		HN_SAFE_DELETE(_gameLogin);
		HN_SAFE_DELETE(_roomLogic);

		PlatformLogic()->removeEventSelector(MDM_GP_CUTNET_ROOMINFO, ASS_GP_CUTNET_GET_ROOMINFO);
		PlatformLogic()->removeEventSelector(MDM_GP_DESK_VIP, ASS_GP_ENTER_DESK);

		__NotificationCenter::getInstance()->removeObserver(this, DISCONNECT);
	}

	void Reconnection::init()
	{
		__NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(Reconnection::disMsgListens), DISCONNECT, nullptr);
	}

	void Reconnection::saveInfoAndCheckReconnection(const std::string &userName, const std::string &passWord)
	{
		_uName = userName;
		_pWord = passWord;

		// 重置参数
		resetParams();

		// 检查有没有重连状态
		checkReconnection();

		// 开始全局广播消息监听
		//GameNotifyCenter::getInstance()->startListening();
	}

	void Reconnection::checkReconnection()
	{
		if (0 == PlatformLogic()->loginResult.iCutRoomID)//如果不是断线重连，直接进大厅
		{
			if (_isVipRoom)
			{
				/*auto prompt = GamePromptLayer::create();
				prompt->showPrompt(GBKToUtf8("当前游戏未开始或房间已解散，请重新进入"));
				prompt->setCallBack([=](){
					GamePlatform::createPlatform();
				});*/
			}
			else GamePlatform::createPlatform();
		}
		else//如果是断线重连，直接请求指定房间进入指定游戏
		{
			MSG_GP_S_GET_CUTNETROONINFO info;
			info.iUserID = PlatformLogic()->loginResult.dwUserID;
			PlatformLogic()->sendData(MDM_GP_CUTNET_ROOMINFO, ASS_GP_CUTNET_GET_ROOMINFO, &info, sizeof(MSG_GP_S_GET_CUTNETROONINFO),
				HN_SOCKET_CALLBACK(Reconnection::getRoomInfoCallback, this));
		}
	}

	bool Reconnection::getRoomInfoCallback(HNSocketMessage* socketMessage)
	{
		CHECK_SOCKET_DATA_RETURN(MSG_GP_S_GET_CUTNETROOMINFO_RES, socketMessage->objectSize, true,
			"MSG_GP_S_GET_CUTNETROOMINFO_RES size of error!");
		auto res = (MSG_GP_S_GET_CUTNETROOMINFO_RES*)socketMessage->object;

		if (socketMessage->messageHead.bHandleCode == 1
			|| socketMessage->messageHead.bHandleCode == 4)
		{
			if (res->iDeskID != 255) _deskNo = res->iDeskID;
			std::string psd(res->szPass);
			if (!psd.empty()) _deskPsd = psd;

			if (res->tCutNetRoomInfo.uRoomID != 0)
			{
				RoomInfoModule()->addRoom(&res->tCutNetRoomInfo);
				loginRoom(&res->tCutNetRoomInfo);
			}
			else
			{
				PlatformLogic()->close();
				GamePromptLayer::create()->showPrompt(GBKToUtf8("房间信息错误"));
			}
		}
		else
		{
			GamePlatform::createPlatform();
		}

		return true;
	}

	// 进入创建房间
	void Reconnection::doLoginVipRoom(const std::string &password)
	{
		log("============================password:%s", password.c_str());
		if (!password.empty()) _deskPsd = password;
		MSG_GP_S_ENTER_VIPDESK joinRoomStruct;
		joinRoomStruct.iUserID = PlatformLogic()->loginResult.dwUserID;
		strcpy(joinRoomStruct.szInputPassWord, password.c_str());

		PlatformLogic()->sendData(MDM_GP_DESK_VIP, ASS_GP_ENTER_DESK, &joinRoomStruct, sizeof(MSG_GP_S_ENTER_VIPDESK),
			HN_SOCKET_CALLBACK(Reconnection::onJoinRoomMessageCallback, this));
	}

	// 进入创建房间回调
	bool Reconnection::onJoinRoomMessageCallback(HNSocketMessage* socketMessage)
	{
		CHECK_SOCKET_DATA_RETURN(MSG_GP_S_ENTER_VIPDESK_RES, socketMessage->objectSize, true, "MSG_GP_S_ENTER_VIPDESK_RES size of error!");
		MSG_GP_S_ENTER_VIPDESK_RES* joinRoomRes = (MSG_GP_S_ENTER_VIPDESK_RES*)socketMessage->object;

		switch (socketMessage->messageHead.bHandleCode)
		{
		case 0:
			GamePromptLayer::create()->showPrompt(GBKToUtf8("没有这个桌子")); break;
		case 1:
		case 3:
		{
				  _deskNo = joinRoomRes->iDeskID;
				  _deskPsd = joinRoomRes->szPass;
				  if (joinRoomRes->tCutNetRoomInfo.uRoomID == 0)
				  {
					  GamePromptLayer::create()->showPrompt(GBKToUtf8("购买房间信息错误，无法进入")); break;
				  }
				  RoomInfoModule()->addRoom(&joinRoomRes->tCutNetRoomInfo);
				  loginRoom(&joinRoomRes->tCutNetRoomInfo);
		}break;
		case 2:
			GamePromptLayer::create()->showPrompt(GBKToUtf8("用户不存在")); break;
		case 4:
			GamePromptLayer::create()->showPrompt(GBKToUtf8("无空闲桌子")); break;
		default:
			break;
		}

		return true;
	}

	void Reconnection::loginRoom(ComRoomInfo* roomInfo)
	{
		std::vector<UINT> gameNames = GameCreator()->getRegistGameIdList();
		bool bLua = true;
		for (int i = 0; i < gameNames.size(); i++)
		{
			if (gameNames[i] == roomInfo->uNameID)
			{
				bLua = false;
				break;
			}
		}

		if (bLua)
		{
			//int size = sizeof(int)+50 + sizeof(ComRoomInfo);//50是md5密码长度
			//NetMsg* netMsg = NetMsg::createWithSize(size);
			//netMsg->pushINT(PlatformLogic()->loginResult.dwUserID);
			//netMsg->pushNCHAR(PlatformLogic()->loginResult.szMD5Pass, 50);
			//netMsg->pushVOID((const void*)roomInfo, sizeof(ComRoomInfo));
			//netMsg->revertOffset();
			//if (!HN::LuaCppSwitch::getInstance()->enterGame(netMsg))
			//{
			//	MessageBox(GBKToUtf8("启动游戏失败，请查询。"), "Error");
			//}
		}
		else
		{
			_roomLogic->start();
			_roomLogic->requestLogin(roomInfo->uRoomID, true);

			LoadingLayer::createLoading(Director::getInstance()->getRunningScene(), GBKToUtf8("登录房间，请稍候..."), 25);

			//delayReConnection();
		}
	}

	void Reconnection::onRoomLoginCallback(bool success, const std::string& message, UINT roomID, UINT handleCode)
	{
		log("### onRoomLoginCallback:%s", message.c_str());

		_roomLogic->stop();

		auto node = Director::getInstance()->getRunningScene();
		node->stopActionByTag(OUTTIME_TAG);

		if (success)
		{
			LoadingLayer::removeLoading(node);
			_isReconnect = false;

			if (PlatformConfig::getInstance()->getSceneState() == PlatformConfig::SCENE_STATE::INROOM) return;

			if (_deskNo != 255)
			{
				_roomLogic->start();
				_roomLogic->requestQuickSit(_deskNo, _deskPsd);
				LoadingLayer::createLoading(node, GBKToUtf8("游戏加载中，请稍候..."), 25);
			}
			else
			{
				HNLOG_ERROR("deskNo Error：%d", _deskNo);
				RoomLogic()->close();
				if (PlatformConfig::getInstance()->getSceneState() == PlatformConfig::SCENE_STATE::OTHER)
				{
					PlatformLogic()->close();
				}
				else
				{
					GamePlatform::createPlatform();
				}
			}
		}
		else
		{
			RoomLogic()->close();
			if (_CurConnNums < _MaxConnNums)
			{
				++_CurConnNums;
				node->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create([=](){
					loginRoom(RoomLogic()->getSelectedRoom());
				}), nullptr));
			}
			else
			{
				LoadingLayer::removeLoading(node);

				auto prompt = GamePromptLayer::create();
				prompt->setPromptCanSelect();
				prompt->showPrompt(StringUtils::format(GBKToUtf8("%s, 请重试"), message.c_str()));
				prompt->setCallBack([=](){
					_CurConnNums = 0;
					_isReconnect = false;
					loginRoom(RoomLogic()->getSelectedRoom());
				});
				prompt->setCancelCallBack([=](){
					_isReconnect = false;
					PlatformLogic()->close();
					if (PlatformConfig::getInstance()->getSceneState() != PlatformConfig::SCENE_STATE::OTHER)
					{
						GameMenu::createMenu();
					}
				});
			}
		}
	}

	void Reconnection::onRoomSitCallback(bool success, const std::string& message, UINT roomID, BYTE deskNo, BYTE seatNo)
	{
		log("### onRoomSitCallback:%s", message.c_str());

		_roomLogic->stop();
		auto node = Director::getInstance()->getRunningScene();
		node->stopActionByTag(OUTTIME_TAG);

		if (success)
		{
			_isReconnect = false;
			LoadingLayer::removeLoading(node);

			// 如果是游戏中重连，则坐下成功之后自动发送gameInfo，不需要额外处理
			if (PlatformConfig::getInstance()->getSceneState() != PlatformConfig::SCENE_STATE::INGAME)
			{
				// 启动游戏
				bool ret = GameCreator()->startGameClient(RoomLogic()->getSelectedRoom()->uNameID, deskNo, true);
				if (!ret)
				{
					RoomLogic()->close();
					auto prompt = GamePromptLayer::create();
					prompt->showPrompt(GBKToUtf8("游戏启动失败。"));
					prompt->setCallBack([=](){
						GamePlatform::createPlatform();
					});
				}
			}
		}
		else
		{
			RoomLogic()->close();
			LoadingLayer::removeLoading(node);

			auto prompt = GamePromptLayer::create();
			prompt->showPrompt(StringUtils::format(GBKToUtf8("%s"), message.c_str()));
			/*prompt->setPromptCanSelect();
			prompt->showPrompt(StringUtils::format(GBKToUtf8("%s, 请重试"), message.c_str()));
			prompt->setCallBack([=](){
				_CurConnNums = 0;
				_isReconnect = false;
				loginRoom(RoomLogic()->getSelectedRoom());
			});

			prompt->setCancelCallBack([=](){
				_isReconnect = false;
				PlatformLogic()->close();
				if (PlatformConfig::getInstance()->getSceneState() != PlatformConfig::SCENE_STATE::OTHER)
				{
					GameMenu::createMenu();
				}
			});*/
		}
	}

	// 登陆大厅回调
	void Reconnection::onPlatformLoginCallback(bool success, const std::string& message,
		const std::string& name, const std::string& pwd)
	{
		log("### onPlatformLoginCallback:%s", message.c_str());

		_gameLogin->stop();

		auto node = Director::getInstance()->getRunningScene();
		node->stopActionByTag(OUTTIME_TAG);

		if (success)
		{
			_CurConnNums = 0;
			LoadingLayer::removeLoading(node);

			switch (PlatformConfig::getInstance()->getSceneState())
			{
			case PlatformConfig::SCENE_STATE::OTHER:
			case PlatformConfig::SCENE_STATE::INPLATFORM:
				_isReconnect = false;
				break;
			case PlatformConfig::SCENE_STATE::INROOM:
				loginRoom(RoomLogic()->getSelectedRoom());
				break;
			case PlatformConfig::SCENE_STATE::INGAME:
			{
				//如果是创建房间的重连则走平台获取断线信息通道，防止重连进已经解散的房间
				if (_isVipRoom)
				{
					checkReconnection();
				}
				else
				{
					loginRoom(RoomLogic()->getSelectedRoom());
				}
			}
				break;
			default:
				break;
			}
		}
		else
		{
			if (_CurConnNums < _MaxConnNums)
			{
				++_CurConnNums;
				node->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create([=](){
					reConnection(false);
				}), nullptr));
			}
			else
			{
				LoadingLayer::removeLoading(node);

				auto prompt = GamePromptLayer::create();
				prompt->setPromptCanSelect();
				prompt->showPrompt(StringUtils::format(GBKToUtf8("%s, 请重试"), message.c_str()));
				prompt->setCallBack([=](){
					_CurConnNums = 0;
					_isReconnect = false;
					reConnection(false);
				});
				prompt->setCancelCallBack([=](){
					PlatformLogic()->close();
					GameMenu::createMenu();
				});
			}
		}
	}

	// 重连
	void Reconnection::reConnection(bool bAuto/* = true*/)
	{
		if (_isReconnect && bAuto) return;
		_isReconnect = true;

		log(">> reConnection >> .");

		if (PlatformConfig::getInstance()->getSceneState() == PlatformConfig::SCENE_STATE::INGAME)
		{
			_deskNo = RoomLogic()->loginResult.pUserInfoStruct.bDeskNO;
			_seatNo = RoomLogic()->loginResult.pUserInfoStruct.bDeskStation;

			_isVipRoom = RoomLogic()->getSelectedRoom()->bBuyRoom;
		}
		RoomLogic()->close();
		PlatformLogic()->close();

		_gameLogin->start();
		_gameLogin->requestLogin(_uName, _pWord, true);
		LoadingLayer::createLoading(Director::getInstance()->getRunningScene(), GBKToUtf8("正在重连，请稍候..."), 25);

		delayReConnection();
	}

	void Reconnection::delayReConnection()
	{
		auto node = Director::getInstance()->getRunningScene();
		node->stopActionByTag(OUTTIME_TAG);

		auto delay = Sequence::create(DelayTime::create(15.f), CallFunc::create([=](){
			LoadingLayer::removeLoading(node);

			_roomLogic->stop();
			_gameLogin->stop();
			RoomLogic()->close();
			PlatformLogic()->close();

			auto prompt = GamePromptLayer::create();
			prompt->showPrompt(GBKToUtf8("网络连接失败，请重试！"));
			if (PlatformConfig::getInstance()->getSceneState() != PlatformConfig::SCENE_STATE::OTHER)
			{
				prompt->setPromptCanSelect();
				prompt->setCallBack([=](){
					reConnection(false);
				});

				prompt->setCancelCallBack([=](){
					GameMenu::createMenu();
				});
			}
		}), nullptr);

		delay->setTag(OUTTIME_TAG);
		node->runAction(delay);
	}

	void Reconnection::resetParams()
	{
		_isReconnect = false;
		_isVipRoom = false;
		_deskPsd = "";
		_CurConnNums = 0;
		_deskNo = 255;
		_seatNo = 255;
	}

	void Reconnection::disMsgListens(Ref* ref)
	{
		reConnection(true);
	}
}
