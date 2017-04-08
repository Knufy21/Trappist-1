#pragma once

#include <Trappist-1\components\Component.hpp>

#include <string>
#include <Trappist-1\util\EightBoolArray.hpp>
#include <Trappist-1\animation\Animation.hpp>
#include <Trappist-1\animation\AnimationSheetManager.hpp>

class Animation;
class AnimationSheet;
class Animator : public Component
{
	static constexpr EightBoolArray::value_t BOOL_ARRAY_PLAYING			=	0;
	static constexpr EightBoolArray::value_t BOOL_ARRAY_INCREASE		=	1;
	static constexpr EightBoolArray::value_t BOOL_ARRAY_NEEDS_UPDATE	=	2;
public:
	Animator(Entity *entity, const AnimationSheet *animationSheet);
	Animator(Entity *entity, AnimationSheetManager::AnimationSheetHandle handle);

	virtual void update() override final;

	// Returns the animation sheet of the animator.
	const AnimationSheet *getAnimationSheet() const;

	// Sets the animation sheet of the animator.
	void getAnimationSheet(const AnimationSheet *animationSheet);

	// Return the name of the animation currently playing.
	const Animation *getCurrentAnimation() const;

	// Sets the animation to be played by name and resets the animation state.
	void setAnimationByName(const std::string &animationName);

	// Returns whether the playback is currently in progress or not.
	bool isPlaying() const;

	// Sets whether the playback is currently in progress or not.
	void setPlaying(bool playing);

	// Returns whether the playback is currently progressing up or down.
	bool isIncreasing() const;

	// Sets whether the playback is currently progressing up or down.
	void setIncreasing(bool increase);

	// Returns the state of the current animation.
	Animation::state_t getState() const;

	// Sets the state of the current animation.
	void setState(Animation::state_t state);

private:
	void ensureStateUpdate();

	Animation::state_t state;
	const Animation *animation;
	const AnimationSheet *animationSheet;
	EightBoolArray bools;
	float pastTime; // The time having past since the last frame change
};

// Inline

inline const AnimationSheet *Animator::getAnimationSheet() const
{
	return this->animationSheet;
}

inline void Animator::getAnimationSheet(const AnimationSheet *animationSheet)
{
	this->animationSheet = animationSheet;
}

inline const Animation *Animator::getCurrentAnimation() const
{
	return this->animation;
}

inline bool Animator::isPlaying() const
{
	return bools.get(Animator::BOOL_ARRAY_PLAYING);
}

inline void Animator::setPlaying(bool playing)
{
	bools.set(Animator::BOOL_ARRAY_PLAYING, playing);
}

inline bool Animator::isIncreasing() const
{
	return bools.get(Animator::BOOL_ARRAY_INCREASE);
}

inline void Animator::setIncreasing(bool increase)
{
	bools.set(Animator::BOOL_ARRAY_INCREASE, increase);
}

inline Animation::state_t Animator::getState() const
{
	return this->state;
}

inline void Animator::setState(Animation::state_t state)
{
	this->state = state;
	bools.on(Animator::BOOL_ARRAY_NEEDS_UPDATE);
}