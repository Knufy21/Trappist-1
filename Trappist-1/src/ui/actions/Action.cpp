#include "Trappist-1\ui\actions\Action.hpp"

#include <Trappist-1\UI\Widgets\Widget.hpp>

namespace ui
{
	Action::Action(float duration, const Interpolation &interpolation)
		: duration(duration), interpolation(interpolation), currTime(0.0f), finished(false)
	{  }

	Action::~Action()
	{  }

	void Action::update(float deltaTime)
	{
		if (finished) return;

		currTime += deltaTime;

		if (currTime < duration)
		{
			apply(interpolation.get(currTime / duration));
		}
		else
		{
			apply(1.0f);
			finished = true;
			if (onFinish)
				onFinish();
		}
	}

	bool Action::hasFinished() const
	{
		return this->finished;
	}

	void Action::setTarget(Widget &target)
	{
		this->target = &target;
		onTargetChanged();
	}

	const Widget &Action::getTarget() const
	{
		return *target;
	}

	void Action::setFinishListener(std::function<void()> listener)
	{
		onFinish = listener;
	}
}