#pragma once

#include <string>
#include "Problem.h"
#include "vector"
#include "Constants.h"
#include "algorithm"
#include "SmartPointer.h"

using namespace std;

class KnapsackProblem : public Problem
{
public:
    void read(string fileName);

    void initialize(SmartPointer<vector<double>> weights,
                    SmartPointer<vector<double>> values,
                    int capacity);

	double getFitness(vector<int>& genotype) override;

	int getLength() override;

private:

    bool validateWeights(vector<double>& weights);
    bool validateValues(vector<double>& values);
    bool validateCapacity(double capacity);

	vector<double> weights;
    vector<double> values;
	double capacity;

};
