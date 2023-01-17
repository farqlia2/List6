#include "KnapsackProblem.h"

void KnapsackProblem::read(string&& fileName){

    ifstream file(fileName);
    clear();

    if (file.is_open()) {

        if (!read(file)) throw BadFormattingException("File is badly formatted");

        file.close();

        validate();

    } else throw IOException("Couldn't open the file");

}

bool KnapsackProblem::read(ifstream& file){

    int nOfElements;

    // tries to read in number of elements and capacity
    file >> nOfElements >> capacity;

    if (!file) return false;

    double val, weight;

    while (nOfElements-- > 0 && file){

        file >> val >> weight;
        (*values).push_back(val);
        (*weights).push_back(weight);

    }

    if (!file) return false;
    return true;
}

KnapsackProblem::KnapsackProblem(SharedPointer<vector<double>> &weights, SharedPointer<vector<double>> &values,
                                 double capacity) : values(values), weights(weights), capacity(capacity) {
    validate();
}


void KnapsackProblem::clear(){
    this->capacity = 0;
    this->weights = SharedPointer<vector<double>>(new vector<double>());
    this->values = SharedPointer<vector<double>>(new vector<double>());
}

void KnapsackProblem::validate(){
    if (!validateLengths())
        throw IllegalArgumentException("Weights length and values length should be the same");
    if (!validateCapacity())
        throw IllegalArgumentException("Capacity should be positive");
    if (!validateWeights())
        throw IllegalArgumentException("Weights should be positive");
    if (!validateValues())
        throw IllegalArgumentException("Values should be positive");
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
