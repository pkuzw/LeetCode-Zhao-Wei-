///@file	Best Meeting Point
///@author	zhaowei
///@date	2016.03.13
///@version	1.0
///@version	2.0
///@version	3.0

#include <vector>
#include <algorithm>
using namespace std;

struct home {
	int i;
	int j;
};

class Solution_v1 {
public:
	///@brief	计算棋盘上某一点到达所有'1'的距离之和最短的点
	///@param	grid	棋盘
	///@return	返回最短距离
	///@note	1. 遍历；
	//			2. 直观的想法是将棋盘上的所有点尝试一遍，选出距离之和最小的点，但是也还是有优化的空间；
	//			3. 对于棋盘上的'+1'，到达它们距离之和最小的点一定在'1'围起来的圈子里面，所以先找到'1'位置的最大和最小横纵坐标；
	//			4. 然后在这个坐标范围内来寻找最小值点；
	//			5. 时间复杂度为O(mnk)，空间复杂度为O(mnk)，其中m和n分别是棋盘的行列号，k是1的数目。TLE。
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

class Solution_v2 {
public:
	///@note	1. 考虑在一维的情况。应该是选择'1'所在点横坐标平均值点；
	//			2. 二维的情况是类似的，也是应该选择1所在点的横坐标和纵坐标的平均值点；
	//			3. 时间复杂度为O(mn)，m和n分别是棋盘的行列数。
	//			4. WA，跑不过[[1,1,0,0,0,1],[0,0,1,0,0,0],[0,1,1,0,0,0],[0,0,1,0,1,0],[0,0,0,0,0,0],[0,0,0,0,0,0],[0,0,0,0,0,1],[0,1,0,0,0,0],[0,1,0,0,0,0],[0,0,0,0,1,0],[0,0,0,0,0,0],[1,1,1,1,1,1],[0,1,0,0,1,1],[0,0,0,1,1,0],[0,1,0,0,0,0],[1,1,1,1,0,1],[0,0,0,0,0,0]]
	int minTotalDistance(vector<vector<int>>& grid) {
		if (grid.empty() || grid[0].empty())	return 0;
		vector<home> home_pos;
		for (int i = 0; i != grid.size(); i++) {
			for (int j = 0; j != grid[i].size(); j++) {
				if (grid[i][j] == 1) {
					home h;
					h.i = i;
					h.j = j;
					home_pos.push_back(h);
				}
			}
		}
		int general_i = 0, general_j = 0;
		for (int i = 0; i != home_pos.size(); i++) {
			general_i += home_pos[i].i;
			general_j += home_pos[i].j;
		}
		general_i /= home_pos.size();
		general_j /= home_pos.size();

		int rslt = INT_MAX;
		for (int i = general_i - 1; i <= general_i + 1; i++) {
			for (int j = general_j - 1; j <= general_j + 1; j++) {
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

class Solution {
public:
	///@note	1. 在v2.0的基础上，考虑横纵坐标的中位数点，而非平均值点即可。
	//			2. nth_element(begin(), begin + n, end())能够使数组在第n个位置的元素是排好序的那个元素，其他位置不一定；包含在<algorithm>中；
	//			3. vector::emplacement_back() == push_back()；
	//			4. 时间复杂度为O(mn)，其中m和n为棋盘的行列数；空间复杂度为O(k)，k为'1'元素的数目。
	int minTotalDistance(vector<vector<int>>& grid) {
		if (grid.empty() || grid[0].empty())	return 0;
		vector<int> cols, rows;
		for (int i = 0; i != grid.size(); i++) {
			for (int j = 0; j != grid[0].size(); j++) {
				if (grid[i][j] == 1) {
					rows.push_back(i);
					cols.push_back(j);
				}
			}
		}
		int med_i = rows[rows.size()/2];	//	中位数横坐标
		nth_element(cols.begin(), cols.begin() + cols.size() / 2, cols.end());
		int med_j = cols[cols.size()/2];	//	中位数纵坐标
		int rslt = 0;
		for (int i = 0; i != rows.size(); i++) rslt += abs(rows[i] - med_i) + abs(cols[i] - med_j);
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