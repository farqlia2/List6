#include "KnapsackIndividual.h"

double KnapsackIndividual::getFitness()
{
    return problem->getFitness(*genome);
}

void KnapsackIndividual::mutate(double mutationRate)
{
    for (int g = 0; g < genome->size(); g++){
        if (mutationRate < (*mutationDistrib)(*generator))
            (*genome)[g] = 1 - (*genome)[g];
    }
}

KnapsackIndividual::~KnapsackIndividual(){

    delete genome;
    delete mutationDistrib;
    delete crossoverDistrib;
    delete generator;

    if (DEBUG )std::cout << "deleting individual\n";

}

vector<int> exchangeGenes(Individual& p1,
                          Individual& p2,
                          int cutPoint, int genomeLength){

    vector<int> genome;

    int g = 0;
    for (; g < cutPoint; g++) genome.push_back(p1.getGenome()->at(g));
    for (; g < genomeLength; g++) genome.push_back(p1.getGenome()->at(g));

    return std::move(genome);

}

vector<Individual*> KnapsackIndividual::crossover(Individual& other){

    int genomeLength = problem->getLength();
    int cutPoint = (*crossoverDistrib)(*generator);

    vector<Individual*> children;

    KnapsackIndividual* child1 =
            new KnapsackIndividual(problem, exchangeGenes(*this, other, cutPoint, genomeLength));
    KnapsackIndividual* child2 =
            new KnapsackIndividual(problem, exchangeGenes(other, *this, cutPoint, genomeLength));

    children.push_back(child1);
    children.push_back(child2);

    return children;
}


