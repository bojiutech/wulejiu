/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#ifndef __NH_HNThread_H__
#define __NH_HNThread_H__

#include <functional>
#include <thread>

namespace HN 
{
	typedef std::function<void(void* pragma)> HNThreadFunc;

	class HNThread
	{
	public:
		HNThread(void);
		virtual ~HNThread(void);

	public:
		void start();
		void stop();
		virtual void onExecute();

	protected:	
		bool need_quit;

	private:
		void socketWorkThread();

	private:
		std::thread* _thread;
		HNThreadFunc _func;
	};

};

#endif		//__NH_HNThread_H__