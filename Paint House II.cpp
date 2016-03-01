///@file	Paint House II
///@author	zhaowei
///@date	2016.01.30
///@version	1.0

///@date	2016.03.01
///@version	2.0
//	如何把时间复杂度降到O(nk)？

#include <vector>
using namespace std;

class Solution_v1 {
public:
	///@brief	给n栋房子刷k种漆，要求相邻的屋子颜色不能相同，求最小花费。
	///@param	costs	一个n * k的矩阵，costs[i][j]表示给第i栋房子刷第j种漆的花费
	///@return	返回最小花费
	///@note	1. 动态规划；
	///			2. 设dp[i][j]表示给第i栋房子刷第j种漆的前i栋房子的最小花费；
	//			3. 初始化dp[0][j] = costs[0][j]；
	//			4. 递推关系式为dp[i][j] = costs[i][j] + min(dp[i-1][k])，k != j
	//			5. 时间复杂度为O(nk^2)，空间复杂度为O(nk)。
	int minCostII(vector<vector<int>>& costs) {
		if (costs.empty() || costs[0].empty())	return 0;
		int row = costs.size(), col = costs[0].size();
		vector<vector<int>> dp(row, vector<int>(col, 0));
		for (int j = 0; j != col; j++)	dp[0][j] = costs[0][j];
		for (int i = 1; i != row; i++) {
			for (int j = 0; j != col; j++) {
				int min_tmp = INT_MAX;
				for (int k = 0; k != col; k++) {
					if (k == j)	continue;
					min_tmp = min(min_tmp, dp[i-1][k]);
				}
				dp[i][j] = costs[i][j] + min_tmp;
			}
		}
		int rslt = dp[row-1][0];
		for (int j = 0; j != col; j++)	rslt = min(rslt, dp[row-1][j]);
		return rslt;
	}
};

class Solution {
public:
	///@note	1. 动态规划；
	//			2. 用两个临时变量来保存刷前i-1个房子时的最小值和次小值时的颜色；
	//			3. 递推关系式为costs[i][j] += costs[i-1][min_color]；时间复杂度为O(nk)；
	//			4. 然后用现有的输入数组来作为中间结果的存储空间，时间复杂度为O(1)。
	int minCostII(vector<vector<int>>& costs) {
		if (costs.empty() || costs[0].empty())	return 0;
		int n = costs.size();		//	房屋数目
		int k = costs[0].size();	//	颜色数目
		int min1 = -1, min2 = -1;	//	前i-1栋房子最小值和次小值的颜色编号
		for (int i = 0; i != n; i++) {
			int last1 = min1, last2 = min2;
			min1 = -1;
			min2 = -1;
			for (int j = 0; j != k; j++) {
				if (j != last1)	costs[i][j] += last1 < 0 ? 0 : costs[i-1][last1];
				else	costs[i][j] += last2 < 0 ? 0 : costs[i-1][last2];

				//	更新最小值和次小值的颜色编号
				if (min1 < 0 || costs[i][j] < costs[i][min1]) {
					min2 = min1;
					min1 = j;
				}
				else if (min2 < 0 || costs[i][j] < costs[i][min2]) min2 = j;
			}
		}
		return costs[n-1][min1];
	}
};

int main() {
	vector<vector<int>> costs;
	vector<int> cost;
	cost.push_back(1);
	cost.push_back(5);
	cost.push_back(1);
	costs.push_back(cost);
	cost.clear();
	cost.push_back(2);
	cost.push_back(9);
	cost.push_back(4);
	costs.push_back(cost);
	Solution_v1 s1;
	int r1 = s1.minCostII(costs);

	Solution slt;
	int rslt = slt.minCostII(costs);

	return 0;
}