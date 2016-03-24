///@file	Number of Connected Components in an Undirected Graph
///@author	zhaowei
///@date	2016.03.24
///@version	1.0

#include <vector>
#include <numeric>	//	iota: 从val开始进行累加，对数组指定区域进行赋值
using namespace std;

class Solution {
public:
	///@brief	计算无向图中的块数
	///@param	n	点数
	///@param	edges	边表，其中的元素<i, j>表示顶点i和j之间有一条无向边
	///@return	返回图的连通块数
	///@note	1. 压缩路径的并查集
	//			2. 遍历边表中的每一条边，找到每条边两个顶点的最终父节点，如果二者的父节点相同，则说明它们在一个块中，否则不是。
	int countComponents(int n, vector<pair<int, int>>& edges) {
		vector<int> p(n, 0);
		iota(p.begin(), p.end(), 0);
		for (int i = 0; i != edges.size(); i++) {
			int v = edges[i].first;
			int w = edges[i].second;
			while (v != p[v])	v = p[v] = p[p[v]];
			while (w != p[w])	w = p[w] = p[p[w]];
			p[v] = w;	//	路径压缩，v作为一个子树放在了w的下面
			n -= (v != w);	//	如果v还不等于w，说明二者不在一个块内
		}
		return n;
	}
};

int main() {
	vector<pair<int, int>> edges;
	edges.push_back(make_pair(0, 1));
	edges.push_back(make_pair(1, 2));
	edges.push_back(make_pair(3, 4));
	Solution slt;
	int rslt = slt.countComponents(5, edges);
	return 0;
}