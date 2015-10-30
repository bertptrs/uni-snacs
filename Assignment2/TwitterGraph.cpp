#include "TwitterGraph.hpp"
#include <algorithm>
#include <cassert>
#include <queue>
#include <iterator>
#include <limits>
#include <set>

Node::Node():
	componentID(TwitterGraph::NO_COMPONENT),
	inDegree(0),
	outDegree(0),
	eccentricity(-1)
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
		nodes[from].outDegree++;
		adjList[from][to]++;
		adjList[to][from]++;
	}
}

int TwitterGraph::numEdges(int componentID) const
{
	if (componentID == NO_COMPONENT) {
	return accumulate(adjList.begin(), adjList.end(), 0, [](int curSum, const map<int, int>& item) {
			return curSum + item.size();
			}) / 2;
	} else {
		int edgesNo = 0;
		for (int i = 0; i < (int) nodes.size(); i++) {
			if (nodes[i].componentID != componentID) {
				continue;
			}
			for (auto& neighbour : adjList[i]) {
				if (nodes[neighbour.first].componentID == componentID) {
					edgesNo++;
				}
			}
		}
		return edgesNo / 2;
	}
}

int TwitterGraph::numNodes(int componentID) const
{
	if (componentID == NO_COMPONENT) {
		return nodes.size() - 1;
	} else {
		return count_if(nodes.begin(), nodes.end(), [componentID](const Node& node) -> bool {
			return node.componentID == componentID;
		});
	}
}

int TwitterGraph::inDegree(int node) const
{
	return nodes[node].inDegree;
}

int TwitterGraph::outDegree(int node) const
{
	return nodes[node].outDegree;
}

void TwitterGraph::print(ostream& stream, int componentID) const
{
	for (int i = 0; i < numNodes(); i++)
	{
		if (componentID != NO_COMPONENT && nodes[i].componentID != componentID) {
			continue;
		}

		for (auto& neighbour : adjList[i]) {
			if (neighbour.first >= i) {
				break;
			}
			stream << i << "\t" << neighbour.first << "\t" << neighbour.second << endl;
		}
	}
}

int TwitterGraph::eccentricity(int node) const
{
	return nodes[node].eccentricity;
}
