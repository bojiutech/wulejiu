/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#ifndef __GAME_CHAT_LAYER_H__
#define __GAME_CHAT_LAYER_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "HNNetExport.h"
#include "HNUIExport.h"

USING_NS_CC;

using namespace cocostudio;
using namespace ui;

struct Chat_Record_Info
	{
		INT tag;															//�����ǩ
		std::string content;												//��������

		Chat_Record_Info()
		{
			memset(this, 0, sizeof(Chat_Record_Info));
		}
	};

class GameChatLayer : public HNLayer, public ui::EditBoxDelegate
{
public:
	typedef std::function<void(const std::string& text)> SendTextCallBack;

	SendTextCallBack	 onSendTextCallBack;

	struct CHAT_UI
	{
		ImageView*		ImageView_BG;

		Button*			Button_common;
		Button*			Button_face;
		Button*			Button_chat;
		Button*			Button_send;
		Button*			Button_voice;
		Button*			Button_message;
		Button*			Button_chat_content;
		TextField*		TextField_chat_content;
		HNEditBox*		editBox;
		ui::ScrollView* ScrollView_face;
		ui::ScrollView* ScrollView_chat;
		ui::ListView*	ListView_common;
		ui::ListView*	ListView_chatRecord;

		Widget*			chatUI;

	}_chatUI;

public:
	GameChatLayer();
	virtual ~GameChatLayer();

	virtual bool init() override;

	void closeChatLayer();

private:
	void createCommonList(INT idx);
	//������水ť�ص�
	void chatUiButtonCallBack(Ref* pSender, Widget::TouchEventType type);
	//�������찴ť�ص�
	void voiceChatUiButtonCallBack(Ref* pSender, Widget::TouchEventType type);
	//�������ص�
	void faceTouchEventCallBack(Ref* pSender, Widget::TouchEventType type);
	//�������б����ص�
	void commonListEventCallBack(Ref* pSender, ui::ListView::EventType type);
	//�����¼����ص�
	void chatRecordEventCallBack(Ref* pSender, ui::ListView::EventType type);
	//���ݵ���ص�
	void chatBubbleEventCallBack(Ref* pSender, Widget::TouchEventType type);
	//����¼���Ϸ�
	void setRecordVoiceValid(float dalta);
	//����¼�����Ϸ�
	void setRecordVoiceInValid(float dalta);
	//��ʾ�����¼
	void showChatRecords();
	//�����������ֺ���Ч
	void resumeBackgroundMusic(float delta);

public:
	CREATE_FUNC(GameChatLayer);
	//���������¼
	void addChatRecords(std::vector<Chat_Record_Info> records);
	//���������¼����
	void addChatRecord(Chat_Record_Info record);
	//���������¼����ʾ
	void updateRecordListView();

	virtual void editBoxReturn(ui::EditBox* editBox) {};

	void clearChatRecords(); //��������¼

	void show(bool willShow); //��ʾ�����

	void showBubble(Vec2 bubblePos, CHAR msg[], const std::string &nickName, bool isBubbleFlipped = false,
		bool showUserName = false); //��ʾ����

	void showVoiceBubble(Vec2 bubblePos, const std::string &nickName, int voiceID, bool showUserName = false, bool isBubbleFlipped = false); //��ʾ��������

	void showChatRecord(CHAR content[], const std::string &nickName); //��ʾ�����¼

	void showUserVoice(int userID, int voiceID); //��ʾ��������

	void onHandleTextMessage(Vec2 bubblePos, CHAR msg[], const std::string &nickName, bool isBubbleFlipped = false, 
		bool showUserName = false, bool showUpBubble = true); //�����ı�������Ϣ

	void onHandleVocieMessage(UserInfoStruct* userInfo, int voiceID, bool showBuble = false, Vec2 bubblePos = Vec2::ZERO, bool isBubbleFlipped = false, bool showUserName = true);

private:
	float _scalex;
	float _scaley;

	std::vector<Chat_Record_Info> _chatRecords; //�����¼����
	EventListenerTouchOneByOne* _touchEventListener; //�����¼�������

	bool _isClosed; //������Ƿ�ر�

	bool _isRecordedVoiceValid; //¼���Ƿ�Ϸ�
};

#endif //__GAME_CHAT_LAYER_H_