//
// Created by julia on 12/28/2022.
//

#include <iostream>
#include "KnapsackProblem.h"
#include "KnapsackIndividual.h"
#include "Constants.h"
#include "GeneticAlgorithm.h"
int main(){

    std::cout << "Hello\n";

    vector<double> weights = { 4, 2, 3, 2 };
    vector<double> values = { 5, 1, 4, 3 };
    double capacity = 5;

    KnapsackProblem* problem = KnapsackProblem::create(std::move(weights),
                                                       std::move(values), capacity);

    std::vector<int> genome {ZERO, ONE, ZERO, ONE};
    KnapsackIndividual ind(std::move(genome));

    std::cout << problem->getFitness(ind);

    GeneticAlgorithm gA(problem, 10, 0.1, 0.6, 100);

}