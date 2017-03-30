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
    /*****************************����̳�****************************/
    virtual void scrollViewDidScroll(extension::ScrollView* view) {};//����
    virtual void scrollViewDidZoom(extension::ScrollView* view) {};  //�Ŵ�

    /***************************TableView**********************************/

    virtual void tableCellTouched(TableView* table, TableViewCell* cell);//�����¼�
    virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);//Cell��С
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);//���Cell
    virtual ssize_t numberOfCellsInTableView(TableView *table);//����Cell����

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
    //��ȡ��������
    void getOrderListData();
    //����򿪶����б�ص�
    void openOrderListEventSelector(const std::string& data);
    //����
    void PayAgain(const std::string& data);
    // ����ʧ����ʾ
    void supportAlert();
};


#endif // __GAMERANKING_LAYER_H__