#ifndef __Cherry97_CheckAward_H__
#define __Cherry97_CheckAward_H__

#include "HNNetExport.h"
#include "HNUIExport.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Cherry97GameTableUICallback.h"

namespace Cherry97
{
	class GameTableUICallback;
	class GameCheckAward : public HN::HNLayer
	{
	public:
		static GameCheckAward* create(GameTableUICallback* uicallback);
		virtual bool init(GameTableUICallback* uicallback);
		GameCheckAward();
		virtual ~GameCheckAward();
		void btnCallBack(cocos2d::Ref* pSender, ui::Widget::TouchEventType touchtype);
		int _saveAward[18];//保存现有的奖励数
	private:
		GameTableUICallback* _uicallback;
		Size winsize;
		LayerColor* _colorLayer;
		Node* _loader;
		Layout* _layout;
		Button* _btnClose;
		Button* _btnLastPage;
		Button* _btnNextPage;
		Text* _award[18];

	public:
		void setAwardInfo(int award[18]);
	};
}
#endif