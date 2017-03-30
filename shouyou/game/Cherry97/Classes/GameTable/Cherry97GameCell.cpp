#include "Cherry97GameCell.h"
#include "Cherry97MessageHead.h"
#include "Cherry97GameAudio.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include <string>
#include <ctime>

using namespace ui;
using namespace std;
using namespace HN;

namespace Cherry97
{

	GameCell::GameCell():_time(3.0f), _rollNum(0)
	{
		
	}

	GameCell::~GameCell()
	{
	}

	GameCell* GameCell::create()
	{
		GameCell* gameCell = new GameCell();
		if (gameCell->init())
		{
			gameCell->autorelease();
			return gameCell;
		}
		else
		{
			CC_SAFE_DELETE(gameCell);
			return nullptr;
		}
	}

	bool GameCell::init()
	{
		if (!HNSprite::init())
		{
			return false;
		}
		srand(time(NULL));
		return true;
	}

	void GameCell::setPlay(float dt)
	{
		setRollImagePos(0);
		//每一次进这个函数，就让图片下移22
		_runTime += dt;
		if (_runTime >= _time)
		{
			unschedule(schedule_selector(GameCell::setPlay));
			_rollNum = 0;
			schedule(schedule_selector(GameCell::setStop), 0.03f);
		}
	}

	void GameCell::setStop(float dt)
	{
		setImageStop();
		_rollNum++;
	}


	//设置图片时间和开始转动图片
	void GameCell::setCell()
	{
		_runTime = 0.0f;
		schedule(schedule_selector(GameCell::setPlay), 0.03f);
	}

	//设置9个裁剪层的图片
	void GameCell::setImage(Layout* panel[9])
	{
		for (int i = 0; i < 9; i++)
		{
			_panel[i] = panel[i];
		}
	}

	//获取滚动的图片
	void GameCell::showRollImage()
	{
		char str[50];
		for (int i = 0; i < 9; i++)//i代表9个滚动区域
		{
			for (int j = 0; j < 2; j++)//j代表一个滚动区域的两张图
			{
				sprintf(str, "Image_roll_%d", j);
				_panelImage[i][j] = (ImageView* ) _panel[i]->getChildByName(str);
				//_panelImage[i][j]->setScale(0.5);
			}
		}
	}

	//滚动设置图片位置
	void GameCell::setRollImagePos(int num)
	{
		char str[50];
		for (int i = num; i < 9; i++)//i代表9个滚动区域
		{
			for (int j = 0; j < 2; j++)//j代表一个滚动区域的两张图
			{
				_panelImage[i][j]->setPositionY(_panelImage[i][j]->getPositionY()-30);
				if (_panelImage[i][j]->getPositionY() <= 0)//判断图片是否完全超出裁剪层
				{
					//int currentScale = _panelImage[i][j]->getScale();

					//随机获取一张图片
					int n = rand() % 9;
					sprintf(str, "Cherry97/zhuapantu/tu_%d.png", n);
					_panelImage[i][j]->loadTexture(str);
					_panelImage[i][j]->setPositionY(_panelImage[i][j]->getContentSize().height*2);//将图片高设置在裁剪层的上面

					_panelImage[i][j]->setScale(0.75);
				}
			}
		}
	}

	//保存最后要显示的纹理图
	void GameCell::setImageResult(int imageTexture[9])
	{
		for (int i = 0; i < 9; i++)
		{
			_saveImageResult[i] = imageTexture[i];
		}
	}

	//让裁剪层中的图片逐个停止
	void GameCell::setImageStop()
	{
		if (_rollNum < 9)
		{
			setRollImagePos(_rollNum);
			CCLOG("************** %d ************", _rollNum);
			char str[32];
			sprintf(str, "Cherry97/zhuapantu/tu_%d.png", _saveImageResult[_rollNum]);
			_panelImage[_rollNum][0]->loadTexture(str);
			_panelImage[_rollNum][0]->setPositionY(_panelImage[_rollNum][0]->getContentSize().height + 30);
			_panelImage[_rollNum][0]->runAction(JumpTo::create(0.01f, Vec2(_panelImage[_rollNum][0]->getPositionX(), _panelImage[_rollNum][0]->getContentSize().height), -10, 1));
			_panelImage[_rollNum][1]->setPositionY(_panelImage[_rollNum][1]->getContentSize().height*2);
		}
		else
		{
			GameAudio::stopOtherEffect();
			unschedule(schedule_selector(GameCell::setStop));	
		}
	} 

	//2倍,3倍，4倍数字动画
	void GameCell::playNumAni(BYTE star)
	{
		for (int i = 0; i < 9; i++)//i代表9个滚动区域
		{
			for (int j = 0; j < 2; j++)//j代表一个滚动区域的两张图
			{
				_panelImage[i][j]->setPositionY(_panelImage[i][j]->getContentSize().height * 2);
			}
		}
		char str[32];
		sprintf(str, "Cherry97/num_%d.png", star);
		_panelImage[4][0]->loadTexture(str);
		_panelImage[4][0]->setPositionY(_panelImage[4][0]->getContentSize().height * 2);
		_panelImage[4][0]->runAction(Sequence::create(MoveTo::create(0.2f, Vec2(_panelImage[4][0]->getPositionX(), _panelImage[4][0]->getContentSize().height)),
			DelayTime::create(0.5f), CallFunc::create([=](){
				playStarAni(star);
				_panelImage[1][0]->setPositionY(_panelImage[3][0]->getContentSize().height * 2);
		}), nullptr));
	}

	//2倍,3倍，4倍明星动画
	void GameCell::playStarAni(BYTE star)
	{
		char str[32];
		for (int i = 0; i < 9; i++)
		{
			sprintf(str, "Cherry97/star%d/start_%d.png", star, i);
			_panelImage[i][0]->loadTexture(str);
			_panelImage[i][0]->setScale(1);
			_panelImage[i][0]->setPositionY(_panelImage[i][0]->getContentSize().height * 2);
			_panelImage[i][0]->runAction(Sequence::create(MoveTo::create(0.3f, Vec2(_panelImage[i][0]->getPositionX(), _panelImage[i][0]->getContentSize().height)), nullptr));
		}
	}

	//播放完整的明星动画
	void GameCell::playCompleteAni()
	{
		runAction(Sequence::create(CallFunc::create([=](){
			playNumAni(2);
		}), DelayTime::create(2.0f), CallFunc::create([=](){
			playNumAni(3);
		}), DelayTime::create(2.0f), CallFunc::create([=](){
			playNumAni(4);
		}), DelayTime::create(2.0f), CallFunc::create([=](){
			GameAudio::playRoll();
			setCell();
			int iamgeResult[9] = {8, 8, 8, 8, 8, 8, 8, 8, 8};
			setImageResult(iamgeResult);
		}), nullptr));
	}

	//获取是否立即停止
	void GameCell::setIsStop(bool isStop)
	{
		if (!isStop)
		{
			_runTime = _time;
		}
	}

}
