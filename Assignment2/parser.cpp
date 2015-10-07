#include <iostream>
#include "TwitterGraph.hpp"
#include <fstream>

using namespace std;

int main()
{
	cin.ignore(255, '\n'); // Ignore header row.
	TwitterGraph g(cin);
	cout << g.numEdges() << "\t" << g.numNodes() << endl;
	return 0;
}

