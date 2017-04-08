#pragma once

#include <Trappist-1\util\EightBoolArray.hpp>

class Animation
{
	friend class AnimationSheet;
	static constexpr EightBoolArray::value_t BOOL_ARRAY_IS_FLIPPED_HORIZONTALLY	=	0;
	static constexpr EightBoolArray::value_t BOOL_ARRAY_IS_FLIPPED_VERTICALLY	=	1;
	static constexpr EightBoolArray::value_t BOOL_ARRAY_IS_SMOOTH				=	2;
	static constexpr EightBoolArray::value_t BOOL_ARRAY_IS_REVERSE				=	3;
public:
	using state_t = unsigned short;

	// Returns the start state of the animation.
	state_t getStartState() const;

	// Returns the end state of the animation.
	state_t getEndState() const;

	// Returns the count of states between the start and end state.
	state_t getStateCount() const;

	// Returns the time in seconds of how long each frame of the animation is displayed.
	float getFrameTime() const;

	// Returns whether the frame is mirrored in horizontal (x) direction.
	bool isFlippedHorizontally() const;

	// Returns whether the frame is mirrored in vertical (y) direction.
	bool isFlippedVertically() const;

	// Returns whether the animation is repeated backwards after one playback.
	bool isSmooth() const;

	// Returns whether the animation should be played backwards.
	bool isReverse() const;

private:
	state_t startState;
	state_t endState;
	float frameTime;

	EightBoolArray bools;
};

// Inline

inline Animation::state_t Animation::getStartState() const
{
	return this->startState;
}

inline Animation::state_t Animation::getEndState() const
{
	return this->endState;
}

inline Animation::state_t Animation::getStateCount() const
{
	return this->endState - this->startState;
}

inline float Animation::getFrameTime() const
{
	return this->frameTime;
}

inline bool Animation::isFlippedHorizontally() const
{
	return bools.get(Animation::BOOL_ARRAY_IS_FLIPPED_HORIZONTALLY);
}

inline bool Animation::isFlippedVertically() const
{
	return bools.get(Animation::BOOL_ARRAY_IS_FLIPPED_VERTICALLY);
}

inline bool Animation::isSmooth() const
{
	return bools.get(Animation::BOOL_ARRAY_IS_SMOOTH);
}

inline bool Animation::isReverse() const
{
	return bools.get(Animation::BOOL_ARRAY_IS_REVERSE);
}