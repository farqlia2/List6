//
// Created by julia on 1/17/2023.
//

#include "Runner.h"

string concat(const string& dir, const string& fileName){
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
        switch (code) {
            case ReturnCode::ILLEGAL_VALUE :
                std::cout << "ReturnCode::ILLEGAL_VALUE\n";
                break;
            case ReturnCode::INCORRECT_FORMAT :
                std::cout << "ReturnCode::INCORRECT_FORMAT\n";
                break;
            case ReturnCode::FILE_NOT_FOUND :
                std::cout << "ReturnCode::FILE_NOT_FOUND\n";
                break;
        }
    }

}

