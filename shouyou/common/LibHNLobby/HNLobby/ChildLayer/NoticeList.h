#ifndef NoticeList_h__
#define NoticeList_h__

#include "HNUIExport.h"
#include "HNNetExport.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "extensions/cocos-ext.h"
#include "network/HttpClient.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

// ���浯��
class NoticeList : public HNLayer, public extension::TableViewDataSource, public extension::TableViewDelegate, public HNHttpDelegate
{
public:
	// ��ʼ��
	virtual bool init() override;

	// ��ʾ����
	virtual void onEnter() override;

	// ���캯��
	NoticeList();

	// ��������
	virtual ~NoticeList();

	// �رյ����ص�
	void onCloseClickCallback(Ref* pSender, Widget::TouchEventType type);

	// ��������
	CREATE_FUNC(NoticeList);

protected:
	// �б����С
	virtual Size tableCellSizeForIndex(extension::TableView *table, ssize_t idx) override;

	// �б�������
	virtual extension::TableViewCell* tableCellAtIndex(extension::TableView *table, ssize_t idx) override;

	// �б�������
	virtual ssize_t numberOfCellsInTableView(extension::TableView *table) override;

	// �б�����
	virtual void tableCellTouched(extension::TableView* table, extension::TableViewCell* cell) override;

	// ��ѯ�����¼
	void queryNoticeList();

	// ���淵��
	virtual void onHttpResponse(const std::string& requestName, bool isSucceed, const std::string &responseData) override;
private:
	// ���ݽڵ�
	struct DataNode
	{
		std::string title;
		std::string time;
		std::string content;
	};

	// �����б�
	std::vector<DataNode> _datas;

	// �б�
	extension::TableView* _tableView;

	ImageView* ImageView_bg;

	ImageView* ImageView_frame;
};

#endif // NoticeList_h__
