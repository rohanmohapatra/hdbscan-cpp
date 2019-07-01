#pragma once
#include<vector>
#include"../HdbscanStar/outlierScore.hpp"
using namespace std;

class hdbscanResult
{
public:
	vector<int> labels;
	vector<outlierScore> outliersScores;
	bool hasInfiniteStability;
	hdbscanResult();
	hdbscanResult(vector<int> pLables, vector<outlierScore> pOutlierScores, bool pHsInfiniteStability);
};
