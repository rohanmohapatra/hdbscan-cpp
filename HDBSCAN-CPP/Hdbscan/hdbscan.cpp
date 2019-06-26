#include "hdbscan.hpp"
#include<iostream>
#include<fstream>
#include<sstream>
#include<set>
using namespace std;

string Hdbscan::getFileName() {
	return this->fileName;
}

int Hdbscan::loadCsv(int numberOfValues, bool skipHeader) {
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

void Hdbscan::execute(int minPoints,int minClusterSize,string distanceMetric) {
	//Call The Runner Class here
	hdbscanRunner runner;
	hdbscanParameters parameters;
	parameters.dataset = this->dataset;
	parameters.minPoints = minPoints;
	parameters.minClusterSize = minClusterSize;
	parameters.distanceFunction = distanceMetric;
	this->result = runner.run(parameters);
	
	this->labels_ = result.labels;
	this->outlierScores_ = result.outliersScores;
}

void Hdbscan::displayResult() {
	hdbscanResult result = this->result;
	uint32_t numClusters = 0;
	uint32_t noisyPoints = 0;
	set<int> numClustersSet;
	cout << "HDBSCAN clustering for " << this->dataset.size() << " objects." << endl << endl;
	for(uint32_t i=0;i<result.labels.size();i++){
		cout << result.labels[i] << " ";
		if (result.labels[i] == 0) {
			noisyPoints++;
		}
		else {
			numClustersSet.insert(result.labels[i]);
		}
	}
	cout << endl << endl;
	cout << "The Clustering contains " << numClustersSet.size() << " clusters with " << noisyPoints << " noise Points."<<endl;

}
