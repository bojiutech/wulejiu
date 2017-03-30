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
		//处理游戏结算后的数据
		virtual void setGameEndData() = 0;
		//向服务器发送游戏结束的消息
		virtual void sendGameOver() = 0;
		//发送查看下一页数据的消息
		virtual void sendNextPageReq() = 0;
		//发送查看上一页数据的消息
		virtual void sendLastPageReq() = 0;

		//保存中奖的线条
		virtual void saveWinLine(bool winLine[8]) = 0;
		//处理彩金
		virtual void setWinnings(LLONG allHandsel) = 0;
		//设置按钮状态
		virtual void setBtnState(bool isvisible) = 0;
		//设置自己的金币
		virtual void setMyMoney(LLONG money) = 0;
		//设置掉线提示
		virtual void setOnConnect() = 0;
		//设置提示文本
		virtual void setPromptText(const std::string& prompt) = 0;
		virtual void dealLeaveDesk() = 0;
		//设置开始前数据清空
		virtual void setGameStartData() = 0;
		//设置上分的结果显示
		virtual void setOnResult(int money) = 0;
		//保存游戏最高单线投注额
		virtual void setMaxLineBet(int bet) = 0;
		//保存开奖图形的数据
		virtual void setImageType(int imageType[9]) = 0;
		//记录时候有二次奖励
		virtual void setSecondGetMoney(int secondMoney) = 0;
		virtual int getSecondGetMoney() = 0;
		//保存玩家输赢分数
		virtual void setWinMoney(int money) = 0;
		//保存单机彩金
		virtual void saveSinglePond(LLONG money) = 0;
		//跑马灯运动动画
		virtual void setRunCell() = 0; 
		//显示广播
		virtual void showRadio(const std::string& str) = 0;
		//显示查看大奖
		virtual void showCheckPrize(int AllCount[18]) = 0;
		//显示下一页大奖界面
		virtual void showCheckPrizeNext(UINT AllCount[12]) = 0;
		//添加开场动画
		virtual void addStartGameAnimate() = 0;
		//判断游戏是否为全盘
		virtual void isAllGame(bool isAll) = 0;
		//判断游戏类型（是否为常规游戏）
		virtual void setGameRule(BYTE rule) = 0;
		//特殊玩法剩余局数
		virtual void setSpecialRestCount(BYTE count) = 0;
		//特殊玩法总局数
		virtual void setSpecialCount(BYTE count) = 0;
		//特殊玩法时，显示特殊玩法倍数的图片
		virtual void setSpecialRateImage(BYTE rate) = 0;
		//设置奖励分数
		virtual void setAward(int score) = 0;
		//保存玩家总筹码
		virtual void setAllHandOff(int handoff) = 0;
		//设置7的个数
		virtual void set7Count(int count) = 0;

		//设置服务端回应的游戏结束
		virtual void setGameOver(bool isOver) = 0;
		//保存所得的单机彩金
		virtual void setSingleWinnings(LLONG winning) = 0;
		//保存所得的总彩金
		virtual void setAllWinnings(LLONG winning) = 0;
		//显示断线进来的彩金
		virtual void setHandsel(LLONG winning, LLONG allwinning) = 0;

		virtual void setRoomInfo(char szRootName[64], BYTE deskId) = 0;
		
		virtual void setShareAward(int iShareAward) = 0;
	};
}


#endif