/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #pragma once
#include "..\ChangeFile\GameDataEx.h"
#include "..\ChangeFile\UserDataEx.h"

class CServerGameDesk;

///���Ƽ����
class CheckHuPai
{
public:
	CheckHuPai(void);
	~CheckHuPai(void);
	
public:	
	CServerGameDesk  *pDesk;//���ࣨ���ӣ�

	///��ǰ�����ҵ�λ��
	BYTE            m_byStation;
	///����Ƿ���������
	bool            m_bZimo;
	///�������ṹ����
	PingHuStruct	hupaistruct;
	PingHuStruct	TempHupaistruct;///�������ṹ����
	///���Ƽ����ʱ����
	CheckHuStruct	HuTempData;		
	///���Ƽ����ʱ����(�޲���)
	CheckHuStruct	NoJingHuTempData;		
	///��������
	BYTE			m_byJingNum;
	///��������
	BYTE			m_byHuType[MAX_HUPAI_TYPE];
	//��ǰ�����ֵ
	int				m_iMaxFan;
	//�����������ڵ���
	BYTE			m_byLastPai;
	//���Ʋ�����20�ţ�0Ϊ������־
	BYTE			m_byArHandPai[HAND_CARD_NUM];


	///��������
	BYTE		   m_byShunNum;			//˳�ӵĸ���
	BYTE           m_byShunData[4];		//˳�ӵ�����
	BYTE		   m_byKeziNum;			//���ӵĸ���
	BYTE           m_byKeziData[4];		//���ӵ�����
	BYTE		   m_byGangNum;			//���Ƶĸ���
	BYTE           m_byGangData[4][2];	//���Ƶ�����
	BYTE		   m_byJiang;			//��������

	BYTE		   m_byChiNum;			//���Ƶĸ���
	BYTE		   m_byPengNum;			//���Ƶĸ���


public:
	//��������ָ��
	void SetDeskPoint(CServerGameDesk *desk);

	///����ܷ�����
	virtual bool CanTing(BYTE station,BYTE CanOut[]);

	///����ܷ�����ƣ��Ժ�����
	virtual bool ChiTing(BYTE station,BYTE CanOut[],BYTE pai[][3]);

	///���ܺ��ܷ񱣴�����״̬
	virtual bool GangTing(BYTE station,tagCPGNotifyEx &cpg ,BYTE ps = 255,bool CanTing[] = NULL);

	//ֻ����ܷ����
	virtual bool CanHu(BYTE station,BYTE lastpai,bool zimo);

	//��ϸ����������
	virtual bool CanHu(BYTE station,BYTE lastpai,BYTE hutype[],bool zimo);

	///�����������ݼ��뵽���ƽṹ��
	virtual void AddGCPData(GCPStructEx gcpData[],PingHuStruct * tempstruct);

	///ת���������ݵĴ洢��ʽ��Ϊ�˷�����Ƽ��
	virtual void ChangeHandPaiData(BYTE handpai[],BYTE pai);

	///���һ���Ƶ���ʱ������
	virtual void AddAPaiToArr(BYTE pai);

	///ƽ�����
	virtual bool CheckPingHu(BYTE lastzhuapai=255,bool zimo=false,bool jing=false,bool CheckTing=false);

	///���þ���
	virtual void SetJingPai();

	///�ָ�����
	virtual void ReSetJingPai();

	///��ȡ�����������
	virtual bool  GetMaxCombination(bool zimo,bool jing,BYTE lastpai = 255);

	///ƽ������
	virtual bool MakePingHu(CheckHuStruct &PaiData,PingHuStruct &hupaistruct,int csnum=0);

	///�ָ�����,�Ѽ������ƻ�ԭ
	virtual void ReSetPaiNum(BYTE num[],CheckHuStruct &TempPai);

	///��������Ƿ�ͬһ��ɫ
	virtual bool CheckTongSe(BYTE pai1,BYTE pai2);

	///��������Ƿ�����
	virtual bool CheckLianPai(BYTE pai1,BYTE pai2,BYTE num=1);

	///�����������������
	virtual void CheckHuPai::ClearPingHuData();

	///���ƽ��������ϣ����ƣ��ԣ����ܣ�˳�ӣ����̵�
	virtual void CheckPingHuData();

	///���һ�ֺ�������
	virtual void SetAHupaiType(BYTE type,BYTE hupai[]);

	///����һ�ֺ�������
	virtual void ReSetAHupaiType(BYTE type,BYTE hupai[]);

	///������������к�������
	virtual void ClearHupaiType(BYTE hupai[]);

	///����Ƿ����ĳ�ֺ�������
	virtual bool CheckHupaiType(BYTE type,BYTE hupai[]);

	///��ʼ������
	virtual void InitData();



/////////////////��ϸ�������ͼ��///////////////////////////////////////////////////////////////////////////////	
	//ƽ��
	virtual bool CheckIsPingHu();	
	//���
	virtual bool CheckTianHu();	//sdmj
	//�غ�
	virtual bool CheckDiHu();	//sdmj
	//���ϻ�
	virtual bool CheckGangKai();//sdmj	
	//�ܺ���
	virtual bool CheckGangHouPao();	
	//һ���
	virtual bool CheckYiBanGao();	
	//ϲ���
	virtual bool CheckXiXiangFeng();	
	//����
	virtual bool CheckLianLiu();	
	//���ٸ�
	virtual bool CheckLaoShaoFu();	
	//�۾ſ�
	virtual bool CheckYaoJiuKe();	
	//����
	virtual bool CheckMingGang();	
	//ȱһ��
	virtual bool CheckQueYiMen();	
	//����
	virtual bool CheckWuZi();	
	//����
	virtual bool CheckBianZhang();	
	//����
	virtual bool CheckKanZhang();	
	//������
	virtual bool CheckDanDiaoJiang();	
	//����
	virtual bool CheckJianKe();	
	//Ȧ���
	virtual bool CheckQuanFengKe();	
	//�ŷ��
	virtual bool CheckMenFengKe();	
	//��ǰ��
	virtual bool CheckMenQianQing();	
	//�Ĺ�һ
	virtual bool CheckSiGuiYi();	
	//˫ͬ��
	virtual bool CheckShuangTongKe();	
	//˫����
	virtual bool CheckShuangAnGang();	
	//����
	virtual bool CheckAnGang();	
	//����
	virtual bool CheckDuanYao();	
	//ȫ����
	virtual bool CheckQuanDaiYao();	
	//������
	virtual bool CheckBuQiuRen();	
	//˫����
	virtual bool CheckShuangMingGang();	
	//�;���
	virtual bool CheckHuJueZhang();	
	//������
	virtual bool CheckPengPengHu();	
	//һɫ�Ƽ�⣨������ƺͳ������ƣ����ﶼ���ã���0����һɫ�ƣ�1��һɫ��2��һɫ��
	virtual int CheckYiSe();	
	//��ɫ������
	virtual bool CheckSanSeSanBuGao();	
	//������
	virtual bool CheckWuMenQi();	
	//ȫ����
	virtual bool CheckQuanQiuRen();	
	//˫����
	virtual bool CheckShuangAnKe();	
	//˫����
	virtual bool CheckShuangJianKe();	
	//����
	virtual bool CheckHuaLong();	
	//�Ʋ���
	virtual bool CheckTuiBuDao();	
	//��ɫ��ͬ˳
	virtual bool CheckSanSeSanTongShun();	
	//��ɫ���ڸ�
	virtual bool CheckSanSeSanJieGao();	
	//�޷���
	virtual bool CheckWuFanHe();	
	//���ֻش�
	virtual bool CheckMiaoShouHuiChun();	
	//��������
	virtual bool CheckHaiDiLaoYue();	
	//���ܺ�
	virtual bool CheckQiangGangHe();	
	//������
	virtual bool CheckDaYuWu();	
	//С����
	virtual bool CheckXiaoYuWu();	
	//�����
	virtual bool CheckSanFengKe();	
	//����
	virtual bool CheckQingLong();	
	//��ɫ˫����
	virtual bool CheckSanSeShuangLongHui();	
	//һɫ������
	virtual bool CheckYiSeSanBuGao();	
	//ȫ����
	virtual bool CheckQuanDaiWu();	
	//��ͬ��
	virtual bool CheckSanTongKe();	
	//������
	virtual bool CheckSanAnKe();	
	//ȫ˫��
	virtual bool CheckQuanShuangKe();	
	//��һɫ
	virtual bool CheckQingYiSe();	
	//��һɫ
	virtual bool CheckHunYiSe();	
	//һɫ��ͬ˳
	virtual bool CheckYiSeSanTongShun();	
	//һɫ���ڸ�
	virtual bool CheckYiSeSanJieGao();	
	//ȫ��
	virtual bool CheckQuanDa();	
	//ȫ��
	virtual bool CheckQuanZhong();	
	//ȫС
	virtual bool CheckQuanXiao();	
	//һɫ�Ĳ���
	virtual bool CheckYiSeSiBuGao();	
	//����
	virtual bool CheckSanGang();	
	//���۾�
	virtual bool CheckHunYaoJiu();	
	//һɫ��ͬ˳
	virtual bool CheckYiSeSiTongShun();	
	//һɫ�Ľڸ�
	virtual bool CheckYiSeSiJieGao();	
	//���۾�
	virtual bool CheckQingYaoJiu();	
	//С��ϲ
	virtual bool CheckXiaoSiXi();	
	//С��Ԫ
	virtual bool CheckXiaoSanYuan();	
	//��һɫ
	virtual bool CheckZiYiSe();	
	//�İ���
	virtual bool CheckSiAnKe();	
	//һɫ˫����
	virtual bool CheckYiSeShuangLongHui();	
	//����ϲ
	virtual bool CheckDaSiXi();	
	//����Ԫ
	virtual bool CheckDaSanYuan();	
	//��һɫ
	virtual bool CheckLvYiSe();	
	//�ĸܣ�ʮ���޺���
	virtual bool CheckSiGang();	
	//��������
	virtual bool CheckJiuLianBaoDeng();	

	virtual bool CheckNoHua();
	
	/////////////////////////��������///////////////////////////////////////////////////////////////////////////////////////////////

	//ȫ��������ʮ���ã�
	virtual bool CheckQuanBuKao();	
	//�����
	virtual bool CheckZuHeLong();	
	//�߶�
	virtual int CheckQiDui();	
	//���ǲ���������ʮ���ã�
	virtual bool CheckQiXingBuKao();	

	//���߶ԣ��߶Ե����⣩
	virtual bool CheckLianQiDui();	
	//ʮ����
	virtual bool CheckShiSanYao();	



};