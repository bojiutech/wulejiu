#ifndef ServiceLayer_h__
#define ServiceLayer_h__

#include "HNUIExport.h"
#include "HNNetExport.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

class ServiceLayer : public HNLayer, public HNHttpDelegate
{
public:
	// ��ʾ
	void showService(Node* parent, Vec2 vec, int zorder, int tag);

	// ����
	void closeService();

	// ��ʼ��
	virtual bool init() override; 

	// ����λ��
	void setBGPositon(Vec2 vec);

	// ����
	CREATE_FUNC(ServiceLayer);

protected:
	// ��ť�ص�
	void onServiceClick(Ref* pRef);

	// �ͷ���Ϣ�ص�
	virtual void onHttpResponse(const std::string& requestName, bool isSucceed, const std::string &responseData) override;

	// ���캯��
	ServiceLayer();

	// ��������
	virtual ~ServiceLayer();

	// ��ȡ�ͷ���Ϣ
	void requestServiceInfo();

private:
	// �����ļ�
	Node*           _csNode;
	
	// �ͷ��绰
	std::string		_phone;

	// �ͷ���Ϣ
	std::string		_message;

	// �ͷ�����
	std::string		_email;

	// �����С
	Size            _winSize;

	// ��ť
	Button*         _buttonPhone;
	Button*         _buttonMessage;
	Button*         _buttonEmail;
};

#endif // ServiceLayer_h__
