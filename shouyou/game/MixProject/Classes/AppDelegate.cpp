#include "AppDelegate.h"

#include "HNLobbyExport.h"
#include "HNNetExport.h"

#include "json/rapidjson.h"
#include "json/document.h"

/*******************************�����Ϸ****************************************/
// ���ְ����齫
#include "AQMJ_MessageHead.h"
#include "AQMJ_GameTableUI.h"

// ӣ��97
#include "Cherry97MessageHead.h"
#include "Cherry97GameTableUI.h"

// ������
#include "GoBangMessage.h"
#include "GoBangTableUI.h"


/******************************************************************************/

USING_NS_CC;

static const char* GameLogoPath = "platform/game_logo.png";

// ��Ϸ��Ƴߴ�
static cocos2d::Size designResolutionSize = cocos2d::Size(1280, 720);

// ������Կ
static std::string XXTEA_KEY("G9w0BAQEFAASCAl8wgg");

// ������Ȩ��
static std::string APP_INFO_KEY("mixproject-createroom");

// ��Ϸѡ��
struct GameItem
{
	UINT nameId;
	HNGameCreator::GAMETYPE type;
	GAME_CREATE_SELECTOR create;
};

/*******************************�����Ϸ****************************************/
static GameItem GameList[] =
{
	// ���ְ����齫
	{ AQMJ::NAME_ID, HNGameCreator::NORMAL, AQMJ::GameTableUI::create },

	// ӣ��97
	{ Cherry97::NAME_ID, HNGameCreator::NORMAL, Cherry97::GameTableUI::create },

	// ������
	{ GoBang::GAME_NAME_ID, HNGameCreator::NORMAL, GoBang::GameTableUI::create }

};
/******************************************************************************/

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
	//set OpenGL context attributions,now can only set six attributions:
	//red,green,blue,alpha,depth,stencil
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
	return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		Size size = getConfigSize();
		glview = GLViewImpl::createWithRect("Redbird", Rect(0, 0, size.width, size.height));
#else
		glview = GLViewImpl::create("Redbird");
#endif
		director->setOpenGLView(glview);
	}

	// turn on display FPS
	//director->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0f / 60);

	// Set the design resolution
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::FIXED_WIDTH);
	Size frameSize = glview->getFrameSize();
	//glview->setFrameZoomFactor(0.5f);
	register_all_packages();

	initGameConfig();

	Scene * scene = GameInitial::createScene();
	director->runWithScene(scene);

	/*#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		 FastDevelop::createScene();
		 #else
		 Scene * scene = GameInitial::createScene();
		 director->runWithScene(scene);

		 #endif*/
	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	//Director::getInstance()->pause();
	Director::getInstance()->stopAnimation();
	HNAudioEngine::getInstance()->pauseBackgroundMusic();

	Configuration::getInstance()->setValue("bBackground", Value(true));

	// if you use SimpleAudioEngine, it must be pause
	//SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	//Director::getInstance()->resume();
	Director::getInstance()->startAnimation();
	HNAudioEngine::getInstance()->resumeBackgroundMusic();

	Configuration::getInstance()->setValue("bBackground", Value(false));

	// if you use SimpleAudioEngine, it must resume here
	//SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

Size AppDelegate::getConfigSize()
{
	Size size = designResolutionSize;
	do
	{
		std::string filename("config.json");
		if (FileUtils::getInstance()->isFileExist(filename))
		{
			std::string json = FileUtils::getInstance()->getStringFromFile(filename);
			rapidjson::Document doc;
			doc.Parse<rapidjson::kParseDefaultFlags>(json.c_str());
			if (doc.HasParseError() || !doc.IsObject())
			{
				break;
			}

			if (doc.HasMember("width"))
			{
				size.width = doc["width"].GetInt();
			}
			if (doc.HasMember("height"))
			{
				size.height = doc["height"].GetInt();
			}
		}
	} while (0);

	return size;
}

void AppDelegate::initGameConfig()
{
	FileUtils::getInstance()->addSearchPath("Games");
	FileUtils::getInstance()->setXXTeaKey(XXTEA_KEY);
	PlatformConfig::getInstance()->setGameLogo(GameLogoPath);

	// �����Ϸ
	int gameCount = sizeof(GameList) / sizeof(GameItem);
	for (int i = 0; i < gameCount; i++)
	{
		GameCreator()->addGame(GameList[i].nameId, GameList[i].type, GameList[i].create);
	}

	// ������Ϸ��Ȩ��
	PlatformConfig::getInstance()->setAppKey(APP_INFO_KEY);

	// ƽ̨��Ƴߴ�
	PlatformConfig::getInstance()->setPlatformDesignSize(designResolutionSize);

	// ��Ϸ��Ƴߴ�
	PlatformConfig::getInstance()->setGameDesignSize(designResolutionSize);

	// ��ȡ��Ʒ�б�
	ProductManger::getInstance()->addProducts("mixproject");

}