#pragma once

#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Graph
{
	int n = 0;
	int** matrix = nullptr;
};

inline void clear(Graph& graph)
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

inline void init(Graph& graph)
{
	graph.matrix = new int*[graph.n];
	for (int i = 0; i < graph.n; i++)
	{
		graph.matrix[i] = new int[graph.n];
	}
}

inline void print(const Graph& graph)
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

inline int countEdges(const Graph& graph)
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

inline map<pair<int, int>, vector<int>> splitToGroups(const Graph& graph)
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

inline bool check(const Graph& graph1, const Graph& graph2)
{
	// ����� �� ���������� ������
	if (graph1.n != graph2.n)
	{
		return false;
	}

	// ����� �� ���������� ���
	if (countEdges(graph1) != countEdges(graph2))
	{
		return false;
	}

	// ��������� ���� �� ������ ������ �� ���������� ��������� � �������� ���
	// ��������� �� ���������� ����� ��� ������ ������ � �����������
	auto groups1 = splitToGroups(graph1);
	auto groups2 = splitToGroups(graph2);

	// ��������� ���� �����
	auto predicate = [](auto a, auto b)
	{
		return a.first == b.first && a.second.size() == b.second.size();
	};

	// ������ � ���������� ������ � ������ ������ ���������, ����� ����� �� ���������
	if (groups1.size() != groups2.size() ||
		!equal(groups1.begin(), groups1.end(), groups2.begin(), predicate))
	{
		return false;
	}



	return true;
}