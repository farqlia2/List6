//
// Created by julia on 1/17/2023.
//

#include "Runner.h"

string concat(string dir, string fileName){
    return dir + "\\" + fileName;
}

void KnapsackProblemRunner::runAlgorithm(const string& fileName) {

     KnapsackProblem* KProblem = new KnapsackProblem();

    Solution solution;
    if (!solution.read(concat(SOLUTIONS_DIR, fileName)))
        if (DEBUG) std::cout << "Couldn't read in optimal solution\n";

    ofstream resultsFile {concat(RESULTS_DIR, fileName)};

    string instanceFile = concat(INSTANCES_DIR, fileName);
    ReturnCode code = KProblem->read(instanceFile);

    if (code == ReturnCode::SUCCESS){

        SharedPointer<IndividualFactory> factory(new BasicIndividualFactory());
        SharedPointer<Problem> problemPointer(KProblem);

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
