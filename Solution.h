//
// Created by julia on 1/17/2023.
//

#ifndef LIST6_SOLUTION_H
#define LIST6_SOLUTION_H

#include "string"
#include "fstream"

using namespace std;

class Solution {
public:

    Solution() : optimalSolution(1.0){};

    bool read(string&& file);

    double relativeToOptimal(double fitness){
        return fitness / optimalSolution;
    }

private:
    double optimalSolution;
};


#endif //LIST6_SOLUTION_H
