/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
#include "stdafx.h"
#include "UserData.h"


UserData::UserData(void)
{
	memset(m_byArHandPai,255,sizeof(m_byArHandPai));	/// ���Ʋ�����20�ţ�255Ϊ������־
	memset(m_byArOutPai,255,sizeof(m_byArOutPai));		/// ���Ʋ�����160�ţ�255Ϊ������־
	memset(m_byArHuaPai,255,sizeof(m_byArHuaPai));		/// ���Ʋ�����10�ţ�255Ϊ������־
	memset(m_iArMenPai,255,sizeof(m_iArMenPai));		/// ���Ʋ�����40�ţ�255Ϊ������־
	memset(m_byGuanXi,0,sizeof(m_byGuanXi));			/// �����ܹ�ϵ����
	memset(m_bEnableCard,1,sizeof(m_bEnableCard));		/// �Ƿ���õ���
	memset(m_bIsBoy,0,sizeof(m_bIsBoy));				/// �ؼ�����	
	memset(m_byCanOutCard,255,sizeof(m_byCanOutCard));	/// ͣ�ƻ������������ܴ������
	memset(m_byMenFeng,255,sizeof(m_byMenFeng));		/// �ŷ�	
	memset(m_bFoceLeave,0,sizeof(m_bFoceLeave));		///	����Ƿ��Ѿ�����
	memset(m_bTing,0,sizeof(m_bTing));					///	����Ƿ�����
	memset(m_bTuoGuan,0,sizeof(m_bTuoGuan));			///	����Ƿ��й�
	memset(m_bWinner,0,sizeof(m_bWinner));				///	����Ƿ�Ӯ��
	memset(m_byLastZhuaPai,255,sizeof(m_byLastZhuaPai));///	���ץ������
	memset(m_bySetMoPai,255,sizeof(m_bySetMoPai));//ץ��ǿ��ָ��ֵ�������ã�
	memset(m_bSiziFinish,0,sizeof(m_bSiziFinish));			///	����Ƿ񷵻���ɫ�ӽ�����Ϣ
	memset(m_bHaveOut,0,sizeof(m_bHaveOut));			///	��¼����Ƿ��������

	m_bWaitSezi = false;//�Ƿ���ȴ�ɫ�Ӷ�������״̬

	m_StrJing.Init();
	for(int i=0;i<4;++i)
	{//�������ݽṹ
		m_SetData[i].Init();
	}
	//��ʼ����
	m_MenPai.Init();

	m_byFoceLeavCount=0;		///����뿪������

	m_byStation = 255;			///��ǰ��ҵ��߼�λ�ã��ͻ���ʹ�ã�
	byPlayCount = 0;			///��Ϸ�Ѿ����еľ�����ǿ�ˣ���ȫ�˳�����ɢ�����¿�ʼ���㣩
	m_byQuanFeng = 255;			///Ȧ��
	m_bIsDuoXiang = false;		///�Ƿ�һ�ڶ���


	m_bMeOutPai = false;		//�Ƿ��ҳ���
	m_bySelectIndex = 255;		///��ǰѡ��������
	m_bisTing = 0;				///��ǰ����Ƿ�����
	m_byLastOutPai = 255;		///���������
	m_byMeZhuaPai = 255;		///��ǰ������ץ��
	m_byNowOutStation = 255;	///��ǰ����λ��
	m_byLastOutStation = 255;	///�ϴγ���λ��
	m_byBaoPaiUser = 255;		///�������
	m_byOtherOutPai = 255;		///��ǰ������Ҵ������
	///��ǰץ�Ʒ���true ˳ʱ�룬false ��ʱ��
	m_bZhuaPaiDir = true;
	//ͬ������뿪������
	m_byAgreeLeaveNum = 0;

	m_byApplyMaxAction = 0;//��ҵ�ǰ���������¼�

	m_byCanDoMaxAction = 0;//���μ����������������
}

UserData::~UserData(void)
{

}


///���ƣ�IsHaveAHandPai
///����������Ƿ����ָ��������
///@param pai Ҫ������
///@return true �� false ��
bool UserData::IsHaveAHandPai(BYTE station,BYTE pai)
{
	if(station <0 || station>=PLAY_COUNT)
		return false;
	for(int i=0;i<HAND_CARD_NUM;i++)
	{
		if(m_byArHandPai[station][i] == pai)
			return true;
	}
	return false;
}

///���ƣ�GetAHandPaiCount
///���������������ĳ���Ƶĸ���
///@param pai Ҫ������
///@return ������
int UserData::GetAHandPaiCount(BYTE station,BYTE pai)
{
	if(station <0 || station>=PLAY_COUNT)
		return 0;
	int count = 0;
	for(int i=0;i<HAND_CARD_NUM;i++)
	{
		if(m_byArHandPai[station][i] == pai)
			count++;
	}
	return count;
}

///���ƣ�GetHandPaiCount
///������������Ƹ���
///@param 
///@return ������Ƶ�����
int UserData::GetHandPaiCount(BYTE station)
{
	if(station <0 || station>=PLAY_COUNT)
		return 0;
	int count = 0;
	for(int i=0;i<HAND_CARD_NUM;i++)
	{
		if(m_byArHandPai[station][i] != 255)
			count++;
	}
	return count;
}

///���ƣ�CopyHandPai
///������������ҵ�����
///@param pai[] ������, station λ��, show �Ƿ񿽱�����
///@return �����������
int UserData::CopyHandPai(BYTE pai[][HAND_CARD_NUM] ,BYTE station,bool show)
{
	if(station <0 || station>=PLAY_COUNT)
		return 0;
	memset(pai,255,sizeof(pai));
	for(int i=0;i<4;++i)
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
			if(!show)//��ʾ�Ʊ�
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
			else
			{
				for(int j=0;j<HAND_CARD_NUM;++j)
				{
					pai[i][j] = m_byArHandPai[i][j];
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
int UserData::CopyOneUserHandPai(BYTE pai[HAND_CARD_NUM] ,BYTE station)
{
	if(station <0 || station>=PLAY_COUNT)
		return 0;
	memset(pai,255,sizeof(pai));
	for(int j=0;j<HAND_CARD_NUM;++j)
	{
		pai[j] = m_byArHandPai[station][j];
	}
	return GetHandPaiCount(station);
}

void UserData::SortHuaPai(BYTE station,bool big)
{
	if(station <0 || station>=PLAY_COUNT)
		return ;

	MaoPaoSort(m_byArHuaPai[station],HUA_CARD_NUM,big);
}
///���ƣ�SortHandPai
///��������������small�Ƿ��С������
///@param big �Ƿ�ӵ���С����Ĭ�ϴ�С��������
void UserData::SortHandPai(BYTE station,bool big)
{
	if(station <0 || station>=PLAY_COUNT)
		return ;
	///����
	MaoPaoSort(m_byArHandPai[station],HAND_CARD_NUM,big);
	BYTE HandPai[HAND_CARD_NUM];
	for(int j=0;j<HAND_CARD_NUM;++j)
	{
		HandPai[j] = m_byArHandPai[station][j];
	}
	int index=0;
	for(int j=0;j<HAND_CARD_NUM;++j)
	{
		if(m_StrJing.CheckIsJing(HandPai[j]))
		{
			m_byArHandPai[station][index] = HandPai[j];
			index++;
		}
	}
	for(int j=0;j<HAND_CARD_NUM;++j)
	{
		if(!m_StrJing.CheckIsJing(HandPai[j]) && index<HAND_CARD_NUM)
		{
			m_byArHandPai[station][index] = HandPai[j];
			index++;
		}
	}
}

///���ƣ�AddToHandPai
///���������һ���Ƶ�������
///@param pai ��ӵ�����ֵ
///@return 
void UserData::AddToHandPai(BYTE station,BYTE pai)
{
	if(station <0 || station>=PLAY_COUNT)
		return ;
	if((GetHandPaiCount(station)+3*GetGCPCount(station))>=MAX_HAND_PAI || pai==255)
	{
		return;
	}
	for(int i=0;i<HAND_CARD_NUM;i++)
	{
		if(m_byArHandPai[station][i] == 255)
		{
			m_byArHandPai[station][i] = pai;
			break;
		}
	}
}

///���ƣ�SetHandPaiData
///������������������
///@param  pai[] �������������
void UserData::SetHandPaiData(BYTE station,BYTE pai[],BYTE byCount)
{
	if(station <0 || station>=PLAY_COUNT)
	{
		return ;
	}
	for(int i=0;i<HAND_CARD_NUM;i++)
	{
		m_byArHandPai[station][i] = pai[i];
	}
	m_byArHandPaiCount[station] = byCount;
}

///���ƣ�DelleteAHandPai
///������ɾ��һ��ָ��������
///@param pai Ҫɾ������
void UserData::DelleteAHandPai(BYTE station,BYTE pai)
{
	if(station <0 || station>=PLAY_COUNT)
		return ;
	for(int i=0;i<HAND_CARD_NUM;i++)
	{
		if(m_byArHandPai[station][i] == pai)
		{
			m_byArHandPai[station][i] = 255;
			break;
		}
	}
	MaoPaoSort(m_byArHandPai[station],HAND_CARD_NUM,false);

	BYTE HandPai[HAND_CARD_NUM];
	for(int j=0;j<HAND_CARD_NUM;++j)
	{
		HandPai[j] = m_byArHandPai[station][j];
	}
	int index=0;
	for(int j=0;j<HAND_CARD_NUM;++j)
	{
		if(m_StrJing.CheckIsJing(HandPai[j]))
		{
			m_byArHandPai[station][index] = HandPai[j];
			index++;
		}
	}
	for(int j=0;j<HAND_CARD_NUM;++j)
	{
		if(!m_StrJing.CheckIsJing(HandPai[j]) && index<HAND_CARD_NUM)
		{
			m_byArHandPai[station][index] = HandPai[j];
			index++;
		}
	}
}

///���ƣ�SetHandPaiBack
///���������������Ʊ�
///@param num���õ�����
///@return 
void UserData::SetHandPaiBack(BYTE station,BYTE num)
{
	if(station <0 || station>=PLAY_COUNT)
		return ;
	memset(m_byArHandPai[station],255,sizeof(m_byArHandPai[station]));
	for(int i=0;i<num;i++)
	{
		m_byArHandPai[station][i] = 0;
	}
}

///���ƣ�GetLastHandPai
///������������һ������
///@param 
BYTE UserData::GetLastHandPai(BYTE station)
{
	if(station <0 || station>=PLAY_COUNT)
		return 255;
	for(int i=HAND_CARD_NUM-1;i>=0;i--)
	{
		if(m_byArHandPai[station][i] != 255 && m_bEnableCard[station][i])
		{
			return m_byArHandPai[station][i];
		}
	}
	return 255;
}

///���ƣ�GetSelectHandPai
///���������ѡ�е�һ������
///@param 
///@return 
BYTE UserData::GetSelectHandPai(BYTE station)
{
	if(station <0 || station>=PLAY_COUNT)
		return 255;
	if(m_bySelectIndex<HAND_CARD_NUM && m_bySelectIndex!=255)
		return m_byArHandPai[station][m_bySelectIndex];
	return 255;
}

///���ƣ�IsOutPaiPeople
///�������Ƿ�������
///@param 
///@return  true �� ,false ����
bool UserData::IsOutPaiPeople(BYTE station)
{
	if(station <0 || station>=PLAY_COUNT)
		return false;
	if(GetHandPaiCount(station)%3==2)
	{
		return true;
	}
	return false;
}

///���ƣ�IsHuaPaiInHand
///����������������Ƿ���ڻ���
///@param 
///@return  true �� ,false ����
bool UserData::IsHuaPaiInHand(BYTE station)
{
	if(station <0 || station>=PLAY_COUNT)
		return false;
	for(int i=0;i<HAND_CARD_NUM;i++)
	{
		if(CheckIsHuaPai(m_byArHandPai[station][i]))
		{
			return true;
		}
	}
	return false;
}

///���ƣ�MoveHuaPaiFormHand
///�������������еĻ����Ƶ�����������
///@param 
///@return  ���Ƶ�����
int UserData::MoveHuaPaiFormHand(BYTE station,BYTE byCard)
{
	if(station <0 || station>=PLAY_COUNT)
		return 0;
	//int hua = 0;
	for(int i=0;i<HAND_CARD_NUM;i++)
	{
		/*if(m_byArHandPai[station][i] == 255)
		{
		break;
		}*/
		if(m_byArHandPai[station][i] != byCard)
		{
			continue;
		}
		if(CheckIsHuaPai(byCard))
		{
			//hua++;
			AddToHuaPai(station,m_byArHandPai[station][i]);
			DelleteAHandPai(station,m_byArHandPai[station][i]);
			return 1;
		}
	}
	return 0;
	//return hua;
}

///ͨ��������ȡһ������
BYTE UserData::GetHandPaiFromIndex(BYTE station,int index)
{
	if(station <0 || station>=PLAY_COUNT)
		return 255;
	if(station <0 || station>3)
		return 255;
	return m_byArHandPai[station][index];
}

///ͨ����������һ������
bool UserData::SetHandPaiFromIndex(BYTE station,int index,BYTE pai)
{
	if(station <0 || station>3 || !CMjRef::IsValidateMj(pai))
		return false;
	if(m_byArHandPai[station][index] == 255)
		return false;
	m_byArHandPai[station][index] = pai;
	return true;
}

///�����Ƿ�����
bool UserData::IsHaveHandPaiFromIndex(BYTE station,int index)
{
	if(station <0 || station>3 || index < 0 || index >= HAND_CARD_NUM)
	{
		OutputDebugString(TEXT("�����齫�� IsHaveHandPaiFromIndex ���ݴ���"));
		return false;
	}
	if(m_byArHandPai[station][index] == 255)
	{
		OutputDebugString(TEXT("�����齫��IsHaveHandPaiFromIndex ����"));
		return false;
	}
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///���ƣ�GetUserGangNum
///��������ȡ��Ҹ��Ƶĸ���(���ܣ����ܣ�����)
///@param &an ��������, &ming �������� ,  &bu ��������
///@return ���Ƶ��ܸ���
int UserData::GetUserGangNum(BYTE station,BYTE &an,BYTE &ming , BYTE &bu)
{
	if(station <0 || station>=PLAY_COUNT)
		return 0;
	int all = 0;
	an = 0;
	ming = 0;
	bu = 0;
	for(int i=0;i<5;i++)
	{
		switch(m_UserGCPData[station][i].byType)
		{
		case AT_QUADRUPLET_CONCEALED://����
			an++;
			break;
		case AT_QUADRUPLET://����
			bu++;
			break;
		case AT_QUADRUPLET_REVEALED://����
			ming++;
			break;
		}
	}
	all = ming + an + bu;
	return all;
}

///���ƣ�GetUserChiNum
///��������ҳ��ƴ���
///@param station ���λ��
///@return ���Ƶ��ܸ���
int UserData::GetUserChiNum(BYTE station)
{
	if(station <0 || station>=PLAY_COUNT)
		return 0;
	int num = 0;
	for(int i=0;i<5;i++)
	{
		switch(m_UserGCPData[station][i].byType)
		{
		case ACTION_CHI://����
			num++;
			break;
		}
	}
	return num;
}

///���ƣ�GetUserPengNum
///��������Ҹ��ƴ���
///@param station ���λ��
///@return ���Ƶ��ܸ���
int UserData::GetUserPengNum(BYTE station)
{
	if(station <0 || station>=PLAY_COUNT)
		return 0;
	int num = 0;
	for(int i=0;i<5;i++)
	{
		switch(m_UserGCPData[station][i].byType)
		{
		case ACTION_PENG://����
			num++;
			break;
		}
	}
	return num;
}

///���ƣ�IsUserHaveGangPai
///��������Ҹ���ĳ����
///@param pai ��, &type ����
///@return  true �� ,false ����
bool UserData::IsUserHaveGangPai(BYTE station,BYTE pai,BYTE &type)
{	
	if(station <0 || station>=PLAY_COUNT)
		return false;
	for(int i=0;i<5;i++)
	{
		if(m_UserGCPData[station][i].byType>=ACTION_AN_GANG && m_UserGCPData[station][i].byType<=ACTION_MING_GANG && m_UserGCPData[station][i].byData[0] == pai)
		{
			type = m_UserGCPData[station][i].byType;
			return true;
		}
	}
	return false;
}
///
///���ƣ�IsUserHavePengPai
///����������Ƿ�����ĳ����
///@param pai ��
///@return  true �� ,false ����
bool UserData::IsUserHavePengPai(BYTE station,BYTE pai)
{
	if(station <0 || station>=PLAY_COUNT)
		return false;
	for(int i=0;i<5;i++)
	{
		if(m_UserGCPData[station][i].byType == 255)
			continue;
		if(m_UserGCPData[station][i].byType == ACTION_PENG &&  m_UserGCPData[station][i].byData[0] == pai)
		{
			return true;
		}
	}
	return false;
}

///���ƣ�IsUserHaveChiPai
///����������Ƿ�Թ�ĳ����
///@param pai ��
///@return  true �� ,false ����
bool UserData::IsUserHaveChiPai(BYTE station,BYTE pai)
{
	if(station <0 || station>=PLAY_COUNT)
		return false;
	for(int i=0;i<5;i++)
	{
		if(m_UserGCPData[station][i].byType==ACTION_CHI &&  m_UserGCPData[station][i].iOutpai == pai)
		{
			return true;
		}
	}
	return false;
}

///���ƣ�AddToGCP
///���������һ�����ݵ��ܳ���������
///@param gcpData Ҫ��ӵĳ���������
void UserData::AddToGCP(BYTE station,GCPStructEx *gcpData)
{
	if(station <0 || station>=PLAY_COUNT)
		return ;
	for(int i=0;i<5;i++)
	{
		if(m_UserGCPData[station][i].byType==255)
		{
			m_UserGCPData[station][i].byType = gcpData->byType;
			m_UserGCPData[station][i].iBeStation = gcpData->iBeStation;
			m_UserGCPData[station][i].iOutpai = gcpData->iOutpai;
			m_UserGCPData[station][i].iStation = gcpData->iStation;
			for(int j=0;j<4;j++)
			{
				m_UserGCPData[station][i].byData[j] = gcpData->byData[j];
			}
			break;
		}
	}
}

///���ƣ�DelleteAGCPData
///������ɾ���ܳ���������ָ����������
///@param type ����, pai ��
void UserData::DelleteAGCPData(BYTE station,BYTE type ,BYTE pai)
{			
	if(station <0 || station>=PLAY_COUNT)
		return ;
	for(int i=0;i<5;i++)
	{
		if(m_UserGCPData[station][i].byType == type && (m_UserGCPData[station][i].byData[0]==pai ||m_UserGCPData[station][i].byData[1]==pai || m_UserGCPData[station][i].byData[2]==pai ))
		{
			m_UserGCPData[station][i].Init();
			break;
		}
	}
	ShortGCP(station);//����ܳ�������
}	

///���ƣ�CopyGCPData
///�����������ܳ��������е�������
///@param gcpData ����������
///@return �����ܸ���
int UserData::CopyGCPData(BYTE station,GCPStructEx gcpData[])
{
	if(station <0 || station>=PLAY_COUNT)
		return 0;
	//memcpy(gcpData,m_UserGCPData,sizeof(m_UserGCPData));
	for(int i=0;i<5;i++)
	{
		gcpData[i] = m_UserGCPData[station][i];
	}
	return GetGCPCount(station);
}

///���ƣ�SetGCPData
///���������øܳ��������е�������
///@param gcpData ����������
///@return 
void UserData::SetGCPData(BYTE station,GCPStructEx gcpData[])
{
	if(station <0 || station>=PLAY_COUNT)
		return ;
	for(int i=0;i<5;i++)
	{
		m_UserGCPData[station][i] = gcpData[i];
	}
}

///���ƣ�GetGCPCount
///��������ȡ�ܳ����Ľڵ����
///@param 
///@return ��ó������ܸ���
int UserData::GetGCPCount(BYTE station)
{
	if(station <0 || station>=PLAY_COUNT)
		return 0;
	int count =0;
	for(int i=0;i<5;i++)
	{
		if(m_UserGCPData[station][i].byType!=255)
		{
			count++;
		}
	}
	return count;
}
///���ƣ�GetOnePaiGCPCount
///��������ȡ�ܳ�������ĳ���Ƶ�����
///@param 
///@return ĳ���Ƶ�����
int UserData::GetOnePaiGCPCount(BYTE station,BYTE pai)
{
	if(station <0 || station>=PLAY_COUNT)
		return 0;
	int count =0;
	for(int i=0;i<5;i++)
	{
		if(m_UserGCPData[station][i].byType==255)
			continue;
		for(int j=0;j<4;j++)
		{
			if(m_UserGCPData[station][i].byData[j] == pai && pai!=255)
			{
				count++;
			}
		}
	}
	return count;
}
///���ƣ�ShortGCP
///����������ܳ�������
///@param 
void UserData::ShortGCP(BYTE station)
{
	if(station <0 || station>=PLAY_COUNT)
		return ;
	int index=0;
	GCPStructEx m_TempGCPData[5];
	for(int i=0;i<5;i++)
	{
		m_TempGCPData[i] = m_UserGCPData[station][i];
	}
	memset(m_UserGCPData[station],255,sizeof(m_UserGCPData[station]));
	for(int i=0;i<5;i++)
	{
		if(m_TempGCPData[i].byType != 255)
		{
			m_UserGCPData[station][index] = m_TempGCPData[i];
			index++;
		}
	}
}
///���ƣ�InitGCP
///��������ʼ���ܳ�������
///@param 
void UserData::InitGCP(BYTE station)
{
	if(station <0 || station>=PLAY_COUNT)
		return ;
	for(int i=0;i<5;i++)
	{
		m_UserGCPData[station][i].Init();
	}
}
//////////////////���Ʋ���///////////////////////////////////////////////////////////////////////////////

///���ƣ�AddToOutPai
///���������һ���Ƶ�����������
///@param pai ��
void UserData::AddToOutPai(BYTE station,BYTE pai)
{
	if(station <0 || station>=PLAY_COUNT)
		return ;
	for(int i=0;i<OUT_CARD_NUM;i++)
	{
		if(m_byArOutPai[station][i] == 255)
		{
			m_byArOutPai[station][i] = pai;
			break;
		}
	}
}

///���ƣ�DelleteLastOutPai
///������ɾ�����һ�ų���
///@param 
void UserData::DelleteLastOutPai(BYTE station)
{
	if(station <0 || station>=PLAY_COUNT)
		return ;
	for(int i=0;i<OUT_CARD_NUM;i++)
	{
		if(m_byArOutPai[station][i] == 255 && i>0)
		{
			m_byArOutPai[station][i-1] = 255;
			break;
		}
	}
}

///���ƣ�SetOutPaiData
///���������ó�������
///@param pai[] ��������
///@return 
void UserData::SetOutPaiData(BYTE station,BYTE pai[],BYTE byCount)
{
	if(station <0 || station>=PLAY_COUNT)
	{
		return ;
	}
	//memcpy(m_byArOutPai[station],pai,sizeof(m_byArOutPai[station]));
	for(int i=0;i<OUT_CARD_NUM;i++)
	{
		m_byArOutPai[station][i] = pai[i] ;
	}
	m_byArOutPaiCount[station] = byCount;
}

///���ƣ�CopyOutPai
///������������ҵĳ���
///@param pai[] ��������
///@return ���Ƶ�����
int UserData::CopyOutPai(BYTE station,BYTE pai[])
{
	if(station <0 || station>=PLAY_COUNT)
		return 0;
	//memcpy(pai,m_byArOutPai,sizeof(m_byArOutPai));
	for(int i=0;i<OUT_CARD_NUM;i++)
	{
		pai[i] = m_byArOutPai[station][i];
	}
	return GetPaiNum(station,m_byArOutPai[station],OUT_CARD_NUM);
}

///���ƣ�GetOutPaiCount
///��������ȡ��ҵĳ�������
///@param 
///@return ���Ƶ�����
int UserData::GetOutPaiCount(BYTE station)
{
	if(station <0 || station>=PLAY_COUNT)
		return 0;
	int num = 0;
	for(int i=0;i<OUT_CARD_NUM;i++)
	{
		if(m_byArOutPai[station][i] != 255)
		{
			num++;
		}
	}
	return num;
}
///���ƣ�GetOutPaiCount
///��������ȡ���ĳ���Ƶĳ�������
///@param 
///@return ĳ���Ƴ��Ƶ�����
int UserData::GetOneOutPaiCount(BYTE station,BYTE pai)
{
	if(station <0 || station>=PLAY_COUNT)
		return 0;
	int num = 0;
	for(int i=0;i<OUT_CARD_NUM;i++)
	{
		if(m_byArOutPai[station][i] != 255 && m_byArOutPai[station][i] == pai)
		{
			num++;
		}
	}
	return num;
}
/////////////////////���Ʋ���////////////////////////////////////////////////////////

///���ƣ�AddToHuaPai
///���������һ�Ż��Ƶ�����������
///@param pai ����
void UserData::AddToHuaPai(BYTE station,BYTE pai)
{
	if(station <0 || station>=PLAY_COUNT)
		return ;
	for(int i=0;i<HUA_CARD_NUM;i++)
	{
		if(m_byArHuaPai[station][i] == 255)
		{
			m_byArHuaPai[station][i] = pai;
			break;
		}
	}
}

///���ƣ�SetHuaPaiData
///���������û�������
///@param pai[] ��������
///@return 
void UserData:: SetHuaPaiData(BYTE station,BYTE pai[])
{
	if(station <0 || station>=PLAY_COUNT)
		return ;
	memcpy(m_byArHuaPai[station],pai,sizeof(m_byArHuaPai[station]));
}

///���ƣ�CopyHuaPai
///������������ҵĻ���
///@param pai[] ��������
///@return 
int UserData::CopyHuaPai(BYTE station,BYTE pai[])
{
	if(station <0 || station>=PLAY_COUNT)
		return 0;
	SortHuaPai(station,false);
	int count =0;
	for(int i=0;i<HUA_CARD_NUM;i++)
	{
		pai[i] = m_byArHuaPai[station][i];
		if(m_byArHuaPai[station][i]!=255)
		{
			count++;
		}
	}
	return count;
}

///����Ƿ���
bool UserData::CheckIsHuaPai(BYTE pai)
{
	//if(pai>=CMjEnum::MJ_TYPE_FCHUN && pai != 255)
	//	return true;
	if(pai == CMjEnum::MJ_TYPE_FD || CMjEnum::MJ_TYPE_ZHONG == pai || CMjEnum::MJ_TYPE_FA == pai || CMjEnum::MJ_TYPE_BAI == pai)
		return true;
	return false;
}
///////////////////////���Ʋ���//////////////////////////////////////////////////////////////////

///���ƣ�SetMenPaiData
///������������������
///@param  pai[] ��������
///@return 
void UserData::SetMenPaiData(BYTE station,BYTE pai[])
{
	if(station <0 || station>=PLAY_COUNT)
		return ;
	memcpy(m_iArMenPai[station],pai,sizeof(m_iArMenPai[station]));
}

///���ƣ�CopyMenPai
///������������ҵ�����
///@param  pai[] ��������
///@return �����������
int UserData::CopyMenPai(BYTE station,BYTE pai[])
{
	if(station <0 || station>=PLAY_COUNT)
		return 0;
	for(int i=0;i<MEN_CARD_NUM;i++)
	{
		pai[i] = m_iArMenPai[station][i];
	}
	return GetPaiNum(station,m_iArMenPai[station],MEN_CARD_NUM);
}

///���ƣ�ChangeMenPai
///����������ת��
///@param  pai[] ��������
///@return �����������
void UserData::ChangeMenPai(BYTE station)
{
	if(station <0 || station>=PLAY_COUNT)
		return ;
	BYTE index = 0;
	bool shang = false;
	for(int i=0;i<MEN_CARD_NUM;i++)
	{
		if(m_iArMenPai[station][i]!=255 && i%2==0)
		{
			index = i/2;
			shang =true;
		}
		else if(m_iArMenPai[station][i]!=255)
		{
			index = i/2;
			shang = false;
		}
		if(i%2==0)//����һ��
		{	
			m_byMenPaiData[station][i/2][0] = m_iArMenPai[station][i];    //ת�������������
		}
		else//����һ��
		{
			m_byMenPaiData[station][i/2][1] = m_iArMenPai[station][i];    //ת�������������
		}
	}

	if(shang)//���һ�����Ϸ���Ҫǿ�ƻ������·�
	{
		m_byMenPaiData[station][index][1] = m_byMenPaiData[station][index][0] ;
		m_byMenPaiData[station][index][0] = 255;
	}

}
///��������ȡĳ��ҵ���������
int UserData::GetMenPaiCount(BYTE station)
{
	if(station <0 || station>=PLAY_COUNT)
		return false;
	int count = 0;
	for(int i=0;i<MEN_CARD_NUM;++i)
	{
		if(m_iArMenPai[station][i] != 255)
		{
			count++;
		}
	}
	return count;
}

///���ƣ�ChangeAllHandPai
///����������
///@param  station λ��, pai[] ��, count������
void UserData::ChangeAllHandPai(BYTE station,BYTE pai[],BYTE count)
{
	if(station <0 || station>=PLAY_COUNT)
		return ;
	for(int i=0;i<count;i++)
	{
		if(!CMjRef::IsValidateMj(pai[i]))
			continue;
		if(m_byArHandPai[station][i] == 255)
			break;
		m_byArHandPai[station][i] = pai[i];
	}
}

///���ƣ�ChangeAllHandPai
///��ָ������
///@param  station λ��, pai[] ��, handpai[]Ҫ����������, count������
void UserData::ChangeSomeHandPai(BYTE station,BYTE pai[],BYTE handpai[],BYTE count)
{
	if(station <0 || station>=PLAY_COUNT)
		return ;
	for(int i=0;i<count;i++)
	{
		if(!CMjRef::IsValidateMj(pai[i]) || !CMjRef::IsValidateMj(handpai[i]))
			continue;
		if(IsHaveAHandPai(station,handpai[i]))
		{
			DelleteAHandPai(station,handpai[i]);
			AddToHandPai(station,pai[i]);
		}
	}
}

///���ƣ�SetMeNextPai
///�����Լ�����һ����
///@param  station λ��,pai ��
void UserData::SetMeNextPai(BYTE station,BYTE pai)
{
	
}

///���ƣ�SetGameNextPai
///������ǽ����һ����
///@param  pai ��
void UserData::SetGameNextPai(BYTE pai)
{
	if(m_MenPai.byStartIndex == 255 )
		return;
	if(m_MenPai.byMenPai[m_MenPai.byStartIndex] == 255)
		return;
	m_MenPai.byMenPai[m_MenPai.byStartIndex]  = pai;
}


///���ƣ�GetPaiNum
///��������ȡ���������Ч������
///@param  pai[] Ҫ����������, count ��Ч�Ƶ�����
///@return 
int UserData::GetPaiNum(BYTE station,BYTE pai[],BYTE count)
{
	int num=0;
	for(int i=0;i<count;i++)
	{
		if(pai[i]!=255)
		{
			num++;
		}
	}
	return num;
}


///���ƣ�InitData
///��������ʼ������
///@param 
///@return 
void UserData::InitData()
{
	memset(m_byArHandPai,255,sizeof(m_byArHandPai));			//���Ʋ�����20�ţ�255Ϊ������־
	memset(m_byArHandPaiCount,0,sizeof(m_byArHandPaiCount));	//��������
	memset(m_byArOutPai,255,sizeof(m_byArOutPai));				//���Ʋ�����160�ţ�255Ϊ������־
	memset(m_byArOutPaiCount,0,sizeof(m_byArOutPaiCount));		//��������
	memset(m_byArHuaPai,255,sizeof(m_byArHuaPai));				//���Ʋ�����10�ţ�255Ϊ������־
	memset(m_iArMenPai,255,sizeof(m_iArMenPai));				//���Ʋ�����40�ţ�255Ϊ������־



	memset(m_byMenPaiData,255,sizeof(m_byMenPaiData));	//ת�������������
		
	memset(m_byGuanXi,0,sizeof(m_byGuanXi));			//�����ܹ�ϵ����
	memset(m_bEnableCard,1,sizeof(m_bEnableCard));		//�Ƿ���õ���
	memset(m_bySetMoPai,255,sizeof(m_bySetMoPai));		//ץ��ǿ��ָ��ֵ�������ã�

	m_StrJing.Init();//��ʼ������
	m_MenPai.Init();//��ʼ����
	for(int i=0;i<PLAY_COUNT;++i)
	{//�������ݽṹ
		m_SetData[i].Init();
		m_bHaveOut[i] = false;
	}
	for(int i=0;i<5;i++)
	{
		m_UserGCPData[0][i].Init();
		m_UserGCPData[1][i].Init();
		m_UserGCPData[2][i].Init();
		m_UserGCPData[3][i].Init();
	}	

	memset(m_bTing,0,sizeof(m_bTing));				//����Ƿ�����
	memset(m_byTingType,0,sizeof(m_byTingType));	//�����������
	memset(m_bWinner,0,sizeof(m_bWinner));			//����Ƿ�Ӯ��
	memset(m_bTuoGuan,0,sizeof(m_bTuoGuan));		//����Ƿ��й�
	memset(m_bFoceLeave,0,sizeof(m_bFoceLeave));	//����Ƿ��Ѿ�����

	memset(m_byCanOutCard,255,sizeof(m_byCanOutCard));///ͣ�ƻ������������ܴ������
	memset(m_byMenFeng,255,sizeof(m_byMenFeng));	///�ŷ�	
	memset(m_bFoceLeave,0,sizeof(m_bFoceLeave));	///	����Ƿ��Ѿ�����
	memset(m_bTing,0,sizeof(m_bTing));				///	����Ƿ�����
	memset(m_bTuoGuan,0,sizeof(m_bTuoGuan));		///	����Ƿ��й�
	memset(m_bWinner,0,sizeof(m_bWinner));			///	����Ƿ�Ӯ��
	memset(m_byLastZhuaPai,255,sizeof(m_byLastZhuaPai));///	���ץ������
	memset(m_bHaveOut,0,sizeof(m_bHaveOut));			///	��¼����Ƿ��������

	m_byFoceLeavCount=0;				////����뿪������
	m_bMeOutPai = false;				///�Ƿ��ҳ���
	m_bySelectIndex = 255;				///��ǰѡ��������
	m_bisTing = 0;						///��ǰ����Ƿ�����
	m_byLastOutPai = 255;				///���������
	m_byMeZhuaPai = 255;				///��ǰ������ץ��
	m_byNowOutStation = 255;			///��ǰ����λ��
	m_byLastOutStation = 255;			///�ϴγ���λ��
	m_byBaoPaiUser = 255;				///�������
	m_byOtherOutPai = 255;				///��ǰ������Ҵ������
	memset(m_bSiziFinish,0,sizeof(m_bSiziFinish));			///	����Ƿ񷵻���ɫ�ӽ�����Ϣ
	m_bWaitSezi = false;//�Ƿ���ȴ�ɫ�Ӷ�������״̬
	///��ǰץ�Ʒ���true ˳ʱ�룬false ��ʱ��
	m_bZhuaPaiDir = true;
	//ͬ������뿪������
	m_byAgreeLeaveNum = 0;
	m_byApplyMaxAction = 0;//��ҵ�ǰ���������¼�
	m_byCanDoMaxAction = 0;//���μ����������������
} 