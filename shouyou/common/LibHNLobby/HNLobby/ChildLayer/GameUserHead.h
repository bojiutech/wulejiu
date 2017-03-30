#ifndef __Game_UserHead_h__
#define __Game_UserHead_h__

#include "HNUIExport.h"
#include "cocos2d.h"
#include "HNNetExport.h"

namespace HN
{
	class GameUserHead : public HNSprite, public HNUserHeadHttpDelegate
	{
	private:
		Sprite* _userHead;

	public:
		static GameUserHead* create(const std::string& frame);

		static GameUserHead* create();

		void setUserHead(const std::string& head);

		void updateOwnUserHead(const std::string& headUrl, int userID);

		void updateGeneralUserHead(const std::string& headUrl, Sprite* head, int userID);

		// http«Î«ÛœÏ”¶
		virtual void onHttpResponse(const std::string& requestName, bool isSucceed, std::vector<char> &responseData) override;

	protected:
		bool initWithImage(const std::string& frame);

		bool onTouchBegan(Touch* touch, Event* event);

		void onTouchEnd(Touch* touch, Event* event);

	public:
		std::function<void(GameUserHead* sender, Vec2 touchVec)> onHeadClickEvent;

	private:
		GameUserHead();
		virtual ~GameUserHead();


		Sprite* _tempHeadSprite;
		int _userID;
	};
}


#endif // __Game_UserHead_h__