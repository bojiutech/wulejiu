#ifndef __GAMESIGN_LAYER_H__
#define __GAMESIGN_LAYER_H__

#include "HNNetExport.h"
#include "HNUIExport.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio;
using namespace ui;

class GameSignLayer : public HNLayer
{
	struct signUi
	{
		ImageView*		ImageView_SignBG;
		ImageView*		ImageView_Light;
		Text*			Text_Prompt;
		Text*			Text_Money;

		Button*			Button_Get;

	}_SignUi;

public:
	typedef std::function<void (LLONG money)> UpdataUserMoney;
	UpdataUserMoney onUpdataUserMoney;

	typedef std::function<void ()> CloseCallBack;
	CloseCallBack	onCloseCallBack;

public:
	GameSignLayer();
	virtual ~GameSignLayer();

public:
	virtual bool init() override;

	void closeSign();

	//��ť�ص�
	void buttonEventCallBack(Ref* pSender, Widget::TouchEventType type);

private:
	//��ѯǩ����Ϣ
	void checkSignData();
	//�����ѯǩ����Ϣ�ص�
	bool checkSignDataEventSelector(HNSocketMessage* socketMessage);

private:
	//������ȡǩ�������ص�
	bool getSignRewardEventSelector(HNSocketMessage* socketMessage);

public:
	CREATE_FUNC(GameSignLayer);
};

#endif // __GAMESIGN_LAYER_H__