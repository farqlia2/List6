#pragma once
#include "Individual.h"
#include "vector"
#include "KnapsackProblem.h"
#include "random"
#include "SmartPointer.h"

using namespace std;

//
class KnapsackIndividual : public Individual {
public:

	KnapsackIndividual(KnapsackProblem* problem, 
		vector<int>&& genome, int seed = DEFAULT_SEED) : Individual(seed) {
        this->genome = new vector<int>(std::move(genome));
        this->problem = problem;
        this->mutationDistrib = new uniform_real_distribution<double>(0, 1);
        this->crossoverDistrib = new uniform_int_distribution<int>(1, problem->getLength() - 1);
        this->generator = new mt19937 (seed);
	};

    ~KnapsackIndividual();

    double getFitness() override;

	void mutate(double mutationRate) override;

	vector<int>* getGenome() override { return genome; };

	vector<Individual*> crossover(Individual& other) override;

private:

	vector<int>* genome;
	KnapsackProblem* problem;

    uniform_real_distribution<double>* mutationDistrib;
    uniform_int_distribution<int>* crossoverDistrib;
    mt19937* generator;

};



