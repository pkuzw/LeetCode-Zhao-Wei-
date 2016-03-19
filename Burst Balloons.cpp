///@file	Burst Balloons
///@author	zhaowei
///@date	2016.03.19
///@version	1.0

#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

class Solution {
public:
	///@brief	给定一组数，每次选中一个数，得到它前后和其本身的乘积，然后将该数字去掉，问最后的累加和最大是多少
	///@param	nums	数组
	///@return	返回最大值
	///@note	1. 动态规划；
	//			2. 设dp[i][j]表示数组从nums[i]到nums[j]的最大和，递推关系式为dp[i][j] = dp[i][k-1] + dp[k-1] * dp[k] * dp[k+1] + dp[k+1][j]；
	//			3. 时间复杂度为O(n^3)，空间复杂度为O(n^2)。
	int maxCoins(vector<int>& nums) {
		if (nums.empty())	return 0;
		int n = nums.size() + 2;

		vector<int> balloons(n, 0);
		balloons[0] = 1;
		balloons[n-1] = 1;
		for (int i = 1; i < n - 1; i++)	balloons[i] = nums[i-1];

		vector<vector<int>> dp(n, vector<int>(n, 0));
		for (int k = 2; k < n; k++) {
			for (int left = 0; left < n - k; left++) {
				int right = left + k;
				for (int i = left + 1; i < right; i++) {
					dp[left][right] = max(dp[left][right], dp[left][i] + balloons[left]*balloons[i]*balloons[right] + dp[i][right]);
				}
			}
		}
		return dp[0][n-1];
	}
};

int main() {
	vector<int> nums;
	int n[4] = {3, 1, 5, 8};
	for (int i = 0; i < 4; i++)	nums.push_back(n[i]);
	Solution slt;
	int rslt = slt.maxCoins(nums);
	return 0;
}