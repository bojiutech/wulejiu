#pragma once

#ifndef AFC_SERVER_SHOWHAND_MESSAGE_HEAD_FILE
#define AFC_SERVER_SHOWHAND_MESSAGE_HEAD_FILE

#ifdef VIDEO
#define GAMENAME					TEXT("��������Ƶ��")
#define NAME_ID						30000302							///< ���� ID
#else
#define GAMENAME					TEXT("������")
#define NAME_ID						30000302							///< ���� ID
#endif

/// �ļ����ֶ���
/// �汾����
#define GAME_MAX_VER				1									///< ������߰汾
#define GAME_LESS_VER				1									///< ������Ͱ汾
#define GAME_CHANGE_VER				0									///< �޸İ汾

/// ֧������
#define SUPPER_TYPE					SUP_NORMAL_GAME|SUP_MATCH_GAME|SUP_MONEY_GAME
#define GAME_TABLE_NAME				"WZQ"
/// ��Ϸ��Ϣ

#define PLAY_COUNT					2									///< ��Ϸ����

#define MAIN_VERSION                704									///< ���汾��,?��?��
#define ASS_VERSION                 21									///< �����汾��,?��


/// ��Ϸ�����汾
#define DEV_HEIGHT_VERSION				8								///< �ڲ������߰汾��
#define DEV_LOW_VERSION					8								///< �ڲ������Ͱ汾��

/// ��Ϸ״̬����
#define GS_WAIT_SETGAME					0								///< �ȴ���������״̬
#define GS_WAIT_ARGEE					1								///< �ȴ�ͬ������
#define GS_SEND_CARD					20								///< ����״̬
#define GS_WAIT_BACK					21								///< �ȴ���ѹ����
#define GS_PLAY_GAME					22								///< ��Ϸ��״̬
#define GS_WAIT_NEXT					23								///< �ȴ���һ�̿�ʼ 

//#define SKIN_FOLDER						TEXT("wzq")					///< ͼƬ�ļ���
//#define SKIN							TEXT("cardskin1")				///< ����ͼƬ����һ��
//#define SKIN_CARD						TEXT("card")					///< ����ͼƬ�ļ���

#define GET_STRING(NUM)                 #NUM
#define INT_TO_STR(NUM)                 GET_STRING(NUM)
#define CLIENT_DLL_NAME                 TEXT(INT_TO_STR(NAME_ID)##".ico")        ///<  �ͻ���ico����
#define SKIN_FOLDER                     TEXT("")//TEXT(INT_TO_STR(NAME_ID))      ///<  �ͻ���Ŀ¼


#define BOARD_LINE_NUMBER				19								///< ���̴�С
/********************************************************************************/
#define ALLOW_SYSTEM_AUTO				0								///< ϵͳ�й����0����,1������,2ϵͳ�й�
//��Ϸ���ݰ�
/********************************************************************************/

//��Ϸ��ʹ���˵�ʱ����Ϣ jph100127
struct UsedTimeInfo
{
	int m_iJuUseTime[2];
	int	m_iBuUseTime[2];
	int	m_iDuUseTime[2];
	UsedTimeInfo()
	{
		memset(m_iJuUseTime,0,sizeof(m_iJuUseTime));
		memset(m_iBuUseTime,0,sizeof(m_iBuUseTime));
		memset(m_iDuUseTime,0,sizeof(m_iDuUseTime));
	}
};

///ָ�������ݰ�
struct GuidanceMoney
{
	__int64		iGuidandeMoney;	
};

/// ��Ϸ״̬���ݰ�	�� �ȴ���������״̬ ��
struct GameStation_1
{

	/// ��Ϸ��Ϣ
	BYTE			iCardCount;											///< �˿���Ŀ
	/// ��Ϸ�汾
	BYTE				iVersion;										///< ��Ϸ�汾��
	BYTE				iVersion2;										///< ��Ϸ�汾��
	int					iRoomBasePoint;									///< ���䱶��
	int					iRunPublish;									///< ���ܿ۷�

};

/// ��Ϸ״̬���ݰ�	�� �ȴ�������ҿ�ʼ ��
struct GameStation_2
{
	/// ��Ϸ�汾
	BYTE				iVersion;										///< ��Ϸ�汾��
	BYTE				iVersion2;										///< ��Ϸ�汾��
	int					iRoomBasePoint;									///< ���䱶��
	int					iRunPublish;									///< ���ܿ۷�

	int			iJuTimeMinute;											///< ��ʱ��
	int			iJuTimeSecond;											///< ��ʱ��
	int			iBuTimeMinute;											///< ��ʱ��
	int			iBuTimeSecond;											///< ��ʱ��
	int			iDuMiaoMinute;											///< �����
	int			iDuMiaoSecond;											///< ������
	__int64		iGuidandeMoney;											///< ������
};

/// ��Ϸ״̬���ݰ�	�� ��Ϸ���ڷ���״̬ ��
/// ��Ϸ״̬���ݰ�	�� �ȴ���Ѻ����״̬ ��
struct GameStation_3
{
	/// ��Ϸ�汾
	BYTE				iVersion;						///< ��Ϸ�汾��
	BYTE				iVersion2;						///< ��Ϸ�汾��
	int					iRoomBasePoint;					///< ���䱶��
	int					iRunPublish;					///< ���ܿ۷�
	/// ��Ϸ��Ϣ
	BYTE				iBeginStation;					///< ��ʼλ��
	BYTE				iEndStation;					///< ����λ��
	BYTE				iMeStation;
	BYTE				iOtherStation;
	BYTE				iPlayCount;						///< ��Ϸ����
	BYTE				iCardCount;						///< �˿���Ŀ

	/// ����״̬����
	int					iWinPoint;						///< ��Ϸ����
	int					iPunishPoint;					///< �û�����
	int					iUpGradePeople;					///< ׯ��λ��
	BYTE				iPlayNTNum[2];					///< ����ҵ�������Ŀ
	BYTE				iBeenPlayGame;					///< �Ѿ���Ϸ�ľ���

	/// ������Ϣ
	int					iNtPeople;						///< �������
	BYTE				iNtHua;							///< ���ƻ�ɫ
	BYTE				iNtCardCount;					///< ��������

	/// ״̬��Ϣ
	BYTE				iUserCardCount;					///< �û������˿���Ŀ
	BYTE				iUserCard[45];					///< �û����ϵ��˿�

};

/// ��Ϸ״̬���ݰ�	�� ��Ϸ��״̬ ��
struct GameStation_4	
{
	/// ��Ϸ�汾
	BYTE				iVersion;						///< ��Ϸ�汾��
	BYTE				iVersion2;						///< ��Ϸ�汾��
	int					iRoomBasePoint;					///< ���䱶��
	int					iRunPublish;					///< ���ܿ۷�
	/// ��Ϸ��Ϣ
	int			iJuTimeMinute;							///< ��ʱ��
	int			iJuTimeSecond;							///< ��ʱ��
	int			iBuTimeMinute;							///< ��ʱ��
	int			iBuTimeSecond;							///< ��ʱ��
	int			iDuMiaoMinute;							///< �����
	int			iDuMiaoSecond;							///< ������
	__int64		iGuidandeMoney;							///< ��Ϸָ����

	BYTE				iPlayCount;						///< ��Ϸ����
	BYTE				iBeenPlayGame;					///< �Ѿ���Ϸ�ľ���
	int					iOutCardPeople;					///< ���ڳ����û�
	int					iFirstOutPeople;				///< �ȳ��Ƶ��û�
	int					iQiZi[21][21];
	int					iTiZiNum[2];
	int					iQiZiNum[2];					///< ����������
	int					iEndI;
	int					iEndJ;
	int                 iUpGradePeople;                 ///< ׯ��,����
	UsedTimeInfo		m_stUsedTimeInfo;					//ʹ�ù���ʱ��

	bool				bIsInHuiquStation[2];///< ����״̬s
};

/// ��Ϸ״̬���ݰ�	�� �ȴ����̿�ʼ״̬  ��
struct GameStation_5
{
	/// ��Ϸ�汾
	BYTE				iVersion;						///< ��Ϸ�汾��
	BYTE				iVersion2;						///< ��Ϸ�汾��
	int					iRoomBasePoint;					///< ���䱶��
	int					iRunPublish;					///< ���ܿ۷�
	/// ��Ϸ��Ϣ
	BYTE				iBeginStation;					///< ��ʼλ��
	BYTE				iEndStation;					///< ����λ��
	BYTE				iPlayCount;						///< ��Ϸ����
	BYTE				iCardCount;						///< �˿���Ŀ

	/// ����״̬����
	int					iWinPoint;						///< ��Ϸ����
	int					iPunishPoint;					///< �û�����
	int					iUpGradePeople;					///< ׯ��λ��
	BYTE				iPlayNTNum[2];					///< ����ҵ�������Ŀ
	BYTE				iBeenPlayGame;					///< �Ѿ���Ϸ�ľ���
};

/// �û�ͬ����Ϸ
struct UserArgeeGame
{

	int			iJuTimeMinute;							///< ��ʱ��
	int			iJuTimeSecond;							///< ��ʱ��
	int			iBuTimeMinute;							///< ��ʱ��
	int			iBuTimeSecond;							///< ��ʱ��
	int			iDuMiaoMinute;							///< �����
	int			iDuMiaoSecond;							///< ������
	__int64		iGuidandeMoney;							///< ������

	//BYTE				iBeginStation;					///< ��ʼλ��
	//BYTE				iEndStation;					///< ����λ��
	//BYTE				iPlayCount;						///< ��Ϸ����
	//BYTE				iCardCount;						///< �˿���Ŀ
};

/// ��Ϸ׼��,����λ��,����λ��
struct GameReadyStruct
{
	BYTE				iBlackStation;					///< ����λ��
	BYTE				iWhiteStation;					///< ����λ��
};

/// ��Ϸ��ʼ
struct BeginUpgradeStruct
{
	BYTE				iUpgradeStation;				///< ׯ��λ��
	BYTE				iPlayCount;						///< ��Ϸ�غ�
	BYTE				iNtStation;						///< ���ڵ�����
	BYTE				iStation[2];					///< ���Ƶ�λ��
};

/// �������ݰ�
struct SendCardStruct
{
	BYTE				iCard;							///< �Ʊ��
};

/// ���������ݰ�  �������������
struct ClientNtStruct
{
	BYTE				iHuaKind;						///< �Ʊ��
	BYTE				iCardCount;						///< ������Ŀ
};

/// ���������ݰ�  ������ͻ��ˣ�
struct ServerNtStruct
{
	BYTE				bDeskStation;					///< ����λ��
	BYTE				iHuaKind;						///< ��ɫ
};

/// �������ݰ�
struct BackCardStruct
{
	BYTE				iBackCardCount;					///< �˿���Ŀ
	BYTE				iBackCard[8];					///< ��������
};

/// �������ݰ�
struct BackCardExStruct
{
	BYTE				iNtHua;							///< ���ƻ�ɫ
	BYTE				iGiveBackPeople;				///< �������
	BYTE				iBackCardCount;					///< �˿���Ŀ
	BYTE				iBackCard[8];					///< ��������
};

/// ������״̬���ݰ�
struct BackStationStruct
{
	BYTE				iNtPeople;						///< ����λ��	
	BYTE				iGiveBackStation;				///< ����λ��
};

/// ��Ϸ��ʼ���ݰ�
struct BeginPlayStruct
{
	BYTE				iOutDeskStation;				///< ���Ƶ�λ��
	int			iJuTimeMinute;											///< ��ʱ��
	int			iJuTimeSecond;											///< ��ʱ��
	int			iBuTimeMinute;											///< ��ʱ��
	int			iBuTimeSecond;											///< ��ʱ��
	int			iDuMiaoMinute;											///< �����
	int			iDuMiaoSecond;											///< ������
	__int64		iGuidandeMoney;											///< ������
};

/// �û��������ݰ� �������������
struct OutCardStruct
{
	int					iCardCount;						///< �˿���Ŀ
	BYTE				iCardList[39];					///< �˿���Ϣ
};

/// �û�˦��ʧ�����ݰ� ������ͻ��ˣ�
struct OutShowCardStruct
{
	BYTE				iCardCount;						///< �˿���Ŀ
	BYTE				bDeskStation;					///< ��ǰ������
	BYTE				iResultCount;					///< ����˿���Ŀ
	BYTE				iCardList[78];					///< �˿���Ϣ
};

/// �û��������ݰ� ������ͻ��ˣ�
struct OutCardMsg
{
	int					iNextDeskStation;				///< ��һ������
	BYTE				iCardCount;						///< �˿���Ŀ
	BYTE				bDeskStation;					///< ��ǰ������
	BYTE				iCardList[39];					///< �˿���Ϣ
};

/// �û��������ݰ� ������ͻ��ˣ�
struct BatchOutCardMsg
{
	BYTE				iCardCount;						///< �˿���Ŀ
	BYTE				iCardList[156];					///< �˿���Ϣ
};

/// ��ҵķ����ݰ�
struct GamePointStruct
{
	bool				bAdd;
	int					iPoint;							///< �÷���Ŀ
};

/// ��Ϸ����ͳ�����ݰ�
struct GameEndStruct
{
	int					iGamePoint;						///< ��Ϸ�÷�
	__int64				iTurePoint[4];					///< ׯ�ҵ÷�
	__int64				iChangeMoney[8];				///< ���
	BYTE				iUpGradeStation;				///< ׯ��λ��
	BYTE				iDoublePointEffect;				///< ˫�����ֿ�����Ч�� 20081125
	int					iWinNum[2];						///< �ȷ�
};

/// ��Ϸ����ͳ�����ݰ�
struct GameCutStruct
{
	int					bDeskStation;					///< �˳�λ��
	__int64					iTurePoint[2];					///< ��ҵ÷�
	__int64					iChangeMoney[8];				///< ���
	BYTE				iDoublePointEffect;				///< ˫�����ֿ�����Ч��
	char				cNickName[PLAY_COUNT][61];		///�������
};

struct HaveThingStruct
{
	BYTE pos;
	char szMessage[61];
};

struct LeaveResultStruct
{
	BYTE bDeskStation;
	int bArgeeLeave;
};

/// �ͻ��˵�������
struct MessageStruct	
{
	char Message[200];
};

struct StopResultStruct
{
	bool bArgee;
};

///�������ݰ�������ͻ��ˣ�
struct PlayChessMsg
{	
	//int					iStartI;
	//int					iStartJ;
	int					iEndI;
	int					iEndJ;
	int					iPlayFlag;
	int					iTiZiNum[2];					///< ������
	int					iChessArray[21][21];
	int					iNextPlayStation;
	int					iQiZiNum[2];
};

/// �z���Ƿ�Y��
struct PlayCheckFinish
{
	BOOL bCanFinish;
	int iCurI;
	int iCurJ;
	char cValue;
};
/*
struct DianMu
{
int qi[21][21];
};
*/

/*
struct FinishDianMu
{
int qi[21][21];
char msg[50];
};
*/

/// �������ݰ�(����ͻ���)
struct RegretChessMsg
{
	int		iLastChessArray[21][21];					///< ��¼�ϲ����
	int		iLastTiZiNum[2];							///< ��¼�ϲ�������
	int		iLastDeskStation;							///< �����ߵ�λ��
};

/*
struct DianMuResultStruct	//��Ŀ
{
bool bAgree;
};
*/

/// ��Ϸ����
struct GameFinishNotify
{
	int	 iUpGradePeople;
	int iGrade2;
	TCHAR name[4][21];
	//	int	iBasePoint;
	BYTE iStyle;										///< ��Ϸ�����Ƿ�Ϊǿ��,������������
	__int64 	iWardPoint[4];
	//__int64 iTotalPoint[4];
	//int iAwardPoint[4];		//����
	//	int iGetPoint[4];		//����ץ��
	//	int nt;					//���s
	__int64    iMoney[4];
};

/********************************************************************************/
// ���ݰ���������ʶ
/********************************************************************************/

#define ASS_UG_USER_SET					50				///< �û�������Ϸ
#define ASS_BEGIN_UPGRADE				51				///< ������Ϸ��ʼ
#define ASS_SEND_CARD					52				///< ������Ϣ
#define ASS_NT_CARD						53				///< �û�����
#define ASS_SEND_FINISH					54				///< �������
#define ASS_BACK_CARD					55				///< ��������
#define ASS_BACK_CARD_EX				56				///< ��������
#define ASS_BACK_CARD_RES				57				///< �������ݽ��
#define ASS_WAIT_BACK					58				///< �û�������
#define ASS_GAME_PLAY					59				///< ��ʼ��Ϸ
#define ASS_OUT_CARD					60				///< �û�����
#define ASS_OUT_CARD_RESULT				61				///< ���ƽ��
#define ASS_CAN_FINISH					62				///< �����Ƿ���Խ���
#define ASS_GAME_READY					63				///< ��Ϸ׼������
//#define ASS_SHOW_CARD					61				///< ˦��ʧ��
//#define ASS_BATCH_OUT					62				///< ��������
//#define ASS_GAME_POINT					63			///< �û�����
//#define ASS_NEW_TURN					64				///< ��һ�ֿ�ʼ
#define ASS_CONTINUE_END				65				///< ��Ϸ����
#define ASS_NO_CONTINUE_END				66				///< ��Ϸ����
#define ASS_CUT_END						67				///< �û�ǿ���뿪
#define ASS_SALE_END					68				///< ��Ϸ��ȫ����
#define ASS_HAVE_THING					69
#define ASS_LEFT_RESULT					70
#define ASS_MESSAGE						71
#define ASS_STOP_THING					72
#define ASS_AGREE_STOP					73
#define ASS_SUPER_TIMER					74				///< ��ʱ����
#define ASS_REN_SHU						75				///< ����
#define ASS_HUI_QI						76				///< ����
#define ASS_AGREE_HUI_QI				77				///< ͬ�����
#define ASS_AGREE_HUI_QI_PHONE			78				///< ͬ����� �ֻ�ר��
#define ASS_GET_GAME_USED_TIME			95				//��ȡʹ��ʱ��

//#define ASS_DIAN_MU						79			///< ��Ŀ
//#define ASS_AGREE_DIAN_MU				80				///< ͬ���Ŀ
//#define ASS_NUMBER_ZI					81				///< ǿ������
//#define ASS_DIAN_MU_RESULT				82			///< ��Ŀ�������
#define ASS_LOCK_END					83				///< ��ʤ��֮����������

/********************************************************************************/
#endif
