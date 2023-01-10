//
// Created by julia on 12/28/2022.
//

#include "GeneticAlgorithm.h"
GeneticAlgorithm::GeneticAlgorithm(KnapsackProblem* problem,
int iterations, double mutationRate,
double crossoverRate, int populationSize){
    this->problem = problem;
    this->iterations = iterations;
    this->mutationRate = mutationRate;
    this->crossoverRate = crossoverRate;
    this->currentIteration = 0;
    this->populationSize = populationSize;

    this->gen = std::mt19937(this->rd());
    this->distrib = std::uniform_real_distribution<double>(0, 1);
}

void GeneticAlgorithm::initialize(){

    for (int i = 0; i < populationSize; i++){
        std::vector<int> genome;
        for (int j = 0; j < problem->getSize(); j++) {
            int gene = (int) std::round(distrib(gen));
            genome.push_back(gene);
        }
        KnapsackIndividual ind(std::move(genome));
        problem->computeFitness(ind);
        population.push_back(ind);
    }

}

void GeneticAlgorithm::runIteration(){

    vector<KnapsackIndividual> newPopulation;

    for (int i = 0; i < populationSize; i+=2){

        if (distrib(gen) < crossoverRate){

            // generate new children
            // use maybe tournament selection or other
        }

    }

}

bool GeneticAlgorithm::isFinished(){return currentIteration < iterations;}