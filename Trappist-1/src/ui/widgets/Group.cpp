#include <Trappist-1\ui\widgets\Group.hpp>

namespace ui
{
	Group::Group()
		: BASE()
	{  }

	Group::~Group() {  }

	void Group::addChild(Widget &child)
	{
		child.setParent(this);
		childWidgets.insert(&child);
	}

	void Group::removeChild(Widget &child)
	{
		child.setParent(nullptr);
		childWidgets.erase(&child);
	}

	void Group::performSubmittion(Renderer2D &renderer2d) const
	{
		BASE::performSubmittion(renderer2d);

		for (Widget *childWidget : childWidgets)
			childWidget->submit(renderer2d);
	}
}