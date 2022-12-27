#include "KnapsackProblem.h"

KnapsackProblem::KnapsackProblem(vector<double> weights,
	vector<double> values, double capacity) {
	this->weights = weights;
	this->values = values;
	this->capacity = capacity;
}

KnapsackProblem* KnapsackProblem::create(vector<double> weights,
	vector<double> values, double capacity)
{
	if (validate) return new KnapsackProblem(weights, values, capacity);
}

bool KnapsackProblem::validate(vector<double> weights,
	vector<double> values, double capacity) {
	return true;
}

double KnapsackProblem::getFitness(Individual& ind) 
{
	vector<int> genome = *ind.getGenome();
	double fitness = 0;
	double weight = 0;
	for (int gene = 0; gene < getSize(); gene++) {
		if (genome[gene] == ONE) {
			fitness += values[gene];
			weight += weights[gene];
		}
	}
	return weight <= capacity ? fitness : 0; 
}

int KnapsackProblem::getSize()
{
	return values.size();
}
