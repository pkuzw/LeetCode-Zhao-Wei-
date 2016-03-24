///@file	Number of Connected Components in an Undirected Graph
///@author	zhaowei
///@date	2016.03.24
///@version	1.0

#include <vector>
#include <numeric>	//	iota: ��val��ʼ�����ۼӣ�������ָ��������и�ֵ
using namespace std;

class Solution {
public:
	///@brief	��������ͼ�еĿ���
	///@param	n	����
	///@param	edges	�߱����е�Ԫ��<i, j>��ʾ����i��j֮����һ�������
	///@return	����ͼ����ͨ����
	///@note	1. ѹ��·���Ĳ��鼯
	//			2. �����߱��е�ÿһ���ߣ��ҵ�ÿ����������������ո��ڵ㣬������ߵĸ��ڵ���ͬ����˵��������һ�����У������ǡ�
	int countComponents(int n, vector<pair<int, int>>& edges) {
		vector<int> p(n, 0);
		iota(p.begin(), p.end(), 0);
		for (int i = 0; i != edges.size(); i++) {
			int v = edges[i].first;
			int w = edges[i].second;
			while (v != p[v])	v = p[v] = p[p[v]];
			while (w != p[w])	w = p[w] = p[p[w]];
			p[v] = w;	//	·��ѹ����v��Ϊһ������������w������
			n -= (v != w);	//	���v��������w��˵�����߲���һ������
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