/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#include "HNLobby/GameVoice/GameVoiceManager.h"
#include "HNLobby/GamePrompt.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include <algorithm>
#include <string>
#include <cstdlib>
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "spine/Json.h"
#include "HNMarketExport.h"

using namespace network;

#define JSON_RESOVE(obj, key) (obj.HasMember(key) && !obj[key].IsNull())

namespace HN
{
	static VoiceManager* pruductManager = nullptr;

	VoiceManager* VoiceManager::getInstance()
	{
		if (nullptr == pruductManager)
		{
			pruductManager = new (std::nothrow) VoiceManager();
			return pruductManager;
		}
		return pruductManager;
	}

	void VoiceManager::destroyInstance()
	{
		CC_SAFE_DELETE(pruductManager);
	}

	VoiceManager::VoiceManager()
	{

	}

	VoiceManager::~VoiceManager()
	{
		HNHttpRequest::getInstance()->removeObserver(this);
	}

	void VoiceManager::onHttpResponse(const std::string& requestName, bool isSucceed, const std::string &responseData)
	{
		if (requestName.compare("uploadAudio") == 0)
		{
			onHandleUploadAudio(isSucceed, responseData);
		}
		else if (requestName.compare("downloadAudio") == 0)
		{
			onHandleDownloadAudio(isSucceed, responseData);
		}
	}

	void VoiceManager::onHandleUploadAudio(bool isSucceed, const std::string &responseData)
	{
		log("upload audio str>>>>>1");

		if (!isSucceed)
		{
			log("upload audio str>>>>>2");
			return;
		}

		log("upload audio str>>>>>3");

		rapidjson::Document doc;
		doc.Parse<rapidjson::kParseDefaultFlags>(responseData.c_str());
		if (!doc.IsObject())
		{
			return;
		}

		int status = 1;

		if (JSON_RESOVE(doc, "status")) status = doc["status"].GetInt();

		log("upload audio str>>>>>%d", status);

		if (0 == status) //获取失败
		{
			return;
		}

		int audioID = 0;
		rapidjson::Value& _array = doc["info"];
		if (JSON_RESOVE(_array[0], "id")) audioID = _array[0]["id"].GetInt();

		sendVoiceMessage(audioID);
	}

	void VoiceManager::onHandleDownloadAudio(bool isSucceed, const std::string &responseData)
	{
        if (!isSucceed)
        {
            return;
        }
        
        rapidjson::Document doc;
        doc.Parse<rapidjson::kParseDefaultFlags>(responseData.c_str());
        if (!doc.IsObject())
        {
            return;
        }
        
        int status = 1;
        
        if (JSON_RESOVE(doc, "status")) status = doc["status"].GetInt();
        
        if (0 == status) //获取失败
        {
            return;
        }
        
        std::string audioString = "";
        rapidjson::Value& _array = doc["info"];
        if (JSON_RESOVE(_array[0], "Audio")) audioString = _array[0]["Audio"].GetString();

		//log("download audio str>>>>>%s", audioString.c_str());
        playAudio(audioString);
	}

	//开始录音
	void VoiceManager::startRecordAudio()
	{   
		HNAudioEngine::getInstance()->pauseBackgroundMusic();
        Operator::requestChannel("hnvoice", "startRecord");
	}
    
    void VoiceManager::stopRecordAudio()
    {       
        std::string audio = Operator::requestChannel("hnvoice", "stopRecord");
    
		log("recorded audio str>>>>>%s", audio.c_str());
        uploadAudio(audio);
		//uploadAudio(StringUtils::format("fdsf"));
		//sendVoiceMessage(12);
		HNAudioEngine::getInstance()->resumeBackgroundMusic();
    }

	//结束录音
	void VoiceManager::endRecordAudio(std::string audio)
	{
		return;
	}

	//上传音频(http接口)
	void VoiceManager::uploadAudio(std::string &audio)
	{
		std::string url = PlatformConfig::getInstance()->getVoiceUrl();
		std::string requestData = "action=SaveAudio";		
		requestData.append(StringUtils::format("&userid=%d", PlatformLogic()->loginResult.dwUserID));
		requestData.append("&audio=");
        requestData.append(URLEncode(audio));
		
		log("upload audio requestData>>>>>%s", requestData.c_str());

		HNHttpRequest::getInstance()->addObserver(this);
		HNHttpRequest::getInstance()->request("uploadAudio", HttpRequest::Type::POST, url, requestData);
	}

	//发送TCP消息给游戏服务端, 表示玩家已经发出语音
	void VoiceManager::sendVoiceMessage(int audioID)
	{
		VoiceInfo audioInfo;
		audioInfo.uUserID = PlatformLogic()->loginResult.dwUserID;
		audioInfo.uVoiceID = audioID;
		
		// 发送语音消息
		//RoomLogic()->sendData(MDM_GM_GAME_NOTIFY, ASS_GR_VOIEC, &audioInfo, sizeof(audioInfo),
		//	HN_SOCKET_CALLBACK(VoiceManager::sendVoiceCallback, this));
		RoomLogic()->sendData(MDM_GM_GAME_NOTIFY, ASS_GR_VOIEC, &audioInfo, sizeof(audioInfo));
	}

	//录音消息回调
	bool VoiceManager::sendVoiceCallback(HNSocketMessage* socketMessage)
	{
		if (MDM_GM_GAME_NOTIFY != socketMessage->messageHead.bMainID) return false;
		if (ASS_GR_VOIEC != socketMessage->messageHead.bAssistantID) return false;
		if (RES_GR_VOIEC_SUC != socketMessage->messageHead.bHandleCode) return false;
			
		CCAssert(sizeof(VoiceInfo) == socketMessage->objectSize, "VoiceInfo is error.");
		VoiceInfo* iCheck = (VoiceInfo*)socketMessage->object;
		
		return true;
	}

	//下载音频(http接口)
	void VoiceManager::downloadAudio(int audioID)
	{
		std::string url = PlatformConfig::getInstance()->getVoiceUrl();
		std::string requestData = "action=GetAudio";
		requestData.append(StringUtils::format("&id=%d", audioID));

		HNHttpRequest::getInstance()->addObserver(this);
		HNHttpRequest::getInstance()->request("downloadAudio", HttpRequest::Type::POST, url, requestData);
	}

	//播放音频
	void VoiceManager::playAudio(std::string &audio)
	{	
		HNAudioEngine::getInstance()->pauseBackgroundMusic();
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        _callback.selector = CC_CALLBACK_1(VoiceManager::onPlayFinished, this);
        Operator::requestChannel("hnvoice", "playAudio", audio, &_callback);
#else
		Operator::requestChannel("hnvoice", "playAudio", audio);
#endif
	}
    
    void VoiceManager::onPlayFinished(std::string data)
    {
        if(data.compare("finish") == 0)
        {
            HNAudioEngine::getInstance()->resumeBackgroundMusic();
        }
    }

	//播放音频
	void VoiceManager::playAudio(int audioID)
	{
		downloadAudio(audioID);
	}

	//取消录音
	void VoiceManager::cancelRecordAudio()
	{
		Operator::requestChannel("hnvoice", "cancelRecord");
		HNAudioEngine::getInstance()->resumeBackgroundMusic();
	}
}