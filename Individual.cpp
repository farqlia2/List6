#include "Individual.h"

void BasicIndividual::mutate(double mutationRate)
{
    for (int g = 0; g < genome.size(); g++){
        if (mutationRate < real0to1Distrib(generator))
            genome[g] = 1 - genome[g];
    }
}


vector<int> BasicIndividual::exchangeGenes(Individual& p1,
                                           Individual& p2,
                                           int* mask, int genomeLength){

    vector<int> genome;

    for (int g = 0; g < genomeLength; g++){
        genome.push_back(mask[g] * p1.getGenome()->at(g)
                         + (1 - mask[g]) * p2.getGenome()->at(g));
    }

    return std::move(genome);

}

int* BasicIndividual::generateMask(){

    int* mask = new int[(*problem).getLength()];
    int cutPoint = int1ToGenomeLengthDistrib(generator);
    int g = 0;
    for (; g < cutPoint; g++) mask[g] = 0;
    for (; g < (*problem).getLength(); g++) mask[g] = 1;
    return mask;

}

int* BasicIndividual::generateUniformMask(){

    int* mask = new int[(*problem).getLength()];

    for (int g = 0; g < (*problem).getLength(); g++)

        mask[g] = real0to1Distrib(generator) < 0.5 ? 0 : 1;

    return mask;

}

vector<SharedPointer<Individual>> BasicIndividual::crossover(Individual& other){

    int genomeLength = (*problem).getLength();
    int* mask = generateUniformMask();

    vector<SharedPointer<Individual>> children;
    children.push_back(
            SharedPointer<Individual>(new BasicIndividual(problem, exchangeGenes(*this, other, mask, genomeLength))));
     children.push_back(
             SharedPointer<Individual>(new BasicIndividual(problem, exchangeGenes(other, *this, mask, genomeLength))));

    return children;
}



