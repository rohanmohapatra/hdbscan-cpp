#include <vector>

namespace hdbscanStar
{
	class undirectedGraph
	{
		private :
		int _numVertices;
		std::vector<int> _verticesA;
		std::vector<int> _verticesB;
		std::vector<double> _edgeWeights;
		std::vector<std::vector<int>> _edges;

		public :
		undirectedGraph(int numVertices, std::vector<int> verticesA, std::vector<int> verticesB, std::vector<double> edgeWeights)
		{
			_numVertices = numVertices;
			_verticesA = verticesA;
			_verticesB = verticesB;
			_edgeWeights = edgeWeights;
			_edges.resize(numVertices);
			int _edgesLength = _edges.size();
			int _edgeWeightsLength = _edgeWeights.size();

			for(int i = 0; i < _edgesLength; i++)
			{
				 _edges[i].resize(1 + _edgeWeightsLength / numVertices);
			}
			for (int i = 0; i < _edgeWeightsLength; i++)
			{
				_edges[_verticesA[i]].push_back(_verticesB[i]);

				if (_verticesA[i] != _verticesB[i])
					_edges[_verticesB[i]].push_back(_verticesA[i]);
			}

		}
		
		void quicksortByEdgeWeight()
		{
			int _edgeWeightsLength = _edgeWeights.size();
			if(_edgeWeightsLength <= 1)
				return ;
			
			std::vector<int> startIndexStack(_edgeWeightsLength / 2);
			std::vector<int> endIndexStack(_edgeWeightsLength / 2); 

			startIndexStack[0] = 0;
			endIndexStack[0] = _edgeWeightsLength - 1;

			int stackTop = 0;
			while(stackTop >= 0)
			{
				int startIndex = startIndexStack[stackTop];
				int endIndex = endIndexStack[stackTop];
				stackTop--;
				int pivotIndex = selectPivotIndex(startIndex, endIndex);
				pivotIndex = partition(startIndex, endIndex, pivotIndex);
				if (pivotIndex > startIndex + 1)
				{
					startIndexStack[stackTop + 1] = startIndex;
					endIndexStack[stackTop + 1] = pivotIndex - 1;
					stackTop++;
				}
				if (pivotIndex < endIndex - 1)
				{
					startIndexStack[stackTop + 1] = pivotIndex + 1;
					endIndexStack[stackTop + 1] = endIndex;
					stackTop++;
				}

			}
		}
		
		private:
		int selectPivotIndex(int startIndex, int endIndex)
		{
			if (startIndex - endIndex <= 1)
					return startIndex;
			
			double first = _edgeWeights[startIndex];
			double middle = _edgeWeights[startIndex + (endIndex - startIndex) / 2];
			double last = _edgeWeights[endIndex];
			
			if (first <= middle)
			{
				if (middle <= last)
					return startIndex + (endIndex - startIndex) / 2;
				
				if (last >= first)
					return endIndex;
				
				return startIndex;
			}

			if (first <= last)
				return startIndex;
			
			if (last >= middle)
				return endIndex;
			
			return startIndex + (endIndex - startIndex) / 2;
		}
		
		int partition(int startIndex, int endIndex, int pivotIndex)
		{
			double pivotValue = _edgeWeights[pivotIndex];
			swapEdges(pivotIndex, endIndex);
			int lowIndex = startIndex;
			for (int i = startIndex; i < endIndex; i++)
			{
				if (_edgeWeights[i] < pivotValue)
				{
					swapEdges(i, lowIndex);
					lowIndex++;
				}
			}
			swapEdges(lowIndex, endIndex);
			return lowIndex;
		}

		void swapEdges(int indexOne, int indexTwo)
		{
			if (indexOne == indexTwo)
				return;

			int tempVertexA = _verticesA[indexOne];
			int tempVertexB = _verticesB[indexOne];
			double tempEdgeDistance = _edgeWeights[indexOne];
			_verticesA[indexOne] = _verticesA[indexTwo];
			_verticesB[indexOne] = _verticesB[indexTwo];
			_edgeWeights[indexOne] = _edgeWeights[indexTwo];
			_verticesA[indexTwo] = tempVertexA;
			_verticesB[indexTwo] = tempVertexB;
			_edgeWeights[indexTwo] = tempEdgeDistance;
		}

		public:
		int getNumVertices()
		{
			return _numVertices;
		}

		int getNumEdges()
		{
			return _edgeWeights.size();
		}

		int getFirstVertexAtIndex(int index)
		{
			return _verticesA[index];
		}

		int getSecondVertexAtIndex(int index)
		{
			return _verticesB[index];
		}

		double getEdgeWeightAtIndex(int index)
		{
			return _edgeWeights[index];
		}

		std::vector<int> getEdgeListForVertex(int vertex)
		{
			return _edges[vertex];
		}

	};
}