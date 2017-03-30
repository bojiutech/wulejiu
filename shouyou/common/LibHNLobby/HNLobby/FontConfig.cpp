#include "FontConfig.h"                                     

Color3B colorGold(255, 215, 72);                               //��ɫ
Color3B colorYellow(255, 255, 0);                              //��ɫ
Color3B colorGreen(0, 255, 0);								   //��ɫ
Color3B colorMagenta(255, 0, 255);							   //�Ϻ�ɫ
Color3B colorBlue(0, 0, 255);								   //��ɫ
Color3B colorOrange(255, 165, 0);                              //��ɫ
Color3B colorWhite(255, 255, 255);                             //��ɫ
Color3B colorRed(255, 0, 0);                                   //��ɫ
Color3B colorBlack(0, 0, 0);                                   //��ɫ
Color3B colorGray(128, 128, 128);                              //��ɫ

Label* createLabel(const std::string& text, float fontSize, Color3B color)
{	
	Label* label = Label::createWithSystemFont(text, "", fontSize);
	label->setColor(color);
	return label;
}
