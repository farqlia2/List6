#pragma once
#ifndef LIST6_PROBLEM_H
#define LIST6_PROBLEM_H

#include "vector"
#include "ReturnCode.h"
#include <string>

using namespace std;

class Problem
{
public:
    virtual ~Problem() = default;
	virtual double getFitness(vector<int>& genome) = 0;
	virtual int getLength() = 0;
    virtual ReturnCode read(string& filename) = 0;
};
#endif

