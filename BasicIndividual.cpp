#include "BasicIndividual.h"

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

void BasicIndividual::mutate(double mutationRate,
            SharedPointer<Individual>& other){

    for (int g = 0; g < genome.size(); g++){
        if (genome.at(g) != (*other).getGenome()->at(g)) {
            if (mutationRate < realDistrib(*generatorPointer))
                genome[g] = 1 - genome[g];
        }
    }

}

vector<int> BasicIndividual::exchangeGenes(Individual& p1,
                                           Individual& p2,
                                           vector<int>& mask, int genomeLength){

    vector<int> genome;

    for (int g = 0; g < genomeLength; g++){
        genome.push_back(mask.at(g)* p1.getGenome()->at(g)
                         + (1 - mask.at(g)) * p2.getGenome()->at(g));
    }

    return std::move(genome);

}

vector<int> BasicIndividual::generateOnePointMask(){

    vector<int> mask;
    int cutPoint = intDistrib(*generatorPointer);
    int g = 0;
    for (; g < cutPoint; g++) mask.push_back(0);
    for (; g < (*problem).getLength(); g++) mask.push_back(1);
    return std::move(mask);

}


vector<SharedPointer<Individual>> BasicIndividual::crossover(Individual& other){

    int genomeLength = (*problem).getLength();
    vector<int> mask = std::move(generateOnePointMask());

    vector<SharedPointer<Individual>> children;
    children.push_back(
            SharedPointer<Individual>(new BasicIndividual(problem,
                                                          exchangeGenes(*this, other, mask, genomeLength), generatorPointer)));
     children.push_back(
             SharedPointer<Individual>(new BasicIndividual(problem,
                                                           exchangeGenes(other, *this, mask, genomeLength), generatorPointer)));

    return children;
}



