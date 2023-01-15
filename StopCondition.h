//
// Created by julia on 1/13/2023.
//
# pragma once
#ifndef LIST6_STOPCONDITION_H
#define LIST6_STOPCONDITION_H

#include "GeneticAlgorithm.h"

/*
class StopCondition {

public:
    StopCondition() = default;
    virtual bool isFinished(GeneticAlgorithm& algorithm) {return true;};
};

class IterationsStopCondition : public StopCondition {

public:
    explicit IterationsStopCondition() : iterations(0) {}

    explicit IterationsStopCondition(int iterations) : iterations(iterations){}

    bool isFinished(GeneticAlgorithm& algorithm) override {
        return algorithm.getCurrentIteration() > iterations;
    }

private:

    int iterations;

};*/

#endif //LIST6_STOPCONDITION_H
