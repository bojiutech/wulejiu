/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #pragma once

#include "../GameMessage/CheckHuPai.h"
///事件处理类（重载）
class CheckHuPaiEx:public CheckHuPai
{
public:
	CheckHuPaiEx(void);
	~CheckHuPaiEx(void);
	
public:
	int   m_byTingMaxFan ;//听牌可能的最大番

	//可以平胡的牌的张数
	int				m_iCanPingHuCardNum;

public:
	
	///检测能否听牌
	virtual bool CanTing(BYTE station,BYTE CanOut[]);
	//检查是否有杠
	bool CheckHaveGang(BYTE station);
	//检查是否有承包
	int CheckHaveChengBao(BYTE station,BYTE &byBeStation);
	///计算听牌玩家根的数量
	int CountTingGen(BYTE pai[]);
    ///名称：CanHu
    ///描述：详细检测糊牌
    ///@param station 糊牌检测位置，hutype[] 能糊牌的类型，zimo 是否自摸
    ///@return true  能糊， false 不能
    virtual bool CanHu(BYTE station,BYTE lastpai,BYTE hutype[],bool zimo);
	///平糊检测
	virtual bool CheckPingHu(BYTE lastzhuapai=255,bool zimo=false,bool jing=false,bool CheckTing=false);

	///获取最大的组合牌型
	virtual bool  GetMaxCombination(bool zimo,bool jing,BYTE lastpai = 255);


    bool CheckJiangDui();

	//将将胡
	bool CheckAllJiang();

	///检测是否全幺牌
	bool CheckQuanYao();

	///计算玩家根的数量
	int CountGen();
	///计算七对中四张牌的数量
	int CountLongQi();
	///计算七对中四张牌的数量
	bool CheckHuGen(BYTE lastpai);

	//检测是否幺九七对
	bool CheckYaoJiuQiDui();


	//检测是否打吊车
	bool CheckDaDiaoChe(BYTE byStation);

	bool CheckBianPai(BYTE pai);

	bool CheckKaPa(BYTE pai);

	bool CheckLiangDui(BYTE pai);
	bool CheckDianDiao(BYTE station,BYTE pai);
	bool CheckThreeNan(BYTE station);
	bool CheckThreeXi(BYTE station);
	bool CheckThreeBei(BYTE station);
	bool CheckHaveMingGang(BYTE station);
	bool CheckHaveAnGang(BYTE station);
	bool CheckHaveHuaGang(BYTE station);
	bool CheckHaveFengGang(BYTE station);

	bool CheckQuanBuKao();

	bool CheckNoHua();

	int  CanPingHuNum(BYTE station,bool bzimo);
};
