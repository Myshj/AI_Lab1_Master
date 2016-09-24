#pragma once
#include "iostream"
#include "Hypersphere.h"
#include "Griewank.h"
#include "Rastrigin.h"
#include "Rosenbrock.h"
#include "ParticleSwarmOptimization.h"

#include "math.h"
int main(int argc, char* argv[])
{
	Interval sphereInterval(-100, 100);
	Interval griewankInterval(-600, 600);
	Interval rastriginInterval(-5.12, 5.12);
	Interval rosenbrockInterval(-5, 10);

	unsigned int countOfParticles = 50;
	double c1 = 1.0;
	double c2 = 1.0;
	unsigned int countOfIterations = 500;
	double minInertia = 0.1;
	double maxInertia = 1.2;
	unsigned int countOfDimensions = 10;
	FunctionExtremum extremumToFind = FunctionExtremum::Minimum;
	shared_ptr<TestFunction> function = make_shared<Hypersphere>(Hypersphere());
	Interval interval = sphereInterval;
	// Find count of particles
	/*for (int i = 0; i < argc - 1; i++)
	{
		if (0 == stricmp(argv[i], "-pc"))
		{
			countOfParticles = atoi(argv[i+1]);
		}
		else if (0 == _stricmp(argv[i], "-c1"))
		{
			c1 = atof(argv[i+1]);		
		}
		else if (0 == _stricmp(argv[i], "-c2"))
		{
			c2 = atof(argv[i + 1]);
		}
		else if (0 == _stricmp(argv[i], "-it"))
		{
			countOfIterations = atoi(argv[i+1]);
		}
		else if (0 == _stricmp(argv[i], "-wlow"))
		{
			minInertia = atof(argv[i+1]);
		}
		else if (0 == _stricmp(argv[i], "-wup"))
		{
			maxInertia = atof(argv[i + 1]);
		}
		else if (0 == _stricmp(argv[i], "-d"))
		{
			countOfDimensions = atoi(argv[i+1]);
		}
		else if (0 == _stricmp(argv[i], "-extr"))
		{
			if (0 == _stricmp(argv[i + 1], "min"))
			{
				extremumToFind = FunctionExtremum::Minimum;
			}
			else if (0 == _stricmp(argv[i + 1], "max"))
			{
				extremumToFind = FunctionExtremum::Maximum;
			}
		}
		else if (0 == _stricmp(argv[i], "-func"))
		{
			if (0 == _stricmp(argv[i + 1], "sphere"))
			{
				function = make_shared<Hypersphere>(Hypersphere());
				interval = sphereInterval;
			}
			else if (0 == _stricmp(argv[i + 1], "griewank"))
			{
				function = make_shared<Griewank>(Griewank());
				interval = griewankInterval;
			}
			else if (0 == _stricmp(argv[i + 1], "rastrigin"))
			{
				function = make_shared<Rastrigin>(Rastrigin());
				interval = rastriginInterval;
			}
			else if (0 == _stricmp(argv[i + 1], "rosenbrock"))
			{
				function = make_shared<Rosenbrock>(Rosenbrock());
				interval = rosenbrockInterval;
			}
		}
	}
*/
	vector<Interval> intervals = vector<Interval>();
	for (unsigned int i = 0; i < countOfDimensions; i++)
	{
		intervals.push_back(interval);
	}

	

	auto swarm = ParticleSwarmOptimization(
		countOfParticles,
		c1,
		c2,
		countOfIterations,
		minInertia,
		maxInertia
	);

	swarm.Optimize(function, intervals, extremumToFind);

	getchar();
	return 0;
}