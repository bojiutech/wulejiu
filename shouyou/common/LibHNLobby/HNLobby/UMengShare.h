#ifndef __UMeng_Share_h__
#define __UMeng_Share_h__

#include "cocos2d.h"
#include "HNOpenExport.h"
#include "HNNetExport.h"
#include "HNLobbyExport.h"

USING_NS_CC;
namespace HN
{
	class UMengShare
	{
	public:
		//打开友盟分享组件(邀请/炫耀)
        static void screenShoot(const std::string& gameName, const std::string& deskPassword, bool bShow = false, int platform = -1);

	public:
		// 快速分享（邀请好友）
		static void doFastShare(const std::string& gameName, const std::string& deskPassword);

		// 快速分享图片(结算榜)
		static void doFastShareImage(const std::string& gameName, const std::string& deskPassword);
	};
}


#endif // __UMeng_Share_h__