#include "KnapsackIndividual.h"

double KnapsackIndividual::getFitness()
{
    return problem->getFitness(*this);
}

void KnapsackIndividual::mutate()
{

}

Individual* KnapsackIndividual::crossover(Individual& other)
{
    return nullptr;
}
