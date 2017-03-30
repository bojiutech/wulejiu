#pragma once

#include "StdAfx.h"

#include <fstream>

/// ��ʱ�� ID
#define TIME_SEND_CARD				30				///< ���ƶ�ʱ��
#define TIME_WAIT_NT				31				///< �ȴ�����
#define TIME_GAME_FINISH			32				///< ��Ϸ������ʱ��


/// �˿���Ŀ����
#define PLAY_TWO_CARD				1				///< �����˿�
#define PLAY_THREE_CARD				2				///< �����˿�

/// ��Ϸ������־����
#define GF_NORMAL					10				///< ��Ϸ��������
#define GF_SAFE						11				///< ��Ϸ��ȫ����


//////////////////////////////////////////////////////////////////////////
#define WZQ_FLAG_NONE				0
#define WZQ_FLAG_BLACK				1
#define WZQ_FLAG_WHITE				2
//#define WQ_FLAG_SIDE				3

#define WQ_FLAG_BLACK_CROSS			4
#define WQ_FLAG_WHITE_CROSS			5

#define WZQ_MAX_I					19
#define WZQ_MAX_J					19

#define WQ_BLACK_TIE_MU				(3.75)			///< ����Ŀ3��3/4��

enum WQ_PLAY_FLAG
{
	WZQ_BLACK_PLAYER = 0,
	WZQ_WHITE_PLAYER = 1
};

#define WZQ_NUMBER 5								///< 5����

///////////////////////////////////////////////////////////////////

/******************************************************************************************************/


/// ����
#define XQ_FLAG_NONE				0
#define XQ_FLAG_RED					1
#define XQ_FLAG_BLACK				-1

#define XQ_QIZI_NONE				0
#define XQ_CROSS					8

/// �췽
#define XQ_RED_JU					1
#define XQ_RED_MA					2
#define XQ_RED_PAO					3
#define XQ_RED_JIANG				6
#define XQ_RED_SHI					4
#define XQ_RED_XIANG				5
#define XQ_RED_BIN					7

/// �ڷ�
#define XQ_BLACK_JU					-1
#define XQ_BLACK_MA					-2
#define XQ_BLACK_PAO				-3
#define XQ_BLACK_JIANG				-6
#define XQ_BLACK_SHI				-4
#define XQ_BLACK_XIANG				-5
#define XQ_BLACK_BIN				-7

#define XQ_MAX_I					(10)
#define XQ_MAX_J					(9)

/******************************************************************************************************/
/******************************************************************************************************/

/*
//�߼��� //�������������
class CUpGradeGameLogic
{
	//��������
private:
	
	//��������
public:
	//���캯��
	CUpGradeGameLogic(void);
	

	//���ܺ���������������
public:

	void NumQiZi(float *totalBlack, float *totalWhite, int qi[][21]);
	
private:
		
	int GetEmptyFlag(int pi,int pj,int qi[][21]);
	
};
*/

//*****************************************************************************************

/// ��Ϸ����
class CServerGameDesk : public CGameDesk
{
protected:
	/// ��Ϸ��������
	BYTE					m_CardCount;						///< �˿���Ŀ��λ������

	/// �����������
	BYTE					m_iLessCount;						///< ������Ϸ����
	BYTE					m_iPlayCardCount;					///< ��Ϸ�˿���Ŀ
	BYTE					m_iBeginStation;					///< ��Ϸ��ʼλ��
	BYTE					m_iEndStation;						///< ��Ϸ����λ��
	BYTE					m_iEnableWatch;						///< �Ƿ������Թ�

	int						m_iJuTimeMinute,					///< ��ʱ
							m_iJuTimeSecond,
							m_iBuTimeMinute,					///< ��ʱ
							m_iBuTimeSecond,
							m_iDuMiaoMinute,					///< ����
							m_iDuMiaoSecond;
	__int64					m_iGuidandeMoney;					///< ָ����

	/// ����״̬����
	int						m_PunishPoint[4];					///< �û�����
	int						m_iUpGradePeople;					///< ׯ��λ��
	BYTE					m_iBeenPlayGame;					///< �Ѿ���Ϸ�ľ���
	BYTE					m_iLeaveArgee;						///< �뿪ͬ���־

	/// ������Ϣ
	int						m_iGamePoint;						///< �û���Ϸ����
	int						m_iOutCardPeople;					///< ���ڳ����û�
	int						m_iFirstOutPeople;					///< �ȳ��Ƶ��û�

	//CUpGradeGameLogic		m_Logic;							///< ��Ϸ�߼�
	bool					m_bQueryQuit;						///< ����������˳�

	int						m_iWinFlag;							///< ��ʤ��
	int						m_iTurePoint[2];					///< ��ʵ�÷�
	int						m_iWinNum[2];						///< ����Ӯ�Ĵ��������ȷ�

	bool					m_bFirstRed;
	bool					m_bQiuHe;
	
	int						m_iBoard[19][19];
	int						m_idianmu[19][19];
	int						m_iQiZiNum[2];						///< ͳ�ƺڰ��������µ����������������ӣ�
	int						m_iQiZiLastNum[2];					///< ����˫��������
	int						m_iTiZiNum[2];

	/// ��������
	int						m_iLastDeskStation;					///< �ϲ������ߵ�λ��
	int						m_iLastBoard[19][19];				///< �ϲ����
	int						m_iLastTiZiNum[2];					///< �ϲ�������
	int						m_Endi;								///< ��һ������λ��
	int						m_Endj;								///< ��һ������λ��
	int						m_iBlackStation;					///< ����λ��
	int						m_iWhiteStation;					///< ����λ��

	int						m_iFinishNumCnt;					///< ��ɵ�Ŀ
	int						m_iDianMuResult;					///< ��Ŀ�������
	CString					m_dianmumsg;

	bool                    m_bUserNetCut[PLAY_COUNT];  //�û�����
	UsedTimeInfo			m_stUsedTimeInfo;//�Ѿ�ʹ�õ�ʱ����Ϣ
	
	/*
	 ���±�������Ϊ�˷�ֹһ�����ٽ���ʱ���������
	 �������������ٽ�����һ��������������󣬵��Է������ӣ����ڷ�������ֱ��ȡ�����������;
	 Data:   2008.07.17
	*/
	int                     m_playerChessNum[2];				///< ���˫�����µ�������
	bool					m_bIsInHuiquStation[2];				///< �Ƿ��ڻ���״̬

	/// ��������
public:
	/// ���캯��
	CServerGameDesk(); 
	/// ��������
	virtual ~CServerGameDesk();

	/// ���غ���
public:
	/// ��Ϸ��ʼ
	virtual bool GameBegin(BYTE bBeginFlag);
	/// ��Ϸ����
	virtual bool GameFinish(BYTE bDeskStation, BYTE bCloseFlag);
	/// �ж��Ƿ�������Ϸ
	virtual bool IsPlayGame(BYTE bDeskStation);
	/// ��Ϸ���ݰ�������
	virtual bool HandleNotifyMessage(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser);
	/// �û��뿪��Ϸ��
	virtual BYTE UserLeftDesk(BYTE bDeskStation, CGameUserInfo * pUserInfo);
	//��Ҷ��ߴ���
	virtual bool UserNetCut(BYTE bDeskStation, CGameUserInfo * pLostUserInfo);
	//�û����½�����Ϸ
	virtual  bool UserReCome(BYTE bDeskStation, CGameUserInfo * pLostUserInfo);

	/// ���ش��麯��
public:
	/// ��ȡ��Ϸ״̬��Ϣ
	virtual bool OnGetGameStation(BYTE bDeskStation, UINT uSocketID, bool bWatchUser);
	/// ������Ϸ״̬
	virtual bool ReSetGameState(BYTE bLastStation);
	/// ��ʱ����Ϣ
	virtual bool OnTimer(UINT uTimerID);
	/// ������
public:
	/// �û�������Ϸ
	BOOL UserSetGame(UserArgeeGame * pGameSet,BYTE desk);
	/// ��Ϸ׼������
	BOOL GameReady();
	/// ��Ϸ��ʼ
	BOOL BeginPlayUpGrade();	
	/// �û�����
	bool UserOutCard(BYTE bDeskStation, int iPlayQi[][21], int chessColor, int iEndI, int iEndJ);
	/// �¼Ӻ���
	BOOL UserOutCard(BYTE bDeskStation,int iPlayer,int iEndI,int iEndJ);
	/// ����ĺ������û�����ʱ�����BUG
	/// �û������¹��ܺ���
	BOOL UserOutCard(BYTE bDeskStation,int iEndI,int iEndJ);
	/// �ܷ����(�������Լ����)
	BOOL CanFinish(BYTE PutStoneDeskStation,BOOL bCanFinish = false);
	/// ���նˁ�yӋ�Ƿ�Y��
	BOOL IsFinish(int iEndI,int iEndJ,int Value);
	/// ��һ�ֿ�ʼ
	BOOL NewPlayTurn(int iWiner);
	/// �û������뿪
	bool UserHaveThing(BYTE bDeskStation, char * szMessage);
	/// ͬ���û��뿪
	bool ArgeeUserLeft(BYTE bDeskStation, BOOL bArgee);
	/// ������
	int	GetUpGrade(int iPlayCardCount);
	/// ǿ������
	void ForceNumberZi(int &iWinFlag, CString &strMessage);
	/// ����
	int Judge(int nX, int nY, char cValue);
	/// ��Ϸ����
	int CountWinPiont();
	/// ���䱶��
	int GetRoomBasePoint();
	/// ���ӱ���
	int GetDeskBasePoint();
	/// ��ͷ����
	int GetHumanBasePoint();
	/// ���ܿ۷�
	int GetRunPublish();
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
};

/******************************************************************************************************/
