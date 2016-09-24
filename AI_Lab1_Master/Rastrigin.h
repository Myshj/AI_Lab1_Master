#pragma once
#define _USE_MATH_DEFINES

#include "TestFunction.h"
#include "math.h"
class Rastrigin :
	public TestFunction
{
public:
	virtual double Calculate(const vector<double>& args) const override
	{
		double sum = 0.0;
		auto size = args.size();
		for (unsigned int i = 0; i < size; i++)
		{
			sum += args[i] * args[i] - 10 * cos(2 * 3.14*args[i]);
		}
		return sum + 10 * size;
	}
};
