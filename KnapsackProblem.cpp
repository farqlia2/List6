#include "KnapsackProblem.h"

KnapsackProblem::KnapsackProblem(vector<double>&& weights,
	vector<double>&& values, double capacity) {
	this->weights = weights;
	this->values = values;
	this->capacity = capacity;
}

// use move semantics here
KnapsackProblem* KnapsackProblem::create(vector<double>&& weights,
	vector<double>&& values, double capacity)
{
	if (validate(weights, values, capacity))
        return new KnapsackProblem(std::move(weights), std::move(values), capacity);
    return nullptr;
}

bool KnapsackProblem::validate(vector<double>& weights,
	vector<double>& values, double capacity){
	return true;
}

void KnapsackProblem::computeFitness(KnapsackIndividual& ind)
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
	ind.setFitness(weight <= capacity ? fitness : 0.0);
}

int KnapsackProblem::getSize()
{
	return values.size();
}
