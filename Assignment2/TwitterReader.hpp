#ifndef TWITTER_READER_H
#define TWITTER_READER_H

#include <string>
#include <iostream>
#include <queue> 
#include <locale>

using namespace std;

struct Mention {
	string from;
	string to;
	string timestamp;
	int amount;

	Mention(string from = "", string to = "", string timestamp = "", int amount = 1) :
		from(from),
		to(to),
		timestamp(timestamp),
		amount(amount)
	{
	}
	Mention(const Mention&) = default;
};

class TwitterReader {
	public:
		TwitterReader();

		bool read(istream& input);
		bool hasMention() const;
		Mention getMention();

	private:
		static constexpr int TIMESTAMP_LENGTH = 20;

		queue<Mention> readMentions;

		bool isUsername(const string& word) const;
		string getUsername(const string& word) const;
};

#endif
