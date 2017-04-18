#pragma once

namespace ui
{
	class Interpolation
	{
	public:
		static Interpolation linear;
		static Interpolation swingIn;
		static Interpolation swingOut;
		static Interpolation swing;

		Interpolation(float(*getFunction)(float));

		// Returns the interpolated value of the specified value.
		float get(float value) const;

	private:
		float(*getFunction)(float);
	};

	// Inline

	inline float Interpolation::get(float value) const
	{
		return getFunction(value);
	}
}