#ifndef __GAMEORDER_LAYER_H__
#define __GAMEORDER_LAYER_H__

#include "HNLobby/PlatformDefine.h"
#include "HNNetExport.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "extensions/cocos-ext.h"
#include "network/HttpClient.h"
#include <vector>

USING_NS_CC;
USING_NS_CC_EXT;

using namespace HN;
using namespace ui;
using namespace std;
using namespace extension;

typedef struct OrderList
{
    std::string orderID;
    std::string typeinfo;
    std::string receiptData;
    DOUBLE	    price;
    bool        paySuccess;
}OrderList;

class GameOrderList : public HNLayer, public TableViewDataSource, public TableViewDelegate,public HNHttpDelegate
{

public:
    GameOrderList();
    virtual ~GameOrderList();

public:
    typedef std::function<void()> CloseCallBack;
    CloseCallBack	onCloseCallBack;
private:
    MoneyChangeNotify* _delegate;

public:
    virtual bool init() override;
    void closeOrderList();
    void closeEventCallBack(Ref* pSender, Widget::TouchEventType type);
    void getOrderAgain(Ref* pSender, Widget::TouchEventType type, ssize_t idx);
 
    void setChangeDelegate(MoneyChangeNotify* delegate)
    {
        _delegate = delegate;
    }

    void openOrder(Node* parent, Vec2 vec, int zorder, int tag);
    CREATE_FUNC(GameOrderList);

    virtual void onHttpResponse(const std::string& requestName, bool isSucceed, const std::string &responseData) override;
    /*****************************必须继承****************************/
    virtual void scrollViewDidScroll(extension::ScrollView* view) {};//滑动
    virtual void scrollViewDidZoom(extension::ScrollView* view) {};  //放大

    /***************************TableView**********************************/

    virtual void tableCellTouched(TableView* table, TableViewCell* cell);//触摸事件
    virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);//Cell大小
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);//添加Cell
    virtual ssize_t numberOfCellsInTableView(TableView *table);//设置Cell个数

private:
    TableView *	_tableView;
    vector<OrderList> _iList;
    int MyRankNum;
    ui::Scale9Sprite* rankingFrame;
    ui::Text* rankingText;
    Button* _PayAgainButton;
    std::string _orderID;
    float _itemWidth;
    float _itemHeight;

private:
    //获取排行数据
    void getOrderListData();
    //申请打开订单列表回调
    void openOrderListEventSelector(const std::string& data);
    //补单
    void PayAgain(const std::string& data);
    // 发货失败提示
    void supportAlert();
};


#endif // __GAMERANKING_LAYER_H__