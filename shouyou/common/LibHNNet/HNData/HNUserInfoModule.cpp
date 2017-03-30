#include "HNUserInfoModule.h"
#include "HNCommon/HNCommonMarco.h"
#include <algorithm>
#include <iterator>

namespace HN
{
	HNUserInfoModule* HNUserInfoModule::getInstance()
	{
		static HNUserInfoModule sUserModule;
		return &sUserModule;
	}

	HNUserInfoModule::HNUserInfoModule(void)
	{
		_onlineUsers = new USERLIST();
		_dataChangedQueue = new std::vector<IUserInfoChangedEvent*>();
	}

	HNUserInfoModule::~HNUserInfoModule(void)
	{
		clear();
		HN_SAFE_DELETE(_onlineUsers);
		HN_SAFE_DELETE(_dataChangedQueue);
	}

	void HNUserInfoModule::addObserver(IUserInfoChangedEvent* delegate)
	{
		_dataChangedQueue->push_back(delegate);
	}

	void HNUserInfoModule::removeObserver(IUserInfoChangedEvent* delegate)
	{
		_dataChangedQueue->erase(std::remove(_dataChangedQueue->begin(), _dataChangedQueue->end(), delegate));
	}

	void HNUserInfoModule::clear()
	{
		for (auto iter = _onlineUsers->begin(); iter != _onlineUsers->end(); ++iter)
		{
			HN_SAFE_DELETE(*iter);
		}
		_onlineUsers->clear();
		onNotify(nullptr, IUserInfoChangedEvent::CLEAR);
	}

	const UserInfoStruct* HNUserInfoModule::addUser(UserInfoStruct* user)
	{
		if (user == nullptr || user->dwUserID == INVALID_USER_ID)
		{
			return nullptr;
		}

		const UserInfoStruct* pUserInfo = findUser(user->dwUserID);
		if (pUserInfo != nullptr)
		{
			return nullptr;
		}

		UserInfoStruct * newUser = new UserInfoStruct;
		*newUser = *user;
		_onlineUsers->push_back(newUser);
		onNotify(newUser, IUserInfoChangedEvent::ADD);
		return newUser;
	}

	bool HNUserInfoModule::removeUser(INT userID)
	{
		for (auto iter = _onlineUsers->begin(); iter != _onlineUsers->end(); ++iter)
		{
			if (userID == (*iter)->dwUserID)
			{
				onNotify(*iter, IUserInfoChangedEvent::REMOVE);
				HN_SAFE_DELETE(*iter);
				_onlineUsers->erase(iter);
				return true;
			}
		}
		return false;
	}

	const UserInfoStruct* HNUserInfoModule::findUser(INT userID)
	{
		UserInfoStruct* user = nullptr;
		for (auto iter = _onlineUsers->begin(); iter != _onlineUsers->end(); ++iter)
		{
			if (userID == (*iter)->dwUserID)
			{
				user = *iter;
				break;
			}
		}
		return user;
	}

	UserInfoStruct* HNUserInfoModule::getUser(INT userId)
	{
		UserInfoStruct* user = nullptr;
		for (auto iter = _onlineUsers->begin(); iter != _onlineUsers->end(); ++iter)
		{
			if (userId == (*iter)->dwUserID)
			{
				user = *iter;
				break;
			}
		}
		return user;
	}

	const UserInfoStruct* HNUserInfoModule::findUser(BYTE deskNo, BYTE station)
	{
		std::vector<UserInfoStruct*> tmpUsers;
		findDeskUsers(deskNo, tmpUsers);
		UserInfoStruct* user = nullptr;
		for (auto iter = tmpUsers.begin(); iter != tmpUsers.end(); ++iter)
		{
			if (station == (*iter)->bDeskStation)
			{
				user = *iter;
				break;
			}
		}
		return user;
	}

	void HNUserInfoModule::updateUser(UserInfoStruct* user)
	{
		UserInfoStruct* oldUser = getUser(user->dwUserID);
		if (nullptr != oldUser)
		{
			*oldUser = *user;
			onNotify(oldUser, IUserInfoChangedEvent::UPDATE);
		}
		else
		{
			addUser(user);
		}
	}

	void HNUserInfoModule::findDeskUsers(BYTE bDeskNO, std::vector<UserInfoStruct*>& users)
	{
		{
			std::vector<UserInfoStruct*>().swap(users);
		}

		std::copy_if(_onlineUsers->begin(), _onlineUsers->end(), std::inserter(users, users.begin()), 
			[&bDeskNO](UserInfoStruct* user) -> bool
		{
			return (bDeskNO == user->bDeskNO) && (user->bUserState != USER_WATCH_GAME) && (user->bUserState != USER_LOOK_STATE);
		});
	}

	void HNUserInfoModule::findLooker(BYTE deskNO, std::vector<UserInfoStruct*>& users)
	{
		{
			std::vector<UserInfoStruct*>().swap(users);
		}
		
		std::copy_if(_onlineUsers->begin(), _onlineUsers->end(), std::back_inserter(users), 
			[deskNO](UserInfoStruct* user) -> bool
			{
				return deskNO == user->bDeskNO && user->bUserState == USER_WATCH_GAME;
			});
	}

	// 获取游戏玩家
	void HNUserInfoModule::findGameUsers(BYTE deskNO, std::vector<UserInfoStruct*>& users)
	{
		{
			std::vector<UserInfoStruct*>().swap(users);
		}

		std::copy_if(_onlineUsers->begin(), _onlineUsers->end(), std::back_inserter(users), 
			[deskNO](UserInfoStruct* user) -> bool
			{
				return (
						(deskNO == user->bDeskNO) 
						&& ((user->bUserState == USER_SITTING) || (user->bUserState == USER_PLAY_GAME) || (user->bUserState == USER_ARGEE)));
			});
	}

	void HNUserInfoModule::onNotify(UserInfoStruct* user, IUserInfoChangedEvent::COMMAND command)
	{
		for (auto iter = _dataChangedQueue->begin(); iter != _dataChangedQueue->end(); ++iter)
		{
			(*iter)->onChanged(user, command);
		}
	}

	void HNUserInfoModule::transform(const TransformUserFunc& func)
	{
		INT index = 0;
		for (auto iter = _onlineUsers->begin(); iter != _onlineUsers->end(); ++iter, ++index)
		{
			func(*iter, index);
		}
	}

	void HNUserInfoModule::transform(BYTE deskNO, const TransformUserFunc& func)
	{
		INT index = 0;
		for (auto iter = _onlineUsers->begin(); iter != _onlineUsers->end(); ++iter, ++index)
		{
			if (deskNO == (*iter)->bDeskNO)
			{
				func(*iter, index);
			}
		}
	}
}
