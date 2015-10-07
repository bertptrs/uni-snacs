#include "TwitterGraph.hpp"
#include <algorithm>
#include <cassert>

Node::Node():
	numEdges(0),
	edgeOffset(0),
	componentID(-1)
{
}

TwitterGraph::TwitterGraph(istream& input) :
	giantComponentID(-1)
{
	int from, to;
	char timestamp[21] = {0};
	int prevFrom = 0;
	int readEdges = 0;
	while (input >> from >> to) {
		input.ignore();
		input.read(timestamp, 20);
		if (from != prevFrom) {
			assert(from > prevFrom && "Input data should be sorted.");
			nodes.resize(from + 1);
			nodes[prevFrom].numEdges = readEdges;
			nodes[from].edgeOffset = nodes[prevFrom].edgeOffset + readEdges;

			prevFrom = from;
			readEdges = 0;
		}

		edges.push_back(to);
		readEdges++;
	}
}

int TwitterGraph::numEdges() const
{
	return edges.size();
}

int TwitterGraph::numNodes() const
{
	return nodes.size() - 1;
}
