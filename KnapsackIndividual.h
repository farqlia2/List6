#pragma once
#include "Individual.h"
#include "vector"
#include "KnapsackProblem.h"

using namespace std;

class KnapsackIndividual : Individual 
{
public:
	KnapsackIndividual(KnapsackProblem* problem, 
		vector<int> genome) {
		this->genome = genome; 
		this->problem = problem; 
	};
	double getFitness();
	void mutate(); 
	vector<int>* getGenome() { return &genome; };
	virtual KnapsackIndividual* crossover(Individual& other) override;
private:
	vector<int> genome;
	KnapsackProblem* problem; 
};

