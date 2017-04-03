#include <Trappist-1\ui\actions\Vec4Action.hpp>

#include <Trappist-1\ui\widgets\Widget.hpp>
#include <Trappist-1\ui\widgets\Label.hpp>

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
		case Type::TEXT_RGBA_TO:
			startValue = static_cast<Label*>(target)->getTextColor();
			endValue = inputValue;
			break;
		case Type::TEXT_RGBA_BY:
			startValue = static_cast<Label*>(target)->getTextColor();
			endValue = startValue + inputValue;
			break;
		case Type::TEXT_OUTLINE_RGBA_TO:
			startValue = static_cast<Label*>(target)->getTextOutlineColor();
			endValue = inputValue;
			break;
		case Type::TEXT_OUTLINE_RGBA_BY:
			startValue = static_cast<Label*>(target)->getTextOutlineColor();
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
		case Type::TEXT_RGBA_TO:
		case Type::TEXT_RGBA_BY:
			static_cast<Label*>(target)->setTextColor(startValue + (endValue - startValue) * percent);
			break;
		case Type::TEXT_OUTLINE_RGBA_TO:
		case Type::TEXT_OUTLINE_RGBA_BY:
			static_cast<Label*>(target)->setTextOutlineColor(startValue + (endValue - startValue) * percent);
			break;
		}
	}
}