#pragma once

#include <string>
#include <fstream>
#include "Problem.h"
#include "vector"
#include "Constants.h"
#include "algorithm"
#include "SmartPointer.h"

using namespace std;

enum class ReturnCodes: int {
    SUCCESS, INCORRECT_FORMAT, FILE_NOT_FOUND, ILLEGAL_VALUE
};

class KnapsackProblem : public Problem
{
public:

    KnapsackProblem() : weights(SmartPointer<vector<double>>(new vector<double>())),
                        values(SmartPointer<vector<double>>(new vector<double>())),
                        capacity(0) {};
    // Enum type for returning error codes
    // Format for reading from file
    // n wmax
    // v1 w1
    // ...
    // vn wn
    ReturnCodes read(string fileName);

    /*
    bool validate(vector<double>& weights,
                  vector<double>& values,
                  int capacity);*/
    bool initialize(SmartPointer<vector<double>>& weights,
                    SmartPointer<vector<double>>& values,
                    double capacity);

	double getFitness(vector<int>& genotype) override;

	int getLength() override;

private:

    bool validateWeights();
    bool validateValues();
    bool validateCapacity();
    bool validateLengths();

    bool validate();

    void clear();

	SmartPointer<vector<double>> weights;
    SmartPointer<vector<double>> values;

	double capacity;

};
