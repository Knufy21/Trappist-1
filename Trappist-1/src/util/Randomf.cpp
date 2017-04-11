#include <Trappist-1\util\Randomf.hpp>

#include <random>
#include <ctime>

namespace Randomf
{
	static std::default_random_engine randomGenerator;

	void seed()
	{
		randomGenerator.seed(static_cast<unsigned int>(time(0)));
	}

	void seed(unsigned int seed)
	{
		randomGenerator.seed(seed);
	}

	bool randomBool(int chancePercentage)
	{
		return randomFloat(0.0000f, 99.9999f) < chancePercentage;
	}

	bool randomBool(float chancePercentage)
	{
		return randomInt(0, 99) < chancePercentage;
	}

	template<typename T, typename U>
	T random(T inclStart, T inclEnd)
	{
		U range(inclStart, inclEnd);
		return range(randomGenerator);
	}

	template<typename T>
	T randomInt(T inclStart, T inclEnd)
	{
		return random<T, std::uniform_int_distribution<T>>(inclStart, inclEnd);
	}

	template<typename T>
	T randomReal(T inclStart, T inclEnd)
	{
		return random<T, std::uniform_real_distribution<T>>(inclStart, inclEnd);
	}

	template<typename T, typename U>
	T *randomBlock(T inclStart, T inclEnd, unsigned int blockSize)
	{
		if (blockSize == 0)
			return nullptr;

		T *block = new T[blockSize];
		while (blockSize > 0)
		{
			--blockSize;
			block[blockSize] = random<T, U>(inclStart, inclEnd);
		}
		return block;
	}

	int randomInt(int inclStart, int inclEnd)
	{
		return random<int, std::uniform_int_distribution<int>>(inclStart, inclEnd);
	}

	float randomFloat(float inclStart, float inclEnd)
	{
		return random<float, std::uniform_real_distribution<float>>(inclStart, inclEnd);
	}

	double randomDouble(double inclStart, double inclEnd)
	{
		return random<double, std::uniform_real_distribution<double>>(inclStart, inclEnd);
	}

	int *randomIntBlock(int inclStart, int inclEnd, unsigned int blockSize)
	{
		return randomBlock<int, std::uniform_int_distribution<int>>(inclStart, inclEnd, blockSize);
	}

	float *randomFloatBlock(float inclStart, float inclEnd, unsigned int blockSize)
	{
		return randomBlock<float, std::uniform_real_distribution<float>>(inclStart, inclEnd, blockSize);
	}

	double *randomDoubleBlock(double inclStart, double inclEnd, unsigned int blockSize)
	{
		return randomBlock<double, std::uniform_real_distribution<double>>(inclStart, inclEnd, blockSize);
	}
}