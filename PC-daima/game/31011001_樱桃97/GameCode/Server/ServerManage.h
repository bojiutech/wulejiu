#pragma once

#include "../../../../sdk/include/ServerCommon/GameDesk.h"

//��ʱ�� ID
#define TIME_MY_TIMER				20				//���ö�ʱ����ֻ�������ʱ����ʵ�ʶ�ʱ�������඼�Ǵ������ʱ�������ж�����
#define MY_ELAPSE					250				// ��ʱ�����
#define TIMER_COUNT					11				// �õ��Ķ�ʱ����Ŀ
/*---------------------------------------------------------------------*/
// ����Ϊ��Ϸ��ʹ�õ��Ķ�ʱ�����������TIME_MY_TIMER��������ͳһ����
#define	TIME_MIN					30				//��С��ʱ��ID
#define	TIME_MAX					50				//����ʱ��ID
/*---------------------------------------------------------------------*/

//��Ϸ������־����
#define GF_NORMAL					10				//��Ϸ��������
#define GF_SALE						11				//��Ϸ��ȫ����
/*---------------------------------------------------------------------*/

#define MAX_SEAT_COUNT              180              //������λ����

//���ؿ��Ʋ���
static int     G_i64Pond=0;                    //����ʽ�
static int     G_iAIControlHaveMoney=0;          //����
static __int64         m_i64SinglePond[MAX_SEAT_COUNT];                //���˲ʽ�
static unsigned int    m_iCheckPrize[MAX_SEAT_COUNT][18];              //��¼�鿴�󽱵�һҳ����
static unsigned int    m_iLineGameCount[MAX_SEAT_COUNT][12];           //��¼�鿴����һҳ����
static CRITICAL_SECTION	cs;

/*---------------------------------------------------------------------*/
//��Ϸ����
class CServerGameDesk : public CGameDesk
{
	CRITICAL_SECTION m_csForIPCMessage;

private:	
	int             m_iShangFenMoney;               //ÿ���϶��ٷ�

	int				m_iAIWinLuckyAtA1;				//����1�н�����
	int				m_iAIWinLuckyAtA2;				//����2�н�����
	int				m_iAIWinLuckyAtA3;				//����3�н�����
	int				m_iAIWinLuckyAtA4;				//��������3�н�����

	int			    m_iRewardLeve1;					//��Ϸ���� ���Ӵ󽱸���
	int			    m_iRewardLeve2;					//��Ϸ���� ���Ӵ󽱸���
	int			    m_iRewardLeve3;					//��Ϸ���� ���Ӵ󽱸���
	int             m_iRewardLeve4;                 //��Ϸ���� ���Ӵ󽱸���

	int             m_iFruitJuShuA1;                //��ȫˮ��������������1
	int             m_iFruitJuShuA2;                //��ȫˮ��������������2
	int             m_iFruitJuShuA3;                //��ȫˮ��������������3
	int             m_iFruitJuShuA4;                //��ȫˮ��������������4
	int             m_iFruitWinLuckyAtA1;           //��ȫˮ����������1
	int             m_iFruitWinLuckyAtA2;           //��ȫˮ����������2
	int             m_iFruitWinLuckyAtA3;           //��ȫˮ����������3
	int             m_iFruitWinLuckyAtA4;           //��ȫˮ����������4

	int             m_iAIControlSwitch;             //���ؿ��ƿ���
	int             m_iMinCaijinFen;                //�ܲʽ��͸������ͷ���ֵ
	int             m_iMaxCaijinFen;                //�ܲʽ��͸���ҵ�������ֵ
	int             m_iSpeCaijinFen;                //�ܲʽ��͸�ָ����ҷ���ֵ
       		
	int             m_iCaiJin[9];//ȫ�̲ʽ���
	int             m_iSecondControl;               //���ƶ��ν�������

	bool		    m_bIsPlaying;			        //��Ϸ�Ƿ��Ѿ���ʼ
	BYTE            m_byReJuShu;                    //���������ӷ֣���һ�Σ� ��3�� �� �� ��Ҳ�� �� 3�֣� �� �� �Σ� ��4��
	int             m_iJuShu;                       //���󽱾���
	int             m_iAllFruits;                   //��ȫˮ������
private:		/*��������*/

	bool			m_bClearPreWin;		            //�Ƿ��Զ��������ӮǮ��	
	int             m_maxCellBet;                   //�������ע��
	int             m_iPercentRoom;                 //����ʽ��ۻ����������ְٷ�֮��
	int             m_iPercentPerson;               //���˲ʽ��Ե�ǰ�����ְٷ�֮��
	int             m_Variety;                      //���˲ʽ�ɵ�����

	vector  <long>  m_lvSpecifyUserID;              //ָ�����ܲ�����б�

	vector	<long>	m_lvSuperUserID;	            //�����û��б�
	bool            m_bIsSuccesse;                  //���������Ƿ�ɹ�
	int             m_bySetSuperImg[9];             //������������

private:
	bool            m_bAllGame;                     //ȫ��
	bool            m_bWinLine[8];                  //�ĸ��߿���������
	BYTE            m_byPlayStly;                   //1:��������Ϸ  2������2����������  3������3����������  4������4����������
	BYTE            m_bySpecialRestCount;           //�����淨ʣ����� 
	BYTE			m_bySpecialCount;				//�����淨�ܾ���
	BYTE			m_bLineCount;		            //�н�����
	int             m_iAllCellMoney;				//��Ϸ�ܼ�ע	
	int             m_ImgType[9];                   //ͼ������
	int				m_iAllWinMoney;			        //����ӮǮ
	int             m_iCellMoney;		            //������ע��	
	int             m_iExtaPay;                     //���⽱��
	int             m_iAllJiangTip;                 //���д���ʾ��ֵ
	__int64         m_i64ShangFenMoney;             //����Ϸֽ��
	__int64         m_i64UserMoney;					//�������ԭ���Ľ����	
	__int64         m_i64UserSYMoney;               //����Ϸֳ����Ľ����

	int				m_iDoubleProbability;			//�����ĸ���(x/1000)
	int				m_iThreeProbability;			//�����ĸ���(x/1000)
	int				m_iFourProbability;				//�ı��ĸ���(x/1000)
	
	int             m_ilogoValue;                   //�ߵĸ���
	int             m_iGetZhongCai;                 //��õ��ܲʽ��ҷ�ֵ
	int             m_iRewardMoney;                 //�ʽ��������
	int             m_iSecondGetMoney;              //���ν����õ���Ǯ
	int             m_iSecondRewardMoney[9];           //���ν��������  �����ǣ������ߣ�ľ�ϣ����ӣ���BAR,ӣ�ң��壬��BAR,���ϣ���BAR

	int             m_iAllGameCount[12];          //ȫ�̴���
	__int64         m_i64AllBet;                  //ȫ����ע
	__int64         m_i64AllWin;                  //Ӯ������

	__int64			m_i64SystemWinMoney;			//ϵͳ��ӮǮͳ�ƣ������ǿͻ����ڲ鿴��

	int             m_iExchangeRateBS;              //�һ��������Ӵ��תС��
	int             m_iExchangeRateSB;             //�һ���������С��ת���
	BYTE            m_byThreeLine[9];             //�������
	BYTE            m_byAnyBar;                   //���ֳ���ANYBAR
	BYTE            m_byFirstCherry;              //һ��ӣ��
	BYTE            m_bySecondCherry;             //����ӣ��
	bool            m_bAnyBar;                    //ȫ������bar
	bool            m_bAllFruits;                 //ȫ��ˮ��
	int             m_iGetSinglePond;             //�����ݿ�ȡ�õ����ʻ�
	int				m_shareAward;				  //������ 
public:
	//���캯��
	CServerGameDesk(); 
	//��������
	virtual ~CServerGameDesk();

	//���غ���
public:
	//��Ϸ��ʼ
	virtual bool	GameBegin(BYTE bBeginFlag);
	//��Ϸ����
	virtual bool	GameFinish(BYTE bDeskStation, BYTE bCloseFlag);
	//�ж��Ƿ�������Ϸ
	virtual bool	IsPlayGame(BYTE bDeskStation);
	///�жϴ���Ϸ���Ƿ�ʼ��Ϸ
	virtual BOOL	IsPlayingByGameStation();
	//��Ϸ���ݰ�������
	virtual bool	HandleNotifyMessage(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser);
	//�����Ϣ������
	virtual bool	HandleFrameMessage(BYTE bDeskStation, NetMessageHead * pNetHead, void * pData, UINT uSize, UINT uSocketID, bool bWatchUser);
	//�û��뿪��Ϸ��
	virtual BYTE	UserLeftDesk(BYTE bDeskStation, CGameUserInfo * pUserInfo);
	///�û�������Ϸ��
	virtual BYTE	UserSitDesk(MSG_GR_S_UserSit * pUserSit, CGameUserInfo * pUserInfo);
	//�û�����
	virtual bool	UserNetCut(BYTE bDeskStation, CGameUserInfo * pUserInfo);
	//��ʼ��������Ϣ
	virtual bool	InitDeskGameStation();
	//��ȡ��Ϸ״̬��Ϣ
	virtual bool	OnGetGameStation(BYTE bDeskStation, UINT uSocketID, bool bWatchUser);
	//������Ϸ״̬
	virtual bool	ReSetGameState(BYTE bLastStation);
	//��ʱ����Ϣ
	virtual bool	OnTimer(UINT uTimerID);

	virtual  bool SetRoomPond(bool	bAIWinAndLostAutoCtrl);
	virtual  bool SetRoomPondEx(__int64	iAIWantWinMoney[], int	iAIWinLuckyAt[]);
	virtual  bool SetRoomPondEx(__int64	iReSetAIHaveWinMoney);
	/// �ж�
	virtual BOOL Judge();
	/// ʤ
	virtual BOOL JudgeWiner();
	/// ��
	virtual BOOL JudgeLoser();

private:
	//����Ϸֽ��
	void OnHandleShangFen(BYTE byStation,void *pdata,UINT uSize);
	//���ÿ���ϷֵĽ��
	__int64 GetUserSFMoney(BYTE byStation=0);
	//�����������
	void OnHandleStartRoll(BYTE byStation,void * pData, UINT uSize);
	//�����淨
	void getRandStyle();
	//������
	void getRandImgType();
	//���������
	int  GetDaJiangImgTpye();
	//��ҵ���鿴��
	void OnHandleCheckPrize(BYTE byStation,void * pData, UINT uSize);
	//��ҵ���鿴����һҳ
	void OnHandleNextPagePrize(BYTE byStation,void * pData, UINT uSize);
	//���ܿͻ�����Ϸ����
	void OnHandleGameOver(BYTE byStation,void * pData, UINT uSize);
	//���ܿͻ��˵ĳ�������
	void OnHandleSuperSet(BYTE byStation,void * pData, UINT uSize);

	void OnHandleShareAward(BYTE byStation, void* pData, UINT uSize);
	//��ȡ����
	void ChecKLine();
	//ϵͳ����
	void GetSystemReward();
	//����������
	void GetWinLine();
	//��ѯ�Ƿ��д�
	bool  CheckGainAward();
	//��ѯ�Ƿ��ȫˮ��
	bool  CheckGetAllFruits();
	//��ȡ���⽱��LOGO�ĸ���
	INT getLogoValue(INT imageValue[]);
	//�ж��Ƿ�ȫ����Ϸ
	bool isAllGame(INT imageValue[]);
	//��ȡ��������
	INT getLineReward(INT a, INT b, INT c);  

private:
	//��ʼ������Ϸ
	void	StartGame();
	//�Ƿ񳬼��û�
	bool	IsSuperUser(BYTE byStation);
	//�Ƿ���ָ���Ͳʽ����
	bool    IsSpecifyUser(BYTE byStation);
	//��ȡ�ܲʽ�
	void    GetZhongCai(BYTE byStation);
	
	//������
private:
	//��ո�λ�õ�����
	void	IniUserData(BYTE byStation);
	//��ȡ��̬����
	BOOL	LoadIni();	
	//���ݷ���ID���ص�ע������
	BOOL	LoadExtIni(int iRoomID);
	//�����ʽ��ۻ�
	void    GetSinglePond();
	//ͳ�Ʋ鿴����һҳ����
	void    CountPrePageData();
	//ͳ�Ʋ鿴����һҳ����
	void    CountNextPageData();

	void saveDeskData(int iDeskId, CString key, CString& value);

	int readDeskData(int iDeskId,CString key, int defaultValue);
};

/******************************************************************************************************/
