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

    explicit Runner(int populationSize, double crossoverRate,
                    double mutationRate, int iterations, int tournament,
                    unsigned int seed = SEED) : seed(seed),
                    populationSize(populationSize),
        crossoverRate(crossoverRate),
        mutationRate(mutationRate),
        tournament(tournament),
        iterations(iterations) {}

    void runAlgorithm(const string& filename,
                      SharedPointer<Problem>& problemPointer);

    unsigned int getSeed() const { return seed; }

private:
    unsigned int seed;
    int populationSize;
    int tournament;
    double crossoverRate;
    double mutationRate;
    int iterations;

};


#endif //LIST6_RUNNER_H
