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
		//��ʱ��������ͼƬ��ʼת��
		void setPlay(float dt);
		//��ʱ��������ͼƬֹͣת��
		void setStop(float dt);
		//���������
		void setCell();
		//���ø��ڵ�ͼƬ
		void setImage(Layout* pande[9]);

	public:
		Layout* _panel[9];//�ü���
		ImageView* _panelImage[9][2];
		float _time;
		float _levelTime[3];
		float _runTime;//�ܵ�ʱ��
		ImageView* _rollImage[2];//����ͼ
		int _saveImageResult[9];//�������տ����������
		int _rollNum;//���ôӵ�_rollNum��ͼ��ʼ����

		//��ȡ������ͼƬ
		void showRollImage();
		//��������ͼƬλ��
		void setRollImagePos(int num);
		//�������Ҫ��ʾ������ͼ
		void setImageResult(int imageTexture[9]);
		//�òü����е�ͼƬ���ֹͣ
		void setImageStop();
		//2��,3����4�����Ƕ���
		void playStarAni(BYTE star);
		//2��,3����4�����ֶ���
		void playNumAni(BYTE star);
		//�������������Ƕ�����
		void playCompleteAni();

		//��ȡ�Ƿ�����ֹͣ
		void setIsStop(bool isStop);
	};
}
#endif



