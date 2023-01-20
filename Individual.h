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
    virtual vector<SharedPointer<Individual>> crossover(Individual& other) = 0;

	double getFitness() const { return fitness;};
    vector<int>* getGenome() { return &genome; };

protected:
    vector<int> genome;
    SharedPointer<mt19937>& generatorPointer;
    SharedPointer<Problem> problem;
    double fitness;
};

class BasicIndividual : public Individual {
public:

    BasicIndividual(SharedPointer<Problem>& problem,
                    vector<int>&& genome,
                    SharedPointer<mt19937>& generator) : Individual(problem, std::move(genome),
                                                                    generator),
                                         realDistrib(0, 1),
                                         intDistrib(1, (*problem).getLength() - 1)
                                         {
    }

    BasicIndividual(SharedPointer<Problem>& problem,
                    SharedPointer<mt19937>& generator) : Individual(problem, generator),
                                               realDistrib(0, 1),
                                               intDistrib(1, (*problem).getLength() - 1)
                                               {
        createGenome();
    };

    explicit BasicIndividual(const Individual& other): Individual(other),
                                                       realDistrib(0, 1),
                                                       intDistrib(1, (*problem).getLength() - 1){};

    void mutate(double mutationRate) override;

    vector<SharedPointer<Individual>> crossover(Individual& other) override;

private:

    static vector<int> exchangeGenes(Individual& p1,
                                     Individual& p2,
                                     int* mask,
                                     int genomeLength);

    int* generateOnePointMask();
    int* generateUniformMask();

    void createGenome();

    uniform_real_distribution<double> realDistrib;
    uniform_int_distribution<int> intDistrib;

};

