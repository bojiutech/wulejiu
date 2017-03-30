/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #pragma once

/**
* ɽ���齫������
*/

#include "StdAfx.h"
#include "..\GameMessage\CLogicBase.h"

#include "..\ChangeFile\GameDataEx.h"
#include "..\ChangeFile\UserDataEx.h"
#include "..\ChangeFile\CheckHuPaiEx.h"
#include "..\ChangeFile\CheckCPGActionEx.h"
#include "..\ChangeFile\ThingHandleEx.h"


// ��ʱ�� ID
#define TIME_GAME_FINISH			91				// ��Ϸ������ʱ��
#define TIME_CHECK_CONNECT          92              // ������
#define DEFAULT_CHECK_TIME          10000           //���һ�������ղ�����Ϣ

//��Ϸ������־����
#define GF_NORMAL					10				// ��Ϸ��������
#define GF_SALE						11				// ��Ϸ��ȫ����
#define GF_NET_CAUSE                12              //����ԭ����Ϸ����   yjj 081204


#define GFF_FORCE_CONTINUE          2               //add by yjj

#define  DEFAULT_AIOUT_TIMER        600
#define  DEFAULT_AUTO_HU_TIME       600
#define  DEFAULT_AIOUT_HANDLE_TIMER 601          //Ĭ���Զ������ʱ��


#define TIME_CHECK_GAME_MSG          30              // �����Ϸ��Ϣ���ݰ�����ʱû���յ����ݰ�����Ϊ�ǿ�ס�ˣ�ϵͳ�Զ�����
#define TIME_DEFAULT_HANDLE          60000			 // Ĭ��ʱ��60��

const int TIME_STEP = 31;           /// ʱ��
const int TIME_STEP_TIME = 500;     /// 

const int TIME_NETWORK = 1000;      /// �����ӳ�ʱ��

/** ��Ϸ�������� */
#define GF_NORMAL					10
/** ��Ϸ��ȫ���� */
#define GF_SALE						11	

/// ��Ϸ������
class CServerGameDesk : public CGameDesk
{
public:

protected:

public:

public:
	/// ���캯��
	CServerGameDesk(); 
	/// ��������
	virtual ~CServerGameDesk();

public:
	/// ��ʼ��Ϸ
	virtual bool	InitDeskGameStation();
	/// ��Ϸ��ʼ
	virtual bool	GameBegin(BYTE bBeginFlag);
	/// ��Ϸ����
	virtual bool	GameFinish(BYTE bDeskStation, BYTE bCloseFlag);
	/// �ж��Ƿ�������Ϸ
	virtual bool	IsPlayGame(BYTE bDeskStation);
	/// �����Ϣ������
	virtual bool	HandleFrameMessage(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser);
	/// ��Ϸ���ݰ�������
	virtual bool	HandleNotifyMessage(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser);
	/// �û��뿪��Ϸ��
	virtual BYTE	UserLeftDesk(BYTE bDeskStation, CGameUserInfo * pUserInfo);	
	//�����ı��û����������ĺ���
	//virtual bool	CanNetCut(BYTE bDeskStation);
	//��Ҷ��ߴ���
	virtual bool UserNetCut(BYTE bDeskStation, CGameUserInfo * pLostUserInfo);
	/// �������
	virtual BYTE	UserSitDesk(MSG_GR_S_UserSit * pUserSit, CGameUserInfo * pUserInfo);
	/// ��ȡ��Ϸ״̬��Ϣ
	virtual bool	OnGetGameStation(BYTE bDeskStation, UINT uSocketID, bool bWatchUser);
	/// ������Ϸ״̬
	virtual bool	ReSetGameState(BYTE bLastStation);
	/// ��ʱ����Ϣ
	virtual bool	OnTimer(UINT uTimerID);



	void KillAllTimer();


public:
	////////////�������ݶ���/////////////////////////////////////////////////////////
	///ͬ�������Ϸ���������
	BYTE			m_byAgreeLeaveNum;	

    BYTE			m_byGameStation;	//��Ϸ״̬

    int				m_RoomId;			//����id

	GameDataEx		sGameData;			//��Ϸ����	DWJ

	UserDataEx		sUserData;			//�û�����	DWJ

	CheckCPGActionEx sCPGAction;		//�����ܼ�ⷽ��

	CheckHuPaiEx	sCheckHuPai;		//���Ƽ�ⷽ��

	ThingHandleEx	m_sThingHandle;		//�¼�����
	vector <long int> m_vlSuperUserID;	//�������ID����
	int				m_iBase;			//����
	int				m_iFanBase;			//���ĵ���
	bool			m_bCanTing[PLAY_COUNT]; //�Ƿ��������

	CalculateBoard m_calculateMsg;

public:

	UINT m_uSocketID;

	///������Ϸ��ʱ��
	void SetGameTimer(UINT iId,int iTime);
	//ɾ��ָ����ʱ��
	void KillGameTimer(UINT iId);

    ///������Ϸ״̬
    void SendGameStationEx(BYTE bDeskStation, bool bWatchUser, void * pData, UINT uSize);
    ///�������ݺ��� ��������Ϣ����Ϸ�ߣ�
    void SendGameDataEx(BYTE bDeskStation, BYTE bMainID, BYTE bAssID, BYTE bHandleCode);
    ///�����Թ����� ��������Ϣ���Թ��ߣ�
    void SendWatchDataEx(BYTE bDeskStation, BYTE bMainID, BYTE bAssID, BYTE bHandleCode);
    ///�������ݺ��� ��������Ϣ����Ϸ�ߣ�
    void SendGameDataEx(BYTE bDeskStation, void * pData, UINT uSize, BYTE bMainID, BYTE bAssID, BYTE bHandleCode);
    ///�����Թ����� ��������Ϣ���Թ��ߣ�
    void SendWatchDataEx(BYTE bDeskStation, void * pData, UINT uSize, BYTE bMainID, BYTE bAssID, BYTE bHandleCode);
	//���ط�������
	void	LoadiniByRoom(int iRoomId);
	//�޸Ľ�������1(ƽ̨->��Ϸ)
	/// @param bAIWinAndLostAutoCtrl �����˿�����Ӯ����
	/// @return �Ƿ�ɹ�
	virtual bool SetRoomPond(bool	bAIWinAndLostAutoCtrl);

	//�޸Ľ�������2(ƽ̨->��Ϸ)
	/// @param m_iAIWantWinMoney ��������Ӯ���ƣ�������ӮǮ����1,2,3 4���öϵ�
	/// @param m_iAIWinLuckyAt ��������Ӯ���ƣ�������������1,2,3,4ӮǮ�ĸ���
	/// @return �Ƿ�ɹ�
	virtual bool SetRoomPondEx(__int64	iAIWantWinMoney[], int	iAIWinLuckyAt[]);

	//�޸Ľ�������3(ƽ̨->��Ϸ)
	/// @param iReSetAIHaveWinMoney ��������Ӯ���ƣ����û������Ѿ�ӮǮ����Ŀ
	/// @return �Ƿ�ɹ�
	virtual bool SetRoomPondEx(__int64	iReSetAIHaveWinMoney);

	//����ʤ��
	/// �ж�
	virtual BOOL Judge();
	/// ʤ
	virtual BOOL JudgeWiner();
	/// ��
	virtual BOOL JudgeLoser();
	//GRM����
	//���½�������(��Ϸ->ƽ̨)
	/// @return ������ӮǮ��
	virtual void UpDataRoomPond(__int64 iAIHaveWinMoney);

	virtual void DissmissRoomBefore();
};


/******************************************************************************************************/
