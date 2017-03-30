/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#include "HNUpdate.h"
#include "HNMarketExport.h"
#include "HNNetExport.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "GamePrompt.h"

USING_NS_CC_EXT;
using namespace std;

namespace HN
{
	static const std::string PROGRESS_BAR("platform/setting/settingRes/progress_bar.png");
	static const std::string PROGRESS_BAR_BACK("platform/setting/settingRes/progress_bar_bg.png");

	HNUpdate* HNUpdate::create()
	{
		HNUpdate* update = new HNUpdate();
		if(update != nullptr && update->init())
		{
			update->autorelease();
			return update;
		}
		CC_SAFE_DELETE(update);
		return nullptr;
	}

	void HNUpdate::checkUpdate()
	{
		getOnlineVersion();
	}

	HNUpdate::HNUpdate()
		: _progressTimer(nullptr)
		, _labelPercent(nullptr)
		, _labelMessage(nullptr)
		, _progressBg(nullptr)
		, _isMustUpdate(false)
	{
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = [](Touch* pTouch, Event* pEvent){
			return true;
		};
		listener->setSwallowTouches(true);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

		_downloader = std::make_shared<Downloader>();
		_downloader->onTaskProgress = std::bind(&HNUpdate::onTaskProgress, this,
			std::placeholders::_1,
			std::placeholders::_2,
			std::placeholders::_3,
			std::placeholders::_4);

		_downloader->onFileTaskSuccess = std::bind(&HNUpdate::onFileTaskSuccess, this,
			std::placeholders::_1);

		_downloader->onTaskError = std::bind(&HNUpdate::onTaskError, this,
			std::placeholders::_1,
			std::placeholders::_2,
			std::placeholders::_3,
			std::placeholders::_4);

		//_downloader->setProgressCallback(std::bind(&HNUpdate::onProgressCallback, this, 
		//	std::placeholders::_1,
		//	std::placeholders::_2,
		//	std::placeholders::_3,
		//	std::placeholders::_4));
		//_downloader->setSuccessCallback(std::bind(&HNUpdate::onSuccessCallback, this,
		//	std::placeholders::_1,
		//	std::placeholders::_2,
		//	std::placeholders::_3));
		//_downloader->setErrorCallback(std::bind(&HNUpdate::onErrorCallback, this,
		//	std::placeholders::_1));

		_localVersion  = HN::Operator::requestChannel("sysmodule", "getversion");
		_onlineVersion = _localVersion;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		_storePath = "/sdcard/";
#else
		_storePath = FileUtils::getInstance()->getWritablePath();
#endif
	}

	HNUpdate::~HNUpdate()
	{
		HNHttpRequest::getInstance()->removeObserver(this);
	}

	bool HNUpdate::init()
	{
		if(!HNLayer::init())
		{
			return false;
		}

		Size winSize = Director::getInstance()->getWinSize();

		auto layer = LayerColor::create(Color4B(0, 0, 0, 125));
		this->addChild(layer, 1);
		layer->setPosition(Vec2::ZERO);

		Sprite* bar_bg = Sprite::create(PROGRESS_BAR_BACK);
		if(bar_bg != nullptr)
		{
			this->addChild(bar_bg, 2);
			bar_bg->setAnchorPoint(Vec2(0.5f, 0.5f));
			bar_bg->setPosition(winSize.width / 2, winSize.height / 2);
			bar_bg->setVisible(false);
			_progressBg= bar_bg;
		}

		Sprite* bar = Sprite::create(PROGRESS_BAR);
		if(bar != nullptr)
		{			
			_progressTimer = ProgressTimer::create(bar);
			this->addChild(_progressTimer, 3);
			_progressTimer->setAnchorPoint(Vec2(0.5f, 0.5f));
			_progressTimer->setPosition(winSize.width / 2, winSize.height  / 2);
			_progressTimer->setPercentage(0);
			_progressTimer->setType(ProgressTimer::Type::BAR);
			_progressTimer->setMidpoint(Vec2(0,0));
			_progressTimer->setBarChangeRate(Vec2(1, 0));
			_progressTimer->setVisible(false);
		}		

		_labelPercent = Label::createWithSystemFont("", "Arial", 24);
		this->addChild(_labelPercent,4);
		_labelPercent->setAnchorPoint(Vec2(0.5f, 0.5f));
		_labelPercent->setPosition(winSize.width / 2, winSize.height / 2);

		_labelMessage = Label::createWithSystemFont("", "Arial", 24);
		this->addChild(_labelMessage, 4);
		_labelMessage->setAnchorPoint(Vec2(0.5f, 0.5f));
		_labelMessage->setPosition(winSize.width / 2, winSize.height / 2 + 60);
		_labelMessage->setString(GBKToUtf8("�汾���¼����"));

		return true;
	}

	static const int BUFFER_SIZE = 200;
	static unsigned char buffer[BUFFER_SIZE] = {0};

	bool HNUpdate::getOnlineVersion()
	{
		memset(buffer, 0, sizeof(buffer));
		_labelMessage->setString(GBKToUtf8("�汾���¼����"));

		//�������󣬻�ȡ�汾�źͰ�װ����ַ
		requestWithParams("action=GetInfoByKey", "update", PlatformConfig::getInstance()->getAppInfoUrl().c_str(), HttpRequest::Type::POST);

		return true;
	}

	bool HNUpdate::hasNewVersion()
	{
		return _localVersion.compare(_onlineVersion) != 0;
	}

	void HNUpdate::onTaskProgress(const DownloadTask& task, int64_t bytesReceived, int64_t totalBytesReceived, int64_t totalBytesExpected)
	{
		if (task.identifier.compare("download") == 0)
		{
			if(_progressTimer != nullptr)
			{
				float percent = (float)(totalBytesReceived / totalBytesExpected) * 100;
				_progressTimer->setPercentage(percent);
			}
			
			if(_labelPercent != nullptr)
			{
				char str[50] = {0};
				sprintf(str, "%.2fKB / %.2fKB", (double)totalBytesReceived / 1024, (double)totalBytesExpected / 1024);
				_labelPercent->setString(str);
			}
		}
		else
		{
			
		}	
	}

	void HNUpdate::onFileTaskSuccess(const DownloadTask& task)
	{
		if(task.identifier.compare("download") == 0)
		{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			do 
			{
				//CC_BREAK_IF(_progressTimer == nullptr);
				CC_BREAK_IF(onFinishCallback == nullptr);
				//if(_progressTimer->getPercentage() >= 100.f)
				{
					onFinishCallback(true, this, GBKToUtf8("�������"), _storePath);
				}
			} while (0);
#endif
		}
		else
		{
		
		}
	}


	void HNUpdate::onTaskError(const DownloadTask& task, int errorCode, int errorCodeInternal, const std::string& errorStr)
	{
		onFinishCallback(false, this, errorStr, "");
	}

//	void HNUpdate::onProgressCallback(double total, double downloaded, const std::string &url, const std::string &customId)
//	{
//		if(customId.compare("download") == 0)
//		{
//			if(_progressTimer != nullptr)
//			{
//				float percent = (float)(downloaded / total) * 100;
//				_progressTimer->setPercentage(percent);
//			}
//
//			if(_labelPercent != nullptr)
//			{
//				char str[50] = {0};
//				sprintf(str, "%.2fKB / %.2fKB", downloaded / 1024, total / 1024);
//				_labelPercent->setString(str);
//			}
//		}
//		else
//		{
//
//		}		
//	}
//
//	void HNUpdate::onSuccessCallback(const std::string &url, const std::string &tmp, const std::string &customId)
//	{
//		if(customId.compare("download") == 0)
//		{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//			do 
//			{
//				//CC_BREAK_IF(_progressTimer == nullptr);
//				CC_BREAK_IF(onFinishCallback == nullptr);
//				//if(_progressTimer->getPercentage() >= 100.f)
//				{
//					onFinishCallback(true, this, GBKToUtf8("�������"), _storePath);
//				}
//			} while (0);
//#endif
//		}
//		else
//		{
//
//		}
//
//	}
//
//	void HNUpdate::onErrorCallback(const Downloader::Error &error)
//	{
//		onFinishCallback(false, this, error.message, "");
//	}

	//�������ݽӿ�
	void HNUpdate::requestWithParams(const std::string& params, const std::string& tag, const std::string& url, HttpRequest::Type type)
	{
		std::string requestData;
		requestData.append(params);
		requestData.append("&key=");
		requestData.append(PlatformConfig::getInstance()->getAppKey());

		HNHttpRequest::getInstance()->addObserver(this);
		HNHttpRequest::getInstance()->request(tag, type, url, requestData);
	}

	void HNUpdate::onHttpResponse(const std::string& requestName, bool isSucceed, const std::string &responseData)
	{
		if (!isSucceed)
		{
			std::string errorMsg = GBKToUtf8("���²�ѯʧ��(") + responseData + ")";
			auto prompt = GamePromptLayer::create();
			prompt->showPrompt(errorMsg);
			prompt->setCallBack([this](){
				this->removeFromParent();
			});
			return;
		}
		if (requestName.compare("update") == 0)
		{
			HNLOG("appInfo>%s", responseData.c_str());

			rapidjson::Document doc;
			doc.Parse<rapidjson::kParseDefaultFlags>(responseData.c_str());
			if (doc.HasParseError() || !doc.IsObject())
			{
				auto prompt = GamePromptLayer::create();
				prompt->showPrompt(GBKToUtf8("���ݽ���ʧ��"));
				prompt->setCallBack([this](){
					this->removeFromParent();
				});
				return;
			}
			do
			{
				rapidjson::Value& array = doc["content"];
				if (array.IsArray())
				{
					//�������ص�����
					for (UINT i = 0; i < array.Size(); i++)
					{
						rapidjson::Value& arraydoc = array[i];
						do
						{
							if (arraydoc.HasMember("AutoLaunch"))
							{
								_isMustUpdate = arraydoc["AutoLaunch"].GetBool();
							}
							if (arraydoc.HasMember("PlistUrl"))
							{
								_plistUrl = arraydoc["PlistUrl"].GetString();
								PlatformConfig::getInstance()->setDownloadPlistUrl(_plistUrl);
							}
							if (arraydoc.HasMember("id"))
							{
								PlatformConfig::getInstance()->setAppId(arraydoc["id"].GetInt());
							}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
							if (arraydoc.HasMember("AndroidVersion"))
							{
								_onlineVersion = arraydoc["AndroidVersion"].GetString();
							}
							if (arraydoc.HasMember("AndroidName"))
							{
								_downloadUrl = arraydoc["AndroidName"].GetString();
							}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
							if (arraydoc.HasMember("AppleVersion"))
							{
								_onlineVersion = arraydoc["AppleVersion"].GetString();
							}
							if (arraydoc.HasMember("AppleName"))
							{
								_downloadUrl = arraydoc["AppleName"].GetString();
							}
#endif
						} while (0);
					}
				}
			} while (0);

			if (hasNewVersion())
			{
				needUpdate();
			}
			else
			{
				this->removeFromParent();
			}
		}
	}

	void HNUpdate::onClickDownloadCallback()
	{
		if(_progressTimer != nullptr)
		{
			_progressBg->setVisible(true);
			_progressTimer->setVisible(true);
			_progressTimer->setPercentage(0.f);
		}
		if(_labelMessage != nullptr)
		{
			_labelMessage->setString(GBKToUtf8("�°�������..."));
		}

		size_t locate = _downloadUrl.find_last_of("/");
		if(locate == std::string::npos)
		{
			GamePromptLayer::create()->showPrompt(GBKToUtf8("�ļ�������"));
			return;
		}
		std::string filename = _downloadUrl.substr(locate + 1);

		_storePath.append(filename);

		_downloader->createDownloadFileTask(_downloadUrl, _storePath, "download");

		//_downloader->downloadAsync(_downloadUrl, _storePath, "download");
	}

	//�и���
	void HNUpdate::needUpdate()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		auto prompt = GamePromptLayer::create();
		if (_isMustUpdate)
		{
			prompt->showPrompt(GBKToUtf8("�����°汾�����½�����Ϸ"));
		}
		else
		{
			prompt->showPrompt(GBKToUtf8("�����°汾���Ƿ��������أ�"));
			prompt->setPromptCanSelect();
		}
		prompt->setCallBack(CC_CALLBACK_0(HNUpdate::onClickDownloadCallback, this));
		prompt->setCancelCallBack([this](){
			this->removeFromParent();
		});

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				onFinishCallback(true, this, GBKToUtf8("���³ɹ�"), _plistUrl);
#else

#endif
	}
}