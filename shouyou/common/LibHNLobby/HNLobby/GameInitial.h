#ifndef __GAMEINITIAL_SCENE_H__
#define __GAMEINITIAL_SCENE_H__

#include "HNUIExport.h"
#include "cocos2d.h"
#include "ui/UIVideoPlayer.h"
#include "ui/CocosGUI.h"

class GameInitial : public HNLayer
{
public:
	// ��������
    static cocos2d::Scene* createScene();

	// ��ʼ��
    virtual bool init() override;
	virtual void onEnterTransitionDidFinish() override;

	// ������Ƶ
	void showVideo();

	// ��������
	CREATE_FUNC(GameInitial);

	// �������Żص�(win32)
	void onPlayVideoOverCallback();

	/**
	* ��Ƶ����״̬��ֻ����android��iosƽ̨��Ч
	*/
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	void videoEventCallback(Ref* sender, cocos2d::experimental::ui::VideoPlayer::EventType eventType);
#endif	

protected:
	GameInitial();
	virtual ~GameInitial();
	void waitting(float dt);   
private:
	bool _isCustomer;
};

#endif // __GAMEINITIAL_SCENE_H__
