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

vector<int> generateGenome(KnapsackIndividual& p1, KnapsackIndividual& p2, int* mask){

    vector<int> genome;
    int genomeLength = p1.getGenome()->size();

    for (int g = 0; g < genomeLength; g++){
        genome.push_back(mask[g] * p1.getGenome()->at(g) + (1 - mask[g]) * p2.getGenome()->at(g));
    }

    return std::move(genome);

}

pair<KnapsackIndividual, KnapsackIndividual>* KnapsackIndividual::crossover(KnapsackIndividual& other){

    int genomeLength = problem->getLength();
    int *mask = new int[genomeLength];
    for (int g = 0; g < genomeLength; g++) {
        mask[g] = ((int) std::round((*crossoverDistrib)(*generator)));
    }

    KnapsackIndividual child1 (problem, generateGenome(*this, other, mask));
    KnapsackIndividual child2 (problem, generateGenome(other, *this, mask));

    return new pair<KnapsackIndividual, KnapsackIndividual>(std::move(child1), std::move(child2));
}


