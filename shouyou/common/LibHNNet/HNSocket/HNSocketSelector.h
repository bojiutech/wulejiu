/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#ifndef __HN_HNSocketSelector_H__
#define __HN_HNSocketSelector_H__

#include "HNCommon/HNCommonMarco.h"
#include "HNSocketMessage.h"
#include <unordered_map>

namespace HN
{

	template <class KEY>
	class HNSocketSelector
	{
		typedef typename std::unordered_map<KEY, HNSocketSelectorItem> SOCKET_OBSERVERS;
		typedef typename std::unordered_map<KEY, HNSocketSelectorItem>::iterator ITERATOR;

	public:
		HNSocketSelector()
		{
		}

		~HNSocketSelector()
		{
			clear();
		}

	public:
		void addSelector(KEY key, SEL_SocketMessage selector)
		{
			HN_ASSERT(nullptr != selector, "selector is nullptr");
			if (nullptr == selector) return;

			auto tmp = _observers.find(key);
			if (tmp != _observers.end())
			{
				tmp->second = selector;
			}
			else
			{
				_observers.insert(std::make_pair(key, HNSocketSelectorItem(selector)));
			}
		}

		void removeSelector(KEY key)
		{
			auto selector = _observers.find(key);
			if (selector != _observers.end())
			{
				_observers.erase(key);
			}
		}

		bool executeSelector(KEY key, HNSocketMessage* socketMessage)
		{
			auto selector = _observers.find(key);
			if (selector != _observers.end())
			{
				selector->second.doCallSelector(socketMessage);
				return true;
			}
			return false;
		}

		ITERATOR begin()
		{
			return _observers.begin();
		}

		ITERATOR end()
		{
			return _observers.end();
		}

		bool empty()
		{
			return _observers.empty();
		}

		void clear() 
		{
			_observers.clear();
		}
	private:
		SOCKET_OBSERVERS _observers;
	};
}

#endif	//__HN_HNSocketSelector_H__

