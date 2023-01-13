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

    // Generator liczb pseudolosowych powinien być ustawiony randomowo
    this->gen = std::mt19937(this->rd());
    this->distrib = std::uniform_real_distribution<double>(0, 1);
}

void GeneticAlgorithm::createGenome(vector<int>& genome){
    for (int j = 0; j < problem->getLength(); j++) {
        int gene = (int) std::round(distrib(gen));
        genome.push_back(gene);
    }
}

bool GeneticAlgorithm::performCrossover(){
    return distrib(gen) < crossoverRate;
}

KnapsackIndividual* GeneticAlgorithm::initializeIndividual(){
    std::vector<int> genome;
    createGenome(genome);
    return new KnapsackIndividual(problem, std::move(genome));
}

void GeneticAlgorithm::initialize(){

    for (int i = 0; i < populationSize; i++){
        population.push_back(initializeIndividual());
    }

}



void GeneticAlgorithm::runIteration(){

    vector<KnapsackIndividual*> newPopulation;

    for (int i = 0; i < populationSize; i+=2){

        if (performCrossover()){

            // generate new children
            // use maybe tournament selection or other
        }

    }

}

bool GeneticAlgorithm::isFinished(){
    return currentIteration >= iterations;
}