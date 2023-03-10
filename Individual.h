#pragma once
#include "vector"
#include "KnapsackProblem.h"
#include "random"
#include "UniquePointer.h"

using namespace std;

# define DEFAULT_SEED 0

class Individual
{
public:

    Individual(SharedPointer<Problem>& problem,
               vector<int>&& genome,
               int seed = DEFAULT_SEED) : seed(seed),
               problem(problem), genome(std::move(genome)) {};

    Individual(const Individual& other) = default;
    virtual ~Individual() = default;
	double getFitness() { return (*problem).getFitness(genome);};
	virtual void mutate(double mutationRate) = 0;
    vector<int>* getGenome() { return &genome; };
	virtual vector<UniquePointer<Individual>> crossover(Individual& other) = 0;
    int getSeed() const {return seed;}
private:
    int seed;
protected:
    vector<int> genome;
    SharedPointer<Problem> problem;
};

class BasicIndividual : public Individual {
public:

    BasicIndividual(SharedPointer<Problem>& problem,
                    vector<int>&& genome,
                    int seed = DEFAULT_SEED) : Individual(problem, std::move(genome), seed),
                       mutationDistrib(0, 1),
                       crossoverDistrib(1, (*problem).getLength() - 1),
                       generator(seed){
    };

    explicit BasicIndividual(const Individual& other): Individual(other),
                                                       mutationDistrib(0, 1), crossoverDistrib(1, (*problem).getLength() - 1),
                                                       generator(other.getSeed()) {};

    void mutate(double mutationRate) override;

    vector<UniquePointer<Individual>> crossover(Individual& other) override;

private:

    static vector<int> exchangeGenes(Individual& p1,
                                     Individual& p2,
                                     int* mask,
                                     int genomeLength);

    int* generateMask();

    uniform_real_distribution<double> mutationDistrib;
    uniform_int_distribution<int> crossoverDistrib;
    mt19937 generator;

};

