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

using namespace std;
/*
enum class ReturnCodes: int {
    SUCCESS, INCORRECT_FORMAT, FILE_NOT_FOUND, ILLEGAL_VALUE
};
 */

class KnapsackProblem : public Problem
{
public:

    explicit KnapsackProblem() : weights(SharedPointer<vector<double>>(new vector<double>())),
                                values(SharedPointer<vector<double>>(new vector<double>())),
                                capacity(0) {};

    KnapsackProblem(SharedPointer<vector<double>> &weights,
                    SharedPointer<vector<double>> &values,
                    double capacity) noexcept(false);

    // Enum type for returning error codes
    // Format for reading from file
    // n wmax
    // v1 w1
    // ...
    // vn wn
    void read(string&& fileName) noexcept(false) override;

	double getFitness(vector<int>& genotype) override;

	int getLength() override;

private:

    bool validateWeights();
    bool validateValues();
    bool validateCapacity();
    bool validateLengths();

    void validate() noexcept(false);

    void clear();

    bool read(ifstream& file);

	SharedPointer<vector<double>> weights;
    SharedPointer<vector<double>> values;

	double capacity;

};
