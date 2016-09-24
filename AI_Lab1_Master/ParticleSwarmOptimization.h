#pragma once

#include "TestFunction.h"
#include "Interval.h"
#include "FunctionExtremum.h"
#include "memory"
#include "random"
#include "chrono"
#include "iostream"

class ParticleSwarmOptimization
{
public:
	ParticleSwarmOptimization(
		const unsigned int countOfParticles=1000,
		const double cognitiveMultiplier=1, //c1
		const double socialMultiplier=1, //c2
		const unsigned int maxIterations=10000, //Tmax
		const double minInertia=0.1, //Wdown
		const double maxInertia=1.2 //Wup
		)
	{
		this->countOfParticles = countOfParticles;
		this->cognitiveMultiplier = cognitiveMultiplier;
		this->socialMultiplier = socialMultiplier;
		this->maxIterations = maxIterations;
		this->minInertia = minInertia;
		this->maxInertia = maxInertia;

		currentPositions = vector<vector<double> >(countOfParticles);
		currentFunctionResults = vector<double>(countOfParticles);

		currentBestPositions = vector<vector<double> >(countOfParticles);
		currentBestFunctionResults = vector<double>(countOfParticles);

		currentSpeeds = vector<vector<double> >(countOfParticles);
	}

	double Optimize(
		const shared_ptr<TestFunction>& function,
		const vector<Interval>& intervals,
		const FunctionExtremum& extremumToFind
		)
	{
		this->function = function;
		this->intervals = intervals;
		this->extremumToFind = extremumToFind;
		countOfDimensions = intervals.size();

		InitializeParticles();
		InitializeMaxSpeeds();
		FindGlobalBest();

		iteration = 0;
		while (iteration < maxIterations)
		{
			CalculateCurrentInertia();
			for (unsigned int particleNumber = 0; particleNumber < countOfParticles; particleNumber++)
			{
				CalculateSpeedForParticle(particleNumber);
				CalculatePositionForParticle(particleNumber);
				currentFunctionResults[particleNumber] = function->Calculate(currentPositions[particleNumber]);
				UpdateLocalBestForParticle(particleNumber);
			}
			FindGlobalBest();

			//cout << currentBestFunctionResults[globalBestIndex] << endl;
			DisplayState();

			iteration++;
		}

		return currentBestFunctionResults[globalBestIndex];
	}

private:

	void DisplayState()
	{
		system("cls");
		cout << "Global best: " << currentBestFunctionResults[globalBestIndex] << endl;
		cout << "Iteration " << iteration+1 << "/" << maxIterations << endl;
		cout << "Count of particles: " << countOfParticles << endl;
		cout << "Count of dimensions: " << countOfDimensions << endl;
		cout << "Extremum: " << (extremumToFind == FunctionExtremum::Minimum ? "minimum" : "maximum") << endl;
		cout << "Cognitive multiplier: " << cognitiveMultiplier << endl;
		cout << "Social multiplier: " << socialMultiplier << endl;
		cout << "Minimal inertia: " << minInertia << endl;
		cout << "Maximal inertia: " << maxInertia << endl;
		cout << "Current inertia: " << currentInertia << endl;
	}

	void UpdateLocalBestForParticle(const unsigned int particleNumber)
	{
		switch(extremumToFind)
		{
		case FunctionExtremum::Minimum:
		{
			if (currentFunctionResults[particleNumber] < currentBestFunctionResults[particleNumber])
			{
				currentBestFunctionResults[particleNumber] = currentFunctionResults[particleNumber];
				currentBestPositions[particleNumber] = currentPositions[particleNumber];
			}
			break;
		}
		case FunctionExtremum::Maximum:
		{
			if (currentFunctionResults[particleNumber] > currentBestFunctionResults[particleNumber])
			{
				currentBestFunctionResults[particleNumber] = currentFunctionResults[particleNumber];
				currentBestPositions[particleNumber] = currentPositions[particleNumber];
			}
			break;
		}
		}
	}

	void CalculatePositionForParticle(const unsigned int particleNumber)
	{
		for (unsigned int dimension = 0; dimension < countOfDimensions; dimension++)
		{
			double newPosition = currentPositions[particleNumber][dimension] + currentSpeeds[particleNumber][dimension];
			if (newPosition > intervals[dimension].GetMax())
			{
				newPosition = intervals[dimension].GetMax();
			}
			else if (newPosition < intervals[dimension].GetMin())
			{
				newPosition = intervals[dimension].GetMin();
			}
			currentPositions[particleNumber][dimension] = newPosition;
		}
	}

	void CalculateSpeedForParticle(const unsigned int particleNumber)
	{
		static uniform_real_distribution<> dist(0, 1);

		for (unsigned int dimension = 0; dimension < countOfDimensions; dimension++)
		{
			double r1 = dist(e2);
			double r2 = dist(e2);

			double speed =
				currentInertia * currentSpeeds[particleNumber][dimension] +
				cognitiveMultiplier * r1 * (currentBestPositions[particleNumber][dimension] - currentPositions[particleNumber][dimension]) +
				socialMultiplier * r2 * (currentBestPositions[globalBestIndex][dimension] - currentPositions[particleNumber][dimension]);

			if (speed > maxSpeeds[dimension])
			{
				speed = maxSpeeds[dimension];
			}
			else if (speed < -maxSpeeds[dimension])
			{
				speed = -maxSpeeds[dimension];
			}

			currentSpeeds[particleNumber][dimension] = speed;
		}
	}

	void CalculateCurrentInertia()
	{
		currentInertia = maxInertia - (maxInertia - minInertia) * ((double)iteration / maxIterations);
	}

	void InitializeMaxSpeeds()
	{
		maxSpeeds = vector<double>(countOfDimensions);
		for (unsigned int dimension = 0; dimension < countOfDimensions; dimension++)
		{
			maxSpeeds[dimension] = (intervals[dimension].GetMax() - intervals[dimension].GetMin()) / 2;
		}
	}

	void FindGlobalBest()
	{
		unsigned int currentGlobalBestIndex = globalBestIndex;
		switch (extremumToFind)
		{
		case FunctionExtremum::Minimum:
		{
			for (unsigned int particleNumber = 0; particleNumber < countOfParticles; particleNumber++)
			{
				if (currentBestFunctionResults[particleNumber] < currentBestFunctionResults[currentGlobalBestIndex])
				{
					currentGlobalBestIndex = particleNumber;
				}
			}
			break;
		}
		case FunctionExtremum::Maximum:
		{
			for (unsigned int particleNumber = 0; particleNumber < countOfParticles; particleNumber++)
			{
				if (currentBestFunctionResults[particleNumber] > currentBestFunctionResults[currentGlobalBestIndex])
				{
					currentGlobalBestIndex = particleNumber;
				}
			}

		}
		}
		globalBestIndex = currentGlobalBestIndex;
	}

	void InitializeParticles()
	{
		for (unsigned int particleNumber = 0; particleNumber < countOfParticles; particleNumber++)
		{
			currentPositions[particleNumber] = vector<double>(countOfDimensions);
			currentBestPositions[particleNumber] = vector<double>(countOfDimensions);
			currentSpeeds[particleNumber] = vector<double>(countOfDimensions);

			for (unsigned int coordinateNumber = 0; coordinateNumber < countOfDimensions; coordinateNumber++)
			{
				uniform_real_distribution<> dist(intervals[coordinateNumber].GetMin(), intervals[coordinateNumber].GetMax());
				currentPositions[particleNumber][coordinateNumber] = dist(e2);
				currentBestPositions[particleNumber][coordinateNumber] = currentPositions[particleNumber][coordinateNumber];
			}
			currentFunctionResults[particleNumber] = function->Calculate(currentPositions[particleNumber]);
			currentBestFunctionResults[particleNumber] = currentFunctionResults[particleNumber];
		}
	}

	unsigned int countOfParticles;
	double cognitiveMultiplier;
	double socialMultiplier;
	unsigned int maxIterations;

	double minInertia;
	double maxInertia;
	double currentInertia;

	unsigned int countOfDimensions;

	vector<vector<double> > currentPositions;
	vector<double> currentFunctionResults;
	vector<vector<double> > currentBestPositions;
	vector<double> currentBestFunctionResults;

	vector<double> maxSpeeds;
	vector<vector<double> > currentSpeeds;

	shared_ptr<TestFunction> function;
	vector<Interval> intervals;
	unsigned int globalBestIndex;

	FunctionExtremum extremumToFind;

	unsigned int iteration;

	static mt19937 e2;
};

