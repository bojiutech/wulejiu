#ifndef __HNLogicBase_H__
#define __HNLogicBase_H__

#include "HNNetExport.h"

namespace HN
{
	static const char* DISCONNECT = "is disConnect";		//����Ͽ���Ϣ
	static const char* RECONNECTION = "reconnection";		//�����ɹ���Ϣ
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