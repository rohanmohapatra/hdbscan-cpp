#include<iostream>
#include"Example/example.hpp"
using namespace std;

//using namespace csv;
#include <typeinfo>
#include <vector>


int main() {

	cout << "Hello World!" << endl;
	vector< vector<double>> x;
	cout << typeid(x).name() <<endl;
	Example example("../HDBSCANDataset/Dataset.csv");
	example.loadCsv(2);
	vector<vector <double>> dataset = example.dataset;

	for (int i = 0; i < dataset.size(); i++) {

		for (int j = 0; j < dataset[i].size(); j++) {

			cout << dataset[i][j] << ",";

		}

		cout << endl;

	}
	return 0;

}