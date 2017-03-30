#ifndef __Cherry97_GameShare_H__
#define __Cherry97_GameShare_H__
#include "HNNetExport.h"
#include "HNUIExport.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Cherry97GameTableUICallback.h"

//#include "network/HttpClient.h"

namespace Cherry97{
	class GameTableUICallback;
	class GameShare : public HN::HNLayer, public HN::HNHttpDelegate
	{
	public:
		GameShare();
		virtual ~GameShare();
		static GameShare* create(GameTableUICallback* uicallback);
		virtual bool init(GameTableUICallback* uicallback);
		void btnCallBack(cocos2d::Ref* pSender, ui::Widget::TouchEventType touchtype);
		void setShareAward(int ishareAward);

		virtual void onHttpResponse(const std::string& requestName, bool isSucceed, const std::string &responseData) override;

	private:
		void dealShareResp(const std::string& data);

		void updateBankData();

		bool bankerEventSelector(HNSocketMessage* socketMessage);
	private:
		GameTableUICallback* _uicallback;
		Size winsize;
		Node* _loader;
		Layout* _layout;
		TextAtlas* m_textAward;
		Button* m_shareButton;
		Button* m_closeButton;
	};

}

#endif

