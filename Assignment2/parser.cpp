#include <iostream>
#include "TwitterReader.hpp"
#include <fstream>
#include <locale>

using namespace std;

int main(int argc, char** argv)
{
	TwitterReader twitter;
	for (int i = 1; i < argc; i++) {
		wifstream file(argv[i]);
		while (twitter.read(file)) {
		}
	}
	return 0;
}

