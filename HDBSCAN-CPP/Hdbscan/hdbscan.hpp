#pragma once
#include<string>
#include<vector>
#include"../Runner/hdbscanParameters.hpp"
#include"../Runner/hdbscanResult.hpp"
#include"../HdbscanStar/outlierScore.hpp"

using namespace std;


class Hdbscan

{
private:

	string fileName;

	hdbscanResult result;

public:

	vector<vector<double>> dataset;

	std::vector<int> labels_;

	std::vector<int> normalizedLabels_;

	std::vector<outlierScore> outlierScores_;

	uint32_t noisyPoints_;

	uint32_t numClusters_;


	Hdbscan(string readFileName)
	{
		fileName = readFileName;
		noisyPoints_ = 0;
		numClusters_ = 0;
	}

	string getFileName() const;

	int loadCsv(int numberOfValues, bool skipHeader = false);

	void execute(int minPoints, int minClusterSize, string distanceMetric);

	void displayResult() const;
};
