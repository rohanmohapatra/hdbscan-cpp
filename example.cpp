#include "example.hpp"

using namespace std;
using namespace example;

void example::loadCsv(int number_of_values, bool skip_header=false) {
	string attribute;
	string line = "";
	int currentAttributes;
	//Dataset of Vectors holding the Dataset
	vector<vector<double>> dataset;

	//cout << "Got these many values" << number_of_values << endl;
	//Read the File name from the Object passed
	string file_name = this->get_file_name();

	//Read the Dataset as passed as argument
	ifstream file(file_name, ios::in);

	//Skips is skip_header == true
	if (skip_header) {
		getline(file, line);
	}


	while (getline(file, line)) {      //Read through each line
		stringstream s(line);
		vector<double> row;
		current_attributes = number_of_values;
		while (getline(s, attribute, ',') && current_attributes != 0) {
			row.push_back(stod(attribute));
			//cout<<current_attributes<<endl;
			current_attributes--;
		}
		dataset.push_back(row);
	}
	return dataset;
}