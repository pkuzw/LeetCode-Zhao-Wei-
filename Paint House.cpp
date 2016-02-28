///@file	Paint House
///@author	zhaowei
///@date	2016.01.29
///@version	1.0

///@date	2016.02.28
///@version	1.1

#include <vector>
using namespace std;

class Solution_v1 {
public:
	///@brief	刷房子的最小花费，相邻房子的颜色不能相同
	///@param	costs	给每栋房子刷不同颜色油漆的花费
	///@return	返回刷完一排房子的最小花费
	///@note	1. 动态规划；
	//			2. 设dp[i][j]为给第i栋房子刷第j种颜色的前i栋房子的最小花费；
	//			3. 初始化为dp[0][j] = costs[0][j]；
	//			4. 递推关系式为dp[i][j] = min(dp[i-1][k] + costs[i][j])，0 <= k <= 2且 k != j；
	//			5. 时间复杂度为O(n)，空间复杂度为O(n)，n为房屋的数量。
	int minCost(vector<vector<int>>& costs) {
		if (costs.empty())	return 0;
		const int len = costs.size();
		vector<vector<int>> dp(len, vector<int>(3, 0));
		for (int j = 0; j != 3; j++)	dp[0][j] = costs[0][j];
		for (int i = 1; i != len; i++) {
			dp[i][0] = costs[i][0] + min(dp[i-1][1], dp[i-1][2]);
			dp[i][1] = costs[i][1] + min(dp[i-1][0], dp[i-1][2]);
			dp[i][2] = costs[i][2] + min(dp[i-1][0], dp[i-1][1]);
		}
		return min(min(dp.back()[0], dp.back()[1]), dp.back()[2]);
	}
};

class Solution {
public:
	int minCost(vector<vector<int>>& costs) {
		if (costs.empty())	return 0;
		const int len = costs.size();
		vector<vector<int>> dp(len, vector<int>(3, 0));
		for (int i = 0; i != 3; i++)	dp[0][i] = costs[0][i];
		for (int i = 1; i != len; i++) {
			dp[i][0] = costs[i][0] + min(dp[i-1][1], dp[i-1][2]);
			dp[i][1] = costs[i][1] + min(dp[i-1][0], dp[i-1][2]);
			dp[i][2] = costs[i][2] + min(dp[i-1][0], dp[i-1][1]);
		}
		return min(dp.back()[0], min(dp.back()[1], dp.back()[2]));
	}
};

int main() {
	vector<vector<int>> costs;
	for (int i = 0; i != 4; i++) {
		vector<int> cost_one_house(3, 0);
		for (int j = 0; j != 3; j++)
			cost_one_house[j] = (i + 1) * (j + 1);
		costs.push_back(cost_one_house);
	}
	Solution slt;
	int rslt = slt.minCost(costs);
	Solution_v1 s1;
	int r1 = s1.minCost(costs);
	return 0;
}