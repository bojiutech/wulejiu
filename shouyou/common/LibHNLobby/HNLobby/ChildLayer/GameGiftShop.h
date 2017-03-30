#ifndef __GameGiftShop_LAYER_H__
#define __GameGiftShop_LAYER_H__

#include "HNLobby/PlatformDefine.h"
#include "HNLobby/Shop/ShopManager.h"
#include "network/HttpClient.h"
#include "HNNetExport.h"
#include "HNUIExport.h"
//#include "HNOpenExport.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace HN;
using namespace ui;
using namespace cocostudio;
using namespace cocos2d::network;


class GameGiftShop : public HNLayer, public HNHttpDelegate
{
	struct GiftInfo
	{
		int				giftID;			//��ƷID
		std::string		giftName;		//��Ʒ����
		std::string		giftInfo;		//��Ʒ���
		std::string		giftPic;		//��ƷͼƬ
		int				giftNum;		//��Ʒ���
		LLONG			lotteryNum;		//���轱ȯ
		int				giftType;		//��Ʒ���ͣ�����/ʵ�
		std::string		addDate;		//���ʱ��
	};

	std::vector<GiftInfo>		_gifts;
	std::vector<Sprite*>		_pagesPrompt;

public:
	typedef std::function<void ()> CloseCallBack;
	CloseCallBack	onCloseCallBack;

public:
	static GameGiftShop* createGameGiftShop(MoneyChangeNotify* delegate, LLONG lottery);

public:
	GameGiftShop();
	virtual ~GameGiftShop();

	bool init(LLONG lottery);

	void setChangeDelegate(MoneyChangeNotify* delegate);

	//�ر��̵�
	void closeGiftShop();

public:
	// ��ȡ������Ʒ�һ�ҳ��
	void getVirtualPage(GiftInfo* info, SpriteFrame* frame);

	// ��ȡʵ��һ�ҳ��
	void getEntityPage(GiftInfo* info, SpriteFrame* frame);

public:
	// ��ȡ��ѯ��������
	void getQueryParams();

	// ������Ʒҳ��
	void createGiftPages();

	// ��ѯ�����Ӧ
	void onHttpQueryCompleted(const std::string& data);

	// ��ȡ�һ���¼����
	void getRecordParams();

	// �һ���¼��Ӧ
	void onHttpRecordCompleted(const std::string& data);

	// ������ƷͼƬ��Ӧ
	void onHttpDownloadPicCompleted(const std::string& tag, const std::string& data);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// ��ȡ�һ���������
	std::string getExchangeParams(int awardid, const std::string address, const std::string name, const std::string mobile);

	// �һ���Ʒ��Ӧ
	void onHttpExchangeGiftCompleted(const std::string& data);

	virtual void onHttpResponse(const std::string& requestName, bool isSucceed, const std::string &responseData) override;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// ǩ����Ϸ�������
	std::string signParams(std::vector<std::string>& params);

	// ��������
	void requestWithParams(const std::string& params, const std::string& tag, const std::string& url, HttpRequest::Type type);


private:
	//pageView�϶��ص�����
	void pageViewMoveCallBack(Ref* pSender, PageView::EventType type);

	//�б�ť����ص�����
	void btnEventCallBack(Ref* pSender, Widget::TouchEventType type);

private:
	MoneyChangeNotify*				_delegate;
	Layout*							_panel_Gift;
	Layout*							_panel_GiftPage;
	Layout*							_panel_Record;
	Layout*							_panel_Virtual;
	Layout*							_panel_Entity;
	PageView*						_pageView_Gift;
	ListView*						_listView_Record;
	Button*							_btnShop;
	Button*							_btnRecord;
	INT								_currentPageIdx;



};

#endif // __GameGiftShop_LAYER_H__
