#ifndef __GameMenu_H__
#define __GameMenu_H__

#include "HNNetExport.h"
#include "HNLogicExport.h"
#include "HNUIExport.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <string>

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

class GameMenu : public HNLayer, public HN::IHNPlatformLogin, public HN::IHNPlatformRegist
{

enum ThirdLoginType
{
	WeChat	= 2,	//΢��
	QQLogin = 3,	//QQ
};

public:
	// �����½����
	static void createMenu();

	// ���캯��
	GameMenu();

	// ��������
	virtual ~GameMenu();

	// ���¼��
	void checkUpdate();

	// ���¼��
	void updateCheckFinishCallback(bool updated, cocos2d::Node* pSender, const std::string& message, const std::string& installPath);

	// ��ʼ��
	virtual bool init() override;

	// ��ʾ���
	virtual void onEnterTransitionDidFinish() override;

	// �ο͵�½��ť�ص�����
	void guestLoginEventCallback(Ref* pSender, Widget::TouchEventType type);

	// ע���½��ť�ص�����
	void accountLoginEventCallback(Ref* pSender, Widget::TouchEventType type);

	// �˺�ע�ᰴť�ص�����
	void RegisterEventCallback(Ref* pSender, Widget::TouchEventType type);

	// ΢�ŵ�½��ť�ص�����
	void onWeChatLoginClicked(Ref* pSender, Widget::TouchEventType type);

	// QQ��½��ť�ص�
	void onQQLoginClicked(Ref* pSender, Widget::TouchEventType type);

	// ������Ϸ
	void enterGame(const std::string& userName, const std::string& userPswd);

	// ����
	CREATE_FUNC(GameMenu);

	// ����Icon
	void loadIcon();

private:
	//ע�ᰴť�ص�
	void registerActionCallBack();

	//�����û��˺�
	void saveUserInfo(const std::string& userName, const std::string& userPswd);

public:
	//�ֻ����ؼ������ص�����
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent) override;

public:
	//ע��ص�
	virtual void onPlatformRegistCallback(bool success, bool fastRegist, const std::string& message,
		const std::string&name, const std::string& pwd, int loginTimes)  override;

	//��½�ص�
	virtual void onPlatformLoginCallback(bool success, const std::string& message,
		const std::string& name, const std::string& pwd)  override;

public:
	HNPlatformLogin*	_gameLogin;
	HNPlatformRegist*	_gameRegist;
	Sprite*				_logo					= nullptr;
	Sprite*				_backGround				= nullptr;
	Button*				_buttonGuestLogin		= nullptr;
	Button*				_buttonAccountLogin		= nullptr;
	Button*				_buttonRegister			= nullptr;
	Button*				_buttonWeiXinLogin		= nullptr;
	bool				_isAccountLogin			= false;
	std::string			_userName				= "";
	std::string			_userPsd				= "";

	// �Ƿ����ο�
	static bool			isVisitor;
	bool				_bAuthorize = false;
};

#endif // __GameMenu_H__