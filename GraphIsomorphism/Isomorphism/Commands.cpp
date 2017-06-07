#include "Commands.h"

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#include "Algorithm.h"

using namespace std;

namespace isomorphism
{
	void help()
	{
		cout << " stop - exit from program" << endl;
		cout << " load - load graphs from file" << endl;
		cout << " rig {0} - make random isomorphic graphs, {0} - size" << endl;
		cout << " show - print graphs" << endl;
		cout << " check - check if graphs are isomorphic and show possible permutation" << endl;
	}

	void stop()
	{
		exit(0);
	}

	//создание рандомных изоморфных графов заданной размерности
	void rig(Graph& graph1, Graph& graph2, int n)
	{
		graph1.n = graph2.n = n;
		init(graph1);
		init(graph2);

		createRIGs(graph1, graph2);
	}

	void loadGraph(Graph& graph, const string& filename)
	{
		ifstream file(filename);

		clear(graph);
		file >> graph.n;
		init(graph);

		for (int i = 0; i < graph.n; i++)
		{
			for (int j = 0; j < graph.n; j++)
			{
				file >> graph.matrix[i][j];
			}
		}

		file.close();
	}

	void load(Graph& graph1, Graph& graph2)
	{
		loadGraph(graph1, "graph1.txt");
		loadGraph(graph2, "graph2.txt");
	}

	void show(const Graph& graph1, const Graph& graph2)
	{
		cout << "First graph:" << endl;
		print(graph1);

		cout << "Second graph:" << endl;
		print(graph2);
	}

	void check(const Graph& graph1, const Graph& graph2)
	{
		clock_t t1 = clock();
		bool isomorphic = graphIsomorphism(graph1, graph2);
		clock_t t2 = clock();

		cout << (isomorphic ? "Isomorphic" : "Not isomorphic") << endl;
		cout << "Time: " << (double)(t2 - t1) / CLOCKS_PER_SEC << endl;
	}
}