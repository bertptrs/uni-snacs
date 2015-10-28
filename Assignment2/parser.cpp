#include <iostream>
#include "TwitterGraph.hpp"
#include <fstream>
#include <cstring>

using namespace std;

void printUsage(char** argv)
{
	cerr << "Usage: " << argv[0] << " COMMAND" << endl << endl;
	cerr << "Available commands:" << endl
		<< "\tstats" << endl
		<< "\tindegrees" << endl
		<< "\toutdegrees" << endl
		<< endl;
}

void cmdDegrees(bool out, const TwitterGraph& graph) {
	for (int i = 0; i <= graph.numNodes(); i++) {
		cout << i << "\t" << (out ? graph.outDegree(i) : graph.inDegree(i)) << endl;
	}
}

void cmdStats(TwitterGraph& graph)
{
	cout << "In the entire graph are" << endl;
	cout << graph.numEdges() << " edges" << endl;
	cout << graph.numNodes() << " nodes" << endl;
	int giantComponent = graph.weakComponents();
	cout << "In the giant component are" << endl;
	cout << graph.numEdges(giantComponent) << " edges" << endl;
	cout << graph.numNodes(giantComponent) << " nodes" << endl;
}

int main(int argc, char** argv)
{
	if (argc < 2) {
		printUsage(argv);
		return 1;
	}
	cin.ignore(255, '\n'); // Ignore header row.
	TwitterGraph g(cin);

	if (!strcmp(argv[1], "indegrees") || !strcmp(argv[1], "outdegrees")) {
		cmdDegrees(!strcmp(argv[1], "outdegrees"), g);
		return 0;
	}

	if (!strcmp(argv[1], "stats")) {
		cmdStats(g);
		return 0;
	}

	cerr << "Unknown command " << argv[1] << endl;
	printUsage(argv);
	return 1;
}
