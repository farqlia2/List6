//
// Created by julia on 12/28/2022.
//

#include <iostream>
#include <fstream>
#include "Individual.h"
#include "Constants.h"
#include "GeneticAlgorithm.h"
#include <functional>

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

void mockf();

void testInitializingProblem();

int main(){

    testReadingInstanceFromFile();
    testInitializingProblem();

}

void mockf(){

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

    assert_throws(f, "Weights, values and capacity should be positive",
                  "Shouldn't initialize object with negative value");

    *weights = vector<double>{ 4, 2, 3 };
    *values = vector<double>{ 5, 1, 4, 3 };

    f = [&pointerWeights, &pointerValues, &capacity](){ KnapsackProblem(pointerWeights, pointerValues, capacity); };

    assert_throws(f, "Weights, values and capacity should be positive",
                  "Weights length and values length should be the same");

}

void testReadingInstanceFromFile(){

    std::vector<int> genome {ZERO, ONE, ZERO, ONE};
    KnapsackProblem problem;
    string fileName("C:\\Users\\julia\\source\\repos\\List6\\test_instances\\non_existing.txt");

    function<void(void)> f = [&problem, &fileName](){ problem.read(fileName); };

    assert_throws(f, "Couldn't open the file", "Should throw for non existing file");


    fileName = ("C:\\Users\\julia\\source\\repos\\List6\\test_instances\\incorrect_header.txt");

    f = [&problem, &fileName](){ problem.read(fileName); };
    assert_throws(f, "File is badly formatted", "Shouldn't accept file with incorrect header");

    fileName = ("C:\\Users\\julia\\source\\repos\\List6\\test_instances\\incorrect_format.txt");

    f = [&problem, &fileName](){ problem.read(fileName); };
    assert_throws(f, "File is badly formatted", "Shouldn't accept file with missing values");


    fileName = ("C:\\Users\\julia\\source\\repos\\List6\\test_instances\\text_occurence.txt");

    f = [&problem, &fileName](){ problem.read(fileName); };
    assert_throws(f, "File is badly formatted", "Shouldn't accept file with non-numeric occurence");


    fileName = ("C:\\Users\\julia\\source\\repos\\List6\\test_instances\\negative_value.txt");

    f = [&problem, &fileName](){ problem.read(fileName); };
    assert_throws(f, "Weights, values and capacity should be positive", "Shouldn't accept file with negative value");


    fileName = ("C:\\Users\\julia\\source\\repos\\List6\\test_instances\\correct_mock_file.txt");

    problem.read(fileName);

    assert_equals(problem.getLength(), 4, "Length should agree");
    assert_equals(problem.getFitness(genome), 4.0, "Should correctly compute fitness");

}