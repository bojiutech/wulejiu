#ifndef __GAMEONLINEREWARD_LAYER_H__
#define __GAMEONLINEREWARD_LAYER_H__

#include "HNNetExport.h"
#include "HNUIExport.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio;
using namespace ui;

class GameOnlineReward : public HNLayer
{
	struct OnlineRewardUi
	{
		ImageView*		ImageView_OnlineBG;
		ImageView*		ImageView_Light;
		Layout*			Layout_Wait;
		Layout*			Layout_Get;
		Text*			Text_Time;
		Text*			Text_Money;

		Button*			Button_Get;

	}_OnlineRewardUi;

	INT				_Time;

public:
	typedef std::function<void (LLONG money)> UpdataUserMoney;
	UpdataUserMoney onUpdataUserMoney;

	typedef std::function<void ()> CloseCallBack;
	CloseCallBack	onCloseCallBack;

public:
	GameOnlineReward();
	virtual ~GameOnlineReward();

public:
	virtual bool init() override;

	void closeOnlineReward();

	//��ť�ص�
	void buttonEventCallBack(Ref* pSender, Widget::TouchEventType type);

private:
	//��ѯ������Ϣ
	void checkRewardData();
	//�����ѯ������Ϣ�ص�
	bool checkRewardDataEventSelector(HNSocketMessage* socketMessage);

	//�콱����ʱ
	void updataGetRewardTimeMessage(float dt);

private:
	//������ȡǩ�������ص�
	bool getOnlineRewardEventSelector(HNSocketMessage* socketMessage);

public:
	CREATE_FUNC(GameOnlineReward);
};

#endif // __ONLINEREWARD_LAYER_H__
