#pragma once
#include "TestFunction.h"
#include "math.h"
class Griewank :
	public TestFunction
{
public:
	virtual double Calculate(const vector<double>& args) const override
	{
		double sum = 0.0;
		double mul = 1.0;
		auto size = args.size();
		for (unsigned int i = 0; i < size; i++)
		{
			sum += args[i] * args[i] / 4000;
			mul *= cos(args[i]/sqrt(i+1));
		}
		return sum + mul + 1;
	}
};
