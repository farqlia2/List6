//
// Created by julia on 12/28/2022.
//

#include "GeneticAlgorithm.h"
GeneticAlgorithm::GeneticAlgorithm(SharedPointer<Problem>& problem, SharedPointer<IndividualFactory>& factory,
                                   int iterations, double mutationRate,
                                   double crossoverRate, int populationSize, int tournament, unsigned int seed) :
        problem(problem), individualsFactory(factory),
        bestSolution(nullptr), iterations(iterations),
        mutationRate(mutationRate), crossoverRate(crossoverRate),
        currentIteration(0), populationSize(populationSize),
        tournament(tournament),
        generator(seed), realDistrib(0, 1), intDistrib(0, populationSize - 1){

    initializePopulation();
}


bool GeneticAlgorithm::shouldPerformCrossover(){
    return realDistrib(generator) < crossoverRate;
}


vector<SharedPointer<Individual>> GeneticAlgorithm::uniformSelection(){

    int parent1 = intDistrib(generator);
    int parent2 = intDistrib(generator);

    while (parent2 == parent1)
        parent2 = intDistrib(generator);

    vector<SharedPointer<Individual>> parents {
        population.at(parent1),
        population.at(parent2)
    };

    return std::move(parents);
}

SharedPointer<Individual> GeneticAlgorithm::tournamentParentSelection(){
    vector<int> tournamentGroup;

    for (int i = 0; i < tournament; i++){
        tournamentGroup.push_back(intDistrib(generator));
    }

    int bestIndividual = tournamentGroup.at(0);
    for (int ind : tournamentGroup)
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
    SharedPointer<Individual> individual ((*individualsFactory).create(problem));
    (*individual).computeFitness();
    return std::move(individual);
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
    vector<SharedPointer<Individual>> parents;
    vector<SharedPointer<Individual>> children;

    for (int i = 0; i < populationSize; i+=2){

        parents = tournamentSelection();

        if (shouldPerformCrossover()){

            children = (*parents.at(0)).crossover(*parents.at(1));

            for (SharedPointer<Individual>& child : children)
                newPopulation.push_back(std::move(child));

        } else {

            for (SharedPointer<Individual>& parent : parents)
                newPopulation.push_back((*individualsFactory).copy(parent));

        }
    }

    population = std::move(newPopulation);
}

void GeneticAlgorithm::mutate() {

    for (SharedPointer<Individual> &ind: population)
        (*ind).mutate(mutationRate);

}
void GeneticAlgorithm::computeFitness(){
    for (SharedPointer<Individual> &ind: population)
        (*ind).computeFitness();
}

void GeneticAlgorithm::runIteration(){

    reproduce();

    mutate();

    computeFitness();

    findBestSolution();

    currentIteration++;
}

void GeneticAlgorithm::findBestSolution(){

    int indexOfBestSolution = -1;

    for (int i = 0; i < populationSize; i++) {
        if ((*population.at(i)).getFitness() > (*bestSolution).getFitness()) indexOfBestSolution = i;
    }

    if (indexOfBestSolution >= 0) {
        bestSolution = (*individualsFactory).copy(population.at(indexOfBestSolution));
    }
}

bool GeneticAlgorithm::isFinished(){
    return currentIteration >= iterations;
}