///@file	Alien Dictionary
///@author	zhaowei
///@date	2016.02.22
///@version	1.0

#include <string>
#include <vector>
#include <map>
#include <set>
#include <deque>

using namespace std;

class Solution {
public:
	///@brief	通过已知的字典序好序的单词表，给出对应的字典序
	///@param	words	单词表
	///@return	返回对应字典序
	///@note	1. 拓扑排序；2. BFS。
	string alienOrder(vector<string>& words) {
		map<char, set<char>> adjacent_list;
		map<char, set<char>> adjacent_list_reverse;
		set<char> characters;
		// 建立按照字典序排列的有向图
		for (int i = 0; i < words.size(); i++) {
			for (int k = 0; k < words[i].size(); k++) 
				characters.insert(words[i][k]);
			for (int j = i+1; j < words.size(); j++) {
				int k = 0;
				while (k < words[i].size() && k < words[j].size() && words[i][k] == words[j][k]) k++;
				if (k < words[i].size() && k < words[j].size()) {
					adjacent_list[words[i][k]].insert(words[j][k]);
					adjacent_list_reverse[words[j][k]].insert(words[i][k]);
				}
			}
		}

		deque<char> BFS_visit;
		for (set<char>::iterator char_itr = characters.begin(); char_itr != characters.end(); char_itr++)
			if (adjacent_list_reverse[*char_itr].empty()) BFS_visit.push_back(*char_itr);

		int count = 0;
		string result;
		while (!BFS_visit.empty()) {
			char cur = BFS_visit.front();
			BFS_visit.pop_front();
			result += cur;
			count++;
			for (set<char>::iterator neigh_itr = adjacent_list[cur].begin(); neigh_itr != adjacent_list[cur].end(); neigh_itr++) {
				char next = *neigh_itr;
				adjacent_list_reverse[next].erase(adjacent_list_reverse[next].find(cur));
				if (adjacent_list_reverse[next].empty()) BFS_visit.push_back(next);
			}
		}

		if (count != characters.size()) return "";
		return result;
	}
};

int main() {
	vector<string> words;
	return 0;
}
