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

		//���½�������
		virtual void showAndUpdateBoard();

		//��ʾ�����
		void showBoard();

		void close();

		//ȷ����ť�ص�
		virtual void confirmBtnCallBack(Ref* pSender, Widget::TouchEventType type);

		//����ť�ص�
		virtual void shareBtnCallBack(Ref* pSender, Widget::TouchEventType type);

		//���ذ�ť�ص�
		virtual void backBtnCallBack(Ref* pSender, Widget::TouchEventType type);

	protected:
		//�����û��Զ���ͷ��
		virtual void updateUserHead(int userId, int logoID, const std::string& headUrl, Sprite* headSprite);
	};
}


#endif // HN_CalculateBoard_H__
