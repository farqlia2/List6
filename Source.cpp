//
// Created by julia on 12/28/2022.
//

#include <iostream>
#include "Individual.h"
#include "Constants.h"
#include <functional>
#include "Runner.h"
#include "Globals.h"

#include <stdexcept>

constexpr void assert_that(bool statement, const char* message){
    if (!statement) throw std::runtime_error{message};
}

template<typename T> constexpr void assert_equals(T actual, T expected, const char* message){
    if (actual != expected) throw std::runtime_error{message};
}

void assert_throws(std::function<void(void)>& f, const char* expected_message, const char* message){
    try {
        f();
    } catch (exception& exception) {
        if (std::string (expected_message) != std::string (exception.what()))
            throw std::runtime_error{"Other exception has been thrown"};
        return;
    };
    throw std::runtime_error{message};
}

void assert_does_not_throw(std::function<void(void)>& f, const char* message){
    try{
        f();
    } catch (exception& exception){
        throw std::runtime_error{message};
    }
}

void testReadingInstanceFromFile();

void testInitializingProblem();

void runTests(){
    testInitializingProblem();
    testReadingInstanceFromFile();
}

SharedPointer<Runner> configure(int populationSize = 100,
                                int iterations = 100,
                                double mutationRate = 0.1,
                                double crossoverRate = 0.65,
                                int tournament = 2);

void runProblems(Runner& runner,
                 const vector<string>& problemNames);

int main(){

    SharedPointer<Runner> runnerPtr = configure();

    runProblems(*runnerPtr, LOW_DIM_PROBLEMS);

    std::cout << "Used seed = " << (*runnerPtr).getSeed() << "\n";

    //runTests();
}

SharedPointer<Runner> configure(int populationSize,
                                int iterations,
                                double mutationRate,
                                double crossoverRate,
                                int tournament){
    random_device rd;

    unsigned int seed = rd();

    SharedPointer<Runner> runnerPtr (new KnapsackProblemRunner(populationSize, crossoverRate,
                                  mutationRate, iterations, tournament, seed));

    return std::move(runnerPtr);
}

void runProblems(Runner& runner,
                 const vector<string>& problemNames){

    for (const string& problemName : problemNames){

        std::cout << "\nRunning Problem = " << problemName << "\n";

        runner.runAlgorithm(problemName);

    }

}



void testInitializingProblem(){


    vector<double>* weights = new vector<double>{ 4, 2, 3, 2 };
    vector<double>* values = new vector<double>{ 5, 1, 4, 3 };
    double capacity = 5;

    SharedPointer<vector<double>> pointerWeights(weights);
    SharedPointer<vector<double>> pointerValues(values);

    KnapsackProblem problem;

    assert_that(problem.initialize(pointerWeights, pointerValues, capacity),
                "Couldn't initialize object with correct arguments");

    /*
    cout << weights << "\n";
    cout << (&pointerWeights) << "\n";
     // now, weights is going to point to a new memory address
     // we could actually get a memory leak here
    weights = new vector<double>{ 4, 2, 3, 2 };
    cout << weights << "\n";
    cout << (&pointerWeights) << "\n";
     */

    *weights = vector<double>{ 4, 2, 3, -2 };
    *values = vector<double>{ 5, 1, 4, 3 };

    assert_that(!problem.initialize(pointerWeights, pointerValues, capacity),
                "Initialized object with negative value");

    *weights = vector<double>{ 4, 2, 3 };
    *values = vector<double>{ 5, 1, 4, 3 };

    assert_that(!problem.initialize(pointerWeights, pointerValues, capacity),
                "Initialized object with unequal argument lengths");

    std::vector<int> genome {ZERO, ONE, ZERO, ONE};

    cout << problem.getLength() << "\n";
    cout << problem.getFitness(genome) << "\n";

}

void testReadingInstanceFromFile(){

    std::vector<int> genome {ZERO, ONE, ZERO, ONE};
    KnapsackProblem problem;
    string fileName("C:\\Users\\julia\\source\\repos\\List6\\test_instances\\non_existing.txt");

    ReturnCode code = problem.read(fileName);
    assert_that(code == ReturnCode::FILE_NOT_FOUND,
                "Shouldn't read from non-existing file");


    fileName = ("C:\\Users\\julia\\source\\repos\\List6\\test_instances\\incorrect_header.txt");

    code = problem.read(fileName);
    assert_that(code == ReturnCode::INCORRECT_FORMAT,
                "Shouldn't accept file with incorrect header");

    fileName = ("C:\\Users\\julia\\source\\repos\\List6\\test_instances\\incorrect_format.txt");

    code = problem.read(fileName);
    assert_that(code == ReturnCode::INCORRECT_FORMAT,
                "Shouldn't accept file with missing values");


    fileName = ("C:\\Users\\julia\\source\\repos\\List6\\test_instances\\text_occurence.txt");

    code = problem.read(fileName);
    assert_that(code == ReturnCode::INCORRECT_FORMAT,
                "Shouldn't accept file with non-numeric occurence");


    fileName = ("C:\\Users\\julia\\source\\repos\\List6\\test_instances\\negative_value.txt");

    code = problem.read(fileName);
    assert_that(code == ReturnCode::ILLEGAL_VALUE,
                "Shouldn't accept file with negative value");


    fileName = ("C:\\Users\\julia\\source\\repos\\List6\\test_instances\\correct_mock_file.txt");

    code = problem.read(fileName);
    assert_that(code == ReturnCode::SUCCESS,
                "Should accept correctly formatted instance");

    assert_equals(problem.getLength(), 4, "Length should agree");
    assert_equals(problem.getFitness(genome), 4.0, "Should correctly compute fitness");

}