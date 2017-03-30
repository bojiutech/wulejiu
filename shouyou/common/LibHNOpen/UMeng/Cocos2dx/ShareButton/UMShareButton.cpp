//
//  UMShareButton.cpp
//  Umeng Social SDK ShareButton
//
//  Created by mrsimple on 3/18/14.
//
//

#include "UMShareButton.h"
#include "cocos2d.h"
#include <iostream>

USING_NS_CC;
using namespace std;
// ʹ����������ռ� 
USING_NS_UM_SOCIAL;

/*
 * ���캯��
 */
UMShareButton::UMShareButton() {
	new (this) UMShareButton("", "", "");
}

/*
 * ���캯��, û��ʹ��cocos2d-x���ڴ����, ��Ҫ���������й����ڴ�
 * @param  normalImage  ��ť�����������ʾ��ͼƬ
 * @param  selectedImage ��ťѡ���������ʾ��ͼƬ
 * @param  umAppKey ����AppKey
 */
UMShareButton::UMShareButton(const char *normalImage, const char *selectedImage,
		const char* umAppKey) :
		mShareText(""), mImageName(""), mSocialSDK(NULL), mCallback(
		NULL) {
	log("UMShareButtonͼƬ: normalImage = %s, selectedImage = %s.", normalImage,
			selectedImage);
#ifdef CC_CALLBACK_1
	// ��ʼ��ͼƬ��ť
	 initWithNormalImage(normalImage, selectedImage, "", CC_CALLBACK_1(UMShareButton::shareCallback, this)) ;
//	initWithNormalImage(normalImage, selectedImage, "", [&](Ref* pSender) ->
//			{
//				CCLog("Cocos2d-x V3.X ShareButton.    in lambda.");
//				this->openShareBoard();
//			}, this));
#else
	// ��ʼ��ͼƬ��ť
	initWithNormalImage(normalImage, selectedImage, "", this,
			menu_selector(UMShareButton::shareCallback));
#endif
	// ����CCUMSocialSDK����
	mSocialSDK = CCUMSocialSDK::create(umAppKey);
}

/*
 * ����һ��UMShareButton����
 * @param  normalImage  ��ť�����������ʾ��ͼƬ
 * @param  selectedImage ��ťѡ���������ʾ��ͼƬ
 * @param  umAppKey ����AppKey
 * @param callback ����ص�����
 */
UMShareButton* UMShareButton::create(const char *normalImage,
		const char *selectedImage, const char* umAppKey,
		ShareEventHandler callback) {
	UMShareButton* shareButton = new UMShareButton(normalImage, selectedImage,
			umAppKey);
	shareButton->setShareCallback(callback);
	return shareButton;
}

/*
 * ��������,�ͷ��ڴ�
 */
UMShareButton::~UMShareButton() {
	delete mSocialSDK;
}

/*
 * ��ȡCCUMSocialSDK����
 */
CCUMSocialSDK* UMShareButton::getSocialSDK() {
	return mSocialSDK;
}

/*
 * �����ı�����
 * @param text
 */
void UMShareButton::setShareContent(const char* text) {
	if (text != NULL) {
		this->mShareText = text;
	}

}

/*
 * ���ñ���ͼƬ��urlͼƬ, urlͼƬ������http://����https://��ͷ
 * @param imgName ͼƬ�ı���·������url��ַ.
 */
void UMShareButton::setShareImage(const char* imgName) {
	if (imgName != NULL) {
		this->mImageName = imgName;
	}
}

/*
 * ���÷���ص��ص�
 * @param callback ����ص�
 */
void UMShareButton::setShareCallback(ShareEventHandler callback) {
	mCallback = callback;
}

/*
 * ��������SDK֧�ֵ�ƽ̨�� ƽ̨�������ο�CCUMTypeDef.h�е�Platformö��
 * @param platforms ����SDK֧�ֵ�ƽ̨
 */
void UMShareButton::setPlatforms(vector<int>* platforms) {
	if (mSocialSDK != NULL) {
		mSocialSDK->setPlatforms(platforms);
	}
}

/*
 * �򿪷������
 */
void UMShareButton::openShareBoard() {
	if (mSocialSDK != NULL) {
		mSocialSDK->openShare(mShareText.c_str(), mImageName.c_str(),
				mCallback);
	}
}

#ifdef CC_CALLBACK_1
/*
 * ����ð�ťʱ�Ļص�, ����ʵ��Ϊ���ô򿪷������
 * @param pSender 
 */
void UMShareButton::shareCallback(Ref* pSender)
{
	log("Cocos2d-x V3.X ShareButton.");
	this->openShareBoard();
}
#else 
/*
 * ����ð�ťʱ�Ļص�, ����ʵ��Ϊ���ô򿪷������
 * @param pSender 
 */
void UMShareButton::shareCallback(CCNode* pSender) {
	log("Cocos2d-x V2.X ShareButton.");
	this->openShareBoard();
}
#endif
