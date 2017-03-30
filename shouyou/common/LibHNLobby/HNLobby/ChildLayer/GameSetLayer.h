#ifndef __GAMESET_LAYER_H__
#define __GAMESET_LAYER_H__

#include "HNUIExport.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio;
using namespace ui;

class GameSetLayer : public HNLayer
{
	enum UI_TYPE  
	{
		M_SLIDER = 28,                           //�����϶���
		E_SLIDER = 32,                           //��Ч�϶���
		M_CHECKBOX = 40,                         //���־�����ѡ��
		E_CHECKBOX = 41,                         //��Ч������ѡ��
	};
	Slider* _musicSlider;
	Slider* _effectSlider;
	CheckBox* _musicCheckBox;
	CheckBox* _effectCheckBox;
	Layout* _layout;
public:
	GameSetLayer();
	virtual ~GameSetLayer();

public:
    virtual bool init() override;

	void showSet(Node* parent, int zorder, int tag = -1);

	void closeSet();

private:
	LayerColor* colorLayer;
	Node* settingLoader;
	Slider* effectSlider;
	Slider* musicSlider;
	//�رջص�
	void closeSetCallBack(Ref* pSender, Widget::TouchEventType type);
	//�϶����ص�����
	void sliderCallback(Ref* pSender, Slider::EventType type, UI_TYPE num);
	//������Ч
	void setCallBack(Ref* pSender,Widget::TouchEventType type,int num);

public:
    CREATE_FUNC(GameSetLayer);
};

#endif // __GAMESET_LAYER_H__
