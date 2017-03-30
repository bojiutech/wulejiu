
#include "HNLobby/ChildLayer/GameOrderList.h"
#include "HNLobby/ChildLayer/GameStoreLayer.h"
#include "HNLobby/PlatformDefine.h"
#include "HNLobby/FontConfig.h"
#include "HNLobby/GamePrompt.h"
#include "HNUIExport.h"
#include "network/HttpRequest.h"
#include "json/rapidjson.h"
#include <string>

static const INT ORDERID = 10;
static const INT NUMBER = 12;
static const INT ORDERBUTTON  = 13;

static const char* RANKING_BG = "platform/store/second_payBg.png";                           //backGround
static const char* RANKING_TITLE = "platform/order/orderRecordTitle.png";
static const char* CLOSE_N = "platform/order/second_back.png";
static const char* LIST_BG = "platform/order/OrderItem.png";                                //rankingListBG
static const char* SELF_FRAME = "platform/store/common_opaque.png";                         //frame
static const char* RANK_FRAME = "platform/order/subViewFrame.png";
static const char* RANK_MYFRAME = "platform/order/myFrame.png";
static const char* LEAF_LEFT = "platform/subViewBambooLeft.png";
static const char* LEAF_RIGHT = "platform/subViewBambooRight.png";
static const char* RANK_ITEM = "platform/order/Item.png";
static const char* USER_MEN_HEAD = "platform/head/men_head.png";
static const char* USER_WOMEN_HEAD = "platform/head/women_head.png";
static const char* MY_HEAD_FRAME = "platform/ranking/headframe.png"; 
static const char* ORDER_AGAIN1 = "platform/order/OrderAgain1.png";
static const char* ORDER_AGAIN2 = "platform/order/OrderAgain2.png"; 
static const char* ORDER_SUCCESS = "platform/order/OrderSuccess.png";
static const char* ORDER_GIVEUP = "platform/order/give_up.png";


GameOrderList::GameOrderList()
{  
    _PayAgainButton = nullptr;
    _itemWidth = 0;
    _itemHeight = 0;
}

GameOrderList::~GameOrderList()
{
    PlatformLogic()->removeEventSelector(MDM_GP_PAIHANGBANG, 0);
    HNHttpRequest::getInstance()->removeObserver(this);

}

void GameOrderList::openOrder(Node* parent, Vec2 vec, int zorder, int tag)
{
    CCAssert(nullptr != parent, "parent is nullptr");

    Size winSize = Director::getInstance()->getWinSize();
    this->setPosition(vec);
    parent->addChild(this, zorder, tag);
    parent->runAction(MoveTo::create(0.3f, Vec2(0, 0)));
}

void GameOrderList::closeOrderList()
{
    HNAudioEngine::getInstance()->playEffect(GAME_SOUND_CLOSE);
    auto winSize = Director::getInstance()->getWinSize();
    this->getParent()->runAction(Sequence::create(
        MoveTo::create(0.3f, Vec2(winSize.width, 0)),
        CCCallFunc::create([&]()
    {
        //ˢ�½��
        GameStoreLayer* pLayout = (GameStoreLayer*) this->getParent();
        pLayout->RefrshCoin();
        this->removeFromParent();
    }), nullptr));
}

bool GameOrderList::init()
{
    if (!HNLayer::init()) return false;

    Size winSize = Director::getInstance()->getWinSize();

    MyRankNum = -1;
    //���а񱳾�
    setBackGroundImage(RANKING_BG);

    //���а����
    auto titleBtn = Button::create(RANKING_TITLE, RANKING_TITLE);
    titleBtn->setAnchorPoint(Point(0.5, 1));
    titleBtn->setPosition(Vec2(winSize.width / 2, winSize.height - 10));
    auto titleSize = titleBtn->getContentSize();
    titleBtn->setScale((0.8f*1280.0f / winSize.width) / (720 / winSize.height), (0.8f*1280.0f / winSize.width) / (720 / winSize.height));
    this->addChild(titleBtn, 2);

    //��Ҷ
    auto leftLeaf = Sprite::create(LEAF_LEFT);
    leftLeaf->setAnchorPoint(Point(0, 1));
    leftLeaf->setPosition(0, winSize.height);
    addChild(leftLeaf, 5);
    auto rightleaf = Sprite::create(LEAF_RIGHT);
    rightleaf->setAnchorPoint(Point(1, 1));
    rightleaf->setPosition(winSize.width, winSize.height);
    addChild(rightleaf, 5);

    auto MyListener = EventListenerTouchOneByOne::create();
    //��ֹ�������´���
    MyListener->setSwallowTouches(true);
    MyListener->onTouchBegan = [&](Touch* touch, Event* event)
    {
        auto target = dynamic_cast<GameOrderList*>(event->getCurrentTarget());//��ȡ�ĵ�ǰ������Ŀ��       
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        return rect.containsPoint(locationInNode);//�жϴ������Ƿ���Ŀ��ķ�Χ��

    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(MyListener, this);

    // �رհ�ť
    auto closeBtn = Button::create(CLOSE_N, CLOSE_N);
    closeBtn->setPosition(Vec2(winSize.width * 0.05f, winSize.height * 0.94f));
    addChild(closeBtn, 5);
    closeBtn->addTouchEventListener(CC_CALLBACK_2(GameOrderList::closeEventCallBack, this));

    //���а񱳾���ɫ
    auto rankingbg = ui::Scale9Sprite::create(SELF_FRAME);
    rankingbg->setAnchorPoint(Point(0.5, 0));
    rankingbg->setPreferredSize(Size(1300, (620.0f*(1280.0f / winSize.width)) / (720.0f / winSize.height)));
    rankingbg->setPosition(Vec2(winSize.width / 2, 0));
    addChild(rankingbg, 2);

    //���а�ı�����
    rankingFrame = ui::Scale9Sprite::create(RANK_FRAME);
    rankingFrame->setAnchorPoint(Point(0.5, 0.5));
    rankingFrame->setPreferredSize(Size(1180, (594.0f* (1280.0f / winSize.width)) / (720.0f / winSize.height)));
    rankingFrame->setPosition(Size(rankingbg->getContentSize().width / 2, winSize.height / 2 - 20));
    auto rankWidth = rankingFrame->getContentSize().width;
    auto rankHeight = rankingFrame->getContentSize().height;
    rankingbg->addChild(rankingFrame, 5);

    //���а�Ŀ¼
    auto rankImage = ui::Scale9Sprite::create(RANK_ITEM);
    //rankImage->setPreferredSize(Size(1170, 60));
    rankImage->setAnchorPoint(Point(0.5, 1));
    rankImage->setPosition(Vec2(rankWidth / 2, rankHeight - 5));
    rankingFrame->addChild(rankImage, 5);

    //���а��б�
    _tableView = TableView::create(this, Size(1180, (rankHeight - rankImage->getContentSize().height - 20)));
    _tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);//����TableView����
    _tableView->ignoreAnchorPointForPosition(false);
    _tableView->setAnchorPoint(Vec2(0.5f, 0.5f));
    _tableView->setPosition(Vec2(rankWidth / 2, rankHeight / 2 - rankImage->getContentSize().height / 2 - 3));
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);//����TableView������(��������)
    _tableView->setDelegate(this);//����ί��
    rankingFrame->addChild(_tableView);

    getOrderListData();

    return true;
}

//�رհ�ť�ص�
void GameOrderList::closeEventCallBack(Ref* pSender, Widget::TouchEventType type)
{
    Button* selectedBtn = (Button*)pSender;
    switch (type)
    {
    case cocos2d::ui::Widget::TouchEventType::BEGAN:
        selectedBtn->setColor(Color3B(170, 170, 170));
        break;
    case cocos2d::ui::Widget::TouchEventType::ENDED:
        selectedBtn->setColor(Color3B(255, 255, 255));
        closeOrderList();
        break;
    case cocos2d::ui::Widget::TouchEventType::CANCELED:
        selectedBtn->setColor(Color3B(255, 255, 255));
        break;
    default:
        break;
    }
}

//��ȡ���׼�¼
void GameOrderList::getOrderListData()
{
    std::string url = PlatformConfig::getInstance()->getNoticeUrl();
    url.append("Type=GetOrderListByUser");
    //url.append("&userID=27368");
    url.append(StringUtils::format("&userID=%d", PlatformLogic()->loginResult.dwUserID));
    url.append("&pageIndex=1");
    url.append("&pagesize=20");

    HNHttpRequest::getInstance()->addObserver(this);
    HNHttpRequest::getInstance()->request("GetOrderList", cocos2d::network::HttpRequest::Type::GET, url);
}

//����򿪶����б�ص�
void GameOrderList::openOrderListEventSelector(const std::string& data)
{
    if (data.empty())
    {
        log("data is empty");
        GamePromptLayer::create()->showPrompt(GBKToUtf8("��ѯʧ��"));
        return;
    }

    _iList.clear();
    rapidjson::Document doc;
    doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());

    if (!doc.IsObject() || doc.HasParseError())
    {
        log("data HasParseError");
        GamePromptLayer::create()->showPrompt(GBKToUtf8("��ѯʧ��"));
        return;
    }

    rapidjson::Value &array = doc["list"];
    if (array.IsArray())
    {
        for (UINT i = 0; i < array.Size(); i++)
        {
            rapidjson::Value &arraydoc = array[i];
            OrderList orderlistStruct;

            if (arraydoc.HasMember("orderID"))
            {
                orderlistStruct.orderID = arraydoc["orderID"].GetString();                                                              
            }
            if (arraydoc.HasMember("paySuccess"))
            {
                orderlistStruct.paySuccess = arraydoc["paySuccess"].GetBool();
            }
            if (arraydoc.HasMember("TypeInfo"))
            {
                orderlistStruct.typeinfo = arraydoc["TypeInfo"].GetString();
            }
            if (arraydoc.HasMember("PayMoney"))
            {
                orderlistStruct.price = arraydoc["PayMoney"].GetInt();
            }
            if (arraydoc.HasMember("Info"))
            {
                if (arraydoc["Info"].IsNull())
                {
                    orderlistStruct.receiptData = "";
                }
                else
                {
                    orderlistStruct.receiptData = arraydoc["Info"].GetString();
                }               
            }

            _iList.push_back(orderlistStruct);
        }

        _tableView->reloadData();//��������
    }
}

//���Cell
TableViewCell* GameOrderList::tableCellAtIndex(TableView *table, ssize_t idx)
{
    TableViewCell* cell = table->dequeueCell();
    if (!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
    }

    cell->removeAllChildrenWithCleanup(true);

    if (idx >= _iList.size()) return cell;
    //���б���ͼ
    auto storeItemTemplate = ImageView::create(LIST_BG);
    storeItemTemplate->setAnchorPoint(Vec2::ZERO);
    storeItemTemplate->setPosition(Vec2(5, 0));
    storeItemTemplate->setName("item");

    _itemWidth = storeItemTemplate->getContentSize().width;
    _itemHeight = storeItemTemplate->getContentSize().height;

    auto iter = _iList.begin();
    OrderList ite = *(iter + idx);
    char str[64];

    //���к�
    auto other = Sprite::create("platform/ranking/hua1.png");
    other->setPosition(Vec2(_itemWidth * 0.125f, _itemHeight * 0.5f));
    storeItemTemplate->addChild(other, 1);
    sprintf(str, "%d", idx + 1);
    rankingText = Text::create(str, "", 28);
    rankingText->setPosition(Vec2(_itemWidth * 0.125f, _itemHeight * 0.5f));
    storeItemTemplate->addChild(rankingText, 1, NUMBER);

    //������
    auto orderText = Text::create(ite.orderID, "", 28);
    orderText->setPosition(Vec2(_itemWidth * 0.47f, _itemHeight * 0.5f));
    storeItemTemplate->addChild(orderText, 1, ORDERID);

    //����״̬
    if (true == ite.paySuccess)
    {
        auto getOrder = ImageView::create(ORDER_SUCCESS);
        getOrder->setPosition(Vec2(_itemWidth * 0.865f, _itemHeight * 0.5f));
        storeItemTemplate->addChild(getOrder, 100, ORDERBUTTON);
    }
    else
    {
        //ֻ��Ҫ��ƻ���ڹ��Ľ��в�������
        if (0 == ite.typeinfo.compare("IAP"))
        {
            auto getOrder = Button::create(ORDER_AGAIN1, ORDER_AGAIN2);
            getOrder->setPosition(Vec2(_itemWidth * 0.865f, _itemHeight * 0.5f));
            getOrder->addTouchEventListener(CC_CALLBACK_2(GameOrderList::getOrderAgain, this, idx));
            storeItemTemplate->addChild(getOrder, 100, ORDERBUTTON);
        }
        else
        {
            auto getOrder = ImageView::create(ORDER_GIVEUP);
            getOrder->setPosition(Vec2(_itemWidth * 0.865f, _itemHeight * 0.5f));
            storeItemTemplate->addChild(getOrder, 100, ORDERBUTTON);
        }
    }


    cell->addChild(storeItemTemplate);

    return cell;

}

void GameOrderList::getOrderAgain(Ref* pSender, Widget::TouchEventType type,ssize_t idx)
{
    if (Widget::TouchEventType::ENDED != type) return;
    //��ȡ��ǰ��ť
    _PayAgainButton = (Button*)pSender;
    _PayAgainButton->setEnabled(false);
    //Button* psender = (Button*)pSender;
    //auto parentNode = psender->getParent();
    //��ȡ��ǰ��ť�еĶ�����
    //std::string OrderID = ((Text*)(parentNode->getChildByTag(ORDERID)))->getString();

    std::string requestData;
    // ����
    requestData.append("type=PaySucceedByIOS");

    // �û���
    requestData.append("&userName=");
    requestData.append(PlatformLogic()->loginResult.szName);

    // ��֤����
    requestData.append("&receipt_data=");
    requestData.append(_iList[idx].receiptData);

    // ������
    requestData.append("&OrderID=");
    requestData.append(_iList[idx].orderID);
    _orderID = _iList[idx].orderID;

    // ֧�����
    requestData.append("&payMoney=");
    char ch[20] = { 0 };
    sprintf(ch, "%lf", _iList[idx].price);
    requestData.append(ch);

    // ֧����ʽ
    requestData.append("&typeInfoLog=IAP");

    log("send>%s", requestData.c_str());
    std::string url_temp = PlatformConfig::getInstance()->getPayCallbackUrl_iOS();

    log("url_temp =%s", PlatformConfig::getInstance()->getPayCallbackUrl_iOS().c_str());
    //HNHttpRequest::getInstance()->addObserver(this);
    HNHttpRequest::getInstance()->request("PayAgain", cocos2d::network::HttpRequest::Type::POST, url_temp, requestData);
}

//����Cell��С
Size GameOrderList::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return Size(1090, 85);
}

//����Cell����
ssize_t GameOrderList::numberOfCellsInTableView(TableView *table)
{
    return _iList.size();
}

//Cell�����¼�
void GameOrderList::tableCellTouched(TableView *table, TableViewCell *cell)
{
    log("cell touched at index %d", cell->getIdx());
}


void GameOrderList::onHttpResponse(const std::string& requestName, bool isSucceed, const std::string &responseData)
{   
    std::string tmp = Utf8ToGB(responseData.c_str());
    
    if (requestName.compare("GetOrderList") == 0)
   {
       if (!isSucceed)
       {
           GamePromptLayer::create()->showPrompt(GBKToUtf8("��ѯʧ�ܣ�"));
           return;
       }

       openOrderListEventSelector(responseData);
   }

   if (requestName.compare("PayAgain") == 0)
   {
       if (!isSucceed)
       {
           _PayAgainButton->setEnabled(true);
           GamePromptLayer::create()->showPrompt(GBKToUtf8("����֧��ʧ�ܣ�"));
           return;
       }

       PayAgain(responseData);
   }
}

void GameOrderList::PayAgain(const std::string& data)
{
    std::string cache = data;

    if (cache.empty())
    {
        supportAlert();
        return;
    }
    rapidjson::Document doc;
    doc.Parse<rapidjson::kParseDefaultFlags>(cache.c_str());

    if (doc.HasParseError())
    {
        supportAlert();
        return;
    }

    // �������
    if (!doc.IsObject() || !doc.HasMember("rs") || !doc.HasMember("msg"))
    {
        supportAlert();
        return;
    }

    int rs = doc["rs"].GetInt();
    if (rs == 1)
    {
        if (doc.HasMember("WalletMoney"))
        {
            LLONG money = doc["WalletMoney"].GetUint64();
			std::string str;
			str.append("�����ɹ� ,��ǰ����Ϊ:");
			str.append(StringUtils::toString(money));
			str.append("��");
            GamePromptLayer::create()->showPrompt(GBKToUtf8(str.c_str()));
            PlatformLogic()->loginResult.i64Money = money;
			str.clear();
			str.append(StringUtils::toString(money));
            _delegate->walletChanged(money);

            //��ʾ�ɹ���״̬
            auto getOrder = ImageView::create(ORDER_SUCCESS);
            getOrder->setPosition(Vec2(_itemWidth * 0.865f, _itemHeight * 0.5f));
            _PayAgainButton->getParent()->addChild(getOrder, 100, ORDERBUTTON);

            //���ز�����ť
            _PayAgainButton->setVisible(false);                     
        }
        else
        {          
            supportAlert();
        }

    }
    else
    {
        supportAlert();
    }
}

void GameOrderList::supportAlert()
{
    _PayAgainButton->setEnabled(true);
	std::string str;
	str.append("����ʧ�ܣ�");
	str.append(_orderID);
	str.append("��������ϵ�ͷ���");
    GamePromptLayer::create()->showPrompt(GBKToUtf8(str.c_str()));
}

