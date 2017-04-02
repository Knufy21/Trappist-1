#pragma once

#include "Trappist-1\ui\widgets\Widget.hpp"
#include <unordered_set>

namespace ui
{
	class CheckButton;
	class CheckButtonGroup : public Widget
	{
		using BASE = Widget;
	public:
		CheckButtonGroup();
		virtual ~CheckButtonGroup();

		virtual void addChild(CheckButton &child);
		virtual void removeChild(CheckButton &child);

		virtual void onCheckButtonCheckChanged(CheckButton &checkButton) = 0;
	protected:
		virtual void performSubmittion(Renderer2D &renderer2d) const override;

		std::unordered_set<CheckButton*> childCheckButtons;
	private:
	};
}