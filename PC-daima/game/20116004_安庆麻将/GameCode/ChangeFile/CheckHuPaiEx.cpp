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
	m_byTingMaxFan = 0;//���ƿ��ܵ����
	m_iMaxFan = -1;
	///����Ƿ���������
	m_bZimo = false;
}
CheckHuPaiEx::~CheckHuPaiEx(void)
{
}

///����������ܷ�����
///@param  handpai[] ��������, pai ���һ����, gcpData[] ����������, MainJing ����, LessJing ����, CanOut[] ����������Ƶ��ƣ������ж��ţ�
///@return true ������false ������
bool CheckHuPaiEx::CanTing(BYTE station,BYTE CanOut[])
{
	if(station<0 || station>PLAY_COUNT)
	{
		return false;
	}
	
	//�����齫ȡ������
	//return false;

	pDesk->sUserData.m_StrJing.sort();
	m_byStation = station;
	m_byTingMaxFan  = 0;//���ƿ��ܵ����
	///����Ƿ���������
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
		//��С��������
		MaoPaoSort(m_byArHandPai,HAND_CARD_NUM,false);
		///������ת��
		ChangeHandPaiData(m_byArHandPai,255);
		m_byJingNum = 0;
			
		bool tmphu = false,bqidui=false;
		int tempFan = 1;
		if(CheckQiDui()>0)//�߶�
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
		else if(CheckPingHu(255,true,false))//ƽ����
		{
			do
			{
				if(pDesk->sUserData.IsHuaPaiInHand(station))
					break;
				CheckPingHuData();//�Ȼ�ȡ�����
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
			//��ȡ����
			int gen = 0;
			if(!bqidui)//�߶Բ����,2011-11-29
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
			//��¼���ֵ
			if(m_byTingMaxFan < tempFan || m_byTingMaxFan==255)
			{
				m_byTingMaxFan = tempFan;
			}
			char strdug[500];
			sprintf(strdug,"��ֲ��ԣ� λ��%d �� %d ��%d �������%d  ������%d",m_byStation,tempFan,gen,i,m_byTingMaxFan);
			OutputDebugString(strdug);
		}
	}
	if(canhu)
	{
		char strdug[500];
		sprintf(strdug,"��ֲ��ԣ����ղ��� λ��%d �� %d ",m_byStation,m_byTingMaxFan);
		OutputDebugString(strdug);
	}

	return canhu;
}

///����������Ҹ�������
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

	//�ж��Լ��Ƿ��ǳа���
	for(int i = 0; i < PLAY_COUNT; i++)
	{
		if(i != station && pDesk->sUserData.m_byChengBao[station][i] > 2)
		{
			byBeStation = i;
			return 1;
		}
	}

	//�ж��Լ��Ƿ��Ƿ�����
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

///��������ϸ������
///@param station ���Ƽ��λ�ã�hutype[] �ܺ��Ƶ����ͣ�zimo �Ƿ�����
///@return true  �ܺ��� false ����
bool CheckHuPaiEx::CanHu(BYTE station,BYTE lastpai,BYTE hutype[],bool zimo)
{

// 	if(!CheckHaveGang(station) && !zimo)
// 		return false;
	BYTE byBeSation;
	if(CheckHaveChengBao(station,byBeSation) && !zimo)
	{
		return false;
	}

	//û�л��ƺ͸��ƣ������ͱ������������ܱ�����
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

	///����Ƿ���������
	m_bZimo = zimo;
    //�����������ڵ���
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


    ///��С��������
    MaoPaoSort(m_byArHandPai,HAND_CARD_NUM,false);
    bool bb = false;
	bool dahu = false;
    ///������ת��
    ChangeHandPaiData(m_byArHandPai,255);
    if(CheckQiDui()>0)        //���߶�
    {
		do
		{
			if(pDesk->sUserData.IsHuaPaiInHand(station))
				break;
			SetAHupaiType(HUPAI_AN_QI_DUI,hutype);//�߶�
			bb = true;
			dahu = true;
		}while(0);
    }
	else if(CheckQiXingBuKao())
	{
		if(zimo)
		{
			SetAHupaiType(HUPAI_QIXING_BUKAO,hutype);//����13��
			bb = true;
			dahu = true;
		}
	}
	else if(CheckQuanBuKao())
	{
		if(zimo)
		{
			SetAHupaiType(HUPAI_QUAN_BUKAO,hutype);//13��
			bb = true;
			dahu = true;
		}
	}
    else if(CheckPingHu(lastpai,zimo,false))//ƽ������
    {   
		do
		{
			/*if(pDesk->sUserData.IsHuaPaiInHand(station))
				break;*/

			bb = true;
			bool bHuWay = false;
			CheckPingHuData();//�Ȼ�ȡ�����
			//������
			if(CheckPengPengHu())   
			{
				SetAHupaiType(HUPAI_PENG_PENG_HU,hutype);
				dahu = true;
			}
			if(CheckMenQianQing())//��ǰ��
			{
				SetAHupaiType(HUPAI_MEN_QIAN_QING,hutype);
			}
			if(CheckDaDiaoChe(station))//�����
			{
				dahu = true;
				SetAHupaiType(HUPAI_DA_DIAOCHE,hutype);
			}
			if(CheckBianPai(lastpai)) //����
			{
				bHuWay = true;
				SetAHupaiType(HUPAI_BIAN_PAI,hutype);
			}
			if(CheckKaPa(lastpai))	//����
			{
				if(!bHuWay)
				{
					bHuWay = true;
					SetAHupaiType(HUPAI_KAI_PAI,hutype);
				}
			}
			if(CheckLiangDui(lastpai))//������
			{
				if(!bHuWay)
					SetAHupaiType(HUPAI_LIANG_DUI,hutype);
			}
			if(CheckDianDiao(station,lastpai))//������
			{
				SetAHupaiType(HUPAI_DIAN_DIAO,hutype);
			}
			if(CheckThreeNan(station))//�����Ϸ�
			{
				SetAHupaiType(HUPAI_THREE_NAN,hutype);
			}
			if(CheckThreeXi(station))//��������
			{
				SetAHupaiType(HUPAI_THREE_XI,hutype);
			}
			if(CheckThreeBei(station))//���ű���
			{
				SetAHupaiType(HUPAI_THREE_BEI,hutype);
			}

		}while(false);
    }
    if (bb)
    {
		//û�д�������Ƶ���
		if(!dahu)
		{
			SetAHupaiType(HUPAI_HU_PAI,hutype);
		}
		//����
		if(zimo)
		{
			SetAHupaiType(HUPAI_ZI_MO,hutype);
		}
		//���
		if(CheckTianHu())
		{
			SetAHupaiType(HUPAI_TYPE_TIAN_HU,hutype);
		}
		//�غ�
		if(CheckDiHu())
		{
			SetAHupaiType(HUPAI_TYPE_DI_HU,hutype);
		}
		// �ܿ�
        if (CheckGangKai())     
        {
            SetAHupaiType(HUPAI_TYPE_GANG_KAI, hutype);
        }    

		//�޻���
		if (CheckNoHua())
		{
			 SetAHupaiType(HUPAI_NO_HUA, hutype);
		}

    }



    return bb;
}

///ƽ�����
bool CheckHuPaiEx::CheckPingHu(BYTE lastzhuapai,bool zimo,bool jing,bool CheckTing)
{
	//ѭ������
	TempHupaistruct.Init();
	hupaistruct.Init();
	m_iMaxFan = -1;
	BYTE pai[4]={255};
	bool caishen[4]={0};

	//1������ļ��,һ�������һ��������  //û�в���Ĳ������������
	if(m_byJingNum>=1 && m_byJingNum!=255)
	{

		for(int i=0;i<NoJingHuTempData.conut;i++)
		{
			if(NoJingHuTempData.data[i][1]<1 || NoJingHuTempData.data[i][1] == 255 ||NoJingHuTempData.data[i][0]==255)
			{
				continue;
			}
			hupaistruct.Init();//��ʼ�����ƽṹ
			NoJingHuTempData.data[i][1]-=1;

			memset(caishen,0,sizeof(caishen));
			memset(pai,255,sizeof(pai));
			pai[0] = pai[1] = NoJingHuTempData.data[i][0];
			caishen[0] = true;
			hupaistruct.AddData(TYPE_JIANG_PAI,pai,caishen);	
			MakePingHu(NoJingHuTempData,hupaistruct,m_byJingNum-1);//���Ƽ��ݹ麯�����ڵݹ������ȫ�����
			NoJingHuTempData.data[i][1]+=1;
		}
	}
	//���������ļ��,(�޾����齫HuTempData �� NoJingHuTempData��һ��������)
	for(int i=0;i<NoJingHuTempData.conut;i++)
	{
		if(NoJingHuTempData.data[i][1]<2 || NoJingHuTempData.data[i][0]==255)
		{
			continue;
		}
		hupaistruct.Init();//��ʼ�����ƽṹ
		NoJingHuTempData.data[i][1]-=2;

		memset(caishen,0,sizeof(caishen));
		memset(pai,255,sizeof(pai));
		pai[0] = pai[1] = NoJingHuTempData.data[i][0];
		hupaistruct.AddData(TYPE_JIANG_PAI,pai,caishen);
		MakePingHu(NoJingHuTempData,hupaistruct,m_byJingNum);//���Ƽ��ݹ麯�����ڵݹ������ȫ�����
		NoJingHuTempData.data[i][1]+=2;
	}
	if(m_iMaxFan>=0)
	{
		hupaistruct = TempHupaistruct;
		return true;
	}
	return false;
}

///��ȡ�����������
bool CheckHuPaiEx:: GetMaxCombination(bool zimo,bool jing,BYTE lastpai)
{
	CheckPingHuData();//�Ȼ�ȡ�����

	ClearHupaiType(m_byHuType);//�����������
	int fan = 0;
	bool bMax =  false;//�Ƿ���ڸ��������

    if(CheckQingYiSe())    //��һɫ
    {
		fan = 4;
    }
    if(CheckQuanDaiYao())  //ȫ����  
    {
		if(CheckQingYiSe())//��һɫ
		{
			fan = 16;//����� 5 �� 16��
		}
		else
		{
			fan = 4;
		}
    }
	if(CheckPengPengHu())   //�����
	{
		if (CheckQingYiSe())    //���
		{
			fan = 8;
		}
		else if (CheckJiangDui())   //����
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
		TempHupaistruct = hupaistruct;//��¼�������
	}
	return bMax;
}

//������
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
		case AT_COLLECT://���ƶ���
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

//��⽫�ԣ�258��������
bool CheckHuPaiEx::CheckJiangDui()
{
	for(int i=0;i<hupaistruct.count;++i)
	{
		if(hupaistruct.byType[i] == TYPE_SHUN_ZI)//˳��
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
		case ACTION_CHI://���ƶ���
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

///����Ƿ�ȫ����
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

///������Ҹ�������
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

///�����߶��������Ƶ�����
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

///�����߶��������Ƶ�����
bool CheckHuPaiEx::CheckHuGen(BYTE lastpai)
{	
	if(lastpai == 255)
		return false;
	if(CLogicBase::GetNumInArr(m_byArHandPai,lastpai ,HAND_CARD_NUM) >= 4)
		return true;
	return false;
}

//����Ƿ��۾��߶� 8 
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
 	str.Format("chenlog----------���Ƽ��  ��ҿɺ�������  %d",m_iCanPingHuCardNum);
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
 	str.Format("chenlog----------���Ƽ��  ��ҿɺ�������  %d",m_iCanPingHuCardNum);
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

//ȫ�������ɵ���3�ֻ�ɫ147��258��369���ܴ�λ�������Ƽ����������з����е��κ�14������ɵĺ��ƣ�ʮ���ã������������롢�����ˡ�����(��ƽ������)
bool CheckHuPaiEx::CheckQuanBuKao()
{
	BYTE num=0;
	for(int i=0;i<5;++i)
	{
		if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byType == 255)
			continue;
		num++;
	}
	if(num>0)//�����г�����
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

		//��С��������
		MaoPaoSort(m_byArHandPai,HAND_CARD_NUM,false);
		///������ת��
		ChangeHandPaiData(m_byArHandPai,255);
		if (CheckPingHu(j,bzimo,false))
		{
			iNum++;
		}
	}
	return iNum;
}