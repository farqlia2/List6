#pragma once

#include "Individual.h"
class Problem
{
public:
	virtual double getFitness(Individual* ind) = 0;
	virtual int getSize() = 0;
};

