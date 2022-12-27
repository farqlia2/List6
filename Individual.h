#pragma once
#include "Problem.h"
#include "vector"

class Individual
{
public:
	virtual double getFitness();
	virtual void mutate();
	virtual vector<int>* getGenome() = 0;
	virtual Individual* crossover(Individual& other);
};

