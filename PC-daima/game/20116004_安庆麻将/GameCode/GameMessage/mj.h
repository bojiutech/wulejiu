/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #pragma once

#define MAKE_A_MJ(hs,pd)  ( (hs) * 10 +(pd))
///lym2010-05-07���¶����齫ֵ
///�֣�11-13
///�磺14-17
///����21-29
///ͬ��31-39
///��41-49
///���ƣ�51-58 ���߸���

class CMjEnum
{
	
public:
			
	enum MJ_TYPE_HUA_SE
	{
			MJ_TYPE_HUA_SE_NONE=-10,//lu�޻�ɫ
			MJ_TYPE_HUA_SE_BIN=3,//luͬ
			MJ_TYPE_HUA_SE_WAN=4,//lu��
			MJ_TYPE_HUA_SE_TIAO=2,//lu��
			MJ_TYPE_HUA_SE_FENG=1//lu��
	};

	enum MJ_TYPE_PAI//������
	{
		MJ_TYPE_PAI_NONE=-10,//lu�޻�ɫ
		MJ_TYPE_PAI_WAN=0,//lu��
		MJ_TYPE_PAI_TIAO=1,//lu��
		MJ_TYPE_PAI_BING=2,//luͬ
		MJ_TYPE_PAI_FENG=3,//lu��
		MJ_TYPE_PAI_HUA=4//lu��
	};

	enum MJ_TYPE_PAI_DIAN//lu�Ƶ�
	{
			MJ_TYPE_PAI_DIAN_NONE=-1,

			MJ_TYPE_PAI_DIAN_1 = 1,
			MJ_TYPE_PAI_DIAN_2 = 2,
			MJ_TYPE_PAI_DIAN_3 = 3,
			MJ_TYPE_PAI_DIAN_4 = 4,
			MJ_TYPE_PAI_DIAN_5 = 5,
			MJ_TYPE_PAI_DIAN_6 = 6,
			MJ_TYPE_PAI_DIAN_7 = 7,
			MJ_TYPE_PAI_DIAN_8 = 8,
			MJ_TYPE_PAI_DIAN_9 = 9
			
	};


	enum MJ_TYPE
	{
				MJ_TYPE_NONE=0,

				MJ_TYPE_FCHUN=MAKE_A_MJ(MJ_TYPE_PAI_FENG,11),
				MJ_TYPE_FXIA=MAKE_A_MJ(MJ_TYPE_PAI_FENG,12),
				MJ_TYPE_FQIU=MAKE_A_MJ(MJ_TYPE_PAI_FENG,13),
				MJ_TYPE_FDONG=MAKE_A_MJ(MJ_TYPE_PAI_FENG,14),
				MJ_TYPE_FMEI=MAKE_A_MJ(MJ_TYPE_PAI_FENG,15),
				MJ_TYPE_FLAN=MAKE_A_MJ(MJ_TYPE_PAI_FENG,16),
				MJ_TYPE_FZHU=MAKE_A_MJ(MJ_TYPE_PAI_FENG,17),
				MJ_TYPE_FJU=MAKE_A_MJ(MJ_TYPE_PAI_FENG,18),
				

				MJ_TYPE_CAISHEN=MAKE_A_MJ(MJ_TYPE_PAI_FENG,19),
				MJ_TYPE_YUANBAO=MAKE_A_MJ(MJ_TYPE_PAI_FENG,20),
				MJ_TYPE_MAO=MAKE_A_MJ(MJ_TYPE_PAI_FENG,21),
				MJ_TYPE_LAOXU=MAKE_A_MJ(MJ_TYPE_PAI_FENG,22),



				MJ_TYPE_FD=MAKE_A_MJ(MJ_TYPE_PAI_FENG,MJ_TYPE_PAI_DIAN_1),///��
				MJ_TYPE_FN=MAKE_A_MJ(MJ_TYPE_PAI_FENG,MJ_TYPE_PAI_DIAN_2),///��
				MJ_TYPE_FX=MAKE_A_MJ(MJ_TYPE_PAI_FENG,MJ_TYPE_PAI_DIAN_3),///��
				MJ_TYPE_FB=MAKE_A_MJ(MJ_TYPE_PAI_FENG,MJ_TYPE_PAI_DIAN_4),///��
				MJ_TYPE_ZHONG=MAKE_A_MJ(MJ_TYPE_PAI_FENG,MJ_TYPE_PAI_DIAN_5),///����
				MJ_TYPE_FA=MAKE_A_MJ(MJ_TYPE_PAI_FENG,MJ_TYPE_PAI_DIAN_6),///����
				MJ_TYPE_BAI=MAKE_A_MJ(MJ_TYPE_PAI_FENG,MJ_TYPE_PAI_DIAN_7),///�װ�


				MJ_TYPE_W1=MAKE_A_MJ(MJ_TYPE_PAI_WAN,MJ_TYPE_PAI_DIAN_1),///��
				MJ_TYPE_W2=MAKE_A_MJ(MJ_TYPE_PAI_WAN,MJ_TYPE_PAI_DIAN_2),
				MJ_TYPE_W3=MAKE_A_MJ(MJ_TYPE_PAI_WAN,MJ_TYPE_PAI_DIAN_3),
				MJ_TYPE_W4=MAKE_A_MJ(MJ_TYPE_PAI_WAN,MJ_TYPE_PAI_DIAN_4),
				MJ_TYPE_W5=MAKE_A_MJ(MJ_TYPE_PAI_WAN,MJ_TYPE_PAI_DIAN_5),
				MJ_TYPE_W6=MAKE_A_MJ(MJ_TYPE_PAI_WAN,MJ_TYPE_PAI_DIAN_6),
				MJ_TYPE_W7=MAKE_A_MJ(MJ_TYPE_PAI_WAN,MJ_TYPE_PAI_DIAN_7),
				MJ_TYPE_W8=MAKE_A_MJ(MJ_TYPE_PAI_WAN,MJ_TYPE_PAI_DIAN_8),
				MJ_TYPE_W9=MAKE_A_MJ(MJ_TYPE_PAI_WAN,MJ_TYPE_PAI_DIAN_9),

				MJ_TYPE_T1=MAKE_A_MJ(MJ_TYPE_PAI_TIAO,MJ_TYPE_PAI_DIAN_1),///��
				MJ_TYPE_T2=MAKE_A_MJ(MJ_TYPE_PAI_TIAO,MJ_TYPE_PAI_DIAN_2),
				MJ_TYPE_T3=MAKE_A_MJ(MJ_TYPE_PAI_TIAO,MJ_TYPE_PAI_DIAN_3),
				MJ_TYPE_T4=MAKE_A_MJ(MJ_TYPE_PAI_TIAO,MJ_TYPE_PAI_DIAN_4),
				MJ_TYPE_T5=MAKE_A_MJ(MJ_TYPE_PAI_TIAO,MJ_TYPE_PAI_DIAN_5),
				MJ_TYPE_T6=MAKE_A_MJ(MJ_TYPE_PAI_TIAO,MJ_TYPE_PAI_DIAN_6),
				MJ_TYPE_T7=MAKE_A_MJ(MJ_TYPE_PAI_TIAO,MJ_TYPE_PAI_DIAN_7),
				MJ_TYPE_T8=MAKE_A_MJ(MJ_TYPE_PAI_TIAO,MJ_TYPE_PAI_DIAN_8),
				MJ_TYPE_T9=MAKE_A_MJ(MJ_TYPE_PAI_TIAO,MJ_TYPE_PAI_DIAN_9),

				MJ_TYPE_B1=MAKE_A_MJ(MJ_TYPE_PAI_BING,MJ_TYPE_PAI_DIAN_1),///ͬ
				MJ_TYPE_B2=MAKE_A_MJ(MJ_TYPE_PAI_BING,MJ_TYPE_PAI_DIAN_2),
				MJ_TYPE_B3=MAKE_A_MJ(MJ_TYPE_PAI_BING,MJ_TYPE_PAI_DIAN_3),
				MJ_TYPE_B4=MAKE_A_MJ(MJ_TYPE_PAI_BING,MJ_TYPE_PAI_DIAN_4),
				MJ_TYPE_B5=MAKE_A_MJ(MJ_TYPE_PAI_BING,MJ_TYPE_PAI_DIAN_5),
				MJ_TYPE_B6=MAKE_A_MJ(MJ_TYPE_PAI_BING,MJ_TYPE_PAI_DIAN_6),
				MJ_TYPE_B7=MAKE_A_MJ(MJ_TYPE_PAI_BING,MJ_TYPE_PAI_DIAN_7),
				MJ_TYPE_B8=MAKE_A_MJ(MJ_TYPE_PAI_BING,MJ_TYPE_PAI_DIAN_8),
				MJ_TYPE_B9=MAKE_A_MJ(MJ_TYPE_PAI_BING,MJ_TYPE_PAI_DIAN_9)



		
	};

};


#define MAX_MJ_PAI   (CMjEnum::MJ_TYPE_B9)




class CMjRef
{
	public:
		//
		static int MakeACard(int hs,int pd) { return  MAKE_A_MJ(hs,pd); }
   public:

	   int m_iPs;
	   static bool IsValidateMj(BYTE iCard)
	   {
			return iCard >= CMjEnum::MJ_TYPE_FCHUN && iCard <= CMjEnum::MJ_TYPE_LAOXU ||  
				iCard >= CMjEnum::MJ_TYPE_FD && iCard <= CMjEnum::MJ_TYPE_BAI ||
				iCard >= CMjEnum::MJ_TYPE_B1 && iCard <= CMjEnum::MJ_TYPE_B9  ||
				iCard >= CMjEnum::MJ_TYPE_W1 && iCard <= CMjEnum::MJ_TYPE_W9  ||
				iCard >= CMjEnum::MJ_TYPE_T1 && iCard <= CMjEnum::MJ_TYPE_T9 
				;
	   }
	   //��ȡ�ƵĻ�ɫ
	   static BYTE GetHuaSe(BYTE byCard)
	   {
		   return (byCard) / 10;
	   }
	   //��ȡ�Ƶ��Ƶ�
	   static BYTE GetCardPaiDian(BYTE byCard) 
	   { 
		   return (byCard) % 10 ;
	   }

	   //���2�����Ƿ�ͬһ��ɫ
	   static bool CheckIsTongSe(BYTE Card1,BYTE Card2)
	   { 
		   return (Card1/10==Card2/10);
	   }
	   //���2�����Ƿ�һ����
	   static  bool CheckIsYiXiangLian(BYTE Card1,BYTE Card2,bool big=false)
	   { 
			if(!CheckIsTongSe(Card1,Card2))
				return false;
			if(!big)
				return (Card1==Card2+1);
			return (Card1==Card2-1);
	   }
	   //���2�����Ƿ������
	   static  bool CheckIsErXiangLian(BYTE Card1,BYTE Card2,bool big=false)
	   { 
			if(!CheckIsTongSe(Card1,Card2))
				return false;
			if(!big)
				return (Card1==Card2+1 || Card1==Card2+2 );
			return (Card1==Card2-1 || Card1==Card2-2 );
	   }

		static BYTE ExDToB(BYTE byMJ)//�߼�����ת���ɿؼ�����
		{
			if (byMJ == 0)
			{
				return 34;
			}
			else if(byMJ <= 9)	//����ת��
			{
				return (byMJ - 1);
			}
			else if(byMJ <= 19)	//��ͬ��ת��
			{
				return (byMJ + 7);
			}
			else if(byMJ <= 29)	//������ת��
			{
				return (byMJ - 12);
			}
			else if(byMJ <= 37)	//���ơ����з��ס�ת��
			{
				if(byMJ == 31)//��
				{
					return 27;
				}
				else if(byMJ == 32)//��
				{
					return 29;
				}
				else if(byMJ == 33)//��
				{
					return 28;
				}
				else if(byMJ == 34)//��
				{
					return 30;
				}
				else 
				{
					return byMJ - 4;
				}
			}
			else if(byMJ <= 48)	//�������ﶬ÷����ա�ת��
			{
				return (byMJ - 5);
			}
			return 255;
		}

		static BYTE ExBToD(BYTE byMJ)//�ؼ�����ת�����߼�����
		{
			if (byMJ < 0)
			{
				return byMJ;
			}
			else if(byMJ <= 8)	//����ת��
			{
				return (byMJ + 1);
			}
			else if(byMJ <= 17)	//������ת��
			{
				return (byMJ + 12);
			}
			else if(byMJ <= 26)	//��ͬ��ת��
			{
				return (byMJ - 7);
			}
			else if(byMJ <= 33)	//���ơ����з��ס�ת��
			{
				if(byMJ == 27)//��
				{
					return 31;					
				}
				else if(byMJ == 29)//��
				{
					return 32;					
				}
				else if(byMJ == 28)//��
				{
					return 33;					
				}
				else if(byMJ == 30)//��
				{
					return 34;
				}
				else 
				{
					return (byMJ + 4);
				}
			}
			else if(byMJ == 34) //�����뱳��
			{
				return 0;
			}
			else if(byMJ <= 43)	//�������ﶬ÷����ա�ת��
			{
				return (byMJ + 5);
			}

			return 255;
		}

		static bool ExDToB(BYTE* byT,const BYTE* byS,int nMJSize)//�߼��齫ת���ɿؼ��齫���ݣ�����ת����
		{
			if (!byT || !byS)
				return false;

			for (int i = 0; i < nMJSize; i++)
			{
				byT[i] = CMjRef::ExDToB(byS[i]);
			}

			return true;
		}

		///���ͼ��

		///���������һ�ֺ�������
		///@param   type Ҫ��ӵ����� , hupai[] ������������
		static void SetAHupaiType(BYTE type,BYTE hupai[],BYTE maxtype)
		{
			if(CheckHupaiType(type,hupai,maxtype))//���˾Ͳ������
				return;
			for(int i=0;i<maxtype;i++)
			{
				if(hupai[i] == 255)
				{
					hupai[i] = type;
					break;
				}
			}
		}

		///����������һ�ֺ�������
		///@param type Ҫɾ�������� , hupai[] ������������
		static void ReSetAHupaiType(BYTE type,BYTE hupai[],BYTE maxtype)
		{
			int index = 0;
			for(int i=0;i<maxtype;i++)
			{
				if(hupai[i] == type)
				{
					hupai[i] = 255;
					break;
				}
			}
			//ȥ���м���ЧԪ��
			BYTE temp[255];
			memset(temp,255,sizeof(temp));
			for(int i=0;i<maxtype;i++)
			{
				if(hupai[i] != 255)
				{
					temp[index] = hupai[i];
					index++;
				}
			}
			for(int i=0;i<maxtype;i++)
			{
				hupai[i] = temp[i];
			}
		}

		///������������к�������
		///@param type Ҫɾ�������� , hupai[] ������������
		static void ClearHupaiType(BYTE hupai[],BYTE maxtype)
		{
			for(int i=0;i<maxtype;i++)
			{
				hupai[i] = 255;
			}
		}

		///����������Ƿ����ĳ�ֺ�������
		///@param type Ҫ�������� , hupai[] ������������
		static bool CheckHupaiType(BYTE type,BYTE hupai[],BYTE maxtype)
		{
			int index = 0;
			for(int i=0;i<maxtype;i++)
			{
				if(hupai[i] == type && type!=255)
				{
					return true;
				}
			}
			return false;
		}


	   CMjRef(int card = 0){m_iPs =card;}
	   virtual ~CMjRef(){m_iPs =0;}
	   
};


#define MJ_H   36
#define MJ_W   24


#define	A_FU_MJ_JINZHOU_NUM	28			//�����齫��һ���齫(27+����)
#define A_FU_MJ_NUM  34
#define A_FU_MJ_OTHER  8

static int stcArr_A_Direction[] = 
{
	CMjEnum::MJ_TYPE_FD,
	CMjEnum::MJ_TYPE_FN,
	CMjEnum::MJ_TYPE_FX,
	CMjEnum::MJ_TYPE_FB
};

static int stcArr_A_Mj[]=
{
	        CMjEnum::MJ_TYPE_W1,
			CMjEnum::MJ_TYPE_W2,
			CMjEnum::MJ_TYPE_W3,
			CMjEnum::MJ_TYPE_W4,
			CMjEnum::MJ_TYPE_W5,
			CMjEnum::MJ_TYPE_W6,
			CMjEnum::MJ_TYPE_W7,
			CMjEnum::MJ_TYPE_W8,
			CMjEnum::MJ_TYPE_W9,
	        
			CMjEnum::MJ_TYPE_B1 ,
			CMjEnum::MJ_TYPE_B2 ,
			CMjEnum::MJ_TYPE_B3 ,
			CMjEnum::MJ_TYPE_B4,
			CMjEnum::MJ_TYPE_B5,
			CMjEnum::MJ_TYPE_B6,
			CMjEnum::MJ_TYPE_B7,
			CMjEnum::MJ_TYPE_B8,
			CMjEnum::MJ_TYPE_B9,


			CMjEnum::MJ_TYPE_T1,
			CMjEnum::MJ_TYPE_T2,
			CMjEnum::MJ_TYPE_T3,
			CMjEnum::MJ_TYPE_T4,
			CMjEnum::MJ_TYPE_T5,
			CMjEnum::MJ_TYPE_T6,
			CMjEnum::MJ_TYPE_T7,
			CMjEnum::MJ_TYPE_T8,
			CMjEnum::MJ_TYPE_T9,

			CMjEnum::MJ_TYPE_FD,
			CMjEnum::MJ_TYPE_FN  ,
			CMjEnum::MJ_TYPE_FX ,
			CMjEnum::MJ_TYPE_FB ,
			CMjEnum::MJ_TYPE_ZHONG,	
			CMjEnum::MJ_TYPE_FA ,
			CMjEnum::MJ_TYPE_BAI
	
};
//�齫����
static int stcArr_A_Mj_W[]=
{
	CMjEnum::MJ_TYPE_W1,
	CMjEnum::MJ_TYPE_W2,
	CMjEnum::MJ_TYPE_W3,
	CMjEnum::MJ_TYPE_W4,
	CMjEnum::MJ_TYPE_W5,
	CMjEnum::MJ_TYPE_W6,
	CMjEnum::MJ_TYPE_W7,
	CMjEnum::MJ_TYPE_W8,
	CMjEnum::MJ_TYPE_W9
};
//�齫��Ͳ
static int stcArr_A_Mj_B[]=
{
	CMjEnum::MJ_TYPE_B1 ,
	CMjEnum::MJ_TYPE_B2 ,
	CMjEnum::MJ_TYPE_B3 ,
	CMjEnum::MJ_TYPE_B4,
	CMjEnum::MJ_TYPE_B5,
	CMjEnum::MJ_TYPE_B6,
	CMjEnum::MJ_TYPE_B7,
	CMjEnum::MJ_TYPE_B8,
	CMjEnum::MJ_TYPE_B9
};
//�齫����
static int stcArr_A_Mj_T[]=
{
	CMjEnum::MJ_TYPE_T1,
	CMjEnum::MJ_TYPE_T2,
	CMjEnum::MJ_TYPE_T3,
	CMjEnum::MJ_TYPE_T4,
	CMjEnum::MJ_TYPE_T5,
	CMjEnum::MJ_TYPE_T6,
	CMjEnum::MJ_TYPE_T7,
	CMjEnum::MJ_TYPE_T8,
	CMjEnum::MJ_TYPE_T9
};
//�齫�ķ���
static	int	stcArr_A_Mj_FENG[]=
{
			CMjEnum::MJ_TYPE_FD,
			CMjEnum::MJ_TYPE_FN,
			CMjEnum::MJ_TYPE_FX,
			CMjEnum::MJ_TYPE_FB 

};
//�齫������
static	int	stcArr_A_Mj_ZI[]=
{
			CMjEnum::MJ_TYPE_ZHONG,	//����
			CMjEnum::MJ_TYPE_FA,	//����
			CMjEnum::MJ_TYPE_BAI	//�װ�

};
////���ϴ����ﶬ÷�����
static int stcArr_A_Mj_Other[]=
{
	       CMjEnum::MJ_TYPE_FCHUN,
		   CMjEnum::MJ_TYPE_FXIA,
		   CMjEnum::MJ_TYPE_FQIU,
		   CMjEnum::MJ_TYPE_FDONG,

		   CMjEnum::MJ_TYPE_FMEI,
		   CMjEnum::MJ_TYPE_FLAN,
		   CMjEnum::MJ_TYPE_FZHU,
		   CMjEnum::MJ_TYPE_FJU
};

static int GetGangHua(int caishen)
{
	int ii=-1;
	for(int i=0;i<A_FU_MJ_NUM;i++)
	{
		if(caishen == stcArr_A_Mj[i])
		{
			ii=i;
			break;
		}
	}
	if(ii < 0)return -1;

	int is=ii+1;
	if(is == A_FU_MJ_NUM)is=is-7;
	else 
	{
		if( is % 9 == 0)is=is-9;
	}
	return stcArr_A_Mj[is];
}

static int stc_GangHuaArr[]={
	            CMjEnum::  MJ_TYPE_FCHUN,
			    CMjEnum::  MJ_TYPE_FXIA,
				CMjEnum::	MJ_TYPE_FQIU,
				CMjEnum::	MJ_TYPE_FDONG,
				CMjEnum::	MJ_TYPE_FMEI,
				CMjEnum::	MJ_TYPE_FLAN,
				CMjEnum::	MJ_TYPE_FZHU,
				CMjEnum::	MJ_TYPE_FJU,
				CMjEnum::	MJ_TYPE_CAISHEN,
				CMjEnum::	MJ_TYPE_YUANBAO,
				CMjEnum::	MJ_TYPE_MAO,
				CMjEnum::	MJ_TYPE_LAOXU
	                };


typedef  int ARRUSERMJ[20];








