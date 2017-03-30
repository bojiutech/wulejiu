/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#ifndef __NH_HNSocketMessageDelegate_H__
#define __NH_HNSocketMessageDelegate_H__

#include "HNBaseType.h"
#include "HNNetProtocol/HNProtocolExport.h"
#include "HNSocketMessage.h"

namespace HN 
{

	class ISocketEventDelegate
	{
	public:
		virtual ~ISocketEventDelegate() {}
		//virtual void onReadSocketData(HNSocketMessage* socketMessage) = 0;
		virtual void onReadComplete() = 0;
		//virtual void onConnected(bool connect, emSocketStatus status) = 0;
		//virtual void onDisConnect() = 0;
	};

}

#endif	//__NH_HNSocketMessageDelegate_H__
