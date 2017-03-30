/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#include "UMengSocial.h"
#include "HNUIExport.h"
#include "HNNetExport.h"
#include "../LibHNMarket/HNOperator.h"

USING_NS_CC;
using namespace network;

#define JSON_RESOVE(obj, key) (obj.HasMember(key) && !obj[key].IsNull())

namespace HN
{
	static UMengSocial* social = nullptr;

	UMengSocial* UMengSocial::getInstance()
	{
		if (nullptr == social)
		{
			social = new (std::nothrow) UMengSocial();
			social->initData();
		}
		return social;
	}

	void UMengSocial::destroyInstance()
	{
		CC_SAFE_DELETE(social);
	}

	UMengSocial::UMengSocial()
	{
	}

	UMengSocial::~UMengSocial()
	{
	}

	void UMengSocial::initData()
	{
		// ��������AppKey
		_uMengAppKey = "585bac7f734be45610001a97";
		//// ����QQ����ƽ̨�˺���Ϣ
		//_qqAppId = "1105655910";
		//_qqAppKey = "RaJIuub9BszetjB1";
		// ����΢�ſ���ƽ̨�ʺ���Ϣ
		_weChatAppId = "wxc3e81c981f91be0d";
		_weChatAppKey = "fece50d0c89c7560e7fd57ee0e2ec50f";

	}

	// ��ʼ��������ữ���
	CCUMSocialSDK* UMengSocial::getUMengSocial()
	{
		CCUMSocialSDK* sdk = CCUMSocialSDK::create(_uMengAppKey.c_str());
		sdk->setQQAppIdAndAppKey(_qqAppId.c_str(), _qqAppKey.c_str());
		sdk->setWeiXinAppInfo(_weChatAppId.c_str(), _weChatAppKey.c_str());

		return sdk;
	}

	// ���÷���ƽ̨
	vector<int>* UMengSocial::setSharePlatforms(bool bWeixin, bool bQQ, bool bWeixinCircle, bool bQzone, bool bSina)
	{
		// �������˷����������ʾ��ƽ̨
		vector<int>* platforms = new vector<int>();
		//if (Operator::requestChannel("sysmodule", "isAppInstalled", StringUtils::format("%d", QQ)).compare("true") == 0)
		//{
		//	if (bQQ)			platforms->push_back(QQ);
		//	if (bQzone && "" != _shareText)			platforms->push_back(QZONE); // QQ�ռ�ֻ�ܷ���ͼ����ʽ�����ܷ���ͼƬ
		//}
		
		if (Operator::requestChannel("sysmodule", "isAppInstalled", StringUtils::format("%d", WEIXIN)).compare("true") == 0)
		{
			if (bWeixin)		platforms->push_back(WEIXIN);
			if (bWeixinCircle)	platforms->push_back(WEIXIN_CIRCLE);
		}
		//if (bSina)			platforms->push_back(SINA);

		return platforms;
	}

	// ִ�з���
	void UMengSocial::doShare(const std::string& text, const std::string& titile, const std::string& url, const std::string& imgName,
		int platform, Node* node)
	{
		_shareText = text;
		_shareTitile = titile.empty() ? "Welcome!" : titile;
		_shareUrl = url.empty() ? "http://www.hotniao.com" : url;
		_shareImg = imgName;

		if (imgName.empty())
		{
			Node* captureNode = (node == nullptr) ? Director::getInstance()->getRunningScene() : node;
			float scale = (node == nullptr) ? 0.5f : 0.8f;
			auto img = utils::captureNode(captureNode, scale);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			_shareImg = "/sdcard/umeng_share.jpg";
#else
			_shareImg = FileUtils::getInstance()->getWritablePath() + "umeng_share.jpg";
#endif
			img->saveToFile(_shareImg);
		}
		openUMengShare(platform);
	}

	// ִ�з���
	void UMengSocial::openUMengShare(int platform)
	{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID && CC_TARGET_PLATFORM != CC_PLATFORM_IOS) 
		MessageBox("Only supports Android and IOS!", "error");
		return;
#endif

		CCUMSocialSDK* sdk = getUMengSocial();

		// ��ȡ����Ŀ��ƽ̨
		vector<int>* platforms = setSharePlatforms();

		// ���÷�����ƽ̨��������Ϊ�˷�ֹ�����ͽ��ֻ��Ӳ���ƽ̨
		sdk->setPlatforms(platforms);

		// ���÷������
		for (auto platform : *platforms)
		{
			sdk->setPlatformShareContent(platform, _shareText.c_str(), _shareImg.c_str(), _shareTitile.c_str(), _shareUrl.c_str());
		}
		
		if (platforms->empty())
		{
			sdk->setPlatformShareContent(RENREN, _shareText.c_str(), _shareImg.c_str(), _shareTitile.c_str(), _shareUrl.c_str());
			sdk->directShare(RENREN, _shareText.c_str(), _shareImg.c_str(), share_selector(UMengShareCallback));
			return;
		}

		if (platform == -1)
		{
			sdk->openShare(_shareText.c_str(), _shareImg.c_str(), share_selector(UMengShareCallback));
		}
		else
		{
			if (1 == platform || 2 == platform)
			{
				if (Operator::requestChannel("sysmodule", "isAppInstalled", StringUtils::format("%d", WEIXIN)).compare("false") == 0)
				{
					MessageBox("Application not installed!", "error");
					return;
				}
			}

			if (3 == platform || 4 == platform)
			{
				if (Operator::requestChannel("sysmodule", "isAppInstalled", StringUtils::format("%d", QQ)).compare("false") == 0)
				{
					MessageBox("Application not installed!", "error");
					return;
				}
			}
			
			sdk->directShare(platform, _shareText.c_str(), _shareImg.c_str(), share_selector(UMengShareCallback));
		}
	}

	//���˷���ص�
	void UMengSocial::UMengShareCallback(int platform, int stCode, const std::string& errorMsg)
	{
		if (200 == stCode && nullptr != social->onShareCallBack)
		{
			social->onShareCallBack(true, platform, errorMsg);
			social->onShareCallBack = nullptr;
		}
	}

	// ����ʧ��
	void UMengSocial::shareFaild(const std::string& errorMsg)
	{
		if (!onShareCallBack) return;

		onShareCallBack(false, -1, errorMsg);
		onShareCallBack = nullptr;
	}

	// ִ�е�������¼
	void UMengSocial::doThirdLogin(int platform)
	{
		CCUMSocialSDK* sdk = getUMengSocial();
		sdk->setPlatforms(setSharePlatforms());

		// ��ĳ��ƽ̨��Ȩ, ������Ϊ��Ȩ�ص�
		sdk->authorize(platform, auth_selector(authCallback));
	}

	// ɾ����Ȩ
	void UMengSocial::doDedeteAuthorize(int platform)
	{
		CCUMSocialSDK* sdk = getUMengSocial();
		sdk->setPlatforms(setSharePlatforms());

		sdk->deleteAuthorization(platform, nullptr);
	}

	/*
	 *	��Ȩ�ص�
	 *	ע�ⰲ׿������΢�Żص�·����������һ�£������޻ص���Ϣ
	 *	������׿������com.redbird.project��΢�Żص�·����������Ϊ��com.redbird.project.wxapi
	 */
	void UMengSocial::authCallback(int platform, int stCode, std::map<std::string, std::string>& data)
	{
		auto userDefault = UserDefault::getInstance();
		if (stCode == 100)
		{
			log("#### authBegin");
		}
		else if (stCode == 200)
		{
			log("#### authFinish");

			switch (platform)
			{
			case WEIXIN:
			{
				// �����Ȩ����, �����Ȩʧ��,������������Ϣ
				auto it = data.begin();
				for (; it != data.end(); ++it) {
					log("#### data  %s -> %s.", it->first.c_str(), it->second.c_str());
				}

				std::string access_token = data.find("token")->second;
				log("#### data  token after-> %s.", access_token.c_str());

				std::string openId = data.find("uid")->second;
				if ("" == openId)
				{
					time_t tt;
					time(&tt);
					struct tm * now;
					//��ñ���ʱ��
					now = localtime(&tt);
					openId = StringUtils::format("%d%02d%02d%02d%02d%02d%d", now->tm_year + 1900, now->tm_mon + 1,
						now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec, rand());
				}
				log("#### data  openId after-> %s.", openId.c_str());

				userDefault->setStringForKey(WECHAT_OPEN_ID, openId);
				userDefault->setStringForKey(WECHAT_ACCESS_TOKEN, access_token);

				UMengSocial::getInstance()->getLoginInfo(WEIXIN, openId, access_token);
			}
				break;
			case QQ:
			{
				// �����Ȩ����, �����Ȩʧ��,������������Ϣ
				auto it = data.begin();
				for (; it != data.end(); ++it) {
					log("#### data  %s -> %s.", it->first.c_str(), it->second.c_str());
				}

				std::string access_token = data.find("token")->second;
				log("#### data  token after-> %s.", access_token.c_str());

				std::string openId = data.find("uid")->second;
				if ("" == openId)
				{
					time_t tt;
					time(&tt);
					struct tm * now;
					//��ñ���ʱ��
					now = localtime(&tt);
					openId = StringUtils::format("%d%02d%02d%02d%02d%02d%d", now->tm_year + 1900, now->tm_mon + 1,
						now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec, rand());
				}
				log("#### data  openId after-> %s.", openId.c_str());

				userDefault->setStringForKey(QQ_OPEN_ID, openId);
				userDefault->setStringForKey(QQ_ACCESS_TOKEN, access_token);

				UMengSocial::getInstance()->getLoginInfo(QQ, openId, access_token);
			}
				break;
			default:
				break;
			}
		}
		else if (stCode == 0)
		{
			social->loginFaild("��Ȩ����", 1);
		}
		else if (stCode == -1)
		{
			social->loginFaild("ȡ����Ȩ", 1);
		}
		else
		{

		}

		userDefault->flush();
	}

	//��ȡ��½�û���Ϣ
	void UMengSocial::getLoginInfo(int platform, const std::string& openID, const std::string& access_token)
	{
		std::string openid = openID;
		std::string access = access_token;

		switch (platform)
		{
		case WEIXIN:
		{
			if (openID.empty() || access_token.empty())
			{
				openid = UserDefault::getInstance()->getStringForKey(WECHAT_OPEN_ID);
				access = UserDefault::getInstance()->getStringForKey(WECHAT_ACCESS_TOKEN);
			}

			std::string url = "https://api.weixin.qq.com/sns/userinfo?access_token=" + access + "&openid=" + openid;

			requestHttp("getWeChatLoginInfo", cocos2d::network::HttpRequest::Type::GET, url);
		}
			break;
		case QQ:
		{
			if (openID.empty() || access_token.empty())
			{
				openid = UserDefault::getInstance()->getStringForKey(QQ_OPEN_ID);
				access = UserDefault::getInstance()->getStringForKey(QQ_ACCESS_TOKEN);
			}

			log("#### data  openId -> %s.", openid.c_str());
			log("#### data  token -> %s.", access.c_str());

			std::string url = "https://graph.qq.com/user/get_user_info?access_token=" + access + "&openid=" + openid
				+ "&oauth_consumer_key=" + _qqAppId;

			log("#### url:%s", url.c_str());

			requestHttp("getQQLoginInfo", cocos2d::network::HttpRequest::Type::GET, url);
		}
			break;
		default:
			break;
		}
	}

	// ��ȡ��Ϣ���
	void UMengSocial::getWeChatInfoResult(rapidjson::Document& doc)
	{
		if (JSON_RESOVE(doc, "errcode"))
		{
			loginFaild("��ȡ�û���Ϣʧ��", -1);
			return;
		}

		ThirdPartyLoginInfo userInfo;

		if (JSON_RESOVE(doc, "unionid"))
		{
			userInfo.unionid = doc["unionid"].GetString();
		}

		if (JSON_RESOVE(doc, "nickname"))
		{
			std::string nickName_temp = doc["nickname"].GetString();
			std::wstring nickName_temp_unicode = utf8_to_unicode(nickName_temp.c_str());
			std::wstring nickName_wtemp = Tools::filterEmoji(nickName_temp_unicode);
			userInfo.nickName = unicode_to_utf8(nickName_wtemp.c_str());

			if ("" == userInfo.nickName)
			{
				userInfo.nickName = "����";
			}
		}

		if (JSON_RESOVE(doc, "headimgurl"))
		{
			userInfo.headUrl = doc["headimgurl"].GetString();
		}

		if (JSON_RESOVE(doc, "sex"))
		{
			userInfo.bBoy = doc["sex"].GetInt() == 1;
		}

		if (onAuthorizeCallBack)
		{
			onAuthorizeCallBack(true, &userInfo, "��Ȩ�ɹ�", 0);
		}
	}

	// ��ȡQQ��Ϣ���
	void UMengSocial::getQQInfoResult(rapidjson::Document& doc)
	{
		//auto userDefault = UserDefault::getInstance();

		if (JSON_RESOVE(doc, "errcode"))
		{
			loginFaild("��ȡ�û���Ϣʧ��", -1);
			return;
		}

		ThirdPartyLoginInfo userInfo;

		//QQ��½��ȡ���û���Ϣ��û������ֶΣ�������Ȩ�ɹ���ص�����Ϣ���У����ֶα����ڱ���
		userInfo.unionid = UserDefault::getInstance()->getStringForKey(QQ_OPEN_ID);

		if (JSON_RESOVE(doc, "nickname"))
		{
			std::string nickName_temp = doc["nickname"].GetString();
			std::wstring nickName_temp_unicode = utf8_to_unicode(nickName_temp.c_str());
			std::wstring nickName_wtemp = Tools::filterEmoji(nickName_temp_unicode);
			userInfo.nickName = unicode_to_utf8(nickName_wtemp.c_str());

			if ("" == userInfo.nickName)
			{
				userInfo.nickName = "����";
			}
		}

		if (JSON_RESOVE(doc, "figureurl_qq_2"))
		{
			userInfo.headUrl = doc["figureurl_qq_2"].GetString();
		}
		else if (JSON_RESOVE(doc, "figureurl_qq_1"))
		{
			userInfo.headUrl = doc["figureurl_qq_1"].GetString();
		}

		if (JSON_RESOVE(doc, "gender"))
		{
			std::string gender = doc["gender"].GetString();
			userInfo.bBoy = (gender.compare(GBKToUtf8("��")) == 0);
		}

		if (onAuthorizeCallBack)
		{
			onAuthorizeCallBack(true, &userInfo, "��Ȩ�ɹ�", 0);
		}
	}

	// ��½ʧ�ܣ���Ҫ������Ȩ
	void UMengSocial::loginFaild(const std::string& errorMsg, int errorCode)
	{
		if (onAuthorizeCallBack)
		{
			onAuthorizeCallBack(false, nullptr, errorMsg, errorCode);
		}
	}

	void UMengSocial::requestHttp(const std::string& name, cocos2d::network::HttpRequest::Type type, const std::string& url, const std::string& param)
	{
		HttpRequest* request = new (std::nothrow) HttpRequest();
		request->setUrl(url.c_str());
		request->setRequestType(type);
		request->setResponseCallback(CC_CALLBACK_2(UMengSocial::onHttpResponse, social));
		request->setTag(name.c_str());

		if (type == HttpRequest::Type::POST && !param.empty())
		{
			request->setRequestData(param.c_str(), param.size());
		}

		HttpClient::getInstance()->sendImmediate(request);
		request->release();
	}

	void UMengSocial::onHttpResponse(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response)
	{
		bool isSucceed = response->isSucceed();
		std::string data;

		if (isSucceed)
		{
			std::vector<char>* recv = response->getResponseData();
			data.assign(recv->begin(), recv->end());
		}
		else
		{
			data = response->getErrorBuffer();

			loginFaild(data, 1);
			return;
		}

		std::string requestName = response->getHttpRequest()->getTag();

		rapidjson::Document doc;
		doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
		if (!doc.IsObject()) return;

		if (requestName.compare("getWeChatLoginInfo") == 0)
		{
			getWeChatInfoResult(doc);
		}
		else if (requestName.compare("getQQLoginInfo") == 0)
		{
			getQQInfoResult(doc);
		}
		else
		{

		}
	}
}