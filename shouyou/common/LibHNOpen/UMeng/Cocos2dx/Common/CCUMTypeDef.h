/**
 * CCUMTypeDef.h
 *	���Ͷ����ļ��� ������ƽ̨ö�٣�����ص�����Ȩ�ص�������.
 *
 */
#include <map>
#include <string>
using namespace std;

#ifndef _CCUMTypeDef_h
#define _CCUMTypeDef_h

/// ��������ữ���SDK�����ռ�ĺ�
#ifdef __cplusplus

#define USING_NS_UM_SOCIAL      using namespace umeng::social
#else 
#define USING_NS_SOCIAL
#endif 

namespace umeng {
////////////////////////////////////////////////////////////////////////////////////
/// @namespace social
/// @brief ������ữ���Cocos2d-x SDK�����ռ�

namespace social {

/// ��������ƽ̨��ö��
enum Platform {
	/// ����΢��
	SINA = 0,
	/// ΢��
	WEIXIN = 1,
	/// ΢������Ȧ
	WEIXIN_CIRCLE = 2,
	/// QQ
	QQ = 3,
	 /// QQ�ռ�
	QZONE = 4,
	/// ������
	RENREN = 5,
	/// ����
	DOUBAN = 6,
	/// ����
	LAIWANG = 7,
	/// ������̬
	LAIWANG_CIRCLE = 8,
	/// ����
	YIXIN = 9,
	/// ��������Ȧ
	YIXIN_CIRCLE = 10,
	/// facebook
	FACEBOOK = 11,
	/// twitter
	TWITTER = 12,
	/// instagram
	INSTAGRAM = 13,
	/// ����
	SMS = 14,
	/// �ʼ�
	EMAIL = 15,
	/// ��Ѷ΢��
	TENCENT_WEIBO = 16
};

/**
 * ��Ȩ�ص�����ָ������
 * @param platform ƽ̨
 * @param stCode ״̬��, 200������Ȩ�ɹ�, 100����ʼ��Ȩ, 0������Ȩ����, -1����ȡ����Ȩ
 * @param data ��Ȩ����
 */
typedef void (*AuthEventHandler)(int platform, int stCode,
		const map<string, string>& data);
/**
 * ����ص�����ָ������
 * @param platform ƽ̨
 * @param stCode ״̬��, 200�������ɹ�, 100����ʼ����
 * @param errorMsg ������Ϣ, Androidƽ̨��û�д�����Ϣ����
 */
typedef void (*ShareEventHandler)(int platform, int stCode,
		const string& errorMsg);

/// ��Ȩ�ص�selector
#define auth_selector(_SELECTOR) (AuthEventHandler)(&_SELECTOR)

/// ����ص�selector

#define share_selector(_SELECTOR) (ShareEventHandler)(&_SELECTOR)

}
}

#endif
