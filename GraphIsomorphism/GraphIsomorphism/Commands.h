#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "Algorithm.h"

using namespace std;

inline void help()
{
	cout << " stop - exit from program" << endl;
	cout << " load - load graphs from file" << endl;
	cout << " show - print graphs" << endl;
	cout << " check - check if graphs are isomorphic and show possible permutation" << endl;
}

inline void stop()
{
	exit(0);
}

inline void loadGraph(Graph &graph, string filename)
{
	ifstream file(filename);

	graph.clear();
	file >> graph.n;
	graph.init();

	for (int i = 0; i < graph.n; i++)
	{
		for (int j = 0; j < graph.n; j++)
		{
			file >> graph.matrix[i][j];
		}
	}

	file.close();
}

inline void load(Graph &graph1, Graph &graph2)
{
	loadGraph(graph1, "graph1.txt");
	loadGraph(graph2, "graph2.txt");
}

inline void show(Graph graph1, Graph graph2)
{
	cout << "First graph:" << endl;
	graph1.print();

	cout << "Second graph:" << endl;
	graph2.print();
}