//
// Created by julia on 12/28/2022.
//

#ifndef LIST6_GENETICALGORITHM_H
#define LIST6_GENETICALGORITHM_H
#include "Individual.h"
#include "KnapsackProblem.h"
#include <random>

using namespace std;

class GeneticAlgorithm {
public:
    GeneticAlgorithm(KnapsackProblem* problem,
                     int iterations, double mutationRate,
                     double crossoverRate, int populationSize);

    // move semantics should be implemented for this
    Individual* getBest() {return bestSolution; };

    void runIteration();

    void initialize();

    bool isFinished();

    int getCurrentIteration();

private:

    void createGenome(vector<int>& genome);
    KnapsackIndividual* initializeIndividual();

    bool performCrossover();

    KnapsackProblem* problem;
    KnapsackIndividual* bestSolution;

    int iterations;
    int currentIteration;
    double mutationRate;
    double crossoverRate;
    int populationSize;

    vector<KnapsackIndividual*> population;

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<double> distrib;
};


#endif //LIST6_GENETICALGORITHM_H
