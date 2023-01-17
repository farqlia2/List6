//
// Created by julia on 12/28/2022.
//

#include <iostream>
#include <fstream>
#include "Individual.h"
#include "Constants.h"
#include "GeneticAlgorithm.h"
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
        if (std::string (expected_message) != std::string (exception.what())) throw std::runtime_error{"Other exception has been thrown"};
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

void runProblems(Runner& runner,
                 vector<string>& problemNames);

int main(){

    random_device rd;

    unsigned int seed = rd();

    int iterations = 100;
    double mutationRate = 0.1;
    double crossoverRate = 0.65;
    int populationSize = 100;

    KnapsackProblemRunner runner (populationSize, crossoverRate,
                          mutationRate, iterations, seed);

    vector<string> problemNames {"f2_l-d_kp_20_878"};

    runProblems(runner, problemNames);

    std::cout << "Used seed = " << seed << "\n";

    //testReadingInstanceFromFile();
    //testInitializingProblem();

}

void runProblems(Runner& runner,
                 vector<string>& problemNames){

    for (string& problemName : problemNames){

        std::cout << "Running Problem = " << problemName << "\n";

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

    function<void(void)> f = [&pointerWeights, &pointerValues, &capacity](){ KnapsackProblem(pointerWeights,
                                                                             pointerValues, capacity); };

    assert_does_not_throw(f, "Shouldn't throw for correct values");

    /*
    cout << weights << "\n";
    cout << (&pointerWeights) << "\n";
     // now, weights is going to point to a new memory address
     // we could actually get a memory leak here
    weights = new vector<double>{ 4, 2, 3, 2 };
    cout << weights << "\n";
    cout << (&pointerWeights) << "\n";*/

    *weights = vector<double>{ 4, 2, 3, -2 };
    *values = vector<double>{ 5, 1, 4, 3 };

    f = [&pointerWeights, &pointerValues, &capacity](){ KnapsackProblem(pointerWeights, pointerValues, capacity); };

    assert_throws(f, "Weights should be positive",
                  "Shouldn't initialize object with negative value");

    *weights = vector<double>{ 4, 2, 3 };
    *values = vector<double>{ 5, 1, 4, 3 };

    f = [&pointerWeights, &pointerValues, &capacity](){ KnapsackProblem(pointerWeights, pointerValues, capacity); };

    assert_throws(f, "Weights length and values length should be the same",
                  "Shouldn't initialize object with unequal weights and values lengths");

}

void testReadingInstanceFromFile(){

    std::vector<int> genome {ZERO, ONE, ZERO, ONE};
    KnapsackProblem problem;
    string fileName("C:\\Users\\julia\\source\\repos\\List6\\test_instances\\non_existing.txt");

    function<void(void)> f = [&problem, &fileName](){ problem.read(std::move(fileName)); };

    assert_throws(f, "Couldn't open the file", "Should throw for non existing file");


    fileName = ("C:\\Users\\julia\\source\\repos\\List6\\test_instances\\incorrect_header.txt");

    f = [&problem, &fileName](){ problem.read(std::move(fileName)); };
    assert_throws(f, "File is badly formatted", "Shouldn't accept file with incorrect header");

    fileName = ("C:\\Users\\julia\\source\\repos\\List6\\test_instances\\incorrect_format.txt");

    f = [&problem, &fileName](){ problem.read(std::move(fileName)); };
    assert_throws(f, "File is badly formatted", "Shouldn't accept file with missing values");


    fileName = ("C:\\Users\\julia\\source\\repos\\List6\\test_instances\\text_occurence.txt");

    f = [&problem, &fileName](){ problem.read(std::move(fileName)); };
    assert_throws(f, "File is badly formatted", "Shouldn't accept file with non-numeric occurence");


    fileName = ("C:\\Users\\julia\\source\\repos\\List6\\test_instances\\negative_value.txt");

    f = [&problem, &fileName](){ problem.read(std::move(fileName)); };
    assert_throws(f, "Values should be positive", "Shouldn't accept file with negative value");


    fileName = ("C:\\Users\\julia\\source\\repos\\List6\\test_instances\\correct_mock_file.txt");

    problem.read(std::move(fileName));

    assert_equals(problem.getLength(), 4, "Length should agree");
    assert_equals(problem.getFitness(genome), 4.0, "Should correctly compute fitness");

}