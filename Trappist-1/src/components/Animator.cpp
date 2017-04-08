#include <Trappist-1\components\Animator.hpp>

#include <Trappist-1\util\Time.hpp>
#include <Trappist-1\entities\Entity.hpp>
#include <Trappist-1\animation\AnimationSheet.hpp>

Animator::Animator(Entity *entity, const AnimationSheet *animationSheet)
	: Component(entity), animationSheet(animationSheet)
{
	setPlaying(true);
	type = ComponentType::ANIMATOR;
	setAnimationByName("IdleFront");
}

Animator::Animator(Entity *entity, AnimationSheetManager::AnimationSheetHandle handle)
	: Component(entity), animationSheet(AnimationSheetManager::get(handle))
{
	setPlaying(true);
	type = ComponentType::ANIMATOR;
	setAnimationByName("IdleFront");
}

void Animator::update()
{
	if (isPlaying())
	{
		pastTime += Time::deltaTime;

		if (pastTime > animation->getFrameTime())
		{
			pastTime = 0.0f;

			if (isIncreasing()) // alias !isReverse, but that cant be modified
			{
				if (state < animation->getEndState()) // if next state is valid -> increase
					setState(state + 1);
				else if (animation->isSmooth()) // if next state not valid and smooth turn playdir
					setIncreasing(false);
				else // if next state not valid and !smooth reset
					setState(animation->getStartState());
			}
			else
			{
				if (state > animation->getStartState()) // if next state is valid -> decrease
					setState(state - 1);
				else if (animation->isSmooth()) // if next state not valid and smooth turn playdir
					setIncreasing(true);
				else // if next state not valid and !smooth reset
					setState(animation->getEndState());
			}
		}

		ensureStateUpdate();
	}
}

void Animator::setAnimationByName(const std::string &animationName)
{
	this->animation = animationSheet->getAnimationByName(animationName);
	setState(animation->isReverse() ? animation->getEndState() : animation->getStartState());
	pastTime = 0.0f;
	setIncreasing(!animation->isReverse());
}

void Animator::ensureStateUpdate()
{
	if (bools.get(Animator::BOOL_ARRAY_NEEDS_UPDATE))
	{
		entity->setTextureRect(animationSheet->getTextureRectByState(getState()));

		bools.off(Animator::BOOL_ARRAY_NEEDS_UPDATE);
	}
}