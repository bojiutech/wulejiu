#ifndef __Cherry97_GAME_AUDIO_H__
#define __Cherry97_GAME_AUDIO_H__

#include <string>

namespace Cherry97
{

	class GameAudio
	{
	public:
		static void playBackground();
		static void stopBackground();

		static void playRoll();
		static void playLine();
		static void playAward();
		static void playwin();
		static void playlose();
		static void playBtn();
		static void playSpecial();
		static void stopOtherEffect();
		static void playAddMoney();
	};
}


#endif