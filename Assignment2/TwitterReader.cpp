#include "TwitterReader.hpp"

TwitterReader::TwitterReader()
{
}

bool TwitterReader::read(istream& input)
{
	char timestamp[TIMESTAMP_LENGTH + 1] = {0};
	string username;
	string word;

	input.get(timestamp, TIMESTAMP_LENGTH);
	input.ignore();
	input >> username;
	while (input.peek() != '\n') {
		input >> word;
		if (isUsername(word)) {
			
		}
	}

	return !input.eof();
}
