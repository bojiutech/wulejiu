/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               

#include "stdafx.h"
#include "MjLogic0Srv.h"
#include "../ChangeFile/CountFen.h"

///���ƣ�CMjLogic0Srv
///��������ʼ���������ã��������͵�
///@param 
///@return 
CMjLogic0Srv::CMjLogic0Srv(void)
{	
    m_GameStatus = 255;				// ��Ϸ״̬
	m_iOutCardPeople = 255;			// ���ڳ����û�
	m_byNtStation = 255;			// ׯ��λ��
	byMainJing = 255;				// ����
	byLessJing = 255;				// ����
	memset(m_setpai,255,sizeof(m_setpai));		//lym0806 super
	memset(m_bhaveset,0,sizeof(m_bhaveset));	//lym0806 super
	memset(m_isetcount,0,sizeof(m_isetcount));	//lym0806 super
	memset(m_byOutCount,0,sizeof(m_byOutCount));//ÿ���Ƶĳ��ƴ���
	::memset(&m_bistuoguan,0,sizeof(m_bistuoguan));//����й�
	::memset(&m_bFoceLeave,0,sizeof(m_bFoceLeave));///���������
	m_iFoceLeavCount = 0;			///���������
	memset(byMainJingNum,0,sizeof(byMainJingNum));//��������
	memset(byLessJingNum,0,sizeof(byLessJingNum));//��������
	memset(m_byCPGHjing,255,sizeof(m_byCPGHjing));//�ж�����Ƿ�����ܺ����ƣ���¼���һ��
	///��¼�齫�Ķ������ӿ�ʼ�¼��Ժ󵽽���ֻ��¼1���¼���0���ͣ�1��ֵ������¼�йܣ������뿪���������޹ص��¼���
	memset(m_byRecordAction,255,sizeof(m_byRecordAction));
}

///���ƣ�DisPatchCard
///�����������ƣ�����������ҷ��ơ�
///@param 
///@return 
void CMjLogic0Srv::DisPatchCard()////������
{

}
///���ƣ�GetGoodPai
///��������ȡ�ֺ���
///@param 
///@return 
void CMjLogic0Srv::GetGoodPai()
{
	//��ȷ��λ��
	int station = 0;
	station = rand()%PLAY_COUNT;
	if(station<0 || station>= PLAY_COUNT)//λ�ò�����
		return;
	//��ȷ����ʲô����
	
}
///���ƣ�GetPai
///������ץһ����
///@param station ץ����ҵ�λ�� , head  �Ƿ��ǰ��ץ
///@return ץ������ֵ
int CMjLogic0Srv::GetPai(int station,bool head)
{
	return 0;
}

///���ƣ�GetReMainMenPaiNum
///���������ʣ�����Ƶ�����
///@param 
///@return ʣ�����Ƶ�����
int CMjLogic0Srv::GetReMainMenPaiNum()
{
	int num = 0;
	return num;
}

///���ƣ�TiaoPai
///������ׯ������
///@param 
///@return 
void CMjLogic0Srv::TiaoPai()////
{
}

///���ƣ�CastSeZi
///��������ɫ��
///@param *sezi0 ��һ��ɫ�� ,*sezi1 �ڶ���ɫ��,*sezi2 ������ɫ��
///@return 
void CMjLogic0Srv::CastSeZi(BYTE *sezi0,BYTE *sezi1,BYTE *sezi2)
{

}

///���ƣ�Init
///��������ʼ��
///@param 
///@return 
void CMjLogic0Srv::Init()
{
	for(int i=0;i<4;i++)
	{
		m_bisTing[i] = false;
	}
	memset(m_byOutCount,0,sizeof(m_byOutCount));		///ÿ���Ƶĳ��ƴ���
	::memset(&m_bistuoguan,0,sizeof(m_bistuoguan));		///�Ƿ��й�״̬ 
	::memset(&m_bFoceLeave,0,sizeof(m_bFoceLeave));		///���������
}

///���ƣ�GetNextStation
///�������õ��¼�λ��
///@param  station ����¼�λ��,shun �Ƿ�˳ʱ��
///@return �¼�λ��
int CMjLogic0Srv::GetNextStation(int station ,bool shun)
{	
	int re = -1;
	if(shun)//˳ʱ��
	{
		re = (station + 1)%PLAY_COUNT;
	}
	else
	{
		re = (station + 3)%PLAY_COUNT;
	}

	return re;
}

///���ƣ�GetUpStation
///��������ȡ�ϼ�λ��
///@param station ��ǰ���λ��
///@return �ϼ�λ��
int CMjLogic0Srv::GetUpStation(int station)
{
	int re = -1;
	return re;
}
///���ƣ���������
///������~CMjLogic0Srv
///@param 
///@return 
CMjLogic0Srv::~CMjLogic0Srv(void)
{
}

///���ƣ�Compare
///�������Ƚϳ������ȼ� c1�� �����򷵻�1 ��c2�򷵻�-1�� ����򷵻�0
///@param 
///@return 
int CMjLogic0Srv::Compare()
{
	return 0;
}

///���ƣ�CompareStation
///�������Ƚ�s1,s2˭�ȳ��� ��s1 �����򷵻�1��s2�򷵻�-1������򷵻�0
///@param s1 ���λ��, s2 ���λ��
///@return 
int CMjLogic0Srv::CompareStation(int s1,int s2)
{
	return 0;
}

///���ƣ�GetNextNt
///��������ȡ�¼�ׯ��λ��
///@param  station ��ǰׯ��λ��, nowin �Ƿ�Ӯ��
///@return �¾�ׯ��λ��
int CMjLogic0Srv::GetNextNt(int station,bool nowin)
{
	return 0;
}

///���ƣ�ChangeMenPai
///������ת����������,�������������е�����ת����ÿ����ҵ�����������
///@param 
///@return 
void CMjLogic0Srv::ChangeMenPai()
{
}

///���ƣ�ChangeMenPai
///����������ɫ��ֵȷ������
///@param  sezi0 ɫ��1��ֵ, sezi1 ɫ��2��ֵ
///@return 
void CMjLogic0Srv::MakeMainJing(BYTE sezi0,BYTE sezi1)
{
}

///���ƣ�MakeLessJing
///��������������ȷ������
///@param 
///@return 
void CMjLogic0Srv::MakeLessJing()
{
}
///��¼��ҵĶ���
void CMjLogic0Srv::RecordUserAction( BYTE ActionSt,BYTE BeSt,BYTE ActionType0,BYTE ActionType1,BYTE pai)
{///��¼�齫�Ķ������ӿ�ʼ�¼��Ժ󵽽���ֻ��¼1���¼���0���ͣ�1λ�ã�2��ֵ������¼�йܣ������뿪���������޹ص��¼���
	BYTE data0=255,data1=255,data2=255;
	data0 = ActionType0 + ActionType1*20;
	data1 = ActionSt*10 + BeSt;
	data2 = pai;
	if(m_byRecordAction[9][0]!=255)
	{//��¼����,�ƶ�λ��
		for(int i=0;i<9;i++)
		{
			m_byRecordAction[i][0] = m_byRecordAction[i+1][0];
			m_byRecordAction[i][1] = m_byRecordAction[i+1][1];
			m_byRecordAction[i][2] = m_byRecordAction[i+1][2];
		}
		m_byRecordAction[9][0] = data0;
		m_byRecordAction[9][1] = data1;
		m_byRecordAction[9][2] = data2;
	}
	else
	{
		int index = 0;
		for(int i=0;i<9;i++)
		{
			if(m_byRecordAction[i][0] == 255)
			{
				index = i;
				break;
			}
		}
		m_byRecordAction[index][0] = data0;
		m_byRecordAction[index][1] = data1;
		m_byRecordAction[index][2] = data2;
	}
}

///���ƣ�CountFen
///���������������������ֽӿڣ�����ÿ����ҵķ����ͽ��
///@param verb �������ݰ�, CountFen ������ݰ�
///@return 
void CMjLogic0Srv::CountFen(tagHuPaiEx& verb,tagCountFenEx& CountFen,UINT uBasePoint,bool bMultiHePai)
{
}

///���ƣ�CountJingPaiNum
///���������㾫�Ƹ���
///@param 
///@return 
void CMjLogic0Srv::CountJingPaiNum()
{
}

///��ȡ�߼�λ��
BYTE CMjLogic0Srv::GetLogicStation(BYTE station)
{
	///��¼��ҵ��߼�λ�ã�0����1����2����3��
	if(station<4)
		return m_byLogicStation[station];
	return 255;
}