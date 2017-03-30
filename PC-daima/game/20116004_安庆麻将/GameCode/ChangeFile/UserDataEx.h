/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #pragma once
//#include "../ChangeFile/UpgradeMessageEx.h"
#include "../GameMessage/UserData.h"

///������ݹ�����
class UserDataEx: public UserData
{
public:
	UserDataEx(void);
	~UserDataEx(void);
	
public:	

	bool    m_bIsHu[PLAY_COUNT];//�Ƿ����


	BYTE	m_byCaiPiaoStation;//��Ʈλ�ã���ֵ��Ϊ255�ǲ���������ܺͷ��ڣ������齫ר�ã�
	BYTE    m_byGuanXi[PLAY_COUNT][PLAY_COUNT]; //�����ܹ�ϵ
	bool	m_bGangKai[PLAY_COUNT];//�ܿ�״̬���
	BYTE    m_byLianZhuang;//��ׯ��
	bool    m_bTianHu;//ׯ�����״̬
	bool	m_bOutJing[PLAY_COUNT];//����Ƿ����˲�����
	bool	m_bChanPai;		//����Ƿ����

	bool   m_bLookBao[PLAY_COUNT];//����״̬
	
	BYTE   m_byFirstHandPai[PLAY_COUNT][HAND_CARD_NUM];//��һ���ƣ����ƣ������ܺ�ץ���Ĳ���
	
	BYTE    m_byDingQue[PLAY_COUNT];//����ȱ��0����  1���� 2��Ͳ
    
    int    m_byGFXY[PLAY_COUNT][PLAY_COUNT+1];   //�η���������
                                    //�η磨���ܣ� ��δ������1
                                    //���꣨���ܣ� ��δ������2
                                    //���ֱ꣨�ܣ� �����ܶ���2

    int    m_byGengCount[PLAY_COUNT];//����ʱ����

    BYTE   m_byChengBao[PLAY_COUNT][PLAY_COUNT];

	BYTE   m_byPengChengBao[PLAY_COUNT][PLAY_COUNT];//���Ƴа�
	BYTE   m_byChiChengBao[PLAY_COUNT][PLAY_COUNT];//���Ƴа�

	bool	m_bIsGangPao[PLAY_COUNT];//���ڸܺ��ڵ�״̬
	bool    m_bQiHu[PLAY_COUNT];//����Ƿ�����״̬

	BYTE    m_NoFenGang[PLAY_COUNT][4];//��¼�޷ָܣ����ܣ�������4������������޷֣�ץ�ƺ��ܲ��ܵ��ǲ��ڵ�ǰȦ���޷֣�
	BYTE	m_byTimeOut[PLAY_COUNT];//��ʱ����
	//���ܵ÷ֵ���
	BYTE    m_byBuGangPai;
	BYTE    m_byNeedBuHua;
	//��¼ÿ������
	GangFenRecordEx m_stGangFen[PLAY_COUNT];

public:
	
	//��ָ����һ������
	bool	ChangeAHandPai(BYTE station,BYTE ChangePai,BYTE byNewCard);
	///����Ƿ����ָ��������
	virtual	bool IsHaveAMenPai(BYTE pai);
	//��ָ��һ������
	bool	ChangeAMenPai(BYTE ChangePai,BYTE byNewCard);
	//////////////////���Ʋ���/////////////////////////////////////

	///����Ƿ����ָ��������
	virtual bool IsHaveAHandPai(BYTE station,BYTE pai);
	///���������ĳ���Ƶĸ���
	virtual int GetAHandPaiCount(BYTE station,BYTE pai);
    ///���ĳ�ֻ�ɫ�Ƶĸ�����0�� 1Ͳ 2��)
    int GetAKindPaiCount(BYTE station,BYTE kind);
    ///�õ�ĳ�ֻ�ɫ�ƣ�0�� 1Ͳ 2��)
    int GetAKindPai(BYTE station,BYTE kind);
	///������Ƶ�����
	virtual int GetHandPaiCount(BYTE station);
	///������ҵ�����
	virtual int CopyHandPai(BYTE pai[][HAND_CARD_NUM],BYTE station,bool show);
	///����������ĳ����ҵ�����
	virtual int CopyOneUserHandPai(BYTE pai[HAND_CARD_NUM] ,BYTE station);
	///��������small�Ƿ��С������
	virtual void SortHandPai(BYTE station,bool big);
	///���һ���Ƶ�������
	virtual void AddToHandPai(BYTE station,BYTE pai);
	///������������
	virtual void SetHandPaiData(BYTE station,BYTE pai[], BYTE byCount);
	///ɾ��һ��ָ��������
	virtual void DelleteAHandPai(BYTE station,BYTE pai);
	///���������Ʊ�
	virtual void SetHandPaiBack(BYTE station,BYTE num);
	///������һ������
	virtual BYTE GetLastHandPai(BYTE station);
	///���ѡ�е�һ������
	virtual BYTE GetSelectHandPai(BYTE station);
	///�Ƿ�������
	virtual bool IsOutPaiPeople(BYTE station);
	///����������Ƿ���ڻ���
	virtual bool IsHuaPaiInHand(BYTE station);
	///�������еĻ����Ƶ�����������
	virtual int MoveHuaPaiFormHand(BYTE station,BYTE byCard);

	///��ȡ���Ƶ���ɫ��
	virtual int GetPaiSeCount(BYTE station);
	///�Ƿ���ȱ�ŵ���
	bool IsHaveQueMen(BYTE station,BYTE type);
	//��ȡһ��data��û�е��ƣ���������
	BYTE GetChangePai(BYTE station,BYTE data[]);

	//////////////////�������Ʋ���/////////////////////////////////////

	///��ȡ��Ҹ��Ƶĸ���(���ܣ����ܣ�����)
	virtual int GetUserGangNum(BYTE station,BYTE &an,BYTE &ming , BYTE &bu);
	///��ҳ��ƴ���
	virtual int GetUserChiNum(BYTE station);
	///��Ҹ��ƴ���
	virtual int GetUserPengNum(BYTE station);
	///��Ҹ���ĳ����
	virtual bool IsUserHaveGangPai(BYTE station,BYTE pai,BYTE &type);
	///����Ƿ�����ĳ����
	virtual bool IsUserHavePengPai(BYTE station,BYTE pai);
	///����Ƿ�Թ�ĳ����
	virtual bool IsUserHaveChiPai(BYTE station,BYTE pai);
	///���һ�����ݵ��ܳ���������
	virtual void AddToGCP(BYTE station,GCPStructEx *gcpData);
	///ɾ���ճ���������ָ����������
	virtual void DelleteAGCPData(BYTE station,BYTE type ,BYTE pai);
	///�����ܳ��������е�������
	virtual int CopyGCPData(BYTE station,GCPStructEx gcpData[]);
	///���ó��������е�������
	virtual void SetGCPData(BYTE station,GCPStructEx gcpData[]);
	///��ȡ�ܳ����Ľڵ����
	virtual int GetGCPCount(BYTE station);
	///��������ȡ�ܳ�������ĳ���Ƶ�����
	virtual int GetOnePaiGCPCount(BYTE station,BYTE pai);
	///����ܳ�������
	virtual void ShortGCP(BYTE station);
	///��������ʼ���ܳ�������
	virtual void InitGCP(BYTE station);


	///////////////////���Ʋ���///////////////////////////////////////////////////////

	///���һ���Ƶ�����������
	virtual void AddToOutPai(BYTE station,BYTE pai);
	///ɾ�����һ�ų���
	virtual void DelleteLastOutPai(BYTE station);
	///���ó�������
	virtual void SetOutPaiData(BYTE station,BYTE pai[],BYTE byCount);
	///������ҵĳ���
	virtual int CopyOutPai(BYTE station,BYTE pai[]);
	///��ȡ��ҵĳ�������
	virtual int GetOutPaiCount(BYTE station);
	///��������ȡ���ĳ���Ƶĳ�������
	virtual int GetOneOutPaiCount(BYTE station,BYTE pai);

	//////////////////���Ʋ���///////////////////////////////////////////////////////

	///���һ�Ż��Ƶ�����������
	virtual void AddToHuaPai(BYTE station,BYTE pai);
	///���û�������
	virtual void SetHuaPaiData(BYTE station,BYTE pai[]);
	///������ҵĻ���
	virtual int CopyHuaPai(BYTE station,BYTE pai[]);
	virtual int GetAHuaCount(BYTE station,BYTE pai);
	///����Ƿ���
	virtual bool CheckIsHuaPai(BYTE pai);

	///////////////////�����Ʋ���///////////////////////////////////////////////////////

	///������������
	virtual void SetMenPaiData(BYTE station,BYTE pai[]);
	///������ҵ�����
	virtual int CopyMenPai(BYTE station,BYTE pai[]);

/////////////////////////////////////////////////////
	
	///��ȡ���������Ч������
	virtual int GetPaiNum(BYTE station,BYTE pai[],BYTE count);
	
	///��ʼ������
	virtual void InitData();
	
	///����������Ƿ����ĳ���ƵĴ��
	bool IsUserHaveBigGangPai(BYTE station,BYTE pai);

	///��������ץ������ת����ץ����ҵ���������
	bool ZhuaPaiIndex(BYTE &index,BYTE &dir);		

};

//ȫ�ֶ���
extern UserDataEx g_UserData;