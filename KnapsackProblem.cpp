#include "KnapsackProblem.h"

KnapsackProblem::KnapsackProblem(vector<double>&& weights,
	vector<double>&& values, double capacity) {
	this->weights = weights;
	this->values = values;
	this->capacity = capacity;
}

// Or maybe have these arguments copied into this method
KnapsackProblem* KnapsackProblem::create(vector<double>&& weights,
	vector<double>&& values, double capacity)
{
	if (validate(weights, values, capacity))
        return new KnapsackProblem(std::move(weights), std::move(values), capacity);
    else
        return nullptr;
}

bool KnapsackProblem::validate(vector<double>& weights,
	vector<double>& values, double capacity) {

    return (std::all_of(values.cbegin(), values.cend(), [](int i){ return i > 0; })
    && std::all_of(weights.cbegin(), weights.cend(), [](int i){ return i > 0; }) && capacity > 0);

}


double KnapsackProblem::getFitness(vector<int>& genotype)
{
	double fitness = 0;
	double weight = 0;
	for (int g = 0; g < genotype.size(); g++) {
		if (genotype.at(g) == ONE) {
			fitness += values[g];
			weight += weights[g];
		}
	}
	return weight <= capacity ? fitness : 0; 
}

int KnapsackProblem::getLength()
{
	return values.size();
}
