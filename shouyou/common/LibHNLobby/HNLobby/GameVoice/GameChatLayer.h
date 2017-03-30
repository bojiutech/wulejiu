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
		INT tag;															//聊天标签
		std::string content;												//聊天内容

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
	//聊天界面按钮回调
	void chatUiButtonCallBack(Ref* pSender, Widget::TouchEventType type);
	//语音聊天按钮回调
	void voiceChatUiButtonCallBack(Ref* pSender, Widget::TouchEventType type);
	//点击表情回调
	void faceTouchEventCallBack(Ref* pSender, Widget::TouchEventType type);
	//常用语列表点击回调
	void commonListEventCallBack(Ref* pSender, ui::ListView::EventType type);
	//聊天记录点击回调
	void chatRecordEventCallBack(Ref* pSender, ui::ListView::EventType type);
	//气泡点击回调
	void chatBubbleEventCallBack(Ref* pSender, Widget::TouchEventType type);
	//设置录音合法
	void setRecordVoiceValid(float dalta);
	//设置录音不合法
	void setRecordVoiceInValid(float dalta);
	//显示聊天记录
	void showChatRecords();
	//启动背景音乐和音效
	void resumeBackgroundMusic(float delta);

public:
	CREATE_FUNC(GameChatLayer);
	//加载聊天记录
	void addChatRecords(std::vector<Chat_Record_Info> records);
	//更新聊天记录容器
	void addChatRecord(Chat_Record_Info record);
	//增加聊天记录并显示
	void updateRecordListView();

	virtual void editBoxReturn(ui::EditBox* editBox) {};

	void clearChatRecords(); //清空聊天记录

	void show(bool willShow); //显示聊天框

	void showBubble(Vec2 bubblePos, CHAR msg[], const std::string &nickName, bool isBubbleFlipped = false,
		bool showUserName = false); //显示气泡

	void showVoiceBubble(Vec2 bubblePos, const std::string &nickName, int voiceID, bool showUserName = false, bool isBubbleFlipped = false); //显示语音气泡

	void showChatRecord(CHAR content[], const std::string &nickName); //显示聊天记录

	void showUserVoice(int userID, int voiceID); //显示语音聊天

	void onHandleTextMessage(Vec2 bubblePos, CHAR msg[], const std::string &nickName, bool isBubbleFlipped = false, 
		bool showUserName = false, bool showUpBubble = true); //处理文本聊天消息

	void onHandleVocieMessage(UserInfoStruct* userInfo, int voiceID, bool showBuble = false, Vec2 bubblePos = Vec2::ZERO, bool isBubbleFlipped = false, bool showUserName = true);

private:
	float _scalex;
	float _scaley;

	std::vector<Chat_Record_Info> _chatRecords; //聊天记录容器
	EventListenerTouchOneByOne* _touchEventListener; //触摸事件监听器

	bool _isClosed; //聊天框是否关闭

	bool _isRecordedVoiceValid; //录音是否合法
};

#endif //__GAME_CHAT_LAYER_H_