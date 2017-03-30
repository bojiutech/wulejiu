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
		//��ȡ��������
		CC_SYNTHESIZE(int ,_awardScore, AwardScore);
		//�ж��Ƿ���ʾ������
		void showAwardFrame(TextAtlas* allMoney, TextAtlas* ewMoney, TextAtlas* defen, TextAtlas* caijin, LLONG winWinnings, LLONG awardMoney, int winMoney, int secondMoney);
		//��ʾ�ʽ�ݼ��Ķ���
		void showWinningsSub();
		void showAwardSub();
		void showSecondMoney();
		void showMyAllMoney();
		void updateWinningSub(float dt);
		void updateAwardSub(float dt);
		void updateSecondMoney(float dt);
		void updateAllMoney(float dt);

		//ֹͣ���м�ʱ��
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
		LLONG _winHandSel;//�ʽ���
		LLONG _awardMoney;//���⽱��
		int _winScore;//�÷�
		int _secondMoney;//���ν�������
		int _stageNum;
		int _keepNUm;//ͳ�Ƽ�������

	};
}
#endif