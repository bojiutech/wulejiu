/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/



#ifndef __HNUpdate_H__
#define __HNUpdate_H__

#include "HNUIExport.h"
#include "HNNetExport.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include <string>

#include "network/HttpClient.h"
using namespace cocos2d::network;

USING_NS_CC;
USING_NS_CC_EXT;

namespace HN
{
	/*
	 * redbird app update.
	 */
	class HNUpdate: public HN::HNLayer, public HNHttpDelegate
	{
	public:
		static HNUpdate* create();
		void checkUpdate();
		HNUpdate();
		virtual ~HNUpdate();
		virtual bool init();
		std::function<void(bool updated, cocos2d::Node* pSender, const std::string& message, const std::string& storePath)> onFinishCallback;
	protected:
		bool getOnlineVersion();
		bool hasNewVersion();

		void onTaskProgress(const DownloadTask& task, int64_t bytesReceived, int64_t totalBytesReceived, int64_t totalBytesExpected);

		void onFileTaskSuccess(const DownloadTask& task);

		void onTaskError(const DownloadTask& task, int errorCode, int errorCodeInternal, const std::string& errorStr);
		//void onProgressCallback(double total, double downloaded, const std::string &url, const std::string &customId);
		//void onSuccessCallback(const std::string &url, const std::string &tmp, const std::string &customId);
		//void onErrorCallback(const Downloader::Error &error);

		// ��������
		void requestWithParams(const std::string& params, const std::string& tag, const std::string& url, HttpRequest::Type type);

		virtual void onHttpResponse(const std::string& requestName, bool isSucceed, const std::string &responseData) override;
		
		//�и���
		void needUpdate();

		// ���ػص�
		void onClickDownloadCallback();
	private:
		std::string _onlineVersion;
		std::string _localVersion;
		std::string _storePath;
		std::string _jsonPath;
		std::string _downloadUrl;
		std::string _plistUrl;
		std::shared_ptr<Downloader> _downloader;
		ProgressTimer* _progressTimer;
		Sprite* _progressBg;
		Label* _labelPercent;
		Label* _labelMessage;
		bool _isMustUpdate;//�ж��Ƿ�������
	};
}

#endif