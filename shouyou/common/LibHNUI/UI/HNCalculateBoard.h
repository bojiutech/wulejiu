#ifndef HN_CalculateBoard_H__
#define HN_CalculateBoard_H__

#include "Base/HNLayer.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

namespace HN
{
	class HNCalculateBoard : public HNLayer
	{		
	public:
		Layout*			_calculateBoardLayout;
	
		Button*         _btn_confirm;
		Button*         _btn_share;
		Button*         _btn_back;
		Text*			_txt_applyUser;
		Node*			_calculateBoardNode;		

	public:
		CREATE_FUNC(HNCalculateBoard);

		HNCalculateBoard();
		virtual ~HNCalculateBoard();

	public:
		virtual bool init() override;

		//更新结算数据
		virtual void showAndUpdateBoard();

		//显示结算榜
		void showBoard();

		void close();

		//确定按钮回调
		virtual void confirmBtnCallBack(Ref* pSender, Widget::TouchEventType type);

		//分享按钮回调
		virtual void shareBtnCallBack(Ref* pSender, Widget::TouchEventType type);

		//返回按钮回调
		virtual void backBtnCallBack(Ref* pSender, Widget::TouchEventType type);

	protected:
		//更新用户自定义头像
		virtual void updateUserHead(int userId, int logoID, const std::string& headUrl, Sprite* headSprite);
	};
}


#endif // HN_CalculateBoard_H__
