#pragma once
#include "TestFunction.h"

class Rosenbrock :
	public TestFunction
{
public:
	virtual double Calculate(const vector<double>& args) const override
	{
		double sum = 0.0;
		auto size = args.size();
		for (unsigned int i = 0; i < size - 1; i++)
		{
			sum += 100 * (args[i + 1] - args[i] * args[i]) * (args[i + 1] - args[i] * args[i]) + (args[i] - 1) * (args[i] - 1);
		}
		return sum + 10 * size;
	}
};
