#include <Trappist-1\ui\Interpolation.hpp>
#include <cmath>

namespace ui
{
	Interpolation Interpolation::linear([](float value) -> float
	{
		return value;
	});

	Interpolation Interpolation::swingIn([](float value) -> float
	{
		return value * value * ((2.0f + 1.0f) * value - 2.0f);
	});

	Interpolation Interpolation::swingOut([](float value) -> float
	{
		value--;
		return value * value * ((2.0f + 1.0f) * value + 2.0f) + 1.0f;
	});

	Interpolation Interpolation::swing([](float value) -> float
	{
		if (value <= 0.5f) {
			value *= 2.0f;
			return value * value * ((2.25f + 1.0f) * value - 2.25f) / 2.0f;
		}
		value--;
		value *= 2.0f;
		return value * value * ((2.25f + 1.0f) * value + 2.25f) / 2.0f + 1.0f;
	});

	Interpolation::Interpolation(float(*getFunction)(float))
		: getFunction(getFunction)
	{	}
}