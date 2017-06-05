#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <iomanip>

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

inline void printPermutation(const vector<int>& permutation)
{
	cout << "Permutation:" << endl;
	for (int i = 0; i < permutation.size(); i++)
	{
		cout << setw(3) << i + 1 << " ";
	}
	cout << endl;

	for (int i = 0; i < permutation.size(); i++)
	{
		cout << setw(3) << permutation[i] + 1 << " ";
	}
	cout << endl;
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

inline vector<int**> randomIsomorphicMatrix(int n)
{
	vector<int**> randomIsomMatrix; 
	
	int** m1 = new int*[n];
	int** m2 = new int*[n];

	for (int i = 0; i < n; i++)
	{
		m1[i] = new int[n];
		m2[i] = new int[n];
	}	

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n ; j++)
		{
			m1[i][j] = m2[i][j] = rand() % 2;
			if (i == j)
			{
				m1[i][j] = m2[i][j] = 0;
			}
		}
	}

	int r1, r2;  // r1 - ��������� ������,  r2 - ��������� �����
	int count = 0; 
	bool d = true; // ��� �������� ��������� �� ����
	while (count < n || d) // ������ n-��� � ���� ��������� �� ������ �������
	{
		d = false;
		count++;

		r2 = 1 + rand() % 2;
		r1 = rand() % (n - r2);

		swap(m2[r1], m2[r1 + r2]); // ������ ������

		for (int i = 0; i < n; i++) //������ �������
		{
			swap(m2[i][r1], m2[i][r1 + r2]);
		}

		for (int i = 0; i < n; i++) //�������� ���������
		{
			if (m2[i][i] != 0)
			{
				d = true;
			}
		}
	}

	randomIsomMatrix.push_back(m1);
	randomIsomMatrix.push_back(m2);

	return randomIsomMatrix;
}

inline int** distanceMatrix(const Graph& graph)
{
	int** distanceMatrix = new int*[graph.n];

	const int noWay = 4000; // ������ ������������� 

    // ������ ������ ��������, ��� i-�� ������ �������� � ���� ������ ������ � ������� ����� ������� � i-�� �������
	vector<int> adjacent[1001];
	for (int i = 0; i < graph.n; i++)
	{
		for (int j = 0; j < graph.n; j++)
		{
			if (graph.matrix[i][j] != 0)
			{
				adjacent[i].push_back(j);
			}
		}
	}

	bool* visited = new bool[graph.n];
	int minimum = noWay;
	int position;

	//��� ������ ������� ���� ��������� �� ������ ������
	for (int curentVertex = 0; curentVertex < graph.n; curentVertex++)
	{
		distanceMatrix[curentVertex] = new int[graph.n];

		position = 0;

		for (int i = 0; i < graph.n; i++)
		{
			visited[i] = false;
		}

		for (int i = 0; i < graph.n; i++)
		{
			distanceMatrix[curentVertex][i] = noWay;
		}

		distanceMatrix[curentVertex][curentVertex] = 0;

		//���� ������� � ���������� ������ ���� �� �������� ������� 
		for (int i = 0; i < graph.n; i++)
		{ 
			minimum = noWay;
			position = 0;
			for (int j = 0; j < graph.n; j++)
			{
				if (distanceMatrix[curentVertex][j] < minimum && !visited[j])
				{
					minimum = distanceMatrix[curentVertex][j];
					position = j;
				}
			}
			visited[position] = true; 

			// ��������� �������� �������� 
			for (int i = 0; i < adjacent[position].size(); i++)
			{ 
				distanceMatrix[curentVertex][adjacent[position][i]] = 
					min(distanceMatrix[curentVertex][adjacent[position][i]], (distanceMatrix[curentVertex][position] + 1));
			}
		}		
	}

	//�������� ����� �������, ������ �������� noWay c 4000 �� -1    <<<<<<<<<<<<<<<<<<<<<<<<<
	cout << endl << "distance matrix"<< endl;
	for (int i = 0; i < graph.n; i++)
	{
		for (int j = 0; j < graph.n; j++)
		{
			cout << setw(3)<< ((distanceMatrix[i][j] == noWay) ? distanceMatrix[i][j] = -1 : distanceMatrix[i][j]) << " ";
		}
		cout << endl;
	}

	return distanceMatrix;
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

inline bool graphIsomorphism(const Graph& graph1, const Graph& graph2)
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

	vector<int> permutation(graph1.n);

	// �������� �� ������� ����� ������ ������������
	for (auto it1 = groups1.begin(), end1 = groups1.end(), it2 = groups2.begin();
		it1 != end1; it1++, it2++)
	{
		auto vertices1 = it1->second;
		auto vertices2 = it2->second;

		vector<int> groupPerm = vertices2;

		bool isomorphicGroup = false;
		// ���������� ��� ������������ ������ � ������ ������� �����
		do
		{
			// �������� ����������� ������� �� �����, �� ���� ����� ����������
			if (matchVertices(graph1, graph2, vertices1, groupPerm))
			{
				isomorphicGroup = true;

				for (int i = 0; i < groupPerm.size(); i++)
				{
					permutation[vertices2[i]] = groupPerm[i];
				}
			}
		}
		while (next_permutation(groupPerm.begin(), groupPerm.end()));

		// ���� ���� �� � ����� ������ �� ������ ����������, �� ����� �� ���������
		if (isomorphicGroup == false)
		{
			return false;
		}
	}

	printPermutation(permutation);
	
	return true;
}