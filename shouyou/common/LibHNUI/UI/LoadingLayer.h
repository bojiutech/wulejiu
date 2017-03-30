/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#ifndef __libCommon_LoadingLayer_h__
#define __libCommon_LoadingLayer_h__

#include "Base/HNLayer.h"
#include <string>

namespace HN
{

	class LoadingLayer : public HNLayer
	{
	public:
		// 创建loading
		static LoadingLayer* createLoading(Node* parent, const std::string& text, float fontSize);
		static LoadingLayer* createLoading(Node* parent, const std::string& text, float fontSize, const std::string& image);
		static LoadingLayer* createLoading(const std::string& text, float fontSize, const std::string& image, const std::string& image_bg);

		static void removeLoading(Node* parent);		
		virtual bool init() override;
		void setText(const std::string& text);
		CREATE_FUNC(LoadingLayer);	
	protected:
		// 创建界面
		void createDialog(const std::string& text, float fontSize, const std::string& image, bool rotate = false);
		void createDialog(const std::string& text, float fontSize, const std::string& image, const std::string& image_bg);
	private:
		Label*	_label;
		LoadingLayer();
		virtual ~LoadingLayer();
	};

}
#endif // __libCommon_LoadingLayer_h__
