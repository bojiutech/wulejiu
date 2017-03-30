#pragma once

#ifndef GAME_LOGON_DT_HEAD_FILE
#define GAME_LOGON_DT_HEAD_FILE

#include "MainManage.h"
#include "GameRoomMessage.h"
/********************************************************************************************/

//	���ݿ�ͨ�����ݰ����� 

/********************************************************************************************/

//�û�ע����Ϣ
struct DL_GP_I_Register
{
	DataBaseLineHead				DataBaseHead;						//���ݰ�ͷ
	MSG_GP_S_Register				_data;
};

struct DL_GP_O_Register
{
	DataBaseResultLine				ResultHead;							//������ݰ�ͷ
	MSG_GP_S_Register				_data;
};

//�û�֧��
struct DL_GP_I_PAY
{
	DataBaseLineHead				DataBaseHead;						//���ݰ�ͷ
	MSG_GP_S_Pay					param;
};

struct DL_GP_O_PAY
{
	DataBaseResultLine				ResultHead;							//������ݰ�ͷ
	MSG_GP_S_Pay					data;
};

//ͨ���û�֧����RMB����ȡ��ҽ���
struct DL_GP_I_GETMONEY_BY_PAY
{
	DataBaseLineHead				DataBaseHead;
	unsigned long					dwUserID;
};

struct DL_GP_O_GETMONEY_BY_PAY
{
	DataBaseResultLine				ResultHead;
	MSG_GP_S_GetMoney_ByPay			data;
};

//��½��������½��Ϣ
struct DL_GP_I_LogonByNameStruct////////������½��Ϣ�Ľṹ
{
	DataBaseLineHead					DataBaseHead;						//���ݰ�ͷ
	MSG_GP_S_LogonByNameStruct			LogonInfo;							//��½��Ϣ���ַ�״��һ���ṹ
	char								szAccessIP[16];						//��½ IP
	int									gsqPs;
	///////////////////////////
	//// ��ӷ�ֹ�˻�ͬʱ��½
	int ID;//ZID
	///////////////////////////

};

//�������� zxj 2009-11-13
struct DL_GP_LockAccount
{
	DataBaseLineHead				DataBaseHead;
	MSG_GP_S_LockAccount			LockAccount;
};

///���ֻ�����
struct DL_GP_BindMobile
{
	DataBaseLineHead				DataBaseHead;
	MSG_GP_S_BindMobile				data;
};

//�����û�ͷ��
struct DL_GP_SetLogo
{
	DataBaseLineHead				DataBaseHead;
	MSG_GP_S_SET_LOGO				LogoInfo;
};

//��½��������½��Ϣ
struct DL_GP_I_LogonByAccStruct
{
	DataBaseLineHead					DataBaseHead;						//���ݰ�ͷ
	MSG_GP_S_LogonByAccStruct			LogonInfo;							//��½��Ϣ
	char								szAccessIP[16];						//��½ IP
};

//��½��������½��Ϣ
struct DL_GP_I_LogonByMobileStruct
{
	DataBaseLineHead					DataBaseHead;						//���ݰ�ͷ
	MSG_GP_S_LogonByMobileStruct		LogonInfo;							//��½��Ϣ
	char								szAccessIP[16];						//��½ IP
};

//��½��������½��Ϣ
struct DL_GP_I_RegisterStruct
{
	DataBaseLineHead					DataBaseHead;						//���ݰ�ͷ
	MSG_GP_S_RegisterStruct				RegisterInfo;						//ע����Ϣ
	char								szAccessIP[16];						//��½ IP
};
//��Ҳ���
struct GP_User_Opt_Struct
{
	DataBaseLineHead					DataBaseHead;						//���ݰ�ͷ
	MSG_GP_User_Opt_Struct				stUserOpt;							//��Ҳ����ṹ
};
//������Ϸ�б�����
struct DL_GP_I_UpdateDataListStruct
{
	DataBaseLineHead					DataBaseHead;						//���ݰ�ͷ
	void								* pGameList;						//�б�ָ��	
};

//��½��������½��Ϣ
struct DL_GP_O_LogonResultStruct
{
	DataBaseResultLine					ResultHead;							//������ݰ�ͷ
	MSG_GP_R_LogonResult				LogonResult;						//��½���
};

//�޸�дZ��¼��¼��ʱ����ȷ�����翨��ʱ�򣬲����ڵ����û���¼���� 2009-4-30 zxj
struct  DL_GP_WriteZRecord
{
	DataBaseLineHead		DataBaseHead;
	long	int				lUserID;
	int						ZID;
};

//����������� zxj 2009-11-12
struct MSG_GP_S_LockAccountResult
{
	DataBaseResultLine					ResultHead;							//������ݰ�ͷ
	UINT	dwUserID;
	UINT	dwCommanType;			//������������
	UINT	dwCommanResult;			//����Ľ��
};

//���ֻ����
struct MSG_GP_S_BindMobileResult
{
	DataBaseResultLine					ResultHead;							//������ݰ�ͷ
	UINT	dwUserID;
	UINT	dwCommanType;			//������������
	UINT	dwCommanResult;			//����Ľ��
};

//���뷿�� add by lxl 2010-10-08
struct DL_GP_I_EnterCrypticRoom
{
	DataBaseLineHead					DataBaseHead;						//���ݰ�ͷ
	UINT                                uRoomID;						// �����
	char								szMD5PassWord[50];				// ��������
};
struct DL_GP_O_EnterCrypticRoom
{
	DataBaseResultLine					ResultHead;						//���ݰ�ͷ
	int                                nRet;						// ����ֵ��0��ʾ�ɹ���-1��ʾʧ��
	UINT                               uRoomID;						// �����
};

struct DL_GP_O_GetContestRoomID
{
	DataBaseResultLine	ResultHead;		//������ݰ�ͷ
	UINT				iGameID;		//��ϷID
	int					iRoomID;		//��������ID
	int					iContestID;		//����ID
	int                 iConstestNum;   //�ѱ�������
	int                 iChampionCount; //��ڴ���
	int                 iBestRank;      //�������
	int                 iJoinCount;     //��������
	int                 iEntryFee;      //�볡����
	int                 iRankAward[3];  //ǰ����������Ϣ
	int                 iAwardType[3];  //ǰ������������
};

struct DL_GP_I_GetContestRoomID
{
	DataBaseLineHead					DataBaseHead;				//���ݰ�ͷ
	long int							iUserID;					//�û���
	UINT								iGameID;					//��ϷID
	UINT								iUpPeople;					//�ﵽ�������ſ���
	int									iContestID;					//����ID
};

//��ʱ��������ʼʱ��
struct DL_GP_I_GetContestBeginTime
{
	DataBaseLineHead					DataBaseHead;
	UINT								iGameID;		//��ϷID
	int									iContestID;		//����ID	
};
struct DL_GP_O_GetContestBeginTime
{
	DataBaseResultLine					ResultHead;
	UINT								iGameID;		//��ϷID
	int									iContestID;		//����ID	
	COleDateTime						matchBeginTime;	//������ʼʱ��
};

//added by JianGuankun 20111108,�û������޸�
struct DL_GP_I_UserInfoStruct
{
	DataBaseLineHead	DataBaseHead;	//���ݰ�ͷ
	MSG_GP_S_UserInfo   UserInfo;		//�û���������
};

struct DL_GR_O_UserInfoStruct
{
	DataBaseResultLine	ResultHead;		//������ݰ�ͷ
};

struct DL_GP_I_ChPasswordStruct
{
	DataBaseLineHead	DataBaseHead;	//���ݰ�ͷ
	MSG_GP_S_ChPassword ChPwd;		//�û����������
};

struct DL_GP_O_ChPasswordStruct
{
	DataBaseResultLine	ResultHead;	//���ݰ�ͷ
};

/// ���汾
struct DL_GR_I_CheckVersion_t
{
	DataBaseLineHead					DataBaseHead;						///<���ݰ�ͷ
	UINT								uType;								///<��������
};
struct DL_GP_I_ReceiveMoney
{
	DataBaseLineHead					DataBaseHead;						///<���ݰ�ͷ
	int									iUserID;
};

struct DL_GP_O_ReceiveMoney
{
	DataBaseResultLine					ResultHead;						///<���ݰ�ͷ
	TReceiveMoney						date;
};

struct DL_GP_O_CharmExchangeList
{
	DataBaseResultLine					ResultHead;						///<���ݰ�ͷ
	TCharmExchange_Item					date;
};

struct DL_GP_I_CharmExchange
{
	DataBaseLineHead					DataBaseHead;						///<���ݰ�ͷ
	TCharmExchange						date;
};


struct  DL_GP_I_SetFriendType
{
	DataBaseLineHead					DataBaseHead;						///<���ݰ�ͷ
	int									iUserID;
	int									iType;
};

struct DL_GP_O_GetLogonPeopleCount
{
	DataBaseResultLine					ResultHead;							///<���ݰ�ͷ
	ONLINEUSERSCOUNT					logonUsers;
};
struct DL_GP_O_MailGet
{
	DataBaseResultLine					ResultHead;						///<���ݰ�ͷ
	TMailItem							date;
};

struct DL_GP_I_MailUpdate
{
	DataBaseLineHead					DataBaseHead;						///<���ݰ�ͷ
	int									iMsgID;
};

struct DL_GP_I_GetNickNameID
{
	DataBaseLineHead					DataBaseHead;						///<���ݰ�ͷ
	MSG_GP_NickNameID_t					_data;
};

struct DL_GP_O_GetNickNameID
{
	DataBaseResultLine					ResultHead;							///<���ݰ�ͷ
	MSG_GP_NickNameID_t					_data;
};

//added by JianGuankun 2012.7.12 ,����õ���������
struct DL_GP_I_FinanceInfo
{
	DataBaseLineHead		 DataBaseHead;		//���ݰ�ͷ
	TMSG_GP_BankFinanceInfo  _data;				//��������
};

struct DL_GP_O_FinanceInfo
{
	DataBaseResultLine		 ResultHead;		//���ݰ�ͷ
	TMSG_GP_BankFinanceInfo  _data;				//��������
};

struct DL_GP_I_LastLoginGame
{
	DataBaseLineHead		DataBaseHead;		//���ݰ�ͷ
	int						iUserID;
};

struct DL_GP_O_LastLoginGame
{
	DataBaseResultLine		ResultHead;		//���ݰ�ͷ
	TLoginGameInfo			_data;
};

// ���а�
struct DL_GP_I_PaiHangBang
{
	DataBaseLineHead				DataBaseHead;							///<���ݰ�ͷ
	MSG_GP_PaiHangBang_In			_param;								
};
struct DL_GP_O_PaiHangBang
{
	DataBaseResultLine				ResultHead;							///<���ݰ�ͷ
	MSG_GP_MoneyPaiHangBang_Result		_data;
};

//ִ��ǩ��
struct DL_I_HALL_SIGN
{
	DataBaseLineHead					DataBaseHead;						///<���ݰ�ͷ
	long								dwUserID;
};

struct DL_O_HALL_SIGN_CHECK
{
	DataBaseResultLine					ResultHead;							///<���ݰ�ͷ
	MSG_GP_S_SIGN_CHECK_RESULT			_data;
};

struct DL_O_HALL_SIGN_DO
{
	DataBaseResultLine					ResultHead;							///<���ݰ�ͷ
	MSG_GP_S_SIGN_DO_RESULT				_data;
};

//���߽���
struct DL_I_HALL_ONLINE_AWARD
{
	DataBaseLineHead					DataBaseLineHead;
	long								dwUserID;
};

struct DL_O_HALL_ONLINE_AWARD_CHECK_RESULT
{
	DataBaseResultLine					ResultHead;							///<���ݰ�ͷ
	MSG_GP_S_ONLINE_AWARD_CHECK_RESULT	_result;
};
struct DL_O_HALL_ONLINE_AWARD_DO_RESULT
{
	DataBaseResultLine					ResultHead;							///<���ݰ�ͷ
	MSG_GP_S_ONLINE_AWARD_DO_RESULT	_result;
};
struct DL_I_HALL_BUY_DESK
{
	DataBaseLineHead					DataBaseLineHead;
	MSG_GP_S_BUY_DESK                   _data;
	DL_I_HALL_BUY_DESK()
	{
		memset(this,0,sizeof(DL_I_HALL_BUY_DESK));
	}
};
struct DL_O_HALL_BUY_DESK_RES
{
	DataBaseResultLine					ResultHead;	
	MSG_GP_S_BUY_DESK_RES               _result;
	DL_O_HALL_BUY_DESK_RES()
	{
		memset(this,0,sizeof(DL_O_HALL_BUY_DESK_RES));
	}
};
struct DL_I_HALL_ENTER_VIPDESK
{
	DataBaseLineHead					DataBaseLineHead;
	MSG_GP_S_ENTER_VIPDESK				_data;
	DL_I_HALL_ENTER_VIPDESK()
	{
		memset(this,0,sizeof(DL_I_HALL_ENTER_VIPDESK));
	}
};
struct DL_O_HALL_ENTER_VIPDESK_RES
{
	DataBaseResultLine					ResultHead;	
	MSG_GP_S_ENTER_VIPDESK_RES			_result;
	DL_O_HALL_ENTER_VIPDESK_RES()
	{
		memset(this,0,sizeof(DL_O_HALL_ENTER_VIPDESK_RES));
	}
};
struct DL_I_HALL_VIPDESK_CONFIG
{
	DataBaseLineHead					DataBaseLineHead;
	MSG_GP_S_VIP_DESK_CONFIG				_data;
	DL_I_HALL_VIPDESK_CONFIG()
	{
		memset(this,0,sizeof(DL_I_HALL_VIPDESK_CONFIG));
	}
};
struct DL_O_HALL_VIPDESK_CONFIG_RES
{
	DataBaseResultLine					ResultHead;	
	MSG_GP_S_VIP_DESK_CONFIG_RES			_result;
	DL_O_HALL_VIPDESK_CONFIG_RES()
	{
		memset(this,0,sizeof(DL_O_HALL_VIPDESK_CONFIG_RES));
	}
};
struct DL_I_HALL_MONEY_TO_JEWEL
{
	DataBaseLineHead					DataBaseLineHead;
	MSG_GP_S_MONEY_TO_JEWEL				_data;
	DL_I_HALL_MONEY_TO_JEWEL()
	{
		memset(this,0,sizeof(DL_I_HALL_MONEY_TO_JEWEL));
	}
};
struct DL_O_HALL_MONEY_TO_JEWEL_RES
{
	DataBaseResultLine					ResultHead;	
	MSG_GP_S_MONEY_TO_JEWEL_RES			_result;
	DL_O_HALL_MONEY_TO_JEWEL_RES()
	{
		memset(this,0,sizeof(DL_O_HALL_MONEY_TO_JEWEL_RES));
	}
};

//��ö��߷�����Ϣ
struct DL_I_HALL_NETCUT
{
	DataBaseLineHead					DataBaseLineHead;
	MSG_GP_S_GET_CUTNETROOMINFO				_data;
	DL_I_HALL_NETCUT()
	{
		memset(this,0,sizeof(DL_I_HALL_NETCUT));
	}
};
struct DL_O_HALL_NETCUT_RES
{
	DataBaseResultLine								ResultHead;	
	MSG_GP_S_GET_CUTNETROOMINFO_RES					_result;
	DL_O_HALL_NETCUT_RES()
	{
		memset(this,0,sizeof(DL_O_HALL_NETCUT_RES));
	}
};

//������
struct MSG_GP_SC_Agent
{
	char		szUserName[64];			//������Ϣ�û����û���
	int			iOperaType;			//���� ��  1-��ѯ�������Ƿ����;  2-�󶨴�����
	char		szAgentName[100];	//����������
};

struct DL_GP_I_Agent
{
	DataBaseLineHead				DataBaseHead;
	MSG_GP_SC_Agent					tAgent;
};

struct DL_GP_O_Agent
{
	DataBaseResultLine				ResultHead;
};
/********************************************************************************************/

//������½�����ʶ
#define DTK_GP_LOGON_BY_NAME			1									//ͨ�����ֵ�½
#define DTK_GP_LOGON_BY_ACC				2									//ͨ�� ACC��½
#define DTK_GP_LOGON_BY_MOBILE			3									//ͨ���ֻ���½
#define DTK_GP_RIGSTER_USER				4									//�û�ע�ᴦ��
#define DTK_GP_UPDATE_LIST				5									//������Ϸ�б�
#define DTK_GP_UPDATE_STRING			6									//���������ַ�
#define DTK_GP_CHECK_CONNECT			7									//����������
//#define DTK_GP_GAME_POWER   			9									//�û�Ȩ��
#define DTK_GP_CHECK_SELLGAMELIST		9									//�����Ƿ��������б�
			
#define DTK_GP_ZRECORD					11									//�޸�дZ��¼��¼��ʱ����ȷ�����翨��ʱ�򣬲����ڵ����û���¼����

#define DTK_GP_GET_ROOM_LIST_PEOCOUNT	8									//pppp
#define	DTK_GP_LOCK_UNLOCK_ACCOUNT		12									//����������������
#define DTK_GP_CHECK_ROOM_PASSWD		10									// �������뷿��
#define	DTK_GP_PASSWD_SUCC              0									//��������ɹ�
#define	DTK_GP_PASSWD_ERROR             1									//�����������

//������½�������
#define DTR_GP_ERROR_UNKNOW				0									//δ֪����
#define DTR_GP_DATABASE_CUT				1									//���ݿ�Ͽ�
#define DTR_GP_LOGON_SUCCESS			10									//��½�ɹ�
#define DTR_GP_USER_NO_FIND				11									//��½���ִ���
#define DTR_GP_USER_PASS_ERROR			12									//�û��������
#define DTR_GP_USER_VALIDATA			13									//�û��ʺŽ���
#define DTR_GP_USER_IP_LIMITED			14									//��½ IP ��ֹ
#define DTR_GP_USER_EXIST				15									//�û��Ѿ�����
#define DTR_GP_PASS_LIMITED				16									//�����ֹЧ��
#define DTR_GP_IP_NO_ORDER				17									//����ָ����ַ 
#define DTR_GP_LIST_SCUESS				18									//�����б�ɹ�
#define DTR_GP_LIST_ERROR				19									//�����б�ʧ��
#define DTR_GP_STRING_SCUESS			20									//�������ֳɹ�
#define DTR_GP_STRING_ERROR				21									//��������ʧ��
#define DTR_GP_USERNICK_EXIST			22									//�ǳ��Ѿ�����

#define DTR_GP_GET_ROOM_LIST_PEOCOUNT_SCUESS			23					//ppp
#define DTR_GP_GET_ROOM_LIST_PEOCOUNT_ERROR				24					//ppp
#define DTR_GP_IP_FULL					25									//��IP����
#define DTR_GP_USER_NAME_BAD			26									//�Ƿ��ַ�
/////////////////////////////
///�û��Ѿ���½
#define DTR_GP_USER_LOGONED				28										//�û��Ѿ���½
////////////////////////////
//#define DTK_GP_USER_OPT				27									//���ѻ��˲���
#define	DTR_GP_ACCOUNT_LOCKED			29									//���ʺ�������ĳ̨�������������ǵ�ǰ���ڵ�¼��̨
#define	DTR_GP_LOCK_SUCCESS				30									//�����ɹ�	
#define	DTR_GP_MATHINE_UNLOCK			31									//�ʺŸ�����û����ĳ̨����
#define	DTR_GP_UNLOCK_SUCCESS			32									//�����ɹ�
#define	DTR_GP_CODE_ERROR				33									//�����벻ƥ��
#define DTK_GR_CHECK_VERSION			34									//���汾
#define DTK_GP_GET_SELLGAMELIST			35									//��ȡ�����б�

#define DTK_GP_MATHINELOCK				36

#define DTR_GP_ALLO_PARTY				37									//��ص�½

#define DTR_GP_LOCK_VALID				38									//������֤

#define DTR_GP_MOBILE_VALID				39									//�ֻ�������֤

#define DTK_GP_UPDATE_USERINFO_BASE			40									//�û����������޸�
#define DTR_GP_UPDATE_USERINFO_BASE			41									//�û����������޸�
#define DTK_GP_UPDATE_USERINFO_DETAIL		42									//�û���ϸ�����޸�
#define DTR_GP_UPDATE_USERINFO_DETAIL		43									//�û���ϸ�����޸�
#define DTK_GP_UPDATE_USERINFO_PWD			44									//�û������޸�
#define DTR_GP_UPDATE_USERINFO_PWD			45									//�û������޸�
#define DTR_GP_UPDATE_USERINFO_ACCEPT		47									//�û���ϸ�������ⱻ����������
#define DTR_GP_UPDATE_USERINFO_NOTACCEPT	48									//�û���ϸ����δ�ⱻ����������
#define DTK_GP_UPDATE_NICKNAMEID			49									//��ѯĳ�û����ǳƻ�ID

#define DTK_GP_RECEIVEMONEY					50									//��ȡ���	

#define DTK_GP_CHARMEXCHANGE_LIST			51									//����ֵ�һ�
#define DTK_GP_CHARMEXCHANGE				52									//����ֵ�һ�


#define	DTK_GP_SETFRIENDTYPE				53									//�޸��û����Ѻ��������������

#define DTK_GP_MAILLIST_GET					54

#define DTK_GP_MAIL_UPDATE					55

#define DTK_GP_LASTLOGINGAME				56									//�����¼��Ϸ

#define DTK_GP_LOGONPEOPLE_GET				57									//��ȡ��¼����

#define DTK_GP_BIND_MOBILE					58									//�ֻ���

#define DTK_GP_SET_LOGO						59									//�����û�ͷ��

#define DTK_GP_GET_CONTEST_ROOMID			60									//��ȡ��������ID

#define DTK_GP_REGISTER					61										//�û�ע��

#define DTK_GP_PAY						62										//�û�֧��
#define DTK_GP_GETMONEY_BY_PAY			63										//ͨ��֧���� RMB ��ȡ��ҽ���
#define DTK_GP_GETMONEY_BY_PAY_CHECK	64										//��ѯ
#define DTK_GP_PAIHANGBANG				65										//���а�
#define DTK_GP_SIGNIN_CHECK				66										//��ѯǩ��
#define DTK_GP_SIGNIN_DO				67										//ִ��ǩ��

#define DTK_GP_ONLINE_AWARD_CHECK		68										//��ѯ���߽���
#define DTK_GP_ONLINE_AWARD_DO			69										//��ȡ���߽���

#define DTK_GP_GET_TIMINGMATCHBEIGNTIME 70										//��ȡ��ʱ��������ʼʱ��
#define DTK_GP_BUY_DESK					71										//��������
#define DTK_GP_ENTER_VIPDESK			72										//����VIP����
#define DTK_GP_VIPDESK_CONFIG			73										//VIP��������
#define DTK_GP_MONEY_TO_JEWEL           74										//��Ҷһ���ʯ

#define DTK_GP_AGENT					75										//������

#define DTK_GP_NETCUT					120										//��ö�����Ϣ
/********************************************************************************************/

#endif