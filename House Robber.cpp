///@file	House Robber
/*
You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.
*/
///@author	zhaowei
///@date	2015.07.28
///@version	1.0

///@date	2015.08.11
///@version	2.0

#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	计算劫匪能够抢劫的最大金额
	///@param	每家的金额
	///@return	返回最大抢劫金额
	/* @note	动态规划：设dp[i]表示抢前i家的最大金额。初始条件dp[0] = nums[0]，dp[1] = max(nums[0], nums[1])。递推关系式为
				dp[i] = max(dp[i-2]+nums[i], dp[i-1])。时间复杂度为O(n)，空间复杂度为O(n)。*/
	int rob(vector<int>& nums) {
		if (nums.empty())		return 0;
		if (nums.size() == 1)	return nums[0];

		vector<int> dp(nums.size(), 0);
		dp[0] = nums[0];
		dp[1] = max(nums[0], nums[1]);

		for (int i = 2; i != nums.size(); i++)
		{
			dp[i] = max(nums[i]+dp[i-2], dp[i-1]);
		}

		return dp.back();
	}
};

class Solution {
public:
	int rob(vector<int>& nums) {
		if (nums.empty())		return 0;
		if (nums.size() == 1)	return nums[0];

		vector<int> dp(nums.size(), 0);
		dp[0] = nums[0];
		dp[1] = max(nums[0], nums[1]);

		for (int i = 2; i != nums.size(); i++)
			dp[i] = max(dp[i-1], nums[i] + dp[i-2]);
		return dp.back();
	}
};

int main()
{
	int n[4] = {10,1,2,17};
	vector<int> nums;
	for (int i = 0; i < 4; i++)
		nums.push_back(n[i]);

	Solution slt;
	int rslt = slt.rob(nums);
	return 0;
}