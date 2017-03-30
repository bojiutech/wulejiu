/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #include "stdafx.h"
#include "CheckHuPaiEx.h"

#include "../server/ServerManage.h"

#include<iostream>
#include<cstring>
using namespace std;

CheckHuPaiEx::CheckHuPaiEx(void)
{
	m_byTingMaxFan = 0;//听牌可能的最大番
	m_iMaxFan = -1;
	///玩家是否自摸胡牌
	m_bZimo = false;
}
CheckHuPaiEx::~CheckHuPaiEx(void)
{
}

///描述：检测能否听牌
///@param  handpai[] 手牌数组, pai 最后一张牌, gcpData[] 吃碰杠数组, MainJing 正精, LessJing 副精, CanOut[] 打出后能听牌的牌（可以有多张）
///@return true 能听，false 不能听
bool CheckHuPaiEx::CanTing(BYTE station,BYTE CanOut[])
{
	if(station<0 || station>PLAY_COUNT)
	{
		return false;
	}
	
	//安庆麻将取消听牌
	//return false;

	pDesk->sUserData.m_StrJing.sort();
	m_byStation = station;
	m_byTingMaxFan  = 0;//听牌可能的最大番
	///玩家是否自摸胡牌
	m_bZimo = true;
	memset(CanOut,255,sizeof(CanOut));
	int num=0;
	bool canhu = false;
	for(int i=1;i<40;++i)
	{
		if(i%10 == 0)
		{
			continue;
		}
		memset(m_byArHandPai,255,sizeof(m_byArHandPai));
		for(int j=0;j<HAND_CARD_NUM;j++)
		{
			m_byArHandPai[j] = pDesk->sUserData.m_byArHandPai[station][j];
		}
		for(int j=0;j<HAND_CARD_NUM;j++)
		{
			if(m_byArHandPai[j] == 255)
			{
				m_byArHandPai[j] = i;
				break;
			}
		}
		//从小到大排序
		MaoPaoSort(m_byArHandPai,HAND_CARD_NUM,false);
		///牌数据转换
		ChangeHandPaiData(m_byArHandPai,255);
		m_byJingNum = 0;
			
		bool tmphu = false,bqidui=false;
		int tempFan = 1;
		if(CheckQiDui()>0)//七对
		{
			do
			{
				if(pDesk->sUserData.IsHuaPaiInHand(station))
					break;
				bqidui=true;
				canhu = true;
				tmphu = true;
			}while(false);
			
		}
		else if(CheckQiXingBuKao())
		{
			canhu = true;
			tmphu = true;
		}
		else if(CheckQuanBuKao())
		{
			canhu = true;
			tmphu = true;
		}
		else if(CheckPingHu(255,true,false))//平胡，
		{
			do
			{
				if(pDesk->sUserData.IsHuaPaiInHand(station))
					break;
				CheckPingHuData();//先获取牌组合
				canhu = true;
				tmphu = true;
			}while(false);
		}

		if(tmphu)
		{
			if(tempFan < 1)
			{
				tempFan = 1;
			}
			//获取根数
			int gen = 0;
			if(!bqidui)//七对不算根,2011-11-29
			{
				gen = CountTingGen(m_byArHandPai);
			}
			if(gen>0)
			{
				for(int j=0;j<gen;++j)
				{
					tempFan *= 2;
				}
			}
			//记录最多值
			if(m_byTingMaxFan < tempFan || m_byTingMaxFan==255)
			{
				m_byTingMaxFan = tempFan;
			}
			char strdug[500];
			sprintf(strdug,"算分测试： 位置%d 分 %d 根%d 加入的牌%d  最大分数%d",m_byStation,tempFan,gen,i,m_byTingMaxFan);
			OutputDebugString(strdug);
		}
	}
	if(canhu)
	{
		char strdug[500];
		sprintf(strdug,"算分测试：最终查大叫 位置%d 分 %d ",m_byStation,m_byTingMaxFan);
		OutputDebugString(strdug);
	}

	return canhu;
}

///计算听牌玩家根的数量
int CheckHuPaiEx::CountTingGen(BYTE pai[])
{	
	int count = 0,num=0;
	BYTE data = 255,type=255;
	for(int i=0;i<9;++i)
	{
		for(int j=0;j<3;++j)
		{
			num = 0;
			data = i+1+j*10;
			num = CLogicBase::GetNumInArr(pai,data,17);
			if(pDesk->sUserData.IsUserHaveGangPai(m_byStation,data,type))
			{
				count++;
			}
			else if(pDesk->sUserData.IsUserHavePengPai(m_byStation,data))
			{
				num+=3;
			}
			else
			{
				if(pDesk->sUserData.GetGCPCount(m_byStation) >0)
				{
					num += pDesk->sUserData.GetOnePaiGCPCount(m_byStation,data);
				}
			}
			if(num>=4)
			{
				count++;
			}
		}
	}
	return count;
}

bool CheckHuPaiEx::CheckHaveGang(BYTE station)
{

	if(pDesk->sUserData.m_byArHuaPai[station][0]!=255)
	{
		return true;
	}

	BYTE an,ming,bu;
	if(pDesk->sUserData.GetUserGangNum(station,an,ming,bu)>0)
		return true;

	return false;
}

int CheckHuPaiEx::CheckHaveChengBao(BYTE station,BYTE &byBeStation)
{
	//bool bHaveChengBao = false;

	//判断自己是否是承包方
	for(int i = 0; i < PLAY_COUNT; i++)
	{
		if(i != station && pDesk->sUserData.m_byChengBao[station][i] > 2)
		{
			byBeStation = i;
			return 1;
		}
	}

	//判断自己是否是反包方
	for(int i = 0; i < PLAY_COUNT; i++)
	{
		if(i == station)
			continue;
		//for(int j = 0; j < PLAY_COUNT; j++)
		//{
		if(pDesk->sUserData.m_byChengBao[i][station] > 2)
		{
			byBeStation = i;
			return -1;
		}
		//}
	}
	return 0;
}

///描述：详细检测糊牌
///@param station 糊牌检测位置，hutype[] 能糊牌的类型，zimo 是否自摸
///@return true  能糊， false 不能
bool CheckHuPaiEx::CanHu(BYTE station,BYTE lastpai,BYTE hutype[],bool zimo)
{

// 	if(!CheckHaveGang(station) && !zimo)
// 		return false;
	BYTE byBeSation;
	if(CheckHaveChengBao(station,byBeSation) && !zimo)
	{
		return false;
	}

	//没有花牌和杠牌，此牌型必须自摸，不能被点炮
	if (!zimo)
	{
		BYTE an = 0;
		BYTE ming = 0;
		BYTE bu = 0;
		pDesk->sUserData.GetUserGangNum(station, an, ming, bu);

		if (pDesk->sUserData.m_byArHuaPai[station][0] == 255
			&& (an + ming + bu <= 0)
			/*&& !pDesk->sUserData.GetAHandPaiCount(station, CMjEnum::MJ_TYPE_FB)
			&& !pDesk->sUserData.GetAHandPaiCount(station, CMjEnum::MJ_TYPE_FX)
			&& !pDesk->sUserData.GetAHandPaiCount(station, CMjEnum::MJ_TYPE_FN)*/)
		{
			return false;
		}

	}

	///玩家是否自摸胡牌
	m_bZimo = zimo;
    //最后自摸或点炮的牌
    m_byLastPai = lastpai;
    m_byStation = station;

	m_iCanPingHuCardNum = CanPingHuNum(station,zimo);

    memset(m_byArHandPai,255,sizeof(m_byArHandPai));
    for(int i=0;i<HAND_CARD_NUM;i++)
    {
        m_byArHandPai[i] = pDesk->sUserData.m_byArHandPai[station][i];
        if(pDesk->sUserData.m_byArHandPai[station][i] == 255 && lastpai != 255 && !zimo)
        {
            m_byArHandPai[i] = lastpai;
            break;
        }
    }


    ///从小到大排序
    MaoPaoSort(m_byArHandPai,HAND_CARD_NUM,false);
    bool bb = false;
	bool dahu = false;
    ///牌数据转换
    ChangeHandPaiData(m_byArHandPai,255);
    if(CheckQiDui()>0)        //暗七对
    {
		do
		{
			if(pDesk->sUserData.IsHuaPaiInHand(station))
				break;
			SetAHupaiType(HUPAI_AN_QI_DUI,hutype);//七对
			bb = true;
			dahu = true;
		}while(0);
    }
	else if(CheckQiXingBuKao())
	{
		if(zimo)
		{
			SetAHupaiType(HUPAI_QIXING_BUKAO,hutype);//七星13烂
			bb = true;
			dahu = true;
		}
	}
	else if(CheckQuanBuKao())
	{
		if(zimo)
		{
			SetAHupaiType(HUPAI_QUAN_BUKAO,hutype);//13烂
			bb = true;
			dahu = true;
		}
	}
    else if(CheckPingHu(lastpai,zimo,false))//平糊组牌
    {   
		do
		{
			/*if(pDesk->sUserData.IsHuaPaiInHand(station))
				break;*/

			bb = true;
			bool bHuWay = false;
			CheckPingHuData();//先获取牌组合
			//碰碰胡
			if(CheckPengPengHu())   
			{
				SetAHupaiType(HUPAI_PENG_PENG_HU,hutype);
				dahu = true;
			}
			if(CheckMenQianQing())//门前清
			{
				SetAHupaiType(HUPAI_MEN_QIAN_QING,hutype);
			}
			if(CheckDaDiaoChe(station))//打吊车
			{
				dahu = true;
				SetAHupaiType(HUPAI_DA_DIAOCHE,hutype);
			}
			if(CheckBianPai(lastpai)) //边牌
			{
				bHuWay = true;
				SetAHupaiType(HUPAI_BIAN_PAI,hutype);
			}
			if(CheckKaPa(lastpai))	//卡牌
			{
				if(!bHuWay)
				{
					bHuWay = true;
					SetAHupaiType(HUPAI_KAI_PAI,hutype);
				}
			}
			if(CheckLiangDui(lastpai))//胡两对
			{
				if(!bHuWay)
					SetAHupaiType(HUPAI_LIANG_DUI,hutype);
			}
			if(CheckDianDiao(station,lastpai))//单调将
			{
				SetAHupaiType(HUPAI_DIAN_DIAO,hutype);
			}
			if(CheckThreeNan(station))//三张南风
			{
				SetAHupaiType(HUPAI_THREE_NAN,hutype);
			}
			if(CheckThreeXi(station))//三张西风
			{
				SetAHupaiType(HUPAI_THREE_XI,hutype);
			}
			if(CheckThreeBei(station))//三张北风
			{
				SetAHupaiType(HUPAI_THREE_BEI,hutype);
			}

		}while(false);
    }
    if (bb)
    {
		//没有大胡就是推倒胡
		if(!dahu)
		{
			SetAHupaiType(HUPAI_HU_PAI,hutype);
		}
		//自摸
		if(zimo)
		{
			SetAHupaiType(HUPAI_ZI_MO,hutype);
		}
		//天胡
		if(CheckTianHu())
		{
			SetAHupaiType(HUPAI_TYPE_TIAN_HU,hutype);
		}
		//地胡
		if(CheckDiHu())
		{
			SetAHupaiType(HUPAI_TYPE_DI_HU,hutype);
		}
		// 杠开
        if (CheckGangKai())     
        {
            SetAHupaiType(HUPAI_TYPE_GANG_KAI, hutype);
        }    

		//无花果
		if (CheckNoHua())
		{
			 SetAHupaiType(HUPAI_NO_HUA, hutype);
		}

    }



    return bb;
}

///平糊检测
bool CheckHuPaiEx::CheckPingHu(BYTE lastzhuapai,bool zimo,bool jing,bool CheckTing)
{
	//循环遍历
	TempHupaistruct.Init();
	hupaistruct.Init();
	m_iMaxFan = -1;
	BYTE pai[4]={255};
	bool caishen[4]={0};

	//1个财神的检测,一个财神和一张牌做将  //没有财神的不会进到这里来
	if(m_byJingNum>=1 && m_byJingNum!=255)
	{

		for(int i=0;i<NoJingHuTempData.conut;i++)
		{
			if(NoJingHuTempData.data[i][1]<1 || NoJingHuTempData.data[i][1] == 255 ||NoJingHuTempData.data[i][0]==255)
			{
				continue;
			}
			hupaistruct.Init();//初始化糊牌结构
			NoJingHuTempData.data[i][1]-=1;

			memset(caishen,0,sizeof(caishen));
			memset(pai,255,sizeof(pai));
			pai[0] = pai[1] = NoJingHuTempData.data[i][0];
			caishen[0] = true;
			hupaistruct.AddData(TYPE_JIANG_PAI,pai,caishen);	
			MakePingHu(NoJingHuTempData,hupaistruct,m_byJingNum-1);//胡牌检测递归函数：在递归中完成全部检测
			NoJingHuTempData.data[i][1]+=1;
		}
	}
	//正常牌做的检测,(无精的麻将HuTempData 与 NoJingHuTempData是一样的数据)
	for(int i=0;i<NoJingHuTempData.conut;i++)
	{
		if(NoJingHuTempData.data[i][1]<2 || NoJingHuTempData.data[i][0]==255)
		{
			continue;
		}
		hupaistruct.Init();//初始化糊牌结构
		NoJingHuTempData.data[i][1]-=2;

		memset(caishen,0,sizeof(caishen));
		memset(pai,255,sizeof(pai));
		pai[0] = pai[1] = NoJingHuTempData.data[i][0];
		hupaistruct.AddData(TYPE_JIANG_PAI,pai,caishen);
		MakePingHu(NoJingHuTempData,hupaistruct,m_byJingNum);//胡牌检测递归函数：在递归中完成全部检测
		NoJingHuTempData.data[i][1]+=2;
	}
	if(m_iMaxFan>=0)
	{
		hupaistruct = TempHupaistruct;
		return true;
	}
	return false;
}

///获取最大的组合牌型
bool CheckHuPaiEx:: GetMaxCombination(bool zimo,bool jing,BYTE lastpai)
{
	CheckPingHuData();//先获取牌组合

	ClearHupaiType(m_byHuType);//清除糊牌类型
	int fan = 0;
	bool bMax =  false;//是否存在更大的牌型

    if(CheckQingYiSe())    //清一色
    {
		fan = 4;
    }
    if(CheckQuanDaiYao())  //全带幺  
    {
		if(CheckQingYiSe())//清一色
		{
			fan = 16;//清带幺 5 番 16分
		}
		else
		{
			fan = 4;
		}
    }
	if(CheckPengPengHu())   //大对子
	{
		if (CheckQingYiSe())    //清对
		{
			fan = 8;
		}
		else if (CheckJiangDui())   //将对
		{
			fan = 8;
		}
		else
		{
			fan += 2;
		}
	}


	if(fan>m_iMaxFan)
	{
		m_iMaxFan = fan;
		bMax =  true;   
	}
	if(bMax)
	{
		TempHupaistruct = hupaistruct;//记录最大牌型
	}
	return bMax;
}

//将将胡
bool	CheckHuPaiEx::CheckAllJiang()
{
	for(int i=0;i<hupaistruct.count;++i)
	{
		if(hupaistruct.data[i][0]%10 != 2 && hupaistruct.data[i][0]%10 != 5 && hupaistruct.data[i][0]%10 != 8)
		{
			return false;
		}
	}
	for(int i=0;i<5;i++)
	{
		if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byType == 255)
			continue;
		BYTE pai =255;
		pai = pDesk->sUserData.m_UserGCPData[m_byStation][i].byData[0];
		switch(pDesk->sUserData.m_UserGCPData[m_byStation][i].byType)
		{
		case AT_COLLECT://吃牌动作
			{
				return false;
				break;
			}
		case AT_TRIPLET:
		case AT_QUADRUPLET:
		case AT_QUADRUPLET_CONCEALED:
		case AT_QUADRUPLET_REVEALED:
			{
				if(pai %10 != 2 && pai %10 != 5 && pai %10 != 8)
				{
					return false;
				}
			}
			break;
		}
	}
	return true;
}

//检测将对（258碰碰胡）
bool CheckHuPaiEx::CheckJiangDui()
{
	for(int i=0;i<hupaistruct.count;++i)
	{
		if(hupaistruct.byType[i] == TYPE_SHUN_ZI)//顺子
		{
			return false;
		}
		if(hupaistruct.data[i][0]%10 != 2 && hupaistruct.data[i][0]%10 != 5 && hupaistruct.data[i][0]%10 != 8)
		{
			return false;
		}
	}
	for(int i=0;i<5;i++)
	{
		if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byType == 255)
			continue;
		BYTE pai =255;
		pai = pDesk->sUserData.m_UserGCPData[m_byStation][i].byData[0];
		switch(pDesk->sUserData.m_UserGCPData[m_byStation][i].byType)
		{
		case ACTION_CHI://吃牌动作
			{
				return false;
			}
			break;
		case AT_QUADRUPLET:
		case AT_QUADRUPLET_CONCEALED:
		case AT_QUADRUPLET_REVEALED:
		case ACTION_PENG:
			{
				if(pai %10 != 2 && pai %10 != 5 && pai %10 != 8)
				{
					return false;
				}
			}
			break;
		}
	}
    return true;
}

///检测是否全幺牌
bool CheckHuPaiEx::CheckQuanYao()
{
	if(pDesk->sUserData.GetGCPCount(m_byStation) > 0)
		return false;
    for(int i=0;i<HAND_CARD_NUM;i++)
    {
		if(m_byArHandPai[i] == 255 )
			continue;
		if( m_byArHandPai[i] > CMjEnum::MJ_TYPE_B9 || (m_byArHandPai[i]%10 != 1 && m_byArHandPai[i]%10 != 9))
			return false;
    }
	return true;
}

///计算玩家根的数量
int CheckHuPaiEx::CountGen()
{	
	int count = 0,num=0;
	BYTE pai = 255;
	char strdug[500];
	for(int i=0;i<9;++i)
	{
		for(int j=0;j<3;++j)
		{
			num = 0;
			pai = i+1+j*10;
			num += HuTempData.GetPaiCount(pai);
			num += pDesk->sUserData.GetOnePaiGCPCount(m_byStation,pai);
			if(num>=4)
			{
				count++;
			}
		}
	}
	return count;
}

///计算七对中四张牌的数量
int CheckHuPaiEx::CountLongQi()
{	
	int count = 0;
	for(int i=0;i<HuTempData.conut;++i)
	{
		if(HuTempData.data[i][0] == 255 || HuTempData.data[i][1] < 4 || HuTempData.data[i][1] == 255)
			continue;
		count++;
	}
	return count;
}

///计算七对中四张牌的数量
bool CheckHuPaiEx::CheckHuGen(BYTE lastpai)
{	
	if(lastpai == 255)
		return false;
	if(CLogicBase::GetNumInArr(m_byArHandPai,lastpai ,HAND_CARD_NUM) >= 4)
		return true;
	return false;
}

//检测是否幺九七对 8 
bool CheckHuPaiEx::CheckYaoJiuQiDui()
{
	if(CheckQiDui() <= 0)
		return false;
	for(int i=0;i<HuTempData.conut;++i)
	{
		if(HuTempData.data[i][0] == 255)
			continue;
		if(HuTempData.data[i][0] %10 != 1 && HuTempData.data[i][0] %10 != 9)
			return false;
	}
	return true;
}

bool CheckHuPaiEx::CheckDaDiaoChe(BYTE station)
{
	int nCount = pDesk->sUserData.GetGCPCount(station);
	if(nCount == 4)
		return true;

	return false;
}

bool CheckHuPaiEx::CheckBianPai(BYTE pai)
{
	bool bb = false;
	for(int i = 0; i < hupaistruct.count; i++)
	{
		if(hupaistruct.byType[i] == TYPE_SHUN_ZI)
		{
			if(hupaistruct.data[i][0] == pai && hupaistruct.data[i][0] %10 == 7)
			{
				bb = true;
				break;
			}

			if(hupaistruct.data[i][2] == pai && hupaistruct.data[i][2] %10 == 3)
			{
				bb = true;
				break;
			}
		}
	}

	if (!bb)
	{
		return false;
	}


 	CString str;
 	str.Format("chenlog----------边牌检测  玩家可糊牌数量  %d",m_iCanPingHuCardNum);
 	OutputDebugString(str);

	if (m_iCanPingHuCardNum >=2)
	{
		return false;
	}

	for(int i = 0; i < hupaistruct.count; i++)
	{
		if(hupaistruct.byType[i] == TYPE_JIANG_PAI && hupaistruct.data[i][0] == pai)
		{
			bb = false;
			break;
		}
		if(hupaistruct.byType[i] == TYPE_AN_KE && hupaistruct.data[i][0] == pai)
		{
			bb = false;
			break;
		}
		if(hupaistruct.byType[i] == TYPE_SHUN_ZI && (hupaistruct.data[i][0] == pai && pai % 10 != 7))
		{
			bb = false;
			break;
		}
		if(hupaistruct.byType[i] == TYPE_SHUN_ZI && (hupaistruct.data[i][2] == pai && pai % 10 != 3))
		{
			bb = false;
			break;
		}
	}
	return bb;
}

bool CheckHuPaiEx::CheckKaPa(BYTE pai)
{
	bool bb = false;
	for(int i = 0; i < hupaistruct.count; i++)
	{
		if(hupaistruct.byType[i] == TYPE_SHUN_ZI)
		{
			if(hupaistruct.data[i][1] == pai)
			{
				bb = true;
				break;
			}
		}
	}

 	CString str;
 	str.Format("chenlog----------卡牌检测  玩家可糊牌数量  %d",m_iCanPingHuCardNum);
 	OutputDebugString(str);


	if (m_iCanPingHuCardNum >=2)
	{
		return false;
	}

	bool bFlag1 = false;
	bool bFlag2 = false;
	for(int i = 0; i < hupaistruct.count; i++)
	{
// 		if(hupaistruct.byType[i] == TYPE_JIANG_PAI && hupaistruct.data[i][0] == pai)
// 		{
// 			bb = false;
// 			break;
// 		}

		if(hupaistruct.byType[i] == TYPE_JIANG_PAI && hupaistruct.data[i][0] == pai-1)
		{
			bFlag1 = true;
		}

		if(hupaistruct.byType[i] == TYPE_JIANG_PAI && hupaistruct.data[i][0] == pai+1)
		{
			bFlag2 = true;
		}

		if(hupaistruct.byType[i] == TYPE_AN_KE && hupaistruct.data[i][0] == pai)
		{
			bb = false;
			break;
		}
		if(hupaistruct.byType[i] == TYPE_SHUN_ZI && (hupaistruct.data[i][0] == pai || hupaistruct.data[i][2] == pai))
		{
			bb = false;
			break;
		}
	}

	if(pDesk->sUserData.GetAHandPaiCount(m_byStation,pai-1)>2 && bFlag1)
		return false;

	if(pDesk->sUserData.GetAHandPaiCount(m_byStation,pai+1)>2 && bFlag2)
		return false;

	return bb;
}
bool CheckHuPaiEx::CheckDianDiao(BYTE station,BYTE pai)
{
	if(hupaistruct.count < 2)
		return false;
	if(pDesk->sUserData.GetAHandPaiCount(station,pai)>=2)
		return false;

	if (m_iCanPingHuCardNum >=2)
	{
		return false;
	}

	bool bFlag1 = false;
	bool bFlag2 = false;

	for(int i = 0; i < hupaistruct.count; i++)
	{
		if(hupaistruct.byType[i] == TYPE_JIANG_PAI && hupaistruct.data[i][0] == pai)
			break;
		else if(hupaistruct.byType[i] == TYPE_JIANG_PAI && hupaistruct.data[i][0] != pai)
			return false;

		else if(hupaistruct.byType[i] == TYPE_SHUN_ZI)
		{
			if(pai == hupaistruct.data[i][0] +1 || pai == hupaistruct.data[i][2] - 1)
				return false;
		}
	}

	return true;
}
bool CheckHuPaiEx::CheckLiangDui(BYTE pai)
{
	bool bb = false;

	if (m_iCanPingHuCardNum >=3)
	{
		return false;
	}

	for(int i = 0; i < hupaistruct.count; i++)
	{
		if(hupaistruct.byType[i] == TYPE_AN_KE)
		{
			if(hupaistruct.data[i][0] == pai)
			{
				bb = true;
				break;
			}
		}
	}

	for(int i = 0; i < hupaistruct.count; i++)
	{
		if(hupaistruct.byType[i] == TYPE_SHUN_ZI && (hupaistruct.data[i][0] == pai && pai % 10 != 7))
		{
			bb = false;
			break;
		}

		if(hupaistruct.byType[i] == TYPE_SHUN_ZI && (hupaistruct.data[i][2] == pai && pai % 10 != 3))
		{
			bb = false;
			break;
		}
	}
	return bb;
}

bool CheckHuPaiEx::CheckThreeNan(BYTE station)
{
	for(int i = 0; i < hupaistruct.count; i++)
	{
		if(hupaistruct.byType[i] == TYPE_AN_KE)
		{
			if(hupaistruct.data[i][0] == CMjEnum::MJ_TYPE_FN)
				return true;
		}
	}

	for(int i=0;i<5;i++)
	{
		if(pDesk->sUserData.m_UserGCPData[station][i].byType == AT_TRIPLET)
		{
			if(pDesk->sUserData.m_UserGCPData[station][i].byData[0] == CMjEnum::MJ_TYPE_FN)
			{
				return true;
			}
		}
	}
	return false;
}

bool CheckHuPaiEx::CheckThreeXi(BYTE station)
{
	for(int i = 0; i < hupaistruct.count; i++)
	{
		if(hupaistruct.byType[i] == TYPE_AN_KE)
		{
			if(hupaistruct.data[i][0] == CMjEnum::MJ_TYPE_FX)
				return true;
		}
	}
	for(int i=0;i<5;i++)
	{
		if(pDesk->sUserData.m_UserGCPData[station][i].byType == AT_TRIPLET)
		{
			if(pDesk->sUserData.m_UserGCPData[station][i].byData[0] == CMjEnum::MJ_TYPE_FX)
			{
				return true;
			}
		}
	}
	return false;
}

bool CheckHuPaiEx::CheckNoHua()
{
	BYTE an = 0;
	BYTE ming = 0;
	BYTE bu = 0;
	pDesk->sUserData.GetUserGangNum(m_byStation,an,ming,bu);
	pDesk->sUserData.GetUserGangNum(m_byStation,an,ming,bu);

	if(pDesk->sUserData.m_byArHuaPai[m_byStation][0] == 255
		&& (an + ming+bu <= 0)
		&&!pDesk->sUserData.GetAHandPaiCount(m_byStation,CMjEnum::MJ_TYPE_FB)
		&&!pDesk->sUserData.GetAHandPaiCount(m_byStation,CMjEnum::MJ_TYPE_FX)
		&&!pDesk->sUserData.GetAHandPaiCount(m_byStation,CMjEnum::MJ_TYPE_FN)
		)
	{
		return true;
	}

	return false;
}

bool CheckHuPaiEx::CheckThreeBei(BYTE station)
{
	for(int i = 0; i < hupaistruct.count; i++)
	{
		if(hupaistruct.byType[i] == TYPE_AN_KE)
		{
			if(hupaistruct.data[i][0] == CMjEnum::MJ_TYPE_FB)
				return true;
		}
	}

	for(int i=0;i<5;i++)
	{
		if(pDesk->sUserData.m_UserGCPData[station][i].byType == AT_TRIPLET)
		{
			if(pDesk->sUserData.m_UserGCPData[station][i].byData[0] == CMjEnum::MJ_TYPE_FB)
			{
				return true;
			}
		}
	}
	return false;
}

bool CheckHuPaiEx::CheckHaveMingGang(BYTE station)
{
	for(int i=0;i<5;i++)
	{
		if(pDesk->sUserData.m_UserGCPData[station][i].byType == AT_QUADRUPLET || pDesk->sUserData.m_UserGCPData[station][i].byType == AT_QUADRUPLET_REVEALED)
		{
			return true;
		}
	}
	return false;
}

bool CheckHuPaiEx::CheckHaveAnGang(BYTE station)
{
	for(int i=0;i<5;i++)
	{
		if(pDesk->sUserData.m_UserGCPData[station][i].byType == AT_QUADRUPLET_CONCEALED && pDesk->sUserData.m_UserGCPData[station][i].byData[0] < CMjEnum::MJ_TYPE_FD)
		{
			return true;
		}
	}
	return false;
}

bool CheckHuPaiEx::CheckHaveHuaGang(BYTE station)
{
	if(pDesk->sUserData.GetAHuaCount(station,CMjEnum::MJ_TYPE_FD)>3)
	{
		return true;
	}

	if(pDesk->sUserData.GetAHuaCount(station,CMjEnum::MJ_TYPE_ZHONG)>3)
	{
		return true;
	}

	if(pDesk->sUserData.GetAHuaCount(station,CMjEnum::MJ_TYPE_FA)>3)
	{
		return true;
	}

	if(pDesk->sUserData.GetAHuaCount(station,CMjEnum::MJ_TYPE_BAI)>3)
	{
		return true;
	}

	return false;
}

bool CheckHuPaiEx::CheckHaveFengGang(BYTE station)
{
	for(int i=0;i<5;i++)
	{
		if(pDesk->sUserData.m_UserGCPData[station][i].byType == AT_QUADRUPLET_CONCEALED && pDesk->sUserData.m_UserGCPData[station][i].byData[0] > CMjEnum::MJ_TYPE_FD)
		{
			return true;
		}
	}
	return false;
}

//全不靠：由单张3种花色147、258、369不能错位的序数牌及东南西北中发白中的任何14张牌组成的和牌（十三烂）。不计五门齐、不求人、单钓(非平糊类型)
bool CheckHuPaiEx::CheckQuanBuKao()
{
	BYTE num=0;
	for(int i=0;i<5;++i)
	{
		if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byType == 255)
			continue;
		num++;
	}
	if(num>0)//不能有吃碰杠
	{
		return false;
	}
	BYTE pai = 255;
	for(int i=0;i<HuTempData.conut;++i)
	{
		if(HuTempData.data[i][1]>1)
			return false;
		if(HuTempData.data[i][0]>=CMjEnum::MJ_TYPE_FD)
		{
			continue;
		}

		if(pai == 255 || pai/10!=HuTempData.data[i][0]/10)
		{
			pai = HuTempData.data[i][0];
			continue;
		}

		if((HuTempData.data[i][0]-pai)<3)
		{
			return false;
		}

		pai = HuTempData.data[i][0];
	}
	return true;
}


int  CheckHuPaiEx::CanPingHuNum(BYTE station,bool bzimo)
{
	int iNum= 0;
	for(int j=1;j<40;++j)
	{
		if(j%10 == 0)
		{
			continue;
		}

		memset(m_byArHandPai,255,sizeof(m_byArHandPai));
// 		for(int i=0;i<HAND_CARD_NUM;i++)
// 		{
// 			m_byArHandPai[i] = pDesk->sUserData.m_byArHandPai[station][i];
// 			if(pDesk->sUserData.m_byArHandPai[station][i] == 255 && j != 255 )
// 			{
// 				m_byArHandPai[i] = j;
// 				break;
// 			}
// 		}



		for(int i=0;i<HAND_CARD_NUM;i++)
		{
			m_byArHandPai[i] = pDesk->sUserData.m_byArHandPai[station][i];
		}

		if (bzimo)
		{
			for(int i=0;i<HAND_CARD_NUM;i++)
			{
				if (m_byArHandPai[i] == m_byLastPai)
				{
					m_byArHandPai[i] = 255;
					break;
				}
			}
		}


		for(int i=0;i<HAND_CARD_NUM;i++)
		{
			if(m_byArHandPai[i] == 255)
			{
				m_byArHandPai[i] = j;
				break;
			}
		}

		//从小到大排序
		MaoPaoSort(m_byArHandPai,HAND_CARD_NUM,false);
		///牌数据转换
		ChangeHandPaiData(m_byArHandPai,255);
		if (CheckPingHu(j,bzimo,false))
		{
			iNum++;
		}
	}
	return iNum;
}