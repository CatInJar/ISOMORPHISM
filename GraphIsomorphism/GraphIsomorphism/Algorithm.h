#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <numeric>
#include <algorithm>

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

// ������� ���������� �����
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

// ��������� ����� �� ������ ������ �� ���������� �������� � ��������� ���
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

// ������������ �������������� ������� �� ������� ����� � �������� �� �������
inline bool matchVertices(const Graph& graph1, const Graph& graph2, 
	const vector<int>& vertices, const vector<int>& permutation)
{
	for (int i = 0; i < permutation.size(); i++)
	{
		for (int j = 0; j < permutation.size(); j++)
		{
			if (graph1.matrix[vertices[i]][vertices[j]] != graph2.matrix[permutation[i]][permutation[j]])
			{
				return false;
			}
		}
	}
	return true;
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

	// �������� �� ������� ����� ������ ������������
	for (auto it1 = groups1.begin(), end1 = groups1.end(), it2 = groups2.begin();
		it1 != end1; it1++, it2++)
	{
		auto vertices1 = it1->second;
		auto vertices2 = it2->second;

		vector<int> permutation = vertices2;

		bool isomorphicGroup = false;
		// ���������� ��� ������������ ������ � ������ ������� �����
		do
		{
			// �������� ����������� ������� �� �����, �� ���� ����� ����������
			if (matchVertices(graph1, graph2, vertices1, permutation))
			{
				isomorphicGroup = true;
			}
		}
		while (next_permutation(permutation.begin(), permutation.end()));

		// ���� ���� �� � ����� ������ �� ������ ����������, �� ����� �� ���������
		if (isomorphicGroup == false)
		{
			return false;
		}
	}

	return true;
}