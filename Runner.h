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
    virtual bool runAlgorithm(const string& filename) { return false; };
    virtual bool runAlgorithm() { return true; };

protected:
    unsigned int seed;
};

class KnapsackProblemRunner : public Runner {

public:

    KnapsackProblemRunner(int populationSize, double crossoverRate,
                          double mutationRate, int iterations,
                          unsigned int seed = DEFAULT_SEED) : Runner(seed),
                          populationSize(populationSize),
                          crossoverRate(crossoverRate),
                          mutationRate(mutationRate),
                          iterations(iterations) {}

    bool runAlgorithm(const string& fileName) override;

    bool runAlgorithm() override;

private:
    int populationSize;
    double crossoverRate;
    double mutationRate;
    int iterations;
};


#endif //LIST6_RUNNER_H
