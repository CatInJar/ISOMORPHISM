#include <map>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "Commands.h"

using namespace std;
using namespace isomorphism;

int main(void)
{
	Graph graph1, graph2;
	int n = 5;

	map<string, function<void()>> commands;

	commands["help"] = help;
	commands["stop"] = stop;
	commands["rig"] = [&]() { rig(graph1, graph2, n); };
	commands["load"] = [&]() { load(graph1, graph2); };
	commands["show"] = [&]() { show(graph1, graph2); };
	commands["check"] = [&]() { check(graph1, graph2); };

	vector<string> vc;

	string command;
	string buffer;

	while (true)
	{
		n = 0;

		getline(cin, command);

		if (commands.find(command) != commands.end())
		{
			commands[command]();
		}
		else
		{
			buffer = "";
			for (int i = 0; i < command.size(); i++) {
				if (command[i] != ' ') {
					buffer += command[i];
				}
				else {
					vc.push_back(buffer);
					buffer = "";
				}
			}
			vc.push_back(buffer);

			try
			{
				if (vc.size() == 2 && commands.find(vc[0]) != commands.end())
				{
					n = atoi(vc[1].c_str());
					commands[vc[0]]();
				}
				else
				{
					cout << "Unknown command: " << command << endl;
				}
			}
			catch (exception)
			{
				cout << " rig {0} - make random isomorphic graphs, {0} - size (number)" << endl;
			}
		}
		cout << "........................." << endl;

		vc.clear();
	}

	clear(graph1);
	clear(graph2);

	return 0;
}