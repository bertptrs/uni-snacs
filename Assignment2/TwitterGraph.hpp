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
	int outDegree;

	Node();
};

class TwitterGraph
{
	public:
		static constexpr int NO_COMPONENT = -1;

		TwitterGraph(istream& edges);
		TwitterGraph(const TwitterGraph&) = default;
		TwitterGraph(TwitterGraph&&) = default;

		int numEdges(int componentID = NO_COMPONENT) const;
		int numNodes(int componentID = NO_COMPONENT) const;

		int weakComponents();

		int inDegree(int node) const;
		int outDegree(int node) const;
		void print(ostream& output, int componentID) const;
		ostream& operator<< (ostream& stream) const
		{
			print(stream, NO_COMPONENT);
			return stream;
		}

	private:
		vector<map<int, int>> adjList; // Destination and timestamp.
		vector<Node> nodes; // Offset and number of edges 
		int giantComponentID;

		void recolor(int original, int to);

		template<class CallbackType>
			void bfs(const int startNode, CallbackType callback);
};

#endif
