/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #include "stdafx.h"
#include "CheckCPGActionEx.h"
#include "../server/ServerManage.h"
//ȫ�ֶ���
//CheckCPGActionEx g_CPGAction;


CheckCPGActionEx::CheckCPGActionEx(void)
{

}

CheckCPGActionEx::~CheckCPGActionEx(void)
{
	
}
///�ܷ����
bool CheckCPGActionEx::CanChi(BYTE station,BYTE pai,BYTE Result[][3])
{
	bool canchi = false;
	int index = 0;
	if(!pDesk->sGameData.m_mjAction.bChi || pai == 255)
	{
		return false;
	}
	if(!pDesk->sGameData.m_mjAction.bChiJing && pDesk->sUserData.m_StrJing.CheckIsJing(pai))
	{
		return false;
	}
	memset(Result,255,sizeof(Result));
	if(pai <= CMjEnum::MJ_TYPE_B9)
	{//�������
		BYTE huase = pai/10;
		if(pDesk->sUserData.IsHaveAHandPai(station,pai+1) && pDesk->sUserData.IsHaveAHandPai(station,pai+2) && (pai+1)/10 == huase && (pai+2)/10 == huase)
		{
			if(pDesk->sGameData.m_mjAction.bChiJing || (!pDesk->sUserData.m_StrJing.CheckIsJing(pai+1) && !pDesk->sUserData.m_StrJing.CheckIsJing(pai+2)))
			{
				Result[index][0] = pai;
				Result[index][1] = pai+1;
				Result[index][2] = pai+2;
				index++;
				canchi = true;
			}
		}
		if(pDesk->sUserData.IsHaveAHandPai(station,pai+1) && pDesk->sUserData.IsHaveAHandPai(station,pai-1) && (pai+1)/10 == huase && (pai-1)/10 == huase)
		{
			if(pDesk->sGameData.m_mjAction.bChiJing || (!pDesk->sUserData.m_StrJing.CheckIsJing(pai+1) && !pDesk->sUserData.m_StrJing.CheckIsJing(pai-1)))
			{
				Result[index][0] = pai-1;
				Result[index][1] = pai;
				Result[index][2] = pai+1;
				index++;
				canchi = true;
			}
		}
		if(pDesk->sUserData.IsHaveAHandPai(station,pai-1) && pDesk->sUserData.IsHaveAHandPai(station,pai-2) && (pai-1)/10 == huase && (pai-2)/10 == huase)
		{
			if(pDesk->sGameData.m_mjAction.bChiJing || (!pDesk->sUserData.m_StrJing.CheckIsJing(pai-1) && !pDesk->sUserData.m_StrJing.CheckIsJing(pai-2)))
			{
				Result[index][0] = pai-2;
				Result[index][1] = pai-1;
				Result[index][2] = pai;
				index++;
				canchi = true;
			}
		}

	}
	else if( pai <= CMjEnum::MJ_TYPE_FB &&  pDesk->sGameData.m_mjAction.bChiFeng )
	{//�Զ�������
		switch(pai)
		{
		case CMjEnum::MJ_TYPE_FD://��
			{
				if(pDesk->sUserData.IsHaveAHandPai(station,CMjEnum::MJ_TYPE_FN) && pDesk->sUserData.IsHaveAHandPai(station,CMjEnum::MJ_TYPE_FX))//������
				{
					if(pDesk->sGameData.m_mjAction.bChiJing || (!pDesk->sUserData.m_StrJing.CheckIsJing(CMjEnum::MJ_TYPE_FN) && !pDesk->sUserData.m_StrJing.CheckIsJing(CMjEnum::MJ_TYPE_FX)))
					{
						Result[index][0] = CMjEnum::MJ_TYPE_FD;
						Result[index][1] = CMjEnum::MJ_TYPE_FN;
						Result[index][2] = CMjEnum::MJ_TYPE_FX;
						index++;
						canchi = true;
					}
				}
				if(pDesk->sUserData.IsHaveAHandPai(station,CMjEnum::MJ_TYPE_FN) && pDesk->sUserData.IsHaveAHandPai(station,CMjEnum::MJ_TYPE_FB))//���ϱ�
				{
					if(pDesk->sGameData.m_mjAction.bChiJing || (!pDesk->sUserData.m_StrJing.CheckIsJing(CMjEnum::MJ_TYPE_FN) && !pDesk->sUserData.m_StrJing.CheckIsJing(CMjEnum::MJ_TYPE_FB)))
					{
						Result[index][0] = CMjEnum::MJ_TYPE_FD;
						Result[index][1] = CMjEnum::MJ_TYPE_FN;
						Result[index][2] = CMjEnum::MJ_TYPE_FB;
						index++;
						canchi = true;
					}
				}
				if(pDesk->sUserData.IsHaveAHandPai(station,CMjEnum::MJ_TYPE_FX) && pDesk->sUserData.IsHaveAHandPai(station,CMjEnum::MJ_TYPE_FB))//������
				{
					if(pDesk->sGameData.m_mjAction.bChiJing || (!pDesk->sUserData.m_StrJing.CheckIsJing(CMjEnum::MJ_TYPE_FX) && !pDesk->sUserData.m_StrJing.CheckIsJing(CMjEnum::MJ_TYPE_FB)))
					{
						Result[index][0] = CMjEnum::MJ_TYPE_FD;
						Result[index][1] = CMjEnum::MJ_TYPE_FX;
						Result[index][2] = CMjEnum::MJ_TYPE_FB;
						index++;
						canchi = true;
					}
				}
			}
			break;
		case CMjEnum::MJ_TYPE_FN://��
			{
				if(pDesk->sUserData.IsHaveAHandPai(station,CMjEnum::MJ_TYPE_FD) && pDesk->sUserData.IsHaveAHandPai(station,CMjEnum::MJ_TYPE_FX))//�϶���
				{
					if(pDesk->sGameData.m_mjAction.bChiJing || (!pDesk->sUserData.m_StrJing.CheckIsJing(CMjEnum::MJ_TYPE_FD) && !pDesk->sUserData.m_StrJing.CheckIsJing(CMjEnum::MJ_TYPE_FX)))
					{
						Result[index][0] = CMjEnum::MJ_TYPE_FN;
						Result[index][1] = CMjEnum::MJ_TYPE_FD;
						Result[index][2] = CMjEnum::MJ_TYPE_FX;
						index++;
						canchi = true;
					}
				}
				if(pDesk->sUserData.IsHaveAHandPai(station,CMjEnum::MJ_TYPE_FD) && pDesk->sUserData.IsHaveAHandPai(station,CMjEnum::MJ_TYPE_FB))//�϶���
				{
					if(pDesk->sGameData.m_mjAction.bChiJing || (!pDesk->sUserData.m_StrJing.CheckIsJing(CMjEnum::MJ_TYPE_FD) && !pDesk->sUserData.m_StrJing.CheckIsJing(CMjEnum::MJ_TYPE_FB)))
					{
						Result[index][0] = CMjEnum::MJ_TYPE_FN;
						Result[index][1] = CMjEnum::MJ_TYPE_FD;
						Result[index][2] = CMjEnum::MJ_TYPE_FB;
						index++;
						canchi = true;
					}
				}
				if(pDesk->sUserData.IsHaveAHandPai(station,CMjEnum::MJ_TYPE_FX) && pDesk->sUserData.IsHaveAHandPai(station,CMjEnum::MJ_TYPE_FB))//������
				{
					if(pDesk->sGameData.m_mjAction.bChiJing || (!pDesk->sUserData.m_StrJing.CheckIsJing(CMjEnum::MJ_TYPE_FX) && !pDesk->sUserData.m_StrJing.CheckIsJing(CMjEnum::MJ_TYPE_FB)))
					{
						Result[index][0] = CMjEnum::MJ_TYPE_FN;
						Result[index][1] = CMjEnum::MJ_TYPE_FX;
						Result[index][2] = CMjEnum::MJ_TYPE_FB;
						index++;
						canchi = true;
					}
				}
			}
			break;
		case CMjEnum::MJ_TYPE_FX://��
			{
				if(pDesk->sUserData.IsHaveAHandPai(station,CMjEnum::MJ_TYPE_FD) && pDesk->sUserData.IsHaveAHandPai(station,CMjEnum::MJ_TYPE_FN))//������
				{
					if(pDesk->sGameData.m_mjAction.bChiJing || (!pDesk->sUserData.m_StrJing.CheckIsJing(CMjEnum::MJ_TYPE_FD) && !pDesk->sUserData.m_StrJing.CheckIsJing(CMjEnum::MJ_TYPE_FN)))
					{
						Result[index][0] = CMjEnum::MJ_TYPE_FX;
						Result[index][1] = CMjEnum::MJ_TYPE_FD;
						Result[index][2] = CMjEnum::MJ_TYPE_FN;
						index++;
						canchi = true;
					}
				}
				if(pDesk->sUserData.IsHaveAHandPai(station,CMjEnum::MJ_TYPE_FN) && pDesk->sUserData.IsHaveAHandPai(station,CMjEnum::MJ_TYPE_FB))//���ϱ�
				{
					if(pDesk->sGameData.m_mjAction.bChiJing || (!pDesk->sUserData.m_StrJing.CheckIsJing(CMjEnum::MJ_TYPE_FN) && !pDesk->sUserData.m_StrJing.CheckIsJing(CMjEnum::MJ_TYPE_FB)))
					{
						Result[index][0] = CMjEnum::MJ_TYPE_FX;
						Result[index][1] = CMjEnum::MJ_TYPE_FN;
						Result[index][2] = CMjEnum::MJ_TYPE_FB;
						index++;
						canchi = true;
					}
				}
				if(pDesk->sUserData.IsHaveAHandPai(station,CMjEnum::MJ_TYPE_FD) && pDesk->sUserData.IsHaveAHandPai(station,CMjEnum::MJ_TYPE_FB))//������
				{
					if(pDesk->sGameData.m_mjAction.bChiJing || (!pDesk->sUserData.m_StrJing.CheckIsJing(CMjEnum::MJ_TYPE_FD) && !pDesk->sUserData.m_StrJing.CheckIsJing(CMjEnum::MJ_TYPE_FB)))
					{
						Result[index][0] = CMjEnum::MJ_TYPE_FX;
						Result[index][1] = CMjEnum::MJ_TYPE_FD;
						Result[index][2] = CMjEnum::MJ_TYPE_FB;
						index++;
						canchi = true;
					}
				}
			}
			break;
		case CMjEnum::MJ_TYPE_FB://��
			{
				if(pDesk->sUserData.IsHaveAHandPai(station,CMjEnum::MJ_TYPE_FD) && pDesk->sUserData.IsHaveAHandPai(station,CMjEnum::MJ_TYPE_FN))//������
				{
					if(pDesk->sGameData.m_mjAction.bChiJing || (!pDesk->sUserData.m_StrJing.CheckIsJing(CMjEnum::MJ_TYPE_FD) && !pDesk->sUserData.m_StrJing.CheckIsJing(CMjEnum::MJ_TYPE_FN)))
					{
						Result[index][0] = CMjEnum::MJ_TYPE_FB;
						Result[index][1] = CMjEnum::MJ_TYPE_FD;
						Result[index][2] = CMjEnum::MJ_TYPE_FN;
						index++;
						canchi = true;
					}
				}
				if(pDesk->sUserData.IsHaveAHandPai(station,CMjEnum::MJ_TYPE_FD) && pDesk->sUserData.IsHaveAHandPai(station,CMjEnum::MJ_TYPE_FX))//������
				{
					if(pDesk->sGameData.m_mjAction.bChiJing || (!pDesk->sUserData.m_StrJing.CheckIsJing(CMjEnum::MJ_TYPE_FD) && !pDesk->sUserData.m_StrJing.CheckIsJing(CMjEnum::MJ_TYPE_FX)))
					{
						Result[index][0] = CMjEnum::MJ_TYPE_FB;
						Result[index][1] = CMjEnum::MJ_TYPE_FD;
						Result[index][2] = CMjEnum::MJ_TYPE_FX;
						index++;
						canchi = true;
					}
				}
				if(pDesk->sUserData.IsHaveAHandPai(station,CMjEnum::MJ_TYPE_FN) && pDesk->sUserData.IsHaveAHandPai(station,CMjEnum::MJ_TYPE_FX))//������
				{
					if(pDesk->sGameData.m_mjAction.bChiJing || (!pDesk->sUserData.m_StrJing.CheckIsJing(CMjEnum::MJ_TYPE_FN) && !pDesk->sUserData.m_StrJing.CheckIsJing(CMjEnum::MJ_TYPE_FX)))
					{
						Result[index][0] = CMjEnum::MJ_TYPE_FB;
						Result[index][1] = CMjEnum::MJ_TYPE_FN;
						Result[index][2] = CMjEnum::MJ_TYPE_FX;
						index++;
						canchi = true;
					}
				}
			}
			break;
		}

	}
	else if(pDesk->sGameData.m_mjAction.bChiJian &&  pai <= CMjEnum::MJ_TYPE_BAI && pai >= CMjEnum::MJ_TYPE_ZHONG)
	{//���з���
		if(pai==CMjEnum::MJ_TYPE_ZHONG && pDesk->sUserData.IsHaveAHandPai(station,CMjEnum::MJ_TYPE_FA) && pDesk->sUserData.IsHaveAHandPai(station,CMjEnum::MJ_TYPE_BAI))
		{
			canchi = true;
		}
		else if(pai==CMjEnum::MJ_TYPE_FA && pDesk->sUserData.IsHaveAHandPai(station,CMjEnum::MJ_TYPE_ZHONG) && pDesk->sUserData.IsHaveAHandPai(station,CMjEnum::MJ_TYPE_BAI))
		{
			canchi = true;
		}
		else if(pai==CMjEnum::MJ_TYPE_BAI && pDesk->sUserData.IsHaveAHandPai(station,CMjEnum::MJ_TYPE_ZHONG) && pDesk->sUserData.IsHaveAHandPai(station,CMjEnum::MJ_TYPE_FA))
		{
			canchi = true;
		}
		if(canchi)
		{
			if(pDesk->sGameData.m_mjAction.bChiJing 
				|| (!pDesk->sUserData.m_StrJing.CheckIsJing(CMjEnum::MJ_TYPE_ZHONG) && !pDesk->sUserData.m_StrJing.CheckIsJing(CMjEnum::MJ_TYPE_FA) && !pDesk->sUserData.m_StrJing.CheckIsJing(CMjEnum::MJ_TYPE_BAI))
				)
			{
				Result[0][0] = CMjEnum::MJ_TYPE_ZHONG;
				Result[0][1] = CMjEnum::MJ_TYPE_FA;
				Result[0][2] = CMjEnum::MJ_TYPE_BAI;
			}
			else
			{
				canchi=false;
				memset(Result,255,sizeof(Result));
			}
		}
	}
	return canchi;
    //return false;
}

///�ܷ����(ֻ�ж�)
bool CheckCPGActionEx::CanChi(BYTE station,BYTE pai)
{
    return false;
}

///�ܷ�����
bool CheckCPGActionEx::CanPeng(BYTE station,BYTE pai)
{
    if (pDesk->sUserData.m_byDingQue[station]==pai/10)   // ����ȱ����
    {
        return false;
    }
    if(pai != 255 && pDesk->sUserData.GetAHandPaiCount(station,pai) >= 2)
    {
        return true;
    }
    return false;
}

//�ܷ���
bool CheckCPGActionEx::CanKan(BYTE station,BYTE kan[])
{
	return false;
}

//�ܷ���
bool CheckCPGActionEx::CanSaoHu(BYTE station)
{
	return false;
}

///�ܷ����
bool CheckCPGActionEx::CanGang(BYTE station,BYTE pai,BYTE Result[][2],bool me)
{
    bool bb = false;
	
    if(me)//���Լ����ƣ����ܺͲ���
    {	
        int temp = 0,index=0,huaIndex = 0;
        for(int i=0;i<HAND_CARD_NUM;i++)
        {
            if(pDesk->sUserData.m_byArHandPai[station][i] == 255 || pDesk->sUserData.m_byDingQue[station]==pDesk->sUserData.m_byArHandPai[station][i]/10)
                continue;

			//�������С����ƺͰװ岻�ܸܣ��Ʒ�ʱ��4��
			if(pDesk->sUserData.m_byArHandPai[station][i] == CMjEnum::MJ_TYPE_FD ||
				pDesk->sUserData.m_byArHandPai[station][i] == CMjEnum::MJ_TYPE_ZHONG ||
				pDesk->sUserData.m_byArHandPai[station][i] == CMjEnum::MJ_TYPE_FA ||
				pDesk->sUserData.m_byArHandPai[station][i] == CMjEnum::MJ_TYPE_BAI)
			{
				continue;
			}

            if(pDesk->sUserData.GetAHandPaiCount(station,pDesk->sUserData.m_byArHandPai[station][i])>=4 && temp != pDesk->sUserData.m_byArHandPai[station][i])
            {
                Result[index][1] = pDesk->sUserData.m_byArHandPai[station][i];
                Result[index][0] = ACTION_AN_GANG;
                temp = pDesk->sUserData.m_byArHandPai[station][i];
                bb = true;
                index++;
            }
        }

		//���е���Ҳ�ܲ���
		if (pDesk->sGameData.m_mjAction.bBuGang)
		{
			for (int i = 0; i < HAND_CARD_NUM; i++)
			{
				if (pDesk->sUserData.m_byArHandPai[station][i] == 255 || pDesk->sUserData.m_byDingQue[station] == pDesk->sUserData.m_byArHandPai[station][i] / 10)
					continue;

				if (pDesk->sUserData.IsUserHavePengPai(station, pDesk->sUserData.m_byArHandPai[station][i]))
				{
					Result[index][1] = pDesk->sUserData.m_byArHandPai[station][i];
					Result[index][0] = ACTION_BU_GANG;
					temp = pDesk->sUserData.m_byArHandPai[station][i];
					bb = true;
					index++;
				}
			}
		}

		/*if(pDesk->sUserData.GetAHandPaiCount(station,CMjEnum::MJ_TYPE_FD)>=1)
		{
		Result[index][1] = CMjEnum::MJ_TYPE_FD;
		Result[index][0] = ACTION_BU_HUA;
		bb = true;
		index++;
		}
		if(pDesk->sUserData.GetAHandPaiCount(station,CMjEnum::MJ_TYPE_ZHONG)>=1)
		{
		Result[index][1] = CMjEnum::MJ_TYPE_ZHONG;
		Result[index][0] = ACTION_BU_HUA;
		bb = true;
		index++;
		}
		if(pDesk->sUserData.GetAHandPaiCount(station,CMjEnum::MJ_TYPE_FA)>=1)
		{
		Result[index][1] = CMjEnum::MJ_TYPE_FA;
		Result[index][0] = ACTION_BU_HUA;
		bb = true;
		index++;
		}
		if(pDesk->sUserData.GetAHandPaiCount(station,CMjEnum::MJ_TYPE_BAI)>=1)
		{
		Result[index][1] = CMjEnum::MJ_TYPE_BAI;
		Result[index][0] = ACTION_BU_HUA;
		bb = true;
		index++;
		}*/
        return bb;
    }
    else//����
    {
		if (pDesk->sUserData.m_byDingQue[station] == pai/10)   // ����ȱ����
		{
			return false;
		}
        if(pai == 255 || pai == 0)
            return false;
        if(pDesk->sUserData.GetAHandPaiCount(station,pai)>=3)
        {
            bb = true;
            Result[0][1] = pai;
            Result[0][0] = ACTION_MING_GANG;
        }
    }
    return bb;
}





