#ifndef __Cherry97_GameAward_H__
#define __Cherry97_GameAward_H__

#include "HNNetExport.h"
#include "HNUIExport.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Cherry97GameTableUICallback.h"

namespace Cherry97
{
	class GameAward : public HN::HNLayer
	{
	public:
		static GameAward* create(GameTableUICallback* uiCallback);
		virtual bool init(GameTableUICallback* uiCallback);
		GameAward();
		virtual ~GameAward();
		//获取奖励分数
		CC_SYNTHESIZE(int ,_awardScore, AwardScore);
		//判断是否显示奖励框
		void showAwardFrame(TextAtlas* allMoney, TextAtlas* ewMoney, TextAtlas* defen, TextAtlas* caijin, LLONG winWinnings, LLONG awardMoney, int winMoney, int secondMoney);
		//显示彩金递减的动画
		void showWinningsSub();
		void showAwardSub();
		void showSecondMoney();
		void showMyAllMoney();
		void updateWinningSub(float dt);
		void updateAwardSub(float dt);
		void updateSecondMoney(float dt);
		void updateAllMoney(float dt);

		//停止所有计时器
		void stopAllSchedule();
	private:
		GameTableUICallback* _uicallback;
		Size winsize;
		Node* _loader;
		Layout* _layout;
		TextAtlas* _TextAward;

		TextAtlas* _textAllMoney;
		TextAtlas* _textEW;
		TextAtlas* _textDefen;
		TextAtlas* _textCaijin;
		int _caijin;
		LLONG _allMoney;
		LLONG _winHandSel;//彩金奖励
		LLONG _awardMoney;//额外奖励
		int _winScore;//得分
		int _secondMoney;//二次奖励分数
		int _stageNum;
		int _keepNUm;//统计减的数量

	};
}
#endif