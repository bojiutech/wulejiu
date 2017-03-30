/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#ifndef PlatformConfig_h__
#define PlatformConfig_h__

#include "cocos2d.h"
#include <string>

USING_NS_CC;

class PlatformConfig
{
public:
	enum ACCOUNT_TYPE
	{
		UNKNOWN = 0,
		GUEST,
		NORMAL
	};

	enum PLATFORM_TYPE
	{
		CLASSIC = 0,	//经典版
		LITE,			//精简版
		LUXURY			//豪华版
	};

	enum SCENE_STATE
	{
		INPLATFORM,		//当前场景在大厅中
		INROOM,			//当前场景在房间中
		INGAME,			//当前场景在游戏中
		OTHER
	};
public:
	// 获取配置单例
	static PlatformConfig* getInstance();

	// 销毁配置单例
	static void destroyInstance();

	// 获取更新检测地址
	std::string getAppInfoUrl();

	// 获取推广员地址
	std::string getPromoterUrl();

	// 获取iOS在线安装地址
	std::string getOnlineInstallUrl_iOS(const std::string& url);

	// 获取苹果内购后台验证地址
	std::string getPayCallbackUrl_iOS();

	// 获取公告地址
	std::string getNoticeUrl();

	// 获取商品列表地址
	std::string getGoodsListUrl(const std::string& platForm_Type);

	// 获取订单信息接口地址
	std::string getOrderUrl();

	// 获取兑换奖品地址
	std::string getPrizeUrl();

	// 获取分享地址
	std::string getShareUrl(int id);

	// 获取用户协议地址
	std::string getProtocolUrl();

	// 获取客服信息
	std::string getEditUrl();

	// 获取语音地址
	std::string getVoiceUrl();

	// 获取支付回到地址
	//std::string getPayCallbackUrl_iOS();

	// APP授权码
	CC_SYNTHESIZE_PASS_BY_REF(std::string, _appKey, AppKey);

	// APP类型id
	CC_SYNTHESIZE_PASS_BY_REF(int, _appId, AppId);

	// 游戏logo
	CC_SYNTHESIZE_PASS_BY_REF(std::string, _gameLogo, GameLogo);

	// 过程动画图片
	CC_SYNTHESIZE_PASS_BY_REF(std::string, _splashLogo, SplashLogo);

	// 游戏设计尺寸
	CC_SYNTHESIZE_PASS_BY_REF(cocos2d::Size, _gameDesignSize, GameDesignSize);

	// 平台设计尺寸
	CC_SYNTHESIZE_PASS_BY_REF(cocos2d::Size, _platformDesignSize, PlatformDesignSize);

	// 获取登陆玩家类型（正常的还是游客）
	CC_SYNTHESIZE_PASS_BY_REF(ACCOUNT_TYPE, _accountType, AccountType);

	// 获取平台类型类型（经典版，精简版，豪华版）
	CC_SYNTHESIZE_PASS_BY_REF(PLATFORM_TYPE, _platformType, PlatformType);

	// 玩家当前场景状态（平台，房间，游戏）
	CC_SYNTHESIZE_PASS_BY_REF(SCENE_STATE, _sceneState, SceneState);

	// plist下载地址
	CC_SYNTHESIZE_PASS_BY_REF(std::string, _downloadPlistUrl, DownloadPlistUrl);

	// 是否IAP支付(苹果平台才有效）
	bool isIAP() const { return _isIAP; }

	// 是否pc启动
	CC_SYNTHESIZE_PASS_BY_REF(bool, _isStartFromPC, IsStartFromPC);

protected:
	// 生成Http完整路径
	std::string buildHttp(const std::string& url, const std::string& path);

	// 生成Https完整路径
	std::string buildHttps(const std::string& url, const std::string& path);

	// 构造函数
	PlatformConfig();

	// 析构函数
	~PlatformConfig();

	// 是否IAP支付
	bool _isIAP;
};

#endif // PlatformConfig_h__
