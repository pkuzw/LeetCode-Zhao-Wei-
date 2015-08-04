///@file	Maximum Product Subarray
/*
Find the contiguous subarray within an array (containing at least one number) which has the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.
*/
///@author	zhaowei
///@date	2015.08.04
///@version	1.0
#include <vector>

using namespace std;

class Solution {
public:
	///@brief	计算整数型数组最大的连续子串乘积
	///@param	nums	数组
	///@return	返回最大的连续子串乘积
	/* @note	动态规划：dp_max[i]表示包含nums[i]的连续元素的最大值，dp_min[i]表示包含nums[i]的连续元素的最小值。初始条件是dp_max[0] = nums[0]，
				dp_min[0] = nums[0]，递推关系式为dp_max[i] = max(nums[i], nums[i]*dp_max[i-1], nums[i]*dp_min[i-1])，
				dp_min[i] = min(nums[i], nums[i]*dp_max[i-1], nums[i]*dp_min[i-1])。在求最大值的同时计算最小值是因为负数的最小值乘以负数
				就会转化成正数。时间复杂度为O(n)，空间复杂度为O(1)。*/
	int maxProduct(vector<int>& nums) {
		int dp_max = nums[0], dp_min = nums[0];
		int rslt = nums[0];
		for (int i = 1; i < nums.size(); i++)
		{
			int tmp = dp_max;
			dp_max = max(max(nums[i], dp_max*nums[i]), dp_min*nums[i]);
			dp_min = min(min(nums[i], tmp*nums[i]), dp_min*nums[i]);
			rslt = max(dp_max, rslt);
		}
		return rslt;
	}
};

int main()
{
	vector<int> nums;
	nums.push_back(-4);
 	nums.push_back(-3);
 	nums.push_back(-2);
// 	nums.push_back(-1);
	Solution slt;
	int rslt = slt.maxProduct(nums);
	return 0;
}