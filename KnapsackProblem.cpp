#include "KnapsackProblem.h"

ReturnCode KnapsackProblem::readInstance(std::string& fileName) {

    ifstream file(fileName);
    clear();

    if (file.is_open()) {

        if (!readHeader(file)) return ReturnCode::INCORRECT_FORMAT;

        if (!validateCapacity() || !validateGenomeLength())
            return ReturnCode::ILLEGAL_VALUE;

        if (!readValuesAndWeights(file)) return ReturnCode::INCORRECT_FORMAT;

        file.close();

        if (validateValues() && validateWeights())
            return ReturnCode::SUCCESS;

        else return ReturnCode::ILLEGAL_VALUE;

    } else return ReturnCode::FILE_NOT_FOUND;

}

ReturnCode KnapsackProblem::read(std::string& fileName){

    ReturnCode code = readInstance(fileName);

    if (code != ReturnCode::SUCCESS) {
        clear();
    }
    return code;
}

bool KnapsackProblem::readHeader(ifstream& file){
    // tries to readValuesAndWeights in number of elements and capacity
    file >> genomeLength >> capacity;
    return file.good();
}

bool KnapsackProblem::readValuesAndWeights(ifstream& file){

    double val, weight;

    for (int line = 0; line < genomeLength; line++){
        file >> val >> weight;
        (*values).push_back(val);
        (*weights).push_back(weight);
    }

    return !file.fail();
}

bool KnapsackProblem::initialize(SharedPointer<vector<double>>& weights,
                                 SharedPointer<vector<double>>& values,
                                     double capacity){
    this->values = values;
    this->weights = weights;
    this->capacity = capacity;
    this->genomeLength = (*weights).size();

    bool areArgumentsValid = validateLengths() && validateWeights()
            && validateValues() && validateCapacity();

    if (!areArgumentsValid) clear();

    return areArgumentsValid;

}


void KnapsackProblem::clear(){
    this->capacity = 0;
    this->genomeLength = 0;
    this->weights = SharedPointer<vector<double>>(new vector<double>());
    this->values = SharedPointer<vector<double>>(new vector<double>());
}

bool KnapsackProblem::validateWeights() {
    return areValuesPositive(*weights);
};
bool KnapsackProblem::validateValues(){
    return areValuesPositive(*values);
};

bool KnapsackProblem::areValuesPositive(vector<double>& input){
    return std::all_of(input.cbegin(), input.cend(), [](double i){ return i > 0; });
}

bool KnapsackProblem::validateCapacity() const{
    return capacity > 0;
};

bool KnapsackProblem::validateGenomeLength() const {
    return genomeLength > 0;
}

bool KnapsackProblem::validateLengths(){
    return (*values).size() == (*weights).size();
}

double KnapsackProblem::getFitness(vector<int>& genotype){
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

int KnapsackProblem::getLength() {
	return genomeLength;
}
