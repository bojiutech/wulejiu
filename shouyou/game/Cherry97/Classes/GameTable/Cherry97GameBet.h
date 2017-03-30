#ifndef __Cherry97_Bet_H__
#define __Cherry97_Bet_H__

#include "HNNetExport.h"
#include "HNUIExport.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

namespace Cherry97
{
	class GameBet : public HN::HNLayer
	{
	public:
		static GameBet* create();
		virtual bool init();
		GameBet();
		virtual ~GameBet();
		void btnCallBack(cocos2d::Ref* pSender, ui::Widget::TouchEventType touchtype);
	private:
		Size winsize;
		Node* _loader;
		Layout* _layout;
		Button* _btnClose;
	};
}



#endif