/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #pragma once

#include "../GameMessage/ThingHandle.h"
///�¼������ࣨ���أ�
class ThingHandleEx:public ThingHandle
{
public:
	ThingHandleEx(void);
	~ThingHandleEx(void);
	
public:	
	
public:
	
///////�������ݴ���//////////////////////////////////////////////////////
	//���������¼�
	virtual bool	GetGameStaton(BYTE bDeskStation, UINT uSocketID, bool bWatchUser,BYTE GameStation);
	// ��Ϸ���ݰ�������
	virtual int		HandleNotifyMessage(int bDeskStation, UINT code, BYTE* pData, int uSize, bool bWatchUser);

	//��һ���
	int		ReceiveUserChangeCard(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser);
	bool	IsSuperUser(BYTE bDeskStation);
	// �յ��й���Ϣ
	virtual int		ReceiveUserTuoGuan(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser);
	// �û�����
	virtual int		ReceiveUserOutCard(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser);
	// �յ��û�pass ��Ϣ
	virtual int		ReceiveUserPassCheck(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser,bool bAuto = false);
	//�յ��û�ͬ����Ϸ��Ϣ
	virtual int		ReceiveUserAgreeGame(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser);
	// �û�������Ϣ
	virtual int		ReceiveUserChiCard(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser);
	// �û�������Ϣ
	virtual int		ReceiveUserPengCard(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser);
	// �û�������Ϣ
	virtual int		ReceiveUserGangCard(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser);
	// �û�������Ϣ
	virtual int		ReceiveUserTingCard(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser);
	// �û�������Ϣ
	virtual int		ReceiveUserHuCard(BYTE bDeskStation, void * pData, UINT uSize, bool bWatchUser);

	
	
	

	//��ȡ�������ҽ������:�ж��������ҵ�ʱ��
	virtual BYTE GetCanHuUser(BYTE outst,bool hu[],BYTE hust);
	///��ȡ�¼�λ��
	virtual BYTE GetNextStation(BYTE station,bool shun=false);
	///������ʱ����
	virtual void ClearTempData();




public:	/*---------��Ϸ����Ⱥ����-----------*/
	//�����¼�,typeҪ������¼�	DWJ
	virtual void	ApplyAction(int type,int time);
	//��Ϸ�¼����������ģ�ȷ����һ���¼���ʲô�������¼�ֵ,type������¼�����	DWJ
	virtual void	GameCPU(int type);
	///��ʼ�¼�����	DWJ
	virtual void	ExecuteGameBegin(BYTE &nextID,BYTE &time);
	///�Ե�һ�����Ϊׯ��	DWJ
	virtual void	ExecuteDongNt(BYTE &nextID,BYTE &time);
	///��2��ɫ��ȷ�����Ʒ��򣨵�����ȷ������	DWJ
	virtual void	ExecuteTwoSeziDir(BYTE &nextID,BYTE &time);	
	///��2��ɫ��ȷ�����Ʒ�������ƶ����������ͷ���С�������	DWJ
	virtual void	ExecuteTwoSeziDirGp(BYTE &nextID,BYTE &time);
	///����	DWJ
	virtual void	ExecuteSendPai(BYTE &nextID,BYTE &time);
	//���ƺ���	DWJ
	virtual void	DisPatchCard();
	///������ץһ����
	virtual BYTE	GetPai(int station,bool head,BYTE type=0,BYTE *pIndex=NULL);
	///������ת����������,�������������е�����ת����ÿ����ҵ�����������
	virtual void	ChangeMenPai();
	///������Ҳ����¼�	DWJ
	virtual void	ExecuteAllBuHua(BYTE &nextID,BYTE &time);
	///��ʼ����֪ͨ�¼�	DWJ
	virtual void	ExecuteBeginOut(BYTE &nextID,BYTE &time);
	///������station��ǰ������Щ����	DWJ
	virtual bool	CheckAction(int station,BYTE pai,BYTE type);
	//����ܷ�����	DWJ
	bool			CanTingDWJ(BYTE byDeskStation);
	///������ж�������������Ϣ�����	DWJ
	virtual bool	HaveUserCanDoAction(BYTE byIgnoreStation);
	///ץ���¼�
	virtual void	ExecuteZhuaPai(BYTE &nextID,BYTE &time);	
	///������Ҳ����¼�
	virtual void	ExecuteOneBuHua(BYTE &nextID,BYTE &time);
	//�����¼�
	virtual void    ExecuteBuHua(BYTE byDeskStation,BYTE byCard);
	///����¼�
	virtual void	ExecuteCountFen(BYTE &nextID,BYTE &time);
	//���㷬���ͻ���
	void			CountFanAndHua(BYTE byDeskStation,int &iHuaCount, int &iFanCount);
	///������Ϸ�����¼�
	virtual void	ExecuteNormalEnd(BYTE &nextID,BYTE &time);



	

	
	
	
	
public:	/*---------��ʱ����ӦȺ����-----------*/
	/// �����ʱ����Ϣ	DWJ
	virtual void	OnGameTimer(UINT uTimerID);
	/// ���õ�ǰ���ڷ������¼�	DWJ
	virtual void	SetDoingThing(BYTE byStation,BYTE thing, BYTE byTime = 255);
	/// �ָ���ʱ����	DWJ
	virtual void	ReSetOutTime();
	/// ���ó�ʱ����	DWJ
	virtual void	SetOutTime(BYTE station,BYTE time,BYTE thing,bool effect);
	/// ��ʱ����	DWJ
	virtual void	OutTimeHandle();





public:/*---------�¼�����Ⱥ����-----------*/
	//	��Ҵ���ʱ��ϵͳ�Զ�����	DWJ
	virtual void	AutoHandle();
	//	�Զ�������ƻ���ץ��	DWJ
	void	AutoOutOrGet();
	//	�Զ�������	DWJ
	void	AutoDoAction();	
	//	�Զ��������	DWJ
	void	AutoHuPai();
	
		

		
	
   	
	
	
	

	///�쳣��Ϸ�����¼��¼�
	virtual void ExecuteUnNormalEnd(BYTE &nextID,BYTE &time);
		
	///�����Զ�������
	virtual void NetCutAutoHandle();
	

	
	inline void LogAction();



//////�����������///////////////////////////////////////////////////////////
	//�ܷ�����
	bool CanHandleAction();
	//������
	void HandleAction();
	//�������
	void HandleChiPai();
	//��������
	void HandlePengPai();
	//�������
	void HandleGangPai(BYTE & gangType);
	//�������
	void HandleHuPai();
public:
	CString dwjlog;
};

//ȫ�ֶ���
//extern ThingHandleEx g_ThingHandle;