#include "KnapsackProblem.h"

ReturnCode KnapsackProblem::read(string& fileName) {

    ifstream file(fileName);
    clear();

    if (file.is_open()) {

        int nOfElements;

        // tries to read in number of elements and capacity
        file >> nOfElements >> capacity;

        if (!file) return ReturnCode::INCORRECT_FORMAT;

        read(file, nOfElements);

        if (!file) return ReturnCode::INCORRECT_FORMAT;

        file.close();

        if (validate()) return ReturnCode::SUCCESS;
        else return ReturnCode::ILLEGAL_VALUE;

    } else return ReturnCode::FILE_NOT_FOUND;

}

void KnapsackProblem::read(ifstream& file, int nOfElements){

    double val, weight;
    while (nOfElements-- > 0 && file) {
        file >> val >> weight;
        if (file) {
            (*values).push_back(val);
            (*weights).push_back(weight);
        }
    }
}

bool KnapsackProblem::initialize(SharedPointer<vector<double>>& weights,
                                 SharedPointer<vector<double>>& values,
                                     double capacity){
    this->values = values;
    this->weights = weights;
    this->capacity = capacity;

    bool areArgumentsValid = validate();

    if (!areArgumentsValid) clear();

    return areArgumentsValid;

}


void KnapsackProblem::clear(){
    this->capacity = 0;
    this->weights = SharedPointer<vector<double>>(new vector<double>());
    this->values = SharedPointer<vector<double>>(new vector<double>());
}

bool KnapsackProblem::validate(){
    return validateCapacity() && validateLengths()
           && validateValues() && validateWeights();
}

bool KnapsackProblem::validateWeights() {
    return arePositive(*weights);
};
bool KnapsackProblem::validateValues(){
    return arePositive(*values);
};

bool KnapsackProblem::arePositive(vector<double>& input){
    return std::all_of(input.cbegin(), input.cend(), [](double i){ return i > 0; });
}

bool KnapsackProblem::validateCapacity(){
    return capacity > 0;
};

bool KnapsackProblem::validateLengths(){
    return (*values).size() == (*weights).size();
}

double KnapsackProblem::getFitness(vector<int>& genotype)
{
	double fitness = 0;
	double weight = 0;
	for (int g = 0; g < getLength(); g++) {
		if (genotype.at(g) == ONE) {
			fitness += (*values).at(g);
			weight += (*weights).at(g);
		}
	}
	return weight <= capacity ? fitness : 0; 
}

int KnapsackProblem::getLength()
{
	return (*values).size();
}
