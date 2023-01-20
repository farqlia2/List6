//
// Created by julia on 1/17/2023.
//

#include "Runner.h"

string concat(string dir, string fileName){
    return dir + "\\" + fileName;
}

void Runner::runAlgorithm(const string& fileName,
                  SharedPointer<Problem>& problemPointer){

    Solution solution;
    if (!solution.read(concat(SOLUTIONS_DIR, fileName)))
        if (DEBUG) std::cout << "Couldn't readValuesAndWeights in optimal solution\n";

    ofstream resultsFile {concat(RESULTS_DIR, fileName)};

    string instanceFile = concat(INSTANCES_DIR, fileName);
    ReturnCode code = (*problemPointer).read(instanceFile);

    if (code == ReturnCode::SUCCESS){

        SharedPointer<IndividualFactory> factory(new BasicIndividualFactory(seed));

        GeneticAlgorithm gA(problemPointer, factory,
                            iterations, mutationRate,
                            crossoverRate, populationSize, tournament, seed);

        while (!gA.isFinished()) {
            gA.runIteration();
            std::cout << "[" << gA.getCurrentIteration() << "] = " <<
                      solution.relativeToOptimal((*gA.getBest()).getFitness()) << "\n";
            resultsFile << solution.relativeToOptimal((*gA.getBest()).getFitness()) << "\n";
        }

        resultsFile.close();

    } else {
        std::cout << "Error code = " << "\n";
    }

}

