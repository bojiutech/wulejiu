#ifndef __GAMESTORE_LAYER_H__
#define __GAMESTORE_LAYER_H__

#include "HNLobby/PlatformDefine.h"
#include "HNLobby/Shop/ShopManager.h"
#include "HNNetExport.h"
#include "HNUIExport.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "network/HttpClient.h"

USING_NS_CC;
using namespace HN;
using namespace ui;
using namespace cocostudio;


class GameStoreLayer : public HNLayer, public HNHttpDelegate
{
public:
	typedef std::function<void ()> CloseCallBack;
	CloseCallBack	onCloseCallBack;

private:
	ListView* _storeList;
    Button* _closeButton;
	Layout* createStoreItemTemplate(const PRODUCT_INFO* productleft, const PRODUCT_INFO* productRight, int pos, int type = 1);
	Node* payLoader;
	LayerColor* colorLayer;
	EventListenerTouchOneByOne* touchListener;
public:
	static GameStoreLayer* createGameStore(MoneyChangeNotify* delegate);

public:
	GameStoreLayer();
	virtual ~GameStoreLayer();

	virtual bool init() override;

	void setChangeDelegate(MoneyChangeNotify* delegate);
	
	void openStore(Node* parent, Vec2 vec, int zorder, int tag);

	void showPayLayer(const PRODUCT_INFO* product);
	Button* showStoreMassage(const PRODUCT_INFO* product, int pos, int type);

	void closeStore();
    //ˢ�½�һص�
    void RefrshCoin();

	// ������Ϣ�ص�����
private:
	void buyEventCallBack(Ref* pSender, Widget::TouchEventType type);

	void closeEventCallBack(Ref* pSender, Widget::TouchEventType type);

	void closePayCallBack(Ref* pSender, Widget::TouchEventType type);

	bool payEventSelector(HNSocketMessage* socketMessage);

    void GetOrderEventCallBack(Ref* pSender, Widget::TouchEventType type);

	void btnCallBackDiamond(Ref* pSender);

	void btnCallBackJinBi(Ref* pSender);

	void exchangeDiamondsCallBack(Ref* pSender, Widget::TouchEventType type);

private:
	void payCB(const std::string& args);
    
    // ֧���ɹ��ص�
    void payCallback(const std::string& data);

	// ֧���ɹ��ص�
	void payCallback_IAP(const std::string& data);
    
    // http������Ӧ
	virtual void onHttpResponse(const std::string& requestName, bool isSucceed, const std::string &responseData) override;
	void onSDKGetMoneyCallback(const std::string& data);
	void onIAPGetMoneyCallback(const std::string& data);
	void onAddOrderCallback(const std::string& data);
    void onFreshMoneyCallback(const std::string& data);
    
    // ����ʧ����ʾ
    void supportAlert();

	// ��ȡ��ѯ��������
	std::string getCheckOrderParam();

	// ������ѯ�ӿ�(���Ǹ�����֤��
	bool checkOrder(std::string &result);

	// ����������ѯ���ز���
	bool parseCheckOrder(const std::string result, std::string &is_success, std::string &sign, std::string& merchant_code, std::string& order_no,
		std::string& trade_status);

	// ʵ�ʷ�����������̨��
	void payMoney();

	//ִ��֧��
	void executePayment_Dinpay(PRODUCT_INFO* productInfo);
	//ִ��֧��
	void executePayment(PRODUCT_INFO* productInfo);
	//ִ��֧��
	void startPayment(PRODUCT_INFO* productInfo);

	std::string addOrder_URL(const char* userName, LLONG SerialNumber, INT stype, DOUBLE price, std::string payType);

	std::string getOrder_URL(std::string orderID);

	std::string getPayTypeInfo(INT payType);

	void selectTabCallBack(cocos2d::Ref* pSender, Widget::TouchEventType touchtype);

	void handleSelectTab(bool showBuyJinBi, bool showBuyDiamond);

	void createBuyJinBiUi();
    
	//������Ʒ�б�
	void createStore(int type);
private:
    // ������
    std::string						_orderId;
    
    PRODUCT_INFO*					_product;
	MoneyChangeNotify*				_delegate;
	Text*							_selfCoin;//��ֵ�ɹ���ˢ�½��棬�ĳɳ�Ա

	// ������
	std::string                     _orderNo;

	// δ����ҵĶ�����
	std::string                     _notOfferOrderNo;

	Button*							_buyJinBi;
	Button*							_buyDiamond;
	bool                             _isDan = true;
};

#endif // __GAMESTORE_LAYER_H__
