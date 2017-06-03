#pragma once

#include <iostream>
#include <map>
#include <vector>

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

inline int countEdges(Graph graph)
{
	int count = 0;

	for (int i = 0; i < graph.n; i++)
	{
		for (int j = 0; j < graph.n; j++)
		{
			if (graph.matrix[i][j] != 0)
			{
				count++;
			}
		}
	}
	
	return count;
}

inline map<pair<int, int>, vector<int>> splitToGroups(Graph graph)
{
	map<pair<int, int>, vector<int>> groups;

	for (int i = 0; i < graph.n; i++)
	{
		pair<int, int> vertex;

		for (int j = 0; j < graph.n; j++)
		{
			if (graph.matrix[i][j] != 0)
			{
				vertex.first++;
			}

			if (graph.matrix[j][i] != 0)
			{
				vertex.second++;
			}
		}

		groups[vertex].push_back(i);
	}

	return groups;
}

inline bool check1(Graph graph1, Graph graph2)
{
	// Равно ли количество вершин
	if (graph1.n != graph2.n)
	{
		return false;
	}

	// Равно ли количество дуг
	if (countEdges(graph1) != countEdges(graph2))
	{
		return false;
	}

	// Разбиваем граф на группы вершин по количеству исходящих и входящих дуг
	// Проверять на изоморфизм нужно уже каждую группу в отдельности
	auto groups1 = splitToGroups(graph1);
	auto groups2 = splitToGroups(graph2);

	// Сравнение двух групп
	auto predicate = [](auto a, auto b)
	{
		return a.first == b.first && a.second.size() == b.second.size();
	};

	// Группы и количество вершин в каждой должны совпадать, иначе графы не изоморфны
	if (groups1.size() != groups2.size() ||
		!equal(groups1.begin(), groups1.end(), groups2.begin(), predicate))
	{
		return false;
	}



	return true;
}