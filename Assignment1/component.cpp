#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <utility>
#include <libgen.h>
#include <set>
#include <iterator>

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
	vector<int> colors = getColors();
	sort(colors.begin(), colors.end());

	int maxComponent = 0;
	auto streakStart = upper_bound(colors.begin(), colors.end(), 0);
	while (streakStart != colors.end()) {
		auto streakEnd = upper_bound(streakStart, colors.end(), *streakStart);
		int componentSize = distance(streakStart, streakEnd);
		maxComponent = max(maxComponent, componentSize);

		streakStart = streakEnd;
	}

	return maxComponent;
}

vector<int> Network::getColors() const
{
	if (edges.size() == 0) {
		return {};
	}

	vector<int> colors(maxNode + 1, 0);

	for (int i = 1; i <= maxNode; i++) {
		if (colors[i] != 0) {
			continue; // Already colored this one.
		}

		set<int> todo = {i}; // Queue implemented as a set to reduce memory footprint.
		while (!todo.empty()) {
			int node = *todo.begin();
			todo.erase(todo.begin());
			if (colors[node] == 0) {
				// Recolor all nodes with his color to the new one.
				// Queue all related nodes to add to this one.
				colors[node] = i;
				auto it = lower_bound(edges.begin(), edges.end(), make_pair(node, 0));
				for (; it != edges.end() && it->first == node; it++) {
					const int color = colors[it->second];
					if (color == 0) {
						todo.insert(it->second);
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
