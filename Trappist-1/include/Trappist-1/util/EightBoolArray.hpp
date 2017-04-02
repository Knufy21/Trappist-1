#pragma once

#include <stdint.h>

namespace
{
#pragma warning(push)
#pragma warning( disable : 4800 )
	// A class which can store eight bools with only one bytes and absolutly no overhead.
	class EightBoolArray
	{
	public:
		using value_t = uint8_t;

		// Each single bool stored as one bit in this unsigned char.
		value_t values;

		// Constructs an array with all bools set to false.
		EightBoolArray();

		// Constructs an array with all bools set to a specific value.
		EightBoolArray(value_t values);

		// Returns the value of a specific bool from this array via the index.
		bool get(value_t index) const;

		// Sets the value of a specific bool from this array via the index with the specific value.
		void set(value_t index, bool value);

		// Turns the value of the with the index specified bool from this array on.
		void on(value_t index);

		// Turns the value of the with the index specified bool from this array on.
		void off(value_t index);

		// Flips the value of a specific bool from this array via the index.
		void flip(value_t index);
	};

	// Inline

	inline EightBoolArray::EightBoolArray()
		: values(0x00)
	{  }

	inline EightBoolArray::EightBoolArray(value_t values)
		: values(values)
	{  }

	inline bool EightBoolArray::get(value_t index) const
	{
		return this->values & (0x01 << index);
	}

	inline void EightBoolArray::set(value_t index, bool value)
	{
		this->values = value ? this->values | (0x01 << index) : this->values & ~(0x01 << index);
	}

	inline void EightBoolArray::on(value_t index)
	{
		this->values |= (0x01 << index);
	}

	inline void EightBoolArray::off(value_t index)
	{
		this->values &= ~(0x01 << index);
	}

	inline void EightBoolArray::flip(value_t index)
	{
		this->values ^= (0x01 << index);
	}

#pragma warning(pop)
}