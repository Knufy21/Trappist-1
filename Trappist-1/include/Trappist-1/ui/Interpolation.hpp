#pragma once

#include <functional>

namespace ui
{
	class Interpolation
	{
	public:
		static Interpolation linear;
		static Interpolation swingIn;
		static Interpolation swingOut;
		static Interpolation swing;

		Interpolation(const std::function<float(float)> &getFunction);
		float get(float value) const;

	private:
		std::function<float(float)> getFunction;
	};
}