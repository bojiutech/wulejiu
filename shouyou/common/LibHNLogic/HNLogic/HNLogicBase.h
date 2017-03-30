#ifndef __HNLogicBase_H__
#define __HNLogicBase_H__

#include "HNNetExport.h"

namespace HN
{
	static const char* DISCONNECT = "is disConnect";		//网络断开消息
	static const char* RECONNECTION = "reconnection";		//重连成功消息
	/*
	 * redbird logic base.
	 */
	class HNLogicBase
	{
	public:
		virtual void start();
		virtual void stop();
	protected:
		HNLogicBase();
		virtual ~HNLogicBase();
	};
}

#endif