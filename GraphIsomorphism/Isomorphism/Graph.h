#pragma once

namespace isomorphism
{
	struct Graph
	{
		int n = 0;
		int** matrix = nullptr;
	};

	void clear(Graph& graph);
	void init(Graph& graph);
	void createRIGs(Graph& graph1, Graph& graph2);
	void print(const Graph& graph);
}