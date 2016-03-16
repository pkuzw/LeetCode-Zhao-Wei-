///@file	Number of Islands II
///@author	zhaowei
///@date	2016.03.16
///@version	1.0

#include <vector>
using namespace std;

class Solution {
public:
	///@brief	对于二维矩阵，0表示水，1表示陆地，给定一组二维下标来表示每一次会将该坐标上的1转换为0，求每次转换后的岛屿数目
	///@param	m	矩阵行数
	///@param	n	矩阵列数
	///@param	positions	待转换的二维下标数组
	///@return	返回每次操作后岛屿的数目
	///@note	1. 并查集；
	//			2. 使用压缩路径法尽量减少树的高度；
	//			3. 每次进行一次0-1转换，就检查该点的邻居是否和原来的1不相邻，然后将二者做Union操作；
	//			4. 对每一块陆地进行标记时，通过行列坐标转换，将其转换为1维的；
	//			5. 时间复杂度为O(klog(mn))，其中k为转换点数目，m和n分别是矩阵的行列数。
	vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) {
		vector<int> rslt;
		if (m <= 0 || n <= 0)	return rslt;
		int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};	//	方向，上下左右
		int count = 0;	//	陆地块数
		vector<int> roots(m * n, -1);

		for (int i = 0; i != positions.size(); i++) {
			int root = n * positions[i].first + positions[i].second;
			roots[root] = root;
			count++;

			//	转换点的邻居
			for (int j = 0; j != 4; j++) {
				int x = positions[i].first + dir[j][0];
				int y = positions[i].second + dir[j][1];
				int nb = n * x + y;

				if (x < 0 || x >= m || y < 0 || y >= n || roots[nb] == -1)	continue;

				int root_nb = findIsland(roots, nb);
				if (root_nb != root) {	//	如果二者属于不同的块，则做Union操作
					roots[root] = root_nb;
					root = root_nb;
					count--;
				}
			}
			rslt.push_back(count);
		}
		return rslt;
	}

	///@brief	找到当前元素的标记符，相当于Find操作
	///@param	roots	标记符数组
	///@param	id		当前元素
	///@return	返回当前元素的真正根节点
	int findIsland(vector<int> roots, int id) {
		while (id != roots[id]) {
			roots[id] = roots[roots[id]];	//	路径压缩
			id = roots[id];
		}
		return id;
	}
};

int main() {
	return 0;
}