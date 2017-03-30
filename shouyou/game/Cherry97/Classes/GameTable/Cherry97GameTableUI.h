#ifndef __Cherry97_Game_Table_UI_H__
#define __Cherry97_Game_Table_UI_H__

#include "Cherry97GameTableUICallback.h"
#include "Cherry97GameCell.h"
#include "Cherry97GameAward.h"
#include "Cherry97GameCheckAwardNext.h"
#include "Cherry97GameShare.h"
#include "HNNetExport.h"
#include "HNLobbyExport.h"
#include "cocos2d.h"
#include <vector>

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocostudio;

namespace Cherry97
{
	class GameTableLogic;
	class GameCheckAward;
	class GameCheckAwardNext;
	class GameShare;
	class GameTableUI : public HN::HNGameUIBase, public GameTableUICallback
	{
	public:
		static GameTableUI* create(char bDeskIndex, bool bAutoCreate);
		virtual bool init(char bDeskIndex, bool bAutoCreate);
		GameTableUI();
		virtual ~GameTableUI();	
		virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) override;
		void returnMain();
		BYTE _desk;
		bool _baotoCreate;
	public:
		Node* _loader;
		Layout* _layout;
		ImageView* _mainBg;
		ImageView* _turnBg;
		//�ü���ͼƬ
		Layout* _panelImage[9];
		//8������
		ImageView* _line[8];
		//�Ÿ�ȫ����˸�Ŀ�
		ImageView* _redFrame[9];
		//8��������ע��
		TextAtlas* _aloneBetNum[8];
		//��Ϸ���ư�ť
		Button* _setbtn[6];
		//�˳���ť
		Button* _exitBtn;
		//����ǳ� 
		Text* _userName;
		//����ܽ��
		Text* _userMoney;
		//�����Ϸ������
		TextAtlas* _curHandoff;
		//�������ע
		TextAtlas* _curAllBet;
		//�ʽ�ֵ
		TextAtlas* _handsel;//����ʽ�
		
		TextAtlas* _handselAll;//�ܲʽ�
		Text* _textHandSelAll;

		Text* _textgetHandsel;
		TextAtlas* _getHandsel;//��õ��ܲʽ�
		//��ұ���Ӯ��Ǯ��
		TextAtlas* _curWinMoney;
		//��ұ��ֶ���Ӯ��Ǯ
		TextAtlas* _ewMoney;
		//��ʾ�ı�
		Text* _tTishi;
		//����
		Button* _btnBet;
		//��ʾ���ⱶ����ͼƬ
		ImageView* _specialRate;
		//��ʾ�����淨��ǰ�ľ���
		TextAtlas* _specialCountText;

		Text* m_roomNameText;

		Text* m_deskId;

		int m_shareAward;

		LayerColor* colorLayer;
	private:
		Size winSize;
		GameTableLogic*	_gameTableLogic;
		GameCell* _gameCell;
		GameAward* _gameAward;

		//�㲥����ͼ
		Sprite* _radioFrame;
		GameNotice* _radio;

		Sprite* _tishiSp;

		bool _isOutWait;
		int _maxLineBet;//�������ע��
		int _imageType[9];//���濪����ͼƬ��Ϣ
		int _userWinMoney;//���������Ӯ����
		bool _openAwardLine[8];//����������
		int _curLineBet;//���ֵ�����ע��
		bool _isAuto;//�Ƿ��Զ���Ϸ  true-�ǣ�false-��
		int _curStarBet;//��ǰ���Ǳ���
		bool _isAll;//ת�̽�� true-��ȫ�� false-����ȫ��
		BYTE _gameRule;//0:��������Ϸ  1:����2������  2:����3������  3:����4������
		BYTE _SpecialCount;//�����淨����
		BYTE _SpecialRealCount;//�����淨����
		int _7Count;//7�ĸ���
		int _handOff;//����ʱ����ܵĳ���
		bool _isStart;//�ж���ʾ�Ƿ�Ϊ��Ϸ��
		float _saveRightAwayTime;//���Ƽ��㼴ͣ��ʱ��
		int _saveLineBet;//���浥����ע
		LLONG _singleWinnings;
		LLONG _allWinnings;
		float _dt;//��¼Ҫ�ӳٵ�ʱ��
		int _secondMoney;
		GameCheckAward* _lastaward;
		GameCheckAwardNext* _nextaward;
		LLONG _singlePond;//���浥���ʽ�
	private:
		void getChildNode();
		void BtnCallBack(Ref* pSender, Widget::TouchEventType type);
		void createGameLayer();
		//���õ��ߵ���ע��
		void showAloneLineNum(int aloneNum);
		//�Զ���Ϸ
		void setAutoGame();
		//��ʾ�н�������
		void showWinningLine();
		//�����㲥��
		void addRadioFrame();

		//��Ϸ��������
		virtual void setGameEnd(float dt);

		//������ʾ����������ݣ�׼����һ����Ϸ
		void readyNextGame();

		//�����н������Ĳ㼶
		void setAllLineZorder(int zorder);
		//��������״̬
		void setLineState();
		//���ú��Ĳ㼶
		void setRedFrameZorder(int zorder);
		//���ú�����ʾ״̬
		void setRedFrameState(bool isVisib);
		//���ÿ�ʼ/ֹͣ��ͼƬ״̬
		void setStop();
		void setStart();
		//�����Զ�/ȡ����ͼƬ״̬
		void setAuto();
		void setCancel();

		//��ʾ���ʲ�
		void showBetLayer();
		//��ʾ��Ϸ���ƵĶ���
		void showGameNameAni();
		//��ʾ����ʱ�ı��ʶ���
		void showGameBetAni();
		//��ʾ���Ǳ����Ķ���
		void showStarBetAni();
		//��ʾȫ�̶���
		void showAllGameAni();

		//��ʼ��������Ϣ
		void sendGameStartRoll();
		//���Ƽ��㼴ͣ�ļ�ʱ��
		void setRightAwayStop(float dt);

		//��ʼ����עͼƬ�����Ķ���
		void setPlayStartAndBet();
		//ֹͣ��ʼ����עͼƬ�����Ķ���
		void setStopStartAndBet();

		void showShareAward();
		
	public:
		//������Ϸ����������
		virtual void setGameEndData() override;
		//�������������Ϸ��������Ϣ
		virtual void sendGameOver() override;
		//���Ͳ鿴��һҳ���ݵ���Ϣ
		virtual void sendNextPageReq() override;
		//���Ͳ鿴��һҳ���ݵ���Ϣ
		virtual void sendLastPageReq() override;

		//���ð�ť״̬
		virtual void  setBtnState(bool isvisible) override;
		//���ÿ�ʼǰ�������
		virtual void setGameStartData() override;
		//�����ϷֵĽ����ʾ
		virtual void setOnResult(int money) override;
		//��ӿ�������
		virtual void addStartGameAnimate() override;
		//�����н�������
		virtual void saveWinLine(bool winLine[8]) override;
		//������Ϸ��ߵ���Ͷע��
		virtual void setMaxLineBet(int bet) override;
		//���濪��ͼ�ε�����
		virtual void setImageType(int imageType[9]) override;
		//��¼ʱ���ж��ν���
		virtual void setSecondGetMoney(int secondMoney) override;
		virtual int getSecondGetMoney() override;
		//���������Ӯ����
		virtual void setWinMoney(int money) override;
		virtual int getWinMoney();
		//���浥���ʽ�
		virtual void saveSinglePond(LLONG money) override;
		//��ʼת��
		virtual void setRunCell() override; 
		//����ʽ�
		virtual void setWinnings(LLONG allHandsel) override;
		//�����Լ��Ľ��
		virtual void setMyMoney(LLONG money) override;
		//������ʾ�ı�
		virtual void setPromptText(const std::string& prompt) override;
		//���õ�����ʾ
		virtual void setOnConnect() override;
		//�뿪��Ϸ����������
		virtual void dealLeaveDesk() override;
		//�����˳���Ϸ����ʾ��
		void isPopGame();
		//��ʾ�㲥
		virtual void showRadio(const std::string& str) override;
		//��ʾ�󽱽���
		virtual void showCheckPrize(int AllCount[18]) override;
		//��ʾ��һҳ�󽱽���
		virtual void showCheckPrizeNext(UINT AllCount[12]) override;
		//�ж���Ϸ�Ƿ�Ϊȫ��
		virtual void isAllGame(bool isAll) override;
		virtual bool getAllGame();
		//�ж���Ϸ���ͣ��Ƿ�Ϊ������Ϸ��
		virtual void setGameRule(BYTE rule) override;
		virtual BYTE getGameRule();
		//�����淨����
		virtual void setSpecialRestCount(BYTE count) override;
		//�����淨�ܾ���
		virtual void setSpecialCount(BYTE count) override;
		virtual BYTE getSpecialRestCount();
		//�����淨ʱ����ʾ�����淨������ͼƬ
		virtual void setSpecialRateImage(BYTE rate) override;
		//���ý�������
		virtual void setAward(int score) override;
		//��������ܳ���
		virtual void setAllHandOff(int handoff) override;
		virtual int getAllHandOff();
		//����7�ĸ���
		virtual void set7Count(int count) override;
		virtual int get7Count();

		//���÷���˻�Ӧ����Ϸ����
		virtual void setGameOver(bool isOver) override;
		//�������õĵ����ʽ�
		virtual void setSingleWinnings(LLONG winning) override;
		//�������õ��ܲʽ�
		virtual void setAllWinnings(LLONG winning) override;
		//��ʾ���߽����Ĳʽ�
		virtual void setHandsel(LLONG winning, LLONG allwinning) override;

		virtual void setRoomInfo(char szRootName[64], BYTE deskId) override;

		virtual void setShareAward(int iShareAward) override;
	};
}
#endif