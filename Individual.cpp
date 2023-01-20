#include "Individual.h"

void BasicIndividual::createGenome(){

    for (int j = 0; j < (*problem).getLength(); j++) {
        int gene = (int) std::round(realDistrib(*generatorPointer));
        genome.push_back(gene);
    }
}


void BasicIndividual::mutate(double mutationRate)
{
    for (int g = 0; g < genome.size(); g++){
        if (mutationRate < realDistrib(*generatorPointer))
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

int* BasicIndividual::generateOnePointMask(){

    int* mask = new int[(*problem).getLength()];
    int cutPoint = intDistrib(*generatorPointer);
    int g = 0;
    for (; g < cutPoint; g++) mask[g] = 0;
    for (; g < (*problem).getLength(); g++) mask[g] = 1;
    return mask;

}

int* BasicIndividual::generateUniformMask(){

    int* mask = new int[(*problem).getLength()];

    for (int g = 0; g < (*problem).getLength(); g++)

        mask[g] = std::round(realDistrib(*generatorPointer));

    return mask;

}

vector<SharedPointer<Individual>> BasicIndividual::crossover(Individual& other){

    int genomeLength = (*problem).getLength();
    int* mask = generateUniformMask();

    vector<SharedPointer<Individual>> children;
    children.push_back(
            SharedPointer<Individual>(new BasicIndividual(problem,
                                                          exchangeGenes(*this, other, mask, genomeLength), generatorPointer)));
     children.push_back(
             SharedPointer<Individual>(new BasicIndividual(problem,
                                                           exchangeGenes(other, *this, mask, genomeLength), generatorPointer)));

    return children;
}



