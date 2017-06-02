#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <fstream>

using namespace std;

/*
TODO:

1. Может быть разнести по файлам.
2. Обработка ошибок.
3. Комменты (примечания).

*/

struct Graph
{
	int n = 0;
	int** matrix = nullptr;

	void clear()
	{
		if (matrix != nullptr)
		{
			for (int i = 0; i < n; i++)
			{
				delete[] matrix[i];
			}
			delete[] matrix;
		}
	}

	void init()
	{
		matrix = new int*[n];
		for (int i = 0; i < n; i++)
		{
			matrix[i] = new int[n];
		}
	}

	void print()
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
	}
};

Graph graph1;
Graph graph2;

void help()
{
	cout << "stop - exit from program" << endl;
	cout << "load - load graphs from file" << endl;
	cout << "show - print graphs" << endl;
	cout << "check - check if graphs are isomorphic and show possible permutation" << endl;
}

void stop()
{
	exit(0);
}

void loadGraph(Graph& graph, string filename)
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

void load()
{
	loadGraph(graph1, "graph1.txt");
	loadGraph(graph2, "graph2.txt");
}

void show()
{
	cout << "First graph:" << endl;
	graph1.print();
	
	cout << "Second graph:" << endl;
	graph2.print();
}

void check()
{
	//Здесь будет алгоритм
}

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
	}
	return 0;
}