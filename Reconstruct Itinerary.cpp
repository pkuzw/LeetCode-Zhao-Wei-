///@file	Reconstruct Itinerary
///@author	zhaowei
///@date	2016.03.28
///@version	1.0

#include <vector>
#include <string>
#include <set>
#include <map>
using namespace std;

class Solution {
public:
	///@brief	给出一组有向边，找到一个路径，能够遍历所有边，不能重复经过同一条边。起始点为"JFK"。
	///@param	tickets	飞机票
	///@return	返回按照字母表顺序排列最小的节点遍历顺序
	///@note	1. 递归；
	//			2. 用邻接边表来表示有向图，边表用<multiset>来保存，这样能够维护机场的字母顺序；
	//			3. 从"JFK"出发，一直向后找，直到下不去之后返回。
	//			4. 时间复杂度为？
	vector<string> findItinerary(vector<pair<string, string>> tickets) {
		for (int i = 0; i != tickets.size(); i++)	edges[tickets[i].first].insert(tickets[i].second);		
		dfs("JFK");
		return vector<string>(route.rbegin(), route.rend());
	}

	///@brief	递归辅助函数
	///@param	airport	机场名
	void dfs(string airport) {
		while (!edges[airport].empty()) {
			string next = *edges[airport].begin();
			edges[airport].erase(edges[airport].begin());
			dfs(next);
		}
		route.push_back(airport);
	}

	map<string, multiset<string>> edges;	//	邻接边表
	vector<string> route;	//	路径机场名
};

int main() {
	string ticks[5][2] = {{"JFK","SFO"},{"JFK","ATL"},{"SFO","ATL"},{"ATL","JFK"},{"ATL","SFO"}};
	vector<pair<string, string>> tickets;
	for (int i = 0; i != 5; i++) {
		tickets.push_back(make_pair(ticks[i][0], ticks[i][1]));
	}
	Solution slt;
	vector<string> rslt = slt.findItinerary(tickets);
	return 0;
}