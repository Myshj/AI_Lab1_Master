#pragma once
#include "TestFunction.h"
class Hypersphere :
	public TestFunction
{
public:
	virtual double Calculate(const vector<double>& args) const override
	{
		auto ret = 0.0;
		for (auto arg : args)
		{
			ret += arg * arg;
		}
		return ret;
	}
};

