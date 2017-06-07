#include "Graph.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

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

		cout << graph.n << endl;

		for (int i = 0; i < graph.n; i++)
		{
			for (int j = 0; j < graph.n; j++)
			{
				cout << graph.matrix[i][j] << " ";
			}
			cout << endl;
		}
	}

	// Заполнение рандомных изоморфных графов
	void createRIGs(Graph& graph1, Graph& graph2)
	{
		int n = graph1.n;

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				graph1.matrix[i][j] = rand() % 2; // Рандомно заполняем 0 и 1
				if (i == j)
				{
					graph1.matrix[i][j] = 0;
					if (i != 0)
					{
						graph1.matrix[i - 1][j] = 1; // Делаем граф связным
					}
				}
			}
		}

		vector<int> permutation(n);
		iota(permutation.begin(), permutation.end(), 0);
		random_shuffle(permutation.begin(), permutation.end());

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				graph2.matrix[i][j] = graph1.matrix[permutation[i]][permutation[j]];
			}
		}
	}
}