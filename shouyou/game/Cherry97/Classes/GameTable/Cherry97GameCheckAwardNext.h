#ifndef __Cherry97_CheckAwardNext_H__
#define __Cherry97_CheckAwardNext_H__

#include "HNNetExport.h"
#include "HNUIExport.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Cherry97GameTableUICallback.h"

namespace Cherry97
{
	class GameTableUICallback;
	class GameCheckAwardNext : public HN::HNLayer
	{
	public:
		static GameCheckAwardNext* create(GameTableUICallback* uicallback);
		virtual bool init(GameTableUICallback* uicallback);
		GameCheckAwardNext();
		virtual ~GameCheckAwardNext();
		void btnCallBack(cocos2d::Ref* pSender, ui::Widget::TouchEventType touchtype);
		int _saveAward[12];//保存现有的奖励数
	private:
		GameTableUICallback* _uicallback;
		Size winsize;
		LayerColor* _colorLayer;
		Node* _loader;
		Layout* _layout;
		Button* _btnClose;
		Button* _btnLastPage;
		Button* _btnNextPage;
		Text* _award[12];

	public:
		void setAwardInfo(UINT award[12]);
	};
}
#endif