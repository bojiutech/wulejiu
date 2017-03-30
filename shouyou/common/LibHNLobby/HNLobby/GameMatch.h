#ifndef __GameMatch_h__
#define __GameMatch_h__

#include "HNUIExport.h"
#include "HNNetExport.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

using namespace ui;
using namespace cocostudio;

class GameMatch : public HNLayer, IRoomMessageDelegate
{
private:
	struct MATCH_LAYOUT
	{
		Layout*		MatchInfoLayout;
		Text*				Label_ChampionCount;			// ��ڴ���
		Text*				Label_RankingCount;				// �������
		Text*				Label_MatchCount;					// ��������
		ListView*	ListView_Reward;

	} _matchLayout;

	struct MATCH_OPERATOR_LAYOUT
	{
		Button*		Button_JoinMatch;
		Button*		Button_UnJoinMatch;
		Text*				Label_SignedCount;
		Text*				Label_NeedCount;

	} _operatorLayout;

	int						_btnIndex;									//������������ť���л�	
	ImageView*	_Time;											//����ʱ����ͼƬ
	bool					_isOver;										//���������Ƿ�ﵽ
	bool					_isJoin;											//�Ƿ���
	Text*					_beginTimeText;						//��ʱ������ʱ��
	int						_timeMatchIndex;					//������ʹ�õĶ�ʱ���������
	int						_iValue;											//����i��ֵ

public:
	static void createMatch();

public:
	GameMatch();
	virtual ~GameMatch();

public:
	virtual bool init() override;

	// ����ӿں���
public:
	// ��ת�������б�
	void returnRoom(Ref* pSender, Widget::TouchEventType type);

	void joinMatchCallBack(Ref* pSender, Widget::TouchEventType type);

	// ��ʱ���ص�����
public:
	void countDown(float delay);

	void timeMatchCountDown(float delay);

	//���ҵ�ǰ�������Ŀ�ʼʱ��
	std::string stringToTime(std::string beginTime);		

	//�˳�����ʱ�����ʱ������MARKΪ1������
	void cleanTimeMatchData();

	//�˳�����
	void exitMatchRoom();

	//�������
	void overdue(float dt);

	//��ⱨ���Ķ�ʱ���Ƿ�ʼ
	void checkTimeMatchStart(float dt);

	//��ʱ���ȴ�����
	bool waitTimeMatch();

public:
	//���������ʼ��
	bool contestInit();

	//������������Ϣ����
	bool contestRegistrationResult(HNSocketMessage* socketMessage);

public:
	// �Ŷ��û�����
	virtual void I_R_M_QueueUserSit(BYTE deskNo, const std::vector<QUEUE_USER_SIT_RESULT*>& users);// override;

	// ��������
	virtual void I_R_M_ContestOver(MSG_GR_ContestAward* contestAward); 

	//������Ϣ�㲥-------->���±�������
	virtual void I_R_M_ContestNotic(MSG_GR_I_ContestInfo* contestInfo);

public:
	CREATE_FUNC(GameMatch);
};

#endif // __GameMatch_h__