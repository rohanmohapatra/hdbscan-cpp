#include <limits>
#include <vector>
#include "../utils/bitSet.cpp"
#include "undirectedGraph.cpp"

namespace hdbscanStar
{

	class hdbscanAlgorithm
	{
		
		public :
		/// <summary>
        /// Calculates the core distances for each point in the data set, given some value for k.
        /// </summary>
        /// <param name="distances">A vector of vectors where index [i][j] indicates the jth attribute of data point i</param>
        /// <param name="k">Each point's core distance will be it's distance to the kth nearest neighbor</param>
        /// <returns> An array of core distances</returns>
		static std::vector<double> calculateCoreDistances(std::vector<std::vector<double>> distances, int k)
		{
			int length = distances.size();

			int numNeighbors = k - 1;
			std::vector<double>coreDistances(length);
			if (k == 1)
			{
				for (int point = 0; point < length; point++)
				{
					coreDistances[point] = 0;
				}
				return coreDistances;
			}
			for (int point = 0; point < length; point++)
			{
				std::vector<double> kNNDistances(numNeighbors);  //Sorted nearest distances found so far
				for (int i = 0; i < numNeighbors; i++)
				{
					kNNDistances[i] = std::numeric_limits<double>::max();
				}
				
				for (int neighbor = 0; neighbor < length; neighbor++)
				{
					if (point == neighbor)
						continue;
					double distance = distances[point][neighbor];
					int neighborIndex = numNeighbors;
					//Check at which position in the nearest distances the current distance would fit:
					while (neighborIndex >= 1 && distance < kNNDistances[neighborIndex - 1])
					{
						neighborIndex--;
					}
					//Shift elements in the array to make room for the current distance:
					if (neighborIndex < numNeighbors)
					{
						for (int shiftIndex = numNeighbors - 1; shiftIndex > neighborIndex; shiftIndex--)
						{
							kNNDistances[shiftIndex] = kNNDistances[shiftIndex - 1];
						}
						kNNDistances[neighborIndex] = distance;
					}
					
				}
				coreDistances[point] = kNNDistances[numNeighbors - 1];
			}
			return coreDistances;
		};

		static undirectedGraph constructMst(std::vector<std::vector<double>> distances, std::vector<double> coreDistances, bool selfEdges)
		{
			int length=distances.size();
			int selfEdgeCapacity=0;
			if (selfEdges)
					selfEdgeCapacity = length;
			utils::bitSet attachedPoints;

			std::vector<int> nearestMRDNeighbors(length - 1 + selfEdgeCapacity);
			std::vector<double> nearestMRDDistances(length -1 + selfEdgeCapacity);

			for(int i = 0; i < length - 1; i++)
			{
				nearestMRDDistances[i] = std::numeric_limits<double>::max();
			}

			int currentPoint = length - 1;
			int numAttachedPoints = 1;
			attachedPoints.set(length - 1);

			while(numAttachedPoints < length)
			{

				int nearestMRDPoint = -1;
				double nearestMRDDistance = std::numeric_limits<double>::max();
				for (int neighbor = 0; neighbor < length; neighbor++)
				{
					if (currentPoint == neighbor)
							continue;
					if (attachedPoints.get(neighbor) == true)
							continue;
					double distance = distances[currentPoint][neighbor];
					double mutualReachabiltiyDistance = distance;
					if (coreDistances[currentPoint] > mutualReachabiltiyDistance)
							mutualReachabiltiyDistance = coreDistances[currentPoint];

					if (coreDistances[neighbor] > mutualReachabiltiyDistance)
						mutualReachabiltiyDistance = coreDistances[neighbor];

					if (mutualReachabiltiyDistance < nearestMRDDistances[neighbor])
					{
						nearestMRDDistances[neighbor] = mutualReachabiltiyDistance;
						nearestMRDNeighbors[neighbor] = currentPoint;
					}

					if (nearestMRDDistances[neighbor] <= nearestMRDDistance)
					{
						nearestMRDDistance = nearestMRDDistances[neighbor];
						nearestMRDPoint = neighbor;
					}
					
				}
				attachedPoints.set(nearestMRDPoint);
				numAttachedPoints++;
				currentPoint = nearestMRDPoint;
			}
			std::vector<int> otherVertexIndices(length - 1 + selfEdgeCapacity);
			for(int i = 0; i < length - 1; i++)
			{
				otherVertexIndices[i] = i;
			}
			if (selfEdges)
			{
				for (int i = length - 1; i < length * 2 - 1; i++)
				{
					int vertex = i - (length - 1);
					nearestMRDNeighbors[i] = vertex;
					otherVertexIndices[i] = vertex;
					nearestMRDDistances[i] = coreDistances[vertex];
				}
			}
			undirectedGraph undirectedGraphObject(length, nearestMRDNeighbors, otherVertexIndices, nearestMRDDistances);
			return undirectedGraphObject;

		}
	};

}

