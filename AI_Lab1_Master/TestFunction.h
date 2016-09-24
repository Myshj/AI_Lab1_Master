#pragma once
#include "vector"
using namespace std;
class TestFunction
{
public:
	virtual double Calculate(const vector<double>& args) const = 0;
};

