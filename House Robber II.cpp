///@file	House Robber II
/*
After robbing those houses on that street, the thief has found himself a new place for his thievery so that he will not get too much attention. This time, all houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, the security system for these houses remain the same as for those in the previous street.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.
*/
///@author	zhaowei
///@date	2015.08.02
///@version	1.0

#include <vector>

using namespace std;

class Solution {
public:
	///@brief	计算劫匪抢劫环装房屋的最大金额
	///@param	nums	房屋金额
	///@return	返回最大抢劫金额
	///@note	利用"House Robber"中的算法，将环装房屋改成线状排列的，分别去掉第一个屋子和最后一个屋子来计算最大金额，然后取其最大值即可。
	//			时间复杂度为O(n)，空间复杂度为O(n)。
	int rob(vector<int>& nums) {
		if (nums.empty())		return 0;
		if (nums.size() == 1)	return nums[0];

		vector<int> rooms1(nums.begin(), --nums.end());
		vector<int> rooms2(++nums.begin(), nums.end());
		int n1 = rob_line(rooms1);
		int n2 = rob_line(rooms2);

		return n1 > n2 ? n1 : n2;
	}

private:
	///@brief	计算劫匪能够抢劫的最大金额
	///@param	每家的金额
	///@return	返回最大抢劫金额
	/* @note	动态规划：设dp[i]表示抢前i家的最大金额。初始条件dp[0] = nums[0]，dp[1] = max(nums[0], nums[1])。递推关系式为
				dp[i] = max(dp[i-2]+nums[i], dp[i-1])。时间复杂度为O(n)，空间复杂度为O(n)。*/
	int rob_line(vector<int>& nums) {
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