#include <map>
#include <functional>
#include <iostream>
#include <ctime>

#include "Commands.h"

using namespace std;

/*
TODO:
1. Алгоритм.
2. Обработка ошибок.
3. Комменты.
*/

int main(void)
{
	Graph graph1, graph2;

	map<string, function<void()>> commands;
	
	commands["help"] = help;
	commands["stop"] = stop;
	commands["load"] = [&]() { load(graph1, graph2); };
	commands["show"] = [&]() { show(graph1, graph2); };
	commands["check"] = [&]() { cout << (check(graph1, graph2) ? "isomorphic" : "not isomorphic") << endl; };

	string command;
	while (true)
	{
		cin >> command;
		
		if (commands.find(command) != commands.end())
		{
			clock_t t1 = clock();
			commands[command]();
			clock_t t2 = clock();
			if (command == "check")
			{
				cout <<"time: "<< (t2 - t1 + .0) / CLOCKS_PER_SEC << endl;
			}
		}
		else
		{
			cout << "Unknown command: " << command << endl;
		}
		cout << "........................." << endl;
	}
	return 0;
}