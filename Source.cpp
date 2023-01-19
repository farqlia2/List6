//
// Created by julia on 12/28/2022.
//

#include <iostream>
#include "Individual.h"
#include "Constants.h"
#include <functional>
#include "Runner.h"
#include "Globals.h"
#include "MaxOneProblem.h"

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

void readFromFile(){

    string f = "C:\\Users\\julia\\CLionProjects\\List6_\\test_instances\\afile.txt";

    ifstream file {f};

    std::cout << "before reading first two values\n";
    std::cout << std::boolalpha << "file.is_open() = " << file.is_open() << "\n";

    std::cout << std::boolalpha << "file.fail() = " << file.fail() << "\n";

    std::cout << std::boolalpha << "file.bad() = " << file.bad() << "\n";

    std::cout << std::boolalpha << "file.good() = " << file.good() << "\n";

    std::cout << std::boolalpha << "file.eof() = " << file.eof() << "\n";

    int a, b;

    file >> a >> b;

    std::cout << "after reading first two values\n";
    std::cout << std::boolalpha << "file.is_open() = " << file.is_open() << "\n";

    std::cout << std::boolalpha << "file.fail() = " << file.fail() << "\n";

    std::cout << std::boolalpha << "file.bad() = " << file.bad() << "\n";

    std::cout << std::boolalpha << "file.good() = " << file.good() << "\n";

    std::cout << std::boolalpha << "file.eof() = " << file.eof() << "\n";


    file >> a;
    std::cout << "after reading second two values\n";
    std::cout << std::boolalpha << "file.is_open() = " << file.is_open() << "\n";

    std::cout << std::boolalpha << "file.fail() = " << file.fail() << "\n";

    std::cout << std::boolalpha << "file.bad() = " << file.bad() << "\n";

    std::cout << std::boolalpha << "file.good() = " << file.good() << "\n";

    std::cout << std::boolalpha << "file.eof() = " << file.eof() << "\n";


}

SharedPointer<Runner> configure(int populationSize = 100,
                                int iterations = 100,
                                double mutationRate = 0.1,
                                double crossoverRate = 0.65,
                                int tournament = 3);


void runKnapsackProblems(Runner& runner,
                         const vector<string>& problemNames);

void runMaxZeroOneProblems(Runner& runner,
                           const vector<string>& problemNames);

int main(){

    //readFromFile();

    runTests();

    //SharedPointer<Runner> runnerPtr = configure();

    //runKnapsackProblems(*runnerPtr, LOW_DIM_PROBLEMS);

    //runMaxZeroOneProblems(*runnerPtr, ZERO_ONE_PROBLEMS);

    //std::cout << "Used seed = " << (*runnerPtr).getSeed() << "\n";

    //runTests();
}

SharedPointer<Runner> configure(int populationSize,
                                int iterations,
                                double mutationRate,
                                double crossoverRate,
                                int tournament){
    random_device rd;

    unsigned int seed = rd();

    SharedPointer<Runner> runnerPtr (new Runner(populationSize, crossoverRate,
                                  mutationRate, iterations, tournament, seed));

    return std::move(runnerPtr);
}

void runMaxZeroOneProblems(Runner& runner,
                           const vector<string>& problemNames){

    for (const string& problemName : problemNames){

        std::cout << "\nRunning Problem = " << problemName << "\n";

        SharedPointer<Problem> zeroOneProblem (new MaxOneProblem());

        runner.runAlgorithm(problemName, zeroOneProblem);

    }

}

void runKnapsackProblems(Runner& runner,
                         const vector<string>& problemNames){

    for (const string& problemName : problemNames){

        std::cout << "\nRunning Problem = " << problemName << "\n";

        SharedPointer<Problem> knapsackProblem (new KnapsackProblem());

        runner.runAlgorithm(problemName, knapsackProblem);

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

    *weights = vector<double>{ 4, 2, 3, 2 };
    *values = vector<double>{ 5, 1, 4, 3 };
    capacity = -5;

    assert_that(!problem.initialize(pointerWeights, pointerValues, capacity),
                "Initialized object with negative capacity");

    std::vector<int> genome {ZERO, ONE, ZERO, ONE};

    assert_equals(problem.getLength(), 0, "Should return 0 as default length");
    assert_equals(problem.getFitness(genome), 0.0, "Should return 0 as a fitness value");

}

void testReadingInstanceFromFile(){

    std::vector<int> genome {ZERO, ONE, ZERO, ONE};
    KnapsackProblem problem;
    string fileName("C:\\Users\\julia\\source\\repos\\List6\\test_instances\\non_existing.txt");

    ReturnCode code = problem.read(fileName);
    assert_that(code == ReturnCode::FILE_NOT_FOUND,
                "Shouldn't readValuesAndWeights from non-existing file");
    assert_equals(problem.getLength(), 0, "Length should be zero");
    assert_equals(problem.getFitness(genome), 0.0, "Should be zero for fitness");


    fileName = ("C:\\Users\\julia\\source\\repos\\List6\\test_instances\\incorrect_header.txt");

    code = problem.read(fileName);
    assert_that(code == ReturnCode::INCORRECT_FORMAT,
                "Shouldn't accept file with incorrect header");
    assert_equals(problem.getLength(), 0, "Length should be zero");
    assert_equals(problem.getFitness(genome), 0.0, "Should be zero for fitness");


    fileName = ("C:\\Users\\julia\\source\\repos\\List6\\test_instances\\incorrect_format.txt");

    code = problem.read(fileName);
    assert_that(code == ReturnCode::INCORRECT_FORMAT,
                "Shouldn't accept file with missing values");
    assert_equals(problem.getLength(), 0, "Length should be zero");
    assert_equals(problem.getFitness(genome), 0.0, "Should be zero for fitness");


    fileName = ("C:\\Users\\julia\\source\\repos\\List6\\test_instances\\text_occurence.txt");

    code = problem.read(fileName);
    assert_that(code == ReturnCode::INCORRECT_FORMAT,
                "Shouldn't accept file with non-numeric occurence");
    assert_equals(problem.getLength(), 0, "Length should be zero");
    assert_equals(problem.getFitness(genome), 0.0, "Should be zero for fitness");


    fileName = ("C:\\Users\\julia\\source\\repos\\List6\\test_instances\\negative_value.txt");


    code = problem.read(fileName);
    assert_that(code == ReturnCode::ILLEGAL_VALUE,
                "Shouldn't accept file with negative value");
    assert_equals(problem.getLength(), 0, "Length should be zero");
    assert_equals(problem.getFitness(genome), 0.0, "Should be zero for fitness");

    fileName = ("C:\\Users\\julia\\CLionProjects\\List6_\\test_instances\\negative_capacity.txt");

    code = problem.read(fileName);
    assert_that(code == ReturnCode::ILLEGAL_VALUE,
                "Shouldn't accept file with negative capacity");
    assert_equals(problem.getLength(), 0, "Length should be zero");
    assert_equals(problem.getFitness(genome), 0.0, "Should be zero for fitness");

    fileName = ("C:\\Users\\julia\\CLionProjects\\List6_\\test_instances\\negative_genome_length.txt");

    code = problem.read(fileName);
    assert_that(code == ReturnCode::ILLEGAL_VALUE,
                "Shouldn't accept file with negative genome length");
    assert_equals(problem.getLength(), 0, "Length should be zero");
    assert_equals(problem.getFitness(genome), 0.0, "Should be zero for fitness");


    fileName = ("C:\\Users\\julia\\source\\repos\\List6\\test_instances\\correct_mock_file.txt");

    code = problem.read(fileName);
    assert_that(code == ReturnCode::SUCCESS,
                "Should accept correctly formatted instance");

    assert_equals(problem.getLength(), 4, "Length should agree");
    assert_equals(problem.getFitness(genome), 4.0, "Should correctly compute fitness");

}