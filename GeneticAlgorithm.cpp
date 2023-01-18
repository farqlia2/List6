//
// Created by julia on 12/28/2022.
//

#include "GeneticAlgorithm.h"
GeneticAlgorithm::GeneticAlgorithm(SharedPointer<Problem>& problem, SharedPointer<IndividualFactory>& factory,
                                   int iterations, double mutationRate,
                                   double crossoverRate, int populationSize, int tournament, unsigned int seed) :
                                   problem(problem), factory(factory),
                                   bestSolution(nullptr), seed(seed), iterations(iterations),
                                   mutationRate(mutationRate), crossoverRate(crossoverRate),
                                   currentIteration(0), populationSize(populationSize), tournament(tournament),
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

vector<SharedPointer<Individual>> GeneticAlgorithm::uniformSelection(){

    int parent1 = intDistrib(gen);
    int parent2 = intDistrib(gen);

    while (parent2 == parent1)
        parent2 = intDistrib(gen);

    vector<SharedPointer<Individual>> parents {
        population.at(parent1),
        population.at(parent2)
    };

    return std::move(parents);
}

SharedPointer<Individual> GeneticAlgorithm::tournamentParentSelection(){
    vector<int> subgroup;

    for (int i = 0; i < tournament; i++){
        subgroup.push_back(intDistrib(gen));
    }

    int bestIndividual = subgroup.at(0);
    for (int ind : subgroup)
        if ((*population.at(ind)).getFitness() > (*population.at(bestIndividual)).getFitness())
            bestIndividual = ind;

    // copy
    return population.at(bestIndividual);
}

vector<SharedPointer<Individual>> GeneticAlgorithm::tournamentSelection(){

    SharedPointer<Individual> parent1 (std::move(tournamentParentSelection()));
    SharedPointer<Individual> parent2 (std::move(tournamentParentSelection()));

    while (&parent2 == &parent1) parent2 = tournamentParentSelection();

    return {std::move(parent1), std::move(parent2)};
}

SharedPointer<Individual> GeneticAlgorithm::initializeIndividual(){
    std::vector<int> genome;
    createGenome(genome);
    return std::move((*factory).create(problem, std::move(genome), seed));
}


void GeneticAlgorithm::initializePopulation(){
    populationSize = (populationSize / 2) * 2;
    for (int i = 0; i < populationSize; i++){
        population.push_back(initializeIndividual());
    }
    bestSolution = initializeIndividual();
}

void GeneticAlgorithm::reproduce(){

    vector<SharedPointer<Individual>> newPopulation;

    for (int i = 0; i < populationSize; i+=2){

        vector<SharedPointer<Individual>> parents = uniformSelection();

        if (shouldPerformCrossover()){

            vector<SharedPointer<Individual>> children =
                    (*parents.at(0)).crossover(*parents.at(1));

            for (SharedPointer<Individual>& child : children)
                newPopulation.push_back(std::move(child));

        } else {

            for (SharedPointer<Individual>& parent : parents)
                newPopulation.push_back((*factory).copy(parent));

        }
    }

    population = std::move(newPopulation);
}

void GeneticAlgorithm::mutate(){

    for (SharedPointer<Individual>& ind : population)
        (*ind).mutate(mutationRate);

}

void GeneticAlgorithm::runIteration(){

    reproduce();

    mutate();

    findBestSolution();

    currentIteration++;
}

void GeneticAlgorithm::findBestSolution(){

    int indexOfBestSolution = -1;

    for (int i = 0; i < populationSize; i++) {
        if ((*population.at(i)).getFitness() > (*bestSolution).getFitness()) indexOfBestSolution = i;
    }

    if (indexOfBestSolution >= 0) {
        bestSolution = (*factory).copy(population.at(indexOfBestSolution));
    }
}

bool GeneticAlgorithm::isFinished(){
    return currentIteration >= iterations;
}