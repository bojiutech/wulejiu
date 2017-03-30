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

	// ��������
	class VoiceManager : public HNHttpDelegate
	{
	public:
		// ��ȡ����
		static VoiceManager* getInstance();

		// ���ٵ���
		static void destroyInstance();

	public:
		VoiceManager();
		~VoiceManager();

		virtual void onHttpResponse(const std::string& requestName, bool isSucceed, const std::string &responseData) override;

		void onHandleUploadAudio(bool isSucceed, const std::string &responseData);

		void onHandleDownloadAudio(bool isSucceed, const std::string &responseData);

		/////////////////////��������Ϊ�� ��ʼ¼��->����¼��->�ϴ���Ƶ->��ƽ̨��Ƶ��Ϣ////////////////////
		/////////////////////�յ�ƽ̨��Ƶ��Ϣ->������Ƶ��Ϣ->������Ƶ/////////////////////////////////////

		//��ʼ¼��
		void startRecordAudio();
        
        void stopRecordAudio();

		//����¼��
        void endRecordAudio(std::string audio);

		//�ϴ���Ƶ(http�ӿ�)
		void uploadAudio(std::string &audio);

		//����TCP��Ϣ����Ϸ�����, ��ʾ����Ѿ���������
		void sendVoiceMessage(int audioID);

		//������Ƶ(http�ӿ�)
		void downloadAudio(int audioID);

		//������Ƶ
		void playAudio(std::string &audio);

		//������Ƶ
		void playAudio(int audioID);

		//ȡ��¼��
		void cancelRecordAudio();

		//¼����Ϣ�ص�
		bool sendVoiceCallback(HNSocketMessage* socketMessage);
        
        // ���Ž����ص�
        void onPlayFinished(std::string data);
        
    public:
        CALLBACK_PRAGMA _callback;
	
	};
}

#endif // VoiceManager_h__