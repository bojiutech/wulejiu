#pragma  once
// ***************************************************************
//  struct   version:  1.0   ��  date: 08/21/2008
//  -------------------------------------------------------------
//  �ⲿ���ڲ����õĽṹ��
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// ���Ҫ�ڽṹ����ӻ�����ֶΣ��������±���¼����
// ***************************************************************

//��mdm ƽ̨�ͽ�ƽ̨�����ݽṹ�����ۺϣ����֧������ƽ̨
//��ֵ�����ܻ�Ƚ��鷳����ƽ̨��д����ת��������֧�����ݽṹ���ת�������û���ֶ�ѡΪ �� 0
//
struct RecordUserInfoStruct
{
	long int					dwUserID;							//ID ����
	long int					dwExperience;						//����ֵ	
	__int64						dwAccID;							//ACC ����
	__int64						dwPoint;							//����
	__int64						dwMoney;							//���	
	UINT						uWinCount;							//ʤ����Ŀ
	UINT						uLostCount;							//����Ŀ
	UINT						uCutCount;							//ǿ����Ŀ
	UINT						uMidCount;							//�;���Ŀ
	TCHAR						szName[61];							//��¼��	
	UINT						bLogoID;							//ͷ�� ID ����
	BYTE						bDeskNO;							//��Ϸ����
	BYTE						bDeskStation;						//����λ��
	BYTE						bUserState;							//�û�״̬
	BYTE						bMember;							//��Ա�ȼ�
	BYTE						bGameMaster;						//����ȼ�
	ULONG						dwUserIP;							//��¼IP��ַ
	bool						bBoy;								//�Ա�
	TCHAR						nickName[61];						//�û��ǳ�
	//��ƽ̨�ж��е��ֶ�
	int                         iAgencyID;                          //�û��Ĵ����̱��
	long int					dwReputation;						//����ֵ    //yjj  090223
	__int64					    dwMobileNum;						//�ֻ�����   yjj   090223   for tonglou platform
	__int64                     dwScore;                            //��ǰ����   yjj   090223   for tonglou platform
	bool						bSayHello;							//�Ƿ�ӭ����
	BYTE                        bUserType;                          //�������(��ͨ��ҡ��������)
	//mdm ƽ̨�ж��е��ֶ�
	int							dwBank;								//����
	char						szClassName[61];					//��Ϸ����
	UINT						uDeskBasePoint;						//���õ����ӱ���
	int							dwFascination;						//����
	int							iVipTime;							//��Աʱ��
	int							iDoublePointTime;					//˫������ʱ��
	int							iProtectTime;						//�����ʱ�䣬����
};
//�û���Ϣ
struct RecordUserItemStruct
{
	bool							bMatchUser;							//�Ƿ����
	UINT							uSortIndex;							//��������
	UINT							uConnection;						//��ҹ�ϵ
	long int						dwLogonTime;						//��½ʱ��
	RecordUserInfoStruct			GameUserInfo;						//�û���Ϣ
};
//������Ϸ��һЩ��Ϣ
struct RecordGameInfoStruct
{

	//record ���������ֶΣ����븳ֵ,�ͻ���ico������
	TCHAR							szClientDLLName[31];				//ico �ļ�����
	BYTE						    bMeDeskStation;	
	//Ŀǰ����ƽ̨���е��ֶ�
	//������Ϣ
	bool							bDeskOnwer;							//�Ƿ�̨��
	BYTE							bGameStation;						//��Ϸ״̬
	//UserItemStruct					* pMeUserInfo;						//�����Ϣ
	long int						dwGamePower;						//�û�Ȩ��
	long int						dwMasterPower;						//����Ȩ��
	long int						dwRoomRule;							//���ù���


	//���ò���
	bool							bEnableSound;						//��������
	bool							bEnableWatch;						//�����Թ�
	bool							bShowUserInfo;						//��ʾ����
	

	

	//��������
	UINT							uDeskPeople;						//��Ϸ����
	UINT							uRoomID;							//�����ʾ
	DWORD							dwGameMSVer;						//���汾��
	DWORD							dwGameLSVer;						//���汾��
	UINT							uComType;							//��Ϸ����
	UINT							uNameID;							//���ֱ�ʾ	
	TCHAR							szGameName[61];						//��Ϸ����
	UINT							uLessPoint;							//���ٷ���
	TCHAR							szKindName[100];					//��������
	TCHAR							szRoomName[100];					//��������


	int							uVirtualUser;						//20081211 , Fred Huang
	int							uVirtualGameTime;					//20081211 , Fred Huang
	bool                         bIsInRecord;                        //�Ƿ���¼���� yjj  090223  
	//��ƽ̨���е��ֶ�
	int                             iRoomSelcet; //�M�벻ͬ�ה����g
	UINT                            uTaiMoney;                         //ѡ�뷿���ÿ̨���
	UINT                            uDiMoney;                          //ѡ�뷿��ĵ׽��

	//mdmƽ̨�����ֶ�
	bool							bEnableBackSound;					//��������
};
//����ϢӦ��������ƽ̨����һ�µģ�������������������Ϣ��
