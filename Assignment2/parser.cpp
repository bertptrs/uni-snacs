#include <iostream>
#include "TwitterReader.hpp"
#include "TwitterGraph.hpp"
#include <fstream>
#include <locale>

using namespace std;

int main(int argc, char** argv)
{
	TwitterReader twitter;
	for (int i = 1; i < argc; i++) {
		TwitterGraph g(argv[i]);
	}
	return 0;
}

