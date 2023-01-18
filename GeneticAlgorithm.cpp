//
// Created by julia on 12/28/2022.
//

#include "GeneticAlgorithm.h"
GeneticAlgorithm::GeneticAlgorithm(SharedPointer<Problem>& problem,
                                   int iterations, double mutationRate,
                                   double crossoverRate, int populationSize, int seed) :
                                   problem(problem),
                                   bestSolution(nullptr), seed(seed), iterations(iterations),
                                   mutationRate(mutationRate), crossoverRate(crossoverRate),
                                   currentIteration(0), populationSize(populationSize),
                                   gen(seed), realDistrib(0, 1), intDistrib(0, populationSize - 1){

    initializePopulation();
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

    vector<Individual*> parents {
        &population.at(parent1),
        &population.at(parent2)
    };

    return std::move(parents);
}

UniquePointer<Individual> GeneticAlgorithm::initializeIndividual(){
    std::vector<int> genome;
    createGenome(genome);
    return UniquePointer<Individual>(new BasicIndividual(problem, std::move(genome)));
}


void GeneticAlgorithm::initializePopulation(){
    populationSize = (populationSize / 2) * 2;
    for (int i = 0; i < populationSize; i++){
        population.push_back(initializeIndividual());
    }
    bestSolution = SharedPointer<Individual>(new BasicIndividual(*(initializeIndividual())));
}

void GeneticAlgorithm::replicate(){

    vector<UniquePointer<Individual>> newPopulation;

    for (int i = 0; i < populationSize; i+=2){

        vector<Individual*> parents = selectParents();

        if (shouldPerformCrossover()){

            vector<UniquePointer<Individual>> children =
                    parents.at(0)->crossover(*parents.at(1));

            for (UniquePointer<Individual>& child : children)
                newPopulation.push_back(std::move(child));

        } else {

            for (Individual* parent : parents)
                newPopulation.push_back(UniquePointer<Individual>(new BasicIndividual(*parent)));

        }
    }

    population = std::move(newPopulation);
}

void GeneticAlgorithm::mutate(){

    for (UniquePointer<Individual>& ind : population)
        (*ind).mutate(mutationRate);

}

void GeneticAlgorithm::runIteration(){

    replicate();

    mutate();

    findBestSolution();

    currentIteration++;
}

void GeneticAlgorithm::findBestSolution(){

    int indexOfBestSolution = -1;

    for (int i = 0; i < populationSize; i++) {
        if ((*population.at(i)).getFitness() > (*bestSolution).getFitness()) indexOfBestSolution = i;
    }

    if (indexOfBestSolution >= 0) bestSolution =
            SharedPointer<Individual>(new BasicIndividual(*population.at(indexOfBestSolution)));
}

bool GeneticAlgorithm::isFinished(){
    return currentIteration >= iterations;
}