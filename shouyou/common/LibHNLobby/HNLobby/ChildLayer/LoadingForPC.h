#ifndef __LoadingForPC_h__
#define __LoadingForPC_h__

#include "HNUIExport.h"
#include "HNLogicExport.h"
#include "cocos2d.h"
#include <string>

namespace HN
{
	class LoadingForPC: public HNLayer, HNPCStartLogicDelegate
	{
	public:	
		/*
		 * 功能：创建过渡界面场景
		 * 参数：port-端口号
		 */
		static Scene* createScene(int port);

		/*
		 * 功能：创建过渡界面
		 * 参数：port-端口号
		 */
		static LoadingForPC* create(int port);

		/*
		 * 功能：初始化
		 * 参数：port-端口号
		 */
		virtual bool init(int port);
		
	protected:
		/*
		 * 功能：开始连接本地服务器
		 * 参数：port-端口号
		 */
		void startConnect(int port);

		// 添加过渡界面
		void loadUI();

		// 添加测试按钮（主动点击才会连接服务器）
		void addTestMenu();

		// 连接按钮点击
		void onStartClick(Ref* pRef);

		// 启动失败
		virtual void onStartGameError(const std::string& message) override;
	private:
		// 文本显示标签
		Label*	_label;

		// 游戏启动逻辑
		HNPCStartLogic* _logic;

		// 端口号
		int _port;

		// 构造函数
		LoadingForPC();

		// 析构函数
		virtual ~LoadingForPC();
	};

}
#endif // __LoadingForPC_h__
