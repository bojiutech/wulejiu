#include "HNEditBox.h"

namespace HN
{

HNEditBox::HNEditBox(void)
{

}


HNEditBox::~HNEditBox(void)
{
}

HNEditBox* HNEditBox::createEditBox(TextField* module, ui::EditBoxDelegate* pDelegate)
{
	HNEditBox* editBox = new HNEditBox();
	if (editBox->init(module, pDelegate))
	{
		editBox->autorelease();
		return editBox;
	}
	else
	{
		CC_SAFE_DELETE(editBox);
		return nullptr;
	}
}

bool HNEditBox::init(TextField* module, ui::EditBoxDelegate* pDelegate)
{
	Size editSize = module->getCustomSize();
	this->initWithSizeAndBackgroundSprite(editSize, Scale9Sprite::create());
	this->setAnchorPoint(module->getAnchorPoint());
	this->setPosition(module->getPosition());
	this->setFontSize(module->getFontSize());
	//this->setFontColor(Color3B(0, 0, 0));
	this->setFontColor(module->getColor());
	this->setPlaceHolder(module->getPlaceHolder().c_str());
	this->setPlaceholderFontColor(module->getPlaceHolderColor());
	if (module->getMaxLength() > 0)
	{
		this->setMaxLength(module->getMaxLength());
	}
	//���ü�����return����ʾ���ַ�
	this->setReturnType(EditBox::KeyboardReturnType::DONE);
	//���������ı�����
	this->setInputMode(EditBox::InputMode::SINGLE_LINE);
	//����ί�д������
	this->setDelegate(pDelegate);
	module->getParent()->addChild(this, module->getLocalZOrder());

	return true;
}

void HNEditBox::setString(std::string text)
{
	this->setText(text.c_str());
}

std::string HNEditBox::getString()
{
	return this->getText();
}

int HNEditBox::getStringLength()
{
	std::string tmp = this->getText();
	return tmp.length();
}

bool HNEditBox::isPasswordEnabled()
{
	if (_editBoxInputFlag == EditBox::InputFlag::PASSWORD)
	{
		return true;
	}
	else 
		return false;
}

void HNEditBox::setPasswordEnabled(bool enable)
{
	if (enable)
	{
		_editBoxInputFlag= EditBox::InputFlag::PASSWORD;
	}
	else
	{
		_editBoxInputFlag = EditBox::InputFlag::INITIAL_CAPS_ALL_CHARACTERS;
	}
	this->setInputFlag(_editBoxInputFlag);
}

}
