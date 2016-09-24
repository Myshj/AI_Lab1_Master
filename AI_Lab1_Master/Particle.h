#pragma once
#include"TestFunction.h"
#include"Interval.h"
#include"memory"
#include"random"
class Particle
{
public:

	Particle(
		const double cognitiveMultiplier, //c1
		const double socialMultiplier, //c2
		const double minInertia, //Wdown
		const double maxInertia //Wup
	)
	{
		this->cognitiveMultiplier = cognitiveMultiplier;
		this->socialMultiplier = socialMultiplier;
		this->minInertia = minInertia;
		this->maxInertia = maxInertia;

	}

	void Initialize(
		const shared_ptr<TestFunction>& function,
		const shared_ptr<vector<Interval> >& intervals,
		const shared_ptr<vector<double> >& globalBest,
		const shared_ptr<vector<double> >& maxSpeed
	)
	{
		// Initialize random generator once
		


		this->function = function;
		this->intervals = intervals;
		this->globalBest = globalBest;
		this->maxSpeed = maxSpeed;

		
		// Set random positions for all coordinates
		currentPosition.clear();
		for (auto interval : *intervals)
		{
			
		}
		currentResult = function->Calculate(currentPosition);

		currentSpeed = vector<double>(intervals->size());

		localBestPosition = currentPosition;
		localBestResult = currentResult;

		currentIteration = 0;
	}

	void DoIteration()
	{
		CalculateSpeed();
	}

	const vector<double>& GetLocalBestPosition() const
	{
		return localBestPosition;
	}

	double GetLocalBestResult() const
	{
		return localBestResult;
	}

private:

	void CalculateSpeed()
	{

	}

	double cognitiveMultiplier;
	double socialMultiplier;
	double minInertia;
	double maxInertia;

	unsigned int currentIteration;

	vector<double> localBestPosition;
	double localBestResult;

	vector<double> currentPosition;
	double currentResult;

	vector<double> currentSpeed;

	shared_ptr<vector<double> > globalBest;
	shared_ptr<TestFunction> function;
	shared_ptr<vector<Interval> > intervals;
	shared_ptr<vector<double> > maxSpeed;
};

