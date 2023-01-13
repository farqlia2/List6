#pragma once
#include "Individual.h"
#include "vector"
#include "KnapsackProblem.h"
#include "random"
#include "SmartPointer.h"

using namespace std;

class KnapsackIndividual
{
public:
    KnapsackIndividual() = default;

	KnapsackIndividual(KnapsackProblem* problem, 
		vector<int>&& genome) {
		this->genome = new vector<int>(std::move(genome));
		this->problem = problem;
        this->mutationDistrib = new uniform_real_distribution<double>(0, 1);
        this->crossoverDistrib = new uniform_real_distribution<double>(0, 1);
        random_device rd;
        this->generator = new mt19937(rd());
	};
    ~KnapsackIndividual();
	double getFitness();
	void mutate(double mutationRate);
	vector<int>* getGenome() { return genome; };
    //
	KnapsackIndividual* crossover(KnapsackIndividual& other);

private:

	vector<int>* genome;
	KnapsackProblem* problem;

    uniform_real_distribution<double>* mutationDistrib;
    uniform_real_distribution<double>* crossoverDistrib;
    mt19937* generator;
};



