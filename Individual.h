#pragma once
#include "vector"
#include "KnapsackProblem.h"
#include "random"
#include "SmartPointer.h"

using namespace std;

# define DEFAULT_SEED 0

class Individual
{
public:
    Individual() : seed(DEFAULT_SEED) {};
    explicit Individual(int seed) : seed(seed) {};
	virtual double getFitness() = 0;
	virtual void mutate(double mutationRate) = 0;
	virtual vector<int>* getGenome() = 0;
	virtual vector<Individual*> crossover(Individual& other) = 0;
    virtual int getSeed() {return seed;}
private:
    int seed;
};

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

    static vector<int> exchangeGenes(Individual& p1,
                                     Individual& p2,
                                     int* mask,
                                     int genomeLength);

    int* generateMask();

    vector<int>* genome;
    KnapsackProblem* problem;

    uniform_real_distribution<double>* mutationDistrib;
    uniform_int_distribution<int>* crossoverDistrib;
    mt19937* generator;

};

