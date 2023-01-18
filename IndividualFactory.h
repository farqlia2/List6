//
// Created by julia on 1/18/2023.
//

#ifndef LIST6__INDIVIDUALFACTORY_H
#define LIST6__INDIVIDUALFACTORY_H


#include "SharedPointer.h"
#include "Individual.h"

class IndividualFactory {
public:
    virtual ~IndividualFactory() = default;
    virtual SharedPointer<Individual> copy(SharedPointer<Individual>& other) = 0;
    virtual SharedPointer<Individual> create(SharedPointer<Problem>& problem,
                                             vector<int>&& genome,
                                             unsigned int seed) = 0;
};

class BasicIndividualFactory : public IndividualFactory {

public:
    SharedPointer<Individual> copy(SharedPointer<Individual>& other) override {
        return std::move(SharedPointer<Individual>(new BasicIndividual(*other)));
    }
    SharedPointer<Individual> create(SharedPointer<Problem>& problem,
                                     vector<int>&& genome,
                                     unsigned int seed) override {
        return std::move(SharedPointer<Individual>(new BasicIndividual(problem, std::move(genome), seed)));
    }
};




#endif //LIST6__INDIVIDUALFACTORY_H
