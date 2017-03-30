/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#include "HNThread.h"
#include <thread>

namespace HN 
{
	HNThread::HNThread(void) : need_quit(false)
	{
	}

	HNThread::~HNThread(void)
	{
	}

	void HNThread::start() 
	{
		auto t = std::thread(std::bind(&HNThread::socketWorkThread, this));
		//t.join();
		t.detach();
	}

	void HNThread::stop() 
	{
		need_quit = true;
	}

	void HNThread::socketWorkThread()
	{
		onExecute();
	}

	void HNThread::onExecute()
	{

	}

}