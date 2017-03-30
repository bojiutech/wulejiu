#ifndef __GAMELAND_LAYER_H__
#define __GAMELAND_LAYER_H__

#include "HNNetExport.h"
#include "HNUIExport.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio;
using namespace ui;

class LandLayer : public HNLayer, public ui::EditBoxDelegate
{
public:
	typedef std::function<void (const std::string& name, const std::string& psd)> LoginCallBack;
	typedef std::function<void ()> CloseCallBack;
	typedef std::function<void ()> RegistCallBack;

private:

	struct LANDUI
	{
		HNEditBox*	editBoxUserName;
		HNEditBox*	editBoxPassWord;
		CheckBox*	checkBoxSave;
		Node*		landUI;
		ImageView*  backGround;

	}_landUI;

	bool _isGetPassWord;
	bool  _isOpenLayer;
public:

	LoginCallBack	onLoginCallBack;
	CloseCallBack	onCloseCallBack;
	RegistCallBack  onRegistCallBack;

public:
	CREATE_FUNC(LandLayer);

public:
	LandLayer();
	virtual ~LandLayer();

	virtual bool init() override;

public:
	void closeLand();

private:
	LayerColor* colorLayer;
	// ��½�ص�����
	void landEventCallback(Ref* pSender, Widget::TouchEventType type);
	// �رջص�����
	void closeEventCallback(Ref* pSender, Widget::TouchEventType type);
	// ��ѡ��ص�����
	void checkBoxCallback(Ref* pSender,CheckBox::EventType type);
	// ע�ᰴť�ص�����
	void registEventCallback(Ref* pSender, Widget::TouchEventType type);

	virtual void editBoxReturn(ui::EditBox* editBox) {};

	void editBoxTextChanged(ui::EditBox* editBox, const std::string& text);

	void editBoxEditingDidBegin(ui::EditBox* editBox);
};

#endif // __GAMELAND_LAYER_H__