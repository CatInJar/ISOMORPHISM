#pragma once

#include <string>

#include "Graph.h"

namespace isomorphism
{
	void help();
	void stop();
	void load(Graph& graph1, Graph& graph2);
	void rig(Graph& graph1, Graph& graph2, int n);
	void show(const Graph& graph1, const Graph& graph2);
	void check(const Graph& graph1, const Graph& graph2);
}