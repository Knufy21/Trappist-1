#pragma once

#include <chrono>

namespace
{
	class Timer
	{
	public:
		using time_t = float;

		// Constructs a timer and calls the reset method.
		Timer();

		// Resets the timer by setting the start point to the current time point.
		void reset();

		// Returns the elapsed time in years.
		Timer::time_t elapsedYears() const;

		// Returns the elapsed time in weeks.
		Timer::time_t elapsedWeeks() const;

		// Returns the elapsed time in days.
		Timer::time_t elapsedDays() const;

		// Returns the elapsed time in hours.
		Timer::time_t elapsedHours() const;

		// Returns the elapsed time in minutes.
		Timer::time_t elapsedMinutes() const;

		// Returns the elapsed time in seconds.
		Timer::time_t elapsedSeconds() const;

		// Returns the elapsed time in milliseconds.
		Timer::time_t elapsedMilliseconds() const;

		// Returns the elapsed time in microseconds.
		Timer::time_t elapsedMicroseconds() const;

		// Returns the elapsed time in nanoseconds.
		Timer::time_t elapsedNanoseconds() const;

	private:
		std::chrono::high_resolution_clock::time_point start;
	};

	inline Timer::Timer()
	{
		reset();
	}

	inline void Timer::reset()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	inline Timer::time_t Timer::elapsedYears() const
	{
		return static_cast<Timer::time_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count()) * static_cast<Timer::time_t>(3.1709791983764586504312531709792e-17);
	}

	inline Timer::time_t Timer::elapsedWeeks() const
	{
		return static_cast<Timer::time_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count()) * static_cast<Timer::time_t>(1.6534391534391534391534391534392e-15);
	}

	inline Timer::time_t Timer::elapsedDays() const
	{
		return static_cast<Timer::time_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count()) * static_cast<Timer::time_t>(1.1574074074074074074074074074074e-14);
	}

	inline Timer::time_t Timer::elapsedHours() const
	{
		return static_cast<Timer::time_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count()) * static_cast<Timer::time_t>(2.7777777777777777777777777777778e-13);
	}

	inline Timer::time_t Timer::elapsedMinutes() const
	{
		return static_cast<Timer::time_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count()) * static_cast<Timer::time_t>(1.6666666666666666666666666666667e-11);
	}

	inline Timer::time_t Timer::elapsedSeconds() const
	{
		return static_cast<Timer::time_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count()) * static_cast<Timer::time_t>(1.0e-9);
	}

	inline Timer::time_t Timer::elapsedMilliseconds() const
	{
		return static_cast<Timer::time_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count()) * static_cast<Timer::time_t>(1.0e-6);
	}

	inline Timer::time_t Timer::elapsedMicroseconds() const
	{
		return static_cast<Timer::time_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count()) * static_cast<Timer::time_t>(1.0e-3);
	}

	inline Timer::time_t Timer::elapsedNanoseconds() const
	{
		return static_cast<Timer::time_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count());
	}
}