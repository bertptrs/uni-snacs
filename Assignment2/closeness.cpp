#include "TwitterGraph.hpp"
#include <algorithm>

double TwitterGraph::closeness(int node) const
{
	return nodes[node].closeness;
}

// Create a map of distance -> occurrence for the entire network.
//
// This method will do at most budget bfs's, or the number of nodes in the network, whichever is less.
map<int, int> TwitterGraph::distanceDistribution(int budget, int componentID)
{
	const vector<int> nodes = getShuffled(componentID);
	const int actualBudget = min(budget, (int) nodes.size());

	map<int, int> distribution;
	for (int i = 0; i < actualBudget; i++) {
		const vector<int> D = computeDistance(nodes[i]);
		for (auto distance : D) {
			if (distance > 0) {
				distribution[distance]++;
			}
		}
	}

	return distribution;
}

// This method will set for every node the closeness
//
// For this, we use at most budget bfs's, recording the distance to every node in each iteration.
void TwitterGraph::approximateCloseness(int budget, int componentID)
{
	// First, reset all current closeness measures
	for (int node = 0; node < numNodes(); node++) {
		nodes[node].closeness = 0;
	}
	const vector<int> todo = getShuffled(componentID);

	vector<double> avgD(numNodes(), 0.0);
	const int actualBudget = min(budget, (int) todo.size());
	for (int i = 0; i < actualBudget; i++) {
		const vector<int> D = computeDistance(todo[i]);
		for (int node = 0; node < (int) D.size(); node++) {
			nodes[node].closeness += D[node] / (double) actualBudget;
		}
	}
}
