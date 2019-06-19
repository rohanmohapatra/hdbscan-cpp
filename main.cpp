#include<iostream>
#include "utils/example.hpp"
using namespace std;
using namespace csv;

int main() {
	csv_reader reader("dataset.csv");
	vector<vector <double>> dataset = reader.read_csv(2, false);
	for (int i = 0; i < dataset.size(); i++) {
		for (int j = 0; j < dataset[i].size(); j++) {
			cout << dataset[i][j] << ",";
		}
		cout << endl;
	}
	return 0;
}