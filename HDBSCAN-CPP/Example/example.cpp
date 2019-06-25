#include "example.hpp"
#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;

string Example::getFileName() {
	return this->fileName;
}

int Example::loadCsv(int numberOfValues, bool skipHeader) {
	string  attribute;

	string line = "";

	int currentAttributes;
	vector<vector<double>> dataset;

	string fileName = this->getFileName();
	ifstream file(fileName, ios::in);
	if (!file)
		return 0;
	if (skipHeader) {
		getline(file, line);

	}
	while (getline(file, line)) {      //Read through each line
		stringstream s(line);
		vector<double> row;
		currentAttributes = numberOfValues;
		while (getline(s, attribute, ',') && currentAttributes != 0) {
			row.push_back(stod(attribute));
			currentAttributes--;
		}
		dataset.push_back(row);

	}
	this->dataset = dataset;
	return 1;
}

void Example::execute(int minPoints,int minClusterSize,string distanceMetric) {
	//Call The Runner Class here
	hdbscanRunner runner;
	hdbscanParameters parameters;
	parameters.dataset = this->dataset;
	parameters.minPoints = minPoints;
	parameters.minClusterSize = minClusterSize;
	parameters.distanceFunction = distanceMetric;
	this->result = runner.run(parameters);
	
	
}

void Example::displayResult() {
	hdbscanResult result = this->result;
	uint32_t numClusters = 0;
	uint32_t noisyPoints = 0;
	cout << "HDBSCAN clustering for " << this->dataset.size() << " objects.";
	for(uint32_t i=0;i<result.labels.size();i++){
		cout << result.labels[i] << " ";
		if (result.labels[i] == 0) {
			noisyPoints++;
		}
		else {
			numClusters++;
		}
	}

	cout << "The Clustering contains " << numClusters << " " << noisyPoints << " noise Points"<<endl;

}
