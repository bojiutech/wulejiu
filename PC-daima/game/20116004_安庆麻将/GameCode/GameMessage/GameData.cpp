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
#include "GameData.h"

GameData::GameData(void)
{

	m_iHuangZhuangCount = 0;
					
	///����ı���
	basepoint = 0;	
	///Ҫ������¼�id
	ApplyThingID = 255;
	//�Ƿ���ʾ̨��
	m_bShowTax = 0;

	memset(m_byThingNext,255,sizeof(m_byThingNext));

	InitData();
	LoadIni();
}

GameData::~GameData(void)
{

}


///���������¼��ĺ���¼�
void GameData::SetThingNext()
{
	//��Ϸ��ʼ�¼�
/*	T_Begin.byNext = m_byThingNext[THING_BEGIN];*/
	//�׾��Զ�Ϊׯ�¼�	
//	T_DongNt.byNext = m_byThingNext[THING_DONG_NT];
	//�׾���2��ɫ�ӵĵ�����Ϊׯ�¼�	
	T_TwoSeziNt.byNext = m_byThingNext[THING_2SEZI_NT];
	//�׾���2��ɫ�Ӷ�ׯ�Һ����Ƶ��¼�	
	T_TwoSeziNtAndGetPai.byNext = m_byThingNext[THING_2SEZI_NT_GP];
	//�׾�������2��ɫ�Ӷ�ׯ���¼�	
	T_TurnSeziNt.byNext = m_byThingNext[THING_TURN_2SEZI_NT];
	//��2��ɫ���¼������Ʒ����¼�
//	T_TwoSeziDir.byNext = m_byThingNext[THING_2SEZI_DIR];
	//��2��ɫ���¼������Ʒ�������Ƶ��¼�
//	T_TwoSeziDirAndGetPai.byNext = m_byThingNext[THING_2SEZI_DIR_GP];
	//��2��ɫ���¼������Ƶ��¼�	
	T_TwoSeziGetPai.byNext = m_byThingNext[THING_2SEZI_GP];
//����ǰ�¼�
	//�����¼�	
//	T_SendPai.byNext = m_byThingNext[THING_SEND_PAI];
	//�����¼�	
	T_TiaoPai.byNext = m_byThingNext[THING_TIAO_PAI];
	//��2��ɫ�Ӷ������¼�
	T_TwoSeziJing.byNext = m_byThingNext[THING_2SEZI_JING];
	//��1��ɫ�Ӷ������¼�
	T_OneSeziJin.byNext = m_byThingNext[THING_1SEZI_JIN];
	//Ϊ������Ҳ����¼�
	T_AllBuHua.byNext = m_byThingNext[THING_ALL_BUHUA];
	//������Ҳ����¼�	
	T_OneBuHua.byNext = m_byThingNext[THING_ONE_BUHUA];
//���������¼�
	//ׯ�ҿ�ʼ����֪ͨ�¼�
//	T_BeginOutPai.byNext = m_byThingNext[THING_BEGIN_OUT];
	//�����¼�
//	T_OutPai.byNext = m_byThingNext[THING_OUT_PAI];
	//ץ���¼�
	T_ZhuaPai.byNext = m_byThingNext[THING_ZHUA_PAI];
	//�����¼�
	T_ChiPai.byNext = m_byThingNext[THING_CHI_PAI];
	//�����¼�
	T_PengPai.byNext = m_byThingNext[THING_PENG_PAI];

	//�����¼�
	T_GangPai.byNext = m_byThingNext[THING_GANG_PAI];
	//�����¼�
	T_TingPai.byNext = m_byThingNext[THING_TING_PAI];
//���Ƽ����ƺ��¼�
	//���¼�
//	T_HuPai.byNext = m_byThingNext[THING_HU_PAI];
	//����¼�	
//	T_CountFen.byNext = m_byThingNext[THING_COUNT_FEN];
	//���������¼�
	T_EndHandle.byNext = m_byThingNext[THING_ENG_HANDLE];
	//���������������¼�
	T_UnnormalEndHandle.byNext = m_byThingNext[THING_ENG_UN_NORMAL];
}

///����ĳ���¼��ĺ���¼�
void GameData::SetThingNext(BYTE id)
{
//	switch(id)
//	{
////����ǰ�¼�
//	case THING_BEGIN:			//��Ϸ��ʼ�¼�
//		T_Begin.byNext = m_byThingNext[id];
//		break;
//	case THING_DONG_NT:			//�׾��Զ�Ϊׯ�¼�	
//		T_DongNt.byNext = m_byThingNext[id];
//		break;
//	case THING_2SEZI_NT:		//�׾���2��ɫ�ӵĵ�����Ϊׯ�¼�	
//		T_TwoSeziNt.byNext = m_byThingNext[id];
//		break;
//	case THING_2SEZI_NT_GP:		//�׾���2��ɫ�Ӷ�ׯ�Һ����Ƶ��¼�	
//		T_TwoSeziNtAndGetPai.byNext = m_byThingNext[id];
//		break;
//	case THING_TURN_2SEZI_NT:	//�׾�������2��ɫ�Ӷ�ׯ���¼�	
//		T_TurnSeziNt.byNext = m_byThingNext[id];
//		break;
//	case THING_2SEZI_DIR:		//��2��ɫ���¼������Ʒ����¼�
//		T_TwoSeziDir.byNext = m_byThingNext[id];
//		break;
//	case THING_2SEZI_DIR_GP:	//��2��ɫ���¼������Ʒ�������Ƶ��¼�
//		T_TwoSeziDirAndGetPai.byNext = m_byThingNext[id];
//		break;
//	case THING_2SEZI_GP:		//��2��ɫ���¼������Ƶ��¼�	
//		T_TwoSeziGetPai.byNext = m_byThingNext[id];
//		break;
////����ǰ�¼�
//	case THING_SEND_PAI:		//�����¼�	
//		T_SendPai.byNext = m_byThingNext[id];
//		break;
//	case THING_TIAO_PAI:		//�����¼�	
//		T_TiaoPai.byNext = m_byThingNext[id];
//		break;
//	case THING_2SEZI_JING:		//��2��ɫ�Ӷ������¼�
//		T_TwoSeziJing.byNext = m_byThingNext[id];
//		break;
//	case THING_1SEZI_JIN:		//��1��ɫ�Ӷ������¼�
//		T_OneSeziJin.byNext = m_byThingNext[id];
//		break;
//	case THING_ALL_BUHUA:		//Ϊ������Ҳ����¼�
//		T_AllBuHua.byNext = m_byThingNext[id];
//		break;
//	case THING_ONE_BUHUA:		//������Ҳ����¼�	
//		T_OneBuHua.byNext = m_byThingNext[id];
//		break;
////���������¼�
//	case THING_BEGIN_OUT:		//ׯ�ҿ�ʼ����֪ͨ�¼�
//		T_BeginOutPai.byNext = m_byThingNext[id];
//		break;
//	case THING_OUT_PAI:			//�����¼�
//		T_OutPai.byNext =		m_byThingNext[id];
//		break;
//	case THING_ZHUA_PAI:		//ץ���¼�
//		T_ZhuaPai.byNext = m_byThingNext[id];
//		break;
//	case THING_CPG_NOTIFY:		//�ܳ���֪ͨ�¼��¼�
//		break;
//	case THING_CHI_PAI:			//�����¼�
//		T_ChiPai.byNext = m_byThingNext[id];
//		break;
//	case THING_PENG_PAI:		//�����¼�
//		T_PengPai.byNext = m_byThingNext[id];
//		break;

//		break;
//	case THING_SAO_HU:			//ɨ���¼�
//		T_SaoHu.byNext = m_byThingNext[id];
//		break;
//	case THING_GANG_PAI:		//�����¼�
//		T_GangPai.byNext = m_byThingNext[id];
//		break;
//	case THING_TING_PAI:		//�����¼�
//		T_TingPai.byNext = m_byThingNext[id];
//		break;
////���������¼�
////���Ƽ����ƺ��¼�
//	case THING_HU_PAI:			//���¼�
//		T_HuPai.byNext = m_byThingNext[id];
//		break;
//	case THING_COUNT_FEN:		//����¼�	
//		T_CountFen.byNext = m_byThingNext[id];
//		break;
//	case THING_ENG_HANDLE:		//���������¼�
//		T_EndHandle.byNext = m_byThingNext[id];
//		break;
//	case THING_ENG_UN_NORMAL:	//���������������¼�
//		T_UnnormalEndHandle.byNext = m_byThingNext[id];
//		break;
//	}
	 
}

///��ʼ������
void GameData::InitData()
{

	memset(m_byThingRecord,255,sizeof(m_byThingRecord));
	memset(m_bGangState,0,sizeof(m_bGangState));//��¼����״̬��ӵ�ڸܿ��͸ܺ���

	m_byNtStation	= 255;	//ׯ��λ��

	ApplyThingID	= 255;	///Ҫ������¼�	DWJ
	
	m_byThingDoing	= 255;	///���ڷ������¼���

	m_byWatingThing	= 255;	//���ڵȴ���Ӧ���¼�

	m_iRemaindTime = 0;



	///��ִ���¼�
	m_byMaxAction = ACTION_NO;
		
	

	///�������¼�,��ʱ����
	temp_ChiPai.Clear();
	///�������¼�,��ʱ����
	temp_PengPai.Clear();
	///�������¼�,��ʱ����
	temp_GangPai.Clear();

	///��Ϸ��ʼ�¼�
	T_Begin.Clear();

	///�Զ�Ϊׯ�¼�
	T_DongNt.Clear();

	///��2��ɫ�ӵĵ�����Ϊׯ�¼�
	T_TwoSeziNt.Clear();

	///��2��ɫ��ȷ��ׯ�Һ����Ƶ�λ���¼�
	T_TwoSeziNtAndGetPai.Clear();

	///������2��ɫ��ȷ��ׯ��
	T_TurnSeziNt.Clear();

	///��2��ɫ��ȷ������λ���¼�
	T_TwoSeziDir.Clear();

	///��2��ɫ��ȷ������λ�ã������ͣ������Ƶ㣨��С�㣩�¼�
	T_TwoSeziDirAndGetPai.Clear();

	///��2��ɫ��ȷ�����ƶ����¼�
	T_TwoSeziGetPai.Clear();

	///�����¼�
	T_SendPai.Clear();

	///�����¼�
	T_TiaoPai.Clear();

	///��ɫ��2��ɫ�Ӷ������¼�
	T_TwoSeziJing.Clear();

	///��ɫ��1��ɫ�Ӷ������¼�
	T_OneSeziJin.Clear();

	///������Ҳ����¼�
	T_AllBuHua.Clear();

	///������Ҳ����¼�
	T_OneBuHua.Clear();

	///��ʼ����֪ͨ�¼�
	T_BeginOutPai.Clear();

	///�����¼�
	T_OutPai.Clear();

	///ץ�����¼�
	T_ZhuaPai.Clear();

	/////�����ܺ���֪ͨ�¼����¼�
	T_CPGNotify[PLAY_COUNT].Clear();

	///�������¼�
	T_ChiPai.Clear();

	///�������¼�
	T_PengPai.Clear();




	///�������¼�
	T_GangPai.Clear();

	///�������¼�
	T_TingPai.Clear();

	///�������¼�
	T_HuPai.Clear();

	///����¼�
	T_CountFen.Clear();

	///��Ϸ���������¼�
	T_EndHandle.Clear();

	///���������������¼�
	T_UnnormalEndHandle.Clear();

	SetThingNext();

}
/*--------------------------------------------------------------------------*/
///���������ļ�
void GameData::LoadIni()
{

	m_mjRule.byAllMjCount   = 144;			//�齫������ 


	m_mjRule.bHaveWan		= 1;			//�Ƿ�����
	m_mjRule.bHaveTiao		= 1;			//�Ƿ�����
	m_mjRule.bHaveBing		= 1;			//�����б�
	m_mjRule.bHaveHongZhong	= 1;			//�Ƿ��к���
	m_mjRule.bHaveFaCai		= 1;			//�Ƿ��з���
	m_mjRule.bHaveBaiBan	= 1;			//�Ƿ��аװ�
	m_mjRule.bHaveFengPai	= 1;			//�Ƿ��ж�������
	m_mjRule.bHaveFlower	= 0;			//�Ƿ��л���

	m_mjRule.byHandCardNum	= 13;			//��������
	m_mjRule.byGamePassNum	= 0;			//��������
	m_mjRule.byGamePassType	= 0;			//������������
	m_mjRule.byNextNtType	= 0;			//�¾�ׯ�ҵ�ȷ������
	m_mjRule.bHaveJing		= 0;			//���޲���

	m_mjRule.byMenPaiNum[0]	= 17;			//����������
	m_mjRule.byMenPaiNum[1]	= 17;			//����������
	m_mjRule.byMenPaiNum[2]	= 17;			//����������
	m_mjRule.byMenPaiNum[3]	= 17;			//����������

	m_mjAction.bChi				= 1;		//��
	m_mjAction.bChiFeng			= 0;		//�Է���
	m_mjAction.bChiJian			= 0;		//���з���
	m_mjAction.bPeng			= 1;		//��
	m_mjAction.bKan				= 0;		//��
	m_mjAction.bSaoHu			= 0;		//ɨ��
	m_mjAction.bGang			= 1;		//��
	m_mjAction.bBuGang			= 1;		//����
	m_mjAction.bTing			= 1;		//��
	m_mjAction.bQiangChi		= 0;		//����(�Ժ�����)


#pragma warning(push)
#pragma warning(disable:4800)
	CString s = CINIFile::GetAppPath ();/////����·��
	CINIFile pz(s + SKIN_FOLDER  + _T("_s.ini"));
	CString key = TEXT("game");// �齫��������

	m_mjRule.byAutoOutTime	= pz.GetKeyVal(key,TEXT("byAutoOutTime"),1);		//�Զ�����ʱ��	
	m_mjRule.byOutTime		= pz.GetKeyVal(key,TEXT("byOutTime"),20);			//����ʱ��		
	m_mjRule.byBlockTime	= pz.GetKeyVal(key,TEXT("byBlockTime"),10);			//����˼��ʱ��	
	m_mjRule.byBeginTime	= pz.GetKeyVal(key,TEXT("byBeginTime"),20);			//��ʼ�ȴ�ʱ��	
	m_mjRule.bAutoBegin		= pz.GetKeyVal(key,TEXT("bAutoBegin"),0);			//ʱ�䵽���Ƿ��Զ���ʼ

	m_mjRule.bNetCutTuoGuan	= pz.GetKeyVal(key,TEXT("bNetCutTuoGuan"),1);		//�Ƿ�����й�
	m_mjRule.bForceTuoGuan	= pz.GetKeyVal(key,TEXT("bForceTuoGuan"),1);		//�Ƿ�ǿ���й�
	m_mjRule.byGamePassNum	= pz.GetKeyVal(key,TEXT("GamePassNum"),0);;			//��������

#pragma warning(pop)
}
/*--------------------------------------------------------------------------*/