

// ***************************************************************
//  interStruct   version:  1.0   ��  date: 08/21/2008
//  -------------------------------------------------------------
//  ϵͳ�ڲ��õ�����
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
//Ϊ������Ϣ��׼���������Ҫ�������Ͳ��ܱ�֤ͨ���ԡ�
#pragma  once
#define  MAX_MSG_HEAD_LEN   50
#define  MAX_MSG_DATA_LEN   2000   //���һ����Ϣ����
#define  MAX_PLAYER_COUNT   180   //����а˸����

#define  FILE_TYPE_NONE        1
#define  FILE_TYPE_ZIP         2
#define  FILE_TYPE_PASS_ZIP    3
struct RecordNetMessageHead
{
	DWORD						uMessageSize;						//���ݰ���С
	DWORD						bMainID;							//����������
	DWORD						bAssistantID;						//������������ ID
	DWORD						bHandleCode;						//���ݰ��������
	DWORD						bReserve;							//�����ֶ�
};

struct RecordNetMsgStruct
{
	BYTE NetMsgHead[MAX_MSG_HEAD_LEN]; //ͷ��Ϣ   //�50���ֽ�
	BYTE NetMsgData[MAX_MSG_DATA_LEN];   //������Ϣ
	UINT uHeadSize;      //ͷ�Ĵ�С
	UINT uDataSize;      //������Ϣ��С	
	UINT uTimeSlot;      //����һ��Ϣ��ʱ����
};
struct FileHeadBase 
{
	RecordGameInfoStruct RoomGameInfo;
	RecordUserItemStruct UsrInfoStruct[MAX_PLAYER_COUNT]; //�����Ϣ
	BYTE bMyDeskStation;	
	UINT uPlayerCount;
	UINT uFileType;            //������ļ�����  1���� 2ѹ����3����ѹ��	
	UINT uTotalMsgCount;       //�ܹ���Ϣ������
};
struct FileHeadStruct : public FileHeadBase
{
	unsigned char arrcFileHeadMd5[16];
	unsigned char arrcFileMsgMd5[16];
};
