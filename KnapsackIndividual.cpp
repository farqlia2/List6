#include "KnapsackIndividual.h"

KnapsackIndividual::KnapsackIndividual(vector<int>&& genome) {
    this->genome = genome;
    this->fitness = 0;
};

bool KnapsackIndividual::mutate(double mutationRate)
{
    return false;
}

KnapsackIndividual* KnapsackIndividual::crossover(KnapsackIndividual& other)
{
    return nullptr;
}
