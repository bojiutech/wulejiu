#ifndef __Cherry97GameCell_H__
#define __Cherry97GameCell_H__

#include "HNBaseType.h"
#include "HNUIExport.h"

namespace Cherry97
{
	class GameCell: public HN::HNSprite
	{
	public:
		GameCell();
		~GameCell();
		static GameCell* create();
		bool init();
		//定时器，设置图片开始转动
		void setPlay(float dt);
		//定时器，设置图片停止转动
		void setStop(float dt);
		//控制跑马灯
		void setCell();
		//设置父节点图片
		void setImage(Layout* pande[9]);

	public:
		Layout* _panel[9];//裁剪层
		ImageView* _panelImage[9][2];
		float _time;
		float _levelTime[3];
		float _runTime;//跑的时间
		ImageView* _rollImage[2];//滚动图
		int _saveImageResult[9];//保存最终开奖结果类型
		int _rollNum;//设置从第_rollNum个图开始滚动

		//获取滚动的图片
		void showRollImage();
		//滚动设置图片位置
		void setRollImagePos(int num);
		//保存最后要显示的纹理图
		void setImageResult(int imageTexture[9]);
		//让裁剪层中的图片逐个停止
		void setImageStop();
		//2倍,3倍，4倍明星动画
		void playStarAni(BYTE star);
		//2倍,3倍，4倍数字动画
		void playNumAni(BYTE star);
		//播放完整的明星动画、
		void playCompleteAni();

		//获取是否立即停止
		void setIsStop(bool isStop);
	};
}
#endif



