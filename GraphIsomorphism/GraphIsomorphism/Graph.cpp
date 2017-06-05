#include "Graph.h"

#include <iostream>

using namespace std;

namespace isomorphism
{
	void clear(Graph& graph)
	{
		if (graph.matrix != nullptr)
		{
			for (int i = 0; i < graph.n; i++)
			{
				delete[] graph.matrix[i];
			}
			delete[] graph.matrix;
		}
	}

	void init(Graph& graph)
	{
		graph.matrix = new int*[graph.n];
		for (int i = 0; i < graph.n; i++)
		{
			graph.matrix[i] = new int[graph.n];
		}
	}

	void print(const Graph& graph)
	{
		if (graph.n == 0)
		{
			cout << "empty" << endl;
			return;
		}

		for (int i = 0; i < graph.n; i++)
		{
			for (int j = 0; j < graph.n; j++)
			{
				cout << graph.matrix[i][j] << " ";
			}
			cout << endl;
		}
	}
}