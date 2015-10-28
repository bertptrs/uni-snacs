#include "TwitterGraph.hpp"
#include <algorithm>
#include <cassert>
#include <queue>
#include <iterator>

Node::Node():
	componentID(TwitterGraph::NO_COMPONENT),
	inDegree(0)
{
}

TwitterGraph::TwitterGraph(istream& input) :
	nodes(1),
	giantComponentID(-1)
{
	int from, to;
	char timestamp[21] = {0};
	while (input >> from >> to) {
		input.ignore();
		input.read(timestamp, 20);
		const unsigned int requiredSize = max(from, to) + 1;
		if (nodes.size() < requiredSize) {
			nodes.resize(requiredSize);
			adjList.resize(requiredSize);
		}

		nodes[to].inDegree++;
		adjList[from][to].first++;

		if (adjList[from][to].first == 1) {
			adjList[from][to].second = string(timestamp);
		}
	}
}

int TwitterGraph::numEdges() const
{
	return accumulate(adjList.begin(), adjList.end(), 0, [](int curSum, const map<int, pair<int, string>>& item) {
			return curSum + item.size();
			});
}

int TwitterGraph::numNodes() const
{
	return nodes.size() - 1;
}

int TwitterGraph::weakComponents()
{
	int maxComponent = 0;
	for (unsigned int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i].componentID == NO_COMPONENT) {
			const int currentComponent = maxComponent++;
			bfs(i, [currentComponent, this] (int i) -> bool {
				if (nodes[i].componentID == NO_COMPONENT) {
					nodes[i].componentID = currentComponent;
					return true;
				} else if (nodes[i].componentID != currentComponent) {
					recolor(nodes[i].componentID, currentComponent);
					return false;
				}

				return false;
			});
		}
	}

	// Count the occurrernces for the different components.
	vector<int> componentCounts(nodes.size(), 0);
	for (const auto& node : nodes) {
		componentCounts[node.componentID]++;
	}

	// Save the largest component ID and return the size.
	const auto it = max_element(componentCounts.begin(), componentCounts.end());
	giantComponentID = distance(componentCounts.begin(), it);

	return *it;
}

template<class CallbackType>
void TwitterGraph::bfs(const int startNode, CallbackType callback)
{
	vector<bool> queued(nodes.size(), false);
	queue<int> todo;

	todo.push(startNode);
	queued[startNode] = true;

	while (!todo.empty()) {
		const int current = todo.front();
		todo.pop();

		const bool shouldQueue = callback(current);
		for (const auto edge : adjList[current]) {
			const int next = edge.first;
			if (!queued[next] && shouldQueue) {
				todo.push(next);
				queued[next] = true;
			}
		}
	}
}

void TwitterGraph::recolor(int original, int to)
{
	for (auto& node : nodes)
	{
		if (node.componentID == original) {
			node.componentID = to;
		}
	}
}

int TwitterGraph::inDegree(int node) const
{
	return nodes[node].inDegree;
}

int TwitterGraph::outDegree(int node) const
{
	return accumulate(adjList[node].begin(), adjList[node].end(), 0, [] (int curSum, const pair<int, pair<int, string>>& item) {
		return curSum + item.second.first;
	});
}
