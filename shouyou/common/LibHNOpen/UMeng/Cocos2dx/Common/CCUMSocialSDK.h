/*
 * FileName : CCUMScoialSDK.h
 * Author   : hehonghui
 * Company  : umeng.com
 *
 */

#ifndef __CCUMSOCIALSDK__
#define __CCUMSOCIALSDK__

#include "cocos2d.h"
#include "CCUMTypeDef.h"
#include <vector>

USING_NS_CC;
using namespace std;

namespace umeng {
/**
 * Umeng Social�����ռ�, ʹ�ø�SDK�������USING_NS_UM_SOCIAL
 */
namespace social {
/**
 * ����Ϊ������ữ�����Cocos2d-x�汾����������ữ���Android��iOSԭ��SDK�Ͻ������䣬֧�ִ򿪷���������ֱ�ӷ�����Ȩĳƽ̨��ɾ��ĳƽ̨��Ȩ���ж�ĳƽ̨�Ƿ���Ȩ�⼸�����Ĺ��ܣ�
 * 	����н�һ����������ο���SDK����ʵ�֡�
 *
 * Android ƽ̨ʵ�ֵĴ���ο�UmengSocial/AndroidĿ¼�µ�ʵ��, IOSƽ̨�Ĳο�UmengSocial/IOSĿ¼�µ�ʵ�֡�
 *
 */
class CCUMSocialSDK {
private:
	CCUMSocialSDK(const char* umAppKey);
	void initSDK();
public:

	/**
	 * ����CCUMSocialSDK����
	 * @param appKey ����app key
	 */
	static CCUMSocialSDK* create(const char* appKey);

	/*
	 * ��������app key
	 * @param appKey ����app key
	 */
	void setAppKey(const char* appkey);

	/**
	 * ��ĳƽ̨������Ȩ
	 * @param platfrom Ҫ��Ȩ��ƽ̨, �ο�CCUMTypeDef.h�е�Platformö�ٶ���
	 * @param  callback ��Ȩ�ص�, ����ο�CCUMTypeDef.h�еĶ���
	 */
	void authorize(int platform, AuthEventHandler callback);

	/**
	 * ɾ��ĳƽ̨����Ȩ��Ϣ
	 * @param platform Ҫɾ����Ȩ��ƽ̨
	 * @param   callback ɾ����Ȩ�Ļص�, ����ο�CCUMTypeDef.h�еĶ���
	 */
	void deleteAuthorization(int platform, AuthEventHandler callback);

	/**
	 * �ж�ĳƽ̨�Ƿ��Ѿ���Ȩ
	 *@param    platform �ж�ĳƽ̨�Ƿ��Ѿ���Ȩ
	 */
	bool isAuthorized(int platform);

	/**
	 * ����SDK�е�����ƽ̨
	 *@param    platforms SDK�а���������ƽ̨
	 */
	void setPlatforms(vector<int>* platforms);

	/**
	 * ����SDK�����õ�����ƽ̨
	 * @return SDK�����õ�����ƽ̨
	 */
	vector<int>* getPlatforms();

	/**
	 * �����˷������, �ڵ��ø÷���ǰ���ȵ���setPlatforms���������÷���SDK֧�ֵ�����ƽ̨.
	 * @param text Ҫ�������������
	 * @param imgName
	 // *******************************************
	 Ҫ�����ͼƬ֧��urlͼƬ��assetsĿ¼�µ�ͼƬ����ԴͼƬ�ʹ����sd��Ŀ¼�µ�ͼƬ��������ͼƬ����ǰ׺����һ����Ҫ��Ҫ������:
	 //
	 1��urlͼƬ������"http://"����"https://"��ͷ,���� : http://www.umeng.com/images/pic/home/feedback/banner.png��
	 2��assetsĿ¼�µ�ͼƬ������"assets/"��ͷ,cocos2d-x����ԴͼƬĬ�ϻ���ӵ���Ŀ¼ֻ, ���� : assets/CloseNornal.png;
	 3����ԴͼƬ�����ڹ����е�res/drawable�е�ͼƬ, ������"res/"��ͷ������ : res/myimage.png;
	 4��sd��Ŀ¼�µ�ͼƬ������ڱ���Ŀ¼��ͼƬ����ʱ���ݾ���·�����ɣ����� : /sdcard/myimage.jpg;
     5��iOSƽ̨��ֱ�Ӵ���ͼƬ��·��������·�������磺myimage.png��Ҳ����˵��1�д���url����;
	 // *******************************************
	 * @param callback ����ص�,����ο�CCUMTypeDef.h�еĶ���
	 */
	void openShare(const char* text, const char* imgName,
			ShareEventHandler callback);

	/**
	 * ֱ�ӷ���ĳ��ƽ̨�����򿪷����������ݱ༭ҳ��
	 * @param platform Ҫ������Ŀ��ƽ̨���ο�CCUMTypeDef.h�е�Platformö�ٶ���
	 * @param text Ҫ�������������
	 * @param imgName
	 // *******************************************
	 Ҫ�����ͼƬ֧��urlͼƬ��assetsĿ¼�µ�ͼƬ����ԴͼƬ�ʹ����sd��Ŀ¼�µ�ͼƬ��������ͼƬ����ǰ׺����һ����Ҫ��Ҫ������:
	 //
	 1��urlͼƬ������"http://"����"https://"��ͷ,���� : http://www.umeng.com/images/pic/home/feedback/banner.png��
	 2��assetsĿ¼�µ�ͼƬ������"assets/"��ͷ,cocos2d-x����ԴͼƬĬ�ϻ���ӵ���Ŀ¼ֻ, ���� : assets/CloseNornal.png;
	 3����ԴͼƬ�����ڹ����е�res/drawable�е�ͼƬ, ������"res/"��ͷ������ : res/myimage.png;
     4��sd��Ŀ¼�µ�ͼƬ������ڱ���Ŀ¼��ͼƬ����ʱ���ݾ���·�����ɣ����� : /sdcard/myimage.jpg;
     5��iOSƽ̨��ֱ�Ӵ���ͼƬ��·��������·�������磺myimage.png��Ҳ����˵��1�д���url����;
	 // *******************************************
	 * @param callback ����ص�������ο�CCUMTypeDef.h�еĶ���
	 */
	void directShare(int platform, const char* text, const char* imgName,
			ShareEventHandler callback);

	/**
	 * ����SDK��target url, ���û����ĳ������ʱ��ת����Ŀ��ҳ��
	 * @param url �û����ĳ������ʱ��ת����Ŀ��ҳ��ͨ��Ϊapp����ҳ�����������ӵ�
	 */
	void setTargetUrl(const char* targetUrl);

	/**
	 * ����QQ��QQ�ռ��app id, ����ƽ̨������app id, appKey
	 *
	 * @param appid	QQ�ռ����QQ��app id
	 * @param appKey QQ�ռ����QQ��app key
	 */
	void setQQAppIdAndAppKey(const char* appid, const char* appkey);

	/**
	 * ����΢�ź�΢������Ȧ��app id
	 *
	 * @param appid ΢�Ż���΢������Ȧ��appid
	 * @param appsecret ΢�Ż���΢������Ȧ��appsecret
	 */
	void setWeiXinAppInfo(const char* appid, const char* appsecret);
    
    /**
     * ��������΢��appkey��appsecret��redicretURL
     *
     * @param appkey ����΢��appkey
     * @param appsecret ����΢��appsecret
     * @param redicretURL ����΢��redicretURL
     */
    void setSinaAppKey(const char *appkey, const char *appSecret, const char *redicretURL);
    
	/**
	 * ������������app id,app key,app secret��Ϣ
	 *
	 * @param appid ��������appid
	 * @param appKey ��������app key
	 * @param appsecret ��������appsecret
	 */
	void setRenrenAppInfo(const char* appid, const char* appkey,
			const char* appsecret);

	/**
	 * �������ź���������Ȧ��app id
	 *
	 * @param appid ���Ż�����������Ȧ��app id
	 */
	void setYiXinAppKey(const char* appid);

	/**
	 * ����������������̬��app id
	 *
	 * @param appid	������app id
	 * @param appKey  ������app key
	 * @param appid	Ӧ����, һ��Ϊ���Ӧ����
	 */
	void setLaiwangAppInfo(const char* appid, const char* appkey,
			const char* appName);

	/**
	 * ����Facebook��appid
	 *
	 * @param appid   FacebookӦ�õ�app id
	 */
	void setFacebookAppId(const char *appid);

    /**  ����twitterӦ��key��secret
	 *   ��Twitter���أ�ֻ��iOSƽ̨��Ч
	 *  @param appKey   twitterӦ�õ�app key
     *  @param appSecret   twitterӦ�õ�app secret
	 */
	void openTwitterForiOS(const char *appKey, const char* appSecret);

	/** Deprecated��ʹ��'setPlatforms'����������Ӧƽ̨�������п���
	 * ��Instagram���أ�ֻ��iOSƽ̨��Ч
	 *
	 */
	void openInstagramForiOS();

	/**
	 *  �Ƿ���log
	 * @param flag ���Ϊtrue����log, ����ر�.
	 */
	void setLogEnable(bool flag);

	/**
	 * ��ƽ̨���÷�������
	 * @param platform ƽ̨������ö��
	 * @param text ��ƽ̨�������ݵ��ı�
	 * @param imagePath ��ƽ̨�������ݵ�ͼƬurl���ӡ����߱���·����������Դ��������asset�е�ͼƬ.����ο�setShareImageName����
	 * @param title ����ʱ�ı���, Ĭ��Ϊ���ַ���
	 * @param targetUrl ������Ϣ�����ʱ��ת����Ŀ��url ( ��������ƽ̨��֧�ִ���� ) , Ĭ��Ϊ���ַ���
	 */
	void setPlatformShareContent(int platform, const char* text,
			const char* imagePath, const char* title = NULL,
			const char* targetUrl = NULL);

	/**
	 * ����ƽ̨��sso��Ȩ��Ŀǰ֧�ֵ�ƽ̨������΢��������������Ѷ΢������ƽ̨. ������SSOʱ��ȷ���������˹ٷ�������Щƽ̨��app id, app key����Ϣ.iOS��֧������΢������Ѷ΢������֧��������ƽ̨��
	 * ����������app id, app key�����ڱ�����ͨ��setRenrenAppInfo������.
	 * @param  platform Ҫ֧��SSO��Ȩ��ƽ̨
     * @param redirectURL ����Ȩƽ̨�Ļص�URL����URL��Ҫ�Ϳ���ƽ̨Ӧ�ù��������õĻص�URLһ��
	 */
	void setSsoAuthorization(int platform, const char *redirectURL);

private:
	static CCUMSocialSDK *_instance;
	vector<int>* mPlatforms;
	char* _wrapperType;
	char* _wrapperVersion;

};
}
}

#endif
