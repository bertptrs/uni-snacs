#ifndef TWITTER_READER_H
#define TWITTER_READER_H

#include <string>
#include <iostream>
#include <queue> 
#include "utility.hpp"

using namespace std;

struct Mention {
	string from;
	string to;
	string timestamp;
	int amount;

	Mention(const wstring& from, const wstring& to, const wstring& timestamp, int amount = 1) :
		from(unwiden(from)),
		to(unwiden(to)),
		timestamp(unwiden(timestamp)),
		amount(amount)
	{
	}
	Mention(const Mention&) = default;
};

class TwitterReader {
	public:
		TwitterReader();

		bool read(wistream& input);
		bool hasMention() const;
		Mention getMention();

	private:
		static constexpr int TIMESTAMP_LENGTH = 20;

		queue<Mention> readMentions;

		wstring readUsername(wstringstream& input) const;
		inline static constexpr bool isUsernameCharacter(wchar_t c);
};

#endif
