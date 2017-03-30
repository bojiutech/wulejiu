#ifndef __HN_UserHead_Http_H__
#define __HN_UserHead_Http_H__

#include <string>
#include "cocos2d.h"
#include "network/HttpClient.h"

namespace HN
{
	class HNUserHeadHttpDelegate
	{
	public:
		virtual void onHttpResponse(const std::string& requestName, bool isSucceed, std::vector<char> &responseData) = 0;
	};

	class HNUserHeadHttpRequest
	{
	public:
		static HNUserHeadHttpRequest* getInstance();
		static void destroyInstance();
		void request(const std::string& name, cocos2d::network::HttpRequest::Type type, const std::string& url, const std::string& param = "");
		void addObserver(HNUserHeadHttpDelegate* delegate);
		void removeObserver(HNUserHeadHttpDelegate* delegate);

	public:
		HNUserHeadHttpRequest();
		virtual ~HNUserHeadHttpRequest();

	protected:
		void onHttpResponse(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response);

	private:
		std::vector<HNUserHeadHttpDelegate*> _addCache;
		std::vector<HNUserHeadHttpDelegate*> _removeCache;
		std::vector<HNUserHeadHttpDelegate*> _observers;

	};
}

#endif // __HN_UserHead_Http_H__