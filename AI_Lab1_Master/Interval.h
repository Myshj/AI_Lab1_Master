#pragma once
class Interval
{
public:
	Interval(const double min, const double max)
	{
		this->min = min;
		this->max = max;
	}

	double GetMin() const
	{
		return min;
	}

	double GetMax() const
	{
		return max;
	}

private:
	double min;
	double max;
};

