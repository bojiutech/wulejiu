#ifndef __FontConfig_H__
#define __FontConfig_H__

#include "cocos2d.h"

USING_NS_CC;

extern Color3B colorGold;          //��ɫ
extern Color3B colorYellow;        //��ɫ
extern Color3B colorGreen;		   //��ɫ
extern Color3B colorMagenta;	   //�Ϻ�ɫ
extern Color3B colorBlue;		   //��ɫ
extern Color3B colorOrange;        //��ɫ
extern Color3B colorWhite;         //��ɫ
extern Color3B colorRed;           //��ɫ
extern Color3B colorBlack;         //��ɫ
extern Color3B colorGray;          //��ɫ

Label* createLabel(const std::string& text, float fontSize, Color3B color = colorGold);

#endif	//__FontConfig_H__
                                                  