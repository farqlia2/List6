//
// Created by julia on 12/28/2022.
//

#include "GeneticAlgorithm.h"
GeneticAlgorithm::GeneticAlgorithm(SmartPointer<Problem>& problem,
int iterations, double mutationRate,
double crossoverRate, int populationSize, int seed) : problem(problem),
                                            bestSolution(nullptr), seed(seed){

    this->problem = problem;
    this->iterations = iterations;
    this->mutationRate = mutationRate;
    this->crossoverRate = crossoverRate;
    this->currentIteration = 0;
    this->populationSize = populationSize;

    // Generator liczb pseudolosowych powinien być ustawiony randomowo
    this->gen = std::mt19937(seed);
    this->realDistrib = std::uniform_real_distribution<double>(0, 1);
    this->intDistrib = std::uniform_int_distribution<int>(0, populationSize - 1);
}

void GeneticAlgorithm::createGenome(vector<int>& genome){
    for (int j = 0; j < (*problem).getLength(); j++) {
        int gene = (int) std::round(realDistrib(gen));
        genome.push_back(gene);
    }
}

bool GeneticAlgorithm::shouldPerformCrossover(){
    return realDistrib(gen) < crossoverRate;
}

vector<Individual*> GeneticAlgorithm::selectParents(){

    int parent1 = intDistrib(gen);
    int parent2 = intDistrib(gen);

    vector<Individual*> parents {population.at(parent1), population.at(parent2)};

    return std::move(parents);
}

Individual* GeneticAlgorithm::initializeIndividual(){
    std::vector<int> genome;
    createGenome(genome);
    return new KnapsackIndividual(problem, std::move(genome));
}

void GeneticAlgorithm::destroy(vector<Individual*>& pop){
    for (int i = 0; i < populationSize; i++){
        delete pop.at(i);
    }
}

void GeneticAlgorithm::initialize(){
    for (int i = 0; i < populationSize; i++){
        population.push_back(initializeIndividual());
    }
}

void GeneticAlgorithm::replicate(){

    vector<Individual*> newPopulation;

    for (int i = 0; i < populationSize; i+=2){

        vector<Individual*> parents = selectParents();

        if (shouldPerformCrossover()){

            vector<Individual*> children = parents.at(0)->crossover(*parents.at(1));

            for (Individual* child : children) newPopulation.push_back(child);

        } else {

            for (Individual* parent : parents) newPopulation.push_back(parent);

        }

    }

    population = std::move(newPopulation);

}

void GeneticAlgorithm::mutate(){

    for (Individual* ind : population) ind->mutate(mutationRate);

}

void GeneticAlgorithm::runIteration(){

    replicate();

    mutate();

    findBestSolution();

}

bool GeneticAlgorithm::isFinished(){
    return currentIteration >= iterations;
}