#ifndef TWITTER_GRAPH_H
#define TWITTER_GRAPH_H

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <queue>
#include <random>

using namespace std;

struct Node {
	int componentID;
	int inDegree;
	int outDegree;
	int eccentricity;
	double closeness;

	Node();
};

class TwitterGraph
{
	public:
		// Identifier for when we use no connected component, or where indicate
		// that we don't want to use componenets.
		static constexpr int NO_COMPONENT = -1;

		// Construct a graph from any input stream. Assumed format is an edge list.
		TwitterGraph(istream& edges);
		// Default copy and move constructors.
		TwitterGraph(const TwitterGraph&) = default;
		TwitterGraph(TwitterGraph&&) = default;

		// Compute the number of nodes or edges in a certain component.
		int numEdges(int componentID = NO_COMPONENT) const;
		int numNodes(int componentID = NO_COMPONENT) const;

		// Determine the weakly connected components. Returns the ID of the largest component.
		int weakComponents();
		// Compute the eccentricities for every node in the given component.
		//
		// If the progress flag is true, report progress after every BFS.
		int diameter(int componentID, bool progress = false);
		// Return the previously computed eccentricity for a given node.
		int eccentricity(int node) const;
		// Compute approximate closeness for every node in the specified component.
		void approximateCloseness(int budget, int componentID);
		// Compute approximate distance distribution for the specified component.
		map<int, int> distanceDistribution(int budget, int componentID);

		// Check the degree of a certain node.
		int inDegree(int node) const;
		int outDegree(int node) const;

		// Return a previously computed closeness for a node.
		double closeness(int node) const;

		void print(ostream& output, int componentID) const;
		ostream& operator<< (ostream& stream) const
		{
			print(stream, NO_COMPONENT);
			return stream;
		}

	private:
		mt19937 random;
		vector<map<int, int>> adjList; // Destination and timestamp.
		vector<Node> nodes; // Offset and number of edges
		int giantComponentID;

		vector<int> computeDistance(int from);
		// Return the nodes in the specified component, randomly shuffled.
		vector<int> getShuffled(int componentID = NO_COMPONENT) ;

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
