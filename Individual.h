#pragma once
#include "vector"
#include "KnapsackProblem.h"
#include "random"

using namespace std;

class Individual
{
public:

    Individual(SharedPointer<Problem>& problem,
               vector<int>&& genome,
               SharedPointer<mt19937>& generator) :
            problem(problem), genome(std::move(genome)), generatorPointer(generator),
            fitness(0) {};

    explicit Individual(SharedPointer<Problem>& problem,
                        SharedPointer<mt19937>& generator) :
            problem(problem), genome(), generatorPointer(generator),
            fitness(0) {};

    Individual(const Individual& other) = default;

    virtual ~Individual() = default;
    virtual void computeFitness() {
        fitness = (*problem).getFitness(genome);
    };
    virtual void mutate(double mutationRate) = 0;

    virtual void mutate(double mutationRate,
                        SharedPointer<Individual>& other) {};

    virtual vector<SharedPointer<Individual>> crossover(Individual& other) = 0;

	double getFitness() const { return fitness;};
    vector<int>* getGenome() { return &genome; };

protected:
    vector<int> genome;
    SharedPointer<mt19937>& generatorPointer;
    SharedPointer<Problem> problem;
    double fitness;
};

