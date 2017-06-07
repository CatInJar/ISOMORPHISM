#include <map>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>

#include "Commands.h"

using namespace std;
using namespace isomorphism;

int main(void)
{
	srand(time(NULL));

	Graph graph1, graph2;
	map<string, function<void()>> commands;

	commands["help"] = help;
	commands["stop"] = stop;
	commands["random"] = [&]()
	{
		string parameter;
		cin >> parameter;
		int n = atoi(parameter.c_str());

		rig(graph1, graph2, n);
	};
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
		cin.clear();
	}

	clear(graph1);
	clear(graph2);

	return 0;
}