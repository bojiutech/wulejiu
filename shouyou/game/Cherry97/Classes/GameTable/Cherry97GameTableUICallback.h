#ifndef __Cherry97_Game_Table_UI_Callback_H__
#define __Cherry97_Game_Table_UI_Callback_H__

#include "HNNetExport.h"
#include "Cherry97MessageHead.h"
#include "HNLogicExport.h"

namespace Cherry97
{
	class GameTableUICallback : public HN::IHNGameLogicBase
	{
	public:
		//������Ϸ����������
		virtual void setGameEndData() = 0;
		//�������������Ϸ��������Ϣ
		virtual void sendGameOver() = 0;
		//���Ͳ鿴��һҳ���ݵ���Ϣ
		virtual void sendNextPageReq() = 0;
		//���Ͳ鿴��һҳ���ݵ���Ϣ
		virtual void sendLastPageReq() = 0;

		//�����н�������
		virtual void saveWinLine(bool winLine[8]) = 0;
		//����ʽ�
		virtual void setWinnings(LLONG allHandsel) = 0;
		//���ð�ť״̬
		virtual void setBtnState(bool isvisible) = 0;
		//�����Լ��Ľ��
		virtual void setMyMoney(LLONG money) = 0;
		//���õ�����ʾ
		virtual void setOnConnect() = 0;
		//������ʾ�ı�
		virtual void setPromptText(const std::string& prompt) = 0;
		virtual void dealLeaveDesk() = 0;
		//���ÿ�ʼǰ�������
		virtual void setGameStartData() = 0;
		//�����ϷֵĽ����ʾ
		virtual void setOnResult(int money) = 0;
		//������Ϸ��ߵ���Ͷע��
		virtual void setMaxLineBet(int bet) = 0;
		//���濪��ͼ�ε�����
		virtual void setImageType(int imageType[9]) = 0;
		//��¼ʱ���ж��ν���
		virtual void setSecondGetMoney(int secondMoney) = 0;
		virtual int getSecondGetMoney() = 0;
		//���������Ӯ����
		virtual void setWinMoney(int money) = 0;
		//���浥���ʽ�
		virtual void saveSinglePond(LLONG money) = 0;
		//������˶�����
		virtual void setRunCell() = 0; 
		//��ʾ�㲥
		virtual void showRadio(const std::string& str) = 0;
		//��ʾ�鿴��
		virtual void showCheckPrize(int AllCount[18]) = 0;
		//��ʾ��һҳ�󽱽���
		virtual void showCheckPrizeNext(UINT AllCount[12]) = 0;
		//��ӿ�������
		virtual void addStartGameAnimate() = 0;
		//�ж���Ϸ�Ƿ�Ϊȫ��
		virtual void isAllGame(bool isAll) = 0;
		//�ж���Ϸ���ͣ��Ƿ�Ϊ������Ϸ��
		virtual void setGameRule(BYTE rule) = 0;
		//�����淨ʣ�����
		virtual void setSpecialRestCount(BYTE count) = 0;
		//�����淨�ܾ���
		virtual void setSpecialCount(BYTE count) = 0;
		//�����淨ʱ����ʾ�����淨������ͼƬ
		virtual void setSpecialRateImage(BYTE rate) = 0;
		//���ý�������
		virtual void setAward(int score) = 0;
		//��������ܳ���
		virtual void setAllHandOff(int handoff) = 0;
		//����7�ĸ���
		virtual void set7Count(int count) = 0;

		//���÷���˻�Ӧ����Ϸ����
		virtual void setGameOver(bool isOver) = 0;
		//�������õĵ����ʽ�
		virtual void setSingleWinnings(LLONG winning) = 0;
		//�������õ��ܲʽ�
		virtual void setAllWinnings(LLONG winning) = 0;
		//��ʾ���߽����Ĳʽ�
		virtual void setHandsel(LLONG winning, LLONG allwinning) = 0;

		virtual void setRoomInfo(char szRootName[64], BYTE deskId) = 0;
		
		virtual void setShareAward(int iShareAward) = 0;
	};
}


#endif