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
		<< "\tgiant" << endl
		<< "\tdiameter" << endl
		<< "\teccentricities" << endl
		<< "\tcloseness\t budget" << endl
		<< endl;
}

void cmdDegrees(bool out, const TwitterGraph& graph) {
	for (int i = 1; i <= graph.numNodes(); i++) {
		cout << i << "\t" << (out ? graph.outDegree(i) : graph.inDegree(i)) << endl;
	}
}

void cmdStats(TwitterGraph& graph)
{
	int nodes = graph.numNodes(), edges = graph.numEdges();
	cout << "In the entire graph are" << endl
		<< nodes << " nodes" << endl
		<< edges << " edges" << endl
		<< "Density: " << edges / (nodes * (nodes - 1.0)) << endl;

	const int giantComponent = graph.weakComponents();
	nodes = graph.numNodes(giantComponent), edges = graph.numEdges(giantComponent);
	cout << "In the giant component are" << endl
		<< nodes << " nodes" << endl
		<< edges << " edges" << endl
		<< "Density: " << edges / (nodes * (nodes - 1.0)) << endl;
}

void cmdGiant(TwitterGraph& graph)
{
	const int giantComponent = graph.weakComponents();
	graph.print(cout, giantComponent);
}

void cmdDiameter(TwitterGraph& graph)
{
	const int giantComponent = graph.weakComponents();
	cout << "Giant component ID: " << giantComponent << endl;
	cout << "Diameter: " << graph.diameter(giantComponent, true) << endl;
}

void cmdEccentricities(TwitterGraph& graph)
{
	const int giantComponent = graph.weakComponents();
	graph.diameter(giantComponent);
	for (int i = 1; i < graph.numNodes(); i++) {
		if (graph.eccentricity(i) >= 0) {
			cout << i << '\t' << graph.eccentricity(i) << endl;
		}
	}
}

void cmdCloseness(TwitterGraph& graph, int budget)
{
	const int giantComponent = graph.weakComponents();
	graph.approximateCloseness(budget, giantComponent);
	for (int i = 1; i < graph.numNodes(); i++) {
		if (graph.closeness(i) > 0) {
			cout << i << "\t" << graph.closeness(i) << endl;
		}
	}
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

	if (!strcmp(argv[1], "giant")) {
		cmdGiant(g);
		return 0;
	}

	if (!strcmp(argv[1], "diameter")) {
		cmdDiameter(g);
		return 0;
	}

	if (!strcmp(argv[1], "eccentricities")) {
		cmdEccentricities(g);
		return 0;
	}

	if (!strcmp(argv[1], "closeness") && argc >= 3) {
		cmdCloseness(g, atoi(argv[2]));
		return 0;
	}

	cerr << "Unknown command " << argv[1] << endl;
	printUsage(argv);
	return 1;
}
