#include "Graph.h"

using namespace std;

int main(void)
{
	map<string, function<void()>> commands;
	
	commands["help"] = help;
	commands["stop"] = stop;
	commands["load"] = load;
	commands["show"] = show;
	commands["check"] = check;

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
		cout << endl;
	}
	return 0;
}