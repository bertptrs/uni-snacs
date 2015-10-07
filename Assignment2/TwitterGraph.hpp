#ifndef TWITTER_GRAPH_H
#define TWITTER_GRAPH_H

#include <string>
#include <utility>
#include <vector>
#include <iostream>

using namespace std;

struct Node {
	int numEdges;
	int edgeOffset;
	int componentID;

	Node();
};

class TwitterGraph
{
	public:
		TwitterGraph(istream& edges);
		TwitterGraph(const TwitterGraph&) = default;
		TwitterGraph(TwitterGraph&&) = default;

		int numEdges() const;
		int numNodes() const;

		void componentize();

	private:
		vector<int> edges; // Destination and timestamp.
		vector<Node> nodes; // Offset and number of edges 
		int giantComponentID;

		void recolor(int original, int to);
};

#endif
