#include <Trappist-1\ui\widgets\CheckButtonGroup.hpp>

#include <Trappist-1\ui\widgets\CheckButton.hpp>

namespace ui
{
	CheckButtonGroup::CheckButtonGroup()
		: BASE()
	{  }

	CheckButtonGroup::~CheckButtonGroup() {  }

	void CheckButtonGroup::addChild(CheckButton &child)
	{
		child.setParent(this);
		child.checkButtonGroup = this;
		childCheckButtons.insert(&child);
	}

	void CheckButtonGroup::removeChild(CheckButton &child)
	{
		child.setParent(nullptr);
		child.checkButtonGroup = nullptr;
		childCheckButtons.erase(&child);
	}

	void CheckButtonGroup::performSubmittion(Renderer2D &renderer2d) const
	{
		BASE::performSubmittion(renderer2d);

		for (Widget *childCheckButton : childCheckButtons)
			childCheckButton->submit(renderer2d);
	}
}