/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #pragma once
#include "../Server/ServerManage.h"


/// ������Ϸ��������
class CServerGameDeskEx : public CServerGameDesk, virtual public IGameDesk
{
public:
    CServerGameDeskEx();
    ~CServerGameDeskEx();

    //���غ���
public:
    //-------------------------------------------------------------------------
    // ��IGameDesk����
    //-------------------------------------------------------------------------
    /// ������Ϸ�ڲ���Ϣ
    virtual int HandleNotifyMessage(int nDeskStation, UINT code, BYTE* pBuffer, int nLen);
    /// ��ȡ��Ϸ״̬�������͵��ͻ���
    virtual int OnGetGameStation(int nDeskStation, UserInfoForGame_t& userInfo);
    /// �������
    virtual int UserReCome(int nDeskStation, UserInfoForGame_t& userInfo);
    /// ��ʱ��ʱ�䵽
    virtual int OnGameTimer(int nTimerID);
    /// ��Ҷ���
    virtual int UserNetCut(int nDeskStation, UserInfoForGame_t& userInfo);
    /// ���������ĳλ��
    virtual int UserSitDesk(int nDeskStation, UserInfoForGame_t& userInfo);
    /// �������
    virtual int UserLeftDesk(int nDeskStation, UserInfoForGame_t& userInfo);
    /// ���ͬ����Ϸ
    virtual int UserAgreeGame(int nDeskStation, UserInfoForGame_t& userInfo);
    /// ��Ϸ�Ƿ��ڽ�����
    virtual bool IsPlayingByGameStation(void);
    /// ĳ��������Ƿ�����Ϸ��
    virtual bool IsPlayGame(int bDeskStation);
    /// ��ʼ������
    virtual int InitialDesk(int nDeskNo, int nMaxPeople, IGameMainManager* pIMainManager);
    /// ��ȡ��ǰ��Ϸ״̬
    virtual int GetCurGameStation(){return m_bGameStation;}
    ///������Ϸ�û���Ϸ��ǿ��
    virtual int ForceQuit(){return 0;}
    //-------------------------------------------------------------------------    
	// ��Ϸ����
	virtual bool GameFinish(BYTE bDeskStation, BYTE bCloseFlag);


	///��ɫ�ӿ����¼�
	void HandleSeziLookBao();

public:



};
