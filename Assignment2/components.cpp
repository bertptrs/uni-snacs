#include "TwitterGraph.hpp"
#include <vector>
#include <iterator>
#include <algorithm>

int TwitterGraph::weakComponents()
{
	int maxComponent = 0;
	for (unsigned int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i].componentID == NO_COMPONENT) {
			const int currentComponent = maxComponent++;
			bfs(i, [currentComponent, this] (int i) -> bool {
				if (nodes[i].componentID == NO_COMPONENT) {
					nodes[i].componentID = currentComponent;
					return true;
				} else if (nodes[i].componentID != currentComponent) {
					recolor(nodes[i].componentID, currentComponent);
					return false;
				}

				return false;
			});
		}
	}

	// Count the occurrernces for the different components.
	vector<int> componentCounts(nodes.size(), 0);
	for (const auto& node : nodes) {
		componentCounts[node.componentID]++;
	}

	// Save the largest component ID and return the size.
	const auto it = max_element(componentCounts.begin(), componentCounts.end());
	giantComponentID = distance(componentCounts.begin(), it);

	return giantComponentID;
}

void TwitterGraph::recolor(int original, int to)
{
	for (auto& node : nodes)
	{
		if (node.componentID == original) {
			node.componentID = to;
		}
	}
}
