/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #pragma once
#include "../ChangeFile/UpgradeMessageEx.h"

///��Ϸ���ݹ�����:�������ݣ���Ϸ�������ݵȣ������ݽ��в����޸ĵȶ���
class GameData
{
public:
	GameData(void);
	~GameData(void);
	
public:	   

	BYTE					m_byNtStation;	//	ׯ��λ��	DWJ

	int						m_iHuangZhuangCount;	//��ׯ����	DWJ

	BYTE					ApplyThingID;	///Ҫ������¼�	DWJ
	
	BYTE					m_byThingDoing;	///���ڷ������¼���  
	
	BYTE					m_byWatingThing;//��ǰ�ȴ����¼�ID	DWJ

	MjRuleSet				m_mjRule;		/// �齫��������	DWJ

	bool					m_bGangState[PLAY_COUNT];//��¼����״̬��ӵ�ڸܿ��͸ܺ���

	bool					m_bShowTax;//�Ƿ���ʾ̨��

	int						m_iRemaindTime;	//����ʱʣ��ʱ��(�ͻ�����)




	/// �齫��������
	ActionRuleSet			m_mjAction;               
	/// �齫�������
	CountFenRuleSet			m_mjFenRule;				
	/// �齫��������
	HuPaiRuleSet			m_mjHuRule;				
	/// �齫��������
	HuPaiTypeSet			m_mjHuType;				
	///��¼��Ϸ���е������¼���ץ�ƣ����ƣ������ܺ��������ȣ����һ��Ԫ��299��¼�¼�������
	BYTE					m_byThingRecord[300];

	/// ÿ���¼��ĺ���¼������100���¼���
	BYTE					m_byThingNext[100];



	////////////�������ݶ���/////////////////////////////////////////////////////////
	
	

	///��ִ���¼�
	BYTE					m_byMaxAction;
				
	///����ı���
	int						basepoint;	
	
	

	///�������¼�,��ʱ����
	tagChiPaiEx				temp_ChiPai;
	///�������¼�,��ʱ����
	tagPengPaiEx			temp_PengPai;
	///�������¼�,��ʱ����
	tagGangPaiEx			temp_GangPai;
	////�������¼�,��ʱ����

	
public:////////////�¼����ݶ�����//////////////////////
	///��Ϸ��ʼ�¼�	DWJ
	tagBeginEx				T_Begin;
	///�Զ�Ϊׯ�¼�	DWJ
	tagDongNtEx				T_DongNt;
	///��2��ɫ��ȷ������λ���¼�	DWJ
	tagTwoSeziDirEx			T_TwoSeziDir;
	///��2��ɫ��ȷ������λ�ã������ͣ������Ƶ㣨��С�㣩�¼�	DWJ
	tagTwoSeziDirAndGetPaiEx	T_TwoSeziDirAndGetPai;
	///�����¼�	DWJ
	tagSendPaiEx			T_SendPai;
	///������Ҳ����¼�	DWJ
	tagAllBuHuaEx			T_AllBuHua;
	///��ʼ����֪ͨ�¼�	DWJ
	tagBeginOutPaiEx		T_BeginOutPai;
	///�����¼�	DWJ
	tagOutPaiEx				T_OutPai;
	///�����ܺ���֪ͨ�¼����¼�	DWJ
	tagCPGNotifyEx			T_CPGNotify[PLAY_COUNT];
	///ץ�����¼�	DWJ	
	tagZhuaPaiEx			T_ZhuaPai;
	///������Ҳ����¼�	DWJ
	tagOneBuHuaEx			T_OneBuHua;



	///�������¼�	DWJ
	tagChiPaiEx				T_ChiPai;
	///�������¼�	DWJ
	tagPengPaiEx			T_PengPai;
	///�������¼�	DWJ
	tagGangPaiEx			T_GangPai;
	///�������¼�	DWJ
	tagTingPaiEx			T_TingPai;
	///�������¼�	DWJ
	tagHuPaiEx				T_HuPai;
	///����¼�		DWJ
	tagCountFenEx			T_CountFen;

	//��������
	tagNoPeng				T_NoPeng[PLAY_COUNT];
	//���ɺ���
	tagNoHu					T_NoHu[PLAY_COUNT];









	///��2��ɫ�ӵĵ�����Ϊׯ�¼�
	tagTwoSeziNtEx			T_TwoSeziNt;
	///��2��ɫ��ȷ��ׯ�Һ����Ƶ�λ���¼�
	tagTwoSeziNtAndGetPaiEx	T_TwoSeziNtAndGetPai;
	///������2��ɫ��ȷ��ׯ��
	tagTurnSeziNtEx			T_TurnSeziNt;
	
	
	///��2��ɫ��ȷ�����ƶ����¼�
	tagTwoSeziGetPaiEx		T_TwoSeziGetPai;
	
	///�����¼�
	tagTiaoPaiEx			T_TiaoPai;
	///��ɫ��2��ɫ�Ӷ������¼�
	tagTwoSeziJingEx		T_TwoSeziJing;
	///��ɫ��1��ɫ�Ӷ������¼�
	tagOneSeziJinEx			T_OneSeziJin;
	
	
	
	
	///��Ϸ���������¼�
	tagEndHandleEx			T_EndHandle;
	///���������������¼�
	tagUnnormalEndHandleEx   T_UnnormalEndHandle;


	

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