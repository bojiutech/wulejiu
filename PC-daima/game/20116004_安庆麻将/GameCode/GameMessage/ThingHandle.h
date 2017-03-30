/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #pragma once
#include "..\ChangeFile\GameDataEx.h"
#include "..\ChangeFile\UserDataEx.h"
#include "..\ChangeFile\CheckHuPaiEx.h"
#include "..\ChangeFile\CheckCPGActionEx.h"


class CServerGameDesk;

#define TIME_CHECK_GAME_MSG         30              // �����Ϸ��Ϣ���ݰ�����ʱû���յ����ݰ�����Ϊ�ǿ�ס�ˣ�ϵͳ�Զ�����
#define TIME_WAIT_MSG				32              // �����¼�����Ӧ���ǳ�ʱ�Զ�����ϵͳ�Զ�����
#define TIME_DEFAULT_HANDLE         60000			// Ĭ��ʱ��60��

///�¼�������
class ThingHandle
{
public:
	ThingHandle(void);
	~ThingHandle(void);
	
public:	
	CServerGameDesk *pDesk;//���ࣨ���ӣ�
	
public:
	//��������ָ��
	void SetDeskPoint(CServerGameDesk *desk);

///////�������ݴ���//////////////////////////////////////////////////////
	//���������¼�
	virtual bool GetGameStaton(BYTE bDeskStation, bool bWatchUser,BYTE GameStation);
	// ��Ϸ���ݰ�������
	virtual int HandleNotifyMessage(int bDeskStation, UINT code, BYTE* pData, int uSize, bool bWatchUser);

	// �յ��û�ɫ�Ӷ���������Ϣ
	virtual int ReceiveSeziFinish(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser);
	// �յ��й���Ϣ
	virtual int ReceiveUserTuoGuan(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser);
	// �û�����
	virtual int ReceiveUserOutCard(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser);
	// �յ��û�pass ��Ϣ
	virtual int ReceiveUserPassCheck(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser);
	//�յ��û�ͬ����Ϸ��Ϣ
	virtual int ReceiveUserAgreeGame(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser);
	//���������뿪
	virtual int ReceiveUserHaveThing(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser);
	//ͬ���û��뿪
	virtual int ReceiveArgeeUserLeft(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser);
	// �û�������Ϣ
	virtual int ReceiveUserChiCard(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser);
	// �û�������Ϣ
	virtual int ReceiveUserPengCard(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser);
	// �û�������Ϣ
	virtual int ReceiveUserGangCard(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser);
	// �û�������Ϣ
	virtual int ReceiveUserTingCard(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser);
	// �û�������Ϣ
	virtual int ReceiveUserHuCard(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser);
	///�յ������ͻ�����������Ϣ
	virtual void ReceiveSuperChangePai(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser);

	///�����������һ������
	virtual void CheckNextAction();
	///����Ƿ���Խ�����һ������
	virtual bool IsCanHandle();
	//��ȡ�������ҽ������:�ж��������ҵ�ʱ��
	virtual BYTE GetCanHuUser(BYTE outst,bool hu[],BYTE hust);
	///��ȡ�¼�λ��
	virtual BYTE GetNextStation(BYTE station,bool shun=false);
	///������ʱ����
	virtual void ClearTempData();

////�����¼�����///////////////////////////////////////////////////////////////////////////////

	//�����¼�,typeҪ������¼�
	virtual void ApplyAction(int type,int time);
	//��Ϸ�¼����������ģ�ȷ����һ���¼���ʲô�������¼�ֵ,type������¼�����
	virtual void GameCPU(int type);
	///��ʼ�¼�����
	virtual void ExecuteGameBegin(BYTE &nextID,BYTE &time);
	///�Ե�һ�����Ϊׯ��
	virtual void ExecuteDongNt(BYTE &nextID,BYTE &time);
	///��2��ɫ��ȷ��ׯ�ң������ͣ�
	virtual void ExecuteTwoSeziNt(BYTE &nextID,BYTE &time);	
	///��2��ɫ��ȷ��ׯ�Һ����Ʒ��򣨵�����ׯ�ң���㷽��
	virtual void ExecuteTwoSeziNtAndDir(BYTE &nextID,BYTE &time);	
	///������ɫ��ȷ��ׯ��
	virtual void ExecuteTurnSeziNt(BYTE &nextID,BYTE &time);	
	///��2��ɫ��ȷ�����Ʒ��򣨵�����ȷ������
	virtual void ExecuteTwoSeziDir(BYTE &nextID,BYTE &time);	
	///��2��ɫ��ȷ�����Ʒ�������ƶ����������ͷ���С�������
	virtual void ExecuteTwoSeziDirGp(BYTE &nextID,BYTE &time);	
	///��2��ɫ��ȷ�����ƶ����������Ͷ�����
	virtual void ExecuteTwoSeziGp(BYTE &nextID,BYTE &time);	
	///��ע�¼���ȷ��ׯ�Һ󣬿���ͨ��ѡ���ע������Ӯ��
	virtual void ExecuteAddNote(BYTE &nextID,BYTE &time);	
	///��2��ɫ��ȷ��ׯ��+���Ʒ���+���ƶ�����������ׯ�ң���㷽��С�������
	virtual void ExecuteTwoSeziNtDirGp(BYTE &nextID,BYTE &time);	
	///����
	virtual void ExecuteSendPai(BYTE &nextID,BYTE &time);	
	///��2��ɫ�Ӷ����¼�
	virtual void ExecuteTwoSeziMakeJing(BYTE &nextID,BYTE &time);	
	///������Ҳ����¼�
	virtual void ExecuteAllBuHua(BYTE &nextID,BYTE &time);	
	///������Ҳ����¼�
	virtual void ExecuteOneBuHua(BYTE &nextID,BYTE &time);	
	///��ʼ����֪ͨ�¼�
	virtual void ExecuteBeginOut(BYTE &nextID,BYTE &time);	
	///ץ���¼�
	virtual void ExecuteZhuaPai(BYTE &nextID,BYTE &time);	
	///����¼�
	virtual void ExecuteCountFen(BYTE &nextID,BYTE &time);
	///������Ϸ�����¼�
	virtual void ExecuteNormalEnd(BYTE &nextID,BYTE &time);
	///�쳣��Ϸ�����¼��¼�
	virtual void ExecuteUnNormalEnd(BYTE &nextID,BYTE &time);

		//���ƺ���
	virtual void DisPatchCard();
	///������ת����������,�������������е�����ת����ÿ����ҵ�����������
	virtual void ChangeMenPai();
	///������ץһ����
	virtual BYTE GetPai(int station,bool head,BYTE type=0,BYTE *pIndex=NULL);
	///������station��ǰ������Щ����
	virtual bool CheckAction(int station,BYTE pai,BYTE type);
	///�����Զ�������
	virtual void NetCutAutoHandle();
	//�ſ����Զ�����
	virtual void AutoHandle();
	///�Զ�������ƻ���ץ��
	virtual void AutoOutOrGet();

//////�����������///////////////////////////////////////////////////////////

	///�����¼�
	virtual void HandleChiPai(BYTE &nextID,BYTE &time);	
	///�����¼�
	virtual void HandlePengPai(BYTE &nextID,BYTE &time);	
	///���¼�
	virtual void HandleGangPai(BYTE &nextID,BYTE &time);	
	///���¼�
	virtual void HandleTingPai(BYTE &nextID,BYTE &time);	
	///���¼�
	virtual void HandleHuPai(BYTE &nextID,BYTE &time);	
	///���
	virtual void HandleCountFen(BYTE &nextID,BYTE &time);	


////////////////////��������///////////////////////////////////////////////

    /// ��Ҷ���
    virtual void UserNetCut(BYTE bDeskStation);
    /// �������
    virtual void UserLeftDesk(BYTE bDeskStation);
    /// �������
    virtual void UserReCome(BYTE bDeskStation);
	/// �����ʱ����Ϣ
	virtual void OnGameTimer(UINT uTimerID);

	/// ���ó�ʱ����
	virtual void SetOutTime(BYTE station,BYTE time,BYTE thing,bool effect);
	/// �ָ���ʱ����
	virtual void ReSetOutTime();
	/// ��ʱ����
	virtual void OutTimeHandle();
};


