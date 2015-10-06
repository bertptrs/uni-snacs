#include <fstream>
#include "TwitterGraph.hpp"
#include "TwitterReader.hpp"
#include <map>
#include <algorithm>

TwitterGraph::TwitterGraph(const string& filename) :
	entries({{}}),
	maxUserCode(0)
{
	wifstream file(filename);
	TwitterReader reader;

	while (reader.read(file)) {
		while (reader.hasMention()) {
			Mention mention = reader.getMention();
			int fromCode = getOrCreateCode(mention.from);
			int toCode = getOrCreateCode(mention.to);
			auto& entryList = entries[fromCode];
			Entry entry = {toCode, 1, mention.timestamp};
			auto it = lower_bound(entryList.begin(), entryList.end(), entry);
			if (it != entryList.end() && it->to == toCode) {
				it->count++;
			} else {
				entryList.push_back(entry);
				sort(entryList.begin(), entryList.end());
			}
		}
	}
}

int TwitterGraph::getOrCreateCode(const string& username)
{
	auto it = userToCodeMap.find(username);
	if (it != userToCodeMap.end()) {
		return it->second;
	} else {
		maxUserCode = maxUserCode + 1;
		userToCodeMap[username] = maxUserCode;
		codeToUserMap[maxUserCode] = username;
		entries.emplace_back();
		return maxUserCode;
	}
}

bool TwitterGraph::Entry::operator < (const TwitterGraph::Entry& other) const
{
	return to < other.to;
}
