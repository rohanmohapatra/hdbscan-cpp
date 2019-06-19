#pragma once
#include<string>
#include<vector>#include"hdbscanResult.hpp"using namespace std;
namespace example {
	class example
	{
	private:
		string fileName;

	public:		vector < vector <double > > dataset;		hdbscanResult result;
		example(string readFileName) {
			fileName = readFileName;
		}			   
		void loadCsv(int number_of_values, bool skip_header);

	};
}
