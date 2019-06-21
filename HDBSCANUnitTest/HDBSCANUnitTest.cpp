#include "pch.h"
#include <iostream>
#include "CppUnitTest.h"
#include"../HDBSCAN-CPP/distance/EuclideanDistance.hpp"
#include"../HDBSCAN-CPP/Example/example.hpp"
#include <limits>
#include <typeinfo>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HDBSCANUnitTest
{
	TEST_CLASS(ExampleTest)
	{
	public:
		TEST_METHOD(CheckFileNameTest)
		{
			string expectedFileName = "../HDBSCANDataset/Dataset.csv";
			Example example("../HDBSCANDataset/Dataset.csv");
			string fileName = example.getFileName();
			Assert::AreEqual(expectedFileName, fileName);
		}
		TEST_METHOD(CheckDatasetTypeTest)
		{
			Example example(".../../HDBSCANDataset/Dataset.csv");
			example.loadCsv(2);
			string expectedClassName = "class std::vector<class std::vector<double,class std::allocator<double> >,class std::allocator<class std::vector<double,class std::allocator<double> > > >";
			Assert::AreEqual(expectedClassName, (string)typeid(example.dataset).name());
		}
		TEST_METHOD(FileNotFoundErrorTest)
		{
			Example example("../HDBSCANDataset/Dataset2.csv");
			int realLoaded = example.loadCsv(2);
			Assert::AreEqual(0, realLoaded);
		}
		TEST_METHOD(FilePresentTest)
		{
			Example example("../../HDBSCANDataset/Dataset.csv");
			int realLoaded = example.loadCsv(2);
			Assert::AreEqual(1, realLoaded);
		}
		TEST_METHOD(LoadCsvWithHeaderTest)
		{
			Example example("../../HDBSCANDataset/Dataset.csv");
			example.loadCsv(2,true);
			Assert::AreEqual(99, (int)example.dataset.size());
		}
		TEST_METHOD(LoadCsvWithoutHeaderTest)
		{
			Example example("../../HDBSCANDataset/Dataset.csv");
			example.loadCsv(2);
			Assert::AreEqual(100, (int)example.dataset.size());
		}
		TEST_METHOD(CsvNumberOfAttributesTest)
		{
			Example example("../../HDBSCANDataset/Dataset.csv");
			example.loadCsv(1);
			Assert::AreEqual(1, (int)example.dataset[0].size());
		}
	};
	
	
	TEST_CLASS(EuclideanTest)
	{
	public:
		TEST_METHOD(EuclideanDistanceTest1)
		{
			std::vector<double> pointOne{ -7, -4 };
			std::vector<double> pointTwo{ 17, 6.5 };
			double realDistance = 26.1964;
			EuclideanDistance Edistance;
			double distance = Edistance.computeDistance(pointOne, pointTwo);
			Assert::AreEqual(realDistance, distance, 0.0001);
		}
		TEST_METHOD(EuclideanDistanceTest2)
		{
			std::vector<double> pointOne{ 4, 5 };
			std::vector<double> pointTwo{ 1, 1 };
			double realDistance = 5;
			EuclideanDistance Edistance;
			double distance = Edistance.computeDistance(pointOne, pointTwo);
			Assert::AreEqual(realDistance, distance, 0.0001);
		}
		TEST_METHOD(EuclideanDistanceTest3)
		{
			std::vector<double> pointOne{ 7, 4, 3 };
			std::vector<double> pointTwo{ 17, 6, 2 };
			double realDistance = 10.2469;
			EuclideanDistance Edistance;
			double distance = Edistance.computeDistance(pointOne, pointTwo);
			Assert::AreEqual(realDistance, distance, 0.0001);
		}
		TEST_METHOD(EuclideanDistanceTest4)
		{
			std::vector<double> pointOne{ 0,3,4,5 };
			std::vector<double> pointTwo{ 7,6,3,-1 };
			double realDistance = 9.747;
			EuclideanDistance Edistance;
			double distance = Edistance.computeDistance(pointOne, pointTwo);
			Assert::AreEqual(realDistance, distance, 0.001);
		}
	};
	TEST_CLASS(coreDistances)
	{
		TEST_METHOD(coreDistances1)
		{
			std::vector<std::vector<double>> distances(6);
			distances[0].push_back(0);
			distances[0].push_back(5.73428958110767);
			distances[0].push_back(2.98100989599162);
			distances[0].push_back(5.97459429584972);
			distances[0].push_back(0.497398230797014);
			distances[0].push_back(3.20578804664313);
			distances[1].push_back(5.73428958110767);
			distances[1].push_back(0);
			distances[1].push_back(3.45483154437376);
			distances[1].push_back(0.565729617396862);
			distances[1].push_back(6.13567551293254);
			distances[1].push_back(8.63920181498268);
			distances[2].push_back(2.98100989599162);
		    distances[2].push_back(3.45483154437376);
			distances[2].push_back(0);
			distances[2].push_back(3.47814620164248);
			distances[2].push_back(3.20909722507748);
			distances[2].push_back(5.34961054657253);
			distances[3].push_back(5.97459429584972);
			distances[3].push_back(0.565729617396862);
			distances[3].push_back(3.4781462016424);
			distances[3].push_back(0);
			distances[3].push_back(6.34934516308572);
			distances[3].push_back(8.7699862029538);
			distances[4].push_back(0.497398230797014);
			distances[4].push_back(6.1356755129325);
			distances[4].push_back(3.20909722507748);
			distances[4].push_back(6.34934516308572);
			distances[4].push_back(0);
			distances[4].push_back(2.71220390088946);
			distances[5].push_back(3.20578804664313);
			distances[5].push_back(8.63920181498268);
			distances[5].push_back(5.34961054657253);
			distances[5].push_back(8.7699862029538);
			distances[5].push_back(2.71220390088946);
			distances[5].push_back(0);			using namespace hdbscanStar;
			std::vector<double> coreDistances = hdbscanAlgorithm::calculateCoreDistances(distances, 10);
			std::vector<double> actualcoreDistances{ 5.73429, 6.13568, 3.47815, 6.34935, 6.13568, 8.639 };
			Assert::AreEqual(coreDistances, actualcoreDistances);
		}
	};
}
