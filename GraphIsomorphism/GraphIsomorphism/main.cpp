﻿#include <map>
#include <functional>
#include <iostream>
#include <ctime>

#include "Commands.h"

using namespace std;

int main(void)
{
	Graph graph1, graph2;

	map<string, function<void()>> commands;
	
	commands["help"] = help;
	commands["stop"] = stop;
	commands["load"] = [&]() { load(graph1, graph2); };
	commands["show"] = [&]() { show(graph1, graph2); };
	commands["check"] = [&]()
	{
		clock_t t1 = clock();
		bool isomorphic = check(graph1, graph2);
		clock_t t2 = clock();
		
		cout << (check(graph1, graph2) ? "isomorphic" : "not isomorphic") << endl;
		cout << "time: " << (t2 - t1) / CLOCKS_PER_SEC << endl;
	};

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