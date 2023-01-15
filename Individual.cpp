#include "Individual.h"

double KnapsackIndividual::getFitness()
{
    return (*problem).getFitness(*genome);
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

    if (DEBUG)std::cout << "deleting individual\n";

}

vector<int> KnapsackIndividual::exchangeGenes(Individual& p1,
                                              Individual& p2,
                                              int* mask, int genomeLength){

    vector<int> genome;

    for (int g = 0; g < genomeLength; g++){
        genome.push_back(mask[g] * p1.getGenome()->at(g)
                         + (1 - mask[g]) * p2.getGenome()->at(g));
    }

    return std::move(genome);

}

int* KnapsackIndividual::generateMask(){

    int* mask = new int[(*problem).getLength()];
    int cutPoint = (*crossoverDistrib)(*generator);
    int g = 0;
    for (; g < cutPoint; g++) mask[g] = 0;
    for (; g < (*problem).getLength(); g++) mask[g] = 1;
    return mask;

}

vector<Individual*> KnapsackIndividual::crossover(Individual& other){

    int genomeLength = (*problem).getLength();
    int* mask = generateMask();

    vector<Individual*> children;

    KnapsackIndividual* child1 =
            new KnapsackIndividual(problem, exchangeGenes(*this, other, mask, genomeLength));
    KnapsackIndividual* child2 =
            new KnapsackIndividual(problem, exchangeGenes(other, *this, mask, genomeLength));

    children.push_back(child1);
    children.push_back(child2);

    return std::move(children);
}



