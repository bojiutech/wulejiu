#ifndef CUSERPOWERH_HEAD_FILE
#define CUSERPOWERH_HEAD_FILE

///��ͨ���Ȩ�޶���
#define PW_NO_ROOM_TALK					0x00000001L				///�������������
#define PW_NO_GAME_TALK					0x00000002L				///��������Ϸ����
#define PW_NO_SEND_MESSAGE				0x00000004L				///����������Ϣ
#define PW_N0_PLAY_GAME					0x00000008L				///���ܽ�����Ϸ
#define PW_NO_WATCH_GAME				0x00000010L				///�����Թ���Ϸ
#define PW_CAN_THROW_PASS				0x00000020L				///������������
#define PW_CAN_THROW_SET				0x00000040L				///������������
#define PW_CAN_SEND_MUCH				0x00000080L				///����������
#define PW_CAN_SET_FONT					0x00000100L				///������������
#define PW_CAN_TALK_FAST				0x00000200L				///����ˢ��Ļ
#define PW_CAN_HIGH_LOOK				0x00000400L				///����߼��ۿ�
#define PW_CAN_FIND_USER				0x00000800L				///�����������
#define PW_CAN_WATCH_ANYTIME			0x00001000L				///�����κ��Թ�

///����ԱȨ�޶���
#define PW_CAN_SEND_WARNING				0x00000001L				///����������Ϣ
#define PW_CAN_SEND_SYSTEM				0x00000002L				///����ϵͳ��Ϣ
#define PW_CAN_SEND_GAME				0x00000004L				///������Ϸ��Ϣ
#define PW_CAN_LIMIT_OTHER_ROOM_TALK	0x00000008L				///�����ֹ�����˴�������
#define PW_CAN_LIMIT_OTHER_GAME_TALK	0x00000010L				///�����ֹ��������Ϸ����
#define PW_CAN_LIMIT_OTHER_SEND			0x00000020L				///�����ֹ�����˷�����
#define PW_CAN_LIMIT_OTHER_PLAY			0x00000040L				///�����ֹ��������Ϸ
#define PW_CAN_LIMIT_OTHER_WATCH		0x00000080L				///�����ֹ�������Թ�
#define PW_CAN_SAFE_FINISH				0x00000100L				///��������Ϸ
#define PW_CAN_CUT_USER					0x00000200L				///�������������
#define PW_CAN_LOOK_USER_IP				0x00000400L				///����鿴 IP
#define PW_CAN_LIMIT_IP					0x00000800L				///�����ֹ IP
#define PW_CAN_HIDE_IP					0x00001000L				///�������� IP
#define PW_CAN_LIMIT_ACCOUN				0x00002000L				///�����ֹ�ʺ�
#define PW_CAN_LOOK_POWER				0x00004000L				///�����ѯȨ��
#define PW_CAN_SET_POWER				0x00008000L				///��������Ȩ��
#define PW_CAN_BIND_GAME				0x00010000L				///�������Ϸ
#define PW_CAN_BIND_ACCOUN				0x00020000L				///������ʺ�
#define PW_CAN_HIDE_ACTION				0x00040000L				///�������ض���
#define PW_CAN_CONTROL_USER				0x00080000L				///��������û�
#define PW_CAN_MUCH_CLIENT				0x00100000L				///�����ͻ���
#define PW_CAN_SET_SERVER				0x00200000L				///�������÷�����
#define PW_CAN_LISTEN_MESSAGE			0x00400000L				///�����������Ϣ
#define PW_CAN_LISTEN_GAME				0x00800000L				///���������Ϸ����
#define PW_CAN_ADD_PIONT				0x0100000L				///����Ӽ�����
#define PW_CAN_LOGON_LIMIT				0x02000000L				///�����½���Ʒ���
#define PW_CAN_ALL_POWER				0x04000000L				///��������Ȩ��

///�û�Ȩ��
class  CUserPower
{
	///��ѯ��ͨ���Ȩ�޲�ѯ
public:
	CUserPower(){};
	///��ѯ�Ƿ������������
	static bool CanRoomTalk(long int dwGamePower) { return ((dwGamePower&PW_NO_ROOM_TALK)==0L); }
	///��ѯ�Ƿ�������Ϸ����
	static bool CanGameTalk(long int dwGamePower) { return ((dwGamePower&PW_NO_GAME_TALK)==0L); }
	///��ѯ�Ƿ���������Ϣ
	static bool CanSendMessage(long int dwGamePower) { return ((dwGamePower&PW_NO_SEND_MESSAGE)==0L); }
	///��ѯ�Ƿ����������Ϸ
	static bool CanPlayGame(long int dwGamePower) { return ((dwGamePower&PW_N0_PLAY_GAME)==0L); }
	///��ѯ�Ƿ������Թ���Ϸ
	static bool CanWatchGame(long int dwGamePower) { return ((dwGamePower&PW_NO_WATCH_GAME)==0L); }
	///��ѯ�Ƿ�������������
	static bool CanThrowPass(long int dwGamePower) { return ((dwGamePower&PW_CAN_THROW_PASS)!=0L); }
	///��ѯ�Ƿ�������������
	static bool CanThrowSet(long int dwGamePower) { return ((dwGamePower&PW_CAN_THROW_SET)!=0L); }
	///��ѯ�Ƿ�����������
	static bool CanSendMuch(long int dwGamePower) { return ((dwGamePower&PW_CAN_SEND_MUCH)!=0); }
	///��ѯ�Ƿ�������������
	static bool CanSetFont(long int dwGamePower) { return ((dwGamePower&PW_CAN_SET_FONT)!=0); }
	///��ѯ�Ƿ�����ˢ��Ļ
	static bool CanTalkFast(long int dwGamePower) { return ((dwGamePower&PW_CAN_TALK_FAST)!=0); }
	///��ѯ�Ƿ�����߼��ۿ�
	static bool CanHighLook(long int dwGamePower) { return ((dwGamePower&PW_CAN_HIGH_LOOK)!=0); }
	///��ѯ�����������
	static bool CanFindUser(long int dwGamePower) { return ((dwGamePower&PW_CAN_FIND_USER)!=0); }
	///��ѯ�����κ��Թ�
	static bool CanWatchAnyTime(long int dwGamePower) { return ((dwGamePower&PW_CAN_WATCH_ANYTIME)!=0); }

	///��ѯ��ѯ����ԱȨ�޲�ѯ
public:
	///��ѯ�Ƿ�����������Ϣ
	static bool CanSendWarning(long int dwMasterPower) { return ((dwMasterPower&PW_CAN_SEND_WARNING)!=0L); }
	///��ѯ�Ƿ�����ϵͳ��Ϣ
	static bool CanSendSystem(long int dwMasterPower) { return ((dwMasterPower&PW_CAN_SEND_SYSTEM)!=0); }
	///��ѯ�Ƿ�������Ϸ��Ϣ
	static bool CanSendGame(long int dwMasterPower) { return ((dwMasterPower&PW_CAN_SEND_GAME)!=0); }
	///��ѯ�Ƿ������ֹ�����˴�������
	static bool CanLimiteRoomTalk(long int dwMasterPower) { return ((dwMasterPower&PW_CAN_LIMIT_OTHER_ROOM_TALK)!=0L); }
	///��ѯ�Ƿ������ֹ��������Ϸ����
	static bool CanLimiteGameTalk(long int dwMasterPower) { return ((dwMasterPower&PW_CAN_LIMIT_OTHER_GAME_TALK)!=0L); }
	///��ѯ�Ƿ������ֹ�����˷�����
	static bool CanLimiteOtherSend(long int dwMasterPower) { return ((dwMasterPower&PW_CAN_LIMIT_OTHER_SEND)!=0L); }
	///��ѯ�Ƿ������ֹ��������Ϸ
	static bool CanLimiteOtherPlay(long int dwMasterPower) { return ((dwMasterPower&PW_CAN_LIMIT_OTHER_PLAY)!=0L); }
	///��ѯ�Ƿ������ֹ�������Թ�
	static bool CanLimiteOtherWatch(long int dwMasterPower) { return ((dwMasterPower&PW_CAN_LIMIT_OTHER_WATCH)!=0L); }
	///��ѯ�Ƿ���������Ϸ
	static bool CanSafeFinish(long int dwMasterPower) { return ((dwMasterPower&PW_CAN_SAFE_FINISH)!=0L); }
	///��ѯ�Ƿ��������������
	static bool CanCutUser(long int dwMasterPower) { return ((dwMasterPower&PW_CAN_CUT_USER)!=0L); }
	///��ѯ�Ƿ�����鿴 IP
	static bool CanLookIP(long int dwMasterPower) { return ((dwMasterPower&PW_CAN_LOOK_USER_IP)!=0); }
	///��ѯ�Ƿ������ֹ IP
	static bool CanLimiteIP(long int dwMasterPower) { return ((dwMasterPower&PW_CAN_LIMIT_IP)!=0L); }
	///��ѯ�Ƿ������������� IP
	static bool CanHideIP(long int dwMasterPower) { return ((dwMasterPower&PW_CAN_HIDE_IP)!=0L); }
	///��ѯ�Ƿ������ֹ�ʺ�
	static bool CanLimiteAccoun(long int dwMasterPower) { return ((dwMasterPower&PW_CAN_LIMIT_ACCOUN)!=0L); }
	///��ѯ�Ƿ������ѯȨ��
	static bool CanLookPower(long int dwMasterPower) { return ((dwMasterPower&PW_CAN_LOOK_POWER)!=0L); }
	///��ѯ�Ƿ���������Ȩ��
	static bool CanSetPower(long int dwMasterPower) { return ((dwMasterPower&PW_CAN_SET_POWER)!=0L); }
	///��ѯ�Ƿ��������Ϸ
	static bool CanBindGame(long int dwMasterPower) { return ((dwMasterPower&PW_CAN_BIND_GAME)!=0L); }
	///��ѯ�Ƿ�������ʺ�
	static bool CanBindAccoun(long int dwMasterPower) { return ((dwMasterPower&PW_CAN_BIND_ACCOUN)!=0L); }
	///��ѯ�Ƿ��������ض���
	static bool CanHideAction(long int dwMasterPower) { return ((dwMasterPower&PW_CAN_HIDE_ACTION)!=0L); }
	///��ѯ�Ƿ���������û�
	static bool CanControlUser(long int dwMasterPower) { return ((dwMasterPower&PW_CAN_CONTROL_USER)!=0L); }
	///��ѯ�Ƿ������ͻ���
	static bool CanMuchClient(long int dwMasterPower) { return ((dwMasterPower&PW_CAN_MUCH_CLIENT)!=0L); }
	///��ѯ�Ƿ��������÷�����
	static bool CanSetServer(long int dwMasterPower) { return ((dwMasterPower&PW_CAN_SET_SERVER)!=0L); }
	///��ѯ�����������Ϣ
	static bool CanListenMessage(long int dwMasterPower) { return ((dwMasterPower&PW_CAN_LISTEN_MESSAGE)!=0L); }
	///��ѯ���������Ϸ����
	static bool CanListenGame(long int dwMasterPower) { return ((dwMasterPower&PW_CAN_LISTEN_GAME)!=0L); }
	///��ѯ�Ƿ�����Ӽ�����
	static bool CanAddPoint(long int dwMasterPower) { return ((dwMasterPower&PW_CAN_ADD_PIONT)!=0L); }
	///��ѯ�����½���Ʒ���
	static bool CanLogonLimit(long int dwMasterPower) { return ((dwMasterPower&PW_CAN_LOGON_LIMIT)!=0L); }
	///��ѯ�Ƿ���������Ȩ��
	static bool CanAllPower(long int dwMasterPower) { return ((dwMasterPower&PW_CAN_ALL_POWER)!=0L); }

	///������ͨ���Ȩ������
public:
	///�����Ƿ������������
	static void SetCanRoomTalk(long int & dwGamePower, BYTE bEnable) { if (bEnable) dwGamePower&=~PW_NO_ROOM_TALK; else dwGamePower|=PW_NO_ROOM_TALK; }
	///�����Ƿ�������Ϸ����
	static void SetCanGameTalk(long int & dwGamePower, BYTE bEnable) { if (bEnable) dwGamePower&=~PW_NO_GAME_TALK; else dwGamePower|=PW_NO_GAME_TALK; }
	///�����Ƿ���������Ϣ
	static void SetCanSendMessage(long int & dwGamePower, BYTE bEnable) { if (bEnable) dwGamePower&=~PW_NO_SEND_MESSAGE; else dwGamePower|=PW_NO_SEND_MESSAGE; }
	///�����Ƿ����������Ϸ
	static void SetCanPlayGame(long int & dwGamePower, BYTE bEnable) { if (bEnable) dwGamePower&=~PW_N0_PLAY_GAME; else dwGamePower|=PW_N0_PLAY_GAME; }
	///�����Ƿ������Թ���Ϸ
	static void SetCanWatchGame(long int & dwGamePower, BYTE bEnable) { if (bEnable) dwGamePower&=~PW_NO_WATCH_GAME; else dwGamePower|=PW_NO_WATCH_GAME; }
	///�����Ƿ�������������
	static void SetCanThrowPass(long int & dwGamePower, BYTE bEnable) { if (bEnable) dwGamePower|=PW_CAN_THROW_PASS; else dwGamePower&=~PW_CAN_THROW_PASS; }
	///�����Ƿ�������������
	static void SetCanThrowSet(long int & dwGamePower, BYTE bEnable) {  if (bEnable) dwGamePower|=PW_CAN_THROW_SET; else dwGamePower&=~PW_CAN_THROW_SET; }
	///�����Ƿ�����������
	static void SetCanSendMuch(long int & dwGamePower, BYTE bEnable) { if (bEnable) dwGamePower|=PW_CAN_SEND_MUCH; else dwGamePower&=~PW_CAN_SEND_MUCH; }
	///�����Ƿ�������������
	static void SetCanSetFont(long int & dwGamePower, BYTE bEnable) { if (bEnable) dwGamePower|=PW_CAN_SET_FONT; else dwGamePower&=~PW_CAN_SET_FONT; }
	///�����Ƿ�����ˢ��Ļ
	static void SetCanTalkFast(long int & dwGamePower, BYTE bEnable) { if (bEnable) dwGamePower|=PW_CAN_TALK_FAST; else dwGamePower&=~PW_CAN_TALK_FAST; }
	///�����Ƿ�����߼��ۿ�
	static void SetCanHighLook(long int & dwGamePower, BYTE bEnable) { if (bEnable) dwGamePower|=PW_CAN_HIGH_LOOK; else dwGamePower&=~PW_CAN_HIGH_LOOK; }
	///�����Ƿ������������
	static void SetCanFindUser(long int & dwGamePower, BYTE bEnable) { if (bEnable) dwGamePower|=PW_CAN_FIND_USER; else dwGamePower&=~PW_CAN_FIND_USER; }
	///�����Ƿ������κ��Թ�
	static void SetCanWatchAnyTime(long int & dwGamePower, BYTE bEnable) { if (bEnable) dwGamePower|=PW_CAN_WATCH_ANYTIME; else dwGamePower&=~PW_CAN_WATCH_ANYTIME; }

	///���ù���ԱȨ������
public:
	///�����Ƿ�����������Ϣ
	static void SetCanSendWarning(long int & dwMasterPower, BYTE bEnable) { if (bEnable) dwMasterPower|=PW_CAN_SEND_WARNING; else dwMasterPower&=~PW_CAN_SEND_WARNING; }
	///�����Ƿ�����ϵͳ��Ϣ
	static void SetCanSendSystem(long int & dwMasterPower, BYTE bEnable) { if (bEnable) dwMasterPower|=PW_CAN_SEND_SYSTEM; else dwMasterPower&=~PW_CAN_SEND_SYSTEM; }
	///�����Ƿ�������Ϸ��Ϣ
	static void SetCanSendGame(long int & dwMasterPower, BYTE bEnable) { if (bEnable) dwMasterPower|=PW_CAN_SEND_GAME; else dwMasterPower&=~PW_CAN_SEND_GAME; }
	///�Ƿ������ֹ�����˴�������
	static void SetCanLimiteRoomTalk(long int & dwMasterPower, BYTE bEnable) { if (bEnable) dwMasterPower|=PW_CAN_LIMIT_OTHER_ROOM_TALK; else dwMasterPower&=~PW_CAN_LIMIT_OTHER_ROOM_TALK; }
	///�����Ƿ������ֹ��������Ϸ����
	static void SetCanLimiteGameTalk(long int & dwMasterPower, BYTE bEnable) { if (bEnable) dwMasterPower|=PW_CAN_LIMIT_OTHER_GAME_TALK; else dwMasterPower&=~PW_CAN_LIMIT_OTHER_GAME_TALK; }
	///�����Ƿ������ֹ�����˷�����
	static void SetCanLimiteOtherSend(long int & dwMasterPower, BYTE bEnable) { if (bEnable) dwMasterPower|=PW_CAN_LIMIT_OTHER_SEND; else dwMasterPower&=~PW_CAN_LIMIT_OTHER_SEND; }
	///�����Ƿ������ֹ��������Ϸ
	static void SetCanLimiteOtherPlay(long int & dwMasterPower, BYTE bEnable) { if (bEnable) dwMasterPower|=PW_CAN_LIMIT_OTHER_PLAY; else dwMasterPower&=~PW_CAN_LIMIT_OTHER_PLAY; }
	///�����Ƿ������ֹ�������Թ�
	static void SetCanLimiteOtherWatch(long int & dwMasterPower, BYTE bEnable) { if (bEnable) dwMasterPower|=PW_CAN_LIMIT_OTHER_WATCH; else dwMasterPower&=~PW_CAN_LIMIT_OTHER_WATCH; }
	///�����Ƿ���������Ϸ
	static void SetCanSafeFinish(long int & dwMasterPower, BYTE bEnable) { if (bEnable) dwMasterPower|=PW_CAN_SAFE_FINISH; else dwMasterPower&=~PW_CAN_SAFE_FINISH; }
	///�����Ƿ��������������
	static void SetCanCutUser(long int & dwMasterPower, BYTE bEnable) { if (bEnable) dwMasterPower|=PW_CAN_CUT_USER; else dwMasterPower&=~PW_CAN_CUT_USER; }
	///�����Ƿ�����鿴 IP
	static void SetCanLookIP(long int & dwMasterPower, BYTE bEnable) { if (bEnable) dwMasterPower|=PW_CAN_LOOK_USER_IP; else dwMasterPower&=~PW_CAN_LOOK_USER_IP; }
	///�����Ƿ������ֹ IP
	static void SetCanLimiteIP(long int & dwMasterPower, BYTE bEnable) { if (bEnable) dwMasterPower|=PW_CAN_LIMIT_IP; else dwMasterPower&=~PW_CAN_LIMIT_IP; }
	///�����Ƿ������������� IP
	static void SetCanHideIP(long int & dwMasterPower, BYTE bEnable) { if (bEnable) dwMasterPower|=PW_CAN_HIDE_IP; else dwMasterPower&=~PW_CAN_HIDE_IP; }
	///�����Ƿ������ֹ�ʺ�
	static void SetCanLimiteAccoun(long int & dwMasterPower, BYTE bEnable) { if (bEnable) dwMasterPower|=PW_CAN_LIMIT_ACCOUN; else dwMasterPower&=~PW_CAN_LIMIT_ACCOUN; }
	///�����Ƿ������ѯȨ��
	static void SetCanLookPower(long int & dwMasterPower, BYTE bEnable) { if (bEnable) dwMasterPower|=PW_CAN_LOOK_POWER; else dwMasterPower&=~PW_CAN_LOOK_POWER; }
	///�����Ƿ���������Ȩ��
	static void SetCanSetPower(long int & dwMasterPower, BYTE bEnable) { if (bEnable) dwMasterPower|=PW_CAN_SET_POWER; else dwMasterPower&=~PW_CAN_SET_POWER; }
	///�����Ƿ��������Ϸ
	static void SetCanBindGame(long int & dwMasterPower, BYTE bEnable) { if (bEnable) dwMasterPower|=PW_CAN_BIND_GAME; else dwMasterPower&=~PW_CAN_BIND_GAME; }
	///�����Ƿ�������ʺ�
	static void SetCanBindAccoun(long int & dwMasterPower, BYTE bEnable) { if (bEnable) dwMasterPower|=PW_CAN_BIND_ACCOUN; else dwMasterPower&=~PW_CAN_BIND_ACCOUN; }
	///�����Ƿ��������ض���
	static void SetCanHideAction(long int & dwMasterPower, BYTE bEnable) { if (bEnable) dwMasterPower|=PW_CAN_HIDE_ACTION; else dwMasterPower&=~PW_CAN_HIDE_ACTION; }
	///�����Ƿ���������û�
	static void SetCanControlUser(long int & dwMasterPower, BYTE bEnable) { if (bEnable) dwMasterPower|=PW_CAN_CONTROL_USER; else dwMasterPower&=~PW_CAN_CONTROL_USER; }
	///�����Ƿ������ͻ���
	static void SetCanMuchClient(long int & dwMasterPower, BYTE bEnable) { if (bEnable) dwMasterPower|=PW_CAN_MUCH_CLIENT; else dwMasterPower&=~PW_CAN_MUCH_CLIENT; }
	///�����Ƿ��������÷�����
	static void SetCanSetServer(long int & dwMasterPower, BYTE bEnable) { if (bEnable) dwMasterPower|=PW_CAN_SET_SERVER; else dwMasterPower&=~PW_CAN_SET_SERVER; }
	///�����Ƿ������������Ϣ
	static void SetCanListenMessage(long int & dwMasterPower, BYTE bEnable) { if (bEnable) dwMasterPower|=PW_CAN_LISTEN_MESSAGE; else dwMasterPower&=~PW_CAN_LISTEN_MESSAGE; }
	///�����Ƿ����������Ϸ����
	static void SetCanListenGame(long int & dwMasterPower, BYTE bEnable) { if (bEnable) dwMasterPower|=PW_CAN_LISTEN_GAME; else dwMasterPower&=~PW_CAN_LISTEN_GAME; }
	///�����Ƿ�����Ӽ�����
	static void SetCanAddPoint(long int & dwMasterPower, BYTE bEnable) { if (bEnable) dwMasterPower|=PW_CAN_ADD_PIONT; else dwMasterPower&=~PW_CAN_ADD_PIONT; }
	///�����Ƿ������½���Ʒ���
	static void SetLogonLimit(long int & dwMasterPower, BYTE bEnable) { if (bEnable) dwMasterPower|=PW_CAN_LOGON_LIMIT; else dwMasterPower&=~PW_CAN_LOGON_LIMIT; }
	///�����Ƿ���������Ȩ��
	static void SetCanAllPower(long int & dwMasterPower, BYTE bEnable) { if (bEnable) dwMasterPower|=PW_CAN_ALL_POWER; else dwMasterPower&=~PW_CAN_ALL_POWER; }
};

#endif