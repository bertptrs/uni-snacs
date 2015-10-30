#include "TwitterGraph.hpp"
#include <algorithm>

double TwitterGraph::closeness(int node) const
{
	return nodes[node].closeness;
}

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
