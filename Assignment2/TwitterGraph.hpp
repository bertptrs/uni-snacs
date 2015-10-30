#ifndef TWITTER_GRAPH_H
#define TWITTER_GRAPH_H

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <queue>

using namespace std;

struct Node {
	int componentID;
	int inDegree;
	int outDegree;
	int eccentricity;

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
		int diameter(int componentID, bool progress = false);
		int eccentricity(int node) const;

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
			void bfs(const int startNode, CallbackType callback)
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
};

#endif
