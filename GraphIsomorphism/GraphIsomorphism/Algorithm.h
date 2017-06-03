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
	//����� ����� ��������
	if (graph1.n == graph2.n) //�������� ��������
	{
		int n = graph1.n;
		int* adjacent_g1 = new int[n]; // ������ ����������� ���� ��� ������ ������� 1 �����
		int* adjacent_g2 = new int[n]; // ������ ����������� ���� ��� ������ ������� 2 �����
		int* adjacent = new int[n]; // ���������� ������ � ����������� �������(�����������) ����������� ����

		for (int i = 0; i < n; i++)
		{
			for (int j = i; j < n; j++) //��� �� ������
			{
				if (graph1.matrix[i][j] != 0) // ���� �� ����, �� � ������� ���� �����, ��� ���� � ������� ������� ������ +1 (� ������� ������ 1 �����)
				{
					adjacent_g1[i] ++;
					adjacent_g1[j] ++;
				}

				if (graph2.matrix[i][j] != 0) //���� �� ����, �� � ������� ���� �����,  ��� ���� � ������� ������� ������ +1 (� ������� ������ 2 �����)
				{
					adjacent_g2[i] ++;
					adjacent_g2[j] ++;
				}
			}	
			for (int t = i; t > 0; t--) // ��������� ������� �� ���������� ����������� ���� ��� ������� ������: ����������� ������� ������ �� �����
			{
				if (adjacent_g1[t] > adjacent_g1[t - 1]) //������ �������, ���� � ���������� ������� ������ ���� (� ������� ������ 1 �����)
				{
					swap(adjacent_g1[t], adjacent_g1[t - 1]);
				}

				if (adjacent_g2[t] > adjacent_g2[t - 1]) //������ �������, ���� � ���������� ������� ������ ���� (� ������� ������ 2 �����)
				{
					swap(adjacent_g2[t], adjacent_g2[t - 1]); 
				}
			}
		}

		for (int i = 0; i < n; i++)
		{
			adjacent[adjacent_g1[i]]++; //������ ����� ����������� ����-������ � ����� ���������(�������������)
			if (adjacent_g1[i] != adjacent_g2[i]) // � ��� ���� ��������������� ������� �������-����������� � ����, ��� ���� �����, ���������� �������� ���� ��������, � ���������� ��� ������ ���� ���������
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