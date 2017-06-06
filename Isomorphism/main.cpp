#include <map>
#include <functional>
#include <iostream>

#include "Commands.h"

using namespace std;
using namespace isomorphism;

int main(void)
{
	Graph graph1, graph2;

	map<string, function<void()>> commands;

	commands["help"] = help;
	commands["stop"] = stop;
	commands["load"] = [&]() { load(graph1, graph2); };
	commands["show"] = [&]() { show(graph1, graph2); };
	commands["check"] = [&]() { check(graph1, graph2); };

	string command;
	while (true)
	{
		cin >> command;

		if (commands.find(command) != commands.end())
		{
			commands[command]();
		}
		else
		{
			cout << "Unknown command: " << command << endl;
		}
		cout << "........................." << endl;
	}

	clear(graph1);
	clear(graph2);

	return 0;
}