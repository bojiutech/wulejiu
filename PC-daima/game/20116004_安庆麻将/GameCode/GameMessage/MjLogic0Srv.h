/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #pragma once

#include "UserData.h"
//#include "..\GameMessage\ThingStruct.h"

#include "..\ChangeFile\GameDataEx.h"
#include "..\ChangeFile\UserDataEx.h"
enum
{
	RESULT_TYPE_NONE_WIN_LOSE = 0,
	RESULT_TYPE_LIUJU,
	RESULT_TYPE_ZIMO,
	RESULT_TYPE_BEI_ZIMO,
	RESULT_TYPE_HUPAI,
	RESULT_TYPE_FANGQIANG
};
/// �������齫�߼���
class  CMjLogic0Srv
{
public:

	/// ����Ƿ���
	bool			m_bisTing[4];				
	///�Ƿ��й�
	bool			m_bistuoguan[4];							
	/// ��������
/*	MjMenPaiData    m_MenPai;                  
	/// �齫��������
	MjRuleSet       m_mjRule;					
	/// �齫��������
	ActionRuleSet   m_mjAction;               
	/// �齫�������
	CountFenRuleSet m_mjFenRule;				
	/// �齫��������
	HuPaiRuleSet    m_mjHuRule;				
	/// �齫��������
	HuPaiTypeSet	m_mjHuType;				
	/// �齫�������ͷ���
	HuPaiFanSet		m_mjHuFan;		

	///��ҵ����ݣ����ƣ����ƣ��������Ƶ�
	UserData       m_UserData[4];		*/	
	
	/// ��Ϸ״̬
	BYTE			m_GameStatus;			
	/// ���ڳ����û�
	BYTE			m_iOutCardPeople;		
	///ׯ��λ��
	BYTE			m_byNtStation;				
	/// ����
	BYTE			byMainJing;		
	/// ����
	BYTE			byLessJing;	
	/// ��������
	BYTE			byMainJingNum[PLAY_COUNT];	
	/// ��������
	BYTE			byLessJingNum[PLAY_COUNT];
	/// �ж�����Ƿ�����ܺ����ơ�����¼���һ�Ρ�
	BYTE			m_byCPGHjing[PLAY_COUNT];				
	///����ܷ��뿪
	bool            m_bUserCanLeave;
	///���������
	bool			m_bFoceLeave[PLAY_COUNT];	
	///���������
	int				m_iFoceLeavCount;							
	///ÿ���Ƶĳ��ƴ���
	BYTE            m_byOutCount[60];	
	///��¼�齫�Ķ������ӿ�ʼ�¼��Ժ󵽽���ֻ��¼1���¼���0���ͣ�1λ�ã�2��ֵ������¼�йܣ������뿪���������޹ص��¼���
	BYTE			m_byRecordAction[10][3];

	///�齫����
	GUID			m_GuidJiangNum;
	///////////////////����������//////////////////////////////////////
	bool			m_bhaveset[4];//lym0806 super
	int				m_isetcount[4];//lym0806 super
	BYTE			m_setpai[4][20];//lym0806 super
	////////////////////////////////////////////////////////////////////
	///��¼��ҵ��߼�λ�ã�0����1����2����3��
	BYTE           m_byLogicStation[4];

public:
	/// ���
	void CountFen(tagHuPaiEx& verb,tagCountFenEx& CountFen,UINT uBasePoint=1, bool bMultiHePai = false);
	/// �Ƚ�s1,s2˭�ȳ��� ��s1 �����򷵻�1��s2�򷵻�-1������򷵻�0
	int CompareStation(int s1,int s2);
	/// �Ƚϳ������ȼ� c1�� �����򷵻�1 ��c2�򷵻�-1�� ����򷵻�0
	int Compare();
	/// �õ��¼�
    int GetNextStation(int station,bool shun=false);
	///�õ���һ��λ��
    int GetUpStation(int station);
	
public:
	/// ����
	virtual void DisPatchCard();
	///ׯ������
	void TiaoPai();
	///��������ȡ�ֺ���
	void GetGoodPai();
	///ץһ����
	int GetPai(int station,bool head);
	///���ʣ�����Ƶ�����
	int GetReMainMenPaiNum();
	/// ��ɫ��
	void CastSeZi(BYTE *sezi0=NULL,BYTE *sezi1=NULL,BYTE *sezi2=NULL);
	/// ��ʼ��
	virtual void Init();
	///��ȡ�¼�ׯ��λ��
	int GetNextNt(int station,bool nowin=false);
	///ת����������,station���Ʒ�λ��index����
	void ChangeMenPai();


	///��ʼ������
	CMjLogic0Srv(void);
	virtual~CMjLogic0Srv(void);//lu20090116��c++test���������


public:

	///����������ɫ��ֵȷ������
	void MakeMainJing(BYTE sezi0,BYTE sezi1);
	///��������������ȷ������
	void MakeLessJing();
	///��¼��ҵĶ���
	void RecordUserAction( BYTE ActionSt,BYTE BeSt,BYTE ActionType0,BYTE ActionType1,BYTE pai);

	///���������㾫�Ƹ���
	void CountJingPaiNum();

	///��ȡ�߼�λ��
	BYTE GetLogicStation(BYTE station);


public:


};


