///@file	Minimum Height Trees
///@author	zhaowei
///@date	2016.03.19
///@version	1.0

#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
	///@brief	给定一个无向图，有n个节点，n-1条边，找到所有深度最浅的树根节点
	///@param	n	节点数目
	///@param	edges	边
	///@return	返回所有最浅树的根节点编号
	///@note	1. bfs；
	//			2. 如果一个无向图是一棵树，那么最浅树的根节点应该是最靠近中心的节点；
	//			3. 通过邻接表来保存每个节点的相邻节点；
	//			4. 找到叶子节点，然后从叶子节点开始向内层中心（根节点）回溯即可；
	//			5. 注意<unordered_set>的erase()函数只能接收迭代器类型的形参；
	//			6. 时间复杂度为O(n)，空间复杂度为O(n)，其中n为节点数目。
	vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
		vector<unordered_set<int>> adj(n, unordered_set<int>());	//	邻接边表
		for (int i = 0; i != edges.size(); i++) {
			adj[edges[i].first].insert(edges[i].second);
			adj[edges[i].second].insert(edges[i].first);
		}
		vector<int> current;
		if (n == 1) {
			current.push_back(0);
			return current;
		}

		//	找到叶子节点
		for (int i = 0; i != adj.size(); i++)
			if (adj[i].size() == 1)	current.push_back(i);

		//	bfs
		while (1) {
			vector<int> next;
			for (int i = 0; i != current.size(); i++) {
				for (unordered_set<int>::iterator j = adj[current[i]].begin(); j != adj[current[i]].end(); j++) {
					adj[*j].erase(current[i]);
					if (adj[*j].size() == 1)	next.push_back(*j);
				}
			}
			if (next.empty())	return current;
			current = next;
		}
	}
};

int main() {
	int n = 6;
	int edg[5][2] = {{0, 3}, {1, 3}, {2, 3}, {4, 3}, {5, 4}};
	vector<pair<int, int>> edges;
	for (int i = 0; i != 5; i++) {
		edges.push_back(make_pair(edg[i][0], edg[i][1]));
	}
	Solution slt;
	vector<int> rslt = slt.findMinHeightTrees(n, edges);
	return 0;
}