/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #include "stdafx.h"
#include "CheckHuPai.h"
#include "../server/ServerManage.h"


CheckHuPai::CheckHuPai(void)
{
	m_iMaxFan = -1;		
	m_byStation = 0;///��ǰ�����ҵ�λ��
	hupaistruct.Init();
	HuTempData.Init();	//���Ƽ����ʱ����
	NoJingHuTempData.Init();///���Ƽ����ʱ����(�޲���)	
	m_byJingNum = 0;  //��������
	//�����������ڵ���
	m_byLastPai = 255;
	m_bZimo = false;///����Ƿ���������
}

CheckHuPai::~CheckHuPai(void)
{

}
/*------------------------------------------------------------------------------*/
//���������ָ��
void CheckHuPai::SetDeskPoint(CServerGameDesk *desk)
{
	pDesk = desk;
}
/*------------------------------------------------------------------------------*/
///���ƣ�ChangeHandPaiData
///������ת���������ݵĴ洢��ʽ��Ϊ�˷�����Ƽ��
///@param handpai[] ��������, pai ���˴������
///@return 
void CheckHuPai::ChangeHandPaiData(BYTE handpai[],BYTE pai)
{			
	HuTempData.Init();
	NoJingHuTempData.Init();///���Ƽ����ʱ����(�޲���)	
	m_byJingNum = 0;
	for(int i=0;i<HAND_CARD_NUM;i++)
	{
		if(handpai[i] != 255 )
		{
			if(!pDesk->sUserData.m_StrJing.CheckIsJing(handpai[i]))//������
			{
				NoJingHuTempData.Add(handpai[i]);
			}
			else
			{
				m_byJingNum++;
			}
			HuTempData.Add(handpai[i]);
		}
	}
	if(pai!= 255)
	{
		if(!pDesk->sUserData.m_StrJing.CheckIsJing(pai))//������
		{
			NoJingHuTempData.Add(pai);
		}
		else
		{
			m_byJingNum++;
		}
		HuTempData.Add(pai);
	}
}

///���ƣ�AddAPaiToArr
///���������һ���Ƶ���ʱ������
///@param pai Ҫ�ӵ���
///@return 
void CheckHuPai::AddAPaiToArr(BYTE pai)
{	
	for(int i=0;i<HAND_CARD_NUM;i++)
	{
		if(HuTempData.data[i][0] == 255)
		{
			HuTempData.data[i][0] = pai;
			HuTempData.data[i][1] = 1;
			HuTempData.conut++;
			break;
		}
		else if(HuTempData.data[i][0] == pai)
		{
			HuTempData.data[i][1]++;
			break;
		}
	}
}

///���ƣ�SetJingPai
///���������þ��ƣ���������ֵ�����Ӿ�������
///@param 
///@return 
void CheckHuPai::SetJingPai()
{
}

///���ƣ�ReSetJingPai
///�������ָ����ƣ������ƻָ�����ʱ������
///@param 
///@return 
void CheckHuPai::ReSetJingPai()
{
}

///���ƣ�CanTing
///����������ܷ�����
///@param  handpai[] ��������, pai ���һ����, gcpData[] ����������, MainJing ����, LessJing ����, CanOut[] ����������Ƶ��ƣ������ж��ţ�
///@return true ������false ������
bool CheckHuPai::CanTing(BYTE station,BYTE CanOut[])
{
	if(!pDesk->sGameData.m_mjAction.bTing)//��������
	{
		return false;
	}
	m_byStation = station;
	///����Ƿ���������
	m_bZimo = true;

	memset(m_byArHandPai,255,sizeof(m_byArHandPai));
	memset(CanOut,255,sizeof(CanOut));
	int num=0;

	for(int i=0;i<HAND_CARD_NUM;i++)
	{
		m_byArHandPai[i] = pDesk->sUserData.m_byArHandPai[station][i];
	}
	CString str="";
	for(int i=0;i<HAND_CARD_NUM;i++)
	{
		if(m_byArHandPai[i] == 255)
			break;
		BYTE pai =255;
		pai = m_byArHandPai[i];
		m_byArHandPai[i] = 255;
		//��С��������
		MaoPaoSort(m_byArHandPai,HAND_CARD_NUM,false);
		///������ת��
		ChangeHandPaiData(m_byArHandPai,255);

		str.Format("new:ƽ����⣺����  pai=%d %d %d %d %d %d %d %d %d %d %d %d  %d %d",m_byArHandPai[0],m_byArHandPai[1],m_byArHandPai[2],m_byArHandPai[3],m_byArHandPai[4],m_byArHandPai[5],m_byArHandPai[6],m_byArHandPai[7],m_byArHandPai[8],m_byArHandPai[9],m_byArHandPai[10],m_byArHandPai[11],m_byArHandPai[12],m_byArHandPai[13]);
		OutputDebugString(str);

		if(CheckPingHu(255,true,false,true))
		{
			CanOut[num] = pai;
			num++;
		}
		m_byArHandPai[HAND_CARD_NUM-1] = pai;

	}
	if(num>0)
		return true;

	return false;
}
///���ƣ�ChiTing
///����ܷ�����ƣ��Ժ�����
///@param  station ����λ��, CanOut[] ����������Ƶ��ƣ�ÿ�ų���ֻ����һ�ţ���paip[][3] �ܳԵ������
///@return true ������false ������
bool CheckHuPai::ChiTing(BYTE station,BYTE CanOut[],BYTE pai[][3])
{
	m_byStation = station;

	memset(CanOut,255,sizeof(CanOut));

	int num=0,num1=0;
	for(int i=0;i<3;i++)
	{
		if(pai[i][0] != 255)
		{
			num++;
		}
	}

	for(int i=0;i<num;i++)
	{
		memset(m_byArHandPai,255,sizeof(m_byArHandPai));
		for(int j=0;j<HAND_CARD_NUM;j++)
		{
			m_byArHandPai[j] = pDesk->sUserData.m_byArHandPai[station][j];
		}
		///ɾ������

		///��С��������
		MaoPaoSort(m_byArHandPai,HAND_CARD_NUM,false);

		for(int i=0;i<HAND_CARD_NUM;i++)
		{
			if(m_byArHandPai[i] == 255 || CanOut[num]!=255)
				continue;
			BYTE pai =255;
			pai = m_byArHandPai[i];
			m_byArHandPai[i] = 255;
			//��С��������
			MaoPaoSort(m_byArHandPai,HAND_CARD_NUM,false);
			///������ת��
			ChangeHandPaiData(m_byArHandPai,255);

			if(CheckPingHu(255,true,false,true))
			{
				CanOut[num] = pai;
				num1++;
			}
			m_byArHandPai[HAND_CARD_NUM-1] = pai;
		}
	}
	if(num1>0)
		return true;
	return false;
}
///���ƣ�GangTing
///���ܺ��ܷ񱣴�����״̬
///@param  station ����λ��, CanTing[] ��Ӧ����ϸܺ��ܷ񱣴�����paip[][4] ���Ƶ����
///@return true ������false ������
bool CheckHuPai::GangTing(BYTE station,tagCPGNotifyEx &cpg ,BYTE ps,bool CanTing[])
{
	m_byStation = station;

	memset(m_byArHandPai,255,sizeof(m_byArHandPai));
	memset(CanTing,0,sizeof(CanTing));
	int num=0,num1=0;
	for(int i=0;i<4;i++)
	{
		if(cpg.m_iGangData[i][1] != 255)
			num++;
	}
	for(int i=0;i<num;i++)
	{
		memset(m_byArHandPai,255,sizeof(m_byArHandPai));
		for(int j=0;j<HAND_CARD_NUM;j++)
		{
			m_byArHandPai[j] = pDesk->sUserData.m_byArHandPai[station][j];
		}
		///ɾ������

		///��С��������
		MaoPaoSort(m_byArHandPai,HAND_CARD_NUM,false);

		for(int i=0;i<HAND_CARD_NUM;i++)
		{
			if(m_byArHandPai[i] == 255 || CanTing[num])
				continue;
			BYTE pai =255;
			pai = m_byArHandPai[i];
			m_byArHandPai[i] = 255;
			//��С��������
			MaoPaoSort(m_byArHandPai,HAND_CARD_NUM,false);
			///������ת��
			ChangeHandPaiData(m_byArHandPai,255);

			if(CheckPingHu(255,true,false,true))
			{
				CanTing[num1] = true;
				num1++;
			}
			m_byArHandPai[HAND_CARD_NUM-1] = pai;
		}
	}
	if(num1>0)
		return true;

	return false;
}
///���ƣ�CanHu
///������ֻ����ܷ����
///@param station ���λ�� ��zimo �Ƿ�����
///@return true  �ܺ��� false ����
bool CheckHuPai::CanHu(BYTE station,BYTE lastpai,bool zimo)
{


	//�����������ڵ���
	m_byLastPai = lastpai;
	m_byStation = station;

	memset(m_byArHandPai,255,sizeof(m_byArHandPai));
	for(int i=0;i<HAND_CARD_NUM;i++)
	{
		m_byArHandPai[i] = pDesk->sUserData.m_byArHandPai[station][i];
		if(pDesk->sUserData.m_byArHandPai[station][i] == 255 && lastpai != 255 && !zimo)
		{
			m_byArHandPai[i] = lastpai;
			break;
		}
	}
	///��С��������
	MaoPaoSort(m_byArHandPai,HAND_CARD_NUM,false);
	///������ת��
	ChangeHandPaiData(m_byArHandPai,255);	

	return CheckPingHu(lastpai,zimo,pDesk->sGameData.m_mjRule.bHaveJing);
}

///���ƣ�CanHu
///��������ϸ������
///@param station ���Ƽ��λ�ã�hutype[] �ܺ��Ƶ����ͣ�zimo �Ƿ�����
///@return true  �ܺ��� false ����
bool CheckHuPai::CanHu(BYTE station,BYTE lastpai,BYTE hutype[],bool zimo)
{
	//return false;

	//�����������ڵ���
	m_byLastPai = lastpai;
	m_byStation = station;
	CString str="";

	memset(m_byArHandPai,255,sizeof(m_byArHandPai));
	for(int i=0;i<HAND_CARD_NUM;i++)
	{
		m_byArHandPai[i] = pDesk->sUserData.m_byArHandPai[station][i];
		if(pDesk->sUserData.m_byArHandPai[station][i] == 255 && lastpai != 255 && !zimo)
		{
			m_byArHandPai[i] = lastpai;
			break;
		}
	}
	///��С��������
	MaoPaoSort(m_byArHandPai,HAND_CARD_NUM,false);
	bool bb = false;
	///������ת��
	ChangeHandPaiData(m_byArHandPai,255);	
	
	if(pDesk->sGameData.m_mjHuType.byQiXing!=255 && CheckQiXingBuKao())//����
	{
		SetAHupaiType(HUPAI_TYPE_QiXingBuKao,hutype);
		return true;
	}
	if(pDesk->sGameData.m_mjHuType.byQiXingBuKao!=255 && CheckQuanBuKao())//ʮ���� 
	{
		SetAHupaiType(HUPAI_TYPE_QuanBuKao,hutype);
		return true;
	}
	if(pDesk->sGameData.m_mjHuType.byLianQiDui!=255 && CheckLianQiDui())//���߶�
	{
		SetAHupaiType(HUPAI_TYPE_LianQiDui,hutype);
		return true;
	}
	if(pDesk->sGameData.m_mjHuType.byQiDui!=255 && CheckQiDui()>0)//�߶�
	{
		SetAHupaiType(HUPAI_TYPE_QiDui,hutype);
		return true;
	}
	if(pDesk->sGameData.m_mjHuType.byShiSanYao!=255 && CheckShiSanYao())//ʮ����
	{
		SetAHupaiType(HUPAI_TYPE_ShiSanYao,hutype);
		return true;
	}
	
	if(CheckPingHu(lastpai,zimo,true))
	{
		bb = true;
		//����Ͻ��
		///��ӳ���������
		//AddGCPData(pDesk->sUserData.m_UserGCPData[station],&hupaistruct );
		//if(zimo)
		//{
		//	SetAHupaiType(HUPAI_TYPE_ZiMo,hutype);///����
		//}
		//CheckPingHuData();
		for(int i=0;i<MAX_HUPAI_TYPE;i++)
		{
			hutype[i] = m_byHuType[i];
		}
	}
	
	return bb;
}

///���ƣ�AddGCPData
///�����������������ݼ��뵽���ƽṹ��
///@param gcpData[] ��Ҹճ������� , tempstruct  �������ݽṹ
///@return 
void CheckHuPai::AddGCPData(GCPStructEx gcpData[],PingHuStruct * tempstruct)//hupaistruct
{
	BYTE pai[4];
	bool jing[4];
	memset(jing,0,sizeof(jing));
	for(int i=0;i<5;i++)
	{
		if(gcpData[i].byType == 255)
			continue;
		for(int j=0;j<4;j++)
		{
			pai[j] = gcpData[i].byData[j];
		}
		tempstruct->AddData(gcpData[i].byType,pai,jing);
	}
}

///���ƣ�CheckPingHu
///������ƽ�����
///@param  jing �Ƿ����, FengShunZi �����ܷ���˳��, JianShunZi �����Ƿ�����˳��, AddJing �����һ�ž�������ʱ�ã�
///@return true �����ƽ���� false �������ƽ��
bool CheckHuPai::CheckPingHu(BYTE lastzhuapai,bool zimo,bool jing,bool CheckTing)
{
//ѭ������
	TempHupaistruct.Init();
	hupaistruct.Init();
	m_iMaxFan = -1;

	BYTE pai[4]={255};
	bool caishen[4]={0};

	//˫����������ֻ�з�񳤴��齫
	if(m_byJingNum>=2 && m_byJingNum!=255)//
	{
		hupaistruct.Init();//��ʼ�����ƽṹ
		memset(caishen,0,sizeof(caishen));
		memset(pai,255,sizeof(pai));
		pai[0] = pDesk->sUserData.m_StrJing.byPai[0];
		pai[1] = pDesk->sUserData.m_StrJing.byPai[0];
		caishen[0] = true;
		caishen[1] = true;
		hupaistruct.AddData(TYPE_JINGDIAO_JIANG,pai,caishen);//��ӽ�ͷ

		MakePingHu(NoJingHuTempData,hupaistruct,m_byJingNum-2);//���Ƽ��ݹ麯�����ڵݹ������ȫ�����
	}
	//1������ļ��,һ�������һ��������
	if(m_byJingNum>=1 && m_byJingNum!=255)
	{
		for(int i=0;i<NoJingHuTempData.conut;i++)
		{
			if(NoJingHuTempData.data[i][1]<1 || NoJingHuTempData.data[i][1] == 255 ||NoJingHuTempData.data[i][0]==255)
				continue;
			hupaistruct.Init();//��ʼ�����ƽṹ
			NoJingHuTempData.data[i][1]-=1;

			memset(caishen,0,sizeof(caishen));
			memset(pai,255,sizeof(pai));
			pai[0] = NoJingHuTempData.data[i][0];
			pai[1] = NoJingHuTempData.data[i][0];
			caishen[0] = true;
			hupaistruct.AddData(TYPE_JIANG_PAI,pai,caishen);

			MakePingHu(NoJingHuTempData,hupaistruct,m_byJingNum-1);//���Ƽ��ݹ麯�����ڵݹ������ȫ�����
			NoJingHuTempData.data[i][1]+=1;
		}
	}
	//���������ļ��,(�޾����齫HuTempData �� NoJingHuTempData��һ��������)
	for(int i=0;i<NoJingHuTempData.conut;i++)
	{
		if(NoJingHuTempData.data[i][1]<2 || NoJingHuTempData.data[i][0]==255)
			continue;
		hupaistruct.Init();//��ʼ�����ƽṹ
		NoJingHuTempData.data[i][1]-=2;

		memset(caishen,0,sizeof(caishen));
		memset(pai,255,sizeof(pai));
		pai[0] = NoJingHuTempData.data[i][0];
		pai[1] = NoJingHuTempData.data[i][0];
		hupaistruct.AddData(TYPE_JIANG_PAI,pai,caishen);

		MakePingHu(NoJingHuTempData,hupaistruct,m_byJingNum);//���Ƽ��ݹ麯�����ڵݹ������ȫ�����
		NoJingHuTempData.data[i][1]+=2;
	}
	if(m_iMaxFan>=0)
	{
		hupaistruct = TempHupaistruct;
		return true;
	}
	return false;
}
///��ȡ�����������
bool CheckHuPai:: GetMaxCombination(bool zimo,bool jing,BYTE lastpai)
{
	CheckPingHuData();//�Ȼ�ȡ�����

	this->ClearHupaiType(m_byHuType);//�����������

	CString str="";
	int fan = 0;
	///���������ͣ��������̨��������
	SetAHupaiType(HUPAI_TYPE_HuPai,m_byHuType);//����
	if(pDesk->sGameData.m_mjHuType.byZiMo !=255 && zimo)//����
	{
		fan += pDesk->sGameData.m_mjHuType.byZiMo;
		SetAHupaiType(HUPAI_TYPE_ZiMo,m_byHuType);//
	}
	
	if(pDesk->sGameData.m_mjHuType.byPingHu !=255 && CheckIsPingHu())////ƽ��
	{
		fan += pDesk->sGameData.m_mjHuType.byPingHu;
		SetAHupaiType(HUPAI_TYPE_PingHu,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byTianHu !=255 && CheckTianHu())////���
	{
		fan += pDesk->sGameData.m_mjHuType.byTianHu;
		SetAHupaiType(HUPAI_TYPE_TianHu,m_byHuType);//
	}

	if(pDesk->sGameData.m_mjHuType.byDiHu !=255 && CheckDiHu())////�غ�
	{
		fan += pDesk->sGameData.m_mjHuType.byDiHu;
		SetAHupaiType(HUPAI_TYPE_DiHu,m_byHuType);//
	}	

///////

	if(pDesk->sGameData.m_mjHuType.byGSH !=255 && CheckGangKai())//���ϻ�
	{
		fan += pDesk->sGameData.m_mjHuType.byGSH;
		SetAHupaiType(HUPAI_TYPE_GangKai,m_byHuType);//
	}	
	if(pDesk->sGameData.m_mjHuType.byGHP !=255 && CheckGangHouPao())//�ܺ���
	{
		fan += pDesk->sGameData.m_mjHuType.byGHP;
		SetAHupaiType(HUPAI_TYPE_GangHaoPao,m_byHuType);//
	}	
	if(pDesk->sGameData.m_mjHuType.byYiBanGao !=255 && CheckYiBanGao())//һ���
	{
		fan += pDesk->sGameData.m_mjHuType.byYiBanGao;
		SetAHupaiType(HUPAI_TYPE_YiBanGao,m_byHuType);//
	}	
	if(pDesk->sGameData.m_mjHuType.byXiXiangFeng !=255 && CheckXiXiangFeng())//ϲ���
	{
		fan += pDesk->sGameData.m_mjHuType.byXiXiangFeng;
		SetAHupaiType(HUPAI_TYPE_XiXiangFeng,m_byHuType);//
	}	
	if(pDesk->sGameData.m_mjHuType.byLianLiu !=255 && CheckLianLiu())//����
	{
		fan += pDesk->sGameData.m_mjHuType.byLianLiu;
		SetAHupaiType(HUPAI_TYPE_LianLiu,m_byHuType);//
	}	
	if(pDesk->sGameData.m_mjHuType.byLaoShaoFu !=255 && CheckLaoShaoFu())//���ٸ�
	{
		fan += pDesk->sGameData.m_mjHuType.byLaoShaoFu;
		SetAHupaiType(HUPAI_TYPE_LaoShaoFu,m_byHuType);//
	}	
	if(pDesk->sGameData.m_mjHuType.byYaoJiuKe !=255 && CheckYaoJiuKe())//�۾ſ�
	{
		fan += pDesk->sGameData.m_mjHuType.byYaoJiuKe;
		SetAHupaiType(HUPAI_TYPE_YaoJiuKe,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byMingGang !=255 && CheckMingGang())//����
	{
		fan += pDesk->sGameData.m_mjHuType.byMingGang;
		SetAHupaiType(HUPAI_TYPE_MingGang,m_byHuType);//
	}	
	if(pDesk->sGameData.m_mjHuType.byQueYiMen !=255 && CheckQueYiMen())//ȱһ��
	{
		fan += pDesk->sGameData.m_mjHuType.byQueYiMen;
		SetAHupaiType(HUPAI_TYPE_QueYiMen,m_byHuType);//
	}	
	if(pDesk->sGameData.m_mjHuType.byWuZi !=255 && CheckWuZi())//����
	{
		fan += pDesk->sGameData.m_mjHuType.byWuZi;
		SetAHupaiType(HUPAI_TYPE_WuZi,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byBianZhang !=255 && CheckBianZhang())//����
	{
		fan += pDesk->sGameData.m_mjHuType.byBianZhang;
		SetAHupaiType(HUPAI_TYPE_BianZhang,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byKanZhang !=255 && CheckKanZhang())//����
	{
		fan += pDesk->sGameData.m_mjHuType.byKanZhang;
		SetAHupaiType(HUPAI_TYPE_KanZhang,m_byHuType);//
	}	
	if(pDesk->sGameData.m_mjHuType.byDanDiao !=255 && CheckDanDiaoJiang())//������
	{
		fan += pDesk->sGameData.m_mjHuType.byDanDiao;
		SetAHupaiType(HUPAI_TYPE_DanDiaoJiang,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byJianKe !=255 && CheckJianKe())//����
	{
		fan += pDesk->sGameData.m_mjHuType.byJianKe;
		SetAHupaiType(HUPAI_TYPE_JianKe,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byQuanFengKe !=255 && CheckQuanFengKe())//Ȧ���
	{
		fan += pDesk->sGameData.m_mjHuType.byQuanFengKe;
		SetAHupaiType(HUPAI_TYPE_QuanFengKe,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byMenFengKe !=255 && CheckMenFengKe())//�ŷ��
	{
		fan += pDesk->sGameData.m_mjHuType.byMenFengKe;
		SetAHupaiType(HUPAI_TYPE_MenFengKe,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byMenQianQing !=255 && CheckMenQianQing())//��ǰ��
	{
		fan += pDesk->sGameData.m_mjHuType.byMenQianQing;
		SetAHupaiType(HUPAI_TYPE_MenQianQing,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.bySiGuiYi !=255 && CheckSiGuiYi())//�Ĺ�һ
	{
		fan += pDesk->sGameData.m_mjHuType.bySiGuiYi;
		SetAHupaiType(HUPAI_TYPE_SiGuiYi,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byShuangTongKe !=255 && CheckShuangTongKe())//˫ͬ��
	{
		fan += pDesk->sGameData.m_mjHuType.byShuangTongKe;
		SetAHupaiType(HUPAI_TYPE_ShuangTongKe,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byShuangAnKe !=255 && CheckShuangAnGang())//˫����
	{
		fan += pDesk->sGameData.m_mjHuType.byShuangAnKe;
		SetAHupaiType(HUPAI_TYPE_ShuangAnKe,m_byHuType);//
	}
///////

	if(pDesk->sGameData.m_mjHuType.byAnGang !=255 && CheckAnGang())//����
	{
		fan += pDesk->sGameData.m_mjHuType.byAnGang;
		SetAHupaiType(HUPAI_TYPE_AnGang,m_byHuType);//
	}	


	if(pDesk->sGameData.m_mjHuType.byDuanYao !=255 && CheckDuanYao())//����
	{
		fan += pDesk->sGameData.m_mjHuType.byDuanYao;
		SetAHupaiType(HUPAI_TYPE_DuanYao,m_byHuType);//
	}	
	if(pDesk->sGameData.m_mjHuType.byQuanDaiYao !=255 && CheckQuanDaiYao())//ȫ����
	{
		fan += pDesk->sGameData.m_mjHuType.byQuanDaiYao;
		SetAHupaiType(HUPAI_TYPE_QuanDaiYao,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byBuQiuRen !=255 && CheckBuQiuRen())//������
	{
		fan += pDesk->sGameData.m_mjHuType.byBuQiuRen;
		SetAHupaiType(HUPAI_TYPE_BuQiuRen,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byShuangMingGang !=255 && CheckShuangMingGang())//˫����
	{
		fan += pDesk->sGameData.m_mjHuType.byShuangMingGang;
		SetAHupaiType(HUPAI_TYPE_ShuangMingGang,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byHuJueZhang !=255 && CheckHuJueZhang())//�;���
	{
		fan += pDesk->sGameData.m_mjHuType.byHuJueZhang;
		SetAHupaiType(HUPAI_TYPE_HuJueZhang,m_byHuType);//
	}

	if(pDesk->sGameData.m_mjHuType.byPengPengHu !=255 && CheckPengPengHu())//������
	{
		fan += pDesk->sGameData.m_mjHuType.byPengPengHu;
		SetAHupaiType(HUPAI_TYPE_PengPengHu,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byHunYiSe !=255 && CheckHunYiSe())//��һɫ
	{
		fan += pDesk->sGameData.m_mjHuType.byHunYiSe;
		SetAHupaiType(HUPAI_TYPE_HunYiSe,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.bySanSeSanBuGao !=255 && CheckSanSeSanBuGao())//��ɫ������
	{
		fan += pDesk->sGameData.m_mjHuType.bySanSeSanBuGao;
		SetAHupaiType(HUPAI_TYPE_SanSeSanBuGao,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byWuMenQi !=255 && CheckWuMenQi())//������
	{
		fan += pDesk->sGameData.m_mjHuType.byWuMenQi;
		SetAHupaiType(HUPAI_TYPE_WuMenQi,m_byHuType);//
	}	
	if(pDesk->sGameData.m_mjHuType.byQuanQiuRen !=255 && CheckQuanQiuRen())//ȫ����
	{
		fan += pDesk->sGameData.m_mjHuType.byQuanQiuRen;
		SetAHupaiType(HUPAI_TYPE_QuanQiuRen,m_byHuType);//
	}	
	if(pDesk->sGameData.m_mjHuType.byShuangAnGang !=255 && CheckShuangAnKe())//˫����
	{
		fan += pDesk->sGameData.m_mjHuType.byShuangAnGang;
		SetAHupaiType(HUPAI_TYPE_ShuangAnGang,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byShuangJianKe !=255 && CheckShuangJianKe())//˫����
	{
		fan += pDesk->sGameData.m_mjHuType.byShuangJianKe;
		SetAHupaiType(HUPAI_TYPE_ShuangJianKe,m_byHuType);//
	}	
	if(pDesk->sGameData.m_mjHuType.byHuaLong !=255 && CheckHuaLong())//����
	{
		fan += pDesk->sGameData.m_mjHuType.byHuaLong;
		SetAHupaiType(HUPAI_TYPE_HuaLong,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byTuiBuDao !=255 && CheckTuiBuDao())//�Ʋ���
	{
		fan += pDesk->sGameData.m_mjHuType.byTuiBuDao;
		SetAHupaiType(HUPAI_TYPE_TuiBuDao,m_byHuType);//
	}	
	if(pDesk->sGameData.m_mjHuType.bySSSTongShun !=255 && CheckSanSeSanTongShun())//��ɫ��ͬ˳
	{
		fan += pDesk->sGameData.m_mjHuType.bySSSTongShun;
		SetAHupaiType(HUPAI_TYPE_SanSeSanTongShun,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.bySSSJieGao !=255 && CheckSanSeSanJieGao())//��ɫ���ڸ�
	{
		fan += pDesk->sGameData.m_mjHuType.bySSSJieGao;
		SetAHupaiType(HUPAI_TYPE_SanSeSanJieGao,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byWuFanHu !=255 && CheckWuFanHe())//�޷���
	{
		fan += pDesk->sGameData.m_mjHuType.byWuFanHu;
		SetAHupaiType(HUPAI_TYPE_WuFanHu,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byMiaoShouHuiChun !=255 && CheckMiaoShouHuiChun())//���ֻش�
	{
		fan += pDesk->sGameData.m_mjHuType.byMiaoShouHuiChun;
		SetAHupaiType(HUPAI_TYPE_MiaoShouHuiChun,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byHaiDiLaoYue !=255 && CheckHaiDiLaoYue())//��������
	{
		fan += pDesk->sGameData.m_mjHuType.byHaiDiLaoYue;
		SetAHupaiType(HUPAI_TYPE_HaiDiLaoYue,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byQiangGangHu !=255 && CheckQiangGangHe())//���ܺ�
	{
		fan += pDesk->sGameData.m_mjHuType.byQiangGangHu;
		SetAHupaiType(HUPAI_TYPE_QiangGang,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byDaYuWu !=255 && CheckDaYuWu())//������
	{
		fan += pDesk->sGameData.m_mjHuType.byDaYuWu;
		SetAHupaiType(HUPAI_TYPE_DaYuWu,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byXiaoYuWu !=255 && CheckXiaoYuWu())//С����
	{
		fan += pDesk->sGameData.m_mjHuType.byXiaoYuWu;
		SetAHupaiType(HUPAI_TYPE_XiaoYuWu,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.bySanFengKe !=255 && CheckSanFengKe())//�����
	{
		fan += pDesk->sGameData.m_mjHuType.bySanFengKe;
		SetAHupaiType(HUPAI_TYPE_SanFengKe,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byQiangLong !=255 && CheckQingLong())//����
	{
		fan += pDesk->sGameData.m_mjHuType.byQiangLong;
		SetAHupaiType(HUPAI_TYPE_QingLong,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.bySSShuangLongHui !=255 && CheckSanSeShuangLongHui())//��ɫ˫����
	{
		fan += pDesk->sGameData.m_mjHuType.bySSShuangLongHui;
		SetAHupaiType(HUPAI_TYPE_SanSeShuangLongHui,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byYiSeSanBuGao !=255 && CheckYiSeSanBuGao())//һɫ������
	{
		fan += pDesk->sGameData.m_mjHuType.byYiSeSanBuGao;
		SetAHupaiType(HUPAI_TYPE_YiSeSanBuGao,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byQuanDaiWu !=255 && CheckQuanDaiWu())//ȫ����
	{
		fan += pDesk->sGameData.m_mjHuType.byQuanDaiWu;
		SetAHupaiType(HUPAI_TYPE_QuanDaiWu,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.bySanTongKe !=255 && CheckSanTongKe())//��ͬ��
	{
		fan += pDesk->sGameData.m_mjHuType.bySanTongKe;
		SetAHupaiType(HUPAI_TYPE_SanTongKe,m_byHuType);//
	}
/////////////////

	if(pDesk->sGameData.m_mjHuType.bySanAnKe !=255 && CheckSanAnKe())//������
	{
		fan += pDesk->sGameData.m_mjHuType.bySanAnKe;
		SetAHupaiType(HUPAI_TYPE_SanAnKe,m_byHuType);//
	}
	//CheckPingHuData();//�Ȼ�ȡ�����

	if(pDesk->sGameData.m_mjHuType.byQuanShuangKe !=255 && CheckQuanShuangKe())//ȫ˫��
	{
		fan += pDesk->sGameData.m_mjHuType.byQuanShuangKe;
		SetAHupaiType(HUPAI_TYPE_QuanShuangKe,m_byHuType);//
	}	
	if(pDesk->sGameData.m_mjHuType.byQingYiSe !=255 && CheckQingYiSe())//��һɫ
	{
		fan += pDesk->sGameData.m_mjHuType.byQingYiSe;
		SetAHupaiType(HUPAI_TYPE_QingYiSe,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byYiSSTongShun !=255 && CheckYiSeSanTongShun())//һɫ��ͬ˳
	{
		fan += pDesk->sGameData.m_mjHuType.byYiSSTongShun;
		SetAHupaiType(HUPAI_TYPE_YiSeSanTongShun,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byYiSSJieGao !=255 && CheckYiSeSanJieGao())//һɫ���ڸ�
	{
		fan += pDesk->sGameData.m_mjHuType.byYiSSJieGao;
		SetAHupaiType(HUPAI_TYPE_YiSeSanJieGao,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byQuanDa !=255 && CheckQuanDa())//ȫ��
	{
		fan += pDesk->sGameData.m_mjHuType.byQuanDa;
		SetAHupaiType(HUPAI_TYPE_QuanDa,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byQuanZhong !=255 && CheckQuanZhong())//ȫ��
	{
		fan += pDesk->sGameData.m_mjHuType.byQuanZhong;
		SetAHupaiType(HUPAI_TYPE_QuanZhong,m_byHuType);//
	}	
	if(pDesk->sGameData.m_mjHuType.byQuanXiao !=255 && CheckQuanXiao())//ȫС
	{
		fan += pDesk->sGameData.m_mjHuType.byQuanXiao;
		SetAHupaiType(HUPAI_TYPE_QuanXiao,m_byHuType);//
	}	
//

	if(pDesk->sGameData.m_mjHuType.byYiSeSiBuGao !=255 && CheckYiSeSiBuGao())//һɫ�Ĳ���
	{
		fan += pDesk->sGameData.m_mjHuType.byYiSeSiBuGao;
		SetAHupaiType(HUPAI_TYPE_YiSeSiBuGao,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.bySanGang !=255 && CheckSanGang())//����
	{
		fan += pDesk->sGameData.m_mjHuType.bySanGang;
		SetAHupaiType(HUPAI_TYPE_SanGang,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byHunYaoJiu !=255 && CheckHunYaoJiu())//���۾�
	{
		fan += pDesk->sGameData.m_mjHuType.byHunYaoJiu;
		SetAHupaiType(HUPAI_TYPE_HunYaoJiu,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byYSSiTongShun !=255 && CheckYiSeSiTongShun())//һɫ��ͬ˳
	{
		fan += pDesk->sGameData.m_mjHuType.byYSSiTongShun;
		SetAHupaiType(HUPAI_TYPE_YiSeSiTongShun,m_byHuType);//
	}	
	if(pDesk->sGameData.m_mjHuType.byYSSiJieGao !=255 && CheckYiSeSiJieGao())//һɫ�Ľڸ�
	{
		fan += pDesk->sGameData.m_mjHuType.byYSSiJieGao;
		SetAHupaiType(HUPAI_TYPE_YiSeSiJieGao,m_byHuType);//
	}	
	if(pDesk->sGameData.m_mjHuType.byQingYaoJiu !=255 && CheckQingYaoJiu())//���۾�
	{
		fan += pDesk->sGameData.m_mjHuType.byQingYaoJiu;
		SetAHupaiType(HUPAI_TYPE_QingYaoJiu,m_byHuType);//
	}	
	if(pDesk->sGameData.m_mjHuType.byXiaoSiXi !=255 && CheckXiaoSiXi())//С��ϲ
	{
		fan += pDesk->sGameData.m_mjHuType.byXiaoSiXi;
		SetAHupaiType(HUPAI_TYPE_XiaoSiXi,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byXiaoSanYuan !=255 && CheckXiaoSanYuan())//С��Ԫ
	{
		fan += pDesk->sGameData.m_mjHuType.byXiaoSanYuan;
		SetAHupaiType(HUPAI_TYPE_XiaoSanYuan,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byZiYeSe !=255 && CheckZiYiSe())//��һɫ
	{
		fan += pDesk->sGameData.m_mjHuType.byZiYeSe;
		SetAHupaiType(HUPAI_TYPE_ZiYiSe,m_byHuType);//
	}

	if(pDesk->sGameData.m_mjHuType.bySiAnKe !=255 && CheckSiAnKe())//�İ���
	{
		fan += pDesk->sGameData.m_mjHuType.bySiAnKe;
		SetAHupaiType(HUPAI_TYPE_SiAnKe,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byYSShuangLongHui !=255 && CheckYiSeShuangLongHui())//һɫ˫����
	{
		fan += pDesk->sGameData.m_mjHuType.byYSShuangLongHui;
		SetAHupaiType(HUPAI_TYPE_YiSeShuangLongHui,m_byHuType);//
	}	
	if(pDesk->sGameData.m_mjHuType.byDaSiXi !=255 && CheckDaSiXi())//����ϲ
	{
		fan += pDesk->sGameData.m_mjHuType.byDaSiXi;
		SetAHupaiType(HUPAI_TYPE_DaSiXi,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byDaSanYuan !=255 && CheckDaSanYuan())//����Ԫ
	{
		fan += pDesk->sGameData.m_mjHuType.byDaSanYuan;
		SetAHupaiType(HUPAI_TYPE_DaSanYuan,m_byHuType);//
	}	
	if(pDesk->sGameData.m_mjHuType.byLvYiSe !=255 && CheckLvYiSe())//��һɫ
	{
		fan += pDesk->sGameData.m_mjHuType.byLvYiSe;
		SetAHupaiType(HUPAI_TYPE_LvYiSe,m_byHuType);//
	}
	if(pDesk->sGameData.m_mjHuType.byJiuLianBaoDeng !=255 && CheckJiuLianBaoDeng())//��������
	{
		fan += pDesk->sGameData.m_mjHuType.byJiuLianBaoDeng;
		SetAHupaiType(HUPAI_TYPE_JiuLianBaoDeng,m_byHuType);//
	}	
	if(pDesk->sGameData.m_mjHuType.bySiGang!=255 && CheckSiGang())//�ĸܣ�ʮ���޺���
	{
		fan += pDesk->sGameData.m_mjHuType.bySiGang;
		SetAHupaiType(HUPAI_TYPE_SiGang,m_byHuType);//
	}
	
	if(CheckHupaiType(HUPAI_TYPE_PengPengHu,m_byHuType))
	{
			OutputDebugString("���Ʋ��ԣ�����������");
	}
	str.Format("���Ʋ��ԣ�fan=%d m_iMaxFan=%d",fan,m_iMaxFan);
	OutputDebugString(str);
	if(fan>m_iMaxFan)
	{
		m_iMaxFan = fan;
		return true;
	}
	return false;
}

///������ƽ������
///@param csnum ������, hupaistruct ���ƽṹ, FengShunZi �����ܷ���˳��, JianShunZi �����Ƿ�����˳��
///@return true �����ƽ���� false �������ƽ��
bool CheckHuPai::MakePingHu(CheckHuStruct &PaiData,PingHuStruct &hupaistruct,int csnum)
{
	if(PaiData.GetAllPaiCount()<=0)//�Ѿ�����
	{
		//OutputDebugString("���Ʋ��ԣ�MakePingHu ��ɺ���");
		//CheckPingHuData();
		////������ͣ���¼�������
		return GetMaxCombination(m_bZimo,true,m_byLastPai);
	}
	if(csnum >HAND_CARD_NUM)
	{
		csnum=0;
	}
	////ȡ��
	BYTE pai=255;
	int count = 0,ijing = csnum;
	for(int i=0;i<PaiData.conut;i++)
	{
		if(PaiData.data[i][1]==255 || PaiData.data[i][1]==0)
			continue;
		pai = PaiData.data[i][0];   //��¼��ֵ
		count = PaiData.data[i][1]; //��¼����
		break;
	}
	char buf[500];
	//sprintf(buf,"���Ʋ��ԣ�MakePingHu ����� %d ���� %d  ������%d ʣ��������%d",pai,count,csnum,PaiData.GetAllPaiCount());
	//OutputDebugString(buf);


	BYTE data[4];
	bool caishen[4];
	memset(data,255,sizeof(data));
	memset(caishen,0,sizeof(caishen));

	data[0] = pai;
	data[1] = pai;
	data[2] = pai;
	if(csnum>2)//һ���ƺ� 2����
	{		
		caishen[0] = true;
		caishen[1] = true;
		hupaistruct.AddData(TYPE_AN_KE,data,caishen);//�������
		PaiData.SetPaiCount(pai,count-1);//������


		MakePingHu(PaiData,hupaistruct,csnum-2);//�ݹ�

		PaiData.SetPaiCount(pai,count);//�����ϻָ���
		hupaistruct.DeleteData(TYPE_AN_KE,data,caishen);//�ָ�����
	}
	if(csnum >= 1 && count>=2)//һ�Ų���������������
	{
		memset(caishen,0,sizeof(caishen));
		caishen[0] = true;
		hupaistruct.AddData(TYPE_AN_KE,data,caishen);//�������
		PaiData.SetPaiCount(pai,count-2);//������

		MakePingHu(PaiData,hupaistruct,csnum-1);

		PaiData.SetPaiCount(pai,count);//�����ϻָ���
		hupaistruct.DeleteData(TYPE_AN_KE,data,caishen);//�ָ�����
	}

	if(count>=3)//�����������
	{
		memset(caishen,0,sizeof(caishen));
		hupaistruct.AddData(TYPE_AN_KE,data,caishen);//�������
		PaiData.SetPaiCount(pai,count-3);//������

		MakePingHu(PaiData,hupaistruct,csnum);

		PaiData.SetPaiCount(pai,count);//�����ϻָ���
		hupaistruct.DeleteData(TYPE_AN_KE,data,caishen);//�ָ�����
	}
	if(pai>=CMjEnum::MJ_TYPE_FD)//���ƣ�ֻ���ǿ���
		return false;
	 //��ͬ��������˳��
	if(csnum>=2 && pai%10 >=3)//��� xx+pai ��˳�ӣ�x�ǲ���
	{
		memset(caishen,0,sizeof(caishen));
		caishen[0] = true;
		caishen[1] = true;
		data[0] = pai-2;
		data[1] = pai-1;
		data[2] = pai;
		hupaistruct.AddData(TYPE_SHUN_ZI,data,caishen);//������ƣ�˳��
		PaiData.SetPaiCount(pai,count-1);//������

		MakePingHu(PaiData,hupaistruct,csnum-2);

		PaiData.SetPaiCount(pai,count);//�����ϻָ���
		hupaistruct.DeleteData(TYPE_SHUN_ZI,data,caishen);//�ָ�����
	}

	if(csnum>=1 && pai%10 >=2 && pai%10<9 && PaiData.GetPaiCount(pai+1)>=1)//��� x+pai+(pai+1) ��˳�ӣ�x�ǲ���
	{
		memset(caishen,0,sizeof(caishen));
		caishen[0] = true;
		data[0] = pai-1;
		data[1] = pai;
		data[2] = pai+1;
		hupaistruct.AddData(TYPE_SHUN_ZI,data,caishen);//������ƣ�˳��
		PaiData.SetPaiCount(pai,count-1);//������
		PaiData.SetPaiCount(pai+1,PaiData.GetPaiCount(pai+1)-1);//������

		MakePingHu(PaiData,hupaistruct,csnum-1);

		PaiData.SetPaiCount(pai,count);//�����ϻָ���
		PaiData.SetPaiCount(pai+1,PaiData.GetPaiCount(pai+1)+1);//�����ϻָ���
		hupaistruct.DeleteData(TYPE_SHUN_ZI,data,caishen);//�ָ�����
	}

	if(csnum>=2 && pai%10 >=2 && pai%10<9)//��� x+pai+(x) ��˳�ӣ�x�ǲ���
	{
		memset(caishen,0,sizeof(caishen));
		caishen[0] = true;
		caishen[2] = true;
		data[0] = pai-1;
		data[1] = pai;
		data[2] = pai+1;
		hupaistruct.AddData(TYPE_SHUN_ZI,data,caishen);//������ƣ�˳��
		PaiData.SetPaiCount(pai,count-1);//������

		MakePingHu(PaiData,hupaistruct,csnum-2);

		PaiData.SetPaiCount(pai,count);//�����ϻָ���
		hupaistruct.DeleteData(TYPE_SHUN_ZI,data,caishen);//�ָ�����
	}

	if( pai%10<8 && PaiData.GetPaiCount(pai+1)>=1 && PaiData.GetPaiCount(pai+2)>=1)//��� pai+(pai+1)+(pai+2) ��˳��
	{
		memset(caishen,0,sizeof(caishen));
		data[0] = pai;
		data[1] = pai+1;
		data[2] = pai+2;
		hupaistruct.AddData(TYPE_SHUN_ZI,data,caishen);//������ƣ�˳��
		PaiData.SetPaiCount(pai,count-1);//������
		PaiData.SetPaiCount(pai+1,PaiData.GetPaiCount(pai+1)-1);//������
		PaiData.SetPaiCount(pai+2,PaiData.GetPaiCount(pai+2)-1);//������

		MakePingHu(PaiData,hupaistruct,csnum);

		PaiData.SetPaiCount(pai,count);//�����ϻָ���
		PaiData.SetPaiCount(pai+1,PaiData.GetPaiCount(pai+1)+1);//������
		PaiData.SetPaiCount(pai+2,PaiData.GetPaiCount(pai+2)+1);//������
		hupaistruct.DeleteData(TYPE_SHUN_ZI,data,caishen);//�ָ�����	
	}
	
	if(csnum>=1 && pai%10<8 &&  PaiData.GetPaiCount(pai+1)<1 && PaiData.GetPaiCount(pai+2)>=1)//��� pai+(x)+(pai+2) ��˳��
	{
		memset(caishen,0,sizeof(caishen));
		caishen[1] = true;
		data[0] = pai;
		data[1] = pai+1;
		data[2] = pai+2;
		hupaistruct.AddData(TYPE_SHUN_ZI,data,caishen);//������ƣ�˳��
		PaiData.SetPaiCount(pai,count-1);//������
		PaiData.SetPaiCount(pai+2,PaiData.GetPaiCount(pai+2)-1);//������

		MakePingHu(PaiData,hupaistruct,csnum-1);

		PaiData.SetPaiCount(pai,count);//�����ϻָ���
		PaiData.SetPaiCount(pai+2,PaiData.GetPaiCount(pai+2)+1);//������
		hupaistruct.DeleteData(TYPE_SHUN_ZI,data,caishen);//�ָ�����	
	}
	
	if(csnum>=1 && pai%10<8 && PaiData.GetPaiCount(pai+1)>=1 && PaiData.GetPaiCount(pai+2)<1)//��� pai+(pai+1)+(x) ��˳��
	{
		memset(caishen,0,sizeof(caishen));
		caishen[2] = true;
		data[0] = pai;
		data[1] = pai+1;
		data[2] = pai+2;
		hupaistruct.AddData(TYPE_SHUN_ZI,data,caishen);//������ƣ�˳��
		PaiData.SetPaiCount(pai,count-1);//������
		PaiData.SetPaiCount(pai+1,PaiData.GetPaiCount(pai+1)-1);//������

		MakePingHu(PaiData,hupaistruct,csnum-1);

		PaiData.SetPaiCount(pai,count);//�����ϻָ���
		PaiData.SetPaiCount(pai+1,PaiData.GetPaiCount(pai+1)+1);//������
		hupaistruct.DeleteData(TYPE_SHUN_ZI,data,caishen);//�ָ�����	
	}
	
	if(csnum>=2 && pai%10<8 )//��� pai+(x)+(x) ��˳��
	{
		memset(caishen,0,sizeof(caishen));
		caishen[1] = true;
		caishen[2] = true;
		data[0] = pai;
		data[1] = pai+1;
		data[2] = pai+2;
		hupaistruct.AddData(TYPE_SHUN_ZI,data,caishen);//������ƣ�˳��
		PaiData.SetPaiCount(pai,count-1);//������

		MakePingHu(PaiData,hupaistruct,csnum-2);

		PaiData.SetPaiCount(pai,count);//�����ϻָ���
		hupaistruct.DeleteData(TYPE_SHUN_ZI,data,caishen);//�ָ�����	
	}
	return false;	
}

///�������ָ�����,�Ѽ������ƻ�ԭ
///@param num[] ��ʱ�����ԭ������
///@return 
void CheckHuPai::ReSetPaiNum(BYTE num[],CheckHuStruct &TempPai)
{
	for(int i=0;i<TempPai.conut;i++)
	{
		 TempPai.data[i][1] = num[i];
	}
}

///��������������Ƿ�ͬһ��ɫ
///@param pai1, pai2 Ҫ����������
///@return true �ǣ� false ����
bool CheckHuPai::CheckTongSe(BYTE pai1,BYTE pai2)
{
	int count=0;
	if(pai2%10==0 || pai1/10 != pai2/10)
		return false;
	return true;
}

///���ƣ�CheckLianPai
///��������������Ƿ�����,num �����ţ�1���������ţ�2������������
///@param pai1, pai2 Ҫ�����ƣ� num ���������
///@return true �����ţ�flse ��������
bool CheckHuPai::CheckLianPai(BYTE pai1,BYTE pai2,BYTE num)
{
	if(!CheckTongSe(pai1,pai2))
		return false;
	if(num==1)
	{
		if(pai1 == pai2+1 || pai1 == pai2-1)
		{
			return true;
		}
	}
	else if(num == 2)
	{
		if(pai1 == pai2+1 || pai1 == pai2-1 || pai1 == pai2+2 || pai1 == pai2-2)
		{
			if(!pDesk->sGameData.m_mjAction.bChiFeng && (pai1>=CMjEnum::MJ_TYPE_FD && pai1<=CMjEnum::MJ_TYPE_FB || pai2>=CMjEnum::MJ_TYPE_FD && pai2<=CMjEnum::MJ_TYPE_FB))
				return false;
			if(!pDesk->sGameData.m_mjAction.bChiJian && (pai1>=CMjEnum::MJ_TYPE_ZHONG && pai1<=CMjEnum::MJ_TYPE_BAI || pai2>=CMjEnum::MJ_TYPE_ZHONG && pai2<=CMjEnum::MJ_TYPE_BAI))
				return false;
			if(pai2>=CMjEnum::MJ_TYPE_FD && pai2<=CMjEnum::MJ_TYPE_FB)///��������
			{
				if(pai1>CMjEnum::MJ_TYPE_FB || pai1<CMjEnum::MJ_TYPE_FD)
					return false;
			}
			else if(pai2>=CMjEnum::MJ_TYPE_ZHONG && pai2<=CMjEnum::MJ_TYPE_BAI)///�з���
			{
				if(pai1>CMjEnum::MJ_TYPE_BAI || pai1<CMjEnum::MJ_TYPE_ZHONG)
					return false;
			}
			return true;
		}
	}
	return false;
}

///���ƣ�SetAHupaiType
///���������һ�ֺ�������
///@param   type Ҫ��ӵ����� , hupai[] ������������
///@return 
void CheckHuPai::SetAHupaiType(BYTE type,BYTE hupai[])
{
	if(CheckHupaiType(type,hupai))//���˾Ͳ������
		return;
	for(int i=0;i<MAX_HUPAI_TYPE;i++)
	{
		if(hupai[i] == 255)
		{
			hupai[i] = type;
			break;
		}
	}
}

///���ƣ�ReSetAHupaiType
///����������һ�ֺ�������
///@param type Ҫɾ�������� , hupai[] ������������
///@return 
void CheckHuPai::ReSetAHupaiType(BYTE type,BYTE hupai[])
{
	int index = 0;
	for(int i=0;i<MAX_HUPAI_TYPE;i++)
	{
		if(hupai[i] == type)
		{
			hupai[i] = 255;
			break;
		}
	}
	//ȥ���м���ЧԪ��
	BYTE temp[MAX_HUPAI_TYPE];
	memset(temp,255,sizeof(temp));
	for(int i=0;i<MAX_HUPAI_TYPE;i++)
	{
		if(hupai[i] != 255)
		{
			temp[index] = hupai[i];
			index++;
		}
	}
	for(int i=0;i<MAX_HUPAI_TYPE;i++)
	{
		hupai[i] = temp[i];
	}
}

///���ƣ�ClearHupaiType
///������������к�������
///@param type Ҫɾ�������� , hupai[] ������������
///@return 
void CheckHuPai::ClearHupaiType(BYTE hupai[])
{
	for(int i=0;i<MAX_HUPAI_TYPE;i++)
	{
		hupai[i] = 255;
	}
}

///���ƣ�CheckHupaiType
///����������Ƿ����ĳ�ֺ�������
///@param type Ҫ�������� , hupai[] ������������
///@return true ���ڣ�flse ������
bool CheckHuPai::CheckHupaiType(BYTE type,BYTE hupai[])
{
	int index = 0;
	for(int i=0;i<MAX_HUPAI_TYPE;i++)
	{
		if(hupai[i] == type && type!=255)
		{
			return true;
		}
	}
	return false;
}

///���ƣ�InitData
///��������ʼ������
///@param 
///@return 
void CheckHuPai::InitData()
{
	m_byStation = 0;///��ǰ�����ҵ�λ��
	hupaistruct.Init();
	HuTempData.Init();	//���Ƽ����ʱ����
	NoJingHuTempData.Init();///���Ƽ����ʱ����(�޲���)	
	m_byJingNum = 0;  //��������
	//�����������ڵ���
	m_byLastPai = 255;
	ClearPingHuData();
}

///���ƣ�ClearPingHuData
///�����������������
///@param 
///@return 
void CheckHuPai::ClearPingHuData()
{		
	m_byJiang = 255;			//��������
	m_byShunNum = 0;			//˳�ӵĸ���
	memset(m_byShunData,255,sizeof(m_byShunData));//˳�ӵ�����	
	m_byKeziNum = 0;			//���ӵĸ���	
	memset(m_byKeziData,255,sizeof(m_byKeziData));//���ӵ�����
	m_byGangNum = 0;			//���Ƶĸ���
	memset(m_byGangData,255,sizeof(m_byGangData));	//���Ƶ�����
	m_byChiNum = 0;				//���Ƶĸ���
	m_byPengNum = 0;			//���Ƶĸ���
}

///���ƣ�CheckPingHuData
///���������ƽ��������ϣ����ƣ��ԣ����ܣ�˳�ӣ����̵�
///@param 
///@return 
void CheckHuPai::CheckPingHuData()
{
	char str[800];
	//str.Format("new:ƽ����� �������Ƽ�⣺ƽ������  ��������оٿ�ʼ ------------------mainjing=%d",byMainJing);
	//OutputDebugString(str);

	ClearPingHuData();

	sprintf(str,"���Ʋ��ԣ�CheckPingHuData ��ʼ m_byGangNum=%d  m_byShunNum=%d m_byKeziNum=%d",m_byGangNum,m_byShunNum,m_byKeziNum);
	OutputDebugString(str);

	BYTE num = 0;
	for(int i=0;i<hupaistruct.count;i++)
	{
		switch(hupaistruct.byType[i])
		{
		case TYPE_JINGDIAO_JIANG:
		case TYPE_JIANG_PAI:
			{
				m_byJiang = hupaistruct.data[i][0];
				sprintf(str,"���Ʋ��ԣ�  ���� m_byGangNum=%d  m_byShunNum=%d m_byKeziNum=%d ��%d",m_byGangNum,m_byShunNum,m_byKeziNum,m_byJiang);
				OutputDebugString(str);
			}
			break;
		case TYPE_SHUN_ZI:
			{
				m_byShunData[m_byShunNum] = hupaistruct.data[i][0];
				m_byShunNum++;
				sprintf(str,"���Ʋ��ԣ� ˳�� m_byGangNum=%d  m_byShunNum=%d m_byKeziNum=%d ��%d",m_byGangNum,m_byShunNum,m_byKeziNum,hupaistruct.data[i][0]);
				OutputDebugString(str);
			}
			break;
		case TYPE_AN_KE:
			{
				m_byKeziData[m_byKeziNum] = hupaistruct.data[i][0];
				m_byKeziNum++;
				sprintf(str,"���Ʋ��ԣ�  ���� m_byGangNum=%d  m_byShunNum=%d m_byKeziNum=%d ��%d",m_byGangNum,m_byShunNum,m_byKeziNum,hupaistruct.data[i][0]);
				OutputDebugString(str);

			}
			break;
		default:
			break;
		}
	}
	sprintf(str,"���Ʋ��ԣ� m_byGangNum=%d  m_byShunNum=%d m_byKeziNum=%d",m_byGangNum,m_byShunNum,m_byKeziNum);
	OutputDebugString(str);

	BYTE pai[4];
	memset(pai,255,sizeof(pai));
	for(int i=0;i<5;i++)
	{
		if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byType == 255)
			continue;
		for(int j=0;j<4;++j)
		{
			pai[j] = pDesk->sUserData.m_UserGCPData[m_byStation][i].byData[j];
		}
		switch(pDesk->sUserData.m_UserGCPData[m_byStation][i].byType)
		{
		case ACTION_CHI://���ƶ���
			{
				m_byShunData[m_byShunNum] = pai[0];
				m_byShunNum++;
				m_byChiNum++;
				sprintf(str,"���Ʋ��ԣ�   ���ƣ�%d %d %d",pai[0],pai[1],pai[2]);
				OutputDebugString(str);
			}
			break;
		case ACTION_PENG://���ƶ���
			{
				m_byKeziData[m_byKeziNum] = pai[0];
				m_byKeziNum++;
				m_byPengNum++;
				sprintf(str,"���Ʋ��ԣ�   ���ƣ�%d %d %d   ������ = %d  ����%d ",pai[0],pai[1],pai[2],m_byKeziNum,m_byKeziData[m_byKeziNum]);
				OutputDebugString(str);
			}
			break;
		case AT_QUADRUPLET_CONCEALED://���ܶ���
			{
				m_byGangData[m_byGangNum][1] = pai[0];
				m_byGangData[m_byGangNum][0] = ACTION_AN_GANG;
				m_byGangNum++;
				sprintf(str,"���Ʋ��ԣ�   ���ܣ�%d  %d  %d %d",pai[0],pai[1],pai[2],pai[3]);
				OutputDebugString(str);
			}
			break;
		case AT_QUADRUPLET://���ܶ���
			{
				m_byGangData[m_byGangNum][1] = pai[0];
				m_byGangData[m_byGangNum][0] = ACTION_BU_GANG;
				m_byGangNum++;
				sprintf(str,"���Ʋ��ԣ�   ���ܣ�%d  %d  %d %d",pai[0],pai[1],pai[2],pai[3]);
				OutputDebugString(str);
			}
			break;
		case AT_QUADRUPLET_REVEALED://���ܶ���
			{
				m_byGangData[m_byGangNum][1] = pai[0];
				m_byGangData[m_byGangNum][0] = ACTION_MING_GANG;
				m_byGangNum++;
				sprintf(str,"���Ʋ��ԣ�  ���ܣ�%d  %d  %d %d",pai[0],pai[1],pai[2],pai[3]);
				OutputDebugString(str);
			}
			break;
		}
	}
	//str.Format("new:ƽ����� �������Ƽ�⣺ƽ������  ��������о����--------------------------");
	//OutputDebugString(str);
	sprintf(str,"���Ʋ��ԣ�CheckPingHuData ���� m_byGangNum=%d  m_byShunNum=%d m_byKeziNum=%d",m_byGangNum,m_byShunNum,m_byKeziNum);
	OutputDebugString(str);
}


/////////////////��ϸ�������ͼ��///////////////////////////////////////////////////////////////////////////////

/////////////////������ƽ��������ͼ��/////////////////////////////

//ƽ������4��˳�Ӽ�������������ɵĺ��ƣ��ߡ���������Ӱ��ƽ�� 
bool CheckHuPai::CheckIsPingHu()
{
	if(m_byKeziNum>0 || m_byGangNum>0)//�и��ƻ����
		return false;
	return true;
}
//�����
bool CheckHuPai::CheckTianHu()
{
	if(m_byStation != pDesk->sGameData.m_byNtStation || !m_bZimo)
	{
		return false;
	}
	if(pDesk->sUserData.m_bHaveOut[m_byStation] || pDesk->sUserData.GetGCPCount(m_byStation)>0)
	{
		return false;
	}
	return true;
}
//�غ���
bool CheckHuPai::CheckDiHu()
{
	if(m_byStation == pDesk->sGameData.m_byNtStation)
	{
		return false;
	}
	if(pDesk->sUserData.m_bHaveOut[m_byStation] || pDesk->sUserData.GetGCPCount(m_byStation)>0 || pDesk->sUserData.GetOutPaiCount(m_byStation)>0 || pDesk->sUserData.m_byNowOutStation != m_byStation)
	{
		return false;
	}
	return true;
}

//���ϻ�������ץ�����Ƴɺ���(����������)�������� 
bool CheckHuPai::CheckGangKai()
{
	if(m_byStation == pDesk->sUserData.m_byNowOutStation && pDesk->sGameData.m_bGangState[m_byStation])
	{
		return true;
	}
	return false;
}
//�ܺ��ڣ�
bool CheckHuPai::CheckGangHouPao()
{

	char strdug[500];
	sprintf(strdug,"�¼���CheckGangHouPao ��״̬ %d  ����λ��%d ����λ��%d",pDesk->sGameData.m_bGangState[pDesk->sUserData.m_byNowOutStation] ,m_byStation,pDesk->sUserData.m_byNowOutStation );
	OutputDebugString(strdug);

	if(m_byStation != pDesk->sUserData.m_byNowOutStation && pDesk->sGameData.m_bGangState[pDesk->sUserData.m_byNowOutStation])//���ڸ���״̬
	{
			OutputDebugString("�¼��� CheckGangHouPao �����ڸܺ���");
		return true;
	}
	return false;
}

//һ��ߣ���һ�ֻ�ɫ2����ͬ��˳����ɵ��� ,���������ƣ�
bool CheckHuPai::CheckYiBanGao()
{
	if(m_byShunNum>=2)
	{
		for(int i=0;i<m_byShunNum-1;++i)
		{
			for(int j=i+1;j<m_byShunNum;j++)
			{
				if(m_byShunData[i] == m_byShunData[j] && m_byShunData[i] !=255)
					return true;
			}
		}
	}
	return false;
}

//ϲ��꣺2�ֻ�ɫ2��������ͬ��˳��  ,���������ƣ�
bool CheckHuPai::CheckXiXiangFeng()
{
	BYTE shunzi[4],num=0,count=0;
	memset(shunzi,255,sizeof(shunzi));
	for(int i=0;i<4;++i)
	{
		shunzi[i] = m_byShunData[i];
	}
	if(m_byShunNum==4)
	{
		for(int i=0;i<m_byShunNum-1;++i)
		{
			for(int j=i+1;j<m_byShunNum;j++)
			{
				if(shunzi[i] == shunzi[j] && shunzi[i] !=0)
				{
					shunzi[i] = 0;
					shunzi[j] = 0;
					count++;
				}
			}
		}
		if(count>=2)
		{
			return true;
		}	
	}
	return false;
}

//������һ�ֻ�ɫ6�������ӵ������� 
bool CheckHuPai::CheckLianLiu()
{
	if(m_byShunNum>=2)
	{
		for(int i=0;i<m_byShunNum-1;++i)
		{
			for(int j=i+1;j<m_byShunNum;j++)
			{
				if(m_byShunData[i] == m_byShunData[j]+3 && m_byShunData[i] !=255 && CMjRef::CheckIsTongSe(m_byShunData[i],m_byShunData[j]))
				{
					return true;
				}
			}
		}
	}
	return false;
}

//���ٸ���һ�ֻ�ɫ�Ƶ�123��789����˳��  ,���������ƣ�
bool CheckHuPai::CheckLaoShaoFu()
{
	if(m_byShunNum>=2)
	{
		for(int i=0;i<m_byShunNum-1;++i)
		{
			for(int j=i+1;j<m_byShunNum;j++)
			{
				if(m_byShunData[i]%10 == 1 && m_byShunData[j]%10 == 9  && CMjRef::CheckIsTongSe(m_byShunData[i],m_byShunData[j]))
				{
					return true;
				}
				if(m_byShunData[i]%10 == 9 && m_byShunData[j]%10 == 1  && CMjRef::CheckIsTongSe(m_byShunData[i],m_byShunData[j]))
				{
					return true;
				}
			}
		}
	}
	return false;
}

//�۾ſ̣�3����ͬ��һ���������Ƽ�������ɵĿ���(���) 
bool CheckHuPai::CheckYaoJiuKe()
{
	for(int i=0;i<m_byKeziNum;++i)
	{
		if((m_byKeziData[i]%10 == 1 || m_byKeziData[i]%10 == 9 ) && m_byKeziData[i] < CMjEnum::MJ_TYPE_FD)
			return true;
	}
	for(int i=0;i<m_byGangNum;++i)
	{
		if((m_byGangData[i][1]%10 == 1 || m_byGangData[i][1]%10 == 9 ) && m_byGangData[i][1]<CMjEnum::MJ_TYPE_FD)
			return true;
	}
	return false;
}

//���ܣ��Լ��а��̣������˴����һ����ͬ���ƿ��ܣ����Լ�ץ��һ��������������ͬ���ƿ��� 
bool CheckHuPai::CheckMingGang()
{
	for(int i=0;i<m_byGangNum;++i)
	{
		if(m_byGangData[i][1] == ACTION_MING_GANG || m_byGangData[i][1] == ACTION_BU_GANG)
			return true;
	}
	return false;
}

//ȱһ�ţ�������ȱ��һ�ֻ�ɫ������ 
bool CheckHuPai::CheckQueYiMen()
{
	bool hua[4];
	BYTE num = 0;
	memset(hua,0,sizeof(hua));
	if(m_byJiang!=255)
	{
		hua[CMjRef::GetHuaSe(m_byJiang)] = true;
	}
	for(int i=0;i<m_byShunNum;++i)
	{
		if(m_byShunData[i] != 255 && m_byShunData[i]<CMjEnum::MJ_TYPE_FD)
		{
			hua[CMjRef::GetHuaSe(m_byShunData[i])] = true;
		}
	}
	for(int i=0;i<m_byKeziNum;++i)
	{
		if(m_byKeziData[i] != 255 && m_byKeziData[i]<CMjEnum::MJ_TYPE_FD)
		{
			hua[CMjRef::GetHuaSe(m_byKeziData[i])] = true;
		}
	}
	for(int i=0;i<m_byGangNum;++i)
	{
		if(m_byGangData[i][1] != 255 && m_byGangData[i][1]<CMjEnum::MJ_TYPE_FD)
		{
			hua[CMjRef::GetHuaSe(m_byGangData[i][1])] = true;
		}
	}
	for(int i=0;i<3;++i)
	{
		if(hua[i])
		{
			num++;
		}
	}
	if(num==2)
	{
		return true;
	}
	return false;
}

//���֣�������û�з硢���� 
bool CheckHuPai::CheckWuZi()
{
	for(int i=0;i<m_byKeziNum;++i)
	{
		if(m_byKeziData[i] != 255 && m_byKeziData[i]>=CMjEnum::MJ_TYPE_FD )
			return false;
	}
	for(int i=0;i<m_byGangNum;++i)
	{
		if(m_byGangData[i][1] != 255 && m_byGangData[i][1]>=CMjEnum::MJ_TYPE_FD )
			return false;
	}
	return true;
}

//���ţ�����123��3��789��7��1233��3��77879��7��Ϊ�š�(δ����������12345��3��56789��6������� )
bool CheckHuPai::CheckBianZhang()
{
	if(pDesk->sUserData.GetOutPaiCount(pDesk->sGameData.m_byNtStation)==0 && m_byChiNum == 0 && m_byPengNum == 0 && m_byGangNum == 0 )
	{//�������
		return false;
	}
	if(m_byLastPai >=CMjEnum::MJ_TYPE_FD || (m_byLastPai%10 != 3 && m_byLastPai%10 != 7))
	{//���ץ�����������ƣ����3,7���ƣ����ǽ���
		return false;
	}
	for(int i=0;i<hupaistruct.count;++i)
	{
		if(hupaistruct.byType[i] != TYPE_SHUN_ZI)
		{
			continue;
		}
		if(hupaistruct.data[i][2]%10 == 3 && hupaistruct.data[i][2] == m_byLastPai)
		{
			return true;
		}
		if(hupaistruct.data[i][0]%10 == 7 && hupaistruct.data[i][0] == m_byLastPai)
		{
			return true;
		}
	}
	return false;
}

//���ţ���2����֮����ơ�4556��5ҲΪ���š�δ����������45567��6���㿲�� 
bool CheckHuPai::CheckKanZhang()
{
	if(pDesk->sUserData.GetOutPaiCount(pDesk->sGameData.m_byNtStation)==0 && m_byChiNum == 0 && m_byPengNum == 0 && m_byGangNum == 0 )
	{//�������
		return false;
	}
	if(m_byLastPai >=CMjEnum::MJ_TYPE_FD )
	{//���ץ������������
		return false;
	}
	for(int i=0;i<hupaistruct.count;++i)
	{
		if(hupaistruct.byType[i] != TYPE_SHUN_ZI)
		{
			continue;
		}
		if(hupaistruct.data[i][1] == m_byLastPai)
		{
			return true;
		}
	}
	return false;
}

//���������������������ɺ� 
bool CheckHuPai::CheckDanDiaoJiang()
{
	if(pDesk->sUserData.GetOutPaiCount(pDesk->sGameData.m_byNtStation)==0 && m_byChiNum == 0 && m_byPengNum == 0 && m_byGangNum == 0 )
	{//�������
		return false;
	}
	for(int i=0;i<hupaistruct.count;++i)
	{
		if(hupaistruct.byType[i] == TYPE_JIANG_PAI || hupaistruct.byType[i] == TYPE_JINGDIAO_JIANG)
		{
			if(hupaistruct.data[i][0] == m_byLastPai)
			{
				return true;
			}
		}
	}
	return false;
}

//���̣����С�������3����ͬ������ɵĿ��� ,���ܲ��㣩
bool CheckHuPai::CheckJianKe()
{
	for(int i=0;i<m_byKeziNum;++i)
	{
		if(m_byKeziData[i] == CMjEnum::MJ_TYPE_ZHONG || m_byKeziData[i] == CMjEnum::MJ_TYPE_FA  || m_byKeziData[i] == CMjEnum::MJ_TYPE_BAI)
		{
			return true;
		}
	}
	for(int i=0;i<m_byGangNum;++i)
	{
		if(m_byGangData[i][1] == CMjEnum::MJ_TYPE_ZHONG || m_byGangData[i][1] == CMjEnum::MJ_TYPE_FA  || m_byGangData[i][1] == CMjEnum::MJ_TYPE_BAI)
		{
			return true;
		}
	}
	return false;
}

//Ȧ��̣���Ȧ����ͬ�ķ�� �����ܲ��㣩
bool CheckHuPai::CheckQuanFengKe()
{
	if(pDesk->sUserData.m_byQuanFeng == 255)
		return false;
	for(int i=0;i<m_byKeziNum;++i)
	{
		if(m_byKeziData[i] == pDesk->sUserData.m_byQuanFeng)
		{
			return true;
		}
	}
	for(int i=0;i<m_byGangNum;++i)
	{
		if(m_byGangData[i][1] == pDesk->sUserData.m_byQuanFeng)
		{
			return true;
		}
	}
	return false;
}

//�ŷ�̣��뱾�ŷ���ͬ�ķ�� ,���ܲ��㣩
bool CheckHuPai::CheckMenFengKe()
{

	return false;
}

//��ǰ�壺û�гԡ��������ܣ��ͱ��˴������ 
bool CheckHuPai::CheckMenQianQing()
{
	//�����齫û�в����ˣ�����Ҳ����ǰ��
// 	if(m_byStation == pDesk->sUserData.m_byNowOutStation)
// 	{
// 		return false;
// 	}
	if(m_byChiNum>0 || m_byPengNum>0)
	{
		return false;
	}
	for(int i=0;i<m_byGangNum;++i)
	{
		if(m_byGangData[i][0] != ACTION_AN_GANG)
		{
			return false;
		}
	}
	return true;
}

//�Ĺ�һ�� �����У���4����ͬ���ƹ���һ�ҵ�˳�����ӡ��ԡ�������(����������) 
bool CheckHuPai::CheckSiGuiYi()
{
	if(m_byStation == pDesk->sUserData.m_byNowOutStation)//����
	{
		for(int i=0;i<hupaistruct.count;++i)
		{
			if(hupaistruct.byType[i] == TYPE_JIANG_PAI || hupaistruct.byType[i] == TYPE_JINGDIAO_JIANG || hupaistruct.byType[i] == TYPE_AN_KE)
			{
				if(pDesk->sUserData.GetAHandPaiCount(m_byStation,hupaistruct.data[i][0]) == 4)
					return true;
			}
			else if(hupaistruct.byType[i] == TYPE_SHUN_ZI )
			{
				if(pDesk->sUserData.GetAHandPaiCount(m_byStation,hupaistruct.data[i][0]) == 4)
					return true;
				if(pDesk->sUserData.GetAHandPaiCount(m_byStation,hupaistruct.data[i][1]) == 4)
					return true;
				if(pDesk->sUserData.GetAHandPaiCount(m_byStation,hupaistruct.data[i][2]) == 4)
					return true;
			}
		}
	}
	else
	{
		for(int i=0;i<hupaistruct.count;++i)
		{
			if(hupaistruct.byType[i] == TYPE_JIANG_PAI || hupaistruct.byType[i] == TYPE_JINGDIAO_JIANG || hupaistruct.byType[i] == TYPE_AN_KE)
			{
				if(pDesk->sUserData.GetAHandPaiCount(m_byStation,hupaistruct.data[i][0]) == 4 
					|| (pDesk->sUserData.GetAHandPaiCount(m_byStation,hupaistruct.data[i][0]) == 3 && m_byLastPai == hupaistruct.data[i][0]))
					return true;
			}
			else if(hupaistruct.byType[i] == TYPE_SHUN_ZI )
			{
				if(pDesk->sUserData.GetAHandPaiCount(m_byStation,hupaistruct.data[i][0]) == 4
					|| (pDesk->sUserData.GetAHandPaiCount(m_byStation,hupaistruct.data[i][0]) == 3 && m_byLastPai == hupaistruct.data[i][0]))
					return true;
				if(pDesk->sUserData.GetAHandPaiCount(m_byStation,hupaistruct.data[i][1]) == 4
					|| (pDesk->sUserData.GetAHandPaiCount(m_byStation,hupaistruct.data[i][1]) == 3 && m_byLastPai == hupaistruct.data[i][1]))
					return true;
				if(pDesk->sUserData.GetAHandPaiCount(m_byStation,hupaistruct.data[i][2]) == 4
					|| (pDesk->sUserData.GetAHandPaiCount(m_byStation,hupaistruct.data[i][2]) == 3 && m_byLastPai == hupaistruct.data[i][2]))
					return true;
			}
		}
	}
	return false;
}

//˫ͬ�̣� 2��������ͬ�Ŀ��� ,�����������ƣ�
bool CheckHuPai::CheckShuangTongKe()
{
	if(m_byKeziNum<2)
	{
		return false;
	}
	//CString str="";
	BYTE num[9];
	memset(num,0,sizeof(num));
	for(int i=0;i<m_byKeziNum;++i)
	{
		if(m_byKeziData[i]>=CMjEnum::MJ_TYPE_FD)
			continue;
		num[m_byKeziData[i]%10-1]++;
		//str.Format("���Ʋ��ԣ����� %d pai=%d",m_byKeziData[i]%10,m_byKeziData[i]);
		//OutputDebugString(str);
		if(num[m_byKeziData[i]%10-1]>=2)
		{
			return true;
		}
	}
	return false;
}

//˫���̣�2������ ,����˵��ڵ���,�������������ƣ�
bool CheckHuPai::CheckShuangAnGang()
{
	if((m_byKeziNum - m_byPengNum)==2)
		return true;
	return false;
}

//���ܣ���ץ4����ͬ���ƿ��� 
bool CheckHuPai::CheckAnGang()
{
	for(int i=0;i<m_byGangNum;++i)
	{
		if(m_byGangData[i][0] == ACTION_AN_GANG)
		{
			return true;
		}
	}
	return false;
}

//���ۣ�������û��һ���ż����� 
bool CheckHuPai::CheckDuanYao()
{
	for(int i=0;i<HAND_CARD_NUM;i++)
	{
		if(m_byArHandPai[i] == 255)
			continue;
		if(m_byArHandPai[i]>=CMjEnum::MJ_TYPE_FD || m_byArHandPai[i]%10==1 || m_byArHandPai[i]==9)
			return false;
	}
	for(int i=0;i<5;++i)
	{
		if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byType == 255)
			continue;
		if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byData[0]>=CMjEnum::MJ_TYPE_FD || pDesk->sUserData.m_UserGCPData[m_byStation][i].byData[0]%10==1 || pDesk->sUserData.m_UserGCPData[m_byStation][i].byData[0]%10==9)
			return false;
	}
	return true;
}

//ȫ���ۣ�����ʱ��ÿ���ơ����ƶ������� 
bool CheckHuPai::CheckQuanDaiYao()
{
	for(int i=0;i<hupaistruct.count;++i)
	{
		if(hupaistruct.byType[i] == TYPE_JIANG_PAI || hupaistruct.byType[i] == TYPE_JINGDIAO_JIANG || hupaistruct.byType[i] == TYPE_AN_KE)
		{
			if(hupaistruct.data[i][0]<CMjEnum::MJ_TYPE_FD && hupaistruct.data[i][0]%10!=1 && hupaistruct.data[i][0]%10!=9)
				return false;
		}
		else if(hupaistruct.byType[i] == TYPE_SHUN_ZI )
		{
			bool jiu = false;
			for(int j=0;j<3;j++)
			{
				if(hupaistruct.data[i][j] %10 == 1 || hupaistruct.data[i][j] %10 == 9)
				{
					jiu = true;
				}
			}
			if(!jiu)
			{
				return false;
			}
		}
	}
	for(int i=0;i<5;++i)
	{
		if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byType == 255)
			continue;
		if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byData[0]>=CMjEnum::MJ_TYPE_FD)
			continue;
		bool jiu = false;
		for(int j=0;j<3;j++)
		{
			if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byData[j] %10 == 1 || pDesk->sUserData.m_UserGCPData[m_byStation][i].byData[j] %10 == 9)
			{
				jiu = true;
			}
		}
		if(!jiu)
		{
			return false;
		}
	}
	return true;
}

//�����ˣ�4���Ƽ�����û�г��ơ�����(��������)���������� 
bool CheckHuPai::CheckBuQiuRen()
{
	CString str="";
	str.Format("���Ʋ��ԣ������� m_byGangNum=%d",m_byGangNum);
	OutputDebugString(str);
	if(m_byStation != pDesk->sUserData.m_byNowOutStation)//����
	{
		return false;
	}
	for(int i=0;i<m_byGangNum;++i)
	{
		if(m_byGangData[i][0] != ACTION_AN_GANG)
		{
			return false;
		}
	}

	return true;
}

//˫���ܣ�2������ 
bool CheckHuPai::CheckShuangMingGang()
{
	BYTE num = 0;
	for(int i=0;i<m_byGangNum;++i)
	{
		if(m_byGangData[i][0] != ACTION_AN_GANG)
		{
			num++;
		}
	}
	if(num == 2)
	{
		return true;
	}
	return false;
}

//�;��ţ����Ƴء�������������3������ʣ�ĵ�4����(���ܺͲ��ƺ;���) 
bool CheckHuPai::CheckHuJueZhang()
{

	return false;
}

//�����ͣ� ��4������(���)��������ɵĺ��� 
bool CheckHuPai::CheckPengPengHu()
{
	if(m_byShunNum == 0)//˳�Ӹ���Ϊ0
	{
		OutputDebugString("���Ʋ��ԣ������� �ɹ�");
		return true;
	}
	OutputDebugString("���Ʋ��ԣ������� ʧ��");
	return false;
}

//һɫ�Ƽ�⣨������ƺͳ������ƣ����ﶼ���ã���0����һɫ�ƣ�1��һɫ��2��һɫ
int CheckHuPai::CheckYiSe()
{
	bool zi = false;
	BYTE type = 255,pai = 255;
	for(int i=0;i<HAND_CARD_NUM;i++)
	{
		if(m_byArHandPai[i] == 255)
			continue;
		pai = m_byArHandPai[i];
		if(CMjRef::GetHuaSe(pai) == 3)
		{
			zi = true;
			continue;
		}
		if(type == 255)
		{
			type = CMjRef::GetHuaSe(pai);
		}
		if(type != CMjRef::GetHuaSe(pai))
		{
			return 0;
		}
	}
	for(int i=0;i<5;++i)
	{
		if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byType == 255)
			continue;
		pai = pDesk->sUserData.m_UserGCPData[m_byStation][i].byData[0];
		if(CMjRef::GetHuaSe(pai) == 3)
		{
			zi = true;
			continue;
		}
		if(type == 255)
		{
			type = CMjRef::GetHuaSe(pai);
		}
		if(type != CMjRef::GetHuaSe(pai))
		{
			return 0;
		}
	}
	if(type == 255)//ȫ���ֲ�������һɫ
		return 0;

	if(zi)
	{
		return 1;
	}
	return 2;
}



//��ɫ�����ߣ� 3�ֻ�ɫ3�����ε���һλ������˳�ӣ����������ƣ�
bool CheckHuPai::CheckSanSeSanBuGao()
{
	if(m_byShunNum<3)
	{
		return false;
	}
	bool shun[3][9];
	memset(shun,0,sizeof(shun));
	MaoPaoSort(m_byShunData,4,false);
	for(int i=0;i<4;++i)
	{
		if(m_byShunData[i]==255)
			continue;
		shun[CMjRef::GetHuaSe(m_byShunData[i])][m_byShunData[i]%10-1] = true;
	}
	for(int i=0;i<7;++i)
	{
		if(shun[0][i] && shun[1][i+1] && shun[2][i+2]
		|| shun[1][i] && shun[2][i+1] && shun[0][i+2]
		|| shun[2][i] && shun[1][i+1] && shun[0][i+2]
		)
		{
			return true;
		}
	}

	return false;
}

//�����룺����ʱ3�������ơ��硢������ȫ 
bool CheckHuPai::CheckWuMenQi()
{
	bool wbt[3],feng=false,jian=false;
	memset(wbt,0,sizeof(wbt));
	BYTE pai=255;

	for(int i=0;i<hupaistruct.count;++i)
	{
		if(hupaistruct.data[i][0]==255)
			continue;
		pai = hupaistruct.data[i][0];
		if(CMjRef::GetHuaSe(pai)<3)
		{
			wbt[CMjRef::GetHuaSe(pai)] = true;
		}
		else
		{
			if(pai >= CMjEnum::MJ_TYPE_ZHONG)
			{
				jian = true;
			}
			else if(pai>=CMjEnum::MJ_TYPE_FD)
			{
				feng = true;
			}
		}
	}
	for(int i=0;i<5;++i)
	{
		if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byType == 255)
			continue;
		pai = pDesk->sUserData.m_UserGCPData[m_byStation][i].byData[0];
		if(CMjRef::GetHuaSe(pai)<3)
		{
			wbt[CMjRef::GetHuaSe(pai)] = true;
		}
		else
		{
			if(pai>=CMjEnum::MJ_TYPE_ZHONG)
			{
				jian = true;
			}
			else if(pai>=CMjEnum::MJ_TYPE_FD)
			{
				feng = true;
			}
		}
	}

	if(wbt[0] && wbt[1] && wbt[2] && feng && jian)
	{
		return true;
	}
	return false;
}

//ȫ���ˣ�ȫ�����ơ����ơ����������������ƺ��ơ����Ƶ��� 
bool CheckHuPai::CheckQuanQiuRen()
{
	if(m_byStation == pDesk->sUserData.m_byNowOutStation)//����
	{
		return false;
	}
	for(int i=0;i<hupaistruct.count;++i)
	{
		if(hupaistruct.byType[i] == TYPE_SHUN_ZI || hupaistruct.byType[i] == TYPE_AN_KE)
		{
			return false;
		}
	}
	for(int i=0;i<m_byGangNum;++i)
	{
		if(m_byGangData[i][0] == ACTION_AN_GANG)
		{
			return false;
		}
	}
	return true;
}

//˫���ܣ� 2������ 
bool CheckHuPai::CheckShuangAnKe()
{
	BYTE num = 0;
	for(int i=0;i<m_byGangNum;++i)
	{
		if(m_byGangData[i][0] == ACTION_AN_GANG)
		{
			num++;
		}
	}
	if(num == 2)
	{
		return true;
	}
	return false;
}

//˫���̣�2������(���) 
bool CheckHuPai::CheckShuangJianKe()
{
	BYTE num = 0;
	for(int i=0;i<m_byGangNum;++i)
	{
		if(m_byGangData[i][1] >= CMjEnum::MJ_TYPE_ZHONG && m_byGangData[i][1] <= CMjEnum::MJ_TYPE_BAI)
		{
			num++;
		}
	}
	for(int i=0;i<m_byKeziNum;++i)
	{
		if(m_byKeziData[i]>= CMjEnum::MJ_TYPE_ZHONG && m_byKeziData[i] <= CMjEnum::MJ_TYPE_BAI)
		{
			num++;
		}
	}
	return false;
}

//������ 3�ֻ�ɫ��3��˳�����ӳ�1-9�������� ,�����������ƣ�
bool CheckHuPai::CheckHuaLong()
{
	bool shun[3][9];
	memset(shun,0,sizeof(shun));
	for(int i=0;i<m_byShunNum;++i)
	{
		if(m_byShunData[i]>=CMjEnum::MJ_TYPE_FD)
			continue;
		shun[CMjRef::GetHuaSe(m_byShunData[i])][m_byShunData[i]%10-1] = true;
	}
	if(shun[0][1] && shun[1][4] && shun[2][7] 
	||shun[1][1] && shun[2][4] && shun[0][7] 
	||shun[2][1] && shun[0][4] && shun[1][7] )
	{
		return true;
	}
	return false;
}

//�Ʋ����� ������ͼ��û���������������ɵĺ��ƣ�����1234589����245689�����װ塣����ȱһ�� 
bool CheckHuPai::CheckTuiBuDao()
{
	BYTE pai = 255;
	for(int i=0;i<hupaistruct.count;++i)
	{			
		pai = hupaistruct.data[i][0];
		if(pai<=CMjEnum::MJ_TYPE_W9 || pai>=CMjEnum::MJ_TYPE_FD && pai!=CMjEnum::MJ_TYPE_BAI)
		{
			return false;
		}	
		if(hupaistruct.byType[i] == TYPE_SHUN_ZI)
		{
			if(pai>CMjEnum::MJ_TYPE_B3 && pai!=CMjEnum::MJ_TYPE_T4)
			{
				return false;
			}
		}
		else
		{
			if(pai==CMjEnum::MJ_TYPE_B6 || pai==CMjEnum::MJ_TYPE_B7 || pai==CMjEnum::MJ_TYPE_T1 || pai==CMjEnum::MJ_TYPE_T3 || pai==CMjEnum::MJ_TYPE_T7)
			{
				return false;
			}
		}
	}
	for(int i=0;i<5;++i)
	{
		if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byType == 255)
			continue;
		pai = pDesk->sUserData.m_UserGCPData[m_byStation][i].byData[0];
		if(pai<=CMjEnum::MJ_TYPE_W9 || pai>=CMjEnum::MJ_TYPE_FD && pai!=CMjEnum::MJ_TYPE_BAI)
		{
			return false;
		}
		if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byType == ACTION_CHI)
		{
			if(pai>CMjEnum::MJ_TYPE_B3 && pai!=CMjEnum::MJ_TYPE_T4)
			{
				return false;
			}
		}
		else
		{
			if(pai==CMjEnum::MJ_TYPE_B6 || pai==CMjEnum::MJ_TYPE_B7 || pai==CMjEnum::MJ_TYPE_T1 || pai==CMjEnum::MJ_TYPE_T3 || pai==CMjEnum::MJ_TYPE_T7)
			{
				return false;
			}
		}
	}
	return true;
}

//��ɫ��ͬ˳������ʱ����3�ֻ�ɫ3��������ͬ��˳�� �����������ƣ�
bool CheckHuPai::CheckSanSeSanTongShun()
{
	bool shun[3][9];
	memset(shun,0,sizeof(shun));
	for(int i=0;i<m_byShunNum;++i)
	{
		if(m_byShunData[i]>=CMjEnum::MJ_TYPE_FD)
			continue;
		shun[CMjRef::GetHuaSe(m_byShunData[i])][m_byShunData[i]%10-1]=true;
	}
	for(int i=0;i<9;++i)
	{
		if(shun[0][i] && shun[1][i] && shun[2][i])
		{
			return true;
		}
	}
	return false;
}

//��ɫ���ڸߣ�����ʱ����3�ֻ�ɫ3�����ε���һλ���Ŀ��ӣ����������ƣ�
bool CheckHuPai::CheckSanSeSanJieGao()
{
	bool shun[3][9];
	memset(shun,0,sizeof(shun));
	for(int i=0;i<m_byShunNum;++i)
	{
		if(m_byShunData[i]>=CMjEnum::MJ_TYPE_FD)
			continue;
		shun[CMjRef::GetHuaSe(m_byShunData[i])][m_byShunData[i]%10-1]=true;
	}
	for(int i=0;i<7;++i)
	{
		if(shun[0][i] && shun[1][i+1] && shun[2][i+2]
		||shun[1][i] && shun[2][i+1] && shun[0][i+2]
		||shun[2][i] && shun[1][i+1] && shun[0][i+2])
		{
			return true;
		}
	}
	return false;
}

//�޷��ͣ����ƺ��������κη��ַ�(���Ʋ���������) 
bool CheckHuPai::CheckWuFanHe()
{
	
	return false;
}

//���ֻش���������ǽ�����һ���ƺ��ơ��������� 
bool CheckHuPai::CheckMiaoShouHuiChun()
{
	if(m_byStation == pDesk->sUserData.m_byNowOutStation && pDesk->sUserData.m_MenPai.GetMenPaiNum()==0)//����
	{
		return true;
	}
	return false;
}

//�������£��ʹ�������һ���� 
bool CheckHuPai::CheckHaiDiLaoYue()
{
	if(m_byStation != pDesk->sUserData.m_byNowOutStation && pDesk->sUserData.m_MenPai.GetMenPaiNum()==0)//����
	{
		return true;
	}
	return false;
}

//���ܺͣ��ͱ�����ץ�����ܵ��ơ����ƺ;���  
bool CheckHuPai::CheckQiangGangHe()
{
	if(m_byStation != pDesk->sUserData.m_byNowOutStation && pDesk->sGameData.T_GangPai.byUser!=255)
	{
		return true;
	}
	return false;
}

//�����壺��������6-9��˳�ӡ����ӡ�������ɵĺ��ơ��������� 
bool CheckHuPai::CheckDaYuWu()
{
	BYTE pai = 255;
	for(int i=0;i<hupaistruct.count;++i)
	{			
		pai = hupaistruct.data[i][0];
		if(pai>=CMjEnum::MJ_TYPE_FD)
		{
			return false;
		}	
		if(pai%10 < 6 )
		{
			return false;
		}
	}
	for(int i=0;i<5;++i)
	{
		if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byType == 255)
			continue;
		pai = pDesk->sUserData.m_UserGCPData[m_byStation][i].byData[0];
		if(pai>=CMjEnum::MJ_TYPE_FD)
		{
			return false;
		}	
		if(pai%10 < 6)
		{
			return false;
		}
	}
	return true;
}

//С���壺��������1-4��˳�ӡ����ӡ�������ɵĺ��ơ��������� 
bool CheckHuPai::CheckXiaoYuWu()	
{
	BYTE pai = 255;
	for(int i=0;i<hupaistruct.count;++i)
	{			
		pai = hupaistruct.data[i][0];
		if(pai>=CMjEnum::MJ_TYPE_FD)
		{
			return false;
		}	
		if(hupaistruct.byType[i] == TYPE_SHUN_ZI)
		{
			if(pai%10 > 2 )
			{
				return false;
			}
		}
		else
		{
			if(pai%10 > 4)
			{
				return false;
			}
		}
	}
	for(int i=0;i<5;++i)
	{
		if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byType == 255)
			continue;
		pai = pDesk->sUserData.m_UserGCPData[m_byStation][i].byData[0];
		if(pai>=CMjEnum::MJ_TYPE_FD)
		{
			return false;
		}	
		if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byType == ACTION_CHI)
		{
			if(pai%10 > 2 )
			{
				return false;
			}
		}
		else
		{
			if(pai%10 > 4)
			{
				return false;
			}
		}
	}
	return true;
}

//����̣�3����� ��(����������)
bool CheckHuPai::CheckSanFengKe()
{
	BYTE num = 0;
	for(int i=0;i<m_byKeziNum;++i)
	{
		if(m_byKeziData[i]>=CMjEnum::MJ_TYPE_FD && m_byKeziData[i]<=CMjEnum::MJ_TYPE_FB)
		{
			num++;
		}
	}
	for(int i=0;i<m_byGangNum;++i)
	{
		if(m_byGangData[i][1]>=CMjEnum::MJ_TYPE_FD && m_byGangData[i][1]<=CMjEnum::MJ_TYPE_FB)
		{
			num++;
		}
	}
	if(num==3)
	{
		return true;
	}
	return false;
}

//����������ʱ����һ�ֻ�ɫ1-9�����ӵ������� �����������ƣ�
bool CheckHuPai::CheckQingLong()
{ 
	if(m_byShunNum<3)
	{
		return false;
	}
	MaoPaoSort(m_byShunData,4,false);
	if(m_byShunData[0]==m_byShunData[1]-3==m_byShunData[2]-6 && m_byShunData[0]%10==1)
	{
		return true;
	}
	return false;
}

//��ɫ˫���᣺2�ֻ�ɫ2�����ٸ�����һ�ֻ�ɫ5�����ĺ��ơ�����ϲ��ꡢ���ٸ������֡�ƽ�� �����������ƣ�
bool CheckHuPai::CheckSanSeShuangLongHui()
{
	if(m_byShunNum<4)
	{
		return false;
	}
	bool shun[3][9];
	memset(shun,0,sizeof(shun));
	for(int i=0;i<m_byShunNum;++i)
	{
		if(m_byShunData[i]>=CMjEnum::MJ_TYPE_FD)
			continue;
		shun[CMjRef::GetHuaSe(m_byShunData[i])][m_byShunData[i]%10-1]=true;
	}
	if(shun[0][0] && shun[0][6] && shun[1][0] && shun[1][6] && m_byJiang == CMjEnum::MJ_TYPE_T5
	|| shun[0][0] && shun[0][6] && shun[2][0] && shun[2][6] && m_byJiang == CMjEnum::MJ_TYPE_B5
	|| shun[2][0] && shun[2][6] && shun[1][0] && shun[1][6] && m_byJiang == CMjEnum::MJ_TYPE_W5)
	{
		return true;
	}
	return false;
}

//һɫ�����ߣ� ����ʱ����һ�ֻ�ɫ3�����ε���һλ�����ε�����λ���ֵ�˳�� �����������ƣ�
bool CheckHuPai::CheckYiSeSanBuGao()
{
	if(m_byShunNum<3)
	{
		return false;
	}
	bool shun[3][9];
	memset(shun,0,sizeof(shun));
	for(int i=0;i<m_byShunNum;++i)
	{
		if(m_byShunData[i]>=CMjEnum::MJ_TYPE_FD)
			continue;
		shun[CMjRef::GetHuaSe(m_byShunData[i])][m_byShunData[i]%10-1]=true;
	}
	for(int i=0;i<7;++i)
	{
		if(shun[0][i] && shun[0][i+1] && shun[0][i+2] 
		|| shun[1][i] && shun[1][i+1] && shun[1][i+2]
		|| shun[2][i] && shun[2][i+1] && shun[2][i+2])
		{
			return true;
		}
	}
	for(int i=0;i<5;++i)
	{
		if(shun[0][i] && shun[0][i+2] && shun[0][i+4] 
		|| shun[1][i] && shun[1][i+2] && shun[1][i+4]
		|| shun[2][i] && shun[2][i+2] && shun[2][i+4])
		{
			return true;
		}
	}
	return false;
}

//ȫ���壺ÿ���Ƽ����Ʊ�����5�������ơ����ƶ��� 
bool CheckHuPai::CheckQuanDaiWu()
{
	BYTE pai = 255,type = 255;
	bool zi = false;
	for(int i=0;i<hupaistruct.count;++i)
	{	
		pai = hupaistruct.data[i][0];
		if(CMjRef::GetHuaSe(pai)==3)
		{
			return false;
		}
		if(hupaistruct.byType[i] == TYPE_SHUN_ZI)
		{
			if(pai%10>7 || pai%10<3)
			{
				return false;
			}
		}
		else 
		{
			if(pai%10 != 5)
			{
				return false;
			}
		}
	}
	for(int i=0;i<5;++i)
	{
		if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byType == 255)
			continue;
		pai = pDesk->sUserData.m_UserGCPData[m_byStation][i].byData[0];
		if(CMjRef::GetHuaSe(pai)==3)
		{
			return false;
		}
		if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byType == ACTION_CHI)
		{
			if(pai%10>7 || pai%10<3)
			{
				return false;
			}
		}
		else 
		{
			if(pai%10 != 5)
			{
				return false;
			}
		}
	}
	return true;
}

//��ͬ�̣�3��������ͬ�Ŀ���(��) 
bool CheckHuPai::CheckSanTongKe()
{
	BYTE num[9];
	memset(num,0,sizeof(num));
	for(int i=0;i<m_byKeziNum;++i)
	{
		if(m_byKeziData[i]>=CMjEnum::MJ_TYPE_FD)
		{
			continue;
		}
		num[m_byKeziData[i]%10-1]++;
	}
	for(int i=0;i<m_byGangNum;++i)
	{
		if(m_byGangData[i][1]>=CMjEnum::MJ_TYPE_FD)
		{
			continue;
		}
		num[m_byGangData[i][1]%10-1]++;
	}
	for(int i=0;i<9;++i)
	{
		if(num[i]==3)
		{
			return true;
		}
	}
	return false;
}

//�����̣� 3������ 
bool CheckHuPai::CheckSanAnKe()	
{
	BYTE num = 0;
	for(int i=0;i<hupaistruct.count;++i)
	{	
		if(hupaistruct.byType[i] == TYPE_AN_KE)
		{
			num++;
		}
	}
	if(num == 3)
	{
		return true;
	}
	return false;
}

//ȫ˫�̣� ��2��4��6��8�����ƵĿ��ˡ�������ɵĺ��ơ������������ƣ������������͡����� 
bool CheckHuPai::CheckQuanShuangKe()
{
	if(m_byShunNum>0)
	{
		return false;
	}
	for(int i=0;i<m_byKeziNum;++i)
	{
		if(m_byKeziData[i]>=CMjEnum::MJ_TYPE_FD || m_byKeziData[i]%10!=0)
		{
			return false;
		}	
	}
	if(m_byJiang>=CMjEnum::MJ_TYPE_FD || m_byJiang%10!=0)
	{
		return false;
	}
	return true;
}

//��һɫ�� ��һ�ֻ�ɫ����������ɺ͸��ơ������� 
bool CheckHuPai::CheckQingYiSe()
{
	return CheckYiSe()==2;
}

//��һɫ
bool CheckHuPai::CheckHunYiSe()
{
	return CheckYiSe()==1;
}

//һɫ��ͬ˳������ʱ��һ�ֻ�ɫ3��������ͬ��˳�ˡ�����һɫ���ڸ� �����������ƣ�
bool CheckHuPai::CheckYiSeSanTongShun()
{
	if(m_byShunNum<3)
	{
		return false;
	}
	BYTE num[3][9];
	memset(num,0,sizeof(num));
	for(int i=0;i<m_byShunNum;++i)
	{
		if(m_byShunData[i]>=CMjEnum::MJ_TYPE_FD)
			continue;
		num[CMjRef::GetHuaSe(m_byShunData[i])][m_byShunData[i]%10-1]++;
	}
	for(int i=0;i<7;++i)
	{
		if(num[0][i]==3 || num[1][i]==3  || num[2][i]==3)
		{
			return true;
		}
	}
	return false;
}

//һɫ���ڸߣ�����ʱ��һ�ֻ�ɫ3�����ε���һλ���ֵĿ��ӡ�����һɫ��ͬ˳ �����������ƣ�
bool CheckHuPai::CheckYiSeSanJieGao()
{
	if(m_byKeziNum<3)
	{
		return false;
	}
	bool kezi[3][9];
	memset(kezi,0,sizeof(kezi));
	for(int i=0;i<m_byKeziNum;++i)
	{
		if(m_byKeziData[i]>=CMjEnum::MJ_TYPE_FD)
			continue;
		kezi[CMjRef::GetHuaSe(m_byKeziData[i])][m_byKeziData[i]%10-1]=true;
	}
	for(int i=0;i<m_byGangNum;++i)
	{
		if(m_byGangData[i][1]>=CMjEnum::MJ_TYPE_FD)
			continue;
		kezi[CMjRef::GetHuaSe(m_byGangData[i][1])][m_byGangData[i][1]%10-1]=true;
	}
	for(int i=0;i<7;++i)
	{
		if(kezi[0][i] && kezi[0][i+1] && kezi[0][i+2] 
		|| kezi[1][i] && kezi[1][i+1] && kezi[1][i+2]
		|| kezi[2][i] && kezi[2][i+1] && kezi[2][i+2])
		{
			return true;
		}
	}
	return false;
}

//ȫ����������789��ɵ�˳�ˡ�����(��)�����Ƶĺ��ơ��������� 
bool CheckHuPai::CheckQuanDa()
{
	BYTE pai = 255;
	for(int i=0;i<hupaistruct.count;++i)
	{			
		pai = hupaistruct.data[i][0];
		if(pai>=CMjEnum::MJ_TYPE_FD)
		{
			return false;
		}	
		if(pai%10 < 6)
		{
			return false;
		}
	}
	for(int i=0;i<5;++i)
	{
		if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byType == 255)
			continue;
		pai = pDesk->sUserData.m_UserGCPData[m_byStation][i].byData[0];
		if(pai>=CMjEnum::MJ_TYPE_FD)
		{
			return false;
		}	
		if(pai%10 < 6)
		{
			return false;
		}
	}
	return true;
}

//ȫ�У� ��������456��ɵ�˳�ӡ�����(��)�����Ƶĺ��ơ����ƶ��� 
bool CheckHuPai::CheckQuanZhong()	
{
	BYTE pai = 255;
	for(int i=0;i<hupaistruct.count;++i)
	{			
		pai = hupaistruct.data[i][0];
		if(pai>=CMjEnum::MJ_TYPE_FD)
		{
			return false;
		}	
		if(hupaistruct.byType[i] == TYPE_SHUN_ZI)
		{
			if(pai%10 != 4 )
			{
				return false;
			}
		}
		else
		{
			if(pai%10 > 6 ||  pai%10 < 4)
			{
				return false;
			}
		}
	}
	for(int i=0;i<5;++i)
	{
		if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byType == 255)
			continue;
		pai = pDesk->sUserData.m_UserGCPData[m_byStation][i].byData[0];
		if(pai>=CMjEnum::MJ_TYPE_FD)
		{
			return false;
		}	
		if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byType == ACTION_CHI)
		{
			if(pai%10 != 4 )
			{
				return false;
			}
		}
		else
		{
			if(pai%10 > 6 ||  pai%10 < 4)
			{
				return false;
			}
		}
	}
	return true;
}

//ȫС����������123��ɵ�˳�ӡ�����(��)���Ƶĵĺ��ơ��������� 
bool CheckHuPai::CheckQuanXiao()
{
	BYTE pai = 255;
	for(int i=0;i<hupaistruct.count;++i)
	{			
		pai = hupaistruct.data[i][0];
		if(pai>=CMjEnum::MJ_TYPE_FD)
		{
			return false;
		}	
		if(hupaistruct.byType[i] == TYPE_SHUN_ZI)
		{
			if(pai%10 >1 )
			{
				return false;
			}
		}
		else
		{
			if(pai%10 >3 )
			{
				return false;
			}
		}
	}
	for(int i=0;i<5;++i)
	{
		if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byType == 255)
			continue;
		pai = pDesk->sUserData.m_UserGCPData[m_byStation][i].byData[0];
		if(pai>=CMjEnum::MJ_TYPE_FD)
		{
			return false;
		}	
		if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byType == ACTION_CHI)
		{
			if(pai%10 >1 )
			{
				return false;
			}
		}
		else
		{
			if(pai%10 >3 )
			{
				return false;
			}
		}
	}
	return true;
}

//һɫ�Ĳ��ߣ� һ�ֻ�ɫ4�����ε���һλ�������ε�����λ����˳�� �����������ƣ�
bool CheckHuPai::CheckYiSeSiBuGao()	
{
	if(m_byShunNum<4)
	{
		return false;
	}
	bool shun[3][9];
	memset(shun,0,sizeof(shun));
	for(int i=0;i<m_byShunNum;++i)
	{
		if(m_byShunData[i]>=CMjEnum::MJ_TYPE_FD)
			continue;
		shun[CMjRef::GetHuaSe(m_byShunData[i])][m_byShunData[i]%10-1]=true;
	}
	for(int i=0;i<6;++i)
	{
		if(shun[0][i] && shun[0][i+1]  && shun[0][i+2] && shun[0][i+3]
		|| shun[1][i] && shun[1][i+1]  && shun[1][i+2] && shun[1][i+3]
		|| shun[2][i] && shun[0][i+1]  && shun[2][i+2] && shun[2][i+3] )
		{
			return true;
		}
	}
	for(int i=0;i<3;++i)
	{
		if(shun[0][i] && shun[0][i+2]  && shun[0][i+4] && shun[0][i+6]
		|| shun[1][i] && shun[1][i+2]  && shun[1][i+4] && shun[1][i+6]
		|| shun[2][i] && shun[0][i+2]  && shun[2][i+4] && shun[2][i+6] )
		{
			return true;
		}
	}
	return false;
}

//���ܣ�3���� 
bool CheckHuPai::CheckSanGang()
{
	if(m_byGangNum==3)
	{
		return true;
	}
	return false;
}

//���۾ţ������ƺ�������һ���ŵĿ����ý�����ɵĺ��ơ����������� 
bool CheckHuPai::CheckHunYaoJiu()
{
	if(m_byShunNum>0)
	{
		return false;
	}
	BYTE pai = 255,type = 255;
	bool zi = false;
	for(int i=0;i<hupaistruct.count;++i)
	{	
		pai = hupaistruct.data[i][0];
		if(CMjRef::GetHuaSe(pai)==3)
		{
			zi = true;
			continue;
		}
		if(pai%10 != 1 && pai%10 != 9)
		{
			return false;
		}
		if(type == 255)
		{
			type = CMjRef::GetHuaSe(pai);
		}
		if(type != CMjRef::GetHuaSe(pai))
		{
			return false;
		}
	}
	for(int i=0;i<5;++i)
	{
		if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byType == 255)
			continue;
		pai = pDesk->sUserData.m_UserGCPData[m_byStation][i].byData[0];
		if(CMjRef::GetHuaSe(pai)==3)
		{
			zi = true;
			continue;
		}
		if(pai%10 != 1 && pai%10 != 9)
		{
			return false;
		}
		if(type == 255)
		{
			type = CMjRef::GetHuaSe(pai);
		}
		if(type != CMjRef::GetHuaSe(pai))
		{
			return false;
		}
	}
	if(zi)
	{
		return true;
	}
	return false;
}

//һɫ��ͬ˳��һ�ֻ�ɫ4��������ͬ��˳�ӣ�����һɫ���ڸߡ�һ��ߡ��Ĺ�һ �����������ƣ�
bool CheckHuPai::CheckYiSeSiTongShun()
{
	if(m_byShunNum<4)
	{
		return false;
	}
	BYTE num[3][9];
	memset(num,0,sizeof(num));
	for(int i=0;i<m_byShunNum;++i)
	{
		if(m_byShunData[i]>=CMjEnum::MJ_TYPE_FD)
			continue;
		num[CMjRef::GetHuaSe(m_byShunData[i])][m_byShunData[i]%10-1]++;
	}
	for(int i=0;i<7;++i)
	{
		if(num[0][i]==4 || num[1][i]==4  || num[2][i]==4)
		{
			return true;
		}
	}
	return false;
}

//һɫ�Ľڸߣ�һ�ֻ�ɫ4�����ε���һλ���Ŀ��Ӳ���һɫ��ͬ˳�������� �����������ƣ�
bool CheckHuPai::CheckYiSeSiJieGao()
{
	if((m_byKeziNum + m_byGangNum)<4)
	{
		return false;
	}
	bool kezi[3][9];
	memset(kezi,0,sizeof(kezi));
	for(int i=0;i<m_byKeziNum;++i)
	{
		if(m_byKeziData[i]>=CMjEnum::MJ_TYPE_FD)
			continue;
		kezi[CMjRef::GetHuaSe(m_byKeziData[i])][m_byKeziData[i]%10-1]=true;
	}
	for(int i=0;i<m_byGangNum;++i)
	{
		if(m_byGangData[i][1]>=CMjEnum::MJ_TYPE_FD)
			continue;
		kezi[CMjRef::GetHuaSe(m_byGangData[i][1])][m_byGangData[i][1]%10-1]=true;
	}
	for(int i=0;i<6;++i)
	{
		if(kezi[0][i] && kezi[0][i+1] && kezi[0][i+2] && kezi[0][i+3] 
		|| kezi[1][i] && kezi[1][i+1] && kezi[1][i+2] && kezi[1][i+3] 
		|| kezi[2][i] && kezi[2][i+1] && kezi[2][i+2] && kezi[2][i+3] )
		{
			return true;
		}
	}	
	return false;
}

//���۾ţ���������һ���ſ�����ɵĺ��ơ����������͡�ͬ�̡����� 
bool CheckHuPai::CheckQingYaoJiu()
{
	if(m_byShunNum>0)
	{
		return false;
	}
	BYTE pai = 255,type = 255;
	for(int i=0;i<hupaistruct.count;++i)
	{	
		pai = hupaistruct.data[i][0];
		if(pai%10 != 1 && pai%10 != 9)
		{
			return false;
		}
		if(type == 255)
		{
			type = CMjRef::GetHuaSe(pai);
		}
		if(type != CMjRef::GetHuaSe(pai))
		{
			return false;
		}
	}
	for(int i=0;i<5;++i)
	{
		if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byType == 255)
			continue;
		pai = pDesk->sUserData.m_UserGCPData[m_byStation][i].byData[0];
		if(pai%10 != 1 && pai%10 != 9)
		{
			return false;
		}
		if(type == 255)
		{
			type = CMjRef::GetHuaSe(pai);
		}
		if(type != CMjRef::GetHuaSe(pai))
		{
			return false;
		}
	}
	return true;
}

//С��ϲ������ʱ�з��Ƶ�3�����Ӽ����ơ���������� �������������ƣ�
bool CheckHuPai::CheckXiaoSiXi()
{
	if((m_byGangNum+m_byKeziNum)<3)
	{
		return false;
	}
	BYTE num = 0;
	for(int i=0;i<m_byKeziNum;++i)
	{
		if(m_byKeziData[i] >= CMjEnum::MJ_TYPE_FD && m_byKeziData[i] <=CMjEnum::MJ_TYPE_FB)
		{
			num++;
		}
	}
	for(int i=0;i<m_byGangNum;++i)
	{
		if(m_byGangData[i][1] >= CMjEnum::MJ_TYPE_FD && m_byGangData[i][1] <=CMjEnum::MJ_TYPE_FB)
		{
			num++;
		}
	}
	if(num==3 && m_byJiang >= CMjEnum::MJ_TYPE_FD && m_byJiang <=CMjEnum::MJ_TYPE_FB)
	{
		return true;
	}
	return false;
}

//С��Ԫ�� ����ʱ�м��Ƶ��������Ӽ����ơ����Ƽ��� �������������ƣ�
bool CheckHuPai::CheckXiaoSanYuan()
{
	if((m_byGangNum+m_byKeziNum)<2)
		return false;
	BYTE num = 0;
	for(int i=0;i<m_byKeziNum;++i)
	{
		if(m_byKeziData[i] >= CMjEnum::MJ_TYPE_ZHONG && m_byKeziData[i] <=CMjEnum::MJ_TYPE_BAI)
		{
			num++;
		}
	}
	for(int i=0;i<m_byGangNum;++i)
	{
		if(m_byGangData[i][1] >= CMjEnum::MJ_TYPE_ZHONG && m_byGangData[i][1] <=CMjEnum::MJ_TYPE_BAI)
		{
			num++;
		}
	}
	if(num==2 && m_byJiang >= CMjEnum::MJ_TYPE_ZHONG && m_byJiang <=CMjEnum::MJ_TYPE_BAI)
	{
		return true;
	}
	return false;
}

//��һɫ�������ƵĿ���(��)������ɵĺ��ơ����������� 
bool CheckHuPai::CheckZiYiSe()
{
	//m_byShunNum
	BYTE pai = 255;
	for(int i=0;i<HAND_CARD_NUM;i++)
	{
		if(m_byArHandPai[i] == 255 || m_byArHandPai[i] > CMjEnum::MJ_TYPE_W9)
			continue;
		if(m_byArHandPai[i]<=CMjEnum::MJ_TYPE_FD)
		{
			return false;
		}
	}
	for(int i=0;i<5;++i)
	{
		if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byType == 255)
			continue;
		if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byData[0]<=CMjEnum::MJ_TYPE_FD)
		{
			return false;
		}
	}
	return false;
}

//�İ��̣�4������(����)���������˴�����ơ�������ǰ�塢������ 
bool CheckHuPai::CheckSiAnKe()
{

	BYTE num = 0;
	for(int i=0;i<hupaistruct.count;++i)
	{			
		if(hupaistruct.byType[i] == TYPE_AN_KE)
		{
			num++;
		}
	}
	for(int i=0;i<m_byGangNum;++i)
	{
		if(m_byGangData[i][0] == ACTION_AN_GANG)
		{
			num++;
		}
	}
	if(num==4)
	{
		return true;
	}

	CheckPingHuData();

	return false;
}

//һɫ˫���᣺һ�ֻ�ɫ���������ٸ���5Ϊ���ơ�����ƽ�����߶ԡ���һɫ �����������ƣ�
bool CheckHuPai::CheckYiSeShuangLongHui()
{
	if(m_byShunNum<4)
	{
		return false;
	}
	BYTE num[3][9];
	memset(num,0,sizeof(num));
	for(int i=0;i<m_byShunNum;++i)
	{
		if(m_byShunData[i]>=CMjEnum::MJ_TYPE_FD)
			continue;
		num[CMjRef::GetHuaSe(m_byShunData[i])][m_byShunData[i]%10-1]++;
	}
	if(	  num[0][1]==2 && num[0][7]==2 && m_byJiang==CMjEnum::MJ_TYPE_W5
		||num[1][1]==2 && num[1][7]==2 && m_byJiang==CMjEnum::MJ_TYPE_B5
		||num[2][1]==2 && num[2][7]==2 && m_byJiang==CMjEnum::MJ_TYPE_T5 )
	{
	}

	return false;
}

//����ϲ����4�����(��)��ɵĺ��ơ�����Ȧ��̡��ŷ�̡�����̡������� �����������ƣ�
bool CheckHuPai::CheckDaSiXi()
{
	if((m_byGangNum+m_byKeziNum)<4)
	{
		return false;
	}
	bool zfb[4];
	memset(zfb,0,sizeof(zfb));
	for(int i=0;i<m_byKeziNum;++i)
	{
		if(m_byKeziData[i] >= CMjEnum::MJ_TYPE_FD && m_byKeziData[i] <=CMjEnum::MJ_TYPE_FB)
		{
			zfb[m_byKeziData[i]-CMjEnum::MJ_TYPE_FD] = true;
		}
	}
	for(int i=0;i<m_byGangNum;++i)
	{
		if(m_byGangData[i][1] >= CMjEnum::MJ_TYPE_FD && m_byGangData[i][1] <=CMjEnum::MJ_TYPE_FB)
		{
			zfb[m_byGangData[i][1]-CMjEnum::MJ_TYPE_FD] = true;
		}
	}
	if(zfb[0] && zfb[1] && zfb[2] && zfb[3])
	{
		return true;
	}
	return false;
}

//����Ԫ�������У����з���3�����ӣ����ơ����Ƽ��� �������������ƣ�
bool CheckHuPai::CheckDaSanYuan()
{
	if((m_byGangNum+m_byKeziNum)<3)
		return false;
	bool zfb[3];
	memset(zfb,0,sizeof(zfb));
	for(int i=0;i<m_byKeziNum;++i)
	{
		if(m_byKeziData[i] >= CMjEnum::MJ_TYPE_ZHONG && m_byKeziData[i] <=CMjEnum::MJ_TYPE_FA)
		{
			zfb[m_byKeziData[i]-CMjEnum::MJ_TYPE_ZHONG] = true;
		}
	}
	if(zfb[0] && zfb[1] && zfb[2])
	{
		return true;
	}
	return false;
}

//��һɫ����23468���������е��κ�����ɵ�˳�ӡ����ӡ����ĺ��ơ����ƻ�һɫ������"��"����ɵĸ��ƣ��ɼ���һɫ 
bool CheckHuPai::CheckLvYiSe()
{
	BYTE pai = 255;
	for(int i=0;i<HAND_CARD_NUM;i++)//��������
	{
		if(m_byArHandPai[i] == 255)
			continue;
		pai = m_byArHandPai[i];
		if(pai!= CMjEnum::MJ_TYPE_T2 && pai!=CMjEnum::MJ_TYPE_T3 && pai!=CMjEnum::MJ_TYPE_T4 && pai!=CMjEnum::MJ_TYPE_T6 && pai!=CMjEnum::MJ_TYPE_T8 && pai!= CMjEnum::MJ_TYPE_FA)
			return false;
	}
	for(int i=0;i<5;++i)
	{
		if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byType == 255)
			continue;
		pai = pDesk->sUserData.m_UserGCPData[m_byStation][i].byData[0];
		if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byType == ACTION_CHI)
		{
			if(pai!=CMjEnum::MJ_TYPE_T2)
				return false;
		}
		else
		{
			if(pai!= CMjEnum::MJ_TYPE_T2 && pai!=CMjEnum::MJ_TYPE_T3 && pai!=CMjEnum::MJ_TYPE_T4 && pai!=CMjEnum::MJ_TYPE_T6 && pai!=CMjEnum::MJ_TYPE_T8 && pai!= CMjEnum::MJ_TYPE_FA)
				return false;
		}
	}
	return true;
}



//�ĸܣ�ʮ���޺�����4���� 
bool CheckHuPai::CheckSiGang()
{
	if(m_byGangNum == 4)
		return true;
	return false;
}

//�������ƣ���һ�ֻ�ɫ�������Ӱ�1112345678999��ɵ��ض����ͣ���ͬ��ɫ�κ�1�������Ƽ��ɺ��ơ�������һɫ���������������ƣ�
bool CheckHuPai::CheckJiuLianBaoDeng()
{
	if(pDesk->sUserData.GetGCPCount(m_byStation)>0)//�����г�����
	{
		return false;
	}
	BYTE type = 255;
	BYTE num[9];
	memset(num,0,sizeof(num));
	BYTE hand[HAND_CARD_NUM];
	memset(hand,255,sizeof(hand));

	for(int i=0;i<HAND_CARD_NUM;++i)
	{
		if(m_byArHandPai[i] == 255)
			continue;
		hand[i] = m_byArHandPai[i];
	}
	for(int i=0;i<HAND_CARD_NUM;++i)
	{
		if(hand[i] == 255)
			continue;
		if(hand[i] == m_byLastPai)//���һ���Ʋ���
		{
			hand[i] = 255;
			break;
		}
	}
	///��С��������
	MaoPaoSort(hand,HAND_CARD_NUM,false);
	
	for(int i=0;i<HAND_CARD_NUM;++i)
	{
		if(hand[i] == 255)
			continue;
		if(hand[i] >= CMjEnum::MJ_TYPE_FD)//����������
			return false;
		num[hand[i]%10-1]++;
		if(type == 255)
		{
			type = hand[i]/10;
		}
		if(type != hand[i]/10)//��������һɫ
		{
			return false;
		}
	}
	for(int i=0;i<9;i++)
	{
		if(i==0 || i==8)
		{
			if(num[i] < 3)
			{
				return false;
			}
		}
		else
		{
			if(num[i] != 1)
			{
				return false;
			}
		}
	}
	return true;
}

/////////////////////////��������///////////////////////////////////////////////////////////////////////////////////////////////


//ȫ�������ɵ���3�ֻ�ɫ147��258��369���ܴ�λ�������Ƽ����������з����е��κ�14������ɵĺ��ƣ�ʮ���ã������������롢�����ˡ�����(��ƽ������)
bool CheckHuPai::CheckQuanBuKao()
{
	BYTE num=0;
	for(int i=0;i<5;++i)
	{
		if(pDesk->sUserData.m_UserGCPData[m_byStation][i].byType == 255)
			continue;
		num++;
	}
	if(num>0)//�����г�����
	{
		return false;
	}
	BYTE pai = 255;
	for(int i=0;i<HuTempData.conut;++i)
	{
		if(HuTempData.data[i][1]>1)
			return false;
		if(HuTempData.data[i][0]>=CMjEnum::MJ_TYPE_FD)
		{
			continue;
		}
		if(pai == 255 || pai/10!=HuTempData.data[i][0]/10)
		{
			pai = HuTempData.data[i][0];
		}
		else
		{
			if((HuTempData.data[i][0]-pai)<3)
			{
				return false;
			}
		}
	}
	return true;
}

//�������3�ֻ�ɫ��147��258��369���ܴ�λ�������� ��
bool CheckHuPai::CheckZuHeLong()	
{
	if(pDesk->sUserData.GetGCPCount(m_byStation)>0)//�����г�����
	{
		return false;
	}
	
	return false;
}

//�߶ԣ���7��������ɺ��ơ����Ʋ����ˡ�����  (��ƽ������)
int CheckHuPai::CheckQiDui()
{
	if(pDesk->sUserData.GetGCPCount(m_byStation)>0)//�����г�����
	{
		return 0;
	}
	int need = 0;
	for(int i=0;i<HuTempData.conut;++i)
	{
		if(HuTempData.data[i][1] == 0)
			continue;
		if(HuTempData.data[i][1]%2==1)
			return 0;
	}
	return 1;
}

//���ǲ�����������7�����ŵĶ����ϱ��з��ף�����3�ֻ�ɫ����λ��147��258��369�е�7�����������û�н��Ƶĺ��ơ����������롢�����ˡ����� (��ƽ������)
bool CheckHuPai::CheckQiXingBuKao()
{

	if(pDesk->sUserData.GetGCPCount(m_byStation)>0)//�����г�����
	{
		return false;
	}
	BYTE num=0;
	BYTE pai = 255;

	int nWanNum = 0;
	int nTongNum = 0;
	int nTiaoNum = 0;

	for(int i=0;i<HuTempData.conut;++i)
	{
		if(HuTempData.data[i][1]>1)
			return false;
		if(HuTempData.data[i][0]>=CMjEnum::MJ_TYPE_FD)
		{
			num++;
			continue;
		}
		if(pai == 255 || pai/10!=HuTempData.data[i][0]/10)
		{
			pai = HuTempData.data[i][0];
			continue;
		}
		if((HuTempData.data[i][0]-pai)<3)
		{
			return false;
		}
		pai = HuTempData.data[i][0];
	}
	if(num==7)
	{
		return true;
	}
	return false;
}

//���߶ԣ� ��һ�ֻ�ɫ�������������������7�����ӵĺ��ơ�������һɫ�������ˡ����� �������������ƣ�
bool CheckHuPai::CheckLianQiDui()
{
	if(pDesk->sUserData.GetGCPCount(m_byStation)>0)//�����г�����
	{
		return false;
	}	
	BYTE duizi[9],num=0,pai=255;
	memset(duizi,255,sizeof(duizi));
	for(int i=0;i<HuTempData.conut;++i)
	{
		if(HuTempData.data[i][1] == 0)
			continue;
		if(HuTempData.data[i][1] != 2)
			return false;
		duizi[num] = HuTempData.data[i][0];
		num++;
	}
	pai = duizi[0];
	if( duizi[1]-1 == pai && duizi[2]-2 ==  pai && duizi[3]-3 == pai && duizi[4]-4 == pai && duizi[5]-5 == pai && duizi[6]-6==pai)
	{
		return true;
	}
	
	return false;
}

//ʮ���ۣ���3�������Ƶ�һ�����ƣ�7�����Ƽ�����һ��������ɵĺ��ơ����������롢�����ˡ����� �������������ƣ�
bool CheckHuPai::CheckShiSanYao()
{
	if(pDesk->sUserData.GetGCPCount(m_byStation)>0)//�����г�����
	{
		return false;
	}
	int pai[38],duizi=0;
	memset(pai,0,sizeof(pai));
	for(int i=0;i<HAND_CARD_NUM;i++)
	{
		if(m_byArHandPai[i] == 255)
			continue;
		if(m_byArHandPai[i] < CMjEnum::MJ_TYPE_FD && m_byArHandPai[i]%10 != 1 && m_byArHandPai[i]%10 != 9)
		{
			OutputDebugString("���Ʋ��ԣ� ��ʿ��˫  �з�����");
			return false;
		}
		pai[m_byArHandPai[i]]++;
	}
	for(int i=0;i<CMjEnum::MJ_TYPE_BAI+1;++i)
	{
		if(i%10 == 0 || (i<CMjEnum::MJ_TYPE_FD && i%10 != 1 && i%10 != 9))
			continue;
		if(pai[i] <= 0)
		{
			return false;
		}
		if(pai[i] > 1)
		{
			duizi++;
		}
		if(duizi >= 2)
		{
			return false;
		}
	}
	return true;
}

bool CheckHuPai::CheckNoHua()
{
	if(pDesk->sUserData.m_byArHuaPai[m_byStation][0] == 255)
	{
		return true;
	}

	return false;
}