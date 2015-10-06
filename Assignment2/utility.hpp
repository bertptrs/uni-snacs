#ifndef UTILITY_H
#define UTILITY_H

#include <string>

using namespace std;

template<class CharT>
inline string unwiden(const basic_string<CharT>& original)
{
	return string(original.begin(), original.end());
}

#endif
