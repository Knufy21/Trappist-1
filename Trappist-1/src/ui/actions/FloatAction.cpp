#include <Trappist-1\ui\actions\FloatAction.hpp>

#include <Trappist-1\UI\Widgets\Widget.hpp>

namespace ui
{
	FloatAction::FloatAction(Type type, T value, float duration, const Interpolation &interpolation, std::function<void()> onFinish)
		: Action(duration, interpolation, onFinish), type(type), inputValue(value)
	{  }

	FloatAction::FloatAction(Type type, T value, float duration, std::function<void()> onFinish, const Interpolation &interpolation)
		: Action(duration, interpolation, onFinish), type(type), inputValue(value)
	{  }

	FloatAction::~FloatAction() {  }

	Action* FloatAction::clone() const
	{
		return new FloatAction(*this);
	}

	void FloatAction::onTargetChanged()
	{
		switch (type)
		{
		case ALPHA_TO:
			startValue = target->getColor().a;
			endValue = inputValue;
			break;
		case ALPHA_BY:
			startValue = target->getColor().a;
			endValue = startValue + inputValue;
			break;
		case ROTATE_TO:
			startValue = target->getRotation();
			endValue = inputValue;
			break;
		case ROTATE_BY:
			startValue = target->getRotation();
			endValue = startValue + inputValue;
			break;
		}
	}

	void FloatAction::apply(float percent)
	{
		switch (type)
		{
		case ALPHA_TO:
		case ALPHA_BY:
		{
			glm::vec4 color = target->getColor();
			color.a = startValue + (endValue - startValue) * percent;
			target->setColor(color);
		}
		break;
		case ROTATE_TO:
		case ROTATE_BY:
			target->setRotation(startValue + (endValue - startValue) * percent);
			break;
		}
	}
}