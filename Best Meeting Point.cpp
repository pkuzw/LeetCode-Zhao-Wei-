///@file	Best Meeting Point
///@author	zhaowei
///@date	2016.03.13
///@version	1.0

#include <vector>
using namespace std;

struct home {
	int i;
	int j;
};

class Solution {
public:
	///@brief	计算棋盘上某一点到达所有'1'的距离之和最短的点
	///@param	grid	棋盘
	///@return	返回最短距离
	///@note	1. 遍历；
	//			2. 直观的想法是将棋盘上的所有点尝试一遍，选出距离之和最小的点，但是也还是有优化的空间；
	//			3. 对于棋盘上的'1'，到达它们距离之和最小的点一定在'1'围起来的圈子里面，所以先找到'1'位置的最大和最小横纵坐标；
	//			4. 然后在这个坐标范围内来寻找最小值点；
	//			5. 时间复杂度为O(mn)，空间复杂度为O(mn)，其中m和n分别是棋盘的行列号。TLE
	int minTotalDistance(vector<vector<int>>& grid) {
		if (grid.empty() || grid[0].empty())	return 0;
		int col_start = INT_MAX, col_end = -1, row_start = INT_MAX, row_end = -1;
		vector<home> home_pos;
		for (int i = 0; i != grid.size(); i++) {
			for (int j = 0; j != grid[i].size(); j++) {
				if (grid[i][j] == 1) {
					home h;
					h.i = i;
					h.j = j;
					home_pos.push_back(h);
					col_start = min(col_start, j);
					col_end = max(col_end, j);
					row_start = min(row_start, i);
					row_end = max(row_end, i);
				}
			}
		}

		int rslt = INT_MAX;
		for (int i = row_start; i <= row_end; i++) {
			for (int j = col_start; j <= col_end; j++) {
				rslt = min(rslt, getTotalDistance(home_pos, i, j));
			}
		}
		return rslt;
	}

	///@brief	计算在(i, j)处到'1'的距离之和
	///@param	home_pos	'1'所在的位置
	///@param	cur_i	当前位置的横坐标
	///@param	cur_j	当前位置的纵坐标
	///@return	返回当前位置（i, j）到所有'1'的距离之和
	int getTotalDistance(const vector<home>& home_pos, const int& cur_i, const int& cur_j) {
		int rslt = 0;
		for (int i = 0; i != home_pos.size(); i++) rslt += abs(home_pos[i].i - cur_i) + abs(home_pos[i].j - cur_j);
		return rslt;
	}
};

int main() {
	vector<vector<int>> grid;
	vector<int> line;
	line.push_back(1);	
	line.push_back(0);
	line.push_back(0);
	line.push_back(0);
	line.push_back(1);
	grid.push_back(line);

	line.clear();
	line.push_back(0);
	line.push_back(0);
	line.push_back(0);
	line.push_back(0);
	line.push_back(0);
	grid.push_back(line);

	line.clear();
	line.push_back(0);
	line.push_back(0);
	line.push_back(1);
	line.push_back(0);
	line.push_back(0);
	grid.push_back(line);

	Solution slt;
	int rslt = slt.minTotalDistance(grid);
	return 0;
}