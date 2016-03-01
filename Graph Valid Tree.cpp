///@file	Graph Valid Tree
///@author	zhaowei
///@date	2016.01.30
///@version	1.0

///@date	2016.03.01
///@version	1.1

#include <vector>
using namespace std;

class Solution_v1 {
public:
	///@brief	判断给定的一组边能否构成一棵树
	///@param	n		节点数
	///@param	edges	边集合
	///@note	1. 判断一组无向边能否构成树有两点：首先这个无向图没有环；其次该无向图是连通图。
	//			2. 通过一个数组来保存所有节点的最深父节点，每当插入一个新的边时，同时检查边的两节点的最深父节点是否相同，如果相同则说明存在环；
	//			3. 如果无向图是连通图，那么边数 = 节点数 - 1。
	bool validTree(int n, vector<pair<int, int>>& edges) {		
		vector<int> parents(n, 0);
		for (int i = 0; i != n; i++)	parents[i] = i;	//初始化父节点数组
		for (int i = 0; i != edges.size(); i++) {
			int f = edges[i].first;
			int s = edges[i].second;
			while (f != parents[f])	f = parents[f];
			while (s != parents[s])	s = parents[s];
			if (parents[f] == parents[s])	return false;	//	存在环路
			parents[s] = f;	//	插入新边
		}
		return edges.size() == n - 1;	//	是否为连通图
	}
};

class Solution {
public:
	bool validTree(int n, vector<pair<int, int>>& edges) {
		vector<int> parents(n, 0);
		for (int i = 0; i != n; i++)	parents[i] = i;
		for (int i = 0; i != edges.size(); i++) {
			int f = edges[i].first;
			int s = edges[i].second;
			while (f != parents[f])	f = parents[f];
			while (s != parents[s])	s = parents[s];
			if (parents[f] == parents[s])	return false;
			parents[s] = f;
		}
		return n == edges.size() + 1;
	}
};

int main() {
	Solution_v1 s1;
	vector<pair<int, int>> edges;
	edges.push_back(make_pair(0, 1));
	edges.push_back(make_pair(1, 2));
	edges.push_back(make_pair(2, 3));
	edges.push_back(make_pair(1, 3));
	edges.push_back(make_pair(1, 4));
	bool r1 = s1.validTree(5, edges);
	Solution slt;
	bool rslt = slt.validTree(5, edges);
	return 0;
}