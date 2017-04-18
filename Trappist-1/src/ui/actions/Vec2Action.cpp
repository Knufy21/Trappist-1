#include <Trappist-1\ui\actions\Vec2Action.hpp>

#include <Trappist-1\UI\Widgets\Widget.hpp>

namespace ui
{
	Vec2Action::Vec2Action(Type type, const T &value, float duration, const Interpolation &interpolation, std::function<void()> onFinish)
		: Action(duration, interpolation, onFinish), type(type), inputValue(value)
	{  }

	Vec2Action::Vec2Action(Type type, const T &value, float duration, std::function<void()> onFinish, const Interpolation &interpolation)
		: Action(duration, interpolation, onFinish), type(type), inputValue(value)
	{  }

	Vec2Action::~Vec2Action() {  }

	Action* Vec2Action::clone() const
	{
		return new Vec2Action(*this);
	}

	void Vec2Action::onTargetChanged()
	{
		switch (type)
		{
		case MOVE_TO:
			startValue = target->getPosition();
			endValue = inputValue;
			break;
		case SIZE_TO:
			startValue = T(target->getLocalBounds().width, target->getLocalBounds().height);
			endValue = inputValue;
			break;
		case SCALE_TO:
			startValue = target->getScale();
			endValue = inputValue;
			break;
		case MOVE_BY:
			startValue = target->getPosition();
			endValue = startValue + inputValue;
			break;
		case SIZE_BY:
			startValue = T(target->getLocalBounds().width, target->getLocalBounds().height);
			endValue = startValue + inputValue;
			break;
		case SCALE_BY:
			startValue = target->getScale();
			endValue = startValue + inputValue;
			break;
		}
	}

	void Vec2Action::apply(float percent)
	{
		switch (type)
		{
		case MOVE_TO:
		case MOVE_BY:
			target->setPosition(startValue + (endValue - startValue) * percent);
			break;
		case SIZE_TO:
		case SIZE_BY:
			target->setSize(startValue + (endValue - startValue) * percent);
			break;
		case SCALE_TO:
		case SCALE_BY:
			target->setScale(startValue + (endValue - startValue) * percent);
			break;
		}
	}
}