/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#ifndef VoiceManager_h__
#define VoiceManager_h__

#include "HNMarketExport.h"
#include "HNNetExport.h"
#include "HNLogicExport.h"
#include <vector>
#include <string>

namespace HN {

	// 语音管理
	class VoiceManager : public HNHttpDelegate
	{
	public:
		// 获取单例
		static VoiceManager* getInstance();

		// 销毁单例
		static void destroyInstance();

	public:
		VoiceManager();
		~VoiceManager();

		virtual void onHttpResponse(const std::string& requestName, bool isSucceed, const std::string &responseData) override;

		void onHandleUploadAudio(bool isSucceed, const std::string &responseData);

		void onHandleDownloadAudio(bool isSucceed, const std::string &responseData);

		/////////////////////语音流程为： 开始录音->结束录音->上传音频->发平台音频消息////////////////////
		/////////////////////收到平台音频消息->下载音频消息->播放音频/////////////////////////////////////

		//开始录音
		void startRecordAudio();
        
        void stopRecordAudio();

		//结束录音
        void endRecordAudio(std::string audio);

		//上传音频(http接口)
		void uploadAudio(std::string &audio);

		//发送TCP消息给游戏服务端, 表示玩家已经发出语音
		void sendVoiceMessage(int audioID);

		//下载音频(http接口)
		void downloadAudio(int audioID);

		//播放音频
		void playAudio(std::string &audio);

		//播放音频
		void playAudio(int audioID);

		//取消录音
		void cancelRecordAudio();

		//录音消息回调
		bool sendVoiceCallback(HNSocketMessage* socketMessage);
        
        // 播放结束回调
        void onPlayFinished(std::string data);
        
    public:
        CALLBACK_PRAGMA _callback;
	
	};
}

#endif // VoiceManager_h__