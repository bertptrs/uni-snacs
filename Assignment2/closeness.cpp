#include "TwitterGraph.hpp"
#include <algorithm>

double TwitterGraph::closeness(int node) const
{
	return nodes[node].closeness;
}

void TwitterGraph::approximateCloseness(int budget, int componentID)
{
	// First, reset all current closeness measures
	for (int node = 0; node < numNodes(); node++) {
		nodes[node].closeness = 0;
	}
	vector<int> todo;
	for (int i = 0; i < numNodes(); i++) {
		if (nodes[i].componentID == componentID) {
			todo.push_back(i);
		}
	}

	shuffle(todo.begin(), todo.end(), random);

	vector<double> avgD(numNodes(), 0.0);
	const int actualBudget = min(budget, (int) todo.size());
	for (int i = 0; i < actualBudget; i++) {
		const vector<int> D = computeDistance(todo[i]);
		for (int node = 0; node < (int) D.size(); node++) {
			nodes[node].closeness += D[node] / (double) actualBudget;
		}
	}
}
