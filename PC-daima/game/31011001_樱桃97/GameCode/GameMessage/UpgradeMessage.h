#pragma once

#ifndef AFC_SERVER_SHOWHAND_MESSAGE_HEAD_FILE
#define AFC_SERVER_SHOWHAND_MESSAGE_HEAD_FILE

//�ļ����ֶ���
#define GAMENAME						TEXT("ӣ��97")
#define GAME_DLL_AUTHOR                 TEXT("���ں�������Ƽ�")            //
#define GAME_DLL_NOTE                   TEXT("������ -- ��Ϸ���")


#define NAME_ID							31011001						//���� ID
#define KIND_ID							3				                // ���� ID

//�汾����
#define GAME_MAX_VER					1								//������߰汾
#define GAME_LESS_VER					1								//������Ͱ汾
#define GAME_CHANGE_VER					0								//�޸İ汾

//֧������
#define SUPPER_TYPE						SUP_NORMAL_GAME|SUP_MATCH_GAME|SUP_MONEY_GAME
//��Ϸ��Ϣ

#define PLAY_COUNT						1								//��Ϸ����

//��Ϸ�ڲ������汾��
#define DEV_HEIGHT_VERSION				3				//�ڲ������߰汾��(ÿ����һ��LOW_VERSIONG+1)
#define DEV_LOW_VERSION					1				//�ڲ������Ͱ汾��

//#define SKIN_FOLDER					TEXT("ddz")	//ͼƬ�ļ���
//#define SKIN							TEXT("cardskin1")	//����ͼƬ����һ��
#define SKIN_CARD						TEXT("cardskin")		//����ͼƬ�ļ���
static TCHAR szTempStr[MAX_PATH] = {0};//�ݴ��ַ�����������ȡ dll_name �ȵ�ʱ��ʹ��
#define GET_CLIENT_DLL_NAME(A)			(sprintf(A,"%d",NAME_ID),strcat(A,".ico"))
#define GET_SERVER_DLL_NAME(A)			(sprintf(A,"%d",NAME_ID),strcat(A,".dll"))
#define GET_SKIN_FOLDER(A)              (sprintf(A,"%d",NAME_ID),strcat(A,""))     //��ȡͼƬ�ļ���
#define GET_KEY_NAME(A, B, C, D)		(sprintf(A,"%s%d%s", B, C, D),strcat(A,""))
#define GET_CLIENT_BCF_NAME(A)          (sprintf(A,"%d",NAME_ID),strcat(A,".bcf"))    

#define SUPER_PLAYER                    10                         //�������
#define MAX_NAME_INFO                   256

//��Ϸ״̬����
#define GS_WAIT_SETGAME					0				//�ȴ���������״̬
#define GS_WAIT_ARGEE					1				//�ȴ�ͬ������

#define GS_WAIT_START                   20              //�ȴ���ʼ
#define GS_PLAY_GAME					21				//��ʼ��Ϸ��
#define GS_WAIT_NEXT					22				//�ȴ���һ�̿�ʼ 

/********************************************************************************/
//��Ϸ���ݰ�

/********************************************************************************/
/*-------------------------------------------------------------------------------*/

#pragma pack(1)

///�������ݰ�
struct	S_C_TagSuperUser
{	
	BYTE		byStation;			///λ��
	bool        bIsSuper;           /**< �Ƿ�ͨ */

	S_C_TagSuperUser()
	{
		byStation = -1;
		bIsSuper = false;
	}
};

//�����������ݰ�
struct	C_S_TagSuperSet
{	
	bool		bSuccesse;			//�����Ƿ�ɹ�
	int		    bySetSuperImg[9];	

	C_S_TagSuperSet()
	{
		memset(this,0,sizeof(C_S_TagSuperSet));
		bSuccesse = false;
	}
	void	init()
	{
		memset(this,0,sizeof(C_S_TagSuperSet));
		bSuccesse = false;
	}
};

//��Ϸ״̬�������ݰ�
struct  S_C_GameStation
{
	BYTE			byGameStation;					//��Ϸ״̬
	int             iExchangeRateBS;				//�һ��������Ӵ��תС��
	int             iExchangeRateSB;				//�һ���������С��ת���
	int				iCellBet;						//��ߵ���Ͷע��
	__int64			i64UserMoney;					//�û��Ľ����
	__int64         i64Pond;						//���ؽ��
	__int64         i64SinglePond;                    //�����ʽ�
	char			szGameRoomName[61];
	BYTE			bDeskIndex;							///< ���Ӻ���
	S_C_GameStation()
	{
		memset(this, 0 , sizeof(S_C_GameStation));
	}
};
/*-------------------------------------------------------------------------------*/

//��Ϸ��ʼ���ݰ�
struct S_C_GameBegin
{
	bool	bStart;
	BYTE    byGameStation;
	S_C_GameBegin()
	{
		memset(this, 0 , sizeof(S_C_GameBegin));
	}
};

struct C_S_ShareAward{
	int iShareAward;
	C_S_ShareAward(){
		memset(this,0,sizeof(C_S_ShareAward));
	}
};

struct S_C_ShareAwardResult{
	int iShangFenMoney;
	S_C_ShareAwardResult(){
		memset(this, 0, sizeof(S_C_ShareAwardResult));
	}
};

//�Ϸ�
struct C_S_ShangFen
{
	bool  bIsShangFen;      //1���Ϸ�   0���·�
	C_S_ShangFen()
	{
		memset(this,0,sizeof(C_S_ShangFen));
	}
};

//�Ϸֽ��
struct S_C_ShangFenResult
{
	int        iShangFenMoney;   //�Ϸֽ��
	__int64    i64UserMoney;     //���Ǯ
	S_C_ShangFenResult()
	{
		memset(this,0,sizeof(S_C_ShangFenResult));
	}
};

/*-------------------------------------------------------------------------------*/
//��ʼ����
struct C_S_StartRoll
{
	//��ǰ���߷���
	INT         byDeposit;
	//Ͷע����
	BYTE        byLines;
	C_S_StartRoll()
	{
		memset(this,-1,sizeof(C_S_StartRoll));

	}
};

/*-------------------------------------------------------------------------------*/
//������Ϣ
struct S_C_TypeScroll
{  
	bool                           bAllGame;              //ȫ��
	bool                           bWinAreaFlag[8];       //�������н�  0-7���ֱ��ӦA-H
	bool                           iLogoResult[9];        //���⽱��ͼƬ7 ��λ��
	BYTE                           byPlayStly;            //0:��������Ϸ  1������2����������  2������3����������  3������4����������
	BYTE                           bySpecialRestCount;    //�����淨ʣ����� 
	BYTE                           byZhongLine;           //�н�����
	int                            iExtaPay;              //���⽱��
	int                            iGetCaiJin;            //���òʽ�
	int                            iZhongCaiJin;          //�����ܲʽ�
	int                            iSecondGetMoney;       //���ö��ν������
	int                            iTypeImgid[9];         //ͼ������
	int                            iShangFenMoney;        //�Ϸֽ��
	int                            iWinMoney;             //��Ӯ����
	int                            iLogoValue;            //���⽱��ͼƬ(7)����     
	__int64                        iSinglePond;           //�����ʻ�
	int							   iShareAward;			  //������
	BYTE						   bySpecialtCount;		  //�����淨���ܾ���

	S_C_TypeScroll()
	{
		memset(this,0,sizeof(S_C_TypeScroll));
	}
};
//���ظ������ݰ�
struct S_C_Pond
{
	bool    bFlag;             //�Ƿ��д�
	BYTE    byStation;         //�н�������     
	char    szNickName[61];    //˭

	__int64 i64GetPond;        //���н��
	__int64 i64Pond;           //���ؽ��
	
	S_C_Pond()
	{
		memset(this,0,sizeof(S_C_Pond));
	}
};

//�鿴������
struct S_C_Check_Prize
{
	unsigned int      iAllGameCount[18];          //ȫ�̴���
// 	int               iFlashDian;                 //����
// 	__int64           i64AllBet;                  //ȫ����ע
// 	__int64           i64AllWin;                  //Ӯ������

	S_C_Check_Prize()
	{
		memset(this,0,sizeof(S_C_Check_Prize));
	}
};

//�鿴��һҳ�н�����
struct C_S_Next_Prize
{
	bool          bFlag;                    //trueΪ�鿴
	C_S_Next_Prize()
	{
		bFlag = false;
	}
};

//�鿴��һҳ�н�����
struct S_C_Next_Prize
{
	unsigned int     iLineGameCount[12];       //�����н�����
	S_C_Next_Prize()
	{
		memset(this,0,sizeof(S_C_Next_Prize));
	}
};

//����
struct C_S_GameEnd
{
	bool       bGameOver;      //��Ϸ����
};
//�������
struct S_C_GameEnd
{
	bool       bGameOver;      //��Ϸ����
};

#pragma pack()
/********************************************************************************/

// ���ݰ���������ʶ

/**********************************************************************/
#define ASS_VREB_CHECK					179				//�û�����
/**************************����ˡ���>�ͻ�����Ϣ**************************/


#define S_C_GAME_BEGIN					51				//��Ϸ��ʼ

#define S_C_ROLL_RESULT					62				//�������

#define	S_C_UPDATE_POND					63				//���½���

#define S_C_SHANG_FEN                   64              //�Ϸ���Ϣ

#define S_C_CHECK_PRIZE_RESULT          65              //�鿴�󽱽����Ϣ

#define S_C_GAME_OVER                   66              // ��Ϸ����

#define S_C_IS_SUPER_USER               67              //���������Ϣ

#define S_C_NEXT_PAGE_RESULT            68              //�鿴����һҳ�����Ϣ

#define S_C_SHARE_AWARD_RESULT			69			    //���������
/**************************�ͻ��ˡ���>�������Ϣ**************************/
#define ASS_C_XIA_FEN                     55               //�·���Ϣ

#define C_S_SHANG_FEN                     80               //�Ϸ���Ϣ
                  
#define C_S_CHECK_PRIZE                   81               //�鿴��

#define C_S_START_ROLL                    82              //������Ϸ����

#define C_S_GAME_OVER                     83              //��Ϸ����

#define C_S_SUPER_SET                     84              //����������Ϣ

#define C_S_NEXT_PAGE_PRIZE               85              //�鿴��һҳ�н����

#define C_S_SHARE_AWARD					  86			  //������
/**********************************************************************/
#endif
