//
// Created by julia on 1/20/2023.
//

#ifndef LIST6__BASICINDIVIDUAL_H
#define LIST6__BASICINDIVIDUAL_H

#include "Individual.h"

class BasicIndividual : public Individual {
public:

    BasicIndividual(SharedPointer<Problem>& problem,
                    vector<int>&& genome,
                    SharedPointer<mt19937>& generator) : Individual(problem, std::move(genome),
                                                                    generator),
                                                         realDistrib(0, 1),
                                                         intDistrib(1, (*problem).getLength() - 1)
    {
    }

    BasicIndividual(SharedPointer<Problem>& problem,
                    SharedPointer<mt19937>& generator) : Individual(problem, generator),
                                                         realDistrib(0, 1),
                                                         intDistrib(1, (*problem).getLength() - 1)
    {
        createGenome();
    };

    explicit BasicIndividual(const Individual& other): Individual(other),
                                                       realDistrib(0, 1),
                                                       intDistrib(1, (*problem).getLength() - 1){};

    void mutate(double mutationRate) override;

    vector<SharedPointer<Individual>> crossover(Individual& other) override;

private:

    static vector<int> exchangeGenes(Individual& p1,
                                     Individual& p2,
                                     vector<int>& mask,
                                     int genomeLength);

    vector<int> generateOnePointMask();
    int* generateUniformMask();

    void createGenome();

    uniform_real_distribution<double> realDistrib;
    uniform_int_distribution<int> intDistrib;

};


#endif //LIST6__BASICINDIVIDUAL_H
