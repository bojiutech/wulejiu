/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #include "StdAfx.h"
#include "IMjlogicEx.h"
//#include "../Client/StdAfx.h"
//#include <iostream>
//using namespace std;
#include "../Client/ClientGameDlg.h"
///���������캯��
IMjLogicEx::IMjLogicEx()
{	
	///��ǰ���ӵĵ���
	m_nSeZi0 = 0;
	m_nSeZi1 = 0;
}

///��������������
IMjLogicEx::~IMjLogicEx()
{

}

	//******************����ܵ����ĺ���********************************	
///�й�
bool IMjLogicEx::OnTuoGuan()
{
	return IMjLogic::OnTuoGuan();
}
///���������ӿ�
bool IMjLogicEx::SetWaitSetGame(void * pStationData, UINT uDataSize)
{
	return IMjLogic::SetWaitSetGame(pStationData,uDataSize);
}
bool IMjLogicEx::SetWaitAgree(void * pStationData, UINT uDataSize)
{
	return IMjLogic::SetWaitAgree(pStationData,uDataSize);
}
void IMjLogicEx::SetSendCardStation(void * pStationData)
{
	IMjLogic::SetSendCardStation(pStationData);
}
void IMjLogicEx::SetPlayingStation(void * pStationData,int iLessCount)
{
	IMjLogic::SetPlayingStation(pStationData, iLessCount);
	GameStationDataEx * pGameStation=(GameStationDataEx *)pStationData;

	for(int i=0;i<4;i++)
	{
		g_UserData.m_byZuoLaZhuag[i] = pGameStation->m_byZuoLaZhuag[i];
	}

}

//bool IMjLogicEx::GameUserCome(BYTE bDeskStation, UserItemStructInExe * pUserItem, bool bWatchUser)
//{
//	return IMjLogic::GameUserCome(bDeskStation, pUserItem, bWatchUser);
//}
//bool IMjLogicEx::GameUserLeft(BYTE bDeskStation, UserItemStructInExe * pUserItem, bool bWatchUser)
//{
//	return IMjLogic::GameUserLeft(bDeskStation, pUserItem, bWatchUser);
//}
/////////////////////////�¼�����//////////////////////////////////////////////
///��Ϸ��ʼ
void IMjLogicEx::GameBegin(void * pNetData, UINT uDataSize)
{
	IMjLogic::GameBegin(pNetData,uDataSize);
}
///�Զ�Ϊׯ
void IMjLogicEx::MakeDongNt(void * pNetData, UINT uDataSize)
{
	IMjLogic::MakeDongNt(pNetData,uDataSize);
}
///�׾���2��ɫ�ӵĵ�����Ϊׯ�¼�
void IMjLogicEx::SeziMakeNt(void * pNetData, UINT uDataSize)
{
	IMjLogic::SeziMakeNt(pNetData,uDataSize);
}
///�׾���2��ɫ�Ӷ�ׯ�Һ����Ƶ��¼�
void IMjLogicEx::SeziMakeNtAndGetPai(void * pNetData, UINT uDataSize)
{
	IMjLogic::SeziMakeNtAndGetPai(pNetData,uDataSize);
}
///�׾�������2��ɫ�Ӷ�ׯ���¼�
void IMjLogicEx::TurnSeziMakeNt(void * pNetData, UINT uDataSize)
{
	IMjLogic::TurnSeziMakeNt(pNetData,uDataSize);
}
///��2��ɫ���¼������Ʒ����¼�
void IMjLogicEx::SeziMakeDir(void * pNetData, UINT uDataSize)
{
	IMjLogic::SeziMakeDir(pNetData,uDataSize);
}

///��2��ɫ���¼������Ʒ�������Ƶ��¼�
void IMjLogicEx::SeziMakeDirAndGetPai(void * pNetData, UINT uDataSize)
{
	IMjLogic::SeziMakeDirAndGetPai(pNetData,uDataSize);
}
///��2��ɫ���¼������Ƶ��¼�
void IMjLogicEx::SeziMakeGetPai(void * pNetData, UINT uDataSize)
{
	IMjLogic::SeziMakeGetPai(pNetData,uDataSize);
}
///�����¼�
void IMjLogicEx::SendCard(void * pNetData, UINT uDataSize)
{
	IMjLogic::SendCard(pNetData,uDataSize);
}
///�����¼���ׯ������
void IMjLogicEx::TiaoPai(void * pNetData,UINT uDataSize)
{
	IMjLogic::TiaoPai(pNetData,uDataSize);
}
///��2��ɫ�Ӷ������¼�
void IMjLogicEx::SeziMakeJing(void * pNetData, UINT uDataSize)
{
	IMjLogic::SeziMakeJing(pNetData,uDataSize);
}
//Ϊ������Ҳ����¼�
void IMjLogicEx::AllBuHua(void * pNetData, UINT uDataSize)
{
	IMjLogic::AllBuHua(pNetData,uDataSize);
}
///������Ҳ����¼�
void IMjLogicEx::OneBuHua(void * pNetData, UINT uDataSize)
{
	IMjLogic::OneBuHua(pNetData,uDataSize);
}
///ׯ�ҿ�ʼ����֪ͨ�¼���ȷ�����ƺ������������Ϣ֪ͨ��ҳ���
void IMjLogicEx::BeginOutCard(void * pNetData, UINT uDataSize)
{
	IMjLogic::BeginOutCard(pNetData,uDataSize);
}
///�����¼�����ҳ���
void IMjLogicEx::UserOutCard(void * pNetData, UINT uDataSize)
{
	IMjLogic::UserOutCard(pNetData,uDataSize);
}
///ץ���¼�
void IMjLogicEx::UserZhuaAPai(void * pNetData, UINT uDataSize)
{
	IMjLogic::UserZhuaAPai(pNetData,uDataSize);
}
///������֪ͨ�¼�
void IMjLogicEx::CPGNotify(void * pNetData, UINT uDataSize)
{
	IMjLogic::CPGNotify(pNetData,uDataSize);
}
///�����¼�
void IMjLogicEx::UserChi(void * pNetData, UINT uDataSize)
{
	IMjLogic::UserChi(pNetData,uDataSize);
}
///�����¼�
void IMjLogicEx::UserPeng(void * pNetData, UINT uDataSize)
{
	IMjLogic::UserPeng(pNetData,uDataSize);
}
///�����¼�
void IMjLogicEx::UserKan(void * pNetData, UINT uDataSize)
{
	IMjLogic::UserKan(pNetData,uDataSize);
}
///ɨ���¼�
void IMjLogicEx::UserSaoHu(void * pNetData, UINT uDataSize)
{
	IMjLogic::UserSaoHu(pNetData,uDataSize);
}
///�����¼�
void IMjLogicEx::UserGang(void * pNetData, UINT uDataSize)
{
	IMjLogic::UserGang(pNetData,uDataSize);
}
///�����¼�
void IMjLogicEx::UserTing(void * pNetData, UINT uDataSize)
{
	IMjLogic::UserTing(pNetData,uDataSize);
}
///���¼�
void IMjLogicEx::UserHu(void * pNetData, UINT uDataSize)
{
	IMjLogic::UserHu(pNetData,uDataSize);
}
///����¼�
void IMjLogicEx::CountFen(void * pNetData, UINT uDataSize)
{
	IMjLogic::CountFen(pNetData,uDataSize);
}
///���������¼�����Ϸ��������
void IMjLogicEx::H081_UserContinueEnd(void * pNetData, UINT uDataSize)
{
	IMjLogic::H081_UserContinueEnd(pNetData,uDataSize);
}
///���������������¼�������ǿ����Ϸ����
void IMjLogicEx::H080_UserLeftOrGameAnQuanFinish(void * pNetData, UINT uDataSize)
{
	IMjLogic::H080_UserLeftOrGameAnQuanFinish(pNetData,uDataSize);
}
///����й�
void IMjLogicEx::UserTuoGuan(void * pNetData, UINT uDataSize)
{
	IMjLogic::UserTuoGuan(pNetData,uDataSize);
}
//�����齫����
void IMjLogicEx::SetMjRule(void * pNetData, UINT uDataSize)
{
	IMjLogic::SetMjRule(pNetData,uDataSize);
}

void IMjLogicEx::ResetGameStation(int iGameStation)
{
	IMjLogic::ResetGameStation(iGameStation);
}
///�Զ�����,�����˵Ĵ���Ҳ�ڴ˺���
void IMjLogicEx::AutoOutCard(BYTE pai,bool AI)	
{
	//IMjLogic::AutoOutCard(pai,AI);

	g_pCClientGameDlg->KillTimer(ID_OUT_CARD);
	if(!AI)//���ǻ����ˣ�����Ҫ�˹����ܡ������ץ�����ƾͿ�����
	{
		BYTE outpai = g_UserData.GetLastHandPai(m_Station);
		if(g_UserData.m_StrJing.CheckIsJing(outpai))
		{//ȷ�������Զ����������
			for(int i=0;i<g_UserData.GetHandPaiCount(m_Station)-1;i++)
			{
				if(!g_UserData.m_StrJing.CheckIsJing(g_UserData.m_byArHandPai[m_Station][i]))
				{
					outpai = g_UserData.m_byArHandPai[m_Station][i];
					break;
				}
			}
		}
		IChuPai(outpai);
	}
}
/////��������û���ᵽ����Ϣ
//bool IMjLogicEx::HandleGameMessage(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize)
//{
//	return IMjLogic::HandleGameMessage(pNetHead,pNetData,uDataSize);
//}
//*********************����������ĺ���*************************
///��Ӧ����Ҽ�
void IMjLogicEx::OnRButtonUp()
{
	IMjLogic::OnRButtonUp();
}
///��Ӧ�����Ϣ
void IMjLogicEx::OnMouseMove(int iCard,int iCardIndex,bool isclick)
{
	IMjLogic::OnMouseMove(iCard, iCardIndex, isclick);
}
///���齫��ĳ��������ť
void IMjLogicEx::OnMjBtnClick( int btntype)
{
	IMjLogic::OnMjBtnClick(btntype);
}

///���߼�����
///��
void IMjLogicEx::OnMjBtnClickChi(BYTE index)
{
	IMjLogic::OnMjBtnClickChi(index);
}
///��
void IMjLogicEx::OnMjBtnClickPeng()
{
	IMjLogic::OnMjBtnClickPeng();
}
///��
void IMjLogicEx::OnMjBtnClickKan(BYTE pai)
{
	IMjLogic::OnMjBtnClickKan(pai);
}
///ɨ��
void IMjLogicEx::OnMjBtnClickSaoHu()
{
	IMjLogic::OnMjBtnClickSaoHu();
}
///��
void IMjLogicEx::OnMjBtnClickGang(BYTE index)
{
	IMjLogic::OnMjBtnClickGang(index);
}
///��
void IMjLogicEx::OnMjBtnClickTing(bool bIsYanPai)
{
	IMjLogic::OnMjBtnClickTing(bIsYanPai);
}
///��
void IMjLogicEx::OnMjBtnClickHu() 
{
	IMjLogic::OnMjBtnClickHu();
}
///��
void IMjLogicEx::OnMjBtnClickguo()
{
	IMjLogic::OnMjBtnClickguo();
}
///����
void IMjLogicEx::IChuPai( BYTE pai)
{
	OutputDebugString("���ƣ�IMjLogicEx");
	IMjLogic::IChuPai(pai);
}
///�õ������ܳ���,���ƣ����Ƶĸ���
int IMjLogicEx::GetChiGangKanNum(BYTE type)
{
	return IMjLogic::GetChiGangKanNum(type);
}
///������ʱ���ݣ������ܵ���ʱ��Ϣ��
void IMjLogicEx::ClearTempData()
{
	IMjLogic::ClearTempData();
}
///���������ó��������ݣ������ܵ���ʱ��Ϣ��
void IMjLogicEx::GetCPGData(tagCPGNotifyEx * pData)
{
	IMjLogic::GetCPGData(pData);
}

