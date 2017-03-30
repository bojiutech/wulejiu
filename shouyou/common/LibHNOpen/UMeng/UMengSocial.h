/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#ifndef __UMeng_Social_h__
#define __UMeng_Social_h__

#include "cocos2d.h"
#include "network/HttpClient.h"
#include <vector>
#include <string>
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "Cocos2dx/Common/CCUMSocialSDK.h"

USING_NS_CC;
USING_NS_UM_SOCIAL;

namespace HN
{
#define WECHAT_OPEN_ID			"weChat_open_id"
#define WECHAT_ACCESS_TOKEN		"weChat_access_token"

#define QQ_OPEN_ID				"qq_open_id"
#define QQ_ACCESS_TOKEN			"qq_access_token"

	struct ThirdPartyLoginInfo
	{
		std::string unionid;
		std::string nickName;
		std::string headUrl;
		bool bBoy;

		ThirdPartyLoginInfo()
		{
			unionid = "";
			nickName = "";
			headUrl = "";
			bBoy = false;
		}
	};

	class UMengSocial
	{		
	public:
		typedef std::function<void(bool success, ThirdPartyLoginInfo* info, const std::string& errorMsg, int errorCode)> AuthorizeCallBack;

		AuthorizeCallBack onAuthorizeCallBack = nullptr;

		typedef std::function<void(bool success, int platform, const std::string& errorMsg)> ShareCallBack;

		ShareCallBack onShareCallBack = nullptr;

	public:
		// ��ȡ����
		static UMengSocial* getInstance();

		// ���ٵ���
		static void destroyInstance();

	public:
		UMengSocial();

		~UMengSocial();

    public:
		// ִ�з���(platform�����������Ϊ��Ĭ�Ϸ������)
		void doShare(const std::string& text, const std::string& titile, const std::string& url, const std::string& imgName = "", 
			int platform = -1, Node* node = nullptr);

	public:
		// ִ�е�������¼
		void doThirdLogin(int platform);

		// ��ȡ��½�û���Ϣ
		void getLoginInfo(int platform, const std::string& openID = "", const std::string& access_token = "");

		// ɾ����Ȩ
		void doDedeteAuthorize(int platform);

	private:
		void initData();

		// ��ȡ������ữ���
		CCUMSocialSDK* getUMengSocial();

		// ���÷���ƽ̨
		vector<int>* setSharePlatforms(bool bWeixin = true, bool bQQ = true, bool bWeixinCircle = true, bool bQzone = true, bool bSina = true);

		// ִ�з���
		void openUMengShare(int platform = -1);

		// ����ص�
		static void UMengShareCallback(int platform, int stCode, const std::string& errorMsg);

		// ��Ȩ�ص�
		static void authCallback(int platform, int stCode, std::map<std::string, std::string>& data);

	private:

		// ��ȡ΢����Ϣ���
		void getWeChatInfoResult(rapidjson::Document& doc);

		// ��ȡQQ��Ϣ���
		void getQQInfoResult(rapidjson::Document& doc);

		// ����ʧ��
		void shareFaild(const std::string& errorMsg);

		// ��½ʧ�ܣ���Ҫ������Ȩ
		void loginFaild(const std::string& errorMsg, int errorCode);

	protected:
		void requestHttp(const std::string& name, cocos2d::network::HttpRequest::Type type, const std::string& url, const std::string& param = "");

		void onHttpResponse(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response);

	protected:
		// ����AppKey
		CC_SYNTHESIZE_PASS_BY_REF(std::string, _uMengAppKey, UMengAppKey);

		// ΢��AppId
		CC_SYNTHESIZE_PASS_BY_REF(std::string, _weChatAppId, WeChatAppId);

		// ΢��AppKey
		CC_SYNTHESIZE_PASS_BY_REF(std::string, _weChatAppKey, WeChatAppKey);

		// QQ AppId
		CC_SYNTHESIZE_PASS_BY_REF(std::string, _qqAppId, QQAppId);

		// QQ AppKey
		CC_SYNTHESIZE_PASS_BY_REF(std::string, _qqAppKey, QQAppKey);

		// text
		CC_SYNTHESIZE_PASS_BY_REF(std::string, _shareText, ShareText);

		// titile
		CC_SYNTHESIZE_PASS_BY_REF(std::string, _shareTitile, ShareTitile);

		// image
		CC_SYNTHESIZE_PASS_BY_REF(std::string, _shareImg, ShareImg);

		// ShareUrl
		CC_SYNTHESIZE_PASS_BY_REF(std::string, _shareUrl, ShareUrl);

		bool _bShare = true;
	};
}


#endif // __UMeng_Social_h__