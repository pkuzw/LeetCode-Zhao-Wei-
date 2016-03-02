///@file	Alien Dictionary
///@author	zhaowei
///@date	2016.02.25
///@version	1.0

///@date	2016.03.02
///@version	1.1

#include <string>
#include <vector>
#include <map>
#include <set>
#include <deque>

using namespace std;

class Solution_v1 {
public:
	///@brief	通过已知的字典序好序的单词表，给出对应的字典序
	///@param	words	单词表
	///@return	返回对应字典序
	///@note	1. 拓扑排序；2. BFS。
	string alienOrder(vector<string>& words) {
		map<char, set<char>> adjacent_list;	// 词典中的字符'顺'序
		map<char, set<char>> adjacent_list_reverse;	//	词典中的字符逆序
		set<char> characters;
		// 建立按照字典序排列的有向图
		for (int i = 0; i < words.size(); i++) {
			for (int k = 0; k < words[i].size(); k++) 
				characters.insert(words[i][k]);	//	set中的key是唯一的，对于已经存在的元素，不插入当前元素，返回已存在元素的迭代器。
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
			if (adjacent_list_reverse[*char_itr].empty()) BFS_visit.push_back(*char_itr);	// 压入入度为0的节点

		int count = 0;
		string result;
		// 拓扑排序
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

class Solution {
public:
	///@note	1. 拓扑排序，用map<char, set<char>>来模拟正邻接表和逆邻接表；
	//			2. 进行拓扑排序时用BFS实现。
	string alienOrder(vector<string>& words) {
		map<char, set<char>> adj_list, adj_list_reverse;
		set<char> characters;		
		for (int i = 0; i != words.size(); i++) {
			for (int j = 0; j != words[i].size(); j++)	characters.insert(words[i][j]);
			for (int j = i + 1; j != words.size(); j++) {
				int k = 0;
				while (k < words[i].size() && k < words[j].size() && words[i][k] == words[j][k])	k++;
				if (k < words[i].size() && k < words[j].size()) {
					adj_list[words[i][k]].insert(words[j][k]);
					adj_list_reverse[words[j][k]].insert(words[i][k]);
				}
			}
		}
		string alphabet;
		deque<char> deq;
		int cnt = 0;
		for (set<char>::iterator i = characters.begin(); i != characters.end(); i++)
			if (adj_list_reverse[*i].empty())	deq.push_back(*i);
		while (!deq.empty()) {
			char j = deq.front();
			deq.pop_front();
			alphabet += j;
			cnt++;
			for (set<char>::iterator i = adj_list[j].begin(); i != adj_list[j].end(); i++) {
				adj_list_reverse[*i].erase(adj_list_reverse[*i].find(j));
				if (adj_list_reverse[*i].empty())	deq.push_back(*i);
			}
		}
		if (cnt != characters.size())	return "";
		return alphabet;
	}
};

int main() {
	string strs[2] = {"zy", "zx"};
	vector<string> words;
	for (int i = 0; i != 2; i++)	words.push_back(strs[i]);
	Solution slt;
	string rslt = slt.alienOrder(words);
	return 0;
}
