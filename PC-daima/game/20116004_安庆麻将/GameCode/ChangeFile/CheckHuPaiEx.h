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
///�¼������ࣨ���أ�
class CheckHuPaiEx:public CheckHuPai
{
public:
	CheckHuPaiEx(void);
	~CheckHuPaiEx(void);
	
public:
	int   m_byTingMaxFan ;//���ƿ��ܵ����

	//����ƽ�����Ƶ�����
	int				m_iCanPingHuCardNum;

public:
	
	///����ܷ�����
	virtual bool CanTing(BYTE station,BYTE CanOut[]);
	//����Ƿ��и�
	bool CheckHaveGang(BYTE station);
	//����Ƿ��га�
	int CheckHaveChengBao(BYTE station,BYTE &byBeStation);
	///����������Ҹ�������
	int CountTingGen(BYTE pai[]);
    ///���ƣ�CanHu
    ///��������ϸ������
    ///@param station ���Ƽ��λ�ã�hutype[] �ܺ��Ƶ����ͣ�zimo �Ƿ�����
    ///@return true  �ܺ��� false ����
    virtual bool CanHu(BYTE station,BYTE lastpai,BYTE hutype[],bool zimo);
	///ƽ�����
	virtual bool CheckPingHu(BYTE lastzhuapai=255,bool zimo=false,bool jing=false,bool CheckTing=false);

	///��ȡ�����������
	virtual bool  GetMaxCombination(bool zimo,bool jing,BYTE lastpai = 255);


    bool CheckJiangDui();

	//������
	bool CheckAllJiang();

	///����Ƿ�ȫ����
	bool CheckQuanYao();

	///������Ҹ�������
	int CountGen();
	///�����߶��������Ƶ�����
	int CountLongQi();
	///�����߶��������Ƶ�����
	bool CheckHuGen(BYTE lastpai);

	//����Ƿ��۾��߶�
	bool CheckYaoJiuQiDui();


	//����Ƿ�����
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
