#pragma once
#include "vector"
#include "KnapsackProblem.h"
#include "random"
#include "UniquePointer.h"

using namespace std;

class Individual
{
public:

    Individual(SharedPointer<Problem>& problem,
               vector<int>&& genome,
               unsigned int seed) : seed(seed),
               problem(problem), genome(std::move(genome)) {};

    Individual(const Individual& other) = default;

    virtual ~Individual() = default;
    virtual void computeFitness() {
        fitness = (*problem).getFitness(genome);
    };
    virtual void mutate(double mutationRate) = 0;
    virtual vector<SharedPointer<Individual>> crossover(Individual& other) = 0;

	double getFitness() const { return fitness;};
    vector<int>* getGenome() { return &genome; };
    unsigned int getSeed() const {return seed;}

private:
    unsigned int seed;
protected:
    vector<int> genome;
    SharedPointer<Problem> problem;
    double fitness;
};

class BasicIndividual : public Individual {
public:

    BasicIndividual(SharedPointer<Problem>& problem,
                    vector<int>&& genome,
                    unsigned int seed) : Individual(problem, std::move(genome), seed),
                                               realDistrib(0, 1),
                                               intDistrib(1, (*problem).getLength() - 1),
                                               generator(seed){
    };

    explicit BasicIndividual(const Individual& other): Individual(other),
                                                       realDistrib(0, 1),
                                                       intDistrib(1, (*problem).getLength() - 1),
                                                       generator(other.getSeed()) {};

    void mutate(double mutationRate) override;

    vector<SharedPointer<Individual>> crossover(Individual& other) override;

private:

    static vector<int> exchangeGenes(Individual& p1,
                                     Individual& p2,
                                     int* mask,
                                     int genomeLength);

    int* generateOnePointMask();
    int* generateUniformMask();

    uniform_real_distribution<double> realDistrib;
    uniform_int_distribution<int> intDistrib;
    mt19937 generator;

};

