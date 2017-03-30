#ifndef __HN_HNGameUIBase_H__
#define __HN_HNGameUIBase_H__

#include "HNBaseType.h"
#include "HNUIExport.h"

namespace HN
{
    class HNGameUIBase: public HNLayer
	{
	public:
		// 构造函数
		HNGameUIBase();

		// 析构函数
		virtual ~HNGameUIBase();

		// 初始化
		virtual bool init() override;

		// 加载界面（初始化时）
		virtual void loadUI();

		// 卸载界面（界面移除）
		virtual void unLoadUI();

	public:
		// 发送消息
		void sendData(UINT MainID, UINT AssistantID, void* object = nullptr, INT objectSize = 0);

	};
}


#endif