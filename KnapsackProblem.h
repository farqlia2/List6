#pragma once

#include <string>
#include <fstream>
#include "vector"
#include "Constants.h"
#include "algorithm"
#include "UniquePointer.h"
#include "SharedPointer.h"
#include "Exceptions.h"
#include <stdexcept>
#include "Problem.h"
#include "ReturnCode.h"

using namespace std;

class KnapsackProblem : public Problem
{
public:

    explicit KnapsackProblem() : weights(SharedPointer<vector<double>>(new vector<double>())),
                                values(SharedPointer<vector<double>>(new vector<double>())),
                                capacity(0) {};

    ReturnCode read(string& fileName);

    /*
    bool validate(vector<double>& weights,
                  vector<double>& values,
                  int capacity);*/
    bool initialize(SharedPointer<vector<double>>& weights,
                    SharedPointer<vector<double>>& values,
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

	SharedPointer<vector<double>> weights;
    SharedPointer<vector<double>> values;

	double capacity;

};
