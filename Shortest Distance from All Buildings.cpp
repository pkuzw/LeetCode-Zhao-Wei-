///@file	Shortest Distance from All Buildings
///@author	zhaowei
///@date	2016.03.21
///@version	1.0

#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
	///@brief	给定一个二维的矩阵，0表示通路，1表示房子，2表示障碍物，找到一个点，使之到达各个房子的距离之和最短，要绕开障碍物，路径只能上下左右四个方向
	///@param	grid	矩阵
	///@return	返回最短路径之和
	///@note	1. bfs；
	//			2. 对于每一幢房子的通路，用-i来表示，在grid上来更新，这样能够避免在visited[m][n]上更新的时间损失。
	//			3. 需要在仔细思考一下其中的细节。
	int shortestDistance(vector<vector<int>>& grid) {
		int m = grid.size(), n = grid[0].size();
		vector<vector<int>> total = grid;	
		int walk = 0;
		int min_dist = -1;
		int delta[5] = {0, 1, 0, -1, 0};
		for (int i = 0; i != m; i++) {
			for (int j = 0; j != n; j++) {
				if (grid[i][j] == 1) {
					min_dist = -1;
					vector<vector<int>> dist = grid;	//	各点到grid[i][j]的距离
					queue<pair<int, int>> q;
					q.push(make_pair(i, j));
					while (!q.empty()) {
						pair<int, int> p = q.front();
						q.pop();
						for (int k = 0; k != 4; k++) {
							int a = p.first + delta[k];
							int b = p.second + delta[k+1];
							if (a >= 0 && a < m && b >= 0 && b < n && grid[a][b] == walk) {
								grid[a][b]--;
								dist[a][b] = dist[p.first][p.second] + 1;
								total[a][b] += dist[a][b] - 1;
								q.push(make_pair(a, b));
								if (min_dist < 0 || min_dist > total[a][b])	min_dist = total[a][b];
							}
						}
					}
					walk--;
				}
			}
		}
		return min_dist;
	}
};

int main() {
	return 0;
}