/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #pragma once
#pragma pack(1)
#include "mj.h"
/*------------------------------------------------------------------------------------------------------*/
///������汾
#define DEV_LIB_VER				1									///������汾
/*------------------------------------------------------------------------------------------------------*/
//֧������
///֧�����Ͷ���
#define SUP_NORMAL_GAME			0x01								///��ͨ��Ϸ
#define SUP_MATCH_GAME			0x02								///������Ϸ
#define SUP_MONEY_GAME			0x04								///�����Ϸ
#define SUPPER_TYPE						SUP_NORMAL_GAME|SUP_MATCH_GAME|SUP_MONEY_GAME
#define GAME_TABLE_NAME					TEXT("MatchTable_BSMJ")
/*------------------------------------------------------------------------------------------------------*/
#define MAIN_VERSION					710		// ���汾��,?��?��
#define ASS_VERSION						15		// �����汾��,?��
/*------------------------------------------------------------------------------------------------------*/
//�ļ����ֶ���
#define GAMENAME						TEXT("�����齫") 
#define NAME_ID						    20116004  		// ���� ID
/*------------------------------------------------------------------------------------------------------*/
static TCHAR szTempStr[MAX_PATH] =		{0};			/** �ݴ��ַ�����������ȡ dll_name �ȵ�ʱ��ʹ�� */
#define GET_CLIENT_DLL_NAME(A)			(sprintf(A,"%d",NAME_ID),strcat(A,".ico"))
#define GET_SERVER_DLL_NAME(A)			(sprintf(A,"%d",NAME_ID),strcat(A,".dll"))
#define GET_SKIN_FOLDER(A)				(sprintf(A,"%d",NAME_ID),strcat(A,""))
/*------------------------------------------------------------------------------------------------------*/
#define GET_STRING(NUM)                 #NUM
#define INT_TO_STR(NUM)                 GET_STRING(NUM)
#define CLIENT_DLL_NAME                 TEXT(INT_TO_STR(NAME_ID)##".ico")  // �ͻ���ico����
#define SKIN_FOLDER                     TEXT(INT_TO_STR(NAME_ID))          // �ͻ���Ŀ¼
#define SKIN_CARD						TEXT("CardSkin")		           // �ƹ���ͼƬ�ļ���
#define SKIN_MJ							TEXT("MjSkin")					   // �齫����ͼƬ�ļ���
/*------------------------------------------------------------------------------------------------------*/
// �汾����
#define GAME_MAX_VER					2									// ������߰汾
#define GAME_LESS_VER					2									// ������Ͱ汾
#define GAME_CHANGE_VER					0									// �޸İ汾		
#define PLAY_COUNT						4									// ��Ϸ����		
/*------------------------------------------------------------------------------------------------------*/
#define MAX_HAND_PAI					14				//������
/*------------------------------------------------------------------------------------------------------*/
////////////////////////////////////////////////////////////////////////////////
#define GFF_FORCE_FINISH		0									///< ǿ�н��
#define GF_NORMAL               10                                  /// ��Ϸ��������
#define GF_SAFE                 11                                  /// ��Ϸ��ȫ����
/*------------------------------------------------------------------------------------------------------*/
#ifndef AFC_SERVER_SHOWHAND_MESSAGE_HEAD_FILE		// ��֪ʲô��˼
#define AFC_SERVER_SHOWHAND_MESSAGE_HEAD_FILE
/*------------------------------------------------------------------------------------------------------*/
// ��Ϸ״̬����
#define GS_WAIT_SETGAME					0				// �ȴ���������״̬
#define GS_WAIT_ARGEE					1				// �ȴ�ͬ������
#define GS_SEND_CARD					20				// ����״̬
#define GS_PLAY_GAME					22				// ��Ϸ��״̬
#define GS_WAIT_NEXT					23				// �ȴ���һ�̿�ʼ 
/*------------------------------------------------------------------------------------------------------*/
// ץ��״̬
#define GAME_STATUS_FAPAI				0				// ��Ϸ״̬Ϊ0ʱ,��ʾ�ǲ���
#define GAME_STATUS_CHUPAI				1				// Ϊ1,��ʾ����������
/*------------------------------------------------------------------------------------------------------*/
//////�������ͼ���������////////////////////
#define ACTION_NO				0				//û�ж���
#define ACTION_CHI				1				//���ƶ���
#define ACTION_PENG				2				//���ƶ���
#define ACTION_KAN				3				//�����ƶ���
#define ACTION_AN_GANG			4				//���ܶ���
#define ACTION_BU_GANG			5				//���ܶ���
#define ACTION_MING_GANG		6				//���ܶ���
#define ACTION_CHI_TNG			7				//���ԣ��Ժ����ƣ�
#define ACTION_TING_PAI			8				//������
//#define ACTION_BU_HUA			9				//��������
#define ACTION_HU				10				//������
/*------------------------------------------------------------------------------------------------------*/
enum MJ_ACTION_TYPE
{
	AT_EMPTY             =0,    // û����Ϊ���������ƣ�
	AT_COLLECT             ,    // ����
	AT_TRIPLET             ,    // ��
	AT_QUADRUPLET          ,    // ��
	AT_QUADRUPLET_CONCEALED,    // ����
	AT_QUADRUPLET_REVEALED ,    // ����
	AT_QUANDUPLET_SPECIAL  ,    // �����齫����ܣ��ĸ���һ���
	AT_WIN                 ,    // ����
	AT_TING                ,    // ����
	AT_FLOWER              ,    // ����
	AT_GIVE                     // Ҫ�����ƣ����ұߵ�һ�ţ�
};
/*------------------------------------------------------------------------------------------------------*/
#define TYPE_JIANG_PAI			15				//��������
#define TYPE_JINGDIAO_JIANG		16				//������������
#define TYPE_SHUN_ZI			17				//˳������
#define TYPE_AN_KE				18				//��������
#define TYPE_JING_KE			19				//�����������
/*------------------------------------------------------------------------------------------------------*/
///�����Ƶ�����
#define HAND_CARD_NUM			14				//�����������
#define OUT_CARD_NUM			60				//��������
#define HUA_CARD_NUM			16				//��������
#define MEN_CARD_NUM			34				//��������
#define MAX_HUPAI_TYPE			21				//��������
#define MAX_HAND_PAI			14				//������
/*------------------------------------------------------------------------------------------------------*/
///���Ƽ����ʱ����
struct CheckHuStruct
{
	BYTE  data[HAND_CARD_NUM][2];   //�����ݣ�0��ֵ��1����
	BYTE  conut;
	void Add(BYTE pai)
	{
		if(GetPaiCount(pai)>0)
		{
			for(int i=0;i<HAND_CARD_NUM;i++)
			{
				if(data[i][0] == pai && pai != 255)
					data[i][1]++;
			}
		}
		else
		{
			data[conut][0] = pai;
			data[conut][1] = 1;
			conut++;
		}
	};
	BYTE GetPaiCount(BYTE pai)
	{
		for(int i=0;i<HAND_CARD_NUM;i++)
		{
			if(data[i][0] == pai && pai != 255 && data[i][1] != 255)
				return data[i][1];
		}
		return 0;
	};
	BYTE GetDataCount()
	{
		conut = 0;
		for(int i=0;i<HAND_CARD_NUM;i++)
		{
			if(data[i][0] != 255)
				conut++;
		}
		return conut;
	};
	BYTE GetAllPaiCount()
	{
		BYTE num = 0;
		for(int i=0;i<HAND_CARD_NUM;i++)
		{
			if(data[i][0] != 255)
				num += data[i][1];
		}
		return num;
	};
	void SetPaiCount(BYTE pai,BYTE num)
	{
		for(int i=0;i<HAND_CARD_NUM;i++)
		{
			if(data[i][0] == pai && pai != 255)
			{
				data[i][1] = num;
			}
		}
	}
	void Init()
	{
		memset(data,255,sizeof(data));
		for(int i=0;i<HAND_CARD_NUM;i++)
		{
			data[i][1] = 0;
		}
		conut=0;
	};
	CheckHuStruct()
	{
		Init();
	}
};
///ƽ���������ݽṹ
struct PingHuStruct
{
	BYTE  byType[6];    //��������
	BYTE  data[6][4];   //����
	bool  isjing[6][4];//�Ƿ�������
	BYTE  count;        //�ڵ���
	PingHuStruct()
	{
		Init();
	};
	void AddData(BYTE type,BYTE pai[],bool jing[])
	{
		for(int i=0;i<6;i++)
		{
			if(byType[i] == 255)
			{
				byType[i] = type;
				data[i][0] = pai[0];data[i][1] = pai[1];data[i][2] = pai[2];data[i][3] = pai[3];
				isjing[i][0] = jing[0];isjing[i][1] = jing[1];isjing[i][2] = jing[2];isjing[i][3] = jing[3];
				count++;
				break;
			}
		}
	};
	void DeleteData(BYTE type,BYTE pai[],bool jing[])//ɾ��Ԫ��
	{
		for(int i=0;i<6;i++)
		{
			if(byType[i] == type && data[i][0] == pai[0 ]&& data[i][1] == pai[1] && isjing[i][0] == jing[0] && isjing[i][1] == jing[1])
			{
				byType[i] = 255;
				memset(data[i],255,sizeof(data[i]));
				memset(isjing[i],0,sizeof(isjing[i]));
				count--;
				break;
			}
		}
	};
	void SortData()
	{
		for(int i=0;i<5;i++)
		{
			if(byType[i] != 255)
				continue;
			for(int j=i;j<5;j++)
			{
				byType[j] = byType[j+1];
				memcpy(data[j],data[j+1],sizeof(data[j]));//����
				memcpy(isjing[j],isjing[j+1],sizeof(isjing[j]));//�Ƿ�������
			}
		}
		count = 0;
		for(int i=0;i<5;i++)
		{
			if(byType[i] != 255)
				count++;
		}
	};
	void Init()
	{
		memset(this,255,sizeof(PingHuStruct));
		memset(isjing,0,sizeof(isjing));
		count = 0;
	};
};

/////////////////�������ͽṹ//////////////////////////////////////
///��������
enum HUPAI_TYPE//LU��������ö�ٽṹ
{		
	HUPAI_TYPE_None						=0,		////û��	
	HUPAI_TYPE_HuPai					=1,		////����
	HUPAI_TYPE_ZiMo						=2,		////����
	HUPAI_TYPE_PingHu					=3,		////ƽ��
	HUPAI_TYPE_TianHu					=4,		////���
	HUPAI_TYPE_DiHu						=5,		////�غ�
	HUPAI_TYPE_GangKai					=6,		//���ϻ�
	HUPAI_TYPE_GangHaoPao				=7,		//�ܺ���
	HUPAI_TYPE_YiBanGao					=8,		//һ���
	HUPAI_TYPE_XiXiangFeng				=9,		//ϲ���
	HUPAI_TYPE_LianLiu					=10,	//����
	HUPAI_TYPE_LaoShaoFu				=11,	//���ٸ�
	HUPAI_TYPE_YaoJiuKe					=12,	//�۾ſ�
	HUPAI_TYPE_MingGang					=13,	//����
	HUPAI_TYPE_QueYiMen					=14,	//ȱһ��
	HUPAI_TYPE_WuZi						=15,	//����
	HUPAI_TYPE_BianZhang				=16,	//����
	HUPAI_TYPE_KanZhang					=17,	//����
	HUPAI_TYPE_DanDiaoJiang				=18,	//������
	HUPAI_TYPE_JianKe					=19,	//����
	HUPAI_TYPE_QuanFengKe				=20,	//Ȧ���
	HUPAI_TYPE_MenFengKe				=21,	//�ŷ��
	HUPAI_TYPE_MenQianQing				=22,	//��ǰ��
	HUPAI_TYPE_SiGuiYi					=23,	//�Ĺ�һ
	HUPAI_TYPE_ShuangTongKe				=24,	//˫ͬ��
	HUPAI_TYPE_ShuangAnKe				=25,	//˫����
	HUPAI_TYPE_AnGang					=26,	//����
	HUPAI_TYPE_DuanYao					=27,	//����
	HUPAI_TYPE_QuanDaiYao				=28,	//ȫ����
	HUPAI_TYPE_BuQiuRen					=29,	//������
	HUPAI_TYPE_ShuangMingGang			=30,	//˫����
	HUPAI_TYPE_HuJueZhang				=31,	//�;���
	HUPAI_TYPE_PengPengHu				=32,	//������
	HUPAI_TYPE_HunYiSe					=33,	//��һɫ
	HUPAI_TYPE_SanSeSanBuGao			=34,	//��ɫ������
	HUPAI_TYPE_WuMenQi					=35,	//������
	HUPAI_TYPE_QuanQiuRen				=36,	//ȫ����
	HUPAI_TYPE_ShuangAnGang				=37,	//˫����
	HUPAI_TYPE_ShuangJianKe				=38,	//˫����
	HUPAI_TYPE_HuaLong					=39,	//����
	HUPAI_TYPE_TuiBuDao					=40,	//�Ʋ���
	HUPAI_TYPE_SanSeSanTongShun			=41,	//��ɫ��ͬ˳
	HUPAI_TYPE_SanSeSanJieGao			=42,	//��ɫ���ڸ�
	HUPAI_TYPE_WuFanHu					=43,	//�޷���
	HUPAI_TYPE_MiaoShouHuiChun			=44,	//���ֻش�
	HUPAI_TYPE_HaiDiLaoYue				=45,	//��������
	HUPAI_TYPE_QiangGang				=46,	//���ܺ�
	HUPAI_TYPE_QuanBuKao				=47,	//ȫ����(ʮ����)
	HUPAI_TYPE_ZuHeLong					=48,	//�����
	HUPAI_TYPE_DaYuWu					=49,	//������
	HUPAI_TYPE_XiaoYuWu					=50,	//С����
	HUPAI_TYPE_SanFengKe				=51,	//�����
	HUPAI_TYPE_QingLong					=52,	//����
	HUPAI_TYPE_SanSeShuangLongHui		=53,	//��ɫ˫����
	HUPAI_TYPE_YiSeSanBuGao				=54,	//һɫ������
	HUPAI_TYPE_QuanDaiWu				=55,	//ȫ����
	HUPAI_TYPE_SanTongKe				=56,	//��ͬ��
	HUPAI_TYPE_SanAnKe					=57,	//������
	HUPAI_TYPE_QiDui					=58,	//�߶�
	HUPAI_TYPE_QiXingBuKao				=59,	//���ǲ���
	HUPAI_TYPE_QuanShuangKe				=60,	//ȫ˫��
	HUPAI_TYPE_QingYiSe					=61,	//��һɫ
	HUPAI_TYPE_YiSeSanTongShun			=62,	//һɫ��ͬ˳
	HUPAI_TYPE_YiSeSanJieGao			=63,	//һɫ���ڸ�
	HUPAI_TYPE_QuanDa					=64,	//ȫ��
	HUPAI_TYPE_QuanZhong				=65,	//ȫ��
	HUPAI_TYPE_QuanXiao					=66,	//ȫС
	HUPAI_TYPE_YiSeSiBuGao				=67,	//һɫ�Ĳ���
	HUPAI_TYPE_SanGang					=68,	//����
	HUPAI_TYPE_HunYaoJiu				=69,	//���۾�
	HUPAI_TYPE_YiSeSiTongShun			=70,	//һɫ��ͬ˳
	HUPAI_TYPE_YiSeSiJieGao				=71,	//һɫ�Ľڸ�
	HUPAI_TYPE_QingYaoJiu				=72,	//���۾�
	HUPAI_TYPE_XiaoSiXi					=73,	//С��ϲ
	HUPAI_TYPE_XiaoSanYuan				=74,	//С��Ԫ
	HUPAI_TYPE_ZiYiSe					=75,	//��һɫ
	HUPAI_TYPE_SiAnKe					=76,	//�İ���
	HUPAI_TYPE_YiSeShuangLongHui		=77,	//һɫ˫����
	HUPAI_TYPE_DaSiXi					=78,	//����ϲ
	HUPAI_TYPE_DaSanYuan				=79,	//����Ԫ
	HUPAI_TYPE_LvYiSe					=80,	//��һɫ
	HUPAI_TYPE_JiuLianBaoDeng			=81,	//��������
	HUPAI_TYPE_SiGang					=82,	//�ĸܣ�ʮ���޺���
	HUPAI_TYPE_LianQiDui				=83,	//���߶�
	HUPAI_TYPE_ShiSanYao				=84		//ʮ����
};
///////////////////////////////////////////////////////////////

///�������ݽṹ
struct JingStruct
{
	BYTE  byPai[8];    //ÿ�ž��Ƶ���ֵ
	BYTE  byJingNum;   //������������
	JingStruct()
	{
		Init();
	}
	void Init()
	{
		memset(this,255,sizeof(JingStruct));
		byJingNum = 0;
	};
	bool CheckIsJing(BYTE pai)
	{
		for(int i=0;i<8;i++)
		{
			if(byPai[i] == pai && pai!=255)
				return true;
		}
		return false;
	};
	bool AddJing(BYTE pai)
	{
		for(int i=0;i<8;i++)
		{
			if(byPai[i] == 255 && pai !=255)
			{

				byPai[i] = pai;
				byJingNum++;
				return true;
			}
		}
		return false;
	};
	void sort()
	{
		BYTE pai = 255;
		for(int i=0;i<7;i++)
		{
			
			for(int j=i+1;j<8;++j)
			{
				if(byPai[j] < byPai[i])
				{
					pai = byPai[j];
					byPai[j] = byPai[i];
					byPai[i] = pai;
				}
			}
		}
	}
};

///�����������ݽṹ
struct GCPStruct
{
	BYTE  byType;    //����������
	BYTE  iStation;  //���������λ��
	BYTE  iBeStation;//�����������λ��
	BYTE  iOutpai;   //���˳�����
	BYTE  byData[4]; //������������
	
	GCPStruct()
	{
		Init();
	}
	void Init()
	{
		memset(byData,255,sizeof(byData));
		byType = 255;    //����������
		iOutpai = 255;   //���˳�����
		iStation = 255;  //���������λ��
		iBeStation = 255;//�����������λ��
	};
};
//
///�����ݽṹ��������ֵ��������
struct PaiStruct
{
	BYTE  pai;   //������
	BYTE  count; //������
	PaiStruct()
	{
		Init();
	};
	void Init()
	{
		memset(this,255,sizeof(PaiStruct));
		count = 0;
	};
};


// ��Ϸ���ݰ�
/********************************************************************************/
//ֻ��һ�����ݰ�����������ݿ��Բ�ʹ��,��������ʹ��
/*------------------------------------------------------------------------------*/
//��Ϸ�������ݰ�	DWJ
struct	GameStation_Base
{
	int			iVersion;				//���汾
	int			iVersion2;				//���汾

	BYTE		byGameStation;			//��Ϸ״̬

	BYTE		byBeginTime;			//��ʼ�ȴ�ʱ��
	BYTE		byOutTime;				//����ʱ��
	BYTE		byBlockTime;			//˼��ʱ��

	bool        bIsSuperUser;			//�Ƿ��ǳ����û�
	bool		bForceTuoGuan;			//�Ƿ�ǿ���й�
	bool		bShowTax;				//�Ƿ���ʾ̨��
	int			iTax;					//̨��

	GameStation_Base()
	{
		memset(this,0,sizeof(GameStation_Base));

		byBeginTime		= 30;			
		byOutTime		= 20;			
		byBlockTime		= 10;
		bForceTuoGuan	= true;
		bShowTax		= false;
		iTax			= 0;
	}
};
/*------------------------------------------------------------------------------*/
//�ȴ�ͬ��״̬
struct	GameStation_Wait_Agree : public GameStation_Base
{
	bool		bUserAgree[PLAY_COUNT];	//����Ƿ�ͬ����

	GameStation_Wait_Agree()
	{
		memset(this, 0, sizeof(GameStation_Wait_Agree));
	}
};
/*------------------------------------------------------------------------------*/
//�û��й����ݰ�
struct UserTouGuan
{						
	BYTE			byStation;				// ˭�й�
	bool			bIsTuoGuan;				// �Ƿ��й�
	bool			bTuoGuan[PLAY_COUNT];	// ��������й�״̬
	UserTouGuan()
	{
		memset(this,0,sizeof(UserTouGuan));
	}
};
/*------------------------------------------------------------------------------*/


struct GameStationData : public GameStation_Base
{
	BYTE				byNtStation;					// ׯ��λ��
	bool				m_bistuoguan[PLAY_COUNT];		// �Ƿ��й�
	
	BYTE				m_byNowOutStation;				// ���ڳ����û�
	BYTE				m_byThingDoing;					// ���ڷ������¼��� 
	//������
	BYTE				m_byArHandPai[PLAY_COUNT][HAND_CARD_NUM];//���Ʋ�����20�ţ�0Ϊ������־
	BYTE				m_iArMenPai[PLAY_COUNT][MEN_CARD_NUM];	//���Ʋ�����40��

	GameStationData()
	{
		Init();
	};
	void Init()
	{
		memset(this, 0, sizeof(GameStationData));	
		memset(m_byArHandPai,255,sizeof(m_byArHandPai));
		memset(m_iArMenPai,255,sizeof(m_iArMenPai));
		byNtStation = 255;
		m_byNowOutStation = 255;
		m_byThingDoing = 255;
	}
};









struct HaveThingStruct		// �����뿪
{
	BYTE	pos;
	TCHAR	szMessage[61];
};

struct LeaveResultStruct	// �����뿪���
{
	BYTE	bLeaveStation; //��Ҫ�뿪��ҵ�λ��
	BYTE	bDeskStation;
	int		bArgeeLeave;
};

struct MessageStruct		// �ͻ��˵�������,��Ϣ
{
	TCHAR Message[200];
};

///////////////////////////////////////////////////////////////////////////

#define MAX_HEPAI_TYPES     256 ///����������

///�齫�ƣ��������ƣ������㣬��ǰ���Ʒ���
struct MjMenPaiData 
{
	BYTE    byMenPai[300];				//�齫����������Ҹ�����������������ÿ������2���� 
	BYTE    byNt;						//ׯ��λ��
	BYTE	byStation;					//��ǰץ����ҵ�λ��
	BYTE	byDir;						//��ǰץ�Ʒ���(ץ�Ǹ������ǰ����)
	BYTE	byGetPaiDir;				//�������Ʒ���
	BYTE	byRemainDun;				//ʣ�����
	BYTE	byGetPai;				    //���ƶ���
	BYTE    byMenPaiDun[PLAY_COUNT];	//ÿ�������ǰ�Ķ���
	BYTE    byStartIndex;				//������ʼ����		
	BYTE    byEndIndex;				    //���ƽ�������		
	BYTE    byCaiShenIndex;				//����λ������		
	BYTE    byAllPaiNum;				//�����Ƶ�����		

	MjMenPaiData()
	{
		Init();
	};
	void Init()
	{
		memset(byMenPai,255,sizeof(byMenPai));
		memset(byMenPaiDun,255,sizeof(byMenPaiDun));//�����ǰ�Ķ���
		byNt = 255;						//ׯ��λ��
		byStation = 255;					//��ǰץ����ҵ�λ��
		byDir = 255;						//��ǰץ�Ʒ���(ץ�Ǹ������ǰ����)
		byGetPaiDir = 255;				//�������Ʒ���
		byRemainDun = 255;				//ʣ�����
		byGetPai = 255;				    //���ƶ���
		byStartIndex = 255;				//������ʼ����
		byEndIndex = 255;				    //���ƽ�������
		byAllPaiNum = 255;				    //�����Ƶ�����
		byCaiShenIndex = 255;				//����λ������
	};
	BYTE GetMenPaiNum()
	{
		BYTE num = 0;
		for(int i=0;i<300;i++)
		{
			if(byMenPai[i] != 255)
			{
				num++;
			}
			if(num >= 254)
				break;
		}
		return num;
	};
	BYTE GetOnePaiNum(BYTE pai)
	{
		BYTE num = 0;
		for(int i=0;i<300;i++)
		{
			if(byMenPai[i] == pai)
			{
				num++;
			}
		}
		return num;
	};
	bool DeleteAnMenPai(BYTE pai)
	{
		if(pai == 255)
			return false;
		for(int i=0;i<300;++i)
		{
			if(byMenPai[i] != 255)
			{
				byMenPai[i] = 255;
				return true;
			}
		}
		return false;
	};
	bool ChangAnMenPai(BYTE oldpai,BYTE newpai)// ������Ҫ�������� oldpai,���������� newpai
	{
		if(oldpai == 255 || newpai == 255)
			return false;
		for(int i=0;i<300;++i)
		{
			if(byMenPai[i] == oldpai)
			{
				byMenPai[i] = newpai;//���Ƴɹ�
				return true;
			}
		}
		return false;
	};
};
/*--------------------------------------------------------------------*/
///�齫��������
struct MjRuleSet 
{
	BYTE    byAllMjCount;		//�齫������ 
	BYTE	byHandCardNum;		//��������
	BYTE	byGamePassType;		//����ʣ������
	BYTE	byGamePassNum;		//��������
	BYTE	byNextNtType;		//�¾�ׯ�ҵ�ȷ������	dwjdelete
	BYTE    byMenPaiNum[PLAY_COUNT];		//����������dwjdelete


	BYTE    byAutoOutTime;		//�Զ�����ʱ��	DWJ
	BYTE    byOutTime;			//����ʱ��		DWJ
	BYTE    byBlockTime;		//����˼��ʱ��	DWJ
	BYTE    byBeginTime;		//��ʼ�ȴ�ʱ��	DWJ
	

	bool	bHaveWan;			//�Ƿ�����		DWJ
	bool	bHaveTiao;			//�Ƿ�����		DWJ
	bool	bHaveBing;			//�����б�		DWJ
	bool    bHaveHongZhong;		//�Ƿ��к���	DWJ
	bool    bHaveFaCai;			//�Ƿ��з���	DWJ
	bool    bHaveBaiBan;		//�Ƿ��аװ�	DWJ
	bool    bHaveFengPai;		//�Ƿ��ж�������DWJ
	bool    bHaveFlower;		//�Ƿ��л���	DWJ

	bool	bHaveJing;			//���޲���		

	bool    bNetCutTuoGuan;		//�Ƿ�����й�
	bool	bForceTuoGuan;		//�Ƿ�ǿ���й�
	bool	bAutoBegin;			//ʱ�䵽���Ƿ��Զ���ʼ	DWJ

	MjRuleSet()
	{
		memset(this, 0, sizeof(MjRuleSet));		
	}

};
/*--------------------------------------------------------------------*/
///��������
struct ActionRuleSet 
{
	bool bChi;			//��
	bool bChiFeng;		//�Է���
	bool bChiJian;		//���з���
	bool bChiJing;		//�Բ���
	bool bPeng;			//��
	bool bKan;			//��
	bool bSaoHu;		//ɨ�����黢�齫��
	bool bGang;			//��
	bool bBuGang;		//����
	bool bTing;			//��
	bool bQiangChi;		//����(�Ժ�����)
	bool bGangAfterTing;//���ƺ��ܸ���
	bool bSeziAfterGang;//�ܺ��ɫ��ץ��
	bool bQxHh;			//�������Ⱥ���һȦ�ڣ�
	bool bQxHhBut;		//�������Ⱥ���һȦ�ڣ�������ͬ���ƿ��ԣ����ø������
	bool bOutLianZhang;	//���ƺ��ܳ����ţ������Ʋ�����������Լ������������˳�ӣ�
	ActionRuleSet()
	{
		memset(this, 0, sizeof(ActionRuleSet));
	}
};
///�������
struct CountFenRuleSet 
{
	CountFenRuleSet()
	{
		memset(this, 0, sizeof(CountFenRuleSet));
	}
};
///��������
struct HuPaiRuleSet 
{
	bool bDuoXiang;		//һ�ڶ���
	bool bJieHu;		//�غ�,��һ�ڶ����У����˿��Ժ��ƣ����������͵���ҿ��Խغ�
	bool bZimoHu;		//����
	bool bDianPaoHu;	//����
	bool bNoLimite;		//û��������ֻҪ���ͷ��ϼ�¼��4+1 ���� 7�ԣ�ʮ���ã�ʮ���ۣ�
	bool bSanMQ;		//������
	bool bHaveYJ;		//���۾�
	bool bHaveZi;		//������
	bool bHaveZorYJ;	//�����ƻ����۾�
	bool b258Jiang;		//258����
	bool bKaiMen;		//�ѿ���
	bool bShouBaYi;		//�����ְ�һ
	bool bPiaoCan;		//Ʈ����������
	bool bQiangGHu;		//���ܺ�
	bool bGangKai;		//���Ͽ���
	bool bGangPao;		//�ܺ���
	bool bHaiDiLaoYue;  //��������
	bool bTianHu;		//���
	bool bDiHu;			//�غ�
	BYTE byPingHuType;	//ƽ����������,0û�����ƣ�1��2��3
	HuPaiRuleSet()
	{
		memset(this, 0, sizeof(HuPaiRuleSet));
	}
};

///������������
struct HuPaiTypeSet 
{
	BYTE byZiMo;			//����
	BYTE byTianHu;			//���
	BYTE byDiHu;			//�غ�
	BYTE byGSH;				//���ϻ�
	BYTE byGHP;				//�ܺ���
	BYTE byWuHu;			//�ں�����
	BYTE byQiXing;			//����
	BYTE byLongQiDui;		//���߶�
	BYTE byYiBanGao;		//һ���
	BYTE byXiXiangFeng;		//ϲ���
	BYTE byLianLiu;			//����
	BYTE byLaoShaoFu;		//���ٸ�
	BYTE byYaoJiuKe;		//�۾ſ�
	BYTE byMingGang;		//����
	BYTE byQueYiMen;		//ȱһ��
	BYTE byWuZi;			//����
	BYTE byBianZhang;		//����
	BYTE byKanZhang;		//����
	BYTE byDanDiao;			//������
	BYTE byJianKe;			//����
	BYTE byQuanFengKe;		//Ȧ���
	BYTE byMenFengKe;		//�ŷ��
	BYTE byMenQianQing;		//��ǰ��
	BYTE byPingHu;			//ƽ��
	BYTE bySiGuiYi;			//�Ĺ�һ
	BYTE byShuangTongKe;	//˫ͬ��
	BYTE byShuangAnKe;		//˫����
	BYTE byAnGang;			//����
	BYTE byDuanYao;			//����
	BYTE byQuanDaiYao;		//ȫ����
	BYTE byBuQiuRen;		//������
	BYTE byShuangMingGang;	//˫����
	BYTE byHuJueZhang;		//�;���
	BYTE byPengPengHu;		//������
	BYTE byHunYiSe;			//��һɫ
	BYTE bySanSeSanBuGao;	//��ɫ������
	BYTE byWuMenQi;			//������
	BYTE byQuanQiuRen;		//ȫ����
	BYTE byShuangAnGang;	//˫����
	BYTE byShuangJianKe;	//˫����
	BYTE byHuaLong;			//����
	BYTE byTuiBuDao;		//�Ʋ���
	BYTE bySSSTongShun;		//��ɫ��ͬ˳
	BYTE bySSSJieGao;		//��ɫ���ڸ�
	BYTE byWuFanHu;			//�޷���
	BYTE byMiaoShouHuiChun;	//���ֻش�
	BYTE byHaiDiLaoYue;		//��������
	BYTE byQiangGangHu;		//���ܺ�
	BYTE byQuanBuKao;		//ȫ����
	BYTE byZuHeLong;		//�����
	BYTE byDaYuWu;			//������
	BYTE byXiaoYuWu;		//С����
	BYTE bySanFengKe;		//�����
	BYTE byQiangLong;		//����
	BYTE bySSShuangLongHui;	//��ɫ˫����
	BYTE byYiSeSanBuGao;	//һɫ������
	BYTE byQuanDaiWu;		//ȫ����
	BYTE bySanTongKe;		//��ͬ��
	BYTE bySanAnKe;			//������
	BYTE byQiDui;			//�߶�
	BYTE byQiXingBuKao;		//���ǲ���
	BYTE byQuanShuangKe;	//ȫ˫��
	BYTE byQingYiSe;		//��һɫ
	BYTE byYiSSTongShun;	//һɫ��ͬ˳
	BYTE byYiSSJieGao;		//һɫ���ڸ�
	BYTE byQuanDa;			//ȫ��
	BYTE byQuanZhong;		//ȫ��
	BYTE byQuanXiao;		//ȫС
	BYTE byYiSeSiBuGao;		//һɫ�Ĳ���
	BYTE bySanGang;			//����
	BYTE byHunYaoJiu;		//���۾�
	BYTE byYSSiTongShun;	//һɫ��ͬ˳
	BYTE byYSSiJieGao;		//һɫ�Ľڸ�
	BYTE byQingYaoJiu;		//���۾�
	BYTE byXiaoSiXi;		//С��ϲ
	BYTE byXiaoSanYuan;		//С��Ԫ
	BYTE byZiYeSe;			//��һɫ
	BYTE bySiAnKe;			//�İ���
	BYTE byYSShuangLongHui;	//һɫ˫����
	BYTE byDaSiXi;			//����ϲ
	BYTE byDaSanYuan;		//����Ԫ
	BYTE byLvYiSe;			//��һɫ
	BYTE byJiuLianBaoDeng;	//��������
	BYTE bySiGang;			//�ĸܣ�ʮ���޺���
	BYTE byLianQiDui;		//���߶�
	BYTE byShiSanYao;		//ʮ����

	HuPaiTypeSet()
	{
		memset(this, 255, sizeof(HuPaiTypeSet));
	}
};

///�齫�¼����ݽṹ
struct MjThing
{
	BYTE byBeginNext1;			//	��һ��ǰ����Ϸ��ʼ�¼�����¼���
	BYTE byBeginNext2;			//	��һ�ֺ���Ϸ��ʼ�¼�����¼���
	BYTE byDongNtNext;			//	�Զ�Ϊׯ�¼��ĺ���¼���
	BYTE by2SeziNtNext;			//	��2��ɫ�Ӷ�ׯ�¼��ĺ���¼���
	BYTE by2SeziNtAndGpNext;	//	��2��ɫ�Ӷ�ׯ�����Ƶ��¼��ĺ���¼���
	BYTE byTurnSeziNtNext;		//	������2��ɫ�Ӷ�ׯ�¼��ĺ���¼���
	BYTE by2SeziDirNext;		//	��2��ɫ�Ӷ������¼��ĺ���¼���
	BYTE by2SeziDirAndGpNext;	//	��2��ɫ�Ӷ���������Ƶ��¼��ĺ���¼���
	BYTE by2SeziGpNext;			//	��2��ɫ�Ӷ����Ƶ��¼��ĺ���¼���
	BYTE bySendPaiNext;			//	�����¼��ĺ���¼���
	BYTE byTiaoPaiNext;			//	�����¼��ĺ���¼���
	BYTE by2SeziJingNext;		//	��2��ɫ�Ӷ������¼��ĺ���¼���
	BYTE by1SeziJinNext;		//	��1��ɫ�Ӷ������¼��ĺ���¼���
	BYTE byAllBuHuaNext;		//	����ǰ������Ҳ����¼��ĺ���¼���
	BYTE byOneBuHuaNext;		//	��Ϸ�е��˲����¼��ĺ���¼���
	BYTE byBeginOutNext;		//	��ʼ�����¼��ĺ���¼���
	BYTE byOutPaiNext;			//	�����¼��ĺ���¼���
	BYTE byZhuaPaiNext;			//	ץ���¼��ĺ���¼���
	BYTE byChiPaiNext;			//	�����¼��ĺ���¼���
	BYTE byPengPaiNext;			//	�����¼��ĺ���¼���
	BYTE byKanPaiNext;			//	�����¼��ĺ���¼���
	BYTE bySaoHuNext;			//	ɨ���¼��ĺ���¼���
	BYTE byGangPaiNext;			//	�����¼��ĺ���¼���
	BYTE byTingPaiNext;			//	�����¼��ĺ���¼���
	BYTE byHuPaiNext;			//	�����¼��ĺ���¼���
	BYTE byCountFenNext;		//	����¼��ĺ���¼���
	BYTE byEndHandleNext;		//	���������¼��ĺ���¼���
	BYTE byUnnormalEngNext;		//	�����������¼��ĺ���¼���

	MjThing()
	{
		memset(this, 255, sizeof(MjThing));
	}
};

//�齫�������ݰ���֪ͨ�ͻ��˸��齫������
struct MjRuleStruct 
{	
	MjRuleSet       m_mjRule;					// �齫��������
	ActionRuleSet   m_mjAction;                 // �齫��������
	CountFenRuleSet m_mjFenRule;				// �齫�������
	HuPaiRuleSet    m_mjHuRule;					// �齫��������
	HuPaiTypeSet	m_mjHuType;					// �齫��������
};

//���������������ݰ�
struct SuperStruct
{
	BYTE  bySetType;	//�������ͣ�0 �������ƣ�1��ѡ���ƣ�2�����Լ�����һ���ƣ�3������ǿ����һ����
	BYTE  mjcount;		//�����Ƶĸ���
	BYTE  mjdata[HAND_CARD_NUM];	//����������
	BYTE  handdata[HAND_CARD_NUM];	//����������

	SuperStruct()
	{
		Init();
	}
	void Init()
	{	 
		bySetType = 255;
		mjcount = 0;
		for( int i = 0; i < 20; i++)
		{  mjdata[i] = 255; }
	}
};
/********************************************************************************/

// ���ݰ���������ʶ

/********************************************************************************/
#define		MDM_GM_GAME_NOTIFY				180				///��Ϣ���ͣ���Ϸ֪ͨ��Ϣ
#define		ASS_GM_GAME_STATION				2				///��Ϸ״̬
#define		ASS_GM_AGREE_GAME               1               ///�û�ͬ��


#define ASS_UG_USER_SET					70				//�û�������Ϸ
#define ASS_SEZIFINISH					72				//ɫ�ӽ���
#define ASS_AUTOCARD					74				//�й�
#define ASS_PASS_CHECK					75				//"��"
#define ASS_HAVE_THING					76				//�����뿪
#define ASS_LEFT_RESULT					77				//�뿪���

#define ASS_SUPER						78				//�����ͻ��ˣ�������
#define ASS_HUPAI_TEST					79				//�����ͻ��ˣ����Ʋ���

#define ASS_MJ_RULE						89				//�齫��������
#define ASS_EXIT						90				//�˳�
#define ASS_MESSAGE						91				//��Ϣ
#define	ASS_SET_STATE					92				//���ڳ����˵��������󷢸�4���ͻ��˵ļ�ʱ���ź�
#define ASS_GM_SHORT_STOP               93              //��ͣ��Ϣ
#define ASS_NET_CAUSE_END               94              //����ԭ������Ϸ����

//#define ASS_HUPAI_TEST					159			//�����ͻ��ˣ����Ʋ���
#define ASS_CHANGE_PAI					160				//�û����ƣ�������
#define ASS_SET_MOPAI					161				//�û�����׼��Ҫ������
#define ASS_HUANGZHUANG					162				//ǿ�ƻ�ׯ
#define ASS_CHANGE_PAI_RESULT           163             //�û����ƽ��
/********************************************************************************/

//////////////////////�¼���////////////////////////////////////////////////////////////////////
//����ǰ�¼�
enum MJTHINGS
{
	THING_AUTOOUTCARD		= 9,
    THING_GAME_BEGIN		=10,		//��Ϸ��ʼ�¼�			DWJ			        
    THING_DING_NT			,			//��ׯ�¼�				DWJ				         
    THING_2SEZI_NT			,			//�׾���2��ɫ�ӵĵ�����Ϊׯ�¼�		   
    THING_2SEZI_NT_GP		,			//�׾���2��ɫ�Ӷ�ׯ�Һ����Ƶ��¼�	
    THING_TURN_2SEZI_NT		,			//�׾�������2��ɫ�Ӷ�ׯ���¼�		
    THING_2SEZI_DIR			,			//��2��ɫ���¼������Ʒ����¼�			DWJ	
    THING_2SEZI_DIR_GP		,			//��2��ɫ���¼������Ʒ�������Ƶ��¼�	DWJ
    THING_2SEZI_GP			,			//��2��ɫ���¼������Ƶ��¼�		
    THING_2SEZI_NT_DIR_GP	,			//��2��ɫ���¼������Ƶ��¼�	
    //����ǰ�¼�            
    THING_SEND_PAI			,			//�����¼�		DWJ					
    THING_TIAO_PAI			,			//�����¼�							
    THING_2SEZI_JING		,			//��2��ɫ�Ӷ������¼�			
    THING_1SEZI_JIN			,			//��1��ɫ�Ӷ������¼�
    THING_ALL_BUHUA		    ,			//Ϊ������Ҳ����¼�	DWJ			
    THING_ONE_BUHUA		    ,			//������Ҳ����¼�		DWJ				
    //���������¼�          
    THING_BEGIN_OUT			,			//ׯ�ҿ�ʼ����֪ͨ�¼�
    THING_DING_QUE          ,           //��ȱ�¼�
    THING_OUT_PAI			,			//�����¼�				DWJ
    THING_ZHUA_PAI			,			//ץ���¼�
    THING_CPG_NOTIFY		,			//�ܳ���֪ͨ�¼��¼�	DWJ
    THING_CHI_PAI			,			//�����¼�				DWJ
    THING_PENG_PAI			,			//�����¼�				DWJ
	THING_GUO_PAI			,			//�����¼�				DWJ
    THING_KAN_PAI			,			//�����¼�
    THING_SAO_HU			,			//ɨ���¼�
    THING_GANG_PAI			,			//�����¼�				DWJ
    THING_TING_PAI			,			//�����¼�				DWJ
    //���������¼�          

    //���Ƽ����ƺ��¼�
    THING_HU_PAI			,			//���¼�		DWJ
    THING_COUNT_FEN			,			//����¼�		DWJ
    THING_ENG_HANDLE		,			//���������¼�	DWJ
    THING_ENG_UN_NORMAL		,			//���������������¼�
    THING_HAVE_ACTION		,                           
	THING_CAN_TING			,
	THING_CALCULATE_BOARD=164,			//�����
	THING_LAST_ROUNDS		,			//ʣ�����
	THING_MAX		                //����¼�id
};                              
             

//////////////////////�¼����ݽṹ/////////////
/*----------------------------------------------------------------*/
//�����
struct CalculateBoard 
{
	INT bBestFire;//����������
	INT bWinner;//���Ӯ��
	INT iZimo[PLAY_COUNT];//��������
	INT iJiePao[PLAY_COUNT];//���ڴ���
	INT iDianPao[PLAY_COUNT];//���ڴ���
	INT iAnGan[PLAY_COUNT];//���ܴ���
	INT iMingGan[PLAY_COUNT];//���ܴ���
	long long i64WinMoney[PLAY_COUNT];//��Ӯ���
	CalculateBoard() {
		init();
	}
	void init() {
		memset(this, 0, sizeof(CalculateBoard));
	}
};

//ʣ�����
struct LastRounds
{
	int iLastRounds;//ʣ�����
	void Clear() {
		memset(this, 0, sizeof(LastRounds));
	}
};

///��Ϸ��ʼ�¼�	DWJ
struct tagBegin
{
	BYTE	byNt;		//ׯ��λ��
	int		iHuangZhuangCount;	//��ׯ����
	BYTE	byPlayCount;// ��Ϸ�غ�
	BYTE	byQuanFeng;	// Ȧ������
	BYTE	byMenPai[PLAY_COUNT][MEN_CARD_NUM];//����
	BYTE	byNo;		//�¼��Ĵ���

	void Clear()
	{
		byNt	=255;		//ׯ��λ��
		iHuangZhuangCount = 0;
		byPlayCount	=255;// ��Ϸ�غ�
		byQuanFeng	=255;// Ȧ������
		memset(byMenPai, 255, sizeof(byMenPai));	//����
		byNo = THING_DING_NT;//�¼��Ĵ���
	}
};
/*----------------------------------------------------------------*/
///��ׯ�¼�	DWJ
struct tagDongNt
{
	BYTE	byNt;		//ׯ��λ��
	BYTE	byNo;		//�¼��Ĵ���
	int		iHuangZhuangCount;	//��ׯ����

	void Clear()
	{	
		byNt	=255;//ׯ��λ��
		byNo	= THING_GAME_BEGIN;//�¼��Ĵ���
		iHuangZhuangCount = 0;
	}
};

/*----------------------------------------------------------------*/
///��2��ɫ��ȷ������λ���¼�	DWJ
struct	tagTwoSeziDir
{
	BYTE	byUser;			//��ɫ�����
	BYTE	byNt;			//ׯ��
	BYTE	bySezi0;		//ɫ��0����
	BYTE	bySezi1;		//ɫ��1����
	BYTE	byDirection;	//���Ʒ�λ
	BYTE	byNo;			//�¼��Ĵ���

	void Clear()
	{
		byUser	=255;		//��ɫ�����
		bySezi0	=255;		//ɫ��0����
		bySezi1	=255;		//ɫ��1����
		byNt = 255;			//ׯ��
		byDirection	=255;	//���Ʒ�λ
		byNo = THING_2SEZI_DIR;//�¼��Ĵ���
	}
};
/*----------------------------------------------------------------*/
///��2��ɫ��ȷ������λ�ã������ͣ������Ƶ㣨��С�㣩�¼�	DWJ
struct	tagTwoSeziDirAndGetPai
{
	BYTE	byUser;		//��ɫ�����
	BYTE	bySezi0;	//ɫ��0����
	BYTE	bySezi1;	//ɫ��1����
	BYTE	byDirection;//���Ʒ�λ
	BYTE	byGetPai;	//���Ƶ�

	BYTE	byNo;		//�¼��Ĵ���

	void Clear()
	{
		byUser	=255;	//��ɫ�����
		bySezi0	=255;	//ɫ��0����
		bySezi1	=255;	//ɫ��1����
		byDirection	=255;//���Ʒ�λ
		byGetPai	=255;	//���Ƶ�

		byNo = THING_2SEZI_DIR_GP;//�¼��Ĵ���
	}
};
/*----------------------------------------------------------------*/
///�����¼�
struct	tagSendPai
{
	BYTE	byDo;			//0δ������10�ѽ������м�״̬Ϊ���ڷ���
	BYTE	bySendPai;		//��������
	BYTE	byGetPai;		//���Ƶ�
	BYTE	byAllPaiNum;	//������
	BYTE	m_byArHandPai[PLAY_COUNT][HAND_CARD_NUM];//��������
	BYTE	m_byArHandPaiCount[PLAY_COUNT];		//�����������
	BYTE	byMenPai[PLAY_COUNT][MEN_CARD_NUM];//����
	BYTE	byStartIndex;///��ʼ����
	BYTE	byEndIndex;  ///��������

	BYTE	byNo;	//�¼��Ĵ���

	void Clear()
	{
		byDo		=255;//0δ������10�ѽ������м�״̬Ϊ���ڷ���
		bySendPai	=255;//��������
		byGetPai	=255;//���Ƶ�
		byAllPaiNum	=255;//������
		memset(m_byArHandPai, 255, sizeof(m_byArHandPai));//��������	
		memset(m_byArHandPaiCount,0,sizeof(m_byArHandPaiCount));//��������
		memset(byMenPai, 255, sizeof(byMenPai));	//����
		byStartIndex	=255;///��ʼ����
		byEndIndex	=255;///��������
		byNo = THING_SEND_PAI;//�¼��Ĵ���
	}
};
/*----------------------------------------------------------------*/
///������Ҳ����¼�
struct	tagAllBuHua
{
	BYTE	byDo;//0δ������10�ѽ������м�״̬Ϊ���ڷ���
	BYTE	byUser[PLAY_COUNT];//��Ҫ�������λ��
	BYTE	m_byArHandPai[PLAY_COUNT][HAND_CARD_NUM];//��������
	BYTE	m_byArHandPaiCount[PLAY_COUNT];//��������
	BYTE	byMenPai[PLAY_COUNT][MEN_CARD_NUM];//����
	BYTE	m_byArHuaPai[PLAY_COUNT][HUA_CARD_NUM];//��������
	bool	bBuHuaFinish[PLAY_COUNT];//��¼�Ѿ��Ѿ�������ɵ����
	BYTE	byNo;	//�¼��Ĵ���
	BYTE	byNext;//��һ���¼��Ĵ���
	void Clear()
	{
		byDo = 255;//0δ������10�ѽ������м�״̬Ϊ���ڷ���
		memset(byUser, 255, sizeof(byUser));	//��Ҫ�������λ��
		memset(byMenPai, 255, sizeof(byMenPai));	//����
		memset(m_byArHandPai, 255, sizeof(m_byArHandPai));//��������	
		memset(m_byArHandPaiCount,0,sizeof(m_byArHandPaiCount));
		memset(m_byArHuaPai, 255, sizeof(m_byArHuaPai));//��������	
		memset(bBuHuaFinish,0,sizeof(bBuHuaFinish));
		byNo = THING_ALL_BUHUA;//�¼��Ĵ���
	}
};
/*----------------------------------------------------------------*/
///��ʼ����֪ͨ�¼�
struct	tagBeginOutPai
{
	BYTE	byDo;		//0δ������10�ѽ������м�״̬Ϊ���ڷ���
	BYTE	byUser;		//�״γ������λ��
	BYTE	byNt;		//ׯ��λ��

	BYTE	m_byArHandPai[PLAY_COUNT][HAND_CARD_NUM];//��������
	BYTE	m_byArHandPaiCount[PLAY_COUNT];//��������
	BYTE	byMenPai[PLAY_COUNT][MEN_CARD_NUM];//����
	BYTE	byNo;	//�¼��Ĵ���

	void Clear()
	{
		byDo	=255;//0δ������10�ѽ������м�״̬Ϊ���ڷ���
		byUser	=255;//�״γ������λ��
		byNt	=255;//ׯ��λ��
		memset(m_byArHandPai, 255, sizeof(m_byArHandPai));//��������	
		memset(m_byArHandPaiCount,0,sizeof(m_byArHandPaiCount));
		memset(byMenPai, 255, sizeof(byMenPai));	//����
		byNo = THING_BEGIN_OUT;//�¼��Ĵ���
	}
};
/*----------------------------------------------------------------*/
///�����ܺ�֪ͨ�¼��¼�
struct	tagCPGNotify
{
	BYTE	byDo;				//0δ������10�ѽ������м�״̬Ϊ���ڷ���
	BYTE	byUser;				//�������λ��
	BYTE	byPs;				//���Ƶ�ֵ
	bool	bZhuaPai;			//�����ץ�ƺ��ж���(�ͻ���������ʾ����ʱʱ���)

	BYTE	byBlockTime;		//����ʱ��	DWJ

	bool	bChi;				//�Ƿ��ܳ�
	bool	bPeng;				//�Ƿ�����
	bool	bGang;				//�Ƿ��ܸ�
	bool	bKan;				//�Ƿ��ܿ���
	bool	bSaoHu;				//��ǰ�ܷ�ɨ��
	bool	bTing;				//��ǰ�ܷ�����
	bool	bHu;				//�Ƿ��ܺ�
	bool	bQiangGang;			//�Ƿ����ܺ�
	bool    bHaveReturn;		//�ͻ����Ƿ񷵻ص��û�ѡ��
	bool    bCanAction;			//����Ƿ��ж�������
	BYTE	m_iChi[3][3];		//�ܳԵ���
	BYTE	m_iGangData[4][2];	//�ܸܵ���
	BYTE	m_byTingCanOut[HAND_CARD_NUM];//�����ܴ����
	BYTE    m_byMaxThing;		//��������������
	BYTE	byHuType[MAX_HUPAI_TYPE];	//��������
	BYTE	m_byKan[5];			//��ǰ�ܿ�����
	BYTE    m_iHuPs;			//��Һ�����
	BYTE	m_byDianPao;		//�������λ��
	BYTE	byNo;				//�¼��Ĵ���
//	BYTE	byNext;				//��һ���¼��Ĵ���(0������ѭ���¼�����һ���¼����û�����)

	void Clear()
	{
		byDo	=255;			//0δ������10�ѽ������м�״̬Ϊ���ڷ���
		byUser	=255;			//�������λ��
		byPs	=255;			//���Ƶ�ֵ
		byBlockTime = 255;		//����˼��ʱ��
		bZhuaPai=false;			//�Ƿ��Լ�ץ��
		bChi	=0;				//�Ƿ��ܳ�
		bPeng	=0;				//�Ƿ�����
		bGang	=0;				//�Ƿ��ܸ�
		bKan	=0;				//�Ƿ��ܿ���
		bSaoHu  =0;				//��ǰ�ܷ�ɨ��
		bTing	=0;				//��ǰ�ܷ�����
		bHu		=0;				//�Ƿ��ܺ�
		bQiangGang = 0;			//�Ƿ����ܺ�
		bCanAction = false;		//����Ƿ��ж�������
		m_byMaxThing = ACTION_NO;//��������������
		bHaveReturn = 0;		//�ͻ����Ƿ񷵻ص��û�ѡ��
		memset(m_iChi,255,sizeof(m_iChi));//�ܳԵ���
		memset(m_iGangData,255,sizeof(m_iGangData));//�ܸܵ���	
		memset(m_byTingCanOut,255,sizeof(m_byTingCanOut));///�����ܴ����
		memset(byHuType,255,sizeof(byHuType));///��������
		memset(m_byKan,255,sizeof(m_byKan));///��ǰ�ܿ�����
		m_iHuPs = 255;///��Һ�����
		m_byDianPao = 255;		//�������λ��
		byNo = THING_OUT_PAI;//�¼��Ĵ���
	}
};
/*----------------------------------------------------------------*/
///�����¼�
struct	tagOutPai
{
	BYTE	byDo;				//0δ������10�ѽ������м�״̬Ϊ���ڷ���
	BYTE	byUser;				//�������λ��
	BYTE	byPs;				//���Ƶ�ֵ
	bool	bTing;

	BYTE	m_byArHandPai[PLAY_COUNT][HAND_CARD_NUM];//��������
	BYTE	m_byArHandPaiCount[PLAY_COUNT];	//��������
	BYTE	m_byArOutPai[PLAY_COUNT][OUT_CARD_NUM];//���Ʋ�����160�ţ�0Ϊ������־
	BYTE	m_byArOutPaiCount[PLAY_COUNT];		//���Ƶ�����
	bool	bUserTing[PLAY_COUNT];
	BYTE	byNo;				//�¼��Ĵ���
	void Clear()
	{
		byDo	=255;				//0δ������10�ѽ������м�״̬Ϊ���ڷ���
		byUser	=255;				//�������λ��
		byPs	=255;				//���Ƶ�ֵ

		memset(m_byArHandPai, 255, sizeof(m_byArHandPai));//��������	
		memset(m_byArHandPaiCount, 0 ,sizeof(m_byArHandPaiCount));	//��������
		memset(m_byArOutPai, 255, sizeof(m_byArOutPai));//��������	
		memset(m_byArOutPaiCount, 0, sizeof(m_byArOutPaiCount));//��������	
		memset(bUserTing , 0, sizeof(bUserTing));

		byNo = THING_OUT_PAI;//�¼��Ĵ���
	}
};
/*----------------------------------------------------------------*/
///ץ�����¼�
struct	tagZhuaPai
{
	BYTE	byDo;		//0δ������10�ѽ������м�״̬Ϊ���ڷ���
	BYTE	byUser;		//ץ�����λ��
	BYTE	byPs;		//ץ�Ƶ�ֵ
	BYTE	byStartIndex;///��ʼ����
	BYTE	byEndIndex;  ///��������
	BYTE	byCaiShenIndex; ///��������
	BYTE	m_byArHandPai[PLAY_COUNT][HAND_CARD_NUM];//��������
	BYTE	m_byArHandPaiCount[PLAY_COUNT];	//��������
	BYTE	m_byArOutPai[PLAY_COUNT][OUT_CARD_NUM];//���Ʋ�����160�ţ�0Ϊ������־
	BYTE	byMenPai[PLAY_COUNT][MEN_CARD_NUM];//����
	BYTE	m_byArHuaPai[PLAY_COUNT][HUA_CARD_NUM];//��һ���
	BYTE	byGetPaiIndex;//ץ�Ƶ�����
	bool	bHead;		//ץ�Ƶķ���
	bool	bCanOutPai;	//ץ�ƺ��Ƿ���Գ���
	bool    m_bGangKai;	//�Ƿ�ܿ�	
	bool    m_bBuHua;	//�Ƿ�Ҫ����	
	bool    bUserTing[4];		//�������״̬
	BYTE	byNo;		//�¼��Ĵ���
	BYTE	byNext;		//��һ���¼��Ĵ���
	void Clear()
	{
		byDo	=255;		//0δ������10�ѽ������м�״̬Ϊ���ڷ���
		byUser	=255;		//ץ�����λ��
		byPs		=255;		//ץ�Ƶ�ֵ
		byStartIndex=255;///��ʼ����
		byEndIndex	=255;  ///��������
		byCaiShenIndex=255; ///��������
		memset(m_byArHandPai, 255, sizeof(m_byArHandPai));//��������	
		memset(m_byArHandPaiCount, 0, sizeof(m_byArHandPaiCount));	//��������
		memset(m_byArOutPai, 255, sizeof(m_byArOutPai));//��������
		memset(byMenPai, 255, sizeof(byMenPai));	//����
		memset(m_byArHuaPai, 255, sizeof(m_byArHuaPai));	//����
		byGetPaiIndex = 255;//ץ�Ƶ�����
		bHead = true;
		bCanOutPai = false;//ץ�ƺ��Ƿ���Գ���
		m_bGangKai = false;//�Ƿ�ܿ�	
		m_bBuHua = false;	//�Ƿ�Ҫ����	
		memset(bUserTing, 0, sizeof(bUserTing));//�������״̬	
		byNo = THING_ZHUA_PAI;//�¼��Ĵ���
	}
};
/*----------------------------------------------------------------*/
///������Ҳ����¼�
struct tagOneBuHua
{
	BYTE	byDo;//0δ������10�ѽ������м�״̬Ϊ���ڷ���
	BYTE	byUser;		//�������λ��
	BYTE	byHua;		//ץ���û���
	BYTE	byPs;		//��������
	BYTE	m_byArHandPai[PLAY_COUNT][HAND_CARD_NUM];//��������
	BYTE	m_byArHandPaiCount[PLAY_COUNT];	//��������
	BYTE	byMenPai[PLAY_COUNT][MEN_CARD_NUM];//����
	BYTE	m_byArHuaPai[PLAY_COUNT][HUA_CARD_NUM];//
	bool	bFinish;//�Ƿ񲹻�����
	BYTE	byNo;	//�¼��Ĵ���
	BYTE	byNext;//��һ���¼��Ĵ���
	void Clear()
	{
		byDo	=255;//0δ������10�ѽ������м�״̬Ϊ���ڷ���
		byUser	=255;//�������λ��
		byHua	=255;	  //ץ���û���
		byPs	=255;	  //��������
		memset(byMenPai, 255, sizeof(byMenPai));	//����
		memset(m_byArHandPai, 255, sizeof(m_byArHandPai));//��������
		memset(m_byArHandPaiCount, 0 ,sizeof(m_byArHandPaiCount));	//��������
		memset(m_byArHuaPai, 255, sizeof(m_byArHuaPai));//��������
		bFinish=false;
		byNo = THING_ONE_BUHUA;//�¼��Ĵ���
	}
};
/*----------------------------------------------------------------*/
///�������¼�
struct tagChiPai
{
	BYTE	byDo;		//0δ������10�ѽ������м�״̬Ϊ���ڷ���
	BYTE	byUser;		//�������λ��
	BYTE	byBeChi;	//���������λ��
	BYTE	byType;		//���Ƶ����ͣ�0�Դ�1���м䣬2��С�������ƣ�
	BYTE	byPs;		//�Ե���ֵ
	BYTE	byChiPs[3];	//���Ƶ�����
	BYTE	m_byArHandPai[PLAY_COUNT][HAND_CARD_NUM];//��������
	BYTE	m_byArHandPaiCount[PLAY_COUNT];	//��������
	BYTE	m_byArOutPai[PLAY_COUNT][OUT_CARD_NUM];	//���Ʋ�����160�ţ�0Ϊ������־
	BYTE	m_byArOutPaiCount[PLAY_COUNT];		//���Ƶ�����
	BYTE	byNo;	//�¼��Ĵ���
	BYTE	byNext;//��һ���¼��Ĵ���
	void Clear()
	{
		byDo	=255;//0δ������10�ѽ������м�״̬Ϊ���ڷ���
		byUser	=255;//�������λ��
		byBeChi	=255;//���������λ��
		byType	=255;//���Ƶ����ͣ�0�Դ�1���м䣬2��С�������ƣ�
		byPs		=255;	//�Ե���ֵ
		memset(byChiPs, 255, sizeof(byChiPs));//���Ƶ�����
		memset(m_byArHandPai, 255, sizeof(m_byArHandPai));//��������	
		memset(m_byArHandPaiCount,0,sizeof(m_byArHandPaiCount));//��������
		memset(m_byArOutPai, 255, sizeof(m_byArOutPai));//��������
		memset(m_byArOutPaiCount,0,sizeof(m_byArOutPaiCount));	//��������
		byNo = THING_CHI_PAI;//�¼��Ĵ���
	}
};
/*----------------------------------------------------------------*/
///�������¼�
struct tagPengPai
{
	BYTE	byDo;		//0δ������10�ѽ������м�״̬Ϊ���ڷ���
	BYTE	byUser;		//�������λ��
	BYTE	byBePeng;	//���������λ��
	BYTE	byPs;		//������ֵ
	BYTE	m_byArHandPai[PLAY_COUNT][HAND_CARD_NUM];//��������
	BYTE	m_byArHandPaiCount[PLAY_COUNT];	//��������
	BYTE	m_byArOutPai[PLAY_COUNT][OUT_CARD_NUM];//���Ʋ�����160�ţ�0Ϊ������־
	BYTE	m_byArOutPaiCount[PLAY_COUNT];		//���Ƶ�����
	BYTE	byNo;	//�¼��Ĵ���
	BYTE	byNext;//��һ���¼��Ĵ���
	void Clear()
	{
		byDo	=255;//0δ������10�ѽ������м�״̬Ϊ���ڷ���
		byUser	=255;//�������λ��
		byBePeng	=255;//���������λ��
		byPs		=255;//������ֵ
		memset(m_byArHandPai, 255, sizeof(m_byArHandPai));//��������	
		memset(m_byArHandPaiCount,0,sizeof(m_byArHandPaiCount));//��������
		memset(m_byArOutPai, 255, sizeof(m_byArOutPai));//��������
		memset(m_byArOutPaiCount,0,sizeof(m_byArOutPaiCount));	//��������
		byNo = THING_PENG_PAI;//�¼��Ĵ���
	}
};
/*----------------------------------------------------------------*/
///�������¼�
struct tagGangPai
{
	BYTE	byDo;		//0δ������10�ѽ������м�״̬Ϊ���ڷ���
	BYTE	byUser;		//�������λ��
	BYTE	byBeGang;	//���������λ��
	BYTE	byType;		//���Ƶ�����
	BYTE	byPs;		//�ܵ���ֵ
	BYTE	byGangPai[4];//Ҫ�ܵ�������
	BYTE	m_byArHandPai[PLAY_COUNT][HAND_CARD_NUM];//��������
	BYTE	m_byArHandPaiCount[PLAY_COUNT];	//��������
	BYTE	m_byArOutPai[PLAY_COUNT][OUT_CARD_NUM];//���Ʋ�����160�ţ�0Ϊ������־
	BYTE	m_byArOutPaiCount[PLAY_COUNT];		//���Ƶ�����
	bool    bHe[4];//����ܷ����ܺ�
	bool    bChenkQ;//�������
	BYTE	byNo;	//�¼��Ĵ���
	BYTE	byNext;//��һ���¼��Ĵ���
	void Clear()
	{
		byDo	=255;//0δ������10�ѽ������м�״̬Ϊ���ڷ���
		byUser	=255;//�������λ��
		byBeGang	=255;//���������λ��
		byType	=255;//���Ƶ�����
		byPs		=255;	//�ܵ���ֵ
		memset(byGangPai, 255, sizeof(byGangPai));//Ҫ�ܵ�������
		memset(m_byArHandPai, 255, sizeof(m_byArHandPai));//��������	
		memset(m_byArHandPaiCount,0,sizeof(m_byArHandPaiCount));//��������
		memset(m_byArOutPai, 255, sizeof(m_byArOutPai));//��������
		memset(m_byArOutPaiCount,0,sizeof(m_byArOutPaiCount));	//��������
		memset(bHe, 0, sizeof(bHe));
		bChenkQ = false;
		byNo = THING_GANG_PAI;//�¼��Ĵ���
	}
};
/*----------------------------------------------------------------*/
///�������¼�
struct tagTingPai
{
	BYTE	byDo;		//0δ������10�ѽ������м�״̬Ϊ���ڷ���
	BYTE	byUser;		//�������λ��
	BYTE	byTing;		//�������λ��
	BYTE	byPs;		//���Ƴ�����ֵ
	BYTE	byNo;		//�¼��Ĵ���
	bool	bTing;		//�Ƿ�����
	bool	bHitTing[4];//��ҵ��������
	BYTE	byNext;		//��һ���¼��Ĵ���
	void Clear()
	{
		byDo	=255;//0δ������10�ѽ������м�״̬Ϊ���ڷ���
		byUser	=255;//�������λ��
		byTing	=255;//�������λ��
		byPs	=255;	//���Ƴ�����ֵ	
		bTing	=true;
		memset(bHitTing,0,sizeof(bHitTing));//��ҵ��������
		byNo = THING_TING_PAI;//�¼��Ĵ���
	}
};
/*----------------------------------------------------------------*/
///�������¼�
struct tagHuPai
{
	BYTE	byDo;				//0δ������10�ѽ������м�״̬Ϊ���ڷ���
	bool	bIsLiuJu;			//�Ƿ�����
	BYTE	byUser;				//�������λ��
	BYTE	byDianPao;			//�������λ��
	BYTE	byPs;				//���ڵ���ֵ

	bool    bQiangGang;			//�Ƿ�����
	bool    bZimo;				//�Ƿ�����
	bool	bGangKai;			//�Ƿ�ܿ�
	BYTE	byUserNum;			//������ҵĸ���


	BYTE	m_byArHandPai[PLAY_COUNT][HAND_CARD_NUM];//��������
	BYTE	m_byArHandPaiCount[PLAY_COUNT];	//��������
	BYTE	m_byArOutPai[PLAY_COUNT][OUT_CARD_NUM];//���Ʋ�����160�ţ�0Ϊ������־
	BYTE    byHuType[PLAY_COUNT][MAX_HUPAI_TYPE];//������ҵĺ�������
	bool	bHaveHu[PLAY_COUNT];	//��Ӧ������Ƿ������

	BYTE	byBaoPaiUser;		//�������
	
	void Clear()
	{
		byDo		= 255;//0δ������10�ѽ������м�״̬Ϊ���ڷ���
		byUser		= 255;//�������λ��
		byDianPao	= 255;//�������λ��
		byPs		= 255;	//���ڵ���ֵ
		bIsLiuJu	= true;	//�Ƿ�����

		byBaoPaiUser=255;		//�������
		memset(m_byArHandPai, 255, sizeof(m_byArHandPai));//��������	
		memset(m_byArHandPaiCount,0,sizeof(m_byArHandPaiCount));//��������
		memset(m_byArOutPai, 255, sizeof(m_byArOutPai));//��������
		memset(byHuType, 255, sizeof(byHuType));//������ҵĺ�������
		memset(bHaveHu,0,sizeof(bHaveHu));
		byUserNum = 0;		//������ҵĸ���
		bGangKai = false;	//�Ƿ�ܿ�
		bZimo = false;		//�Ƿ�����
		bQiangGang = false; //�Ƿ�����
	}
};
/*----------------------------------------------------------------*/
///����¼�
struct tagCountFen
{
	BYTE	byDo;		//0δ������10�ѽ������м�״̬Ϊ���ڷ���
	bool	bIsLiuJu;	//�Ƿ�����
	BYTE	byUser;		//�������λ��
	BYTE	byDianPao;	//�������λ��
	bool	bZiMo;		//�Ƿ�����
	bool	bGangKai;	//�Ƿ�ܿ�
	bool    bQiangGang;	//�Ƿ�����
	BYTE	byUserNum;	//������Ҹ���
	BYTE	byNt;		//ׯ��λ��
	BYTE	byHuUserNum;//������ҵĸ���

	BYTE	m_byArHandPai[PLAY_COUNT][HAND_CARD_NUM];//��������
	BYTE	m_byArHandPaiCount[PLAY_COUNT];	//��������
	
	__int64 		i64ZongFen[PLAY_COUNT];//������ҵ��ܷ�
	__int64 		i64Money[PLAY_COUNT];//������ҵ��ܷ�

	void Clear()
	{
		byDo		= 255;		//0δ������10�ѽ������м�״̬Ϊ���ڷ���
		byUser		= 255;		//�������λ��
		byDianPao	= 255;		//�������λ��
		byNt		= 255;		//ׯ��λ��
		bIsLiuJu	= true;		//�Ƿ�����
		bZiMo		= false;
		bGangKai	= false;	//�Ƿ�ܿ�
		bQiangGang	= false;
		byUserNum	= 0;		//������ҵĸ���

		memset(i64ZongFen,0,sizeof(i64ZongFen));
		memset(i64Money,0,sizeof(i64Money));
		memset(m_byArHandPai, 255, sizeof(m_byArHandPai));//��������	
		memset(m_byArHandPaiCount,0,sizeof(m_byArHandPaiCount));//��������		
	}
};




















///��2��ɫ�ӵĵ�����Ϊׯ�¼�
struct tagTwoSeziNt
{
	BYTE	byDo;//0δ������10�ѽ������м�״̬Ϊ���ڷ���
	BYTE	byUser;//��ɫ�����
	BYTE	byNt;//ׯ��λ��
	BYTE	bySezi0;//ɫ��0����
	BYTE	bySezi1;//ɫ��1����
	bool	bSeziFinish[4];//��¼�Ѿ�������ɫ�Ӷ��������
	BYTE	byNo;//�¼��Ĵ���
	BYTE	byNext;//��һ���¼��Ĵ���
	void Clear()
	{
		byDo	=255;//0δ������10�ѽ������м�״̬Ϊ���ڷ���
		byUser	=255;//��ɫ�����
		byNt	=255;//ׯ��λ��
		bySezi0	=255;//ɫ��0����
		bySezi1	=255;//ɫ��1����	
		memset(bSeziFinish,0,sizeof(bSeziFinish));
		byNo = THING_2SEZI_NT;//�¼��Ĵ���
	}
};

///��2��ɫ��ȷ��ׯ�Һ����Ƶ�λ���¼�
struct tagTwoSeziNtAndGetPai
{
	BYTE   byDo;	//0δ������10�ѽ������м�״̬Ϊ���ڷ���
	BYTE   byUser;	//��ɫ�����
	BYTE   byNt;	//ׯ��λ��
	BYTE   bySezi0;	//ɫ��0����
	BYTE   bySezi1;	//ɫ��1����
	BYTE   byGetPai;//����λ��
	bool   bSeziFinish[4];//��¼�Ѿ�������ɫ�Ӷ��������
	BYTE   byNo;//�¼��Ĵ���
	BYTE   byNext;//��һ���¼��Ĵ���
	void Clear()
	{
		byDo	=255;//0δ������10�ѽ������м�״̬Ϊ���ڷ���
		byUser	=255;//��ɫ�����
		byNt	=255;//ׯ��λ��
		bySezi0	=255;//ɫ��0����
		bySezi1	=255;//ɫ��1����
		byGetPai=255;//����λ��
		memset(bSeziFinish,0,sizeof(bSeziFinish));
		byNo = THING_2SEZI_NT_GP;//�¼��Ĵ���
	}
};

///������2��ɫ��ȷ��ׯ��
struct tagTurnSeziNt
{

	BYTE	byDo;//0δ������10�ѽ������м�״̬Ϊ���ڷ���
	BYTE	byNt;//ׯ��λ��
	BYTE	byUser;//��ǰ��ɫ�ӵ����
	BYTE	bySezi0;//ɫ��0����
	BYTE	bySezi1;//ɫ��1����
	BYTE	bySezi[4];//���0ɫ������
	BYTE	byMaxUser;//����������Ҹ���
	BYTE	byMaxDian;//������ֵ
	bool	bSeziFinish[4];//��¼�Ѿ�������ɫ�Ӷ��������
	bool	bDoFinish[4];//��¼�Ѿ�����ɫ�����
	bool	bDoSezi[4];//����Ҫ��ɫ�ӵ����
	bool	bFirst;//�Ƿ��һ����ɫ��
	BYTE	byNo;//�¼��Ĵ���
	BYTE	byNext;//��һ���¼��Ĵ���
	void Clear()
	{
		byDo	=255;//0δ������10�ѽ������м�״̬Ϊ���ڷ���
		byNt	=255;//ׯ��λ��
		byUser	=255;//��ǰ��ɫ�ӵ����
		bySezi0	=255;//ɫ��0����
		bySezi1	=255;//ɫ��1����
		memset(bySezi,255,sizeof(bySezi));//���0ɫ������
		byMaxUser	=255;//����������Ҹ���
		byMaxDian	=255;//������ֵ
		memset(bSeziFinish,0,sizeof(bSeziFinish));
		memset(bDoFinish,0,sizeof(bDoFinish));
		memset(bDoSezi,0,sizeof(bDoSezi));
		bFirst = true;//�Ƿ��һ����ɫ��
		byNo = THING_TURN_2SEZI_NT;//�¼��Ĵ���
	}
};

///��2��ɫ��ȷ�����ƶ����¼�
struct tagTwoSeziGetPai
{
	BYTE	byDo;//0δ������10�ѽ������м�״̬Ϊ���ڷ���
	BYTE	byUser;//��ɫ�����
	BYTE	bySezi0;//ɫ��0����
	BYTE	bySezi1;//ɫ��1����
	BYTE	byGetPai;//���Ƶ�
	bool	bSeziFinish[4];//��¼�Ѿ�������ɫ�Ӷ��������
	BYTE	byNo;	//�¼��Ĵ���
	BYTE	byNext;//��һ���¼��Ĵ���
	void Clear()
	{
		byDo	=255;		//0δ������10�ѽ������м�״̬Ϊ���ڷ���
		byUser	=255;	//��ɫ�����
		bySezi0	=255;	//ɫ��0����
		bySezi1	=255;	//ɫ��1����
		byGetPai	=255;	//���Ƶ�
		memset(bSeziFinish,0,sizeof(bSeziFinish));
		byNo = THING_2SEZI_GP;//�¼��Ĵ���
	}
};

///�����¼�
struct tagTiaoPai
{
	BYTE	byDo;//0δ������10�ѽ������м�״̬Ϊ���ڷ���
	BYTE	byUser;//�������λ��
	BYTE	byNt;//ׯ��λ��
	BYTE	byIndex0;//����λ��0
	BYTE	byIndex1;//����λ��1
	BYTE	byRemainPai;//ʣ������
	BYTE	bySendPai;//��������
	BYTE	byGetPai;//���Ƶ�
	BYTE	m_byArHandPai[4][HAND_CARD_NUM];//��������
	BYTE	byMenPai[4][MEN_CARD_NUM];//����
	BYTE	byNo;	//�¼��Ĵ���
	BYTE	byNext;//��һ���¼��Ĵ���
	void Clear()
	{
		byDo		=255;//0δ������10�ѽ������м�״̬Ϊ���ڷ���
		byUser		=255;//�������λ��
		byNt		=255;//ׯ��λ��
		byIndex0	=255;//����λ��0
		byIndex1	=255;//����λ��1
		byRemainPai	=255;//ʣ������
		bySendPai	=255;//��������
		byGetPai	=255;//���Ƶ�
		memset(m_byArHandPai, 255, sizeof(m_byArHandPai));//��������	
		memset(byMenPai, 255, sizeof(byMenPai));	//����
		byNo = THING_TIAO_PAI;//�¼��Ĵ���
	}
};
///��ɫ��2��ɫ�Ӷ������¼�
struct tagTwoSeziJing
{
	BYTE	byDo;//0δ������10�ѽ������м�״̬Ϊ���ڷ���
	BYTE	byUser;//��ɫ�����λ��
	BYTE	byNt;//ׯ��λ��
	BYTE	byFanPai;//���Ƶ�
	BYTE	bySezi0;//ɫ��0����
	BYTE	bySezi1;//ɫ��1����
	BYTE	byMainJing;//������ֵ
	BYTE	byLessJing;//��������ֵ
	BYTE	byStartIndex;///��ʼ����
	BYTE	byEndIndex;  ///��������
	BYTE	byCaiShenIndex; ///��������
	BYTE	byMenPai[4][MEN_CARD_NUM];//����
	bool	bSeziFinish[4];//��¼�Ѿ�������ɫ�Ӷ��������
	BYTE	byNo;	//�¼��Ĵ���
	BYTE	byNext;//��һ���¼��Ĵ���
	void Clear()
	{
		byDo		=255;//0δ������10�ѽ������м�״̬Ϊ���ڷ���
		byUser		=255;//��ɫ�����λ��
		byNt		=255;//ׯ��λ��
		byFanPai	=255;//���Ƶ�
		bySezi0		=255;//ɫ��0����
		bySezi1		=255;//ɫ��1����
		byMainJing	=255;//������ֵ
		byLessJing	=255;//��������ֵ
		byStartIndex	=255;///��ʼ����
		byEndIndex	=255;  ///��������
		byCaiShenIndex=255; ///��������
		memset(byMenPai, 255, sizeof(byMenPai));	//����
		memset(bSeziFinish,0,sizeof(bSeziFinish));
		byNo = THING_2SEZI_JING;//�¼��Ĵ���
	}
};
///��ɫ��1��ɫ�Ӷ������¼�
struct tagOneSeziJin
{
	BYTE	byDo;//0δ������10�ѽ������м�״̬Ϊ���ڷ���
	BYTE	byUser;//��ɫ�����λ��
	BYTE	byNt;//ׯ��λ��
	BYTE	byFanPai;//���Ƶ�
	BYTE	bySezi0;//ɫ��0����
	BYTE	byMainJing;//������ֵ
	BYTE	byLessJing;//��������ֵ
	BYTE	byStartIndex;///��ʼ����
	BYTE	byEndIndex;  ///��������
	BYTE	byCaiShenIndex; ///��������
	BYTE	byMenPai[4][MEN_CARD_NUM];//����
	bool	bSeziFinish[4];//��¼�Ѿ�������ɫ�Ӷ��������
	BYTE	byNo;	//�¼��Ĵ���
	BYTE	byNext;//��һ���¼��Ĵ���
	void Clear()
	{
		byDo		=255;//0δ������10�ѽ������м�״̬Ϊ���ڷ���
		byUser		=255;//��ɫ�����λ��
		byNt		=255;//ׯ��λ��
		byFanPai	=255;//���Ƶ�
		bySezi0		=255;//ɫ��0����
		byMainJing	=255;//������ֵ
		byLessJing	=255;//��������ֵ
		byStartIndex	=255;///��ʼ����
		byEndIndex	=255;  ///��������
		byCaiShenIndex=255; ///��������
		memset(byMenPai, 255, sizeof(byMenPai));	//����
		memset(bSeziFinish,0,sizeof(bSeziFinish));
		byNo = THING_1SEZI_JIN;//�¼��Ĵ���
	}
};




///�����¼�
struct tagKanPai
{
	BYTE	byDo;//0δ������10�ѽ������м�״̬Ϊ���ڷ���
	BYTE	byUser;//�������λ��
	BYTE	byPs;	//������ֵ
	BYTE	m_byArHandPai[4][HAND_CARD_NUM];//��������
	BYTE	byNo;	//�¼��Ĵ���
	BYTE	byNext;//��һ���¼��Ĵ���
	void Clear()
	{
		byDo	=255;//0δ������10�ѽ������м�״̬Ϊ���ڷ���
		byUser	=255;//�������λ��
		byPs		=255;//������ֵ
		memset(m_byArHandPai, 255, sizeof(m_byArHandPai));//��������	
		byNo = THING_KAN_PAI;//�¼��Ĵ���
	}
};
///ɨ���¼����黢�齫ר�ã�
struct tagSaoHu
{
	BYTE	byDo;		//0δ������10�ѽ������м�״̬Ϊ���ڷ���
	BYTE	byUser;		//���λ��
	BYTE	byPs;		//������ֵ
	bool	bSaohu[4];	//ɨ�������
	bool	bHitSaohu[4];	//�յ����ɨ��
	BYTE    byOutData[4];//����ɨ����ҳ�����
	BYTE    byHandData[4];//����ɨ������������е���
	BYTE    byBaoPai;	//�������λ��
	BYTE	byNo;		//�¼��Ĵ���
	BYTE	byNext;		//��һ���¼��Ĵ���
	void Clear()
	{
		byDo	=255;//0δ������10�ѽ������м�״̬Ϊ���ڷ���
		byUser	=255;//�������λ��
		byPs	=255;//������ֵ
		byBaoPai=255;	//�������λ��
		memset(bSaohu, 0, sizeof(bSaohu));//	
		memset(bHitSaohu, 0, sizeof(bHitSaohu));//	
		memset(byOutData, 255, sizeof(byOutData));//	
		memset(byHandData, 255, sizeof(byHandData));//	
		byNo = THING_SAO_HU;//�¼��Ĵ���
	}
};
///��Ϸ���������¼�
struct tagEndHandle
{
	BYTE	byDo;//0δ������10�ѽ������м�״̬Ϊ���ڷ���
	BYTE	byUser;//�������λ��
	BYTE	byHu;//�������λ��
	BYTE	byNextNt;//�¾�ׯ��λ��
	BYTE	byPs;	//���ڵ���ֵ
	bool	bDH;//һ�ڶ���
	BYTE	byNo;	//�¼��Ĵ���
	BYTE	byNext;//��һ���¼��Ĵ���
	tagEndHandle()
	{
		Clear();
	}
	void Clear()
	{		
		byDo	=255;//0δ������10�ѽ������м�״̬Ϊ���ڷ���
		byUser	=255;//�������λ��
		byHu	=255;//�������λ��
		byNextNt=255;//�¾�ׯ��λ��
		byPs		=255;	//���ڵ���ֵ
		bDH = 0;	
		byNo = THING_ENG_HANDLE;//�¼��Ĵ���
	}
};
///���������������¼�
struct tagUnnormalEndHandle
{
	BYTE	byDo;//0δ������10�ѽ������м�״̬Ϊ���ڷ���
	BYTE	byUser;//�������λ��
	int		iFen[8];//�÷�
	int		iMoney[8];//���
	bool    bForce;//�Ƿ�ǿ�˽���
	BYTE	byNo;	//�¼��Ĵ���
	BYTE	byNext;//��һ���¼��Ĵ���
	tagUnnormalEndHandle()
	{
		Clear();
	}
	void Clear()
	{		
		byDo	=255;//0δ������10�ѽ������м�״̬Ϊ���ڷ���
		byUser	=255;//�������λ��
		memset(iFen, 0, sizeof(iFen));
		memset(iMoney, 0, sizeof(iMoney));
		bForce = false;//�Ƿ�ȫ����
		byNo = THING_ENG_UN_NORMAL;//�¼��Ĵ���
	}
};
///////////////////////////////////////////////////
#pragma pack()

#endif
