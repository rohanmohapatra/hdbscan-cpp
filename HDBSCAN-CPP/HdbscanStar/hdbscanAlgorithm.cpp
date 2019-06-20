#include <limits>
#include <vector>
#include "../utils/bitSet.hpp"
#include "undirectedGraph.hpp"

namespace hdbscanStar
{

	class hdbscanAlgorithm
	{
	public:
		static undirectedGraph constructMst(std::vector<std::vector<double>> distances, std::vector<double> coreDistances, bool selfEdges)
		{
			int length = distances.size();
			int selfEdgeCapacity = 0;
			if (selfEdges)
				selfEdgeCapacity = length;
			bitSet attachedPoints;

			std::vector<int> nearestMRDNeighbors(length - 1 + selfEdgeCapacity);
			std::vector<double> nearestMRDDistances(length - 1 + selfEdgeCapacity);

			for (int i = 0; i < length - 1; i++)
			{
				nearestMRDDistances[i] = std::numeric_limits<double>::max();
			}

			int currentPoint = length - 1;
			int numAttachedPoints = 1;
			attachedPoints.set(length - 1);

			while (numAttachedPoints < length)
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
			for (int i = 0; i < length - 1; i++)
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


