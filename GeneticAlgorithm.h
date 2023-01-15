//
// Created by julia on 12/28/2022.
//
# pragma once
#ifndef LIST6_GENETICALGORITHM_H
#define LIST6_GENETICALGORITHM_H
#include "Individual.h"
#include "KnapsackProblem.h"
#include "StopCondition.h"
#include <random>

using namespace std;

class GeneticAlgorithm {
public:
    GeneticAlgorithm(SmartPointer<Problem>& problem,
                     int iterations, double mutationRate,
                     double crossoverRate, int populationSize,
                     int seed = DEFAULT_SEED);

    // What type should go there
    SmartPointer<Individual> getBest() {return bestSolution; };

    void runIteration();

    void initialize();

    bool isFinished();

    int getCurrentIteration();

private:

    void createGenome(vector<int>& genome);
    Individual* initializeIndividual();

    bool shouldPerformCrossover();

    void replicate();
    void mutate();

    void destroy(vector<Individual*>& pop);

    vector<Individual*> selectParents();

    SmartPointer<Problem> problem;
    SmartPointer<Individual> bestSolution;

    int iterations;
    int currentIteration;
    double mutationRate;
    double crossoverRate;
    int populationSize;

    int seed;

    vector<Individual*> population;

    std::mt19937 gen;
    std::uniform_real_distribution<double> realDistrib;
    std::uniform_int_distribution<int> intDistrib;
};


#endif //LIST6_GENETICALGORITHM_H
