//
// Created by julia on 1/18/2023.
//

#ifndef LIST6__INDIVIDUALFACTORY_H
#define LIST6__INDIVIDUALFACTORY_H


#include "SharedPointer.h"
#include "BasicIndividual.h"

class IndividualFactory {
public:
    virtual ~IndividualFactory() = default;
    virtual SharedPointer<Individual> copy(SharedPointer<Individual>& other) = 0;
    virtual SharedPointer<Individual> create(SharedPointer<Problem>& problem) = 0;
};

class BasicIndividualFactory : public IndividualFactory {

public:

    explicit BasicIndividualFactory(unsigned int seed) : generatorPointer(new mt19937(seed)) {};

    SharedPointer<Individual> copy(SharedPointer<Individual>& other) override {
        return std::move(SharedPointer<Individual>(new BasicIndividual(*other)));
    }
    SharedPointer<Individual> create(SharedPointer<Problem>& problem) override {
        return std::move(SharedPointer<Individual>(new BasicIndividual(problem, generatorPointer)));
    }
private:
    SharedPointer<mt19937> generatorPointer;
};




#endif //LIST6__INDIVIDUALFACTORY_H
