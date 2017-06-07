#include "Graph.h"

#include <iostream>
#include <algorithm>

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

	// заполнение рандомных изоморфных графов
	void createRIGs(Graph& graph1, Graph& graph2)
	{
		int n = graph1.n;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				graph1.matrix[i][j] = graph2.matrix[i][j] = rand() % 2; //рандомно заполныем 0 и 1
				if (i == j) {
					graph1.matrix[i][j] = graph2.matrix[i][j] = 0;
					if (i != 0) {
						graph1.matrix[i - 1][j] = graph2.matrix[i - 1][j] = 1; //делаем граф связным
					}
				}
			}
		}

		int* permutation = new int[n];
		for (int i = 0; i < n; i++) {
			permutation[i] = i;
		}
		random_shuffle(permutation, permutation + n);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				graph2.matrix[i][j] = graph1.matrix[permutation[i]][permutation[j]];
			}
		}
		delete[] permutation;
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
}