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

pair<KnapsackIndividual*, KnapsackIndividual*>* KnapsackIndividual::crossover(KnapsackIndividual& other){


    return nullptr;
}
