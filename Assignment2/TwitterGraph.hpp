#ifndef TWITTER_GRAPH_H
#define TWITTER_GRAPH_H

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

class TwitterGraph
{
	public:
		TwitterGraph(const string& filename);
		TwitterGraph(const TwitterGraph&) = default;
		TwitterGraph(TwitterGraph&&) = default;

	private:
		struct Entry {
			int to;
			int count;
			string timestamp;
			bool operator < (const Entry&) const;
		};

		unordered_map<string, int> userToCodeMap;
		unordered_map<int, string> codeToUserMap;
		vector<vector<Entry>> entries;
		unsigned int maxUserCode;

		int getOrCreateCode(const string& username);
};

#endif
