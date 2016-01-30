///@file	Paint House II
///@author	zhaowei
///@date	2016.01.30
///@version	1.0
//	如何把时间复杂度降到O(nk)？

#include <vector>
using namespace std;

class Solution {
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
	Solution slt;
	int rslt = slt.minCostII(costs);

	return 0;
}