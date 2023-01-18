//
// Created by julia on 12/28/2022.
//
# pragma once
#ifndef LIST6_GENETICALGORITHM_H
#define LIST6_GENETICALGORITHM_H
#include "Individual.h"
#include "KnapsackProblem.h"
#include "IndividualFactory.h"
#include <random>

using namespace std;

class GeneticAlgorithm {
public:
    GeneticAlgorithm(SharedPointer<Problem>& problem,
                     SharedPointer<IndividualFactory>& factory,
                     int iterations, double mutationRate,
                     double crossoverRate, int populationSize, int tournament,
                     unsigned int seed);

    SharedPointer<Individual> getBest() { return bestSolution; };

    vector<SharedPointer<Individual>> getPopulation(){
        return population;
    }

    void runIteration();

    bool isFinished();

    int getCurrentIteration() const {return currentIteration;};

    int getSeed() const {return seed;}

private:

    void createGenome(vector<int>& genome);

    SharedPointer<Individual> initializeIndividual();

    vector<SharedPointer<Individual>> uniformSelection();

    SharedPointer<Individual> tournamentParentSelection();
    vector<SharedPointer<Individual>> tournamentSelection();

    bool shouldPerformCrossover();

    void initializePopulation();

    void reproduce();

    void mutate();

    void findBestSolution();

    SharedPointer<IndividualFactory> factory;
    SharedPointer<Problem> problem;
    SharedPointer<Individual> bestSolution;
    vector<SharedPointer<Individual>> population;

    int iterations;
    int currentIteration;
    double mutationRate;
    double crossoverRate;
    int populationSize;
    int tournament;
    unsigned int seed;
    std::mt19937 gen;
    std::uniform_real_distribution<double> realDistrib;
    std::uniform_int_distribution<int> intDistrib;

};


#endif //LIST6_GENETICALGORITHM_H
