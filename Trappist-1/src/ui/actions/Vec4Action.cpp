#include <Trappist-1\ui\actions\Vec4Action.hpp>

#include <Trappist-1\UI\Widgets\Widget.hpp>

namespace ui
{
	Vec4Action::Vec4Action(Type type, const T &value, float duration, const Interpolation &interpolation)
		: Action(duration, interpolation), type(type), inputValue(value)
	{  }

	Vec4Action::~Vec4Action() {  }

	Action* Vec4Action::clone() const
	{
		return new Vec4Action(*this);
	}

	void Vec4Action::onTargetChanged()
	{
		switch (type)
		{
		case Type::RGBA_TO:
			startValue = target->getColor();
			endValue = inputValue;
			break;
		case Type::RGBA_BY:
			startValue = target->getColor();
			endValue = startValue + inputValue;
			break;
		}
	}

	void Vec4Action::apply(float percent)
	{
		switch (type)
		{
		case Type::RGBA_TO:
		case Type::RGBA_BY:
			target->setColor(startValue + (endValue - startValue) * percent);
			break;
		}
	}
}