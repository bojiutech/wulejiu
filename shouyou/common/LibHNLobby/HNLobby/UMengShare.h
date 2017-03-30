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
		//�����˷������(����/��ҫ)
        static void screenShoot(const std::string& gameName, const std::string& deskPassword, bool bShow = false, int platform = -1);

	public:
		// ���ٷ���������ѣ�
		static void doFastShare(const std::string& gameName, const std::string& deskPassword);

		// ���ٷ���ͼƬ(�����)
		static void doFastShareImage(const std::string& gameName, const std::string& deskPassword);
	};
}


#endif // __UMeng_Share_h__