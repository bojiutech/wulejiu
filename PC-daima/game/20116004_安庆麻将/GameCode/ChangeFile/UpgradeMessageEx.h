/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #pragma once
#include "../GameMessage/UpgradeMessage.h"
#pragma pack(1)



enum	BUTTON_TYPE			// ��������
{
	BUTTON_HE = 0,
	BUTTON_GANG,
	BUTTON_PENG,
	BUTTON_KAN,//����
	BUTTON_SAOHU,//ɨ��
	BUTTON_CHI,
	BUTTON_CHU,
	BUTTON_GUO,
	BUTTON_TING,
	BUTTON_BUPAI,			// ����
	BUTTON_YANPAI             
};

char strBaoType[][64] = 
{
	{"����˳��"},
	{"����˳��"},
	{"����˳��"},
	{"����˳��"},
	{"��������"},
	{"���ķ���"},
	{"��������"},
	{"���ķ���"}
};

//�а�����
enum em_BAO_TYPE
{
	e_BAO_TYPE_BEGIN = 0,
	e_SHUN_CHI_3 = 0,	//������˳��
	e_SHUN_CHI_4,		//���Ŀ�˳��
	e_SHUN_PENG_3,		//������˳��
	e_SHUN_PENG_4,		//���Ŀ�˳��
	e_FAN_CHI_3,		//�����ڷ���
	e_FAN_CHI_4,		//���Ŀڷ���
	e_FAN_PENG_3,		//�����ڷ���
	e_FAN_PENG_4,		//���Ŀڷ���
	e_BAO_TYPE_END,
};



enum HUPAI_TYPE_EX//LU��������ö�ٽṹ
{	
	HUPAI_HU_PAI				= 150,		//�ܺ����ط���1�� 1��
	HUPAI_PENG_PENG_HU			,		//����ӣ���������2�� 2��	//sdmj
	HUPAI_AN_QI_DUI				,		//���߶ԣ����߶��ӣ�3�� 4��	//sdmj
	HUPAI_QUAN_BUKAO			,		//13��
	HUPAI_QIXING_BUKAO			,		//����ʮ����
	HUPAI_KAI_PAI				,		//����
	HUPAI_BIAN_PAI				,		//����
	HUPAI_LIANG_DUI				,		//������
	HUPAI_MEN_QIAN_QING			,		//��ǰ��
	HUPAI_DA_DIAOCHE			,		//�����
	HUPAI_THREE_NAN				,		//�����Ϸ�
	HUPAI_THREE_XI				,		//���ű�
	HUPAI_THREE_BEI				,
	HUPAI_DIAN_DIAO				,		//������
	HUPAI_TYPE_GANG_KAI			,		// �ܿ� 			//sdmj
	HUPAI_TYPE_TIAN_HU			,		// ��� 			//sdmj
	HUPAI_TYPE_DI_HU			,		// �غ� 			//sdmj
	HUPAI_TYPE_QIANG_GANG		,		// ���� 			//sdmj	
	HUPAI_ZI_MO					,		//����	//sdmj
	HUPAI_NO_HUA				,
	HUPAI_QIANG_GANG_HU			,		//���ܺ�
};

///ð������(�Ӵ�С����)
static void MaoPaoSort(int a[], int count,bool big)
{
	if(a == NULL)
        return ;
	for (int i =0; i < count - 1; i++ )
	{
	    for(int j = 0; j < count - i -1; j++)
		{
			if(big)
			{
				if(a[j] < a[j+1])
				{
					int iTempBig = a[j];
					a[j] = a[j+1];
					a[j+1] = iTempBig;		
				}
			}
			else
			{
				if(a[j] > a[j+1])
				{
					int iTempBig = a[j];
					a[j] = a[j+1];
					a[j+1] = iTempBig;		
				}
			}
		}	
	}
}

///ð������(�Ӵ�С����)
static void MaoPaoSort(BYTE a[], int count,bool big)
{
	if(a == NULL)
        return ;
	for (int i =0; i < count - 1; ++i )
	{
	    for(int j = i+1; j < count; ++j)
		{
			if(big)
			{
				if(a[j] > a[i])
				{
					BYTE iTempBig = a[j];
					a[j] = a[i];
					a[i] = iTempBig;		
				}
			}
			else
			{
				if(a[j] < a[i])
				{
					BYTE iTempBig = a[j];
					a[j] = a[i];
					a[i] = iTempBig;		
				}
			}
		}	
	}
}

//ð������(�Ӵ�С)
static void MaoPaoSort(PaiStruct a[], int count)
{
	if(a == NULL)
        return ;
	PaiStruct iTempBig ;
	for (int i =0; i < count - 1; i++ )
	{
	    for(int j = i; j < count; j++)
		{
			if(a[i].count < a[j].count)
			{
				iTempBig.count= a[i].count;
				iTempBig.pai= a[i].pai;

				a[i].count = a[j].count;
				a[i].pai = a[j].pai;

				a[j].count = iTempBig.count;	
				a[j].pai = iTempBig.pai;	
			}
		}	
	}
}

///�����������ݽṹ
struct GCPStructEx:GCPStruct
{
	BYTE  byBigGang[4][2]; //����������ݣ������齫��
	bool  bIsBigGang;      //�Ƿ���
	GCPStructEx()
	{
		Init();
	}
	void Init()
	{
		GCPStruct::Init();
		bIsBigGang = false;
		memset(byBigGang,255,sizeof(byBigGang));
	};
};


/*--------------------------------------------------------------*/
///�¼����ݰ�,���ص�������������Լ�����������
///��Ϸ��ʼ�¼�	DWJ
struct tagBeginEx:tagBegin
{
	void Clear()
	{
		tagBegin::Clear();
	}
};
/*--------------------------------------------------------------*/
///�Զ�Ϊׯ�¼�	DWJ
struct tagDongNtEx:tagDongNt
{
	void Clear()
	{
		tagDongNt::Clear();
	}
};
/*----------------------------------------------------------------*/
///��2��ɫ��ȷ������λ���¼�
struct tagTwoSeziDirEx:tagTwoSeziDir
{
	void Clear()
	{
		tagTwoSeziDir::Clear();
	}
};
/*----------------------------------------------------------------*/
///��2��ɫ��ȷ������λ�ã������ͣ������Ƶ㣨��С�㣩�¼�
struct tagTwoSeziDirAndGetPaiEx:tagTwoSeziDirAndGetPai
{
	void Clear()
	{
		tagTwoSeziDirAndGetPai::Clear();
	}
};
/*----------------------------------------------------------------*/
///�����¼�	DWJ
struct tagSendPaiEx:tagSendPai
{
	void Clear()
	{
		tagSendPai::Clear();
	}
};
/*----------------------------------------------------------------*/
///������Ҳ����¼�
struct tagAllBuHuaEx:tagAllBuHua
{
	void Clear()
	{
		tagAllBuHua::Clear();
	}
};
/*----------------------------------------------------------------*/
///��ʼ����֪ͨ�¼�
struct	tagBeginOutPaiEx:tagBeginOutPai
{
	void Clear()
	{
		tagBeginOutPai::Clear();
	}
};
/*----------------------------------------------------------------*/
///�����ܺ�֪ͨ�¼��¼�
struct	tagCPGNotifyEx:tagCPGNotify
{
	void Clear()
	{
		tagCPGNotify::Clear();
	}
};
/*----------------------------------------------------------------*/
///�����¼�
struct	tagOutPaiEx:tagOutPai
{
	void Clear()
	{
		tagOutPai::Clear();
	}
};
/*----------------------------------------------------------------*/
///ץ�����¼�
struct	tagZhuaPaiEx:tagZhuaPai
{
	void Clear()
	{
		tagZhuaPai::Clear();
	}
};
/*----------------------------------------------------------------*/
///������Ҳ����¼�
struct tagOneBuHuaEx:tagOneBuHua
{
	void Clear()
	{
		tagOneBuHua::Clear();
	}
};
/*----------------------------------------------------------------*/
///�������¼�
struct tagChiPaiEx:tagChiPai
{
	GCPStructEx m_UserGCPData[PLAY_COUNT][5];     //�����ܸ���
	void Clear()
	{
		tagChiPai::Clear();
		memset(m_UserGCPData, 255, sizeof(m_UserGCPData));//�����ܸ���
	}
};
/*----------------------------------------------------------------*/
///�������¼�
struct tagPengPaiEx:tagPengPai
{
	GCPStructEx m_UserGCPData[PLAY_COUNT][5];     //�����ܸ���
	void Clear()
	{
		tagPengPai::Clear();
		memset(m_UserGCPData, 255, sizeof(m_UserGCPData));//�����ܸ���
	}
};

struct tagCanTing
{
	BYTE byDeskStation;
	tagCanTing()
	{
		byDeskStation = 255;
	}
};
/*----------------------------------------------------------------*/
///�������¼�
struct tagGangPaiEx:tagGangPai
{
	GCPStructEx m_UserGCPData[PLAY_COUNT][5];     //�����ܸ���
	bool		bIsBigGang;				//�Ƿ���
	int			iGangFen[PLAY_COUNT];	//���θ��Ƶĵ÷����
	void Clear()
	{
		tagGangPai::Clear();
		memset(m_UserGCPData, 255, sizeof(m_UserGCPData));//�����ܸ���
		memset(iGangFen, 0, sizeof(iGangFen));//���θ��Ƶĵ÷����
		bIsBigGang = false;				//�Ƿ���
	}
};
/*----------------------------------------------------------------*/
///�������¼�
struct tagTingPaiEx:tagTingPai
{
	//BYTE    byAnGangCard;		//���ܺ�����Ҫ�����ܵ�һ����
	void Clear()
	{
		tagTingPai::Clear();
		//byAnGangCard = 255;
	}
};
/*----------------------------------------------------------------*/
///�������¼�
struct tagHuPaiEx:tagHuPai
{
//	GCPStructEx m_UserGCPData[4][5];//�����ܸ���
	int		iZongFen[8];	//������ҵ��ܷ�
	int		iHuShu[4];		//������ҵĺ���
	int		iMoney[8];		//������ҵ��ܷ�
	int 	iHuFen[4];		//������ҵĺ��Ʒ�
	int 	iGangFen[4];	//������ҵĸܷ�
	BYTE    byGengCount;

	BYTE    m_byDianPao[PLAY_COUNT];//�������λ��
	bool    m_bIsZiMo[PLAY_COUNT];//�Ƿ���������
	int		m_iZongFan[PLAY_COUNT];//�����ܷ���
	int		m_iGengCount[PLAY_COUNT];//ÿ��������ҵĸ���
	void Clear()
	{
		tagHuPai::Clear();
		memset(iZongFen,0,sizeof(iZongFen));

		memset(iMoney,0,sizeof(iMoney));
		memset(iHuFen,0,sizeof(iHuFen));
		byGengCount = 0;

		memset(iGangFen, 0, sizeof(iGangFen));//������ҵĸܷ�



		memset(m_byDianPao, 0, sizeof(m_byDianPao));	//�������λ��
		memset(m_bIsZiMo, 0, sizeof(m_bIsZiMo));	//�Ƿ���������

		memset(m_iZongFan, 0, sizeof(m_iZongFan));	//�����ܷ���
		memset(m_iGengCount, 0, sizeof(m_iGengCount));	//ÿ��������ҵĸ���
	}
};
struct tagHuDetails
{
	BYTE byHua[PLAY_COUNT];
	BYTE byNoHua[PLAY_COUNT];
	BYTE byThreeNan[PLAY_COUNT];
	BYTE byThreeXi[PLAY_COUNT];
	BYTE byThreeBei[PLAY_COUNT];
	BYTE byKaPai[PLAY_COUNT];
	BYTE byBianPai[PLAY_COUNT];
	BYTE byDianDiao[PLAY_COUNT];
	BYTE byLiangDui[PLAY_COUNT];
	BYTE byGangHua[PLAY_COUNT];
	BYTE byMenQing[PLAY_COUNT];
	BYTE byMingGang[PLAY_COUNT];
	BYTE byAnGang[PLAY_COUNT];
	BYTE byNanGang[PLAY_COUNT];
	BYTE byXiGang[PLAY_COUNT];
	BYTE byBeiGang[PLAY_COUNT];
	BYTE byQiangGang[PLAY_COUNT];
	BYTE byNanGang_an[PLAY_COUNT];
	BYTE byXiGang_an[PLAY_COUNT];
	BYTE byBeiGang_an[PLAY_COUNT];

	BYTE byFourDong[PLAY_COUNT];
	BYTE byFourZhong[PLAY_COUNT];
	BYTE byFourFa[PLAY_COUNT];
	BYTE byFourBai[PLAY_COUNT];
	BYTE byShiSanLan[PLAY_COUNT];
	BYTE byQiXing[PLAY_COUNT];
	BYTE byQiDui[PLAY_COUNT];
	BYTE byPengPengHu[PLAY_COUNT];
	BYTE byDiaoChe[PLAY_COUNT];
	BYTE byTianHu[PLAY_COUNT];
	BYTE byDiHu[PLAY_COUNT];
	BYTE byShunBao[PLAY_COUNT];
	BYTE byFanBao[PLAY_COUNT];

	tagHuDetails()
	{
		init();
	}

	void init()
	{
		memset(this,0,sizeof(tagHuDetails));
		for (int i = 0;i < PLAY_COUNT;i++)
		{
			byFanBao[i] = 255;
			byShunBao[i] = 255;
			byFanBao[i] = 255;
		}
	}
};
/*----------------------------------------------------------------*/
///����¼�
struct tagCountFenEx:tagCountFen
{
	int		iBase;						//�׷�
	int		iFanBase;					//����
	int 	iHuaCount[PLAY_COUNT];		//��������
	int		iFanCount[PLAY_COUNT];		//����ҷ���
	int		iZongFen[PLAY_COUNT];		//������ܷ�
	bool	bMingPai[PLAY_COUNT];		//�Ƿ���¥
	bool    m_bIsHu[PLAY_COUNT];		//��Щ��Һ�����
	BYTE    byHuType[PLAY_COUNT][MAX_HUPAI_TYPE];//������ҵĺ�������
	int		iShunBaoFen[PLAY_COUNT];		//�����˳����
	int		iFanBaoFen[PLAY_COUNT];			//����ҷ�����
	BYTE	byShunBaoType[PLAY_COUNT];		//�����˳������
	BYTE	byFanBaoType[PLAY_COUNT];		//����ҷ�������

	//GCPStructEx m_UserGCPData[4][5];//�����ܸ���
//------------------����չʾ������ϸ��Ϣ ɵ�ƿͻ�
	tagHuDetails huDetail;

	int		iTax;//����ѣ���˰��
	int     iBasePoint;//����
	bool    bIsShowTax;//�Ƿ���ʾ�����
	BYTE    byCloseFlag;//������ʽ��������������ǿ��
	void Clear()
	{
		tagCountFen::Clear();
		iBase = 0;
		//iHuangZhuangBase = 1;
		memset(iHuaCount,0,sizeof(iHuaCount));
		memset(iFanCount,0,sizeof(iFanCount));
		memset(iZongFen,0,sizeof(iZongFen));
		memset(bMingPai,0,sizeof(bMingPai));
		memset(byHuType, 255, sizeof(byHuType));
		memset(iShunBaoFen,0,sizeof(iShunBaoFen));
		memset(iFanBaoFen,0,sizeof(iFanBaoFen));
		memset(byShunBaoType, 255, sizeof(byShunBaoType));
		memset(byFanBaoType, 255, sizeof(byFanBaoType));
		//memset(m_UserGCPData, 255, sizeof(m_UserGCPData));
		memset(m_bIsHu, 0, sizeof(m_bIsHu));	//��Щ��Һ�����
		huDetail.init();
		iTax = 0;//����ѣ���˰��
		iBasePoint = 1;//����
		bIsShowTax = 1;//�Ƿ���ʾ�����
		byCloseFlag = GF_NORMAL;//������ʽ��������������ǿ��
	}
};

//���˻�������
struct tagSuperChangeCard
{
	BYTE	byStation;			//λ��
	BYTE	byChangeCard;		//������	
	BYTE	byNewCard;			//������������	
	bool	bSuccese;			//�Ƿ�ɹ�

	BYTE	byArHandPai[HAND_CARD_NUM];//��������
	BYTE	byArHandPaiCount;	//��������

	tagSuperChangeCard()
	{
		byStation = 255;
		byChangeCard = 255;		
		byNewCard = 255;	
		bSuccese = false;	
		memset(byArHandPai,255,sizeof(byArHandPai));
		byArHandPaiCount=0;
	}
};


struct tagHaveAction
{
	BYTE byStation;
	tagHaveAction()
	{
		byStation = 255;
	}
};













///��2��ɫ�ӵĵ�����Ϊׯ�¼�
struct tagTwoSeziNtEx:tagTwoSeziNt
{
	void Clear()
	{
		tagTwoSeziNt::Clear();
	}
};
///��2��ɫ��ȷ��ׯ�Һ����Ƶ�λ���¼�
struct tagTwoSeziNtAndGetPaiEx:tagTwoSeziNtAndGetPai
{
	void Clear()
	{
		tagTwoSeziNtAndGetPai::Clear();
	}
};

///������2��ɫ��ȷ��ׯ��
struct tagTurnSeziNtEx:tagTurnSeziNt
{
	void Clear()
	{
		tagTurnSeziNt::Clear();
	}
};



///��2��ɫ��ȷ�����ƶ����¼�
struct tagTwoSeziGetPaiEx:tagTwoSeziGetPai
{
	void Clear()
	{
		tagTwoSeziGetPai::Clear();
	}
};


///�����¼�
struct tagTiaoPaiEx:tagTiaoPai
{
	void Clear()
	{
		tagTiaoPai::Clear();
	}
};
///��ɫ��2��ɫ�Ӷ������¼�
struct tagTwoSeziJingEx:tagTwoSeziJing
{
	JingStruct  m_StrJing;
	bool bUserTing[4];
	bool m_bLookBao[4];
	void Clear()
	{
		tagTwoSeziJing::Clear();
		m_StrJing.Init();
		memset(bUserTing,0,sizeof(bUserTing));
		memset(m_bLookBao,0,sizeof(m_bLookBao));
	}
};
///��ɫ��1��ɫ�Ӷ������¼�
struct tagOneSeziJinEx:tagOneSeziJin
{
	JingStruct  m_StrJing;
	void Clear()
	{
		tagOneSeziJin::Clear();
		m_StrJing.Init();
	}
};










///�����¼�
struct tagKanPaiEx:tagKanPai
{
	GCPStructEx m_UserGCPData[4][5];     //�����ܸ���
	void Clear()
	{
		tagKanPai::Clear();
		memset(m_UserGCPData, 255, sizeof(m_UserGCPData));//�����ܸ���	
	}
};
///ɨ���¼����黢�齫ר�ã�
struct tagSaoHuEx:tagSaoHu
{
	void Clear()
	{
		tagSaoHu::Clear();
	}
};


///��Ϸ���������¼�
struct tagEndHandleEx:tagEndHandle
{
	void Clear()
	{
		tagEndHandle::Clear();
	}
};
///���������������¼�
struct tagUnnormalEndHandleEx:tagUnnormalEndHandle
{
	void Clear()
	{
		tagUnnormalEndHandle::Clear();
	}
};
///////////////////////////////////////////////////

///��ȱ�¼����ݰ�
struct tagDingQueEx
{
	BYTE byUser; //��ȱ���
	BYTE byQue; //ȱ����
	BYTE byQuePai[PLAY_COUNT]; //ȱ����
	bool bNotify; // �Ƿ��������ȱ֪ͨ
	bool bFinish[PLAY_COUNT];//�Ƿ��Ѿ���ɶ�ȱ
	tagDingQueEx()
	{
		Clear();
	}
	void Clear()
	{
		byUser = 255; //��ȱ���
		byQue = 255; //ȱ����
		memset(byQuePai, 255, sizeof(byQuePai));//
		memset(bFinish, 0, sizeof(bFinish));////�Ƿ��Ѿ���ɶ�ȱ
		bNotify = false; // �Ƿ��������ȱ֪ͨ
	}
};

//////////////////�������ݰ�/////////
///�齫��������
struct MJ_Setting
{
    int                                 nSeziTime;                          ///����ʱ��(ms)
    int                                 nSendcardTime;                      ///����ʱ��(ms)
    BYTE                                ucDingQueTime;                      ///��ȱʱ��(s)
    BYTE                                ucBlockTime;                        ///����ʱ��
    BYTE                                ucOutcardTime;                      ///����ʱ��
    BYTE                                ucBeginTime;                        ///�Զ���ʼ���뿪��ʱ��
    BYTE                                ucNextTime;                         ///��һ���Զ���ʼ���뿪��ʱ��
    BYTE                                bAutoBegin;                         ///�Ƿ��Զ�׼��
    int                                 nAutoTime;							///�йܵķ�Ӧʱ��(ms)

    MJ_Setting()
    {
        nSeziTime = 10000;
        nSendcardTime = 3000;
        ucDingQueTime = 20;
        ucBlockTime = 15;
        ucOutcardTime = 20;
        ucBeginTime = 20;
        ucNextTime = 20;
        bAutoBegin = 1;
        nAutoTime = 1;
    }
};
///�齫״̬
struct MJ_State
{
    MJTHINGS                thingDoing;           // ��ǰ״̬
    BYTE                    ucCurChair;           // ��ǰ��˭����        
    BYTE                    ucTime;               // ʱ��(s)
};
/*----------------------------------------------------------------------*/
///�齫ʱ��ȴ���ʱ�䵽�˷�������Ϊ����
struct MJ_WaitTimeEx
{
	BYTE					byWaitThing;		  // �ȴ������¼�
    BYTE                    byCurChair;           // ��ǰ��˭����        
    BYTE                    byTime;               // �ȴ�ʱ��ʱ��(s)
	bool					bEffect;			  // �ȴ��Ƿ���Ч
    MJ_WaitTimeEx()
    {
		Clear();
    }
	void Clear()
	{	
		byWaitThing = 0;		// �ȴ������¼�
		byCurChair = 255;       // ��ǰ��˭����        
		byTime = 255;           // �ȴ�ʱ��ʱ��(s)
		bEffect = false;		// �ȴ��Ƿ���Ч
	}
};
/*----------------------------------------------------------------------*/
///�����������ݰ�
struct GameStationDataEx:GameStationData
{
	GCPStructEx			m_UserGCPData[4][5];					//��ҳ�������
	BYTE				m_byArOutPai[PLAY_COUNT][OUT_CARD_NUM];	//��������
	BYTE				m_byArHuaPai[PLAY_COUNT][HUA_CARD_NUM];
	bool				m_bTing[PLAY_COUNT];
	BYTE                m_byNowOutStation;
	BYTE                m_byNowThing;
	BYTE				m_byRemainTime;

	BYTE				lastOutStation;					//����������
	BYTE				lastOutCard;					//����������ֵ

	GameStationDataEx()
	{		
		Init();
	};
	void Init()
	{
		memset(this, 0, sizeof(GameStationDataEx));	
		memset(m_byArHandPai,255,sizeof(m_byArHandPai));
		memset(m_byArOutPai,255,sizeof(m_byArOutPai));
		memset(m_byArHuaPai,255,sizeof(m_byArHuaPai));
		memset(m_iArMenPai,255,sizeof(m_iArMenPai));
		memset(m_UserGCPData,255,sizeof(m_UserGCPData));
		m_byNowOutStation = 255;
		m_byNowThing = 255;
		lastOutCard = 255;
		lastOutStation = 255;
	}
};
///�����������ݰ�
struct GangFenRecordEx
{
	int fen[5][PLAY_COUNT+1];
	int count;//����
	GangFenRecordEx()
	{
		Init();
	};
	void Init()
	{
		memset(this,0,sizeof(GangFenRecordEx));
	}
};

struct  tagNoPeng
{
	BYTE bPai[4][2];
	tagNoPeng()
	{
		init();
	}
	void init()
	{
		memset(bPai,255,sizeof(bPai));
	}
	void add(BYTE Pai)
	{
		if (bHas(Pai))
		{
			return;
		}
		for (int i = 0;i < 4;i++)
		{
			if (bPai[i][0] == 255)
			{
				bPai[i][0] = Pai;
				bPai[i][1] = 0;
				break;
			}
		}
	}
	void set(BYTE Pai)
	{
		for (int i = 0;i < 4;i++)
		{
			if (Pai == bPai[i][0])
			{
				bPai[i][1] = 1;
				break;
			}
		}
	}

	void del(BYTE Pai)
	{
		for (int i = 0;i < 4;i++)
		{
			if (Pai == bPai[i][0])
			{
				bPai[i][0] = 255;
				bPai[i][1] = 255;
				break;
			}
		}
	}

	bool bCanPeng(BYTE Pai)
	{
		for (int i = 0;i < 4;i++)
		{
			if (Pai == bPai[i][0] && 0 == bPai[i][0])
			{
				return true;
			}
		}
		return false;
	}
 
	bool bHas(BYTE Pai)
	{
		for (int i = 0;i < 4;i++)
		{
			if (Pai == bPai[i][0])
			{
				return true;
			}
		}
		return false;
	}
	void clr()
	{
		init();
	}
};

struct  tagNoHu
{
	BYTE bPai[16][2];
	tagNoHu()
	{
		init();
	}
	void init()
	{
		memset(bPai,255,sizeof(bPai));
	}
	void add(BYTE Pai)
	{
		if (bHas(Pai))
		{
			return;
		}
		for (int i = 0;i < 16;i++)
		{
			if (bPai[i][0] == 255)
			{
				bPai[i][0] = Pai;
				bPai[i][1] = 0;
				break;
			}
		}
	}
	void set(BYTE Pai)
	{
		for (int i = 0;i < 16;i++)
		{
			if (Pai == bPai[i][0])
			{
				bPai[i][1] = 1;
				break;
			}
		}
	}

	void del(BYTE Pai)
	{
		for (int i = 0;i < 16;i++)
		{
			if (Pai == bPai[i][0])
			{
				bPai[i][0] = 255;
				bPai[i][1] = 255;
				break;
			}
		}
	}

	bool bCanHu(BYTE Pai)
	{
		for (int i = 0;i < 16;i++)
		{
			if (Pai == bPai[i][0] && 0 == bPai[i][0])
			{
				return true;
			}
		}
		return false;
	}
 
	bool bHas(BYTE Pai)
	{
		for (int i = 0;i < 16;i++)
		{
			if (Pai == bPai[i][0])
			{
				return true;
			}
		}
		return false;
	}
	void clr()
	{
		init();
	}
};

#pragma pack()
