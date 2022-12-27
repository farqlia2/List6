#include "Individual.h"

Individual* Individual::crossover(Individual& other) {

	Individual* children = new Individual[2];
	children[0] = *this;
	children[1] = other;
	return children;
}

double Individual::getFitness() { return 0; }

void Individual::mutate() {};
