#ifndef _CHERRY97_MESSAGEHEAD_H_
#define _CHERRY97_MESSAGEHEAD_H_
#include "HNBaseType.h"

namespace Cherry97
{
	#pragma pack(1)
	enum 
	{
		NAME_ID = 31011001,
		PLAY_COUNT = 1,
	};

	//��Ϸ״̬����
	const int  GS_WAIT_SETGAME	=  0;				//�ȴ���������״̬
	const int  GS_WAIT_ARGEE	=  1;				//�ȴ�ͬ������
	const int  GS_WAIT_START	=  20;		    	//�ȴ���ʼ
	const int  GS_PLAY_GAME		=  21;				//��ʼ��Ϸ��
	const int  GS_WAIT_NEXT		=  22;			    //�ȴ���һ�̿�ʼ 

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
		LLONG			i64UserMoney;					//�û��Ľ����
		LLONG           i64Pond;						//���ؽ��
		LLONG           i64SinglePond;                  //�����ʽ�
		char			szGameRoomName[61];
		BYTE			bDeskIndex;
		int				iShareAward;
		S_C_GameStation()
		{
			memset(this, 0 , sizeof(S_C_GameStation));
		}
	};

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

	struct  C_S_ShareAward{
		int iShareAward;
		C_S_ShareAward(){
			memset(this, 0, sizeof(C_S_ShareAward));
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
		int      iShangFenMoney;   //�Ϸֽ��
		LLONG    i64UserMoney;     //���Ǯ
		S_C_ShangFenResult()
		{
			memset(this,0,sizeof(S_C_ShangFenResult));
		}
	};

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

	//������Ϣ
	struct S_C_TypeScroll
	{
		bool                 iAllGame;          //ȫ��
		bool                 bWinAreaFlag[8];   //�������н�  0-7���ֱ��ӦA-H
		bool                 iLogoResult[9];    //���⽱��ͼƬ��7����λ��
		BYTE                 byPlayStly;        //1:��������Ϸ  2:����2������  3:����3������  4:����4������
		BYTE                 bySpecialRestCount;//�����淨ʣ�����
		BYTE                 byZhongLine;       //�н�����
		int                  iExtaPay;          //���⽱��
		int                  iGetCaiJin;        //���òʽ�
		int                  iZhongCaiJin;      //�����ܲʽ�
		int                  iSecondGetMoney;   //���ö��ν������
		int                  iTypeImgid[9];     //ͼ������
		int                  bShangFenMoney;    //�Ϸֽ��
		int                  iWinMoney;         //��Ӯ����
		int                  iLogoValue;        //���⽱��ͼƬ��7������
		LLONG	             iSinglePond;       //�����ʽ�
		int					 iShareAward;		//������
		BYTE				bySpecialCount;//�����淨�ܾ���
		S_C_TypeScroll()
		{
			memset(this,0,sizeof(S_C_TypeScroll));
		}
	};
	//���ظ������ݰ�
	struct S_C_Pond 
	{
		bool                  bFlag;              //�Ƿ��д�
		BYTE                  byStation;          //�н�������
		char                  szNickName[61];     //�н�����ǳ�
		LLONG                 i64GetPond;         //�н����
		LLONG                 i64Pond;            //���ؽ��
		S_C_Pond()
		{
			memset(this,0,sizeof(S_C_Pond));
		}
	};
	//�鿴������
	struct S_C_Check_Prize
	{
		int               iAllGameCount[18];     //ȫ�̴���
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
		UINT     iLineGameCount[12];       //�����н�����
		S_C_Next_Prize()
		{
			memset(this,0,sizeof(S_C_Next_Prize));
		}
	};
	//����
	struct C_S_GameEnd
	{
		bool bGameOver;    //��Ϸ����
	};
	//�������
	struct S_C_GameEnd
	{
		bool bGameOver;    //��Ϸ����
	};

	// ���ݰ���������ʶ
	/**********************************************************************/
	const int ASS_VREB_CHECK = 179;				//�û�����
	/**************************����ˡ���>�ͻ�����Ϣ**************************/
	const int S_C_GAME_BEGIN = 51;				//��Ϸ��ʼ

	const int S_C_ROLL_RESULT = 62;				//�������

	const int S_C_UPDATE_POND = 63;			    //���½���

	const int S_C_SHANG_FEN = 64;               //�Ϸ���Ϣ

	const int S_C_CHECK_PRIZE_RESULT = 65;      //�鿴�󽱽����Ϣ

	const int S_C_GAME_OVER = 66;               //��Ϸ����

	const int S_C_IS_SUPER_USER = 67;           //���������Ϣ

	const int S_C_NEXT_PAGE_RESULT = 68;        //�鿴����һҳ�����Ϣ

	const int S_C_SHARE_AWARD_RESULT = 69;
	/**************************�ͻ��ˡ���>�������Ϣ**************************/
	const int ASS_C_XIA_FEN = 55;               //�·���Ϣ

	const int C_S_SHANG_FEN = 80;               //�Ϸ���Ϣ

	const int C_S_CHECK_PRIZE = 81;             //�鿴��

	const int C_S_START_ROLL = 82;              //������Ϸ����

	const int C_S_GAME_OVER   = 83;             //��Ϸ����

	const int C_S_SUPER_SET  =  84;             //����������Ϣ

	const int C_S_NEXT_PAGE_PRIZE =  85;        //�鿴��һҳ�н����

	const int C_S_SHARE_AWARD = 86;		    //������


	#pragma pack()
}
#endif
