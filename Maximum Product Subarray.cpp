///@file	Maximum Product Subarray
/*
Find the contiguous subarray within an array (containing at least one number) which has the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.
*/
///@author	zhaowei
///@date	2015.08.04
///@version	1.0

///@date	2015.08.18
///@version	1.1

///@date	2016.01.14
///@version	1.2
#include <vector>

using namespace std;

class Solution_v1 {
public:
	///@brief	计算整数型数组最大的连续子串乘积
	///@param	nums	数组
	///@return	返回最大的连续子串乘积
	/* @note	动态规划：dp_max[i]表示包含nums[i]的连续元素的最大值，dp_min[i]表示包含nums[i]的连续元素的最小值。
				初始条件是dp_max[0] = nums[0]，
				dp_min[0] = nums[0]，递推关系式为dp_max[i] = max(nums[i], nums[i]*dp_max[i-1], nums[i]*dp_min[i-1])，
				dp_min[i] = min(nums[i], nums[i]*dp_max[i-1], nums[i]*dp_min[i-1])。在求最大值的同时计算最小值是因为负数的最小值
				乘以负数就会转化成正数。时间复杂度为O(n)，空间复杂度为O(1)。*/
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

class Solution_v1_1 {
public:
	int maxProduct(vector<int>& nums) {
		vector<int> dp_max(nums.size(), INT_MIN);
		vector<int> dp_min(nums.size(), INT_MAX);
		dp_max[0] = nums[0];
		dp_min[0] = nums[0];
		int rslt = max(INT_MIN, dp_max[0]);
		for (int i = 1; i != nums.size(); i++)
		{
			dp_max[i] = max(nums[i], max(nums[i] * dp_max[i-1], nums[i] * dp_min[i-1]));
			dp_min[i] = min(nums[i], min(nums[i] * dp_max[i-1], nums[i] * dp_min[i-1]));
			rslt = max(rslt, dp_max[i]);
		}
		return rslt;
	}
};

class Solution {
public:
	///@brief	计算整数型数组最大的连续子串乘积
	///@param	nums	数组
	///@return	返回最大的连续子串乘积
	///@note	1. 动态规划；
	//			2. 设dp_max[i]表示包含num[i]之前的所有数的最大乘积，dp_min[i]表示包含num[i]之前的所有数的最小乘积；
	//			3. 初始化dp_max[0] = dp_min[0] = num[0]；
	//			4. 递推关系式为dp_max[i] = max(num[i], dp_max[i-1] * num[i], dp_min[i-1] * num[i])；
	//			5. dp_min[i] = min(num[i], dp_max[i-1] * num[i], dp_min[i-1] * num[i])；
	//			6. 时间复杂度为O(n)，空间复杂度为O(1)。
	int maxProduct(vector<int>& nums) {
		if (nums.empty())	return 0;
		int rslt = nums[0];
		int dp_max = nums[0], dp_min = nums[0];
		for (int i = 1; i < nums.size(); i++) {
			int tmp = dp_max;
			dp_max = max(nums[i], max(nums[i] * dp_max, nums[i] * dp_min));
			dp_min = min(nums[i], min(nums[i] * tmp, nums[i] * dp_min));
			rslt = max(rslt, dp_max);
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
 	nums.push_back(8);
	nums.push_back(4);
	Solution_v1_1 s11;
	int r11 = s11.maxProduct(nums);

	Solution slt;
	int rslt = slt.maxProduct(nums);
	return 0;
}