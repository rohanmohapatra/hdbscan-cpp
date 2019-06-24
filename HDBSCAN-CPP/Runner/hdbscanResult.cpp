#include "hdbscanResult.hpp"

hdbscanResult::hdbscanResult() {
	;
}
hdbscanResult::hdbscanResult(vector<int> pLables, vector<outlierScore> pOutlierScores, bool pHsInfiniteStability) {
	labels = pLables;
	outliersScores = pOutlierScores;
	hasInfiniteStability = pHsInfiniteStability;
}