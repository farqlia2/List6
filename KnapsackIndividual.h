#ifndef LIST6_KNAPSACKINDIVIDUAL_H
#define LIST6_KNAPSACKINDIVIDUAL_H
#include <vector>

using namespace std;

class KnapsackIndividual
{
public:
    KnapsackIndividual(vector<int>&& genome);
    void setFitness(double newFitness) {this->fitness = newFitness; };
    double getFitness() {return this->fitness;}
    bool mutate(double mutationRate);
    vector<int>* getGenome() { return &genome; };
    KnapsackIndividual* crossover(KnapsackIndividual& other);
private:
    double fitness;
    vector<int> genome;
};



#endif