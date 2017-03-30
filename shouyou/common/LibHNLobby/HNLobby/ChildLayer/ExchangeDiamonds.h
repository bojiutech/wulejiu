#ifndef EXCHANGE_MONEY_H__
#define EXCHANGE_MONEY_H__

#include "HNUIExport.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "network/HttpClient.h"
#include "../PlatformDefine.h"

USING_NS_CC;
using namespace HN;
using namespace ui;
using namespace cocostudio;
using namespace cocos2d::network;

class ExchangeDiamonds : public HNLayer, public ui::EditBoxDelegate
{
	struct ExchangeDiamondsUI
	{
		Node* exchangeDiamondsNode;
		Layout* exchangeDiamondsLayout;

		TextField* txtField_number;
		Button* btn_exchange;
		HNEditBox* _txtField = nullptr;
	} _exchangeDiamondsUI;
	

public:
	ExchangeDiamonds();
	virtual ~ExchangeDiamonds();

	static ExchangeDiamonds* createExchangeMoneyLayer();

	void showExchangeMoneyUI(Node* parent, Vec2 vec, int zorder, int tag);

	void closeExchangeMoneyUI();

	void setBGPositon(Vec2 vec);

	virtual bool init() override;

	void setChangeDelegate(MoneyChangeNotify* delegate);

private:
	void buttonEventCallBack(Ref* pSender, Widget::TouchEventType type);

	// 获取桌子配置回调
	bool exchangeDiamondsCallBack(HNSocketMessage* socketMessage);

	//获取兑换比例
	void getPointExchangeRate();

	// 更新兑换金币信息
	void updateExchangeMoney();
	
	virtual void editBoxReturn(ui::EditBox* editBox) {};
private:
	std::string _exchangeMoneyByPointUrl;

	std::string _getRateKeyMD5;

	std::string _exchangeKeyMD5;

	MoneyChangeNotify*	_delegate;

	INT _exchangeRate;
};

#endif // EXCHANGE_MONEY_H__
