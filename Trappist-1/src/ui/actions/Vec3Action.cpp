#include <Trappist-1\ui\actions\Vec3Action.hpp>

#include <Trappist-1\UI\Widgets\Widget.hpp>

namespace ui
{
	Vec3Action::Vec3Action(Type type, const T &value, float duration, const Interpolation &interpolation, std::function<void()> onFinish)
		: Action(duration, interpolation, onFinish), type(type), inputValue(value)
	{  }

	Vec3Action::Vec3Action(Type type, const T &value, float duration, std::function<void()> onFinish, const Interpolation &interpolation)
		: Action(duration, interpolation, onFinish), type(type), inputValue(value)
	{  }

	Vec3Action::~Vec3Action() {  }

	Action* Vec3Action::clone() const
	{
		return new Vec3Action(*this);
	}

	void Vec3Action::onTargetChanged()
	{
		switch (type)
		{
		case RGB_TO:
			startValue = T(target->getColor());
			endValue = inputValue;
			break;
		case RGB_BY:
			startValue = T(target->getColor());
			endValue = startValue + inputValue;
			break;
		}
	}

	void Vec3Action::apply(float percent)
	{
		switch (type)
		{
		case RGB_TO:
		case RGB_BY:
			T val(startValue + (endValue - startValue) * percent);
			target->setColor(glm::vec4(val.r, val.g, val.b, target->getColor().a));
			break;
		}
	}
}