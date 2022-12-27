#pragma once

#include "Problem.h"
#include "vector"
#include "Constants.h"

using namespace std;

class KnapsackProblem : Problem
{
public:
	static KnapsackProblem* create(vector<double> weights,
		vector<double> values, double capacity);
	double getFitness(Individual& ind);
	int getSize();

private:
	KnapsackProblem(vector<double> weights,
		vector<double> values, double capacity);
	bool validate(vector<double> weights,
		vector<double> values, double capacity);
	
	vector<double> weights;
	vector<double> values;
	double capacity;
};

