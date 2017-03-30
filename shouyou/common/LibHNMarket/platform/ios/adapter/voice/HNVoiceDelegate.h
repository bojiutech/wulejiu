//Copyright (c) 2012—2015 Beijing TianRuiDiAn Network Technology Co,Ltd. All rights reserved



#ifndef HNMutlLobby_HNVoiceDelegate_h
#define HNMutlLobby_HNVoiceDelegate_h

#include <string>

class HNVoiceDelegate
{
public:
    virtual void HandleStopRecord(const std::string& data) = 0;
	
	// 声音播放结束
    virtual void HandlePlayFinish(const std::string& data) = 0;
};

#endif
