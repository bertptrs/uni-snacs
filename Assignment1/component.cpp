#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <utility>
#include <libgen.h>
#include <set>
#include <queue>

using namespace std;

typedef pair<int, int> edge_t;

class Network {
	public:
		void read(istream& input);
		int degree(int node) const;
		int nEdges() const;
		int nNodes() const;
		int largestComponentSize() const;
		
	private:
		vector<edge_t> edges;
		int maxNode;

		vector<int> getColors() const;
};

void Network::read(istream& input)
{
	maxNode = 0;
	edges = vector<edge_t>();

	int from, to;
	while ((input >> from >> to))
	{
		edges.emplace_back(from, to);
		maxNode = max(maxNode, max(from, to));
	}

	sort(edges.begin(), edges.end());
}

int Network::nEdges() const
{
	return edges.size();
}

int Network::nNodes() const
{
	set<int> nodes;
	for (auto& edge : edges)
	{
		nodes.insert(edge.first);
		nodes.insert(edge.second);
	}

	return nodes.size();
}

int Network::largestComponentSize() const
{
	
	vector<int> colors = getColors();
	sort(colors.begin(), colors.end());

	// Now determine the longest streak
	int maxConnected = 0;
	for (int i = 0; i < maxNode; i++) {
		if (i % 10000 == 0) {
			cerr << i << endl;
		}
		int connected = 1;
		const int color = colors[i];
		if (color == 0) {
			continue;
		}
		for (i = i + 1; i < maxNode && colors[i] == color; i++, connected++);

		maxConnected = max(maxConnected, connected);
	}

	return maxConnected;
}

vector<int> Network::getColors() const
{
	if (edges.size() == 0) {
		return {};
	}

	vector<int> colors(maxNode + 1, 0);

	queue<int> todo;
	for (int i = 1; i < maxNode; i++) {
		if (colors[i] != 0) {
			continue; // Already colored this one.
		}

		todo.push(i);
		while (!todo.empty()) {
			int node = todo.front();
			todo.pop();
			if (colors[node] != i) {
				if (colors[node] != 0) {
					// Recolor all nodes with his color to the new one.
					replace(colors.begin(), colors.end(), colors[node], i);
				} else {
					// Queue all related nodes to add to this one.
					colors[node] = i;
					auto it = lower_bound(edges.begin(), edges.end(), make_pair(node, 0));
					for (; it != edges.end() && it->first == node; it++) {
						if (colors[it->second] != i) {
							todo.push(it->second);
						}
					}
				}
			}
		}
	}

	return colors;
}

int main(int argc, char** argv)
{
	for (int i = 1; i < argc; i++)
	{
		ifstream input(argv[i]);
		cout << basename(argv[i]) << ": " << endl;

		Network network;
		network.read(input);
		cout << "\tEdges: " << network.nEdges() << endl;
		cout << "\tNodes: " << network.nNodes() << endl;
		cout << "\tLargest component: " << network.largestComponentSize() << endl;
	}
}
