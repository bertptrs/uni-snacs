#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <utility>
#include <libgen.h>
#include <queue>

using namespace std;

typedef pair<int, int> edge_t;

class Network {
	public:
		void read(istream& input);
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

int Network::largestComponentSize() const
{
	const vector<int> colors = getColors();
	vector<int> counts(colors.size(), 0);

	for (const int& color : colors) {
		counts[color]++;
	}

	return *max_element(counts.begin(), counts.end());
}

vector<int> Network::getColors() const
{
	if (edges.size() == 0) {
		return {};
	}

	vector<int> colors(maxNode + 1, 0);

	queue<int> todo; // Allocated outside the loop to prevent excess allocations.
	for (int i = 1; i <= maxNode; i++) {
		if (colors[i] != 0) {
			continue; // Already colored this one.
		}

		todo.push(i);
		while (!todo.empty()) {
			int node = todo.front();
			todo.pop();
			if (colors[node] == 0) {
				// Recolor all nodes with his color to the new one.
				// Queue all related nodes to add to this one.
				colors[node] = i;
				auto it = lower_bound(edges.begin(), edges.end(), make_pair(node, 0));
				for (; it != edges.end() && it->first == node; it++) {
					const int color = colors[it->second];
					if (color == 0) {
						todo.push(it->second);
					} else if (color != i) {
						// Do it immediately, so we don't have multiple recolors in the queue.
						replace(colors.begin(), colors.end(), color, i);
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
		Network network;
		network.read(input);
		cout << basename(argv[i]) << ": " << network.largestComponentSize() << endl;
	}
}
