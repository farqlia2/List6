#pragma once
#include "vector"

using namespace std;

class Individual
{
public:
	virtual double getFitness() = 0;
	virtual void mutate() = 0;
	virtual vector<int>* getGenome() = 0;
	virtual pair<Individual*, Individual*> crossover(Individual& other) = 0;
};

