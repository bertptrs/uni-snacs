#include "TwitterReader.hpp"
#include <sstream>
#include <locale>
#include <stdexcept>
#include <cwctype>
#include <algorithm>

TwitterReader::TwitterReader()
{
	locale::global(locale(""));
}

bool TwitterReader::read(wistream& input)
{
	wchar_t timestamp[TIMESTAMP_LENGTH];
	wstring username;
	wstring line;
	getline(input, line);
	if (input.eof()) {
		return false;
	}

	wstringstream lineStream(line);
	lineStream.read(timestamp, TIMESTAMP_LENGTH);

	lineStream >> username;
	while (!lineStream.eof()) {
		wchar_t c = lineStream.get();
		if (c == L'@') {
			wstring to = readUsername(lineStream);
			if (!to.empty()) {
				readMentions.emplace(username, to, timestamp);
			}
		}
	}

	return !input.eof() && input.good();
}

wstring TwitterReader::readUsername(wstringstream& input) const
{
	wstringstream usernameStream;
	wchar_t c;
	while (isUsernameCharacter(c = input.peek())) {
		input.ignore();
		usernameStream << c;
	}

	wstring username = usernameStream.str();
	transform(username.begin(), username.end(), username.begin(), towlower);
	return username;
}

constexpr bool TwitterReader::isUsernameCharacter(wchar_t c)
{
	return iswalnum(c) || c == L'_';
}

bool TwitterReader::hasMention() const
{
	return !readMentions.empty();
}

Mention TwitterReader::getMention()
{
	if (!hasMention()) {
		throw runtime_error("No remaining mentions");
	}

	Mention m = readMentions.front();
	readMentions.pop();

	return m;
}
