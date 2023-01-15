#include "KnapsackProblem.h"

ReturnCodes KnapsackProblem::read(string fileName){

    ifstream file(fileName);
    clear();

    if (file.is_open()) {

        int nOfElements;

        // tries to read in number of elements and capacity
        file >> nOfElements >> capacity;

        if (!file) return ReturnCodes::INCORRECT_FORMAT;

        double val, weight;

        while (nOfElements-- > 0 && file){

            file >> val >> weight;
            (*values).push_back(val);
            (*weights).push_back(weight);

        }

        if (!file) return ReturnCodes::INCORRECT_FORMAT;

        file.close();

        if (validate()) return ReturnCodes::SUCCESS;

        else return ReturnCodes::ILLEGAL_VALUE;

    } else return ReturnCodes::FILE_NOT_FOUND;

}

bool KnapsackProblem::initialize(SmartPointer<vector<double>>& weights,
                                SmartPointer<vector<double>>& values,
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
    this->weights = SmartPointer<vector<double>>(new vector<double>());
    this->values = SmartPointer<vector<double>>(new vector<double>());
}

bool KnapsackProblem::validate(){
    return validateCapacity() && validateLengths()
            && validateValues() && validateWeights();
}

bool KnapsackProblem::validateWeights() {
    return std::all_of((*weights).cbegin(), (*weights).cend(), [](double i){ return i > 0; });
};
bool KnapsackProblem::validateValues(){
    return std::all_of((*values).cbegin(), (*values).cend(), [](double i){ return i > 0; });

};
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
