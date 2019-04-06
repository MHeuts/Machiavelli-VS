#pragma once
#include <random>

class random_generator
{
	random_generator() = default;
	std::random_device rd;
	std::mt19937 generator{ rd() };

public:
	static random_generator& instance()
	{
		static random_generator rg;
		return rg;
	};

	int operator()(int min, int max) 
	{
		std::uniform_int_distribution<> dis(min, max);
		return dis(generator);
	};

	size_t operator()(size_t min, size_t max)
	{
		std::uniform_int_distribution<size_t> dis(min, max);
		return dis(generator);
	};

	float operator()(float min, float max)
	{
		std::uniform_real_distribution<float> dis(min, max);
		return dis(generator);
	};

	std::mt19937 random_generation() const
	{
		return generator;
	};
};

#define random_generator random_generator::instance()