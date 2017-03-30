﻿/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#include "HNSocketMessage.h"
#include "HNCommon/HNLog.h"
#include "HNCommon/HNMemoryPool.h"

namespace HN 
{
	//////////////////////////////////////////////////////////////////////////
	HNMemPool gMemPool(sizeof(HNSocketMessage), 32, 1024);

	HNSocketMessage* HNSocketMessage::getMessage()
	{
		return new HNSocketMessage();
	}

	void HNSocketMessage::releaseMessage(HNSocketMessage* message)
	{
		HN_SAFE_DELETE(message);
	}

	HNSocketMessage::HNSocketMessage() : objectSize(0), socketStatus(SocketStatus_UNKNOW)
	{
		::memset(object, 0x0, sizeof(object));
		::memset(&messageHead, 0x0, sizeof(object));
	}

	HNSocketMessage::~HNSocketMessage()
	{

	}

	void *HNSocketMessage::operator new(std::size_t ObjectSize)
	{
		return gMemPool.get();
	}

	void HNSocketMessage::operator delete(void *ptrObject)
	{
		gMemPool.release(ptrObject);
	}

	void HNSocketMessage::setMessage(const NetMessageHead* head, CHAR* obj, INT Size)
	{
		messageHead = *head;
		objectSize = Size;
		memcpy(object, obj, objectSize);
		CHAR buf[16] = {0};
		sprintf(buf, "%u_%u", messageHead.bMainID, messageHead.bAssistantID);
		strKey.assign(buf);
	}
}
