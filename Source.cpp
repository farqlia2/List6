//
// Created by julia on 12/28/2022.
//

#include <iostream>
#include <fstream>
#include "Individual.h"
#include "Constants.h"
#include "GeneticAlgorithm.h"

#include <stdexcept>

constexpr void assert_that(bool statement, const char* message){
    if (!statement) throw std::runtime_error{message};
}

template<typename T> constexpr void assert_equals(T actual, T expected, const char* message){
    if (actual != expected) throw std::runtime_error{message};
}

void testReadingInstanceFromFile();

void testReadingFromFile();

void testInitializingProblem();

int main(){

    /*
    std::cout << "Hello\n";

    vector<double> weights = { 4, 2, 3, 2 };
    vector<double> values = { 5, 1, 4, 3 };
    double capacity = 5;

    KnapsackProblem* problem = KnapsackProblem::create(std::move(weights),
                                                       std::move(values), capacity);

    std::vector<int> genome {ZERO, ONE, ZERO, ONE};
    KnapsackIndividual ind;

    std::cout << problem->getFitness(*ind.getGenome());

    GeneticAlgorithm gA(problem, 10, 0.1, 0.6, 100);
     */

    //testReadingInstanceFromFile();

    SmartPointer<string> smPointer(nullptr);

}

void testReadingFromFile(){

    string fileName("C:\\Users\\julia\\source\\repos\\List6\\mock_file.txt");

    fstream file(fileName, ios::in);

    if (file.is_open()){

        int i1 = 0;
        file >> i1;
        cout << i1 << "\n";

        int i2, i3;
        file >> i2 >> i3;
        cout << i2 << ", " << i3 <<"\n";

    }
}

void testInitializingProblem(){


    vector<double>* weights = new vector<double>{ 4, 2, 3, 2 };
    vector<double>* values = new vector<double>{ 5, 1, 4, 3 };
    double capacity = 5;

    SmartPointer<vector<double>> pointerWeights(weights);
    SmartPointer<vector<double>> pointerValues(values);

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

    ReturnCodes code = problem.read(fileName);
    assert_that(code == ReturnCodes::FILE_NOT_FOUND,
                "Shouldn't read from non-existing file");

    assert_equals(problem.getLength(), 0, "Shouldn't throw if the reading operation is not success");
    assert_equals(problem.getFitness(genome), 0.0, "Shouldn't throw if the reading operation is not success");

    fileName = ("C:\\Users\\julia\\source\\repos\\List6\\test_instances\\incorrect_header.txt");

    code = problem.read(fileName);
    assert_that(code == ReturnCodes::INCORRECT_FORMAT,
                "Shouldn't accept file with incorrect header");

    fileName = ("C:\\Users\\julia\\source\\repos\\List6\\test_instances\\incorrect_format.txt");

    code = problem.read(fileName);
    assert_that(code == ReturnCodes::INCORRECT_FORMAT,
                "Shouldn't accept file with missing values");

    fileName = ("C:\\Users\\julia\\source\\repos\\List6\\test_instances\\text_occurence.txt");

    code = problem.read(fileName);
    assert_that(code == ReturnCodes::INCORRECT_FORMAT,
                "Shouldn't accept file with non-numeric occurence");

    fileName = ("C:\\Users\\julia\\source\\repos\\List6\\test_instances\\negative_value.txt");

    code = problem.read(fileName);
    assert_that(code == ReturnCodes::ILLEGAL_VALUE,
                "Shouldn't accept file with negative value");

    fileName = ("C:\\Users\\julia\\source\\repos\\List6\\test_instances\\correct_mock_file.txt");

    code = problem.read(fileName);
    assert_that(code == ReturnCodes::SUCCESS,
                "Should accept correctly formatted instance");

    assert_equals(problem.getLength(), 4, "Length should agree");
    assert_equals(problem.getFitness(genome), 4.0, "Should correctly compute fitness");

}