#include <iostream>
#include <string>
#include <fstream>
#include <sstream> 
#include <ctime>
#include "graph.h"

using namespace std;

int readGraph(const string &input, graph &graph) {
	ifstream inputfile(input);
	string line;

	if(inputfile.is_open()) {
		while(getline(inputfile, line)) {
			stringstream ss(line);
			string args[3];
			int count = 0;

			while(ss >> line) {
				args[count] = line;
				count++;
			}

			graph.insert(args[0], args[1], stoi(args[2]));
		}
	}

	inputfile.close();
	return 0;
}

int main() {
	graph graph;
	string inFile;
	string outFile;
	string start;

	cout << "Enter name of graph file: ";
	cin >> inFile;
	readGraph(inFile, graph);
	cout << "Enter name of starting vertex: ";
	cin >> start;

	clock_t begin = clock();

	while(graph.dijkstra(start) == -1) {
		cout << "Not a valid vertex. Try again." << "\n";
		cout << "Enter name of starting vertex: ";
		cin >> start;
	}

	clock_t end = clock();
	double time = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

	cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << time << "\n";
	cout << "Enter name of the output  file: ";
	cin >> outFile;

	graph.printGraph(outFile);
    return 0;
}