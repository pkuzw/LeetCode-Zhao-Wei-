///@file	Longest Increasing Subsequence
///@author	zhaowei
///@date	2016.03.14
///@version	1.0

#include <vector>
using namespace std;

class Solution {
public:
	///@brief	寻找最长的递增子序列
	///@param	nums	数组
	///@return	返回最长递增子序列的长度
	///@note	1. 动态规划；
	//			2. 设dp[i]表示前i个数中最长的递增子序列长度，初始化dp[i] = 1；
	//			3. 递推方程为dp[i] = (dp[j] + 1) > dp[i] ? dp[j] + 1 : dp[i]；其中0 <= j < i；
	//			4. 时间复杂度为O(n^2)，空间复杂度为O(n)。其中n为数组长度。
	int lengthOfLIS(vector<int>& nums) {
		if (nums.empty())	return 0;
		vector<int> dp(nums.size(), 1);
		for (int i = 1; i < nums.size(); i++)
			for (int j = 0; j < i; j++)
				if (nums[j] < nums[i])
					if (dp[j] + 1 > dp[i])	dp[i] = dp[j] + 1;				

		int rslt = 0;
		for (int i = 0; i < nums.size(); i++)	rslt = max(rslt, dp[i]);
		return rslt;
	}
};

int main() {
	int n[8] = {10, 9, 2, 5, 3, 7, 101, 18};
	vector<int> nums;
	for (int i = 0; i != 8; i++)	nums.push_back(n[i]);
	Solution slt;
	int rslt = slt.lengthOfLIS(nums);
	return 0;
}