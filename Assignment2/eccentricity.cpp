#include "TwitterGraph.hpp"
#include <iostream>
#include <set>
#include <limits>
#include <algorithm>

using namespace std;


/**
 * Implementation of the graph diameter algorithm by Frank Takes.
 *
 * Slight adaptations to compute the eccentricity for all nodes, rather than the largest eccentricity.
 */
int TwitterGraph::diameter(int componentID, bool progress)
{
	vector<pair<int, int>> bounds(adjList.size(), make_pair(0, numeric_limits<int>::max()));
	vector<int> distance(adjList.size());

	set<int> toCompute;

	for (int i = 0; i < (int) adjList.size(); i++) {
		if (nodes[i].componentID != componentID) {
			bounds[i] = make_pair(0, 0);
		} else {
			toCompute.insert(i);
		}
	}

	int it = 1;
	while (!toCompute.empty()) {
		// Pick a point to be computed.
		int bestNode = -1;
		pair<int, int> bestProperties = make_pair(0, 0);
		pair<int, int> properties;
		for (int node : toCompute) {
			properties.second = nodes[node].inDegree + nodes[node].outDegree;
			switch (it % 2) {
				case 0:
					// Maximize upper bound
					properties.first = bounds[node].second;
					break;

				case 1:
					// Minimize lower bound
					properties.first = numeric_limits<int>::max() - bounds[node].first;
					break;
			}

			if (properties > bestProperties) {
				bestProperties = properties;
				bestNode = node;
			}
		}

		vector<int> distance = computeDistance(bestNode);
		const int eccentricity = *max_element(distance.begin(), distance.end());
		bounds[bestNode].first = bounds[bestNode].second = nodes[bestNode].eccentricity = eccentricity;
		toCompute.erase(bestNode);

		for (int node : toCompute) {
			if (node == bestNode) {
				continue; // Had this one already.
			}

			bounds[node].first = max(bounds[node].first, max(distance[node], eccentricity - distance[node]));
			bounds[node].second = min(bounds[node].second, eccentricity + distance[node]);
			if (bounds[node].first >= bounds[node].second) {
				// Bound is tight, we are done with this one.
				toCompute.erase(node);
				nodes[node].eccentricity = bounds[node].second;
			}
		}
		it++;
		if (progress) {
			cerr << "Iteration " << it << "\tRemaining " << toCompute.size() << endl;
		}
	}

	return max_element(bounds.begin(), bounds.end())->first;
}
