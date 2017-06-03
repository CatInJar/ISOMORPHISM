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
	if (graph1.n == graph2.n) //проверка размеров
	{
		int n = graph1.n;
		int* adjacent_g1 = new int[n]; // наборы инцидентных рёбер для каждой вершины 1 графа
		int* adjacent_g2 = new int[n]; // наборы инцидентных рёбер для каждой вершины 2 графа
		int* adjacent = new int[n]; // количество вершим с определённым набором(количеством) инцедентных рёбер

		for (int i = 0; i < n; i++)
		{
			for (int j = i; j < n; j++) //идём по строке
			{
				if (graph1.matrix[i][j] != 0) // если не ноль, то у вершины есть ребро, для этой и смежной вершины ставим +1 (в массиве вершин 1 графа)
				{
					adjacent_g1[i] ++;
					adjacent_g1[j] ++;
				}

				if (graph2.matrix[i][j] != 0) //если не ноль, то у вершины есть ребро,  для этой и смежной вершины ставим +1 (в массиве вершин 2 графа)
				{
					adjacent_g2[i] ++;
					adjacent_g2[j] ++;
				}
			}	
			for (int t = i; t > 0; t--) // сортируем вершины по количеству инцидентных рёбер оба массива вершин: добавленную вершину ставим на место
			{
				if (adjacent_g1[t] > adjacent_g1[t - 1]) //меняем местами, если у предыдущей вершины больше рёбер (в массиве вершин 1 графа)
				{
					swap(adjacent_g1[t], adjacent_g1[t - 1]);
				}

				if (adjacent_g2[t] > adjacent_g2[t - 1]) //меняем местами, если у предыдущей вершины больше рёбер (в массиве вершин 2 графа)
				{
					swap(adjacent_g2[t], adjacent_g2[t - 1]); 
				}
			}
		}

		for (int i = 0; i < n; i++)
		{
			adjacent[adjacent_g1[i]]++; //делаем масив колличество рёбер-вершин с таким свойством(коллличеством)
			if (adjacent_g1[i] != adjacent_g2[i]) // у нас есть отсортированные массивы вершина-колличество её рёбер, для двух грфов, сравниваем значения этих массивов, в изоморфных они должны быть одинаковы
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