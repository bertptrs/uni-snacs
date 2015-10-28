#ifndef TWITTER_GRAPH_H
#define TWITTER_GRAPH_H

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <map>
#include <string>

using namespace std;

struct Node {
	int componentID;
	int inDegree;

	Node();
};

class TwitterGraph
{
	public:
		static constexpr int NO_COMPONENT = -1;

		TwitterGraph(istream& edges);
		TwitterGraph(const TwitterGraph&) = default;
		TwitterGraph(TwitterGraph&&) = default;

		int numEdges() const;
		int numNodes() const;

		int weakComponents();

		int inDegree(int node) const;
		int outDegree(int node) const;

	private:
		vector<map<int, pair<int, string>>> adjList; // Destination and timestamp.
		vector<Node> nodes; // Offset and number of edges 
		int giantComponentID;

		void recolor(int original, int to);

		template<class CallbackType>
			void bfs(const int startNode, CallbackType callback);
};

#endif
