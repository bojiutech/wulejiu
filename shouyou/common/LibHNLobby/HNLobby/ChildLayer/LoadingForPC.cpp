#include "LoadingForPC.h"

namespace HN 
{
	Scene* LoadingForPC::createScene(int port)
	{
		auto scene = Scene::create();
		auto layer = LoadingForPC::create(port);
		scene->addChild(layer);
		return scene;
	}

	LoadingForPC* LoadingForPC::create(int port)
	{
		LoadingForPC* layer = new LoadingForPC();
		if (layer && layer->init(port))
		{
			layer->autorelease();
			return layer;
		}
		CC_SAFE_DELETE(layer);
		return layer;
	}

	LoadingForPC::LoadingForPC()
		: _label(nullptr)
		, _port(-1)
	{
		_logic = new HNPCStartLogic(this);
	}

	LoadingForPC::~LoadingForPC()
	{
		HN_SAFE_DELETE(_logic);
	}

	bool LoadingForPC::init(int port)
	{
		if (!HNLayer::init())
		{
			return false;
		}

		_port = port;

		loadUI();

		addTestMenu();
		//startConnect(_port);

		return true;
	}

	void LoadingForPC::startConnect(int port)
	{
		_logic->start();
		_logic->connect("127.0.0.1", port);
	}


	void LoadingForPC::loadUI()
	{
		auto background = Sprite::create("platform/hallBg.png");
		background->setPosition(_winSize.width / 2, _winSize.height / 2);
		this->addChild(background);

		auto label = Label::createWithSystemFont(GBKToUtf8("正在进行界面初始化，请耐心等候。"), "", 28);
		label->setColor(Color3B::RED);
		label->setPosition(_winSize.width / 2, _winSize.height / 3 + 20);
		this->addChild(label, 2);
		_label = label;
	}

	void LoadingForPC::addTestMenu()
	{
		auto btnText = Label::createWithSystemFont(GBKToUtf8("连接"), "", 28);
		btnText->setColor(Color3B::BLACK);
		auto menuItem = MenuItemLabel::create(btnText);
		menuItem->setCallback(CC_CALLBACK_1(LoadingForPC::onStartClick, this));

		auto menu = Menu::create(menuItem, nullptr);
		menu->setPosition(_winSize.width / 2, _winSize.height / 3 - 40);
		this->addChild(menu, 2);

		std::string str = StringUtils::format(GBKToUtf8("连接端口号：%d"), _port);
		_label->setString(str.c_str());
	}

	void LoadingForPC::onStartClick(Ref* pRef)
	{
		startConnect(_port);
	}


	void LoadingForPC::onStartGameError(const std::string& message)
	{

	}
}