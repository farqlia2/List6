#pragma once

#include "Problem.h"
#include "vector"
#include "Constants.h"

using namespace std;

class KnapsackProblem
{
public:
	static KnapsackProblem* create(vector<double>&& weights,
		vector<double>&& values, double capacity);
	double getFitness(vector<int>& genotype);
	int getLength();

private:
	KnapsackProblem(vector<double>&& weights,
		vector<double>&& values, double capacity);
	static bool validate(vector<double>& weights,
		vector<double>& values, double capacity);
	
	vector<double> weights;
	vector<double> values;
	double capacity;
};

