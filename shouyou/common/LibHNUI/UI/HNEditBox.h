#ifndef __libCommon_HNEditBox_h__
#define __libCommon_HNEditBox_h__

#include "cocos2d.h"
#include <string>
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

namespace HN
{

	class HNEditBox : public ui::EditBox
	{
	public:
		//ʹ�÷���������1Ϊ�༭���ϰڷŵ�����򣬲���2Ϊʹ������������࣬��Ҫ�̳���ui::EditBoxDelegate
		static HNEditBox* createEditBox(TextField* module, ui::EditBoxDelegate* pDelegate);

	private:
		HNEditBox(); 
		virtual ~HNEditBox();

	public:
		bool init(TextField* module, ui::EditBoxDelegate* pDelegate);
		//�������������
		void setString(std::string text);
		//��ȡ���������
		std::string getString();
		//��ȡ��������ݳ���
		int getStringLength();
		//�����Ƿ���ʾ����
		void setPasswordEnabled(bool enable);
		//��ѯ�Ƿ���ʾ����
		bool isPasswordEnabled();
	};

}
#endif // __libCommon_HNEditBox_h__
