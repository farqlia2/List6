#ifndef LIST6_KNAPSACKPROBLEM_H
#define LIST6_KNAPSACKPROBLEM_H

#include <vector>
#include "Constants.h"
#include "KnapsackIndividual.h"

using namespace std;

class KnapsackProblem
{
public:
	static KnapsackProblem* create(vector<double>&& weights,
		vector<double>&& values, double capacity);
	void computeFitness(KnapsackIndividual& ind);
	int getSize();

private:
	KnapsackProblem(vector<double>&& weights,
		vector<double>&& values, double capacity);
	static bool validate(vector<double>& weights,
		vector<double>& values, double capacity);
	
	vector<double> weights;
	vector<double> values;
	double capacity;
};


#endif