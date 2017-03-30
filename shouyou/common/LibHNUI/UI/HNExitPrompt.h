#ifndef __HNExitPrompt_h__
#define __HNExitPrompt_h__

#include "Base/HNLayer.h"
#include "cocos2d.h"

namespace HN
{
	class HNExitPromptLayer : public HN::HNLayer
	{
	public:
		CREATE_FUNC(HNExitPromptLayer);

	public:
		virtual bool init() override;

	public:
		void setExitCallBack(const std::function<void ()>& onExit);

	public:
		void onExitCallBack(Ref* pSender, Widget::TouchEventType type);
		void onCancelCallBack(Ref* pSender, Widget::TouchEventType type);

	protected:
		HNExitPromptLayer();
		~HNExitPromptLayer();

	private:
		std::function<void ()> _onExit;
	};
}

#endif // __HNExitPrompt_h__
