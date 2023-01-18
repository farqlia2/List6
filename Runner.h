//
// Created by julia on 1/17/2023.
//

#ifndef LIST6_RUNNER_H
#define LIST6_RUNNER_H

#include "GeneticAlgorithm.h"
#include "Solution.h"
#include "Globals.h"

class Runner {

public:

    explicit Runner(unsigned int seed = DEFAULT_SEED) : seed(seed) {}
    virtual void runAlgorithm(const string& filename) {};
    virtual bool runAlgorithm() { return false; };
    unsigned int getSeed() const { return seed; }

protected:
    unsigned int seed;
};

class KnapsackProblemRunner : public Runner {

public:

    KnapsackProblemRunner(int populationSize, double crossoverRate,
                          double mutationRate, int iterations, int tournament,
                          unsigned int seed = DEFAULT_SEED) : Runner(seed),
                          populationSize(populationSize),
                          crossoverRate(crossoverRate),
                          mutationRate(mutationRate),
                          tournament(tournament),
                          iterations(iterations) {}

    void runAlgorithm(const string& fileName) override;


private:
    int populationSize;
    int tournament;
    double crossoverRate;
    double mutationRate;
    int iterations;
};


#endif //LIST6_RUNNER_H
