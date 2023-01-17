//
// Created by julia on 1/17/2023.
//

#include "Runner.h"

string concat(string dir, string fileName){
    return dir + "//" + fileName + ".txt";
}

bool KnapsackProblemRunner::runAlgorithm(string& fileName) {

    SharedPointer<Problem> problemPointer =
            SharedPointer<Problem>(new KnapsackProblem());

    Solution solution;
    //if (!solution.read(concat(SOLUTIONS_DIR, fileName)))
      //  std::cout << "Couldn't read in optimal solution\n";

    try {

        (*problemPointer).read(concat(INSTANCES_DIR, fileName));

        GeneticAlgorithm gA(problemPointer,
                            iterations, mutationRate,
                            crossoverRate, populationSize, seed);

        while (!gA.isFinished()) {
            gA.runIteration();
            std::cout << "[" << gA.getCurrentIteration() << "] = " <<
            solution.relativeToOptimal((*gA.getBest()).getFitness()) << "\n";
        }


    } catch (exception& exc){
        std::cout << exc.what();
        return false;
    }

    return true;

}

bool KnapsackProblemRunner::runAlgorithm() {

    return false;

};