#pragma once
#include<vector>
using namespace std;
class hdbscanResult
{
public:
	vector <int> labels;
	// vector <outlierScore> outliersScores;s
	bool hasInfiniteStability;
};

