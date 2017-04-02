#pragma once

#include "Trappist-1\ui\widgets\Widget.hpp"
#include <unordered_set>

namespace ui
{
	class Group : public Widget
	{
		using BASE = Widget;
	public:
		Group();
		virtual ~Group();

		virtual void addChild(Widget &child);
		virtual void removeChild(Widget &child);

	protected:
		virtual void performSubmittion(Renderer2D &renderer2d) const override;

	private:
		std::unordered_set<Widget*> childWidgets;
	};
}