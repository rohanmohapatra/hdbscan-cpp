#pragma once
#include<string>
#include<vector>
#include"../Runner/hdbscanRunner.hpp"
#include"../Runner/hdbscanParameters.hpp"
#include"../Runner/hdbscanResult.hpp"

using namespace std;


class Example

{

private:

	string fileName;



public:

	vector < vector <double > > dataset;

	hdbscanResult result;


	Example(string readFileName) {

		fileName = readFileName;

	}

	string getFileName();
			   
	int loadCsv(int numberOfValues, bool skipHeader=false);

	void execute();

	void displayResult();


};

