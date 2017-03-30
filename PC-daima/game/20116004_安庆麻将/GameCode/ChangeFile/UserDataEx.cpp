/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #include "stdafx.h"
//#include "../Client/stdafx.h"
#include "UserDataEx.h"

//ȫ�ֶ���
UserDataEx g_UserData;

UserDataEx::UserDataEx(void)
{
	UserData::UserData();
	m_byCaiPiaoStation = 255;//��Ʈλ�ã���ֵ��Ϊ255�ǲ���������ܺͷ���
	memset(m_byGuanXi,0,sizeof(m_byGuanXi));//�����ܹ�ϵ

	memset(m_bGangKai,0,sizeof(m_bGangKai));//�ܿ�״̬���
	memset(m_bOutJing,0,sizeof(m_bOutJing));//����Ƿ����˲�����

	m_byLianZhuang = 0;//��ׯ��
	m_bTianHu = true;		//ׯ�����״̬
	m_bChanPai = false;		//����Ƿ����

	memset(m_bLookBao,0,sizeof(m_bLookBao));//����״̬
	memset(m_byFirstHandPai,255,sizeof(m_byFirstHandPai));//��һ���ƣ����ƣ������ܺ�ץ���Ĳ���
    memset(m_byDingQue, 255, sizeof(m_byDingQue));
    memset(m_byGFXY, 0, sizeof(m_byGFXY));
    memset(m_bIsHu, false, sizeof(m_bIsHu));
    memset(m_byGengCount, 0, sizeof(m_byGengCount));

    memset(m_bIsGangPao, 0, sizeof(m_bIsGangPao));//���ڸܺ��ڵ�״̬
    memset(m_bQiHu, 0, sizeof(m_bQiHu));//����Ƿ�����״̬
    memset(m_NoFenGang, 255, sizeof(m_NoFenGang));////��¼�޷ָܣ����ܣ�������4������������޷֣�ץ�ƺ��ܲ��ܵ��ǲ��ڵ�ǰȦ���޷֣�

	
	m_byBuGangPai = 255;//���ܵ÷ֵ���
	//�ܷ�
	for(int i=0;i<PLAY_COUNT;++i)
	{
		m_stGangFen[i].Init();
	}
}

UserDataEx::~UserDataEx(void)
{
	UserData::~UserData();
}


///���ƣ�IsHaveAHandPai
///����������Ƿ����ָ��������
///@param pai Ҫ������
///@return true �� false ��
bool UserDataEx::IsHaveAHandPai(BYTE station,BYTE pai)
{
	return UserData::IsHaveAHandPai(station,pai);
}

///���ƣ�GetAHandPaiCount
///���������������ĳ���Ƶĸ���
///@param pai Ҫ������
///@return ������
int UserDataEx::GetAHandPaiCount(BYTE station,BYTE pai)
{
	return UserData::GetAHandPaiCount(station,pai);
}

///�õ�ĳ�ֻ�ɫ�ƣ�0�� 1Ͳ 2��)
int UserDataEx::GetAKindPai(BYTE station,BYTE kind)
{
    kind %= 3;

    int count = 0;
    for(int i=0;i<HAND_CARD_NUM;i++)
    {
        if(m_byArHandPai[station][i]/10 == kind)
            return m_byArHandPai[station][i];
    }
    return 0;
}

///���ĳ�ֻ�ɫ�Ƶĸ�����0�� 1Ͳ 2��)
int UserDataEx::GetAKindPaiCount(BYTE station,BYTE kind)
{
    kind %= 3;

    int count = 0;
    for(int i=0;i<HAND_CARD_NUM;i++)
    {
		if(m_byArHandPai[station][i] == 255)
			continue;
        if(m_byArHandPai[station][i]/10 == kind)
            count++;
    }
    return count;
}

///���ƣ�GetHandPaiCount
///������������Ƹ���
///@param 
///@return ������Ƶ�����
int UserDataEx::GetHandPaiCount(BYTE station)
{
	return UserData::GetHandPaiCount(station);
}

///���ƣ�CopyHandPai
///������������ҵ�����
///@param pai[] ������, station λ��, show �Ƿ񿽱�����
///@return �����������
int UserDataEx::CopyHandPai(BYTE pai[][HAND_CARD_NUM] ,BYTE station,bool show)
{
	memset(pai,255,sizeof(pai));
	for(int i=0;i<PLAY_COUNT;++i)
	{
		int count = GetHandPaiCount(station);
		if(i == station)//�Լ�����
		{
			for(int j=0;j<HAND_CARD_NUM;++j)
			{
				pai[i][j] = m_byArHandPai[station][j];
			}
		}
		else 
		{
			if(m_bIsHu[i] || show)//�����˷�������
			{
				for(int j=0;j<HAND_CARD_NUM;++j)
				{
					pai[i][j] = m_byArHandPai[i][j];
				}
			}
			else//�����Ʊ�
			{
				for(int j=0;j<HAND_CARD_NUM;++j)
				{
					if( m_byArHandPai[i][j] != 255)
					{	
						pai[i][j] = 0;
					}
					else 
					{
						pai[i][j] = m_byArHandPai[i][j];
					}
				}
			}
		}
	}
	return 0;
}

///���ƣ�CopyOneUserHandPai
///����������ĳ����ҵ�����
///@param pai[] ������, station λ��
///@return �����������
int UserDataEx::CopyOneUserHandPai(BYTE pai[HAND_CARD_NUM] ,BYTE station)
{
	return UserData::CopyOneUserHandPai( pai,station);
}

///���ƣ�SortHandPai
///��������������small�Ƿ��С������
///@param big �Ƿ�ӵ���С����Ĭ�ϴ�С��������
///@return 
void UserDataEx::SortHandPai(BYTE station,bool big)
{
	UserData::SortHandPai( station, big);
}

///���ƣ�AddToHandPai
///���������һ���Ƶ�������
///@param pai ��ӵ�����ֵ
///@return 
void UserDataEx::AddToHandPai(BYTE station,BYTE pai)
{
	UserData::AddToHandPai( station, pai);
}

///���ƣ�SetHandPaiData
///������������������
///@param  pai[] �������������
///@return 
void UserDataEx::SetHandPaiData(BYTE station,BYTE pai[],BYTE byCount)
{
	UserData::SetHandPaiData( station, pai,byCount);
}

///���ƣ�DelleteAHandPai
///������ɾ��һ��ָ��������
///@param pai Ҫɾ������
///@return 
void UserDataEx::DelleteAHandPai(BYTE station,BYTE pai)
{
	UserData::DelleteAHandPai(station,pai);
}

///���ƣ�SetHandPaiBack
///���������������Ʊ�
///@param num���õ�����
///@return 
void UserDataEx::SetHandPaiBack(BYTE station,BYTE num)
{
	UserData::SetHandPaiBack(station,num);
}

///���ƣ�GetLastHandPai
///������������һ������
///@param 
///@return 
BYTE UserDataEx::GetLastHandPai(BYTE station)
{
	return UserData::GetLastHandPai(station);
}

///���ƣ�GetSelectHandPai
///���������ѡ�е�һ������
///@param 
///@return 
BYTE UserDataEx::GetSelectHandPai(BYTE station)
{
	return UserData::GetSelectHandPai(station);
}

///���ƣ�IsOutPaiPeople
///�������Ƿ�������
///@param 
///@return  true �� ,false ����
bool UserDataEx::IsOutPaiPeople(BYTE station)
{
	return UserData::IsOutPaiPeople(station);
}

///���ƣ�IsHuaPaiInHand
///����������������Ƿ���ڻ���
///@param 
///@return  true �� ,false ����
bool UserDataEx::IsHuaPaiInHand(BYTE station)
{
	return UserData::IsHuaPaiInHand(station);
}

///���ƣ�MoveHuaPaiFormHand
///�������������еĻ����Ƶ�����������
///@param 
///@return  ���Ƶ�����
int UserDataEx::MoveHuaPaiFormHand(BYTE station,BYTE byCard)
{
	return UserData::MoveHuaPaiFormHand(station,byCard);
}

///��ȡ���Ƶ���ɫ��
int UserDataEx::GetPaiSeCount(BYTE station)
{
	int count = 0;
	bool se[3];
	memset(se,0,sizeof(se));
	for(int i=0;i<HAND_CARD_NUM;i++)
	{
		if(m_byArHandPai[station][i] < 0 || m_byArHandPai[station][i] > CMjEnum::MJ_TYPE_B9)
			continue;
		se[m_byArHandPai[station][i]/10] = true;
	}
	for(int i=0;i<3;i++)
	{
		if(se[i])
			count++;
	}
	return count;
}
///�Ƿ���ȱ�ŵ���
bool UserDataEx::IsHaveQueMen(BYTE station,BYTE type)
{
	if(type >2 || type<0)
		return false;
	for(int i=0;i<HAND_CARD_NUM;i++)
	{
		if(m_byArHandPai[station][i] < 0 || m_byArHandPai[station][i] > CMjEnum::MJ_TYPE_B9)
			continue;
		if(m_byArHandPai[station][i]/10 == type)
			return true;
	}
	return false;
}
//��ȡһ��data��û�е��ƣ���������
BYTE UserDataEx::GetChangePai(BYTE station,BYTE data[])
{
	BYTE pai = 255;
	for(int i=0;i<HAND_CARD_NUM;i++)
	{
		bool have = false;
		for(int j=0;j<HAND_CARD_NUM;++j)
		{
			if(data[j] == m_byArHandPai[station][i])
				have = true;//���������д��ڸ��ƣ�������ȥ�滻
		}
		if(!have)
		{
			return m_byArHandPai[station][i];
		}
	}
	return pai;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///���ƣ�GetUserGangNum
///��������ȡ��Ҹ��Ƶĸ���(���ܣ����ܣ�����)
///@param &an ��������, &ming �������� ,  &bu ��������
///@return ���Ƶ��ܸ���
int UserDataEx::GetUserGangNum(BYTE station,BYTE &an,BYTE &ming , BYTE &bu)
{
	return UserData::GetUserGangNum(station,an,ming ,bu);
}

///���ƣ�GetUserChiNum
///��������ҳ��ƴ���
///@param station ���λ��
///@return ���Ƶ��ܸ���
int UserDataEx::GetUserChiNum(BYTE station)
{
	return UserData::GetUserChiNum(station);
}

///���ƣ�GetUserPengNum
///��������Ҹ��ƴ���
///@param station ���λ��
///@return ���Ƶ��ܸ���
int UserDataEx::GetUserPengNum(BYTE station)
{
	return UserData::GetUserPengNum(station);
}
///���ƣ�IsUserHaveGangPai
///��������Ҹ���ĳ����
///@param pai ��, &type ����
///@return  true �� ,false ����
bool UserDataEx::IsUserHaveGangPai(BYTE station,BYTE pai,BYTE &type)
{	
	return UserData::IsUserHaveGangPai(station, pai, type);
}
///
///���ƣ�IsUserHavePengPai
///����������Ƿ�����ĳ����
///@param pai ��
///@return  true �� ,false ����
bool UserDataEx::IsUserHavePengPai(BYTE station,BYTE pai)
{
	return UserData::IsUserHavePengPai(station, pai);
}

///���ƣ�IsUserHaveChiPai
///����������Ƿ�Թ�ĳ����
///@param pai ��
///@return  true �� ,false ����
bool UserDataEx::IsUserHaveChiPai(BYTE station,BYTE pai)
{
	return UserData::IsUserHaveChiPai(station,pai);
}

///���ƣ�AddToGCP
///���������һ�����ݵ��ܳ���������
///@param gcpData Ҫ��ӵĳ���������
///@return 
void UserDataEx::AddToGCP(BYTE station,GCPStructEx *gcpData)
{
	//UserData::AddToGCP(station,gcpData);
	for(int i=0;i<5;i++)
	{
		if(m_UserGCPData[station][i].byType==255)
		{
			m_UserGCPData[station][i].byType = gcpData->byType;
			m_UserGCPData[station][i].iBeStation = gcpData->iBeStation;
			m_UserGCPData[station][i].iOutpai = gcpData->iOutpai;
			m_UserGCPData[station][i].iStation = gcpData->iStation;
			m_UserGCPData[station][i].bIsBigGang = gcpData->bIsBigGang;
			for(int j=0;j<4;j++)
			{
				m_UserGCPData[station][i].byData[j] = gcpData->byData[j];
			}
			for(int j=0;j<4;j++)
			{
				m_UserGCPData[station][i].byBigGang[j][0] = gcpData->byBigGang[j][0];
				m_UserGCPData[station][i].byBigGang[j][1] = gcpData->byBigGang[j][1];
			}
			break;
		}
	}
}

///���ƣ�DelleteAGCPData
///������ɾ���ܳ���������ָ����������
///@param type ����, pai ��
///@return 
void UserDataEx::DelleteAGCPData(BYTE station,BYTE type ,BYTE pai)
{
	UserData::DelleteAGCPData(station, type , pai);
}	

///���ƣ�CopyGCPData
///�����������ܳ��������е�������
///@param gcpData ����������
///@return �����ܸ���
int UserDataEx::CopyGCPData(BYTE station,GCPStructEx gcpData[])
{
	return UserData::CopyGCPData(station,gcpData);
}

///���ƣ�SetGCPData
///���������øܳ��������е�������
///@param gcpData ����������
///@return 
void UserDataEx::SetGCPData(BYTE station,GCPStructEx gcpData[])
{
	UserData::SetGCPData(station,gcpData);
}

///���ƣ�GetGCPCount
///��������ȡ�ܳ����Ľڵ����
///@param 
///@return ��ó������ܸ���
int UserDataEx::GetGCPCount(BYTE station)
{
	return UserData::GetGCPCount(station);
}
///���ƣ�GetOnePaiGCPCount
///��������ȡ�ܳ�������ĳ���Ƶ�����
///@param 
///@return ĳ���Ƶ�����
int UserDataEx::GetOnePaiGCPCount(BYTE station,BYTE pai)
{
	return UserData::GetOnePaiGCPCount(station,pai);
}
///���ƣ�ShortGCP
///����������ܳ�������
///@param 
///@return 
void UserDataEx::ShortGCP(BYTE station)
{
	UserData::ShortGCP(station);
}
///���ƣ�InitGCP
///��������ʼ���ܳ�������
///@param 
///@return 
void UserDataEx::InitGCP(BYTE station)
{
	UserData::InitGCP(station);
}
//////////////////���Ʋ���///////////////////////////////////////////////////////////////////////////////

///���ƣ�AddToOutPai
///���������һ���Ƶ�����������
///@param pai ��
///@return 
void UserDataEx::AddToOutPai(BYTE station,BYTE pai)
{
	UserData::AddToOutPai(station, pai);
}

///���ƣ�DelleteLastOutPai
///������ɾ�����һ�ų���
///@param 
///@return 
void UserDataEx::DelleteLastOutPai(BYTE station)
{
	UserData::DelleteLastOutPai(station);
}

///���ƣ�SetOutPaiData
///���������ó�������
///@param pai[] ��������
///@return 
void UserDataEx::SetOutPaiData(BYTE station,BYTE pai[],BYTE byCount)
{
	UserData::SetOutPaiData(station, pai, byCount);
}

///���ƣ�CopyOutPai
///������������ҵĳ���
///@param pai[] ��������
///@return ���Ƶ�����
int UserDataEx::CopyOutPai(BYTE station,BYTE pai[])
{
	return UserData::CopyOutPai(station, pai);
}

///���ƣ�GetOutPaiCount
///��������ȡ��ҵĳ�������
///@param 
///@return ���Ƶ�����
int UserDataEx::GetOutPaiCount(BYTE station)
{
	return UserData::GetOutPaiCount(station);
}
///���ƣ�GetOutPaiCount
///��������ȡ���ĳ���Ƶĳ�������
///@param 
///@return ĳ���Ƴ��Ƶ�����
int UserDataEx::GetOneOutPaiCount(BYTE station,BYTE pai)
{
	return UserData::GetOneOutPaiCount(station, pai);
}
/////////////////////���Ʋ���////////////////////////////////////////////////////////

///���ƣ�AddToHuaPai
///���������һ�Ż��Ƶ�����������
///@param pai ����
///@return 
void UserDataEx::AddToHuaPai(BYTE station,BYTE pai)
{
	UserData::AddToHuaPai(station, pai);
}

///���ƣ�SetHuaPaiData
///���������û�������
///@param pai[] ��������
///@return 
void UserDataEx:: SetHuaPaiData(BYTE station,BYTE pai[])
{
	UserData::SetHuaPaiData( station, pai);
}

///���ƣ�CopyHuaPai
///������������ҵĻ���
///@param pai[] ��������
///@return 
int UserDataEx::CopyHuaPai(BYTE station,BYTE pai[])
{
	return UserData::CopyHuaPai(station, pai);
}

///����Ƿ���
bool UserDataEx::CheckIsHuaPai(BYTE pai)
{
	return UserData::CheckIsHuaPai(pai);
}

int UserDataEx::GetAHuaCount(BYTE station,BYTE pai)
{
	int iCount = 0;
	for(int i = 0; i < HUA_CARD_NUM; i++)
	{
		if(m_byArHuaPai[station][i] == pai)
		{
			iCount++;
		}
	}
	return iCount;
}
///////////////////////���Ʋ���//////////////////////////////////////////////////////////////////
///���ƣ�SetMenPaiData
///������������������
///@param  pai[] ��������
///@return 
void UserDataEx::SetMenPaiData(BYTE station,BYTE pai[])
{
	UserData::SetMenPaiData(station, pai);
}

///���ƣ�CopyMenPai
///������������ҵ�����
///@param  pai[] ��������
///@return �����������
int UserDataEx::CopyMenPai(BYTE station,BYTE pai[])
{
	return UserData::CopyMenPai(station,pai);
}

///���ƣ�GetPaiNum
///��������ȡ���������Ч������
///@param  pai[] Ҫ����������, count ��Ч�Ƶ�����
///@return 
int UserDataEx::GetPaiNum(BYTE station,BYTE pai[],BYTE count)
{
	return UserData::GetPaiNum(station, pai,count);
}
///���ƣ�InitData
///��������ʼ������
///@param 
///@return 
void UserDataEx::InitData()
{
	UserData::InitData();

	m_byCaiPiaoStation = 255;//��Ʈλ�ã���ֵ��Ϊ255�ǲ���������ܺͷ���
	memset(m_byGuanXi,0,sizeof(m_byGuanXi));//�����ܹ�ϵ
	memset(m_bGangKai,0,sizeof(m_bGangKai));//�ܿ�״̬���
	memset(m_bOutJing,0,sizeof(m_bOutJing));//����Ƿ����˲�����
	m_bTianHu = true;;//ׯ�����״̬
	m_bChanPai = false;		//����Ƿ����

	memset(m_bLookBao,0,sizeof(m_bLookBao));//����״̬

	memset(m_byFirstHandPai,255,sizeof(m_byFirstHandPai));//��һ���ƣ����ƣ������ܺ�ץ���Ĳ���
    memset(m_byDingQue, 255, sizeof(m_byDingQue));
    memset(m_byGFXY, 0, sizeof(m_byGFXY));
    memset(m_bIsHu, false, sizeof(m_bIsHu));
    memset(m_byGengCount, 0, sizeof(m_byGengCount));

    memset(m_bIsGangPao, 0, sizeof(m_bIsGangPao));//���ڸܺ��ڵ�״̬
    memset(m_bQiHu, 0, sizeof(m_bQiHu));//����Ƿ�����״̬
    memset(m_NoFenGang, 255, sizeof(m_NoFenGang));////��¼�޷ָܣ����ܣ�������4������������޷֣�ץ�ƺ��ܲ��ܵ��ǲ��ڵ�ǰȦ���޷֣�
	m_byBuGangPai = 255;//���ܵ÷ֵ���
	memset(m_byTimeOut,0,sizeof(m_byTimeOut));
	memset(m_byChengBao,0,sizeof(m_byChengBao));
	memset(m_byPengChengBao,0,sizeof(m_byPengChengBao));
	memset(m_byChiChengBao,0,sizeof(m_byChiChengBao));
	//�ܷ�
	for(int i=0;i<PLAY_COUNT;++i)
	{
		m_stGangFen[i].Init();
	}

}

///���ƣ�IsUserHaveBigGangPai
///����������Ƿ����ĳ���ƵĴ��
///@param pai ��
///@return  true �� ,false ����
bool UserDataEx::IsUserHaveBigGangPai(BYTE station,BYTE pai)
{
	if(pai == 255)
		return false;
	for(int i=0;i<5;i++)
	{
		if(!m_UserGCPData[station][i].bIsBigGang || m_UserGCPData[station][i].byType<ACTION_AN_GANG || m_UserGCPData[station][i].byType>ACTION_MING_GANG )
			continue;
		for(int j=0;j<4;j++)
		{
			if(m_UserGCPData[station][i].byBigGang[j][0] == pai)
				return true;
		}
	}
	return false;
}

///��������ץ������ת����ץ����ҵ���������
bool UserDataEx::ZhuaPaiIndex(BYTE &index,BYTE &dir)
{
	dir = 255;
	if(index == 255)
		return false;
	//int num = 0;
	//int count = 0;
	//num = 27;
	//for(int i=0;i<4;i++)
	//{
	//	if(i == 0 || i == 2)
	//	{
	//		num += 1;
	//	}
	//	else 
	//	{
	//		num -= 1;
	//	}
	//	for(int j=count;j<(count + num) ;++j)
	//	{
	//		if(j == index)
	//		{
	//			dir = i;
	//			index = j-count;
	//			return true;
	//		}
	//	}		
	//	count += num;
	//}

	if(index<28)
	{
		dir = 0;
		index = index;
	}
	else if(index<54)
	{
		dir = 1;
		index = index%28;
	}
	else if(index<82)
	{
		dir = 2;
		index = index%54;
	}
	else if(index<108)
	{
		dir = 3;
		index = index%82;
	}
	return true;
}
///����Ƿ����ָ��������
bool UserDataEx::IsHaveAMenPai(BYTE pai)
{
	for(int i=0;i<300;i++)
	{
		if(m_MenPai.byMenPai[i] != 255 && m_MenPai.byMenPai[i] == pai)
			return true;
	}
	return false;
}

//��ָ����һ������
bool	UserDataEx::ChangeAHandPai(BYTE station,BYTE ChangePai,BYTE byNewCard)
{
	if(station <0 || station>=PLAY_COUNT )
	{
		return false;
	}
	if(0 == ChangePai || 255 == ChangePai || 0 == byNewCard || 255 == byNewCard)
	{
		return false;
	}
	for(int i=0;i<HAND_CARD_NUM;i++)
	{
		if(m_byArHandPai[station][i] == ChangePai)
		{
			m_byArHandPai[station][i] = byNewCard;
			return true;
		}
	}
	return false;
}

//��ָ��һ������
bool	UserDataEx::ChangeAMenPai(BYTE ChangePai,BYTE byNewCard)
{
	if(0 == ChangePai || 255 == ChangePai || 0 == byNewCard || 255 == byNewCard)
	{
		return false;
	}
	for(int i=0;i<300;i++)
	{
		if(m_MenPai.byMenPai[i] != 255 && m_MenPai.byMenPai[i] == ChangePai)
		{
			m_MenPai.byMenPai[i] = byNewCard;
			return true;
		}
	}
	return false;
}