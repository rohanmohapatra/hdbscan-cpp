#include "pch.h"
#include <iostream>
#include <algorithm>
#include "CppUnitTest.h"
#include"../HDBSCAN-CPP/distance/EuclideanDistance.hpp"
#include"../HDBSCAN-CPP/Example/example.hpp"
#include"..//HDBSCAN-CPP/HdbscanStar/outlierScore.hpp"
#include"../HDBSCAN-CPP/HdbscanStar/hdbscanAlgorithm.hpp"
#include"../HDBSCAN-CPP/HdbscanStar/cluster.hpp"
#include"../HDBSCAN-CPP/HdbscanStar/undirectedGraph.hpp"
#include <limits>
#include <typeinfo>
#include <windows.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace hdbscanStar;
namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<> static std::wstring ToString<cluster>(const class cluster& t) { return L"cluster"; }
		}
	}
}

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

	TEST_CLASS(OutlierScoreTest)
	{
	public:
		TEST_METHOD(OutlierScoreSortTest)
		{
			vector <vector<double>> x = {
				{0,0.889528896739179,0.536626916823739},
				{1,1.30766765703343,0.684794721931497},
				{2,0.936505261432846,0.559870334496815},
				{3,1.35315204874408,0.695389924702862},
				{4,1.33800483587915,0.691941511417945},
				{5,1.27630172186469,0.677048349622057},
				{6,1.06622138711494,0.61341635758055},
				{7,0.970467785702901,0.575273127528009},
				{8,0.937062926916861,0.560132264742791},
				{9,0.730108008669853,0},
				{10,0.979612737644039,0.579238068659958},
				{11,0.952675354149085,0.567340809582959},
				{12,1.06535735576111,0.613102828616657},
				{13,0.845096031235497,0.136065036771662},
				{14,0.884558228998538,0.534023047953474},
				{15,0.9042601301378,0.544175692680823},
				{16,0.928273423718686,0.555967307773185},
				{17,0.9323689173711,0.557917751464086},
				{18,0.896417147140688,0.540187569178971},
				{19,1.0187200513571,0.595390562002469},
				{20,1.01596972644001,0.594295246472827},
				{21,0.938697386384946,0.560898162246101},
				{22,0.854842252354049,0.145914925637688},
				{23,0.815181661626957,0.104361588295928},
				{24,1.03827746057,0.603011947085772},
				{25,0.921778928039446,0.552838826188949},
				{26,0.765984306607496,0},
				{27,0.900398719462828,0.542220864438459},
				{28,1.29652957723496,0.68208689204341},
				{29,1.38797576323793,0.703032460383277},
				{30,1.33500590418165,0.691249494728581},
				{31,1.18221041594258,0.651344852068677},
				{32,0.973669270098528,0.576669655585719},
				{33,0.744074562803077,0.0187703690348033},
				{34,0.810863085163569,0.0995915068416579},
				{35,0.952675354149085,0.567340809582959},
				{36,0.785997173244647,0.0254617539583976},
				{37,0.970862509701085,0.57544580891962},
				{38,0.896049360290902,0.53999883742722},
				{39,1.44900243136215,0.715539644009476},
				{40,0.863807536200697,0.154779302017782},
				{41,1.42496365556362,0.710740869883184},
				{42,0.880271372609541,0.531753774708697},
				{43,1.14039940333005,0.638561940445774},
				{44,1.26276150470785,0.673585434842841},
				{45,0.996716490650408,0.58645838478358},
				{46,0.89143293910424,0.537616651376383},
				{47,0.883562175576474,0.533497744867264},
				{48,0.992112166688545,0.584539166743422},
				{49,1.00096857175111,0.588215095769359},
				{50,0.642021351080678,0.323159630873048},
				{51,0.578143764578302,0.248377315684122},
				{52,0.450791083928523,0.0856435227947701},
				{53,0.788777814018606,0.477439983565906},
				{54,0.502681769986088,0.180030444573674},
				{55,0.468359254700564,0.119941063788881},
				{56,0.607715530929302,0.28495168193524},
				{57,0.630803460709561,0.311123043358021},
				{58,0.658159785784114,0.339756123605875},
				{59,0.49476618073348,0.166912041471068},
				{60,0.799903426493218,0.456751960473675},
				{61,0.472562408527833,0.080447449033101},
				{62,0.647349601142268,0.363274887743654},
				{63,0.859389453279494,0.520376069448505},
				{64,0.607715530929302,0.28495168193524},
				{65,0.442882781445025,0.069316386354985},
				{66,0.609489696607938,0.287033118572375},
				{67,0.834060993406554,0.505811024955225},
				{68,0.517893306388851,0.20411454951895},
				{69,0.597947374581131,0.273270547333309},
				{70,0.442512210896381,0.068537009133679},
				{71,0.537436171165546,0.191446367834855},
				{72,0.553211822052489,0.214503466971101},
				{73,0.545112412893128,0.202832373699725},
				{74,0.495499136271057,0.123013671581625},
				{75,0.663814320590995,0.379067708136451},
				{76,0.471147506702102,0.12514925454752},
				{77,0.719200362049385,0.395792895578393},
				{78,0.541281856226111,0.197190958362169},
				{79,0.54776864122783,0.24752219014857},
				{80,0.475984826568942,0.134040153280579},
				{81,0.723222276242127,0.399152954039611},
				{82,0.426762469024164,0.0341612082268815},
				{83,0.596160243978712,0.308602424231546},
				{84,0.43454596825283,0},
				{85,0.494600379391922,0.121420066868781},
				{86,0.412183747456411,0},
				{87,0.671464731696394,0.386142372042286},
				{88,0.771238614633195,0.436560929383052},
				{89,0.833427761160873,0.505435543828916},
				{90,0.48186426479736,0.0981983932019291},
				{91,0.474458512558731,0.131254395176672},
				{92,0.461525011742081,0.106909188083707},
				{93,0.648961298996584,0.330397715665448},
				{94,0.838699820665304,0.50854437153755},
				{95,0.47841352889118,0.0916938129655765},
				{96,0.453604234451421,0.0913141541659175},
				{97,0.446428484613226,0.0767082261484362},
				{98,0.453604234451421,0.0913141541659175},
				{99,0.445870270202155,0.0755522962552984}
			};
			vector<outlierScore> test;
			for (int i = 0; i < 100; i++) {
				outlierScore each = outlierScore(x[i][2], x[i][1], x[i][0]);
				test.push_back(each);
			}
			sort(test.begin(), test.end());
			double actual;
			double expected;
			for (int i = 0; i < 100; i++) {
				actual = test[i].score;
				expected = x[test[i].id][2];
				Assert::AreEqual(expected, actual,0.001);
			}
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(OutlierScoreSortTest2)
		{
			vector <vector<double>> x = {
				{0,0.889528896739179,0.536626916823739},
				{1,1.30766765703343,0.684794721931497},
				{2,0.936505261432846,0.559870334496815}
			};
			vector<outlierScore> test;
			test.push_back(outlierScore(x[0][2], x[0][1], x[0][0]));
			test.push_back(outlierScore(x[1][2], x[1][1], x[1][0]));
			test.push_back(outlierScore(x[2][2], x[2][1], x[2][0]));
			vector<double> expected = { 0.536626916823739, 0.559870334496815, 0.684794721931497 };
			sort(test.begin(), test.end());
			double actual;
			for (int i = 0; i < 3; i++) {
				actual = test[i].score;
				Assert::AreEqual(expected[i], actual);
			}
			
		}
	};

	TEST_CLASS(clusterTest)
	{
		TEST_METHOD(clusterEqualityCheck)
		{
			std::vector<cluster> test;
			cluster expected = cluster();
			test.push_back(expected);
			cluster real = *std::find(test.begin(), test.end(), expected);
			Assert::AreEqual(expected.getClusterId(), real.getClusterId());
		}
		TEST_METHOD(clusterEqualityCheck2)
		{
			std::vector<cluster> test;
			for (int i = 0; i < 10; i++) {
				cluster expected = cluster();
				test.push_back(expected);
				cluster real = *std::find(test.begin(), test.end(), expected);
				Assert::AreEqual(expected, real);
			}
		}
		/*TEST_METHOD(clusterEqualityCheck)
		{
			std::vector<cluster> test;
			cluster expected = cluster();
			test.push_back(expected);
			cluster real = *std::find(test.begin(), test.end(), expected);
			Assert::AreEqual(expected.getClusterId(), real.getClusterId());
		}*/
	};
	TEST_CLASS(hdbscanAlgorithmTest)
	{
		TEST_METHOD(computedDistanceTest)
		{
			std::vector<std::vector<double>> test = {
			{ 0,1.43030767999571,0.633501559579796,1.5499878396692,1.59836416418661 },
			{ 1.43030767999571,0,0.870775304614075,0.136060318520133,0.316297648052891 },
			{ 0.633501559579796,0.870775304614075,0,1.00314302071041,1.10818455409305 },
			{ 1.5499878396692,0.136060318520133,1.00314302071041,0,0.216207899828692 },
			{ 1.59836416418661,0.316297648052891,1.10818455409305,0.216207899828692,0 }
			};
			Example example("../../HDBSCANDataset/ShortData.csv");
			example.loadCsv(2);
			std::vector<std::vector<double>> actual(example.dataset.size());
			for (int i = 0; i < actual.size(); i++) {
				actual[i].resize(example.dataset.size());
				EuclideanDistance Edistance;
				for (int j = 0; j < i; j++) {
					double distance = Edistance.computeDistance(example.dataset[i], example.dataset[j]);
					actual[i][j] = distance;
					actual[j][i] = distance;
				}	
			}
			for (int i = 0; i < test.size(); i++) {
				for (int j = 0; j < test[i].size(); j++) {
					Assert::AreEqual(test[i][j], actual[i][j],0.00001);
				}
			}

		}
		TEST_METHOD(coreDistancesTest)
		{
			std::vector<std::vector<double>> distances = {
			{ 0,1.43030767999571,0.633501559579796,1.5499878396692,1.59836416418661 },
			{ 1.43030767999571,0,0.870775304614075,0.136060318520133,0.316297648052891 },
			{ 0.633501559579796,0.870775304614075,0,1.00314302071041,1.10818455409305 },
			{ 1.5499878396692,0.136060318520133,1.00314302071041,0,0.216207899828692 },
			{ 1.59836416418661,0.316297648052891,1.10818455409305,0.216207899828692,0 }
			};
			hdbscanAlgorithm testObject;
			std::vector<double> actual = testObject.calculateCoreDistances(distances, 2);
			std::vector<double> expected = { 0.633501559579796,0.136060318520133,0.633501559579796,0.136060318520133,0.216207899828692 };
			for (int i = 0; i< expected.size(); i++) {
				Assert::AreEqual(expected[i], actual[i], 0.00001);
			}
			
		}
		TEST_METHOD(constructMSTNumVeriticesTest)
		{
			std::vector<std::vector<double>> distances = {
			{ 0,1.43030767999571,0.633501559579796,1.5499878396692,1.59836416418661 },
			{ 1.43030767999571,0,0.870775304614075,0.136060318520133,0.316297648052891 },
			{ 0.633501559579796,0.870775304614075,0,1.00314302071041,1.10818455409305 },
			{ 1.5499878396692,0.136060318520133,1.00314302071041,0,0.216207899828692 },
			{ 1.59836416418661,0.316297648052891,1.10818455409305,0.216207899828692,0 }
			};
			std::vector<double>coreDistances = { 0.633501559579796,0.136060318520133,0.633501559579796,0.136060318520133,0.216207899828692 };
			hdbscanAlgorithm testObject;
			undirectedGraph mst = testObject.constructMst(distances, coreDistances, true);
			Assert::AreEqual(5, mst.getNumVertices());

		}
		TEST_METHOD(constructMSTNumEdgesTest)
		{
			std::vector<std::vector<double>> distances = {
			{ 0,1.43030767999571,0.633501559579796,1.5499878396692,1.59836416418661 },
			{ 1.43030767999571,0,0.870775304614075,0.136060318520133,0.316297648052891 },
			{ 0.633501559579796,0.870775304614075,0,1.00314302071041,1.10818455409305 },
			{ 1.5499878396692,0.136060318520133,1.00314302071041,0,0.216207899828692 },
			{ 1.59836416418661,0.316297648052891,1.10818455409305,0.216207899828692,0 }
			};
			std::vector<double>coreDistances = { 0.633501559579796,0.136060318520133,0.633501559579796,0.136060318520133,0.216207899828692 };
			hdbscanAlgorithm testObject;
			undirectedGraph mst = testObject.constructMst(distances, coreDistances, true);
			Assert::AreEqual(9, mst.getNumEdges());

		}
		TEST_METHOD(constructMSTVericesATest)
		{
			std::vector<std::vector<double>> distances = {
			{ 0,1.43030767999571,0.633501559579796,1.5499878396692,1.59836416418661 },
			{ 1.43030767999571,0,0.870775304614075,0.136060318520133,0.316297648052891 },
			{ 0.633501559579796,0.870775304614075,0,1.00314302071041,1.10818455409305 },
			{ 1.5499878396692,0.136060318520133,1.00314302071041,0,0.216207899828692 },
			{ 1.59836416418661,0.316297648052891,1.10818455409305,0.216207899828692,0 }
			};
			std::vector<double>coreDistances = { 0.633501559579796,0.136060318520133,0.633501559579796,0.136060318520133,0.216207899828692 };
			hdbscanAlgorithm testObject;
			vector<int> expected = {2, 3, 1, 4, 0, 1, 2, 3, 4};
			undirectedGraph mst = testObject.constructMst(distances, coreDistances, true);
			for (int i = 0; i < mst.getNumEdges(); i++) {
				Assert::AreEqual(expected[i], mst.getFirstVertexAtIndex(i));

			}

		}
		TEST_METHOD(constructMSTVericesBTest)
		{
			std::vector<std::vector<double>> distances = {
			{ 0,1.43030767999571,0.633501559579796,1.5499878396692,1.59836416418661 },
			{ 1.43030767999571,0,0.870775304614075,0.136060318520133,0.316297648052891 },
			{ 0.633501559579796,0.870775304614075,0,1.00314302071041,1.10818455409305 },
			{ 1.5499878396692,0.136060318520133,1.00314302071041,0,0.216207899828692 },
			{ 1.59836416418661,0.316297648052891,1.10818455409305,0.216207899828692,0 }
			};
			std::vector<double>coreDistances = { 0.633501559579796,0.136060318520133,0.633501559579796,0.136060318520133,0.216207899828692 };
			hdbscanAlgorithm testObject;
			vector<int> expected = { 0, 1, 2, 3, 0, 1, 2, 3, 4 };
			undirectedGraph mst = testObject.constructMst(distances, coreDistances, true);
			for (int i = 0; i < mst.getNumEdges(); i++) {
				Assert::AreEqual(expected[i], mst.getSecondVertexAtIndex(i));

			}

		}

		TEST_METHOD(constructMSTEdgeWeightsTest)
		{
			std::vector<std::vector<double>> distances = {
			{ 0,1.43030767999571,0.633501559579796,1.5499878396692,1.59836416418661 },
			{ 1.43030767999571,0,0.870775304614075,0.136060318520133,0.316297648052891 },
			{ 0.633501559579796,0.870775304614075,0,1.00314302071041,1.10818455409305 },
			{ 1.5499878396692,0.136060318520133,1.00314302071041,0,0.216207899828692 },
			{ 1.59836416418661,0.316297648052891,1.10818455409305,0.216207899828692,0 }
			};
			std::vector<double>coreDistances = { 0.633501559579796,0.136060318520133,0.633501559579796,0.136060318520133,0.216207899828692 };
			std::vector<double> expected = { 0.633501559579796,0.136060318520133,0.870775304614075,0.216207899828692,0.633501559579796,0.136060318520133,0.633501559579796,0.136060318520133,0.216207899828692 };
			hdbscanAlgorithm testObject;
			Assert::AreEqual(5, (int)distances.size());
			Assert::AreEqual(5, (int)coreDistances.size());
			undirectedGraph mst = testObject.constructMst(distances, coreDistances, true);
			for (int i = 0; i < mst.getNumEdges(); i++) {
				double actual = mst.getEdgeWeightAtIndex(i);
				Assert::AreEqual(expected[i], actual, 0.00001);
			}

		}
	};


	/*
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
			distances[5].push_back(0);
			using namespace hdbscanStar;
			std::vector<double> coreDistances = hdbscanAlgorithm::calculateCoreDistances(distances, 10);
			std::vector<double> actualcoreDistances{ 5.73429, 6.13568, 3.47815, 6.34935, 6.13568, 8.639 };
			Assert::AreEqual(coreDistances, actualcoreDistances);
		}
	};*/
}
