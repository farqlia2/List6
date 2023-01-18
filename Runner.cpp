//
// Created by julia on 1/17/2023.
//

#include "Runner.h"

string concat(string dir, string fileName){
    return dir + "\\" + fileName;
}

void KnapsackProblemRunner::runAlgorithm(const string& fileName) {

    SharedPointer<Problem> problemPointer =
            SharedPointer<Problem>(new KnapsackProblem());

    Solution solution;
    if (!solution.read(concat(SOLUTIONS_DIR, fileName)))
        if (DEBUG) std::cout << "Couldn't read in optimal solution\n";

    ofstream resultsFile {concat(RESULTS_DIR, fileName)};

    try {

        (*problemPointer).read(concat(INSTANCES_DIR, fileName));

        GeneticAlgorithm gA(problemPointer,
                            iterations, mutationRate,
                            crossoverRate, populationSize, seed);

        while (!gA.isFinished()) {
            gA.runIteration();
            std::cout << "[" << gA.getCurrentIteration() << "] = " <<
            solution.relativeToOptimal((*gA.getBest()).getFitness()) << "\n";
            resultsFile << solution.relativeToOptimal((*gA.getBest()).getFitness()) << "\n";
        }

        resultsFile.close();

    } catch (exception& exc){
        std::cout << exc.what();
    }

}
