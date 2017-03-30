#include "Cherry97GameAudio.h"
#include "HNUIExport.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

namespace Cherry97
{

	void GameAudio::playBackground()
	{
		HNAudioEngine::getInstance()->playBackgroundMusic("Cherry97/audio/backgroundmusic.mp3", true);
	}

	void GameAudio::stopBackground()
	{
		HNAudioEngine::getInstance()->stopBackgroundMusic();
	}

	////////////////////////////////////////////////////////////////////////////////////////
	void GameAudio::playRoll()
	{
		stopOtherEffect();
		HNAudioEngine::getInstance()->playEffect("Cherry97/audio/fruitroll.mp3");
	}
	void GameAudio::playLine()
	{
		stopOtherEffect();
		HNAudioEngine::getInstance()->playEffect("Cherry97/audio/hasline.mp3");
	}
	void GameAudio::playAward()
	{
		stopOtherEffect();
		HNAudioEngine::getInstance()->playEffect("Cherry97/audio/award.mp3");
	}
	void GameAudio::playwin()
	{
		stopOtherEffect();
		HNAudioEngine::getInstance()->playEffect("Cherry97/audio/ying.mp3");
	}
	void GameAudio::playlose()
	{
		stopOtherEffect();
		HNAudioEngine::getInstance()->playEffect("Cherry97/audio/shu.mp3");
	}
	void GameAudio::playBtn()
	{
		stopOtherEffect();
		HNAudioEngine::getInstance()->playEffect("Cherry97/audio/btn.mp3");
	}
	void GameAudio::playSpecial()
	{
		stopOtherEffect();
		HNAudioEngine::getInstance()->playEffect("Cherry97/audio/reels.mp3");
	}
	void GameAudio::playAddMoney()
	{
		stopOtherEffect();
		HNAudioEngine::getInstance()->playEffect("Cherry97/audio/gold.mp3");
	}
	void GameAudio::stopOtherEffect()
	{
		SimpleAudioEngine::getInstance()->stopAllEffects();
	}
}
