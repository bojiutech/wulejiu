/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #pragma once
#include "../GameMessage/GameData.h"

///游戏数据管理类
class GameDataEx: public GameData
{
public:
	GameDataEx(void);
	~GameDataEx(void);
public:
	///麻将时间等待：时间到了服务器代为处理
	MJ_WaitTimeEx   m_MjWait;
	BYTE m_byLianGang;
	BYTE m_byGangHua;
	//BYTE m_byNowOutStation;
public:
	///设置所有事件的后接事件
	virtual void SetThingNext();
	///设置某个事件的后接事件
	virtual void SetThingNext(BYTE id);
	//virtual 初始化数据
	virtual void InitData();
	///初始化数据
	virtual void LoadIni();

};

//全局对象
extern GameDataEx g_GameData;