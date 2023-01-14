#pragma once

#include "Individual.h"
class Problem
{
public:
	virtual double getFitness(vector<int>& genome) = 0;
	virtual int getLength() = 0;
};

