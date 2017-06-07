#include "Algorithm.h"

#include <iostream>
#include <map>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <iomanip>

using namespace std;

namespace isomorphism
{
	// ������� ��������� ������������
	void printPermutation(const vector<int>& permutation)
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

	// ���������� �������� �����
	int graphDiameter(const Graph& graph)
	{
		int diameter = 0;
		int* distance = new int[graph.n];

		const int noWay = 4000; // ������ ������������� 

		// ������ ������ ��������, ��� i-�� ������ �������� � ���� ������ ������ � ������� ����� ������� � i-�� �������
		vector<int>* adjacent = new vector<int>[graph.n];
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

		// ��� ������ ������� ���� ��������� �� ������ ������
		for (int curentVertex = 0; curentVertex < graph.n; curentVertex++)
		{
			position = 0;

			for (int i = 0; i < graph.n; i++)
			{
				visited[i] = false;
			}

			for (int i = 0; i < graph.n; i++)
			{
				distance[i] = noWay;
			}

			distance[curentVertex] = 0;

			// ���� ������� � ���������� ������ ���� �� �������� ������� 
			for (int i = 0; i < graph.n; i++)
			{
				minimum = noWay;
				position = 0;
				for (int j = 0; j < graph.n; j++)
				{
					if (distance[j] < minimum && !visited[j])
					{
						minimum = distance[j];
						position = j;
					}
				}
				visited[position] = true;

				// ��������� �������� �������� 
				for (int i = 0; i < adjacent[position].size(); i++)
				{
					distance[adjacent[position][i]] =
						min(distance[adjacent[position][i]], (distance[position] + 1));
				}
			}

			for (int i = 0; i < graph.n; i++)
			{
				if (distance[i] > diameter && distance[i] != noWay)
				{
					diameter = distance[i];
				}
			}
		}

		delete[] distance;
		delete[] visited;

		return diameter;
	}

	// ������� ���������� �����
	int countEdges(const Graph& graph)
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
	map<pair<int, int>, vector<int>> splitToGroups(const Graph& graph)
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

	// ������� ������� ��� ������ ������
	Graph createGroupGraph(Graph graph, const vector<int>& vertices)
	{
		Graph groupGraph;
		groupGraph.n = vertices.size();
		init(groupGraph);

		for (int i = 0; i < groupGraph.n; i++)
		{
			for (int j = 0; j < groupGraph.n; j++)
			{
				groupGraph.matrix[i][j] = graph.matrix[vertices[i]][vertices[j]];
			}
		}

		return groupGraph;
	}

	// ������������ �������������� ������� �� ������� ����� � �������� �� �������
	bool matchVertices(const Graph& graph1, const Graph& graph2, const vector<int>& permutation)
	{
		for (int i = 0; i < permutation.size(); i++)
		{
			for (int j = 0; j < permutation.size(); j++)
			{
				if (graph1.matrix[i][j] != graph2.matrix[permutation[i]][permutation[j]])
				{
					return false;
				}
			}
		}
		return true;
	}

	// ��������� ����� �� ���������� � ������� ������������, ���� ����� ����������
	bool graphIsomorphism(const Graph& graph1, const Graph& graph2)
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

		// ����� �� ��������
		if (graphDiameter(graph1) != graphDiameter(graph2))
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

		vector<int> permutation(graph1.n); // ������� �������� ������������ ������� �����

		// �������� �� ������� ����� ������ ������������
		for (auto it1 = groups1.begin(), end1 = groups1.end(), it2 = groups2.begin();
			it1 != end1; it1++, it2++)
		{
			auto vertices1 = it1->second;
			auto vertices2 = it2->second;

			// ��������� ������ ��� �����
			Graph groupGraph1 = createGroupGraph(graph1, vertices1);
			Graph groupGraph2 = createGroupGraph(graph2, vertices2);

			vector<int> groupPerm(vertices2.size()); // ������������ ������ ������� �����
			map<int, int> groupMatch; // ���������� ������ ������, ����� �������� �� � �������� ������������
			for (int i = 0; i < vertices2.size(); i++)
			{
				groupPerm[i] = i;
				groupMatch[i] = vertices2[i];
			}

			bool isomorphicGroup = false;
			// ���������� ��� ������������ ������ � ������ ������� �����
			do
			{
				// �������� ����������� ������� �� �����, �� ���� ����� ����������
				if (matchVertices(groupGraph1, groupGraph2, groupPerm))
				{
					isomorphicGroup = true;

					for (int i = 0; i < groupPerm.size(); i++)
					{
						permutation[vertices1[i]] = groupMatch[groupPerm[i]];
					}

					break;
				}
			}
			while (next_permutation(groupPerm.begin(), groupPerm.end()));

			clear(groupGraph1);
			clear(groupGraph2);

			// ���� ���� �� � ����� ������ �� ������ ����������, �� ����� �� ���������
			if (isomorphicGroup == false)
			{
				return false;
			}
		}

		printPermutation(permutation);

		// Just testing
		if (graph1.n < 51)
		{
			print(graph1);
			cout << endl;
			for (int i = 0; i < graph2.n; i++)
			{
				for (int j = 0; j < graph2.n; j++)
				{
					cout << graph2.matrix[permutation[i]][permutation[j]] << " ";
				}
				cout << endl;
			}
		}

		cout << "groups" << endl;
		for each (auto item in groups1)
		{
			cout << endl;
			cout << "< " << item.first.first << "_;_" << item.first.second << " >   ";
			for each (auto vert in item.second)
			{
				cout << vert<<" ";
			}
		}
		cout << endl;

		for each (auto item in groups2)
		{
			cout << endl;
			cout << "< " << item.first.first << "_;_" << item.first.second << " >   ";
			for each (auto vert in item.second)
			{
				cout << vert << " ";
			}
		}
		cout << endl;

		return true;
	}
}