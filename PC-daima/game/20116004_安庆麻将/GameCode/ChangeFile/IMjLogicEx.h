/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #pragma once
//#include "StdAfx.h"
//#include "../Client/StdAfx.h"
#include "../Client/IMjLogic.h"


/// �����齫�߼���:�齫�������߼��ڸ�����ʵ�֣����û��������ֱ�ӵ��ø��༴��
class IMjLogicEx:public  IMjLogic
{
public:

	IMjLogicEx();
	virtual ~IMjLogicEx();


public:
	//******************����ܵ����ĺ���********************************	
    ///�й�
	virtual bool OnTuoGuan();
	///���������ӿ�
	virtual bool SetWaitSetGame(void * pStationData, UINT uDataSize);
	virtual bool SetWaitAgree(void * pStationData, UINT uDataSize);
	virtual void SetSendCardStation(void * pStationData);
	virtual void SetPlayingStation(void * pStationData,int iLessCount);

	//virtual bool GameUserCome(BYTE bDeskStation, UserItemStruct * pUserItem, bool bWatchUser);
	//virtual bool GameUserLeft(BYTE bDeskStation, UserItemStruct * pUserItem, bool bWatchUser);

	/////////////////////////�¼�����//////////////////////////////////////////////
	///��Ϸ��ʼ
	virtual void GameBegin(void * pNetData, UINT uDataSize);
	///�Զ�Ϊׯ
	virtual void MakeDongNt(void * pNetData, UINT uDataSize);
	///�׾���2��ɫ�ӵĵ�����Ϊׯ�¼�
	virtual void SeziMakeNt(void * pNetData, UINT uDataSize);
	///�׾���2��ɫ�Ӷ�ׯ�Һ����Ƶ��¼�
	virtual void SeziMakeNtAndGetPai(void * pNetData, UINT uDataSize);
	///�׾�������2��ɫ�Ӷ�ׯ���¼�
	virtual void TurnSeziMakeNt(void * pNetData, UINT uDataSize);
	///��2��ɫ���¼������Ʒ����¼�
	virtual void SeziMakeDir(void * pNetData, UINT uDataSize);
	///��2��ɫ���¼������Ʒ�������Ƶ��¼�
	virtual void SeziMakeDirAndGetPai(void * pNetData, UINT uDataSize);
	///��2��ɫ���¼������Ƶ��¼�
	virtual void SeziMakeGetPai(void * pNetData, UINT uDataSize);
	///�����¼�
	virtual void SendCard(void * pNetData, UINT uDataSize);
	///�����¼���ׯ������
	virtual void TiaoPai(void * pNetData,UINT uDataSize);
	///��2��ɫ�Ӷ������¼�
	virtual void SeziMakeJing(void * pNetData, UINT uDataSize);
	//Ϊ������Ҳ����¼�
	virtual void AllBuHua(void * pNetData, UINT uDataSize);
	///������Ҳ����¼�
	virtual void OneBuHua(void * pNetData, UINT uDataSize);
	///ׯ�ҿ�ʼ����֪ͨ�¼���ȷ�����ƺ������������Ϣ֪ͨ��ҳ���
	virtual void BeginOutCard(void * pNetData, UINT uDataSize);
	///�����¼�����ҳ���
	virtual void UserOutCard(void * pNetData, UINT uDataSize);
	///ץ���¼�
	virtual void UserZhuaAPai(void * pNetData, UINT uDataSize);
	///������֪ͨ�¼�
	virtual void CPGNotify(void * pNetData, UINT uDataSize);
	///�����¼�
	virtual void UserChi(void * pNetData, UINT uDataSize);
	///�����¼�
	virtual void UserPeng(void * pNetData, UINT uDataSize);
	///�����¼�
	virtual void UserKan(void * pNetData, UINT uDataSize);
	///ɨ���¼�
	virtual void UserSaoHu(void * pNetData, UINT uDataSize);
	///�����¼�
	virtual void UserGang(void * pNetData, UINT uDataSize);
	///�����¼�
	virtual void UserTing(void * pNetData, UINT uDataSize);
	///���¼�
	virtual void UserHu(void * pNetData, UINT uDataSize);
	///����¼�
	virtual void CountFen(void * pNetData, UINT uDataSize);
	///���������¼�����Ϸ��������
	virtual void H081_UserContinueEnd(void * pNetData, UINT uDataSize);
	///���������������¼�������ǿ����Ϸ����
	virtual void H080_UserLeftOrGameAnQuanFinish(void * pNetData, UINT uDataSize);
	///����й�
	virtual void UserTuoGuan(void * pNetData, UINT uDataSize);
	//�����齫����
	virtual void SetMjRule(void * pNetData, UINT uDataSize);

	virtual void ResetGameStation(int iGameStation);

	///�Զ�����,�����˵Ĵ���Ҳ�ڴ˺���
	virtual void AutoOutCard(BYTE pai=255,bool AI=false);		

    ///��������û���ᵽ����Ϣ
	//virtual bool HandleGameMessage(NetMessageHead * pNetHead, void * pNetData, UINT uDataSize); 

	//*********************����������ĺ���*************************
	///��Ӧ����Ҽ�
	virtual void OnRButtonUp();
	///��Ӧ�����Ϣ
	virtual void OnMouseMove(int iCard,int iCardIndex,bool isclick=false);
	///���齫��ĳ��������ť
	virtual void OnMjBtnClick( int btntype);	

public:
	//**********************���ú���****************************
	///���߼�����
	///��
	virtual void OnMjBtnClickChi(BYTE index = 0); 
	///��
	virtual void OnMjBtnClickPeng( );
	///��
	virtual void OnMjBtnClickKan(BYTE pai = 255);
	///ɨ��
	virtual void OnMjBtnClickSaoHu();
	///��
	virtual void OnMjBtnClickGang(BYTE index = 0);
	///��
	virtual void OnMjBtnClickTing(bool bIsYanPai = false);	
	///��
	virtual void OnMjBtnClickHu();   
	///��
	virtual void OnMjBtnClickguo(void); 
	///����
	virtual void IChuPai( BYTE pai = 255);	

public:
	///�õ������ܳ���,���ƣ����Ƶĸ���
	virtual int GetChiGangKanNum(BYTE type);
	///������ʱ���ݣ������ܵ���ʱ��Ϣ��
	virtual void ClearTempData();
	///���������ó��������ݣ������ܵ���ʱ��Ϣ��
	virtual void GetCPGData(tagCPGNotifyEx * pData);

	public:


};