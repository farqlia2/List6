//
// Created by julia on 1/17/2023.
//

#include "Solution.h"

bool Solution::read(string&& fileName){

    ifstream file(fileName);
    if (file.is_open()) {

        file >> optimalSolution;

    } else {
        return false;
    }
    return file.fail();
}