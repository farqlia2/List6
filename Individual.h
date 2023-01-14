#pragma once
#include "vector"

using namespace std;

# define DEFAULT_SEED 0

class Individual
{
public:
    Individual() : seed(DEFAULT_SEED) {};
    explicit Individual(int seed) : seed(seed) {};
	virtual double getFitness() = 0;
	virtual void mutate(double mutationRate) = 0;
	virtual vector<int>* getGenome() = 0;
	virtual vector<Individual*> crossover(Individual& other) = 0;
    virtual int getSeed() {return seed;}
private:
    int seed;
};

