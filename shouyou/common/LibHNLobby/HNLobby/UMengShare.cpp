#include "UMengShare.h"

USING_NS_UM_SOCIAL;

namespace HN
{
	void UMengShare::screenShoot(const std::string& gameName, const std::string& deskPassword, bool bShow, int platform)
	{
		//设置分享链接
		std::string shareUrl = PlatformConfig::getInstance()->getShareUrl(66);
		//设置分享标题
		std::string buffer = "";
		buffer.append("【房号：");
		buffer.append(deskPassword.c_str());
		buffer.append("】舞乐久-");
		buffer.append(gameName.c_str());
		std::string shareTitile = GBKToUtf8(buffer.c_str());

		//设置分享内容
		std::string content = "";
		content.append("我在舞乐久的“");
		content.append(gameName.c_str());
		content.append("”, ");
		content.append(deskPassword.c_str());
		content.append("号房间游戏，快来一起玩吧！");
		//sprintf(buffer, "我在红鸟游戏的“%s”, %s号房间游戏，快来一起玩吧！", gameName.c_str(), deskPassword.c_str());
		std::string shareContent = GBKToUtf8(content.c_str());

		if (bShow)
		{
			//设置分享内容
			shareContent = "";
		}

		UMengSocial::getInstance()->onShareCallBack = [=](bool success, int platform, const std::string& errorMsg) {
			if (success)
			{
				
			}
			else
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8(errorMsg.c_str()));
			}
		};	

		UMengSocial::getInstance()->doShare(shareContent, shareTitile, shareUrl, "", platform);
	}

	void UMengShare::doFastShare(const std::string& gameName, const std::string& deskPassword)
	{
		//设置分享链接
		std::string shareUrl = PlatformConfig::getInstance()->getShareUrl(64);
		//设置分享标题
		char buffer[128] = { 0 };
		sprintf(buffer, "【房号：%s】舞乐久-%s", deskPassword.c_str(), gameName.c_str());
		std::string shareTitile = buffer;
		//设置分享内容
		sprintf(buffer, "我在舞乐久的“%s”, %s号房间游戏，快来一起玩吧！", gameName.c_str(), deskPassword.c_str());
		std::string shareContent = buffer;

		UMengSocial::getInstance()->onShareCallBack = [=](bool success, int platform, const std::string& errorMsg) {
			if (success)
			{

			}
			else
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8(errorMsg.c_str()));
			}
		};

		log("##AA %s %s %s ", shareContent.c_str(), shareTitile.c_str(), shareUrl.c_str());

		UMengSocial::getInstance()->doShare(shareContent, shareTitile, shareUrl, "", 1);
	}

	void UMengShare::doFastShareImage(const std::string& gameName, const std::string& deskPassword)
	{
		//设置分享链接
		std::string shareUrl = PlatformConfig::getInstance()->getShareUrl(64);
		//设置分享标题
		char buffer[128] = { 0 };
		sprintf(buffer, "【房号：%s】结算榜-%s", deskPassword.c_str(), gameName.c_str());
		std::string shareTitile = GBKToUtf8(buffer);
		//std::string shareTitile = "";
		//设置分享内容
		std::string shareContent = "";

		UMengSocial::getInstance()->onShareCallBack = [=](bool success, int platform, const std::string& errorMsg) {
			if (success)
			{

			}
			else
			{
				GamePromptLayer::create()->showPrompt(GBKToUtf8(errorMsg.c_str()));
			}
		};

		UMengSocial::getInstance()->doShare("", shareTitile, shareUrl, "", -1);
	}
}