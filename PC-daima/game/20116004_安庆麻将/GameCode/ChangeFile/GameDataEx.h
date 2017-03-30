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

///��Ϸ���ݹ�����
class GameDataEx: public GameData
{
public:
	GameDataEx(void);
	~GameDataEx(void);
public:
	///�齫ʱ��ȴ���ʱ�䵽�˷�������Ϊ����
	MJ_WaitTimeEx   m_MjWait;
	BYTE m_byLianGang;
	BYTE m_byGangHua;
	//BYTE m_byNowOutStation;
public:
	///���������¼��ĺ���¼�
	virtual void SetThingNext();
	///����ĳ���¼��ĺ���¼�
	virtual void SetThingNext(BYTE id);
	//virtual ��ʼ������
	virtual void InitData();
	///��ʼ������
	virtual void LoadIni();

};

//ȫ�ֶ���
extern GameDataEx g_GameData;