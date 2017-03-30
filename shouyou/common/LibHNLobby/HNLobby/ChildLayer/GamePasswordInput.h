#ifndef __GamePasswordInput_H__
#define __GamePasswordInput_H__

#include "HNUIExport.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio;
using namespace ui;

class GamePasswordInput : public HNLayer, public ui::EditBoxDelegate
{
public:
	// ���캯��
	GamePasswordInput();

	// ��������
	virtual ~GamePasswordInput();

	// ��������
	static GamePasswordInput* create();

	// ��ʼ��
	virtual bool init() override;

	std::function<void(const std::string& password)> onEnterCallback;
protected:	
	// �رյ����ص�
	void onCloseClickCallback(Ref* pSender, Widget::TouchEventType type);
	
	// ���뷿��ص�
	void onEnterClickCallback(Ref* pSender, Widget::TouchEventType type);

	// ��������
	virtual void editBoxReturn(ui::EditBox* editBox) override{};

private:
	// ���������
	HNEditBox* _editbox_pass;
};

#endif // 
