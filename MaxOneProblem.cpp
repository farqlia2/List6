//
// Created by julia on 1/18/2023.
//

#include "MaxOneProblem.h"
ReturnCode MaxOneProblem::read(string& filename){

    ifstream file{filename};
    genomeLength = 0;

    if (file.is_open()){

        file >> genomeLength;

    } else {
        return ReturnCode::FILE_NOT_FOUND;
    }
    if (!file) return ReturnCode::INCORRECT_FORMAT;

    bool isArgumentValid = validate();

    if (!isArgumentValid) {
        genomeLength = 0;
        return ReturnCode::ILLEGAL_VALUE;
    }

    return ReturnCode::SUCCESS;
}

bool MaxOneProblem::validate(){
    return genomeLength > 0;
}