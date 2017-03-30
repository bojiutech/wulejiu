//
//  UMShareButton.h
//  UMShareButton, ��װ��CCUMSocialSDK�ķ����� ( ͨ������������ ). û��ʹ��Cocos2d-x���ڴ������ԣ����������й����Button���ڴ��ͷ�.
//
//  Created by mrsimple on 3/18/14.
//
//

#ifndef __crossdemo__UMShareButton__
#define __crossdemo__UMShareButton__

#include <iostream>
#include "cocos2d.h"
#include "UMeng/Cocos2dx/Common/CCUMSocialSDK.h"
#include <vector>

USING_NS_CC;
using namespace std;

namespace umeng {
namespace social {

/**
 * ���༯����Cocos2d-x��ͼƬ��ť�࣬����û��ʹ��Cocos2d-x���ڴ���������������н����ڴ��ͷš������װ��CCUMSocialSDK��openShare���ܣ�
 * 	���û������ťʱ�����˷������, ����ʵ����ο�Դ�롣
 *
 */
#ifdef CC_CALLBACK_1
class UMShareButton : public cocos2d::MenuItemImage
{
#else
class UMShareButton: public cocos2d::CCMenuItemImage {
#endif
public:
	/**
	 * ��������,�ͷ��ڴ�
	 */
	virtual ~UMShareButton();
	/**
	 * ����һ��UMShareButton����
	 * @param  normalImage  ��ť�����������ʾ��ͼƬ
	 * @param  selectedImage ��ťѡ���������ʾ��ͼƬ
	 * @param  umAppKey ����AppKey
	 * @param callback ����ص�����
	 */
	static UMShareButton* create(const char *normalImage,
			const char *selectedImage, const char* umAppKey,
			ShareEventHandler callback);

	/**
	 * ����Ҫ������ı�����
	 * @param text Ҫ������ı�����
	 */
	void setShareContent(const char* text);

	/**
	 * ����Ҫ�����ͼƬ·������url
	 * @param imgName ����ͼƬ��urlͼƬ, urlͼƬ�������http://����https://��ͷ
	 */
	void setShareImage(const char* imgName);

	/**
	 * ���÷���ص��ص�
	 * @param callback ����ص�
	 */
	void setShareCallback(ShareEventHandler callback);
	/**
	 * ��������SDK֧�ֵ�ƽ̨�����������Ҳ����ʾ��Щƽ�壬�����Щƽ̨û�������Ӧ�������򲻻���ʾ��ƽ̨�������ο�CCUMTypeDef.h�е�Platformö��
	 * @param platforms ����SDK֧�ֵ�ƽ̨
	 */
	void setPlatforms(vector<int>* platforms);
	/**
	 * ��ȡCCUMSocialSDK����
	 * @return ����CCUMSocialSDK��������
	 */
	CCUMSocialSDK* getSocialSDK();

private:
	UMShareButton();
	// ���캯��
	UMShareButton(const char *normalImage, const char *selectedImage,
			const char* umAppKey);
	// �򿪷������
	void openShareBoard();
#ifdef CC_CALLBACK_1
	// ����ť�ص�, �����˷������
	void shareCallback(cocos2d::Ref* pSender);
#else
	// ����ť�ص�, �����˷������
	void shareCallback(CCNode* pSender);
#endif

private:
	// ���˷������SDK
	CCUMSocialSDK* mSocialSDK;
	// Ҫ���֧�ֵ�ƽ̨
//	vector<int>* mPlatforms;
	// Ҫ������ı�����
	string mShareText;
	// Ҫ�����ͼƬ����·������url
	string mImageName;
	// ����ص�
	ShareEventHandler mCallback;
};
}
}

#endif /* defined(__crossdemo__UMShareButton__) */
