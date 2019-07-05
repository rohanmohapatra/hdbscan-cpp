# HDBSCAN-CPP
Fast and Efficient Implementation of HDBSCAN in C++ using STL.


Authored by:
Sumedh Basarkod
Rohan Mohapatra
--------------------------------------------------------------------------------------------------------------

The Standard Template Library (STL) is a set of C++ template classes to provide common programming 
data structures and functions such as lists, stacks, arrays, etc. It is a library of container classes, algorithms, and iterators. 

# About HDBSCAN
HDBSCAN - Hierarchical Density-Based Spatial Clustering of Applications with Noise. Performs DBSCAN over varying epsilon values and integrates the result to find a clustering that gives the best stability over epsilon. This allows HDBSCAN to find clusters of varying densities (unlike DBSCAN), and be more robust to parameter selection.

In practice this means that HDBSCAN returns a good clustering straight away with little or no parameter tuning -- and the primary parameter, minimum cluster size, is intuitive and easy to select.

HDBSCAN is ideal for exploratory data analysis; it's a fast and robust algorithm that you can trust to return meaningful clusters (if there are any).

Based on the paper:
> R. Campello, D. Moulavi, and J. Sander, Density-Based Clustering Based on Hierarchical Density Estimates In: Advances in Knowledge Discovery and Data Mining, Springer, pp 160-172. 2013

### How to Run this code?

Clone this project as this contains the library.
```
git clone https://github.com/rohanmohapatra/hdbscan-cpp.git
```

Run the Makefile
```
make all clean
```

Wait for it to complete, this will run the already present example in the Four Prominent Cluster Example Folder. Plot the points and see the clustering.
To run:
```
./main
```

If you want to use it , have a look at the example and use it.



### Outlier Detection
The HDBSCAN clusterer objects also support the GLOSH outlier detection algorithm. After fitting the clusterer to 
data the outlier scores can be accessed via the `outlierScores_` from the `Hdbscan` Object. The result is a vector of score values,
one for each data point that was fit. Higher scores represent more outlier like objects. Selecting outliers via upper 
quantiles is often a good approach.

Based on the papers:
> R.J.G.B. Campello, D. Moulavi, A. Zimek and J. Sander Hierarchical Density Estimates for Data Clustering, Visualization, and Outlier Detection, ACM Trans. on Knowledge Discovery from Data, Vol 10, 1 (July 2015), 1-51.

## Examples
```
#include<iostream>
#include"../HDBSCAN-CPP/Hdbscan/hdbscan.hpp"
using namespace std;
int main() {

	Hdbscan hdbscan("HDBSCANDataset/FourProminentClusterDataset.csv");
  hdbscan.loadCsv(2);
	hdbscan.execute(5, 5, "Euclidean");
	hdbscan.displayResult();
	cout << "You can access other fields like cluster labels, membership probabilities and outlier scores."<<endl;

	/*Use it like this
	hdbscan.labels_;
	hdbscan.membershipProbabilities_;
	hdbscan.outlierScores_;
	*/
	return 0;

}
```

### Help and Support
If you have issues, please check the issues on github. Finally, if no solution is available there feel free to open an issue ; 
the authors will attempt to respond.

### Contributing
We welcome contributions in any form! Assistance with documentation, is always welcome. 
To contribute please fork the project make your changes and submit a pull request. 
We will do our best to work through any issues with you and get your code merged into the master branch.
