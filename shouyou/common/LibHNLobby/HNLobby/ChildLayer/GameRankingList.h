#ifndef __GAMERANKING_LAYER_H__
#define __GAMERANKING_LAYER_H__

#include "HNNetExport.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "extensions/cocos-ext.h"
#include <vector>

USING_NS_CC;
USING_NS_CC_EXT;

using namespace HN;
using namespace ui;
using namespace std;
using namespace extension;

class GameRankingList : public HNLayer, public TableViewDataSource, public TableViewDelegate
{

public:
	GameRankingList();
	virtual ~GameRankingList();

public:
	typedef std::function<void ()> CloseCallBack;
	CloseCallBack	onCloseCallBack;

public:
	virtual bool init() override;
	void closeRanking();
	void closeEventCallBack(Ref* pSender, Widget::TouchEventType type);

	void openRank(Node* parent, Vec2 vec, int zorder, int tag);
	CREATE_FUNC(GameRankingList);

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
	vector<MSG_GP_MoneyPaiHangBang_Item> _iList;
	int MyRankNum;
	ui::Scale9Sprite* rankingFrame;
	Text* rankingText;
private:
	//��ȡ��������
	void getRankListData();
	//��������а�ص�
	bool openRankListEventSelector(HNSocketMessage* socketMessage);
	//��ʾ�ҵ�����
	void showMyRank();
};


#endif // __GAMERANKING_LAYER_H__