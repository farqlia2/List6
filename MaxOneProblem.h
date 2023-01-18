//
// Created by julia on 1/18/2023.
//

#ifndef LIST6__MAXONEPROBLEM_H
#define LIST6__MAXONEPROBLEM_H

#include "Problem.h"
#include <string>
#include <fstream>

using namespace std;

class MaxOneProblem : public Problem {

public:

    MaxOneProblem() : genomeLength(0) {};

    int getLength() override {
        return genomeLength;
    }

    double getFitness(vector<int>& genome) override {
        double sum = 0;
        if (genome.size() != genomeLength) return 0;
        for (int g : genome) sum += g;
        return sum;
    }

    ReturnCode read(string& filename) override;

    bool initialize(int length) {
        bool isSet = length > 0;
        if (isSet){
            this->genomeLength = length;
        }
        return isSet;
    }

private:

    bool validate();

    int genomeLength;
};


#endif //LIST6__MAXONEPROBLEM_H
