#pragma once

#include <iostream>
#include <cstdlib> 

using namespace std;

struct Graph
{
	int n = 0;
	int** matrix = nullptr;

	void clear()
	{
		if (matrix != nullptr)
		{
			for (int i = 0; i < n; i++)
			{
				delete[] matrix[i];
			}
			delete[] matrix;
		}
	}

	void init()
	{
		matrix = new int*[n];
		for (int i = 0; i < n; i++)
		{
			matrix[i] = new int[n];
		}
	}

	void print()
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
	}
};

inline bool check(Graph graph1, Graph graph2)
{
	//Здесь будет алгоритм
	if (graph1.n == graph2.n)
	{
		int n = graph1.n;
		int* adjacent_g1 = new int[n]; // наборы инцидентных рёбер для вершин 1 графа
		int* adjacent_g2 = new int[n]; // наборы инцидентных рёбер для вершин 2 графа

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++) 
			{
				if (graph1.matrix[i][j] != 0) 
				{
					adjacent_g1[i] ++;
				}

				if (graph2.matrix[i][j] != 0) 
				{
					adjacent_g2[i] ++;
				}
			}	
			for (int t = i; t > 0; t--)
			{
				if (adjacent_g1[t] > adjacent_g1[t - 1])
				{
					swap(adjacent_g1[t], adjacent_g1[t - 1]);
				}

				if (adjacent_g2[t] > adjacent_g2[t - 1])
				{
					swap(adjacent_g2[t], adjacent_g2[t - 1]);
				}
			}
		}

		for (int i = 0; i < n; i++)
		{
			if (adjacent_g1[i] != adjacent_g2[i])
			{
				cout << "not isomorphic" << endl;
				return false;
			}
		}
		cout << "perhaps isomorphic" << endl;
		return true;
	}
	cout << "not isomorphic" << endl;
	return false;
}