/**
 * FileName : CCUMScoialSDK.cpp
 * Author   : hehonghui
 * Company  : umeng.com
 * ����Ϊ������ữ�����Cocos2d-x�汾����������ữ���Android��iOSԭ��SDK�Ͻ������䣬֧�ִ򿪷���������ֱ�ӷ�����Ȩĳƽ̨��ɾ��ĳƽ̨��Ȩ���ж�ĳƽ̨�Ƿ���Ȩ�⼸�����Ĺ��ܡ�
 *
 * Android ƽ̨ʵ�ֵĴ���ο�UmengSocial/AndroidĿ¼�µ�ʵ��, IOSƽ̨�Ĳο�UmengSocial/IOSĿ¼�µ�ʵ�֡�
 *
 */

#include <UMeng/Cocos2dx/Common/CCUMSocialSDK.h>
#include <platform/CCCommon.h>
//#include <platform/CCPlatformConfig.h>
//#include <platform/CCPlatformMacros.h>
#include <stddef.h>
//#include <vector>

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#include "UmSocialControllerIOS.h"

#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "UMeng/Cocos2dx/Android/CCUMSocialController.h"

#endif

USING_NS_CC;
using namespace std;
// ʹ����������ռ� 
USING_NS_UM_SOCIAL;

CCUMSocialSDK* CCUMSocialSDK::_instance = NULL;

/*
 * ���캯��, ���봫������appKey
 * @param appKey ����appKey
 */
CCUMSocialSDK::CCUMSocialSDK(const char* appKey) :
		mPlatforms(new vector<int>()), _wrapperType("Cocos2d-x"), _wrapperVersion(
				"2.0") {

	setAppKey(appKey);
	initSDK();
}

/*
 * ��ʼ��sdk
 */
void CCUMSocialSDK::initSDK() {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	// ��ʼ��cocos2d-xƽ̨
	initCocos2dxSDKFromJni(_wrapperType, _wrapperVersion);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

	UmSocialControllerIOS::initCocos2dxSDK(_wrapperType, _wrapperVersion);

#endif
}

/*
 * ����CCUMSocialSDK����, ����ģʽ
 * @param appKey ����app key
 */

CCUMSocialSDK* CCUMSocialSDK::create(const char* appKey) {

	if (_instance == NULL) {
		_instance = new CCUMSocialSDK(appKey);
	} else if (appKey != NULL) {
		_instance->setAppKey(appKey);
	}
	return _instance;
}

/*
 * ��������app key
 * @param appKey ����app key
 */
void CCUMSocialSDK::setAppKey(const char* appkey) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	if (appkey == NULL) {
		CCLog("CCUMSocialSDK::setAppKey, key == null");
	}
	// ��Ȩĳƽ̨
	setUmengAppkey(appkey);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

	UmSocialControllerIOS::setAppKey(appkey);

#endif
}

/*
 * ����SDK�е�����ƽ̨
 *@param    platforms SDK�а���������ƽ̨
 */
void CCUMSocialSDK::setPlatforms(vector<int>* platforms) {
	if (platforms != NULL && platforms->size() > 0) {
		mPlatforms = platforms;
	} else {
		mPlatforms->push_back(SINA);
		mPlatforms->push_back(TENCENT_WEIBO);
		mPlatforms->push_back(RENREN);
		mPlatforms->push_back(DOUBAN);
		mPlatforms->push_back(SMS);
		mPlatforms->push_back(EMAIL);
	}

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	// ����ƽ̨
	setSocialPlatforms(mPlatforms);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	//intagram�򿪿���
	for (int i = 0; i < platforms->size(); i++) {
		int platformType = platforms->at(i);
		if (platformType == INSTAGRAM) {
			UmSocialControllerIOS::openInstagram();
        }
    }
	UmSocialControllerIOS::setSharePlatforms(mPlatforms);
#endif

}

/*
 * ����SDK�����õ�����ƽ̨
 */
vector<int>* CCUMSocialSDK::getPlatforms() {
	return mPlatforms;
}

/*
 * ��ĳƽ̨������Ȩ
 * @param platfrom Ҫ��Ȩ��ƽ̨, �ο�CCUMTypeDef.h�е�Platformö�ٶ���
 * @param  callback ��Ȩ�ص�, ����ο�CCUMTypeDef.h�еĶ���
 */
void CCUMSocialSDK::authorize(int platform, AuthEventHandler callback) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	// ��Ȩĳƽ̨
	doAuthorize(platform, callback);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

	UmSocialControllerIOS::authorize(platform, callback);

#endif
}

/*
 * ɾ��ĳƽ̨����Ȩ��Ϣ
 * @param platform Ҫɾ����Ȩ��ƽ̨
 * @param   callback ɾ����Ȩ�Ļص�, ����ο�CCUMTypeDef.h�еĶ���
 */
void CCUMSocialSDK::deleteAuthorization(int platform,
		AuthEventHandler callback) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	deletePlatformAuthorization(platform, callback);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

	UmSocialControllerIOS::deleteAuthorization(platform, callback);

#endif
}

/*
 * �ж�ĳƽ̨�Ƿ��Ѿ���Ȩ
 * @param platform Ҫ�ж���ƽ̨, �ο�CCUMTypeDef.h�е�Platformö�ٶ���
 */
bool CCUMSocialSDK::isAuthorized(int platform) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	return isPlatformAuthorized(platform);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	return UmSocialControllerIOS::isAuthorized(platform);

#endif
	return false;
}

/*
 * �򿪷������
 * @param text Ҫ�������������
 * @param imgName
 * 	 // *******************************************
 Ҫ�����ͼƬ֧��urlͼƬ��assetsĿ¼�µ�ͼƬ����ԴͼƬ�ʹ����sd��Ŀ¼�µ�ͼƬ��������ͼƬ����ǰ׺����һ����Ҫ��Ҫ������:
 //
 1��urlͼƬ������"http://"����"https://"��ͷ,���� : http://www.umeng.com/images/pic/home/feedback/banner.png��
 2��assetsĿ¼�µ�ͼƬ������"assets/"��ͷ,cocos2d-x����ԴͼƬĬ�ϻ���ӵ���Ŀ¼ֻ, ���� : assets/CloseNornal.png;
 3����ԴͼƬ�����ڹ����е�res/drawable�е�ͼƬ, ������"res/"��ͷ������ : res/myimage.png;
 4��sd��Ŀ¼�µ�ͼƬ������ڱ���Ŀ¼��ͼƬ����ʱ���ݾ���·�����ɣ����� : /sdcard/myimage.jpg;
 5��iOSƽֱ̨�Ӵ���ͼƬ��·��������·�����ɣ����磺myimage.png;
 // *******************************************
 * @param callback ����ص�,����ο�CCUMTypeDef.h�еĶ���
 */
void CCUMSocialSDK::openShare(const char* text, const char* imgName,
		ShareEventHandler callback) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	// ���÷�������
	setShareTextContent(text);
	// ����ͼƬ����
	setShareImagePath(imgName);
	// �򿪷������
	doOpenShare(callback);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	UmSocialControllerIOS::openShareWithImagePath(mPlatforms, text, imgName, callback);
#endif
}

/*
 * ֱ�ӷ���ĳ��ƽ̨�����򿪷����������ݱ༭ҳ��
 * @param platform Ҫ������Ŀ��ƽ̨�� �ο�CCUMTypeDef.h�е�Platformö�ٶ���
 * @param text Ҫ�������������
 * @param imgName
 * 	 // *******************************************
 Ҫ�����ͼƬ֧��urlͼƬ��assetsĿ¼�µ�ͼƬ����ԴͼƬ�ʹ����sd��Ŀ¼�µ�ͼƬ��������ͼƬ����ǰ׺����һ����Ҫ��Ҫ������:
 //
 1��urlͼƬ������"http://"����"https://"��ͷ,���� : http://www.umeng.com/images/pic/home/feedback/banner.png��
 2��assetsĿ¼�µ�ͼƬ������"assets/"��ͷ,cocos2d-x����ԴͼƬĬ�ϻ���ӵ���Ŀ¼ֻ, ���� : assets/CloseNornal.png;
 3����ԴͼƬ�����ڹ����е�res/drawable�е�ͼƬ, ������"res/"��ͷ������ : res/myimage.png;
 4��sd��Ŀ¼�µ�ͼƬ������ڱ���Ŀ¼��ͼƬ����ʱ���ݾ���·�����ɣ����� : /sdcard/myimage.jpg;
 5��iOSƽֱ̨�Ӵ���ͼƬ��·��������·�����ɣ����磺myimage.png;
 // *******************************************
 * @param callback ����ص�������ο�CCUMTypeDef.h�еĶ���
 */
void CCUMSocialSDK::directShare(int platform, const char* text,
		const char* imgName, ShareEventHandler callback) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	setShareTextContent(text);
	setShareImagePath(imgName);
	doDirectShare(platform, callback);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	UmSocialControllerIOS::directShare(text, imgName, platform, callback);

#endif
}

/*
 * ����QQ��app id
 *
 * @param appid
 */
void CCUMSocialSDK::setQQAppIdAndAppKey(const char* appid, const char* appKey) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	setQQAndQzoneAppIdWithAppKey(appid, appKey);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

	UmSocialControllerIOS::setQQAppIdAndAppKey(appid, appKey);

#endif
}

/*
 * ����΢�ź�΢������Ȧ��app id
 *
 * @param appid
 */
void CCUMSocialSDK::setWeiXinAppInfo(const char* appid, const char* appsecret) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	setWeiXinPlatformInfo(appid, appsecret);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

	UmSocialControllerIOS::setWechatAppId(appid,appsecret);

#endif
}

/**
 * ��������΢��appkey��appsecret��redicretURL
 *
 * @param appkey ����΢��appkey
 * @param appsecret ����΢��appsecret
 * @param redicretURL ����΢��redicretURL
 */
void CCUMSocialSDK::setSinaAppKey(const char *appkey, const char *appSecret, const char *redicretURL)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    UmSocialControllerIOS::setSinaAppKey(appkey, appSecret, redicretURL);
    
#endif
}


/*
 * �������ź���������Ȧ��app id
 *
 * @param appid
 */
void CCUMSocialSDK::setYiXinAppKey(const char* appKey) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	setYiXinPlatformAppKey(appKey);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

	UmSocialControllerIOS::setYiXinAppKey(appKey);

#endif
}

/*
 * ����������������̬��app id
 *
 * @param appid	������app id
 * @param appKey  ������app key
 * @param appid	Ӧ����, һ��Ϊ���Ӧ����
 */
void CCUMSocialSDK::setLaiwangAppInfo(const char* appid, const char* appKey,
		const char* appName) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	setLaiwangPlatformAppId(appid);
	setLaiwangPlatformAppKey(appKey);
	setLaiwangPlatformAppName(appName);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

	UmSocialControllerIOS::setLaiwangAppInfo(appid, appKey, appName);

#endif
}

/*
 * ����SDK��target url, ���û����ĳ������ʱ��ת����Ŀ��ҳ��
 * @param url �û����ĳ������ʱ��ת����Ŀ��ҳ��ͨ��Ϊapp����ҳ�����������ӵ�
 */
void CCUMSocialSDK::setTargetUrl(const char* targetUrl) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	setShareTargetUrl(targetUrl);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

	UmSocialControllerIOS::setTargetUrl(targetUrl);

#endif
}

/*
 * ���� facebook appId
 * @param appid facebook��app id
 */
void CCUMSocialSDK::setFacebookAppId(const char *appid) {

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	setFacebookPlatformAppId(appid);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

	UmSocialControllerIOS::setFacebookAppId(appid);

#endif

}

/*
 * ���iOSƽ̨�򿪷���Twitter�Ŀ���
 *
 */
void CCUMSocialSDK::openTwitterForiOS(const char *appKey, const char* appSecret) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	UmSocialControllerIOS::openTwitter(appKey, appSecret);
#endif
}

/*
 * ���iOSƽ̨�򿪷���Instagram�Ŀ���
 *
 */
void CCUMSocialSDK::openInstagramForiOS() {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	UmSocialControllerIOS::openInstagram();
#endif
}

/*
 *  �Ƿ���log
 * @param flag ���Ϊtrue����log, ����ر�.
 */
void CCUMSocialSDK::setLogEnable(bool flag) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	setAndroidLogEnable(flag);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

	UmSocialControllerIOS::openLog(flag);

#endif
}

/*
 * ��ƽ̨���÷�������
 * @param platform ƽ̨������ö��
 * @param text ��ƽ̨�������ݵ��ı�
 * @param imagePath ��ƽ̨�������ݵ�ͼƬurl���ӡ����߱���·����������Դ��������asset�е�ͼƬ.����ο�setShareImageName����
 * @param title ����ʱ�ı���, Ĭ��Ϊ���ַ���
 * @param targetUrl ������Ϣ�����ʱ��ת����Ŀ��url ( ��������ƽ̨��֧�ִ���� ) , Ĭ��Ϊ���ַ���
 */
void CCUMSocialSDK::setPlatformShareContent(int platform, const char* text,
		const char* imagePath, const char* title, const char* targetUrl) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	setPlatformDepShareContent(platform, text, imagePath, title, targetUrl);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	UmSocialControllerIOS::setPlatformShareContent(platform, text, imagePath, title, targetUrl);
#endif
}

/*
 * ������������app id,app key,app secret��Ϣ
 *
 * @param appid ��������appid
 * @param appKey ��������app key
 * @param appsecret ��������appsecret
 */
void CCUMSocialSDK::setRenrenAppInfo(const char* appid, const char* appkey,
		const char* appsecret) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	setRenrenSsoAppInfo(appid, appkey, appsecret);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	// TODO
#endif
}

/*
 * ����ƽ̨��sso��Ȩ��Ŀǰ֧�ֵ�ƽ̨������΢��������������Ѷ΢������ƽ̨. ������SSOʱ��ȷ���������˹ٷ�������Щƽ̨��app id, app key����Ϣ.
 * ����������app id, app key�����ڱ�����ͨ��setRenrenAppInfo������.
 * @param  platform Ҫ֧��SSO��Ȩ��ƽ̨
 * @param redirectURL ����Ȩƽ̨�Ļص�URL����URL��Ҫ�Ϳ���ƽ̨Ӧ�ù��������õĻص�URLһ�¡�
 */
void CCUMSocialSDK::setSsoAuthorization(int platform, const char *redirectURL) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	// TODO
	supportSsoAuthorization(platform, redirectURL);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	UmSocialControllerIOS::openSSOAuthorization(platform, redirectURL);
#endif
}
